
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "EPwmSetup.h"
#include "ADC_all.h"
#include "math.h"
#include "Example_posspeed.h"   // Example specific Include file
#include "Control.h"

extern float  	theta_m;			//机械角速度
extern float	Udc;
extern POSSPEED qep_posspeed;
extern float v1[2000],v2[2000],v3[2000];
extern unsigned int viewcount,viewcountFlag,RelayFlag,TcountFlag,StopFlag,testcount;
extern float theta_r,Grid_uab,Grid_ubc,cos_theta_Us;
extern float ura_r_ref,urb_r_ref,urc_r_ref,Grid_uab,ird_p,irq_p;
extern int theta_raw0,delta_N0,delta_N,theta_raw_view1,theta_raw_view2,theta_raw_view3;
extern float view_w0,view_theta,viewd,viewq;
unsigned int countFlag=0,Ksatrt=0;
int vt=0;
//float	ParameterKRef=0;
  
/***********************************************************************	 
函数名称： void InitEPwm1forSPWM(void)
函数功能:ePWM1端口初始化
输入：无  
输出：无		
***********************************************************************/	
void InitEPwm1forSPWM(void)
{

   	EPwm1Regs.TBPRD = CarryPRD;                    // Set timer period
   	EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   	EPwm1Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

  	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Setup compare
   	EPwm1Regs.CMPA.half.CMPA =CarryPRD/2;

   // Set actions
   	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on Zero
   	EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
   	EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;

   // Active Low PWMs - Setup Deadband
  	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   	EPwm1Regs.DBCTL.bit.POLSEL =DB_ACTV_LOC; //DB_ACTV_HIC;
   	EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm1Regs.DBRED = DeadTime;
	EPwm1Regs.DBFED = DeadTime;

	// Interrupt where we will change the Deadband
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;	  // Select INT on Zero event
	EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
	
}
/***********************************************************************	 
函数名称： void InitEPwm2forSPWM(void)
函数功能:ePWM2端口初始化
输入：无  
输出：无		
***********************************************************************/
void InitEPwm2forSPWM(void)
{

   	EPwm2Regs.TBPRD = CarryPRD;                        // Set timer period
   	EPwm2Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   	EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   	EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

  	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Setup compare
   	EPwm2Regs.CMPA.half.CMPA =CarryPRD/2;

   // Set actions
   	EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on Zero
   	EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	EPwm2Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
   	EPwm2Regs.AQCTLB.bit.CAD = AQ_SET;

   // Active Low PWMs - Setup Deadband
  	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   	EPwm2Regs.DBCTL.bit.POLSEL =DB_ACTV_LOC;;// DB_ACTV_HIC;
   	EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm2Regs.DBRED =DeadTime;
	EPwm2Regs.DBFED =DeadTime;

	// Interrupt where we will change the Deadband
	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;  // Select INT on Zero event
	EPwm2Regs.ETSEL.bit.INTEN = 1;                // Enable INT
	EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
	
}

/***********************************************************************	 
函数名称： void InitEPwm3forSPWM(void)
函数功能:ePWM3端口初始化
输入：无  
输出：无		
***********************************************************************/
void InitEPwm3forSPWM(void)
{

   	EPwm3Regs.TBPRD = CarryPRD;                        // Set timer period
   	EPwm3Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   	EPwm3Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   	EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

  	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Setup compare
   	EPwm3Regs.CMPA.half.CMPA = CarryPRD/2;

   // Set actions
   	EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on Zero
   	EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	EPwm3Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
   	EPwm3Regs.AQCTLB.bit.CAD = AQ_SET;

   // Active Low PWMs - Setup Deadband
  	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC;;//DB_ACTV_HIC;
   	EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm3Regs.DBRED = DeadTime;
	EPwm3Regs.DBFED = DeadTime;

	// Interrupt where we will change the Deadband
	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;  // Select INT on Zero event
	EPwm3Regs.ETSEL.bit.INTEN = 1;                // Enable INT
	EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
	
}
/***********************************************************************	 
函数名称：interrupt void epwm1_isr(void)
函数功能:ePWM1中断函数
输入：无  
输出：无		
***********************************************************************/
interrupt void epwm1_isr(void)
{

	/***************计算占空比**********************************/ 
			    
	GetAdcData();
    GetUdcData();       
    theta_m=qep_posspeed.calc(&qep_posspeed);   //获取机械角度
    Control();	
   /*if(RelayFlag==1&&viewcountFlag==0)
   	{
   		v1[viewcount]=viewd;//		//查看参数
   		v2[viewcount]=viewq;//cos(theta_r);
   		v3[viewcount]=view_theta;    //查看参数
   		vt++;
   		if(vt>=5)
   	   {
   		viewcount++;
   		vt=0;
   	   }
   		//viewcount++;
   		if(viewcount>=2000)
   		{
   			viewcount=0;
   			viewcountFlag=1;
   		}
   	}*/
     if(StopFlag==0&&viewcountFlag==0)
     {
    	 Ksatrt=1;
    	 vt++;
    	 if(vt>5000)
    	 {
    	   testcount=1;
    	   vt=0;
    	 }
    	// v1[viewcount]=vt;
    	 viewcount++;
    	 if(viewcount>6000)
    	 {
    	   viewcount=0;
    	   viewcountFlag=1;
    	 }
     }
   //view_theta=viewcount;
  /* v1[viewcount]=viewd;
   v2[viewcount]=theta_raw_view2;
   v3[viewcount]=view_theta;
   	viewcount++;
   	if(viewcount>=2000)
   	viewcount=0;*/
	/***************计算占空比**********************************/ 	
	EPwm1Regs.CMPA.half.CMPA=(unsigned int)((2*ura_r_ref*151.0519/MUdc+1)/2.0*CarryPRD);

 // Clear INT flag for this timer
    EPwm1Regs.ETCLR.bit.INT = 1;
    // Acknowledge this interrupt to receive more interrupts from group 3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

}
/***********************************************************************	 
函数名称：interrupt void epwm3_isr(void)
函数功能:ePWM1中断函数
输入：无  
输出：无		
***********************************************************************/
interrupt void epwm2_isr(void)
{
	EPwm2Regs.CMPA.half.CMPA=(unsigned int)((2*urb_r_ref*151.0519/MUdc+1)/2.0*CarryPRD);

    // Clear INT flag for this timer
    EPwm2Regs.ETCLR.bit.INT = 1;
    // Acknowledge this interrupt to receive more interrupts from group 3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
/***********************************************************************	 
函数名称：interrupt void epwm3_isr(void)
函数功能:ePWM1中断函数
输入：无  
输出：无		
***********************************************************************/
interrupt void epwm3_isr(void)
{
	EPwm3Regs.CMPA.half.CMPA=(unsigned int)((2*urc_r_ref*151.0519/MUdc+1)/2.0*CarryPRD);

    // Clear INT flag for this timer
    EPwm3Regs.ETCLR.bit.INT = 1;
    // Acknowledge this interrupt to receive more interrupts from group 3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

}



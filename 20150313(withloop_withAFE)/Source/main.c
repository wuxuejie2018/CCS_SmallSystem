#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "ADC_all.h"
#include "EPwmSetup.h"
#include "MyDefine.h"
#include "Example_posspeed.h"   // Example specific Include file


POSSPEED qep_posspeed=POSSPEED_DEFAULTS;  
float v1[2000]={0},v2[2000]={0},v3[2000]={0}; 		//�۲�����
unsigned int viewcount=0,viewcountFlag=0,testcount=0;
unsigned int StopFlag=1,ErrorFlag=0,StartFlag=0,Flag=0,EndFlag1=0;
int Tc1=0;
unsigned int RelayFlag=0;

void main(void)
{  

															InitSysCtrl();   	//Initialize System Control,PLL, WatchDog, enable Peripheral Clocks:
   	DINT; 				//Clear all interrupts,Disable CPU interrupts :
   	InitPieCtrl();     	//Initialize the PIE control registers to their default state
   	IER = 0x0000;		//Disable CPU interrupts and clear all CPU interrupt flags:
   	IFR = 0x0000;
   	InitPieVectTable(); //PIE ������ָ��ָ���жϷ����(ISR)������ʼ��
   	
   	InitEPwm1Gpio();	//ePWM�˿ڳ�ʼ��
    InitEPwm2Gpio();
    InitEPwm3Gpio();
    AD7607InitGpio();	//AD7607�˿ڳ�ʼ��
   	RelayInitGpio();	//�̵����˿ڳ�ʼ������
    EnDisableEPWMGpio();//PWM�˿ڳ�ʼ��
    InitEQep1Gpio();	//������ٶ˿ڳ�ʼ��
    
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = &epwm1_isr;    //pwm�ж�����
    PieVectTable.EPWM2_INT = &epwm2_isr;
    PieVectTable.EPWM3_INT = &epwm3_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers
 	
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
    InitEPwm1forSPWM();
    InitEPwm2forSPWM();
    InitEPwm3forSPWM();
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

 	AD7607Init();	//AD7607��ʼ�� 
 	InitUdcAdc();
 	RotorPWMEnable;
   
    IER |= M_INT3;  // Enable CPU INT3 which is connected to EPWM1-3 INT:
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx3 = 1;
    
    EINT;   // ���ж� INTM ʹ��
    ERTM;   // ʹ����ʵʱ�ж� DBGM
    
    qep_posspeed.init(&qep_posspeed);    //��ʼ��

    while(1)
    {  	 	
		if(RelayFlag==1)
			Relay_C1=1;
		else
			Relay_C1=0;

    	if((StopFlag==1&&Flag==0)||ErrorFlag==1)   //���� ǿ������ض�
		{	
			EPwm1Regs.AQCSFRC.all=0x06;
			EPwm2Regs.AQCSFRC.all=0x06;
			EPwm3Regs.AQCSFRC.all=0x06;
			Flag=1;
    	}
    	if((StopFlag==0&&Flag==1)&&ErrorFlag==0)
    	{
    		EPwm1Regs.AQCSFRC.all=0x00;
    		EPwm2Regs.AQCSFRC.all=0x00;
    		EPwm3Regs.AQCSFRC.all=0x00;
    		Flag=0;
    	}
    	if(testcount==1)
    	{
    			EPwm1Regs.AQCSFRC.all=0x06;
    		    EPwm2Regs.AQCSFRC.all=0x06;
    			EPwm3Regs.AQCSFRC.all=0x06;

    	}
    }
    
}


//===========================================================================
// No more.
//===========================================================================

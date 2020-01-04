#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "ADC_all.h"
#include "MyDefine.h"

/**************************定义变量*********************************/
int 	AD7607_Stator_Uab=0,AD7607_Stator_Ubc=0,AD7607_Grid_Uab=0,AD7607_Grid_Ubc=0,
		AD7607_Stator_Ia=0,AD7607_Stator_Ic=0,AD7607_Rotor_Ia=0,AD7607_Rotor_Ic=0,
		ADC_Udc=0;
extern float 	Stator_uab,Stator_ubc,Grid_uab,Grid_ubc,
				Stator_line_ia,Stator_line_ic,Rotor_line_ia,Rotor_line_ic,
				Udc;						//一次侧直流电压信号
int RotorIaOverCurrent=0,RotorIcOverCurrent=0,RotorIaOverCurrentFlag=0, RotorIcOverCurrentFlag=0,ADC_UdcOverVoltage=0;

extern unsigned int  ErrorFlag,StartFlag;
	    

/***********************************************************************	 
函数名称： void AD7607InitGpio(void)
函数功能:	AD7607端口初始化
输入：无  
输出：无		
***********************************************************************/	
void AD7607InitGpio(void)
{
	EALLOW;
   	GpioCtrlRegs.GPBMUX1.bit.GPIO42=0;		//CS和RD
   	GpioCtrlRegs.GPBDIR.bit.GPIO42 =1; 		//输出
   	GpioCtrlRegs.GPBMUX1.bit.GPIO40=0;		//CONVST
   	GpioCtrlRegs.GPBDIR.bit.GPIO40 =1; 
    GpioCtrlRegs.GPBMUX1.bit.GPIO41=0;		//RESET
   	GpioCtrlRegs.GPBDIR.bit.GPIO41 =1; 
   	GpioCtrlRegs.GPBMUX2.bit.GPIO54=0;		//BUSY
   	GpioCtrlRegs.GPBDIR.bit.GPIO54 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO79=0;		//D0
   	GpioCtrlRegs.GPCDIR.bit.GPIO79 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO78=0;		//D1
   	GpioCtrlRegs.GPCDIR.bit.GPIO78 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO77=0;		//D2
   	GpioCtrlRegs.GPCDIR.bit.GPIO77 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO76=0;		//D3
   	GpioCtrlRegs.GPCDIR.bit.GPIO76 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO75=0;		//D4
   	GpioCtrlRegs.GPCDIR.bit.GPIO75 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO74=0;		//D5
   	GpioCtrlRegs.GPCDIR.bit.GPIO74 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO73=0;		//D6
   	GpioCtrlRegs.GPCDIR.bit.GPIO73 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO72=0;		//D7
   	GpioCtrlRegs.GPCDIR.bit.GPIO72 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO71=0;		//D8
   	GpioCtrlRegs.GPCDIR.bit.GPIO71 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO70=0;		//D9
   	GpioCtrlRegs.GPCDIR.bit.GPIO70 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO69=0;		//D10
   	GpioCtrlRegs.GPCDIR.bit.GPIO69 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO68=0;		//D11
   	GpioCtrlRegs.GPCDIR.bit.GPIO68 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO67=0;		//D12
   	GpioCtrlRegs.GPCDIR.bit.GPIO67 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO66=0;		//D13
   	GpioCtrlRegs.GPCDIR.bit.GPIO66 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO65=0;		//D14
   	GpioCtrlRegs.GPCDIR.bit.GPIO65 =0;      //输入
   	GpioCtrlRegs.GPCMUX1.bit.GPIO64=0;		//D15
   	GpioCtrlRegs.GPCDIR.bit.GPIO64 =0;      //输入
   	
   	EDIS;	
}

/***********************************************************************	 
函数名称： void ADInit(void)
函数功能:	初始化AD7607
输入：无  
输出：无		
***********************************************************************/	
void AD7607Init(void)
{
   	CLR_AD_RESET;
   	asm(" RPT#10||NOP");
   	SET_AD_RESET;
   	asm(" RPT#20||NOP");   //上升沿50ns
   	CLR_AD_RESET;
   	
}
/***********************************************************************	 
函数名称：void InitUdcAdc(void)
函数功能:	初始化DSP ADC端口，用于采样Udc端电压
输入：无  
输出：无		
***********************************************************************/	
void InitUdcAdc(void)
{
	EALLOW;
   	SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/ADC_MODCLK
   	EDIS;
   	DELAY_US(5);
   	
   	InitAdc(); 
 
   	// Specific ADC setup for this example:
   	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;  // Sequential mode: Sample rate   = 1/[(2+ACQ_PS)*ADC clock in ns]
                        //                     = 1/(3*40ns) =8.3MHz (for 150 MHz SYSCLKOUT)
					    //                     = 1/(3*80ns) =4.17MHz (for 100 MHz SYSCLKOUT)
					    // If Simultaneous mode enabled: Sample rate = 1/[(3+ACQ_PS)*ADC clock in ns]
   	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
   	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode
   	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x1;
   	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // Setup continuous run

   	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;       // Enable Sequencer override feature
   	AdcRegs.ADCCHSELSEQ1.all = 0x0;         // Initialize all ADC channel selects to A0
   	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x0;  // convert and store in 8 results registers
   	
   	// Start SEQ1
   	AdcRegs.ADCTRL2.all = 0x2000;
		
}

/***********************************************************************	 
函数名称： void GetUdcData(unsigned char volatile i)
函数功能:	 获取一次转换数据
输入：无  
输出：		
***********************************************************************/
void GetUdcData(void)
{
	while(AdcRegs.ADCST.bit.INT_SEQ1 == 0);
		AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
	ADC_Udc= ((AdcRegs.ADCRESULT0)>>4);
	Udc=(float)ADC_Udc*0.3045;  //转换为一次侧电压值
	if( ADC_Udc>MaxADC_Udc)
   	{	
   		ADC_UdcOverVoltage=1;
   		ErrorFlag=1;
   	}
}

/***********************************************************************	 
函数名称： int AD7607Resualt(void)
函数功能:	 获取一次转换数据
输入：无  
输出：转换数据 int型		
***********************************************************************/
int AD7607Resualt(void)
{
	int data=0;
	if(AD_D0==1)
		data|=0x0001;
	if(AD_D1==1)
		data|=0x0002;
	if(AD_D2==1)
		data|=0x0004;
	if(AD_D3==1)
		data|=0x0008;
	if(AD_D4==1)
		data|=0x0010;
	if(AD_D5==1)
		data|=0x0020;
	if(AD_D6==1)
		data|=0x0040;
	if(AD_D7==1)
		data|=0x0080;
	if(AD_D8==1)
		data|=0x0100;
	if(AD_D9==1)
		data|=0x0200;
	if(AD_D10==1)
		data|=0x0400;
	if(AD_D11==1)
		data|=0x0800;
	if(AD_D12==1)
		data|=0x1000;
	if(AD_D13==1)
		data|=0x2000;
	if(AD_D14==1)
		data|=0x4000;
	if(AD_D15==1)
		data|=0x8000;	
	return(data);
}

/***********************************************************************	 
函数名称： void GetAdcData(unsigned char i)
函数功能:	 获得8个通道的ADC转换值
输入：无  
输出：无		
***********************************************************************/
void GetAdcData(void)
{   
  /* data acquisition routine */
    SET_AD_CS;
    asm(" RPT#10||NOP");
    CLR_AD_CONVST;
	asm(" RPT#5||NOP");
   	SET_AD_CONVST;			//启动转换
	asm(" RPT#8||NOP");
  
   	while( AD_BUSY!=0);		//判断转换结束？
	
    CLR_AD_CS;
	asm(" RPT#3||NOP");		//获取Stator_Uab电压值
	AD7607_Stator_Ia=AD7607Resualt();
//  AD7607_Grid_Uab=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   	
  	CLR_AD_CS;
	asm(" RPT#3||NOP");			//获取Stator_Ubc电压值
	AD7607_Stator_Ic=AD7607Resualt();
//  AD7607_Grid_Ubc=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   	
  	CLR_AD_CS;
	asm(" RPT#3||NOP");			//获取Grid_Uab电压值
   	AD7607_Stator_Uab=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   	   
  	CLR_AD_CS;
	asm(" RPT#3||NOP");			//获取Grid_Ubc电压值
   	AD7607_Stator_Ubc=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   	  
  	CLR_AD_CS;
	asm(" RPT#3||NOP");			//获取Rotor_Ia电压值
	AD7607_Grid_Uab=AD7607Resualt();
//	AD7607_Stator_Ia=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   	
  	CLR_AD_CS;
	asm(" RPT#3||NOP");			//获取Rotor_Ib电压值
   	AD7607_Grid_Ubc=AD7607Resualt();
//  AD7607_Stator_Ic=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   
   	CLR_AD_CS;
	asm(" RPT#3||NOP");			//获取Stator_Ia电压值
   	AD7607_Rotor_Ia=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
  
    CLR_AD_CS;
	asm(" RPT#3||NOP");			//获取Stator_Ib电压值
	AD7607_Rotor_Ic=AD7607Resualt();

   	AD7607DataTransition();	//将AD7607读取的数据变换为一次侧数据
   	
   	if(	StartFlag==1&&(AD7607_Rotor_Ia<MaxAD7607RotorIa_N||AD7607_Rotor_Ia>MaxAD7607RotorIa_P))
   	{	
   		RotorIaOverCurrent++;
   		if(RotorIaOverCurrent==3)
   		{
   			RotorIaOverCurrentFlag=1;
   			RotorIaOverCurrent=0;
   			ErrorFlag=1;
   		}
   	}
   	else
   		RotorIaOverCurrent=0;

   	if(	StartFlag==1&&(AD7607_Rotor_Ic<MaxAD7607RotorIc_N||AD7607_Rotor_Ic>MaxAD7607RotorIc_P))
   	{
   		RotorIcOverCurrent++;
   		if(RotorIaOverCurrent==3)
   		{
   			RotorIcOverCurrentFlag=1;
   			RotorIcOverCurrent=0;
   			ErrorFlag=1;
   		}
   	}
   	else
   		RotorIcOverCurrent=0;

}

/************************************+***********************************	 
函数名称： void AD7607DataTransition(void)
函数功能:	 将AD7607读取的数据变换为一次侧数据
输入：电压电流数据  
输出：无		
***********************************************************************/
void AD7607DataTransition(void)
{

	Grid_uab=(float)AD7607_Grid_Uab*0.11441*1.0784;   //StatorUabPTRate可变 反相
	Grid_ubc=(float)AD7607_Grid_Ubc*0.11441*1.0784;
	Stator_uab  =(float)AD7607_Stator_Uab*-0.094;
	Stator_ubc  =(float)AD7607_Stator_Ubc*-0.094;
//	Stator_line_ia=(float)AD7607_Stator_Ia*-0.00947;
//	Stator_line_ic =(float)AD7607_Stator_Ic*-0.0095;
	Rotor_line_ic=125-(float)AD7607_Rotor_Ia*0.061;     //用板子自带的AD采样功能   变频器自带板子上电流传感器的顺序和输出相反，从接线端看乳右边的传感器是a，左边的传感器是c
	Rotor_line_ia=125-(float)AD7607_Rotor_Ic*0.061;
}



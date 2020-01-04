#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "MyDefine.h"

/***********************************************************************	 
函数名称：void RelayInitGpio(void)
函数功能:	初始化继电器端口函数
输入：无  
输出：无		
***********************************************************************/	
void RelayInitGpio(void)
{
	EALLOW;
   	GpioCtrlRegs.GPBMUX1.bit.GPIO43=0;		//C1
   	GpioCtrlRegs.GPBDIR.bit.GPIO43 =1; 		//输出
   	GpioCtrlRegs.GPBMUX1.bit.GPIO44=0;		//C2
   	GpioCtrlRegs.GPBDIR.bit.GPIO44 =1; 
   	EDIS;
   	DELAY_US(100);
   	Relay_C1=0;
   	Relay_C2=0;	
}

/***********************************************************************	 
函数名称：void EnDisableEPWMGpio(void)
函数功能:	
输入：无  
输出：无		
***********************************************************************/
void EnDisableEPWMGpio(void)
{
   	EALLOW;	
   	GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 0; // GPIO0 = GPIO0
   	GpioCtrlRegs.GPBDIR.bit.GPIO46 = 1;  	
   	EDIS;	
	RotorPWMDisable;
}

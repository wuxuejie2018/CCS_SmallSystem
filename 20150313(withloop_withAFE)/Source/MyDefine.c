#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "MyDefine.h"

/***********************************************************************	 
�������ƣ�void RelayInitGpio(void)
��������:	��ʼ���̵����˿ں���
���룺��  
�������		
***********************************************************************/	
void RelayInitGpio(void)
{
	EALLOW;
   	GpioCtrlRegs.GPBMUX1.bit.GPIO43=0;		//C1
   	GpioCtrlRegs.GPBDIR.bit.GPIO43 =1; 		//���
   	GpioCtrlRegs.GPBMUX1.bit.GPIO44=0;		//C2
   	GpioCtrlRegs.GPBDIR.bit.GPIO44 =1; 
   	EDIS;
   	DELAY_US(100);
   	Relay_C1=0;
   	Relay_C2=0;	
}

/***********************************************************************	 
�������ƣ�void EnDisableEPWMGpio(void)
��������:	
���룺��  
�������		
***********************************************************************/
void EnDisableEPWMGpio(void)
{
   	EALLOW;	
   	GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 0; // GPIO0 = GPIO0
   	GpioCtrlRegs.GPBDIR.bit.GPIO46 = 1;  	
   	EDIS;	
	RotorPWMDisable;
}

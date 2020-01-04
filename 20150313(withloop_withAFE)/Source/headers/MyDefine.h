#ifndef MYDEFINE_H_
#define MYDEFINE_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

/***************************继电器端口define***************************/
#define 	Relay_C1			GpioDataRegs.GPBDAT.bit.GPIO43	  	//继电器C1和C2
#define 	Relay_C2			GpioDataRegs.GPBDAT.bit.GPIO44
#define	  	RotorPWMEnable		GpioDataRegs.GPBDAT.bit.GPIO46=1;   //PWM开通
#define	  	RotorPWMDisable		GpioDataRegs.GPBDAT.bit.GPIO46=0;

#define		MaxAD7607RotorIa_P	2951//电流保护用 最大转子电流 正值   V=2.5-0.02I -55A    (125-x)/0.061
#define		MaxAD7607RotorIa_N	1148//电流保护用 最大转子电流 负值	55A
#define		MaxAD7607RotorIc_P	2951//电流保护用 最大转子电流 正值   V=2.5-0.02I
#define		MaxAD7607RotorIc_N	1148//电流保护用 最大转子电流 负值
#define 	MaxADC_Udc			2215//直流端电压保护	650V

/************************相关函数声明************************/
void RelayInitGpio(void);		//继电器端口初始化函数
void EnDisableEPWMGpio(void);


#endif /*MYDEFINE_H_*/

#ifndef MYDEFINE_H_
#define MYDEFINE_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

/***************************�̵����˿�define***************************/
#define 	Relay_C1			GpioDataRegs.GPBDAT.bit.GPIO43	  	//�̵���C1��C2
#define 	Relay_C2			GpioDataRegs.GPBDAT.bit.GPIO44
#define	  	RotorPWMEnable		GpioDataRegs.GPBDAT.bit.GPIO46=1;   //PWM��ͨ
#define	  	RotorPWMDisable		GpioDataRegs.GPBDAT.bit.GPIO46=0;

#define		MaxAD7607RotorIa_P	2951//���������� ���ת�ӵ��� ��ֵ   V=2.5-0.02I -55A    (125-x)/0.061
#define		MaxAD7607RotorIa_N	1148//���������� ���ת�ӵ��� ��ֵ	55A
#define		MaxAD7607RotorIc_P	2951//���������� ���ת�ӵ��� ��ֵ   V=2.5-0.02I
#define		MaxAD7607RotorIc_N	1148//���������� ���ת�ӵ��� ��ֵ
#define 	MaxADC_Udc			2215//ֱ���˵�ѹ����	650V

/************************��غ�������************************/
void RelayInitGpio(void);		//�̵����˿ڳ�ʼ������
void EnDisableEPWMGpio(void);


#endif /*MYDEFINE_H_*/

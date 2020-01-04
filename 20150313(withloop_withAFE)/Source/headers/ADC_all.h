#ifndef ADC_all_H_
#define ADC_all_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

/*************************AD7607�˿ڶ���************************/
#define SET_AD_CS			GpioDataRegs.GPBDAT.bit.GPIO42=1	  	//CS��RD�˿�����һ��
#define CLR_AD_CS			GpioDataRegs.GPBDAT.bit.GPIO42=0
#define SET_AD_CONVST		GpioDataRegs.GPBDAT.bit.GPIO40=1
#define CLR_AD_CONVST		GpioDataRegs.GPBDAT.bit.GPIO40=0
#define SET_AD_RESET		GpioDataRegs.GPBDAT.bit.GPIO41=1
#define CLR_AD_RESET		GpioDataRegs.GPBDAT.bit.GPIO41=0
#define AD_BUSY				GpioDataRegs.GPBDAT.bit.GPIO54       	//BUSY�˿�

#define AD_D0				GpioDataRegs.GPCDAT.bit.GPIO79
#define AD_D1				GpioDataRegs.GPCDAT.bit.GPIO78
#define AD_D2				GpioDataRegs.GPCDAT.bit.GPIO77
#define AD_D3				GpioDataRegs.GPCDAT.bit.GPIO76
#define AD_D4				GpioDataRegs.GPCDAT.bit.GPIO75
#define AD_D5				GpioDataRegs.GPCDAT.bit.GPIO74
#define AD_D6				GpioDataRegs.GPCDAT.bit.GPIO73
#define AD_D7				GpioDataRegs.GPCDAT.bit.GPIO72
#define AD_D8				GpioDataRegs.GPCDAT.bit.GPIO71
#define AD_D9				GpioDataRegs.GPCDAT.bit.GPIO70
#define AD_D10				GpioDataRegs.GPCDAT.bit.GPIO69
#define AD_D11				GpioDataRegs.GPCDAT.bit.GPIO68
#define AD_D12				GpioDataRegs.GPCDAT.bit.GPIO67
#define AD_D13				GpioDataRegs.GPCDAT.bit.GPIO66
#define AD_D14				GpioDataRegs.GPCDAT.bit.GPIO65
#define AD_D15				GpioDataRegs.GPCDAT.bit.GPIO64


/************************������������************************/
#define		AD7607_NUM_MAX	100 	//AD7607ת�������С
#define 	Udc_NUM_MAX		100  //Udcת�������С

// ADC Udc start parameters
#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
  #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
#endif
#if (CPU_FRQ_100MHZ)
  #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
#endif
#define ADC_CKPS   0x0   // ADC module clock = HSPCLK/1      = 25.5MHz/(1)   = 25.0 MHz
#define ADC_SHCLK  0x1   // S/H width in ADC module periods                  = 2 ADC cycle


//��ѹת����·
#define	 	StatorUabPTRate		200 		//��ѹ���������(����200k)
#define		StatorUabAMPRatio	2127.32		//�˷ŷŴ�ϵ��������2.6k��ADϵ��818.2
#define	 	StatorUbcPTRate		200 		//��ѹ���������(����200k)
#define		StatorUbcAMPRatio	2127.32		//�˷ŷŴ�ϵ��������2.6k��ADϵ��818.2
#define	 	GridUabPTRate		200 		//��ѹ���������(����200k)
#define		GridUabAMPRatio		2127.32		//�˷ŷŴ�ϵ��������2.6k��ADϵ��818.2
#define	 	GridUbcPTRate		200 		//��ѹ���������(����200k)
#define		GridUbcAMPRatio		2127.32		//�˷ŷŴ�ϵ��������2.6k��ADϵ��818.2
//����ת����·
#define	 	RotorIaCTRate		200 		//������������ȣ���Сһ����2559
#define		RotorIaAMPRatio		27000		//�˷ŷŴ�ϵ��������330R��ADϵ��818.2
#define	 	RotorIbCTRate		200 		//������������ȣ���Сһ����2570
#define		RotorIbAMPRatio		27000		//�˷ŷŴ�ϵ��������330R��ADϵ��818.2
#define	 	StatorIaCTRate		200 		//������������ȣ���Сһ����2693
#define		StatorIaAMPRatio	16364		//�˷ŷŴ�ϵ��������330R��ADϵ��818.2
#define	 	StatorIbCTRate		200 		//������������ȣ���Сһ����2612
#define		StatorIbAMPRatio	16364		//�˷ŷŴ�ϵ��������330R��ADϵ��818.2
//ֱ��ת����·
#define		UdcCTRate			40			//������ֵ2.5 ������100k��
#define		UdcAMPRatio			136.5		//����100R,4095ʱΪ3V

//#define	 	AD7606_CT_Rate			//�������������

/************************AD7607��������************************/
void AD7607InitGpio(void);	//AD7607�˿ڳ�ʼ��
void AD7607Init(void);		//��ʼ��AD7607
void InitUdcAdc(void);		//��ʼ��DSP ADC�˿ڣ����ڲ���Udc�˵�ѹ
int AD7607Resualt(void);	//��ȡһ��ת������
void GetAdcData(void);		//���8��ͨ����ADCת��ֵ
void GetUdcData(void);		//��ȡADCת����ֵ
void AD7607DataTransition(void);	//��AD7607��ȡ�����ݱ任Ϊһ�β�����		

#endif /*ADC_all_H_*/

#ifndef ADC_all_H_
#define ADC_all_H_
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

/*************************AD7607端口定义************************/
#define SET_AD_CS			GpioDataRegs.GPBDAT.bit.GPIO42=1	  	//CS和RD端口连在一起
#define CLR_AD_CS			GpioDataRegs.GPBDAT.bit.GPIO42=0
#define SET_AD_CONVST		GpioDataRegs.GPBDAT.bit.GPIO40=1
#define CLR_AD_CONVST		GpioDataRegs.GPBDAT.bit.GPIO40=0
#define SET_AD_RESET		GpioDataRegs.GPBDAT.bit.GPIO41=1
#define CLR_AD_RESET		GpioDataRegs.GPBDAT.bit.GPIO41=0
#define AD_BUSY				GpioDataRegs.GPBDAT.bit.GPIO54       	//BUSY端口

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


/************************其他变量定义************************/
#define		AD7607_NUM_MAX	100 	//AD7607转换数组大小
#define 	Udc_NUM_MAX		100  //Udc转换数组大小

// ADC Udc start parameters
#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
  #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
#endif
#if (CPU_FRQ_100MHZ)
  #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
#endif
#define ADC_CKPS   0x0   // ADC module clock = HSPCLK/1      = 25.5MHz/(1)   = 25.0 MHz
#define ADC_SHCLK  0x1   // S/H width in ADC module periods                  = 2 ADC cycle


//电压转换回路
#define	 	StatorUabPTRate		200 		//电压互感器变比(电阻200k)
#define		StatorUabAMPRatio	2127.32		//运放放大系数（电阻2.6k）AD系数818.2
#define	 	StatorUbcPTRate		200 		//电压互感器变比(电阻200k)
#define		StatorUbcAMPRatio	2127.32		//运放放大系数（电阻2.6k）AD系数818.2
#define	 	GridUabPTRate		200 		//电压互感器变比(电阻200k)
#define		GridUabAMPRatio		2127.32		//运放放大系数（电阻2.6k）AD系数818.2
#define	 	GridUbcPTRate		200 		//电压互感器变比(电阻200k)
#define		GridUbcAMPRatio		2127.32		//运放放大系数（电阻2.6k）AD系数818.2
//电流转换回路
#define	 	RotorIaCTRate		200 		//电流互感器变比（缩小一倍）2559
#define		RotorIaAMPRatio		27000		//运放放大系数（电阻330R）AD系数818.2
#define	 	RotorIbCTRate		200 		//电流互感器变比（缩小一倍）2570
#define		RotorIbAMPRatio		27000		//运放放大系数（电阻330R）AD系数818.2
#define	 	StatorIaCTRate		200 		//电流互感器变比（缩小一倍）2693
#define		StatorIaAMPRatio	16364		//运放放大系数（电阻330R）AD系数818.2
#define	 	StatorIbCTRate		200 		//电流互感器变比（缩小一倍）2612
#define		StatorIbAMPRatio	16364		//运放放大系数（电阻330R）AD系数818.2
//直流转换回路
#define		UdcCTRate			40			//电流比值2.5 （电阻100k）
#define		UdcAMPRatio			136.5		//电阻100R,4095时为3V

//#define	 	AD7606_CT_Rate			//电流互感器变比

/************************AD7607函数定义************************/
void AD7607InitGpio(void);	//AD7607端口初始化
void AD7607Init(void);		//初始化AD7607
void InitUdcAdc(void);		//初始化DSP ADC端口，用于采样Udc端电压
int AD7607Resualt(void);	//获取一次转换数据
void GetAdcData(void);		//获得8个通道的ADC转换值
void GetUdcData(void);		//获取ADC转换数值
void AD7607DataTransition(void);	//将AD7607读取的数据变换为一次侧数据		

#endif /*ADC_all_H_*/

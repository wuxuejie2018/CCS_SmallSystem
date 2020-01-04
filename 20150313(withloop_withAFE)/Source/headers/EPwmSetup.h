#ifndef EPWMSETUP_H_
#define EPWMSETUP_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File


#if (CPU_FRQ_150MHZ)
  #define CPU_CLK   150e6
#endif
#if (CPU_FRQ_100MHZ)
  #define CPU_CLK   100e6
#endif

#define SPWM_CLK   			10e3          	//SPWM工作频率	
#define CarryPRD            CPU_CLK/(2.0*SPWM_CLK)	//ePWM的PRD
#define SPWM_CLK   			10e3          	//SPWM工作频率	
#define DeadTime			600				//死区时间
#define PI					2*3.14159


/************************函数声明************************/
void InitEPwm1forSPWM(void);
void InitEPwm2forSPWM(void);
void InitEPwm3forSPWM(void);
interrupt void epwm1_isr(void);
interrupt void epwm2_isr(void);
interrupt void epwm3_isr(void);

#endif /*EPWMSETUP_H_*/

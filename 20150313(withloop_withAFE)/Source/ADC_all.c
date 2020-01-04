#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "ADC_all.h"
#include "MyDefine.h"

/**************************�������*********************************/
int 	AD7607_Stator_Uab=0,AD7607_Stator_Ubc=0,AD7607_Grid_Uab=0,AD7607_Grid_Ubc=0,
		AD7607_Stator_Ia=0,AD7607_Stator_Ic=0,AD7607_Rotor_Ia=0,AD7607_Rotor_Ic=0,
		ADC_Udc=0;
extern float 	Stator_uab,Stator_ubc,Grid_uab,Grid_ubc,
				Stator_line_ia,Stator_line_ic,Rotor_line_ia,Rotor_line_ic,
				Udc;						//һ�β�ֱ����ѹ�ź�
int RotorIaOverCurrent=0,RotorIcOverCurrent=0,RotorIaOverCurrentFlag=0, RotorIcOverCurrentFlag=0,ADC_UdcOverVoltage=0;

extern unsigned int  ErrorFlag,StartFlag;
	    

/***********************************************************************	 
�������ƣ� void AD7607InitGpio(void)
��������:	AD7607�˿ڳ�ʼ��
���룺��  
�������		
***********************************************************************/	
void AD7607InitGpio(void)
{
	EALLOW;
   	GpioCtrlRegs.GPBMUX1.bit.GPIO42=0;		//CS��RD
   	GpioCtrlRegs.GPBDIR.bit.GPIO42 =1; 		//���
   	GpioCtrlRegs.GPBMUX1.bit.GPIO40=0;		//CONVST
   	GpioCtrlRegs.GPBDIR.bit.GPIO40 =1; 
    GpioCtrlRegs.GPBMUX1.bit.GPIO41=0;		//RESET
   	GpioCtrlRegs.GPBDIR.bit.GPIO41 =1; 
   	GpioCtrlRegs.GPBMUX2.bit.GPIO54=0;		//BUSY
   	GpioCtrlRegs.GPBDIR.bit.GPIO54 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO79=0;		//D0
   	GpioCtrlRegs.GPCDIR.bit.GPIO79 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO78=0;		//D1
   	GpioCtrlRegs.GPCDIR.bit.GPIO78 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO77=0;		//D2
   	GpioCtrlRegs.GPCDIR.bit.GPIO77 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO76=0;		//D3
   	GpioCtrlRegs.GPCDIR.bit.GPIO76 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO75=0;		//D4
   	GpioCtrlRegs.GPCDIR.bit.GPIO75 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO74=0;		//D5
   	GpioCtrlRegs.GPCDIR.bit.GPIO74 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO73=0;		//D6
   	GpioCtrlRegs.GPCDIR.bit.GPIO73 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO72=0;		//D7
   	GpioCtrlRegs.GPCDIR.bit.GPIO72 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO71=0;		//D8
   	GpioCtrlRegs.GPCDIR.bit.GPIO71 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO70=0;		//D9
   	GpioCtrlRegs.GPCDIR.bit.GPIO70 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO69=0;		//D10
   	GpioCtrlRegs.GPCDIR.bit.GPIO69 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO68=0;		//D11
   	GpioCtrlRegs.GPCDIR.bit.GPIO68 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO67=0;		//D12
   	GpioCtrlRegs.GPCDIR.bit.GPIO67 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO66=0;		//D13
   	GpioCtrlRegs.GPCDIR.bit.GPIO66 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO65=0;		//D14
   	GpioCtrlRegs.GPCDIR.bit.GPIO65 =0;      //����
   	GpioCtrlRegs.GPCMUX1.bit.GPIO64=0;		//D15
   	GpioCtrlRegs.GPCDIR.bit.GPIO64 =0;      //����
   	
   	EDIS;	
}

/***********************************************************************	 
�������ƣ� void ADInit(void)
��������:	��ʼ��AD7607
���룺��  
�������		
***********************************************************************/	
void AD7607Init(void)
{
   	CLR_AD_RESET;
   	asm(" RPT#10||NOP");
   	SET_AD_RESET;
   	asm(" RPT#20||NOP");   //������50ns
   	CLR_AD_RESET;
   	
}
/***********************************************************************	 
�������ƣ�void InitUdcAdc(void)
��������:	��ʼ��DSP ADC�˿ڣ����ڲ���Udc�˵�ѹ
���룺��  
�������		
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
�������ƣ� void GetUdcData(unsigned char volatile i)
��������:	 ��ȡһ��ת������
���룺��  
�����		
***********************************************************************/
void GetUdcData(void)
{
	while(AdcRegs.ADCST.bit.INT_SEQ1 == 0);
		AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
	ADC_Udc= ((AdcRegs.ADCRESULT0)>>4);
	Udc=(float)ADC_Udc*0.3045;  //ת��Ϊһ�β��ѹֵ
	if( ADC_Udc>MaxADC_Udc)
   	{	
   		ADC_UdcOverVoltage=1;
   		ErrorFlag=1;
   	}
}

/***********************************************************************	 
�������ƣ� int AD7607Resualt(void)
��������:	 ��ȡһ��ת������
���룺��  
�����ת������ int��		
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
�������ƣ� void GetAdcData(unsigned char i)
��������:	 ���8��ͨ����ADCת��ֵ
���룺��  
�������		
***********************************************************************/
void GetAdcData(void)
{   
  /* data acquisition routine */
    SET_AD_CS;
    asm(" RPT#10||NOP");
    CLR_AD_CONVST;
	asm(" RPT#5||NOP");
   	SET_AD_CONVST;			//����ת��
	asm(" RPT#8||NOP");
  
   	while( AD_BUSY!=0);		//�ж�ת��������
	
    CLR_AD_CS;
	asm(" RPT#3||NOP");		//��ȡStator_Uab��ѹֵ
	AD7607_Stator_Ia=AD7607Resualt();
//  AD7607_Grid_Uab=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   	
  	CLR_AD_CS;
	asm(" RPT#3||NOP");			//��ȡStator_Ubc��ѹֵ
	AD7607_Stator_Ic=AD7607Resualt();
//  AD7607_Grid_Ubc=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   	
  	CLR_AD_CS;
	asm(" RPT#3||NOP");			//��ȡGrid_Uab��ѹֵ
   	AD7607_Stator_Uab=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   	   
  	CLR_AD_CS;
	asm(" RPT#3||NOP");			//��ȡGrid_Ubc��ѹֵ
   	AD7607_Stator_Ubc=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   	  
  	CLR_AD_CS;
	asm(" RPT#3||NOP");			//��ȡRotor_Ia��ѹֵ
	AD7607_Grid_Uab=AD7607Resualt();
//	AD7607_Stator_Ia=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   	
  	CLR_AD_CS;
	asm(" RPT#3||NOP");			//��ȡRotor_Ib��ѹֵ
   	AD7607_Grid_Ubc=AD7607Resualt();
//  AD7607_Stator_Ic=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
   
   	CLR_AD_CS;
	asm(" RPT#3||NOP");			//��ȡStator_Ia��ѹֵ
   	AD7607_Rotor_Ia=AD7607Resualt();
   	SET_AD_CS;
   	asm(" RPT#5||NOP");
  
    CLR_AD_CS;
	asm(" RPT#3||NOP");			//��ȡStator_Ib��ѹֵ
	AD7607_Rotor_Ic=AD7607Resualt();

   	AD7607DataTransition();	//��AD7607��ȡ�����ݱ任Ϊһ�β�����
   	
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
�������ƣ� void AD7607DataTransition(void)
��������:	 ��AD7607��ȡ�����ݱ任Ϊһ�β�����
���룺��ѹ��������  
�������		
***********************************************************************/
void AD7607DataTransition(void)
{

	Grid_uab=(float)AD7607_Grid_Uab*0.11441*1.0784;   //StatorUabPTRate�ɱ� ����
	Grid_ubc=(float)AD7607_Grid_Ubc*0.11441*1.0784;
	Stator_uab  =(float)AD7607_Stator_Uab*-0.094;
	Stator_ubc  =(float)AD7607_Stator_Ubc*-0.094;
//	Stator_line_ia=(float)AD7607_Stator_Ia*-0.00947;
//	Stator_line_ic =(float)AD7607_Stator_Ic*-0.0095;
	Rotor_line_ic=125-(float)AD7607_Rotor_Ia*0.061;     //�ð����Դ���AD��������   ��Ƶ���Դ������ϵ�����������˳�������෴���ӽ��߶˿����ұߵĴ�������a����ߵĴ�������c
	Rotor_line_ia=125-(float)AD7607_Rotor_Ic*0.061;
}



#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "ADC_all.h"
#include "Control.h"
#include "math.h"

float theta_m=0;			//机械角速度

float wm=0;           	//转子机械角频率	
float Ps_ref=0;       	//定子有功标么值的参考值
float Qs_ref=0;       	//定子无功标么值参考值
unsigned int Krc=0;    //转子侧变频器起动指令( =1起动，0不起动)
extern unsigned int Ksatrt;

//PI调节器系数
//float   Kp1=0,Ki1=0,Kp2=0.3,Ki2=3,Kp3=0,Ki3=0,Kp4=0.3,Ki4=3;
float   Kp1=0,Ki1=0,Kp2=0.45,Ki2=9,Kp3=0,Ki3=0,Kp4=0.45,Ki4=9;
float   u1=0,u1_0=0,e1=0,e1_0=0,u2=0,u2_0=0,e2=0,e2_0=0,u3=0,u3_0=0,e3=0,e3_0=0,u4=0,u4_0=0,e4=0,e4_0=0;
//限幅参数
float   u_real2=0,u_real4=0,sta=0.8;
float   u_limited2=0,u_limited4=0;
//电网电压锁相环参数
float   u=0,u_0=314.1593,e=0,e_0=0,w_0=0,theta_Ug=0,theta_Ug0=0,theta_Ug1=0;

float 	Stator_uab=0,Stator_ubc=0,Grid_uab=0,Grid_ubc=0,
		Stator_line_ia=0,Stator_line_ic=0,Rotor_line_ia=0,Rotor_line_ic=0,
		Udc=0;	
float	us_ab=0,us_bc=0,is_a_line=0,is_c_line=0,ir_a_line=0,ir_c_line=0;
float	us_a=0,us_b=0,us_c=0,usd=0,usq=0,abs_Us=0,cos_theta_Us=0,sin_theta_Us=0;
float 	cos_theta_Us_p=0,sin_theta_Us_p=0,Usd_p=0,Usq_p=0,cos_theta_Us_p0=0,sin_theta_Us_p0=0;
float	is_a=0,is_b=0,is_c=0,isd=0,isq=0,abs_Is=0,cos_theta_Is=0,sin_theta_Is=0;
float	cos_theta_Is_p=0,sin_theta_Is_p=0,isd_p=0,isq_p=0;
float	ir_a=0,ir_b=0,ir_c=0,ird_r=0,irq_r=0,abs_Ir=0,cos_theta_Ir_r=0,sin_theta_Ir_r=0;
float	theta_r=0,cos_theta_Ir=0,sin_theta_Ir=0,cos_theta_Ir_p=0,sin_theta_Ir_p=0,ird_p=0,irq_p=0;
float	Ps=0,Qs=0;
float	urq_p_ref=0,urd_p_ref=0;
float   irq_p_ref=-0.3,ird_p_ref=0;
float	abs_Ur_ref=0,cos_theta_Ur_p_ref=0,sin_theta_Ur_p_ref=0;
float	cos_theta_Ur_ref=0,sin_theta_Ur_ref=0,cos_theta_Ur_r_ref=0,sin_theta_Ur_r_ref=0;
float	ura_r_ref=0,urb_r_ref=0,urc_r_ref=0;
float	Ur=0,theta_Ur=0;
float   view_w0,view_theta,viewq;
float   ka=0.933,kc=0.923,offseta=0.05,offsetc=0.02;
unsigned int     TcountFlag=0,EndFlag2=0;
extern unsigned int EndFlag1;
int     Tc2=0;
extern int Tc1;
float ParameterKRef=0,ParameterQRef=0,ParameterDRef=0;



void Control(void)
{
	//定子线电压、线电流以及转子线电流的测量与标么化
	us_ab=K_us*Grid_uab;
	us_bc=K_us*Grid_ubc;
	is_a_line=K_is*Stator_line_ia;
	is_c_line=K_is*Stator_line_ic;
	ir_a_line=K_ir*Rotor_line_ia*ka+offseta;
	ir_c_line=K_ir*Rotor_line_ic*kc+offsetc;
	
	//坐标正变换定子线电压空间矢量的计算（双馈电机Y-Y接线） 
	//静止轴系下定子电压空间矢量      
 	us_a=(us_bc+2*us_ab)/sqrt(3);
 	us_b=(us_bc-us_ab)/sqrt(3);
	us_c=(-2*us_bc-us_ab)/sqrt(3);
	//view_w0=us_b;
	//viewd=us_a;
	//viewq=cos(theta_Ug+2*pi/3);

	usd=(us_a-us_b/2-us_c/2)*2/3;
	usq=(sqrt(3)/2*(us_b-us_c))*2/3;
	//usd=(2*us_a-(us_b+us_c))/3;
	//usq=(us_b-us_c)/sqrt(3);
	/*abs_Us=sqrt(usd*usd+usq*usq);   //电压幅值
	cos_theta_Us=usd/(abs_Us+1e-9);   //角度
	sin_theta_Us=usq/(abs_Us+1e-9);
	
	同步轴系下定子电压空间矢量(将定子电压转到dq轴上)
	cos_theta_Us_p=1;
	sin_theta_Us_p=0;
	Usd_p=abs_Us*cos_theta_Us_p;
	Usq_p=abs_Us*sin_theta_Us_p;

    */

	//PLL闭环跟踪电网电压角度

	e=Usq_p;
	u=discrete_PI(e,e_0,u_0,Kp0,Ki0,T);                              	//PI调节器
	u_0=u;
	e_0=e;
	w_0=u;

	//view_w0=w_0;

	theta_Ug1=theta_Ug0+T*w_0;
	theta_Ug=fmod(theta_Ug1,2*pi);
	theta_Ug0=theta_Ug;

	//view_theta=theta_Ug;

	cos_theta_Us=cos(theta_Ug);
	sin_theta_Us=sin(theta_Ug);
	Usd_p=usd*cos_theta_Us+usq*sin_theta_Us;

	//viewd=Usd_p;

    Usq_p=-usd*sin_theta_Us+usq*cos_theta_Us;

    //viewq= Usq_p;

	
	//坐标正变、换静止轴系下定子电流空间矢量
	//静止轴系下定子电流空间矢量
	is_a=is_a_line;
	is_b=-(is_a_line+is_c_line);
	is_c=is_c_line;
	isd=(2*is_a-(is_b+is_c))/3;
	isq=(is_b-is_c)/sqrt(3);
	abs_Is=sqrt(isd*isd+isq*isq);
	cos_theta_Is=isd/(abs_Is+1e-9);
	sin_theta_Is=isq/(abs_Is+1e-9); 
	
	//viewq=is_a;
	//同步轴系下定子电流空间矢量(将定子电流转到dq轴上)
	cos_theta_Is_p=cos_theta_Is*cos_theta_Us+sin_theta_Is*sin_theta_Us; 
	sin_theta_Is_p=sin_theta_Is*cos_theta_Us-cos_theta_Is*sin_theta_Us; 
	isd_p=abs_Is*cos_theta_Is_p; 
	isq_p=abs_Is*sin_theta_Is_p; 
	
	//坐标正变、转子轴系下转子电流空间矢量
    //转子轴系下转子电流空间矢量
	ir_a=ir_a_line*(-1);                 //电动机惯例
	ir_b=-(ir_a_line+ir_c_line)*(-1);
	ir_c=ir_c_line*(-1);
	ird_r=(2*ir_a-(ir_b+ir_c))/3;
	irq_r=(ir_b-ir_c)/sqrt(3);
	abs_Ir=sqrt(ird_r*ird_r+irq_r*irq_r);
	cos_theta_Ir_r=ird_r/(abs_Ir+1e-9);
	sin_theta_Ir_r=irq_r/(abs_Ir+1e-9);
	//viewd=ir_a;
	//viewq=ir_b;
	//view_theta=ir_c;

	
	//静止轴系下转子电流空间矢量  
	theta_r=Pp*theta_m;											//转子电角度
	cos_theta_Ir=cos_theta_Ir_r*cos(theta_r)-sin_theta_Ir_r*sin(theta_r);
	sin_theta_Ir=sin_theta_Ir_r*cos(theta_r)+cos_theta_Ir_r*sin(theta_r);
	//同步轴系下转子电流空间矢量(将转子电流转到dq轴上)
	cos_theta_Ir_p=cos_theta_Ir*cos_theta_Us+sin_theta_Ir*sin_theta_Us; 
	sin_theta_Ir_p=sin_theta_Ir*cos_theta_Us-cos_theta_Ir*sin_theta_Us; 
	ird_p=abs_Ir*cos_theta_Ir_p;
	//viewd=ird_p;
	irq_p=abs_Ir*sin_theta_Ir_p;
	//viewq=irq_p;
	//view_theta=theta_r;
	
	//	定子功率计算    
	Ps=-3/2*(Usd_p*isd_p+Usq_p*isq_p); 										//“+”表示电机向电网输出有功
	Qs=-3/2*(Usq_p*isd_p-Usd_p*isq_p); 										//“+”表示电机向电网输出滞后无功

	//有功通道
    /*e1=Krc*(Ps_ref-Ps);
      u1=discrete_PI(e1,e1_0,u1_0,Kp1,Ki1,T);                              	//PI调节器
	  u1_0=u1;
	  e1_0=e1;
	  irq_p_ref=u1;*/

	  e2=Ksatrt*(irq_p_ref-irq_p)*(-1);
	  u2=discrete_PI(e2,e2_0,u2_0,Kp2,Ki2,T);           					     //PI调节器
	  u2_0=u2;
	  e2_0=e2;

	//电压限幅
	  u_real2=u2;
	  u_limited2=voltage_limit(u_real2,sta);
	  urq_p_ref=u_limited2;


	  // urq_p_ref=Ur*sin(theta_Ur/180*pi);

   //定子无功调节（无功通道）
	/*e3=Krc*(Qs_ref-Qs);
	  u3=discrete_PI(e3,e3_0,u3_0,Kp3,Ki3,T);                               //PI调节器
	  u3_0=u3;
	  e3_0=e3;
	  ird_p_ref=u3;*/

	  e4=Ksatrt*(ird_p_ref-ird_p)*(-1);
	  u4=discrete_PI(e4,e4_0,u4_0,Kp4,Ki4,T);
	  u4_0=u4;
	  e4_0=e4;

	//限幅
	  u_real4=u4;
	  u_limited4=voltage_limit(u_real4,sta);
	  urd_p_ref=u_limited4;

	  //view_theta=urd_p_ref;

	  //viewd=Tc1;
	  //viewq=Tc2;
	    //viewd=urd_p_ref;
	   // urd_p_ref=Ur*cos(theta_Ur/180*pi);
	//坐标反变换
	//同步轴系下转子电压指令空间矢量
	abs_Ur_ref=sqrt(urd_p_ref*urd_p_ref+urq_p_ref*urq_p_ref);
	cos_theta_Ur_p_ref=urd_p_ref/(abs_Ur_ref+1e-9);
	sin_theta_Ur_p_ref=urq_p_ref/(abs_Ur_ref+1e-9); 
	
	//静止轴系下转子电压指令空间矢量
	cos_theta_Ur_ref=cos_theta_Ur_p_ref*cos_theta_Us-sin_theta_Ur_p_ref*sin_theta_Us; 
	sin_theta_Ur_ref=sin_theta_Ur_p_ref*cos_theta_Us+cos_theta_Ur_p_ref*sin_theta_Us; 
	//转子轴系下转子电压指令空间矢量
	cos_theta_Ur_r_ref=cos_theta_Ur_ref*cos(theta_r)+sin_theta_Ur_ref*sin(theta_r);  
	sin_theta_Ur_r_ref=sin_theta_Ur_ref*cos(theta_r)-cos_theta_Ur_ref*sin(theta_r); 
	//转子轴系下转子三相电压指令
	ura_r_ref=abs_Ur_ref*cos_theta_Ur_r_ref;
	urb_r_ref=abs_Ur_ref*(cos_theta_Ur_r_ref*cos(2*pi/3)+sin_theta_Ur_r_ref*sin(2*pi/3));
	urc_r_ref=abs_Ur_ref*(cos_theta_Ur_r_ref*cos(2*pi/3)-sin_theta_Ur_r_ref*sin(2*pi/3));
    //viewq=ura_r_ref;
    //viewq=urb_r_ref;
    //view_theta=urc_r_ref;
}

//functions definition

float discrete_PI(float e,float e0,float u0,float Kp,float Ki,float t)
{
	float u;
	u=u0+Kp*(e-e0)+Ki*t*e;
	return(u);
}


float voltage_limit(float u_real0,float sta)
{
	  float u_limited;
      if(u_real0>sta)
	  {
    	 u_real0=sta;
	  }
	  else if(u_real0<-sta)
	  {
		 u_real0=-sta;
	  }
      u_limited=u_real0;
	  return(u_limited);
}


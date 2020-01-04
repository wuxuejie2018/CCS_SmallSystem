#ifndef CONTROL_H_
#define CONTROL_H_

#define we 		314.1592653 	//同步角频率
#define Rs_pu  	0.0349          //定子电阻标么值  基值：537.4012/sqrt(3)/16.1151=19.2533
#define Ls_pu	1.0254   		//定子电感标么值  基值：19.2533/2/pi/50=0.0613
#define Lm_pu	0.9725			//激磁电感标么值
#define Lr_pu	1.0254   		//转子电感标么值
#define Pp		3				//电机极对数
#define theta_h 0      			//定子电压和电流硬件测量环节以及离散引起的信号延迟角
#define pi		3.14159

#define K_us	1/537.4012
#define K_is	1/16.1151  				//满载线电流的幅值7.5e3/380/sqrt(3)*sqrt(2)
#define K_ir	1/33.1020     				//7.5e3*0.3/sqrt(3)/185*sqrt(2)
#define Kc_rc	0        				//交叉耦合项补偿系数( Kc_rc=1补偿，Kc_rc=0不补偿)
#define MUdc	565

#define Kp0		180/100*3
#define Ki0     3200/100*3*3
#define T		100e-6

void Control(void);				//函数说明
float discrete_PI(float e,float e0,float u0,float Kp,float Ki,float t);
float voltage_limit(float u_real0,float sta);

#endif /*CONTROL_H_*/

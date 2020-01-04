#ifndef CONTROL_H_
#define CONTROL_H_

#define we 		314.1592653 	//ͬ����Ƶ��
#define Rs_pu  	0.0349          //���ӵ����ôֵ  ��ֵ��537.4012/sqrt(3)/16.1151=19.2533
#define Ls_pu	1.0254   		//���ӵ�б�ôֵ  ��ֵ��19.2533/2/pi/50=0.0613
#define Lm_pu	0.9725			//���ŵ�б�ôֵ
#define Lr_pu	1.0254   		//ת�ӵ�б�ôֵ
#define Pp		3				//���������
#define theta_h 0      			//���ӵ�ѹ�͵���Ӳ�����������Լ���ɢ������ź��ӳٽ�
#define pi		3.14159

#define K_us	1/537.4012
#define K_is	1/16.1151  				//�����ߵ����ķ�ֵ7.5e3/380/sqrt(3)*sqrt(2)
#define K_ir	1/33.1020     				//7.5e3*0.3/sqrt(3)/185*sqrt(2)
#define Kc_rc	0        				//����������ϵ��( Kc_rc=1������Kc_rc=0������)
#define MUdc	565

#define Kp0		180/100*3
#define Ki0     3200/100*3*3
#define T		100e-6

void Control(void);				//����˵��
float discrete_PI(float e,float e0,float u0,float Kp,float Ki,float t);
float voltage_limit(float u_real0,float sta);

#endif /*CONTROL_H_*/

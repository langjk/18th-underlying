#include "sys.h"

char Page_Show[]="";

void All_Init()
{
	__disable_irq();// �ر����ж� ,���������жϲ���
	
	SystemInit();   //ϵͳʱ�ӳ�ʼ��
	delay_init();	  //��ʱ������ʼ��
  delay_ms(1000); //��ʱ1��ȴ�ϵͳʱ���ȶ� �ⲿ��Դ��ѹ��·�ȶ�	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//�жϷ�����ռʽ���ȼ�����0-7
	Led_Init();     //LED��ʼ����������led��˸��ʾϵͳ�����ˣ�  PC13
  //Key_Init();   //��ת���������ְ�����ʼ��     PA11 12 15  PB3 4 14��ע��Ҫ����jtag���ܣ� 
	
	TSUI_Init();    //oled��spi��ʼ�� ��ȡflash�����Ĳ��� ������oled��ʾʹ�õ�spiͨ�� ����spi��Ҫ���ߣ�
	//LCD_P6x8StrW(0,0," singing:");
	OLED_Clear();  	//����
	delay_ms(1000); //��ʱ1��ȴ���ʾ�ȶ� 	
	
	Adc_Init();    //8·���ģ�����ɼ���ʼ��      PA0-PA7
	MPU_Init();		 //MPU6050��ʼ��                PB10-SCL PB11-SDA
	Mpu_Dmp_Init();//6050 dmp		                

	Beep_Init();   //��������ʼ��                PB12
	Encode_Exti_Init();//�������ⲿ�жϳ�ʼ��     PB8 PB9  ��ע�����ȼ�Ҫ����key��
	Motor_TIM1_Init(7199,1);//���pwm��ʼ������   t1ch1-PB13 t1ch1n-PA8
	Steer_TIM3_PWM_Init(7199,0);//���PWM���     Timer3 T3-ch2PB5	
	Key_DMA_EXTI_Init(); //��ת���������ְ�����ʼ��     PA11 12 15  PB3 4 14��ע��Ҫ����jtag���ܣ� 
	                     /*cw��ccw ���������AB��ʹ��dma ����ʹ���ⲿ�ж�*/
	//TIM4_Int_Init(199,719);       //��ʱ�� tim4 ��ʱ�жϳ�ʼ��,200HZ��5ms
	TIM4_Int_Init(999,719);       //��ʱ�� tim4 ��ʱ�жϳ�ʼ��,100HZ��10ms
	
	__enable_irq();    //�������жϣ���ʼ�������о�����Ҫ�����ж�
	

//	OLED_DrawBMP(92, 1,128, 8,PKQ);
//	sprintf(Page_Show,"%d/%d",Show_Page+1,Show_Page_Num);
//	OLED_ShowString(104,0,Page_Show,12);
}





int Get_Speed(unsigned int R_L)  //1Ϊ���֣�0λ����
{
	int speed = 0,raw_speed=0;
	if(R_L)	raw_speed = Read_Encoder(2);  //���ֱ�����������
	else	raw_speed = Read_Encoder(1);  //���ֱ�����������
	//65mm�־������תһȦ11�������źţ�10ms��ȡһ��
	//speed = (raw_speed * 1000 / 110)*(3.14159*65.0/1000);  //������һȦ���11�����壬raw_speed������*1000/11/10ms*60����r/s��,ת��Ϊm/s
	return raw_speed;
}


int Motor_PID_Cal_L(int input_speed,int setspeed)
{
  static int pwmout_L=0,last_error_L=0,last_last_error_R=0;
  int error =setspeed - input_speed;
  int d_error=error-last_error_L;
  int dd_error = -2*last_error_L+error+last_last_error_R;  
  pwmout_L+=Sped_KP*d_error/10 +Sped_KI*error/10+Sped_KD*dd_error/10;
  last_last_error_R=last_error_L;
  last_error_L = error;
	if(pwmout_L > 7200) pwmout_L = 7200;
	if(pwmout_L < -7200) pwmout_L = -7200;
  return pwmout_L;
}

int Motor_PID_Cal_R(int input_speed,int setspeed)
{
  static int pwmout=0,last_error=0,last_last_error=0;
  int error =setspeed - input_speed;
  int d_error=error-last_error;
  int dd_error = -2*last_error+error+last_last_error;  
  pwmout+=Sped_KP*d_error/10 +Sped_KI*error/10+Sped_KD*dd_error/10;
  last_last_error=last_error;
  last_error = error;
	if(pwmout > 7200) pwmout = 7200;
	if(pwmout < -7200) pwmout = -7200;
  return pwmout;
}


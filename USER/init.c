#include "sys.h"

char Page_Show[]="";

void All_Init()
{
	__disable_irq();// 关闭总中断 ,避免意外中断产生
	
	SystemInit();   //系统时钟初始化
	delay_init();	  //延时函数初始化
  delay_ms(1000); //延时1秒等待系统时钟稳定 外部电源电压电路稳定	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//中断分组抢占式优先级分组0-7
	Led_Init();     //LED初始化（可以用led闪烁提示系统正在运）  PC13
  //Key_Init();   //旋转编码器波轮按键初始化     PA11 12 15  PB3 4 14（注意要禁用jtag功能） 
	
	TSUI_Init();    //oled的spi初始化 读取flash存贮的参数 （这里oled显示使用的spi通信 想用spi需要飞线）
	//LCD_P6x8StrW(0,0," singing:");
	OLED_Clear();  	//清屏
	delay_ms(1000); //延时1秒等待显示稳定 	
	
	Adc_Init();    //8路电磁模拟量采集初始化      PA0-PA7
	MPU_Init();		 //MPU6050初始化                PB10-SCL PB11-SDA
	Mpu_Dmp_Init();//6050 dmp		                

	Beep_Init();   //蜂鸣器初始化                PB12
	Encode_Exti_Init();//编码器外部中断初始化     PB8 PB9  （注意优先级要高于key）
	Motor_TIM1_Init(7199,1);//电机pwm初始化互补   t1ch1-PB13 t1ch1n-PA8
	Steer_TIM3_PWM_Init(7199,0);//舵机PWM输出     Timer3 T3-ch2PB5	
	Key_DMA_EXTI_Init(); //旋转编码器波轮按键初始化     PA11 12 15  PB3 4 14（注意要禁用jtag功能） 
	                     /*cw和ccw 正交解码的AB相使用dma 其余使用外部中断*/
	//TIM4_Int_Init(199,719);       //定时器 tim4 定时中断初始化,200HZ，5ms
	TIM4_Int_Init(999,719);       //定时器 tim4 定时中断初始化,100HZ，10ms
	
	__enable_irq();    //开启总中断，初始化过程中尽量不要进行中断
	

//	OLED_DrawBMP(92, 1,128, 8,PKQ);
//	sprintf(Page_Show,"%d/%d",Show_Page+1,Show_Page_Num);
//	OLED_ShowString(104,0,Page_Show,12);
}





int Get_Speed(unsigned int R_L)  //1为右轮，0位左轮
{
	int speed = 0,raw_speed=0;
	if(R_L)	raw_speed = Read_Encoder(2);  //右轮编码器脉冲数
	else	raw_speed = Read_Encoder(1);  //左轮编码器脉冲数
	//65mm轮径，电机转一圈11个脉冲信号，10ms读取一次
	//speed = (raw_speed * 1000 / 110)*(3.14159*65.0/1000);  //编码器一圈输出11个脉冲，raw_speed脉冲数*1000/11/10ms*60等于r/s，,转换为m/s
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


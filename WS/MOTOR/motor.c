#include "sys.h"

void Motor_Init(void)//电机驱动
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE); 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50MHZ
  GPIO_Init(GPIOD, &GPIO_InitStructure);			

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);		
	PCout(5)=1;	
}

void Set_Pwm(int moto1,int moto2)//电机的方向控制
{
//	  	if(moto1<0) 	AIN2=1,			AIN1=0;
//				
//			else 					AIN2=0,			AIN1=1;				
//			PWMA=myabs(moto1);
//			
//		  if(moto2<0)		BIN1=1,			BIN2=0;
//			else					BIN1=0,			BIN2=1;
//			PWMB=myabs(moto2);
//	
	
    	if(moto1<0)			AIN2=1,			AIN1=0;
			else 	          AIN2=0,			AIN1=1;
			PWMA=myabs(moto1);
		  if(moto2<0)	BIN1=0,			BIN2=1;
			else        BIN1=1,			BIN2=0;
			PWMB=myabs(moto2);	
}



int myabs(int a)//
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}



void Xianfu_Pwm(void)//限幅
{
	                                 //PWM满幅是7200 限制在7000
    if(Moto1<-7200 ) Moto1=-7200 ;
		if(Moto1>7200 )  Moto1=7200 ;
	  if(Moto2<-7200 ) Moto2=-7200 ;
		if(Moto2>7200 )  Moto2=7200 ;
}


void Turn_Off(float angle) //判断小车的倾斜角来使电机打死
{
		if(angle<-40||angle>40)	    //倾角大于40度关闭电机				
		{	                                   															 
				Moto1=0;
				Moto2=0;
		}		

}
	

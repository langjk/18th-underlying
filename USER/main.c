#include "sys.h"
float pitch=0,roll=0,yaw=0; 								  			 //欧拉角
short aacx,aacy,aacz;													 //传感器原始数据
short gyrox,gyroy,gyroz;											 //陀螺仪数据
int Encoder_Left,Encoder_Right;         		 //左右编码器
int Moto1=0,Moto2=0;			
unsigned int Time_Count=0,T1_Count=0,T2_Count=0,T3_Count=0;

int Key_Test=0;
unsigned char Flag_Task=0;
int Sped_KP = 1200,Sped_KI = 350,Sped_KD = 15; //110/45/3
int Speed_Set_L=30,Speed_Set_R=30,Speed_R=0,Speed_L=0;

int Adc_M1,Adc_M2,Adc_M3,Adc_M4,Adc_M5,Adc_M6,Adc_M7,Adc_M8;//adc采集
int Adc_Set_M5,Adc_Set_M4,Adc_Set_M3,Adc_Set_M2,Adc_Set_M1;//adc的给定阈值

int main(void)	
{ 
	All_Init();//所有模块的初始化
  while(1)	
	{	
//		if(Time_Count-T1_Count>=100)  //500ms
//		{
//			T1_Count=Time_Count;
//			//BEEP=~BEEP;
//			LED1=~LED1;
////			LED2=~LED2;
////			LED3=~LED3;
//		}		
//		if(Time_Count-T2_Count>=20)  //200ms
//		{
//			T2_Count=Time_Count;
//			Mpu_Dmp_Get_Data(&pitch,&roll,&yaw);									//欧拉角的数据
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);							//陀螺仪数据
//			Oled_Show();	//更新OLED显示
//		}
//		if(Time_Count-T3_Count>=10)  //100ms
//		{
//			Key_Test=Key_Scan();  //获取按键检测值
//			if(!Key_Test)	Show_Test=1;  //检测到按键松开，恢复按键作用使能
//			if(Key_Test&&Show_Test)  //按键按下且按键使能
//			{
//				Para_Ref();
//			}
//		}
    TSUI_ButtonEvent();//按键查询与响应 这里检测是否有旋转编码器的旋转 按下  波轮的上下翻页和摁下  （标志位置位在中断进行）
    TSUI_Display();    //oled显示函数   显示数据和参数



	} 	
}





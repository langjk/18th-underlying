#include "sys.h"
float pitch=0,roll=0,yaw=0; 								  			 //ŷ����
short aacx,aacy,aacz;													 //������ԭʼ����
short gyrox,gyroy,gyroz;											 //����������
int Encoder_Left,Encoder_Right;         		 //���ұ�����
int Moto1=0,Moto2=0;			
unsigned int Time_Count=0,T1_Count=0,T2_Count=0,T3_Count=0;

int Key_Test=0;
unsigned char Flag_Task=0;
int Sped_KP = 1200,Sped_KI = 350,Sped_KD = 15; //110/45/3
int Speed_Set_L=30,Speed_Set_R=30,Speed_R=0,Speed_L=0;

int Adc_M1,Adc_M2,Adc_M3,Adc_M4,Adc_M5,Adc_M6,Adc_M7,Adc_M8;//adc�ɼ�
int Adc_Set_M5,Adc_Set_M4,Adc_Set_M3,Adc_Set_M2,Adc_Set_M1;//adc�ĸ�����ֵ

int main(void)	
{ 
	All_Init();//����ģ��ĳ�ʼ��
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
//			Mpu_Dmp_Get_Data(&pitch,&roll,&yaw);									//ŷ���ǵ�����
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);							//����������
//			Oled_Show();	//����OLED��ʾ
//		}
//		if(Time_Count-T3_Count>=10)  //100ms
//		{
//			Key_Test=Key_Scan();  //��ȡ�������ֵ
//			if(!Key_Test)	Show_Test=1;  //��⵽�����ɿ����ָ���������ʹ��
//			if(Key_Test&&Show_Test)  //���������Ұ���ʹ��
//			{
//				Para_Ref();
//			}
//		}
    TSUI_ButtonEvent();//������ѯ����Ӧ �������Ƿ�����ת����������ת ����  ���ֵ����·�ҳ������  ����־λ��λ���жϽ��У�
    TSUI_Display();    //oled��ʾ����   ��ʾ���ݺͲ���



	} 	
}





#ifndef __SYS_H
#define __SYS_H	 

/****stm32�ײ��ļ�****/
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "oled.h"
#include "timer.h"
#include "led.h"
#include "key.h"
#include "init.h"
#include "mpu6050.h"
#include "mpuiic.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "motor.h"
#include "encoder.h"
#include "pwm.h"
#include "adc.h"
#include  "flash.h"


typedef unsigned char	        uint8;  /*  8 bits */
typedef unsigned short int	uint16; /* 16 bits */
typedef unsigned long int	uint32; /* 32 bits */

typedef signed char		int8;   /*  8 bits */
typedef short int	        int16;  /* 16 bits */
typedef int		        int32;  /* 32 bits */

/******���ܳ����***********/
#include "setpara.h"//����ͷ�ļ�
#include "TJSC_Display.h"//display��ʾͷ�ļ�
#include "TJSC_UI.h"   //uiͷ�ļ�

#include "data_input.h"
#include "data_output.h"
#include "data_process.h"




/****��׼���ļ�****/
#include <string.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stm32f10x_tim.h"

/****��Ƭ������****/




#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

/****Ex_NVIC_Configר�ö���****/
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 

#define FTIR   1  //�½��ش���
#define RTIR   2  //�����ش���

/****JTAGģʽ���ö���****/
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	


#define TIM4_MS 5

/****ȫ�ֱ���****/
typedef struct STATUS_CAR_STRUCT
{
  uint8 status;         //С������״̬
  uint8 status_message;
  uint8 status_reed;    //�ɻɹ�״̬
  uint32 reed_time;     //�ɻɹ�
  uint16 batt_volt;     //��ص�ѹ
  uint32 RUNTIME;       //С������ʱ��
  uint32 SLOPETIME1;
  uint32 RACETIME;
  uint32 SLOPETIME;
  uint32 SLOPETIME2;
  uint8 mpu6050_error;
  uint32 mpu6050_error_count;
}STATUS_CAR_STRUCT;

extern STATUS_CAR_STRUCT mycar;               //С����״̬

extern int T;

extern float pitch,roll,yaw; 										//ŷ����
extern short aacx,aacy,aacz;										//������ԭʼ����
extern short gyrox,gyroy,gyroz;									//������ԭʼ����
extern int   Encoder_Left,Encoder_Right;        //���ұ�����
extern int   en_pos1;
extern int 	 Moto1,Moto2;												//�������ı���								    
void NVIC_Configuration(void);									//�ж����ȼ�����	 
extern int qian,hou,left,right,csb1,qjs,hjs,Qjs,Hjs;						//�������Ƶı���
extern float csbcj;      												//������������
extern int Key_Test;
extern unsigned int Time_Count,T1_Count,T2_Count;
extern unsigned char Flag_Task;
extern int Adc_M1,Adc_M2,Adc_M3,Adc_M4,Adc_M5,Adc_M6,Adc_M7,Adc_M8;
extern int Adc_Set_M5, Adc_Set_M4,Adc_Set_M3,Adc_Set_M2,Adc_Set_M1;
extern int Sped_KP,Sped_KI,Sped_KD;
extern int Speed_Set_L,Speed_Set_R,Speed_R,Speed_L;
extern unsigned int Show_Para_Order,Show_Data_Order,Show_Mode,Show_Test,Para_Num,Data_Num,Show_Page,Show_Page_Num;
extern unsigned char PKQ[];
#endif


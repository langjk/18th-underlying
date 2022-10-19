#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "string.h"

#define depth 130

#define ROBOT_M1_PIN            GPIO_Pin_0
#define ROBOT_M1_GPIO_PORT      GPIOA
#define ROBOT_M1_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ROBOT_M1_ADC_CH         ADC_Channel_0
#define ROBOT_M1_ADC_CH_NUM     0

#define ROBOT_M2_PIN            GPIO_Pin_1
#define ROBOT_M2_GPIO_PORT      GPIOA
#define ROBOT_M2_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ROBOT_M2_ADC_CH         ADC_Channel_1
#define ROBOT_M2_ADC_CH_NUM     1

#define ROBOT_M3_PIN            GPIO_Pin_2
#define ROBOT_M3_GPIO_PORT      GPIOA
#define ROBOT_M3_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ROBOT_M3_ADC_CH         ADC_Channel_2
#define ROBOT_M3_ADC_CH_NUM     2

#define ROBOT_M4_PIN            GPIO_Pin_3
#define ROBOT_M4_GPIO_PORT      GPIOA
#define ROBOT_M4_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ROBOT_M4_ADC_CH         ADC_Channel_3
#define ROBOT_M4_ADC_CH_NUM     3


#define ROBOT_M5_PIN            GPIO_Pin_4
#define ROBOT_M5_GPIO_PORT      GPIOA
#define ROBOT_M5_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ROBOT_M5_ADC_CH         ADC_Channel_4
#define ROBOT_M5_ADC_CH_NUM     4

#define ROBOT_M6_PIN            GPIO_Pin_5
#define ROBOT_M6_GPIO_PORT      GPIOA
#define ROBOT_M6_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ROBOT_M6_ADC_CH         ADC_Channel_5
#define ROBOT_M6_ADC_CH_NUM     5


#define ROBOT_M7_PIN            GPIO_Pin_6
#define ROBOT_M7_GPIO_PORT      GPIOA
#define ROBOT_M7_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ROBOT_M7_ADC_CH         ADC_Channel_6
#define ROBOT_M7_ADC_CH_NUM     6

#define ROBOT_M8_PIN            GPIO_Pin_7
#define ROBOT_M8_GPIO_PORT      GPIOA
#define ROBOT_M8_GPIO_CLK       RCC_APB2Periph_GPIOA
#define ROBOT_M8_ADC_CH         ADC_Channel_7
#define ROBOT_M8_ADC_CH_NUM     7
//#define ROBOT_BATTERY_ADC_CLK        RCC_APB2Periph_ADC1


extern  u16 ADC_ConvertedValue;  

extern u8 displayflag;

extern  u16 lcddmaflag;
extern  u16   displayadc[depth];
extern  int   Adclog;

extern  int   AdcMax;

extern u32 AdcNum;
extern int16_t AdcData[6000];

extern  int16_t AdcAgv;
extern int16_t AdcSum;



void Adc_Init(void);
void ADC_GPIO_Init(void);
void DMA_ADC_Init(void);
u16 Get_Adc(ADC_TypeDef* ADCx,u8 ch);
#endif /* __ADC_H */


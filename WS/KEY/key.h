#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
/****���Ŷ���****/
//��ת������A��:PA15
#define SW_CHA_GPIO_PORT      GPIOA
#define SW_CHA_PIN            GPIO_Pin_15
#define SW_CHA_GPIO_CLK       RCC_APB2Periph_GPIOA
#define SW_CHA_EXTI_PORT      GPIO_PortSourceGPIOA
#define SW_CHA_IRQ            EXTI15_10_IRQn
#define SW_CHA_EXTI_LINE      EXTI_Line15
#define SW_CHA_EXTI_PIN       GPIO_PinSource15

#define SW_CHA PAin(15)
//��ת������B��:PA12
#define SW_CHB_GPIO_PORT      GPIOA
#define SW_CHB_PIN            GPIO_Pin_12
#define SW_CHB_GPIO_CLK       RCC_APB2Periph_GPIOA
#define SW_CHB_EXTI_PORT      GPIO_PortSourceGPIOA
#define SW_CHB_IRQ            EXTI15_10_IRQn
#define SW_CHB_EXTI_LINE      EXTI_Line12
#define SW_CHB_EXTI_PIN       GPIO_PinSource12

#define SW_CHB PAin(12)

//��ת������������PA11
#define SW_PRESS_GPIO_PORT      GPIOA
#define SW_PRESS_PIN            GPIO_Pin_11
#define SW_PRESS_GPIO_CLK       RCC_APB2Periph_GPIOA
#define SW_PRESS_EXTI_PORT      GPIO_PortSourceGPIOA
#define SW_PRESS_IRQ            EXTI15_10_IRQn
#define SW_PRESS_EXTI_LINE      EXTI_Line11
#define SW_PRESS_EXTI_PIN       GPIO_PinSource11

#define SW_PRESS PAin(11)

#define SW_PRESS_ADDR    0X9000   //11λ ��0 ˵��pa11 �͵�ƽ press ����
#define SW_CW_ADDR       0X8800 
#define SW_CCW_ADDR      0X1800   
#define SW_ADDR          0x9800

//�����Ϸ� -PB14
#define KEY_UP_GPIO_PORT      GPIOB
#define KEY_UP_PIN            GPIO_Pin_14
#define KEY_UP_GPIO_CLK       RCC_APB2Periph_GPIOB
#define KEY_UP_EXTI_PORT      GPIO_PortSourceGPIOB
#define KEY_UP_IRQ            EXTI15_10_IRQn
#define KEY_UP_EXTI_LINE      EXTI_Line14
#define KEY_UP_EXTI_PIN       GPIO_PinSource14

#define KEY_UP PBin(14)
//�����·� -PB3
#define KEY_DOWN_GPIO_PORT GPIOB
#define KEY_DOWN_PIN GPIO_Pin_3
#define KEY_DOWN_GPIO_CLK       RCC_APB2Periph_GPIOB
#define KEY_DOWN_EXTI_PORT      GPIO_PortSourceGPIOB
#define KEY_DOWN_IRQ            EXTI3_IRQn
#define KEY_DOWN_EXTI_LINE      EXTI_Line3
#define KEY_DOWN_EXTI_PIN       GPIO_PinSource3

#define KEY_DOWN PBin(3)

//���ְ��� -PB4
#define KEY_PUSH_GPIO_PORT      GPIOB
#define KEY_PUSH_PIN            GPIO_Pin_4
#define KEY_PUSH_GPIO_CLK       RCC_APB2Periph_GPIOB
#define KEY_PUSH_EXTI_PORT      GPIO_PortSourceGPIOB
#define KEY_PUSH_IRQ            EXTI4_IRQn
#define KEY_PUSH_EXTI_LINE      EXTI_Line4
#define KEY_PUSH_EXTI_PIN       GPIO_PinSource4


#define KEY_PUSH PBin(4)



/****��������****/
void Key_Init(void);
void Key_DMA_EXTI_Init(void);
int Key_Scan(void);
#endif

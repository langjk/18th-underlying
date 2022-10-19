#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
/****引脚定义****/
//旋转编码器A相:PA15
#define SW_CHA_GPIO_PORT      GPIOA
#define SW_CHA_PIN            GPIO_Pin_15
#define SW_CHA_GPIO_CLK       RCC_APB2Periph_GPIOA
#define SW_CHA_EXTI_PORT      GPIO_PortSourceGPIOA
#define SW_CHA_IRQ            EXTI15_10_IRQn
#define SW_CHA_EXTI_LINE      EXTI_Line15
#define SW_CHA_EXTI_PIN       GPIO_PinSource15

#define SW_CHA PAin(15)
//旋转编码器B相:PA12
#define SW_CHB_GPIO_PORT      GPIOA
#define SW_CHB_PIN            GPIO_Pin_12
#define SW_CHB_GPIO_CLK       RCC_APB2Periph_GPIOA
#define SW_CHB_EXTI_PORT      GPIO_PortSourceGPIOA
#define SW_CHB_IRQ            EXTI15_10_IRQn
#define SW_CHB_EXTI_LINE      EXTI_Line12
#define SW_CHB_EXTI_PIN       GPIO_PinSource12

#define SW_CHB PAin(12)

//旋转编码器按键：PA11
#define SW_PRESS_GPIO_PORT      GPIOA
#define SW_PRESS_PIN            GPIO_Pin_11
#define SW_PRESS_GPIO_CLK       RCC_APB2Periph_GPIOA
#define SW_PRESS_EXTI_PORT      GPIO_PortSourceGPIOA
#define SW_PRESS_IRQ            EXTI15_10_IRQn
#define SW_PRESS_EXTI_LINE      EXTI_Line11
#define SW_PRESS_EXTI_PIN       GPIO_PinSource11

#define SW_PRESS PAin(11)

#define SW_PRESS_ADDR    0X9000   //11位 是0 说明pa11 低电平 press 触发
#define SW_CW_ADDR       0X8800 
#define SW_CCW_ADDR      0X1800   
#define SW_ADDR          0x9800

//波轮上翻 -PB14
#define KEY_UP_GPIO_PORT      GPIOB
#define KEY_UP_PIN            GPIO_Pin_14
#define KEY_UP_GPIO_CLK       RCC_APB2Periph_GPIOB
#define KEY_UP_EXTI_PORT      GPIO_PortSourceGPIOB
#define KEY_UP_IRQ            EXTI15_10_IRQn
#define KEY_UP_EXTI_LINE      EXTI_Line14
#define KEY_UP_EXTI_PIN       GPIO_PinSource14

#define KEY_UP PBin(14)
//波轮下翻 -PB3
#define KEY_DOWN_GPIO_PORT GPIOB
#define KEY_DOWN_PIN GPIO_Pin_3
#define KEY_DOWN_GPIO_CLK       RCC_APB2Periph_GPIOB
#define KEY_DOWN_EXTI_PORT      GPIO_PortSourceGPIOB
#define KEY_DOWN_IRQ            EXTI3_IRQn
#define KEY_DOWN_EXTI_LINE      EXTI_Line3
#define KEY_DOWN_EXTI_PIN       GPIO_PinSource3

#define KEY_DOWN PBin(3)

//波轮按下 -PB4
#define KEY_PUSH_GPIO_PORT      GPIOB
#define KEY_PUSH_PIN            GPIO_Pin_4
#define KEY_PUSH_GPIO_CLK       RCC_APB2Periph_GPIOB
#define KEY_PUSH_EXTI_PORT      GPIO_PortSourceGPIOB
#define KEY_PUSH_IRQ            EXTI4_IRQn
#define KEY_PUSH_EXTI_LINE      EXTI_Line4
#define KEY_PUSH_EXTI_PIN       GPIO_PinSource4


#define KEY_PUSH PBin(4)



/****函数声明****/
void Key_Init(void);
void Key_DMA_EXTI_Init(void);
int Key_Scan(void);
#endif

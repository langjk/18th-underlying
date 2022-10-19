#ifndef __LED_H
#define __LED_H

#include "sys.h"
/****Òý½Å¶¨Òå****/
//LED1:PC13
#define LED1_GPIO_PORT GPIOC
#define LED1_PIN GPIO_Pin_13
#define LED1_GPIO_CLK RCC_APB2Periph_GPIOC
#define LED1 PCout(13)
//LED2:PF13
//#define USE_LED2
#define LED2_GPIO_PORT GPIOF
#define LED2_PIN GPIO_Pin_13
#define LED2_GPIO_CLK RCC_APB2Periph_GPIOF
#define LED2 PFout(13)
////LED3:PA5
//#define USE_LED3
#define LED3_GPIO_PORT GPIOA
#define LED3_PIN GPIO_Pin_5
#define LED3_GPIO_CLK RCC_APB2Periph_GPIOA
#define LED3 PAout(5)
//·äÃùÆ÷:PB12
#define BEEP_GPIO_PORT GPIOB
#define BEEP_PIN GPIO_Pin_12
#define BEEP_GPIO_CLK RCC_APB2Periph_GPIOB
#define BEEP PBout(12)

void Led_Init(void);
void Beep_Init(void);

#endif


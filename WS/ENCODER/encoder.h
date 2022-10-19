#ifndef __ENCODER_H
#define __ENCODER_H

#include <sys.h>	 

#define ENCODER_TIM_PERIOD (u16)(65535)   //65536

#define HIGH 1
#define LOW  0

#define ROBOT_ENCODER1_A_PIN         GPIO_Pin_8              //M1 -±àÂëÆ÷A  PA15
#define ROBOT_ENCODER1_B_PIN         GPIO_Pin_9              //M1 -±àÂëÆ÷B  PB3
#define ROBOT_ENCODER1_A_GPIO_PORT     GPIOB
#define ROBOT_ENCODER1_B_GPIO_PORT     GPIOB
#define ROBOT_ENCODER1_A_GPIO_CLK      RCC_APB2Periph_GPIOB
#define ROBOT_ENCODER1_B_GPIO_CLK      RCC_APB2Periph_GPIOB
#define ROBOT_ENCODER1_A_EXTI_LINE   EXTI_Line8
#define ROBOT_ENCODER1_B_EXTI_LINE   EXTI_Line9
#define ROBOT_ENCODER1_A_IRQ         EXTI9_5_IRQn
#define ROBOT_ENCODER1_B_IRQ         EXTI9_5_IRQn
#define ROBOT_ENCODER1_A_EXTI_PORT   GPIO_PortSourceGPIOB
#define ROBOT_ENCODER1_B_EXTI_PORT   GPIO_PortSourceGPIOB
#define ROBOT_ENCODER1_A_EXTI_PIN    GPIO_PinSource8
#define ROBOT_ENCODER1_B_EXTI_PIN    GPIO_PinSource9

void Encode_Exti_Init(void);
void Encoder_Right_Init(void);
void Encoder_Left_Init(void);
int Read_Encoder(u8 TIMX);

#endif

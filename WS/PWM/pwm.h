#ifndef __PWM_H
#define __PWM_H


#include "sys.h"
#include "stm32f10x_tim.h" 

void TIM3_PWM_Init(u16 arr,u16 psc);
void Steer_TIM3_PWM_Init(u16 arr,u16 psc );
void Motor_TIM1_Init(u16 psc,u16 arr);
#endif

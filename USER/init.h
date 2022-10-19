#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"

void All_Init(void);
void Oled_First_Show(void);
void Oled_Show(void);
int Get_Speed(unsigned int R_L);
int Motor_PID_Cal_L(int input_speed,int setspeed);
int Motor_PID_Cal_R(int input_speed,int setspeed);
void Para_Ref(void);

#endif


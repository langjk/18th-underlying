#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	


#define PWMA   TIM3->CCR1  //PA6  ◊Û¬÷

#define AIN2   PDout(7)
#define AIN1   PDout(6)
#define BIN1   PDout(4)
#define BIN2   PDout(5)

#define PWMB   TIM3->CCR2  //PA7   ”“¬÷

void Motor_Init(void);
void Set_Pwm(int moto1,int moto2);
int myabs(int a);
void Xianfu_Pwm(void);
void Turn_Off(float angle);
#endif

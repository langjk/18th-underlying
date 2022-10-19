#ifndef _DATA_OUTPUT_H_
#define _DATA_OUTPUT_H_

#include "sys.h"

typedef struct outdata_STRUCT
{
  int pwm_left;
  int pwm_right;
//  int pwm_bal;
//  int pwm_bal_p;
//  int pwm_bal_d;
  int pwm_speed;
  int pwm_speed_p;
  int pwm_speed_i;
  int pwm_dir;
  int pwm_dir_cal;
}outdata_STRUCT;

void PWM_Output(void);


#endif

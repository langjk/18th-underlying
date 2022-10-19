//#include "common.h"
#include "data_output.h"
//#include "setpara.h"
//#include "CarStatus.h"
//#include "Task_RTDBG.h"
//#include "MPU6050_ForDMP.h"

#define limit(value,min,max) (value > (max) ? (max) : ( value < (min) ? (min) : (value) ))

outdata_STRUCT outdata; 

void PWM_Output()
{
  setpara.TestLR = limit(setpara.TestLR,0,20);
  switch(setpara.TestLR)  //PWM¹¦ÄÜ²âÊÔ  
  {
  case 1:
    outdata.pwm_left = setpara.TestPWM;
    outdata.pwm_right = 0;
    break;
  case 2:
    outdata.pwm_left = 0;    
    outdata.pwm_right = setpara.TestPWM;
    break;
  case 3:
    outdata.pwm_right = setpara.TestPWM;
    outdata.pwm_left = setpara.TestPWM;
    break;
  case 4:
    outdata.pwm_left = 0;
    outdata.pwm_right = 0;
    break;
  case 5:
    outdata.pwm_right = 0;
    break;
  case 6:
    outdata.pwm_left = 0;
    break;
  case 10:
//    if((Car_GetRunTime()/(setpara.TestShakePeriod/4)+1)/2%2==0)  //Æ½ºâ³µÕñ¶¯²âÊÔ
//      outdata.pwm_left = outdata.pwm_right = setpara.TestPWM;
//    else
//      outdata.pwm_left = outdata.pwm_right = -setpara.TestPWM;
  default:
    break;
  }

  if(mycar.status!=0)
  {
//    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch6,outdata.pwm_left>0?outdata.pwm_left:0);    //×ó+
//    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch7,outdata.pwm_left<0?-outdata.pwm_left:0);    //×ó-
//    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch5,outdata.pwm_right>0?outdata.pwm_right:0);   //ÓÒ+
//    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4,outdata.pwm_right<0?-outdata.pwm_right:0);   //ÓÒ-
  }
  else
  {
//    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4,0);
//    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch5,0);
//    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch6,0);
//    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch7,0);
  }
}

#include "sys.h"

#include "math.h"
#include "setpara.h"
//#include "CarStatus.h"
//#include "Task_RTDBG.h"

#define sgn(x)((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))
#define limit(value,min,max) (value > (max) ? (max) : ( value < (min) ? (min) : (value) ))
#define MAX_PWM 9900
#define _ABS(val) (val>0?val:-(val))
extern indata_STRUCT indata;
extern outdata_STRUCT outdata;

void Data_Process(void);
void Track_Cal(void);
int dir_cal(void);
int balance_cal(void);
int speed_cal(void);
//int Angel_Weight_Cal(int xvalue,int* setarray);
//int Speed_Weight_Cal(int xvalue,int* setarray);

void Data_Process()
{
  if(mycar.status==3)  //停车状态保持方向控制防止冲出赛道
  {
   // outdata.pwm_bal = 0;    
    outdata.pwm_speed = 0;    
    outdata.pwm_dir = dir_cal();
    outdata.pwm_left = outdata.pwm_dir;
    outdata.pwm_right = -outdata.pwm_dir;
  }
  else
  {
//    outdata.pwm_bal = balance_cal();
    outdata.pwm_dir = dir_cal();
   // outdata.pwm_left  = outdata.pwm_bal + outdata.pwm_speed + outdata.pwm_dir;
   // outdata.pwm_right = outdata.pwm_bal + outdata.pwm_speed - outdata.pwm_dir;
  }
  outdata.pwm_left = limit(outdata.pwm_left, -MAX_PWM, MAX_PWM);
  outdata.pwm_right = limit(outdata.pwm_right, -MAX_PWM, MAX_PWM);
}
int angle_cal()
{
//  static int error,derror,last_error,tempAngle;
//  if(mycar.status()<=1)
//  {
//    error = derror = last_error = 0;
//    tempAngle = setpara.BalAngle;
//  }
//  else
//  {
//    error =  setpara.SetSpeed - indata.Speed;
//    derror =  error - last_error;
//    last_error = error;
//    tempAngle += setpara.SpeedKp * derror + setpara.SpeedKi * error/100;
//  }
//  const int setAccTime = 3000;
//  if(Car_GetRunTime()<setAccTime)
//    tempAngle = limit(tempAngle,
//                      0,
//                      ((setAccTime - Car_GetRunTime())*4500+Car_GetRunTime()*setpara.iSpeedMax)/setAccTime
//                        );
//  else
//    tempAngle = limit(tempAngle,0,setpara.iSpeedMax);
//  return tempAngle;
  return setpara.BalAngle;
}
int balance_cal()
{
  static int error,pwmout,derror;
  error =  angle_cal()-indata.angle;
  derror = indata.gx;   //d(setpara.BalAngle-indata.angle)/dt = -d(indata.angle)/dt = - (-indata.gx)
  pwmout = -setpara.BalKp * error - setpara.BalKd * derror/10;
 // outdata.pwm_bal_p = -setpara.BalKp * error;
 // outdata.pwm_bal_d = - setpara.BalKd * derror/10;
//  pwmout = limit(pwmout, -2*MAX_PWM, 2*MAX_PWM);
  return pwmout;
}


int dir_cal()
{
  static int error,pwmout,derror;
  
 // int dirkp_calib = Speed_Weight_Cal(indata.Speed,setpara.spd_dirkp_array);
//    * Angel_Weight_Cal(indata.angle,setpara.ang_dirkp_array) ;
//  error =  indata.caminfo.dir;
//  derror = indata.caminfo.ddir;
//  pwmout = (setpara.DirKp*dirkp_calib)* error/100 + setpara.DirKd * derror + setpara.GzKd * indata.gz/10;
//  outdata.pwm_dir_cal = pwmout;
//  int pwm_balspd = outdata.pwm_bal + outdata.pwm_speed;
//  int pwm_dir_limit = 0; 
//  if(_ABS(pwm_balspd) < MAX_PWM)  
//    pwm_dir_limit = MAX_PWM - _ABS(pwm_balspd);
//  outdata.pwm_dir = limit(outdata.pwm_dir,-pwm_dir_limit,pwm_dir_limit);
  
  
  return pwmout;
  
}

//int Angel_Weight_Cal(int xvalue,int* setarray)
//{  
//  const int seglen = 1000;
//  if(xvalue<=0)
//    return setarray[0];
//  if(xvalue>=5000/seglen*seglen)
//    return setarray[5];
//  int8 segment=xvalue/seglen;                    //分段区域
//  int position=xvalue-segment*seglen;      //区域内位置
//  return (setarray[segment]*(seglen-position)+setarray[segment+1]*position)/seglen;
//}
//分区控制以适应不同速度下的转弯力度
//int Speed_Weight_Cal(int xvalue,int* setarray) 
//{  
//  const int seglen = 50 ;
//  if(xvalue<=0)
//    return setarray[0];
//  if(xvalue>=300/seglen*seglen)
//    return setarray[6];
//  int8 segment=xvalue/seglen;                    //分段区域
//  int position=xvalue-segment*seglen;      //区域内位置
//  return (setarray[segment]*(seglen-position)+setarray[segment+1]*position)/seglen;
//}




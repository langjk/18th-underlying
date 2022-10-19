#ifndef SETPARA_H
#define SETPARA_H 1

#include "sys.h"

struct paralist_s
{
  int* para;
  char label[13];
  unsigned short precision;
};
//摄像头配置
struct camcfg_s
{
  short int wl;
  short int wr;
  short int wf;
  short int show_mode;
  short int debug_mode;
  short int forward_near;
  short int forward_far;
  short int d_angle;
  short int setbright;
  short int focus;
  short int edge_select;
  short int temp[14]; //(32-2-2)/2
};

struct camcfg_para_s
{
  int wl;
  int wr;
  int wf;
  int show_mode;
  int debug_mode;
  int forward_near;
  int forward_far;
  int d_angle;
  int setbright;
  int focus;
  int edge_select;
  int temp[14]; //(32-2-2)/2
};


struct setpara_s
{
  int CarSelect;
  int SetTime;
  int SetSpeed;
  
  int BalAngle;
  int AccAngle;
  int AccTime;
  int AngelKacc;
  int GxFilter;
  int GxBias;
  int BalKp;
  int BalKd;
  
  int DirKp;
  int DirKd;
  int GzKd;
  
  int SpeedKp;
  int SpeedKi;
  int iSpeedAngle;
  int AngleMax;
  int AngleMin;
  int SpeedPeriod;
  
  int TestLR;
  int TestPWM;
  int TestShakePeriod;
  
 // struct camcfg_para_s camcfg_para;
  int cam0angle;
  int ang_array[6];
  int spd_dirkp_array[7];
  int EdgeSelect;
  int EdgeTime;
  
  
  int StopKp;
  int StopKd;
  int KMotor;
  int DeadZoneL;
  int DeadZoneR;
  int MaxPWM;
  int GameTime;
  int AyBias;
  int AzBias;
};

extern struct setpara_s setpara;
//extern struct setpara_s setpara_temp1;
extern struct paralist_s paralist[100];
extern struct camcfg_s camcfg;

void TSUI_Setpara(struct setpara_s*);    //可调参数赋值
void TSUI_SendCamParam(void);

#endif /* SETPARA_H */


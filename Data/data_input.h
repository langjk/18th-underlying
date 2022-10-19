#ifndef _DATA_INPUT_H_
#define _DATA_INPUT_H_
//#include "common.h"
#include  "sys.h"

typedef struct rawdata_STRUCT
{
  int LSpeed;
  int RSpeed;
  short gyr[3];
  float acc[3];
}rawdata_STRUCT;

//struct caminfo_s
//{
//  int16 dir;
//  int16 ddir;
//  int16 zebra_count;
//  int16 left_out_count;
//  int16 right_out_count;  
//  int16 temp[6];//(16-2-2)/2
//};

typedef struct indata_STRUCT
{
  int Speed;
  int rawavespeed;
  int rawcalspeed;
  int LSpeed;
  int RSpeed;
  int LSum;
  int RSum;
  int gx;
  int gy;
  int gz;
  int ax;
  int ay;
  int az;
  int angle;
  uint16 battvolt;
  //struct caminfo_s caminfo;
  int cam_valid_count;
  int cam_fps;
}indata_STRUCT;

void Data_Input(void);
//void Get_Speed();
//void Control_Speed();
void Get_BattVolt(void);
//void SC12CAM_StartCallback();
//void SC12CAM_CompleteCallback();

#endif

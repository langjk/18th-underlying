//#include "common.h"
#include "setpara.h"
//#include "CarStatus.h"
struct setpara_s setpara;
struct camcfg_s camcfg;
struct paralist_s paralist[100]=      //可调参数的调节精度
{
  {&setpara.CarSelect,"CarSelect",1},
  {&setpara.SetTime,"SetTime",5},
  {&setpara.SetSpeed,"SetSpeed",10},
  
  {&setpara.BalAngle,"BalAngle",100},  
  {&setpara.AccAngle,"AccAngle",100},  
  {&setpara.AccTime,"AccTime",500},  
  {&setpara.AngelKacc,"AngelKacc",1},  
  {&setpara.GxFilter,"GxFilter",1},  
  {&setpara.BalKp,"BalKp",1},
  {&setpara.BalKd,"BalKd",1},
  
  {&setpara.DirKp,"DirKp",1},
  {&setpara.DirKd,"DirKd",1},
  {&setpara.GzKd,"GzKd",1},
  
  {&setpara.SpeedKp,"SpeedKp",1}, 
  {&setpara.SpeedKi,"SpeedKi",1}, 
  {&setpara.iSpeedAngle,"iSpeedAngle",100},
  {&setpara.AngleMax,"AngleMax",100},
  {&setpara.AngleMin,"AngleMin",100},
  {&setpara.SpeedPeriod,"SpeedPeriod",1}, 
  
  {&setpara.TestLR,"TestLR",1},
  {&setpara.TestPWM,"TestPWM",100},
  {&setpara.TestShakePeriod,"ShakePeriod",10},
  
//  {&setpara.camcfg_para.debug_mode,"CamDebug",1},
//  {&setpara.camcfg_para.show_mode,"CamShow",1},
//  {&setpara.camcfg_para.setbright,"CamBright",1},
//  {&setpara.camcfg_para.wf,"CamWF",1},
//  {&setpara.camcfg_para.wl,"CamWL",1},
//  {&setpara.camcfg_para.wr,"CamWR",1},
//  {&setpara.camcfg_para.forward_near,"FwardNear",1},
//  {&setpara.camcfg_para.forward_far,"FwardFar",1},
//  {&setpara.camcfg_para.d_angle,"Cam_d_angle",10},
  
//  {&setpara.camcfg_para.focus,"CamFocus",1},
  {&setpara.cam0angle,"Cam0Angle",100},
//  {&setpara.camcfg_para.edge_select,"EdgeSelect",1},
  {&setpara.EdgeSelect,"EdgeInit",1},
  {&setpara.EdgeTime,"EdgeTime",5},
  {&setpara.GxBias,"GxBias",1},
  {&setpara.ang_array[5],"AngCal50",1},
  
  {&setpara.spd_dirkp_array[0],"SpdDirCal0",1},
  {&setpara.spd_dirkp_array[1],"SpdDirCal50",1},
  {&setpara.spd_dirkp_array[2],"SpdDirCal100",1},
  {&setpara.spd_dirkp_array[3],"SpdDirCal150",1},
  {&setpara.spd_dirkp_array[4],"SpdDirCal200",1},
  {&setpara.spd_dirkp_array[5],"SpdDirCal250",1},
  {&setpara.spd_dirkp_array[6],"SpdDirCal300",1},
  

  
  {&setpara.KMotor,"KMotor",1},    
  {&setpara.DeadZoneL,"DeadZoneL",10},
  {&setpara.DeadZoneR,"DeadZoneR",10},
  {&setpara.GameTime,"GameTime",5},
  {&setpara.AyBias,"AyBias",10},
  {&setpara.AzBias,"AzBias",10},
  {0}
};

//可初始化为以下值
 struct setpara_s setpara_temp1={

  .CarSelect = 1,
  .SetTime = 30, 
  .SetSpeed = 200, 
  .BalAngle = 500,
  .AccAngle = 4000,
  .AccTime = 3000,
  .AngelKacc =1,
  .GxFilter = 5,
  
  .BalKp = 40,
  .BalKd = 70,
  
  
  
  
  .DirKp = 70,  
  .DirKd = 8,
  .GzKd = 10,
  
  .SpeedKp = 25,
  .SpeedKi = 30,  
  .iSpeedAngle = 2000, 
  .AngleMax = 2600,
  .AngleMin = 600,
  .SpeedPeriod = 20,
  
  .TestLR = 0,
  .TestPWM = 0,
  .TestShakePeriod =0,

  
  
  

  .cam0angle = 2800,
  
//  .camcfg_para.edge_select = 1,
  .ang_array[0] = 100,
  .ang_array[1] = 0,
  .ang_array[2] = -180,
  .ang_array[3] = -330,
  .ang_array[4] = -490,
  .ang_array[5] = -720,
  .spd_dirkp_array[0] = 7,
  .spd_dirkp_array[1] = 13,
  .spd_dirkp_array[2] = 15,
  .spd_dirkp_array[3] = 15,  
  .spd_dirkp_array[4] = 15, 
  .spd_dirkp_array[5] = 18,
  .spd_dirkp_array[6] = 23,

  .KMotor = 7, 
  .DeadZoneL = 480,
  .DeadZoneR = 480,
};


void TSUI_Setpara(struct setpara_s* setpara_temp)    //可调参数赋值
{
  memcpy(&setpara,setpara_temp,sizeof(struct setpara_s));
}
//向摄像头处理板发送配置信息
//void TSUI_SendCamParam()
//{
//  //延时
////  static u32 last_ms=0;
////  int new_ms = Car_GetTimeMs();
////  if(new_ms-last_ms<100)
////    return;
////  last_ms = new_ms;
////  PTD0_O=0;
////  int8 camcfg_buf[32] = {0x55,0xAA};
////  for(int i=0;i<sizeof(struct camcfg_s)/sizeof(int16);i++)
////    *(int16*)((uint32)(&camcfg)+i*sizeof(int16)) = *(int*)((uint32)(&setpara.camcfg_para)+i*sizeof(int));
////  memcpy(&camcfg_buf[2],&camcfg,28);
////  camcfg_buf[31]=0;
////  for(int i=2;i<31;i++)camcfg_buf[31]+=camcfg_buf[i];
////  LPLD_UART_PutCharArr(UART2,camcfg_buf,32);
////  PTD0_O=1;

//}


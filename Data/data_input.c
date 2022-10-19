//#include "sys.h"
#include "data_input.h"
//#include "data_output.h"
//#include "setpara.h"
//#include "CarStatus.h"
//#include "CarConfig.h"
//#include "MPU6050_ForDMP.h"
//#include "math.h"
//#include "Task_RTDBG.h"
#define limit(value,min,max) (value > (max) ? (max) : ( value < (min) ? (min) : (value) ))

 STATUS_CAR_STRUCT mycar;               //小车总状态
indata_STRUCT indata;           //输入变量
extern outdata_STRUCT outdata;
rawdata_STRUCT rawdata;
char uart2_buff[64];
void Data_Input(void);
//void Get_Speed(void);

const float gx_to_delta_angle = TIM4_MS*2.0/32768; //TimePeriod(ms)*GyrFullScale(°/ms)/DataFullScale
//Z向上
int getAngleFilter(int gx,int ay,int az,int k)   //互补滤波获得角度
{
  float f_k = k*0.0001;
  static float angle_last=0;
  float angle_acc = 57.29577951 * atan2(ay,az);
  angle_last = (1-f_k)*(angle_last+gx_to_delta_angle*gx) + f_k * angle_acc;
  return (int)(-100*angle_last);
}
//Z向下
//int getAngleFilter(int gx,int ay,int az,int k)
//{
//  float f_k = k*0.0001;
//  static float angle_last=0;
//  float angle_acc = 57.29577951 * atan2(ay,-az);
//  angle_last = (1-f_k)*(angle_last-gx_to_delta_angle*gx) + f_k * angle_acc;
//  return (int)(100*angle_last);
//}
double testgx=0.0,testay=0.0,testaz=0.0;
//两车有不同偏移校正
//static const int gyr_bias_Carone[3]= {-58,9,12};
//static const int acc_bias_Carone[3]= {500,-100,-1700};
//static const int gyr_bias_Cartwo[3]= {-46,7,-16};
//static const int acc_bias_Cartwo[3]= {700,-300,-2100};

void Data_Input()
{                
	
	//  Mpu_Dmp_Get_Data(&rawdata.acc[0],&rawdata.acc[1],&rawdata.acc[2]);   //欧拉角的数据
	//	MPU_Get_Gyroscope(&rawdata.gyr[0],&rawdata.gyr[1],&rawdata.gyr[2]);	 //陀螺仪数据
	  
 // MPU6050_ReadData(rawdata.gyr,rawdata.acc);
//  static int32 gx_h[10]={0};
//	int i;
//  for(i=9;i>0;i--)gx_h[i]=gx_h[i-1];
//  static int32 gz_h[10]={0};
//  for(int i=9;i>0;i--)gz_h[i]=gz_h[i-1];
  //偏移校正
//  if (setpara.CarSelect ==1)
//  {
//    gx_h[0] = rawdata.gyr[0] - gyr_bias_Carone[0]-setpara.GxBias;
//    gz_h[0] = rawdata.gyr[2] - gyr_bias_Carone[2];
//    indata.ay = rawdata.acc[1] - acc_bias_Carone[1]-setpara.AyBias;//testay;
//    indata.az = rawdata.acc[2] - acc_bias_Carone[2]-setpara.AzBias;//testaz;//
//  }
//  else if (setpara.CarSelect ==2)
//  {
//    gx_h[0] = rawdata.gyr[0] - gyr_bias_Cartwo[0]-setpara.GxBias;
//    gz_h[0] = rawdata.gyr[2] - gyr_bias_Cartwo[2];
//    indata.ay = rawdata.acc[1] - acc_bias_Cartwo[1]-setpara.AyBias;//testay;
//    indata.az = rawdata.acc[2] - acc_bias_Cartwo[2]-setpara.AzBias;//testaz;//
//  }
//  
  //  indata.gx = (gx_h[0]+gx_h[1]+gx_h[2]+gx_h[3])/4;//10*testgx;
  //角度滤波 提高平衡抗震能力
//			setpara.GxFilter = limit(setpara.GxFilter,1,10);
//			int tempindatagx = 0;
//			for(int i=0;i<setpara.GxFilter;i++)
//			tempindatagx += gx_h[i];
//			indata.gx=tempindatagx/setpara.GxFilter;

//			indata.gz = (gz_h[0]+gz_h[1]+gz_h[2]+gz_h[3]+gz_h[4]+gz_h[5]+gz_h[6]+gz_h[7]+gz_h[8]+gz_h[9])/10;//10*testgx;

//			//  indata.gz = rawdata.gyr[2] - gyr_bias[2];//10*testgx;

//			if (mycar.status == 0 )
//			indata.angle = getAngleFilter(indata.gx,indata.ay,indata.az,50);
//			else
//			indata.angle = getAngleFilter(indata.gx,indata.ay,indata.az,setpara.AngelKacc);
  
  //摄像头校正角度
//  setpara.camcfg_para.d_angle = indata.angle - setpara.cam0angle;
//  static u32 last_cam_valid_count[6] = {0};
//  if(mycar.RUNTIME%200==0)
//  {
//    for(int i=5;i>0;i--)
//      last_cam_valid_count[i] = last_cam_valid_count[i-1];
//    last_cam_valid_count[0] = indata.cam_valid_count;
//    indata.cam_fps = last_cam_valid_count[0]-last_cam_valid_count[5];
//  }
  
  //一定时间后更换选边
//  setpara.EdgeSelect = limit(setpara.EdgeSelect,0,1);
//  if(mycar.RUNTIME > setpara.EdgeTime*100)
//  {
//    setpara.camcfg_para.edge_select = 1 - setpara.EdgeSelect;
//  }
//  else
//  {
//    setpara.camcfg_para.edge_select = setpara.EdgeSelect;
//  }
  //  if(mycar.status==2)Car_IncControlCycle();
  //  saveRAM(1,indata.caminfo.left_out_count);
  //  saveRAM(2,indata.caminfo.right_out_count);
}

void Get_BattVolt()
{
//  static float fBattVolt = 7.8;
//  if(setpara.CarSelect==1)
//    fBattVolt = 0.98*fBattVolt + 0.02*0.004139*LPLD_ADC_Get(ADC1, AD17);
//  else if(setpara.CarSelect==2)
//    fBattVolt = 0.98*fBattVolt + 0.02*0.004284*LPLD_ADC_Get(ADC1, AD17);
//  indata.battvolt = (int)(100*fBattVolt);
}

//void Get_Speed()
//{
////  rawdata.LSpeed = (int16)LPLD_FTM_GetCounter(FTM2);
////  rawdata.RSpeed = -(int16)LPLD_FTM_GetCounter(FTM1);
////  LPLD_FTM_ClearCounter(FTM1);
////  LPLD_FTM_ClearCounter(FTM2);
//}

int speed_cal()
{
  static int error,pwmout,ierrorout;
  error = indata.Speed - setpara.SetSpeed;
  ierrorout += setpara.SpeedKi*error;
  if(mycar.RUNTIME<1500)
    ierrorout = 0;
  else
    ierrorout = limit(ierrorout,
                      -setpara.BalKp*setpara.iSpeedAngle,
                      setpara.BalKp*setpara.iSpeedAngle);//此处电机PWM稳态误差可忽略不计（通常影响不超过1°）
  //SpeedKp:单位误差(m/s)所提供的角度(°)
  pwmout = setpara.SpeedKp*setpara.BalKp*error + ierrorout;
  outdata.pwm_speed_p = setpara.SpeedKp*setpara.BalKp*error;
  outdata.pwm_speed_i = ierrorout;
  //对车运行过程中角度进行限制
  if(mycar.RUNTIME<setpara.AccTime&&setpara.AccTime>0)
  {
    int temp_angle_max = ((setpara.AccTime-mycar.RUNTIME)*setpara.AccAngle
                          + mycar.RUNTIME*setpara.AngleMax)/setpara.AccTime;
    pwmout = limit(pwmout,
                   -setpara.BalKp*(temp_angle_max-setpara.BalAngle),
                   -setpara.BalKp*(setpara.AngleMin-setpara.BalAngle));
  }
  else
    pwmout = limit(pwmout,
                   -setpara.BalKp*(setpara.AngleMax-setpara.BalAngle),
                   -setpara.BalKp*(setpara.AngleMin-setpara.BalAngle));
  return pwmout;
}

void Control_Speed()
{
  
  //原始速度与累加器
  indata.LSpeed = rawdata.LSpeed;
  indata.RSpeed = rawdata.RSpeed;
  indata.LSum+=rawdata.LSpeed;
  indata.RSum+=rawdata.RSpeed;
  //速度滤波
  indata.rawavespeed = (rawdata.LSpeed+rawdata.RSpeed)/2;
  if(indata.rawavespeed > indata.rawcalspeed + 2)
    indata.rawcalspeed += 2;
  else if(indata.rawavespeed < indata.rawcalspeed - 2)
    indata.rawcalspeed -= 2;
  else
    indata.rawcalspeed = indata.rawavespeed;
  //平均速度
  setpara.SpeedPeriod = limit(setpara.SpeedPeriod,1,50);
  //static int rawcalspeed_history[50], SumSpeed;
	
//  int i = 0;
	// int rawcalspeed_history[50], SumSpeed;
//   int i = 0;
//	
//  i = (i + 1) % setpara.SpeedPeriod;
 // rawcalspeed_history[i] = indata.rawcalspeed;
//   int pwm_old,pwm_new;
//  if(i==0)      //速度控制
//  {
//    SumSpeed = 0;
//		u8 j;
//    for (j = 0; j < setpara.SpeedPeriod; j++)
//      SumSpeed += rawcalspeed_history[j];
//   // indata.Speed = 9*SumSpeed/setpara.SpeedPeriod/SPD_MS;
//    pwm_old = pwm_new;
//    pwm_new = speed_cal();
//  }
  //均匀输出
//  outdata.pwm_speed = ((setpara.SpeedPeriod - i) * pwm_old + i * pwm_new)/setpara.SpeedPeriod;
//  if(mycar.status==2)
//  {
//    if(mycar.RUNTIME>20000)
     // Car_IncControlCycle();
    //速度控制组
//    saveRAM(1,indata.angle);
//    saveRAM(2,indata.gx);
//    saveRAM(3,indata.ay);
//    saveRAM(4,indata.az);
//    saveRAM(5,outdata.pwm_bal);
//    saveRAM(6,indata.Speed);
//    saveRAM(7,indata.rawavespeed);
//    saveRAM(8,outdata.pwm_speed_p);
//    saveRAM(9,outdata.pwm_speed_i);
//    saveRAM(10,outdata.pwm_speed);
    //    //转向分析组
    //    saveRAM(1,indata.angle);
    //    saveRAM(2,indata.Speed);
    //    saveRAM(3,indata.rawavespeed);
    //    saveRAM(4,indata.caminfo.dir);
    //    saveRAM(5,indata.caminfo.ddir);
    //    saveRAM(6,indata.gz);
    //    saveRAM(7,outdata.pwm_dir);
    //    saveRAM(8,outdata.pwm_dir_cal);
    
//  }
}

//int is_dataframe_valid(char* dat, int count)
//{
//  if(dat[0]!=0x55||dat[1]!=0xAA)
//    return -1;  //帧头错误
//  u8 datsum=0;
//	int i;
//  for( i=2;i<count-1;i++)
//    datsum+=dat[i];
//  if(datsum!=dat[count-1])
//    return -2;  //校验和错误
//  return 0;     //数据有效
//}

void SC12CAM_StartCallback()
{
  //Reload DMA Address
 // LPLD_DMA_LoadDstAddr(DMA_CH10, uart2_buff);
  //  //Enable DMA
  //  LPLD_DMA_EnableReq(DMA_CH10);
}

//void SC12CAM_CompleteCallback()
//{
//  //Check if data is valid
//  if(is_dataframe_valid(uart2_buff,16)==0)
//  {
//    //Parse Data
//   // memcpy(&indata.caminfo,&uart2_buff[2],12);
//    indata.cam_valid_count++;
//  }


//}
#include "TJSC_Display.h"
//#include "OLED.h"


//#include "CarStatus.h"

extern indata_STRUCT indata;
extern outdata_STRUCT outdata;
///extern STATUS_CAR_STRUCT mycar;               //С����״̬ 

static void TSUI_DisplayUpperPage(s8);
static void TSUI_DisplayPara(void);
static void TSUI_DisplayFullPage(s8);

#define TSUI_PRINTF(line,xpos,...)

void TSUI_Display()
{
  //�����ͱ��� ������Ӧ�ü���  �������Ų�����
//  if(indata.battvolt<720)  //����ص����ܵ�ʱ����Ļ������˸ ������ʾ
//  {
//    //LCD_CLS();
//		OLED_Clear();
//  }            
  if(tsui.showPage>=0)
  {
    TSUI_DisplayUpperPage(tsui.showPage);//��ҳ��ʾ ���� 
    TSUI_DisplayPara();                  //��ʾ���� 
  }
  else
  {
    TSUI_DisplayFullPage(tsui.showPage);
  }
}

void TSUI_Printf(u8 y, u8 x, const char * fmt, ...)
{
  char printf_str[21];
  va_list ap;
  va_start(ap,fmt);
  vsnprintf(printf_str,21,fmt,ap);
  LCD_P6x8Str(x,y,(u8*)printf_str);
	//OLED_ShowString(x,y,(u8*)printf_str,12);
	//OLED_ShowChar(x,y,(u8*)printf_str);
}

void TSUI_PrintfW(u8 y, u8 x, const char * fmt, ...)
{
  char printf_str[21];
  va_list ap;
  va_start(ap,fmt);
  vsnprintf(printf_str,21,fmt,ap);
  LCD_P6x8StrW(x,y,(u8*)printf_str);
	//OLED_ShowString(x,y,(u8*)printf_str,12);
	//OLED_ShowChar(x,y,(u8*)printf_str);
}

void TSUI_DisplayUpperPage(s8 page)
{
  //��ҳǰ���ǰ5����ʾ��
	int i;
  static int lastpage;
  if(lastpage!=page)
  {
    for( i=0;i<5;OLED_ClearLine(i++));   //������ҳ��Ӧ���ǰҳ ��ǰ5����ʾ����     
    lastpage=page;
  }
  //��ҳ��ʾ����
  switch(page)
  {		
   case 0: 	 
  	TSUI_Printf(0,0,"State:%1d,T:%4d.%1d",mycar.status,T/ 1000, (T %1000)/100);
    TSUI_Printf(1,0,"RT:%3d.%1d",mycar.RUNTIME / 1000, (mycar.RUNTIME %1000) / 100);
    TSUI_Printf(2,0," ");
    TSUI_Printf(3,0," ");
    TSUI_Printf(4,0,"Batt:%2d.%02dV",indata.battvolt/100,indata.battvolt%100);
    break;
  case 1:
    TSUI_Printf(0,0,"Ang:%6d,S:%6d",indata.angle,setpara.BalAngle);
    TSUI_Printf(1,0,"Gx:%6d,Gz:%6d",indata.gx,indata.gz); 
    TSUI_Printf(2,0,"Ay:%6d,Az:%6d",indata.ay,indata.az); 
    TSUI_Printf(3,0," ");
    TSUI_Printf(4,0," ");
    break;
  case 2:  
    TSUI_Printf(0,0,"Speed L:%4d,R:%4d",indata.LSpeed,indata.RSpeed);
    TSUI_Printf(1,0,"PWM L:%5d,R:%5d",outdata.pwm_left,outdata.pwm_right);
    TSUI_Printf(2,0,"Speed: %6d",indata.Speed);
    TSUI_Printf(3,0,"SumL:%6d,R:%6d",indata.LSum,indata.RSum);
    TSUI_Printf(4,0," ");
    break;
  case 3:  
   // TSUI_Printf(0,0,"Dir:%5d,dDir:%5d",indata.caminfo.dir,indata.caminfo.ddir);
//    TSUI_Printf(1,0,"Zebra:%5d",indata.caminfo.zebra_count);
//    TSUI_Printf(2,0,"LO:%3d,RO:%3d",indata.caminfo.left_out_count,indata.caminfo.right_out_count);
  // TSUI_Printf(3,0,"DAngle:%6d",setpara.camcfg_para.d_angle);
    TSUI_Printf(4,0,"Count:%6d,FPS:%3d",indata.cam_valid_count,indata.cam_fps);
    break;
	 
  default:
    break;
  }
}

void TSUI_DisplayPara()
{
  int temp_ParaSelect = tsui.paraSelect;      //����Ǳ�ڵ��жϸ��ţ������ȴ洢��������Ա���Σ��
  
  //��ʾ��5��
  if(temp_ParaSelect>0) //�ж��Ƿ�Ϊ�� 
  {
    TSUI_Printf(5,0,"%02d.%-13s",temp_ParaSelect-1,paralist[temp_ParaSelect-1].label);
    TSUI_Printf(5,96,"%5d",*paralist[temp_ParaSelect-1].para);
  }
  else
  {
    OLED_ClearLine(5);//�����һ����ʾ 
  }
  //��ʾ��6�У����ڲ���
  if(tsui.paraStatus)
  {
    TSUI_Printf(6,0,"%02d.%-13s",temp_ParaSelect,paralist[temp_ParaSelect].label);
    TSUI_PrintfW(6,96,"%5d",*paralist[temp_ParaSelect].para);
  }
  else
  {
    TSUI_PrintfW(6,0,"%02d.%-13s",temp_ParaSelect,paralist[temp_ParaSelect].label);
    TSUI_Printf(6,96,"%5d",*paralist[temp_ParaSelect].para);
  }
  //��ʾ��7��
  if(temp_ParaSelect < tsui.paraMax)
  {
    TSUI_Printf(7,0,"%02d.%-13s",temp_ParaSelect+1,paralist[temp_ParaSelect+1].label);
    TSUI_Printf(7,96,"%5d",*paralist[temp_ParaSelect+1].para);
  }
  else
  {
    OLED_ClearLine(7);//��������һ����ʾ 
  }
}

void TSUI_DisplayFullPage(s8 page)
{
  switch(page)
  {
  case -1:
    break;
  case -2:
    break;
  case -3:
    break;
  default:
    break; 
  }
}


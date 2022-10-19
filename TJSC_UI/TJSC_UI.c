//#include "common.h"
#include "setpara.h"
#include "TJSC_UI.h"
//#include "TSUI_HardwareInit.h"
//#include "CarStatus.h"
//#include "OLED.h"
//#include "HW_FLASH.h"
//#include "Task_RTDBG.h"

#define FLASH_SAVE_SECTOR 255

extern TSUI_ButtonEventEnum buttonEvent;
 extern struct setpara_s setpara_temp1;
TSUI_TypeDef tsui;

void TSUI_HardwareInit(void);
static u16 tsui_GetParaMax(void);

void TSUI_FlashSave()
{
  uint32 data_to_write[100];
	u8 i;
	//STMFLASH_Write(FLASH_SAVE_ADDR,(u16)&paralist[0].para,sizeof()
  for( i=0;i<100;i++)
    data_to_write[i] = *paralist[i].para;
	STMFLASH_Write(FLASH_SAVE_ADDR,(u32 *)data_to_write,sizeof(data_to_write));
  //LPLD_Flash_SectorErase(FLASH_SAVE_SECTOR*0x800);
  //LPLD_Flash_ByteProgram(FLASH_SAVE_SECTOR*0x800,data_to_write,(tsui.paraMax+1)*4);
  
}

void TSUI_FlashRead()
{
  //定义参数读取
	int i;
  for( i=0;i<tsui.paraMax+1;i++)
  {
   // *paralist[i].para = *(int*)(FLASH_SAVE_SECTOR*0x800+i*4);
		STMFLASH_Read(FLASH_SAVE_ADDR+i*0x02,(u32 *)paralist[i].para,2);
		if(*paralist[i].para>32768)   //小于0位负数  应该用65535 减去这个数
			*paralist[i].para=*paralist[i].para-0xffff-1;  
  }
}

void TSUI_Init()
{
  TSUI_HardwareInit();                    //oled 软件spi初始化
  
  tsui.paraMax = tsui_GetParaMax();     //获得参数列表最大序号
//  TSUI_Setpara(&setpara_temp1);         //可调参数赋值
  TSUI_FlashRead();                     //读取存贮flash的参数

}

//旋转编码器响应
void TSUI_EncoderEvent()
{
//  if(!TSUI_PT_CCW_I)  //如果逆时针引脚是高电平，则是正转
//  {
////    if(tsui.paraStatus)
////      *paralist[tsui.paraSelect].para += paralist[tsui.paraSelect].precision;
////    else
////    {
////      if(tsui.paraSelect < tsui.paraMax )
////        tsui.paraSelect ++;
////      else
////        tsui.paraSelect = 0;
////    }
//  }
//  else
//  {
//    if(tsui.paraStatus)
//      *paralist[tsui.paraSelect].para -= paralist[tsui.paraSelect].precision;
//    else
//    {
//      if(tsui.paraSelect > 0)
//        tsui.paraSelect --;
//      else
//        tsui.paraSelect = tsui.paraMax;
//    }
//  }
}

void TSUI_ButtonEvent()
{
  //记录按键时间
  u32 pushtime=T;
  
  //旋钮或拨轮按下操作后屏幕初始化，以修复花屏
  if(buttonEvent==PRESS||buttonEvent==OK)
      OLED_Init();  //重新初始化 oled  但不清屏 应该是原来显示的内容 达到修复花屏的目的
  switch(buttonEvent)
  {
  case PRESS:
    while(!TSUI_PT_PRESS_I);    
    if(T-pushtime<300)          //短按
    {
      tsui.paraStatus ^= 1;    //状态取反，参数选择和参数改变切换
    }
    else                      //长按 表示发车
    {
      TSUI_FlashSave();       //发车前应当存贮调整完的参数，避免行车过程中参数意外改变
//      delay_ms(1000);
      mycar.status=1;         //小车状态 置1
//      setpara.camcfg_para.show_mode=0;
      //setpara.GameTime = 600;
    }
    break;
  case OK: 
    while(!TSUI_PT_OK_I);
    if(T-pushtime<800)
    {
      
    }
    else
    {
      TSUI_Setpara(&setpara_temp1);       //初始化所有参数
    }
    break;
  case UP:
    while(!TSUI_PT_UP_I);
    if(T-pushtime<300)
    {
      if(tsui.paraStatus)   //参数改变状态
      {
        if(tsui.paraSelect > 0)
          tsui.paraSelect --;
        else
          tsui.paraSelect = tsui.paraMax;
      }
      else                 //参数选择状态
      {
        if(tsui.showPage > __TSUI_ShowPageMin)
          tsui.showPage --;
        else
          tsui.showPage = __TSUI_ShowPageMax;
      }
    }
    else
    {
      __disable_irq();// 关闭总中断;			
      //sendRAM();
     __enable_irq(); // 开启总中断
			
    }
    break;  
  case DOWN:
    while(!TSUI_PT_DOWN_I);
    if(T-pushtime<300)
    {
      if(tsui.paraStatus)   //参数改变状态
      {
        if(tsui.paraSelect < tsui.paraMax)
          tsui.paraSelect ++;
        else
          tsui.paraSelect = 0;
      }
      else                 //参数选择状态
      {
        if(tsui.showPage < __TSUI_ShowPageMax)
          tsui.showPage ++;
        else
          tsui.showPage = __TSUI_ShowPageMin;
      }
    }
    else
    {
      //TSUI_FlashSave();
     // delay_ms(1000);
			//delay_ms(1000);
    //  mycar.status=1;
     // setpara.camcfg_para.show_mode=0;
      setpara.GameTime = 0;
    }
    break;
	case CW:                //如果是顺时针旋转         
      while(!TSUI_PT_CW_I);		
			if(tsui.paraStatus)
				*paralist[tsui.paraSelect].para += paralist[tsui.paraSelect].precision;
			else
			{
				if(tsui.paraSelect < tsui.paraMax )
					tsui.paraSelect ++;
				else
					tsui.paraSelect = 0;
			} 
   break;
  case CCW:           //如果是逆时针旋转
		while(!TSUI_PT_CCW_I);
    if(tsui.paraStatus)  //参数改变状态
      *paralist[tsui.paraSelect].para -= paralist[tsui.paraSelect].precision;
    else
    {
      if(tsui.paraSelect > 0) 
        tsui.paraSelect --;
      else
        tsui.paraSelect = tsui.paraMax;
    }     		
   break;	
  default:
    break;
  }
  
  
  buttonEvent = NONE;//清除按键状态
  
}
/*****将发生的button事件传入***/
void TSUI_SetButtonEvent(TSUI_ButtonEventEnum inputEvent)
{
// static uint32 last_T=0;
//  if(T<last_T+200)return;
//   last_T = T;
  buttonEvent = inputEvent;
}

static u16 tsui_GetParaMax()
{
  u16 i = 0;
  while(paralist[i].precision > 0)i++;//参数大于等于0
  return (i - 1);
}


//TSUI的硬件初始化，包括旋转编码器、拨轮开关的6个IO中断，以及OLED屏幕初始化。
void TSUI_HardwareInit()
{
	OLED_Init();    //OLED初始化                  SCL-PB8 SDA-PB9 
  //tsui.paraMax = tsui_GetParaMax();     //获得参数列表最大序号

}


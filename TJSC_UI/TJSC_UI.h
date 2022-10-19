#ifndef TJSC_UI_H
#define TJSC_UI_H 1

//#include "setpara.h"
#include "TJSC_Display.h"
#include "sys.h"

#define TSUI_PT_OK_I      KEY_PUSH
#define TSUI_PT_UP_I      KEY_UP
#define TSUI_PT_DOWN_I    KEY_DOWN
#define TSUI_PT_PRESS_I   SW_PRESS
#define TSUI_PT_CW_I      SW_CHA
#define TSUI_PT_CCW_I     SW_CHB


#define FLASH_SAVE_ADDR  0X800FC00 //这事c8t6的第63页



typedef struct
{
  unsigned char paraStatus;
  unsigned short paraSelect;
  unsigned short paraMax;
  signed char showPage;
}TSUI_TypeDef;

typedef enum
{
  NONE=0,
  PRESS,  //旋转编码器按下
  UP,
  OK,
  DOWN,
	CW,
	CCW
}TSUI_ButtonEventEnum;

typedef enum
{
  OLED_NORMAL = 0,
  OLED_REVERT
}OLED_DirType;

#define __TSUI_ShowPageMax 3
#define __TSUI_ShowPageMin 0

void TSUI_Init(void);
void TSUI_EncoderEvent(void);
void TSUI_ButtonEvent(void);
void TSUI_SetButtonEvent(TSUI_ButtonEventEnum inputEvent);
void TSUI_FlashRead(void);

extern TSUI_TypeDef tsui;


#endif /* TSUI_H */


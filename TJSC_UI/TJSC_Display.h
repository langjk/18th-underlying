#ifndef TJSC_DISPLAY_H
#define TJSC_DISPLAY_H 1

//#include "setpara.h"
#include "sys.h"
#include <stdio.h>
#include <stdarg.h>

//typedef struct
//{
//  unsigned char paraStatus;
//  unsigned short paraSelect;
//  unsigned short paraMax;
//  signed char showPage;
//}TSUI_TypeDef;

////typedef enum
////{
////  NONE=0,
////  PRESS,
////  UP,
////  OK,
////  DOWN
////}TSUI_ButtonEventEnum;

//#define __TSUI_ShowPageMax 3
//#define __TSUI_ShowPageMin 0

//void TSUI_Init();
//void TSUI_EncoderEvent();
//void TSUI_ButtonEvent();
//void TSUI_SetButtonEvent(TSUI_ButtonEventEnum inputEvent);
//void TSUI_FlashRead();

//extern TSUI_TypeDef tsui;
void TSUI_Display(void);

#endif /* TSUI_H */

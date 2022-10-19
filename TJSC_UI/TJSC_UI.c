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
  //���������ȡ
	int i;
  for( i=0;i<tsui.paraMax+1;i++)
  {
   // *paralist[i].para = *(int*)(FLASH_SAVE_SECTOR*0x800+i*4);
		STMFLASH_Read(FLASH_SAVE_ADDR+i*0x02,(u32 *)paralist[i].para,2);
		if(*paralist[i].para>32768)   //С��0λ����  Ӧ����65535 ��ȥ�����
			*paralist[i].para=*paralist[i].para-0xffff-1;  
  }
}

void TSUI_Init()
{
  TSUI_HardwareInit();                    //oled ���spi��ʼ��
  
  tsui.paraMax = tsui_GetParaMax();     //��ò����б�������
//  TSUI_Setpara(&setpara_temp1);         //�ɵ�������ֵ
  TSUI_FlashRead();                     //��ȡ����flash�Ĳ���

}

//��ת��������Ӧ
void TSUI_EncoderEvent()
{
//  if(!TSUI_PT_CCW_I)  //�����ʱ�������Ǹߵ�ƽ��������ת
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
  //��¼����ʱ��
  u32 pushtime=T;
  
  //��ť���ְ��²�������Ļ��ʼ�������޸�����
  if(buttonEvent==PRESS||buttonEvent==OK)
      OLED_Init();  //���³�ʼ�� oled  �������� Ӧ����ԭ����ʾ������ �ﵽ�޸�������Ŀ��
  switch(buttonEvent)
  {
  case PRESS:
    while(!TSUI_PT_PRESS_I);    
    if(T-pushtime<300)          //�̰�
    {
      tsui.paraStatus ^= 1;    //״̬ȡ��������ѡ��Ͳ����ı��л�
    }
    else                      //���� ��ʾ����
    {
      TSUI_FlashSave();       //����ǰӦ������������Ĳ����������г������в�������ı�
//      delay_ms(1000);
      mycar.status=1;         //С��״̬ ��1
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
      TSUI_Setpara(&setpara_temp1);       //��ʼ�����в���
    }
    break;
  case UP:
    while(!TSUI_PT_UP_I);
    if(T-pushtime<300)
    {
      if(tsui.paraStatus)   //�����ı�״̬
      {
        if(tsui.paraSelect > 0)
          tsui.paraSelect --;
        else
          tsui.paraSelect = tsui.paraMax;
      }
      else                 //����ѡ��״̬
      {
        if(tsui.showPage > __TSUI_ShowPageMin)
          tsui.showPage --;
        else
          tsui.showPage = __TSUI_ShowPageMax;
      }
    }
    else
    {
      __disable_irq();// �ر����ж�;			
      //sendRAM();
     __enable_irq(); // �������ж�
			
    }
    break;  
  case DOWN:
    while(!TSUI_PT_DOWN_I);
    if(T-pushtime<300)
    {
      if(tsui.paraStatus)   //�����ı�״̬
      {
        if(tsui.paraSelect < tsui.paraMax)
          tsui.paraSelect ++;
        else
          tsui.paraSelect = 0;
      }
      else                 //����ѡ��״̬
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
	case CW:                //�����˳ʱ����ת         
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
  case CCW:           //�������ʱ����ת
		while(!TSUI_PT_CCW_I);
    if(tsui.paraStatus)  //�����ı�״̬
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
  
  
  buttonEvent = NONE;//�������״̬
  
}
/*****��������button�¼�����***/
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
  while(paralist[i].precision > 0)i++;//�������ڵ���0
  return (i - 1);
}


//TSUI��Ӳ����ʼ����������ת�����������ֿ��ص�6��IO�жϣ��Լ�OLED��Ļ��ʼ����
void TSUI_HardwareInit()
{
	OLED_Init();    //OLED��ʼ��                  SCL-PB8 SDA-PB9 
  //tsui.paraMax = tsui_GetParaMax();     //��ò����б�������

}


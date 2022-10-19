#ifndef _ccd_c
#define _ccd_c

#include "sys.h"

extern uint16_t ccd_data[128];                   //CCD数据
extern uint16_t ccd_two[128];                   //CCD二值化

/****引脚定义****/
//CCD_AO:PF6
#define CCD_AO_PORT GPIOF
#define CCD_AO_PIN GPIO_Pin_6
#define CCD_AO_CLK RCC_APB2Periph_GPIOF
#define CCD_AO_ADC RCC_APB2Periph_ADC3
#define CCD_AO_ADC_chn  4

//CCD_CLK:PF1
#define CCD_CLK_PORT GPIOF
#define CCD_CLK_PIN GPIO_Pin_1
#define CCD_CLK_CLK RCC_APB2Periph_GPIOF
//CCD_SI:PF3
#define CCD_SI_PORT GPIOF
#define CCD_SI_PIN GPIO_Pin_3
#define CCD_SI_CLK RCC_APB2Periph_GPIOF


#define CCD_CLK(x)     PFout(1)=x
#define CCD_SI(x)      PFout(3)=x

void ccd_init(void);
void ccd_collect(void);
void ccd_change(void);
void ccd_gpio_Init();
u16 ccd_Get_Adc(u8 ch);
void ccd_adc_init();



#endif
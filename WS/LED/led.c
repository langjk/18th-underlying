#include "sys.h"

void Led_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=LED1_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStructure);

#ifdef USE_LED2	
	RCC_APB2PeriphClockCmd(LED2_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=LED2_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(LED2_GPIO_PORT,&GPIO_InitStructure);
#endif
	
#ifdef USE_LED3
	
	RCC_APB2PeriphClockCmd(LED3_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=LED3_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(LED3_GPIO_PORT,&GPIO_InitStructure);
	
#endif
}

void Beep_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=BEEP_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(BEEP_GPIO_PORT,&GPIO_InitStructure);
}



#include "sys.h"

TSUI_ButtonEventEnum buttonEvent;

#define BUFFER_SIZE 1
u16 GPIOA_value;

int Key_Scan()
{

//	 if((GPIOA_value& SW_PRESS_ADDR)!=SW_PRESS_ADDR)
//		   TSUI_SetButtonEvent(PRESS);//拨轮按下
//	 if((GPIOA_value&SW_CCW_CW_ADDE)==SW_CW_ADDR)  //第15位为高
//		   TSUI_SetButtonEvent(CW);//拨轮按下
//	 else if((GPIOA_value& SW_CCW_CW_ADDE)==SW_CCW_ADDR)
//	    TSUI_SetButtonEvent(CCW);//拨轮按下
//	if(buttonEvent)
//	{
	  switch (GPIOA_value&SW_ADDR)
		{
			case  SW_PRESS_ADDR :
				  //if(T)
				  TSUI_SetButtonEvent(PRESS);//拨轮按下
			break;
			case SW_CW_ADDR:
				  TSUI_SetButtonEvent(CW);//拨轮按下
			break;
			case SW_CCW_ADDR:
				  TSUI_SetButtonEvent(CCW);//拨轮按下
			break;	
      default:
       break;							
	  }
//	}
}


void Key_DMA_EXTI_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure; 
  DMA_InitTypeDef DMA_InitStructure;	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//禁用jtag功能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      //开启复用时钟
	
	RCC_APB2PeriphClockCmd(SW_CHA_GPIO_CLK,ENABLE);	
	
		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=SW_CHA_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SW_CHA_GPIO_PORT,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(SW_CHB_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=SW_CHB_PIN;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SW_CHB_GPIO_PORT,&GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(SW_PRESS_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=SW_PRESS_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SW_PRESS_GPIO_PORT,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(KEY_UP_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=KEY_UP_PIN;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(KEY_UP_GPIO_PORT,&GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(KEY_DOWN_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=KEY_DOWN_PIN;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(KEY_DOWN_GPIO_PORT,&GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(KEY_PUSH_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=KEY_PUSH_PIN;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(KEY_PUSH_GPIO_PORT,&GPIO_InitStructure);	
	
	
	GPIO_DeInit(GPIOA);

	
	DMA_InitStructure.DMA_PeripheralBaseAddr= (uint32_t)(&(GPIOA->IDR));
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&GPIOA_value;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //工作在循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 
	DMA_Init(DMA1_Channel7, &DMA_InitStructure); //dma1通道7

	DMA_Cmd(DMA1_Channel7,ENABLE);
	
	//GPIO_EXTILineConfig(SW_PRESS_EXTI_PORT, SW_PRESS_EXTI_PIN);  //外部中断管脚配置 PA12
	
	GPIO_EXTILineConfig(KEY_UP_EXTI_PORT,  KEY_UP_EXTI_PIN);  //外部中断管脚配置 PA12
  GPIO_EXTILineConfig(KEY_DOWN_EXTI_PORT, KEY_DOWN_EXTI_PIN);  //外部中断管脚配置 PA12
  GPIO_EXTILineConfig(KEY_PUSH_EXTI_PORT, KEY_PUSH_EXTI_PIN);  //外部中断管脚配置 PA12
	
	
	
//	EXTI_InitStructure.EXTI_Line = SW_PRESS_EXTI_LINE ;  
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;              //中断模式
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                        //使能
//	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = KEY_UP_EXTI_LINE| KEY_DOWN_EXTI_LINE|KEY_PUSH_EXTI_LINE ;  
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;              //中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                        //使能
	EXTI_Init(&EXTI_InitStructure);
	
//		NVIC_InitStructure.NVIC_IRQChannel = SW_PRESS_IRQ;   //选择中断通道EXTI15_10_IRQn
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //抢占式中断优先级设置为1    
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为1    
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
//		NVIC_Init(&NVIC_InitStructure);
	
	
 		NVIC_InitStructure.NVIC_IRQChannel = KEY_UP_IRQ;   //选择中断通道EXTI15_10_IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;   //抢占式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = KEY_DOWN_IRQ;   //选择中断通道EXTI15_10_IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;   //抢占式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
		NVIC_Init(&NVIC_InitStructure);
	
	 	NVIC_InitStructure.NVIC_IRQChannel = KEY_PUSH_IRQ;   //选择中断通道EXTI15_10_IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;   //抢占式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
		NVIC_Init(&NVIC_InitStructure);

	
}

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure; 	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//禁用jtag功能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      //开启复用时钟
	
	RCC_APB2PeriphClockCmd(SW_CHA_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=SW_CHA_PIN;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SW_CHA_GPIO_PORT,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(SW_CHB_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=SW_CHB_PIN;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SW_CHB_GPIO_PORT,&GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(SW_PRESS_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=SW_PRESS_PIN;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SW_PRESS_GPIO_PORT,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(KEY_UP_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=KEY_UP_PIN;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(KEY_UP_GPIO_PORT,&GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(KEY_DOWN_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=KEY_DOWN_PIN;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(KEY_DOWN_GPIO_PORT,&GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(KEY_PUSH_GPIO_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=KEY_PUSH_PIN;
	//GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(KEY_PUSH_GPIO_PORT,&GPIO_InitStructure);	
	
//			
	GPIO_EXTILineConfig(SW_CHA_EXTI_PORT, SW_CHA_EXTI_PIN);  //外部中断管脚配置 PA11
	GPIO_EXTILineConfig(SW_CHB_EXTI_PORT, SW_CHB_EXTI_PIN);  //外部中断管脚配置 PA12
	//GPIO_EXTILineConfig(SW_PRESS_EXTI_PORT, SW_PRESS_EXTI_PIN);  //外部中断管脚配置 PA12

   
	EXTI_InitStructure.EXTI_Line = SW_CHA_EXTI_PORT|SW_CHB_EXTI_LINE ;  
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;              //中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;   //上升下降沿触发  类似编码器
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                        //使能
	EXTI_Init(&EXTI_InitStructure); 
//	
//	EXTI_InitStructure.EXTI_Line = SW_PRESS_EXTI_LINE ;  
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;              //中断模式
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;          //下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                        //使能
//	EXTI_Init(&EXTI_InitStructure);  
//	
//	//GPIO_EXTILineConfig(KEY_UP_EXTI_PORT,  KEY_UP_EXTI_PIN);  //外部中断管脚配置 PA12
//  GPIO_EXTILineConfig(KEY_DOWN_EXTI_PORT, KEY_DOWN_EXTI_PIN);  //外部中断管脚配置 PA12
//  GPIO_EXTILineConfig(KEY_PUSH_EXTI_PORT, KEY_PUSH_EXTI_PIN);  //外部中断管脚配置 PA12
//	
//	EXTI_InitStructure.EXTI_Line =  KEY_DOWN_EXTI_LINE|KEY_PUSH_EXTI_LINE ;  
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;              //中断模式
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                        //使能
//	EXTI_Init(&EXTI_InitStructure); 
//	
//	
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//使用优先级分组3 最高三位抢占式优先级 0-7
//		/* 
//    		NVIC_PriorityGroup_0 => 选择第0组：所有4位用于指定响应优先级
//        NVIC_PriorityGroup_1 => 选择第1组：最高1位用于指定抢占式优先级，最低3位用于指定响应优先级
//        NVIC_PriorityGroup_2 => 选择第2组：最高2位用于指定抢占式优先级，最低2位用于指定响应优先级
//        NVIC_PriorityGroup_3 => 选择第3组：最高3位用于指定抢占式优先级，最低1位用于指定响应优先级
//        NVIC_PriorityGroup_4 => 选择第4组：所有4位用于指定抢占式优先级
//		*/
		NVIC_InitStructure.NVIC_IRQChannel = SW_CHA_IRQ;   //选择中断通道EXTI15_10_IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = SW_CHB_IRQ;           //选择中断通道EXTI15_10_IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
		NVIC_Init(&NVIC_InitStructure);
//	
//	 	NVIC_InitStructure.NVIC_IRQChannel = SW_PRESS_IRQ;   //选择中断通道EXTI15_10_IRQn
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   //抢占式中断优先级设置为1    
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为1    
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
//		NVIC_Init(&NVIC_InitStructure);
//		
//		
//		NVIC_InitStructure.NVIC_IRQChannel = KEY_UP_IRQ;   //选择中断通道EXTI15_10_IRQn
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;   //抢占式中断优先级设置为1    
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为0
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
//		NVIC_Init(&NVIC_InitStructure);

//		NVIC_InitStructure.NVIC_IRQChannel = KEY_DOWN_IRQ;   //选择中断通道EXTI15_10_IRQn
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;   //抢占式中断优先级设置为1    
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为1    
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
//		NVIC_Init(&NVIC_InitStructure);
//	
//	 	NVIC_InitStructure.NVIC_IRQChannel = KEY_PUSH_IRQ;   //选择中断通道EXTI15_10_IRQn
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;   //抢占式中断优先级设置为1    
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为1    
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
//		NVIC_Init(&NVIC_InitStructure);

}



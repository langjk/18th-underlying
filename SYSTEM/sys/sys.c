#include "sys.h" 

   
void NVIC_Configuration(void)
{
		NVIC_InitTypeDef  NVIC_InitStructure;	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2  2位抢占优先级，2位响应优先级

		
		//超声波
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;  //先占优先级1级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;  //从优先级3级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能
		NVIC_Init(&NVIC_InitStructure);  
	
		//超声波
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;							
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能
		NVIC_Init(&NVIC_InitStructure);  	  
	
		//蓝牙
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02 ;//抢占优先级2
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//抢占优先级2
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//使能
		NVIC_Init(&NVIC_InitStructure);														


	
	
}



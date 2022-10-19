#include "sys.h"

 int   en_pos1;

void Encode_Exti_Init()
{
	  GPIO_InitTypeDef GPIO_InitStructure; 
	  NVIC_InitTypeDef NVIC_InitStructure;
	  EXTI_InitTypeDef EXTI_InitStructure; 
  
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //禁用jtag功能，否则可能无法使用jtag脚外部中断
	
		RCC_APB2PeriphClockCmd(ROBOT_ENCODER1_A_GPIO_CLK|ROBOT_ENCODER1_B_GPIO_CLK , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);        //外部中断，需要使能AFIO时钟

		GPIO_InitStructure.GPIO_Pin = ROBOT_ENCODER1_A_PIN;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //浮空输入
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //上拉输入
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROBOT_ENCODER1_A_GPIO_PORT, &GPIO_InitStructure);    //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

		 
		GPIO_InitStructure.GPIO_Pin =  ROBOT_ENCODER1_B_PIN;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //浮空输入
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //上拉输入
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROBOT_ENCODER1_B_GPIO_PORT, &GPIO_InitStructure);    //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		
		GPIO_EXTILineConfig(ROBOT_ENCODER1_A_EXTI_PORT, ROBOT_ENCODER1_A_EXTI_PIN);  //外部中断管脚配置 PA11
		GPIO_EXTILineConfig(ROBOT_ENCODER1_B_EXTI_PORT, ROBOT_ENCODER1_B_EXTI_PIN);  //外部中断管脚配置 PA12

		EXTI_InitStructure.EXTI_Line = ROBOT_ENCODER1_A_EXTI_LINE | ROBOT_ENCODER1_B_EXTI_LINE ;  
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;              //中断模式
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;   //上升下降沿触发
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;                        //使能
		EXTI_Init(&EXTI_InitStructure);  
      
      //  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);             //选择中断分组1
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		NVIC_InitStructure.NVIC_IRQChannel = ROBOT_ENCODER1_A_IRQ;   //选择中断通道EXTI15_10_IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //响应式中断优先级设置为0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = ROBOT_ENCODER1_B_IRQ;   //选择中断通道EXTI15_10_IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //响应式中断优先级设置为1    
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断
		NVIC_Init(&NVIC_InitStructure);
	
	
	
}

void Encoder_Left_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频 不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
  //Reset counter
  TIM_SetCounter(TIM2,0);
  TIM_Cmd(TIM2, ENABLE); 
}

void Encoder_Right_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//使能定时器4的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频  不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	
  TIM_ICStructInit(&TIM_ICInitStructure);
	
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);
	
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
  //Reset counter
	
  TIM_SetCounter(TIM1,0);
  TIM_Cmd(TIM1, ENABLE); 
}


int Read_Encoder(u8 TIMX)
{
   int Encoder_TIM;    
   switch(TIMX)
	 {
		 case 1:  Encoder_TIM= (short)TIM1 -> CNT;  TIM1 -> CNT=0;break;
	   case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default: Encoder_TIM=0;
	 }
		return Encoder_TIM;
}

void TIM1_IRQHandler(void)
{ 		    		  			    
	if(TIM1->SR&0X0001)//溢出中断
	{    				   				     	    	
	}				   
	TIM1->SR&=~(1<<0);//清除中断标志位 	    
}

void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//溢出中断
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//清除中断标志位 	    
}





#include "sys.h"

 int   en_pos1;

void Encode_Exti_Init()
{
	  GPIO_InitTypeDef GPIO_InitStructure; 
	  NVIC_InitTypeDef NVIC_InitStructure;
	  EXTI_InitTypeDef EXTI_InitStructure; 
  
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //����jtag���ܣ���������޷�ʹ��jtag���ⲿ�ж�
	
		RCC_APB2PeriphClockCmd(ROBOT_ENCODER1_A_GPIO_CLK|ROBOT_ENCODER1_B_GPIO_CLK , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);        //�ⲿ�жϣ���Ҫʹ��AFIOʱ��

		GPIO_InitStructure.GPIO_Pin = ROBOT_ENCODER1_A_PIN;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //��������
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROBOT_ENCODER1_A_GPIO_PORT, &GPIO_InitStructure);    //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

		 
		GPIO_InitStructure.GPIO_Pin =  ROBOT_ENCODER1_B_PIN;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       //��������
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(ROBOT_ENCODER1_B_GPIO_PORT, &GPIO_InitStructure);    //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		
		GPIO_EXTILineConfig(ROBOT_ENCODER1_A_EXTI_PORT, ROBOT_ENCODER1_A_EXTI_PIN);  //�ⲿ�жϹܽ����� PA11
		GPIO_EXTILineConfig(ROBOT_ENCODER1_B_EXTI_PORT, ROBOT_ENCODER1_B_EXTI_PIN);  //�ⲿ�жϹܽ����� PA12

		EXTI_InitStructure.EXTI_Line = ROBOT_ENCODER1_A_EXTI_LINE | ROBOT_ENCODER1_B_EXTI_LINE ;  
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;              //�ж�ģʽ
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;   //�����½��ش���
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;                        //ʹ��
		EXTI_Init(&EXTI_InitStructure);  
      
      //  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);             //ѡ���жϷ���1
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		NVIC_InitStructure.NVIC_IRQChannel = ROBOT_ENCODER1_A_IRQ;   //ѡ���ж�ͨ��EXTI15_10_IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //��ռʽ�ж����ȼ�����Ϊ1    
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //��Ӧʽ�ж����ȼ�����Ϊ0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ���ж�
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = ROBOT_ENCODER1_B_IRQ;   //ѡ���ж�ͨ��EXTI15_10_IRQn
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //��ռʽ�ж����ȼ�����Ϊ1    
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //��Ӧʽ�ж����ȼ�����Ϊ1    
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ���ж�
		NVIC_Init(&NVIC_InitStructure);
	
	
	
}

void Encoder_Left_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ ����Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
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
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ  ����Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	
  TIM_ICStructInit(&TIM_ICInitStructure);
	
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM1, &TIM_ICInitStructure);
	
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
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
	if(TIM1->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM1->SR&=~(1<<0);//����жϱ�־λ 	    
}

void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}





#include "sys.h" 

   
void NVIC_Configuration(void)
{
		NVIC_InitTypeDef  NVIC_InitStructure;	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2  2λ��ռ���ȼ���2λ��Ӧ���ȼ�

		
		//������
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;  //��ռ���ȼ�1��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;  //�����ȼ�3��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ��
		NVIC_Init(&NVIC_InitStructure);  
	
		//������
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;							
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�2 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ��
		NVIC_Init(&NVIC_InitStructure);  	  
	
		//����
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02 ;//��ռ���ȼ�2
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//��ռ���ȼ�2
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//ʹ��
		NVIC_Init(&NVIC_InitStructure);														


	
	
}



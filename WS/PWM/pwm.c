#include "sys.h"




void Steer_TIM3_PWM_Init(u16 arr,u16 psc )
{
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO , ENABLE);  //ʹ��GPIO����ʱ��ʹ�ܺ͸�������ʱ��
  
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3  ,ENABLE ); //������ӳ����Ӧ������	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM3_CH2 pb5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;  //���ÿ�©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; 	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0;                            
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //����Ƚϼ��Ը�
	//TIM_OC1Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 

  TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE �����ʹ��	

//	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM1
	
}



void Motor_TIM1_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);  // ����GPIOʱ��
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //����AFʱ�Ӹ���
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //����tim1ʱ��
	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        
  GPIO_Init(GPIOA, &GPIO_InitStructure);
       
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                    // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);        


 
  /* ����TIM1��ʱ��*/
  //TIM_TimeBaseStructure.TIM_Prescaler = 71;
  /*  ��ϵͳ����Ƶ�ʷ�Ƶ������ʱ���Ĺ���Ƶ�� ������72MHz��Ҫ�õ�1MHz��ʱ������Ƶ�ʣ�*/
  TIM_TimeBaseStructure.TIM_Prescaler =  psc ;     
                                 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    
   /* TIM_CounterMode_Up                 TIM ���ϼ���ģʽ
    TIM_CounterMode_Down               TIM ���¼���ģʽ
    TIM_CounterMode_CenterAligned1     TIM �������ģʽ 1 ����ģʽ
   TIM_CounterMode_CenterAligned2     TIM �������ģʽ 2 ����ģʽ  */
          
  TIM_TimeBaseStructure.TIM_Period =arr;  
   /* ��������� TIM_Prescaler  ���� PWM��Ƶ�ʣ�����TIM_Prescaler=71 ʱ��TIM��1MHz��Ƶ�ʼ��������ﵽ
      TIM_Period�趨�ĸ���ʱ���¼���TIM_Period��ֵ���Ĵ�����������һ��ѭ�������TIM_Period��ֵһֱ���䣬
      PWM����һ���̶�������������˴���PWMƵ�����õ��� 1MHz/1000=1kHz��    */           
         
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;		
    /* ���ö�ʱ��ʱ��CK_INTƵ���������������Լ������˲�������ʱ��Ƶ�ʷ�Ƶ�����˴����á�   */
    						  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                         
   /* ����ĳ��ռ�ձȵ�PWM�ظ�ִ�еĴ��������֮ǰ���õ�ռ�ձ�Ϊ50�������ֵ����Ϊ1�Ļ���50%PWM�ᱻִ��
      ���Σ�Ҳ����������һ����ִ��һ������   */

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);



  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
   /*�Ƚ����ģʽѡ�񣬹�8�֡�value��
     TIM_OCMode_Timing                  TIM ����Ƚ�ʱ��ģʽ
     TIM_OCMode_Active                  TIM ����Ƚ�����ģʽ
     TIM_OCMode_Inactive                TIM ����ȽϷ�����ģʽ
     TIM_OCMode_Toggle                  TIM ����Ƚϴ���ģʽ
     TIM_OCMode_PWM1                    TIM �����ȵ���ģʽ 1 
     TIM_OCMode_PWM2                    TIM �����ȵ���ģʽ 2  
     ��PWM�����£�ѡTIM_OCMode_PWM1 ��TIM_OCMode_PWM2 ������ѡ���� */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;              
   /* �Ƚ����ʹ�ܣ������ź��Ƿ�ͨ���ⲿ�������*/
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;            
   /* ����ʹ�ܣ����������ź��Ƿ�ͨ���ⲿ�������*/
  TIM_OCInitStructure.TIM_Pulse = 0; 
   /* ��ʼ��ռ�ձ�   */                          
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
   /* ������ԣ�������ʱ��ͨ����Ч��ƽ�ļ���*/
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
   /* ����������ԣ���ѡ�ߵ�ƽ��Ч���͵�ƽ��Ч*/
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
   /* ����״̬ʱͨ�������ƽ���ã���ѡ�ߵ�ƽ���͵�ƽ*/
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
   /* ����״̬ʱ����ͨ�������ƽ���ã���ѡ�ߵ�ƽ���͵�ƽ���趨ֵ�����TIM_OCIdleState�෴*/

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	 TIM_ARRPreloadConfig(TIM1, ENABLE);  
   /* ��������������ǣ�������ֹ�ڶ�ʱ������ʱ��ARR�Ļ�������д����ֵ ����˼�ǣ���Enable�������£�
      ���¼�����֮ǰ��������ARR��ֵ����������£�Ҳ����˵ԭ�ȵ�PWMƵ����1kHz���������һ������û��
      ����ʱ�������ARR��ֵ��������10kHz������ô��ǰδ��ɵ�PWM�ᱻ����ĳ�10kHz�������Disable����
      ôֻ�����¸�������Чʱ���ġ�
  */
  TIM_Cmd(TIM1, ENABLE);       
   /* ���ܶ�ʱ��*/               
  TIM_CtrlPWMOutputs(TIM1,ENABLE);            
   /* ʹ��PWM����˿ڣ����PWM����*/

}




void TIM3_PWM_Init(u16 arr,u16 psc)//�����PWM����
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //TIM_CH1 //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; 	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0;                            
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //����Ƚϼ��Ը�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 

  TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM1
}

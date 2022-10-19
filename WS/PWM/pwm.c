#include "sys.h"




void Steer_TIM3_PWM_Init(u16 arr,u16 psc )
{
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO , ENABLE);  //使能GPIO外设时钟使能和复用引脚时钟
  
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3  ,ENABLE ); //部分重映射相应的外设	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM3_CH2 pb5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;  //复用开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; 	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0;                            
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出比较极性高
	//TIM_OC1Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 

  TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE 主输出使能	

//	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH2预装载使能	 
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM1
	
}



void Motor_TIM1_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);  // 开启GPIO时钟
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //开启AF时钟复用
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //开启tim1时钟
	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        
  GPIO_Init(GPIOA, &GPIO_InitStructure);
       
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);        


 
  /* 开启TIM1的时钟*/
  //TIM_TimeBaseStructure.TIM_Prescaler = 71;
  /*  把系统工作频率分频后当做定时器的工作频率 ，比如72MHz，要得到1MHz定时器工作频率，*/
  TIM_TimeBaseStructure.TIM_Prescaler =  psc ;     
                                 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    
   /* TIM_CounterMode_Up                 TIM 向上计数模式
    TIM_CounterMode_Down               TIM 向下计数模式
    TIM_CounterMode_CenterAligned1     TIM 中央对齐模式 1 计数模式
   TIM_CounterMode_CenterAligned2     TIM 中央对齐模式 2 计数模式  */
          
  TIM_TimeBaseStructure.TIM_Period =arr;  
   /* 这个参数和 TIM_Prescaler  构成 PWM的频率，即当TIM_Prescaler=71 时，TIM以1MHz的频率计数，当达到
      TIM_Period设定的个数时重新加载TIM_Period的值到寄存器，进行下一个循环，如果TIM_Period的值一直不变，
      PWM就已一个固定的周期输出，此处的PWM频率设置的是 1MHz/1000=1kHz。    */           
         
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;		
    /* 设置定时器时钟CK_INT频率与死区发生器以及数字滤波器采样时钟频率分频化，此处不用。   */
    						  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                         
   /* 对于某个占空比的PWM重复执行的次数，如果之前设置的占空比为50，那这个值设置为1的话，50%PWM会被执行
      两次，也就是连着上一次再执行一个周期   */

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);



  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
   /*比较输出模式选择，共8种。value：
     TIM_OCMode_Timing                  TIM 输出比较时间模式
     TIM_OCMode_Active                  TIM 输出比较主动模式
     TIM_OCMode_Inactive                TIM 输出比较非主动模式
     TIM_OCMode_Toggle                  TIM 输出比较触发模式
     TIM_OCMode_PWM1                    TIM 脉冲宽度调制模式 1 
     TIM_OCMode_PWM2                    TIM 脉冲宽度调制模式 2  
     这PWM功能下，选TIM_OCMode_PWM1 或TIM_OCMode_PWM2 ，这里选后者 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;              
   /* 比较输出使能，决定信号是否通过外部引脚输出*/
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;            
   /* 互补使能，决定互补信号是否通过外部引脚输出*/
  TIM_OCInitStructure.TIM_Pulse = 0; 
   /* 初始化占空比   */                          
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
   /* 输出极性，决定定时器通道有效电平的极性*/
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
   /* 互补输出极性，可选高电平有效、低电平有效*/
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
   /* 空闲状态时通道输出电平设置，可选高电平、低电平*/
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
   /* 空闲状态时互补通道输出电平设置，可选高电平、低电平，设定值必须跟TIM_OCIdleState相反*/

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	 TIM_ARRPreloadConfig(TIM1, ENABLE);  
   /* 这个函数的作用是：允许或禁止在定时器工作时向ARR的缓冲器中写入新值 ，意思是，在Enable的条件下，
      当事件触发之前，更改了ARR的值，会立马更新，也就是说原先的PWM频率是1kHz，如果你在一个周期没结
      束的时候更新了ARR的值（比如是10kHz），那么当前未完成的PWM会被立马改成10kHz；如果是Disable，那
      么只能在下个周期生效时更改。
  */
  TIM_Cmd(TIM1, ENABLE);       
   /* 是能定时器*/               
  TIM_CtrlPWMOutputs(TIM1,ENABLE);            
   /* 使能PWM输出端口，输出PWM波形*/

}




void TIM3_PWM_Init(u16 arr,u16 psc)//电机的PWM控制
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //TIM_CH1 //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; 	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0;                            
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 

  TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH4预装载使能	 
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM1
}

#include "sys.h"

int T;

//定时器4中断服务程序
void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生
	{
		
     T=T+TIM4_MS;//中断计时
		 Key_Scan();
//		Adc_M1=Get_Adc(ADC1,ROBOT_M1_ADC_CH_NUM);
//		Adc_M2=Get_Adc(ADC1,ROBOT_M2_ADC_CH_NUM);
//		Adc_M3=Get_Adc(ADC1,ROBOT_M3_ADC_CH_NUM);
//		Adc_M4=Get_Adc(ADC1,ROBOT_M4_ADC_CH_NUM);
//		
//  	Adc_M5=Get_Adc(ADC1,ROBOT_M5_ADC_CH_NUM);
//		Adc_M6=Get_Adc(ADC1,ROBOT_M6_ADC_CH_NUM);
//		Adc_M7=Get_Adc(ADC1,ROBOT_M7_ADC_CH_NUM);
//		Adc_M8=Get_Adc(ADC1,ROBOT_M8_ADC_CH_NUM);
		
  //	Adc_M5=Get_Adc(ADC3,ROBOT_M5_ADC_CH_NUM);
		
//		Speed_R=Get_Speed(1);
//		Speed_L=Get_Speed(0);
//		Moto1=Motor_PID_Cal_L(Speed_L,Speed_Set_L);
//		Moto2=Motor_PID_Cal_R(Speed_R,Speed_Set_R);
//		//Set_Pwm(Moto1,Moto2);
//		if(Time_Count==5000)
//		{
//			Time_Count=0;
//			T1_Count=0;
//			T2_Count=0;
//		}			  //5s一个整周期
//		else	Time_Count++;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIMx的中断
	}
}

/** 编码器 ab相中断引脚触发函数*****/
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(ROBOT_ENCODER1_A_EXTI_LINE) != RESET){
			if(GPIO_ReadInputDataBit(ROBOT_ENCODER1_A_GPIO_PORT, ROBOT_ENCODER1_A_PIN) == HIGH){
					if(GPIO_ReadInputDataBit(ROBOT_ENCODER1_B_GPIO_PORT, ROBOT_ENCODER1_B_PIN) == LOW){
							en_pos1--;
					}else {
							en_pos1++;
					}
			} else {
					if(GPIO_ReadInputDataBit(ROBOT_ENCODER1_B_GPIO_PORT, ROBOT_ENCODER1_B_PIN) == HIGH){
							en_pos1--;
					}else {
							en_pos1++;
					}
			}
			EXTI_ClearITPendingBit(ROBOT_ENCODER1_A_EXTI_LINE);
			EXTI_ClearFlag(ROBOT_ENCODER1_A_EXTI_LINE);
	}
	
	if(EXTI_GetITStatus(ROBOT_ENCODER1_B_EXTI_LINE) != RESET){
			if(GPIO_ReadInputDataBit(ROBOT_ENCODER1_B_GPIO_PORT, ROBOT_ENCODER1_B_PIN) == HIGH){
					if(GPIO_ReadInputDataBit(ROBOT_ENCODER1_A_GPIO_PORT, ROBOT_ENCODER1_A_PIN) == HIGH){
							en_pos1--;
					}else {
							en_pos1++;
					}
			} else {
					if(GPIO_ReadInputDataBit(ROBOT_ENCODER1_A_GPIO_PORT, ROBOT_ENCODER1_A_PIN) == LOW){
							en_pos1--;
					}else {
							en_pos1++;
					}
			}
			EXTI_ClearITPendingBit(ROBOT_ENCODER1_B_EXTI_LINE);
			EXTI_ClearFlag(ROBOT_ENCODER1_B_EXTI_LINE);
	}

}

/** 旋钮 中断引脚触发函数*****/
void EXTI15_10_IRQHandler(void)
{
	
	
//	if(EXTI_GetITStatus(SW_CHB_EXTI_LINE) != RESET)
//		{
//			
// 			TSUI_EncoderEvent();
//			EXTI_ClearITPendingBit(SW_CHB_EXTI_LINE);
//			EXTI_ClearFlag(SW_CHB_EXTI_LINE);
//	 }
//		else if(EXTI_GetITStatus(SW_CHA_EXTI_LINE) != RESET)
//		{
//			
// 			TSUI_EncoderEvent();
//			EXTI_ClearITPendingBit(SW_CHA_EXTI_LINE);
//			EXTI_ClearFlag(SW_CHA_EXTI_LINE);
//	 }
		
	 if(EXTI_GetITStatus(SW_PRESS_EXTI_LINE) != RESET)
		{
//			if(!TSUI_PT_PRESS_I)     //读取引脚电平，若为低电平 说明触发
        TSUI_SetButtonEvent(PRESS);//旋钮按下
			EXTI_ClearITPendingBit(SW_PRESS_EXTI_LINE);
			EXTI_ClearFlag(SW_PRESS_EXTI_LINE);
	  }
	 if(EXTI_GetITStatus(KEY_UP_EXTI_LINE) != RESET)
		{
		  //if(!TSUI_PT_UP_I)
         TSUI_SetButtonEvent(UP);    //拨轮向上
		  EXTI_ClearITPendingBit(KEY_UP_EXTI_LINE);
			EXTI_ClearFlag(KEY_UP_EXTI_LINE);
	  }
//	if(EXTI_GetITStatus(KEY_UP_EXTI_LINE) != RESET)
//		{

//			EXTI_ClearITPendingBit(SW_PRESS_EXTI_LINE);
//			EXTI_ClearFlag(SW_PRESS_EXTI_LINE);
//	  }

//		if(EXTI_GetITStatus(SW_PRESS_EXTI_LINE) != RESET)
//		{

//			EXTI_ClearITPendingBit(SW_PRESS_EXTI_LINE);
//			EXTI_ClearFlag(SW_PRESS_EXTI_LINE);
//	  }	
}


void EXTI3_IRQHandler(void) 
{
	if(EXTI_GetITStatus(KEY_DOWN_EXTI_LINE) != RESET)
		{
      TSUI_SetButtonEvent(DOWN);    //拨轮向上
			EXTI_ClearITPendingBit(KEY_DOWN_EXTI_LINE);
			EXTI_ClearFlag(KEY_DOWN_EXTI_LINE);
	  }		
}

void EXTI4_IRQHandler(void) 
{
	if(EXTI_GetITStatus(KEY_PUSH_EXTI_LINE) != RESET)
		{
      TSUI_SetButtonEvent(OK);//拨轮按下
			EXTI_ClearITPendingBit(KEY_PUSH_EXTI_LINE);
			EXTI_ClearFlag(KEY_PUSH_EXTI_LINE);
	  }		
}

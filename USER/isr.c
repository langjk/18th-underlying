#include "sys.h"

int T;

//��ʱ��4�жϷ������
void TIM4_IRQHandler(void)   //TIM4�ж�
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ���
	{
		
     T=T+TIM4_MS;//�жϼ�ʱ
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
//		}			  //5sһ��������
//		else	Time_Count++;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIMx���ж�
	}
}

/** ������ ab���ж����Ŵ�������*****/
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

/** ��ť �ж����Ŵ�������*****/
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
//			if(!TSUI_PT_PRESS_I)     //��ȡ���ŵ�ƽ����Ϊ�͵�ƽ ˵������
        TSUI_SetButtonEvent(PRESS);//��ť����
			EXTI_ClearITPendingBit(SW_PRESS_EXTI_LINE);
			EXTI_ClearFlag(SW_PRESS_EXTI_LINE);
	  }
	 if(EXTI_GetITStatus(KEY_UP_EXTI_LINE) != RESET)
		{
		  //if(!TSUI_PT_UP_I)
         TSUI_SetButtonEvent(UP);    //��������
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
      TSUI_SetButtonEvent(DOWN);    //��������
			EXTI_ClearITPendingBit(KEY_DOWN_EXTI_LINE);
			EXTI_ClearFlag(KEY_DOWN_EXTI_LINE);
	  }		
}

void EXTI4_IRQHandler(void) 
{
	if(EXTI_GetITStatus(KEY_PUSH_EXTI_LINE) != RESET)
		{
      TSUI_SetButtonEvent(OK);//���ְ���
			EXTI_ClearITPendingBit(KEY_PUSH_EXTI_LINE);
			EXTI_ClearFlag(KEY_PUSH_EXTI_LINE);
	  }		
}

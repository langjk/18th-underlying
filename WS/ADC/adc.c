/************************************
 * �ļ���  ��adc.c
 * ����    ��DMA��ʽ��ȡADCֵӦ�ú�����         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ� PCA0 - ADC1 
 * ��汾  ��ST3.0.0  

**********************************************************************************/
#include "sys.h"


#include <math.h>

#include "adc.h"

#define ADC1_DR_Address    ((u32)0x4001244C)



/*���ò���ͨ���˿� ʹ��GPIOʱ��	  ����ADC����PA0�˿��ź�*/
 void ADC1_GPIO_Config(void)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure;    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		    //GPIO����Ϊģ������
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
}

void  DMA1_Channel1_IRQHandler(void)
{
//	if(DMA_GetITStatus(DMA1_IT_TC1)!=RESET){
//		//�жϴ������

//		lcddmaflag=1;
//    TIM_Cmd(TIM2,DISABLE);		//�ر�TIM2
//			

//	//	OLED2_Clear();     //OLED����
//		if(AdcStartFlag==1)
//		{
//			
//			memcpy(&AdcData[AdcNum],&displayadc[0],2);//
//			AdcNum++;
//		}

//		
//		
//		DMA_ClearITPendingBit(DMA1_IT_TC1);
//		
//	}
}


void DMA_ADC_Init()
{
//	DMA_InitTypeDef DMA_InitStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);	  			//ʹ��ADC1ͨ��ʱ��
	
//	//DMA1��ʼ��
//	DMA_DeInit(DMA1_Channel1);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;				//ADC1��ַ
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)displayadc; 		//�ڴ��ַ
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 				//����(�����赽�ڴ�)
//	DMA_InitStructure.DMA_BufferSize = depth; 						//�������ݵĴ�С
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 		//�����ַ����  	//�ڴ��ַ�̶�
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 		
////	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord ; //�������ݵ�λ
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord ;    //�ڴ����ݵ�λ
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular  ; 		//DMAģʽ��ѭ������
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High ; 		//���ȼ�����
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;   		//��ֹ�ڴ浽�ڴ�Ĵ���
//	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //����DMA1
//	
//	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC, ENABLE);		//ʹ�ܴ�������ж�

//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	DMA_Cmd(DMA1_Channel1,ENABLE);
}


void ADC_GPIO_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(ROBOT_M1_GPIO_CLK|ROBOT_M2_GPIO_CLK|ROBOT_M3_GPIO_CLK|ROBOT_M4_GPIO_CLK, ENABLE);	  //ʹ��GPIOAʱ��

	//PC0 ��Ϊģ��ͨ����������   
	GPIO_InitStructure.GPIO_Pin = ROBOT_M1_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ROBOT_M1_GPIO_PORT, &GPIO_InitStructure);  
	
	
	GPIO_InitStructure.GPIO_Pin = ROBOT_M2_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ROBOT_M2_GPIO_PORT, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = ROBOT_M3_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ROBOT_M3_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ROBOT_M4_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ROBOT_M4_GPIO_PORT, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = ROBOT_M5_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ROBOT_M5_GPIO_PORT, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = ROBOT_M6_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ROBOT_M6_GPIO_PORT, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = ROBOT_M7_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ROBOT_M7_GPIO_PORT, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = ROBOT_M8_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ROBOT_M8_GPIO_PORT, &GPIO_InitStructure);
}




void Adc_Init()
{
	ADC_InitTypeDef ADC_InitStructure;
	
	// TIM2_Init(16,8);		//72000000/��8+1��/16=500KHz��   ռ�ձ� =ֵ/arr   ADCҪ��2us�����  ��12.5+1.5��/12M =1.66us
  //TIM2_Init(500,719);	//72M/(720)/500=200hz  ������Ϊ200hz
	
	//DMA_ADC_Init();//ʹ��DMAģʽ ADC����ֱ�ӵ�����
	ADC_GPIO_Init();//��ʼ��ADC�ɼ�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_ADC3, ENABLE);	  //ʹ��ADC1ͨ��ʱ��

	//ADC1��ʼ��
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 			//����ADCģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;  			//�ر�ɨ�跽ʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;			//�ر�����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;   	//ʹ���ⲿ����ģʽ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 			//�ɼ������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1; 			//Ҫת����ͨ����Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);
	
//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 			//����ADCģʽ
//	ADC_InitStructure.ADC_ScanConvMode = DISABLE;  			//�ر�ɨ�跽ʽ
//	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;			//�ر�����ת��ģʽ
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;   	//ʹ���ⲿ����ģʽ
//	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 			//�ɼ������Ҷ���
//	ADC_InitStructure.ADC_NbrOfChannel = 1; 			//Ҫת����ͨ����Ŀ
//	ADC_Init(ADC3, &ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);				//����ADCʱ�ӣ�ΪPCLK2��6��Ƶ����12MHz
	ADC_RegularChannelConfig(ADC1, ROBOT_M1_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//����ADC1ͨ��6Ϊ239.5���������� 
	ADC_RegularChannelConfig(ADC1, ROBOT_M2_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//����ADC1ͨ��6Ϊ239.5���������� 
	ADC_RegularChannelConfig(ADC1, ROBOT_M3_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//����ADC1ͨ��6Ϊ239.5���������� 
	ADC_RegularChannelConfig(ADC1, ROBOT_M4_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//����ADC1ͨ��6Ϊ239.5���������� 
	
	//ADC_RegularChannelConfig(ADC1, ROBOT_M5_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//����ADC1ͨ��6Ϊ239.5����������

 	ADC_RegularChannelConfig(ADC1, ROBOT_M5_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//����ADC1ͨ��6Ϊ239.5���������� 
	ADC_RegularChannelConfig(ADC1, ROBOT_M6_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//����ADC1ͨ��6Ϊ239.5���������� 
	ADC_RegularChannelConfig(ADC1, ROBOT_M7_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//����ADC1ͨ��6Ϊ239.5���������� 
	ADC_RegularChannelConfig(ADC1, ROBOT_M8_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//����ADC1ͨ��6Ϊ239.5���������� 
	
	
	//ʹ��ADC��DMA
	//ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
 
	ADC_ResetCalibration(ADC1);				//��λУ׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));				//�ȴ�У׼�Ĵ�����λ���
 
	ADC_StartCalibration(ADC1);				//ADCУ׼
	while(ADC_GetCalibrationStatus(ADC1));				//�ȴ�У׼���
	
	ADC_ExternalTrigConvCmd(ADC1, ENABLE);		//�����ⲿ����ģʽʹ��
	
	/*adc3 */
		ADC_Cmd(ADC3,ENABLE);
 
	ADC_ResetCalibration(ADC3);				//��λУ׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC3));				//�ȴ�У׼�Ĵ�����λ���
 
	ADC_StartCalibration(ADC3);				//ADCУ׼
	while(ADC_GetCalibrationStatus(ADC3));				//�ȴ�У׼���
	
	ADC_ExternalTrigConvCmd(ADC3, ENABLE);		//�����ⲿ����ģʽʹ��
}


//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(ADC_TypeDef* ADCx,u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADCx, ch, 1, ADC_SampleTime_28Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADCx);	//�������һ��ADC1�������ת�����
	
	
}

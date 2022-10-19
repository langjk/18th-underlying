/************************************
 * 文件名  ：adc.c
 * 描述    ：DMA方式读取ADC值应用函数库         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接： PCA0 - ADC1 
 * 库版本  ：ST3.0.0  

**********************************************************************************/
#include "sys.h"


#include <math.h>

#include "adc.h"

#define ADC1_DR_Address    ((u32)0x4001244C)



/*配置采样通道端口 使能GPIO时钟	  设置ADC采样PA0端口信号*/
 void ADC1_GPIO_Config(void)
{ 
	
	GPIO_InitTypeDef GPIO_InitStructure;    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		    //GPIO设置为模拟输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
}

void  DMA1_Channel1_IRQHandler(void)
{
//	if(DMA_GetITStatus(DMA1_IT_TC1)!=RESET){
//		//中断处理代码

//		lcddmaflag=1;
//    TIM_Cmd(TIM2,DISABLE);		//关闭TIM2
//			

//	//	OLED2_Clear();     //OLED清屏
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

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);	  			//使能ADC1通道时钟
	
//	//DMA1初始化
//	DMA_DeInit(DMA1_Channel1);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;				//ADC1地址
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)displayadc; 		//内存地址
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 				//方向(从外设到内存)
//	DMA_InitStructure.DMA_BufferSize = depth; 						//传输内容的大小
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 		//外设地址自增  	//内存地址固定
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 		
////	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord ; //外设数据单位
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord ;    //内存数据单位
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular  ; 		//DMA模式：循环传输
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High ; 		//优先级：高
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;   		//禁止内存到内存的传输
//	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //配置DMA1
//	
//	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC, ENABLE);		//使能传输完成中断

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
	
	RCC_APB2PeriphClockCmd(ROBOT_M1_GPIO_CLK|ROBOT_M2_GPIO_CLK|ROBOT_M3_GPIO_CLK|ROBOT_M4_GPIO_CLK, ENABLE);	  //使能GPIOA时钟

	//PC0 作为模拟通道输入引脚   
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
	
	// TIM2_Init(16,8);		//72000000/（8+1）/16=500KHz，   占空比 =值/arr   ADC要在2us内完成  （12.5+1.5）/12M =1.66us
  //TIM2_Init(500,719);	//72M/(720)/500=200hz  采样率为200hz
	
	//DMA_ADC_Init();//使用DMA模式 ADC外设直接到数组
	ADC_GPIO_Init();//初始化ADC采集引脚

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_ADC3, ENABLE);	  //使能ADC1通道时钟

	//ADC1初始化
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 			//独立ADC模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;  			//关闭扫描方式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;			//关闭连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;   	//使用外部触发模式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 			//采集数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1; 			//要转换的通道数目
	ADC_Init(ADC1, &ADC_InitStructure);
	
//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 			//独立ADC模式
//	ADC_InitStructure.ADC_ScanConvMode = DISABLE;  			//关闭扫描方式
//	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;			//关闭连续转换模式
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;   	//使用外部触发模式
//	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 			//采集数据右对齐
//	ADC_InitStructure.ADC_NbrOfChannel = 1; 			//要转换的通道数目
//	ADC_Init(ADC3, &ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);				//配置ADC时钟，为PCLK2的6分频，即12MHz
	ADC_RegularChannelConfig(ADC1, ROBOT_M1_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//配置ADC1通道6为239.5个采样周期 
	ADC_RegularChannelConfig(ADC1, ROBOT_M2_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//配置ADC1通道6为239.5个采样周期 
	ADC_RegularChannelConfig(ADC1, ROBOT_M3_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//配置ADC1通道6为239.5个采样周期 
	ADC_RegularChannelConfig(ADC1, ROBOT_M4_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//配置ADC1通道6为239.5个采样周期 
	
	//ADC_RegularChannelConfig(ADC1, ROBOT_M5_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//配置ADC1通道6为239.5个采样周期

 	ADC_RegularChannelConfig(ADC1, ROBOT_M5_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//配置ADC1通道6为239.5个采样周期 
	ADC_RegularChannelConfig(ADC1, ROBOT_M6_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//配置ADC1通道6为239.5个采样周期 
	ADC_RegularChannelConfig(ADC1, ROBOT_M7_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//配置ADC1通道6为239.5个采样周期 
	ADC_RegularChannelConfig(ADC1, ROBOT_M8_ADC_CH, 1, ADC_SampleTime_28Cycles5);		//配置ADC1通道6为239.5个采样周期 
	
	
	//使能ADC、DMA
	//ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
 
	ADC_ResetCalibration(ADC1);				//复位校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));				//等待校准寄存器复位完成
 
	ADC_StartCalibration(ADC1);				//ADC校准
	while(ADC_GetCalibrationStatus(ADC1));				//等待校准完成
	
	ADC_ExternalTrigConvCmd(ADC1, ENABLE);		//设置外部触发模式使能
	
	/*adc3 */
		ADC_Cmd(ADC3,ENABLE);
 
	ADC_ResetCalibration(ADC3);				//复位校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC3));				//等待校准寄存器复位完成
 
	ADC_StartCalibration(ADC3);				//ADC校准
	while(ADC_GetCalibrationStatus(ADC3));				//等待校准完成
	
	ADC_ExternalTrigConvCmd(ADC3, ENABLE);		//设置外部触发模式使能
}


//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(ADC_TypeDef* ADCx,u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADCx, ch, 1, ADC_SampleTime_28Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADCx);	//返回最近一次ADC1规则组的转换结果
	
	
}

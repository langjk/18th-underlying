/*********************************************************************************************************************
					TSL1401接线定义：
					------------------------------------ 
					    模块管脚       	单片机管脚
					    CCD_AO	   		F6   :ADC3  ch4
					    CCD_CLK	   		F1
					    CCD_SI	   		F3
					------------------------------------ 
 ********************************************************************************************************************/



#include "sys.h"





uint16_t ccd_data[128];    //CCD数据
uint16_t ccd_two[128];
int Line_mid;
int dir_error;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TSL1401线阵CCD初始化
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void ccd_init(void)     
{       
    ccd_adc_init();                  
    ccd_gpio_Init();
	  CCD_CLK(0);
	  CCD_SI(0);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      TSL1401线阵CCD数据采集
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				在isr.c里面先创建对应的中断函数，然后调用该函数(之后别忘记清除中断标志位)
//-------------------------------------------------------------------------------------------------------------------
void ccd_collect(void)
{
  uint16_t i = 0;

	CCD_SI(1);
	delay_us(1);
	CCD_CLK(1);
	delay_us(1);
	CCD_SI(0);
	delay_us(1);
	//延时采样第一个点（0点）
	for(i=0;i<20;i++)
	{
		delay_us(1);
	}
	//*ccd_data=Normalized_U8(ccd_Get_Adc(CCD_AO_ADC_chn));//读取后取8位
	ccd_data[0]=ccd_Get_Adc(CCD_AO_ADC_chn);

	CCD_CLK(0); 
	
	for(i=1;i<128;i++)//2~128个点
	{
	    delay_us(1);
		CCD_CLK(1);
		 //*ccd_data=Normalized_U8(ccd_Get_Adc(CCD_AO_ADC_chn));//读取后取8位
		ccd_data[i]=ccd_Get_Adc(CCD_AO_ADC_chn); 
	    CCD_CLK(0);
	}
	//必须有第129个时钟，使内部开关归位，否则，下次不正常
	delay_us(1);
	CCD_CLK(1); 
	delay_us(1);
	CCD_CLK(0);
  
		
}

void ccd_gpio_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(CCD_CLK_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=CCD_CLK_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(CCD_CLK_PORT,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(CCD_SI_CLK,ENABLE);	
	GPIO_InitStructure.GPIO_Pin=CCD_SI_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(CCD_SI_PORT,&GPIO_InitStructure);

}

void ccd_adc_init()
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(CCD_AO_CLK |CCD_AO_ADC	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
                       
	GPIO_InitStructure.GPIO_Pin = CCD_AO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(CCD_AO_PORT, &GPIO_InitStructure);	

	ADC_DeInit(ADC3);  //复位ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC3, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC3, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC3);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC3));	//等待复位校准结束
	
	ADC_StartCalibration(ADC3);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC3));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
}


				  
//获得ADC值
//ch:通道值 0~3
u16 ccd_Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_28Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC3, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC3);	//返回最近一次ADC1规则组的转换结果
}


/////////////////////算法部分

void ccd_change()
{
    int i,j= 0;
    static int first,fl;
    static uint16_t max_value,min_value;
    max_value =ccd_data[0];
    for(i = 5; i < 123; i++)                               
    {
        if(max_value <= ccd_data[i])
        {
            max_value = ccd_data[i];
        }
    }
    min_value =  ccd_data[0];                    
    
    for(i = 5; i < 123; i++)                              
    {
        if(min_value >= ccd_data[i])
        {
            min_value = ccd_data[i];
        }
    }
    
    ccd_count = (max_value + min_value) / 2;//计算出本次中线提取的阈值
    for(i = 5;i < 118; i++)////////二值化
    {
        if(ccd_data[i]>ccd_count)
        {
           ccd_two[i]=0xFFF;
        }
        else ccd_two[i]=0x000;
    }
             for(i = 5;i < 118; i++) ////////////////计算跳变沿                
             {
               
                if(ccd_two[i]==0xFFF&&ccd_two[i+1]==0xFFF&&ccd_two[i+2]==0xFFF&&ccd_two[i+3]==0x000&&ccd_two[i+4]==0x000&&ccd_two[i+5]==0x000)
                {
                 first=i;//mid,first,fl=0;
                 break;
                } 
              }   
             for(i = 117;i >4; i--) 
              {
                if(ccd_two[i]==0xFFF&&ccd_two[i-1]==0xFFF&&ccd_two[i-2]==0xFFF&&ccd_two[i-3]==0x000&&ccd_two[i-4]==0x000&&ccd_two[i-5]==0x000)
                 {
                       fl=i;                      
                       break;                    
                 }  
              }                
           temp_dir=(first+fl)/2-64;
              
}






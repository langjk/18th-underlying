/*********************************************************************************************************************
					TSL1401���߶��壺
					------------------------------------ 
					    ģ��ܽ�       	��Ƭ���ܽ�
					    CCD_AO	   		F6   :ADC3  ch4
					    CCD_CLK	   		F1
					    CCD_SI	   		F3
					------------------------------------ 
 ********************************************************************************************************************/



#include "sys.h"





uint16_t ccd_data[128];    //CCD����
uint16_t ccd_two[128];
int Line_mid;
int dir_error;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      TSL1401����CCD��ʼ��
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
//  @brief      TSL1401����CCD���ݲɼ�
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				��isr.c�����ȴ�����Ӧ���жϺ�����Ȼ����øú���(֮�����������жϱ�־λ)
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
	//��ʱ������һ���㣨0�㣩
	for(i=0;i<20;i++)
	{
		delay_us(1);
	}
	//*ccd_data=Normalized_U8(ccd_Get_Adc(CCD_AO_ADC_chn));//��ȡ��ȡ8λ
	ccd_data[0]=ccd_Get_Adc(CCD_AO_ADC_chn);

	CCD_CLK(0); 
	
	for(i=1;i<128;i++)//2~128����
	{
	    delay_us(1);
		CCD_CLK(1);
		 //*ccd_data=Normalized_U8(ccd_Get_Adc(CCD_AO_ADC_chn));//��ȡ��ȡ8λ
		ccd_data[i]=ccd_Get_Adc(CCD_AO_ADC_chn); 
	    CCD_CLK(0);
	}
	//�����е�129��ʱ�ӣ�ʹ�ڲ����ع�λ�������´β�����
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

	RCC_APB2PeriphClockCmd(CCD_AO_CLK |CCD_AO_ADC	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
                       
	GPIO_InitStructure.GPIO_Pin = CCD_AO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(CCD_AO_PORT, &GPIO_InitStructure);	

	ADC_DeInit(ADC3);  //��λADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC3, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC3, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC3);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC3));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC3);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC3));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
}


				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 ccd_Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_28Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC3, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC3);	//�������һ��ADC1�������ת�����
}


/////////////////////�㷨����

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
    
    ccd_count = (max_value + min_value) / 2;//���������������ȡ����ֵ
    for(i = 5;i < 118; i++)////////��ֵ��
    {
        if(ccd_data[i]>ccd_count)
        {
           ccd_two[i]=0xFFF;
        }
        else ccd_two[i]=0x000;
    }
             for(i = 5;i < 118; i++) ////////////////����������                
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






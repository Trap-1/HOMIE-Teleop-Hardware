 #include "adc.h"
 #include "delay.h"

///* Right hand */
int muxChannel[16][4]=
{
	{0,0,0,0}, //channel 0

	{1,0,0,0}, //channel 1

	{0,1,0,0}, //channel 2

	{1,1,0,0}, //channel 3

	{0,0,1,0}, //channel 4

	{1,0,1,0}, //channel 5

	{0,1,1,0}, //channel 6

	{1,1,1,0}, //channel 7

	{0,0,0,1}, //channel 8

	{1,0,0,1}, //channel 9

	{0,1,0,1}, //channel 10

	{1,1,0,1}, //channel 11

	{0,0,1,1}, //channel 12

	{1,0,1,1}, //channel 13

	{0,1,1,1}, //channel 14
};
	

/* Left Hand */
//int muxChannel[16][4]=
//{
//	{0,0,1,1}, //channel 12

//	{1,0,1,1}, //channel 13

//	{0,1,1,1}, //channel 14

//	{1,0,0,1}, //channel 9

//	{0,1,0,1}, //channel 10

//	{1,1,0,1}, //channel 11

//	{0,1,1,0}, //channel 6

//	{1,1,1,0}, //channel 7

//	{0,0,0,1}, //channel 8

//	{1,1,0,0}, //channel 3

//	{0,0,1,0}, //channel 4

//	{1,0,1,0}, //channel 5

//	{0,0,0,0}, //channel 0

//	{1,0,0,0}, //channel 1

//	{0,1,0,0}, //channel 2
//};
		   							   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   						


	//PA5 Analog input                   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	ADC_DeInit(ADC1);  //Reset ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;					
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;								
	ADC_Init(ADC1, &ADC_InitStructure);										 

  
	ADC_Cmd(ADC1, ENABLE);			
	
	ADC_ResetCalibration(ADC1);	
	while(ADC_GetResetCalibrationStatus(ADC1));	
	
	ADC_StartCalibration(ADC1);	
	while(ADC_GetCalibrationStatus(ADC1));	 		
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
}



//Get ADC data
u16 Get_Adc(u8 ch)   
{
  //239.5
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	 			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));

	return ADC_GetConversionValue(ADC1);	
}

 
//Get average data
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	 




























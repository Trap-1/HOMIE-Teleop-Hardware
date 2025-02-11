//////////////////////////////////////////////////////////////////////////////////	 
//  文 件 名   : main.c
//  版 本 号   : v1.0
//  作    者   : 贾飞宇
//  生成日期   : 2024-10-31
//  功能描述   :	
//              ----------------------------------------------------------------
//******************************************************************************/

#include "sys.h"
#include "led.h"
#include "adc.h"
#include "key.h"
#include "oled.h"


/**************手指参数*********************/
u16 num1 = 0;
u16 num2 = 0;
u16 num3 = 0;

// 用于标识数据包的起始和结束符
#define START_BYTE 0xFE   	// 起始标志
#define END_BYTE   0xFF	   	// 结束标志

int main(void)
{
	/**************初始化********************/
	delay_init();
	LED = 0;
	LED_Init();						//LED初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);			//串口1初始化	   ！！！！！！串口1中断没写完
	Adc_Init();						//ADC初始化
//	OLED1_Init();				 	//初始化OLED1
//	OLED1_Clear(); 				//清空OLED1
	KEY_Init();						//按键初始化

	/**************OLED初始名词显示********************/
//	OLED1_ShowString(0,1,"Pedal-1:",12);
//	OLED1_ShowString(0,2,"Pedal-2:",12);
//	OLED1_ShowString(0,3,"Pedal-3:",12);
//	OLED1_ShowString(0,4,"LR_Mode:",12);
//	OLED1_ShowString(0,5,"FB_Mode:",12);
	
	
	while(1)
	{
		/**************按键 / 踏板按键开始********************/
		Scan();		
		// ---------------踏板按键 -------------------------------
		if(LR_mode == 0)
		{
			LED = 1;
		}
		else LED = 0;
		//-------------------------------------
		
		/**************ADC采集********************/
		num1=Get_Adc(ADC_Channel_1);
		num2=Get_Adc(ADC_Channel_4);
		num3=Get_Adc(ADC_Channel_5);
		
		num1 = (uint8_t)(num1 >> 4);	// 右移4位，数据降到0-255范围
		num2 = (uint8_t)(num2 >> 4);
		num3 = (uint8_t)(num3 >> 4);
		
		
		/**************数据包********************/
		// 起始标志
		Usart_SendData(USART1, START_BYTE); 
		while (Usart_Tx_End(USART1) == 0);  

		// 发送	数据
		Usart_SendData(USART1, num1);  
		while (Usart_Tx_End(USART1) == 0);
		Usart_SendData(USART1, num2);  
		while (Usart_Tx_End(USART1) == 0);
		Usart_SendData(USART1, num3);  
		while (Usart_Tx_End(USART1) == 0); 
		Usart_SendData(USART1, LR_mode);  
		while (Usart_Tx_End(USART1) == 0);
		Usart_SendData(USART1, FB_mode);  
		while (Usart_Tx_End(USART1) == 0); 			
		
		// 结束符
		Usart_SendData(USART1, END_BYTE); 
		while (Usart_Tx_End(USART1) == 0);
		
		
		/*************OLED显示********************/
//		OLED1_ShowString(70,1,"     ",12);			
//		OLED1_ShowString(70,2,"     ",12);
//		OLED1_ShowString(70,3,"     ",12);
//		OLED1_ShowString(70,4,"     ",12);
//		OLED1_ShowString(70,5,"     ",12);

//		OLED1_ShowNum(70,1,num1,4,12);	
//		OLED1_ShowNum(70,2,num2,4,12);
//		OLED1_ShowNum(70,3,num3,4,12);
//		OLED1_ShowNum(70,4,LR_mode,4,12);
//		OLED1_ShowNum(70,5,FB_mode,4,12);				
	}
}



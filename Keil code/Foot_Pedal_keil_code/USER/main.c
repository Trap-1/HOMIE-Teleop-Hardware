//////////////////////////////////////////////////////////////////////////////////	 
//  �� �� ��   : main.c
//  �� �� ��   : v1.0
//  ��    ��   : �ַ���
//  ��������   : 2024-10-31
//  ��������   :	
//              ----------------------------------------------------------------
//******************************************************************************/

#include "sys.h"
#include "led.h"
#include "adc.h"
#include "key.h"
#include "oled.h"


/**************��ָ����*********************/
u16 num1 = 0;
u16 num2 = 0;
u16 num3 = 0;

// ���ڱ�ʶ���ݰ�����ʼ�ͽ�����
#define START_BYTE 0xFE   	// ��ʼ��־
#define END_BYTE   0xFF	   	// ������־

int main(void)
{
	/**************��ʼ��********************/
	delay_init();
	LED = 0;
	LED_Init();						//LED��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);			//����1��ʼ��	   ����������������1�ж�ûд��
	Adc_Init();						//ADC��ʼ��
//	OLED1_Init();				 	//��ʼ��OLED1
//	OLED1_Clear(); 				//���OLED1
	KEY_Init();						//������ʼ��

	/**************OLED��ʼ������ʾ********************/
//	OLED1_ShowString(0,1,"Pedal-1:",12);
//	OLED1_ShowString(0,2,"Pedal-2:",12);
//	OLED1_ShowString(0,3,"Pedal-3:",12);
//	OLED1_ShowString(0,4,"LR_Mode:",12);
//	OLED1_ShowString(0,5,"FB_Mode:",12);
	
	
	while(1)
	{
		/**************���� / ̤�尴����ʼ********************/
		Scan();		
		// ---------------̤�尴�� -------------------------------
		if(LR_mode == 0)
		{
			LED = 1;
		}
		else LED = 0;
		//-------------------------------------
		
		/**************ADC�ɼ�********************/
		num1=Get_Adc(ADC_Channel_1);
		num2=Get_Adc(ADC_Channel_4);
		num3=Get_Adc(ADC_Channel_5);
		
		num1 = (uint8_t)(num1 >> 4);	// ����4λ�����ݽ���0-255��Χ
		num2 = (uint8_t)(num2 >> 4);
		num3 = (uint8_t)(num3 >> 4);
		
		
		/**************���ݰ�********************/
		// ��ʼ��־
		Usart_SendData(USART1, START_BYTE); 
		while (Usart_Tx_End(USART1) == 0);  

		// ����	����
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
		
		// ������
		Usart_SendData(USART1, END_BYTE); 
		while (Usart_Tx_End(USART1) == 0);
		
		
		/*************OLED��ʾ********************/
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



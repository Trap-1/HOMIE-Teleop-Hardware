//////////////////////////////////////////////////////////////////////////////////	 
//  File name  : Glove_keil_code
//  version    : v3.0
//  Author     : Feiyu Jia
//  Data       : 2024-10-31
//              ----------------------------------------------------------------
//******************************************************************************/

#include "sys.h"
#include "led.h"
#include "adc.h"
#include "key.h"
#include "channel.h"
#include "stdint.h"
#define DoF 15

#define MAX_CHANNELS DoF
u16 adc_data[MAX_CHANNELS];

// Data packet
#define START_BYTE 0x01    // Start
#define END_BYTE   0x02	   // End


/**************Figner config*********************/
u16 adc[DoF] ;

u8 Trap = 0; 


///* Hand config */
extern int muxChannel[16][4];

int main(void)
{
	/**************Channel********************/
	int j = 0;
	
	// delay_init();
	LED_Init();						//LED
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);			//Usart1
	Adc_Init();						//ADC
	Channel_Init();				
	KEY_Init();						//Key

	while(1)
	{
		// Read ADC
		for(j = 0; j < MAX_CHANNELS; j++)
		{
				s0 = muxChannel[j][0];
				s1 = muxChannel[j][1];
				s2 = muxChannel[j][2];
				s3 = muxChannel[j][3];				
				adc_data[j] = Get_Adc(ADC_Channel_5);  
				adc_data[j] = (uint8_t)(adc_data[j] >> 4); // Move 4 bits to the right, the data drops to the range of 0-255
		}

		// Add Start byte
		Usart_SendData(USART1, START_BYTE); 
		while (Usart_Tx_End(USART1) == 0);  

		// Send data
		for(j = 0; j < MAX_CHANNELS; j++)
		{
				Usart_SendData(USART1, adc_data[j]);  
				while (Usart_Tx_End(USART1) == 0);    // range of 0-255
//				Usart_SendData(USART1, adc_data[j] >> 8);  
//				while (Usart_Tx_End(USART1) == 0);  // range of 0-4095		
		}

		// Add END byte
		Usart_SendData(USART1, END_BYTE); 
		while (Usart_Tx_End(USART1) == 0);  
	}
}




#include "key.h"

u8 Ctr = 0;

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	          
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         
  GPIO_Init(GPIOC, &GPIO_InitStructure);					      
	
}

void Scan(void)
{
	if(KEY1 == 0)
	{
		delay_ms(10);
		if(KEY1 == 0)
		{
			Ctr = !Ctr;		
			while(KEY1 != 1);		
		}
	}
	
}	


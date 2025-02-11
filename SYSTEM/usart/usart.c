#include "sys.h"
#include "usart.h"	  
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					  
#endif
	  
 
void Usart_SendData(USART_TypeDef* USARTx, u8 Data);
u8 Usart_Tx_End(USART_TypeDef* USARTx);
#if 1
#pragma import(__use_no_semihosting)             
                
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;
 
void _sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
#if EN_USART1_RX   
 	
u8 USART_RX_BUF[USART_REC_LEN];    

u16 USART_RX_STA=0;      
  
void uart_init(u32 bound)
{

  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	//Usart1 NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
  
  //USART 
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	USART_Init(USART1, &USART_InitStructure); 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);                   

}

void Usart_SendData(USART_TypeDef* USARTx, u8 Data)
{
	USARTx->DR = (Data & (u8)0xFF);
	while(!Usart_Tx_End(USARTx));
}

u8 Usart_Tx_End(USART_TypeDef* USARTx)
{
	if((u8)(USARTx->SR&(1<<6)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
  
}

void USART1_IRQHandler(void)                
	{
	u8 Res;
#ifdef OS_TICKS_PER_SEC	 	
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
		{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	
		
		if((USART_RX_STA&0x8000)==0)
			{
			if(USART_RX_STA&0x4000)
				{
				if(Res!=0x0a)USART_RX_STA=0;
				else USART_RX_STA|=0x8000;	
				}
			else 
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0; 
					}		 
				}
			}   		 
     } 
#ifdef OS_TICKS_PER_SEC	
	OSIntExit();  											 
#endif
} 
#endif	


void USART3_SendData(u8 data)
{
	while((USART3->SR & 0X40) == 0);
	USART3->DR = data;
}

void USART3_SendString(u8 *DAT, u8 len)
{
	u8 i;
	for(i = 0; i < len; i++)
	{
		USART3_SendData(*DAT++);
	}
}

#if EN_USART3_RX   

u8 USART3_RX_BUF[USART3_REC_LEN];    

u16 USART3_RX_STA = 0;    

 void USART3_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	//USART3_TX   GPIOB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//USART3_RX	  GPIOB.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//USART3 NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	

	//USART 
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	USART_Init(USART3, &USART_InitStructure); 
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);                  

	TIM3_Int_Init(99, 7199);	
	USART3_RX_STA = 0;		
	TIM_Cmd(TIM3, DISABLE);		
}

void USART3_IRQHandler(void)               
{
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		Res = USART_ReceiveData(USART3);	
		if((USART3_RX_STA & 0x8000) == 0)
		{
			if(USART3_RX_STA < USART3_REC_LEN)	
			{
				TIM_SetCounter(TIM3, 0); 
				if(USART3_RX_STA == 0) 				
				{
					TIM_Cmd(TIM3, ENABLE);
				}
				USART3_RX_BUF[USART3_RX_STA++] = Res;	
			}
			else
			{
				USART3_RX_STA |= 1 << 15;			
			}
		}
	}
}
#endif


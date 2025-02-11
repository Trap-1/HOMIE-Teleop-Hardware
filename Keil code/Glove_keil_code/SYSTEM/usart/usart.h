#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  			200  	
#define EN_USART1_RX 			1		

#define USART3_REC_LEN  			200  	
#define EN_USART3_RX 			1		

extern u8  USART_RX_BUF[USART_REC_LEN]; 
extern u16 USART_RX_STA;         		

extern u8  USART3_RX_BUF[USART3_REC_LEN]; 
extern u16 USART3_RX_STA;         		


void uart_init(u32 bound);
void Usart_SendData(USART_TypeDef* USARTx, u8 Data);
u8 Usart_Tx_End(USART_TypeDef* USARTx);

void USART3_SendString(u8 *DAT,u8 len);
void USART3_SendData(u8 data);
void USART3_Init(u32 bound);
#endif



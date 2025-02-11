#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
#include "usart.h"
#include "delay.h"

#define KEY1 PCin(13)


extern u8 Ctr;
extern u8 Ped_mode;

void KEY_Init(void);          

u8 click_N_Double (u8 time);  
u8 click(void);               
u8 Long_Press(void);           
void Scan(void);


#endif  


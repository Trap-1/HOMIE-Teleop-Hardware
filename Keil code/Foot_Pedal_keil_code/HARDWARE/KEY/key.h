#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"

#define KEY1 PAin(12)
#define Pedal_key_1 PBin(3)
#define Pedal_key_2 PBin(1)

extern u8 Ctr; 								// KEY ����
extern u8 LR_mode;						// Left or Rignt
extern u8 FB_mode;						// Front or Back

void KEY_Init(void);          //������ʼ��

u8 click_N_Double (u8 time);  //��������ɨ���˫������ɨ��
u8 click(void);               //��������ɨ��
u8 Long_Press(void);          //����ɨ�� 

void Scan(void);


#endif  


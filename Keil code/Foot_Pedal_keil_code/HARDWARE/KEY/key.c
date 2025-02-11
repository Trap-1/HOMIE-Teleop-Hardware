#include "key.h"
/**************************************************************************
Function: Key initialization
Input   : none
Output  : none
�������ܣ�������ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/

u8 Ctr = 0;
u8 LR_mode = 1;
u8 FB_mode = 1;

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��PA�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	          //�˿����ã� PA12
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��PA�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_3;	//�˿����ã� PB1, PB3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA
}

void Scan(void)
{
	if(KEY1 == 0)
	{
		delay_ms(10);
		if(KEY1 == 0)
		{
			Ctr = !Ctr;						// ������������(�� & �أ�
			while(KEY1 !=1);		
		}
	}
	if(Pedal_key_1 == 0)
	{
		delay_ms(10);
		if(Pedal_key_1 == 0)
		{
			LR_mode = !LR_mode;		// ���ҷ��򰴼�̤���������(�� & �أ�
			while(Pedal_key_1 !=1);		
		}
	}
	if(Pedal_key_2 == 0)
	{
		delay_ms(10);
		if(Pedal_key_2 == 0)
		{
			FB_mode = !FB_mode;		// ǰ���򰴼�̤���������(�� & �أ�
			while(Pedal_key_2 !=1);		
		}
	}
	
}	


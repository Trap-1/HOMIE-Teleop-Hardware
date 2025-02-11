#include "key.h"
/**************************************************************************
Function: Key initialization
Input   : none
Output  : none
函数功能：按键初始化
入口参数：无
返回  值：无 
**************************************************************************/

u8 Ctr = 0;
u8 LR_mode = 1;
u8 FB_mode = 1;

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	          //端口配置： PA12
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_3;	//端口配置： PB1, PB3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA
}

void Scan(void)
{
	if(KEY1 == 0)
	{
		delay_ms(10);
		if(KEY1 == 0)
		{
			Ctr = !Ctr;						// 按键操作函数(开 & 关）
			while(KEY1 !=1);		
		}
	}
	if(Pedal_key_1 == 0)
	{
		delay_ms(10);
		if(Pedal_key_1 == 0)
		{
			LR_mode = !LR_mode;		// 左右方向按键踏板操作函数(开 & 关）
			while(Pedal_key_1 !=1);		
		}
	}
	if(Pedal_key_2 == 0)
	{
		delay_ms(10);
		if(Pedal_key_2 == 0)
		{
			FB_mode = !FB_mode;		// 前后方向按键踏板操作函数(开 & 关）
			while(Pedal_key_2 !=1);		
		}
	}
	
}	


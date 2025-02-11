
#ifndef __OLED1_H
#define __OLED1_H			  	 
#include "sys.h"
#include "stdlib.h"	    	
#define OLED1_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	  


//-----------------OLED1 IIC端口定义----------------  					   

#define OLED1_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//SCL
#define OLED1_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

#define OLED1_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_6)//SDA
#define OLED1_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_6)

 		     
#define OLED1_CMD  0	//写命令
#define OLED1_DATA 1	//写数据



//OLED1控制用函数
void OLED1_WR_Byte(unsigned dat,unsigned cmd);  
void OLED1_Display_On(void);
void OLED1_Display_Off(void);	   							   		    
void OLED1_Init(void);
void OLED1_Clear(void);
void OLED1_DrawPoint(u8 x,u8 y,u8 t);
void OLED1_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED1_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED1_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED1_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED1_Set_Pos(unsigned char x, unsigned char y);
void OLED1_ShowCHinese(u8 x,u8 y,u8 no);
void OLED1_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture1(unsigned char fill_Data);
void Picture();
void IIC1_Start();
void IIC1_Stop();
void Write_IIC1_Command(unsigned char IIC_Command);
void Write_IIC1_Data(unsigned char IIC_Data);
void Write_IIC1_Byte(unsigned char IIC_Byte);

void IIC1_Wait_Ack();
#endif  
	 

//////////////////////////////////////////////////////////////////////////////////
#ifndef __OLED2_H
#define __OLED2_H			
#define OLED2_MODE 0


//-----------------OLED2 IIC端口定义----------------  					   

#define OLED2_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)//SCL
#define OLED2_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define OLED2_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_4)//SDA
#define OLED2_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_4)

 		     
#define OLED2_CMD  0	//写命令
#define OLED2_DATA 1	//写数据

void OLED2_WR_Byte(unsigned dat,unsigned cmd);  
void OLED2_Display_On(void);
void OLED2_Display_Off(void);	   							   		    
void OLED2_Init(void);
void OLED2_Clear(void);
void OLED2_DrawPoint(u8 x,u8 y,u8 t);
void OLED2_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED2_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED2_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED2_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
void OLED2_Set_Pos(unsigned char x, unsigned char y);
void OLED2_ShowCHinese(u8 x,u8 y,u8 no);
void OLED2_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
//void Delay_50ms(unsigned int Del_50ms);
//void Delay_1ms(unsigned int Del_1ms);
void fill_picture2(unsigned char fill_Data);
void Picture();
void IIC2_Start();
void IIC2_Stop();
void Write_IIC2_Command(unsigned char IIC_Command);
void Write_IIC2_Data(unsigned char IIC_Data);
void Write_IIC2_Byte(unsigned char IIC_Byte);

//void IIC_Wait_Ack();
#endif



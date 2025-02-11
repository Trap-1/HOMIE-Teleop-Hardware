//////////////////////////////////////////////////////////////////////////////////	 
//  Àµ√˜: 
//			OLED1
//       ----------------------------------------------------------------
//       GND   µÁ‘¥µÿ
//       VCC   Ω”5VªÚ3.3vµÁ‘¥
//       SCL   Ω”PA7£®SCL£©
//       SDA   Ω”PA6£®SDA£©            
//       ----------------------------------------------------------------
//
//			OLED2
//       ----------------------------------------------------------------
//       GND   µÁ‘¥µÿ
//       VCC   Ω”5VªÚ3.3vµÁ‘¥
//       SCL   Ω”PA7£®SCL£©
//       SDA   Ω”PA6£®SDA£©            
//       ----------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////£

#include "OLED.h"
#include "stdlib.h"
#include "OLEDfont.h"  	 
#include "delay.h"
//OLEDµƒœ‘¥Ê
//¥Ê∑≈∏Ò Ω»Áœ¬.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   


/**********************************************
//IIC Start
**********************************************/
void IIC1_Start()
{

	OLED1_SCLK_Set() ;
	OLED1_SDIN_Set();
	OLED1_SDIN_Clr();
	OLED1_SCLK_Clr();
}

void IIC2_Start()
{

	OLED2_SCLK_Set() ;
	OLED2_SDIN_Set();
	OLED2_SDIN_Clr();
	OLED2_SCLK_Clr();
}


/**********************************************
//IIC Stop
**********************************************/
void IIC1_Stop()
{
OLED1_SCLK_Set() ;
//	OLED1_SCLK_Clr();
	OLED1_SDIN_Clr();
	OLED1_SDIN_Set();	
}

void IIC2_Stop()
{
OLED2_SCLK_Set() ;
//	OLED1_SCLK_Clr();
	OLED2_SDIN_Clr();
	OLED2_SDIN_Set();	
}


void IIC1_Wait_Ack()
{

	//GPIOB->CRH &= 0XFFF0FFFF;	//…Ë÷√PB12Œ™…œ¿≠ ‰»Îƒ£ Ω
	//GPIOB->CRH |= 0x00080000;
//	OLED1_SDA = 1;
//	delay_us(1);
	//OLED1_SCL = 1;
	//delay_us(50000);
/*	while(1)
	{
		if(!OLED1_SDA)				//≈–∂œ «∑ÒΩ” ’µΩOLED1 ”¶¥–≈∫≈
		{
			//GPIOB->CRH &= 0XFFF0FFFF;	//…Ë÷√PB12Œ™Õ®”√Õ∆√‚ ‰≥ˆƒ£ Ω
			//GPIOB->CRH |= 0x00030000;
			return;
		}
	}
*/
	OLED1_SCLK_Set() ;
	OLED1_SCLK_Clr();
}

void IIC2_Wait_Ack()
{
	OLED2_SCLK_Set() ;
	OLED2_SCLK_Clr();
}


/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC1_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED1_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED1_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED1_SDIN_Set();}
		else OLED1_SDIN_Clr();
			da=da<<1;
		OLED1_SCLK_Set();
		OLED1_SCLK_Clr();
		}
}

void Write_IIC2_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED2_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED1_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED2_SDIN_Set();}
		else OLED2_SDIN_Clr();
			da=da<<1;
		OLED2_SCLK_Set();
		OLED2_SCLK_Clr();
		}
}

/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC1_Command(unsigned char IIC_Command)
{
   IIC1_Start();
   Write_IIC1_Byte(0x78);            //Slave address,SA0=0
	IIC1_Wait_Ack();	
   Write_IIC1_Byte(0x00);			//write command
	IIC1_Wait_Ack();	
   Write_IIC1_Byte(IIC_Command); 
	IIC1_Wait_Ack();	
   IIC1_Stop();
}

void Write_IIC2_Command(unsigned char IIC_Command)
{
   IIC2_Start();
   Write_IIC2_Byte(0x78);            //Slave address,SA0=0
	IIC2_Wait_Ack();	
   Write_IIC2_Byte(0x00);			//write command
	IIC2_Wait_Ack();	
   Write_IIC2_Byte(IIC_Command); 
	IIC2_Wait_Ack();	
   IIC2_Stop();
}

/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC1_Data(unsigned char IIC_Data)
{
   IIC1_Start();
   Write_IIC1_Byte(0x78);			//D/C#=0; R/W#=0
	IIC1_Wait_Ack();	
   Write_IIC1_Byte(0x40);			//write data
	IIC1_Wait_Ack();	
   Write_IIC1_Byte(IIC_Data);
	IIC1_Wait_Ack();	
   IIC1_Stop();
}
void OLED1_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		Write_IIC1_Data(dat); 
	}
	else 
	{
		Write_IIC1_Command(dat);	
	}
}

void Write_IIC2_Data(unsigned char IIC_Data)
{
   IIC2_Start();
   Write_IIC2_Byte(0x78);			//D/C#=0; R/W#=0
	IIC2_Wait_Ack();	
   Write_IIC2_Byte(0x40);			//write data
	IIC2_Wait_Ack();	
   Write_IIC2_Byte(IIC_Data);
	IIC2_Wait_Ack();	
   IIC2_Stop();
}
void OLED2_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		Write_IIC2_Data(dat); 
	}
	else 
	{
		Write_IIC2_Command(dat);	
	}
}


/********************************************
// fill_Picture
********************************************/
void fill_picture1(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED1_WR_Byte(0xb0+m,0);		//page0-page1
		OLED1_WR_Byte(0x00,0);		//low column start address
		OLED1_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED1_WR_Byte(fill_Data,1);
			}
	}
}
void fill_picture2(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED2_WR_Byte(0xb0+m,0);		//page0-page1
		OLED2_WR_Byte(0x00,0);		//low column start address
		OLED2_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED2_WR_Byte(fill_Data,1);
			}
	}
}


/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

//◊¯±Í…Ë÷√

void OLED1_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED1_WR_Byte(0xb0+y,OLED1_CMD);
	OLED1_WR_Byte(((x&0xf0)>>4)|0x10,OLED1_CMD);
	OLED1_WR_Byte((x&0x0f),OLED1_CMD); 
}   

void OLED2_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED2_WR_Byte(0xb0+y,OLED2_CMD);
	OLED2_WR_Byte(((x&0xf0)>>4)|0x10,OLED2_CMD);
	OLED2_WR_Byte((x&0x0f),OLED2_CMD); 
} 


//ø™∆ÙOLED1œ‘ æ    
void OLED1_Display_On(void)
{
	OLED1_WR_Byte(0X8D,OLED1_CMD);  //SET DCDC√¸¡Ó
	OLED1_WR_Byte(0X14,OLED1_CMD);  //DCDC ON
	OLED1_WR_Byte(0XAF,OLED1_CMD);  //DISPLAY ON
}
void OLED2_Display_On(void)
{
	OLED2_WR_Byte(0X8D,OLED2_CMD);  //SET DCDC√¸¡Ó
	OLED2_WR_Byte(0X14,OLED2_CMD);  //DCDC ON
	OLED2_WR_Byte(0XAF,OLED2_CMD);  //DISPLAY ON
}

//πÿ±’OLED1œ‘ æ     
void OLED1_Display_Off(void)
{
	OLED1_WR_Byte(0X8D,OLED1_CMD);  //SET DCDC√¸¡Ó
	OLED1_WR_Byte(0X10,OLED1_CMD);  //DCDC OFF
	OLED1_WR_Byte(0XAE,OLED1_CMD);  //DISPLAY OFF
}
void OLED2_Display_Off(void)
{
	OLED2_WR_Byte(0X8D,OLED2_CMD);  //SET DCDC√¸¡Ó
	OLED2_WR_Byte(0X10,OLED2_CMD);  //DCDC OFF
	OLED2_WR_Byte(0XAE,OLED2_CMD);  //DISPLAY OFF
}		   			 

//«Â∆¡∫Ø ˝,«ÂÕÍ∆¡,’˚∏ˆ∆¡ƒª «∫⁄…´µƒ!∫Õ√ªµ„¡¡“ª—˘!!!	  
void OLED1_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED1_WR_Byte (0xb0+i,OLED1_CMD);    //…Ë÷√“≥µÿ÷∑£®0~7£©
		OLED1_WR_Byte (0x00,OLED1_CMD);      //…Ë÷√œ‘ æŒª÷√°™¡–µÕµÿ÷∑
		OLED1_WR_Byte (0x10,OLED1_CMD);      //…Ë÷√œ‘ æŒª÷√°™¡–∏ﬂµÿ÷∑   
		for(n=0;n<128;n++)OLED1_WR_Byte(0,OLED1_DATA); 
	} //∏¸–¬œ‘ æ
}
void OLED2_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED2_WR_Byte (0xb0+i,OLED2_CMD);    //…Ë÷√“≥µÿ÷∑£®0~7£©
		OLED2_WR_Byte (0x00,OLED2_CMD);      //…Ë÷√œ‘ æŒª÷√°™¡–µÕµÿ÷∑
		OLED2_WR_Byte (0x10,OLED2_CMD);      //…Ë÷√œ‘ æŒª÷√°™¡–∏ﬂµÿ÷∑   
		for(n=0;n<128;n++)OLED2_WR_Byte(0,OLED2_DATA); 
	} //∏¸–¬œ‘ æ
}

void OLED1_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED1_WR_Byte (0xb0+i,OLED1_CMD);    //…Ë÷√“≥µÿ÷∑£®0~7£©
		OLED1_WR_Byte (0x00,OLED1_CMD);      //…Ë÷√œ‘ æŒª÷√°™¡–µÕµÿ÷∑
		OLED1_WR_Byte (0x10,OLED1_CMD);      //…Ë÷√œ‘ æŒª÷√°™¡–∏ﬂµÿ÷∑   
		for(n=0;n<128;n++)OLED1_WR_Byte(1,OLED1_DATA); 
	} //∏¸–¬œ‘ æ
}

void OLED2_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED2_WR_Byte (0xb0+i,OLED2_CMD);    //…Ë÷√“≥µÿ÷∑£®0~7£©
		OLED2_WR_Byte (0x00,OLED2_CMD);      //…Ë÷√œ‘ æŒª÷√°™¡–µÕµÿ÷∑
		OLED2_WR_Byte (0x10,OLED2_CMD);      //…Ë÷√œ‘ æŒª÷√°™¡–∏ﬂµÿ÷∑   
		for(n=0;n<128;n++)OLED2_WR_Byte(1,OLED2_DATA); 
	} //∏¸–¬œ‘ æ
}


//‘⁄÷∏∂®Œª÷√œ‘ æ“ª∏ˆ◊÷∑˚,∞¸¿®≤ø∑÷◊÷∑˚
//x:0~127
//y:0~63
//mode:0,∑¥∞◊œ‘ æ;1,’˝≥£œ‘ æ				 
//size:—°‘Ò◊÷ÃÂ 16/12 
void OLED1_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//µ√µΩ∆´“∆∫Ûµƒ÷µ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED1_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED1_WR_Byte(F8X16[c*16+i],OLED1_DATA);
			OLED1_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED1_WR_Byte(F8X16[c*16+i+8],OLED1_DATA);
			}
			else {	
				OLED1_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED1_WR_Byte(F6x8[c][i],OLED1_DATA);
				
			}
}
//m^n∫Ø ˝
u32 OLED1_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//œ‘ æ2∏ˆ ˝◊÷
//x,y :∆µ„◊¯±Í	 
//len : ˝◊÷µƒŒª ˝
//size:◊÷ÃÂ¥Û–°
//mode:ƒ£ Ω	0,ÃÓ≥‰ƒ£ Ω;1,µ˛º”ƒ£ Ω
//num: ˝÷µ(0~4294967295);	 		  
void OLED1_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/OLED1_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED1_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED1_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

//œ‘ æ ˝◊÷(¥¯∑˚∫≈£©
void OLED1_ShowSignleNum(u8 x,u8 y, int32_t num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;
	if(num <= 0)
	{
		num = -num;
		OLED1_ShowString(x-5, y, "-",size2);
	}	
	else
	{
		OLED1_ShowString(x-5, y, "+",size2);
	}	
	for(t=0;t<len;t++)
	{
		temp=(num/OLED1_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED1_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED1_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

//œ‘ æ“ª∏ˆ◊÷∑˚∫≈¥Æ
void OLED1_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED1_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//œ‘ æ∫∫◊÷
void OLED1_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED1_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED1_WR_Byte(Hzk[2*no][t],OLED1_DATA);
				adder+=1;
     }	
		OLED1_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED1_WR_Byte(Hzk[2*no+1][t],OLED1_DATA);
				adder+=1;
      }					
}
/***********π¶ƒ‹√Ë ˆ£∫œ‘ æœ‘ æBMPÕº∆¨128°¡64∆ ºµ„◊¯±Í(x,y),xµƒ∑∂Œß0°´127£¨yŒ™“≥µƒ∑∂Œß0°´7*****************/
void OLED1_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED1_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED1_WR_Byte(BMP[j++],OLED1_DATA);	    	
	    }
	}
} 

void OLED2_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED2_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED2_WR_Byte(BMP[j++],OLED2_DATA);	    	
	    }
	}
} 



//≥ı ºªØSSD1306					    
void OLED1_Init(void)
{ 		 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 // πƒ‹A∂Àø⁄ ±÷”
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //Õ∆ÕÏ ‰≥ˆ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//ÀŸ∂»50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //≥ı ºªØGPIOD3,6
 	GPIO_SetBits(GPIOA,GPIO_Pin_7|GPIO_Pin_6);	


delay_ms(800);
OLED1_WR_Byte(0xAE,OLED1_CMD);//--display off
	OLED1_WR_Byte(0x00,OLED1_CMD);//---set low column address
	OLED1_WR_Byte(0x10,OLED1_CMD);//---set high column address
	OLED1_WR_Byte(0x40,OLED1_CMD);//--set start line address  
	OLED1_WR_Byte(0xB0,OLED1_CMD);//--set page address
	OLED1_WR_Byte(0x81,OLED1_CMD); // contract control
	OLED1_WR_Byte(0xFF,OLED1_CMD);//--128   
	OLED1_WR_Byte(0xA1,OLED1_CMD);//set segment remap 
	OLED1_WR_Byte(0xA6,OLED1_CMD);//--normal / reverse
	OLED1_WR_Byte(0xA8,OLED1_CMD);//--set multiplex ratio(1 to 64)
	OLED1_WR_Byte(0x3F,OLED1_CMD);//--1/32 duty
	OLED1_WR_Byte(0xC8,OLED1_CMD);//Com scan direction
	OLED1_WR_Byte(0xD3,OLED1_CMD);//-set display offset
	OLED1_WR_Byte(0x00,OLED1_CMD);//
	
	OLED1_WR_Byte(0xD5,OLED1_CMD);//set osc division
	OLED1_WR_Byte(0x80,OLED1_CMD);//
	
	OLED1_WR_Byte(0xD8,OLED1_CMD);//set area color mode off
	OLED1_WR_Byte(0x05,OLED1_CMD);//
	
	OLED1_WR_Byte(0xD9,OLED1_CMD);//Set Pre-Charge Period
	OLED1_WR_Byte(0xF1,OLED1_CMD);//
	
	OLED1_WR_Byte(0xDA,OLED1_CMD);//set com pin configuartion
	OLED1_WR_Byte(0x12,OLED1_CMD);//
	
	OLED1_WR_Byte(0xDB,OLED1_CMD);//set Vcomh
	OLED1_WR_Byte(0x30,OLED1_CMD);//
	
	OLED1_WR_Byte(0x8D,OLED1_CMD);//set charge pump enable
	OLED1_WR_Byte(0x14,OLED1_CMD);//
	
	OLED1_WR_Byte(0xAF,OLED1_CMD);//--turn on OLED1 panel
}  

void OLED2_Init(void)
{ 		 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 // πƒ‹A∂Àø⁄ ±÷”
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //Õ∆ÕÏ ‰≥ˆ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//ÀŸ∂»50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //≥ı ºªØGPIOD3,6
 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_4);	


delay_ms(800);
OLED2_WR_Byte(0xAE,OLED2_CMD);//--display off
	OLED2_WR_Byte(0x00,OLED2_CMD);//---set low column address
	OLED2_WR_Byte(0x10,OLED2_CMD);//---set high column address
	OLED2_WR_Byte(0x40,OLED2_CMD);//--set start line address   
	OLED2_WR_Byte(0xB0,OLED2_CMD);//--set page address
	OLED2_WR_Byte(0x81,OLED2_CMD); // contract control
	OLED2_WR_Byte(0xFF,OLED2_CMD);//--128   
	OLED2_WR_Byte(0xA1,OLED2_CMD);//set segment remap 
	OLED2_WR_Byte(0xA6,OLED2_CMD);//--normal / reverse
	OLED2_WR_Byte(0xA8,OLED2_CMD);//--set multiplex ratio(1 to 64)
	OLED2_WR_Byte(0x3F,OLED2_CMD);//--1/32 duty
	OLED2_WR_Byte(0xC8,OLED2_CMD);//Com scan direction
	OLED2_WR_Byte(0xD3,OLED2_CMD);//-set display offset
	OLED2_WR_Byte(0x00,OLED2_CMD);//
	
	OLED2_WR_Byte(0xD5,OLED2_CMD);//set osc division
	OLED2_WR_Byte(0x80,OLED2_CMD);//
	
	OLED2_WR_Byte(0xD8,OLED2_CMD);//set area color mode off
	OLED2_WR_Byte(0x05,OLED2_CMD);//
	
	OLED2_WR_Byte(0xD9,OLED2_CMD);//Set Pre-Charge Period
	OLED2_WR_Byte(0xF1,OLED2_CMD);//
	
	OLED2_WR_Byte(0xDA,OLED2_CMD);//set com pin configuartion
	OLED2_WR_Byte(0x12,OLED2_CMD);//
	
	OLED2_WR_Byte(0xDB,OLED2_CMD);//set Vcomh
	OLED2_WR_Byte(0x30,OLED2_CMD);//
	
	OLED2_WR_Byte(0x8D,OLED2_CMD);//set charge pump enable
	OLED2_WR_Byte(0x14,OLED2_CMD);//
	
	OLED2_WR_Byte(0xAF,OLED2_CMD);//--turn on OLED2 panel
}  





























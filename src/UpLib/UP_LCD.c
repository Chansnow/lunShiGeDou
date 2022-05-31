/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  	: 乔潇楠  
//  Update Date   : 2013/07/12
//  Version   	  : 1.3          
//  Description   : Modification for new LCD
//  Update Date   : 2013/09/24
//  Version   	  : 1.3.1          
//  Description   : Modification for using "printf"
/******************************************************************/ 

#include "STM32Lib\\stm32f10x.h"
#include "UP_LCD.h"

#define L_DELAY	12

u8 g_LCD_X = 0;
u8 g_LCD_Y = 0;

void Delay_us(u16 us)
{
	u16 i;
	while(us)
	{
		us--;
		for(i=0;i<8;i++);
	}
}

void Delay_ms(u16 ms)
{
	u16 i;
	while(ms)
	{
		ms--;
		for(i=0;i<8000;i++);
	}
}
/*************************************************
  函数名称: Lcds_Config
  函数功能: Lcd初始化
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void Lcds_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//使能端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	CS_H;
	//GPIO设置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//50M时钟速度
	//PC6输出 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//PD9,8,10,11输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*************************************************
  函数名称: SPIByte(用户不用)
  函数功能: 读写SPI总线，此LCD发送命令、数据、基本读写
  被本函数调用的函数: 无        
  调用本函数的函数: LCD_WriteCmd(u8 addr,u8 cmd);LCD_WriteData(u8 dat);
  输入参数说明: byte是指发送一个字节长度的数据
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void SPIByte(u8 byte)
{
	u8 i;
	u8 temp = byte;

	for(i=0;i<8;i++)
	{
		SCL_L;
		if(temp&0x80)
			SDA_H;
		else
			SDA_L;
		__nop();
		__nop();
		__nop();

		SCL_H;
		temp<<=1;
		__nop();
		__nop();
		__nop();

	}
	SCL_H;
	SDA_H;
}

/*************************************************
  函数名称: LCD_WriteCmd
  函数功能: 向LCD相应寄存器发送相应命令。
  被本函数调用的函数: SPIByte(u8 byte);    
  调用本函数的函数:   UP_LCD_Init(void);UP_LCD_OnOff(u8 onoff);UP_LCD_Fill(u8 dat);
                      UP_LCD_ClearLine(u8 y);UP_LCD_ShowCharacter(u8 x, u8 y, char cha[2]);
                      UP_LCD_ShowCharacter(u8 x, u8 y, char cha[2]);UP_LCD_ShowString(u8 x, u8 y, char *pstring);
                      UP_LCD_ShowProgressBar(u8 y,u8 percent);
  输入参数说明: addr是要操作的LCD的寄存器的地址;cmd是要下发给LCD的命令。
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void LCD_WriteCmd(u8 addr,u8 cmd)
{
	CS_L;
    __nop();
	__nop();
	__nop();
	RS_L;
    __nop();
	__nop();
	__nop();
	
	SCL_L;
	SDA_L;
	__nop();
	__nop();
	__nop();
	SCL_H;
	__nop();
	__nop();
	__nop();
	SPIByte(addr);
    __nop();
	__nop();
	__nop();
	SPIByte(cmd);
    __nop();
	__nop();
	__nop();
	CS_H;
}
	
/*************************************************
  函数名称: LCD_WriteData
  函数功能: 写数据到LCD
  被本函数调用的函数: SPIByte(u8 byte);       
  调用本函数的函数:  UP_LCD_Fill(u8 dat);UP_LCD_ClearLine(u8 y);UP_LCD_ShowLetter(u8 x, u8 y, u8 ch);
                     UP_LCD_ShowCharacter(u8 x, u8 y, char cha[2]);UP_LCD_ShowString(u8 x, u8 y, char *pstring);
                     UP_LCD_ShowCharacterString(u8 x, u8 y, char *pstring);UP_LCD_ShowProgressBar(u8 y,u8 percent);
  输入参数说明: 发送一个字节的数据到LCD。
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void LCD_WriteData(u8 dat)
{
	CS_L;
    __nop();
	__nop();
	__nop();
	RS_H;
    __nop();
	__nop();
	__nop();

	SCL_L;
	SDA_L;
    __nop();
	__nop();
	__nop();
	SCL_H;
    __nop();
	__nop();
	__nop();
	SPIByte(dat);
    __nop();
	__nop();
	__nop();
	CS_H;
}
/*************************************************
  函数名称: UP_LCD_Init
  函数功能: LCD基层显示函数
  被本函数调用的函数: Lcds_Config();LCD_WriteData(u8 dat);LCD_WriteCmd(u8 addr,u8 cmd);UP_LCD_ClearScreen();	       
  调用本函数的函数: 无
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void UP_LCD_Init(void)
{
	Lcds_Config();			//初始化LCD管脚

	RST_L;
	Delay_ms(100);
	RST_H;
	Delay_ms(100);
	
	LCD_WriteCmd(0x00,0x00);
	LCD_WriteCmd(0x01,0x00);

	LCD_WriteCmd(0x02,0x7b);

	LCD_WriteCmd(0x03,0x00);
	LCD_WriteCmd(0x04,0x00);
	LCD_WriteCmd(0x05,0x00);
	LCD_WriteCmd(0x06,0x00);
	LCD_WriteCmd(0x07,0x00);
	LCD_WriteCmd(0x08,0x00);
	LCD_WriteCmd(0x09,0x00);
	LCD_WriteCmd(0x0a,0x00);
	LCD_WriteCmd(0x0b,0x00);
	LCD_WriteCmd(0x0c,0x00);
	LCD_WriteCmd(0x0d,0x00);
	LCD_WriteCmd(0x0e,0x00);
	LCD_WriteCmd(0x0f,0x00);

	LCD_WriteCmd(0x13,0x00);
	LCD_WriteCmd(0x14,0x00);
	LCD_WriteCmd(0x15,0x00);
	LCD_WriteCmd(0x16,0x00);
	LCD_WriteCmd(0x17,0x00);
	LCD_WriteCmd(0x18,0x00);

	LCD_WriteCmd(0x10,0x2C);
	LCD_WriteCmd(0x12,0x24);
	LCD_WriteCmd(0x11,0xf8);

    LCD_WriteCmd(0x01,0x02);
	UP_LCD_Turn(0);              //调整角度为0度
	UP_LCD_ClearScreen();		  //清屏

	LCD_BK_ON;//开背光
}

/*************************************************
  函数名称: UP_LCD_OnOff
  函数功能: 开关LCD
  被本函数调用的函数: LCD_WriteCmd(u8 addr,u8 cmd);     
  调用本函数的函数: 无
  输入参数说明: onoff意即开关状态，0关1开。
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
***************************************************/
void UP_LCD_OnOff(u8 onoff)
{
     if(onoff>0) 
		 LCD_WriteCmd(0x01,0x02);       //开显示
     else 
		 LCD_WriteCmd(0x01,0x00);   	//关显示
}

/*************************************************
  函数名称: UP_LCD_Turn
  函数功能: LCD显示区域翻转 dir=0正向显示 dir=1 180度翻转
  被本函数调用的函数: LCD_WriteCmd(u8 addr,u8 cmd);     
  调用本函数的函数: UP_LCD_Init(void);
  输入参数说明: dec用于判断比较的值
  输出参数说明: 无          
  函数返回值: 无   
  其它说明: 无         
***************************************************/ 
void UP_LCD_Turn(u8 dec)
{
     if(dec) 
		 LCD_WriteCmd(0x11,0xfb);
     else 
		 LCD_WriteCmd(0x11,0xf8);
}

/*************************************************
  函数名称: UP_LCD_Fill
  函数功能: 填充LCD.
  被本函数调用的函数: LCD_WriteCmd(u8 addr,u8 cmd);LCD_WriteData(u8 dat);     
  调用本函数的函数: 无
  输入参数说明: 发送一个字节的数据到LCD
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
***************************************************/ 
void UP_LCD_Fill(u8 dat)
{
    u8 i,j;
	LCD_WriteCmd(0x03,0x40);
    for(i=0;i<64;i++)
    {  
	    LCD_WriteCmd(0x05,0);
		LCD_WriteCmd(0x06,i); 
		for(j=0;j<16;j++)
		{
			LCD_WriteData(dat);
			Delay_us(350); 
		}
    }			
}

/*************************************************
  函数名称: UP_LCD_ClearScreen
  函数功能: 清屏
  被本函数调用的函数: UP_LCD_Fill(u8 dat);    
  调用本函数的函数: 无
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
***************************************************/ 
void UP_LCD_ClearScreen(void)
{
	 UP_LCD_Fill(0);
	 g_LCD_X = 0;
	 g_LCD_Y = 0;
}

/*************************************************
  函数名称: UP_LCD_ClearLine
  函数功能: 清除某行
  被本函数调用的函数: LCD_WriteData(u8 dat);LCD_WriteCmd(u8 addr,u8 cmd);
  调用本函数的函数: 无
  输入参数说明: 发送一个数字到LCD，清除某一行，范围0——3
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
***************************************************/ 
void UP_LCD_ClearLine(u8 y)
{
     u8 i,j;
     for(i=0;i<17;i++)
     {
	     LCD_WriteCmd(0x03,0x40);
		 LCD_WriteCmd(0x05,0);
	     LCD_WriteCmd(0x06,y*16+i);
		 for(j=0;j<16;j++)
		 {
			 LCD_WriteData(0);
			 Delay_us(350); 
		 }
     }
}// */

/*************************************************
  函数名称: UP_LCD_ShowLetter
  函数功能: 显示单个英文字符
  被本函数调用的函数: LCD_WriteData(u8 dat);LCD_WriteCmd(u8 addr,u8 cmd);Delay_us(u16 us)；
  调用本函数的函数: 无
  输入参数说明: x代表列(0-15)，y代表行(0-3)，ch代表英文字符。
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
***************************************************/ 
void UP_LCD_ShowLetter(u8 x, u8 y, u8 ch)
{
	 LCD_WriteCmd(0x03,0x42);
	 LCD_WriteCmd(0x05,x);
	 LCD_WriteCmd(0x06,y*16);
	 LCD_WriteData(ch);
	 Delay_us(350); 
}

/*************************************************
  函数名称: UP_LCD_ShowCharacter
  函数功能: 显示单个汉字
  被本函数调用的函数: LCD_WriteData(u8 dat);LCD_WriteCmd(u8 addr,u8 cmd);Delay_us(u16 us)；
  调用本函数的函数: 无
  输入参数说明: x代表列(0-15)，y代表行(0-3)，cha[i]代表输入的汉字。
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
***************************************************/ 
void UP_LCD_ShowCharacter(u8 x, u8 y, char cha[2])
{ 
	 LCD_WriteCmd(0x03,0x43);
	 LCD_WriteCmd(0x05,x*2);
	 LCD_WriteCmd(0x06,y*16);
	 LCD_WriteData(cha[0]);
	 Delay_us(350);
	 LCD_WriteData(cha[1]);
	 Delay_us(350);
}

/*************************************************
  函数名称: UP_LCD_ShowString
  函数功能: 显示字符串
  被本函数调用的函数: LCD_WriteData(u8 dat);LCD_WriteCmd(u8 addr,u8 cmd);Delay_us(u16 us)；
  调用本函数的函数: 无
  输入参数说明: x代表列(0-15)，y代表行(0-3),*pstring代表字符串.
  输出参数说明: 无       
  函数返回值:  result代表写进LCD的字符的个数, 0代表汉字字符串没有写完
  其它说明: 无        
***************************************************/ 
u8 UP_LCD_ShowString(u8 x, u8 y, char *pstring)
{
   u8 result = 0;
   if(y > 3 || x > 16)
		return 0;
   LCD_WriteCmd(0x03,0x42);
   LCD_WriteCmd(0x05,x);
   LCD_WriteCmd(0x06,y*16);

   while(*pstring != 0)
   {
         LCD_WriteData(*pstring);
		 Delay_us(350);
		 pstring++;
		 result++;
   }
   return result;
}

/*************************************************
  函数名称: UP_LCD_ShowCharacterString
  函数功能: 显示汉字字符串
  被本函数调用的函数: LCD_WriteData(u8 dat);LCD_WriteCmd(u8 addr,u8 cmd);Delay_us(u16 us)；
  调用本函数的函数: 无
  输入参数说明: x代表列(0-15)，y代表行(0-3),*pstring代表字符串.
  输出参数说明: 无       
  函数返回值:  result代表写进LCD的字符的个数
  其它说明: 无        
***************************************************/ 
u8 UP_LCD_ShowCharacterString(u8 x, u8 y, char *pstring)
{
   u8 result = 0;
   if(y > 3 || x > 16)
		return 0;
   LCD_WriteCmd(0x03,0x43);
   LCD_WriteCmd(0x05,x*2);
   LCD_WriteCmd(0x06,y*16);

   while(*pstring != 0)
   {
         LCD_WriteData(*pstring);
		 Delay_us(400);
		 pstring++;
		 LCD_WriteData(*pstring);
		 Delay_us(400);
		 pstring++;
		 result++;
   }
   return result;
}

/*************************************************
  函数名称: UP_LCD_ShowInt
  函数功能: 显示整形数字
  被本函数调用的函数:UP_LCD_ShowString(u8 x, u8 y, char *pstring);
  调用本函数的函数: 无
  输入参数说明: x代表列(0-15)，y代表行(0-3),n代表整形数字
  输出参数说明: 无       
  函数返回值: 返回输入的整形数的个数
  其它说明: 无        
***************************************************/ 
u8 UP_LCD_ShowInt(u8 x, u8 y, int n)
{
   s8 i; 
   u8 bf = 0;
   char display_buffer[8] = {0};

   if(n < 0)
   {
	  n = -n;
	  bf = 1;
   }

   for(i=6; i>=0; i--)
   {
      display_buffer[i] = '0'+n%10;
      n = n/10.0f;
      if(n == 0)
      break;
   }
   if(bf)
   {
	  i--;
	  display_buffer[i] = '-';
   }
   UP_LCD_ShowString(x,y,&display_buffer[i]);// */
   return 7-i;
}
void UP_LCD_ShowHex(u8 x,u8 y,u8 hex)
{
	char H,L;
	
	if((hex/16)<10)	H = '0'+hex/16;
	else H = 'A'+hex/16-10;
	
	if((hex%16)<10)	L = '0'+hex%16;
	else L = 'A'+hex%16-10;
	UP_LCD_ShowLetter(x,y,H);
	UP_LCD_ShowLetter(x+1,y,L);
}
/*************************************************
  函数名称: UP_LCD_ShowProgressBar
  函数功能: 显示百分比 0-112 step = 8 8*14 = 112 
  被本函数调用的函数: LCD_WriteData(u8 dat);LCD_WriteCmd(u8 addr,u8 cmd);Delay_us(u16 us)；
  调用本函数的函数: 无
  输入参数说明: y表示行,percent*0.125表示进度值大小，其值最大112.
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
***************************************************/ 
void UP_LCD_ShowProgressBar(u8 y,u8 percent)
{
	u8 i,j;
	LCD_WriteCmd(0x03,0x40);
	//show form
	for(i=(y*16+2);i<(y*16+13);i++)
	{
	    LCD_WriteCmd(0x05,1);
		LCD_WriteCmd(0x06,i);
		LCD_WriteData(0x80);
		Delay_us(50);
		LCD_WriteCmd(0x05,14);
		LCD_WriteCmd(0x06,i);
		LCD_WriteData(0x01);
		Delay_us(50);
	}
	LCD_WriteCmd(0x06,y*16+2);
	for(i=1;i<15;i++)
	{
	    LCD_WriteCmd(0x05,i);
		LCD_WriteData(255);
		Delay_us(50);
	}
	LCD_WriteCmd(0x06,y*16+13);
	for(i=1;i<15;i++)
	{
	    LCD_WriteCmd(0x05,i);
		LCD_WriteData(255);
		Delay_us(50);
	}
	//show percent
	for(j=(y*16+2);j<(y*16+13);j++)
	{
		LCD_WriteCmd(0x06,j);
		for(i=1;i<=percent;i++)
	    {
	       LCD_WriteCmd(0x05,i);
		   LCD_WriteData(255);
		   Delay_us(50);
	    }
	}
}	

/*************************************************/
//定义 fputc 此函数为printf所用
/*************************************************/
int fputc(int ch) 
{ 
	static u8 s_bClearScreen = 0;
	if(s_bClearScreen)
	{
		s_bClearScreen = 0;
		UP_LCD_ClearScreen();
	}
	if(ch == '\n')
	{
		g_LCD_Y++;
		g_LCD_X = 0;
	}
  if(g_LCD_X > 15)
	{	
		g_LCD_Y++;
		g_LCD_X = 0;
	}
	if(g_LCD_Y > 3)
	{
		s_bClearScreen = 1;
	}
	if(ch != '\r' && ch != '\n')
	{
		UP_LCD_ShowLetter(g_LCD_X,g_LCD_Y,(u8)ch);
		g_LCD_X++;
	}
    return ch; 
} 

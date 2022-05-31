/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  : 乔潇楠  
//  Update Date   : 2013/07/15
//  Version   	  : 1.0            
//  Reviser				: 王伟
//  Update Date   : 2014/08/18
//  Version   	  : 1.0.1          
//  Description   : The "UP_EnableUSR232IT(u32 BaudRate);" moves from UP_UART.c to UP_USR232.c
/******************************************************************/ 


#include "UP_USR232.h" 
#include "UP_UART.h"
#include "UP_Globle.h"

/*************************************************
  函数名称: UP_EnableUSR232IT
  函数功能: 设置波特率
  被本函数调用的函数: 无
  调用本函数的函数: 无
  输入参数说明: BaudRate可以是115200等
  输出参数说明: 无       
  函数返回值:  无
  其它说明: 无        
***************************************************/
void UP_EnableUSR232IT(u32 BaudRate)
{
	g_UP_USR232BaudRate = BaudRate;
	g_UP_bUSR232IT = TRUE;		
}
/*************************************************
  函数名称: UP_USR232_EnableIT
  函数功能: 使能USR232数据接收中断
  被本函数调用的函数: 无
  调用本函数的函数: 无
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值:  无
  其它说明: 无        
***************************************************/ 
void UP_USR232_EnableIT(void)
{
	g_UP_bUSR232IT = TRUE;		
}

/*************************************************
  函数名称: UP_SetUSR232Hadler
  函数功能: 传递USR232数据接收中断入口函数
  被本函数调用的函数: 无
  调用本函数的函数: 无
  输入参数说明: ApplicationAddress可以定义成接收中断入口函数地址
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
***************************************************/ 
void UP_SetUSR232Hadler(void (*ApplicationAddress)(u32))
{
	if(ApplicationAddress != 0)
		g_UP_USR232ITAddress = (u32)ApplicationAddress;
}

/*************************************************
  函数名称: UP_USR232_Putc
  函数功能: USR232发送一个字符
  被本函数调用的函数: UP_UART5_Putc(unsigned char c);
  调用本函数的函数: 无
  输入参数说明: c代表的是发送的字符
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
***************************************************/ 
void UP_USR232_Putc(unsigned char c)
{
	UP_UART5_Putc(c);
} 

/*************************************************
  函数名称: UP_USR232_Puts
  函数功能: USR232发送一串字符
  被本函数调用的函数: UP_UART5_Puts(str);
  调用本函数的函数: 无
  输入参数说明: 可以发送字符串
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
***************************************************/ 	
void UP_USR232_Puts(char * str)
{
	UP_UART5_Puts(str);
}		

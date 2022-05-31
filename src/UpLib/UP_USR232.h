/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  : 乔潇楠  
//  Update Date   : 2013/07/15
//  Version   	  : 1.0            
//  Description   :  
/******************************************************************/

#ifndef USR232_H
#define USR232_H

#include "STM32Lib\\stm32f10x.h"

//USR232相关函数
void UP_USR232_EnableIT(void);					//使能USR232数据接收中断
void UP_SetUSR232Hadler(void (*ApplicationAddress)(u32));		//传递USR232数据接收中断入口函数
void UP_USR232_Putc(unsigned char c);		//USR232发送一个字符
void UP_USR232_Puts(char * str);				//USR232发送一串字符	


#endif

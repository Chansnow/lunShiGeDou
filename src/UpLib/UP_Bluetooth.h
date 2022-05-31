/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  : 陈中元  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
/******************************************************************/

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "STM32Lib\\stm32f10x.h"

//蓝牙相关函数
extern void UP_Bluetooth_Init(void);				//蓝牙初始化
extern void UP_Bluetooth_EnableIT(void); 			//使能蓝牙数据接收中断
extern void UP_Bluetooth_SetHadler(void (*ApplicationAddress)(u8));	//定义蓝牙数据接收中断入口函数
extern void UP_Bluetooth_Putc(unsigned char c); 	//蓝牙发送一个字符
extern void UP_Bluetooth_Puts(char * str);			//蓝牙发送一串字符

#endif

/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
//  Update Date   : 2013/07/12
//  Version   	  : 1.3.1          
//  Description   : Modification for new controller
/******************************************************************/ 

#ifndef UART_H
#define UART_H

//串口3发送接收使能端口宏定义
#define UART3_RXEN 		(GPIOE->ODR |= GPIO_Pin_15)
#define UART3_RXDS 		(GPIOE->ODR &= ~GPIO_Pin_15)
#define UART3_TXEN 		(GPIOE->ODR |= GPIO_Pin_14)
#define UART3_TXDS 		(GPIOE->ODR &= ~GPIO_Pin_14)

//串口相关函数
extern void UP_UART_Init(void);					//UART相关初始化

extern void UP_EnableBluetoothIT(u32 BaudRate);		//使能蓝牙数据接收中断
extern void UP_SetBluetoothHadler(void (*ApplicationAddress)(u32));	//传递蓝牙数据接收中断入口函数
extern void UP_EnableZigbeeIT(u32 BaudRate);		//使能Zigbee数据接收中断
extern void UP_SetZigbeeHadler(void (*ApplicationAddress)(u32));	//传递Zigbee数据接收中断入口函数
extern void UP_EnableUSR232IT(u32 BaudRate);		//使能USR232数据接收中断
extern void UP_SetUSR232Hadler(void (*ApplicationAddress)(u32));	//传递USR232数据接收中断入口函数

extern void UP_UART1_Putc(unsigned char c); 	//UART1发送一个字符
extern void UP_UART1_Puts(char * str);			//UART1发送一串字符
extern void UP_UART4_Putc(unsigned char c); 	//UART4发送一个字符
extern void UP_UART4_Puts(char * str);			//UART4发送一串字符
extern void UP_UART5_Putc(unsigned char c); 	//UART5发送一个字符
extern void UP_UART5_Puts(char * str);			//UART5发送一串字符

extern void UP_Uart3_SendCDSFrame(u8 id, u8 len, u8 Cmd, u8* pData);	//发送数字舵机协议帧

#endif

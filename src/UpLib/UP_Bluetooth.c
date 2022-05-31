/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  : 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2013/07/12
//  Version   	  : 1.2.1            
//  Description   :  modification for new controller
/******************************************************************/ 

#include "UP_Bluetooth.h" 
#include "UP_UART.h"
#include "UP_Globle.h"

#define HC_KEY_L		(GPIOD->ODR &= ~GPIO_Pin_7)
#define HC_KEY_H		(GPIOD->ODR |= GPIO_Pin_7)

//蓝牙初始化
void UP_Bluetooth_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	//PD7做蓝牙控制端
	HC_KEY_L;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  //推挽输出
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//使能蓝牙数据接收中断
void UP_Bluetooth_EnableIT(void)
{
	g_UP_bBluetoothIT = TRUE;		
}

//定义蓝牙数据接收中断入口函数
void UP_SetBluetoothHadler(void (*ApplicationAddress)(u32))
{
	if(ApplicationAddress != 0)
		g_UP_BluetoothITAddress = (u32)ApplicationAddress;	
}

//蓝牙发送一个字符
void UP_Bluetooth_Putc(unsigned char c)
{
	UP_UART1_Putc(c);
} 

//蓝牙发送一串字符	
void UP_Bluetooth_Puts(char * str)
{
	UP_UART1_Puts(str);
}			

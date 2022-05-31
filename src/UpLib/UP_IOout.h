/******************************************************************/
//	Copyright (C), 2011-2012, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
/******************************************************************/ 

#ifndef SERVO_L
#define SERVO_L
#include "STM32Lib\\stm32f10x.h"


//常量宏定义
#define UP_IOout_NUM		6				//IO输出端口数目

//输出宏定义
//IOout0~PA14
#define UP_IOout0_L		(GPIOA->BSRR = GPIO_Pin_14)
#define UP_IOout0_H		(GPIOA->BRR = GPIO_Pin_14)
//IOout1~PA15
#define UP_IOout1_L		(GPIOA->BSRR = GPIO_Pin_15)
#define UP_IOout1_H		(GPIOA->BRR = GPIO_Pin_15)
//IOout2~PD0
#define UP_IOout2_L		(GPIOD->BSRR = GPIO_Pin_0)
#define UP_IOout2_H		(GPIOD->BRR = GPIO_Pin_0)	
//IOout3~PD1
#define UP_IOout3_L		(GPIOD->BSRR = GPIO_Pin_1)
#define UP_IOout3_H		(GPIOD->BRR = GPIO_Pin_1)	
//IOout4~PD2
#define UP_IOout4_L		(GPIOD->BSRR = GPIO_Pin_3)
#define UP_IOout4_H		(GPIOD->BRR = GPIO_Pin_3)
//IOout5~PD3
#define UP_IOout5_L		(GPIOD->BSRR = GPIO_Pin_4)
#define UP_IOout5_H		(GPIOD->BRR = GPIO_Pin_4)		


//硬件初始化
extern void  UP_IOout_Init(void);																		//舵机相关初始化
extern void  UP_IOout_SetIO(u8 Channel, u8 Value);									//设置模拟舵机端口IO输出电平，通道0~7，值0或1
extern void  UP_IOout_SetALLIO(u8 Value);														//同时设置8路模拟舵机端口IO输出电平，值0x00~0xFF

#endif

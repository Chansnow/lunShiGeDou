/******************************************************************/
//	Copyright (C), 2011-2012, 北京博创 
//  Author   	  : 陈中元  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
//  Reviser				: 乔潇楠
//  Update Date   : 2013/09/24
//  Version   	  : 1.3          
//  Description   : Change EXTI line Settings.
/******************************************************************/

#ifndef EXTI_H
#define EXTI_H

#include "STM32Lib\\stm32f10x.h"

//外部中断通道宏定义
#define EXTI_DOWN		EXTI_Line13
#define EXTI_UP			EXTI_Line14
#define EXTI_BACK		EXTI_Line12
#define EXTI_OK			EXTI_Line15
#define EXTI_AD4		EXTI_Line7
#define EXTI_AD5		EXTI_Line6
#define EXTI_AD6		EXTI_Line5
#define EXTI_AD7		EXTI_Line4
#define EXTI_AD12		EXTI_Line3
#define EXTI_AD13		EXTI_Line2
#define EXTI_AD14		EXTI_Line1
#define EXTI_AD15		EXTI_Line0

//外部中断相关函数
extern void UP_Exti_Init(void);				//外部中断初始化
extern void UP_Exti_EnableIT(u32 Channel, EXTITrigger_TypeDef TriggerMode);	//使能外部中断通道并配置其中断模式
extern void UP_Exti_DisableIT(u32 Channel); 	//禁能外部中断
extern void UP_Exti_SetHadler(void (*ApplicationAddress)(u32));	//传递外部中断入口函数

#endif

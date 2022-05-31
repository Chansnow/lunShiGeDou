/******************************************************************/
//	Copyright (C), 2011-2012, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
/******************************************************************/ 

#ifndef TIMER_H
#define TIMER_H

#include "STM32Lib\\stm32f10x.h"

void TIM4_Int_Init(u16 arr,u16 psc);
void TIM5_Int_Init(u16 arr,u16 psc);

//计时器相关宏定义
#define TIMER_CHANNEL0	0
#define TIMER_CHANNEL1	1
#define TIMER_CHANNEL2	2
#define TIMER_CHANNEL3	3

//硬件初始化
extern void UP_Timer_Init(void);								//定时器相关初始化
extern void UP_Timer_EnableIT(u32 TimerChannel, u32 Time_us);	//使能计时器中断
extern void UP_Timer_DisableIT(u32 TimerChannel);				//禁能计时器中断
extern void UP_Timer_SetHadler(u32 channel,void (*ApplicationAddress)(u32));//设置定时器中断入口函数
extern u32 UP_Timer_GetCount(void);								//获取计时器计数值（32位）,每计数值1us
extern void UP_Timer_CleanCount(void);							//清零计时器计数值
extern void Edge(void);

#endif

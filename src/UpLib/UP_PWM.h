/******************************************************************/
//	Copyright (C), 2011-2012, 北京博创 
//  Author   	  : 陈中元  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
/******************************************************************/

#ifndef PWM_H
#define PWM_H

extern void UP_PWM_Init(void);								//PWM相关初始化
extern void UP_PWM_Enable(u8 Channel, FunctionalState NewState);	//使能PWM模式输出，通道0~3，状态ENABLE或DISABLE
extern void UP_PWM_SetDutyTime(u8 Channel, u16 DutyTime);	//设置高电平时长0~4095对应0%~100%
extern void UP_PWM_SetFrequency(u32 Frequency);				//设置频率（Hz），50~1000000
extern void UP_PWM_SetIO(u8 Channel, u8 Value);				//设置PWM端口IO输出电平，通道0~3，值0或1

#endif


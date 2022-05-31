/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
//  Reviser				: 乔潇楠
//  Update Date   : 2013/07/18
//  Version   	  : 1.3.1         
//  Description   : Change GPIO configuration for keys.
/******************************************************************/ 

#ifndef KEYS_H
#define KEYS_H

#include "STM32Lib\\stm32f10x.h"

//按键初始化
extern void UP_Key_Init(void);

//按键输入宏定义
#define UP_Key_Down()	(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13))	//下
#define UP_Key_Up()		(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14))	//上
#define UP_Key_BACK()	(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12))	//返回
#define UP_Key_OK()		(!GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15))	//确认

#endif

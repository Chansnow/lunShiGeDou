/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  : 陈中元  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
//  Reviser				: 乔潇楠
//  Update Date   : 2013/09/24
//  Version   	  : 1.3          
//  Description   : Change GPIO Settings and EXTI line Settings.
/******************************************************************/ 

#include "UP_Exti.h" 
#include "UP_Globle.h"

/*************************************************
  函数名称: UP_Exti_Init
  函数功能: 外部中断初始化
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void UP_Exti_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//连接按键IO口到中断线
	if(g_UP_ExtiFlag & EXTI_UP)
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource14);
	if(g_UP_ExtiFlag & EXTI_DOWN)
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource13);
	if(g_UP_ExtiFlag & EXTI_OK)
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource15);
	if(g_UP_ExtiFlag & EXTI_BACK)
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource12);
	
	//连接AD口到中断线
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//悬空输入
	if(g_UP_ExtiFlag & EXTI_AD4)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);
	}
	if(g_UP_ExtiFlag & EXTI_AD5)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
	}
	if(g_UP_ExtiFlag & EXTI_AD6)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);
	}
	if(g_UP_ExtiFlag & EXTI_AD7)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
	}
	if(g_UP_ExtiFlag & EXTI_AD12)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);
	}
	if(g_UP_ExtiFlag & EXTI_AD13)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
	}
	if(g_UP_ExtiFlag & EXTI_AD14)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);
	}
	if(g_UP_ExtiFlag & EXTI_AD15)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);
	}
}

/*************************************************
  函数名称: UP_Exti_EnableIT
  函数功能: 使能外部中断
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: Channel代表设置的外部中断的通道，
                EXTITrigger_TypeDef TriggerMode代表设置的外部中断触发信号的模式。
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void UP_Exti_EnableIT(u32 Channel, EXTITrigger_TypeDef TriggerMode)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	g_UP_ExtiFlag |= Channel;
	//配置中断线
	EXTI_InitStructure.EXTI_Line = Channel;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = TriggerMode;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);		
}

/*************************************************
  函数名称: UP_Exti_SetHadler
  函数功能: 传递外部中断入口函数
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: 定义ApplicationAddress为指针类型
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void UP_Exti_SetHadler(void (*ApplicationAddress)(u32))
{
	if(ApplicationAddress != 0)
		g_UP_ExtiITAddress = (u32)ApplicationAddress;	
}

/*************************************************
  函数名称: UP_Exti_DisableIT
  函数功能: 禁能外部中断
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: Channel为禁能的通道。
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void UP_Exti_DisableIT(u32 Channel)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	g_UP_ExtiFlag &= ~Channel;
	//配置中断线
	EXTI_InitStructure.EXTI_Line = Channel;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);		
}
			

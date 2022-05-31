/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
/******************************************************************/ 

#include "STM32Lib\\stm32f10x.h"
#include "UP_System.h"
#include "UP_NVIC.h"

/*************************************************
  函数名称: UP_System_Init   
  函数功能: 初始化系统函数
  被本函数调用的函数: SystemInit();UP_NVIC_Configuration();UP_Key_Init();UP_ADC_Init();UP_UART_Init();
                      UP_LCD_Init();UP_IOout_Init();UP_PWM_Init();UP_Exti_Init();UP_Timer_Init();UP_Bluetooth_Init();	
  调用本函数的函数: 无    
  输入参数说明: 无       
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_System_Init(void)
{
	
	SystemInit();							//初始化库
	UP_NVIC_Configuration();	//初始化中断
	UP_Key_Init();						//初始化按键	
	UP_ADC_Init();						//初始化ADC
	UP_LCD_Init();						//初始化LCD
	UP_IOout_Init();					//初始化IO输出口
	UP_PWM_Init();						//初始化PWM
	UP_Exti_Init();						//初始化外部中断
	UP_UART_Init();
	UP_Timer_Init();					//初始化定时器

}

/*************************************************
  函数名称: UP_ITConfig   
  函数功能: 使能外设
  被本函数调用的函数: 无
  调用本函数的函数: 无    
  输入参数说明: 无       
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_ITConfig(u8 channel, u8 flag)
{
	
	
}



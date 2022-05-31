/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
/******************************************************************/ 


#include "STM32Lib\\stm32f10x.h" 
#include "UP_NVIC.h"
#include "UP_Globle.h"
void UP_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0xB000);

	// Configure one bit for preemption priority 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	

	//SYSTICK分频--1ms的系统时钟中断，
	if (SysTick_Config(SystemCoreClock / 1000))
  	{ 
    	while (1);
  	}		// */

	//外部中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	if(g_UP_ExtiFlag & EXTI_Line0)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & EXTI_Line1)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & EXTI_Line2)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & EXTI_Line3)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & EXTI_Line4)
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & (EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9))
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if(g_UP_ExtiFlag & (EXTI_Line10|EXTI_Line11|EXTI_Line12|EXTI_Line13|EXTI_Line14|EXTI_Line15))
	{
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}

	// Timer2中断，模拟舵机计时器
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// Timer3中断，用户计时器
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/*
	// Timer4中断，PWM计时器
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);			 // */
	/*
	//ADC的DMA中断 
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);						 // */
	
	//UART1，UART中断
	if(g_UP_bBluetoothIT)	 		//如果开启了UART1接收中断
	{
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);			   // */
	}
		
	//UART4，UART中断
	if(g_UP_bZigbeeIT)	 		//如果开启了UART4接收中断
	{
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);			   // */
	}
	//UART5，UART中断
	if(g_UP_bUSR232IT)	 		//如果开启了UART5接收中断
	{
		NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);			   // */
	}
	//UART3的DMA发送中断 
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);						 // */
}

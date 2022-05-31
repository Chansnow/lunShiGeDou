/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
/******************************************************************/ 

/* Includes ------------------------------------------------------------------*/
#include "STM32Lib\\stm32f10x.h"
#include "UP_Timer.h"
#include "UP_UART.h"
#include "UP_Globle.h"

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMIException
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMIException(void)
{
}

/*******************************************************************************
* Function Name  : HardFaultException
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFaultException(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManageException
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManageException(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFaultException
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFaultException(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFaultException
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFaultException(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : DebugMonitor
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMonitor(void)
{
}

/*******************************************************************************
* Function Name  : SVCHandler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCHandler(void)
{
}

/*******************************************************************************
* Function Name  : PendSVC
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSVC(void)
{
}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    :系统时钟，一般调教到1MS中断一次
*******************************************************************************/
extern void CheckCDSSend(void);
void SysTick_Handler(void)		//检查是否有舵机数据帧需要发送（每1ms检查一次）
{
	CheckCDSSend();
}

void EXTI_IRQHandler(u32 Channel)
{
	if(g_UP_ExtiITAddress != 0)
		(*((void(*)(u32))g_UP_ExtiITAddress))(Channel);
	EXTI->PR = Channel;		//清零标志
}

void EXTI0_IRQHandler(void)
{
	EXTI_IRQHandler(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
	EXTI_IRQHandler(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{
	EXTI_IRQHandler(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
	EXTI_IRQHandler(EXTI_Line3);
}

void EXTI4_IRQHandler(void)
{
	EXTI_IRQHandler(EXTI_Line4);
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
		EXTI_IRQHandler(EXTI_Line5);
	else if(EXTI_GetITStatus(EXTI_Line6) != RESET)
		EXTI_IRQHandler(EXTI_Line6);
	else if(EXTI_GetITStatus(EXTI_Line7) != RESET)
		EXTI_IRQHandler(EXTI_Line7);
	else if(EXTI_GetITStatus(EXTI_Line8) != RESET)
		EXTI_IRQHandler(EXTI_Line8);
	else if(EXTI_GetITStatus(EXTI_Line9) != RESET)
		EXTI_IRQHandler(EXTI_Line9);
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
		EXTI_IRQHandler(EXTI_Line10);
	else if(EXTI_GetITStatus(EXTI_Line11) != RESET)
		EXTI_IRQHandler(EXTI_Line11);
	else if(EXTI_GetITStatus(EXTI_Line12) != RESET)
		EXTI_IRQHandler(EXTI_Line12);
	else if(EXTI_GetITStatus(EXTI_Line13) != RESET)
		EXTI_IRQHandler(EXTI_Line13);
	else if(EXTI_GetITStatus(EXTI_Line14) != RESET)
		EXTI_IRQHandler(EXTI_Line14);
	else if(EXTI_GetITStatus(EXTI_Line15) != RESET)
		EXTI_IRQHandler(EXTI_Line15);
}

//extern volatile bool ADC_Ok;
void DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC1))
 	{
		DMA_ClearITPendingBit(DMA1_IT_GL1);	//清除全部中断标志
	//	ADC_Ok=TRUE;
	}
}
/*
extern void UP_Sev_TimerPro(void);
void TIM2_IRQHandler(void)
{
	UP_Sev_TimerPro();
}
*/
extern void UP_Timer_Pro(void);
void TIM3_IRQHandler(void)
{	
	UP_Timer_Pro();
}
/*
extern void UP_PWM_TimerPro(void);
void TIM4_IRQHandler(void)
{	
	UP_PWM_TimerPro();
}  // */

void USART1_IRQHandler(void)
{
	//接收中断
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		if(g_UP_BluetoothITAddress != 0)
			(*((void(*)(u8))g_UP_BluetoothITAddress))(USART_ReceiveData(USART1));
	}
	
	//溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(USART1,USART_FLAG_ORE);	//读SR
		USART_ReceiveData(USART1);				//读DR
	}
}

void UART5_IRQHandler(void)
{
	//接收中断
	if(USART_GetITStatus(UART5,USART_IT_RXNE)==SET)
	{
		USART_ClearITPendingBit(UART5,USART_IT_RXNE);
		if(g_UP_USR232ITAddress != 0)
			(*((void(*)(u8))g_UP_USR232ITAddress))(USART_ReceiveData(UART5));
	}
	
	//溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	if(USART_GetFlagStatus(UART5,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(UART5,USART_FLAG_ORE);	//读SR
		USART_ReceiveData(UART5);				//读DR
	}
}
extern void UP_Zigbee_Rec(u32 data);
u32 count=0;
void UART4_IRQHandler(void)
{
	//接收中断
	if(USART_GetITStatus(UART4,USART_IT_RXNE)==SET)
	{
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
 		if(g_UP_ZigbeeITAddress != 0)
 			(*((void(*)(u8))g_UP_ZigbeeITAddress))(USART_ReceiveData(UART4));
		//UP_Zigbee_Rec((u32)USART_ReceiveData(UART4));
		//count++;
	}
	//溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	if(USART_GetFlagStatus(UART4,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(UART4,USART_FLAG_ORE);	//读SR
		USART_ReceiveData(UART4);				//读DR
	}
}

void DMA1_Channel2_IRQHandler(void)
{
	if((DMA1->ISR & DMA1_IT_TC2) != (uint32_t)RESET)
 	{	
		DMA1->IFCR = DMA1_IT_GL2;				//清除中断标志
		DMA1_Channel2->CCR &= ~((u32)0x01);		//禁用DMA
		UP_delay_us(100);
		UART3_TXDS;
	//	DMA1_Channel2->CNDTR = 15;				//重新装载要发送的字节数	// */
	}
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/

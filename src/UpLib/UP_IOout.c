/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
//  Update Date   : 2013/07/09
//  Version   	  : 1.3.1          
//  Description   : modify the UP_Sev_SetALLIO(u8 Value) 
//  Update Date   : 2013/09/24
//  Version   	  : 1.4          
//  Description   : modify to IO out function
/******************************************************************/ 

#include "STM32Lib\\stm32f10x.h"
#include "UP_IOout.h"


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


//相关变量定义

u8  g_UP_IOVal[UP_IOout_NUM];					//IO端口电平

/*************************************************
  函数名称: UP_IOout_AllLow    
  函数功能: 所有端口输出低电平
  被本函数调用的函数: 无        
  调用本函数的函数: void UP_IOout_GPIOInit(void);   
  输入参数说明: 无         
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_IOout_AllLow(void)
{
	UP_IOout0_L; UP_IOout1_L; UP_IOout2_L;
	UP_IOout3_L; UP_IOout4_L; UP_IOout5_L; 
}

/*************************************************
  函数名称: UP_IOout_GPIOInit    
  函数功能: 初始化IO
  被本函数调用的函数: void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
                      void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
                      void UP_IOout_AllLow(void);void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
  调用本函数的函数: 无    
  输入参数说明: 无         
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_IOout_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;			//定义GPIO初始化结构体变量

	//允许总线CLOCK,在使用GPIO之前必须允许相应端的时钟
	RCC_APB2PeriphClockCmd(
		RCC_APB2Periph_GPIOA|
		RCC_APB2Periph_GPIOD|
		RCC_APB2Periph_GPIOE|
		RCC_APB2Periph_AFIO,
		ENABLE);

	//进行端口重映射
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);	//调试端口不可用

	//初始化IO输出为0
	UP_IOout_AllLow();

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推免输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M时钟速度

	//PA14,15输出 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//PD0~1,PD3~4,输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*************************************************
  函数名称: UP_IOout_Init    
  函数功能: 初始化IOout
  被本函数调用的函数: void UP_IOout_GPIOInit(void)；       
  调用本函数的函数: void UP_System_Init(void)；
  输入参数说明: 无         
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_IOout_Init(void)
{
	UP_IOout_GPIOInit();		//初始化IO
}

/*************************************************
  函数名称: UP_IOout_SetIO    
  函数功能: 设置IO输出
  被本函数调用的函数: 无      
  调用本函数的函数: 无
  输入参数说明: Channel：对应的6个端口0~5
				        Value  ：设置端口的输出电平0/1       
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void  UP_IOout_SetIO(u8 Channel, u8 Value)
{
	if(Channel > UP_IOout_NUM || Value > 1)
		return;
	switch(Channel)								//将相应的端口设置成需要的电平
	{
		case 0: Value?UP_IOout0_H:UP_IOout0_L;break;
		case 1: Value?UP_IOout1_H:UP_IOout1_L;break;
		case 2: Value?UP_IOout2_H:UP_IOout2_L;break;
		case 3: Value?UP_IOout3_H:UP_IOout3_L;break;
		case 4: Value?UP_IOout4_H:UP_IOout4_L;break;
		case 5: Value?UP_IOout5_H:UP_IOout5_L;break;
		default: break;
	}
}

/*************************************************
  函数名称: UP_IOout_SetALLIO   
  函数功能: 同时设置6路模拟舵机端口IO输出电平，值0x00~0x3F
  被本函数调用的函数: 无      
  调用本函数的函数: 无
  输入参数说明: Value  ：设置端口的输出电平0/1       
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void  UP_IOout_SetALLIO(u8 Value)
{
	u8 i;
	for(i=0; i<8; i++)
	{
		g_UP_IOVal[i] = Value&0x01;
		switch(i)								//将相应的端口设置成需要的电平
		{
			case 0: Value?UP_IOout0_H:UP_IOout0_L;break;
			case 1: Value?UP_IOout1_H:UP_IOout1_L;break;
			case 2: Value?UP_IOout2_H:UP_IOout2_L;break;
			case 3: Value?UP_IOout3_H:UP_IOout3_L;break;
			case 4: Value?UP_IOout4_H:UP_IOout4_L;break;
			case 5: Value?UP_IOout5_H:UP_IOout5_L;break;	
			default: break;
		}
		Value >>= 1;	
	}
}						

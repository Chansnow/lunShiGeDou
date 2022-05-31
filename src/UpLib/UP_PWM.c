/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  : 陈中元  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
/******************************************************************/ 

#include "STM32Lib\\stm32f10x.h"
#include "UP_PWM.h"

//常量宏定义
#define UP_PWM_NUM		4					//PWM通道数目

//输出宏定义（注意有个非门转向）
#define UP_PWM0_L		(GPIOB->BSRR = GPIO_Pin_6)
#define UP_PWM0_H		(GPIOB->BRR = GPIO_Pin_6)
#define UP_PWM1_L		(GPIOB->BSRR = GPIO_Pin_7)
#define UP_PWM1_H		(GPIOB->BRR = GPIO_Pin_7)
#define UP_PWM2_L		(GPIOB->BSRR = GPIO_Pin_8)
#define UP_PWM2_H		(GPIOB->BRR = GPIO_Pin_8)	
#define UP_PWM3_L		(GPIOB->BSRR = GPIO_Pin_9)
#define UP_PWM3_H		(GPIOB->BRR = GPIO_Pin_9)	

u32 g_UP_PWMPeriod = 24000;					//PWM周期（计数值）
u16 g_UP_PWMDutyTime[UP_PWM_NUM] = {2048,2048,2048,2048};		//PWM占空比
u8  g_UP_bPWMMode[UP_PWM_NUM] = {0};		//是否是PWM模式
TIM_OCInitTypeDef  g_TIM_OCInitStructure; 	//初始化比较器用的变量


//PWM相关初始化
void UP_PWM_Init(void)	
{
	//Timer4的4个输出比较做4路PWM
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	//使能端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	UP_PWM0_L;
	UP_PWM1_L;
	UP_PWM2_L;
	UP_PWM3_L;
	//GPIO设置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//推挽复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//50M时钟速度
	//PB6,7,8,9输出 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Timer4基本设置   
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Prescaler = 2;						//3分频，24MHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseStructure.TIM_Period = 24000;						//计数值24000，1KHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

	//比较输出通道设置
	g_TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//PWM模式1
	g_TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//正向通道有效
	g_TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;//反向通道无效
	g_TIM_OCInitStructure.TIM_Pulse = 12000; 							//50%占空时间
	g_TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 		//输出极性
	g_TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;     //互补端的极性  
	g_TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	g_TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
 
//	TIM_OC1Init(TIM4,&g_TIM_OCInitStructure); 						//通道1
//	TIM_OC2Init(TIM4,&g_TIM_OCInitStructure); 						//通道2
//	TIM_OC3Init(TIM4,&g_TIM_OCInitStructure); 						//通道3
//	TIM_OC4Init(TIM4,&g_TIM_OCInitStructure); 						//通道4
	//TIM4计数使能
	TIM_Cmd(TIM4,ENABLE);
	//TIM4 PWM输出使能
	TIM_CtrlPWMOutputs(TIM4,ENABLE);
}

//设置占空时间0~4095
void UP_PWM_SetDutyTime(u8 Channel, u16 DutyTime)	
{
	if(Channel > UP_PWM_NUM || DutyTime > 4095)
		return;
	g_UP_PWMDutyTime[Channel] = DutyTime;
	switch(Channel)
	{
	case 0:
		TIM4->CCR1 = (g_UP_PWMPeriod*DutyTime)/4095; break;
	case 1:
		TIM4->CCR2 = (g_UP_PWMPeriod*DutyTime)/4095; break;
	case 2:
		TIM4->CCR3 = (g_UP_PWMPeriod*DutyTime)/4095; break;
	case 3:
		TIM4->CCR4 = (g_UP_PWMPeriod*DutyTime)/4095; break;
	default: 
		break;
	}
}

//设置频率
void UP_PWM_SetFrequency(u32 Frequency)
{
	u16 temp = 0;
	if(Frequency != 0)
	{
		TIM4->PSC = temp = 2000/Frequency;		//分频值，目标频率越低分频越大
		TIM4->ARR = g_UP_PWMPeriod = 72000000/(temp+1)/Frequency;	//计数值
		temp = g_UP_PWMPeriod>>1;
		TIM4->CCR1 = temp;			//占空时间默认50%
		TIM4->CCR2 = temp;
		TIM4->CCR3 = temp;
		TIM4->CCR4 = temp;
	}
}

//设置IO输出
void  UP_PWM_SetIO(u8 Channel, u8 Value)
{
	if(Channel > UP_PWM_NUM || g_UP_bPWMMode[Channel] == 1)
		return;
	switch(Channel)								//将相应的端口设置成需要的电平
	{
		case 0: Value?UP_PWM0_H:UP_PWM0_L;break;
		case 1: Value?UP_PWM1_H:UP_PWM1_L;break;
		case 2: Value?UP_PWM2_H:UP_PWM2_L;break;
		case 3: Value?UP_PWM3_H:UP_PWM3_L;break;	
		default: break;
	}
}

//使能PWM模式输出
void  UP_PWM_Enable(u8 Channel, FunctionalState NewState)
{  
	if(Channel > UP_PWM_NUM)
		return;
	if(NewState == ENABLE)
	{
		g_TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//正向通道有效
		g_TIM_OCInitStructure.TIM_Pulse = (g_UP_PWMPeriod*g_UP_PWMDutyTime[Channel])/4095; 	//占空时间
		g_UP_bPWMMode[Channel] = 1;
	}
	else
	{
		g_TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; 	//正向通道无效
		g_UP_bPWMMode[Channel] = 0;
		UP_PWM_SetIO(Channel,0);
	}
	switch(Channel)
	{
	case 0:
		TIM_OC1Init(TIM4,&g_TIM_OCInitStructure); break;
	case 1:
		TIM_OC2Init(TIM4,&g_TIM_OCInitStructure); break;
	case 2:
		TIM_OC3Init(TIM4,&g_TIM_OCInitStructure); break;
	case 3:
		TIM_OC4Init(TIM4,&g_TIM_OCInitStructure); break;
	default: 
		break;
	}
}					


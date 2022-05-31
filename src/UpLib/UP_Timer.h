/******************************************************************/
//	Copyright (C), 2011-2012, �������� 
//  Author   	  	: ����Ԫ  
//  Reviser				: �����
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
/******************************************************************/ 

#ifndef TIMER_H
#define TIMER_H

#include "STM32Lib\\stm32f10x.h"

void TIM4_Int_Init(u16 arr,u16 psc);
void TIM5_Int_Init(u16 arr,u16 psc);

//��ʱ����غ궨��
#define TIMER_CHANNEL0	0
#define TIMER_CHANNEL1	1
#define TIMER_CHANNEL2	2
#define TIMER_CHANNEL3	3

//Ӳ����ʼ��
extern void UP_Timer_Init(void);								//��ʱ����س�ʼ��
extern void UP_Timer_EnableIT(u32 TimerChannel, u32 Time_us);	//ʹ�ܼ�ʱ���ж�
extern void UP_Timer_DisableIT(u32 TimerChannel);				//���ܼ�ʱ���ж�
extern void UP_Timer_SetHadler(u32 channel,void (*ApplicationAddress)(u32));//���ö�ʱ���ж���ں���
extern u32 UP_Timer_GetCount(void);								//��ȡ��ʱ������ֵ��32λ��,ÿ����ֵ1us
extern void UP_Timer_CleanCount(void);							//�����ʱ������ֵ
extern void Edge(void);

#endif

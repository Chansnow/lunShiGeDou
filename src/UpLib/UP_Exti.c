/******************************************************************/
//	Copyright (C), 2011-2013, �������� 
//  Author   	  : ����Ԫ  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
//  Reviser				: �����
//  Update Date   : 2013/09/24
//  Version   	  : 1.3          
//  Description   : Change GPIO Settings and EXTI line Settings.
/******************************************************************/ 

#include "UP_Exti.h" 
#include "UP_Globle.h"

/*************************************************
  ��������: UP_Exti_Init
  ��������: �ⲿ�жϳ�ʼ��
  �����������õĺ���: ��        
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
*************************************************/
void UP_Exti_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//���Ӱ���IO�ڵ��ж���
	if(g_UP_ExtiFlag & EXTI_UP)
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource14);
	if(g_UP_ExtiFlag & EXTI_DOWN)
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource13);
	if(g_UP_ExtiFlag & EXTI_OK)
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource15);
	if(g_UP_ExtiFlag & EXTI_BACK)
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource12);
	
	//����AD�ڵ��ж���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
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
  ��������: UP_Exti_EnableIT
  ��������: ʹ���ⲿ�ж�
  �����������õĺ���: ��        
  ���ñ������ĺ���: ��    
  �������˵��: Channel�������õ��ⲿ�жϵ�ͨ����
                EXTITrigger_TypeDef TriggerMode�������õ��ⲿ�жϴ����źŵ�ģʽ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
*************************************************/
void UP_Exti_EnableIT(u32 Channel, EXTITrigger_TypeDef TriggerMode)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	g_UP_ExtiFlag |= Channel;
	//�����ж���
	EXTI_InitStructure.EXTI_Line = Channel;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = TriggerMode;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);		
}

/*************************************************
  ��������: UP_Exti_SetHadler
  ��������: �����ⲿ�ж���ں���
  �����������õĺ���: ��        
  ���ñ������ĺ���: ��    
  �������˵��: ����ApplicationAddressΪָ������
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
*************************************************/
void UP_Exti_SetHadler(void (*ApplicationAddress)(u32))
{
	if(ApplicationAddress != 0)
		g_UP_ExtiITAddress = (u32)ApplicationAddress;	
}

/*************************************************
  ��������: UP_Exti_DisableIT
  ��������: �����ⲿ�ж�
  �����������õĺ���: ��        
  ���ñ������ĺ���: ��    
  �������˵��: ChannelΪ���ܵ�ͨ����
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
*************************************************/
void UP_Exti_DisableIT(u32 Channel)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	g_UP_ExtiFlag &= ~Channel;
	//�����ж���
	EXTI_InitStructure.EXTI_Line = Channel;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);		
}
			

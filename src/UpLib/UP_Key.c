/******************************************************************/
//	Copyright (C), 2011-2013, �������� 
//  Author   	  	: ����Ԫ  
//  Reviser				: �����
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
//  Reviser				: �����
//  Update Date   : 2013/07/18
//  Version   	  : 1.3.1         
//  Description   : Change GPIO configuration for keys.
/******************************************************************/ 

#include "UP_Key.h" 

/*************************************************
  ��������: UP_Key_Init
  ��������: ������ʼ��
  �����������õĺ���: ��        
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��:��        
*************************************************/
void UP_Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;											//����GPIO��ʼ���ṹ�����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);			//ʹ��GPIODʱ��
	
	//PD12~15��������
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12|GPIO_Pin_13|
																 GPIO_Pin_14|GPIO_Pin_15;		//ѡ��PD12~PD15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;							//ѡ����������ģʽ
	GPIO_Init(GPIOD, &GPIO_InitStructure);										//����PD12~15Ϊ��������

	//USB�ж����
	GPIO_ResetBits(GPIOE, GPIO_Pin_2);												//���PE2�˿�
	/* E2-DEV���ƿ� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);			//ʹ��GPIOEʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;									//ѡ��PE2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;					//��������������Ϊ2MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;					//ѡ���������ģʽ
	GPIO_Init(GPIOE, &GPIO_InitStructure);										//����PE2Ϊ�������
}

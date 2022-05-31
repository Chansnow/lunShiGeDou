/******************************************************************/
//	Copyright (C), 2011-2013, �������� 
//  Author   	  : ����Ԫ  
//  Reviser				: �����
//  Update Date   : 2013/07/12
//  Version   	  : 1.2.1            
//  Description   :  modification for new controller
/******************************************************************/ 

#include "UP_Bluetooth.h" 
#include "UP_UART.h"
#include "UP_Globle.h"

#define HC_KEY_L		(GPIOD->ODR &= ~GPIO_Pin_7)
#define HC_KEY_H		(GPIOD->ODR |= GPIO_Pin_7)

//������ʼ��
void UP_Bluetooth_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	//PD7���������ƶ�
	HC_KEY_L;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  //�������
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//ʹ���������ݽ����ж�
void UP_Bluetooth_EnableIT(void)
{
	g_UP_bBluetoothIT = TRUE;		
}

//�����������ݽ����ж���ں���
void UP_SetBluetoothHadler(void (*ApplicationAddress)(u32))
{
	if(ApplicationAddress != 0)
		g_UP_BluetoothITAddress = (u32)ApplicationAddress;	
}

//��������һ���ַ�
void UP_Bluetooth_Putc(unsigned char c)
{
	UP_UART1_Putc(c);
} 

//��������һ���ַ�	
void UP_Bluetooth_Puts(char * str)
{
	UP_UART1_Puts(str);
}			

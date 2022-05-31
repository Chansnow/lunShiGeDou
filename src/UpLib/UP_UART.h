/******************************************************************/
//	Copyright (C), 2011-2013, �������� 
//  Author   	  	: ����Ԫ  
//  Reviser				: �����
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
//  Update Date   : 2013/07/12
//  Version   	  : 1.3.1          
//  Description   : Modification for new controller
/******************************************************************/ 

#ifndef UART_H
#define UART_H

//����3���ͽ���ʹ�ܶ˿ں궨��
#define UART3_RXEN 		(GPIOE->ODR |= GPIO_Pin_15)
#define UART3_RXDS 		(GPIOE->ODR &= ~GPIO_Pin_15)
#define UART3_TXEN 		(GPIOE->ODR |= GPIO_Pin_14)
#define UART3_TXDS 		(GPIOE->ODR &= ~GPIO_Pin_14)

//������غ���
extern void UP_UART_Init(void);					//UART��س�ʼ��

extern void UP_EnableBluetoothIT(u32 BaudRate);		//ʹ���������ݽ����ж�
extern void UP_SetBluetoothHadler(void (*ApplicationAddress)(u32));	//�����������ݽ����ж���ں���
extern void UP_EnableZigbeeIT(u32 BaudRate);		//ʹ��Zigbee���ݽ����ж�
extern void UP_SetZigbeeHadler(void (*ApplicationAddress)(u32));	//����Zigbee���ݽ����ж���ں���
extern void UP_EnableUSR232IT(u32 BaudRate);		//ʹ��USR232���ݽ����ж�
extern void UP_SetUSR232Hadler(void (*ApplicationAddress)(u32));	//����USR232���ݽ����ж���ں���

extern void UP_UART1_Putc(unsigned char c); 	//UART1����һ���ַ�
extern void UP_UART1_Puts(char * str);			//UART1����һ���ַ�
extern void UP_UART4_Putc(unsigned char c); 	//UART4����һ���ַ�
extern void UP_UART4_Puts(char * str);			//UART4����һ���ַ�
extern void UP_UART5_Putc(unsigned char c); 	//UART5����һ���ַ�
extern void UP_UART5_Puts(char * str);			//UART5����һ���ַ�

extern void UP_Uart3_SendCDSFrame(u8 id, u8 len, u8 Cmd, u8* pData);	//�������ֶ��Э��֡

#endif

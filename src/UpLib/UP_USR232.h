/******************************************************************/
//	Copyright (C), 2011-2013, �������� 
//  Author   	  : �����  
//  Update Date   : 2013/07/15
//  Version   	  : 1.0            
//  Description   :  
/******************************************************************/

#ifndef USR232_H
#define USR232_H

#include "STM32Lib\\stm32f10x.h"

//USR232��غ���
void UP_USR232_EnableIT(void);					//ʹ��USR232���ݽ����ж�
void UP_SetUSR232Hadler(void (*ApplicationAddress)(u32));		//����USR232���ݽ����ж���ں���
void UP_USR232_Putc(unsigned char c);		//USR232����һ���ַ�
void UP_USR232_Puts(char * str);				//USR232����һ���ַ�	


#endif

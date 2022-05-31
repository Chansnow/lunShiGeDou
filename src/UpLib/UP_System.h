/******************************************************************/
//	Copyright (C), 2011-2013, �������� 
//  Author   	  	: ����Ԫ  
//  Reviser				: �����
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
//  Reviser				: �����
//  Update Date   : 2013/07/15
//  Version   	  : 1.3          
//  Description   : Delete and add some headfiles
/******************************************************************/ 

#ifndef SYSTEM_H
#define SYSTEM_H

#include "STM32Lib\\stm32f10x.h"
#include "UP_Globle.h" 
#include "UP_LCD.h"		
#include "UP_Key.h"   
#include "UP_ADC.h"	 	
#include "UP_PWM.h"
#include "UP_IOout.h"
#include "UP_Timer.h"
#include "UP_UART.h"
#include "UP_CDS5500.h"
#include "UP_PWM.h"
#include "UP_Exti.h"
#include <stdio.h>					//printf ������
#include <string.h>


extern void UP_System_Init(void);
#define DELAY_TIMES  1000   /***********woody ����ָ��֮���ʱ����***********/

#endif


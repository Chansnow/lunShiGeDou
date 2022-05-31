/******************************************************************/
//	Copyright (C), 2011-2012, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
/******************************************************************/

#ifndef ADC_H
#define ADC_H

//硬件初始化
extern void  UP_ADC_Init(void);								//AD相关初始化
extern u16   UP_ADC_GetValue(u8 Channel);			//获取AD采样值，输入通道0~15，返回ADC值0~4095对应0~5V
extern u8    UP_ADC_GetIO(u8 Channel);				//获取IO采样值，输入通道0~15，返回0或1
extern u16   UP_ADC_GetAllIO(void);						//获取IO采样值，返回16路IO状态，16位无符号整形每一位对应一路

#endif

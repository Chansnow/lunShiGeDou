/******************************************************************/
//	Copyright (C), 2011-2012, �������� 
//  Author   	  	: ����Ԫ  
//  Reviser				: �����
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
/******************************************************************/

#ifndef ADC_H
#define ADC_H

//Ӳ����ʼ��
extern void  UP_ADC_Init(void);								//AD��س�ʼ��
extern u16   UP_ADC_GetValue(u8 Channel);			//��ȡAD����ֵ������ͨ��0~15������ADCֵ0~4095��Ӧ0~5V
extern u8    UP_ADC_GetIO(u8 Channel);				//��ȡIO����ֵ������ͨ��0~15������0��1
extern u16   UP_ADC_GetAllIO(void);						//��ȡIO����ֵ������16·IO״̬��16λ�޷�������ÿһλ��Ӧһ·

#endif

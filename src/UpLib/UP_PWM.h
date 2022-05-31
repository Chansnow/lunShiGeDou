/******************************************************************/
//	Copyright (C), 2011-2012, �������� 
//  Author   	  : ����Ԫ  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
/******************************************************************/

#ifndef PWM_H
#define PWM_H

extern void UP_PWM_Init(void);								//PWM��س�ʼ��
extern void UP_PWM_Enable(u8 Channel, FunctionalState NewState);	//ʹ��PWMģʽ�����ͨ��0~3��״̬ENABLE��DISABLE
extern void UP_PWM_SetDutyTime(u8 Channel, u16 DutyTime);	//���øߵ�ƽʱ��0~4095��Ӧ0%~100%
extern void UP_PWM_SetFrequency(u32 Frequency);				//����Ƶ�ʣ�Hz����50~1000000
extern void UP_PWM_SetIO(u8 Channel, u8 Value);				//����PWM�˿�IO�����ƽ��ͨ��0~3��ֵ0��1

#endif


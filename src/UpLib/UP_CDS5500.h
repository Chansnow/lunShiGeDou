/******************************************************************/
//	Copyright (C), 2011-2012, �������� 
//  Author   	  : ����Ԫ  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
/******************************************************************/

#ifndef CDS5500_H
#define CDS5500_H

#define CDS_SEVMODE			0			//���ģʽ
#define CDS_MOTOMODE		1			//���ģʽ

extern void UP_CDS_SetMode(u8 id, u8 mode);					//����CDS���ֶ��ģʽ��idΪ���ID
															//CDS_SEVMODEΪ���ģʽ��CDS_MOTOMODEΪ���ģʽ
extern void UP_CDS_SetAngle(u8 id, u16 angle, u16 speed);	//�������ֶ�������ģʽ�£��ǶȺ��ٶ�
															//�Ƕ�0~1023��Ӧ0~300�㣬�ٶ�0~1023
extern void UP_CDS_SetSpeed(u8 id, s16 speed);				//�������ֶ�������ģʽ�£��ٶȣ���Χ-1023~+1023

extern void UP_CDS_Set4MotoSpeed(u8 id[4], s16 speed[4]);	//ͬʱ����4·���ֶ�����ٶȣ����ģʽ�£�


#endif

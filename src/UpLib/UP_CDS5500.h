/******************************************************************/
//	Copyright (C), 2011-2012, 北京博创 
//  Author   	  : 陈中元  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
/******************************************************************/

#ifndef CDS5500_H
#define CDS5500_H

#define CDS_SEVMODE			0			//舵机模式
#define CDS_MOTOMODE		1			//电机模式

extern void UP_CDS_SetMode(u8 id, u8 mode);					//设置CDS数字舵机模式，id为舵机ID
															//CDS_SEVMODE为舵机模式，CDS_MOTOMODE为电机模式
extern void UP_CDS_SetAngle(u8 id, u16 angle, u16 speed);	//设置数字舵机（舵机模式下）角度和速度
															//角度0~1023对应0~300°，速度0~1023
extern void UP_CDS_SetSpeed(u8 id, s16 speed);				//设置数字舵机（电机模式下）速度，范围-1023~+1023

extern void UP_CDS_Set4MotoSpeed(u8 id[4], s16 speed[4]);	//同时设置4路数字舵机的速度（电机模式下）


#endif

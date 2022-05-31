/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  : 陈中元  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
/******************************************************************/

#ifndef ZIGBEE_H
#define ZIGBEE_H

#include "STM32Lib\\stm32f10x.h"

typedef struct _UP_ZIGBEE_FRAME
{
	u8 frame_type;
	u8 frame_len;
	u8 *frame_data;
	u8 rec_sign;
	u32 rec_count;
}UP_ZIGBEE_FRAME;




extern UP_ZIGBEE_FRAME UP_Zigbee_RecFrame;


//Zigbee相关函数
void UP_Zigbee_EnableIT(void);					//使能Zigbee数据接收中断
void UP_SetZigbeeHadler(void (*ApplicationAddress)(u32));		//传递Zigbee数据接收中断入口函数
void UP_Zigbee_Putc(unsigned char c);		//Zigbee发送一个字符
void UP_Zigbee_Puts(char * str);				//Zigbee发送一串字符	
void UP_Zigbee_Rec(u32 data);
void UP_Zigbee_SetID(u8 ID);
void UP_Zigbee_SetDeviceType(u8 type);
extern void UP_Zigbee_RequireSensor(u8 S_ID,u8 D_ID);
void UP_Zigbee_SendData(u8 S_ID,u8 D_ID,u8 len,u8 cmd,u8 *data);
void UP_Zigbee_GetConfig(void);
void UP_Zigbee_GetID(void);
extern void Zigbee_TIMER_handler(u32 null);
extern void UP_Push_TxData(u8 S_ID,u8 D_ID,u8 len,u8 cmd,u8 *data);
#endif

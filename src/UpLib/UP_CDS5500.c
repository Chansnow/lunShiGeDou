/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  : 陈中元  
//  Update Date   : 2011/06/12
//  Version   	  : 1.2            
//  Description   :  
//  Update Date   : 2013/09/24
//  Version   	  : 1.2.1            
//  Description   :  temp modify UP_CDS_SetMode()'s delay
/******************************************************************/ 

#include "STM32Lib\\stm32f10x.h"
#include "UP_CDS5500.h"
#include "UP_UART.h"
#include "UP_Globle.h"

#define CMD_READ			0x02		//数字舵机读命令
#define CMD_WRITE			0x03		//数字舵机写命令
#define CMD_SWRITE		0x83		//数字舵机同步写命令

/*************************************************
  函数名称: UP_CDS_SetMode
  函数功能: 舵机模式设置，ID号设置，范围1——253.
  被本函数调用的函数: UP_Uart3_SendCDSFrame(u8 id, u8 len, u8 cmd, u8* pData);        
  调用本函数的函数: 无    
  输入参数说明: id是设置舵机的ID，mode是指设置舵机工作模式，
	              可以设置成CDS_SEVMODE和CDS_MOTOMODE模式。      
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_CDS_SetMode(u8 id, u8 mode)
{
	u8 buf[5];
	if(mode > 1)
		return;
	buf[0] = 0x06;
	if(mode == CDS_SEVMODE)
	{
		buf[1] = 0;		
		buf[2] = 0;
		buf[3] = 0xff;
		buf[4] = 0x03;
	}
	else if(mode == CDS_MOTOMODE)
	{
		buf[1] = 0;		
		buf[2] = 0;
		buf[3] = 0;
		buf[4] = 0;
	}
	UP_Uart3_SendCDSFrame(id,0x07,CMD_WRITE,buf);
	UP_delay_ms(30);
}

/*************************************************
  函数名称: UP_CDS_SetAngle
  函数功能: 设置对应ID号的舵机转角(0~1023对应0~300°)，速度（0~1023，约1圈1s）。
  被本函数调用的函数: UP_Uart3_SendCDSFrame(u8 id, u8 len, u8 cmd, u8* pData);        
  调用本函数的函数: 无    
  输入参数说明: id是设置舵机的ID，mode是指设置舵机工作模式，
	              可以设置成CDS_SEVMODE和CDS_MOTOMODE模式，
                speed设置舵机速度，0~1023，约1圈1s。
  输出参数说明: 无       
  函数返回值: 无 
  其它说明:无        
*************************************************/
void UP_CDS_SetAngle(u8 id, u16 angle, u16 speed)
{
	u8 buf[5];
	if(angle > 1023 || speed > 1023)
		return;
	buf[0] = 0x1E;
	buf[1] = angle;		
	buf[2] = angle>>8;
	buf[3] = speed;
	buf[4] = speed>>8;
	UP_Uart3_SendCDSFrame(id,0x07,CMD_WRITE,buf);
}

/*************************************************
  函数名称: UP_CDS_SetSpeed
  函数功能: 设置对应ID号的电机速度（0~1023，约1圈1s）。
  被本函数调用的函数: UP_Uart3_SendCDSFrame(u8 id, u8 len, u8 cmd, u8* pData);        
  调用本函数的函数: 无    
  输入参数说明: id是设置电机模式的ID，
	              speed设置舵机速度，0~1023，约1圈1s。
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_CDS_SetSpeed(u8 id, s16 speed)
{
	u8 buf[5];
	u16 temp;
	if(speed > 1023 || speed < -1023)
		return;
	temp = speed>0?speed:-speed;
	buf[0] = 0x20;
	buf[1] = temp;
	buf[2] = temp>>8;
	if(speed < 0)
		buf[2] |= 0x04;
	UP_Uart3_SendCDSFrame(id,0x05,CMD_WRITE,buf);
	UP_delay_ms(5);
}

/*************************************************
  函数名称: UP_CDS_Set4MotoSpeed
  函数功能: 同时设置对应ID的4个电机的速度，可以调用此函数用于四驱车前进、后退、左转、右转的动作调试。
  被本函数调用的函数: 无 
  调用本函数的函数: 无    
  输入参数说明:  id[4]可以设置4个电机模式的ID相同,  speed[4]设置对应ID的4个电机的速度。  
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void UP_CDS_Set4MotoSpeed(u8 id[4], s16 speed[4])
{
	u8 i;
	u8 pos = 2;
	u8 buf[20];
	u16 temp;
	for(i=0; i<4; i++)
	{
		if(speed[i] > 1023 || speed[i] < -1023)
			return;
	}
	buf[0] = 0x20; 		//地址
	buf[1] = 0x02; 		//长度
	for(i=0; i<4; i++)
	{
		temp = speed[i]>0?speed[i]:-speed[i];
		buf[pos++] = id[i];	//ID
		buf[pos++] = temp;
		buf[pos++] = temp>>8;
		if(speed[i] < 0)
			buf[pos-1] |= 0x04;
	}
	UP_Uart3_SendCDSFrame(0xFE,pos+2,CMD_SWRITE,buf);
}

/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
/******************************************************************/ 

#include "UP_Globle.h"

//蓝牙相关参数
bool g_UP_bBluetoothIT = FALSE;				//是否启用蓝牙数据接收中断
u32 g_UP_BluetoothBaudRate = 115200;	//蓝牙通信波特率
u32 g_UP_BluetoothITAddress = 0;			//蓝牙中断入口函数

//Zigbee相关参数
bool g_UP_bZigbeeIT = FALSE;					//是否启用Zigbee数据接收中断
u32 g_UP_ZigbeeBaudRate = 19200;			//Zigbee通信波特率
u32 g_UP_ZigbeeITAddress = 0;					//Zigbee中断入口函数

//USR232相关参数
bool g_UP_bUSR232IT = FALSE;					//是否启用USR232数据接收中断
u32 g_UP_USR232BaudRate = 115200;			//USR232波特率
u32 g_UP_USR232ITAddress = 0;					//USR232中断入口函数

//计时器相关参数
bool g_UP_bTimerIT[4] = {FALSE,FALSE,FALSE,FALSE};		//是否启用定时器中断
u32 g_UP_TimerITAddress = 0;					//定时器中断入口函数

u32 g_UP_Timer0ITAddress = 0;
u32 g_UP_Timer1ITAddress = 0;
u32 g_UP_Timer2ITAddress = 0;
u32 g_UP_Timer3ITAddress = 0;

//外部中断相关参数
u32 g_UP_ExtiFlag = 0;								//外部中断使能的通道
u32 g_UP_ExtiITAddress = 0;						//外部中断入口函数

//其他
volatile u32 g_SysTickTimer = 0;			//1ms精确系统时钟计时器计数器（直接在中断函数里被改变值的变量需要加volatile声明）

/*************************************************
  函数名称: UP_delay_us；     
  函数功能: 以1us为单位延时
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: us意即微秒       
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_delay_us(u32 us) 					//以us为单位延时
{
	u16 i;
	while(us)
	{
		us--;
		for(i=0;i<8;i++)__nop();
	}
}

/*************************************************
  函数名称: void UP_delay_ms   
  函数功能: 以ms为单位延时
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: ms意即毫秒        
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_delay_ms(u32 ms)					//以ms为单位延时
{
//	g_SysTickTimer = ms;
//	while(g_SysTickTimer);
	u16 i;
	while(ms)
	{
		ms--;
		for(i=0;i<8000;i++)__nop();
	}
}

/*************************************************
  函数名称: u32 abs 
  函数功能: 求整数绝对值
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: signed long型变量       
  输出参数说明: 无       
  函数返回值: 变量的绝对值
  其它说明:无        
*************************************************/
u32 abs(s32 i)										//求整数绝对值
{
	return i>=0?i:-i;
}

/*************************************************
  函数名称: double fabs
  函数功能: 求浮点数绝对值
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: double型变量     
  输出参数说明: 无       
  函数返回值: 变量的绝对值
  其它说明:无        
*************************************************/
double fabs(double i)							//求浮点数绝对值
{
	return i>=0?i:-i;
}

#include"UP_System.h"
#include "UP_USR232.h" 
#include "UP_UART.h"
#include "UP_Globle.h"
#include "UP_Woody_VoicePlaying.h"
u8 temp;	
u32 w[2]={0x00,0x00};
u32 data1;
u32 H,L;
char  UP_Woody_StartMusic[5]={0x55,0xAA,0x05,0x22,0x26};//启动语音播放指令
char  UP_Woody_MusicPlaying[7]={0x55,0xAA,0x07,0x21,0x00,0x01,0x23};//语音播放指令，此处播放0001歌曲
char  UP_Woody_ClosingMusic[5]={0x55,0xAA,0x05,0x23,0x27};//关闭语音播放指令
char  UP_Woody_ReturnMusic[20]={0x00};//存放语音播放返回的数据

/*************************************************
  函数名称: UP_Woody_StartMusicPlay   
  函数功能: 启动语音播放
  被本函数调用的函数: UP_USR232_Putc
  调用本函数的函数: 无    
  输入参数说明:  无 
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void UP_Woody_StartMusicPlay(void)
{
	for(temp=0;temp<5;temp++)
  {
	   UP_USR232_Putc(UP_Woody_StartMusic[temp]);
  }	
  UP_delay_ms(DELAY_TIMES);
}

/*************************************************
  函数名称: UP_Woody_CloseMusicPlay 
  函数功能: 关闭语音播放
  被本函数调用的函数: UP_USR232_Putc
  调用本函数的函数: 无    
  输入参数说明:  无 
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void UP_Woody_CloseMusicPlay(void)
{
	for(temp=0;temp<5;temp++)
  {
	   UP_USR232_Putc(UP_Woody_ClosingMusic[temp]);
  }	
	UP_delay_ms(DELAY_TIMES);
}

/*************************************************
  函数名称: UP_Woody_PlayingMusic
  函数功能: 按照ID号，播放相应歌曲 
  被本函数调用的函数: UP_UART5_Putc
  调用本函数的函数: 无    
  输入参数说明:  data1：范围0~255，十进制数，对应存放的歌曲ID：0x00~0x31
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void UP_Woody_PlayingMusic(u32 data1)
{	 
		 w[0]=0x00;
		 w[1]=data1;
	
	
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xaa);
	UP_UART5_Putc(0x07);
	UP_UART5_Putc(0x21);
	UP_UART5_Putc(w[0]);
	UP_UART5_Putc(w[1]);
	UP_UART5_Putc(0x34);
	UP_delay_ms(DELAY_TIMES);
}

// /*************************************************
//   函数名称: USR232_Voice_Hadler
//   函数功能: 定义语音播放的中断入口函数
//   被本函数调用的函数: 无
//   调用本函数的函数: 无    
//   输入参数说明: TempData:存储uart5接受寄存器的内容
//   输出参数说明: 无       
//   函数返回值: 无
//   其它说明: 无        
// *************************************************/	
// void USR232_Voice_Hadler(u32 TempData)
// {
// 	
// }

// /*************************************************
//   函数名称: USR232_Voice_Hadler
//   函数功能: 语音播放初始化
//   被本函数调用的函数: UP_EnableUSR232IT(u32 BaudRate);UP_SetUSR232Hadler(void (*ApplicationAddress)(u32));
//   调用本函数的函数: 无    
//   输入参数说明: TempData:存储uart5接受寄存器的内容
//   输出参数说明: 无       
//   函数返回值: 无
//   其它说明: 无        
// *************************************************/
// void UP_Woody_VoicePlaying_Init(void)
//  {   
// //串口使能请放在系统初始化之前，因为使能过程设定了串口的中断入口和波特率
// 	//使能UART5接收中断 (USR232串口)
// 	UP_EnableUSR232IT(19200);
// 	UP_SetUSR232Hadler(USR232_Voice_Hadler);
//  } 
 



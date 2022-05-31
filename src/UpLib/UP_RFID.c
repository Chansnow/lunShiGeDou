#include "STM32Lib\\stm32f10x.h"

#include "UP_Globle.h"
#include "UP_Timer.h"
#include "UP_UART.h"
#include "UP_USR232.h"

u16 RF_RecTimeCount = 0;
u8 RF_Start = 0;
//u8 RF_ReadSign = 0;
u8 RF_RecCount = 0;
u8 RF_RecBuf[10];
u32 RF_Add = 0;
u8 UP_RFID_ReadSign = 0;

/*************************************************
  函数名称: RFIDParser 
  函数功能: 此函数用户无需使用，在void UP_RFID_Init(void){};中已经调用。
            主要用于把接收的卡号等赋给RF_RecBuf以及被调用等。
  被本函数调用的函数: 无  
  调用本函数的函数: 无
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void RFIDParser(u32 rec)
{	
	RF_Start = 1;
	RF_RecTimeCount = 0; 
	RF_RecBuf[RF_RecCount++] = rec;
	RF_Add++;
}

/*************************************************
  函数名称: UP_RFID_ReadCard 
  函数功能: 主要用于判断控制器收到的字节数量等是否超时
  被本函数调用的函数: 无  
  调用本函数的函数: 无
  输入参数说明:  null
                     【in】无意义
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void RFID_Timer_Handler(u32 null)
{
	if(RF_Start)
	{
		if(10 < RF_RecTimeCount++)//判断是否超时
		{
			RF_Start = 0;
			RF_RecTimeCount = 0;
			
			if(5 == RF_RecCount)
			{
				UP_RFID_ReadSign = 1;//收到5个字节的卡号后此标志置1，只有当执行UP_RFID_ReadCard读取卡号后此标志才清零
			}
			RF_RecCount = 0;
		}
	}	
}

/*************************************************
  函数名称: UP_RFID_Init 
  函数功能: 使能RFID的串口及定时器中断，此中断中判断串口接收数据是否超时。
  被本函数调用的函数: void UP_EnableUSR232IT(u32 BaudRate); 
                      void UP_SetUSR232Hadler(void (*ApplicationAddress)(u32)); 
                      void UP_Timer_EnableIT(u32 TimerChannel, u32 Time_us); 
                      void UP_Timer_SetHadler(u32 channel,void (*ApplicationAddress)(u32));
                      void RFID_Timer_Handler(u32 null);void RFIDParser(u32 rec)；    
  调用本函数的函数: 无
  输入参数说明:  空  
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_RFID_Init(void)
{
	UP_EnableUSR232IT(9600);
	UP_SetUSR232Hadler(RFIDParser);
	UP_Timer_EnableIT(TIMER_CHANNEL1,10000);//使能定时中断
	UP_Timer_SetHadler(TIMER_CHANNEL1,RFID_Timer_Handler);//设置定时中断的入口函数	
}

/*************************************************
  函数名称: UP_RFID_ReadCard 
  函数功能: 将RF_RecBuf[5]存取的卡号信息赋值给buf[5]
  被本函数调用的函数: 无  
  调用本函数的函数: 无
  输入参数说明:  将RF_RecBuf[5]存取的卡号信息赋值给buf[5] 
  输出参数说明: 无       
  函数返回值: 1或0
  其它说明:无        
*************************************************/
u8 UP_RFID_ReadCard(u8 buf[5])
{
	if(UP_RFID_ReadSign)
	{	
		UP_RFID_ReadSign = 0;
		buf[0] = RF_RecBuf[0];
		buf[1] = RF_RecBuf[1];
		buf[2] = RF_RecBuf[2];
		buf[3] = RF_RecBuf[3];
		buf[4] = RF_RecBuf[4];
		RF_RecBuf[0]=RF_RecBuf[1]=RF_RecBuf[2]=RF_RecBuf[3]=RF_RecBuf[4]=0;
		return 1;	
	}
	else
	{
		buf[0]=buf[1]=buf[2]=buf[3]=buf[4]=0;
		return 0;
	}
}

/*************************************************
  函数名称: UP_RFID_CheckID 
  函数功能: 比对读到的卡号
  被本函数调用的函数: 无  
  调用本函数的函数: 无
  输入参数说明:  ID1
                   【in】读到的卡号
                 ID2
                   【in】比对的卡号 
  输出参数说明: 无
  函数返回值: 1或0
  其它说明:无        
*************************************************/
u8 UP_RFID_CheckID(u8 *ID1,u8 *ID2)//ID1为读到的卡号，ID2为要比对的卡号
{
	u8 i;
	for(i=0;i<5;i++)
	{
		if(ID1[i] != ID2[i])
		{
			return 0;
		}
	}
	return 1;
}




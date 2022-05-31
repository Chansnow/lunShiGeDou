#include"UP_System.h"

#include "UP_Globle.h"
#include "UP_LCD.h"
#include "UP_UART.h"

u8 flage = 0;				//接收标志
u8 Tab=0;
u8 Var=0;
u8 num=0;
u16 ID;
char UP_Woody_ComparisonTables[7]={0X01,0X02,0X03,0X04,0X05,0X06,0X07};
char TestCommand[5] = {0x55,0xAA,0x05,0x01,0x05};		
char  UP_Woody_StartSpeech[5]={0x55,0xAA,0x05,0x10,0x14};
char  UP_Woody_Read[5]={0x55,0xAA,0x05,0x12,0x16};
char  UP_Woody_Closing[5]={0x55,0xAA,0x05,0x11,0x15};
char  UP_Woody_ReturnData[6]={0x00};

/*************************************************
  函数名称: UP_Woody_Speech_ClearData
  函数功能: 清零UP_Woody_ReturnData[6]
  被本函数调用的函数: 无
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/	
void UP_Woody_Speech_ClearData(void)
{
	for(Var=0;Var<6;Var++)
    {
			UP_Woody_ReturnData[Var]=0x00;
		}
}

/*************************************************
  函数名称: UP_Display_Return_Text
  函数功能: 显示测试通信时返回的数据
  被本函数调用的函数: void UP_LCD_ShowHex(u8 x,u8 y,u8 hex);UP_delay_ms(u32 ms);
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/	
void  UP_Display_Return_Text(void)
 {
	 
if(flage==0x01)
{

	  UP_delay_ms(500);
	  UP_LCD_ShowHex(1,0,UP_Woody_ReturnData[0]);
		UP_LCD_ShowHex(3,0,UP_Woody_ReturnData[1]);
	
		UP_LCD_ShowHex(5,0,UP_Woody_ReturnData[2]);
		
		UP_LCD_ShowHex(7,0,UP_Woody_ReturnData[3]);

		UP_LCD_ShowHex(9,0,UP_Woody_ReturnData[4]);
		
		flage=0;
   	UP_delay_ms(500);
	
   }		
}

/*************************************************
  函数名称: UP_Display_Return_Read
  函数功能: 显示读数据时返回的数据
  被本函数调用的函数: void UP_LCD_ShowHex(u8 x,u8 y,u8 hex);UP_delay_ms(u32 ms);
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
 void  UP_Display_Return_Read(void)
 {
	 if(flage==0x01)
	 {
	  UP_delay_ms(1000);
	  UP_LCD_ShowHex(0,1,UP_Woody_ReturnData[0]);
		
		UP_LCD_ShowHex(2,1,UP_Woody_ReturnData[1]);
		
		UP_LCD_ShowHex(4,1,UP_Woody_ReturnData[2]);
		
		UP_LCD_ShowHex(6,1,UP_Woody_ReturnData[3]);
		
		UP_LCD_ShowHex(8,1,UP_Woody_ReturnData[4]);
		
		UP_LCD_ShowHex(10,1,UP_Woody_ReturnData[5]);
	 
		flage=0;	
		UP_delay_ms(1000);
  }
}

/*************************************************
  函数名称: UP_Woody_Speech_ID_Judge
  函数功能: 语音ID号计算处理
  被本函数调用的函数: 无
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: ID,十进制数值形式，范围1~255。
  其它说明: 无        
*************************************************/
u16 UP_Woody_Speech_ID_Judge(void)
{
  ID=(UP_Woody_ReturnData[4]&0X0F)+((UP_Woody_ReturnData[4]&0XF0)>>4)*16;
	return ID;
}

/*************************************************
  函数名称: UP_Woody_Display_Speech_ID
  函数功能: 显示语音识别返回的ID
  被本函数调用的函数: UP_LCD_ClearScreen();
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 此函数显示在LCD的第三行，约3s显示一次，用户可更改显示时间。    
*************************************************/
 void UP_Woody_Display_Speech_ID(void)
  {
	 printf("\n");
	 printf("\n");
   printf("(S_ID)(%lud)\n",UP_Woody_Speech_ID_Judge());
	 UP_delay_ms(3000);
	 UP_LCD_ClearScreen();
	}
	
	
/*************************************************
  函数名称: UP_Woody_TestCommand
  函数功能: 测试LUBY与Woody之间的通信是否成功
  被本函数调用的函数: void UP_USR232_Putc(unsigned char c);
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无        
*************************************************/
void UP_Woody_Speech_TestCommand(void)
{
	for(Tab=0;Tab<5;Tab++)
  {
	   UP_USR232_Putc(TestCommand[Tab]);
  }	
}

/*************************************************
  函数名称: UP_Woody_StartSpeechRecognize
  函数功能: 启动语音识别
  被本函数调用的函数: void UP_USR232_Putc(unsigned char c);
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: "呗"的一声响，启动成功，无数据返回       
*************************************************/
void UP_Woody_StartSpeechRecognize(void)
{
	revoic_flage =0xAC; 
	for(Tab=0;Tab<5;Tab++)
  {
	   UP_USR232_Putc(UP_Woody_StartSpeech[Tab]);
  }	
	UP_delay_ms(DELAY_TIMES);
}

/*************************************************
  函数名称: UP_Woody_CloseSpeechRecognize
  函数功能: 关闭语音识别
  被本函数调用的函数: void UP_USR232_Putc(unsigned char c);
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/
void UP_Woody_CloseSpeechRecognize(void)
{
	revoic_flage =0; 
	for(Tab=0;Tab<5;Tab++)
  {
	   UP_USR232_Putc(UP_Woody_Closing[Tab]);
  }	
	UP_delay_ms(DELAY_TIMES);
}

/*************************************************
  函数名称: UP_Woody_Speech_ReadData
  函数功能: 发送读数据协议
  被本函数调用的函数: void UP_USR232_Putc(unsigned char c);
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/
void UP_Woody_Speech_ReadData(void)
{
	
  for(Tab=0;Tab<5;Tab++)
   {
	   UP_USR232_Putc(UP_Woody_Read[Tab]);
   }
   UP_delay_ms(DELAY_TIMES);
   revoic_flage =0; 	 
}


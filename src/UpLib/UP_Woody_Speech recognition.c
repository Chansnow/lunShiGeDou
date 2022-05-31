#include"UP_System.h"
#include "UP_Woody_SpeechRecognition.h"
#include "UP_Globle.h"
#include "UP_LCD.h"
#include "UP_UART.h"

static u8 flage = 0;				//接收标志
static u8 temp=0;
static u8 i=0;
char UP_Woody_ComparisonTables[7]={0X01,0X02,0X03,0X04,0X05,0X06,0X07};
char TestCommand[5] = {0x55,0xAA,0x05,0x01,0x05};		
char  UP_Woody_StartSpeech[5]={0x55,0xAA,0x05,0x10,0x14};

char  UP_Woody_Read[5]={0x55,0xAA,0x05,0x12,0x16};

char  UP_Woody_Closing[5]={0x55,0xAA,0x05,0x11,0x15};

char  UP_Woody_ReturnData[6]={0x00};

void UP_Clear_Data(void)
{
	for(i=0;i<6;i++)
    {
			UP_Woody_ReturnData[i]=0x00;
		}
}

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

//测试Woody，返回相同数据
void UP_Woody_TestCommand(void)
{
	for(temp=0;temp<5;temp++)
  {
	   UP_USR232_Putc(TestCommand[temp]);
  }	
}

//启动语音识别，"呗"的一声响，启动成功，无数据返回
void UP_Woody_StartSpeechRecognition(void)
{
	for(temp=0;temp<5;temp++)
  {
	   UP_USR232_Putc(UP_Woody_StartSpeech[temp]);
  }	
}

//关闭语音识别
void UP_Woody_ClosingSpeechRecognition(void)
{
	for(temp=0;temp<5;temp++)
  {
	   UP_USR232_Putc(UP_Woody_Closing[temp]);
  }	
}

//读数据，
void UP_Woody_ReadData(void)
{
  for(temp=0;temp<5;temp++)
   {
	   UP_USR232_Putc(UP_Woody_Read[temp]);
   }	
	
}
static u8 i;
static u8 num=0;

void USR232_Hadler(u32 TempData)
{
     switch(num)
	    {
				case 0:UP_Woody_ReturnData[0]=0x00;
				break;
				case 1:UP_Woody_ReturnData[1]=0x00;
				break;	
				case 2:UP_Woody_ReturnData[2]=0x00;
				break;
				case 3:UP_Woody_ReturnData[3]=0x00;
				break;
        case 4:UP_Woody_ReturnData[4]=0x00;
				break;
				case 5:UP_Woody_ReturnData[5]=0x00;
				break;
        default:
				break;				
			}
				
	flage=0x01;
	{UP_Woody_ReturnData[num++]= TempData;}
 // UP_LCD_ShowInt(7, 3, num);
	if(num==6)
	{
		num=0;
  }
}

void UP_Woody_Init(void)
 {   
//串口使能请放在系统初始化之前，因为使能过程设定了串口的中断入口和波特率
	//使能UART5接收中断 (USR232串口)
	UP_EnableUSR232IT(19200);
	UP_SetUSR232Hadler(USR232_Hadler);
 } 
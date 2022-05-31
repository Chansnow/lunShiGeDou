#include"UP_System.h"

#include "UP_Globle.h"
#include "UP_LCD.h"
#include "UP_UART.h"

u8 flage = 0;				//���ձ�־
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
  ��������: UP_Woody_Speech_ClearData
  ��������: ����UP_Woody_ReturnData[6]
  �����������õĺ���: ��
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
*************************************************/	
void UP_Woody_Speech_ClearData(void)
{
	for(Var=0;Var<6;Var++)
    {
			UP_Woody_ReturnData[Var]=0x00;
		}
}

/*************************************************
  ��������: UP_Display_Return_Text
  ��������: ��ʾ����ͨ��ʱ���ص�����
  �����������õĺ���: void UP_LCD_ShowHex(u8 x,u8 y,u8 hex);UP_delay_ms(u32 ms);
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
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
  ��������: UP_Display_Return_Read
  ��������: ��ʾ������ʱ���ص�����
  �����������õĺ���: void UP_LCD_ShowHex(u8 x,u8 y,u8 hex);UP_delay_ms(u32 ms);
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
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
  ��������: UP_Woody_Speech_ID_Judge
  ��������: ����ID�ż��㴦��
  �����������õĺ���: ��
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ID,ʮ������ֵ��ʽ����Χ1~255��
  ����˵��: ��        
*************************************************/
u16 UP_Woody_Speech_ID_Judge(void)
{
  ID=(UP_Woody_ReturnData[4]&0X0F)+((UP_Woody_ReturnData[4]&0XF0)>>4)*16;
	return ID;
}

/*************************************************
  ��������: UP_Woody_Display_Speech_ID
  ��������: ��ʾ����ʶ�𷵻ص�ID
  �����������õĺ���: UP_LCD_ClearScreen();
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: �˺�����ʾ��LCD�ĵ����У�Լ3s��ʾһ�Σ��û��ɸ�����ʾʱ�䡣    
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
  ��������: UP_Woody_TestCommand
  ��������: ����LUBY��Woody֮���ͨ���Ƿ�ɹ�
  �����������õĺ���: void UP_USR232_Putc(unsigned char c);
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
*************************************************/
void UP_Woody_Speech_TestCommand(void)
{
	for(Tab=0;Tab<5;Tab++)
  {
	   UP_USR232_Putc(TestCommand[Tab]);
  }	
}

/*************************************************
  ��������: UP_Woody_StartSpeechRecognize
  ��������: ��������ʶ��
  �����������õĺ���: void UP_USR232_Putc(unsigned char c);
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: "��"��һ���죬�����ɹ��������ݷ���       
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
  ��������: UP_Woody_CloseSpeechRecognize
  ��������: �ر�����ʶ��
  �����������õĺ���: void UP_USR232_Putc(unsigned char c);
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
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
  ��������: UP_Woody_Speech_ReadData
  ��������: ���Ͷ�����Э��
  �����������õĺ���: void UP_USR232_Putc(unsigned char c);
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
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


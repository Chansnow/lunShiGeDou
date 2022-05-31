#include"UP_System.h"
#include "UP_USR232.h" 
#include "UP_UART.h"
#include "UP_Globle.h"
#include "UP_Woody_VoicePlaying.h"
u8 temp;	
u32 w[2]={0x00,0x00};
u32 data1;
u32 H,L;
char  UP_Woody_StartMusic[5]={0x55,0xAA,0x05,0x22,0x26};//������������ָ��
char  UP_Woody_MusicPlaying[7]={0x55,0xAA,0x07,0x21,0x00,0x01,0x23};//��������ָ��˴�����0001����
char  UP_Woody_ClosingMusic[5]={0x55,0xAA,0x05,0x23,0x27};//�ر���������ָ��
char  UP_Woody_ReturnMusic[20]={0x00};//����������ŷ��ص�����

/*************************************************
  ��������: UP_Woody_StartMusicPlay   
  ��������: ������������
  �����������õĺ���: UP_USR232_Putc
  ���ñ������ĺ���: ��    
  �������˵��:  �� 
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
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
  ��������: UP_Woody_CloseMusicPlay 
  ��������: �ر���������
  �����������õĺ���: UP_USR232_Putc
  ���ñ������ĺ���: ��    
  �������˵��:  �� 
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
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
  ��������: UP_Woody_PlayingMusic
  ��������: ����ID�ţ�������Ӧ���� 
  �����������õĺ���: UP_UART5_Putc
  ���ñ������ĺ���: ��    
  �������˵��:  data1����Χ0~255��ʮ����������Ӧ��ŵĸ���ID��0x00~0x31
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��        
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
//   ��������: USR232_Voice_Hadler
//   ��������: �����������ŵ��ж���ں���
//   �����������õĺ���: ��
//   ���ñ������ĺ���: ��    
//   �������˵��: TempData:�洢uart5���ܼĴ���������
//   �������˵��: ��       
//   ��������ֵ: ��
//   ����˵��: ��        
// *************************************************/	
// void USR232_Voice_Hadler(u32 TempData)
// {
// 	
// }

// /*************************************************
//   ��������: USR232_Voice_Hadler
//   ��������: �������ų�ʼ��
//   �����������õĺ���: UP_EnableUSR232IT(u32 BaudRate);UP_SetUSR232Hadler(void (*ApplicationAddress)(u32));
//   ���ñ������ĺ���: ��    
//   �������˵��: TempData:�洢uart5���ܼĴ���������
//   �������˵��: ��       
//   ��������ֵ: ��
//   ����˵��: ��        
// *************************************************/
// void UP_Woody_VoicePlaying_Init(void)
//  {   
// //����ʹ�������ϵͳ��ʼ��֮ǰ����Ϊʹ�ܹ����趨�˴��ڵ��ж���ںͲ�����
// 	//ʹ��UART5�����ж� (USR232����)
// 	UP_EnableUSR232IT(19200);
// 	UP_SetUSR232Hadler(USR232_Voice_Hadler);
//  } 
 



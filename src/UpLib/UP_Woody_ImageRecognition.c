#include "STM32Lib\\stm32f10x.h"
#include"UP_System.h"
#include "UP_USR232.h" 
#include "UP_UART.h"
#include "UP_Globle.h"
#include "UP_Woody_ImageRecognition.h"


 u8 i;
 u8 lab;	
 u8 flam;
 u8 number;
 u8 Send[2];
 u32 Pixel_0,Pixel_1,Pixel_2,Pixel_3,Pixel_4,Pixel_5,Pixel_6,Pixel_7;
 u32 Pixel;
 u32 X_0, X_1, X_2, X_3,Y_0,Y_1,Y_2,Y_3,X,Y;
 u8 voice_id=0;
 u8 revoic_flage= 0xac;/********oxac ��ʾ��woody ���Ͷ�����ָ��*********/
char  UP_Woody_ReturnData1[20]={0x00};//������з��ص�����
 
char  UP_Woody_StartImageRecognition[5]={0x55,0xAA,0x05,0x30,0x34};//����ͼ��ʶ��ָ��

char  UP_Woody_ClosingImageRecognition[5]={0x55,0xAA,0x05,0x31,0x35};//�ر�ͼ��ʶ��ָ��

char  UP_Woody_ReturnImageRecognition[20]={0x00};//���ͼ��ʶ�𷵻ص���Ч���ص�

char  UP_Woody_White[4]={0x00,0x01,0x11,0x50};//��Ӧ���ص�69968

char  UP_Woody_Pink[4]={0x00,0x00,0xc1,0x88};//��Ӧ���ص�42516

/*************************************************
  ��������: UP_Woody_StartImageRecognize
  ��������: ����ͼ��ʶ��
  �����������õĺ���: UP_USR232_Putc
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/
void UP_Woody_StartImageRecognize(void)
{
	for(lab=0;lab<5;lab++)
  {
	   UP_USR232_Putc(UP_Woody_StartImageRecognition[lab]);
  }	
	UP_Woody_Clear_ImageRecognize_Data();
	UP_Woody_Speech_ClearData();
	UP_delay_ms(DELAY_TIMES);
}

/*************************************************
  ��������: UP_Woody_CloseImageRecognize
  ��������: �ر�ͼ��ʶ��
  �����������õĺ���: UP_USR232_Putc
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/
//�ر�ͼ��ʶ��
void UP_Woody_CloseImageRecognize(void)
{
	for(lab=0;lab<5;lab++)
  {
	   UP_USR232_Putc(UP_Woody_ClosingImageRecognition[lab]);
  }	
	UP_delay_ms(DELAY_TIMES);
}

/*************************************************
  ��������: UP_Woody_WhiteRecognize
  ��������: ���ð�ɫHSI��������
  �����������õĺ���: void UP_UART5_Putc(unsigned char c);
  ���ñ������ĺ���: ��    
  �������˵��: data:������
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/
void UP_Woody_WhiteRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xaa);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
	UP_UART5_Putc(0x00);//H����
	UP_UART5_Putc(0xAF);//H����
	UP_UART5_Putc(0x01);//H����
  UP_UART5_Putc(0x5E);//H����
  UP_UART5_Putc(0xA9); //S����
	UP_UART5_Putc(0x00); //S����
  UP_UART5_Putc(0xFF); //I����
  UP_UART5_Putc(0x00); //I����
  UP_UART5_Putc(0xC3); //У���
	UP_delay_ms(DELAY_TIMES);
	}

/*************************************************
  ��������: UP_Woody_PinkRecognize
  ��������: ���÷ۺ�ɫHSI��������
  �����������õĺ���: void UP_UART5_Putc(unsigned char c);
  ���ñ������ĺ���: ��    
  �������˵��: data:������
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/	
void UP_Woody_PinkRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xaa);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
	UP_UART5_Putc(0x00);//H����
	UP_UART5_Putc(0x43);//H����
	UP_UART5_Putc(0x01);//H����
  UP_UART5_Putc(0x44);//H����
  UP_UART5_Putc(0xE2); //S����
	UP_UART5_Putc(0x39); //S����
  UP_UART5_Putc(0xFF); //I����
  UP_UART5_Putc(0x00); //I����
  UP_UART5_Putc(0xAF); //У���
	UP_delay_ms(DELAY_TIMES);
	}
	
/*************************************************
  ��������: UP_Woody_RedRecognize
  ��������: ���ú�ɫHSI��������
  �����������õĺ���: void UP_UART5_Putc(unsigned char c);
  ���ñ������ĺ���: ��    
  �������˵��: data:������
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/
void UP_Woody_RedRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xaa);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
	UP_UART5_Putc(0x00);//H����
	UP_UART5_Putc(0x29);//H����
	UP_UART5_Putc(0x00);//H����
  UP_UART5_Putc(0x04);//H����
// 	UP_UART5_Putc(0x00);//H����
// 	UP_UART5_Putc(0x64);//H����
// 	UP_UART5_Putc(0x00);//H����
//   UP_UART5_Putc(0x50);//H����
	
  UP_UART5_Putc(0xA9); //S����
	UP_UART5_Putc(0x44); //S����
  UP_UART5_Putc(0xFF); //I����
  UP_UART5_Putc(0x00); //I����
  UP_UART5_Putc(0x26); //У���
	UP_delay_ms(DELAY_TIMES);
	}
	
	/*************************************************
  ��������: UP_Woody_BlueRecognize
  ��������: ������ɫHSI��������
  �����������õĺ���: void UP_UART5_Putc(unsigned char c);
  ���ñ������ĺ���: ��    
  �������˵��: data:������
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/
void UP_Woody_BlueRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xaa);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
	UP_UART5_Putc(0x01);//H����
	UP_UART5_Putc(0x06);//H����
	UP_UART5_Putc(0x00);//H����
  UP_UART5_Putc(0xD3);//H����
  UP_UART5_Putc(0xB1); //S����
	UP_UART5_Putc(0x3F); //S����
  UP_UART5_Putc(0xFF); //I����
  UP_UART5_Putc(0x00); //I����
  UP_UART5_Putc(0xD6); //У���
	UP_delay_ms(DELAY_TIMES);
	}
	
/*************************************************
  ��������: UP_Woody_YellowRecognize
  ��������: ���û�ɫHSI��������
  �����������õĺ���: void UP_UART5_Putc(unsigned char c);
  ���ñ������ĺ���: ��    
  �������˵��: data:������
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/
void UP_Woody_YellowRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xAA);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
// 	UP_UART5_Putc(0x00);//H����
// 	UP_UART5_Putc(0x50);//H����
// 	UP_UART5_Putc(0x00);//H����
//   UP_UART5_Putc(0x30);//H����
//   UP_UART5_Putc(0xCF); //S����
// 	UP_UART5_Putc(0x54); //S����
//   UP_UART5_Putc(0xDF); //I����
//   UP_UART5_Putc(0x82); //I����
//   UP_UART5_Putc(0x11); //У���
	UP_UART5_Putc(0x00);//H����
	UP_UART5_Putc(0x6A);//H����
	UP_UART5_Putc(0x00);//H����
  UP_UART5_Putc(0x2F);//H����
  UP_UART5_Putc(0xBF); //S����
	UP_UART5_Putc(0x47); //S����
  UP_UART5_Putc(0xFF); //I����
  UP_UART5_Putc(0x00); //I����
  UP_UART5_Putc(0xAB); //У���
	UP_delay_ms(DELAY_TIMES);
	}	
	
/*************************************************
  ��������: UP_Woody_GreenRecognize
  ��������: ���û�ɫHSI��������
  �����������õĺ���: void UP_UART5_Putc(unsigned char c);
  ���ñ������ĺ���: ��    
  �������˵��: data:������
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/
void UP_Woody_GreenRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xAA);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
// 	UP_UART5_Putc(0x00);//H����
// 	UP_UART5_Putc(0x88);//H����
// 	UP_UART5_Putc(0x00);//H����
//   UP_UART5_Putc(0x57);//H����
//   UP_UART5_Putc(0xDF); //S����
// 	UP_UART5_Putc(0x58); //S����
//   UP_UART5_Putc(0xFF); //I����
//   UP_UART5_Putc(0x00); //I����
//   UP_UART5_Putc(0x22); //У���
	UP_UART5_Putc(0x00);//H����
	UP_UART5_Putc(0x8D);//H����
	UP_UART5_Putc(0x00);//H����
  UP_UART5_Putc(0x48);//H����
  UP_UART5_Putc(0xB0); //S����
	UP_UART5_Putc(0x37); //S����
  UP_UART5_Putc(0xFF); //I����
  UP_UART5_Putc(0x00); //I����
  UP_UART5_Putc(0xC8); //У���
	UP_delay_ms(DELAY_TIMES);
	}		
/*************************************************
  ��������: UP_Woody_Display_ReturnImageRecognize
  ��������: ��ʾͼ��ʶ�𷵻ص�����
  �����������õĺ���: void UP_LCD_ShowHex(u8 x,u8 y,u8 hex);
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/
	void  UP_Woody_Display_ReturnImageRecognize(void)
 {
	 

	 if(flam==0x01)
	 {
	  UP_delay_ms(1000);
	  UP_LCD_ShowHex(0,0,UP_Woody_ReturnImageRecognition[0]);
		
		UP_LCD_ShowHex(2,0,UP_Woody_ReturnImageRecognition[1]);
		
		UP_LCD_ShowHex(4,0,UP_Woody_ReturnImageRecognition[2]);
		
		UP_LCD_ShowHex(6,0,UP_Woody_ReturnImageRecognition[3]);
		
		UP_LCD_ShowHex(0,1,UP_Woody_ReturnImageRecognition[4]);
		
		UP_LCD_ShowHex(2,1,UP_Woody_ReturnImageRecognition[5]);

		UP_LCD_ShowHex(4,1,UP_Woody_ReturnImageRecognition[6]);
		
		UP_LCD_ShowHex(6,1,UP_Woody_ReturnImageRecognition[7]);
		
		UP_LCD_ShowHex(0,2,UP_Woody_ReturnImageRecognition[8]);
		
		UP_LCD_ShowHex(2,2,UP_Woody_ReturnImageRecognition[9]);
		
		UP_LCD_ShowHex(4,2,UP_Woody_ReturnImageRecognition[10]);
		
		UP_LCD_ShowHex(6,2,UP_Woody_ReturnImageRecognition[11]);
		
		UP_LCD_ShowHex(0,3,UP_Woody_ReturnImageRecognition[12]);
		
		flam=0;	
		UP_delay_ms(1000);
		//UP_LCD_ClearScreen();
		}
}
	
/*************************************************
  ��������: UP_Woody_ImagePixel
  ��������: ���㲢�洢����ͷ���ص����ص��ֵ
  �����������õĺ���: ��
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: Pixel:�洢����ͷ���ص����ص��ֵ
  ����˵��: ��     
*************************************************/
u32 UP_Woody_ImagePixel(void)
{
	if(flam==0x01)
	{
	Pixel_0=(UP_Woody_ReturnImageRecognition[11]&0X0F);
	Pixel_1=((UP_Woody_ReturnImageRecognition[11]&0XF0)>>4)*16;//10
	
	Pixel_2=((UP_Woody_ReturnImageRecognition[10]&0X0F))*256;//100
	Pixel_3=((UP_Woody_ReturnImageRecognition[10]&0XF0)>>4)*4096;//1000
	
	Pixel_4=((UP_Woody_ReturnImageRecognition[9]&0X0F))*65536;//10000
	Pixel_5=((UP_Woody_ReturnImageRecognition[9]&0XF0)>>4)*1048576;//100000
	
	Pixel_6=((UP_Woody_ReturnImageRecognition[8]&0X0F))*16777216;//1000000
	Pixel_7=((UP_Woody_ReturnImageRecognition[8]&0XF0)>>4)*268435456;//10000000
	
	Pixel=Pixel_0+Pixel_1+Pixel_2+Pixel_3+Pixel_4+Pixel_5+Pixel_6+Pixel_7;//���ص�ֵ
	return Pixel;
	}
	flam=0;	
//	memset(UP_Woody_ReturnImageRecognition,0,18);
	return 0;
}

/*************************************************

/*************************************************
  ��������: UP_Woody_Display_Pixel
  ��������: ��ʾ����ͷ���ص����ص��ֵ
  �����������õĺ���: u32 UP_Woody_ImagePixel(void);
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: �˺�����ʾ��LCD�ĵ�һ�У�Լ3s��ʾһ�Σ��û��ɸ�����ʾʱ�䡣    
*************************************************/
 void UP_Woody_Display_Pixel(void)
  {
	 printf("(Pixel)%lud\n",UP_Woody_ImagePixel());
	 UP_delay_ms(3000);
	 UP_LCD_ClearScreen();
	}

/*************************************************
  ��������: UP_Woody_X_Coordinates
  ��������: ���㲢�洢����ͷ���ص�X����ֵ
  �����������õĺ���: ��
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: X:ʶ�������Xλ�ã�Xmax=320
  ����˵��: ��     
*************************************************/
u32 UP_Woody_X_Coordinates(void)
{
	if(flam==0x01)
	{
	X_0=(UP_Woody_ReturnImageRecognition[5]&0X0F);
	X_1=((UP_Woody_ReturnImageRecognition[5]&0XF0)>>4)*16;//10
	
	X_2=((UP_Woody_ReturnImageRecognition[4]&0X0F))*256;//100
	X_3=((UP_Woody_ReturnImageRecognition[4]&0XF0)>>4)*4096;//1000
	
	X=X_0+X_1+X_2+X_3;//X����ֵ
	return X;
	}
	flam=0;	
	return 0;
}

/*************************************************

  ��������: UP_Woody_Y_Coordinates
  ��������: ���㲢�洢����ͷ���ص�Y����ֵ
  �����������õĺ���: ��
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: Y:ʶ�������Yλ�ã�Ymax=240
  ����˵��: ��     
*************************************************/
u32 UP_Woody_Y_Coordinates(void)
{
	if(flam==0x01)
	{
	Y_0=(UP_Woody_ReturnImageRecognition[7]&0X0F);
	Y_1=((UP_Woody_ReturnImageRecognition[7]&0XF0)>>4)*16;//10
	
	Y_2=((UP_Woody_ReturnImageRecognition[6]&0X0F))*256;//100
	Y_3=((UP_Woody_ReturnImageRecognition[6]&0XF0)>>4)*4096;//1000
	
	Y=Y_0+Y_1+Y_2+Y_3;//Y����ֵ
	return Y;
	}
	flam=0;	
	return 0;
}

/*************************************************

/*************************************************
  ��������: UP_Woody_Display_X_Y
  ��������: ��ʾ����ͷ���ص������X��Y������ֵ
  �����������õĺ���: u32 UP_Woody_X_Coordinates(void);u32 UP_Woody_Y_Coordinates(void);void UP_LCD_ClearScreen(void);
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: �˺�����ʾ��LCD�ĵڶ��У�Լ3s��ʾһ�Σ��û��ɸ�����ʾʱ�䡣    
*************************************************/
 void UP_Woody_Display_X_Y(void)
  {
	 printf("\n");
	 printf("(X)(%lud)\n",(UP_Woody_X_Coordinates()));
	 printf("(Y)(%lud)\n",UP_Woody_Y_Coordinates());
   //printf("(X,Y)(%lud,%lud)\n",(UP_Woody_X_Coordinates(),UP_Woody_Y_Coordinates()));
	 UP_delay_ms(3000);
	 UP_LCD_ClearScreen();
	}
	
	
/*************************************************
  ��������: UP_Clear_ImageRecognize_Data
  ��������: UP_Woody_ReturnImageRecognition[20]��0
  �����������õĺ���: ��
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/
void UP_Woody_Clear_ImageRecognize_Data(void)
{
	for(i=0;i<13;i++)
    {
			UP_Woody_ReturnImageRecognition[i]=0x00;
		}
}

/*************************************************
  ��������: USR232_Hadler
  ��������: ����ͼ��ʶ���ж���ں���
  �����������õĺ���: ��
  ���ñ������ĺ���: ��    
  �������˵��: TempData:�洢uart5���ܼĴ���������
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/	
void USR232_Hadler(u32 TempData)
{   
	UP_Woody_ReturnImageRecognition[number++] = TempData;
	UP_Woody_ReturnData[num++]= TempData;
	UP_Timer_EnableIT(TIMER_CHANNEL2,9000);		 	 //ʹ�ܼ�ʱ��2����ʱʱ��9ms
	UP_Timer_Init();
	 if(num>=6)
	{
		num=0;
  }
		if(number>=13)
	{
		number=0;
		num=0;
  }
}

/*************************************************
  ��������: TimeHadler
  ��������: ���嶨ʱ���ж���ں���
  �����������õĺ���: UP_Timer_DisableIT; memset
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/
void TimeHadler(u32 timechannel)
{ 
  	
   if(timechannel == TIMER_CHANNEL2)
   {	
     UP_Timer_DisableIT(TIMER_CHANNEL2);		   /*******��ֹ��ʱ��3ͨ��2�ж�*********/
		 number = 0;
		 num = 0;
     flam=0x01;
     flage=0x01;	
     voice_id = UP_Woody_Speech_ID_Judge(); 
		 memset(UP_Woody_ReturnData,0,6);        /**********�������********/
   };
   
	 
}	

/*************************************************
  ��������: UP_Woody_Init
  ��������: ͼ��ʶ���ʼ��
  �����������õĺ���: UP_EnableUSR232IT(u32 BaudRate);UP_SetUSR232Hadler(void (*ApplicationAddress)(u32));
  ���ñ������ĺ���: ��    
  �������˵��: ��
  �������˵��: ��       
  ��������ֵ: ��
  ����˵��: ��     
*************************************************/	
void UP_Woody_Init(void)
 {   
//����ʹ�������ϵͳ��ʼ��֮ǰ����Ϊʹ�ܹ����趨�˴��ڵ��ж���ںͲ�����
	//ʹ��UART5�����ж� (USR232����)
	UP_EnableUSR232IT(19200);
	UP_SetUSR232Hadler(USR232_Hadler);
	UP_Timer_SetHadler(TIMER_CHANNEL2,TimeHadler);			 			 //���ݼ�ʱ���ж���ں���ָ�� 
 } 
 

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
 u8 revoic_flage= 0xac;/********oxac 表示向woody 发送读数据指令*********/
char  UP_Woody_ReturnData1[20]={0x00};//存放所有返回的数据
 
char  UP_Woody_StartImageRecognition[5]={0x55,0xAA,0x05,0x30,0x34};//启动图像识别指令

char  UP_Woody_ClosingImageRecognition[5]={0x55,0xAA,0x05,0x31,0x35};//关闭图像识别指令

char  UP_Woody_ReturnImageRecognition[20]={0x00};//存放图像识别返回的有效像素点

char  UP_Woody_White[4]={0x00,0x01,0x11,0x50};//对应像素点69968

char  UP_Woody_Pink[4]={0x00,0x00,0xc1,0x88};//对应像素点42516

/*************************************************
  函数名称: UP_Woody_StartImageRecognize
  函数功能: 启动图像识别
  被本函数调用的函数: UP_USR232_Putc
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
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
  函数名称: UP_Woody_CloseImageRecognize
  函数功能: 关闭图像识别
  被本函数调用的函数: UP_USR232_Putc
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/
//关闭图像识别
void UP_Woody_CloseImageRecognize(void)
{
	for(lab=0;lab<5;lab++)
  {
	   UP_USR232_Putc(UP_Woody_ClosingImageRecognition[lab]);
  }	
	UP_delay_ms(DELAY_TIMES);
}

/*************************************************
  函数名称: UP_Woody_WhiteRecognize
  函数功能: 设置白色HSI的上下限
  被本函数调用的函数: void UP_UART5_Putc(unsigned char c);
  调用本函数的函数: 无    
  输入参数说明: data:无意义
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/
void UP_Woody_WhiteRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xaa);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
	UP_UART5_Putc(0x00);//H上限
	UP_UART5_Putc(0xAF);//H上限
	UP_UART5_Putc(0x01);//H下限
  UP_UART5_Putc(0x5E);//H下限
  UP_UART5_Putc(0xA9); //S上限
	UP_UART5_Putc(0x00); //S下限
  UP_UART5_Putc(0xFF); //I上限
  UP_UART5_Putc(0x00); //I上限
  UP_UART5_Putc(0xC3); //校验和
	UP_delay_ms(DELAY_TIMES);
	}

/*************************************************
  函数名称: UP_Woody_PinkRecognize
  函数功能: 设置粉红色HSI的上下限
  被本函数调用的函数: void UP_UART5_Putc(unsigned char c);
  调用本函数的函数: 无    
  输入参数说明: data:无意义
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/	
void UP_Woody_PinkRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xaa);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
	UP_UART5_Putc(0x00);//H上限
	UP_UART5_Putc(0x43);//H上限
	UP_UART5_Putc(0x01);//H下限
  UP_UART5_Putc(0x44);//H下限
  UP_UART5_Putc(0xE2); //S上限
	UP_UART5_Putc(0x39); //S下限
  UP_UART5_Putc(0xFF); //I上限
  UP_UART5_Putc(0x00); //I上限
  UP_UART5_Putc(0xAF); //校验和
	UP_delay_ms(DELAY_TIMES);
	}
	
/*************************************************
  函数名称: UP_Woody_RedRecognize
  函数功能: 设置红色HSI的上下限
  被本函数调用的函数: void UP_UART5_Putc(unsigned char c);
  调用本函数的函数: 无    
  输入参数说明: data:无意义
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/
void UP_Woody_RedRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xaa);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
	UP_UART5_Putc(0x00);//H上限
	UP_UART5_Putc(0x29);//H上限
	UP_UART5_Putc(0x00);//H下限
  UP_UART5_Putc(0x04);//H下限
// 	UP_UART5_Putc(0x00);//H上限
// 	UP_UART5_Putc(0x64);//H上限
// 	UP_UART5_Putc(0x00);//H下限
//   UP_UART5_Putc(0x50);//H下限
	
  UP_UART5_Putc(0xA9); //S上限
	UP_UART5_Putc(0x44); //S下限
  UP_UART5_Putc(0xFF); //I上限
  UP_UART5_Putc(0x00); //I上限
  UP_UART5_Putc(0x26); //校验和
	UP_delay_ms(DELAY_TIMES);
	}
	
	/*************************************************
  函数名称: UP_Woody_BlueRecognize
  函数功能: 设置蓝色HSI的上下限
  被本函数调用的函数: void UP_UART5_Putc(unsigned char c);
  调用本函数的函数: 无    
  输入参数说明: data:无意义
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/
void UP_Woody_BlueRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xaa);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
	UP_UART5_Putc(0x01);//H上限
	UP_UART5_Putc(0x06);//H上限
	UP_UART5_Putc(0x00);//H下限
  UP_UART5_Putc(0xD3);//H下限
  UP_UART5_Putc(0xB1); //S上限
	UP_UART5_Putc(0x3F); //S下限
  UP_UART5_Putc(0xFF); //I上限
  UP_UART5_Putc(0x00); //I上限
  UP_UART5_Putc(0xD6); //校验和
	UP_delay_ms(DELAY_TIMES);
	}
	
/*************************************************
  函数名称: UP_Woody_YellowRecognize
  函数功能: 设置黄色HSI的上下限
  被本函数调用的函数: void UP_UART5_Putc(unsigned char c);
  调用本函数的函数: 无    
  输入参数说明: data:无意义
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/
void UP_Woody_YellowRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xAA);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
// 	UP_UART5_Putc(0x00);//H上限
// 	UP_UART5_Putc(0x50);//H上限
// 	UP_UART5_Putc(0x00);//H下限
//   UP_UART5_Putc(0x30);//H下限
//   UP_UART5_Putc(0xCF); //S上限
// 	UP_UART5_Putc(0x54); //S下限
//   UP_UART5_Putc(0xDF); //I上限
//   UP_UART5_Putc(0x82); //I上限
//   UP_UART5_Putc(0x11); //校验和
	UP_UART5_Putc(0x00);//H上限
	UP_UART5_Putc(0x6A);//H上限
	UP_UART5_Putc(0x00);//H下限
  UP_UART5_Putc(0x2F);//H下限
  UP_UART5_Putc(0xBF); //S上限
	UP_UART5_Putc(0x47); //S下限
  UP_UART5_Putc(0xFF); //I上限
  UP_UART5_Putc(0x00); //I上限
  UP_UART5_Putc(0xAB); //校验和
	UP_delay_ms(DELAY_TIMES);
	}	
	
/*************************************************
  函数名称: UP_Woody_GreenRecognize
  函数功能: 设置黄色HSI的上下限
  被本函数调用的函数: void UP_UART5_Putc(unsigned char c);
  调用本函数的函数: 无    
  输入参数说明: data:无意义
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/
void UP_Woody_GreenRecognize(u8 data)
{
  number=0;
	Send[0] = (data)&0xff;
	 
	UP_UART5_Putc(0x55);
	UP_UART5_Putc(0xAA);
	UP_UART5_Putc(0x0D);
	UP_UART5_Putc(0x01);
// 	UP_UART5_Putc(0x00);//H上限
// 	UP_UART5_Putc(0x88);//H上限
// 	UP_UART5_Putc(0x00);//H下限
//   UP_UART5_Putc(0x57);//H下限
//   UP_UART5_Putc(0xDF); //S上限
// 	UP_UART5_Putc(0x58); //S下限
//   UP_UART5_Putc(0xFF); //I上限
//   UP_UART5_Putc(0x00); //I上限
//   UP_UART5_Putc(0x22); //校验和
	UP_UART5_Putc(0x00);//H上限
	UP_UART5_Putc(0x8D);//H上限
	UP_UART5_Putc(0x00);//H下限
  UP_UART5_Putc(0x48);//H下限
  UP_UART5_Putc(0xB0); //S上限
	UP_UART5_Putc(0x37); //S下限
  UP_UART5_Putc(0xFF); //I上限
  UP_UART5_Putc(0x00); //I上限
  UP_UART5_Putc(0xC8); //校验和
	UP_delay_ms(DELAY_TIMES);
	}		
/*************************************************
  函数名称: UP_Woody_Display_ReturnImageRecognize
  函数功能: 显示图像识别返回的数据
  被本函数调用的函数: void UP_LCD_ShowHex(u8 x,u8 y,u8 hex);
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
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
  函数名称: UP_Woody_ImagePixel
  函数功能: 计算并存储摄像头返回的像素点的值
  被本函数调用的函数: 无
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: Pixel:存储摄像头返回的像素点的值
  其它说明: 无     
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
	
	Pixel=Pixel_0+Pixel_1+Pixel_2+Pixel_3+Pixel_4+Pixel_5+Pixel_6+Pixel_7;//像素点值
	return Pixel;
	}
	flam=0;	
//	memset(UP_Woody_ReturnImageRecognition,0,18);
	return 0;
}

/*************************************************

/*************************************************
  函数名称: UP_Woody_Display_Pixel
  函数功能: 显示摄像头返回的像素点的值
  被本函数调用的函数: u32 UP_Woody_ImagePixel(void);
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 此函数显示在LCD的第一行，约3s显示一次，用户可更改显示时间。    
*************************************************/
 void UP_Woody_Display_Pixel(void)
  {
	 printf("(Pixel)%lud\n",UP_Woody_ImagePixel());
	 UP_delay_ms(3000);
	 UP_LCD_ClearScreen();
	}

/*************************************************
  函数名称: UP_Woody_X_Coordinates
  函数功能: 计算并存储摄像头返回的X坐标值
  被本函数调用的函数: 无
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: X:识别物体的X位置，Xmax=320
  其它说明: 无     
*************************************************/
u32 UP_Woody_X_Coordinates(void)
{
	if(flam==0x01)
	{
	X_0=(UP_Woody_ReturnImageRecognition[5]&0X0F);
	X_1=((UP_Woody_ReturnImageRecognition[5]&0XF0)>>4)*16;//10
	
	X_2=((UP_Woody_ReturnImageRecognition[4]&0X0F))*256;//100
	X_3=((UP_Woody_ReturnImageRecognition[4]&0XF0)>>4)*4096;//1000
	
	X=X_0+X_1+X_2+X_3;//X坐标值
	return X;
	}
	flam=0;	
	return 0;
}

/*************************************************

  函数名称: UP_Woody_Y_Coordinates
  函数功能: 计算并存储摄像头返回的Y坐标值
  被本函数调用的函数: 无
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: Y:识别物体的Y位置，Ymax=240
  其它说明: 无     
*************************************************/
u32 UP_Woody_Y_Coordinates(void)
{
	if(flam==0x01)
	{
	Y_0=(UP_Woody_ReturnImageRecognition[7]&0X0F);
	Y_1=((UP_Woody_ReturnImageRecognition[7]&0XF0)>>4)*16;//10
	
	Y_2=((UP_Woody_ReturnImageRecognition[6]&0X0F))*256;//100
	Y_3=((UP_Woody_ReturnImageRecognition[6]&0XF0)>>4)*4096;//1000
	
	Y=Y_0+Y_1+Y_2+Y_3;//Y坐标值
	return Y;
	}
	flam=0;	
	return 0;
}

/*************************************************

/*************************************************
  函数名称: UP_Woody_Display_X_Y
  函数功能: 显示摄像头返回的物体的X、Y的坐标值
  被本函数调用的函数: u32 UP_Woody_X_Coordinates(void);u32 UP_Woody_Y_Coordinates(void);void UP_LCD_ClearScreen(void);
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 此函数显示在LCD的第二行，约3s显示一次，用户可更改显示时间。    
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
  函数名称: UP_Clear_ImageRecognize_Data
  函数功能: UP_Woody_ReturnImageRecognition[20]置0
  被本函数调用的函数: 无
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/
void UP_Woody_Clear_ImageRecognize_Data(void)
{
	for(i=0;i<13;i++)
    {
			UP_Woody_ReturnImageRecognition[i]=0x00;
		}
}

/*************************************************
  函数名称: USR232_Hadler
  函数功能: 定义图像识别中断入口函数
  被本函数调用的函数: 无
  调用本函数的函数: 无    
  输入参数说明: TempData:存储uart5接受寄存器的内容
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/	
void USR232_Hadler(u32 TempData)
{   
	UP_Woody_ReturnImageRecognition[number++] = TempData;
	UP_Woody_ReturnData[num++]= TempData;
	UP_Timer_EnableIT(TIMER_CHANNEL2,9000);		 	 //使能计时器2，计时时间9ms
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
  函数名称: TimeHadler
  函数功能: 定义定时器中断入口函数
  被本函数调用的函数: UP_Timer_DisableIT; memset
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/
void TimeHadler(u32 timechannel)
{ 
  	
   if(timechannel == TIMER_CHANNEL2)
   {	
     UP_Timer_DisableIT(TIMER_CHANNEL2);		   /*******禁止定时器3通道2中断*********/
		 number = 0;
		 num = 0;
     flam=0x01;
     flage=0x01;	
     voice_id = UP_Woody_Speech_ID_Judge(); 
		 memset(UP_Woody_ReturnData,0,6);        /**********清空数据********/
   };
   
	 
}	

/*************************************************
  函数名称: UP_Woody_Init
  函数功能: 图像识别初始化
  被本函数调用的函数: UP_EnableUSR232IT(u32 BaudRate);UP_SetUSR232Hadler(void (*ApplicationAddress)(u32));
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明: 无     
*************************************************/	
void UP_Woody_Init(void)
 {   
//串口使能请放在系统初始化之前，因为使能过程设定了串口的中断入口和波特率
	//使能UART5接收中断 (USR232串口)
	UP_EnableUSR232IT(19200);
	UP_SetUSR232Hadler(USR232_Hadler);
	UP_Timer_SetHadler(TIMER_CHANNEL2,TimeHadler);			 			 //传递计时器中断入口函数指针 
 } 
 

#include "STM32Lib\\stm32f10x.h"
#include "UP_LCD.h"

void UART2Init(u32 baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
		
	//使能串口2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//使能PD，AFIO总线
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);
	//进行端口重映射
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);	//URT2管脚重映射

	//PD5 做T2X
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	  //推挽复用输出-TX
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //PD6 做R2X 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入-RX
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

    USART_ClockInit(USART2, &USART_ClockInitStructure);
    USART_Init(USART2, &USART_InitStructure);
    
    USART_Cmd(USART2, ENABLE);
  
}

void UART2Putc(unsigned char c)
{
    USART_SendData(USART2, c);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );
}

void UART2Puts(char * str)
{
    while(*str)
    {
        USART_SendData(USART2, *str++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    }
}	

/*************************************************
  函数名称: UP_MP3_Init  
  函数功能: 语音模块串口初始化
  被本函数调用的函数: void UART2Init(u32 baud);     
  调用本函数的函数: 无
  输入参数说明:  空   
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_MP3_Init(void)
{
	UART2Init(9600);	
//	UP_delay_ms(5000);
}

/*************************************************
  函数名称: UP_MP3_PlaySound 
  函数功能: MP3播放站名等
  被本函数调用的函数: void UART2Putc(unsigned char c);     
  调用本函数的函数: 无
  输入参数说明:  num
                     【in】最大值~0x1e   
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_MP3_PlaySound(u16 num)
{
	UART2Putc(0x7E);
	UART2Putc(0x12);
	UART2Putc((num&0xff00)>>8);
	UART2Putc(num&0x00ff);
	UART2Putc(0xEF);
}

/*************************************************
  函数名称: UP_MP3_Pause 
  函数功能: MP3暂停播放
  被本函数调用的函数: void UART2Putc(unsigned char c);     
  调用本函数的函数: 无
  输入参数说明:  空   
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_MP3_Pause(void)
{
	UART2Putc(0x7E);
	UART2Putc(0x0E);
	UART2Putc(0x00);
	UART2Putc(0x00);
	UART2Putc(0xEF);	
}

/*************************************************
  函数名称: UP_MP3_SetVolume  
  函数功能: 可以设置语音模块声音大小
  被本函数调用的函数: void UART2Putc(unsigned char c);     
  调用本函数的函数: 无
  输入参数说明:  volume
                        【in】最大值~0x1e   
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_MP3_SetVolume(u8 volume)//最大为0x1E
{
	UART2Putc(0x7E);
	UART2Putc(0x06);
	UART2Putc(0x00);
	UART2Putc(volume);
	UART2Putc(0xEF);	
}














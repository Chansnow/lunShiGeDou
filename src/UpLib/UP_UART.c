/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
//  Update Date   : 2013/07/12
//  Version   	  : 1.3.1          
//  Description   : Modification for new controller
/******************************************************************/ 

#include "STM32Lib\\stm32f10x.h"
#include "UP_UART.h"
#include "UP_ADC.h"
#include "UP_IOout.h"
#include "UP_PWM.h"
#include "UP_Timer.h"
#include "UP_System.h"
#include "UP_Globle.h"

#define MAX_FRAME_NUM	20			//队列中的最大帧数
#define MAX_BUF_NUM		20			//每帧缓存大小
typedef struct _CDSFrame_Info {	   	//CDS帧队列结构体
	u8 len;							//帧长度
	u8 buf[MAX_BUF_NUM];			//帧数据
} CDSFrame_Info;

CDSFrame_Info g_CDSFrames[MAX_FRAME_NUM];	//CDS帧队列	
u8 g_CDSFrames_Tail = 0;		//CDS帧队列尾指针
u8 g_CDSFrames_Head = 0;		//CDS帧队列头指针

void UP_UART1_Putc(unsigned char c)
{
    USART_SendData(USART1, c);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
}

void UP_UART1_Puts(char * str)
{
    while(*str)
    {
        USART_SendData(USART1, *str++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

void UP_UART4_Putc(unsigned char c)
{
    USART_SendData(UART4, c);
    while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET );
}

void UP_UART4_Puts(char * str)
{
    while(*str)
    {
        USART_SendData(UART4, *str++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
    }
}			

void UP_UART5_Putc(unsigned char c)
{
    USART_SendData(UART5, c);
    while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET );
}

void UP_UART5_Puts(char * str)
{
    while(*str)
    {
        USART_SendData(UART5, *str++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
    }
}

//检查是否有舵机数据帧需要发送（每1ms检查一次）
void CheckCDSSend(void)
{
	//判断队列是否为空
	if(g_CDSFrames_Head == g_CDSFrames_Tail)
		return;
	//开启一次数据发送
	UART3_TXEN;
	DMA1_Channel2->CMAR = (u32)g_CDSFrames[g_CDSFrames_Tail].buf;	//要发送的内存地址 
	DMA1_Channel2->CNDTR = g_CDSFrames[g_CDSFrames_Tail].len;		//要发送的字节数
	DMA1_Channel2->CCR |= 0x01;										//开启一次DMA  // */
	g_CDSFrames_Tail++;
	if(g_CDSFrames_Tail == MAX_FRAME_NUM)
		g_CDSFrames_Tail = 0;	
}

//UART3发送数据帧（数字舵机协议）
void UP_Uart3_SendCDSFrame(u8 id, u8 len, u8 cmd, u8* pData)
{
	unsigned char i;
 	unsigned char csum = 0;
	u16 pos = 0;
	//判断缓存是否已满
	if(g_CDSFrames_Head == g_CDSFrames_Tail-1 || 
		(g_CDSFrames_Tail == 0 && g_CDSFrames_Head == MAX_FRAME_NUM-1))
		return;
	//将要发送的数据帧压入队列
	g_CDSFrames[g_CDSFrames_Head].buf[pos++] = 0xff;	//帧头
	g_CDSFrames[g_CDSFrames_Head].buf[pos++] = 0xff;	//帧头
	g_CDSFrames[g_CDSFrames_Head].buf[pos++] = id;		//ID
	csum += id;
	g_CDSFrames[g_CDSFrames_Head].buf[pos++] = len;		//包长度
	csum += len;
	g_CDSFrames[g_CDSFrames_Head].buf[pos++] = cmd;		//命令
	csum += cmd;		
	for(i=0; i<len-2; i++)
	{
		g_CDSFrames[g_CDSFrames_Head].buf[pos++] = pData[i];//数据
	 	csum += pData[i];
	}
	csum = ~csum; 
	g_CDSFrames[g_CDSFrames_Head].buf[pos++] = csum;	//校验和
	g_CDSFrames[g_CDSFrames_Head].len = pos;			//帧长度
	g_CDSFrames_Head++;
	if(g_CDSFrames_Head == MAX_FRAME_NUM)
		g_CDSFrames_Head = 0;
}

//UART DMA的配置
void UP_UART_DMAConfiguration(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel2);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(USART3->DR));			//源头BUF
	DMA_InitStructure.DMA_MemoryBaseAddr = 0;									//目标BUF
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;							//外设作目标
	DMA_InitStructure.DMA_BufferSize = 0;										//BUF大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			//外设地址寄存器不递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						//内存地址递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;		//外设字节为单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;			//内存字节为单位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;								//普通模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;							//4优先级之一的(高优先)
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								//非内存到内存
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);								//DMA2传输完成中断
	USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);								//串口3发送器器DMA
}

void UP_UART_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		USART_ClockInitTypeDef USART_ClockInitStructure;
	
	//使能串口1，PA，AFIO总线
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | 
													 RCC_APB2Periph_AFIO   |
													 RCC_APB2Periph_USART1 , 
													 ENABLE);

    // A9 USART1_Tx 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//推挽输出-TX
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // A10 USART1_Rx  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入-RX
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = g_UP_BluetoothBaudRate;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
		USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
		USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
		USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
		USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

	USART_ClockInit(USART1, &USART_ClockInitStructure);
    USART_Init(USART1, &USART_InitStructure);
    // Enable the USARTx 
    USART_Cmd(USART1, ENABLE);
	//如果开启了UART接收中断，串口1使用接收中断
	if(g_UP_bBluetoothIT)	 
	{
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);// */
	}
	
	
	//使能串口4时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	//使能PC，AFIO总线
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

	//PC10 做T4X
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	  //推挽复用输出-TX
    GPIO_Init(GPIOC, &GPIO_InitStructure);

  //PC11 做R4X 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入-RX
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = g_UP_ZigbeeBaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

    USART_ClockInit(UART4, &USART_ClockInitStructure);
    USART_Init(UART4, &USART_InitStructure);
    
    USART_Cmd(UART4, ENABLE);
	//如果开启了UART接收中断，串口2使用接收中断
	if(g_UP_bZigbeeIT)	 	
		USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);// */
	
	
	//使能串口5，PC,PD,AFIO总线
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | 
													 RCC_APB2Periph_GPIOD | 
													 RCC_APB2Periph_AFIO  ,
													 ENABLE);
	  
    // C12 USART5_Tx 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//推挽输出-TX
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // D2 USART5_Rx  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入-RX
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = g_UP_USR232BaudRate;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
		USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
		USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
		USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
		USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

		USART_ClockInit(UART5, &USART_ClockInitStructure);
		USART_ClearFlag(UART5,USART_FLAG_TC);
		USART_Init(UART5, &USART_InitStructure);
    // Enable the USARTx 
    USART_Cmd(UART5, ENABLE);	
	//如果开启了UART接收中断，串口5使用接收中断
		if(g_UP_bUSR232IT)	
		{
			USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);// */	
		}
		
		
	//使能串口3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	// B10 做T3X
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   //推挽复用输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // B11 做R3X 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	UART3_RXDS;
 	UART3_TXDS;
	//E14做TX3EN
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   //推挽输出
    GPIO_Init(GPIOE, &GPIO_InitStructure);

	//E15做RX3EN
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   //推挽输出
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 1000000;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

    USART_ClockInit(USART3, &USART_ClockInitStructure);
    USART_Init(USART3, &USART_InitStructure);
    
    USART_Cmd(USART3, ENABLE);
	//串口3使用接收中断
 //	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);// */
	UP_UART_DMAConfiguration();
}

//使能蓝牙(UART1)数据接收中断
void UP_EnableBluetoothIT(u32 BaudRate)
{
	g_UP_BluetoothBaudRate = BaudRate;
	g_UP_bBluetoothIT = TRUE;		
}
//使能Zigbee(UART4)数据接收中断
void UP_EnableZigbeeIT(u32 BaudRate)
{
	g_UP_ZigbeeBaudRate = BaudRate;
	g_UP_bZigbeeIT = TRUE;
}
/*//使能USR232(UART5)数据接收中断
void UP_EnableUSR232IT(u32 BaudRate)
{
	g_UP_USR232BaudRate = BaudRate;
	g_UP_bUSR232IT = TRUE;		
}*/

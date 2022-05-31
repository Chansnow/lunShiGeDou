/******************************************************************/
//	Copyright (C), 2011-2012, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
/******************************************************************/ 

#include "STM32Lib\\stm32f10x.h"
#include "UP_ADC.h"

u16 g_ADValue[16] = {0};			//当前ADC值

/*************************************************
  函数名称: UP_ADC_DMAConfiguration
  函数功能: ADC的DMA的配置
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: 无    
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_ADC_DMAConfiguration(void)
{
	DMA_InitTypeDef DMA_InitStructure;																//定义DMA初始化结构体变量
	// 使能DMA1时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// DMA通道1配置
	DMA_DeInit(DMA1_Channel1); 																				//复位DMA1通道1	
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)( &(ADC1->DR));		//ADC1数据寄存器 	   （定义 DMA通道外设基地址=ADC1_DR）
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)g_ADValue;					  //获取ADC的数组 	   （定义DMA通道存储器地址）
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;								//片内外设作源头	   （指定外设为源地址）
	DMA_InitStructure.DMA_BufferSize = 16;														//每次DMA16个数据	   （定义DMA缓冲区大小为16）
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//外设地址不增加 	   （当前外设寄存器地址不变）
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						//内存地址增加  	   （当前存储器地址不变）
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//半字 	   （定义外设数据宽度16位）
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;					//半字	   （定义存储器数据宽度16位）
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;										//普通模式				   （DMA通道操作模式位环形缓冲模式）
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;								//高优先级				   （DMA通道优先级高）
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;											//非内存到内存		 	 （禁止DMA通道存储器到存储器传输）
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);											//将配置载入DMA1通道1（初始化DMA通道1）
	
//	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);									//DMA通道1传输完成中断
	
	DMA_Cmd(DMA1_Channel1, ENABLE);																		//使能DMA1通道1
}

/*************************************************
  函数名称: UP_ADC_Init
  函数功能: ADC相关初始化
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: 无    
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_ADC_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;																//定义ADC初始化结构体变量
	GPIO_InitTypeDef  GPIO_InitStructure;															//定义GPIO初始化结构体变量

	UP_ADC_DMAConfiguration();																				//ADC DMA配置
  // 允许ADC 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);								//使能ADC1时钟

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);							//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);							//使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);							//使能GPIOC时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;											//选择GPIO模式为模拟输入
	// PA0~7配置
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|
																 GPIO_Pin_2|GPIO_Pin_3|
																 GPIO_Pin_4|GPIO_Pin_5|
																 GPIO_Pin_6|GPIO_Pin_7;							//选择PA0~PA7
	GPIO_Init(GPIOA, &GPIO_InitStructure);													  //配置PA0~PA7为模拟输入
	// PB0~1配置
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;							//选择PB0~PB1
	GPIO_Init(GPIOB, &GPIO_InitStructure);														//配置PB0~PB1为模拟输入
	// PC0~5配置
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|
																 GPIO_Pin_2|GPIO_Pin_3|
																 GPIO_Pin_4|GPIO_Pin_5;							//选择PC0~PC5
	GPIO_Init(GPIOC, &GPIO_InitStructure);														//配置PC0~PC5为模拟输入

	// ADC1配置
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;								//规则同步模式   （ADC1和ADC2工作在独立模式）
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;											//连续多通道模式 （扫描模式<多通道>）
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;								//ADC转换工作在连续模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;						//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 16;													//16个通道
	ADC_Init(ADC1, &ADC_InitStructure);																//初始化ADC1
	
	// 配置通道16的采样速度
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5);   //ADC1选择信道9,音序器等级1,采样时间239.5个周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 2, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 4, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 5, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 6, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 7, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 8, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 9, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 10, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 11, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 12, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 13, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 14, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 15, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 16, ADC_SampleTime_239Cycles5);
	
	// 使能ADC1的DMA模式 
	ADC_DMACmd(ADC1, ENABLE);
	
	// 使能ADC1
	ADC_Cmd(ADC1, ENABLE);
	
	//重置ADC1校准寄存器    
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));		//等待ADC1校准重置完成
	
	//开始ADC1校准状态
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));				//等待ADC1校准完成

	// 人工打开ADC转换. 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				//使能ADC1软件开始转换
}

/*************************************************
  函数名称: UP_ADC_GetValue
  函数功能: 获取某路AD采样值
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: 输入通道0~15   
  输出参数说明: 无       
  函数返回值: 返回ADC值0~4095对应0~5V
  其它说明:无        
*************************************************/				
u16 UP_ADC_GetValue(u8 Channel)
{
	if(Channel < 16)
		return g_ADValue[Channel];
	else
		return 0;
}

/*************************************************
  函数名称: UP_ADC_GetIO
  函数功能: 获取某路IO采样值
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: Channel输入通道0~15   
  输出参数说明: 无       
  函数返回值: 返回值0或1
  其它说明:无        
*************************************************/
u8 UP_ADC_GetIO(u8 Channel)
{
	return 	(g_ADValue[Channel] > 170)?1:0;
}

/*************************************************
  函数名称: UP_ADC_GetAllIO
  函数功能: 获取16路IO采样值
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 返回16路IO状态，16位无符号整形每一位对应一路
  其它说明:无        
*************************************************/
u16 UP_ADC_GetAllIO(void)		
{
	u16 temp = 0;
	u8 i;
	for(i=0; i<16; i++)
	{
		if(g_ADValue[i] > 2048)
			temp |= (0x01<<i);
	}
	return temp;	
}

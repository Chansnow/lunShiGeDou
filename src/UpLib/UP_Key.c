/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  	: 陈中元  
//  Reviser				: 乔潇楠
//  Update Date   : 2012/08/01
//  Version   	  : 1.3          
//  Description   : Transplant to v3.5 function library
//  Reviser				: 乔潇楠
//  Update Date   : 2013/07/18
//  Version   	  : 1.3.1         
//  Description   : Change GPIO configuration for keys.
/******************************************************************/ 

#include "UP_Key.h" 

/*************************************************
  函数名称: UP_Key_Init
  函数功能: 按键初始化
  被本函数调用的函数: 无        
  调用本函数的函数: 无    
  输入参数说明: 无
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;											//定义GPIO初始化结构体变量
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);			//使能GPIOD时钟
	
	//PD12~15按键输入
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12|GPIO_Pin_13|
																 GPIO_Pin_14|GPIO_Pin_15;		//选择PD12~PD15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;							//选择上拉输入模式
	GPIO_Init(GPIOD, &GPIO_InitStructure);										//配置PD12~15为上拉输入

	//USB中断入口
	GPIO_ResetBits(GPIOE, GPIO_Pin_2);												//清除PE2端口
	/* E2-DEV控制口 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);			//使能GPIOE时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;									//选择PE2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;					//设置最高输出速率为2MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;					//选择推挽输出模式
	GPIO_Init(GPIOE, &GPIO_InitStructure);										//配置PE2为推挽输出
}

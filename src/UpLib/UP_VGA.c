#include "STM32Lib\\stm32f10x.h"
#include "UP_CDS5500.h"
#include "UP_Globle.h"
#include "UP_VGA.h"
#include "UP_UART.h"
#include "UP_Timer.h"
#include "UP_LCD.h"
#include "UP_ADC.h"


u16  speed = 800;

s16 Speed1=0,Speed2=0,Speed3=0,Speed4=0;		//四个舵机的速度
u8 CDS_LEN;								//解析循迹板回传数据的有效数据长度
u8 CDS_DATA[5];							//循迹板返回数据的缓存
u8 UP_VGA_TrackSign;							//循迹板7个点的状态
u32 rec_num;

u8 UP_VGA_ForwardSign = 0;
u8 UP_VGA_StopSign = 0;
u8 UP_VGA_TurnSign = 0;

u8 UP_VGA_CrossSign = 0;			//岔路标志0-无岔路（包含十字路口）1-左侧有岔路 2-右侧有岔路 3-T字岔路,此标志只能手动清零
u8 UP_VGA_CrossSign2 = 0;			//岔路标志0，此标志自动清零
u8 iLeft,iMid,iRight,iLeft2,iLeft3,iRight2,iRight3;
s16 spdLeft,spdRight;
s16 sLast = 0;


u8 UP_VGA_ProAdcChannel;
u16 UP_VGA_ProDis;


void USART3_NVIC(void)					//开启串口3中断
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);			   // */	
}

void CDS_UARTHadler(u8 Data)			//用于解析收到的循迹板传回的数据
{//返回数据示例FF FF 00 03 00 03 FB--字头1 字头2 ID 长度 错误信息 数据 校验
	u8 temp;							//收到的数据
	static u8 sum = 0;					//校验
	static u8 count = 0;				
	static u8 data_count = 0;
	temp = Data;	 
	switch(count)
	{
		case 0:
		{
			if(temp == 0xFF)			//判断字头1
				count = 1;
			else
				sum = 0;
		}
		break;
		case 1:
		{
			if(temp != 0xFF)			//判断字头2
			{
			 	count = 0;
				sum = 0;
			}
			else
			{	
				count = 2;
			}
		}
		break;
		case 2:
		{	
			if(temp != 0x00)			//循迹板ID，固定为0x00
			{
			 	count = 0;
				sum = 0;
			}
			else
			{
			 	sum = 0x00;
				count = 3;
			}
		}
		break;
		case 3:
		{	
			if(temp != 0x03)			//有效数据长度
			{
			 	count = 0;
				sum = 0;
			}
			else
			{
				CDS_LEN = 0x03;
				sum += CDS_LEN;
				count = 4;
				data_count = 0x00;
			}			
		}
		break;
		case 4:
		{	
			if(data_count < (CDS_LEN-1))//回传数据的有效数据存入缓存
			{	
				CDS_DATA[data_count] = temp;
				sum += temp;	 
				data_count += 1;
			}	
			else if(data_count == ((CDS_LEN-1)))
			{	
				sum = ~sum;
				if(sum == temp)				//判断校验位是否正确
				{		
					if(CDS_DATA[0] == 0x00)	//判断状态位0x00为正常
					{
						 UP_VGA_TrackSign = CDS_DATA[1] ;//循迹板状态存入标志变量中
						 rec_num++;
					}
				}
			 	sum = 0;
				data_count = 0;
				count = 0;
			}
		}
		break;
		default:
			break;					
	}
	
}
void USART3_IRQHandler(void)//串口3中断函数
{
	//接收中断
	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)//判断是否为接收中断
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);//清中断标志
		CDS_UARTHadler(USART_ReceiveData(USART3));	  //解析收到的数据
		
	}
	//溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
	if(USART_GetFlagStatus(USART3,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(USART3,USART_FLAG_ORE);	//读SR
		USART_ReceiveData(USART3);				//读DR
	}
}

void UP_UART3_Putc(unsigned char c)
{
    USART_SendData(USART3, c);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET );
}

/*************************************************
  函数名称: CDS_Read_Sign  
  函数功能: 读取循迹板状态函数
  被本函数调用的函数: void CDS_Read_Sign(void);      
  调用本函数的函数: 无
  输入参数说明:  空
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void CDS_Read_Sign(void)
{
	
	UART3_RXDS;			//关闭舵机总线的接收信号线
	UART3_TXEN;			//打开舵机总线的发送信号线
	UP_UART3_Putc(0xff);//字头1
	UP_UART3_Putc(0xff);//字头2
	UP_UART3_Putc(0x00);//循迹板ID
	UP_UART3_Putc(0x04);//数据长度
	UP_UART3_Putc(0x02);//读指令
	UP_UART3_Putc(0x32);//读取内存地址
	UP_UART3_Putc(0x01);//读取数据长度
	UP_UART3_Putc(0xc6);//校验
	UP_delay_us(10);	//延时10us等待数据被发送完毕
	//循迹板通讯接口采用了CDS系列数字舵机的单总线接口，接收和发送数据是复用一根线
	UART3_TXDS;			//关闭舵机总线的发送信号线
	UART3_RXEN;			//打开舵机总线的接收信号线
}

void SetSpeed(s16 left,s16 right)
{
	Speed1 = left;//
	Speed2 = 0-right;//
	Speed3 = left;//
	Speed4 = 0-right;//
}
extern void MAIN_TIMER_PRO(u32 null);

/*************************************************
  函数名称: VGA_Timer_Handler  
  函数功能: 1ms定时中断，定时给舵机和循迹板发送指令
  被本函数调用的函数: void CDS_Read_Sign(void);      
  调用本函数的函数: 无
  输入参数说明:  null:无意义   
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void VGA_Timer_Handler(u32 null)
{
	static u32 Count;
	static u32 Count2;
	static u32 Count3;//红外障碍离开后延时计数

	if(UP_ADC_GetValue(UP_VGA_ProAdcChannel)>UP_VGA_ProDis)
	{
		Count3 = 1000;//延时1s
	}
	else
	{
		if(Count3 != 0)
			Count3--;
	}
	
	if(0 == Count)
	{
		CDS_Read_Sign();
	}
	else if(2 == Count)
	{//因在Count为0时打开了舵机总线的接收，在发送新数据前要关闭
		UART3_RXDS;		//关闭舵机总线的接收信号线,舵机速度设置函数中包含了UART3_TXEN
		if(Count3!=0)//if(UP_ADC_GetValue(UP_VGA_ProAdcChannel)>UP_VGA_ProDis)
			UP_CDS_SetSpeed(0x01,0);
		else		
			UP_CDS_SetSpeed(0x01,Speed1);		
	}
	else if(3 == Count)
	{
		if(Count3!=0)//if(UP_ADC_GetValue(UP_VGA_ProAdcChannel)>UP_VGA_ProDis)
			UP_CDS_SetSpeed(0x02,0);	
		else
			UP_CDS_SetSpeed(0x02,Speed2);	
	}
	else if(4 == Count)	
	{
		if(Count3!=0)//if(UP_ADC_GetValue(UP_VGA_ProAdcChannel)>UP_VGA_ProDis)
			UP_CDS_SetSpeed(0x03,0);	
		else
			UP_CDS_SetSpeed(0x03,Speed3);	
	}
	else if(5 == Count)
	{
		if(Count3!=0)//if(UP_ADC_GetValue(UP_VGA_ProAdcChannel)>UP_VGA_ProDis)
			UP_CDS_SetSpeed(0x04,0);
		else
			UP_CDS_SetSpeed(0x04,Speed4);
	}		
	if(6 == Count) 
		Count = 0;
	else
		Count += 1;
	
	if(6 == Count2)
	{
		Count2 = 0;
		
		if(UP_VGA_ForwardSign)
		{
			
			iLeft = (UP_VGA_TrackSign&0x04)>>2;
			iMid = (UP_VGA_TrackSign&0x08)>>3;
			iRight = (UP_VGA_TrackSign&0x10)>>4;
			iLeft2 = (UP_VGA_TrackSign&0x02)>>1;
			iLeft3 = UP_VGA_TrackSign&0x01;
			iRight2 = (UP_VGA_TrackSign&0x20)>>5;
			iRight3 = (UP_VGA_TrackSign&0x40)>>6;
			
			if(iMid == 1)
			{
				spdLeft = speed;
				spdRight = speed;
			}
			
			if(iLeft == 1|| iLeft2 == 1)
			{
				spdLeft = speed*0.8;
				spdRight = speed*1.2;
				sLast = 1;	//线在左侧
			}
			
			if(iRight == 1 || iRight2 == 1)
			{
				spdLeft = speed*1.2;
				spdRight = speed*0.8;
				sLast = 2; 	//线在右侧
			}
			
			if(iMid==0 && iLeft==0 && iRight==0)
			{
				if(sLast == 1)
				{
					//出去前，线在左侧
					spdLeft = 0-speed;
					spdRight = speed;
				}
				else if(sLast == 2)
				{
					//出去前，线在右侧
					spdLeft = speed;
					spdRight = 0-speed;
				}
				else
				{
					if(iLeft3==1)
						sLast = 1;
					else if(iRight3 == 1)
						sLast = 2;	
				}
			}
			SetSpeed(spdLeft,spdRight);
 			
		}
		else
		{
			iLeft = (UP_VGA_TrackSign&0x04)>>2;
			iMid = (UP_VGA_TrackSign&0x08)>>3;
			iRight = (UP_VGA_TrackSign&0x10)>>4;
			iLeft2 = (UP_VGA_TrackSign&0x02)>>1;
			iLeft3 = UP_VGA_TrackSign&0x01;
			iRight2 = (UP_VGA_TrackSign&0x20)>>5;
			iRight3 = (UP_VGA_TrackSign&0x40)>>6;
		}
	
		if(iLeft2 == 1 && iLeft3 == 1)
		{
			if((iLeft==1||iMid==1||iRight==1) && (iRight2==0 && iRight3==0))//遇到左交叉线UP_VGA_CrossSign置1
				UP_VGA_CrossSign2 = UP_VGA_CrossSign = 1;
			else
				UP_VGA_CrossSign2 = UP_VGA_CrossSign = 0;
		}
		else if(iRight2 == 1 && iRight3 == 1)
		{
			if((iLeft==1||iMid==1||iRight==1) && (iLeft2==0 && iLeft3==0))//遇到右交叉线UP_VGA_CrossSign置2
				UP_VGA_CrossSign2 = UP_VGA_CrossSign = 2;
			else
				UP_VGA_CrossSign2 = UP_VGA_CrossSign = 0;
		}
		else
			UP_VGA_CrossSign2 = UP_VGA_CrossSign = 0;
		
		if(iLeft2&iLeft3&iRight2&iRight3)//遇到T字交叉线UP_VGA_CrossSign置3
		{
			UP_VGA_CrossSign2 = UP_VGA_CrossSign = 3;
		}	
		
	}
	else
		Count2 += 1;
	//MAIN_TIMER_PRO(0);
}

/*************************************************
  函数名称: UP_VGA_Timer  
  函数功能: 使能定时器中断，此中断为小车的寻线进程。
  被本函数调用的函数: void UP_Timer_EnableIT(u32 TimerChannel, u32 Time_us);
                      void VGA_Timer_Handler(u32 null);void CDS_Read_Sign(void);    
  调用本函数的函数: 无
  输入参数说明:  空   
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_VGA_Timer(void)
{
	UP_Timer_EnableIT(TIMER_CHANNEL0,1000);//使能定时中断
	UP_Timer_SetHadler(TIMER_CHANNEL0,VGA_Timer_Handler);//设置定时中断的入口函数	
}

/*************************************************
  函数名称: UP_VGA_OPEN_USART3  
  函数功能: 打开串口3，即舵机串口，串口3接收中断使能。
  被本函数调用的函数: void USART3_NVIC(void);
                      void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);    
  调用本函数的函数: 无
  输入参数说明:  空   
  输出参数说明: 无       
  函数返回值: 无
  其它说明:无        
*************************************************/
void UP_VGA_OPEN_USART3(void)
{
	USART3_NVIC();
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//串口3接收中断使能	
}

void UP_VGA_SetSpeed(s16 left,s16 right)
{
	Speed1 = left;//
	Speed2 = 0-right;//
	Speed3 = left;//
	Speed4 = 0-right;//
}


void UP_VGA_DIS_TRACKSIGN(u8 line)
{
	u8 i;
	for(i=0;i<7;i++)				//显示循迹板的7个点的状态
	{
		if((UP_VGA_TrackSign & (1<<i)))
			UP_LCD_ShowInt(2*i+1,line,1);
		else
			UP_LCD_ShowInt(2*i+1,line,0);
	}	
}

void UP_VGA_MOTION_FORWARD(void)
{
	UP_VGA_ForwardSign = 1;
}
void UP_VGA_MOTION_STOP(void)
{
	UP_VGA_ForwardSign = 0;
	UP_VGA_SetSpeed(0,0);
}
void UP_VGA_MOTION_TURN(u8 dir)
{
	u8 temp;//,i;
	temp = UP_VGA_ForwardSign;
	UP_VGA_ForwardSign = 0;
	UP_VGA_SetSpeed(speed,speed);
	
	while(iLeft2|iLeft3|iRight2|iRight3)
	{
		UP_delay_ms(1);
		UP_VGA_SetSpeed(speed,speed);
	}
	UP_VGA_SetSpeed(0,0);
	UP_delay_ms(200);
	if(dir==1)
	{
		UP_VGA_MOTION_STOP();
		UP_VGA_SetSpeed(0-speed,speed);
		UP_delay_ms(50);
		while(iLeft3 != 1)
		{		
			UP_delay_ms(1);//UP_VGA_DIS_TRACKSIGN(2);
			UP_VGA_SetSpeed(0-speed,speed);
		}
		UP_VGA_SetSpeed(0,0);
		UP_delay_ms(200);
		while(!((iLeft==1|iMid==1|iRight==1)&&(iLeft2|iLeft3|iRight2|iRight3)==0))//while(!((iMid==1)&&(iLeft|iLeft2|iLeft3|iRight|iRight2|iRight3)==0))
		{
			UP_delay_ms(1);//UP_VGA_DIS_TRACKSIGN(2);	
			UP_VGA_SetSpeed(0-speed,speed);			
		}	
  }
	else if(dir==2)
	{
		UP_VGA_MOTION_STOP();		
		UP_VGA_SetSpeed(speed,0-speed);
		UP_delay_ms(50);
		while(iRight3 != 1)
		{		
			UP_delay_ms(1);//UP_VGA_DIS_TRACKSIGN(2);
			UP_VGA_SetSpeed(speed,0-speed);
		}
		UP_VGA_SetSpeed(0,0);
		UP_delay_ms(200);
		while(!((iLeft==1|iMid==1|iRight==1)&&(iLeft2|iLeft3|iRight2|iRight3)==0))//while(!((iMid==1)&&(iLeft|iLeft2|iLeft3|iRight|iRight2|iRight3)==0))
		{
			UP_delay_ms(1);//UP_VGA_DIS_TRACKSIGN(2);		
			UP_VGA_SetSpeed(speed,0-speed);
		}	

	}

	UP_VGA_SetSpeed(0,0);
  UP_VGA_ForwardSign = temp;
}

void UP_VGA_PROTECTSET(u8 ADCChannel,u16 ProtectDis)
{
	UP_VGA_ProAdcChannel = ADCChannel;
	UP_VGA_ProDis = ProtectDis;
}

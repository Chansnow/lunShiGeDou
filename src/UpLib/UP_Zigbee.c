/******************************************************************/
//	Copyright (C), 2011-2013, 北京博创 
//  Author   	  : 乔潇楠  
//  Update Date   : 2013/07/15
//  Version   	  : 1.0            
//  Description   : 
/******************************************************************/ 

#include "UP_Zigbee.h" 
#include "UP_UART.h"
#include "UP_Globle.h"
#include "UP_UART_Parse.h"
#include "UP_Variable.h"
//UP_UART_FRAME
//使能Zigbee数据接收中断
void UP_Zigbee_EnableIT(void)
{
	g_UP_bZigbeeIT = TRUE;	
	UP_SetZigbeeHadler(UP_Zigbee_Rec);	
}

//传递Zigbee数据接收中断入口函数
void UP_SetZigbeeHadler(void (*ApplicationAddress)(u32))
{
	if(ApplicationAddress != 0)
		g_UP_ZigbeeITAddress = (u32)ApplicationAddress;
}

//Zigbee发送一个字符
void UP_Zigbee_Putc(unsigned char c)
{
	UP_UART4_Putc(c);
} 

//Zigbee发送一串字符	
void UP_Zigbee_Puts(char * str)
{
	UP_UART4_Puts(str);
}		





u8 UP_Zigbee_RecBuf[200];
u8 UP_Zigbee_RecSign;
u32 UP_Zigbee_RecNum;
u32 UP_Zigbee_TxNum;

u8 Zigbee_RecTime_Count = 0;
UP_UART_FRAME Zigbee_Frame;
u8 zigbee_buf[9];
// void UP_Zigbee_Rec(u32 data)
// {
// 	static u8 FrameStart = 0;
// 	static u8 index = 0;
// 	static u8 last_data;
// 	static u8 len;
// //	static u8 z;
// 	//u8 data;
// 	u8 i;
// 	static u8 sum=0;
// 	//data = (u8) pdata;
// 	
// // 	UP_Zigbee_RecNum++;
// // 	
// // 	if(z==9) 
// // 	{
// // 		z=0;
// // 		for(i=0;i<9;i++)
// // 			zigbee_buf[0]=0;
// // 	}
// // 	zigbee_buf[z++] = data;
// 	//if(Zigbee_RecTime_Count>5
// 	//UP_Zigbee_RecNum++;
// 	if(0 == FrameStart)
// 	{	
// 		
// 		if((last_data==0xFE) && (data==0xda))//(data==0xcc||data==0xed||data==0xda))
// 		{
// 			FrameStart = 1;
// 			index = 2;
// 			last_data = 0;

//  			UP_Zigbee_RecBuf[0] = 0xFE;
//  			UP_Zigbee_RecBuf[1] = data;
// 			Zigbee_RecTime_Count = 5;
// 		}
// 		else
// 		{
// 			last_data = data;	
// 		}
// 	}
// 	else
// 	{
// 		if(Zigbee_RecTime_Count!=0)
// 		{
// 			Zigbee_RecTime_Count = 5;
// 			if(2 == index)	
// 			{	
// 				len = UP_Zigbee_RecBuf[2] = data;
// 				sum = 0xd8+len;
// 				index = 3;
// 			}
// 			else
// 			{
// 				if(index == (len-1))
// 				{
// 					if(sum==data)
// 					{
// 						UP_Zigbee_RecBuf[index] = data;
// 						Zigbee_Frame.DataBuf[Zigbee_Frame.Head].len = UP_Zigbee_RecBuf[2];
// 						Zigbee_Frame.DataBuf[Zigbee_Frame.Head].cmd = UP_Zigbee_RecBuf[5];	
// 						for(i=0;i<len;i++)
// 						{
// 							Zigbee_Frame.DataBuf[Zigbee_Frame.Head].data[i]=UP_Zigbee_RecBuf[i];	
// 							UP_Zigbee_RecBuf[i]=0;
// 						}					
// 						
// 						Zigbee_Frame.Head+=1;	
// 						if(Zigbee_Frame.Head > UP_UART_FRAMENUM_MAX)
// 							Zigbee_Frame.Head = 0;		
// 					}
// 					len=0;
// 					index=0;
// 					FrameStart = 0;	
// 					sum = 0;					
// 					//UP_Zigbee_RecNum++;
// 				}
// 				else
// 				{
// 					UP_Zigbee_RecBuf[index++] = data;
// 					sum+=data;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			len=0;
// 			index=0;
// 			FrameStart = 0;	
// 			sum = 0;				
// 		}
// 	}
// }
void UP_Push_TxData(u8 S_ID,u8 D_ID,u8 len,u8 cmd,u8 *data)
{
	u8 i,sum;
	
	//Zigbee_Frame.DataBuf[Zigbee_Frame.Head].data
// 	UP_Zigbee_Putc(0xfe);
// 	UP_Zigbee_Putc(0xda);
// 	UP_Zigbee_Putc(len+7);
// 	UP_Zigbee_Putc(S_ID);
// 	UP_Zigbee_Putc(D_ID);
// 	UP_Zigbee_Putc(cmd);
// 	sum = 0xfe+0xda+7+len+S_ID+D_ID+cmd;
// 	for(i=0;i<len;i++)
// 	{
// 		UP_Zigbee_Putc(data[i]);	
// 		sum+=data[i];
// 	}
// 	UP_Zigbee_Putc(sum);
	UP_Zigbee_TxNum++;
	Zigbee_Frame.DataBuf[Zigbee_Frame.Head].data[0] = 0xfe;
	Zigbee_Frame.DataBuf[Zigbee_Frame.Head].data[1] = 0xda;
	Zigbee_Frame.DataBuf[Zigbee_Frame.Head].data[2] = len+7;
	Zigbee_Frame.DataBuf[Zigbee_Frame.Head].data[3] = S_ID;
	Zigbee_Frame.DataBuf[Zigbee_Frame.Head].data[4] = D_ID;
	Zigbee_Frame.DataBuf[Zigbee_Frame.Head].data[5] = cmd;
	sum = 0xfe+0xda+7+len+S_ID+D_ID+cmd;
	for(i=0;i<len;i++)
	{
		Zigbee_Frame.DataBuf[Zigbee_Frame.Head].data[6+i] = data[i];	
		sum+=data[i];
	}
	Zigbee_Frame.DataBuf[Zigbee_Frame.Head].data[len+6] = sum;
	
	Zigbee_Frame.Head++;
	if(Zigbee_Frame.Head == UP_UART_FRAMENUM_MAX)
		Zigbee_Frame.Head = 0;
	
}
void Check_Tx_Frame(UP_UART_FRAME *Tx_Frame)
{
	u8 i,len;
	
	if(Tx_Frame->Tail != Tx_Frame->Head)
	{
		len = Tx_Frame->DataBuf[Tx_Frame->Tail].data[2];
		for(i=0;i<len;i++)
			UP_Zigbee_Putc(Tx_Frame->DataBuf[Tx_Frame->Tail].data[i]);
		Tx_Frame->Tail++;
		if(Tx_Frame->Tail == UP_UART_FRAMENUM_MAX)
			Tx_Frame->Tail = 0;
		
	}
		
}
u8 Sensor[8];
void UP_Zigbee_Rec(u32 data)
{
	static u8 FrameStart = 0;
	static u8 index = 0;
	static u8 last_data;
	static u8 len;
//	static u8 z;
	//u8 data;
	u8 i,j,route_len;
	static u8 sum=0;
	//UP_Zigbee_RecNum++;
	if(0 == FrameStart)
	{	
		
		if((last_data==0xFE) && ((data==0xda)||(data==0xed)))//(data==0xcc||data==0xed||data==0xda))
		{
			FrameStart = 1;
			index = 2;
			last_data = 0;
			sum =0;
 			UP_Zigbee_RecBuf[0] = 0xFE;
 			UP_Zigbee_RecBuf[1] = data;
			Zigbee_RecTime_Count = 5;
		}
		else
		{
			last_data = data;	
		}
	}
	else
	{
		Zigbee_RecTime_Count = 5;
		if(2 == index)	
		{	
			len = UP_Zigbee_RecBuf[2] = data;
			sum = 0xd8+len;
			index = 3;
		}
		else
		{
			if(index == (len-1))
			{	UP_Zigbee_RecBuf[index]=data;
				//if(sum==data)
				//{
					UP_Zigbee_RecNum++;
					if(0xda==UP_Zigbee_RecBuf[1])
					{
						if(UP_Zigbee_RecBuf[3]!=UP_SYSTEM_ID)
						{
							
							switch(UP_Zigbee_RecBuf[5])
							{
								case 0x00:
									break;
								case 0x01:
									UP_System_Time = (UP_Zigbee_RecBuf[6]<<8)+ UP_Zigbee_RecBuf[7];										
									break;
								case 0x02:
									break;
								case 0x03:
									break;
								case 0x04:									
									route_len = UP_Zigbee_RecBuf[2]-7;
									if(!(route_len%4))
									{
										for(i=0;i<(route_len/4);i++)
											for(j=0;j<4;j++)
												UP_Route_Info[i][j] = UP_Zigbee_RecBuf[4*i+j+6];
									//	temp = 0x01;
										UP_Car_Wait_Start = 1;
									}
									//else
									//	temp = 0x00;
									//UP_Push_TxData(UP_SYSTEM_ID,0x00,1,0x04,&temp);
									break;
								case 0x05:
									UP_Car_Wait_ToStart = 1;
									break;
								case 0x06:
									UP_Car_WaitCharge = 1;
									break;
								default:
									break;
							}
						}	
					}	
					else if(0xed==UP_Zigbee_RecBuf[1]) 			
					{
						UP_Illegal_CheckData[0] = (UP_Zigbee_RecBuf[8]<<8)+UP_Zigbee_RecBuf[9];
						//Sensor[0] = UP_Zigbee_RecBuf[8];Sensor[1]=UP_Zigbee_RecBuf[9];
						UP_Illegal_CheckData[1] = (UP_Zigbee_RecBuf[10]<<8)+UP_Zigbee_RecBuf[11];
						UP_Illegal_CheckData[2] = (UP_Zigbee_RecBuf[12]<<8)+UP_Zigbee_RecBuf[13];
						UP_Illegal_CheckData[3] = (UP_Zigbee_RecBuf[14]<<8)+UP_Zigbee_RecBuf[15];
					}						
				//}
				len=0;
				index=0;
				FrameStart = 0;	
				sum = 0;					
				//UP_Zigbee_RecNum++;
			}
			else
			{
				UP_Zigbee_RecBuf[index++] = data;
				sum+=data;
			}
		}
	}
}
void Zigbee_TIMER_handler(u32 null)//
{
	static u8 count;
	if(Zigbee_RecTime_Count>0) Zigbee_RecTime_Count--;
	if(count == 5)
	{
		Check_Tx_Frame(&Zigbee_Frame);		
		count = 0;
	}
	else
		count++;
}

void UP_Zigbee_SetID(u8 ID)
{
	UP_Zigbee_Putc(0xfe);
	UP_Zigbee_Putc(0xcc);
	UP_Zigbee_Putc(0x01);
	UP_Zigbee_Putc(0x21);
	UP_Zigbee_Putc(0x09);
	UP_Zigbee_Putc(ID);
}
void UP_Zigbee_SetDeviceType(u8 type)//0-协调器     1-路由器
{
	UP_Zigbee_Putc(0xfe);
	UP_Zigbee_Putc(0xcc);
	UP_Zigbee_Putc(0x01);
	UP_Zigbee_Putc(0x27);
	UP_Zigbee_Putc(0x04);
	UP_Zigbee_Putc(type);	
}
void UP_Zigbee_RequireSensor(u8 S_ID,u8 D_ID)
{
	UP_Zigbee_Putc(0xfe);
	UP_Zigbee_Putc(0xed);
	UP_Zigbee_Putc(0x06);
	UP_Zigbee_Putc(S_ID);
	UP_Zigbee_Putc(D_ID);	
	UP_Zigbee_Putc(0x01);
}
void UP_Zigbee_SendData(u8 S_ID,u8 D_ID,u8 len,u8 cmd,u8 *data)
{
	u8 i;
	u8 sum;
	UP_Zigbee_TxNum++;
	UP_Zigbee_Putc(0xfe);
	UP_Zigbee_Putc(0xda);
	UP_Zigbee_Putc(len+7);
	UP_Zigbee_Putc(S_ID);
	UP_Zigbee_Putc(D_ID);
	UP_Zigbee_Putc(cmd);
	sum = 0xfe+0xda+7+len+S_ID+D_ID+cmd;
	for(i=0;i<len;i++)
	{
		UP_Zigbee_Putc(data[i]);	
		sum+=data[i];
	}
	UP_Zigbee_Putc(sum);
// 	UP_Zigbee_Putc(0xfe);
// 	UP_Zigbee_Putc(0xda);
// 	UP_Zigbee_Putc(0x08);
// 	UP_Zigbee_Putc(0x02);	
// 	UP_Zigbee_Putc(0x00);
// 	UP_Zigbee_Putc(0x01);
// 	UP_Zigbee_Putc(0x02);
// 	UP_Zigbee_Putc(0xe5);
}
void UP_Zigbee_GetConfig(void)
{
	UP_Zigbee_Putc(0xfe);
	UP_Zigbee_Putc(0xcc);
	UP_Zigbee_Putc(0x00);
	UP_Zigbee_Putc(0x27);	
	UP_Zigbee_Putc(0x00);
}
void UP_Zigbee_GetID(void)
{
	UP_Zigbee_Putc(0xfe);
	UP_Zigbee_Putc(0xcc);
	UP_Zigbee_Putc(0x03);
	UP_Zigbee_Putc(0x21);	
	UP_Zigbee_Putc(0x08);	
	UP_Zigbee_Putc(0x77);
	UP_Zigbee_Putc(0x07);
	UP_Zigbee_Putc(0x00);
	
}



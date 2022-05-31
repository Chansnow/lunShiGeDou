#include "STM32Lib\\stm32f10x.h"
#include "UP_UART_Parse.h"
#include "UP_Variable.h"

UP_UART_FRAME USR232_Frame;



u8 USR232_RecBuf[200];
u32 USR232_RecNum=0;
u8 recdata;

void USR232_RecHandler(u32 pdata)
{
	static u8 FrameStart = 0;
	static u8 index = 0;
	static u8 last_data;
	static u8 sum = 0;
	u8 data;
	u8 i;
	data = (u8) pdata;
	//USR232_RecNum++;dg r
	recdata = data;
	if(0 == FrameStart)
	{	
		
		if((last_data==0x55) && (data==0xaa))
		{
			FrameStart = 1;
			index = 2;
			last_data = 0;
			sum = 0;
			USR232_RecBuf[0] = 0x55;
			USR232_RecBuf[1] = 0xaa;
			//USR232_RecNum+=1;
		}
		else
		{
			last_data = data;
			
		}
	}
	else
	{
		if(2 == index)	
		{	
			USR232_RecBuf[2] = data;
			index = 3;
			sum = 0x55+0xaa+data;
		}
		else
		{
			if(index < (USR232_RecBuf[2]+4))
			{
				USR232_RecBuf[index++] = data;
				sum += data;
			}
			else
			{
				
				if(data == sum)
				{				
					USR232_Frame.DataBuf[USR232_Frame.Head].len = USR232_RecBuf[2];
					USR232_Frame.DataBuf[USR232_Frame.Head].cmd = USR232_RecBuf[3];
					for(i=0;i<USR232_RecBuf[2];i++)
						USR232_Frame.DataBuf[USR232_Frame.Head].data[i]=USR232_RecBuf[4+i];
					
					USR232_Frame.Head += 1;
					if(USR232_Frame.Head>UP_UART_FRAMENUM_MAX)
						USR232_Frame.Head = 0;
					//switch()
				}
				FrameStart = 0;
			}		
		}
	}
}

void COM_TIMER_handler(u32 null)
{
	static u16 count=0;
	if(100 == count)
	{
		UP_System_Time++;
		count=0;
	}
	else
		count++;
	
	if(USR232_Frame.Tail != USR232_Frame.Head)
	{
		USR232_Parse(&USR232_Frame.DataBuf[USR232_Frame.Tail]);
		USR232_Frame.Tail += 1;
		if(USR232_Frame.Tail > UP_UART_FRAMENUM_MAX)
			USR232_Frame.Tail = 0;
	}
	
}
extern void UP_USR232_Putc(unsigned char c);
void UP_USR232_Answer(u8 n)
{
	UP_USR232_Putc(0x55);
	UP_USR232_Putc(0xaa);
	UP_USR232_Putc(0x01);
	UP_USR232_Putc(0x02);
	if(n)
	{
		UP_USR232_Putc(0x01);
		UP_USR232_Putc(0x03);		
	}
	else
	{
		UP_USR232_Putc(0x00);
		UP_USR232_Putc(0x02);	
	}
}
extern void UP_Zigbee_SendData(u8 S_ID,u8 D_ID,u8 len,u8 *data);
void USR232_Parse(UP_UART_RECBUF *databuf)
{

	switch(databuf->cmd)
	{
		case 0x00:
			break;
		case 0x01:
			USR232_RecNum+=1;
			UP_System_Time = (databuf->data[0]<<8) + databuf->data[1];
			break;
		case 0x02:
			
		default:
			break;
	}
	
}



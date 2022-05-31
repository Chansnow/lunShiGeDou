#ifndef _UP_UART_PARSE_H
#define _UP_UART_PARSE_H




#define UP_UART_DATANUM_MAX	150
#define UP_UART_FRAMENUM_MAX 20
typedef struct _UART_REC_BUF
{
	u8 len;
	u8 cmd;
	u8 S_UD;
	u8 D_ID;
	u8 data[UP_UART_DATANUM_MAX];
	
}UP_UART_RECBUF;

typedef struct _UART_FRAME_QUEUE
{
	u8 Head;
	u8 Tail;
	UP_UART_RECBUF DataBuf[UP_UART_FRAMENUM_MAX];
}UP_UART_FRAME;



extern u32 USR232_RecNum;

extern void USR232_RecHandler(u32 pdata);
extern void COM_TIMER_handler(u32 null);
extern void USR232_Parse(UP_UART_RECBUF *databuf);

#endif


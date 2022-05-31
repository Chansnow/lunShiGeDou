#ifndef UP_RFID_H
#define UP_RFID_H



extern u8 UP_RFID_ReadSign;
extern u8 RF_RecBuf[10];



extern void UP_RFID_Init(void);
extern u8 UP_RFID_ReadCard(u8 buf[5]);
extern u8 UP_RFID_CheckID(u8 *ID1,u8 *ID2);//ID1为读到的卡号，ID2为要比对的卡号








#endif

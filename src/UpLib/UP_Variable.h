#ifndef UP_VARIABLE_H
#define UP_VARIABLE_H



#define UP_SYSTEM_ID 0x07




#define UP_SYSTEM_SensorID 0x20
#define UP_SYSTEM_VCC_MIN 70
#define UP_SYSTEM_VCC_MAX 80
#define UP_SYSTEM_Sensor 800

extern u32 UP_System_Time;
extern u16 UP_System_Vcc;
extern u8 UP_System_RecCmd_Start;
extern u8 UP_System_RouteIndex;


extern u8 UP_Car_Wait_ToStart;
extern u8 UP_Car_Wait_Start;
extern u8 UP_Car_WaitCharge;
extern u8 UP_Car_ChargeWait_ToStart;

extern u8 UP_Route_NodeNum;
extern u8 UP_Route_Info[50][4];
extern u8 UP_Route_InfoIndex;
extern u8 UP_RFID_CrossID[36][5];
extern u8 UP_Route_StopCount;
extern u16 UP_Illegal_CheckData[4];
extern u8 UP_Back_CrossAllowSign;




extern u8 UP_RFID_GetIdIndex(u8 node);
extern void UP_Clear_RoutInfo(void);







#endif


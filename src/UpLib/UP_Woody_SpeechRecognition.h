
#ifndef UP_Woody_SpeechRecognition
#define UP_Woody_SpeechRecognition


extern u8 flage ;				//接收标志
extern u8 Tab;
extern u8 num;
extern u8 Var;
extern u16 ID;
extern u32 TempData;
extern char  UP_Woody_ComparisonTables[7];
extern char  TestCommand[5];		
extern char  UP_Woody_StartSpeech[5];
extern char  UP_Woody_Read[5];
extern char  UP_Woody_Closing[5];
extern char  UP_Woody_ReturnData[6];
extern void  UP_Woody_Speech_ClearData(void);
extern void  UP_Display_Return_Text(void);
extern void  UP_Display_Return_Read(void);
extern void  UP_Woody_Speech_TestCommand(void);
extern void  UP_Woody_StartSpeechRecognize(void);
extern void  UP_Woody_CloseSpeechRecognize(void);
extern void  UP_Woody_Speech_ReadData(void);
extern void  USR232_Speech_Hadler(u32 TempData);
extern void  UP_Woody_SpeechRecognize_Init(void);
extern u16 UP_Woody_Speech_ID_Judge(void);
extern void UP_Woody_Display_Speech_ID(void);
#endif

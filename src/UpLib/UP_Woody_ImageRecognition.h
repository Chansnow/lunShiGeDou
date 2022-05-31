

#ifndef UP_Woody_ImageRecognition_H
#define UP_Woody_ImageRecognition_H

//Ӳ����ʼ��
extern u8 i;
extern u8 lab;
extern u8 flam;
extern u8 number;
extern u8 Send[2];
extern u32 Pixel;
extern u32 Pixel_0,Pixel_1,Pixel_2,Pixel_3,Pixel_4,Pixel_5,Pixel_6,Pixel_7;
extern u32 X_0, X_1, X_2, X_3,Y_0,Y_1,Y_2,Y_3,X,Y;
extern u8 voice_id;
extern  u8 revoic_flage;
extern void UP_Woody_Init(void);

extern char  UP_Woody_ReturnData1[20];
extern char  UP_Woody_StartImageRecognition[5];//����ͼ��ʶ��

extern char  UP_Woody_ReturnImageRecognition[20];//���ͼ��ʶ�𷵻ص���
extern char  UP_Woody_ClosingImageRecognition[5];//�ر�ͼ��ʶ��
extern void  UP_Clear_ImageRecognition_Data(void);

 extern void UP_Woody_Display_ReturnImageRecognize(void);
extern void UP_Woody_StartImageRecognize(void);
extern void UP_Woody_CloseImageRecognize(void);
extern void UP_Woody_Clear_ImageRecognize_Data(void);
extern u32 UP_Woody_ImagePixel(void);
extern void UP_Woody_Display_Pixel(void);
extern u32 UP_Woody_X_Coordinates(void);
extern u32 UP_Woody_Y_Coordinates(void);

extern void UP_Woody_YellowRecognize(u8 data);
extern void UP_Woody_GreenRecognize(u8 data);
extern void UP_Woody_BlueRecognize(u8 data);
extern void UP_Woody_RedRecognize(u8 data);
extern void UP_Woody_PinkRecognize(u8 data);
extern void UP_Woody_WhiteRecognize(u8 data);

//����USR232�����ж���ں���
extern void USR232_Hadler(u32 TempData);
//���嶨ʱ���ж���ں���
extern void TimeHadler(u32 timechannel);

#endif

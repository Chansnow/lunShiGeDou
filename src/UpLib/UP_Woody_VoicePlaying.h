//#include "UP_Woody_VoicePlaying.h"

#ifndef UP_Woody_VoicePlaying_H
#define UP_Woody_VoicePlaying_H

//Ӳ����ʼ��
extern u8 temp;	
extern u32 w[2];
extern u32 data1;
extern u32 H,L;
extern char  UP_Woody_StartMusic[5];//������������ָ��
extern char  UP_Woody_MusicPlaying[7];//��������ָ��˴�����0001����
extern char  UP_Woody_ClosingMusic[5];//�ر���������ָ��
extern char  UP_Woody_ReturnMusic[20];//����������ŷ��ص���
extern void UP_Woody_StartMusicPlay(void);
extern void UP_Woody_CloseMusicPlay(void);
extern void UP_Woody_PlayingMusic(u32 data1);

//����USR232�����ж���ں���
extern void USR232_Hadler(u32 TempData);

#endif

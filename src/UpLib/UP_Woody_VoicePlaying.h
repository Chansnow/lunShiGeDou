//#include "UP_Woody_VoicePlaying.h"

#ifndef UP_Woody_VoicePlaying_H
#define UP_Woody_VoicePlaying_H

//硬件初始化
extern u8 temp;	
extern u32 w[2];
extern u32 data1;
extern u32 H,L;
extern char  UP_Woody_StartMusic[5];//启动语音播放指令
extern char  UP_Woody_MusicPlaying[7];//语音播放指令，此处播放0001歌曲
extern char  UP_Woody_ClosingMusic[5];//关闭语音播放指令
extern char  UP_Woody_ReturnMusic[20];//存放语音播放返回的数
extern void UP_Woody_StartMusicPlay(void);
extern void UP_Woody_CloseMusicPlay(void);
extern void UP_Woody_PlayingMusic(u32 data1);

//定义USR232接收中断入口函数
extern void USR232_Hadler(u32 TempData);

#endif

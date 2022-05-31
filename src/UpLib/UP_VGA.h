#ifndef UP_VGA_H
#define UP_VGA_H


extern u16  speed;  				//小车基础速度
#define	VGA_TURN_LEFT 1
#define	VGA_TURN_RIGHT 2
extern u8 UP_VGA_ForwardSign;
extern u8 UP_VGA_TrackSign;
extern u8 UP_VGA_CrossSign;
extern u8 UP_VGA_CrossSign2;

extern void UP_VGA_Timer(void);
extern void UP_VGA_OPEN_USART3(void);
// extern void UP_VGA_SetSpeed(s16 left,s16 right);
// extern void SetSpeed(s16 left,s16 right);
extern void UP_VGA_DIS_TRACKSIGN(u8 line);
extern void UP_VGA_MOTION_FORWARD(void);
extern void UP_VGA_MOTION_STOP(void);
extern void UP_VGA_MOTION_TURN(u8 dir);
extern void UP_VGA_PROTECTSET(u8 ADCChannel,u16 ProtectDis);

#endif

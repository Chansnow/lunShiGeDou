#ifndef _CONTROL_H
#define _CONTROL_H
extern int AD1;		//左前红外测距
extern int AD2;		//左中红外测距
extern int AD3;			//左后红外测距
extern int AD4;			//右前红外测距
extern int AD5;		//右中红外测距
extern int AD6;		//右后红外测距
extern int AD7;		//前左红外测距
extern int AD8;			//前右红外测距

extern int AD9;	//左前防掉台红外光电
extern int AD10;	//右前防掉台红外光电
extern int AD11;		//右后防掉台红外光电
extern int AD12;		//左后防掉台红外光电

extern int AD13;		//前红外光电
extern int AD14;		//右红外光电
extern int AD15;		//后红外光电
extern int AD16;			//左红外光电
extern int edge_flag;  //置1检测到边缘(time)
extern int fight_flag; //置1进入攻击模式
extern int stage_flag;//置1在台上
extern int stage_scan_flag;//置1中断中允许台上台下检测
extern int Qian;		//前有无敌人
extern int You;		//右有无敌人
extern int Hou;		//后有无敌人
extern int Zuo;		//左有无敌人	
extern int left;
extern int right;
extern int shangtaiflag;
extern int nStage;	//检测在台上还是在台下
extern int cnt;

extern void scan(void);
extern void enermy(void);
extern int Stage(void);
extern void Edge(void);


void move(int forward,int turn);
void wheel_45_L(void);
void wheel_45_R(void);
void wheel_45_L_H(void);
void wheel_45_R_H(void);
void wheel_90_L(void);
void wheel_90_R(void);
void wheel_135_L(void);
void wheel_135_R(void);
void wheel_180(void);
void wheel_L(void);
void wheel_R(void);
void shangtai(void);

void Fence(void);
void elude(void);


void wander(void);
void fight(void);
void fewchange(void);
void adjust_forward(void);
void main_control(void);
void fewchange(void);
void dispose(void);
void wheel_R(void);
#endif

#ifndef _CONTROL_H
#define _CONTROL_H
extern int AD1;		//��ǰ������
extern int AD2;		//���к�����
extern int AD3;			//��������
extern int AD4;			//��ǰ������
extern int AD5;		//���к�����
extern int AD6;		//�Һ������
extern int AD7;		//ǰ�������
extern int AD8;			//ǰ�Һ�����

extern int AD9;	//��ǰ����̨������
extern int AD10;	//��ǰ����̨������
extern int AD11;		//�Һ����̨������
extern int AD12;		//������̨������

extern int AD13;		//ǰ������
extern int AD14;		//�Һ�����
extern int AD15;		//�������
extern int AD16;			//�������
extern int edge_flag;  //��1��⵽��Ե(time)
extern int fight_flag; //��1���빥��ģʽ
extern int stage_flag;//��1��̨��
extern int stage_scan_flag;//��1�ж�������̨��̨�¼��
extern int Qian;		//ǰ���޵���
extern int You;		//�����޵���
extern int Hou;		//�����޵���
extern int Zuo;		//�����޵���	
extern int left;
extern int right;
extern int shangtaiflag;
extern int nStage;	//�����̨�ϻ�����̨��
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

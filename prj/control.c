#include "control.h"
#include "UP_System.h"

int AD1 = 0;		//��ǰ������
int AD2 = 0;		//���к�����
int AD3 = 0;		//��������

int AD4 = 0;		//��ǰ������
int AD5 = 0;		//���к�����
int AD6 = 0;		//�Һ������

int AD7 = 0;		//ǰ�������
int AD8 = 0;		//ǰ�Һ�����

int AD9 = 0;		//��ǰ����̨������
int AD10 = 0;		//��ǰ����̨������
int AD11 = 0;		//�Һ����̨������
int AD12 = 0;		//������̨������

int AD13 = 0;		//ǰ������
int AD14 = 0;		//�Һ�����
int AD15 = 0;		//�������
int AD16 = 0;		//�������

int edge_flag=0;  //��1��⵽��Ե(time)
int fight_flag=0; //��1���빥��ģʽ

int stage_flag=0;//��1��̨��
int stage_scan_flag=0;//��1�ж�������̨��̨�¼��

int enermy_scan_flag=0;

int Qian = 0;		//ǰ���޵���
int You = 0;		//�����޵���
int Hou = 0;		//�����޵���
int Zuo = 0;		//�����޵���	

int left = 0;
int right = 0;
int shangtaiflag=0;
int nStage = 0;	//�����̨�ϻ�����̨��
int cnt=0;
void Rush_up(void);
void scan()
{
	AD1 = UP_ADC_GetValue(0); //��ǰ������
	AD2 = UP_ADC_GetValue(1); //���к�����
	AD3 = UP_ADC_GetValue(2); //���������
	AD4 = UP_ADC_GetValue(3); //��ǰ������
	AD5 = UP_ADC_GetValue(4); //���к�����
	AD6 = UP_ADC_GetValue(5); //���Һ�����
	AD7 = UP_ADC_GetValue(6); //ǰ�������
	AD8 = UP_ADC_GetValue(7); //ǰ�Һ�����
	AD9  = UP_ADC_GetValue(8);  //��ǰ�����紫����
	AD10 = UP_ADC_GetValue(9); //��ǰ�����紫����
	AD11 = UP_ADC_GetValue(10); //�Һ�����紫����
	AD12 = UP_ADC_GetValue(11); //�������紫����
	AD13 =UP_ADC_GetValue(12); //ǰ������
	AD14 =UP_ADC_GetValue(13); //�Һ�����
	AD15 =UP_ADC_GetValue(14); //�������
	AD16 =UP_ADC_GetValue(15); //�������
}

void move(int forward,int turn)
{
	left = forward;
	right = turn;
	if(left > 1023)
	{
		left = 1023;
	}
	if(left < -1023)
	{
		left = -1023;
	}
	if(right > 1023)
	{
		right = 1023;
	}
	if(right < -1023)
	{
		right = -1023;
	} 
	UP_CDS_SetSpeed(1,-right);
	UP_CDS_SetSpeed(2,left);
//	UP_delay_ms(3);
//	UP_CDS_SetSpeed(3, left);
//	UP_CDS_SetSpeed(4, -right);
}


/////ת�亯��//////
void wheel_45_L()
{
	move(-500,500);
	UP_delay_ms(480);
	move(0,0);
}
void wheel_45_R()
{
	move(500,-500);
	UP_delay_ms(480);
	move(0,0);
}
void wheel_45_L_H()
{
	move(-700,700);
	UP_delay_ms(200);
	move(0,0);
}
void wheel_45_R_H()
{
	move(700,-700);
	UP_delay_ms(200);
	move(0,0);
}
void wheel_90_L()
{
	move(-700,700);
	UP_delay_ms(300);
	move(0,0);
}
void wheel_90_R()
{
	move(800,-800);
	UP_delay_ms(400);
	move(0,0);
}
void wheel_135_L()
{
	move(-800,800);
	UP_delay_ms(480);
	move(0,0);
}
void wheel_135_R()
{
	move(800,-800);
	UP_delay_ms(480);
	move(0,0);
}
void wheel_180()
{
	move(-800,800);
	UP_delay_ms(750);
	move(0,0);
}
void wheel_R()
{
	move(500,-500);
	UP_delay_ms(20);
}
void wheel_L()
{
	move(-500,500);
	UP_delay_ms(20);
}
///////��̨////////
void shangtai()
{
	stage_scan_flag=0;
	move(0,0);
	UP_delay_ms(100);
	
	move(-1023,-1023);//��׼��̨
    UP_delay_ms(1000);
	
	move(0,0);
	UP_delay_ms(100);
	
	wheel_45_L();
	
	stage_scan_flag=1;
}
//	stage_scan_flag=0;
//	UP_delay_ms(100);
//	
//		move(0,0);	//ͣ��������ֹǰһ״̬��ת��ı���̨����
//		UP_delay_ms(100);
//		move(-1023,-1023);//��׼��̨
//		UP_delay_ms(1500);
//	
//		move(0,0);
//		UP_delay_ms(100);
//		wheel_180();
//	
//	stage_scan_flag=1;
//	UP_delay_ms(100);



//����Ƿ���̨��
int Stage()
{
		if( ( ((AD1>800)||(AD2>800)) && ((AD4>800)||(AD5>800)) ) || ( ((AD7>800)||(AD8>800)) && ((AD3>800)||(AD6>800)) ) )
		{
			stage_flag=0;
			return 0;  //��̨��
		}
		else
		{
			stage_flag=1;
			return 1;   //��̨��
		}

}


//����ͷ������΢������
//void fewchange()
//{
//	int count=0;
//	
//	while( ( ((AD7)>(AD8)) && (AD7-AD8>300) )||( ((AD8)>(AD7)) && (AD8-AD7>300) ) )
//	{
//		count++;
//		
//		if((AD7)>(AD8))
//		{
//			move(0,200);
//			UP_delay_ms(100);
//		}
//		else if((AD8)>(AD7))
//		{
//			move(200,0);
//			UP_delay_ms(100);
//		}
//		
//		if(count>10)
//		{
//			count=0;
//			break;
//		}
//	}

//}

void Fence()//��̨�´������⳯�� 
{
	
	   AD13=UP_ADC_GetValue(12); 
		 AD14=UP_ADC_GetValue(13); 
		 AD16=UP_ADC_GetValue(15); 
		 
	while(AD13<1000||(AD14>1000&&AD16>1000))
	 {
		 wheel_R();
		 AD13=UP_ADC_GetValue(12); 
		 AD14=UP_ADC_GetValue(13); 
		 AD16=UP_ADC_GetValue(15); 
		
	 }
	dispose();
		
}
void dispose() //̨���������
{
	 
	 scan();
	 shangtaiflag=0;
	if(shangtaiflag==0)
	{
		if(AD5>1200&&AD2<1000&&AD14<1000)
	 {
		 shangtaiflag=1;
		 move(600,600);
		 UP_delay_ms(100);
		 wheel_90_L();
		 move(300,300);
		 UP_delay_ms(600);
		  
	 }
	else if(AD2>1200&&AD5<1000&&AD16<1000)
	 {
		  shangtaiflag=1;
		  move(600,600);
		  UP_delay_ms(100); 
		  wheel_90_R();
		  move(300,300);
		  UP_delay_ms(600); 
		 
	 }
	else
	{	
		move(300,300);
	  UP_delay_ms(200);
		 shangtaiflag=1;
	}
 }
  if(shangtaiflag)
  //����״̬
{
		if(AD2>1200&&AD5>1200&&AD14>1000&&AD16<1000)
	{
		 wheel_90_R();
	   Rush_up();
	}
	 if(AD2>1200&&AD5>1200&&AD14<1000&&AD16>1000)
	{
	  wheel_90_L();
	 Rush_up();
	}
	
 }
}



void Rush_up() //��̨�� ����
{
	move(-1023,-1023);
	UP_delay_ms(1500);
	wheel_180();
}






//������
void enermy()
{
	if(AD1>1100)//��ǰ�е���
	{
		 fight_flag=1;
	}
	else if(AD4>1100)//��ǰ�е���
	{
		 fight_flag=2;
	}
	else if((AD7+AD8)>2300||AD13<1000)//ǰ�е���
	{
		 fight_flag=3;
	}
	else if(AD2>1200||AD16<1000)//�����е���
	 {
		 fight_flag=4;
	 }
	 else if(AD5>1200||AD14<1000)//�����е���
	 {
		 fight_flag=5;
	 }
	 else if(AD3>1200)
	 {
		 fight_flag=6;
	 }
	 else if(AD5>1200)
	 {
		 fight_flag=7;
	 }
	 else if(AD15<1000)
	 {
		 fight_flag=8;
	 }
	 else 
		 fight_flag=0;
//	 else if(AD2>1200||AD16<1000)//�����е���
//	 {
//		 fight_flag=5;
//	 }
//	 else if(AD5>1200||AD14<1000)//�����е���
//	 {
//		 fight_flag=6;
//	 }
//	 else if(AD3>1200)
//	 {
//		 fight_flag=7;
//	 }
//	 else if(AD5>1200)
//	 {
//		 fight_flag=8;
//	 }
//	 else if(AD15<1000)
//	 {
//		 fight_flag=9;
//	 }
//	 else if(AD13<1000|| AD7>1200 ||AD8>1200)
//	 {
//		 fight_flag=10;
//	 }
}

void Edge()  //����Ե
{
	edge_flag=0;
	
		//δ��⵽��Ե
		if((AD9 < 1000)&&(AD10 < 1000)&&(AD11 < 1000)&&(AD12 < 1000))
		{
			edge_flag=0;
		}
		
		
		//��ǰ��⵽��Ե
		else if((AD9 > 1000)&&(AD10 < 1000)&&(AD11 < 1000)&&(AD12 < 1000))
		{
			edge_flag=1;
		}
		
		//��ǰ��⵽��Ե
		else if((AD9 < 1000)&&(AD10 > 1000)&&(AD11 < 1000)&&(AD12 < 1000))
		{
			edge_flag=2;
		}
		
		//�Һ��⵽��Ե
		else if((AD9 < 1000)&&(AD10 < 1000)&&(AD11 > 1000)&&(AD12 < 1000))
		{
			edge_flag=3;
		}
		
		//����⵽��Ե
		else if((AD9 < 1000)&&(AD10 < 1000)&&(AD11 < 1000)&&(AD12 > 1000))
		{
			edge_flag=4;
		}
		
		//ǰ��������⵽��Ե
		else if((AD9 > 1000)&&(AD10 > 1000)&&(AD11 < 1000)&&(AD12 < 1000))
		{
			edge_flag=5;
		}
		
		//��������⵽��Ե
		else if((AD9 < 1000)&&(AD10 < 1000)&&(AD11 > 1000)&&(AD12 > 1000))
		{
			edge_flag=6;
		}
		
		//���������⵽��Ե
		else if((AD9 > 1000)&&(AD10 < 1000)&&(AD11 < 1000)&&(AD12 > 1000))
		{
			edge_flag=7;
		}
		
		//�Ҳ�������⵽��Ե
		else if((AD9 < 1000)&&(AD10 > 1000)&&(AD11 > 1000)&&(AD12 < 1000))
		{
			edge_flag=8;
		}
		
		else if((AD9>1000)&&(AD10>1000)&&(AD11>1000)&&(AD12<1000))
		{
			edge_flag=9;
		}
		
		else if((AD10>1000)&&(AD11>1000)&&(AD12>1000)&&(AD9<1000))
		{
			edge_flag=10;
		}
		
		else if((AD11>1000)&&(AD12>1000)&&(AD9>1000)&&(AD10<1000))
		{
			edge_flag=11;
		}
		
		else if((AD12>1000)&&(AD9>1000)&&(AD10>1000)&&(AD11<1000))
		{
			edge_flag=12;
		}
		
}


//����
void wander()
{
	//int count0=0;
	while((!edge_flag)&&(!fight_flag))
	{
//		count0++;
		
		move(500,500);
		UP_delay_ms(50);
		
//		if(count0>65535)
//		{
//			break;
//		}	
	}
	
}

//��������
void fight()
{
		while((!edge_flag)&&(fight_flag))
		{
			
			scan();
			Edge();
			
			if(AD9>1000||AD10>1000)
			{
				move(-800,-800);
				UP_delay_ms(30);
				break;
			}
			
			if(edge_flag)	break;
			
			if(!edge_flag)
			{
				move(700,700);
				UP_delay_ms(10);
			}
				
		}
}

void main_control()
{
	shangtai();
     
	while(1)
	{
//		if(nStage==0)
//		{
//			Fence();
//		}			
//			if(nStage==1)
//		{
			
			enermy_scan_flag=1;
				while(1)
				{
					wander();
					if(fight_flag) break;
					if(edge_flag)  break;
				}
				
				if(edge_flag&&(!fight_flag))
				{
						if(edge_flag==1)
						{
							
							move(-500,-500);
							UP_delay_ms(300);
							wheel_45_R();
						}
						if(edge_flag==2)
						{
							
							move(-500,-500);
							UP_delay_ms(250);
							wheel_45_L();
						}
						if(edge_flag==3)
						{
							move(500,500);
							UP_delay_ms(300);
							wheel_45_R();
						}
						if(edge_flag==4)
						{
							move(500,500);
							UP_delay_ms(300);
							wheel_45_L();
						}
						if(edge_flag==5)
						{
							move(-700,-700);
							UP_delay_ms(400);
							wheel_90_R();
						}
						if(edge_flag==6)
						{
							move(700,700);
							UP_delay_ms(400);
							wheel_90_R();
						}
						if(edge_flag==7)
						{
							wheel_90_R();
							move(600,600);
							UP_delay_ms(300);
							
						}
						if(edge_flag==8)
						{
							wheel_90_L();
							move(600,600);
							UP_delay_ms(250);
						}
						if(edge_flag==9)
						{
							move(-700,-700);
							UP_delay_ms(100);	
							wheel_90_L();
							move(300,300);
							UP_delay_ms(100);
						}
						if(edge_flag==10)
						{
							move(700,700);
							UP_delay_ms(100);
							wheel_90_L();
							move(300,300);
							UP_delay_ms(100);
						}
						if(edge_flag==11)
						{
							move(700,700);
							UP_delay_ms(100);
							wheel_90_R();
							move(300,300);
							UP_delay_ms(100);
						}
						if(edge_flag==12)
						{
							move(-700,-700);
							UP_delay_ms(100);
							wheel_90_R();
							move(300,300);
							UP_delay_ms(100);
						}
				}
				if(edge_flag&&fight_flag)
				{
					move(-600,-600);
					UP_delay_ms(50);
				}
				if(fight_flag&&(!edge_flag))
				{
					if(fight_flag==1)
					{
						wheel_45_L();
						fight();
					}
					if(fight_flag==2)
					{
						wheel_45_R();
						fight();
					}
					if(fight_flag==3)
					{
						fight();
					}
					if(fight_flag==4)
					{
						wheel_90_L();
						fight();
					}
					if(fight_flag==5)
					{
					  wheel_90_R();
						fight();
					}
					if(fight_flag==6)
						{
					    move(0,0);
							wheel_135_L();
							fight();
						}
						if(fight_flag==7)
						{
					    move(0,0);
							wheel_135_R();
							fight();
						}
						if(fight_flag==8)
						{
					    move(0,0);
							wheel_180();
							fight();
						}  
					
//						if(fight_flag==10)
//						{
//							fight();
//						}
//						if(fight_flag==3)
//						{
//							move(0,0);
//							wheel_45_L();
//							move(400,400);
//							UP_delay_ms(100);
//						}
//						if(fight_flag==4)
//						{
//					    move(0,0);
//							wheel_45_R();
//							move(400,400);
//							UP_delay_ms(100);
//						}
//						if(fight_flag==5)
//						{
//					    move(0,0);
//							wheel_90_L();
//							move(400,400);
//							UP_delay_ms(100);
//						}
//						if(fight_flag==6)
//						{
//					    wheel_90_R();
//							move(400,400);
//							UP_delay_ms(100);
//						}
//						if(fight_flag==7)
//						{
//					    move(0,0);
//							wheel_135_L();
//							move(400,400);
//							UP_delay_ms(100);
//						}
//						if(fight_flag==8)
//						{
//					    move(0,0);
//							wheel_135_R();
//							move(400,400);
//							UP_delay_ms(100);
//						}
//						if(fight_flag==9)
//						{
//					    move(0,0);
//							wheel_180();
//							move(400,400);
//							UP_delay_ms(100);
//						}  
//					
				}
//				if((!fight_flag)&&(!edge_flag))
//      	   continue;
//		}
	}
}

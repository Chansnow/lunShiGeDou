#include "UP_System.h"
#include "control.h"

extern int enermy_scan_flag;

int main()
{
	/*初始化系统*/
	UP_System_Init();
	
  while(1)
	{
		stage_scan_flag=1;
		enermy_scan_flag=0;
		if(AD14<1000&&AD16<1000&&AD14!=0&&AD16!=0)
		{
			break;
		}
		UP_delay_ms(10);
	}
	main_control();
	 
}



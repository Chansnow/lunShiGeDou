/******************************************************************/
//	Copyright (C), 2011-2013, ±±¾©²©´´ 
//  Author   	  	: ÇÇäìéª  
//  Update Date   : 2013/07/12
//  Version   	  : 1.3          
//  Description   : Modification for new LCD
/******************************************************************/ 

#ifndef LCDS_H
#define LCDS_H

#define RS_H		    (GPIOD->BSRR = GPIO_Pin_9)
#define RS_L		    (GPIOD->BRR = GPIO_Pin_9) 

#define CS_H		    (GPIOD->BSRR = GPIO_Pin_8)
#define CS_L 		    (GPIOD->BRR = GPIO_Pin_8)

#define RST_H	        (GPIOC->BSRR = GPIO_Pin_6)
#define RST_L	        (GPIOC->BRR = GPIO_Pin_6)

#define SCL_H		    (GPIOD->BSRR = GPIO_Pin_11)
#define SCL_L		    (GPIOD->BRR = GPIO_Pin_11)

#define SDA_H		    (GPIOD->BSRR = GPIO_Pin_10)
#define SDA_L		    (GPIOD->BRR = GPIO_Pin_10)

#define LCD_BK_ON       (GPIOC->BSRR = GPIO_Pin_7)
#define LCD_BK_OFF      (GPIOC->BRR = GPIO_Pin_7)

extern void UP_LCD_Init(void);
extern void UP_Lcds_Config(void);
extern void UP_LCD_OnOff(u8 onoff);
extern void UP_LCD_Turn(u8 dec);
extern void UP_LCD_ClearScreen(void);
extern void UP_LCD_ClearLine(u8 y);
extern void UP_LCD_ShowLetter(u8 x, u8 y, u8 ch);
extern void UP_LCD_ShowCharacter(u8 x, u8 y, char cha[2]);
extern u8 UP_LCD_ShowString(u8 x, u8 y, char *pstring);
extern u8 UP_LCD_ShowCharacterString(u8 x, u8 y, char *pstring);
extern u8 UP_LCD_ShowInt(u8 x, u8 y, int n);
extern void UP_LCD_ShowProgressBar(u8 y,u8 percent);
extern void UP_LCD_ShowHex(u8 x,u8 y,u8 hex);
#endif


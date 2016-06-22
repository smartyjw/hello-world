#ifndef __LCD_H__
#define __LCD_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


/* Exported types ------------------------------------------------------------*/
extern __IO u8 u8SpeedLevel;
extern __IO uint8_t LcdReceiveDataFlag;
extern __IO uint8_t LcdReceiveData;
extern __IO uint8_t LcdMustReceive;
extern __IO uint8_t	Lcd_have_receive;
extern __IO uint8_t Lcd_Receive[];
extern __IO uint8_t	Lcd_have_scmd;
extern __IO	uint8_t	LCD_Start_Flag;
extern __IO	uint16_t SWTFlag;
extern __IO uint16_t u16DishCode[];
extern __IO uint8_t RunningMode;
extern __IO	uint16_t SWTFlag;
extern __IO uint8_t RunningMode;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define	LcdStartCmd					(0xAA)			//’æµÿ÷∑
#define	LcdDataPOs					(3)					//’æµÿ÷∑
#define	LcdCmdMustReceive		(8)
#define	LcdDataMustReceive	(10)
#define	Recive_lengthMax	(128)
#define	Send_lengthMax		(128)
/* Exported functions ------------------------------------------------------- */
void LCD_InitialView_Configuration(void);
void LcdReceiveJudge(void);
void KeyDeal(uint8_t	KeyData);
void LCD_Cell(uint8_t	Vol);
void xrd_cnt3string(uint16_t x0, uint16_t y0,uint16_t cnt);
#endif

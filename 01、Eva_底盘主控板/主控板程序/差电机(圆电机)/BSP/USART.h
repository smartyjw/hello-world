#ifndef __USART_H__
#define __USART_H__


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

	//communication with Speaker
	#define SPEAKER_USART						USART1
	#define SPEAKER_USART_BAUD			(9600)
	
	//communication with bluetooth	
	#define BT_USART								USART2
	#define BT_USART_BAUD						(9600)
	
	//communication with RFID Reader
	#define RFID_USART							USART3
	#define RFID_USART_BAUD					(115200) 
	
	//communication with magnetic navigation sensor	
	#define MAGNAVI_USART 					UART4
	#define MAGNAVI_USART_BAUD			(115200)
	
	//communication with pad 
	#define PAD_USART 							UART5
	#define PAD_USART_BAUD					(9600)
	
	//communication with LCD
	#define LCD_USART								USART6
	#define LCD_USART_BAUD					(115200)	
	
  
	

	

/* Exported functions ------------------------------------------------------- */

void USASRT_Configuration(void);
void Send_ReadMagNaviData(uint8_t *pCommand);
void Send_SpeakerData(u8 *pCommand, u8 u8Len);
void Send_LCDData(u8 temp);
void Send_Data(USART_TypeDef* USARTx ,u8 *pCommand, u8 u8Len);
#endif

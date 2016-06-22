#ifndef __RFID_H__
#define __RFID_H__
#include "stm32f4xx.h"

#define RfidMustRec	(4)
#define	UartRxne	0x00000020
#define	UartOver	0x00000008
	
extern __IO uint8_t	HavrCardFlag;
extern __IO uint8_t RFID_Rec;
extern __IO uint8_t RFID_Buffer[];
extern __IO uint8_t RFID_LowPower_Flag;
extern __IO uint8_t RFID_FindCar_Flag;
extern __IO uint8_t FindCar_Flag;
extern __IO uint8_t FindCmd_Flag;
extern __IO	uint8_t HaveStationeFlag;

extern __IO uint16_t Station;
extern __IO uint16_t NoHaveRfid100uS;//ºÏ≤‚”–ŒﬁRFID–≈∫≈
#endif

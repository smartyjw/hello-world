#ifndef __UART_PROTOCOL_H__
#define __UART_PROTOCOL_H__
#include "stm32f4xx.h"

#define CMD_LEN	(9)
#define HEADER (0x55)
#define END		 (0x7E)

#define MODE_CHANGE			(0x1E)
#define IRDA_TRIG_VOICE (0x1F)

extern u8 u8SendBuff[9];
void SetMode(u8 u8Mode);
void IrDA_Trigger_Voice(void);
#endif

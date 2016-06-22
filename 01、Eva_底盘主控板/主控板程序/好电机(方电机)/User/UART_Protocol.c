#include "UART_Protocol.h"
#include "LCD.h"

u8 u8SendBuff[9] = {0};

void SetMode(u8 u8Mode)
{
		u8SendBuff[0] = HEADER;
		u8SendBuff[1] = MODE_CHANGE;
		u8SendBuff[2] = u8Mode;
		u8SendBuff[3] = 0;
		u8SendBuff[4] = 0;
		u8SendBuff[5] = 0;
		u8SendBuff[6] = 0;
		u8SendBuff[7] = 0;
		u8SendBuff[8] = END;
}


void IrDA_Trigger_Voice(void)
{
	  u8SendBuff[0] = HEADER;
		u8SendBuff[1] = IRDA_TRIG_VOICE;
		u8SendBuff[2] = RunningMode;
		u8SendBuff[3] = 0;
		u8SendBuff[4] = 0;
		u8SendBuff[5] = 0;
		u8SendBuff[6] = 0;
		u8SendBuff[7] = 0;
		u8SendBuff[8] = END;
}

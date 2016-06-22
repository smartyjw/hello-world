#include "ResetMode.h"
#include "UART_Protocol.h"
#include "USART.h"
#include "LCD.h"

void CycleSendMode(void)
{
		static u32 u32SendCnt = 0;
		
		u32SendCnt++;
		
		if (u32SendCnt % 2000) 
		{
				SetMode(RunningMode);
				Send_Data(PAD_USART, u8SendBuff, CMD_LEN);
		}
}

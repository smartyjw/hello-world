#include "Init.h"
#include "LED.h"
#include "Speaker.h"
#include "common.h"
#include "LCD.h"
#include "PWM.h"
#include "test.h"
#include "Reserved.h"
#include "VoiceHandler.h"
#include "Remote_Control.h"
#include "Dance.h"
#include "MiscIO.h"
#include "USART.h"
#include "UART_Protocol.h"

int main(void)
{
		BSP_Init();		
	 	GetClocksFreq_Test();
		
		GPIO_PAD_PWRON_Configuration();
		delay_ms(1000);					

		//Forward();
		//Back();			
					
				
		while (1) 
		{				
			#if 1	
			     VoiceHandler();
					 Dance_Without_MegneticNavi();
					 LED_Toggle();			
			#else			
					 IRDA_Test();
					 //TX6_RX6_Output_WithPhaseDiff();			
					 Music_Play_Times_Test(1, 100, 5000);
					 //MeasurePuslesPPR();
			#endif
		}
}

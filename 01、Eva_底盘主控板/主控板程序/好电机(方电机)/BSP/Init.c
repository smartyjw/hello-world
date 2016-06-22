#include "stm32f4xx_rcc.h"
#include "SysTick.h"
#include "LED.h"
#include "NVIC.h"
#include "USART.h"
#include "PWM.h"
#include "common.h"
#include "BLD.h"
#include "TIM.h"
#include "Reserved.h"
#include "IrDA.h"
#include "LCD.h"
#include "MiscIO.h"
#include "test.h"

void BSP_Init(void)
{	
		/* LED control IO configuration */
		GPIO_LED_Configuration();
		
		/* BLD control IO configruation */
		GPIO_BLD_Configruration();
		
		/* IrDA IO configuration */
		GPIO_IrDA_Configuration();
		
		/* systick configuration */
		SysTick_Configuration(1000); //interrupt once every 1000us	
		
	
		
		/* USART configuration */
		USASRT_Configuration();	
		
		/* PWM configuratioin */
		PWM_Configuration(10);   		//pwm output frequency at 10KHz
		
		/* Speed & Phase measurement configuration */
		SpeedExtraction_Configuration();
		
		/* LCD initial view configuration */
		LCD_InitialView_Configuration();
		
		/* NVIC configuration */
		NVIC_Configuration();				
		
		//TX6_RX6_UesdAsIO_Coinfiuration();
		
			
		
}

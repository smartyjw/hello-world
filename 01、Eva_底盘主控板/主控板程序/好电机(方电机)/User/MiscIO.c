#include "stm32f4xx_gpio.h"
#include "common.h"


__IO u8 u8PWRON;

void GPIO_PAD_PWRON_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
											
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	 
		
	//PG5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
  GPIO_Init(GPIOG, &GPIO_InitStructure);		
	
	GPIO_ResetBits(GPIOG, GPIO_Pin_5);
	delay_ms(2000);
	GPIO_SetBits(GPIOG, GPIO_Pin_5);


//	u8PWRON  = 1;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
// // GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//	
//  GPIO_Init(GPIOG, &GPIO_InitStructure);	
	
	
	
}

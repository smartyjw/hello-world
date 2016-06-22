#include "LED.h"
#include "common.h"

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

void GPIO_LED_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
											
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	 
		
	//D7(PB12), D6(PD13)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	 
		
	//D7(PB12), D6(PD13)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);
}

void Sys_LED(void)
{
	 GPIO_ToggleBits(GPIOB, GPIO_Pin_12);
}

void LED_Toggle(void)
{			
		GPIO_ToggleBits(GPIOB, GPIO_Pin_12);
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
#if 0		
		delay(12000000);		//toggle once around 500ms when system core clock at 168MHz 
#else
		delay_ms(200);
#endif
}

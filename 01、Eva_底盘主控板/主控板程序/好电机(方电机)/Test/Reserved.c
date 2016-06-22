#include "Reserved.h"
#include "common.h"

void TX6_RX6_UesdAsIO_Coinfiuration(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;	
												
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	 
			
		/* PG14(TXD6),PG9(RXD6) */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
		
		GPIO_Init(GPIOG, &GPIO_InitStructure);
}

void TX6_RX6_Output_WithPhaseDiff(void)
{
	//  while (1)
		{
			GPIO_SetBits(GPIOG, GPIO_Pin_9);
			delay_ms(1);		
			GPIO_SetBits(GPIOG, GPIO_Pin_14);		
			delay_ms(1);
			
			
			GPIO_ResetBits(GPIOG, GPIO_Pin_9);
			delay_ms(1);		
			GPIO_ResetBits(GPIOG, GPIO_Pin_14);		
			delay_ms(1);
		}
		
}

void TX6_Toggle(void)
{
		GPIO_ToggleBits(GPIOG, GPIO_Pin_14);
}

void TX6_WriteBits(BitAction BitVal)
{	
		GPIO_WriteBit(GPIOG, GPIO_Pin_14, BitVal);
}

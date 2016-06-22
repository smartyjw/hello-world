#include "SysTick.h"
#include "stm32f4xx.h"

u32 SystTickInterval;
/**
  * @brief  Inserts a interrupt interval.
  * @param  u32SysTickInterval: specifies the interrupt time length, in macroseconds.
  * @retval None
  */
	
void SysTick_Configuration(u32 u32SysTickInterval)
{
	 /* SystemFrequency / 1000000: interrupt once every 1us 
	 */	 
	SystTickInterval = u32SysTickInterval;
	if (SysTick_Config(SystTickInterval * (SystemCoreClock / 1000000)))	
	{
		/* Capture error */
		while (1);
	}
}

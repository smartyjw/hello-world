#ifndef __SYSTICK_H__
#define __SYSTICK_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
/* Exported types ------------------------------------------------------------*/
extern u32 SystTickInterval;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SysTick_Configuration(u32 u32SysTickInterval);
#endif

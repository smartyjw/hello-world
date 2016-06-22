#ifndef __COMMON_H__
#define __COMMON_H__
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	WELCOME_CUSTOMR_MODE = 0,
	DILIEVRY_MEALS_MDOE,
	DANCE_MODE,
	DIALOGUE_MODE
} RUNNING_MODE;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define __1S (1000)
#define ARR_COUNT(ARR) (sizeof(ARR) / sizeof(ARR[0]))
/* Exported functions ------------------------------------------------------- */
void delay(int delcnt);
void delay_ms(__IO uint32_t nTime);
#endif

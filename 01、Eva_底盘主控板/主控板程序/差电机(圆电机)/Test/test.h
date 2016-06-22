#ifndef __TEST_H__
#define __TEST_H__
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
/* Exported types ------------------------------------------------------------*/
typedef struct _test
{
		u16 u16Value;
		u8  u8Falg;
} TEST_TypeDef;

typedef struct _speaker_test
{
		u8 u8MusicPlayEn;
		u8 u8FloderNum;
		u8 u8Volume;
		u16 u16Times;
		u16 u16IntervalTime;
		u16 u16TimeOut;
		u8 u8MusicPlayingResult;
} SPEAKER_TEST_TypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void GetClocksFreq_Test(void);
void LED_Test(void);
void BLD_IO_Test(void);
void PWM_Configuration_Test(void);
void Forward(void);
void Back(void);
void IRDA_Test(void);
void Music_Player_Test(void);
void Music_Play_Status_Check(void);
void Music_Play_Times_Test(u16 u16Times, u16 u16IntervalTime, u16 u16TimeOut);
void MeasurePuslesPPR(void);
#endif

#ifndef __STATION_HANDLER_H__
#define __STATION_HANDLER_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
extern u8 LeftTurning_Flag;
extern u8 RightTurning_Flag;
extern u8 u8TableWareStatus;
extern u8 TurnBack_Flag;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define AVALIABLE_MAX_STATION_NUM (1000)
#define SPEC_STA_ORI (0)
#define TURNING_TIME (2500)
#define WAITING_TIME (1000)

#define DANCE_TRUN_LEFT_IN_CYC (5)
#define DANCE_TRUN_RIGHT_IN_CYC (10)
/*the station number below used for test */
#define SPEC_STA_1 (900)
#define SPEC_STA_2 (901)
#define SPEC_STA_3 (902)
#define SPEC_STA_4 (903)
#define IS_SPEC_STATION(STA_NUM)		((STA_NUM == SPEC_STA_1) || \
																		 (STA_NUM == SPEC_STA_2) || \
																		 (STA_NUM == SPEC_STA_3) || \
																		 (STA_NUM == SPEC_STA_4))																		 

#define IS_DANCE_STATION(STA_NUM)		((STA_NUM == DANCE_TRUN_LEFT_IN_CYC) || \
																		 (STA_NUM == DANCE_TRUN_RIGHT_IN_CYC) )

/*1: room A 2: room B*/
#define IS_LEFT_TURN(STA_NUM)			( (STA_NUM == 201) || \
																		(STA_NUM == 207) || \
																		(STA_NUM == 208) \
																		)
		
#define IS_RIGHT_TURN(STA_NUM)  	( (STA_NUM == 101) || \
																		(STA_NUM == 102) || \
																		(STA_NUM == 103) || \
																		(STA_NUM == 104) || \
																		(STA_NUM == 105) || \
																		(STA_NUM == 106) \
																	)

																	
/* Exported functions ------------------------------------------------------- */
void LeftTurning_Deceleration(void);
void RightTurning_Deceleration(void);
void LeftTurning_Movement(void);
void RightTurning_Movement(void);
void TurnBack_Deceleration(void);
void TurnBack_Movement(void);
#endif

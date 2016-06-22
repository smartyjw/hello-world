#include "stm32f4xx.h"
#include "stm32f4xx_type.h"
#include "TIM.h"
#include "Sensor_Acquisition.h"
#include "MagneticNavigation.h"

int SpotSpeed_LeftMotor = 0;
int SpotSpeed_RightMotor = 0;
int Count = 0;
int Dir_LM = 0;
int Dir_RM = 0;
uint16_t Count_LM = 0;
uint16_t Count_RM = 0;

void Sensor_Acquisition(void)
{ 
	  GetmMagNaviData();
		
		Count++;
		if(Count % 20 == 0)  //40
		{
		    Rotation_judgement();
		}
		if(Count > 200)      //300
		{
		    Count = 0;
        Speed_Acquisition();
		}
}
void Rotation_judgement(void)
{
    Dir_LM = (s32)(TIM_GetCounter(ENCODER_TIMER_L)) * (s32)(U32_MAX / (4*ENCODER_PPR)); 
		TIM_SetCounter(ENCODER_TIMER_L, 0);
		Dir_LM = -(s16)(Dir_LM / 65535);
		
		Dir_RM = (s32)(TIM_GetCounter(ENCODER_TIMER_R)) * (s32)(U32_MAX / (4*ENCODER_PPR)); 
		TIM_SetCounter(ENCODER_TIMER_R, 0);
		Dir_RM = (s16)(Dir_RM / 65535);
}
	  
void Speed_Acquisition(void)
{
		Count_LM = TIM4->CNT;
		TIM_SetCounter(TIM4, 0); 
		if(Dir_LM < 0)
		{
				SpotSpeed_LeftMotor = -1 * Count_LM;
		}
		else
		{
				SpotSpeed_LeftMotor = 1 * Count_LM;
		}
  
		Count_RM = TIM1->CNT;
		TIM_SetCounter(TIM1, 0); 
		if(Dir_RM < 0)
		{
				SpotSpeed_RightMotor = -1 * Count_RM;
		}
		else
		{
				SpotSpeed_RightMotor = 1 * Count_RM;
		}
}

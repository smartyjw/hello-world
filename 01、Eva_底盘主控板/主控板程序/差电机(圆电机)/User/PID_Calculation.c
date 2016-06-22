#include "stm32f4xx.h"
#include "PID_Calculation.h"
#include "Filtering_Algorithm.h"
#include "PWM_Output.h"
#include "Remote_Control.h"
#include "MagneticNavigation.h"
#include "Remote_Control.h"
#include "Station_Handler.h"
#include "RFID.h"
#include "LCD.h"
#include "IrDA.h"
#include "VoiceHandler.h"
#include "Dance.h"
#include "common.h"
#include "LCD.h"

#define DirectionCL_Kp  (2.5f) //1.2
#define DirectionCL_Ki  (0)
#define DirectionCL_Kd  (0.05f) //0.1f

#define DirectionCL_Kp_LowSpeed (2.5f)
#define DirectionCL_Kp_MidSpeed (3.5f)
#define DirectionCL_Kp_HigSpeed (4.5f)

float DirectionCL_PError;
float DirectionCL_PID = 0;

#define Increment_Kp  (0.001f) //0.004
#define Speed_Kp  (1.2f)
#define Speed_Ki  (0)
#define Speed_Kd  (0.05f)

float Speed_EXP = 0; //35
float Speed_Increment;
float SpeedLeft_EXP = 0;
float SpeedRight_EXP = 0;
float SpeedL_PID = 0;
float SpeedR_PID = 0;

#define RemoteControlInc_Kp (0.003f)
#define RemoteControl_Kp (1)
#define RemoteControl_Ki (0)
#define RemoteControl_Kd (0)

float RemoteControlL_EXP = 0;
float RemoteControlR_EXP = 0;
float RemoteControlL_PID = 0;
float RemoteControlR_PID = 0;

int PID_LeftMotor = 0;
int PID_RightMotor = 0;
													
void PID_Calculation(void)
{
	  if (Remote_Flag == 0)
		{
	      PID_DirectionCL();
				
	      PID_PositionCL();		
	    	
				PID_SpeedCL();
	      
				if((CTData == 0) && (Station == 0xFFFF))
		    {
           SpeedL_PID = SpeedR_PID = 0;
		    }
		    
	    	PID_LeftMotor = (int)SpeedL_PID;
	    	PID_RightMotor = (int)SpeedR_PID;
	  }
		else if (Remote_Flag == 1)
    {						
		    PID_RemoteControl();				
		    PID_LeftMotor = (int)RemoteControlL_PID;
		    PID_RightMotor = (int)RemoteControlR_PID;
		}		
}


void PID_DirectionCL(void)
{
    
	  //float DirectionCL_PError;
		float DirectionCL_Kp_Temp;
		
    float DirectionCL_IError;
    float DirectionCL_DError;
    float DirectionCL_LastError;
		
		DirectionCL_PError = (8 - CTData);//Direction);
    DirectionCL_IError += DirectionCL_PError;
    DirectionCL_DError = DirectionCL_PError - DirectionCL_LastError;
    DirectionCL_LastError = DirectionCL_PError;

#if 0
    DirectionCL_PID = DirectionCL_Kp * DirectionCL_PError + DirectionCL_Ki * DirectionCL_IError
		                      + DirectionCL_Kd * DirectionCL_DError;  
#else
		if (u8SpeedLevel == LOW_SPEED) 
		{
			  DirectionCL_Kp_Temp = DirectionCL_Kp_LowSpeed;
		}
		else if(u8SpeedLevel == MID_SPEED)
		{
			  DirectionCL_Kp_Temp = DirectionCL_Kp_MidSpeed;
		}
		else if (u8SpeedLevel == HIG_SPEED)
		{
			  DirectionCL_Kp_Temp = DirectionCL_Kp_HigSpeed;
		}
		else
		{}
		
		
	  DirectionCL_PID = DirectionCL_Kp_Temp * DirectionCL_PError + DirectionCL_Ki * DirectionCL_IError
		                      + DirectionCL_Kd * DirectionCL_DError;  
#endif													
}

void PID_PositionCL(void)
{
    ;; 	
}


void PID_SpeedCL(void)
{
    float SpeedL_PError;
    float SpeedL_IError;
    float SpeedL_DError;
    float SpeedL_LastError;
		
    float SpeedR_PError;
    float SpeedR_IError;
    float SpeedR_DError;
    float SpeedR_LastError;
    
			
		if (LCD_Start_Flag == DISABLE || u8Obstacle == 1)
		{
				Speed_EXP = 0;				
		}
		
		else if (LCD_Start_Flag == ENABLE)
		{
				Speed_EXP = u8SpeedLevel;				
		}
					
			if (((Station < AVALIABLE_MAX_STATION_NUM) && 
					 (Station != SPEC_STA_ORI) && 
					 (Station == SWTFlag))
				//	|| IS_SPEC_STATION(Station)  
					)
			{
#if 0			
					if (Station % 2 != 0)
					{
							LeftTurning_Deceleration();
					}
					else if(Station %2 == 0)
					{
							RightTurning_Deceleration();
					}			
#else 
					if (IS_LEFT_TURN(Station))
					{
							LeftTurning_Deceleration();
					}
					else if(IS_RIGHT_TURN(Station))
					{
							RightTurning_Deceleration();
					}			
					else 
					{
							if (Station % 2 == 0)
							{
									RightTurning_Deceleration();
							}
							else 
							{
									LeftTurning_Deceleration();
							}							
					}
#endif					
			}
			else if (Station == SWTFlag && Station == SPEC_STA_ORI) //origion
			{
					TurnBack_Deceleration();					
			}
			else 
			{	
					Station = 0xFFFF;
			}
		
	  Speed_Increment *= (1 - Increment_Kp);	
		Speed_Increment += Speed_EXP * Increment_Kp;		

    SpeedLeft_EXP = Speed_Increment - DirectionCL_PID;			
    SpeedRight_EXP = Speed_Increment + DirectionCL_PID;

		
		if (RunningMode == DANCE_MODE)
		{
		}
		else if (RunningMode == DILIEVRY_MEALS_MDOE)
		{
				if (((Station <= AVALIABLE_MAX_STATION_NUM) && (Station != SPEC_STA_ORI) && (Station == SWTFlag)) 
			   // || IS_SPEC_STATION(Station))                                                                  
					  )
			{ 
#if 0			
				 if (Station % 2 != 0)
				 {
				     LeftTurning_Movement();
				 }
				 else if ((Station % 2 == 0)) 
				 {
						 RightTurning_Movement();
				 }
#else
					if (IS_LEFT_TURN(Station))
					{
							LeftTurning_Movement();
					}
					else if (IS_RIGHT_TURN(Station))
					{
							 RightTurning_Movement();
					}
					else 
					{
							if (Station % 2 == 0)
							{
									RightTurning_Movement();
							}
							else
							{
									LeftTurning_Movement();
							}
					}
#endif 				 
			}	
			else if (Station == SWTFlag && Station == SPEC_STA_ORI && ExistFood() == 0)
			{
					TurnBack_Movement();
			}
		}			
			
    SpeedL_PError = SpeedLeft_EXP - Speed_LeftMotor;
    SpeedL_IError += SpeedL_PError;
    SpeedL_DError = SpeedL_PError - SpeedL_LastError;
    SpeedL_LastError = SpeedL_PError;
    SpeedL_PID = Speed_Kp * SpeedL_PError + Speed_Ki * SpeedL_IError + Speed_Kd * SpeedL_DError;
	  
    SpeedR_PError = SpeedRight_EXP - Speed_RightMotor;
    SpeedR_IError += SpeedR_PError;
    SpeedR_DError = SpeedR_PError - SpeedR_LastError;		
    SpeedR_LastError = SpeedR_PError;
    SpeedR_PID = Speed_Kp * SpeedR_PError + Speed_Ki * SpeedR_IError + Speed_Kd * SpeedR_DError;	
}

void PID_RemoteControl(void)
{
    float RemoteControlL_PError;
    float RemoteControlL_IError;
    float RemoteControlL_DError;
    float RemoteControlL_LastError;
		
    float RemoteControlR_PError;
    float RemoteControlR_IError;
    float RemoteControlR_DError;
    float RemoteControlR_LastError;

    RemoteControlL_EXP *= (1 - RemoteControlInc_Kp);
    RemoteControlL_EXP += RemoteLeft_EXP * RemoteControlInc_Kp;
			
		
    RemoteControlR_EXP *= (1 - RemoteControlInc_Kp);
    RemoteControlR_EXP += RemoteRight_EXP * RemoteControlInc_Kp;

		
    RemoteControlL_PError = RemoteControlL_EXP - Speed_LeftMotor;
    RemoteControlL_IError += RemoteControlL_PError;
    RemoteControlL_DError = RemoteControlL_PError - RemoteControlL_LastError;
    RemoteControlL_LastError = RemoteControlL_PError;
    RemoteControlL_PID = RemoteControl_Kp * RemoteControlL_PError + RemoteControl_Ki * RemoteControlL_IError + RemoteControl_Kd * RemoteControlL_DError;
	  
    RemoteControlR_PError = RemoteControlR_EXP - Speed_RightMotor;
    RemoteControlR_IError += RemoteControlR_PError;
    RemoteControlR_DError = RemoteControlR_PError - RemoteControlR_LastError;		
    RemoteControlR_LastError = RemoteControlR_PError;	
    RemoteControlR_PID = RemoteControl_Kp * RemoteControlR_PError + RemoteControl_Ki * RemoteControlR_IError + RemoteControl_Kd * RemoteControlR_DError;	
	
	

}


#include "Dance.h"
#include "Remote_Control.h"
#include "common.h"
#include "Station_Handler.h"
#include "RFID.h"
#include "PID_Calculation.h"
#include "MagneticNavigation.h"
#include "LCD.h"
#include "Remote_Control.h"
#include "VoiceHandler.h"

u8 u8Dance_LeftTurning_Flag = 0;
u16 u16_Dance_LeftTurning_Time = 0;
u8 u8DanceCount;

float d_SpeedLeft_EXP = 0;
float d_SpeedRight_EXP = 0;

void DStop(u16 u16TimeCnt)
{
		//Stop
		RemoteLeft_EXP = 0;
		RemoteRight_EXP	= 0;		
		delay_ms(u16TimeCnt);
}

void DForward(u16 u16TimeCnt)
{		
		//Forward
		RemoteLeft_EXP = 30;
		RemoteRight_EXP	= 30;		
		delay_ms(u16TimeCnt);	
		
		RemoteLeft_EXP = 0;
		RemoteRight_EXP	= 0;	
		delay_ms(200);	
}

void DBackward(u16 u16TimeCnt)
{		
		//Backward
		RemoteLeft_EXP = -30;
		RemoteRight_EXP	= -30;		
		delay_ms(u16TimeCnt);	
		
		RemoteLeft_EXP = 0;
		RemoteRight_EXP	= 0;	
		delay_ms(200);	
}


void DLeft(u16 u16TimeCnt)
{
		//Left
		RemoteLeft_EXP = -30;
		RemoteRight_EXP	= 30;		
		delay_ms(u16TimeCnt);
		RemoteLeft_EXP = 0;
		RemoteRight_EXP	= 0;	
		delay_ms(200);	
}

void DRight(u16 u16TimeCnt)
{
		//Right
		RemoteLeft_EXP = 30;
		RemoteRight_EXP	= -30;		
		delay_ms(u16TimeCnt);
		RemoteLeft_EXP = 0;
		RemoteRight_EXP	= 0;	
		delay_ms(200);	
}

void Dance_Without_MegneticNavi(void)
{
		u16 u16TimeCnt;
	
		if (RunningMode == DANCE_MODE && u8Playing == 1)
		{					
			u8DanceCount++;
			while (u16TimeCnt < 1)
			{
					DForward(1000);	 //1.2
					DBackward(1000); //1.2
					
					DLeft(1000);	//1.2
					DRight(1000);	//1.2
					
					DRight(1000);	//1.2				
					DLeft(1000);	//1.2
					
					DBackward(1000); //1.2
					DForward(1000);  //1.2
					
					DLeft(5000);  //5.2
					DRight(5000); //5.2
					
						
					DForward(1000);  //1.2
					DBackward(1000); //1.2
					
					DLeft(1000);	//1.2
					DRight(1000);	//1.2				
					
					
					DRight(1000);	//1.2
					DLeft(1000);	//1.2
					
					DBackward(1000); //1.2
					DForward(1000);	 //1.2
					
					DStop(2000);
					u16TimeCnt++;    
			}
			
			u8Playing = 0;
	}
}

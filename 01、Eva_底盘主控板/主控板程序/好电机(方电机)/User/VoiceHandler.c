#include "VoiceHandler.h"
#include "Speaker.h"
#include "Filtering_Algorithm.h"
#include "IrDA.h"
#include "common.h"
#include "Station_Handler.h"
#include "RFID.h"
#include "FoodMenue.h"
#include "LCD.h"
#include "stm32f4xx_it.h"
#include "Dance.h"
#include "Remote_Control.h"
#include "USART.h"
#include "UART_Protocol.h"

__IO u8 u8OutOfRoad;
__IO u8 u8PlayEn;
__IO u8 u8PlayDone;
__IO u8 u8PlayFolderNum;
__IO u8 u8PlayVolume;
__IO u8 u8PlayResult;
__IO u16 u16PlayTimes;
__IO u16 u16PlayInterval;
__IO u16 u16PlayTimeOut;



__IO u8 u8Playing;
__IO u8 u8Direction_Last;
__IO u8 u8Block;
__IO u8 u8Turning;

u16 u16DelayTable[] = {7000, 5000, 5000, 5000, 6000};  //folder 20, 21, 22
u16 u16DelayForRemoteTable[] = {4500, 5500}; //folder 30, 31
void VoiceHandler(void)
{
	//static u8 count = 0;//, u8Remote_count = 0;
			
		if (RunningMode == WELCOME_CUSTOMR_MODE)
		{		
					
				if (Remote_Flag == 0 && u8Obstacle == 1)
				{
						 IrDA_Trigger_Voice();
						 Send_Data(UART5, u8SendBuff, CMD_LEN);												
				}									
				else if (u8Remote_Voice1 == 1)
				{
						u8Remote_Voice1 = DISABLE;										
						
						Music_Play_Slection(REMOTE_VOICE1_FOLDER, PLAYVOLUME);						
				}
				else if (u8Remote_Voice1 == ENABLE)
				{
						u8Remote_Voice1 = DISABLE;										
						
						Music_Play_Slection(REMOTE_VOICE1_FOLDER, PLAYVOLUME);						
				}
				else if (u8Remote_Voice2 == ENABLE)
				{
						u8Remote_Voice2 = DISABLE;										
						
						Music_Play_Slection(REMOTE_VOICE2_FOLDER, PLAYVOLUME);						
				}
				else if (u8Remote_Voice3 == ENABLE)
				{
						u8Remote_Voice3 = DISABLE;										
						
						Music_Play_Slection(REMOTE_VOICE3_FOLDER, PLAYVOLUME);						
				}
				else if (u8Remote_Voice4 == ENABLE)
				{
						u8Remote_Voice4 = DISABLE;										
						
						Music_Play_Slection(REMOTE_VOICE4_FOLDER, PLAYVOLUME);						
				}
				else if (u8Remote_Voice5 == ENABLE)
				{
						u8Remote_Voice5 = DISABLE;										
						
						Music_Play_Slection(REMOTE_VOICE5_FOLDER, PLAYVOLUME);						
				}
				else if (Remote_Flag == 1)
				{				
						u8PlayFolderNum = PURE_MUSIC1;
						u8PlayVolume = PLAYVOLUME;
						u16PlayTimes = 1;
						u16PlayInterval = 100;
						u16PlayTimeOut	= 30000;							
						u8PlayEn = ENABLE;			
				}					
		}
		else if (RunningMode == DANCE_MODE)
		{			
				u8PlayFolderNum = MUSIC_BASE_FOLDER + u8DanceCount % 5;
				u8PlayVolume = PLAYMUSIC_VOLUME;
				u16PlayTimes = 1;
				u16PlayInterval = 100;
				u16PlayTimeOut	= 0;							
				u8PlayEn = ENABLE;	
				
				u8Playing = 1;
		}
		else if (RunningMode == DILIEVRY_MEALS_MDOE)
		{
			if ( u16OutOfRoadCnt > 3000 && 
					 LeftTurning_Flag == 0 && 
					 RightTurning_Flag == 0 && 
					 LCD_Start_Flag == ENABLE &&
					 TurnBack_Flag == 0 
					)  // out of road
			{
					u8PlayFolderNum = OUTOFROAD_FOLDER;
					u8PlayVolume = PLAYVOLUME;
					u16PlayTimes = 1;
					u16PlayInterval = 100;
					u16PlayTimeOut	= 4000;							
					u8PlayEn = ENABLE;
					
					u8OutOfRoad = 1;
			} 
			else if (Direction != 0 && u8OutOfRoad == 1)  // back on road
			{				
					u8PlayFolderNum = THANKYOU_FOLDER;
					u8PlayVolume = PLAYVOLUME;
					u16PlayTimes = 1;
					u16PlayInterval = 100;
					u16PlayTimeOut	= 2000;							
					u8PlayEn = ENABLE;
					
					u8OutOfRoad = 0;
			}
			else if (u8Obstacle == 1 && 
			         LeftTurning_Flag == 0 && RightTurning_Flag == 0 &&
							 LCD_Start_Flag == ENABLE && 
							 TurnBack_Flag == 0							 
							 )  //block
			{
				if (RunningMode == DILIEVRY_MEALS_MDOE)
				{
						delay_ms(1000);
				}					
					
					if (u8Obstacle == 1)
					{
						u8PlayFolderNum = BLOCK_FOLDER;
						u8PlayVolume = PLAYVOLUME;
						u16PlayTimes = 1;
						u16PlayInterval = 100;
						u16PlayTimeOut	= 6000;							
						u8PlayEn = ENABLE;					
						
						u8Block = 1;												
					}
			}
			else if (u8Obstacle == 0 && u8Block == 1)  //no block
			{
					u8PlayFolderNum = THANKYOU_FOLDER;
					u8PlayVolume = PLAYVOLUME;
					u16PlayTimes = 1;
					u16PlayInterval = 100;
					u16PlayTimeOut	= 2000;							
					u8PlayEn = ENABLE;					
					
					u8Block = 0;	
			}		
			else if (LeftTurning_Flag == 2 || RightTurning_Flag == 2)  
			{
					u8PlayFolderNum = YOUR_FOOD_COME_FOLDER;
					u8PlayVolume = PLAYVOLUME;
					u16PlayTimes = 1;
					u16PlayInterval = 100;
					u16PlayTimeOut	= 2000;							
					u8PlayEn = ENABLE;
					
					u8Turning = 0;
			}
			else if (LeftTurning_Flag == 3 || RightTurning_Flag == 3) 
			{
					u8PlayFolderNum = ENJOY_YOUR_FOOD_FOLDER;
					u8PlayVolume = PLAYVOLUME;
					u16PlayTimes = 1;
					u16PlayInterval = 100;
					u16PlayTimeOut	= 5000;							
					u8PlayEn = ENABLE;			
			}		
			else
			{
			}

		}
			

		
		
			if (u8PlayEn == ENABLE)
				{
						u8PlayEn = DISABLE;				
						{
							
										u8PlayResult = Music_Play_Set(u8PlayFolderNum, u8PlayVolume, u16PlayTimes, u16PlayInterval, u16PlayTimeOut);							
						}						
				}		
			
}


#include "Speaker.h"
#include "USART.h"
#include "common.h"

u8 u8MusicPlayCmd[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
u8 u8MusicPlayChkCmd[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};

u8 u8ResposeBuf[7];
u8 u8PlayStatus;
u8 u8ReceiveCnt;

u8 u8Exit;

/**
  * @brief  music selection and volume adjustment.
  * @param  u8FolderNumber: music folder number between 1 to 255(0 means stop palying) , 
	* @param  u8Volume: music volume adjustment between 0 to 28 
  * @retval None
  */
	
void Music_Play_Slection(u8 u8FolderNumber, s8 u8Volume)
{
	u8 i, xor_dat = 0;		
		
		//set command
		u8MusicPlayCmd[MUSIC_CMD] = MUSIC_PLAY_CMD;
		
		//set volume
		if (u8Volume >= 0 && u8Volume <= 28)
		{
				u8MusicPlayCmd[MUSIC_VOL] = u8Volume;
		}
		else
		{
				return;
		}
		
		//select folder for music
		u8MusicPlayCmd[MUSIC_FOL] = u8FolderNumber;				
		
		
		//calculate checksum
		for (i = 0; i < 5; i++)
		{
				xor_dat ^= u8MusicPlayCmd[i];
		}
		
		u8MusicPlayCmd[MUSIC_XOR] = xor_dat;
		
		
		//send the comand frame 
		Send_SpeakerData(u8MusicPlayCmd, ARR_COUNT(u8MusicPlayCmd));
}

/**
  * @brief  music paly status check command 
  * @param  None
  * @retval None
  */
void Music_PlayDone_Check(void)
{
		u8 i, xor_dat = 0;	
			
		//set command
		u8MusicPlayChkCmd[MUSIC_CMD] = MUSIC_PLAY_CHK_CMD;
		
		//calculate checksum
		for (i = 0; i < 5; i++)
		{
				xor_dat ^= u8MusicPlayChkCmd[i];
		}
		
		u8MusicPlayChkCmd[MUSIC_XOR] = xor_dat;
		
		//send the comand frame 
		Send_SpeakerData(u8MusicPlayChkCmd, ARR_COUNT(u8MusicPlayChkCmd));
}

/**
  * @brief  music paly times set
  * @param  u8FolderNumber: music folder number between 1 to 255(0 means stop palying) , 
	
	* @param  u8Volume: music volume adjustment between 0 to 28 
	* @param  u16Interval: interval time between multiple music playing in millseconds
	* @param  u16TimeOut: set timeout for playing music in millseconds
  * @retval ERROR or SUCCESS: the result of music playing
  */

u8 Music_Play_Set(u8 u8FolderNumber, s8 u8Volume, u16 u16Times, u16 u16Interval, u16 u16TimeOut)
{		
		u8 u8Status = 0xFF;
		
		u16 u16DelayCnt;
		u16 u16DelayTimes = u16TimeOut / TIMEOUT_CHECK_INTERVAL;
		u16 u16PlayCnt;		
		
		for (u16PlayCnt = 0; u16PlayCnt < u16Times; u16PlayCnt++)
		{			
				u16DelayCnt = 0;
				if (u16Interval < 100) u16Interval = 100;				 
				delay_ms(u16Interval);	//insert interval between multiple playing	
				Music_Play_Slection(u8FolderNumber, u8Volume);				
				delay_ms(15);								//after response frame of music playing
				
				u8Exit = 0;
				
				while (u8PlayStatus != MUSIC_STOP && u8Exit == 0)
				{
						delay_ms(TIMEOUT_CHECK_INTERVAL);
						u8ReceiveCnt = 0;
						
						Music_PlayDone_Check();
						
						u16DelayCnt++;
						
						if (u16DelayCnt > u16DelayTimes) 
						{						
								break;				
						}
				}
				
				if (u8PlayStatus == MUSIC_STOP)
				{
						u8Status = SUCCESS;			
				}
				else
				{
						u8Status = ERROR;
						goto RET;
				}				
		}		

RET:		
		return u8Status;		
}



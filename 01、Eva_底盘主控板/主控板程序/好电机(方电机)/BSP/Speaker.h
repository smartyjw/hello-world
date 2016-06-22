#ifndef __SPEAKER_H__
#define __SPEAKER_H__
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
/* Exported types ------------------------------------------------------------*/
extern u8 u8ResposeBuf[];
extern u8 u8PlayStatus;
extern u8 u8ReceiveCnt;
extern u8 u8Exit;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define TIMEOUT_CHECK_INTERVAL (200)
#define MUSIC_PLAY_CMD			 (0x51)
#define MUSIC_PLAY_CHK_CMD 	 (0x53)
#define MUSIC_DATLEN (7)

#define MUSIC_CMD (1)
#define MUSIC_FOL (2)
#define MUSIC_VOL (4)
#define MUSIC_XOR (5)

#define MUSIC_STATUS 	(4)
#define MUSIC_PALYING (1)
#define MUSIC_STOP    (2)
/* Exported functions ------------------------------------------------------- */
void Music_Play_Slection(u8 u8FolderNumber, s8 u8Volume);
void Music_PlayDone_Check(void);
u8 Music_Play_Set(u8 u8FolderNumber, s8 u8Volume, u16 u16Times, u16 u16Interval, u16 u16TimeOut);
#endif  

#ifndef __VOICEHANDLER_H__
#define __VOICEHANDLER_H__
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
extern __IO u8 u8Playing;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/*
#define OUTOFROAD_FOLDER (1)
#define ONROAD_FOLDER		 (2)
#define DELIVERY_MEALS_BLOCK_FOLDER (3)
#define RETURN_BLOCK_FOLDER	   (4)
#define ENJOY_YOUR_FOOD				 (5)
#define THAKS_BYEBYE_FOLDER		 (6)
#define WELCOME_FOLDER				 (7)
#define DEAR_CUSTOMER_BASE_FOLDER (10)
#define DINNER_BASE_FOLDER  			 (100)
*/
#define OUTOFROAD_FOLDER 				 (1)
#define THANKYOU_FOLDER	 				 (2)
#define BLOCK_FOLDER		 				 (3)
#define ENJOY_YOUR_FOOD_FOLDER	 (4)
#define YOUR_FOOD_COME_FOLDER 	 (5)
#define PURE_MUSIC1						   (6)

/* Floder:11 ~ 15 for dance */
#define MUSIC_BASE_FOLDER				     (11)

/* Folder:20 ~ 24 for iRda*/
#define WELCOME_BASE_FOLDER 		 (20)

/* Folder 31 ~ 35 for remote voice */
#define REMOTE_VOICE1_FOLDER 			(31)
#define REMOTE_VOICE2_FOLDER 			(32)
#define REMOTE_VOICE3_FOLDER 			(33)
#define REMOTE_VOICE4_FOLDER 			(34)
#define REMOTE_VOICE5_FOLDER 			(35)

#if 0
	#define PLAYVOLUME 			 				 (2) //(26)
	#define PLAYMUSIC_VOLUME				 (2) //(25) 
#else
	#define PLAYVOLUME 			 				 (26)
	#define PLAYMUSIC_VOLUME				 (25)
#endif
/* Exported functions ------------------------------------------------------- */
void VoiceHandler(void);
#endif

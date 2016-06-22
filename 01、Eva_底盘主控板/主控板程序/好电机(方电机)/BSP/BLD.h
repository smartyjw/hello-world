#ifndef __BLD_H__
#define __BLD_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
/* Exported types ------------------------------------------------------------*/
typedef enum {FORWARD = 0, BACKWARD = !FORWARD} FBDIR;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

//PF0
#define ENL_GPIO_RCC  		  RCC_AHB1Periph_GPIOF
#define ENL_GPIO_TYPE 	 	  GPIOF
#define ENL_GPIO_PIN    	  GPIO_Pin_0
#define ENL_SET()						GPIO_SetBits(ENL_GPIO_TYPE, ENL_GPIO_PIN) 
#define ENL_CLR() 			    GPIO_ResetBits(ENL_GPIO_TYPE, ENL_GPIO_PIN)  

//PF2
#define FRL_GPIO_RCC  		  RCC_AHB1Periph_GPIOF
#define FRL_GPIO_TYPE 	 	  GPIOF
#define FRL_GPIO_PIN    	  GPIO_Pin_2
#define FRL_SET()					  GPIO_ResetBits(FRL_GPIO_TYPE, FRL_GPIO_PIN) 
#define FRL_CLR() 			    GPIO_SetBits(FRL_GPIO_TYPE, FRL_GPIO_PIN)

//PF4
#define BRKL_GPIO_RCC  		 RCC_AHB1Periph_GPIOF
#define BRKL_GPIO_TYPE 	 	 GPIOF
#define BRKL_GPIO_PIN    	 GPIO_Pin_4
#define BRKL_SET()				 GPIO_SetBits(BRKL_GPIO_TYPE, BRKL_GPIO_PIN) 
#define BRKL_CLR() 			   GPIO_ResetBits(BRKL_GPIO_TYPE, BRKL_GPIO_PIN) 

//PF1
#define ENR_GPIO_RCC  		  RCC_AHB1Periph_GPIOF
#define ENR_GPIO_TYPE 	 	  GPIOF
#define ENR_GPIO_PIN    	  GPIO_Pin_1
#define ENR_SET()						GPIO_SetBits(ENR_GPIO_TYPE, ENR_GPIO_PIN) 
#define ENR_CLR() 			    GPIO_ResetBits(ENR_GPIO_TYPE, ENR_GPIO_PIN) 

//PF3
#define FRR_GPIO_RCC  		  RCC_AHB1Periph_GPIOF
#define FRR_GPIO_TYPE 	 	  GPIOF
#define FRR_GPIO_PIN    	  GPIO_Pin_3
#define FRR_SET()					  GPIO_ResetBits(FRR_GPIO_TYPE, FRR_GPIO_PIN) 
#define FRR_CLR() 			    GPIO_SetBits(FRR_GPIO_TYPE, FRR_GPIO_PIN)

//PF5
#define BRKR_GPIO_RCC  		 RCC_AHB1Periph_GPIOF
#define BRKR_GPIO_TYPE 	 	 GPIOF
#define BRKR_GPIO_PIN    	 GPIO_Pin_5
#define BRKR_SET()				 GPIO_SetBits(BRKR_GPIO_TYPE, BRKR_GPIO_PIN) 
#define BRKR_CLR() 			   GPIO_ResetBits(BRKR_GPIO_TYPE, BRKR_GPIO_PIN) 

/* Exported functions ------------------------------------------------------------*/
void GPIO_BLD_Configruration(void);
void FR_Set(uint8_t u8Dir);
void EN_Set(uint8_t u8En);
void BRK_Set(uint8_t u8En);
void BLD_Ctrl_L(uint8_t u8DriEn, uint8_t u8Dir, uint8_t u8BkEn);
void BLD_Ctrl_R(uint8_t u8DriEn, uint8_t u8Dir, uint8_t u8BkEn);

#endif


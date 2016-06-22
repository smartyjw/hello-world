#ifndef __IRDA_H__
#define __IRDA_H__
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_gpio.h"
/* Exported types ------------------------------------------------------------*/
extern u8 u8Obstacle;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define IRDA12_GPIO_RCC  	   RCC_AHB1Periph_GPIOF
#define IRDA12_GPIO_TYPE     GPIOF
#define IRDA1_GPIO_PIN	   	 GPIO_Pin_8
#define IRDA2_GPIO_PIN	   	 GPIO_Pin_9

#define IRDA34_GPIO_RCC  	   RCC_AHB1Periph_GPIOB
#define IRDA34_GPIO_TYPE     GPIOB
#define IRDA3_GPIO_PIN	     GPIO_Pin_0
#define IRDA4_GPIO_PIN	     GPIO_Pin_1

#define GetIRDA1Status()   GPIO_ReadInputDataBit(IRDA12_GPIO_TYPE, IRDA1_GPIO_PIN)
#define GetIRDA2Status()   GPIO_ReadInputDataBit(IRDA12_GPIO_TYPE, IRDA2_GPIO_PIN)
#define GetIRDA3Status()   GPIO_ReadInputDataBit(IRDA34_GPIO_TYPE, IRDA3_GPIO_PIN)
#define GetIRDA4Status()   GPIO_ReadInputDataBit(IRDA34_GPIO_TYPE, IRDA4_GPIO_PIN)


#define Tableware_GPIO_RCC  RCC_AHB1Periph_GPIOF
#define Tableware_GPIO_TYPE GPIOF
#define Tableware1_GPIO_PIN GPIO_Pin_6
#define Tableware2_GPIO_PIN GPIO_Pin_7

#define GetTableware1Status() GPIO_ReadInputDataBit(Tableware_GPIO_TYPE, Tableware1_GPIO_PIN)
#define GetTableware2Status() GPIO_ReadInputDataBit(Tableware_GPIO_TYPE, Tableware2_GPIO_PIN)

#if 0
		#define ExistFood()	((GetTableware1Status() == 0) || (GetTableware2Status() == 0))
		#define NoFood()		((GetTableware1Status() == 1) && (GetTableware2Status() == 1))
#else
		#define ExistFood()	((GetTableware2Status() == 0))
		#define NoFood()		((GetTableware2Status() == 1))
#endif

/* Exported functions ------------------------------------------------------- */
void GPIO_IrDA_Configuration(void);
u8 IrDA1_Check(void);
u8 IrDA2_Check(void);
u8 IrDA3_Check(void);
u8 IrDA4_Check(void);
u8 TableWare1_Check(void);
u8 TableWare2_Check(void);
void Obstacle_Check(void);
#endif


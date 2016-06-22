#ifndef __PWM_H__
#define __PWM_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

/* Exported macro ------------------------------------------------------------*/
#define DUTY_MIN (0)
#define DUTY_MAX (100)
#define MOTOR_TIM_RCC          RCC_APB1Periph_TIM2
#define MOTOR_TIM_TYPE         TIM2
//#define MOTOR_TIM_PERIOD       (100)
#define MOTOR_TIM_PRESCALER    (84 - 1) 
#define MOTOR_PWML_DUTY(DUTY_VAL)   TIM_SetCompare3(MOTOR_TIM_TYPE, DUTY_VAL * u16Current_TIM_Period / 100) 
#define MOTOR_PWMR_DUTY(DUTY_VAL)   TIM_SetCompare4(MOTOR_TIM_TYPE, DUTY_VAL * u16Current_TIM_Period / 100)


#define GPIO_AF_TIM	GPIO_AF_TIM2			

//PB10
#define PWML_GPIO_RCC  	    RCC_AHB1Periph_GPIOB
#define PWML_GPIO_TYPE   	  GPIOB
#define PWML_GPIO_PIN       GPIO_Pin_10	
#define PWML_GPIO_PINSRC    GPIO_PinSource10


//PB11
#define PWMR_GPIO_RCC  	    RCC_AHB1Periph_GPIOB
#define PWMR_GPIO_TYPE 	    GPIOB
#define PWMR_GPIO_PIN       GPIO_Pin_11
#define PWMR_GPIO_PINSRC		GPIO_PinSource11

/* Exported types ------------------------------------------------------------*/
extern u16 u16Current_TIM_Period;
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void PWM_Configuration(u16 u16KHz);
void PWM_Duty_Set(uint16_t left_duty, uint16_t right_duty);
#endif

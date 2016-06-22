#include "PWM.h"
#include "stm32f4xx_tim.h"

/**
  * @brief  pwm output configuration.
  * @param  u16KHz: output frequency in KHz and frequency between 1 to 1000 KHz
  * @retval None
  */

u16 u16Current_TIM_Period;

void PWM_Configuration(u16 u16KHz)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure; 	
		
		//PWML
		RCC_AHB1PeriphClockCmd(PWML_GPIO_RCC, ENABLE);  
		GPIO_PinAFConfig(PWML_GPIO_TYPE, PWML_GPIO_PINSRC, GPIO_AF_TIM);  	
		
		GPIO_InitStructure.GPIO_Pin = PWML_GPIO_PIN; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(PWML_GPIO_TYPE, &GPIO_InitStructure);
			
		//PWMR
		RCC_AHB1PeriphClockCmd(PWMR_GPIO_RCC, ENABLE);  		
		GPIO_PinAFConfig(PWMR_GPIO_TYPE, PWMR_GPIO_PINSRC, GPIO_AF_TIM);
	
		
		GPIO_InitStructure.GPIO_Pin = PWMR_GPIO_PIN; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(PWMR_GPIO_TYPE, &GPIO_InitStructure);
		
		//initial TIM3 for motor1 & motor2
		RCC_APB1PeriphClockCmd(MOTOR_TIM_RCC, ENABLE);//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
		TIM_TimeBaseStructure.TIM_Period = 1000 / u16KHz;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值		
		TIM_TimeBaseStructure.TIM_Prescaler = MOTOR_TIM_PRESCALER; //设置用来作为TIMx时钟频率除数的预分频值  不分频
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseInit(MOTOR_TIM_TYPE, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
		u16Current_TIM_Period = TIM_TimeBaseStructure.TIM_Period;
		/*****初始化所有通道*****/ 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
		
		TIM_OC3Init(MOTOR_TIM_TYPE, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
		TIM_OC4Init(MOTOR_TIM_TYPE, &TIM_OCInitStructure);	

		TIM_OC3PreloadConfig(MOTOR_TIM_TYPE, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
		TIM_OC4PreloadConfig(MOTOR_TIM_TYPE, TIM_OCPreload_Enable);
	
		TIM_ARRPreloadConfig(MOTOR_TIM_TYPE, ENABLE); //使能TIMx在ARR上的预装载寄存器	
 
		TIM_Cmd(MOTOR_TIM_TYPE, ENABLE);  //使能TIMx外设
}

void Motor_PWM_Duty_Set(uint16_t left_duty, uint16_t right_duty)
{
		MOTOR_PWML_DUTY(left_duty);
		MOTOR_PWMR_DUTY(right_duty);
}

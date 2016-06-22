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
		RCC_APB1PeriphClockCmd(MOTOR_TIM_RCC, ENABLE);//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
		TIM_TimeBaseStructure.TIM_Period = 1000 / u16KHz;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ		
		TIM_TimeBaseStructure.TIM_Prescaler = MOTOR_TIM_PRESCALER; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseInit(MOTOR_TIM_TYPE, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
		u16Current_TIM_Period = TIM_TimeBaseStructure.TIM_Period;
		/*****��ʼ������ͨ��*****/ 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
		
		TIM_OC3Init(MOTOR_TIM_TYPE, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
		TIM_OC4Init(MOTOR_TIM_TYPE, &TIM_OCInitStructure);	

		TIM_OC3PreloadConfig(MOTOR_TIM_TYPE, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
		TIM_OC4PreloadConfig(MOTOR_TIM_TYPE, TIM_OCPreload_Enable);
	
		TIM_ARRPreloadConfig(MOTOR_TIM_TYPE, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���	
 
		TIM_Cmd(MOTOR_TIM_TYPE, ENABLE);  //ʹ��TIMx����
}

void Motor_PWM_Duty_Set(uint16_t left_duty, uint16_t right_duty)
{
		MOTOR_PWML_DUTY(left_duty);
		MOTOR_PWMR_DUTY(right_duty);
}

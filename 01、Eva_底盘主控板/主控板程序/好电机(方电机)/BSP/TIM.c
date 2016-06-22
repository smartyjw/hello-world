#include "TIM.h"
#include "stm32f4xx.h"
//#include "stm32f10x_type.h"

void SpeedExtraction_Configuration(void)
{
/*                             Left_M                         */
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_ICInitTypeDef TIM_ICInitStructure;
  
		/* Encoder unit connected to TIM3 */    
		GPIO_InitTypeDef GPIO_InitStructure;

	
		/* Enable GPIOA, clock */
		RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
		
		GPIO_StructInit(&GPIO_InitStructure);		
		
		/* Configure PA.06,07 as encoder input */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
  
		/* Timer configuration in Encoder mode */		
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		
		TIM_DeInit(ENCODER_TIMER_L);
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
		TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
		TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_PPR)-1;  
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
		TIM_TimeBaseInit(ENCODER_TIMER_L, &TIM_TimeBaseStructure);
 
		TIM_EncoderInterfaceConfig(ENCODER_TIMER_L, TIM_EncoderMode_TI12, 
    TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
		TIM_ICStructInit(&TIM_ICInitStructure);
		TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
		TIM_ICInit(ENCODER_TIMER_L, &TIM_ICInitStructure);
  
		ENCODER_TIMER_L->CNT = COUNTER_RESET;
  
		TIM_Cmd(ENCODER_TIMER_L, ENABLE);

/*                                Right_M                                    */

		
			
		/* Enable GPIOA, clock */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM3);
		
		GPIO_StructInit(&GPIO_InitStructure);
		/* Configure PA.00,01 as encoder input */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOA, &GPIO_InitStructure);  	
		
		/* Timer configuration in Encoder mode */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		
		TIM_DeInit(ENCODER_TIMER_R);
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
		TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
		TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_PPR)-1;  
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
		TIM_TimeBaseInit(ENCODER_TIMER_R, &TIM_TimeBaseStructure);
 
		TIM_EncoderInterfaceConfig(ENCODER_TIMER_R, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
		TIM_ICStructInit(&TIM_ICInitStructure);
		TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
		TIM_ICInit(ENCODER_TIMER_R, &TIM_ICInitStructure);  
 
		//Reset counter
		ENCODER_TIMER_R->CNT = COUNTER_RESET;
  
		TIM_Cmd(ENCODER_TIMER_R, ENABLE);
		
		
		
	  /* configure TIM1 as ETR, PA12*/
		/* TIM1 clock enable */		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_TIM1);
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;					
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
		TIM_DeInit(TIM1);   
		TIM_TimeBaseStructure.TIM_Period = 30000;   
		TIM_TimeBaseStructure.TIM_Prescaler = 0;   
		TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;     
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
		TIM_ETRClockMode2Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
		TIM_SetCounter(TIM1, 0);  
		TIM1->SMCR |= TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0;
		TIM_Cmd(TIM1, ENABLE);   

		/* configure TIM4 as ETR, PE0*/
	  /* TIM4 clock enable */
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);			
	  GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_TIM4);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOE, &GPIO_InitStructure);		

		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 		
		TIM_DeInit(TIM4);   
		TIM_TimeBaseStructure.TIM_Period = 30000;   
		TIM_TimeBaseStructure.TIM_Prescaler = 0x00;   
		TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;     
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
		TIM_ETRClockMode2Config(TIM4, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
		TIM_SetCounter(TIM4, 0);  
		TIM4->SMCR |= TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0;		
		TIM_Cmd(TIM4, ENABLE);  	

}

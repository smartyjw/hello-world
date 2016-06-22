#include "test.h"
#include "common.h"
#include "pwm.h"
#include "Speaker.h"
#include "LED.h"
#include "LCD.h"
#include "BLD.h"
#include "IrDA.h"
#include "common.h"
#include "tim.h"

/* used to test PWM output*/
u16 u16PWM_Freq;
u8 u8PWM_FREQ_UPEN;
u8 u8PWM_Duty_L, u8PWM_Duty_R;

/* used to test music player*/

SPEAKER_TEST_TypeDef Speaker_Test_Structure = {DISABLE, 3, 20, 3, 100, 5000, 0};

/* used to test pusles*/
u32 u32TempL,u32TempR;
/* used to test BLD control IO */
u8 u8DriverEn, u8Direction, u8BreakEn;
u8 u8CtrlSigL_UpEn, u8CtrlSigR_UpEn;

/* used to test IrDA IO*/
u8 u8IrDA1Status, u8IrDA2Status, u8IrDA3Status, u8IrDA4Status;
u8 u8TableWareStatus1, u8TableWareStatus2;

RCC_ClocksTypeDef RCC_ClocksStructure;

void GetClocksFreq_Test(void)
{
		RCC_GetClocksFreq(&RCC_ClocksStructure);	
}

void LED_Test(void)
{
		LED_Toggle();
}

void BLD_IO_Test(void)
{
		if (u8CtrlSigL_UpEn == ENABLE)
		{	
				u8CtrlSigL_UpEn = DISABLE;
				BLD_Ctrl_L(u8DriverEn, u8Direction, u8BreakEn);
		}
		
		if (u8CtrlSigR_UpEn == ENABLE)
		{	
				u8CtrlSigR_UpEn = DISABLE;
				BLD_Ctrl_R(u8DriverEn, u8Direction, u8BreakEn);
		}
}

void PWM_Configuration_Test(void)
{
		/* PWM Configuration */
		if (u8PWM_FREQ_UPEN == ENABLE)
		{
				u8PWM_FREQ_UPEN = DISABLE;
				PWM_Configuration(u16PWM_Freq);
				MOTOR_PWML_DUTY(u8PWM_Duty_L);
				MOTOR_PWMR_DUTY(u8PWM_Duty_R);
		}	
		else
		{
				MOTOR_PWML_DUTY(20);
				MOTOR_PWMR_DUTY(20);
		}
}

void Forward(void)
{
		BLD_Ctrl_L(ENABLE, FORWARD, DISABLE);
		BLD_Ctrl_R(ENABLE, FORWARD, DISABLE);
		MOTOR_PWML_DUTY(100);
		MOTOR_PWMR_DUTY(100);
}

void Back(void)
{
		BLD_Ctrl_L(ENABLE, BACKWARD, DISABLE);
		BLD_Ctrl_R(ENABLE, BACKWARD, DISABLE);
		MOTOR_PWML_DUTY(100);
		MOTOR_PWMR_DUTY(100);
}

void StopL(void)
{
		BLD_Ctrl_L(ENABLE, FORWARD, ENABLE);		
}

void StopR(void)
{
		BLD_Ctrl_R(ENABLE, FORWARD, ENABLE);
}


void Music_Play_Times_Test(u16 u16Times, u16 u16IntervalTime, u16 u16TimeOut)
{

		if (Speaker_Test_Structure.u8MusicPlayEn == ENABLE) 
		{
				Speaker_Test_Structure.u8MusicPlayEn = DISABLE;				
				Speaker_Test_Structure.u8MusicPlayingResult = Music_Play_Set(Speaker_Test_Structure.u8FloderNum, 
																																		 Speaker_Test_Structure.u8Volume, 
																																		 Speaker_Test_Structure.u16Times, 
																																		 Speaker_Test_Structure.u16IntervalTime, 
																																		 Speaker_Test_Structure.u16TimeOut);		
		}
}

void LCD_Disp_Test(void)
{
		LCD_InitialView_Configuration();
}

void LCD_Key_Handler_Test(void)
{
		LcdReceiveJudge();					
}

void IRDA_Test(void)
{	
		u8IrDA1Status = IrDA1_Check();
		u8IrDA2Status = IrDA2_Check();
		u8IrDA3Status = IrDA3_Check();
		u8IrDA4Status = IrDA4_Check();	
		u8TableWareStatus1 = TableWare1_Check();
		u8TableWareStatus2 = TableWare2_Check();
}

void MeasurePuslesPPR(void)
{
		
		
		TIM_SetCounter(TIM4, 0);
		
	//	Forward();
		
		
		while (1)
		{
			
				u32TempL = TIM4->CNT;
				if (u32TempL > 76)
				{
							StopL();						
				}
				
				u32TempR = TIM1->CNT;
				if (u32TempR > 76)
				{
							StopR();						
				}
				
				
				
		}
}

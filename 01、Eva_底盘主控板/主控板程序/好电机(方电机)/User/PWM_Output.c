#include "stm32f4xx.h"
#include "PWM_Output.h"
#include "BLD.h"
#include "PWM.h"

void PWM_Output(int PWM_LeftMotor,int PWM_RightMotor)
{
		if(PWM_LeftMotor < 0)
		{   
			  if(PWM_LeftMotor < -100)
				{
		       PWM_LeftMotor = -100; 
		    }
				if(PWM_LeftMotor > -3)
				{
		       PWM_LeftMotor = -3;
		    }
		    BLD_Ctrl_L(ENABLE, BACKWARD, DISABLE);	
			  PWM_LeftMotor = PWM_LeftMotor * (-1);
        MOTOR_PWML_DUTY(PWM_LeftMotor); 
		}
		else
		{   
			  if(PWM_LeftMotor > 100)
				{
		       PWM_LeftMotor = 100; 
		    }
				if(PWM_LeftMotor < 3) 
				{
		       PWM_LeftMotor = 3; 
		    }
        BLD_Ctrl_L(ENABLE, FORWARD, DISABLE);	
        MOTOR_PWML_DUTY(PWM_LeftMotor);
		}
		
		if(PWM_RightMotor < 0)
		{   
			  if(PWM_RightMotor < -100)
				{
		       PWM_RightMotor = -100; 
		    }
				if(PWM_RightMotor > -3)
				{
		       PWM_RightMotor = -3; 
		    }
			  BLD_Ctrl_R(ENABLE, BACKWARD, DISABLE);	
			  PWM_RightMotor = PWM_RightMotor * (-1);
        MOTOR_PWMR_DUTY(PWM_RightMotor);
		}
		else
		{
			  if(PWM_RightMotor >  100)
				{
		       PWM_RightMotor = 100; 
		    }
				if(PWM_RightMotor < 3)
				{
		       PWM_RightMotor = 3; 
		    }
        BLD_Ctrl_R(ENABLE, FORWARD, DISABLE);
        MOTOR_PWMR_DUTY(PWM_RightMotor);
		} 
}

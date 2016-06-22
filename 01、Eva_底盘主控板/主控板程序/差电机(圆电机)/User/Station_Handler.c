#include "stm32f4xx.h"
#include "Station_Handler.h"
#include "Filtering_Algorithm.h"
#include "PID_Calculation.h"
#include "RFID.h"
#include "IrDA.h"
#include "MagneticNavigation.h"
#include "LCD.h"
//#define THE_FIRST_EVA

u8 LeftTurning_Flag = 0;
u8 RightTurning_Flag = 0;
u8 TurnBack_Flag = 0;


int LeftTurning_Flag1 = 0;
int RightTurning_Flag1 = 0;

int LeftTurning_Angle = 0;
int RightTurning_Angle = 0;
int TurnBack_Angle = 0;

int count = 0;

u8 u8TableWareStatus;

void TurnBack_Deceleration(void)
{
		if (TurnBack_Flag == 0)
		{
				count++;
				if (count > 500)
				{
						Speed_EXP = 0;
						//Speed_Increment = 0;
		        if((Speed_LeftMotor < 5) && (Speed_RightMotor < 5))
		        {
		            TurnBack_Flag = 1;
						    count = 0;
								LCD_Start_Flag = 0;
		        }		   						
				}
		}
}

void TurnBack_Movement(void)
{
		if (TurnBack_Flag == 1)
		{
				SpeedLeft_EXP = - 15;
				SpeedRight_EXP = 15;
				TurnBack_Angle++;				
	      if(TurnBack_Angle > TURNING_TIME)
		    {
			      TurnBack_Angle = 0;
				    TurnBack_Flag = 2;
        }  
		}
		else if (TurnBack_Flag == 2)
		{
				SpeedLeft_EXP =  -15;
				SpeedRight_EXP = 15;
				if((DirectionCL_PError > -1) && (DirectionCL_PError < 1) && (CTData != 0))
				{
							TurnBack_Flag = 3;							
				}
		}
		else if (TurnBack_Flag == 3)
		{
			  TurnBack_Flag = 0;
				Station = 0xFFFF;
				SWTFlag = 0;		
				xrd_cnt3string(700, 80, SWTFlag);//目标站点显示，默认0				
				Speed_Increment = 0;				
		}
}

void LeftTurning_Deceleration(void)
{ 
	  if(LeftTurning_Flag == 0)
		{    
			  count ++;
				if(count > 500)
				{
		        Speed_EXP = 0;
		        if((Speed_LeftMotor < 5) && (Speed_RightMotor < 5))
		        {
		            LeftTurning_Flag = 1;
						    count = 0;
		        }		   
			  }
	  }
}

void LeftTurning_Movement(void)
{
		if(LeftTurning_Flag == 1)
		{
        SpeedLeft_EXP = - 15;
				SpeedRight_EXP = 15;
				LeftTurning_Angle ++;				
	      if(LeftTurning_Angle > TURNING_TIME)
		    {
			      LeftTurning_Angle = 0;
				    LeftTurning_Flag = 2;
        }  
    }
    
		else if(LeftTurning_Flag == 2)
		{
        SpeedLeft_EXP = 0;	
				SpeedRight_EXP = 0;
				//Speed_EXP = 0;
				
				
	
			#ifdef THE_FIRST_EVA
						u8TableWareStatus = (GetTableware1Status() == 0) && (GetTableware2Status() == 0); //L (the first Eva)
			#else		
						u8TableWareStatus = NoFood(); 
			#endif
			
				if(u8TableWareStatus == 1)    
				{
				    LeftTurning_Flag1++;
						if(LeftTurning_Flag1 > WAITING_TIME)
						{
							  LeftTurning_Flag1 = 0;
		            LeftTurning_Flag = 3;
						}
		    }
		}	
		else if (LeftTurning_Flag == 3)
		{
				SpeedLeft_EXP = 0;	
				SpeedRight_EXP = 0;
				count++;
				if (count > 1500)
				{
						count = 0;
						LeftTurning_Flag = 4;
				}
						
   }
	 else if (LeftTurning_Flag == 4)
	 {
				SpeedLeft_EXP =  -15;
				SpeedRight_EXP = 15;
				if((DirectionCL_PError > -1) && (DirectionCL_PError < 1) && (CTData != 0))
		    {
				    LeftTurning_Flag = 5;
        }
		}			
    else if(LeftTurning_Flag == 5)
		{
        LeftTurning_Flag = 0;
				Station = 0xFFFF;
				SWTFlag = 0;
				Speed_EXP = u8SpeedLevel;
				
				Speed_Increment = 0;
	  }		
		else
		{
		    ;;
		}
}

void RightTurning_Deceleration(void)
{ 
	  if(RightTurning_Flag == 0)
		{
			  count++;
				if(count > 500)
				{
		        Speed_EXP = 0;
		        if((Speed_LeftMotor < 5) && (Speed_RightMotor < 5))
		        {
		            RightTurning_Flag = 1;
						    count = 0;
		        }
			  }
	  }
}

void RightTurning_Movement(void)
{
    if(RightTurning_Flag == 1)
		{
        SpeedLeft_EXP = 15;
				SpeedRight_EXP = -15;
				RightTurning_Angle ++;				
	      if(RightTurning_Angle > TURNING_TIME)
		    {
			      RightTurning_Angle = 0;
				    RightTurning_Flag = 2;
        }  
    }
    
		else if(RightTurning_Flag == 2)
		{
        SpeedLeft_EXP = 0;
				SpeedRight_EXP = 0;

			#ifdef THE_FIRST_EVA
						u8TableWareStatus = (GetTableware1Status() == 0) && (GetTableware2Status() == 0); //L (the first Eva)  
			#else		 
						u8TableWareStatus = NoFood();
			#endif
			
				if(u8TableWareStatus == 1)    
				{
					  RightTurning_Flag1++;
						if(RightTurning_Flag1 > WAITING_TIME) 
						{
                RightTurning_Flag1 = 0;							
		            RightTurning_Flag = 3;
						}
		    }
		}	
		else if (RightTurning_Flag == 3)
		{
				SpeedLeft_EXP = 0;	
				SpeedRight_EXP = 0;
				count++;
				if (count > 1500)
				{
						count = 0;
						RightTurning_Flag = 4;
				}
		}
    else if(RightTurning_Flag == 4)
		{
        SpeedLeft_EXP = 15;
				SpeedRight_EXP = -15;
				if((DirectionCL_PError > -1) && (DirectionCL_PError < 1) && (CTData != 0))
		    {
				    RightTurning_Flag = 5;
        }
		}			
    else if(RightTurning_Flag == 5)
		{
        RightTurning_Flag = 0;
				Station = 0xFFFF;
				SWTFlag = 0;  
				Speed_EXP = u8SpeedLevel;
				
				Speed_Increment = 0;
	  }		
		else 
		{
		    ;;
		}
}


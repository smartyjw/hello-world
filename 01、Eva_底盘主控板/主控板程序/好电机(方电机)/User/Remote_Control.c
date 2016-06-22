#include "Remote_Control.h"
#include "PID_Calculation.h"
#include "Speaker.h"
#include "config.h"

DIR_STRUCTURE dir_str;
u8 Remote_Flag = 0;
u8 Remote_Stop = 0;
u8 Remote_Buffer[6] = {0};
u8 u8Remote_Voice1, u8Remote_Voice2, u8Remote_Voice3, u8Remote_Voice4, u8Remote_Voice5;

float Turn_Left = 0;
float Turn_Right = 0;
float Remote_Speed = 0;
float RemoteLeft_EXP = 0;
float RemoteRight_EXP = 0;

void Remote_Recognition(void)  
{   
	  dir_str.dir_forward = DISABLE;
		dir_str.dir_back = DISABLE;

		dir_str.dir_left = DISABLE;
		dir_str.dir_right = DISABLE;

		dir_str.dir_left_forward = DISABLE;
		dir_str.dir_right_forward = DISABLE;

		dir_str.dir_left_back = DISABLE;
		dir_str.dir_right_back = DISABLE;

		dir_str.dir_up = DISABLE;
		dir_str.dir_down = DISABLE;
		
		dir_str.dir_xia = DISABLE;
		dir_str.dir_shang = DISABLE;

		if ((Remote_Buffer[1] == 0x06) && (Remote_Buffer[2] == 0x07) && 
				(Remote_Buffer[3] == 0x08) && (Remote_Buffer[4] == 0x09))
	  {	
        dir_str.dir_forward = ENABLE;
	  }   
		else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x03) && 
						 (Remote_Buffer[3] == 0x00) && (Remote_Buffer[4] == 0x00))
		{
		    dir_str.dir_back = ENABLE;	
		}   
		else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x00) && 
	           (Remote_Buffer[3] == 0x03) && (Remote_Buffer[4] == 0x00))
		{
	      dir_str.dir_left = ENABLE; 
	  }	
		else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x00) && 
						 (Remote_Buffer[3] == 0x01) && (Remote_Buffer[4] == 0x00))
		{
		    dir_str.dir_right = ENABLE;				
		}
		else if  ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x01) && 
							(Remote_Buffer[3] == 0x07) && (Remote_Buffer[4] == 0x00))	
	  { 	
		    dir_str.dir_e_stop = ENABLE;
	  }   
	  else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x01) && 
	           (Remote_Buffer[3] == 0x01) && (Remote_Buffer[4] == 0x00))
	  {
		    dir_str.dir_left_forward = ENABLE;
		}
	  else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x01) && 
	           (Remote_Buffer[3] == 0x03) && (Remote_Buffer[4] == 0x00))
	  {
		    dir_str.dir_right_forward = ENABLE;
	  }
	  else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x03) && 
	           (Remote_Buffer[3] == 0x01) && (Remote_Buffer[4] == 0x00))
	  {
		    dir_str.dir_left_back = ENABLE;
	  }
	  else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x03) && 
	           (Remote_Buffer[3] == 0x03) && (Remote_Buffer[4] == 0x00))
	  {
		    dir_str.dir_right_back = ENABLE;
	  }
    else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x09) && 
	           (Remote_Buffer[3] == 0x02) && (Remote_Buffer[4] == 0x00))
	  {
		    dir_str.dir_up = ENABLE; 			
   	}
    else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x09) && 
	           (Remote_Buffer[3] == 0x03) && (Remote_Buffer[4] == 0x00))
	  {
		    dir_str.dir_down = ENABLE;	
	  }
		else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x09) && 
	           (Remote_Buffer[3] == 0x01) && (Remote_Buffer[4] == 0x00)) 
		{
				dir_str.dir_xia = ENABLE;				
		}
		else if ((Remote_Buffer[1] == 0x00) && (Remote_Buffer[2] == 0x09) && 
	           (Remote_Buffer[3] == 0x00) && (Remote_Buffer[4] == 0x00)) 
		{
				dir_str.dir_shang = ENABLE;				
		}
}	

void Remote_Control(void)
{
	  Turn_Left = Turn_Right = 0;
    if (dir_str.dir_forward == ENABLE)	      //forward
		{
	 	    dir_str.dir_forward = DISABLE;	
			  Remote_Speed = Remote_Speed + 2;	
		}
		else if (dir_str.dir_back == ENABLE)    	//back
		{																															
				dir_str.dir_back = DISABLE;
				Remote_Speed = Remote_Speed - 2;	   
		}
		else if (dir_str.dir_left == ENABLE)      //left 
		{
				dir_str.dir_left = DISABLE;
        Turn_Left = -25;
				Turn_Right = 25;
		}
		else if (dir_str.dir_right == ENABLE)     //right
		{
				dir_str.dir_right = DISABLE;
				Turn_Left = 25;
				Turn_Right = -25;
		}
		else if (dir_str.dir_left_forward == ENABLE)  	//left forward 
		{
				dir_str.dir_left_forward = DISABLE; 
				Remote_Stop = 1;		
		}
		else if (dir_str.dir_right_forward == ENABLE)	//right forward
		{  		
				dir_str.dir_right_forward = DISABLE;
						// add your code here 	
				u8Remote_Voice1 = ENABLE;
		}
		else if (dir_str.dir_left_back == ENABLE)  		//left back 
		{
				dir_str.dir_left_back = DISABLE;
				// add your code here 	
          u8Remote_Voice2 = ENABLE;
		}
		else if (dir_str.dir_right_back == ENABLE)		//right back
		{
				dir_str.dir_right_back = DISABLE;
				// add your code here 		
				u8Remote_Voice3 = ENABLE;
		}
		else if (dir_str.dir_up == ENABLE)		   		//up
		{ 	
				dir_str.dir_up = DISABLE;	
				Remote_Flag = 1;	
				Remote_Speed = 0;
		}							   
		else if (dir_str.dir_down == ENABLE)	  	  //down
		{	
				dir_str.dir_down = DISABLE;	
				Remote_Flag = 0; 
				Remote_Speed = 0;
				Music_Play_Slection(0, 0);
				u8Exit = 1;
		}
		else  if (dir_str.dir_stop == ENABLE)				//stop
		{	 
				dir_str.dir_stop = DISABLE;					 
		}  	  
		else  if (dir_str.dir_e_stop == ENABLE)			//stop
		{	 
				dir_str.dir_e_stop = DISABLE;
				//add your code here 						 
		} 
		else if (dir_str.dir_xia == ENABLE)
		{
		      dir_str.dir_xia = DISABLE;
				//add your code here
				u8Remote_Voice4 = ENABLE;
		}
		else if (dir_str.dir_shang == ENABLE)
		{
				dir_str.dir_shang = DISABLE;
				//add your code here
				u8Remote_Voice5 = ENABLE;
		}
		
		if(Remote_Speed >= REMOTE_MAX_SPEED)
		{
        Remote_Speed = REMOTE_MAX_SPEED;
		}
		if(Remote_Speed <= REMOTE_MIN_SPEED)
		{
        Remote_Speed = REMOTE_MIN_SPEED;
		}
		
		if(Remote_Stop == 1)
		{
        RemoteLeft_EXP = RemoteRight_EXP = Remote_Speed = 0;
		}
		
		RemoteLeft_EXP =  Remote_Speed + Turn_Left;
		RemoteRight_EXP = Remote_Speed + Turn_Right;
		
		
	  Remote_Stop = Turn_Left = Turn_Right = 0;
}

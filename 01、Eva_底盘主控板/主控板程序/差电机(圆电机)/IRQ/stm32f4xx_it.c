#include "stm32f4xx_it.h"
#include "main.h"
#include "Speaker.h"
#include "LCD.h"
#include "Filtering_Algorithm.h"
#include "Sensor_Acquisition.h"
#include "PWM_Output.h"
#include "PID_Calculation.h"
#include "MagneticNavigation.h"
#include "RFID.h"
#include "USART.h"
#include "Reserved.h"
#include "IrDA.h"
#include "Speaker.h"
#include "Remote_Control.h"
#include "MiscIO.h"
#include "ResetMode.h"

__IO uint8_t	UART1Cmd1mS=0;
__IO u16 u16OutOfRoadCnt = 0;

void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{


		TimingDelay_Decrement();	
		
		
				#if 1
					Sensor_Acquisition();
					Filtering_Algorithm();
					PID_Calculation();			
					PWM_Output(PID_LeftMotor,PID_RightMotor);		
					
					LcdReceiveJudge();
					Obstacle_Check();
					
					if (CTData == 0) u16OutOfRoadCnt++;
					else 						 u16OutOfRoadCnt = 0;
  			#endif		
				
			//	CycleSendMode();
		

}
/**
  * @brief  This function handles Magnetic Navi IRQHandler.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{

#if 0
	u16 temp = 0;
	
	
  if(USART_GetITStatus(SPEAKER_USART, USART_IT_RXNE) != RESET)	   
	  {		
		    temp = USART_ReceiveData(SPEAKER_USART);
				
				#if 0
				USART_SendData(SPEAKER_USART, temp);
				 while(USART_GetFlagStatus(SPEAKER_USART, USART_FLAG_TXE) == RESET);
				#endif
				
				#if 1
				u8ResposeBuf[u8ReceiveCnt++] = temp;
				if (u8ReceiveCnt >= 7) 
				{
					u8ReceiveCnt = 0;
					u8PlayStatus = u8ResposeBuf[MUSIC_STATUS];
				}
				#endif
		}
		
		//------------------------------------------------------
		if(USART_GetITStatus(SPEAKER_USART, USART_IT_TXE) != RESET) 
	  { 
        USART_ITConfig(SPEAKER_USART, USART_IT_TXE, DISABLE);
	  } 
		#else
				u16 temp = 0;

	  static u16 ui = 0;
	  static u16 StReceive = 0;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	   
	  {		
		    temp = USART_ReceiveData(USART1);
				
	    	if(Frame_Head == temp) 	                             //0x7B
		    {
			      StReceive = 1;
			      ui = 0;				
		    }
        if(Frame_End == temp)	                               //0x7E
		    {
			      StReceive = 0;	  	  
	     	}
		    if(StReceive == 1)
		    {   
			      Remote_Buffer[ui] = temp;
						ui++;
            if(ui >= 5)
			      {
								Remote_Recognition();
								Remote_Control();	
								ui = 0;								
			      }
		    }
    }
	  
	
	 if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET) 
	  { 
        USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	  }
		#endif
		
	
}



/**
  * @brief  This function handles Test IRQHandler.
  * @param  None
  * @retval None
  */
	
void USART2_IRQHandler(void)
{
			
#if 1
		u16 temp = 0;

	  static u16 ui = 0;
	  static u16 StReceive = 0;

    if(USART_GetITStatus(BT_USART, USART_IT_RXNE) != RESET)	   
	  {		
		    temp = USART_ReceiveData(BT_USART);
				
	    	if(Frame_Head == temp) 	                             //0x7B
		    {
			      StReceive = 1;
			      ui = 0;				
		    }
        if(Frame_End == temp)	                               //0x7E
		    {
			      StReceive = 0;	  	  
	     	}
		    if(StReceive == 1)
		    {   
			      Remote_Buffer[ui] = temp;
						ui++;
            if(ui >= 5)
			      {
								Remote_Recognition();
								Remote_Control();	
								ui = 0;								
			      }
		    }
    }
	  
	
	 if(USART_GetITStatus(BT_USART, USART_IT_TXE) != RESET) 
	  { 
        USART_ITConfig(BT_USART, USART_IT_TXE, DISABLE);
	  }
#else
	u16 temp = 0;
  if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)	   
	  {		
		    temp = USART_ReceiveData(USART6);
				USART_SendData(USART6, temp);
				 while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);
		}
		
		//------------------------------------------------------
		if(USART_GetITStatus(USART6, USART_IT_TXE) != RESET) 
	  { 
        USART_ITConfig(USART6, USART_IT_TXE, DISABLE);
	  } 
#endif		

}

/**
  * @brief  This function handles RFID Reader IRQHandler.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
		if(RFID_USART->SR&UartRxne)  
	{	
		RFID_Buffer[RFID_Rec]=(uint8_t)(RFID_USART->DR);
		RFID_USART->SR=0;
		RFID_Rec++;
		
		if(RfidMustRec == RFID_Rec)	
		{		
			/*if(RFID_LowPower_Flag)
			{
				if((RFID_Buffer[0]==0xA9)||(RFID_Buffer[1]==0xA9)||(RFID_Buffer[2]==0xA9)||(RFID_Buffer[3]==0xA9))
					FindCmd_Flag=1;
				else;
			}
			else	if(RFID_FindCar_Flag)
			{
				if((RFID_Buffer[0]==0xA9)||(RFID_Buffer[1]==0xA9)||(RFID_Buffer[2]==0xA9)||(RFID_Buffer[3]==0xA9))
					FindCmd_Flag=1;
				else;
			}*/
			
		  if(FindCar_Flag == 1)
			{			
				HavrCardFlag=0;
				if((RFID_Buffer[0]==0xAA)&&(RFID_Buffer[1]==0xAA))
				{
					//2组数据对比正确
					Station = RFID_Buffer[2]+RFID_Buffer[3]*256;//调用读卡比对程序
					HavrCardFlag=1;
				}
				else	if((RFID_Buffer[2]==0xAA)&&(RFID_Buffer[3]==0xAA))
				{
					Station = RFID_Buffer[0]+RFID_Buffer[1]*256;//调用读卡比对程序
					HavrCardFlag=1;
				}
				else	if((RFID_Buffer[1]==0xAA)&&(RFID_Buffer[2]==0xAA))
				{
					Station = RFID_Buffer[3]+RFID_Buffer[0]*256;//调用读卡比对程序
					HavrCardFlag=1;
				}
				else;	

				if(HavrCardFlag == 1)
				{
					HaveStationeFlag=1;
					NoHaveRfid100uS=0;			//清0					
					if (Station>999)	Station=999;							
				}						
			RFID_Rec=0;	
		}
		else;
  }
	else;	
	
	if(RFID_USART->SR&UartOver)
	{	//溢出
		RFID_Buffer[RFID_Rec]=(uint8_t)(RFID_USART->DR);
		RFID_USART->SR=0;
	}
	else;
	}

}
/**
  * @brief  This function handles LCD IRQHandler.
  * @param  None
  * @retval None
  */
void UART4_IRQHandler(void)
{	
	volatile int16_t UartSRBuf;

	 if(USART_GetITStatus(MAGNAVI_USART, USART_IT_RXNE) != RESET)	   
		{
			CdhReceive[CdhHaveReceivee]=(uint8_t)(MAGNAVI_USART->DR);
			
			if(CdhHRStart)
			{
				CdhHaveReceivee++;
			}
			else
			{
				if(CdhReceive[Cdh_StartPos]==Cdh_StartCmd)
				{
					CdhHaveReceivee=1;  //收到帧头
					CdhHRStart=1;
				}
				else
				{
					CdhHaveReceivee=0;	//未收到，从第0个开始收数据
				}
			}
			//UART1Cmd1mS=0;
		}
		else if ((UartSRBuf & USART_FLAG_TC) == USART_FLAG_TC)		//发送1次完成中断,
		{
		}
		else;
		
  
}

/**
  * @brief  This function handles Speaker IRQHandler.
  * @param  None
  * @retval None
  */
void UART5_IRQHandler(void)
{
	 	u16 temp = 0;
  if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)	   
	  {		
		    temp = USART_ReceiveData(UART5);
				USART_SendData(UART5, temp);
				 while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
		}
		
		//------------------------------------------------------
		if(USART_GetITStatus(UART5, USART_IT_TXE) != RESET) 
	  { 
        USART_ITConfig(UART5, USART_IT_TXE, DISABLE);
	  } 
}

/**
  * @brief  This function handles Reserved USART IRQHandler.
  * @param  None
  * @retval None
  */
	
void USART6_IRQHandler(void)
{	
		if(USART_GetITStatus(LCD_USART, USART_IT_RXNE) != RESET)	   
		{	// 如果是串口接收中断,lcd
			LcdReceiveData=(uint8_t)(LCD_USART->DR);	
			LCD_USART->SR=0;
			
			if(LcdReceiveData==LcdStartCmd)
			{
				Lcd_have_receive=0;
			}
			else;		
			
			Lcd_Receive[Lcd_have_receive]=LcdReceiveData;
			Lcd_have_receive++;
			
			if(Lcd_have_receive==	LcdCmdMustReceive)
			{
				Lcd_have_receive=0;			
				//Lcd100uS=0;			
				Lcd_have_scmd=1;
			}
			else;	
		}	
		else;
		
		 if(USART_GetITStatus(LCD_USART, USART_IT_RXNE) != RESET)	   
		{	//溢出
			LcdReceiveData=(uint8_t)(LCD_USART->DR);	
			LCD_USART->SR=0;
		}
		else;
}
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

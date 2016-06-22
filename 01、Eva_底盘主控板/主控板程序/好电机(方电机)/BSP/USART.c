#include "USART.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "MagneticNavigation.h"

void USASRT_Configuration(void)
{
	
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		
		/* USART1 configuration */
		/* PA9(USART1_TX),PA10(USART1_RX) */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);  
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOA, &GPIO_InitStructure);   		
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		USART_InitStructure.USART_BaudRate = SPEAKER_USART_BAUD;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		USART_Init(USART1, &USART_InitStructure);
	
		USART_Cmd(USART1, ENABLE);
		USART_ClearFlag(USART1, USART_FLAG_TXE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			
				
			

		/* USART2 configuration */
		/* PD5(USART2_TX),PD6(USART2_RX) */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE); 			
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOD, &GPIO_InitStructure); 		
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);		
		USART_InitStructure.USART_BaudRate = BT_USART_BAUD;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		USART_Init(USART2, &USART_InitStructure);
		
		USART_Cmd(USART2, ENABLE);
		USART_ClearFlag(USART2, USART_FLAG_TXE);
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
		
		/* USART3 configruation */
		/* PD8(USART3_TX),PD9(USART3_RX) */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);			
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOD, &GPIO_InitStructure); 
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
		USART_InitStructure.USART_BaudRate = RFID_USART_BAUD;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		USART_Init(USART3, &USART_InitStructure);
		
		USART_Cmd(USART3, ENABLE);		
		USART_ClearFlag(USART3, USART_FLAG_TXE);		
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		
		/* UART4 configuration */
		/* PC10(UART4_TX),PC11(UART4_RX) */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOC, &GPIO_InitStructure); 
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE); 
		USART_InitStructure.USART_BaudRate = MAGNAVI_USART_BAUD;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		USART_Init(UART4, &USART_InitStructure);
	
		USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
		USART_ClearFlag(UART4, USART_FLAG_TXE);
		USART_Cmd(UART4, ENABLE);
		
		/* UART5 configuration */
		/* PC12(UART5_TX),PD2(UART5_RX) */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);	
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			
		GPIO_Init(GPIOC, &GPIO_InitStructure);		
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE); 		
		USART_InitStructure.USART_BaudRate = PAD_USART_BAUD;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		USART_Init(UART5, &USART_InitStructure);
		
		USART_ClearFlag(UART5, USART_FLAG_TXE);				
		USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
		USART_Cmd(UART5, ENABLE);
	
		/* USART6 configuration */
		/* PG14(TXD6),PG9(RXD6) */		
		#if 1
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);		
		GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);  
		GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOG, &GPIO_InitStructure);   			
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);		
		USART_InitStructure.USART_BaudRate = LCD_USART_BAUD;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		USART_Init(USART6, &USART_InitStructure);
		
		USART_ClearFlag(USART6, USART_FLAG_TXE);		
		USART_Cmd(USART6, ENABLE);		
		USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
		#endif
}

void Send_ReadMagNaviData(uint8_t *pCommand)
{
	uint8_t	Count;	

	for(Count=0; Count < ReadCdhCmdLength; Count++)
	{ 				
		
		MAGNAVI_USART->DR = pCommand[Count];
		

		while(USART_GetFlagStatus(MAGNAVI_USART, USART_FLAG_TXE) == RESET); //等待发送完毕 		
	}
}

void Send_SpeakerData(u8 *pCommand, u8 u8Len)
{
		uint8_t	Count;	

		for(Count=0; Count < u8Len; Count++)
		{ 				
			
			SPEAKER_USART->DR = pCommand[Count];
			
			while(USART_GetFlagStatus(SPEAKER_USART, USART_FLAG_TXE) == RESET); //等待发送完毕 		
		}
} 

void Send_LCDData(u8 temp)
{
		LCD_USART->DR=temp;
    while(USART_GetFlagStatus(LCD_USART, USART_FLAG_TXE) == RESET);
}

void Send_Data(USART_TypeDef* USARTx ,u8 *pCommand, u8 u8Len)
{
		uint8_t	Count;	

		for(Count=0; Count < u8Len; Count++)
		{ 				
			USARTx->DR = pCommand[Count];
			
			while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); //等待发送完毕 		
		}
}

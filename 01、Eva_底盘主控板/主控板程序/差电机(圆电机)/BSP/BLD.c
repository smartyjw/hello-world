#include "BLD.h"
#include "config.h"

void GPIO_BLD_Configruration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
		//FRL
		RCC_AHB1PeriphClockCmd(FRL_GPIO_RCC, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = FRL_GPIO_PIN; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		
		GPIO_Init(FRL_GPIO_TYPE, &GPIO_InitStructure);		
		
		//ENL
		RCC_AHB1PeriphClockCmd(ENL_GPIO_RCC, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = ENL_GPIO_PIN; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		 	
		GPIO_Init(ENL_GPIO_TYPE, &GPIO_InitStructure);	
		
		//BRKL
		RCC_AHB1PeriphClockCmd(BRKL_GPIO_RCC, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = BRKL_GPIO_PIN; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		
		GPIO_Init(BRKL_GPIO_TYPE, &GPIO_InitStructure);		

		//FRR
		RCC_AHB1PeriphClockCmd(FRR_GPIO_RCC, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = FRR_GPIO_PIN; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			
		GPIO_Init(FRR_GPIO_TYPE, &GPIO_InitStructure);	
		
		//ENR
		RCC_AHB1PeriphClockCmd(ENR_GPIO_RCC, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = ENR_GPIO_PIN; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		
		GPIO_Init(ENR_GPIO_TYPE, &GPIO_InitStructure);	
		
		//BRKR
		RCC_AHB1PeriphClockCmd(BRKR_GPIO_RCC, ENABLE);  
		GPIO_InitStructure.GPIO_Pin = BRKR_GPIO_PIN; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		
		GPIO_Init(BRKR_GPIO_TYPE, &GPIO_InitStructure);		
}

void BLD_Ctrl_L(uint8_t u8DriEn, uint8_t u8Dir, uint8_t u8BkEn)
{
		//PA1, Driver Enable Set
		if (ENABLE == u8DriEn)
		{
				ENL_CLR();  
		}
		else
		{
				ENL_SET();  
		}
		
		//PA0, Direction Set
		if (FORWARD == u8Dir)
		{
#ifdef WORSE_MOTOR		
				FRL_SET();
#else
				FRL_CLR();
#endif				
		}
		else
		{								 
#ifdef WORSE_MOTOR		
				FRL_CLR();
#else
				FRL_SET();
#endif				
		}
		
		//PA2, Break Enable Set
		if (ENABLE == u8BkEn)
		{
				BRKL_CLR();
		}
		else
		{
				BRKL_SET();				
		}
		
		
}

void BLD_Ctrl_R(uint8_t u8DriEn, uint8_t u8Dir, uint8_t u8BkEn)
{
		//PA4, Driver Enable Set
		if (ENABLE == u8DriEn)
		{
				ENR_CLR();
		}
		else
		{
				ENR_SET();
		}
		
		//PA3, Direction Set
		if (FORWARD == u8Dir)
		{					
#ifdef WORSE_MOTOR		
				FRR_CLR();
#else
				FRR_SET();
#endif
		}
		else
		{				
#ifdef 	WORSE_MOTOR		
				FRR_SET();
#else
				FRR_CLR();
#endif				
		}
		
		//PA5, Break Enable Set
		if (ENABLE == u8BkEn)
		{
				BRKR_CLR();
		}
		else
		{
				BRKR_SET();				
		}
}

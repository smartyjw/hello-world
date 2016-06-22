#include "IrDA.h"

u8 u8Obstacle;

void GPIO_IrDA_Configuration(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;	
												
		RCC_AHB1PeriphClockCmd(IRDA12_GPIO_RCC, ENABLE);	 			
		
		GPIO_InitStructure.GPIO_Pin = IRDA1_GPIO_PIN | IRDA2_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			
		GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP; 
		GPIO_Init(IRDA12_GPIO_TYPE, &GPIO_InitStructure);
		
		RCC_AHB1PeriphClockCmd(IRDA34_GPIO_RCC, ENABLE);	 			
		
		GPIO_InitStructure.GPIO_Pin = IRDA3_GPIO_PIN | IRDA4_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			
		GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP; 
		GPIO_Init(IRDA34_GPIO_TYPE, &GPIO_InitStructure);
		
		
		RCC_AHB1PeriphClockCmd(Tableware_GPIO_RCC, ENABLE);	 			
		
		GPIO_InitStructure.GPIO_Pin = Tableware1_GPIO_PIN | Tableware2_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			
		GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;
		GPIO_Init(Tableware_GPIO_TYPE, &GPIO_InitStructure);
		
		
}

void Obstacle_Check(void)
{
	u8 u8Status1, u8Status2, u8Status3, u8Status4;
	
		//u8Obstacle = !(GetIRDA1Status() && GetIRDA2Status());
		
		u8Status1 = GetIRDA1Status();
		u8Status2 = GetIRDA2Status();
		u8Status3 = GetIRDA3Status();
		u8Status4 = GetIRDA4Status();
	
	#if 0	
		u8Obstacle = u8Status1 || u8Status2 || u8Status3 || u8Status4;
	#else 
	  u8Obstacle = !(u8Status1 & u8Status2 & u8Status3 & u8Status4);
	#endif 
		
		
		
}

u8 IrDA1_Check(void)
{
	u8 IrDA1_status;
	
	
		IrDA1_status = GetIRDA1Status();
		
		return IrDA1_status;
}

u8 IrDA2_Check(void)
{
	u8 IrDA2_status;
	
		IrDA2_status = GetIRDA2Status();
		
		return IrDA2_status;
}

u8 IrDA3_Check(void)
{
	u8 IrDA3_status;
	
		IrDA3_status = GetIRDA3Status();
		
		return IrDA3_status;
}

u8 IrDA4_Check(void)
{
	u8 IrDA4_status;
	
		IrDA4_status = GetIRDA4Status();
		
		return IrDA4_status;
}

u8 TableWare1_Check(void)
{
	u8 status;
	
		status = GetTableware1Status();
		
		return status;
}

u8 TableWare2_Check(void)
{
	u8 status;
	
		status = GetTableware2Status();
		
		return status;
}

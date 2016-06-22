#include "stm32f4xx.h"
#include "Filtering_Algorithm.h"
#include "Sensor_Acquisition.h"
#include "MagneticNavigation.h"

float Direction = 0;
float Direction_Buf[DirectionBuf_Number] = {0};

uint8_t SumL_Count = 0;
uint8_t SumR_Count = 0;
float Speed_LeftMotor = 0;
float Speed_RightMotor = 0;
float SpeedL_Buf[SpeedBuf_Number] = {0};
float SpeedR_Buf[SpeedBuf_Number] = {0};

void Filtering_Algorithm(void)
{
	  Direction_Filter();
    Speed_Filter();
}

//uint8_t Direction_Count = 0; 
void Direction_Filter(void)
{ 
	
    static uint8_t Direction_Count = 0; 
    uint8_t Direction_Count1 = 0;
	  float Direction_Sum = 0;
    
    Direction_Buf[Direction_Count++] = CTData;
   
    if ( Direction_Count == DirectionBuf_Number)
    {
        Direction_Count = 0;
    }
    
    for ( Direction_Count1 = 0;Direction_Count1 < DirectionBuf_Number;Direction_Count1++) 
    {
        Direction_Sum += Direction_Buf[Direction_Count1];
    }
        
    Direction = Direction_Sum / DirectionBuf_Number;	
}

void Speed_Filter(void)
{
	  uint8_t Speed_Count = 0;
	  float SpeedL_Sum = 0;
    float SpeedR_Sum = 0;
    
    SpeedL_Buf[SumL_Count++] = SpotSpeed_LeftMotor;
    SpeedR_Buf[SumR_Count++] = SpotSpeed_RightMotor;
   
    if ( SumL_Count == SpeedBuf_Number )
    {
        SumL_Count = 0;
    }
    
    if ( SumR_Count == SpeedBuf_Number )
    {
        SumR_Count = 0;
    }
    
    for ( Speed_Count = 0;Speed_Count < SpeedBuf_Number;Speed_Count++) 
    {
        SpeedL_Sum += SpeedL_Buf[Speed_Count];
        SpeedR_Sum += SpeedR_Buf[Speed_Count];
    }
        
    Speed_LeftMotor = SpeedL_Sum / SpeedBuf_Number;
    Speed_RightMotor = SpeedR_Sum / SpeedBuf_Number; 
}

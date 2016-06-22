#include "RFID.h"

__IO uint8_t HavrCardFlag=0;
__IO uint8_t RFID_Rec = 0;
__IO uint8_t RFID_Buffer[32];
__IO uint8_t RFID_LowPower_Flag = 0;	//µÕπ¶∫ƒ√¸¡Ó
__IO uint8_t RFID_FindCar_Flag = 0;		//—∞ø®√¸¡Ó
__IO uint8_t FindCar_Flag = 1;				//—∞ø®∑µªÿ
__IO uint8_t FindCmd_Flag = 0;				//—∞ø®∑µªÿ
__IO uint8_t HaveStationeFlag = 0;

__IO uint16_t Station = 0xFFFF;
__IO uint16_t NoHaveRfid100uS = 0;    //ºÏ≤‚”–ŒﬁRFID–≈∫≈

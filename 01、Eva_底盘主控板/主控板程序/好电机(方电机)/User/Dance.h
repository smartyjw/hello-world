#ifndef __DANCE_H__
#define __DANCE_H__
#include "stm32f4xx.h"

extern u8 u8DanceCount;

void Dance(void);
void Dance_LeftTurning_Movement(void);
void Dance_RightTurning_Movement(void);
void Dance_Without_MegneticNavi(void);
#endif

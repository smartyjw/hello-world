#ifndef __PADCONTROL_H__
#define __PADCONTROL_H__

#include "stm32f4xx.h"

#define Frame_Head 	(0x7B)
#define Frame_End   (0x7E)

typedef struct _dir
{
  int dir_forward;
  int dir_back;

  int dir_left;
  int dir_right;

  int dir_left_forward;
  int dir_right_forward;

  int dir_left_back;
  int dir_right_back;
	
  int dir_e_stop; 
  int dir_stop;
  int dir_cur;

  int dir_up;
  int dir_down;
	
	int dir_xia;
	int dir_shang;

} DIR_STRUCTURE;

extern u8 Remote_Flag;
extern float Remote_Speed;
extern u8 Remote_Buffer[];
extern float RemoteLeft_EXP;
extern float RemoteRight_EXP;
extern u8 Remote_Flag;
extern u8 u8Remote_Voice1, u8Remote_Voice2, u8Remote_Voice3, u8Remote_Voice4, u8Remote_Voice5;

void Remote_Recognition(void);
void Remote_Control(void);
#endif

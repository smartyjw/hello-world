#ifndef __TIM_H__
#define __TIM_H__

#define ENCODER_TIMER_L   TIM3          // Encoder unit connected to TIM3
#define ENCODER_TIMER_R   TIM5          // Encoder unit connected to TIM5
#define ENCODER_PPR       (u16)(24)    //24 // number of pulses per revolution
#define COUNTER_RESET     (u16) (0)        
#define ICx_FILTER        (u8)  (6)      // 6<-> 670nsec

void SpeedExtraction_Configuration(void);
#endif

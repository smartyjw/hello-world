Phripherals Allocation as follows:

GPIO:
PA8: the control signal for Blue LED(D6)
PA11: the control signal for Red LED(D7)

PF0: the EN signal for the left motor
PF2: the Dir signal for the left motor
PF4: the break signal for the left motor

PF1: the EN signal for the right motor
PF3: the Dir signal for the right motor
PF5: the break signal for the right motor

PF6£º

TIM:
TIM4(PE0,TIM4_ETR, HU): measure the left motor pulses
TIM1(PA12,TIM1_ETR, HU): measure the right motor pulses

TIM3((PA6,TIM3_CH1,HV), (PA7,TIM3_CH2,HW)): measure the left motor phase(Encoder)
TIM5((PA0,TIM5_CH1,HV), (PA1,TIM5_CH2,HW)): measure the right motor phase(Encoder)

TIM2(PB10,TIM2_CH3):pwm output: pwm signal used to drive the left motor 
TIM2(PB11,TIM2_CH4):pwm output: pwm signal used to drive the right motor 
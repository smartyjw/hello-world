#ifndef __PID_CALCULATION_H__
#define __PID_CALCULATION_H__
/* Exported types ------------------------------------------------------------*/
extern float DirectionCL_PError;
extern float DirectionCL_PID;

extern float Speed_EXP;
extern float SpeedL_EXP;
extern float SpeedR_EXP;
extern float SpeedLeft_EXP;
extern float SpeedRight_EXP;

extern float SpeedL_PID;
extern float SpeedR_PID;

extern float Speed_Increment;

extern int PID_LeftMotor;
extern int PID_RightMotor;
/* Exported constants --------------------------------------------------------*/
#define LOW_SPEED (35)
#define MID_SPEED (45)
#define HIG_SPEED (55)
/* Exported macro	 ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------------*/
void PID_Calculation(void);
void PID_SpeedCL(void);
void PID_PositionCL(void);
void PID_DirectionCL(void);

void PID_RemoteControl(void);

#endif

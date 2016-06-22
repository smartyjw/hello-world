#ifndef   __FILTERING_ALGORITHM_H__
#define   __FILTERING_ALGORITHM_H__


/* Exported types ------------------------------------------------------------*/
extern float Direction;
extern float Speed_LeftMotor;
extern float Speed_RightMotor;
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define DirectionBuf_Number (100)
#define SpeedBuf_Number (10)
/* Exported functions ------------------------------------------------------------*/
void Filtering_Algorithm(void);
void Direction_Filter(void);
void Speed_Filter(void);
#endif

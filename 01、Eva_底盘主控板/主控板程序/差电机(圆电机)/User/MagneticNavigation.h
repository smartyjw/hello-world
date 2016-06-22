#ifndef __MAGNETICNAVIGATIOIN_H__
#define __MAGNETICNAVIGATIOIN_H__

#include "stm32f4xx.h"

#define	CdhSendCycle		(3)

//cdh
#define	CtWidth30					(3)				//定义磁条宽度50mm
#define	ReadCdhCmdLength  (6)
#define	Cdh_MustLength	  (7)

#define	Cdh_StartPos		(0)
#define	Cdh_CmdPos			(1)
#define	Cdh_LDatPos			(2)
#define	Cdh_RDatPos			(3)
#define	ReceiveCdhCrcHPos	(4)
#define	ReceiveCdhCrcLPos	(5)
#define	Cdh_EndPos				(6)

#define	Cdh_StartCmd		(0X1B)
#define	Cdh_EndCmd			(0X05)

#define	Cdh_ReadDatCmd	(0XA1)
#define	Cdh_ReadBitCmd	(0XA2)
#define	Cdh_SedCmd			(0XA3)
#define	Cdh_ZeroCmd			(0XA4)

#define	Cdh_ReadDatCmdYd	(0XA1)
#define	Cdh_ReadBitCmdYd	(0XA2)
#define	Cdh_SedCmdYd			(0XA3)
#define	Cdh_ZeroCmdYd			(0XA4)

#define	ReceiveCrcHPos	(4)
#define	ReceiveCrcLPos	(5)

#define	CdhModeL					(0)
#define	CdhModeR					(1)

extern __IO float CTData;
extern __IO uint8_t	CdhHRStart;
extern uint8_t CdhReceive[];
extern __IO uint8_t	CdhHaveReceivee;
void	GetmMagNaviData(void);

#endif

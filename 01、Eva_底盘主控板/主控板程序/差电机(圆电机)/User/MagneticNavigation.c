#include "MagneticNavigation.h"
#include "USART.h"

__IO uint8_t	MagNaviSampleCnt;						//����ʱ���1�δŵ�������
__IO uint8_t	CdhHaveReceivee=0;
__IO uint16_t	ReceiveCrc16;
__IO uint8_t	CdhHaveData1mS=0;				    //�жϴŵ����೤ʱ���յ�����
	
uint8_t TempBuffer[64];
uint8_t CdhReceive[64];
uint8_t	ReadCdhCmd[ReadCdhCmdLength]={0x1B,0xA1,0x00,0x40,0xBF,0x05}; 

__IO uint8_t	CdhHRStart=0;
__IO uint8_t	CdhMode = CdhModeL;
__IO float CTData = 0x00;

union
{
	uint8_t a[2];
	uint16_t ui;
} TT0;


//=============================================================================
//CRC16
//=============================================================================
uint16_t CRC16(uint8_t *p,uint8_t len)
{
	uint16_t 	uiCRC=0xffff;
 	uint8_t 	i,j;

 	for(j=0;j<len;j++)
  {
    uiCRC^=(*p);
		p++;
    for(i=0;i<8;i++)
    {
	     if(uiCRC&1){uiCRC>>=1;uiCRC^=0xa001;}
	     else 		uiCRC>>=1;
	  }
	}
	return(uiCRC);			
}

void	GetmMagNaviData(void)
{	
	MagNaviSampleCnt++;
	if(MagNaviSampleCnt >= CdhSendCycle)
	{
		MagNaviSampleCnt = 0;		//������0		
		//�����ŵ�������
		Send_ReadMagNaviData(ReadCdhCmd);
	}
	else;
	
	if(CdhHaveReceivee >= Cdh_MustLength)
	{
		CdhHaveReceivee=0;
		CdhHRStart=0;
		
		if(CdhReceive[Cdh_EndPos]==Cdh_EndCmd)
		{			
			TT0.a[1]=CdhReceive[ReceiveCrcHPos];
			TT0.a[0]=CdhReceive[ReceiveCrcLPos];
			ReceiveCrc16=TT0.ui;	
			TempBuffer[0]=CdhReceive[Cdh_LDatPos];				//�󵼺����ݣ�ΪCRC	
			TempBuffer[1]=CdhReceive[Cdh_RDatPos];				//�ҵ������ݣ�ΪCRC
			TT0.ui=CRC16(TempBuffer,2);
			if(ReceiveCrc16==TT0.ui)
			{
				if((TempBuffer[1]-TempBuffer[0])>=CtWidth30)
				{
					
					if(CdhMode==CdhModeL)
					{
						CTData=TempBuffer[0];										//��ֲ�
					}
					else
					{
						CTData=TempBuffer[1];										//�ҷֲ�
					}
				}
				else
				{
					CTData=(TempBuffer[0]+TempBuffer[1])/2.0;	//������Χ��ȡ�м�ֵ
				}
				CdhHaveData1mS=0;														//��ŵ�����ʱ��δ���յ����ݱ���
			}
			else;
		}
		else;
	}
	else;

}

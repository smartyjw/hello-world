/**
  ******************************************************************************
  * @�ļ���     UHF-RFID.h
  * @����       Thomas Yang
  * @�汾��     V1.0
  * @ʱ��       5-20-2016
  * @���˵��   UHF-RFID �ļ���ͷ�ļ�
  ******************************************************************************
  * @ע�����
  * ���ļ�����Ӳ��ƽ̨STM32F407�Ͽ����ģ�ʹ���˵���ARM��׼���ļ���#include "stm32f4xx.h"
  * 
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
  */
 
 
 
 
/* �����Է�ֹ�ݹ���� --------------------------------------------------------------*/
#ifndef __UFH_RFID_H 
#define __UFH_RFID_H 
 
#ifdef __cplusplus
 extern "C" {
#endif




/* ͷ�ļ�----------------------------------------------------------------------------*/
#include "stm32f4xx.h"

 


 
 
 
 
 

/* Ԥ��������Ͷ��� -----------------------------------------------------------------*/
	 
	 
	 



 /**  Ԥ������ַ��͵�ASCII��ֵ
 {*/ 
/** 
  * @���˵��   
  */

#define LF 0x0A   //����ָ�ͷ���з�
#define CR  0x0D   //�����ʼջ�Ĵ�С
 
 /**  Ԥ������ַ��͵�ASCII��ֵ
 }*/ 
  
 
 
 
 
 /**  UHF-RFID ָ�����
 {*/ 
/** 
  * @���˵��  Command Name Ӣ������Ӧ��ASCII��ֵ 
  */
	
#define FW_Version     ('V')   //��ȡ���汾
#define Reader_ID      ('S')   //��ȡ��ID��
#define Query_EPC      ('Q')   //��ʾ��ǩ EPC ID max 256bits
#define Read_EPC       ('R')   //��ȡTag��ǩоƬ�ϵ���Ϣ
#define Write_EPC      ('W')   //д���ϵ�TAG��ǩ��
#define RFID_Kill      ('K')   //ɾ��Tag��ǩ��Ϣ
#define Lock_Tag       ('L')   //��סTag��ǩ������
#define Writ_pwd       ('P')   //�趨��ȡ���룬�ڶ�ȡ��д�롣��סʱʹ��
#define Multi_EPC      ('U')   //��ȡ���Tag��ǩ��EPC ID ����
#define RFID_Keys      ('G')   //��Ӱ�ť����
#define RFID_other     ('N')   //����ָ��
#define RFID_select    ('T')   //ɸѡ��ǩ

 /**  UHF-RFID ָ�����
 }*/  
 
 
 
 
 
 
 
 
/* ��������--------------------------------------------------------------------------*/




 /**  UHF_RFID_OUT
 {*/ 

/** 
  * @brief  UHF-RFID_STACK just for have the one off_type
  */
  
void UHF_RFID_Command(char Command,char *Data);

  /**  UHF_RFID_OUT
 }*/  
  
  
  

  
#ifdef __cplusplus
}
#endif

#endif /* __UFH_RFID_H */  


 /******************* (C) Thomas Yang *****�ļ�����****/
  
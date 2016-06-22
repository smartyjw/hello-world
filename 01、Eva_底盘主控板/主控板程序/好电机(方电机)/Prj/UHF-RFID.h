/**
  ******************************************************************************
  * @文件名     UHF-RFID.h
  * @作者       Thomas Yang
  * @版本号     V1.0
  * @时间       5-20-2016
  * @简短说明   UHF-RFID 文件的头文件
  ******************************************************************************
  * @注意事项：
  * 此文件是在硬件平台STM32F407上开发的，使用了到了ARM标准库文件，#include "stm32f4xx.h"
  * 
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
  */
 
 
 
 
/* 定义以防止递归包含 --------------------------------------------------------------*/
#ifndef __UFH_RFID_H 
#define __UFH_RFID_H 
 
#ifdef __cplusplus
 extern "C" {
#endif




/* 头文件----------------------------------------------------------------------------*/
#include "stm32f4xx.h"

 


 
 
 
 
 

/* 预定义和类型定义 -----------------------------------------------------------------*/
	 
	 
	 



 /**  预定义非字符型的ASCII码值
 {*/ 
/** 
  * @简短说明   
  */

#define LF 0x0A   //定义指令开头换行符
#define CR  0x0D   //定义初始栈的大小
 
 /**  预定义非字符型的ASCII码值
 }*/ 
  
 
 
 
 
 /**  UHF-RFID 指令代号
 {*/ 
/** 
  * @简短说明  Command Name 英文名对应的ASCII码值 
  */
	
#define FW_Version     ('V')   //读取器版本
#define Reader_ID      ('S')   //读取器ID号
#define Query_EPC      ('Q')   //显示标签 EPC ID max 256bits
#define Read_EPC       ('R')   //读取Tag标签芯片上的信息
#define Write_EPC      ('W')   //写资料到TAG标签上
#define RFID_Kill      ('K')   //删除Tag标签信息
#define Lock_Tag       ('L')   //锁住Tag标签记忆体
#define Writ_pwd       ('P')   //设定存取密码，在读取，写入。锁住时使用
#define Multi_EPC      ('U')   //读取多个Tag标签的EPC ID 号码
#define RFID_Keys      ('G')   //外接按钮功能
#define RFID_other     ('N')   //其他指令
#define RFID_select    ('T')   //筛选标签

 /**  UHF-RFID 指令代号
 }*/  
 
 
 
 
 
 
 
 
/* 函数申明--------------------------------------------------------------------------*/




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


 /******************* (C) Thomas Yang *****文件结束****/
  
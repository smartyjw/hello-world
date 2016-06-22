#include "USART.h"
#include "common.h"
#include "LCD.h"
#include "FoodMenue.h"
#include "string.h"
#include "Remote_Control.h"
#include "IrDA.h"
#include "test.h"
#include "PID_Calculation.h"
#include "UART_Protocol.h"
#include "Speaker.h"

//extern	__IO	uint8_t			Lcd_Move_Station;		
				__IO  u8					u8SpeedLevel = LOW_SPEED;
			  __IO  uint8_t 		RunningMode = WELCOME_CUSTOMR_MODE;
				__IO  uint8_t 		Dilivering = 0;
				__IO 	uint8_t 		LcdReceiveData,LcdMustReceive;
				__IO 	uint8_t 		LcdReceiveDataFlag=0;
				__IO 	uint8_t 		Receive[Recive_lengthMax];
				__IO 	uint8_t			have_scmd=0;	//一帧数据接收完毕标志
				__IO 	uint8_t			have_receive=0;
				
				__IO 	uint8_t			Lcd100uS=0;
				__IO 	uint8_t 		Lcd_Receive[Recive_lengthMax];
				__IO 	uint8_t			Lcd_have_scmd=0;	//一帧数据接收完毕标志
				__IO 	uint8_t			Lcd_have_receive=0;
				__IO	uint8_t			LCD_Start_Flag = DISABLE;
				__IO	uint8_t   	Wifi_Start_Flag=0;
				__IO	uint16_t 		SWTFlag = 0x0000;			//目标站点
				__IO	uint8_t 		MoveFlag = 0;          
			  __IO uint32_t 		data32 = 0;              
				__IO 	uint8_t			OkStation=0;						//按确认键，播放桌号			
				__IO  uint8_t 		row = 0;			//菜名行号
				__IO  uint16_t 		u16DishCode[10] = {0};
				
const int RowTable[] = {210, 250, 290, 330};

void xrd_start(void)
{
    Send_LCDData(0xAA);
}

void xrd_end(void)
{
    Send_LCDData(0xCC);
    Send_LCDData(0x33);
    Send_LCDData(0xC3);
    Send_LCDData(0x3C);
}



//function_name :   xrd_picture       
//parameter     :   p图片id
//return_data   :       
//describe          显示图片
void xrd_picture(uint8_t p)
{
    xrd_start();
    Send_LCDData(0x70);
    Send_LCDData(p);
    xrd_end();
}

/*******************************************************************************
* Function Name  : void xrd_LcdClear(void)
* Description    : 前景色显示多个矩形框
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void xrd_juxingkuang(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    xrd_start();
		
		Send_LCDData(0x59);
		Send_LCDData(x1/256);
		Send_LCDData(x1%256);
		Send_LCDData(y1/256);
		Send_LCDData(y1%256);
		Send_LCDData(x2/256);
		Send_LCDData(x2%256);
		Send_LCDData(y2/256);
		Send_LCDData(y2%256);
		
    xrd_end();
}

/*******************************************************************************
* Function Name  : void xrd_FrontFill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
* Description    : 前景色填充矩形框
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void xrd_FrontFill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    xrd_start();
		
		Send_LCDData(0x5B);
		Send_LCDData(x1/256);
		Send_LCDData(x1%256);
		Send_LCDData(y1/256);
		Send_LCDData(y1%256);
		Send_LCDData(x2/256);
		Send_LCDData(x2%256);
		Send_LCDData(y2/256);
		Send_LCDData(y2%256);
		
    xrd_end();
}
/*******************************************************************************
* Function Name  : void xrd_LcdClear(void)
* Description    : 清屏
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void xrd_LcdClear(void)
{
    xrd_start();
    Send_LCDData(0x52);
    xrd_end();
}

/*******************************************************************************
* Function Name  : void xrd_SetColor(uint16_t x,uint16_t y)
* Description    : 设置前后背景色
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void xrd_SetColor(uint16_t x,uint16_t y)
{
    xrd_start();
		
    Send_LCDData(0x40);
		Send_LCDData(x/256);
		Send_LCDData(x%256);
		Send_LCDData(y/256);
		Send_LCDData(y%256);
		
    xrd_end();
}
/*******************************************************************************
* Function Name  : void xrd_GetBColor(uint16_t x,uint16_t y)
* Description    : 背景色取色
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void xrd_GetBColor(uint16_t x,uint16_t y)
{
    xrd_start();
		
    Send_LCDData(0x42);
		Send_LCDData(x/256);
		Send_LCDData(x%256);
		Send_LCDData(y/256);
		Send_LCDData(y%256);
		
    xrd_end();
}

/*******************************************************************************
* Function Name  : void xrd_SetBuzzer(uint8_t	i)
* Description    : 蜂鸣器响的时间设置
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void xrd_SetBuzzer(uint8_t	i)
{
    xrd_start();
		
    Send_LCDData(0x79);
		Send_LCDData(i);
		
    xrd_end();
}

/*******************************************************************************
* Function Name  : void xrd_SetBacLed(uint8_t	i)
* Description    : 设置背光亮度 
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void xrd_SetBacLed(uint8_t	i)
{
    xrd_start();
		
    Send_LCDData(0x5f);
		Send_LCDData(i);
		
    xrd_end();
}

/*******************************************************************************
* Function Name  : void xrd_SetClock(uint8_t	cTMode,uint8_t	cSMode,uint16_t	cColor,uint16_t X,uint16_t Y)
* Description    : 时钟设置 
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void xrd_SetClock(uint8_t	cTMode,uint8_t	cSMode,uint16_t	cColor,uint16_t X,uint16_t Y)
{
    xrd_start();
		
    Send_LCDData(0x9B);
		Send_LCDData(0xff);
		Send_LCDData(cTMode);
		Send_LCDData(cSMode);
		Send_LCDData(cColor/256);
		Send_LCDData(cColor%256);
		Send_LCDData(X/256);
		Send_LCDData(X%256);
		Send_LCDData(Y/256);
		Send_LCDData(Y%256);
		
    xrd_end();
}

/*******************************************************************************
* Function Name  : void xrd_SetClock(uint8_t	cTMode,uint8_t	cSMode,uint16_t	cColor,uint16_t X,uint16_t Y)
* Description    : 设置时间 
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void xrd_SetHms(uint8_t	YY,uint8_t	MM,uint8_t	DD,uint8_t	HH,uint8_t	MS,uint8_t	SS)
{
    xrd_start();
		
    Send_LCDData(0xE7);
		Send_LCDData(0x55);
		Send_LCDData(0xAA);
		Send_LCDData(0x5A);
		Send_LCDData(0xA5);
		Send_LCDData(YY/10*16+YY%10);
		Send_LCDData(MM/10*16+MM%10);
		Send_LCDData(DD/10*16+DD%10);
		Send_LCDData(HH/10*16+HH%10);
		Send_LCDData(MS/10*16+MS%10);
		Send_LCDData(SS/10*16+SS%10);
		
    xrd_end();
}

//function_name :   xrd_32srting       
//parameter     :   x0,y0(起始坐标) *str显示字符串    
//return_data   :       
//describe      :   32*16 字符 32*32汉字   
void xrd_32srting(uint16_t x0, uint16_t y0,char *str)
{
    xrd_start();
    Send_LCDData(0x55);

    Send_LCDData(x0>>8);
    Send_LCDData(x0);
    Send_LCDData(y0>>8);
    Send_LCDData(y0);
    
    while(*str)
        Send_LCDData(*str++);

    xrd_end();
}

void xrd_cnt1string(uint16_t x0, uint16_t y0, uint8_t cnt)
{
    char str[]="0";
    
    str[0]= cnt%10 + '0';
    str[1]= 0;
    xrd_32srting(x0,y0,str);     
}

void xrd_cnt2string(uint16_t x0, uint16_t y0, uint8_t cnt)
{
    char str[]="00";
    
    str[0]= cnt/10 + '0';
    str[1]= cnt%10 + '0';
    str[2]= 0;
    xrd_32srting(x0,y0,str);     
}

void xrd_cnt3string(uint16_t x0, uint16_t y0,uint16_t cnt)
{
    char str[]="000";
    
		str[0]= cnt/100 + '0';
    str[1]= (cnt/10)%10 + '0';
    str[2]= cnt%10 + '0';
    str[3]= 0;
    xrd_32srting(x0,y0,str);     
}
/*******************************************************************************
* Function Name  : void xrd_SetBColor(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
* Description    : 背景色填充
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void xrd_SetBColor(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    xrd_start();
		
    Send_LCDData(0x5A);
		Send_LCDData(x1/256);
		Send_LCDData(x1%256);
		Send_LCDData(y1/256);
		Send_LCDData(y1%256);
		Send_LCDData(x2/256);
		Send_LCDData(x2%256);
		Send_LCDData(y2/256);
		Send_LCDData(y2%256);
		
    xrd_end();
}
/*******************************************************************************
* Function Name  : void 	LCD_UpCarState(void)
* Description    : 上传小车编号
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	SetColor(void)
{
	//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x43);
	Send_LCDData(0x00);
	Send_LCDData(0x79);
	Send_LCDData(0x00);	
	Send_LCDData(0x0D);
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
}
/*******************************************************************************
* Function Name  : void 	LCD_UpCarState(void)
* Description    : 上传小车编号
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_UpCarState(uint16_t	MoveStation)
{
	if(MoveStation>999)	MoveStation=0;
	else;
	//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x00);
	Send_LCDData(0x72);
	Send_LCDData(0x00);	
	Send_LCDData(0x09);
	Send_LCDData(0x00);
	Send_LCDData(0xBA);
	Send_LCDData(0x00);
	Send_LCDData(0x2B);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
	
	//SetColor();
	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x00);
	Send_LCDData(0x7A);
	Send_LCDData(0x00);
	Send_LCDData(0x0A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0x30+	MoveStation/100);
	MoveStation%=100;
	Send_LCDData(0x30+	MoveStation/10);
	Send_LCDData(0x30+MoveStation%10);	
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
	
	//LCD_Cell(5);
}

/*******************************************************************************
* Function Name  : void 	LCD_RunState(void)
* Description    : 车运行状态
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_RunState(void)
{
	//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x01);
	Send_LCDData(0x34);
	Send_LCDData(0x00);	
	Send_LCDData(0x09);
	Send_LCDData(0x01);
	Send_LCDData(0x80);
	Send_LCDData(0x00);
	Send_LCDData(0x2B);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x01);
	Send_LCDData(0x36);
	Send_LCDData(0x00);
	Send_LCDData(0x0A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0xB9);
	Send_LCDData(0xA4);
	Send_LCDData(0xD7);	
	Send_LCDData(0xF7);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
}

/*******************************************************************************
* Function Name  : void 	LCD_FreeState(void)
* Description    : 车空闲状态
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_FreeState(void)
{
	//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x01);
	Send_LCDData(0x34);
	Send_LCDData(0x00);	
	Send_LCDData(0x09);
	Send_LCDData(0x01);
	Send_LCDData(0x80);
	Send_LCDData(0x00);
	Send_LCDData(0x2B);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
	
	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x01);
	Send_LCDData(0x36);
	Send_LCDData(0x00);
	Send_LCDData(0x0A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0xBF);
	Send_LCDData(0xD5);
	Send_LCDData(0xCF);	
	Send_LCDData(0xD0);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_FztOK(void)
* Description    : 防撞条状态
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_FztOK(void)
{
	//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x01);
	Send_LCDData(0xE6);
	Send_LCDData(0x00);	
	Send_LCDData(0x09);
	Send_LCDData(0x02);
	Send_LCDData(0x46);
	Send_LCDData(0x00);
	Send_LCDData(0x2B);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x01);
	Send_LCDData(0xEA);
	Send_LCDData(0x00);
	Send_LCDData(0x0A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0xD5);
	Send_LCDData(0xFD);
	Send_LCDData(0xB3);	
	Send_LCDData(0xA3);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_FztNG(void)
* Description    : 防撞条状态
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_FztNG(void)
{
	//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x01);
	Send_LCDData(0xE6);
	Send_LCDData(0x00);	
	Send_LCDData(0x09);
	Send_LCDData(0x02);
	Send_LCDData(0x46);
	Send_LCDData(0x00);
	Send_LCDData(0x2B);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x01);
	Send_LCDData(0xEA);
	Send_LCDData(0x00);
	Send_LCDData(0x0A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0xB1);
	Send_LCDData(0xA8);
	Send_LCDData(0xBE);	
	Send_LCDData(0xAF);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_ZawOK(void)
* Description    : 障碍物状态
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_ZawOK(void)
{
	//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x02);
	Send_LCDData(0xAD);
	Send_LCDData(0x00);	
	Send_LCDData(0x09);
	Send_LCDData(0x03);
	Send_LCDData(0x08);
	Send_LCDData(0x00);
	Send_LCDData(0x2B);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);

	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x02);
	Send_LCDData(0xB0);
	Send_LCDData(0x00);
	Send_LCDData(0x0A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0xD5);
	Send_LCDData(0xFD);
	Send_LCDData(0xB3);	
	Send_LCDData(0xA3);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_ZawOK(void)
* Description    : 障碍物状态
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_ZawNG(void)
{
	//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x02);
	Send_LCDData(0xAD);
	Send_LCDData(0x00);	
	Send_LCDData(0x09);
	Send_LCDData(0x03);
	Send_LCDData(0x08);
	Send_LCDData(0x00);
	Send_LCDData(0x2B);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x02);
	Send_LCDData(0xB0);
	Send_LCDData(0x00);
	Send_LCDData(0x0A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0xB1);
	Send_LCDData(0xA8);
	Send_LCDData(0xBE);	
	Send_LCDData(0xAF);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_ZawOK(void)
* Description    : 障碍物状态
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_WifiOK(void)
{
		//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x00);
	Send_LCDData(0x72);
	Send_LCDData(0x00);	
	Send_LCDData(0x3A);
	Send_LCDData(0x00);
	Send_LCDData(0xBE);
	Send_LCDData(0x00);
	Send_LCDData(0x5D);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x00);
	Send_LCDData(0x7A);
	Send_LCDData(0x00);
	Send_LCDData(0x3A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0xD5);
	Send_LCDData(0xFD);
	Send_LCDData(0xB3);	
	Send_LCDData(0xA3);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_ZawOK(void)
* Description    : 障碍物状态
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_WifiNG(void)
{
	//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x00);
	Send_LCDData(0x72);
	Send_LCDData(0x00);	
	Send_LCDData(0x3A);
	Send_LCDData(0x00);
	Send_LCDData(0xBE);
	Send_LCDData(0x00);
	Send_LCDData(0x5D);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x00);
	Send_LCDData(0x7A);
	Send_LCDData(0x00);
	Send_LCDData(0x3A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0xCA);
	Send_LCDData(0xA7);
	Send_LCDData(0xB0);	
	Send_LCDData(0xDC);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_ZawOK(void)
* Description    : 障碍物状态
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_CdhOK(void)
{
			//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x01);
	Send_LCDData(0x20);
	Send_LCDData(0x00);	
	Send_LCDData(0x3A);
	Send_LCDData(0x01);
	Send_LCDData(0x80);
	Send_LCDData(0x00);
	Send_LCDData(0x5D);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x01);
	Send_LCDData(0x28);
	Send_LCDData(0x00);
	Send_LCDData(0x3A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0xD5);
	Send_LCDData(0xFD);
	Send_LCDData(0xB3);	
	Send_LCDData(0xA3);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_ZawOK(void)
* Description    : 障碍物状态
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_CdhNG(void)
{
	//CELAR
	Send_LCDData(0xAA);	
	Send_LCDData(0x5B);
	Send_LCDData(0x01);
	Send_LCDData(0x20);
	Send_LCDData(0x00);	
	Send_LCDData(0x3A);
	Send_LCDData(0x01);
	Send_LCDData(0x80);
	Send_LCDData(0x00);
	Send_LCDData(0x5D);	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x98);
	Send_LCDData(0x01);
	Send_LCDData(0x28);
	Send_LCDData(0x00);
	Send_LCDData(0x3A);
	
	Send_LCDData(0x23);
	Send_LCDData(0x81);
	Send_LCDData(0x03);
	Send_LCDData(0xFF);
	Send_LCDData(0xFF);	
	Send_LCDData(0x00);
	Send_LCDData(0x1F);
	
	Send_LCDData(0xCD);
	Send_LCDData(0xD1);
	Send_LCDData(0xB9);	
	Send_LCDData(0xEC);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_MusicOK(void)
* Description    : 音乐确定
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_MusicNG(void)
{	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x71);
	Send_LCDData(0x00);
	Send_LCDData(0x03);
	Send_LCDData(0x00);
	Send_LCDData(0x59);
	
	Send_LCDData(0x01);
	Send_LCDData(0x81);
	Send_LCDData(0x00);
	Send_LCDData(0xB2);
	Send_LCDData(0x01);	
	Send_LCDData(0xB7);
	Send_LCDData(0x02);
	
	Send_LCDData(0xB3);
	Send_LCDData(0x00);
	Send_LCDData(0x6D);	
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_MusicOK(void)
* Description    : 音乐确定
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_MusicOK(void)
{	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x71);
	Send_LCDData(0x00);
	Send_LCDData(0x03);
	Send_LCDData(0x00);
	Send_LCDData(0xB2);
	
	Send_LCDData(0x00);
	Send_LCDData(0x00);
	Send_LCDData(0x01);
	Send_LCDData(0x0A);
	Send_LCDData(0x00);	
	Send_LCDData(0x36);
	Send_LCDData(0x02);
	
	Send_LCDData(0xB3);
	Send_LCDData(0x00);
	Send_LCDData(0x6D);	
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_MusicOK(void)
* Description    : 障碍物确定
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_ZawONNG(void)
{	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x71);
	Send_LCDData(0x00);
	Send_LCDData(0x03);
	Send_LCDData(0x00);
	Send_LCDData(0x59);
	
	Send_LCDData(0x00);
	Send_LCDData(0x37);
	Send_LCDData(0x00);
	Send_LCDData(0xB2);
	Send_LCDData(0x00);	
	Send_LCDData(0x6D);
	Send_LCDData(0x02);
	
	Send_LCDData(0xB3);
	Send_LCDData(0x00);
	Send_LCDData(0xB4);	
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}

/*******************************************************************************
* Function Name  : void 	LCD_MusicOK(void)
* Description    : 障碍物确定
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_ZawONOK(void)
{	
	Send_LCDData(0xAA);
	
	Send_LCDData(0x71);
	Send_LCDData(0x00);
	Send_LCDData(0x03);
	Send_LCDData(0x00);
	Send_LCDData(0x59);
	
	Send_LCDData(0x00);
	Send_LCDData(0x00);
	Send_LCDData(0x00);
	Send_LCDData(0xB2);
	Send_LCDData(0x00);	
	Send_LCDData(0x36);
	Send_LCDData(0x02);
	
	Send_LCDData(0xB3);
	Send_LCDData(0x00);
	Send_LCDData(0xB4);	
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}
/*******************************************************************************
* Function Name  : void 	LCD_InitView(void)
* Description    :
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_InitView(void)
{
//		LCD_UpCarState(AGVName);
//	
//		if(AgvState1.RunS)	LCD_RunState();
//		else								LCD_FreeState();
//		
//		if(Lcd_Wifi_Sucess)	LCD_WifiOK();				
//		else								LCD_WifiNG();
//		
//					
//		if(AgvState1.FztS)	LCD_FztOK();
//		else								LCD_FztNG();
//		
//		if(AgvState1.ZawS)	LCD_ZawOK();
//		else								LCD_ZawNG();
//		
//		if(AgvState1.CdhS)	LCD_CdhOK();
//		else								LCD_CdhNG();	
//		
//		LCD_MoveStation(SWTFlag);
//		
//		if(AgvState1.Music_ON)	LCD_MusicOK();
//		else										LCD_MusicNG();
//					
//		if(AgvState1.Zaw_ON)		LCD_ZawONOK();
//		else										LCD_ZawONNG();
//		
//		AgvState1Temp.RunS=AgvState1.RunS;
//		AgvState1Temp.FztS=AgvState1.FztS;
//		AgvState1Temp.ZawS=AgvState1.ZawS;
//		AgvState1Temp.CdhS=AgvState1.CdhS;
}

void 	LCD_MoveStation(uint16_t	MoveStation)
{
	if(MoveStation>999)	MoveStation=0;
	else;
	
	if(MoveStation>0)
	{
		//CELAR
		Send_LCDData(0xAA);	
		Send_LCDData(0x5B);
		Send_LCDData(0x01);
		Send_LCDData(0xE2);
		Send_LCDData(0x00);	
		Send_LCDData(0x3A);
		Send_LCDData(0x02);
		Send_LCDData(0x46);
		Send_LCDData(0x00);
		Send_LCDData(0x5D);	
		Send_LCDData(0xCC);
		Send_LCDData(0x33);
		Send_LCDData(0xC3);
		Send_LCDData(0x3C);
		
		Send_LCDData(0xAA);
		
		Send_LCDData(0x98);
		Send_LCDData(0x01);
		Send_LCDData(0xEA);
		Send_LCDData(0x00);
		Send_LCDData(0x3F);
		
		Send_LCDData(0x23);
		Send_LCDData(0x81);
		Send_LCDData(0x03);
		Send_LCDData(0xFF);
		Send_LCDData(0xFF);	
		Send_LCDData(0x00);
		Send_LCDData(0x1F);
		
		Send_LCDData(0x30+	MoveStation/100);
		MoveStation%=100;
		Send_LCDData(0x30+	MoveStation/10);
		Send_LCDData(0x30+MoveStation%10);	
		
		Send_LCDData(0xCC);
		Send_LCDData(0x33);
		Send_LCDData(0xC3);
		Send_LCDData(0x3C);
	}	
	else;
}

/*******************************************************************************
* Function Name  : void 	LCD_Cell( uint8_t	Vol)
* Description    : 电池电量显示
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_Cell(uint8_t	Vol)
{
	Send_LCDData(0xAA);	
	Send_LCDData(0x70);
	Send_LCDData(0x01);
	Send_LCDData(0x00);
	
	Send_LCDData(Vol+1);

	Send_LCDData(0x00);	
	Send_LCDData(0x50);
	Send_LCDData(0x00);
	Send_LCDData(0xE2);
	
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);	
}
/*******************************************************************************
* Function Name  : void 	LCD_PowerOnAndCharge(void)
* Description    : 开机状态，插入充电器
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_PowerOnAndCharge(void)
{
	Send_LCDData(0xAA);
	Send_LCDData(0x9A);
	Send_LCDData(0x00);
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
}

/*******************************************************************************
* Function Name  : void 	LCD_ChargeOver(void)
* Description    : 充电结束
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_ChargeOver(void)
{
	Send_LCDData(0xAA);
	Send_LCDData(0x9A);
	Send_LCDData(0xFF);
	Send_LCDData(0xCC);
	Send_LCDData(0x33);
	Send_LCDData(0xC3);
	Send_LCDData(0x3C);
}

/*******************************************************************************
* Function Name  : void 	LCD_Initial(void)
* Description    : 触摸屏显示界面初始化
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void 	LCD_Initial(void)
{
	SetColor();
	
	LCD_UpCarState(1);
	
	LCD_RunState();
	LCD_FreeState();
	
	LCD_FztOK();
	LCD_FztNG();
	
	LCD_ZawOK();
	LCD_ZawNG();
	
	LCD_WifiOK();
	LCD_WifiNG();
	
	LCD_CdhOK();
	LCD_CdhNG();
	
	LCD_MoveStation(1);
	
//	LCD_Cell(5);
//	LCD_Cell(4);
//	LCD_Cell(3);
//	LCD_Cell(2);
//	LCD_Cell(1);
//	LCD_Cell(0);
//	
//	LCD_PowerOnAndCharge();
//	LCD_ChargeOver();
}

/*******************************************************************************
* Function Name  : LcdReceiveJudge(void)
* Description    : LCD接收数据处理
* Input          : None  
* Output         : None
* Return         : None
*******************************************************************************/
void	LcdReceiveJudge(void)	
{
	
	if(Lcd_have_scmd)
	{		
		Lcd_have_scmd=0;	
		if((Lcd_Receive[1]==0x78)&&(Lcd_Receive[7]==0x3C))
		{//命令和帧尾正确
			if(Lcd_Receive[LcdDataPOs]==18)
			{//启动
				if((LCD_Start_Flag==0)&&(MoveFlag==0))
				{
				//当启动键未按下，且车子未运行时
				//u8TableWareStatus1 = GetTableware1Status();
				//u8TableWareStatus2 = GetTableware2Status();					
					//if (RunningMode == DILIEVRY_MEALS_MDOE && ((u8TableWareStatus1 == 0) || (u8TableWareStatus2 == 0)))
					if (RunningMode == DILIEVRY_MEALS_MDOE && ExistFood() == 1)
					{
						 LCD_Start_Flag=1;						
					}									
				}
				else
				{}
			}
			else	if(Lcd_Receive[LcdDataPOs]==19)
			{//停止			
						LCD_Start_Flag=0;						
			}
			
			else	if(Lcd_Receive[LcdDataPOs]==32)
			{//低速
				xrd_32srting(48,128,"低速");	
				u8SpeedLevel = LOW_SPEED;
				Speed_Increment = 0;
			}
			else	if(Lcd_Receive[LcdDataPOs]==33)
			{//中速
				xrd_32srting(48,128,"中速");	
				u8SpeedLevel = MID_SPEED;
				Speed_Increment = 0;
			}
			else	if(Lcd_Receive[LcdDataPOs]==34)
			{	
			//高速
				xrd_32srting(48,128,"高速");				
				u8SpeedLevel = HIG_SPEED;
				Speed_Increment = 0;
			}
			else	if(Lcd_Receive[LcdDataPOs]==35)
			{		
						//迎宾（默认）/送餐/跳舞
				RunningMode++;
				if (RunningMode > DIALOGUE_MODE) 
				{
						RunningMode = WELCOME_CUSTOMR_MODE;
				}
				
				switch (RunningMode)
				{				
						case WELCOME_CUSTOMR_MODE: xrd_32srting(308,416, "迎宾"); Remote_Flag = 0; break;
						case DILIEVRY_MEALS_MDOE: xrd_32srting(308,416, "送餐"); Remote_Flag = 0; break;
						case DANCE_MODE: xrd_32srting(308,416, "跳舞"); Remote_Flag = 1; break;
						case DIALOGUE_MODE: xrd_32srting(308, 416, "对话");	 Remote_Flag = 0; break;
						default: break;
				}	
				
				SetMode(RunningMode);
				Send_Data(PAD_USART, u8SendBuff, CMD_LEN);
				
				if (RunningMode == WELCOME_CUSTOMR_MODE || RunningMode == DIALOGUE_MODE) 
				{
							Music_Play_Slection(0, 0);	
							
				}
			}
			else	if(Lcd_Receive[LcdDataPOs]==36)
			{//桌号
			
				xrd_GetBColor(404,416);				//背景色取色
			}
			else
			{
				 KeyDeal(Lcd_Receive[LcdDataPOs]);
			}
		}
		else;	
	}
	else;
}


uint8_t		KeyInCount=0;					//记录输入次数
uint16_t	KeyInPutData=0;				//键盘输入值
void	KeyDeal(uint8_t	KeyData)
{
	if(KeyData==16)
	{
		//删除键
		if(KeyInCount>0)
		{			
			KeyInCount--;					//输入次数减1
			xrd_32srting(534,80,"   ");			//站点设置区清空显示
			if(KeyInPutData<10)
			{
				//个位数不处理
			}
			else	if(KeyInPutData<100)
			{
				//2位数处理
				KeyInPutData/=10;	//取10位数，变成个位数
				xrd_cnt1string(534,80,KeyInPutData);	//站点设置显示
			}
			else
			{
				//3位数处理
				KeyInPutData/=10;	//取前2位数
				xrd_cnt2string(534,80,KeyInPutData);	//站点设置显示
			}
		}
		else;
	}
	else	if(KeyData==17)
	{
		//确认键
		if(KeyInCount>0)
		{
			//有值输入
			KeyInCount=0;										//清输入次数
			xrd_32srting(534,80,"   ");			//站点设置区清空显示		
		
				SWTFlag=KeyInPutData;						//目标站点赋值
				xrd_cnt3string(700,80,SWTFlag);	//目标站点显示
				
				data32=SWTFlag;
				//Flash_Init(WriteFlash,TargetStation_Flash_Pos);		//保存目标站点
				OkStation=1;			
		}
		else;
	}
	else	if(KeyData<10)
	{
		//0到9的数字
		if(KeyInCount<3)
		{
			//未输满则处理
//			if((KeyInCount==0)&&(KeyData==0))
//			{

//				//第一次输入0，不处理
//			}
//			if(KeyInCount==0)
//			{
//				//第一次输入0，不处理
//			}
//			else
//			{
				KeyInCount++;	//输入次数累加
				xrd_32srting(534,80,"   ");						//站点设置区清空显示
				if(KeyInCount==1)
				{
					//个位数，直接赋值，并显示
					KeyInPutData=KeyData;	
					xrd_cnt1string(534,80,KeyInPutData);	//站点设置显示
				}
				else	if(KeyInCount==2)
				{
					//2位数，计算，先清空显示区，再显示2位数
					KeyInPutData=KeyInPutData*10+KeyData;	
					xrd_cnt2string(534,80,KeyInPutData);	//站点设置显示
				}	
				else	
				{
					//3位数，计算，先清空显示区，再显示2位数
					KeyInPutData=KeyInPutData*10+KeyData;	
					xrd_cnt3string(534,80,KeyInPutData);	//站点设置显示						
				}
			//}
		}
		else;
	}
	else;
}


void LCD_InitialView_Configuration(void)
{
	delay_ms(1000);
	//uxrd_LcdClear();								//清屏
	//xrd_picture(1);								//显示图片1
	xrd_SetColor(0xffff,0x001f);		//设置前后背景色，前景色为白色
	//xrd_SetBColor(0,0,800,480);		//背景色填充
	//xrd_SetBuzzer(1);							//蜂鸣器响10mS 
	xrd_SetBacLed(50);							//调节背光亮度
	//xrd_SetHms(15,9,18,11,23,30);	//用8421BCD码表示
	xrd_GetBColor(0,0);							//背景色取色
	//xrd_32srting(8,0,"公司");
	//xrd_cnt3string(11,40,1);				//机器人编号显示
	xrd_32srting(340,0,"001");	//机器人编号显示
	xrd_32srting(40,0, "郑州慧腾机器人");
	
	xrd_SetColor(0x001f,0x001f);		//设置前后背景色，前景色为白色
	xrd_SetClock(00,04,0xffff,650,0);
	
	#if 1
	xrd_SetColor(0x0000,0x001f);		//设置前后背景色，前景色为黑色	
	xrd_juxingkuang(575,4,625,28);	//前景色画矩形框,画外框
	xrd_juxingkuang(579,8,621,24);	//前景色画矩形框,画内框
	xrd_juxingkuang(625,9,632,23);	//前景色画矩形框,画侧框
	
	xrd_SetColor(0xffff,0x001f);		//设置前后背景色，前景色为白色
	xrd_juxingkuang(577,6,623,26);	//前景色画矩形框,白色画外框
	//xrd_juxingkuang(627,11,630,21);	//前景色画矩形框
	
	xrd_FrontFill(580,9,620,23);
	xrd_FrontFill(627,11,630,21);
	#endif

	
	xrd_cnt3string(700,80,SWTFlag);//目标站点显示，默认0
 
  
	xrd_32srting(308,416,"迎宾");	
	xrd_GetBColor(404,416);			//背景色取色
	
	xrd_32srting(404,416,"桌号");
	xrd_GetBColor(0,0);						//背景色取色
	


}

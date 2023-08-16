#include "BasicFun.h"
#include "uart.h"
#include "key.h"
#include "DHT11.h"
#include "LCD1602.h"
#include "oled.h"
#include "15AD.h"

#define u8 unsigned char
#define u16 unsigned int

extern u8 is_hongwai_key01;
extern u8 is_hongwai_key02;
extern u8 is_hongwai_key03;

extern bit busy;
//extern sbit SCL=P2^2;
//extern sbit SDA=P2^3;


sbit BEEP = P2^4;	//蜂鸣器

//按键123
sbit KEY01 = P3^5;
sbit KEY02 = P3^6;
sbit KEY03 = P3^7;

//数据包接收数组
u16 CO2_Value = 0;
u16  Tvoc  , Tmplate, Hum ;
u16 PM25 = 0;
u8 change_mode = 0;
u8 send_flag = 0;

u16 warn_buffer[4]={30,30,30,80};

#define BUFFER_MAX 50
u8 data_buffer[BUFFER_MAX] = "";

u8 Key_Scan()
{
	u8 key_value = 0;
//	if(KEY01==0)
//	{
//		delay_ms(15);//@11.0592MHz
//		if(KEY01==0)
//		{
//			key_value = 1;
//			while(!KEY01);
//		}
//	}
//	if(KEY02==0)
//	{
//		delay_ms(15);//@11.0592MHz
//		if(KEY02==0)
//		{
//			key_value = 2;
//			while(!KEY02);
//		}
//	}
//	if(KEY03==0)
//	{
//		delay_ms(15);//@11.0592MHz
//		if(KEY03==0)
//		{
//			key_value = 3;
//			while(!KEY03);
//		}
//	}

	return key_value;
}


void main()
{
	u8 key_value = 0,i=0;
	Timer0Init();
	Uart01_Init();
	Uart02_Init();
	Uart03_Init();
	Uart04_Init();
	OLED_Init();
	LCD_Init();

	while (1)
	{
		
		CO2Devide_DataPacket(&CO2_Value);	//CO2串口读取
		TVOCDevide_DataPacket(&Tvoc,&Tmplate,&Hum);	//TVOC,温度，湿度

		key_value = Key_Scan();	//按键扫描

		if(is_hongwai_key01 || key_value == 1)
		{	
			is_hongwai_key01 = 0;
			change_mode = (change_mode+1)%4;
		}


		if(is_hongwai_key02 || key_value == 2)
		{	
			is_hongwai_key02 = 0;
			warn_buffer[change_mode] ++;

		}
		if(is_hongwai_key03 || key_value == 3)
		{	
			is_hongwai_key03 = 0;
			warn_buffer[change_mode] --;
		}	
		
		memset(data_buffer,0,BUFFER_MAX);
		sprintf(data_buffer,"%u-%u-%u-%u-%u-%u-%u-%u",
						CO2_Value,warn_buffer[0],
						Tvoc,warn_buffer[1],
						Tmplate,warn_buffer[2],
						Hum,warn_buffer[3]);

		Uart01_SendByte(0x2C);	//数据开始帧
		Uart01_SendString(data_buffer);
		Uart01_SendByte(0x60);	//数据结束帧
	}
}



void Timer0_Routine() interrupt 1 // 1ms低优先级定时器0
{
	static u8 conut_device = 0;
	static u16 count_ms = 0;
	conut_device++;
	count_ms++;
	
	if(count_ms == 1000)
	{
		send_flag = 1;
	}
}




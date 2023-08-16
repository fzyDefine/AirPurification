#include <STC15.H>
#include <STDLIB.H>
#include <STRING.H>
#include <stdio.h>
#include "Delay.h"
#include "UART.h"
#include "LCD1602.h"
#include "Timer0.h"
#include <15AD.h>

#define u8 unsigned char
#define u16 unsigned int

sbit REALAY01 = P2^0;
sbit REALAY02 = P2^1;
sbit REALAY03 = P2^2;

sbit BEEP = P2^6;
sbit LED = P2^7;

sbit KEY1 = P3^5;

u16 CO2_Value,warn_CO2,Tvoc,warn_Tvoc,Tmplate,warn_Tmplate,Hum,warn_Hum;
u16 PM25,PM25_Warn = 100;

bit uart_send_flag = 0;

u8 mode = 0;

void ShowCO2_TVOC()
{
	LCD_ShowString(1,1,"CO2:");LCD_ShowNum(1,5,CO2_Value,3);
	LCD_ShowString(1,10,"BJ:");LCD_ShowNum(1,13,warn_CO2,3);

	LCD_ShowString(2,1,"TVC:");LCD_ShowNum(2,5,Tvoc,3);
	LCD_ShowString(2,10,"BJ:");LCD_ShowNum(2,13,warn_Tvoc,3);
}

void ShowTmp_Hum()
{
	LCD_ShowString(1,1,"Tmp:");LCD_ShowNum(1,5,Tmplate,3);
	LCD_ShowString(1,10,"BJ:");LCD_ShowNum(1,13,warn_Tmplate,3);

	LCD_ShowString(2,1,"Hum:");LCD_ShowNum(2,5,Hum,3);
	LCD_ShowString(2,10,"BJ:");LCD_ShowNum(2,13,warn_Hum,3);
}

void ShowHum()
{
	LCD_ShowString(1,1,"P25:");LCD_ShowNum(1,5,PM25,3);
	LCD_ShowString(1,10,"BJ:");LCD_ShowNum(1,13,PM25_Warn,3);

	LCD_ShowString(2,1,"-------  ------ ");
}

void SendBlue()
{
	char buffer[70] = "";
	sprintf(buffer,"CO2=%u,TVOC=%u,Tmp=%u\r\nHum=%u,P25=%u\r\n",CO2_Value,Tvoc,Tmplate,Hum,PM25);
	UART01_SendString(buffer);

}

u8 Key_scan()
{
	u8 key_value = 0;
	if(KEY1==0)
	{
		Delay_ms(20);
		if(KEY1==0)
		{
			key_value = 1;
		}
		while(!KEY1);
	}

	return key_value;
}	


void main()
{
	unsigned char i = 0;
	unsigned char key_v = 0;

	LCD_Init();
	adc_init();//AD功能初始化
	Timer0_Init();
	UART01_Init();
	Uart02_Init();

	BEEP = 1;
	LED = 0;
	
	while(1)
	{
		key_v = Key_scan();
		if(key_v)
			mode = (mode+1)%3;

		if(uart_send_flag)
		{
		
			Devide_DataPacket(&CO2_Value,&warn_CO2,&Tvoc,
				&warn_Tvoc,&Tmplate,&warn_Tmplate,&Hum,&warn_Hum);

			PM25 = get_adc0();

			Tmplate = Tmplate/10 - 7;
			Hum /= 10;
			CO2_Value = CO2_Value*100/2000;
			Tvoc = Tvoc/ 10;

			SendBlue();

			uart_send_flag = 0;
		}

		if( Tmplate> warn_Tmplate || CO2_Value>warn_CO2 )
		{
			LED = 1;
			BEEP = 0;
		}
		else
		{
			LED = 0;
			BEEP = 1;
		}

		


		if(CO2_Value>warn_CO2 || Tvoc>warn_Tvoc)	//环境不好
		{
			REALAY01 = 1;
		}
		else
			REALAY01 = 0;

		if( Tmplate > warn_Tmplate )
		{
			REALAY02 = 1;
		}
		else
			REALAY02 = 0;

		if( Hum > warn_Hum )
		{
			REALAY03 = 1;
		}
		else
			REALAY03 = 0;


		if(mode == 0)
		{
			ShowCO2_TVOC();
		}
		if(mode == 1)
		{
			ShowTmp_Hum();
		}
		if(mode == 2)
		{
			ShowHum();
		}
	}	
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		uart_send_flag = 1;
	}
}








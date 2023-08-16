#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gps.h"
#include "LCD1602.h"

_SaveData Save_Data;

void clrStruct()
{
	Save_Data.isGetData = false;
	Save_Data.isParseData = false;
	Save_Data.isUsefull = false;
	memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //清空
	memset(Save_Data.UTCTime, 0, UTCTime_Length);
	memset(Save_Data.latitude, 0, latitude_Length);
	memset(Save_Data.N_S, 0, N_S_Length);
	memset(Save_Data.longitude, 0, longitude_Length);
	memset(Save_Data.E_W, 0, E_W_Length);
	
}

/**
	recbuffer是传递的数组地址
*/
void Rec_LngLat(u8 *recbuffer,u8 _size)
{
	memset(recbuffer,0,_size);
	sprintf(recbuffer,"UTCTime:%s\r\n%s%s\r\n%s%s",Save_Data.UTCTime,Save_Data.latitude,Save_Data.N_S,Save_Data.longitude,Save_Data.E_W);
}



void errorLog(int num)
{
	
	while (1)
	{
	  	UART01_SendString("ERROR");
		UART01_SendByte(num+0x30);
		UART01_SendString("\r\n");
	}
}

void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
		UART01_SendString("**************\r\n");
		UART01_SendString(Save_Data.GPS_Buffer);

		
		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//解析错误
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//获取UTC时间
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//获取UTC时间
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//获取纬度信息
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//获取N/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//获取经度信息
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//获取E/W

						default:break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;

				}
				else
				{
					errorLog(2);	//解析错误
				}
			}


		}
	}
}

void printGpsBuffer()
{
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		
		UART01_SendString("Save_Data.UTCTime = ");
		UART01_SendString(Save_Data.UTCTime);
		UART01_SendString("\r\n");

		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			UART01_SendString("Save_Data.latitude = ");
			UART01_SendString(Save_Data.latitude);
			UART01_SendString("\r\n");


			UART01_SendString("Save_Data.N_S = ");
			UART01_SendString(Save_Data.N_S);
			UART01_SendString("\r\n");

			UART01_SendString("Save_Data.longitude = ");
			UART01_SendString(Save_Data.longitude);
			UART01_SendString("\r\n");

			UART01_SendString("Save_Data.E_W = ");
			UART01_SendString(Save_Data.E_W);
			UART01_SendString("\r\n");
		}
		else
		{
			UART01_SendString("GPS DATA is not usefull!\r\n");
		}
		
	}
}


#ifndef __GPS_H__
#define __GPS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delay.h"
#include "gps.h"
#include <STC15F2K60S2.H>

#define false 0
#define true 1

#define UART_MAX 50
#define Uart01_SendData UART01_SendByte
#define u8 unsigned char
#define u16 unsigned int

extern void UART01_Init();
extern void UART01_SendString(unsigned char *p);
extern void UART01_SendByte(unsigned char c);

extern void Uart02_Init();
extern void Uart02_SendData(unsigned char dat);
extern void Uart02_SendString(char *s);

extern void Clean_Uart02Buffer();

extern char idata gpsRxBuffer[gpsRxBufferLength];
extern unsigned char RX_Count;

extern void Devide_DataPacket(u16 *rec_1,u16 *rec_2,u16 *rec_3,
u16 *rec_4,u16 *rec_5,u16 *rec_6,u16 *rec_7,u16 *rec_8);

#endif
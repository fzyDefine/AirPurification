#ifndef __UART_H_
#include "BasicFun.h"



void Uart01_Init(void);
void Uart01_SendByte(u8 _data);
void Uart01_SendString(u8 *str);

void Uart02_Init();
void Uart02_SendData(unsigned char dat);
void Uart02_SendString(char *s);

void Uart03_Init(void);
void Uart03_SendData(unsigned char dat);
void Uart03_SendString(char *s);

void Uart04_Init(void);
void Uart04_SendData(unsigned char dat);
void Uart04_SendString(char *s);

void CO2Devide_DataPacket(u16 *rec_value);
void TVOCDevide_DataPacket(u16 *tvoc,u16 *tmp,u16 *hum);
#endif // !__UART_H_




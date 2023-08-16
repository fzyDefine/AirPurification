#ifndef __IIC_H_
#define __IIC_H_
#include "BasicFun.h"

#define IIC_SCL P20
#define IIC_SDA P21

void IIC_Start();
void IIC_Stop();

void IIC_SendByte(u8 byte);
u8 IIC_ReceiveByte();

void IIC_SendAck(u8 ack_bit);
u8 IIC_ReceiveAck();

#endif
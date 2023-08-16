#include "IIC.h"

#define DELAY_TIME 5

sbit SDA = P2^1;  
sbit SCL = P2^0;  

void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}

//起始条件：SCL高电平期间，SDA从高电平切换到低电平
void IIC_Start()
{
    SDA = 1;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 0;
    IIC_Delay(DELAY_TIME);
    SCL = 0;	
}

//终止条件：SCL高电平期间，SDA从低电平切换到高电平
void IIC_Stop()
{
    SDA = 0;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

/**
 * @brief 发送一个字节：
    SCL低电平期间，主机将数据位依次放到SDA线上（高位在前）
    然后拉高SCL，从机将在SCL高电平期间读取数据位，
    所以SCL高电平期间SDA不允许有数据变化，
    依次循环上述过程8次，即可发送一个字节
 *
 * @param byte 传入的字
 */
void IIC_SendByte(u8 byte)
{
    unsigned char i;

    for(i=0; i<8; i++)
    {
        SCL  = 0;
        IIC_Delay(DELAY_TIME);
        if(byte & 0x80) SDA  = 1;
        else SDA  = 0;
        IIC_Delay(DELAY_TIME);
        SCL = 1;
        byte <<= 1;
        IIC_Delay(DELAY_TIME);
    }
    SCL  = 0;  
}

/**
 * @brief 接收一个字节：
    SCL低电平期间，从机将数据位依次放到SDA线上（高位在前）
    然后拉高SCL，主机将在SCL高电平期间读取数据位
    所以SCL高电平期间SDA不允许有数据变化
    依次循环上述过程8次即可接收一个字节（主机在接收之前，需要释放SDA）
 *
 * @return byte
 */
u8 IIC_ReceiveByte()
{
    unsigned char i, da;
    for(i=0; i<8; i++)
    {   
    	SCL = 1;
	IIC_Delay(DELAY_TIME);
	da <<= 1;
	if(SDA) da |= 1;
	SCL = 0;
	IIC_Delay(DELAY_TIME);
    }
    return da;  
}

/**
 * @brief 发送应答：
    在接收完一个字节之后，主机在下一个时钟发送一位数据，
    数据0表示应答，数据1表示非应答
 *
 * @param ack_bit 0为发送应答，1不发送应答
 */
void IIC_SendAck(u8 ack_bit)
{
    SCL = 0;
    SDA = ack_bit;  					// 0为发送应答，1不发送应答
    IIC_Delay(DELAY_TIME);
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

/**
 * @brief 接收应答：
    在发送完一个字节之后，主机在下一个时钟接收一位数据
    判断从机是否应答
    数据0表示应答，数据1表示非应答（主机在接收之前，需要释放SDA）
    
 * @return 1无应答,0有应答
 */
u8 IIC_ReceiveAck()
{
    bit ackbit;
	
    SCL  = 1;
    IIC_Delay(DELAY_TIME);
    ackbit = SDA;
    SCL = 0;
    IIC_Delay(DELAY_TIME);
    return ackbit;
}
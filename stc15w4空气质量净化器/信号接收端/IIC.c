#include "IIC.h"

#define DELAY_TIME 5

sbit SDA = P2^1;  
sbit SCL = P2^0;  

void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}

//��ʼ������SCL�ߵ�ƽ�ڼ䣬SDA�Ӹߵ�ƽ�л����͵�ƽ
void IIC_Start()
{
    SDA = 1;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 0;
    IIC_Delay(DELAY_TIME);
    SCL = 0;	
}

//��ֹ������SCL�ߵ�ƽ�ڼ䣬SDA�ӵ͵�ƽ�л����ߵ�ƽ
void IIC_Stop()
{
    SDA = 0;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

/**
 * @brief ����һ���ֽڣ�
    SCL�͵�ƽ�ڼ䣬����������λ���ηŵ�SDA���ϣ���λ��ǰ��
    Ȼ������SCL���ӻ�����SCL�ߵ�ƽ�ڼ��ȡ����λ��
    ����SCL�ߵ�ƽ�ڼ�SDA�����������ݱ仯��
    ����ѭ����������8�Σ����ɷ���һ���ֽ�
 *
 * @param byte �������
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
 * @brief ����һ���ֽڣ�
    SCL�͵�ƽ�ڼ䣬�ӻ�������λ���ηŵ�SDA���ϣ���λ��ǰ��
    Ȼ������SCL����������SCL�ߵ�ƽ�ڼ��ȡ����λ
    ����SCL�ߵ�ƽ�ڼ�SDA�����������ݱ仯
    ����ѭ����������8�μ��ɽ���һ���ֽڣ������ڽ���֮ǰ����Ҫ�ͷ�SDA��
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
 * @brief ����Ӧ��
    �ڽ�����һ���ֽ�֮����������һ��ʱ�ӷ���һλ���ݣ�
    ����0��ʾӦ������1��ʾ��Ӧ��
 *
 * @param ack_bit 0Ϊ����Ӧ��1������Ӧ��
 */
void IIC_SendAck(u8 ack_bit)
{
    SCL = 0;
    SDA = ack_bit;  					// 0Ϊ����Ӧ��1������Ӧ��
    IIC_Delay(DELAY_TIME);
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

/**
 * @brief ����Ӧ��
    �ڷ�����һ���ֽ�֮����������һ��ʱ�ӽ���һλ����
    �жϴӻ��Ƿ�Ӧ��
    ����0��ʾӦ������1��ʾ��Ӧ�������ڽ���֮ǰ����Ҫ�ͷ�SDA��
    
 * @return 1��Ӧ��,0��Ӧ��
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
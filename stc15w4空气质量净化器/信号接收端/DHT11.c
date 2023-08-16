#include "DHT11.h"

void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 216;
	j = 37;
	do
	{
		while (--j);
	} while (--i);
}

void Delay50us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 135;
	while (--i);
}

void Delay33us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 88;
	while (--i);
}

void DHT11_Start()
{
    dht = 1;
    dht = 0;
    Delay20ms();
    dht = 1;
    Delay50us();
    if(dht == 0)
    {
        //检测到响应信号
        while (!dht);
        while (dht);
    }
    else{

    }
}

u8 DHT11_ReadByte()
{
    u8 flag,i;
    u8 value = 0;
    for(i = 0;i<8;i++)
    {
        while(!dht);    //跳过起始位的50us
        Delay33us();
        if(dht == 1)
        {
            flag = 1;
            while (dht);  
        }
        else{
            flag = 0;
        }
        value <<= 1;    //左移一位
        value |= flag;  //给最低位赋值
    }

    return value;
}

float DHT11_Get_Humidity()
{
    u8 DHT_U8= 0;
    float DHT_FL = 0;


    DHT11_Start();
    DHT_U8 = DHT11_ReadByte();
    DHT_FL = DHT11_ReadByte() / 100.0;
    return DHT_U8 + DHT_FL;
}
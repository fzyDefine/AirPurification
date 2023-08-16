#include "uart.h"
#include <stdlib.h>

#define u8 unsigned char
#define u16 unsigned int

u8 is_hongwai_key01 = 0;
u8 is_hongwai_key02 = 0;
u8 is_hongwai_key03 = 0;

bit busy;
bit busy_uart3;
bit busy_uart4;

u8 rec_buf[10];
u8 rec_buf2[10];

//CO2接包函数
void CO2Rec_DataPacket(u8 _data)
{
	static u8 i = 0;
	static u8 tmp_buffer[10] = "";

	tmp_buffer[i++] = _data;	

	if ( i==1 && tmp_buffer[0]!=0X2C)	//没收到包头,重新接收
	{
		i = 0;	//下标i复位
		memset(tmp_buffer,0,10);	//释放临时数组
		return;
	}

	if( i>=6 )
	{

		memcpy(rec_buf,tmp_buffer,10);	//拷贝到目标数组
		memset(tmp_buffer,0,10);	//释放临时数组
		i = 0;	//下标i复位

	}
	
}

void CO2Devide_DataPacket(u16 *rec_value)
{
	if(rec_buf[0] == 0)	//如果数据包是空的则返回
	{
		return ;
	}

	*rec_value = rec_buf[1]*256+rec_buf[2];
}


//tvoc接包函数
void TVOCRec_DataPacket(u8 _data)
{
	static u8 i = 0;
	static u8 tmp_buffer[10] = "";

	tmp_buffer[i++] = _data;	

	if ( i==1 && tmp_buffer[0]!=0X2C)	//没收到包头,重新接收
	{
		i = 0;	//下标i复位
		memset(tmp_buffer,0,10);	//释放临时数组
		return;
	}

	if( i>=8 )		//接收完所有数据
	{

		memcpy(rec_buf2,tmp_buffer,10);	//拷贝到目标数组
		memset(tmp_buffer,0,10);	//释放临时数组
		i = 0;	//下标i复位

	}
	
}

//tvoc拆包函数
void TVOCDevide_DataPacket(u16 *tvoc,u16 *tmp,u16 *hum)
{
	if(rec_buf2[0] == 0)	//如果数据包是空的则返回
	{
		return ;
	}

	*tvoc = rec_buf2[1]*256+rec_buf2[2];
	*tmp = rec_buf2[3]*256+rec_buf2[4];
	*hum = rec_buf2[5]*256+rec_buf2[6];
}

void Uart01_Init(void)		//9600bps@11.0592MHz
{

	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xE8;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时

    ES = 1;
    EA = 1;     //开启定时器
}

void Uart01_SendByte(u8 _data)
{
    SBUF = _data;
    while(TI == 0);
    TI = 0;
}

void Uart01_SendString(u8 *str)
{
	while(*str !='\0')		
		Uart01_SendByte(*str++);
}



void Uart02_Init()		//9600bps  11.0592mhz
{
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0xE0;		//设置定时初始值
	T2H = 0xFE;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时

    IE2 &= 0xFE;   //先对需要设置的位进行清零 1111 1110
    IE2 |= 0x01;   // | ESPI | ES2 允许UART2中断
    EA = 1;        //允许总中断

	P_SW2 &=~ 0X01;	//选择 P10RX P11TX
}


void Uart02_SendData(unsigned char dat)
{
    while (busy); // 等待前面的数据发送完成
    busy = 1;
    S2BUF = dat; // 写数据到UART2数据寄存器
}


void Uart02_SendString(char *s)
{
    while (*s) // 检测字符串结束标志
    {
        Uart02_SendData(*s++); // 发送当前字符
    }
}

void Uart03_Init(void)		//9600bps@11.0592MHz
{
	S3CON = 0x10;		//8位数据,可变波特率
	S3CON &= 0xBF;		//串口3选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0xE0;		//设置定时初始值
	T2H = 0xFE;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时

    IE2 &= ~0x08;   //先对需要设置的位进行清零 
    IE2 |= 0x08;   //允许串口三中断
    EA = 1;        //允许总中断

	P_SW2 &=~ 0X02;	//选择 P00RX P01TX
}

void Uart03_SendData(unsigned char dat)
{
    while (busy); // 等待前面的数据发送完成
    busy_uart3 = 1;
    S3BUF = dat; // 写数据到UART2数据寄存器
}


void Uart03_SendString(char *s)
{
    while (*s) // 检测字符串结束标志
    {
        Uart03_SendData(*s++); // 发送当前字符
    }
}


void Uart04_Init(void)		//9600bps@11.0592MHz
{
	S4CON = 0x10;		//8位数据,可变波特率
	S4CON &= 0xBF;		//串口4选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0xE0;		//设置定时初始值
	T2H = 0xFE;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时

    IE2 &= ~0x10;   //先对需要设置的位进行清零 
    IE2 |= 0x10;   //允许串口三中断
    EA = 1;        //允许总中断

	P_SW2 &=~ 0X04;	//选择 P02RX P03TX
}

void Uart04_SendData(unsigned char dat)
{
    while (busy); // 等待前面的数据发送完成
    busy_uart4 = 1;
    S4BUF = dat; // 写数据到UART2数据寄存器
}


void Uart04_SendString(char *s)
{
    while (*s) // 检测字符串结束标志
    {
        Uart04_SendData(*s++); // 发送当前字符
    }
}


/***********************串口中断服务函数***********************/




void Uart01_Routine() interrupt 4
{
	u8 uart_data; //串口收到的数据
    if(RI == 1)
    {
        RI = 0;
        uart_data = SBUF;
		// Uart01_SendByte(uart_data);


    }
}

void Uart02_Routine() interrupt 8 using 2
{
    unsigned char mydata;
    if(S2CON & 0x01)          //如果是接收中断
    {
        S2CON &= 0xFE;       //接收中断标志位清0  
        mydata = S2BUF;      //将接收缓冲区的数据保存到mydata变量中
		TVOCRec_DataPacket(mydata);
    }

	if(S2CON & 0x02)          //如果是发送中断
    {
        S2CON &= 0xFD;       //发送中断标志清0  
		busy = 0;
    }

}


void Uart03_Routine() interrupt 17
{
    unsigned char mydata;
    if(S3CON & 0x01)          //如果是接收中断
    {
        S3CON &= 0xFE;       //接收中断标志位清0  
        mydata = S3BUF;      //将接收缓冲区的数据保存到mydata变量中
		CO2Rec_DataPacket(mydata);
    }

	if(S3CON & 0x02)          //如果是发送中断
    {
        S3CON &= 0xFD;       //发送中断标志清0  
		busy_uart3 = 0;
    }

}

void Uart04_Routine() interrupt 18
{
    unsigned char mydata;
    if(S4CON & 0x01)          //如果是接收中断
    {
        S4CON &= 0xFE;       //接收中断标志位清0  
        mydata = S4BUF;      //将接收缓冲区的数据保存到mydata变量中
		

		if( mydata == 0x0C)
			is_hongwai_key01 = 1;
		if( mydata == 0x18)
			is_hongwai_key02 = 1;
		if( mydata == 0x5E)
			is_hongwai_key03 = 1;

    }

	if(S4CON & 0x02)          //如果是发送中断
    {
        S4CON &= 0xFD;       //发送中断标志清0  
		busy_uart4 = 0;
    }

}



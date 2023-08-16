#include "uart.h"

#define BUFFER_MAX 50

unsigned char RX_Count = 0;

bit busy;
char rec_buf[BUFFER_MAX+2];

void Rec_DataPacket(u8 _data)
{
	static u8 i = 0;
	static u8 tmp_buffer[BUFFER_MAX+2] = "";

	tmp_buffer[i++] = _data;	

	if ( i==1 && tmp_buffer[0]!=0X2C)	//没收到包头,重新接收
	{
		i = 0;	//下标i复位
		memset(tmp_buffer,0,BUFFER_MAX+2);	//释放临时数组
		return;
	}

	if( i>= BUFFER_MAX+2 ||  _data == 0X60)	//超界或者接收到结束标识
	{
		tmp_buffer[i-1] = '\0' ;	//替换结束标志
		memcpy(rec_buf,tmp_buffer,BUFFER_MAX+2);	//拷贝到目标数组
		memset(tmp_buffer,0,BUFFER_MAX+2);	//释放临时数组
		i = 0;	//下标i复位

	}
	
}

void Devide_DataPacket(u16 *rec_1,u16 *rec_2,u16 *rec_3,u16 *rec_4,u16 *rec_5,u16 *rec_6,u16 *rec_7,u16 *rec_8)
{
	char *token = NULL;
	if(rec_buf[0] == 0)	//如果数据包是空的则返回
	{
		return ;
	}
	
	token = strtok(&rec_buf[1], "-");
	*rec_1 = atoi(token);
	token = strtok(NULL, "-");
    *rec_2 = atoi(token);
	token = strtok(NULL, "-");
    *rec_3 = atoi(token);
	token = strtok(NULL, "-");
    *rec_4 = atoi(token);
	token = strtok(NULL, "-");
    *rec_5 = atoi(token);
	token = strtok(NULL, "-");
    *rec_6 = atoi(token);
	token = strtok(NULL, "-");
    *rec_7 = atoi(token);
	token = strtok(NULL, "-");
    *rec_8 = atoi(token);

}


void UART01_Init(void)		//9600bps@11.0592MHz
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

void UART01_SendString(unsigned char *str)				//发送字符串
{	
	while(*str !='\0')		
		UART01_SendByte(*str++);	

}

void UART01_SendByte(unsigned char c)				//发送一个字符
{ 
    TI=0;   
    SBUF=c;   
    while(TI==0);   
    TI=0;   
}


void Uart01_Routine(void) interrupt 4 using 3	  		
{ 
	unsigned char temp = 0;
	char i = 0;
	
	if(RI == 1)
	{
		RI = 0;
		Rec_DataPacket(SBUF);
	}
	
}



void Uart02_Init()		//9600bps
{
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0xE8;		//设置定时初始值
	T2H = 0xFF;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时

    IE2 &= 0xFE;   //先对需要设置的位进行清零 1111 1110
    IE2 |= 0x01;   // | ESPI | ES2 允许UART2中断
    EA = 1;        //允许总中断

	P_SW2 &=~ 0X01;	//选择 P10RX P11TX
}

/***********发送*********/
void Uart02_SendData(unsigned char dat)
{
    while (busy); // 等待前面的数据发送完成
    busy = 1;
    S2BUF = dat; // 写数据到UART2数据寄存器
}

/************发送字符串*******************/
void Uart02_SendString(char *s)
{
    while (*s) // 检测字符串结束标志
    {
        Uart02_SendData(*s++); // 发送当前字符
    }
}

void Uart02_Routine() interrupt 8 using 2
{
    unsigned char mydata;
    if(S2CON & 0x01)          //如果是接收中断
    {
        S2CON &= 0xFE;       //接收中断标志位清0  
        mydata = S2BUF;      //将接收缓冲区的数据保存到mydata变量中



    }

	if(S2CON & 0x02)          //如果是发送中断
    {
        S2CON &= 0xFD;       //发送中断标志清0  
		busy = 0;
    }

}























#include "BasicFun.h"

void Timer0Init(void)	//1毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初始值
	TH0 = 0xD4;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时

    ET0 = 1; // 允许定时器0中断
    EA  = 1;  // 中断的总开关
}

void Timer1Init(void)	// 100us定时器,数码管扫描专供
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xAE;		//设置定时初始值
	TH1 = 0xFB;		//设置定时初始值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时	

    ET1 = 1; // 允许定时器1中断
    EA = 1;  // 中断的总开关
}

/*定时器0中断函数模板
void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count;
    TL0 = 0x66; //设置定时初始值
    TH0 = 0xFC; //设置定时初始值
    T0Count++;
    if(T0Count>=1000)
    {
        T0Count=0;

    }
}
*/

/*定时器1中断函数模板
void Timer1_Routine() interrupt 3
{
    static unsigned int T0Count;

    T0Count++;
    if(T0Count>=1000)
    {
        T0Count=0;

    }
}
*/
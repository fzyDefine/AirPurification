#include "BasicFun.h"

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void delay_ms(u16 n_ms) //@11.0592MHz
{
	u16 i = 0;
	for(i=0;i<n_ms;i++)
	{
		Delay1ms();
	}
}
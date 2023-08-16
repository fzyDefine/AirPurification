#include <reg51.h>
#include <intrins.h>
#include <15AD.h>
#define nop _nop_()//延时
#define ADC_POWER 0x80//开电源
#define ADC_START 0x08//AD转换启动控制。
#define ADC_FLAG  0x10//AD转换结束标志
#define ADC_SPEEDH 0x40//转换速度为180个时钟周期
#define ADRJ 0X20  //ADRJ=1
//#define AD_P1_0 0x02 //P1.0为AD输出
//#define AD_P1_1 0x03 //P1.1为AD输出
sfr ADC_CONTR = 0Xbc;//命名ADC控制寄存器
sfr ADC_CONTR0 = 0Xbc;//命名ADC控制寄存器
sfr ADC_RES = 0Xbd;//命名数据高位
sfr ADC_RESL = 0Xbe;//命名数据低位
sfr P1ASF=0X9D;//命名P1口控制寄存器
sfr PCON2=0X97;//命名时钟分频寄存器
/***************AD初始化函数****************
设置P1.0口为AD输入口；
数据存放方式为高两位低八位；
开启电源；
设置转换速度；
*******************************************/
void adc_init(void)
{
  P1ASF=0X0c;//P1ASF.0=1;//设置P1为模拟量输入
	PCON2=PCON2|ADRJ;//ADRJ=1

	
	
	//设置AD电源开启、转换速度设置、AD输入端口
	nop;nop;nop;nop;//延时4个机械周期
	
}
 
/***************读取AD值函数****************
开始转换AD数据；
等待转换完成；
存放数据；
清零标志位和数据位；
*******************************************/
unsigned int get_adc()//读取AD值
{
unsigned int i,j;
	ADC_CONTR = ADC_POWER|ADC_SPEEDH|AD_P1_1;
	nop;nop;nop;nop;
	ADC_CONTR=ADC_CONTR|ADC_START;//开始转换
	while((ADC_CONTR&ADC_FLAG)!=ADC_FLAG);//等待转换标志位
	i=ADC_RES;
	j=ADC_RESL;
	i=i<<8;
	i=i|j;
	ADC_CONTR=ADC_CONTR&~ADC_FLAG;//清零转换标志位
	ADC_RES=0;//数据清零
	ADC_RESL=0;//数据清零
	
	return(i);
}

unsigned int get_adc0()//读取AD值
{
unsigned int i,j;
	ADC_CONTR0 = ADC_POWER|ADC_SPEEDH|AD_P1_0;
	nop;nop;nop;nop;
	ADC_CONTR0=ADC_CONTR0|ADC_START;//开始转换
	while((ADC_CONTR0&ADC_FLAG)!=ADC_FLAG);//等待转换标志位
	i=ADC_RES;
	j=ADC_RESL;
	i=i<<8;
	i=i|j;
	ADC_CONTR0=ADC_CONTR0&~ADC_FLAG;//清零转换标志位
	ADC_RES=0;//数据清零
	ADC_RESL=0;//数据清零
	return(i);
}

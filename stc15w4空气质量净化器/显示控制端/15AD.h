#ifndef __15AD_H
#define __15AD_H
 
//---重定义关键词---//
#define nop _nop_()
#define ADC_POWER 0x80//开电源
#define ADC_START 0x08
#define ADC_FLAG  0x10
#define ADC_SPEEDH 0x40//转换速度为180个时钟周期
#define ADRJ 0X20  //ADRJ=1
#define AD_P1_0 0X02//P1.0为AD输出
#define AD_P1_1 0X03
 
/**********************************
函数声明
**********************************/
void	Delay10ms();//10毫秒延时
void adc_init(void);//AD功能初始化

unsigned int get_adc();//获取AD值

unsigned int get_adc0();//获取AD值

#endif



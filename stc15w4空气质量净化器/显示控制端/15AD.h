#ifndef __15AD_H
#define __15AD_H
 
//---�ض���ؼ���---//
#define nop _nop_()
#define ADC_POWER 0x80//����Դ
#define ADC_START 0x08
#define ADC_FLAG  0x10
#define ADC_SPEEDH 0x40//ת���ٶ�Ϊ180��ʱ������
#define ADRJ 0X20  //ADRJ=1
#define AD_P1_0 0X02//P1.0ΪAD���
#define AD_P1_1 0X03
 
/**********************************
��������
**********************************/
void	Delay10ms();//10������ʱ
void adc_init(void);//AD���ܳ�ʼ��

unsigned int get_adc();//��ȡADֵ

unsigned int get_adc0();//��ȡADֵ

#endif



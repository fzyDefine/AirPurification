#include <reg51.h>
#include <intrins.h>
#include <15AD.h>
#define nop _nop_()//��ʱ
#define ADC_POWER 0x80//����Դ
#define ADC_START 0x08//ADת���������ơ�
#define ADC_FLAG  0x10//ADת��������־
#define ADC_SPEEDH 0x40//ת���ٶ�Ϊ180��ʱ������
#define ADRJ 0X20  //ADRJ=1
//#define AD_P1_0 0x02 //P1.0ΪAD���
//#define AD_P1_1 0x03 //P1.1ΪAD���
sfr ADC_CONTR = 0Xbc;//����ADC���ƼĴ���
sfr ADC_CONTR0 = 0Xbc;//����ADC���ƼĴ���
sfr ADC_RES = 0Xbd;//�������ݸ�λ
sfr ADC_RESL = 0Xbe;//�������ݵ�λ
sfr P1ASF=0X9D;//����P1�ڿ��ƼĴ���
sfr PCON2=0X97;//����ʱ�ӷ�Ƶ�Ĵ���
/***************AD��ʼ������****************
����P1.0��ΪAD����ڣ�
���ݴ�ŷ�ʽΪ����λ�Ͱ�λ��
������Դ��
����ת���ٶȣ�
*******************************************/
void adc_init(void)
{
  P1ASF=0X0c;//P1ASF.0=1;//����P1Ϊģ��������
	PCON2=PCON2|ADRJ;//ADRJ=1

	
	
	//����AD��Դ������ת���ٶ����á�AD����˿�
	nop;nop;nop;nop;//��ʱ4����е����
	
}
 
/***************��ȡADֵ����****************
��ʼת��AD���ݣ�
�ȴ�ת����ɣ�
������ݣ�
�����־λ������λ��
*******************************************/
unsigned int get_adc()//��ȡADֵ
{
unsigned int i,j;
	ADC_CONTR = ADC_POWER|ADC_SPEEDH|AD_P1_1;
	nop;nop;nop;nop;
	ADC_CONTR=ADC_CONTR|ADC_START;//��ʼת��
	while((ADC_CONTR&ADC_FLAG)!=ADC_FLAG);//�ȴ�ת����־λ
	i=ADC_RES;
	j=ADC_RESL;
	i=i<<8;
	i=i|j;
	ADC_CONTR=ADC_CONTR&~ADC_FLAG;//����ת����־λ
	ADC_RES=0;//��������
	ADC_RESL=0;//��������
	
	return(i);
}

unsigned int get_adc0()//��ȡADֵ
{
unsigned int i,j;
	ADC_CONTR0 = ADC_POWER|ADC_SPEEDH|AD_P1_0;
	nop;nop;nop;nop;
	ADC_CONTR0=ADC_CONTR0|ADC_START;//��ʼת��
	while((ADC_CONTR0&ADC_FLAG)!=ADC_FLAG);//�ȴ�ת����־λ
	i=ADC_RES;
	j=ADC_RESL;
	i=i<<8;
	i=i|j;
	ADC_CONTR0=ADC_CONTR0&~ADC_FLAG;//����ת����־λ
	ADC_RES=0;//��������
	ADC_RESL=0;//��������
	return(i);
}

#include "BasicFun.h"

void Timer0Init(void)	//1����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xCD;		//���ö�ʱ��ʼֵ
	TH0 = 0xD4;		//���ö�ʱ��ʼֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ

    ET0 = 1; // ����ʱ��0�ж�
    EA  = 1;  // �жϵ��ܿ���
}

void Timer1Init(void)	// 100us��ʱ��,�����ɨ��ר��
{
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xAE;		//���ö�ʱ��ʼֵ
	TH1 = 0xFB;		//���ö�ʱ��ʼֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ	

    ET1 = 1; // ����ʱ��1�ж�
    EA = 1;  // �жϵ��ܿ���
}

/*��ʱ��0�жϺ���ģ��
void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count;
    TL0 = 0x66; //���ö�ʱ��ʼֵ
    TH0 = 0xFC; //���ö�ʱ��ʼֵ
    T0Count++;
    if(T0Count>=1000)
    {
        T0Count=0;

    }
}
*/

/*��ʱ��1�жϺ���ģ��
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
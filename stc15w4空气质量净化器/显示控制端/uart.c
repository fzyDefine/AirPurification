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

	if ( i==1 && tmp_buffer[0]!=0X2C)	//û�յ���ͷ,���½���
	{
		i = 0;	//�±�i��λ
		memset(tmp_buffer,0,BUFFER_MAX+2);	//�ͷ���ʱ����
		return;
	}

	if( i>= BUFFER_MAX+2 ||  _data == 0X60)	//������߽��յ�������ʶ
	{
		tmp_buffer[i-1] = '\0' ;	//�滻������־
		memcpy(rec_buf,tmp_buffer,BUFFER_MAX+2);	//������Ŀ������
		memset(tmp_buffer,0,BUFFER_MAX+2);	//�ͷ���ʱ����
		i = 0;	//�±�i��λ

	}
	
}

void Devide_DataPacket(u16 *rec_1,u16 *rec_2,u16 *rec_3,u16 *rec_4,u16 *rec_5,u16 *rec_6,u16 *rec_7,u16 *rec_8)
{
	char *token = NULL;
	if(rec_buf[0] == 0)	//������ݰ��ǿյ��򷵻�
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
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xE8;		//���ö�ʱ��ʼֵ
	TH1 = 0xFF;		//���ö�ʱ��ʼֵ
	ET1 = 0;		//��ֹ��ʱ��%d�ж�
	TR1 = 1;		//��ʱ��1��ʼ��ʱ

    ES = 1;
    EA = 1;     //������ʱ��
}

void UART01_SendString(unsigned char *str)				//�����ַ���
{	
	while(*str !='\0')		
		UART01_SendByte(*str++);	

}

void UART01_SendByte(unsigned char c)				//����һ���ַ�
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
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xFB;		//��ʱ��ʱ��12Tģʽ
	T2L = 0xE8;		//���ö�ʱ��ʼֵ
	T2H = 0xFF;		//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ

    IE2 &= 0xFE;   //�ȶ���Ҫ���õ�λ�������� 1111 1110
    IE2 |= 0x01;   // | ESPI | ES2 ����UART2�ж�
    EA = 1;        //�������ж�

	P_SW2 &=~ 0X01;	//ѡ�� P10RX P11TX
}

/***********����*********/
void Uart02_SendData(unsigned char dat)
{
    while (busy); // �ȴ�ǰ������ݷ������
    busy = 1;
    S2BUF = dat; // д���ݵ�UART2���ݼĴ���
}

/************�����ַ���*******************/
void Uart02_SendString(char *s)
{
    while (*s) // ����ַ���������־
    {
        Uart02_SendData(*s++); // ���͵�ǰ�ַ�
    }
}

void Uart02_Routine() interrupt 8 using 2
{
    unsigned char mydata;
    if(S2CON & 0x01)          //����ǽ����ж�
    {
        S2CON &= 0xFE;       //�����жϱ�־λ��0  
        mydata = S2BUF;      //�����ջ����������ݱ��浽mydata������



    }

	if(S2CON & 0x02)          //����Ƿ����ж�
    {
        S2CON &= 0xFD;       //�����жϱ�־��0  
		busy = 0;
    }

}























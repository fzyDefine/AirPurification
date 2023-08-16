#include <STC15.H>
#ifndef __OLED_H
#define __OLED_H	

#define  uchar unsigned char 
#define  uint unsigned int 

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	   
#define high 1
#define low 0 

sbit SCL=P2^0;
sbit SDA=P2^1;

void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void IIC_Start(void);
void IIC_Stop(void);
bit Write_IIC_Byte(unsigned char IIC_Byte);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLEAR(void);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr);
void OLED_OFF(void);
void OLED_ON(void);
void OLED_ShowString(uchar x,uchar y,uchar *chr);
unsigned long oled_pow(uchar m,uchar n);
void OLED_ShowNum(uchar x,uchar y,unsigned long num,uchar len,uchar size2);
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

//2023/5/4  Fzy“∆÷≤
void My_OLED_ShowChar(uchar hang,uchar lie,uchar chr);
void My_OLED_ShowString(uchar hang,uchar lie,uchar *chr);
void My_OLED_ShowNum(uchar hang,uchar lie,unsigned long num,uchar len);



#endif
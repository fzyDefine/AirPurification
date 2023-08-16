#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "BasicFun.h"

//引脚配置：
//蓝桥杯
//  sbit LCD_RS=P2^0;
//  sbit LCD_RW=P2^1;
//  sbit LCD_EN=P1^2;

// 普通51
sbit LCD_RS=P3^2;
sbit LCD_RW=P3^3;
sbit LCD_EN=P3^5;
#define LCD_DataPort P2

//用户调用函数：
void LCD_Init();
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

#endif

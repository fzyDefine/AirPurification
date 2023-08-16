/**
 * @file    BasicFun.h
 * @author  ZhuoYue
 * @brief   ������ʱ���������������ּĴ����Ķ���
 * @version 0.1
 * @date    2022-10-30
 *
 * @copyright Copyright (c) 2022
 */

#ifndef __BASICFUN_H_
#define __BASICFUN_H_

#include <STC15.H> // STC15F2K60S2.H ������ͷ�ļ�
#include <STDIO.H>
#include <INTRINS.H>	  // ʱ�����
#include <STRING.H>       // �ַ�������

#define u16 unsigned int
#define u8 unsigned char

#define bool u8
#define true  1
#define false 0



void Delay1ms();				// @11.0592MHz 1������ʱ����������
void delay_ms(u16 n_ms); 		// @11.0592MHz ���뼶��ʱ����������
void LockPort();         		// ���浱ǰ�˿�
void ChoosePort(u8 Y_device);   // ѡ��ĳ�豸

void Timer0Init(void);          // ��ʱ��


#endif // !__BASICFUN__

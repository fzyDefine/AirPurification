/**
 * @file    BasicFun.h
 * @author  ZhuoYue
 * @brief   包含延时函数的声明、部分寄存器的定义
 * @version 0.1
 * @date    2022-10-30
 *
 * @copyright Copyright (c) 2022
 */

#ifndef __BASICFUN_H_
#define __BASICFUN_H_

#include <STC15.H> // STC15F2K60S2.H 开发板头文件
#include <STDIO.H>
#include <INTRINS.H>	  // 时钟相关
#include <STRING.H>       // 字符串处理

#define u16 unsigned int
#define u8 unsigned char

#define bool u8
#define true  1
#define false 0



void Delay1ms();				// @11.0592MHz 1毫秒延时函数的声明
void delay_ms(u16 n_ms); 		// @11.0592MHz 毫秒级延时函数的声明
void LockPort();         		// 锁存当前端口
void ChoosePort(u8 Y_device);   // 选中某设备

void Timer0Init(void);          // 定时器


#endif // !__BASICFUN__

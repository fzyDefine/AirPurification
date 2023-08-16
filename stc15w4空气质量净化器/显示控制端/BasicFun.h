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

#include <STC15F2K60S2.H> // STC15F2K60S2.H 开发板头文件
#include <STDIO.H>
#include <INTRINS.H>	  // 时钟相关
#include <STRING.H>       // 字符串处理
#include <STDLIB.H>       // 内存处理
#include <STDARG.H>       // 可变参数

#define u16 unsigned int
#define u8 unsigned char

#define bool u8
#define true  1
#define false 0

#define LOCK_REGISTER      P2    // 定义锁存器地址

#define Y_LOCK           0X00    // Y0
#define Y_LED            0X80    // 锁存器Y4对应38译码器段码
#define Y_ULN2003        0XA0    // 锁存器Y5对应38译码器段码   
#define Y_DSPLAYCOM      0XC0    // 锁存器Y6对应38译码器段码
#define Y_DSPLAYINPUT    0XE0    // 锁存器Y7对应38译码器段码
#define Delay delay_ms

void Delay1ms();				// @11.0592MHz 1毫秒延时函数的声明
void delay_ms(u16 n_ms); 		// @11.0592MHz 毫秒级延时函数的声明
void LockPort();         		// 锁存当前端口
void ChoosePort(u8 Y_device);   // 选中某设备

void Timer0Init(void);          // 定时器
void Timer1Init(void);

#endif // !__BASICFUN__

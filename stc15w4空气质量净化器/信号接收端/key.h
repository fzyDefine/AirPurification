#ifndef __KEY__H_
#define __KEY__H_

#include "BasicFun.h"


//定义独立按键IO口
#define KEY_S4_PIN   P33
#define KEY_S5_PIN   P32
#define KEY_S6_PIN   P31
#define KEY_S7_PIN   P30

#define u16        unsigned int
#define u8         unsigned char
#define KEY_16_REG P3
enum {
    S4_PRESS = 4,
    S5_PRESS,
    S6_PRESS,
    S7_PRESS
};


u8   read_key_value();
void Timer_Keys_Scan(u8 key_total);  //短按模式  
void Timer_Long_Press(u8 key_total,u8 *get_value);  //长按模式

#endif // !__KEY__H_
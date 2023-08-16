#ifndef __DHT11_H_
#define __DHT11_H_

#include "BasicFun.h"

sbit dht = P1^3;    //DHT11数据脚

//DHT11模块上电后需要等待1s左右
float DHT11_Get_Humidity();



#endif // !__DHT11__
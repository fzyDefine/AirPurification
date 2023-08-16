/******************************************************************
	作者：神秘藏宝室
	店铺：ILoveMCU.taobao.com
	最终解释权归原作者所有，鄙视其他店铺不劳而获的抄袭行为！
******************************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

#include <STC15F2K60S2.H>

#define gpsRxBufferLength  76
//定义数组长度
#define GPS_Buffer_Length 80
#define UTCTime_Length 11
#define latitude_Length 11
#define N_S_Length 2
#define longitude_Length 12
#define E_W_Length 2 

#define u8 unsigned char
#define u16 unsigned int

typedef struct SaveData 
{
	char GPS_Buffer[GPS_Buffer_Length];
	char isGetData;		//是否获取到GPS数据
	char isParseData;	//是否解析完成
	char UTCTime[UTCTime_Length];		//UTC时间
	char latitude[latitude_Length];		//纬度
	char N_S[N_S_Length];		//N/S
	char longitude[longitude_Length];		//经度
	char E_W[E_W_Length];		//E/W
	char isUsefull;		//定位信息是否有效
} xdata _SaveData;

//函数或者变量声明
extern void Delay_ms(unsigned int n);
extern void clrStruct();
extern void printGpsBuffer();
extern void parseGpsBuffer();
extern void errorLog(int num);
extern void Rec_LngLat(u8 *recbuffer,u8 _size);

extern _SaveData Save_Data;

#endif
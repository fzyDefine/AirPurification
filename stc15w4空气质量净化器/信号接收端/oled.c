#include "oled.h"
#include "oledfont.h"  	 
#include "intrins.h"
void Delay_50ms(unsigned int Del_50ms)		//
{
	unsigned char i, j, k;
	for(;Del_50ms>0;Del_50ms--)
	{
		_nop_();
		_nop_();
		i = 3;
		j = 26;
		k = 223;
		do
		{
			do
			{
				while (--k);
			} while (--j);
		} while (--i);
	}
}

void Delay_1ms(unsigned int Del_1ms)		//
{
	unsigned char j,i;
	while(Del_1ms--)
	{	
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}
/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
   SCL = high;		
   SDA = high;
   _nop_();
   SDA = low;
   _nop_();_nop_();
   SCL = low;

}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
   SDA = low;
   _nop_();
   SCL = high;
   _nop_();_nop_();
   SDA = high;
}
/**********************************************
// IIC Write byte
**********************************************/
bit Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	bit Ack_Bit;                    //应答信号
	for(i=0;i<8;i++)		
	{
		if(IIC_Byte & 0x80)		//1?0?
		SDA=high;
		else
		SDA=low;
		//Delay_us(1);
		SCL=high;
		_nop_();_nop_();
		SCL=low;
		//Delay_us(1);
		IIC_Byte<<=1;			//loop
	}
	 SDA = high;		                //释放IIC SDA总线为主器件接收从器件产生应答信号	
	_nop_();_nop_();
	SCL = high;                     //第9个时钟周期
	_nop_();_nop_();
	Ack_Bit = SDA;		            //读取应答信号
	SCL = low;
	return Ack_Bit;	
}  
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
   Write_IIC_Byte(0x00);			//write command
   Write_IIC_Byte(IIC_Command); 
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			
   Write_IIC_Byte(0x40);			//write data
   Write_IIC_Byte(IIC_Data);
   IIC_Stop(); 
}

void OLED_Init(void)
{
	Delay_50ms(2); //这里的延时很重要
	
	Write_IIC_Command(0xAE); //关显示
	Write_IIC_Command(0x20);	//设置内存寻址模式	
	Write_IIC_Command(0x10);	//00，水平寻址模式;01，垂直寻址模式;10，页面寻址模式(重置);11，无效
	Write_IIC_Command(0xb0);	//为页面寻址模式设置页面开始地址，0-7
	Write_IIC_Command(0xc8);	//设置COM输出扫描方向
	Write_IIC_Command(0x00); //---设置低列地址
	Write_IIC_Command(0x10); //---设置高列地址
	Write_IIC_Command(0x40); //--设置起始行地址
	Write_IIC_Command(0x81); //--set contrast control register
	Write_IIC_Command(0xff); //亮度调节 0x00~0xff
	Write_IIC_Command(0xa1); //--设置段重新映射0到127
	Write_IIC_Command(0xa6); //--设置正常显示
	Write_IIC_Command(0xa8); //--设置复用比(1 ~ 64)
	Write_IIC_Command(0x3F); //
	Write_IIC_Command(0xa4); //0xa4,输出遵循RAM内容;0xa5,Output忽略RAM内容
	Write_IIC_Command(0xd3); //-设置显示抵消
	Write_IIC_Command(0x00); //-not offset
	Write_IIC_Command(0xd5); //--设置显示时钟分频/振荡器频率
	Write_IIC_Command(0xf0); //--设置分率
	Write_IIC_Command(0xd9); //--设置pre-charge时期
	Write_IIC_Command(0x22); //
	Write_IIC_Command(0xda); //--设置com大头针硬件配置
	Write_IIC_Command(0x12);
	Write_IIC_Command(0xdb); //--设置vcomh
	Write_IIC_Command(0x20); //0x20,0.77xVcc
	Write_IIC_Command(0x8d); //--设置DC-DC
	Write_IIC_Command(0x14); //--打开电荷泵
	Write_IIC_Command(0xaf); //--打开oled面板

	OLED_CLEAR();//清屏
}

void OLED_SetPos(unsigned char x, unsigned char y) //设置起始点坐标
{ 
	Write_IIC_Command(0xb0+y);
	Write_IIC_Command(((x&0xf0)>>4)|0x10);
	Write_IIC_Command((x&0x0f)|0x01);
}
void OLED_Fill(unsigned char fill_Data)//全屏填充
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		Write_IIC_Command(0xb0+m);		//page0-page1
		Write_IIC_Command(0x00);		//low column start address
		Write_IIC_Command(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				Write_IIC_Data(fill_Data);
			}
	}
}
void OLED_CLEAR(void)//清屏
{
	OLED_Fill(0x00);
}
//--------------------------------------------------------------
//让OLED休眠 – 休眠模式下,OLED功耗不到10uA
void OLED_OFF(void)
{
	Write_IIC_Command(0X8D);  //设置电荷泵
	Write_IIC_Command(0X10);  //关闭电荷泵 
	Write_IIC_Command(0XAE);  //OLED休眠
}
void OLED_ON(void)
{
	Write_IIC_Command(0X8D);  //设置电荷泵
	Write_IIC_Command(0X14);  //打开电荷泵 
	Write_IIC_Command(0XAF);  //OLED启动
}
//--------------------------------------------------------------
void OLED_ShowChar(uchar x,uchar y,uchar chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		OLED_SetPos(x,y);	
		for(i=0;i<8;i++)
			Write_IIC_Data(F8X16[c*16+i]);
		OLED_SetPos(x,y+1);
		for(i=0;i<8;i++)
			Write_IIC_Data(F8X16[c*16+i+8]);
}

void My_OLED_ShowChar(uchar hang,uchar lie,uchar chr)
{
	
	OLED_ShowChar((lie-1)*8,2*(hang-1),chr);

}

void OLED_ShowString(uchar x,uchar y,uchar *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

void My_OLED_ShowString(uchar hang,uchar lie,uchar *chr)
{	
	unsigned char j=0;
	while (chr[j]!='\0')
	{
		My_OLED_ShowChar(hang,lie,chr[j]);
		lie++; j++;
	}
}

unsigned long oled_pow(uchar m,uchar n)
{
	unsigned long result=1;	 
	while(n--)result*=m;    
	return result;
}
void OLED_ShowNum(uchar x,uchar y,unsigned long num,uchar len,uchar size2)
{         	
	uchar t,temp;
	uchar enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0'); 
	}
} 
void My_OLED_ShowNum(uchar hang,uchar lie,unsigned long num,uchar len)
{

	OLED_ShowNum((lie-1)*8,2*(hang-1),num,len,16);
}



//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------

void OLED_ShowCHinese(uchar x,uchar y,uchar no)
{      			    
	uchar t,adder=0;
	OLED_SetPos(x,y);	
    for(t=0;t<16;t++)
		{
				Write_IIC_Data(Hzk[2*no][t]);
				adder+=1;
     }	
		OLED_SetPos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				Write_IIC_Data(Hzk[2*no+1][t]);
				adder+=1;
      }					
}
//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
//--------------------------------------------------------------
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			Write_IIC_Data(BMP[j++]);
		}
	}
}
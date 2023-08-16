#include "ATcommand.h"
#include "BasicFun.h"
#include "UART.h"
#include "string.h"
#include "LCD1602.h"

extern xdata u8 uart02_buffer[UART_MAX];

void Debug_Print()
{
    static u8 times = 0;
    u8 i = 0;
    times++;
    UART01_SendString("*****print debug*****\r\n");
    for(i=0;i<UART_MAX;i++)
    {
        UART01_SendByte(uart02_buffer[i]);
    }
    UART01_SendString("\r\n");
}


bool Wait_CREG(void)
{
    u8 k = 0,i = 0;
    
	Clean_Uart02Buffer();
    while(1)        			
	{
		Clean_Uart02Buffer();  //清除串口缓存数组   
		Uart02_SendString("AT+CREG?\r\n");//查询模块网络注册状态
		Delay(1000);     //等待模块响应数据	
        // LCD_Init(); //清除上一轮残留重新显示
		// for(i=0; i<16 && uart02_buffer[i]!='\0' ;i++) //显示部分AT指令
        //     LCD_ShowChar(2,i+1,uart02_buffer[i]);	
        Debug_Print();				
	    for(k=0;k<UART_MAX;k++)      			
    	{
			if(uart02_buffer[k] == ':')
			{	
				if((uart02_buffer[k+4] == '1')||(uart02_buffer[k+4] == '4')) //表明网络注册成功
				{
				    return true;
				}
			}
		}

	}

}

bool Is_IncStr( u8 *tar_buffer, u8 *inc_str )
{ 
    if(strstr(tar_buffer,inc_str)!=NULL)
	    return true;
	else
	    return flase;
}

void Send_ATCommand(u8 *command,u8 *want_reaction,u8 wait_s)
{
    u8 react = 0,i = 0;
    LCD_Init();
    do
    {
        Clean_Uart02Buffer();   //清除串口数据缓存数组
        Uart02_SendString(command); //发送AT指令
        Uart02_SendString("\r\n"); //发送换行 

        Delay(wait_s*1000);     //延时等待接收
        Debug_Print();

        react = Is_IncStr(uart02_buffer,want_reaction);
    } while (!react);
}

void Set_MsgMode(u8 *phone_center)  //填写区号,配置短信模式
{
    u8 temp_buffer[30] = "";
    u8 react;
    memset(temp_buffer,0,30);
    sprintf(temp_buffer,"AT+CSCA=\"+861380%s500\"",phone_center);
    Send_ATCommand(temp_buffer,"OK",2); 

    Send_ATCommand("AT+CMGF=1","OK",2); 
    Send_ATCommand("AT+CSCS=\"GSM\"","OK",2); 
    // Send_ATCommand("AT+CSMP=17,167,0,241","OK",2); 



    do
    {
        Clean_Uart02Buffer();   //清除串口数据缓存数组
        Uart02_SendString("AT+CSMP=17,167,0,241"); //发送AT指令
        Uart02_SendString("\r\n"); //发送换行 

        Delay(3*1000);     //延时等待接收

        // for(i=0; i<32 && uart02_buffer[i]!='\0' ;i++) //第二行显示部分响应
        //     LCD_ShowChar(i/16+1,i%16+1,uart02_buffer[i]);
        Debug_Print();
        react = Is_IncStr(uart02_buffer,"OK");
    } while (!react);

    Clean_Uart02Buffer();   //清除串口数据缓存数组

}

void Send_Msg(u8 *target_phone,u8 *content)
{
    u8 temp_buffer[30]="";
    u8 i = 0;
    memset(temp_buffer,0,30);
    sprintf(temp_buffer,"AT+CMGS=\"%s\"",target_phone);
    Send_ATCommand(temp_buffer,">",2);
    Clean_Uart02Buffer(); 
    Uart02_SendString(content);
    Uart02_SendData(0X1A);  //确认发送标志
    delay_ms(3000);
    for(i=0;i<8;i++)
    {
        Debug_Print();
        delay_ms(800);
    }
}
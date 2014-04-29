/***************************************************************

File name:  main.c

Author: SanBin      Version: V1.0    Date: 2012-3

Description: 1.主程序文件


History:
***************************************************************/
#include "Includes.h"

void delay_us(int k);

/******************************************************************************************
  函数名: main
  描述:     软件入口程序
  输入:     无
  输出:     无
  返回:     无
  其他:     无
******************************************************************************************/
int main( void )
{
	SystemInit();//系统初始化

    DDRD=0xFF;
    PORTD=0x00;

    int t;
    for (t=0;t<7;t++)
    {
    	PORTD = 1 << t;
    	_delay_ms(300);
    }
	while(1) //主循环
	{
		int i,k;
		k=500;
		for (i = 0 ; i < k ;i++)
		{
			PORTD = 0XFF;
			delay_us(i);
			PORTD = 0X00;
			delay_us(k-i);
		}

		PORTD = 0xFF;
		_delay_ms(500);

		for (i = 0 ; i < k ;i++)
		{
			PORTD = 0X00;
			delay_us(i);
			PORTD = 0XFF;
			delay_us(k-i);
		}

	}
	return 0;
}

void SendB()
{
	UsartSendOneByte(UDR);
	UsartSendOneByte(UDR);
}

void delay_us(int k)
{
	int i;
	for (i=0;i<k;i++)
	{
		_delay_us(1);
	}
}


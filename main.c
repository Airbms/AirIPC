/***************************************************************

File name:  main.c

Author: SanBin      Version: V1.0    Date: 2012-3

Description: 1.�������ļ�


History:
***************************************************************/
#include "Includes.h"

void delay_us(int k);

/******************************************************************************************
  ������: main
  ����:     �����ڳ���
  ����:     ��
  ���:     ��
  ����:     ��
  ����:     ��
******************************************************************************************/
int main( void )
{
	SystemInit();//ϵͳ��ʼ��

    DDRD=0xFF;
    PORTD=0x00;

    int t;
    for (t=0;t<7;t++)
    {
    	PORTD = 1 << t;
    	_delay_ms(300);
    }
	while(1) //��ѭ��
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


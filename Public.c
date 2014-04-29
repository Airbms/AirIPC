
/***************************************************************

File name:  public.c

Author: SanBin      Version: V1.0    Date: 20112-3

Description: 1.对public.h中定义的函数进行定义


  History:       1. Date:
                            Author:
                           Modification:
                        2. ...
***************************************************************/

//头文件引用**********************************************************
#include "Includes.h"


/*********************************************************************
  函数名: DogInit
  描述:     内部看门狗初始化
  输入:     无
  输出:     无
  返回:     无
  其他:     无
*********************************************************************/
void DogInit( void )
{
    KickDog();
	WDTCR = 0x1F;
	WDTCR = 0x0F; //1.9s不清狗则复位
}


/*********************************************************************
  函数名: Asc2Hex
  描述:     ASC码转十六进制数，UINT8型
  输入:     ASC码
  输出:     无
  返回:     十六进制数 ，如果输入数值不在合法ASCII码值内，将返回0
  其他:     无
*********************************************************************/
UINT8 Asc2Hex( UINT8 asc )
{
	if( asc >= 0x30 && asc <= 0x39 )
	{
		asc -= 0x30;
		return asc;
	}

	if( asc >= 0x41 && asc <= 0x46 )
	{
		asc -= 0x37;
		return asc;
	}

	if( asc >= 0x61 && asc <= 0x66 )
	{
		asc -= 0x57;
		return asc;
	}

	return 0;
}


/*********************************************************************
  函数名: Hex2Asc
  描述:     十六进制数转ASC
  输入:     十六进制数字节，UINT8型
  输出:     无
  返回:     2个ASCII值放在UINT16数中，按高低字节顺序存放。
  其他:     无
*********************************************************************/
UINT16 Hex2Asc( UINT8 hex )
{
	UINT16 word1 = 0;

	//高字节
	if( ( hex / 16 ) >= 0 && ( hex / 16 ) <= 9 )
	{
		word1 = ( hex / 16 + 0x30 ) * 256;
	}
	else
	{
		if( ( hex / 16 ) >= 10 && ( hex / 16) <= 15 )
		{
			word1 = ( hex / 16 + 0x37 ) * 256;
		}
		else
		{
			word1 = 0;
		}
	}

	//低字节
	if( ( hex & 0x0f ) >= 0 && ( hex & 0x0f ) <= 9 )
	{
		word1 += ( hex & 0x0f )+0x30;
	}
	else
	{
		if( ( hex & 0x0f ) >= 10 && ( hex & 0x0f ) <= 15 )
		{
			word1 += ( hex & 0x0f )+0x37;
		}
		else
		{
			word1 = 0;
		}
	}

	return word1;
}


/*********************************************************************
  函数名:	CalCRC16
  描述:		CRC16校验
  输入:		需要校验的数组首地址ptr，UINT8*
				数组长度len，UINT16型
  输出:     无
  返回:     CRC16校验码
  其他:     无
*********************************************************************/
UINT16 CalCRC16( volatile UINT8 *ptr, UINT16 len, UINT16 Polynomial )
{
	volatile UINT8 i = 0;
	volatile UINT16 crc = 0xFFFF;

	while( len != 0 )
	{
		crc ^= *ptr;

		for( i = 0; i < 8; i ++ )
		{
			if( ( crc & 0x0001 ) == 0 )
			{
				crc = crc >> 1;
			}
			else
			{
				crc = crc >> 1;
				crc ^= Polynomial;
			}
		}

		len --;
		ptr++;
	}

	return crc;
}


/*********************************************************************
  函数名:	SystemInit
  描述:		系统初始化
  输入:		无
  输出:     无
  返回:     无
  其他:     无
*********************************************************************/
void SystemInit( void )
{
	CLI(); //关总中断

	//AdcInit( 0 );
	//DisplayInit();
	//Max7219Init( 0x0F, 15, 2, FALSE, FALSE );
	//ModuleInit();
	UsartInit( 0, 9600, 0 , 0, 20, 20 );
	TimerInit0();
	TimerInit1();
	//DogInit();

	SEI();//开总中断
}

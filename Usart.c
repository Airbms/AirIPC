/***************************************************************

File name:  Timer.c

Author: SanBin      Version: V1.0    Date: 2013-8

Description: usart模块

History:  1. Date:
                    Author:
                    Modification:
***************************************************************/

//头文件引用
#include "Includes.h"


//全局变量定义
Msg UsartMsg; //串口接收缓冲区

BOOL UsartInit( UINT8 address, UINT16 baud_rate, UINT8 parity, UINT8 stop_bit, UINT16 rx_buf_len, UINT16 tx_buf_len );
void UsartChangePara( UINT8 address, UINT16 baud_rate );
void UsartCompleteFrame( void );
void UsartSendOneByte( UINT8 DateByte );
void UsartTxTimeOut( void );

//私有变量声明
static BOOL UsartInitOnce = FALSE; //usart初始化一次的标记，FALSE未初始化，TRUE已初始化


/******************************************************
  函数名:	UsartInit
  描述:		串口初始化函数。
  输入:		1.通信地址address，MODBUS协议中范围：0-247。
				2.波特率baud_rate，UINT16型，支持：2400,4800,9600,19200。
				3.校验位parity，UINT8型，0-无校验，2-偶校验，3-奇校验。
				4.停止位stop_bit，UINT8，0-1个停止位，1-2两个停止位。
				5.接收缓冲区大小rx_buf_len，UINT16，使用尽量少的缓冲区。
				6.发送缓冲区大小tx_buf_len，UINT16，使用尽量少的缓冲区。
				此函数只允许初始化一次。
  输出:     无
  返回:     初始化是否成功，成功为TRUE，失败为FALSE。
  其他:     无
********************************************************/
BOOL UsartInit( UINT8 address, UINT16 baud_rate, UINT8 parity, UINT8 stop_bit, UINT16 rx_buf_len, UINT16 tx_buf_len )
{
	//USART硬件初始化
	DDRD &= 0b11111110; //PD0~RX。
	PORTD |= 0b00000001; //使能内部上拉电阻
	DDRD |= 0b00000010; //PD1~TX。
	PORTD &= 0b11111101; //禁止内部上拉电阻

	if ( FALSE == UsartInitOnce )
	{
		UINT16 ubrr; //波特率寄存器
		UINT8 ucsrc;
		ucsrc = ( 1 << URSEL ) | 0x06;
		UCSRB = 0x00;
		UCSRA = 0x02; //倍速

		//设置波特率
		if ( 2400 == baud_rate || 4800 == baud_rate || 9600 == baud_rate || 19200 == baud_rate )
		{
			ubrr = ( UINT16 )( F_CPU / ( 8 * ( FLOAT64 ) baud_rate ) - 1 );
		}
		else
		{
			return FALSE;
		}

		UBRRH = ( UINT8 )( ubrr / 256 );
		UBRRL = ( UINT8 )( ubrr % 256 );


		//设置校验位
		switch ( parity )
		{
			//case NO_PARITY:
			//break;

			case 2:
			ucsrc |= 0x20;
			break;

			case 3:
			ucsrc |= 0x30;
			break;

			default:
			break;
		}

		//设置停止位
		switch ( stop_bit )
		{
			//case STOP1:
			//break;

			case 1:
			ucsrc |= 0x08;
			break;

			default:
			break;
		}

		UCSRC = ucsrc;
		ucsrc = UBRRH;
		ucsrc = UCSRC;
		UCSRB = 0xD8; //8位数据位，中断发送，中断接收

		//串口用到的变量初始化
		UsartMsg.rx_cnt = 0;
		UsartMsg.rx_timer = 0; //启动空闲计时
		UsartMsg.tx_len = 0;
		UsartMsg.rx_cnt = 0;
		UsartMsg.state = USART_IDLE; //设备空闲
		UsartMsg.baud_rate = baud_rate; //初始化波特率值
		UsartMsg.modbus_1_5t = ( UINT8 )( 15000 / baud_rate+1 ); //计算MODBUS的1.5T
		UsartMsg.modbus_3_5t = ( UINT8 )( 35000 / baud_rate+1 ); //计算MODBUS的3.5T
		UsartMsg.address = address; //默认地址为1


		UsartMsg.rx_buf = calloc( rx_buf_len, sizeof( UINT8 ) ); //申请接收缓冲区

		if ( NULL == UsartMsg.rx_buf )
		{
			return FALSE;
		}

		UsartMsg.tx_buf = calloc( tx_buf_len, sizeof( UINT8 ) );//动态申请发送缓冲区

		if ( NULL == UsartMsg.tx_buf )
		{
			return FALSE;
		}

		UsartInitOnce = TRUE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


/******************************************************
函数名:UsartChangePara
描述:    修改参数
 输入:	1.通信地址address，MODBUS协议中范围：0-247。
			2.波特率baud_rate，UINT16型，支持：2400,4800,9600,19200。
输出:    无
返回:    无
其他:    无
********************************************************/
void UsartChangePara( UINT8 address, UINT16 baud_rate )
{
	UINT16 ubrr; //波特率寄存器

	//设置波特率
	if ( 2400 == baud_rate || 4800 == baud_rate || 9600 == baud_rate || 19200 == baud_rate )
	{
		ubrr = ( UINT16 )( F_CPU / ( 8 * ( FLOAT64 ) baud_rate ) - 1 );
	}
	else
	{
		ubrr = ( UINT16 )( F_CPU / ( 8 * ( FLOAT64 ) 9600 ) - 1 );
	}

	UBRRH = ( UINT8 )( ubrr / 256 );
	UBRRL = ( UINT8 )( ubrr % 256 );
	UsartMsg.baud_rate = baud_rate; //保存波特率值
	UsartMsg.address = address;
}


/******************************************************
函数名: ISR( USARTRXC_vect )USARTRXC_vect
描述:     串口接收中断函数。
输入:     无
输出:     无
返回:     无
其他:     无
********************************************************/
ISR(USART_RXC_vect)
{
	UINT8 udr;
	udr = UDR;

	SendB();

	switch ( UsartMsg.state )
	{
		case USART_IDLE:
			if ( UsartMsg.modbus_3_5t == UsartMsg.rx_timer ) //空闲时间得到3.5T
			{
				UsartMsg.rx_buf[ 0 ] = udr;  //读入第一个字节
				UsartMsg.rx_cnt = 1; //记录接收数据的个数
				UsartMsg.rx_timer = 0; //重置接收计时器
				UsartMsg.state = USART_RECEIVING; //开始接收一帧数据
			}
			break;


		case USART_RECEIVING:
			UsartMsg.rx_buf[ UsartMsg.rx_cnt ++ ] = udr;  //读入一个字节，并计数器加1
			UsartMsg.rx_timer = 0; //每正常接收到一个字节，重新计时
			break;
	}
}


/******************************************************
函数名: ISR( USARTTXC_vect )
描述:     串口发送中断函数。
输入:     无
输出:     无
返回:     无
其他:     无
********************************************************/
ISR( USART_TXC_vect )
{
	if ( USART_SENDING == UsartMsg.state && UsartMsg.tx_cnt < UsartMsg.tx_len )
	{
		UsartSendOneByte( UsartMsg.tx_buf[ UsartMsg.tx_cnt ] );
		UsartMsg.tx_cnt ++;

		if ( UsartMsg.tx_cnt == UsartMsg.tx_len ) //全部发送完
		{
			UsartMsg.tx_cnt = 0; //清零
			UsartMsg.tx_len = 0;
			UsartMsg.state = USART_IDLE;
		}
	}
}


/******************************************************
函数名: UsartSendOneByte
描述:     串口发送一个字节
输入:     要发送的字节DateByte
输出:     无
返回:     无
其他:     无
********************************************************/
void UsartSendOneByte( UINT8 DateByte )
{
	while( ( ! ( UCSRA & ( 1 << UDRE ) ) ) ) //30ms超时
	{
		KickDog();
	}

	UDR = DateByte; //发送数据
}


/******************************************************
  函数名:	UsartCompleteFrame
  描述:		串口接收完一帧数据
  输入:		无
  输出:     无
  返回:     无
  其他:     无
********************************************************/
void UsartCompleteFrame( void )
{
	if ( USART_RECEIVING == UsartMsg.state ) //如果数据正在接收中
	{
		if ( UsartMsg.rx_timer < UsartMsg.modbus_3_5t )
		{
			UsartMsg.rx_timer ++;

			//接收过程中超过3.5T，完成一个数据帧的接收
			if ( UsartMsg.rx_timer == UsartMsg.modbus_3_5t )
			{
				UsartMsg.state = USART_RECEIVED; //接收完成，等待处理
				//CommProcessing();
			}
		}
	}

	if ( USART_IDLE == UsartMsg.state ) //空闲计时
	{
		if ( UsartMsg.rx_timer < UsartMsg.modbus_3_5t )
		{
			UsartMsg.rx_timer ++;
		}
	}
}


/******************************************************
函数名: UsartTxTimeOut
描述:     串口发送计时器超时
输入:     无
输出:     无
返回:     无
其他:     无
********************************************************/
void UsartTxTimeOut( void )
{
	if ( UsartMsg.tx_timer < UsartMsg.modbus_3_5t )
	{
		UsartMsg.tx_timer ++;
	}
}

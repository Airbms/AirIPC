/*******************************************************

File name:  Usart.h

Author: SanBin      Version: V1.0    Date: 2013-8

Description: 串口模块，通信功能

History:  1. Date:
                    Author:
                    Modification:
********************************************************/
#ifndef USART_H_
#define USART_H_


//通信状态代码宏定义
#define USART_IDLE					1
#define USART_RECEIVING				2
#define USART_RECEIVED				3
#define USART_TO_SEND				4
#define USART_SENDING				5
#define USART_SENDED					6
#define USART_RX_ERROR				7


//消息结构体声明
typedef struct
{
	UINT8 *rx_buf; //接收数组
	UINT8 rx_cnt; //已接收的长度
	UINT8 *tx_buf; //发送数组
	UINT8 tx_len; //需要发送的长度
	UINT8 tx_cnt; //已发送的长度
	UINT8 state; //通信状态
	UINT16 baud_rate; //波特率
	UINT8 rx_timer; //接收超时定时器
	UINT8 tx_timer; //发送超时定时器
	UINT8 modbus_1_5t; //MODBUS中的1.5T间隔
	UINT8 modbus_3_5t; //MODBUS中的3.5T间隔
	UINT8 address; //通信地址
}Msg;


//接口变量声明
extern Msg UsartMsg; //串口接收缓冲区

//接口函数声明

/******************************************************
  函数名:	UsartInit
  描述:		串口初始化函数。
  输入:		1.通信地址address，MODBUS协议中范围：0-247。
				2.波特率baud_rate，UINSystemInitT16型，支持：2400,4800,9600,19200。
				3.校验位parity，UINT8型，0-无校验，2-偶校验，3-奇校验。
				4.停止位stop_bit，UINT8，0-1个停止位，1-2两个停止位。
				5.接收缓冲区大小rx_buf_len，UINT16，使用尽量少的缓冲区。
				6.发送缓冲区大小tx_buf_len，UINT16，使用尽量少的缓冲区。
				此函数只允许初始化一次。
  输出:     无
  返回:     初始化是否成功，成功为TRUE，失败为FALSE。
  其他:     无
********************************************************/
extern BOOL UsartInit( UINT8 address, UINT16 baud_rate, UINT8 parity, UINT8 stop_bit, UINT16 rx_buf_len, UINT16 tx_buf_len );


/******************************************************
函数名:UsartChangePara
描述:    修改参数
 输入:	1.通信地址address，MODBUS协议中范围：0-247。
			2.波特率baud_rate，UINT16型，支持：2400,4800,9600,19200。
输出:    无
返回:    无
其他:    无
********************************************************/
extern void UsartChangePara( UINT8 address, UINT16 baud_rate );


/******************************************************
  函数名:	UsartCompleteFrame
  描述:		串口接收完一帧数据
  输入:		无
  输出:     无
  返回:     无
  其他:     无
********************************************************/
extern void UsartCompleteFrame( void );

/******************************************************
函数名: UsartSendOneByte
描述:     串口发送一个字节
输入:     要发送的字节DateByte
输出:     无
返回:     无
其他:     无
********************************************************/
extern void UsartSendOneByte( UINT8 DateByte );


/******************************************************
函数名: UsartTxTimeOut
描述:     串口发送计时器超时
输入:     无
输出:     无
返回:     无
其他:     无
********************************************************/
extern void UsartTxTimeOut( void );


#endif

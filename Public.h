/***************************************************************

File name:  Public.h

Author: SanBin      Version: V1.0    Date: 2013-8

Description: 公共数据类型、函数

History:  1. Date:
                    Author:
                    Modification:
***************************************************************/

#ifndef PUBLIC_H_
#define PUBLIC_H_


//定义清除看门狗
#define KickDog() asm("wdr")


//公共函数声明
/*********************************************************************
  函数名: DogInit
  描述:     内部看门狗初始化
  输入:     无
  输出:     无
  返回:     无
  其他:     无
*********************************************************************/
extern void DogInit( void );


/*********************************************************************
  函数名: Asc2Hex
  描述:     ASC码转十六进制数
  输入:     ASC码
  输出:     无
  返回:     十六进制数 ，如果输入数值不在合法ASCII码值内，将返回0
  其他:     无
*********************************************************************/
extern UINT8 Asc2Hex( UINT8 asc );


/*********************************************************************
  函数名: Hex2Asc
  描述:     十六进制数转ASC
  输入:     十六进制数字节，UINT8
  输出:     无
  返回:     2个ASCII值放在UINT16数中，按高低字节顺序存放。
  其他:     无
*********************************************************************/
extern UINT16 Hex2Asc( UINT8 hex );

/*********************************************************************
  函数名:	CalCRC16
  描述:		CRC16校验
  输入:		需要校验的数组首地址ptr，UINT8*
				数组长度len，UINT16型
  输出:     无
  返回:     CRC16校验码
  其他:     无
*********************************************************************/
extern UINT16 CalCRC16( volatile UINT8 *ptr, UINT16 len, UINT16 Polynomial );

/*********************************************************************
  函数名:	SystemInit
  描述:		系统初始化
  输入:		无
  输出:     无
  返回:     无
  其他:     无
*********************************************************************/
extern void SystemInit( void );


#endif

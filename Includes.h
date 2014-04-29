/***************************************************************

File name:  Include.h

Author: SanBin      Version: V1.0    Date: 2013-8

Description: 1.����ϵͳ��ֲ�Ļ����������Ͷ���
                       2.���е�ͷ�ļ�������

  History:       1. Date:
                         Author:
                         Modification:
***************************************************************/


#ifndef INCLUDE_H_
#define INCLUDE_H_

//����Ƶ��
#ifndef F_CPU
#define F_CPU 12000000UL
#endif


//����ֲ�������Ͷ���
typedef unsigned char BOOL;
typedef unsigned char UINT8;
typedef signed char INT8;
typedef unsigned int UINT16;
typedef signed int INT16;
typedef unsigned long UINT32;
typedef signed long INT32;
typedef float FLOAT32;
typedef double FLOAT64;

#ifndef FALSE
#define FALSE 0
#endif


#ifndef TRUE
#define TRUE 1
#endif

#ifdef NULL
#undef NULL
#define NULL 0x0000
#endif


//���û��ָ���ICC��ֲ��Atmel Studio��Ԥ����
#define WDR() 	asm("wdr")
#define SEI()	asm("sei")
#define CLI()	asm("cli")
#define NOP()	asm("nop")
#define SLEEP() asm("sleep")
#define _WDR() 	asm("wdr")
#define _SEI()	asm("sei")
#define _CLI()	asm("cli")
#define _NOP()	asm("nop")
#define _SLEEP() asm("sleep")
#define BIT(x)	(1 << (x))

#define sbit(x,PORT) (PORT) |= (1<<x)
#define cbit(x,PORT) (PORT) &= ~(1<<x)
#define pin(x,PIN) (PIN)&(1<<x)

//EEPROM��д��������ICC��ֲ��Atmel Studio��Ԥ����
#define EEPROM_BUSY_WAIT()							eeprom_busy_wait()
#define EEPROM_READ_BYTE(addr,val)			(val)=eeprom_read_byte((const uint8_t *)(addr))
#define EEPROM_READ_WORD(addr,val)		(val)=eeprom_read_word ((const uint16_t *)(addr))
#define EEPROM_READ_DWORD(addr,val)		(val)=eeprom_read_dword ((const uint32_t *)(addr))
#define EEPROM_READ_FLOAT(addr,val)		(val)=eeprom_read_float ((const float *)(addr))
#define EEPROM_READ_BLOCK(addr,val,n)	eeprom_read_block ((void *)(val), (const void *)(addr), (size_t)(n))

#define  EEPROM_WRITE_BYTE(addr, val)			eeprom_write_byte ((uint8_t *)(addr), (uint8_t)(val))
#define  EEPROM_WRITE_WORD(addr, val)		eeprom_write_word ((uint16_t *)(addr), (uint16_t)(val))
#define  EEPROM_WRITE_DWORD(addr, val)		eeprom_write_dword ((uint32_t *)(addr), (uint32_t)(val))
#define  EEPROM_WRITE_FLOAT(addr, val)		eeprom_write_float ((float *)(addr), (float)(val))
#define EEPROM_WRITE_BLOCK(addr,val,n)		eeprom_write_block ((const void *)(val), (void *)(addr), (size_t)(n))


//����������flash��
#define FLASH_UINT8 prog_uchar
#define READ_FLASH_BYTE( var ) pgm_read_byte_near( var )


//��׼��ͷ�ļ�����
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h> //��ʱ������ͷ�ļ�
#include <avr/interrupt.h> //�ж���Ҫ��ͷ�ļ�
#include <avr/eeprom.h> //eeprom��Ҫ��ͷ�ļ�
#include <avr/pgmspace.h> //���ݷ���flash��ʱ��������ͷ�ļ�


//�Զ���ͷ�ļ�����
#include "Public.h"
#include "Usart.h"
//#include "Comm.h"
//#include "Adc.h"
//#include "PowerModule.h"
//#include "Display.h"
#include "Timer.h"
//#include "Max7219.h"


#endif

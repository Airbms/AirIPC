/***************************************************************

File name:  Timer.h

Author: SanBin      Version: V1.0    Date: 2013-8

Description: 定时器模块，功能为完成定时器初始化和定时器中断服务程序。

History:  1. Date:
                    Author:
                    Modification:
***************************************************************/

#ifndef TIMER_H_
#define TIMER_H_


//定时器延时预定义，基于定时器1周期为10ms
#define TIMER_DELAY_20MS		2
#define TIMER_DELAY_50MS		5
#define TIMER_DELAY_100MS		10
#define TIMER_DELAY_150MS		15
#define TIMER_DELAY_200MS		20
#define TIMER_DELAY_500MS		50
#define TIMER_DELAY_1S				100
#define TIMER_DELAY_2S				200
#define TIMER_DELAY_5S				500
#define TIMER_DELAY_10S			1000
#define TIMER_DELAY_30S			3000
#define TIMER_DELAY_1MIN			6000
#define TIMER_DELAY_3MIN			18000
#define TIMER_DELAY_5MIN			30000
#define TIMER_DELAY_1HOUR		360000

//可自定义部分===========================
//T0初始化寄存器设置宏定义（1ms）
#define TIMER_TCCR0		0x03;
#define TIMER_TCNT0		0x18;
#define TIMER_OCR0			0x00;
#define TIMER_TIMSK0		0x01;

//T1初始化寄存器设置宏定义，数值根据需要自定义
#define TIMER_TCCR1A		0x00;
#define TIMER_TCCR1B		0x02;
#define TIMER_TCNT1H		0xB7;
#define TIMER_TCNT1L		0xFF;
#define TIMER_OCR1AH	0x00;
#define TIMER_OCR1AL		0x00;
#define TIMER_OCR1BH		0x00;
#define TIMER_OCR1BL		0x00;
#define TIMER_ICR1H			0x00;
#define TIMER_ICR1L			0x00;
#define TIMER_TIMSK1		0x04;

//T2初始化寄存器设置宏定义，数值根据需要自定义
#define TIMER_TCCR2		0x00;
#define TIMER_TCNT2		0x00;
#define TIMER_OCR2			0x00;
#define TIMER_TIMSK2		0x00;


//不可自定义部分================================================
//函数声明
void TimerInit0( void ); //T0初始化，定时器相关寄存器初值通过上面的宏定义进行设置，下同
void TimerInit1( void ); //T1初始化
void TimerInit2( void ); //T2初始化


#endif /* TIMER_H_ */

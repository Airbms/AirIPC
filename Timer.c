/***************************************************************

File name:  Timer.c

Author: SanBin      Version: V1.0    Date: 2013-8

Description: 定时器模块

History:  1. Date:
                    Author:
                    Modification:
***************************************************************/
#include "Includes.h"


/******************************************************
  函数名: TimerInit0
  描述:     T0初始化函数。
  输入:     无
  输出:     无
  返回:     无
  其他:     无
********************************************************/
void TimerInit0( void )
{
	TIMSK |= TIMER_TIMSK0; //T0定时器中断屏蔽寄存器设置
	TCNT0 = TIMER_TCNT0; //T0设置计数器初值
	OCR0 = TIMER_OCR0; //T0设置比较寄存器初值
	TCCR0 = TIMER_TCCR0; //T0开定时器
}


/******************************************************
  函数名: TimerInit1
  描述:     T1初始化函数。
  输入:     无
  输出:     无
  返回:     无
  其他:     无
********************************************************/
void TimerInit1( void )
{
	TIMSK |= TIMER_TIMSK1; //T1定时器中断屏蔽寄存器设置
	TCNT1H = TIMER_TCNT1H; //T1设置计数器初值
	TCNT1L = TIMER_TCNT1L;
	OCR1AH = TIMER_OCR1AH; //T1设置比较寄存器初值A
	OCR1AL = TIMER_OCR1AL;
	OCR1BH = TIMER_OCR1BH; //T1设置比较寄存器初值B
	OCR1BL = TIMER_OCR1BL;
	ICR1H = TIMER_ICR1H; //T1设置输入捕获寄存器初值
	ICR1L = TIMER_ICR1L;
	TCCR1A = TIMER_TCCR1A; //T1开定时器
	TCCR1B = TIMER_TCCR1B;
}


/******************************************************
  函数名: TimerInit2
  描述:     T2初始化函数
  输入:     无
  输出:     无
  返回:     无
  其他:     无
********************************************************/
void TimerInit2( void )
{
	TIMSK |= TIMER_TIMSK2; //T2定时器中断屏蔽寄存器设置
	TCNT2 = TIMER_TCNT2; //T2设置计数器初值
	OCR2 = TIMER_OCR2; //T2设置比较寄存器初值
	TCCR2 = TIMER_TCCR2; //T2开定时器
}


/**************************************************
  函数名: ISR( TIMER0_OVF_vect )
  描述:     T0定时溢出中断程序
  输入:     无
  输出:     无
  返回:     无
  其他:     无
***************************************************/
ISR( TIMER0_OVF_vect )
{
	TIMSK &= ~TIMER_TIMSK0; //防止T0自己嵌套
	TCNT0= TIMER_TCNT0; //重置T0

	//此处添加代码：
	UsartCompleteFrame();//usart接收定时器处理

	TIMSK |= TIMER_TIMSK0;   //开定T0
}


/**************************************************
  函数名: ISR( TIMER1_OVF_vect )
  描述:     T1定时溢出中断程序
  输入:     无
  输出:     无
  返回:     无
  其他:     无
***************************************************/
ISR( TIMER1_OVF_vect )
{
	TIMSK &= ~TIMER_TIMSK1; //防止T1自己嵌套
	TCNT1H = TIMER_TCNT1H; //重置T1
	TCNT1L = TIMER_TCNT1L;

	//此处添加代码：
	UsartTxTimeOut(); //usart发送定时器处理，20ms超时
	//SendB();

	TIMSK |= TIMER_TIMSK1;   //开定T1
}


/**************************************************
  函数名: ISR( TIMER2_OVF_vect )
  描述:     T2定时溢出中断程序
  输入:     无
  输出:     无
  返回:     无
  其他:     无
***************************************************/
ISR( TIMER2_OVF_vect )
{
	TIMSK &= ~TIMER_TIMSK2; //防止T2自己嵌套
	TCNT2= TIMER_TCNT2; //重置T2

	//此处添加代码：

	TIMSK |= TIMER_TIMSK2;   //开定T2
}

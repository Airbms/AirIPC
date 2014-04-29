/***************************************************************

File name:  Timer.c

Author: SanBin      Version: V1.0    Date: 2013-8

Description: ��ʱ��ģ��

History:  1. Date:
                    Author:
                    Modification:
***************************************************************/
#include "Includes.h"


/******************************************************
  ������: TimerInit0
  ����:     T0��ʼ��������
  ����:     ��
  ���:     ��
  ����:     ��
  ����:     ��
********************************************************/
void TimerInit0( void )
{
	TIMSK |= TIMER_TIMSK0; //T0��ʱ���ж����μĴ�������
	TCNT0 = TIMER_TCNT0; //T0���ü�������ֵ
	OCR0 = TIMER_OCR0; //T0���ñȽϼĴ�����ֵ
	TCCR0 = TIMER_TCCR0; //T0����ʱ��
}


/******************************************************
  ������: TimerInit1
  ����:     T1��ʼ��������
  ����:     ��
  ���:     ��
  ����:     ��
  ����:     ��
********************************************************/
void TimerInit1( void )
{
	TIMSK |= TIMER_TIMSK1; //T1��ʱ���ж����μĴ�������
	TCNT1H = TIMER_TCNT1H; //T1���ü�������ֵ
	TCNT1L = TIMER_TCNT1L;
	OCR1AH = TIMER_OCR1AH; //T1���ñȽϼĴ�����ֵA
	OCR1AL = TIMER_OCR1AL;
	OCR1BH = TIMER_OCR1BH; //T1���ñȽϼĴ�����ֵB
	OCR1BL = TIMER_OCR1BL;
	ICR1H = TIMER_ICR1H; //T1�������벶��Ĵ�����ֵ
	ICR1L = TIMER_ICR1L;
	TCCR1A = TIMER_TCCR1A; //T1����ʱ��
	TCCR1B = TIMER_TCCR1B;
}


/******************************************************
  ������: TimerInit2
  ����:     T2��ʼ������
  ����:     ��
  ���:     ��
  ����:     ��
  ����:     ��
********************************************************/
void TimerInit2( void )
{
	TIMSK |= TIMER_TIMSK2; //T2��ʱ���ж����μĴ�������
	TCNT2 = TIMER_TCNT2; //T2���ü�������ֵ
	OCR2 = TIMER_OCR2; //T2���ñȽϼĴ�����ֵ
	TCCR2 = TIMER_TCCR2; //T2����ʱ��
}


/**************************************************
  ������: ISR( TIMER0_OVF_vect )
  ����:     T0��ʱ����жϳ���
  ����:     ��
  ���:     ��
  ����:     ��
  ����:     ��
***************************************************/
ISR( TIMER0_OVF_vect )
{
	TIMSK &= ~TIMER_TIMSK0; //��ֹT0�Լ�Ƕ��
	TCNT0= TIMER_TCNT0; //����T0

	//�˴���Ӵ��룺
	UsartCompleteFrame();//usart���ն�ʱ������

	TIMSK |= TIMER_TIMSK0;   //����T0
}


/**************************************************
  ������: ISR( TIMER1_OVF_vect )
  ����:     T1��ʱ����жϳ���
  ����:     ��
  ���:     ��
  ����:     ��
  ����:     ��
***************************************************/
ISR( TIMER1_OVF_vect )
{
	TIMSK &= ~TIMER_TIMSK1; //��ֹT1�Լ�Ƕ��
	TCNT1H = TIMER_TCNT1H; //����T1
	TCNT1L = TIMER_TCNT1L;

	//�˴���Ӵ��룺
	UsartTxTimeOut(); //usart���Ͷ�ʱ������20ms��ʱ
	//SendB();

	TIMSK |= TIMER_TIMSK1;   //����T1
}


/**************************************************
  ������: ISR( TIMER2_OVF_vect )
  ����:     T2��ʱ����жϳ���
  ����:     ��
  ���:     ��
  ����:     ��
  ����:     ��
***************************************************/
ISR( TIMER2_OVF_vect )
{
	TIMSK &= ~TIMER_TIMSK2; //��ֹT2�Լ�Ƕ��
	TCNT2= TIMER_TCNT2; //����T2

	//�˴���Ӵ��룺

	TIMSK |= TIMER_TIMSK2;   //����T2
}

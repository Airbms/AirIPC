/***************************************************************

File name:  Timer.h

Author: SanBin      Version: V1.0    Date: 2013-8

Description: ��ʱ��ģ�飬����Ϊ��ɶ�ʱ����ʼ���Ͷ�ʱ���жϷ������

History:  1. Date:
                    Author:
                    Modification:
***************************************************************/

#ifndef TIMER_H_
#define TIMER_H_


//��ʱ����ʱԤ���壬���ڶ�ʱ��1����Ϊ10ms
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

//���Զ��岿��===========================
//T0��ʼ���Ĵ������ú궨�壨1ms��
#define TIMER_TCCR0		0x03;
#define TIMER_TCNT0		0x18;
#define TIMER_OCR0			0x00;
#define TIMER_TIMSK0		0x01;

//T1��ʼ���Ĵ������ú궨�壬��ֵ������Ҫ�Զ���
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

//T2��ʼ���Ĵ������ú궨�壬��ֵ������Ҫ�Զ���
#define TIMER_TCCR2		0x00;
#define TIMER_TCNT2		0x00;
#define TIMER_OCR2			0x00;
#define TIMER_TIMSK2		0x00;


//�����Զ��岿��================================================
//��������
void TimerInit0( void ); //T0��ʼ������ʱ����ؼĴ�����ֵͨ������ĺ궨��������ã���ͬ
void TimerInit1( void ); //T1��ʼ��
void TimerInit2( void ); //T2��ʼ��


#endif /* TIMER_H_ */

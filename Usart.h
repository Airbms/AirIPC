/*******************************************************

File name:  Usart.h

Author: SanBin      Version: V1.0    Date: 2013-8

Description: ����ģ�飬ͨ�Ź���

History:  1. Date:
                    Author:
                    Modification:
********************************************************/
#ifndef USART_H_
#define USART_H_


//ͨ��״̬����궨��
#define USART_IDLE					1
#define USART_RECEIVING				2
#define USART_RECEIVED				3
#define USART_TO_SEND				4
#define USART_SENDING				5
#define USART_SENDED					6
#define USART_RX_ERROR				7


//��Ϣ�ṹ������
typedef struct
{
	UINT8 *rx_buf; //��������
	UINT8 rx_cnt; //�ѽ��յĳ���
	UINT8 *tx_buf; //��������
	UINT8 tx_len; //��Ҫ���͵ĳ���
	UINT8 tx_cnt; //�ѷ��͵ĳ���
	UINT8 state; //ͨ��״̬
	UINT16 baud_rate; //������
	UINT8 rx_timer; //���ճ�ʱ��ʱ��
	UINT8 tx_timer; //���ͳ�ʱ��ʱ��
	UINT8 modbus_1_5t; //MODBUS�е�1.5T���
	UINT8 modbus_3_5t; //MODBUS�е�3.5T���
	UINT8 address; //ͨ�ŵ�ַ
}Msg;


//�ӿڱ�������
extern Msg UsartMsg; //���ڽ��ջ�����

//�ӿں�������

/******************************************************
  ������:	UsartInit
  ����:		���ڳ�ʼ��������
  ����:		1.ͨ�ŵ�ַaddress��MODBUSЭ���з�Χ��0-247��
				2.������baud_rate��UINSystemInitT16�ͣ�֧�֣�2400,4800,9600,19200��
				3.У��λparity��UINT8�ͣ�0-��У�飬2-żУ�飬3-��У�顣
				4.ֹͣλstop_bit��UINT8��0-1��ֹͣλ��1-2����ֹͣλ��
				5.���ջ�������Сrx_buf_len��UINT16��ʹ�þ����ٵĻ�������
				6.���ͻ�������Сtx_buf_len��UINT16��ʹ�þ����ٵĻ�������
				�˺���ֻ�����ʼ��һ�Ρ�
  ���:     ��
  ����:     ��ʼ���Ƿ�ɹ����ɹ�ΪTRUE��ʧ��ΪFALSE��
  ����:     ��
********************************************************/
extern BOOL UsartInit( UINT8 address, UINT16 baud_rate, UINT8 parity, UINT8 stop_bit, UINT16 rx_buf_len, UINT16 tx_buf_len );


/******************************************************
������:UsartChangePara
����:    �޸Ĳ���
 ����:	1.ͨ�ŵ�ַaddress��MODBUSЭ���з�Χ��0-247��
			2.������baud_rate��UINT16�ͣ�֧�֣�2400,4800,9600,19200��
���:    ��
����:    ��
����:    ��
********************************************************/
extern void UsartChangePara( UINT8 address, UINT16 baud_rate );


/******************************************************
  ������:	UsartCompleteFrame
  ����:		���ڽ�����һ֡����
  ����:		��
  ���:     ��
  ����:     ��
  ����:     ��
********************************************************/
extern void UsartCompleteFrame( void );

/******************************************************
������: UsartSendOneByte
����:     ���ڷ���һ���ֽ�
����:     Ҫ���͵��ֽ�DateByte
���:     ��
����:     ��
����:     ��
********************************************************/
extern void UsartSendOneByte( UINT8 DateByte );


/******************************************************
������: UsartTxTimeOut
����:     ���ڷ��ͼ�ʱ����ʱ
����:     ��
���:     ��
����:     ��
����:     ��
********************************************************/
extern void UsartTxTimeOut( void );


#endif

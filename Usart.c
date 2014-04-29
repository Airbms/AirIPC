/***************************************************************

File name:  Timer.c

Author: SanBin      Version: V1.0    Date: 2013-8

Description: usartģ��

History:  1. Date:
                    Author:
                    Modification:
***************************************************************/

//ͷ�ļ�����
#include "Includes.h"


//ȫ�ֱ�������
Msg UsartMsg; //���ڽ��ջ�����

BOOL UsartInit( UINT8 address, UINT16 baud_rate, UINT8 parity, UINT8 stop_bit, UINT16 rx_buf_len, UINT16 tx_buf_len );
void UsartChangePara( UINT8 address, UINT16 baud_rate );
void UsartCompleteFrame( void );
void UsartSendOneByte( UINT8 DateByte );
void UsartTxTimeOut( void );

//˽�б�������
static BOOL UsartInitOnce = FALSE; //usart��ʼ��һ�εı�ǣ�FALSEδ��ʼ����TRUE�ѳ�ʼ��


/******************************************************
  ������:	UsartInit
  ����:		���ڳ�ʼ��������
  ����:		1.ͨ�ŵ�ַaddress��MODBUSЭ���з�Χ��0-247��
				2.������baud_rate��UINT16�ͣ�֧�֣�2400,4800,9600,19200��
				3.У��λparity��UINT8�ͣ�0-��У�飬2-żУ�飬3-��У�顣
				4.ֹͣλstop_bit��UINT8��0-1��ֹͣλ��1-2����ֹͣλ��
				5.���ջ�������Сrx_buf_len��UINT16��ʹ�þ����ٵĻ�������
				6.���ͻ�������Сtx_buf_len��UINT16��ʹ�þ����ٵĻ�������
				�˺���ֻ�����ʼ��һ�Ρ�
  ���:     ��
  ����:     ��ʼ���Ƿ�ɹ����ɹ�ΪTRUE��ʧ��ΪFALSE��
  ����:     ��
********************************************************/
BOOL UsartInit( UINT8 address, UINT16 baud_rate, UINT8 parity, UINT8 stop_bit, UINT16 rx_buf_len, UINT16 tx_buf_len )
{
	//USARTӲ����ʼ��
	DDRD &= 0b11111110; //PD0~RX��
	PORTD |= 0b00000001; //ʹ���ڲ���������
	DDRD |= 0b00000010; //PD1~TX��
	PORTD &= 0b11111101; //��ֹ�ڲ���������

	if ( FALSE == UsartInitOnce )
	{
		UINT16 ubrr; //�����ʼĴ���
		UINT8 ucsrc;
		ucsrc = ( 1 << URSEL ) | 0x06;
		UCSRB = 0x00;
		UCSRA = 0x02; //����

		//���ò�����
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


		//����У��λ
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

		//����ֹͣλ
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
		UCSRB = 0xD8; //8λ����λ���жϷ��ͣ��жϽ���

		//�����õ��ı�����ʼ��
		UsartMsg.rx_cnt = 0;
		UsartMsg.rx_timer = 0; //�������м�ʱ
		UsartMsg.tx_len = 0;
		UsartMsg.rx_cnt = 0;
		UsartMsg.state = USART_IDLE; //�豸����
		UsartMsg.baud_rate = baud_rate; //��ʼ��������ֵ
		UsartMsg.modbus_1_5t = ( UINT8 )( 15000 / baud_rate+1 ); //����MODBUS��1.5T
		UsartMsg.modbus_3_5t = ( UINT8 )( 35000 / baud_rate+1 ); //����MODBUS��3.5T
		UsartMsg.address = address; //Ĭ�ϵ�ַΪ1


		UsartMsg.rx_buf = calloc( rx_buf_len, sizeof( UINT8 ) ); //������ջ�����

		if ( NULL == UsartMsg.rx_buf )
		{
			return FALSE;
		}

		UsartMsg.tx_buf = calloc( tx_buf_len, sizeof( UINT8 ) );//��̬���뷢�ͻ�����

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
������:UsartChangePara
����:    �޸Ĳ���
 ����:	1.ͨ�ŵ�ַaddress��MODBUSЭ���з�Χ��0-247��
			2.������baud_rate��UINT16�ͣ�֧�֣�2400,4800,9600,19200��
���:    ��
����:    ��
����:    ��
********************************************************/
void UsartChangePara( UINT8 address, UINT16 baud_rate )
{
	UINT16 ubrr; //�����ʼĴ���

	//���ò�����
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
	UsartMsg.baud_rate = baud_rate; //���沨����ֵ
	UsartMsg.address = address;
}


/******************************************************
������: ISR( USARTRXC_vect )USARTRXC_vect
����:     ���ڽ����жϺ�����
����:     ��
���:     ��
����:     ��
����:     ��
********************************************************/
ISR(USART_RXC_vect)
{
	UINT8 udr;
	udr = UDR;

	SendB();

	switch ( UsartMsg.state )
	{
		case USART_IDLE:
			if ( UsartMsg.modbus_3_5t == UsartMsg.rx_timer ) //����ʱ��õ�3.5T
			{
				UsartMsg.rx_buf[ 0 ] = udr;  //�����һ���ֽ�
				UsartMsg.rx_cnt = 1; //��¼�������ݵĸ���
				UsartMsg.rx_timer = 0; //���ý��ռ�ʱ��
				UsartMsg.state = USART_RECEIVING; //��ʼ����һ֡����
			}
			break;


		case USART_RECEIVING:
			UsartMsg.rx_buf[ UsartMsg.rx_cnt ++ ] = udr;  //����һ���ֽڣ�����������1
			UsartMsg.rx_timer = 0; //ÿ�������յ�һ���ֽڣ����¼�ʱ
			break;
	}
}


/******************************************************
������: ISR( USARTTXC_vect )
����:     ���ڷ����жϺ�����
����:     ��
���:     ��
����:     ��
����:     ��
********************************************************/
ISR( USART_TXC_vect )
{
	if ( USART_SENDING == UsartMsg.state && UsartMsg.tx_cnt < UsartMsg.tx_len )
	{
		UsartSendOneByte( UsartMsg.tx_buf[ UsartMsg.tx_cnt ] );
		UsartMsg.tx_cnt ++;

		if ( UsartMsg.tx_cnt == UsartMsg.tx_len ) //ȫ��������
		{
			UsartMsg.tx_cnt = 0; //����
			UsartMsg.tx_len = 0;
			UsartMsg.state = USART_IDLE;
		}
	}
}


/******************************************************
������: UsartSendOneByte
����:     ���ڷ���һ���ֽ�
����:     Ҫ���͵��ֽ�DateByte
���:     ��
����:     ��
����:     ��
********************************************************/
void UsartSendOneByte( UINT8 DateByte )
{
	while( ( ! ( UCSRA & ( 1 << UDRE ) ) ) ) //30ms��ʱ
	{
		KickDog();
	}

	UDR = DateByte; //��������
}


/******************************************************
  ������:	UsartCompleteFrame
  ����:		���ڽ�����һ֡����
  ����:		��
  ���:     ��
  ����:     ��
  ����:     ��
********************************************************/
void UsartCompleteFrame( void )
{
	if ( USART_RECEIVING == UsartMsg.state ) //����������ڽ�����
	{
		if ( UsartMsg.rx_timer < UsartMsg.modbus_3_5t )
		{
			UsartMsg.rx_timer ++;

			//���չ����г���3.5T�����һ������֡�Ľ���
			if ( UsartMsg.rx_timer == UsartMsg.modbus_3_5t )
			{
				UsartMsg.state = USART_RECEIVED; //������ɣ��ȴ�����
				//CommProcessing();
			}
		}
	}

	if ( USART_IDLE == UsartMsg.state ) //���м�ʱ
	{
		if ( UsartMsg.rx_timer < UsartMsg.modbus_3_5t )
		{
			UsartMsg.rx_timer ++;
		}
	}
}


/******************************************************
������: UsartTxTimeOut
����:     ���ڷ��ͼ�ʱ����ʱ
����:     ��
���:     ��
����:     ��
����:     ��
********************************************************/
void UsartTxTimeOut( void )
{
	if ( UsartMsg.tx_timer < UsartMsg.modbus_3_5t )
	{
		UsartMsg.tx_timer ++;
	}
}

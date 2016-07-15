
#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include "mcu.h"
#include "McuUart.h"
#include "McuSerialport.h"
#include <pthread.h>


#ifndef MCU_PROTOCOL_PACK_RX_SIZE
#define MCU_PROTOCOL_PACK_RX_SIZE		16
#endif

#ifndef MCU_PROTOCOL_PACK_TX_SIZE
#define MCU_PROTOCOL_PACK_TX_SIZE		16
#endif

#define MCU_PROTOCOL_TX_RETRY			(3)
#define MCU_PROTOCOL_TX_TIMEOUT			(1000UL)

#define MCUUART_STEP_NONE		0
#define MCUUART_STEP_HEAD		1
#define MCUUART_STEP_TYPE		2
#define MCUUART_STEP_INDEX		3
#define MCUUART_STEP_DEVICE		4
#define MCUUART_STEP_LENGTH		5
#define MCUUART_STEP_DATA		6
#define MCUUART_STEP_CHKSUM		7
#define MCUUART_STEP_TAIL		8

static uint8 l_u8RxStep;
static uint8 l_u8RxDataLen;
static uint8 l_u8RxChksum;
static uint8 l_u8Rx10;
static uint32 l_u32RxPackGet;
static uint32 l_u32RxPackSet;
static struct ProtocolPackT l_ptRxPackCache[MCU_PROTOCOL_PACK_RX_SIZE];

static uint8 l_u8TxRetry;
static uint8 l_u8TxIndex;
static uint32 l_u32TxPackGet;
static uint32 l_u32TxPackSet;
static uint32 l_u32TxTicks;
static struct ProtocolPackT l_ptTxPackCache[MCU_PROTOCOL_PACK_TX_SIZE];
static struct ProtocolPackT* l_ptTxSend;
static uint8 l_u8TxBuffer[600];
static uint16 l_u16TxBufferLen;

static pthread_mutex_t mutex_RxPack = PTHREAD_MUTEX_INITIALIZER;

static void McuUartTxPackSend(void);
static void McuUartReceivedPack(void);

uint32 GetTickCount(void)
{
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return (uint32)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void McuUartPrintfPack(const char *pszText, struct ProtocolPackT* ptPack, unsigned char u8Step, bool bComplete)
{
	unsigned char step;
	unsigned char i;
	LOGI("%s", pszText);
	for(step=0; step<=u8Step; step++)
	{
		switch(step)
		{
		case MCUUART_STEP_NONE:
			break;
		case MCUUART_STEP_HEAD:
			LOGI(" 10 02");
			break;
		case MCUUART_STEP_TYPE:
			LOGI(" %02X", ptPack->m_u8Type);
			break;
		case MCUUART_STEP_INDEX:
			LOGI(" %02X", ptPack->m_u8Index);
			break;
		case MCUUART_STEP_DEVICE:
			LOGI(" %02X", ptPack->m_u8Device);
			break;
		case MCUUART_STEP_LENGTH:
			LOGI(" %02X", ptPack->m_u8Length);
			break;
		case MCUUART_STEP_DATA:
			for(i=0; i<ptPack->m_u8Length; i++)
			{
				LOGI(" %02X", ptPack->m_pu8Data[i]);
			}
			break;
		case MCUUART_STEP_CHKSUM:
			LOGI(" %02X", ptPack->m_u8Checksum);
			break;
		case MCUUART_STEP_TAIL:
			break;
		default:
			break;
		}
	}
	if(bComplete)
	{
		LOGI(" 10 03");
	}
	LOGI("\n");
}

/*
 *******************************************************************************
 Function Name:		McuUartInit
 Input Params:		NONE
 Output Params:		NONE
 Return:			NONE
 Description:		Э��������ֳ�ʼ��
 Autor:				fanxueming
 Date:				2015.9.30
 *******************************************************************************
 Modified by:		
 Modified Date:		
 Description:		
 *******************************************************************************
*/
void McuUartInit(void)
{
	l_u8RxStep = MCUUART_STEP_NONE;
	l_u8Rx10 = 0x00;
	l_u8TxIndex = 0x00;
	l_ptTxSend = null;
	l_u32RxPackGet = 0;
	l_u32RxPackSet = 0;
	l_u32TxPackGet = 0;
	l_u32TxPackSet = 0;
	
	//mutex_RxPack = PTHREAD_MUTEX_INITIALIZER;
}

/*
 *******************************************************************************
 Function Name:		McuUartGetTxWait
 Input Params:		NONE
 Output Params:		NONE
 Return:			��Ҫ�ȴ���ʱ�䣬���Ϊ0����ʾ����ȴ�
 Description:		��ȡ������Ҫ�ȴ���ʱ�䡣
 Autor:				fanxueming
 Date:				2015.9.30
 *******************************************************************************
 Modified by:		
 Modified Date:		
 Description:		
 *******************************************************************************
*/
uint32 McuUartGetTxWait(void)
{
	uint32 timeout;
	if(l_ptTxSend == null)
	{
		if(l_u32TxPackGet == l_u32TxPackSet)
		{
			return MCU_PROTOCOL_TX_TIMEOUT;
		}
		return 0;
	}
	else
	{
		timeout = GetTickCount() - l_u32TxTicks;
		if(timeout >= MCU_PROTOCOL_TX_TIMEOUT)
		{
			return 0;
		}
		else
		{
			return (MCU_PROTOCOL_TX_TIMEOUT - timeout);
		}
	}
}

/*
 *******************************************************************************
 Function Name:		McuUartTxProcess
 Input Params:		NONE
 Output Params:		NONE
 Return:			NONE
 Description:		Э�鷢�ʹ�����̡�
 					�����޻�Ӧʱ�Զ��ط���
 					�뾡���ܿ��ѭ�����á�
 Autor:				fanxueming
 Date:				2015.9.30
 *******************************************************************************
 Modified by:		
 Modified Date:		
 Description:		
 *******************************************************************************
*/
void McuUartTxProcess(void)
{
	uint32 p_get;
	if(l_ptTxSend == null)
	{
		if(l_u32TxPackGet == l_u32TxPackSet)
		{
			return;
		}
		l_ptTxSend = &l_ptTxPackCache[l_u32TxPackGet];
		p_get = l_u32TxPackGet+1;
		if(p_get >= MCU_PROTOCOL_PACK_TX_SIZE)
		{
			p_get = 0;
		}
		l_u32TxPackGet = p_get;
		if((l_ptTxSend->m_u8Type == 0xAA) || (l_ptTxSend->m_u8Type == 0xBB))
		{
			l_u8TxRetry = 0;
			McuUartTxPackSend();
			l_u32TxTicks = GetTickCount();
			if(l_ptTxSend->m_u8Type == 0xBB)
			{
				l_ptTxSend = null;
			}
		}
		else
		{
			l_ptTxSend = null;
		}
	}
	else
	{
		if((GetTickCount() - l_u32TxTicks) < MCU_PROTOCOL_TX_TIMEOUT)
		{
			return;
		}
		l_u8TxRetry++;
		LOGI("MCU_UART: no ack ,retry=%d\n", l_u8TxRetry);
		McuUartTxPackSend();
		l_u32TxTicks = GetTickCount();
		if(l_u8TxRetry >= MCU_PROTOCOL_TX_RETRY)
		{
			l_ptTxSend = null;
		}
	}
}

/*
 *******************************************************************************
 Function Name:		McuUartTxPackSend
 Input Params:		NONE
 Output Params:		NONE
 Return:			NONE
 Description:		��׼���õ����ݰ�(l_ptTxSend)���ͳ�ȥ��
 					�����ļ�����
 Autor:				fanxueming
 Date:				2015.9.30
 *******************************************************************************
 Modified by:		
 Modified Date:		
 Description:		
 *******************************************************************************
*/

static void McuUartTxPackSendHead(void)
{
	l_u8TxBuffer[0] = 0x10;
	l_u8TxBuffer[1] = 0x02;
	l_u16TxBufferLen = 2;
}

static void McuUartTxPackSendData(uint8 u8Data)
{
	l_u8TxBuffer[l_u16TxBufferLen++] = u8Data;
	if(u8Data == 0x10)
	{
		l_u8TxBuffer[l_u16TxBufferLen++] = u8Data;
	}
}

static void McuUartTxPackSendTail(void)
{
	l_u8TxBuffer[l_u16TxBufferLen++] = 0x10;
	l_u8TxBuffer[l_u16TxBufferLen++] = 0x03;
}
static void McuUartTxPackSend(void)
{
	uint8 i;
	if(l_ptTxSend == null)
	{
		LOGD("TxSend is null");
		return;
	}
	McuUartPrintfPack("MCU_UART: TX-PACK =>", l_ptTxSend, MCUUART_STEP_TAIL, true);
	McuUartTxPackSendHead();
	McuUartTxPackSendData(l_ptTxSend->m_u8Type);
	McuUartTxPackSendData(l_ptTxSend->m_u8Index);
	McuUartTxPackSendData(l_ptTxSend->m_u8Device);
	McuUartTxPackSendData(l_ptTxSend->m_u8Length);
	for(i=0; i<l_ptTxSend->m_u8Length; i++)
	{
		McuUartTxPackSendData(l_ptTxSend->m_pu8Data[i]);
	}
	McuUartTxPackSendData(l_ptTxSend->m_u8Checksum);
	McuUartTxPackSendTail();
	McuSerialport_Write(l_u8TxBuffer, l_u16TxBufferLen);
}

static void McuUartTxPackAck(uint8 u8Type, uint8 u8Index)
{
	uint8 buf[10];
	uint8 len=0;
	buf[len++] = 0x10;
	buf[len++] = 0x02;
	buf[len++] = u8Type;
	if(u8Type == 0x10)
	{
		buf[len++] = 0x10;
	}
	buf[len++] = u8Index;
	buf[len++] = 0x10;
	buf[len++] = 0x03;
	LOGI("MCU_UART: TX-ACK => 10 02 %02X %02X 10 03\n", u8Type, u8Index);
	McuSerialport_Write(buf, len);
}

/*
 *******************************************************************************
 Function Name:		McuUartRxAnalyze
 Input Params:		u8Value: �������е�һ���ֽ�
 Output Params:		NONE
 Return:			true: δ���ִ���
 					false: ���ֽ�������
 Description:		���������ֽ����룬������Э���ʽ��
 Autor:				fanxueming
 Date:				2015.9.30
 *******************************************************************************
 Modified by:		
 Modified Date:		
 Description:		
 *******************************************************************************
*/
bool McuUartRxAnalyze(uint8 u8Value)
{
	struct ProtocolPackT* ptPack;
	ptPack = &(l_ptRxPackCache[l_u32RxPackSet]);
	if(l_u8Rx10 == 0x10)
	{
		l_u8Rx10 = 0;
		switch(u8Value)
		{
		case 0x10:
			break;
		case 0x02:
			if(l_u8RxStep != MCUUART_STEP_NONE)
			{
				/* ��һ����Ϣ��ʧβ */
				McuUartPrintfPack("MCU_UART: miss tail\n", ptPack, l_u8RxStep, false);
			}
			l_u8RxStep = MCUUART_STEP_HEAD;
			l_u8RxChksum = 0x00;
			return true;
		case 0x03:
			McuUartReceivedPack();
			l_u8RxStep = MCUUART_STEP_NONE;
			break;
		default:
			/* ��������� */
			LOGI("MCU_UART: error data => 10 %02X\n", u8Value);
			return false;
		}
	}
	else
	{
		if(u8Value == 0x10)
		{
			l_u8Rx10 = 0x10;
			return true;
		}
	}
	if(l_u8RxStep < MCUUART_STEP_CHKSUM)
	{
		l_u8RxChksum ^= u8Value;
	}
	switch(l_u8RxStep)
	{
	case MCUUART_STEP_NONE:
		break;
	case MCUUART_STEP_HEAD:
		ptPack->m_u8Type = u8Value;
		l_u8RxStep = MCUUART_STEP_TYPE;
		break;
	case MCUUART_STEP_TYPE:
		ptPack->m_u8Index = u8Value;
		l_u8RxStep = MCUUART_STEP_INDEX;
		break;
	case MCUUART_STEP_INDEX:
		ptPack->m_u8Device = u8Value;
		l_u8RxStep = MCUUART_STEP_DEVICE;
		break;
	case MCUUART_STEP_DEVICE:
		ptPack->m_u8Length = u8Value;
		l_u8RxStep = MCUUART_STEP_LENGTH;
		l_u8RxDataLen = 0;
		break;
	case MCUUART_STEP_LENGTH:
	case MCUUART_STEP_DATA:
		if(l_u8RxDataLen >= ptPack->m_u8Length)
		{
			ptPack->m_u8Checksum = u8Value;
			l_u8RxStep = MCUUART_STEP_CHKSUM;
		}
		else
		{
			ptPack->m_pu8Data[l_u8RxDataLen] = u8Value;
			l_u8RxDataLen++;
			l_u8RxStep = MCUUART_STEP_DATA;
		}
		break;
	case MCUUART_STEP_CHKSUM:
	case MCUUART_STEP_TAIL:
		/* ���������������� */
		break;
	default:
		l_u8RxStep = MCUUART_STEP_NONE;
		break;
	}
	return true;
}

/*
 *******************************************************************************
 Function Name:		McuUartReceivedPack
 Input Params:		NONE
 Output Params:		NONE
 Return:			NONE
 Description:		���յ�һ�����ݰ�
 Autor:				fanxueming
 Date:				2015.9.30
 *******************************************************************************
 Modified by:		
 Modified Date:		
 Description:		
 *******************************************************************************
*/
static void McuUartReceivedPack(void)
{
	LOGI("McuUartReceivedPack");
	struct ProtocolPackT* ptPack;
	uint32 p_set;
	uint32 p_get;
	ptPack = &(l_ptRxPackCache[l_u32RxPackSet]);
	if(l_u8RxStep < MCUUART_STEP_TYPE)
	{
		/* �������ݲ����� */
		McuUartPrintfPack("MCU_UART: pack is incomplete\n", ptPack, l_u8RxStep, true);
		return;
	}
	if((ptPack->m_u8Type == 0xAA) || (ptPack->m_u8Type == 0xBB))
	{
		if(l_u8RxStep < MCUUART_STEP_CHKSUM)
		{
			/* �������ݲ����� */
			McuUartPrintfPack("MCU_UART: RX-PACK is incomplete\n", ptPack, l_u8RxStep, true);
			return;
		}
		if(l_u8RxChksum != 0)
		{
			/* checksum ���� */
			McuUartPrintfPack("MCU_UART: RX-PACK checksum is error\n", ptPack, l_u8RxStep, true);
			McuUartTxPackAck(0x05, ptPack->m_u8Index);
			return;
		}
		McuUartPrintfPack("MCU_UART: RX-PACK =>", ptPack, l_u8RxStep, true);
		if(ptPack->m_u8Type == 0xAA)
		{
			McuUartTxPackAck(0x55, ptPack->m_u8Index);
		}
		pthread_mutex_lock(&mutex_RxPack);
		p_set = l_u32RxPackSet+1;
		if(p_set >= MCU_PROTOCOL_PACK_RX_SIZE)
		{
			p_set  = 0;
		}
		/*
		if(p_set == l_u32RxPackGet)
		{
			p_get = l_u32RxPackGet+1;
			if(p_get >= MCU_PROTOCOL_PACK_RX_SIZE)
			{
				p_get = 0;
			}
			l_u32RxPackGet = p_get;
		}
		l_u32RxPackSet = p_set;
		*/
		/* �����ɵģ������µ� */
		if(p_set != l_u32RxPackGet)
		{
			l_u32RxPackSet = p_set;
		}
		pthread_mutex_unlock(&mutex_RxPack);
		onReceiveData(ptPack->m_u8Length,ptPack->m_pu8Data);

	}
	else if((ptPack->m_u8Type == 0x55) || (ptPack->m_u8Type == 0x05))
	{
		if(l_u8RxStep < MCUUART_STEP_INDEX)
		{
			/* �������ݲ����� */
			McuUartPrintfPack("MCU_UART: RX-ACK is incomplete\n", ptPack, l_u8RxStep, true);
			return;
		}
		McuUartPrintfPack("MCU_UART: RX-ACK =>", ptPack, l_u8RxStep, true);
		if(ptPack->m_u8Type == 0x55)
		{
			if(ptPack->m_u8Index == l_ptTxSend->m_u8Index)
			{
				l_ptTxSend = null;
			}
		}
		else
		{
		    //�ط�
		    McuUartTxPackSend();
		}
	}
	else
	{
		return;
	}
}

/*
 *******************************************************************************
 Function Name:		McuUartGetPack
 Input Params:		NONE
 Output Params:		ptPack
 Return:			true: ȡ���ɹ�
 					false: û�����ݰ�
 Description:		ȡ��һ�����ݰ�
 Autor:				fanxueming
 Date:				2015.9.30
 *******************************************************************************
 Modified by:		
 Modified Date:		
 Description:		
 *******************************************************************************
*/
bool McuUartGetPack(struct ProtocolPackT* ptPack)
{
	struct ProtocolPackT* ptGet;
	uint8 i;
	uint32 p_get;
	pthread_mutex_lock(&mutex_RxPack);
	if(l_u32RxPackGet == l_u32RxPackSet)
	{
		pthread_mutex_unlock(&mutex_RxPack);
		return false;
	}
	ptGet = &(l_ptRxPackCache[l_u32RxPackGet]);
	ptPack->m_u8Type = ptGet->m_u8Type;
	ptPack->m_u8Index = ptGet->m_u8Index;
	ptPack->m_u8Device = ptGet->m_u8Device;
	ptPack->m_u8Length = ptGet->m_u8Length;
	ptPack->m_u8Checksum = ptGet->m_u8Checksum;
	for(i=0; i<ptGet->m_u8Length; i++)
	{
		ptPack->m_pu8Data[i] = ptGet->m_pu8Data[i];
	}
	p_get = l_u32RxPackGet+1;
	if(p_get >= MCU_PROTOCOL_PACK_RX_SIZE)
	{
		p_get = 0;
	}
	l_u32RxPackGet = p_get;
	pthread_mutex_unlock(&mutex_RxPack);
	return true;
}

/*
 *******************************************************************************
 Function Name:		McuUartPeekPack
 Input Params:		NONE
 Output Params:		ptPack
 Return:			true: ��ȡ�ɹ�
 					false: û�����ݰ�
 Description:		��ȡ����ȡ��һ�����ݰ�
 Autor:				fanxueming
 Date:				2015.9.30
 *******************************************************************************
 Modified by:		
 Modified Date:		
 Description:		
 *******************************************************************************
*/
bool McuUartPeekPack(struct ProtocolPackT* ptPack)
{
	struct ProtocolPackT* ptGet;
	uint8 i;
	if(l_u32RxPackGet == l_u32RxPackSet)
	{
		return false;
	}
	ptGet = &(l_ptRxPackCache[l_u32RxPackGet]);
	ptPack->m_u8Type = ptGet->m_u8Type;
	ptPack->m_u8Index = ptGet->m_u8Index;
	ptPack->m_u8Device = ptGet->m_u8Device;
	ptPack->m_u8Length = ptGet->m_u8Length;
	ptPack->m_u8Checksum = ptGet->m_u8Checksum;
	for(i=0; i<ptGet->m_u8Length; i++)
	{
		ptPack->m_pu8Data[i] = ptGet->m_pu8Data[i];
	}
	return true;
}

/*
 *******************************************************************************
 Function Name:		McuUartPeekPack
 Input Params:		NONE
 Output Params:		ptPack
 Return:			true: ��ȡ�ɹ�
 					false: û�����ݰ�
 Description:		��ȡ����ȡ��һ�����ݰ�
 Autor:				fanxueming
 Date:				2015.9.30
 *******************************************************************************
 Modified by:		
 Modified Date:		
 Description:		
 *******************************************************************************
*/
bool McuUartSendPack(uint8 u8Device, uint8* pu8Data, uint8 u8Length, bool bNeedAck)
{
	struct ProtocolPackT* ptSet;
	uint32 p_set;
	uint8 i;
	uint8 chksum;
	p_set = l_u32TxPackSet+1;
	if(p_set >= MCU_PROTOCOL_PACK_TX_SIZE)
	{
		p_set = 0;
	}
	LOGI("MCU_UART: TX-CACHE, set=%ld, get=%ld. => ", l_u32TxPackSet, l_u32TxPackGet);
	LOGI("u8Device=%02X, bNeedAck=%d, pu8Data=", u8Device, bNeedAck);
	for(i=0; i<u8Length; i++)
	{
		LOGI(" %02X", pu8Data[i]);
	}
	if(p_set == l_u32TxPackGet)
	{
		/* ���ͻ����������� */
		//MCU_DEBUG(LOGI(" no cache\n"));
		LOGE(" no cache\n");
		return false;
	}
	LOGI(" in %ld\n", p_set);
	ptSet = &l_ptTxPackCache[l_u32TxPackSet];
	if(bNeedAck)
	{
		ptSet->m_u8Type = 0xAA;
	}
	else
	{
		ptSet->m_u8Type = 0xBB;
	}
	ptSet->m_u8Index = l_u8TxIndex++;
	ptSet->m_u8Device = u8Device;
	ptSet->m_u8Length = u8Length;
	chksum = ptSet->m_u8Type ^ ptSet->m_u8Index ^ ptSet->m_u8Device ^ ptSet->m_u8Length;
	for(i=0; i<u8Length; i++)
	{
		ptSet->m_pu8Data[i] = pu8Data[i];
		chksum ^= pu8Data[i];
	}
	ptSet->m_u8Checksum = chksum;
	l_u32TxPackSet = p_set;
	return true;
}



//#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <dirent.h>
//#include <errno.h>

#include <unistd.h>
#include <time.h>

//#include <pwd.h>
#include <pthread.h>
#include <semaphore.h>

#include "mcu.h"
#include "McuUart.h"
#include "McuSerialport.h"
#include "McuSerialJNI.h"
#include "McuComm.h"


static const char *PORT_NAME="/dev/ttyHS0";

static pthread_t l_TRxThread;
static sem_t l_TRxSem;
static bool l_bTRxThreadStop;
static bool l_bTRxThreadRun;
static bool l_bCommOpen = false;
static char l_cTxType = 'm';

static void sleep_ms(int ms);
static void McuComm_TRThread(void);

bool McuComm_Open(void)
{
	int error;
	if(l_bCommOpen)
	{
		LOGI("MCU_COMM: had Opened\n");
		return false;
	}
	l_bTRxThreadStop = false;
	l_bTRxThreadRun = false;
	McuUartInit();
	error = sem_init(&l_TRxSem, 0, 0);
	if(error != 0)
	{
		LOGI("MCU_COMM: sem(rx) initial error\n");
		return false;
	}
	error = pthread_create(&l_TRxThread, null, (void*)McuComm_TRThread, null);
	if(error != 0)
	{
		sem_destroy(&l_TRxSem);
		LOGI("MCU_COMM: create McuComm_Thread error\n");
		return false;
	}
	l_bTRxThreadRun = true;
	McuSerialport_Open(PORT_NAME);
	if(!McuSerialport_IsOpen())
	{
		l_bTRxThreadStop = true;
		sem_post(&l_TRxSem);
		while(l_bTRxThreadRun)
		{
			sleep_ms(1);
		}
		sem_destroy(&l_TRxSem);
		LOGI("MCU_COMM: can not open %s\n", PORT_NAME);
		return false;
	}
	McuSerialport_Clear();
	l_bCommOpen = true;
	LOGI("MCU_COMM: Open OK, => %s\n", PORT_NAME);
	return true;
}

bool McuComm_Close(void)
{
	if(!l_bCommOpen)
	{
		LOGI("MCU_COMM: had Closed\n");
		return false;
	}
	l_bTRxThreadStop = true;
	sem_post(&l_TRxSem);
	while(l_bTRxThreadRun)
	{
		sleep_ms(1);
	}
	McuSerialport_Close();
	LOGI("MCU_COMM: Close OK\n");
	l_bCommOpen = false;
	return true;
}

static int sem_wait_ms(sem_t *_sem, int _ms)
{
	struct timeval now;
	struct timespec outtime;
	int s;
	int ms;
	s = _ms/1000;
	ms = _ms%1000;
	gettimeofday(&now, NULL);
	now.tv_sec += s;
	now.tv_usec += ms*1000;
	if(now.tv_usec >= 1000000)
	{
		now.tv_sec += now.tv_usec / 1000000;
		now.tv_usec %= 1000000;
	}
	outtime.tv_sec = now.tv_sec;
	outtime.tv_nsec = now.tv_usec*1000;
	return (sem_timedwait(_sem, &outtime));
}

static void sleep_ms(int ms)
{
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = ms*1000;
	select( 0, NULL, NULL, NULL, &timeout );
}

static void McuComm_TRThread(void)
{
	int error;
	uint32 timeout;
	uint8 buf[200];
	uint16 len;
	uint16 i;
	struct ProtocolPackT pack;
	LOGI("MCU_COMM: Thread start\n");
	while(1)
	{
		timeout = McuUartGetTxWait();
		if(timeout > 0)
		{
			if(timeout > 10) timeout = 10;
			error = sem_wait_ms(&l_TRxSem, timeout);
		}
		if(l_bTRxThreadStop)
		{
			break;
		}
		McuUartTxProcess();
		
		len = 0;
		McuSerialport_Read(buf, &len, 200);
		if(len > 0)
		{
			LOGI("receive new data from mcu,length:%d",len);
		}
		for(i=0; i<len; i++)
		{
			LOGI(" %02X", buf[i]);
			McuUartRxAnalyze(buf[i]);
		}
		//while(McuUartGetPack(&pack))
		//{
			/* ����ȡ��pack */
			//McuComm_Send(pack.m_u8Device, pack.m_pu8Data, pack.m_u8Length, true);
		//	RxPackHandler(&pack);
		//}
	}
	LOGI("MCU_COMM: Thread stop\n");
	l_bTRxThreadRun = false;
}

void McuComm_Send(uint8 u8Device, uint8* pu8Data, uint8 u8Length, bool bNeedAck)
{
	bool ack;
	switch(l_cTxType)
	{
	case 'a':
		ack = true;
		break;
	case 'b':
		ack = false;
		break;
	default:
		ack = bNeedAck;
		break;
	}
	McuUartSendPack(u8Device, pu8Data, u8Length, ack);
	sem_post(&l_TRxSem);
}

void McuComm_Type(char cType)
{
	l_cTxType = (char)tolower(cType);
	MCU_DEBUG(LOGI("MCU_COMM: set type : %c\n", l_cTxType));
}

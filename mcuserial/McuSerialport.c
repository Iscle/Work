

//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
//#include <errno.h>
//#include <unistd.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <termios.h>
//#include <utils/Log.h>

#include "mcu.h"
#include "McuUart.h"
#include "McuSerialport.h"

static bool l_bMcuSerialportOpen;
static int l_FileDescriptor = -1;
void McuSerialport_Open(const char* pszPort)
{
	if(l_FileDescriptor >= 0)
	{
		LOGI("MCU_PORT: has opened.\n");
		return;
	}
	l_FileDescriptor = open(pszPort, O_RDWR|O_NOCTTY|O_NDELAY);
	//l_FileDescriptor = open(pszPort, O_RDWR);
	if(l_FileDescriptor < 0)
	{
		LOGI("MCU_PORT: open error.\n");
		return;
	}
	// configure port
	struct termios tio;
	if(tcgetattr(l_FileDescriptor, &tio))
	{
		memset(&tio, 0, sizeof(tio));
	}
    tio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    tio.c_oflag &= ~OPOST;
    tio.c_iflag = IGNPAR;
    tio.c_lflag = 0;
    tio.c_cc[VTIME] = 0;
    //tio.c_cc[VMIN] = 1;
    tio.c_cc[VMIN] = 0;
    tcsetattr(l_FileDescriptor, TCSANOW, &tio);
    tcflush(l_FileDescriptor, TCIFLUSH);
    LOGI("MCU_PORT: opened. ==>%d.\n", l_FileDescriptor);
}


void McuSerialport_Close(void)
{
	LOGI("MCU_PORT close begin");
	if(l_FileDescriptor < 0)
	{
		LOGI("MCU_PORT: has closed.\n");
	}
	close(l_FileDescriptor);
	l_FileDescriptor = -1;
	LOGI("MCU_PORT: closed.\n");
}

void McuSerialport_Clear(void)
{
	if(l_FileDescriptor < 0)
	{
		return;
	}
	tcflush(l_FileDescriptor, TCIOFLUSH);
}

bool McuSerialport_IsOpen(void)
{
	return ((l_FileDescriptor>=0)?true:false);
}

bool McuSerialport_Write(uint8* pu8Buf, uint16 u16Len)
{
	int len;
	if(l_FileDescriptor < 0)
	{
		LOGD("McuSerialport_Write,l_FileDescriptor < 0");
		return false;
	}
	len = write(l_FileDescriptor, pu8Buf, u16Len);
	if(len < 0)
	{
		LOGD("McuSerialport_Write failed,len < 0");
		return false;
	}
	LOGD("McuSerialport_Write,length:%d",len);
	return true;
}

bool McuSerialport_Read(uint8* pu8Buf, uint16* pu16ReadLen, uint16 u16Len)
{
	int len;
	if(l_FileDescriptor < 0)
	{
		LOGD("read data failed,serial is close");
		*pu16ReadLen = 0;
		return false;
	}
	len = read(l_FileDescriptor, pu8Buf, u16Len);
	if(len < 0)
	{
		LOGD("read data null");
		return false;
	}
	*pu16ReadLen = (uint16)len;
	//LOGD("McuSerialport_Read,length:%d",len);
	return true;
}


#ifndef  __MCU_TYPE_H__
#define  __MCU_TYPE_H__

#include  <android/log.h>

#define LOG_TAG "[OBD_SERIAL_JNI]"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#ifdef __cplusplus									/* for C++ compiler */
extern "C" {
#endif

typedef unsigned char 	uint8;
typedef signed char		int8;
typedef unsigned short	uint16;
typedef signed short	int16;
typedef unsigned long	uint32;
typedef signed long		int32;

#define null	0


#ifdef __cplusplus									/* for C++ compiler */
	}
#endif

#endif	/* __MCU_TYPE_H__ */

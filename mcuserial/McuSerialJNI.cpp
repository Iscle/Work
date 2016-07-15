/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <mtd/mtd-user.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include  <android/log.h>
//#include <utils/Log.h>
//#include <utils/String8.h>


#include "McuExtern.h"
#include "McuSerialJNI.h"


//#include "jni.h"
//#include "JNIHelp.h"
//#include <android_runtime/AndroidRuntime.h>


static const char *classPathName = "com/mct/coreservices/McuSerial";

JavaVM *gJavaVM;
jclass gJavaClass;

static jboolean
openMcuSerial(JNIEnv *env, jobject thiz)
{
    LOGI("open serial port start\n");
    if (!McuComm_Open())
    {
        return false;
    }
    //ע�⣬ֱ��ͨ������ȫ�ֵ�JNIEnv��jobject�������ڴ˱���env��thiz��ֵ�ǲ��������߳���ʹ�õ�
    //�̲߳�������env��������������JavaVMָ��������jvm���õģ����Կ���ͨ������ķ�������JavaVMָ�룬���߳���ʹ��
    env->GetJavaVM(&gJavaVM);
    //ͬ��jobject����Ҳ���������߳��й��ã������Ҫ����ȫ�ֵ�jobject�������߳��з��ʸö���
    jclass javaClass = env->FindClass(classPathName);
    //����ȫ������
    gJavaClass = (jclass) env->NewGlobalRef(javaClass);

    LOGI("open serial port end\n");
    return true;
}

static jboolean
closeMcuSerial(JNIEnv *env, jobject thiz)
{
    LOGI("close serial port start\n");
    if (!McuComm_Close())
    {
        LOGE("close serial port failed\n");
        return false;
    }
    if (gJavaClass != NULL)
    {
        env->DeleteGlobalRef(gJavaClass);
    }
    //ALOGD("close serial port success");
    LOGI("close serial port end\n");
    return true;
}

static void
sendMcuData(JNIEnv *env, jobject thiz, jint device, jbyteArray data,
        jint length, jboolean bNeedAck)
{
    LOGI("sendMcuData");
    jbyte sendData[length];
    env->GetByteArrayRegion(data, 0, length, sendData);
    McuComm_Send(device, (uint8*) sendData, length, bNeedAck);
}

void
onInitGlobalClassObj()
{

}

//��java�㷵������
void
onReceiveData(int length, uint8 data[])
{
    LOGI("onReceiveData");
    JNIEnv *env;
    //��ȫ�ֵ�JavaVM�л�ȡ����������
    int status = gJavaVM->AttachCurrentThread(&env, NULL);
    LOGI("AttachCurrentThread result:%i", status);
    if (gJavaClass == NULL)
    {
        LOGI("global class reference is NULL");
        return;
    }
    jobject newObj = env->AllocObject(gJavaClass);
    if (newObj == NULL)
    {
        LOGI("alloc new object failed\n");
    }
    jmethodID javaCallback = env->GetMethodID(gJavaClass, "onReceiveData",
            "(I[B)V");
    if (javaCallback == NULL)
    {
        LOGI("Fail to find method onReceiveData");
    }
    jbyte byteBuffer[length];
    for (int i = 0; i < length; i++)
    {
        byteBuffer[i] = data[i];
    }
    //��������ת��ΪjbyteArray
    jbyteArray recvData = env->NewByteArray(length);
    env->SetByteArrayRegion(recvData, 0, length, byteBuffer);

    env->CallVoidMethod(newObj, javaCallback, length, recvData);
    gJavaVM->DetachCurrentThread();
}

static JNINativeMethod methods[] = { { "openMcuSerial", "()Z",
        (void *) openMcuSerial }, { "closeMcuSerial", "()Z",
        (void *) closeMcuSerial }, { "sendMcuData", "(I[BIZ)V",
        (void *) sendMcuData }, };

static int
registerNativeMethods(JNIEnv* env, const char* className,
        JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL)
    {
        LOGI("Native registration unable to find class '%s'", className);
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0)
    {
        LOGI("RegisterNatives failed for '%s'", className);
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

static int
registerNatives(JNIEnv* env)
{
    if (!registerNativeMethods(env, classPathName, methods,
            sizeof(methods) / sizeof(methods[0])))
    {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

typedef union
{
        JNIEnv* env;
        void* venv;
} UnionJNIEnvToVoid;

jint
JNI_OnLoad(JavaVM* vm, void* reserved)
{
    UnionJNIEnvToVoid uenv;
    uenv.venv = NULL;
    jint result = -1;
    JNIEnv* env = NULL;

    LOGI("*********JNI_OnLoad*************");

    if (vm->GetEnv(&uenv.venv, JNI_VERSION_1_4) != JNI_OK)
    {
        LOGI("ERROR: GetEnv failed");
        goto bail;
    }
    env = uenv.env;

    if (registerNatives(env) != JNI_TRUE)
    {
        LOGI("ERROR: registerNatives failed");
        goto bail;
    }

    result = JNI_VERSION_1_4;

    bail: return result;
}

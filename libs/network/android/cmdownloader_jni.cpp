// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmdownloader_jni.cpp
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "cmdownloader.h"
#include "cmdownloader_jni.h"
#include "tinyxml.h"
#include "android/env.h"

struct fields_t {
    jmethodID callback1;       //OnDownload
    jmethodID callback2;       //OnProgress
    jclass    clazz;
    jfieldID  mObj;
};

static fields_t gCMDownloaderFieldID;

CMNotifyDownloadAndroid::CMNotifyDownloadAndroid(IMNotifyDownload* pNotify)
{
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("CMNotifyDownloadAndroid::CMNotifyDownloadAndroid GetEnv failed");
		return ;
	}

    jmethodID constructor = env->GetMethodID(gCMDownloaderFieldID.clazz, "<init>", "()V");
    if (constructor == NULL) {
        CM_ERR("Can't find class CMDownloader constructor");
        return ;
    }

    m_obj = env->NewGlobalRef(env->NewObject(gCMDownloaderFieldID.clazz, constructor));
	m_pNotify = pNotify;
	env->SetIntField(m_obj, gCMDownloaderFieldID.mObj, (int)m_pNotify);
}

CMNotifyDownloadAndroid::~CMNotifyDownloadAndroid()
{
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("CMNotifyDownloadAndroid::~CMNotifyDownloadAndroid GetEnv failed");
		return ;
	}
	if(m_obj)
	{
		env->DeleteGlobalRef(m_obj);
		m_obj = NULL;
	}
	m_pNotify = NULL;
}

IMNotifyDownload* CMNotifyDownloadAndroid::SetNotify(IMNotifyDownload* pNotify)
{
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("CMNotifyDownloadAndroid::SetNotify GetEnv failed");
		return NULL;
	}

	IMNotifyDownload* pTmp = m_pNotify;
	m_pNotify = pNotify;
	env->SetIntField(m_obj, gCMDownloaderFieldID.mObj, (int)m_pNotify);
	return pTmp;
}

void CMNotifyDownloadAndroid::OnProgress(unsigned int nRate)
{
	JNIEnv*  env;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("CMNotifyDownloadAndroid::OnProgress GetEnv failed");
		return ;
	}

	env->CallVoidMethod(m_obj,gCMDownloaderFieldID.callback2, nRate);
}

void CMNotifyDownloadAndroid::OnDownload(unsigned int nCode, CMDownloader* pDownloader)
{
	JNIEnv*  env;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("CMNotifyDownloadAndroid::OnDownload GetEnv failed");
		return ;
	}

	env->CallVoidMethod(m_obj,gCMDownloaderFieldID.callback1, nCode, (int)pDownloader);
}

static void CMDownloader_nativeOnProgress(JNIEnv* env, jobject thiz, int nRate)
{
    IMNotifyDownload* pObj = (IMNotifyDownload*)env->GetIntField(thiz, gCMDownloaderFieldID.mObj);

    if (pObj)
    	pObj->OnProgress((unsigned int)nRate);
}

static void CMDownloader_nativeOnDownload(JNIEnv* env, jobject thiz, int nCode, int pDownloader)
{
    IMNotifyDownload* pObj = (IMNotifyDownload*)env->GetIntField(thiz, gCMDownloaderFieldID.mObj);

    if (pObj)
    	pObj->OnDownload((unsigned int)nCode, (CMDownloader*)pDownloader);
}

int register_com_wunding_mlplayer_business_CMDownloader(JNIEnv* env) {
    static JNINativeMethod CMDownloaderMethods[] = {
        { "nativeOnDownload", "(II)V", (void*)CMDownloader_nativeOnDownload },
        { "nativeOnProgress", "(I)V", (void*)CMDownloader_nativeOnProgress }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMDownloader");
    if (clazz == 0) {
        CM_ERR("class CMDownloader no found");
        return -1;
    }
    gCMDownloaderFieldID.clazz = (jclass)env->NewGlobalRef(clazz);

    gCMDownloaderFieldID.mObj = env->GetFieldID(clazz, "mObj", "I");
    if (gCMDownloaderFieldID.mObj == 0) {
        CM_ERR("CMDownloader no found mObj");
        return -1;
    }

    gCMDownloaderFieldID.callback1 = env->GetMethodID(
            clazz, "OnDownload", "(II)V");
    if (gCMDownloaderFieldID.callback1 == NULL) {
        CM_ERR("CMDownloader no found callback1");
        return -1;
    }

    gCMDownloaderFieldID.callback2 = env->GetMethodID(
            clazz, "OnProgress", "(I)V");
    if (gCMDownloaderFieldID.callback2 == NULL) {
        CM_ERR("CMDownloader no found callback2");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMDownloaderMethods,
            sizeof(CMDownloaderMethods) / sizeof(CMDownloaderMethods[0]));
}



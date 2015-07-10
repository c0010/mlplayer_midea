// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmsession_jni.cpp
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "cmsession_jni.h"
#include "cmsession.h"
#include "tinyxml.h"
#include "android/env.h"

struct fields_t {
    jmethodID callback;       //... callback method
    jclass    clazz;
    jfieldID  mObj;
    jfieldID  mCmdID;
    jfieldID  mCode;
    jfieldID  mDoc;
};

static fields_t gCMSessionFieldID;

CMNotifySessionAndroid::CMNotifySessionAndroid(IMNotifySession* pNotify)
{
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
		return ;

    jmethodID constructor = env->GetMethodID(gCMSessionFieldID.clazz, "<init>", "()V");
    if (constructor == NULL) {
        CM_ERR("Can't find class CMSession constructor");
        return ;
    }

    m_obj = env->NewGlobalRef(env->NewObject(gCMSessionFieldID.clazz, constructor));
	m_pNotify = pNotify;
}

CMNotifySessionAndroid::~CMNotifySessionAndroid()
{
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
		return ;
	if(m_obj)
	{
		env->DeleteGlobalRef(m_obj);
		m_obj = NULL;
	}
	m_pNotify = NULL;
}

void CMNotifySessionAndroid::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	JNIEnv*  env;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
		return ;

	env->SetIntField(m_obj, gCMSessionFieldID.mObj, (int)m_pNotify);
	env->SetIntField(m_obj, gCMSessionFieldID.mCmdID, (int)nCmdID);
	env->SetIntField(m_obj, gCMSessionFieldID.mCode, (int)nCode);
	env->SetIntField(m_obj, gCMSessionFieldID.mDoc, (int)pDoc);
	env->CallVoidMethod(m_obj,gCMSessionFieldID.callback);
}

static void CMSession_nativeOnSessionCmd(JNIEnv* env, jobject thiz)
{
    IMNotifySession* pObj = (IMNotifySession*)env->GetIntField(thiz, gCMSessionFieldID.mObj);
    unsigned int nCmdID = (unsigned int)env->GetIntField(thiz, gCMSessionFieldID.mCmdID);
    unsigned int nCode = (unsigned int)env->GetIntField(thiz, gCMSessionFieldID.mCode);
    TiXmlDocument* pDoc = (TiXmlDocument*)env->GetIntField(thiz, gCMSessionFieldID.mDoc);

	CM_LOGP(CM_LOGL_DEBUG, "OnSessionCmd obj %0x cmd %d code %d doc %0x", pObj, nCmdID, nCode, pDoc);

    pObj->OnSessionCmd(nCmdID, nCode, pDoc);
}

int register_com_wunding_mlplayer_business_CMSession(JNIEnv* env) {
    static JNINativeMethod CMSessionMethods[] = {
        { "nativeOnSessionCmd", "()V", (void*)CMSession_nativeOnSessionCmd }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMSession");
    if (clazz == 0) {
        CM_ERR("class CMSession no found");
        return -1;
    }
    gCMSessionFieldID.clazz = (jclass)env->NewGlobalRef(clazz);

    gCMSessionFieldID.mObj = env->GetFieldID(clazz, "mObj", "I");
    if (gCMSessionFieldID.mObj == 0) {
        CM_ERR("CMSession no found mObj");
        return -1;
    }

    gCMSessionFieldID.mCmdID = env->GetFieldID(clazz, "mCmdID", "I");
    if (gCMSessionFieldID.mCmdID == 0) {
        CM_ERR("CMSession no found mCmdID");
        return -1;
    }

    gCMSessionFieldID.mCode = env->GetFieldID(clazz, "mCode", "I");
    if (gCMSessionFieldID.mCode == 0) {
        CM_ERR("CMSession no found mCode");
        return -1;
    }

    gCMSessionFieldID.mDoc = env->GetFieldID(clazz, "mDoc", "I");
    if (gCMSessionFieldID.mDoc == 0) {
        CM_ERR("CMSession no found mDoc");
        return -1;
    }

    // Get the postEvent method
    gCMSessionFieldID.callback = env->GetMethodID(
            clazz, "OnSessionCmd", "()V");
    if (gCMSessionFieldID.callback == NULL) {
        CM_ERR("CMSession no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMSessionMethods,
            sizeof(CMSessionMethods) / sizeof(CMSessionMethods[0]));
}



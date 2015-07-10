// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmwetools_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmwetools.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMWetools {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMWetoolsFieldID;

static void CMWetools_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMWetools when setting up callback.");
        return;
    }
    callback_cookie_CMWetools* pCookie = new callback_cookie_CMWetools;
    pCookie->listener1 = new CMUpdateDataListener(gCMWetoolsFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMWetoolsFieldID.jniData, (int)pCookie);

    CMWetools* pObj = new CMWetools(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMWetoolsFieldID.nativeJavaObj, (int)pObj);
}

static void CMWetools_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMWetools *pObj = (CMWetools*)env->GetIntField(thiz, gCMWetoolsFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMWetools* pCookie = (callback_cookie_CMWetools *)env->GetIntField(
        thiz, gCMWetoolsFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMWetoolsFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMWetoolsFieldID.jniData, 0);
}

static void CMWetools_GetWetool(JNIEnv* env, jobject thiz)
{
    CMWetools* pObj = (CMWetools*)env->GetIntField(thiz, gCMWetoolsFieldID.nativeJavaObj);

    pObj->GetWetool();
}

static jstring CMWetools_GetWesize(JNIEnv* env, jobject thiz)
{
    CMWetools* pObj = (CMWetools*)env->GetIntField(thiz, gCMWetoolsFieldID.nativeJavaObj);

    const char* ret = pObj->GetWesize();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMWetools_GetWeversion(JNIEnv* env, jobject thiz)
{
    CMWetools* pObj = (CMWetools*)env->GetIntField(thiz, gCMWetoolsFieldID.nativeJavaObj);

    const char* ret = pObj->GetWeversion();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMWetools_GetWeUrl(JNIEnv* env, jobject thiz)
{
    CMWetools* pObj = (CMWetools*)env->GetIntField(thiz, gCMWetoolsFieldID.nativeJavaObj);

    const char* ret = pObj->GetWeUrl();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

int register_com_wunding_mlplayer_business_CMWetools(JNIEnv* env) {
    static JNINativeMethod CMWetoolsMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMWetools_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMWetools_nativeDestructor },
        { "GetWetool", "()V", (void*)CMWetools_GetWetool },
        { "GetWesize", "()Ljava/lang/String;", (void*)CMWetools_GetWesize },
        { "GetWeversion", "()Ljava/lang/String;", (void*)CMWetools_GetWeversion },
        { "GetWeUrl", "()Ljava/lang/String;", (void*)CMWetools_GetWeUrl }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMWetools");
    if (clazz == 0) {
        CM_ERR("class CMWetools no found");
        return -1;
    }

    gCMWetoolsFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMWetoolsFieldID.nativeJavaObj == 0) {
        CM_ERR("CMWetools no found mNativeObj");
        return -1;
    }

    gCMWetoolsFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMWetoolsFieldID.jniData == 0) {
        CM_ERR("CMWetools no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMWetoolsFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMWetoolsFieldID.callback == NULL) {
        CM_ERR("CMWetools no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMWetoolsMethods,
            sizeof(CMWetoolsMethods) / sizeof(CMWetoolsMethods[0]));
}


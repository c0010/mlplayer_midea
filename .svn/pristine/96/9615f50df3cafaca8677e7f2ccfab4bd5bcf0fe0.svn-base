// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmspecialtopic_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmspecialtopic.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMSpecialTopic {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMSpecialTopicFieldID;

static void CMSpecialTopic_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMSpecialTopic when setting up callback.");
        return;
    }
    callback_cookie_CMSpecialTopic* pCookie = new callback_cookie_CMSpecialTopic;
    pCookie->listener1 = new CMUpdateDataListener(gCMSpecialTopicFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMSpecialTopicFieldID.jniData, (int)pCookie);

    CMSpecialTopic* pObj = new CMSpecialTopic(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMSpecialTopicFieldID.nativeJavaObj, (int)pObj);
}

static void CMSpecialTopic_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMSpecialTopic *pObj = (CMSpecialTopic*)env->GetIntField(thiz, gCMSpecialTopicFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMSpecialTopic* pCookie = (callback_cookie_CMSpecialTopic *)env->GetIntField(
        thiz, gCMSpecialTopicFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMSpecialTopicFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMSpecialTopicFieldID.jniData, 0);
}

static void CMSpecialTopic_GetSpecialTopic(JNIEnv* env, jobject thiz, jstring sID)
{
    CMSpecialTopic* pObj = (CMSpecialTopic*)env->GetIntField(thiz, gCMSpecialTopicFieldID.nativeJavaObj);

    const jchar* jsID = env->GetStringChars(sID, NULL);
    jsize sizesID = env->GetStringLength(sID);
    char* psID = UTF16toUTF8((jchar*)jsID, (size_t*)&sizesID);
    pObj->GetSpecialTopic(psID);
    env->ReleaseStringChars(sID, jsID);
    free(psID);
}

static jstring CMSpecialTopic_GetTitle(JNIEnv* env, jobject thiz)
{
    CMSpecialTopic* pObj = (CMSpecialTopic*)env->GetIntField(thiz, gCMSpecialTopicFieldID.nativeJavaObj);

    const char* ret = pObj->GetTitle();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMSpecialTopic_GetImage(JNIEnv* env, jobject thiz)
{
    CMSpecialTopic* pObj = (CMSpecialTopic*)env->GetIntField(thiz, gCMSpecialTopicFieldID.nativeJavaObj);

    const char* ret = pObj->GetImage();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

int register_com_wunding_mlplayer_business_CMSpecialTopic(JNIEnv* env) {
    static JNINativeMethod CMSpecialTopicMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMSpecialTopic_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMSpecialTopic_nativeDestructor },
        { "GetSpecialTopic", "(Ljava/lang/String;)V", (void*)CMSpecialTopic_GetSpecialTopic },
        { "GetTitle", "()Ljava/lang/String;", (void*)CMSpecialTopic_GetTitle },
        { "GetImage", "()Ljava/lang/String;", (void*)CMSpecialTopic_GetImage }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMSpecialTopic");
    if (clazz == 0) {
        CM_ERR("class CMSpecialTopic no found");
        return -1;
    }

    gCMSpecialTopicFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMSpecialTopicFieldID.nativeJavaObj == 0) {
        CM_ERR("CMSpecialTopic no found mNativeObj");
        return -1;
    }

    gCMSpecialTopicFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMSpecialTopicFieldID.jniData == 0) {
        CM_ERR("CMSpecialTopic no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMSpecialTopicFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMSpecialTopicFieldID.callback == NULL) {
        CM_ERR("CMSpecialTopic no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMSpecialTopicMethods,
            sizeof(CMSpecialTopicMethods) / sizeof(CMSpecialTopicMethods[0]));
}


// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmmessage_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmmessage.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMMessage {
    jclass      info_class;
    jobject     ref;
    CMSimpleResultListener* listener1;
};

fields_t gCMMessageFieldID;

static void CMMessage_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMMessage when setting up callback.");
        return;
    }
    callback_cookie_CMMessage* pCookie = new callback_cookie_CMMessage;
    pCookie->listener1 = new CMSimpleResultListener(gCMMessageFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMMessageFieldID.jniData, (int)pCookie);

    CMMessage* pObj = new CMMessage();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMMessageFieldID.nativeJavaObj, (int)pObj);
}

static void CMMessage_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMMessage *pObj = (CMMessage*)env->GetIntField(thiz, gCMMessageFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMMessage* pCookie = (callback_cookie_CMMessage *)env->GetIntField(
        thiz, gCMMessageFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMMessageFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMMessageFieldID.jniData, 0);
}

static void CMMessage_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMMessage* pObj = (CMMessage*)env->GetIntField(thiz, gCMMessageFieldID.nativeJavaObj);

    callback_cookie_CMMessage* pCookie = (callback_cookie_CMMessage *)env->GetIntField(
        thiz, gCMMessageFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMSimpleResultListener(gCMMessageFieldID.callback);
        }
        
        IMSimpleResultListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        pObj->SetListener(para1);
    }

    return ;
}

static jboolean CMMessage_UploadPic(JNIEnv* env, jobject thiz, jstring filename)
{
    CMMessage* pObj = (CMMessage*)env->GetIntField(thiz, gCMMessageFieldID.nativeJavaObj);

    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->UploadPic(pfilename);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

static jstring CMMessage_GetUrl(JNIEnv* env, jobject thiz)
{
    CMMessage* pObj = (CMMessage*)env->GetIntField(thiz, gCMMessageFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sUrl.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sUrl.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMMessage_SetUrl(JNIEnv* env, jobject thiz, jstring sUrl)
{
    CMMessage* pObj = (CMMessage*)env->GetIntField(thiz, gCMMessageFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sUrl, NULL);
    jsize size = env->GetStringLength(sUrl);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sUrl = data;

    env->ReleaseStringChars(sUrl, jChar);
    
    free(data);
    
    return true;
}

static jstring CMMessage_GetThumbUrl(JNIEnv* env, jobject thiz)
{
    CMMessage* pObj = (CMMessage*)env->GetIntField(thiz, gCMMessageFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sThumbUrl.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sThumbUrl.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMMessage_SetThumbUrl(JNIEnv* env, jobject thiz, jstring sThumbUrl)
{
    CMMessage* pObj = (CMMessage*)env->GetIntField(thiz, gCMMessageFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sThumbUrl, NULL);
    jsize size = env->GetStringLength(sThumbUrl);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sThumbUrl = data;

    env->ReleaseStringChars(sThumbUrl, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_CMMessage(JNIEnv* env) {
    static JNINativeMethod CMMessageMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMMessage_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMMessage_nativeDestructor },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMMessage_SetListener },
        { "UploadPic", "(Ljava/lang/String;)Z", (void*)CMMessage_UploadPic },
        { "GetUrl", "()Ljava/lang/String;", (void*)CMMessage_GetUrl },
        { "SetUrl", "(Ljava/lang/String;)Z", (void*)CMMessage_SetUrl },
        { "GetThumbUrl", "()Ljava/lang/String;", (void*)CMMessage_GetThumbUrl },
        { "SetThumbUrl", "(Ljava/lang/String;)Z", (void*)CMMessage_SetThumbUrl }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMMessage");
    if (clazz == 0) {
        CM_ERR("class CMMessage no found");
        return -1;
    }

    gCMMessageFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMMessageFieldID.nativeJavaObj == 0) {
        CM_ERR("CMMessage no found mNativeObj");
        return -1;
    }

    gCMMessageFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMMessageFieldID.jniData == 0) {
        CM_ERR("CMMessage no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMMessageFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMMessageFieldID.callback == NULL) {
        CM_ERR("CMMessage no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMMessageMethods,
            sizeof(CMMessageMethods) / sizeof(CMMessageMethods[0]));
}


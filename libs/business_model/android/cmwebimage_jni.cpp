// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmwebimage_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmwebimage.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMWebImage {
    jclass      info_class;
    jobject     ref;
    CMGetImageListener* listener1;
};

fields_t gCMWebImageFieldID;

static void CMWebImage_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMWebImage when setting up callback.");
        return;
    }
    callback_cookie_CMWebImage* pCookie = new callback_cookie_CMWebImage;
    pCookie->listener1 = new CMGetImageListener(gCMWebImageFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMWebImageFieldID.jniData, (int)pCookie);

    CMWebImage* pObj = new CMWebImage(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMWebImageFieldID.nativeJavaObj, (int)pObj);
}

static void CMWebImage_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMWebImage *pObj = (CMWebImage*)env->GetIntField(thiz, gCMWebImageFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMWebImage* pCookie = (callback_cookie_CMWebImage *)env->GetIntField(
        thiz, gCMWebImageFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMWebImageFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMWebImageFieldID.jniData, 0);
}

static jboolean CMWebImage_GetFromUrl(JNIEnv* env, jobject thiz, jint nID, jstring sUrl)
{
    CMWebImage* pObj = (CMWebImage*)env->GetIntField(thiz, gCMWebImageFieldID.nativeJavaObj);

    const jchar* jsUrl = env->GetStringChars(sUrl, NULL);
    jsize sizesUrl = env->GetStringLength(sUrl);
    char* psUrl = UTF16toUTF8((jchar*)jsUrl, (size_t*)&sizesUrl);
    BOOL ret = pObj->GetFromUrl(nID, psUrl);
    env->ReleaseStringChars(sUrl, jsUrl);
    free(psUrl);
    return ret;
}

static void CMWebImage_Cancel(JNIEnv* env, jobject thiz)
{
    CMWebImage* pObj = (CMWebImage*)env->GetIntField(thiz, gCMWebImageFieldID.nativeJavaObj);

    pObj->Cancel();
}

static jstring CMWebImage_GetFilePath(JNIEnv* env, jobject thiz, jstring sUrl)
{
    CMWebImage* pObj = (CMWebImage*)env->GetIntField(thiz, gCMWebImageFieldID.nativeJavaObj);

    const jchar* jsUrl = env->GetStringChars(sUrl, NULL);
    jsize sizesUrl = env->GetStringLength(sUrl);
    char* psUrl = UTF16toUTF8((jchar*)jsUrl, (size_t*)&sizesUrl);
    const char* ret = pObj->GetFilePath(psUrl);
    env->ReleaseStringChars(sUrl, jsUrl);
    free(psUrl);
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

int register_com_wunding_mlplayer_business_CMWebImage(JNIEnv* env) {
    static JNINativeMethod CMWebImageMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMWebImage_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMWebImage_nativeDestructor },
        { "GetFromUrl", "(ILjava/lang/String;)Z", (void*)CMWebImage_GetFromUrl },
        { "Cancel", "()V", (void*)CMWebImage_Cancel },
        { "GetFilePath", "(Ljava/lang/String;)Ljava/lang/String;", (void*)CMWebImage_GetFilePath }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMWebImage");
    if (clazz == 0) {
        CM_ERR("class CMWebImage no found");
        return -1;
    }

    gCMWebImageFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMWebImageFieldID.nativeJavaObj == 0) {
        CM_ERR("CMWebImage no found mNativeObj");
        return -1;
    }

    gCMWebImageFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMWebImageFieldID.jniData == 0) {
        CM_ERR("CMWebImage no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMWebImageFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMWebImageFieldID.callback == NULL) {
        CM_ERR("CMWebImage no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMWebImageMethods,
            sizeof(CMWebImageMethods) / sizeof(CMWebImageMethods[0]));
}


// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmsearchhotkey_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmsearchhotkey.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMSearchHotKey {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMSearchHotKeyFieldID;

static void CMSearchHotKey_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMSearchHotKey when setting up callback.");
        return;
    }
    callback_cookie_CMSearchHotKey* pCookie = new callback_cookie_CMSearchHotKey;
    pCookie->listener1 = new CMUpdateDataListener(gCMSearchHotKeyFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMSearchHotKeyFieldID.jniData, (int)pCookie);

    CMSearchHotKey* pObj = CMSearchHotKey::GetInstance();
    pObj->SetListener(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj, (int)pObj);
}

static void CMSearchHotKey_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMSearchHotKey *pObj = (CMSearchHotKey*)env->GetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMSearchHotKey* pCookie = (callback_cookie_CMSearchHotKey *)env->GetIntField(
        thiz, gCMSearchHotKeyFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMSearchHotKeyFieldID.jniData, 0);
}

static void CMSearchHotKey_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMSearchHotKey* pObj = (CMSearchHotKey*)env->GetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj);

    callback_cookie_CMSearchHotKey* pCookie = (callback_cookie_CMSearchHotKey *)env->GetIntField(
        thiz, gCMSearchHotKeyFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMSearchHotKeyFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

    }
}

static jboolean CMSearchHotKey_GetHotKey(JNIEnv* env, jobject thiz)
{
    CMSearchHotKey* pObj = (CMSearchHotKey*)env->GetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj);

    BOOL ret = pObj->GetHotKey();
    return ret;
}

static jint CMSearchHotKey_GetCourseHotKeyItemCount(JNIEnv* env, jobject thiz)
{
    CMSearchHotKey* pObj = (CMSearchHotKey*)env->GetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj);

    int ret = pObj->GetCourseHotKeyItemCount();
    return ret;
}

static jstring CMSearchHotKey_GetCourseHotKeyItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMSearchHotKey* pObj = (CMSearchHotKey*)env->GetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj);

    const char* ret = pObj->GetCourseHotKeyItem(nIndex);
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jint CMSearchHotKey_GetNewsHotKeyItemCount(JNIEnv* env, jobject thiz)
{
    CMSearchHotKey* pObj = (CMSearchHotKey*)env->GetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj);

    int ret = pObj->GetNewsHotKeyItemCount();
    return ret;
}

static jstring CMSearchHotKey_GetNewsHotKeyItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMSearchHotKey* pObj = (CMSearchHotKey*)env->GetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj);

    const char* ret = pObj->GetNewsHotKeyItem(nIndex);
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jint CMSearchHotKey_GetQaHotKeyItemCount(JNIEnv* env, jobject thiz)
{
    CMSearchHotKey* pObj = (CMSearchHotKey*)env->GetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj);

    int ret = pObj->GetQaHotKeyItemCount();
    return ret;
}

static jstring CMSearchHotKey_GetQaHotKeyItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMSearchHotKey* pObj = (CMSearchHotKey*)env->GetIntField(thiz, gCMSearchHotKeyFieldID.nativeJavaObj);

    const char* ret = pObj->GetQaHotKeyItem(nIndex);
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

int register_com_wunding_mlplayer_business_CMSearchHotKey(JNIEnv* env) {
    static JNINativeMethod CMSearchHotKeyMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMSearchHotKey_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMSearchHotKey_nativeDestructor },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMSearchHotKey_SetListener },
        { "GetHotKey", "()Z", (void*)CMSearchHotKey_GetHotKey },
        { "GetCourseHotKeyItemCount", "()I", (void*)CMSearchHotKey_GetCourseHotKeyItemCount },
        { "GetCourseHotKeyItem", "(I)Ljava/lang/String;", (void*)CMSearchHotKey_GetCourseHotKeyItem },
        { "GetNewsHotKeyItemCount", "()I", (void*)CMSearchHotKey_GetNewsHotKeyItemCount },
        { "GetNewsHotKeyItem", "(I)Ljava/lang/String;", (void*)CMSearchHotKey_GetNewsHotKeyItem },
        { "GetQaHotKeyItemCount", "()I", (void*)CMSearchHotKey_GetQaHotKeyItemCount },
        { "GetQaHotKeyItem", "(I)Ljava/lang/String;", (void*)CMSearchHotKey_GetQaHotKeyItem }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMSearchHotKey");
    if (clazz == 0) {
        CM_ERR("class CMSearchHotKey no found");
        return -1;
    }

    gCMSearchHotKeyFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMSearchHotKeyFieldID.nativeJavaObj == 0) {
        CM_ERR("CMSearchHotKey no found mNativeObj");
        return -1;
    }

    gCMSearchHotKeyFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMSearchHotKeyFieldID.jniData == 0) {
        CM_ERR("CMSearchHotKey no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMSearchHotKeyFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMSearchHotKeyFieldID.callback == NULL) {
        CM_ERR("CMSearchHotKey no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMSearchHotKeyMethods,
            sizeof(CMSearchHotKeyMethods) / sizeof(CMSearchHotKeyMethods[0]));
}


// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmupdate_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmupdate.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMUpdate {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMUpdateFieldID;

static void CMUpdate_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMUpdate when setting up callback.");
        return;
    }
    callback_cookie_CMUpdate* pCookie = new callback_cookie_CMUpdate;
    pCookie->listener1 = new CMUpdateDataListener(gCMUpdateFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMUpdateFieldID.jniData, (int)pCookie);

    CMUpdate* pObj = new CMUpdate(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMUpdateFieldID.nativeJavaObj, (int)pObj);
}

static void CMUpdate_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMUpdate *pObj = (CMUpdate*)env->GetIntField(thiz, gCMUpdateFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMUpdate* pCookie = (callback_cookie_CMUpdate *)env->GetIntField(
        thiz, gCMUpdateFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMUpdateFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMUpdateFieldID.jniData, 0);
}

static jboolean CMUpdate_HasNewVersion(JNIEnv* env, jobject thiz)
{
    CMUpdate* pObj = (CMUpdate*)env->GetIntField(thiz, gCMUpdateFieldID.nativeJavaObj);

    BOOL ret = pObj->HasNewVersion();
    return ret;
}

static jboolean CMUpdate_Update(JNIEnv* env, jobject thiz)
{
    CMUpdate* pObj = (CMUpdate*)env->GetIntField(thiz, gCMUpdateFieldID.nativeJavaObj);

    BOOL ret = pObj->Update();
    return ret;
}

static void CMUpdate_Cancel(JNIEnv* env, jobject thiz)
{
    CMUpdate* pObj = (CMUpdate*)env->GetIntField(thiz, gCMUpdateFieldID.nativeJavaObj);

    pObj->Cancel();
}

static jstring CMUpdate_GetPathName(JNIEnv* env, jobject thiz)
{
    CMUpdate* pObj = (CMUpdate*)env->GetIntField(thiz, gCMUpdateFieldID.nativeJavaObj);

    const char* ret = pObj->GetPathName();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

int register_com_wunding_mlplayer_business_CMUpdate(JNIEnv* env) {
    static JNINativeMethod CMUpdateMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMUpdate_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMUpdate_nativeDestructor },
        { "HasNewVersion", "()Z", (void*)CMUpdate_HasNewVersion },
        { "Update", "()Z", (void*)CMUpdate_Update },
        { "Cancel", "()V", (void*)CMUpdate_Cancel },
        { "GetPathName", "()Ljava/lang/String;", (void*)CMUpdate_GetPathName }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMUpdate");
    if (clazz == 0) {
        CM_ERR("class CMUpdate no found");
        return -1;
    }

    gCMUpdateFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMUpdateFieldID.nativeJavaObj == 0) {
        CM_ERR("CMUpdate no found mNativeObj");
        return -1;
    }

    gCMUpdateFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMUpdateFieldID.jniData == 0) {
        CM_ERR("CMUpdate no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMUpdateFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMUpdateFieldID.callback == NULL) {
        CM_ERR("CMUpdate no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMUpdateMethods,
            sizeof(CMUpdateMethods) / sizeof(CMUpdateMethods[0]));
}


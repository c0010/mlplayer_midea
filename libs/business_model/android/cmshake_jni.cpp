// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmshake_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmshake.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMShake {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMShakeFieldID;

static void CMShake_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMShake when setting up callback.");
        return;
    }
    callback_cookie_CMShake* pCookie = new callback_cookie_CMShake;
    pCookie->listener1 = new CMUpdateDataListener(gCMShakeFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMShakeFieldID.jniData, (int)pCookie);

    CMShake* pObj = new CMShake(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMShakeFieldID.nativeJavaObj, (int)pObj);
}

static void CMShake_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMShake *pObj = (CMShake*)env->GetIntField(thiz, gCMShakeFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMShake* pCookie = (callback_cookie_CMShake *)env->GetIntField(
        thiz, gCMShakeFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMShakeFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMShakeFieldID.jniData, 0);
}

static jboolean CMShake_Request(JNIEnv* env, jobject thiz)
{
    CMShake* pObj = (CMShake*)env->GetIntField(thiz, gCMShakeFieldID.nativeJavaObj);

    BOOL ret = pObj->Request();
    return ret;
}

int register_com_wunding_mlplayer_business_CMShake(JNIEnv* env) {
    static JNINativeMethod CMShakeMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMShake_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMShake_nativeDestructor },
        { "Request", "()Z", (void*)CMShake_Request }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMShake");
    if (clazz == 0) {
        CM_ERR("class CMShake no found");
        return -1;
    }

    gCMShakeFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMShakeFieldID.nativeJavaObj == 0) {
        CM_ERR("CMShake no found mNativeObj");
        return -1;
    }

    gCMShakeFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMShakeFieldID.jniData == 0) {
        CM_ERR("CMShake no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMShakeFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMShakeFieldID.callback == NULL) {
        CM_ERR("CMShake no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMShakeMethods,
            sizeof(CMShakeMethods) / sizeof(CMShakeMethods[0]));
}


// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmrecentcontent_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmrecentcontent.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMRecentContent {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMRecentContentFieldID;

static void CMRecentContent_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMRecentContent when setting up callback.");
        return;
    }
    callback_cookie_CMRecentContent* pCookie = new callback_cookie_CMRecentContent;
    pCookie->listener1 = new CMUpdateDataListener(gCMRecentContentFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMRecentContentFieldID.jniData, (int)pCookie);

    CMRecentContent* pObj = new CMRecentContent(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMRecentContentFieldID.nativeJavaObj, (int)pObj);
}

static void CMRecentContent_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMRecentContent *pObj = (CMRecentContent*)env->GetIntField(thiz, gCMRecentContentFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMRecentContent* pCookie = (callback_cookie_CMRecentContent *)env->GetIntField(
        thiz, gCMRecentContentFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMRecentContentFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMRecentContentFieldID.jniData, 0);
}

static jboolean CMRecentContent_Update(JNIEnv* env, jobject thiz)
{
    CMRecentContent* pObj = (CMRecentContent*)env->GetIntField(thiz, gCMRecentContentFieldID.nativeJavaObj);

    BOOL ret = pObj->Update();
    return ret;
}

int register_com_wunding_mlplayer_business_CMRecentContent(JNIEnv* env) {
    static JNINativeMethod CMRecentContentMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMRecentContent_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMRecentContent_nativeDestructor },
        { "Update", "()Z", (void*)CMRecentContent_Update }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMRecentContent");
    if (clazz == 0) {
        CM_ERR("class CMRecentContent no found");
        return -1;
    }

    gCMRecentContentFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMRecentContentFieldID.nativeJavaObj == 0) {
        CM_ERR("CMRecentContent no found mNativeObj");
        return -1;
    }

    gCMRecentContentFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMRecentContentFieldID.jniData == 0) {
        CM_ERR("CMRecentContent no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMRecentContentFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMRecentContentFieldID.callback == NULL) {
        CM_ERR("CMRecentContent no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMRecentContentMethods,
            sizeof(CMRecentContentMethods) / sizeof(CMRecentContentMethods[0]));
}


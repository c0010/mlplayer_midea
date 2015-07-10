// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmretrievepass_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmretrievepass.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMRetrievePass {
    jclass      info_class;
    jobject     ref;
    CMSimpleResultListener* listener1;
};

fields_t gCMRetrievePassFieldID;

static void CMRetrievePass_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMRetrievePass when setting up callback.");
        return;
    }
    callback_cookie_CMRetrievePass* pCookie = new callback_cookie_CMRetrievePass;
    pCookie->listener1 = new CMSimpleResultListener(gCMRetrievePassFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMRetrievePassFieldID.jniData, (int)pCookie);

    CMRetrievePass* pObj = new CMRetrievePass(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMRetrievePassFieldID.nativeJavaObj, (int)pObj);
}

static void CMRetrievePass_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMRetrievePass *pObj = (CMRetrievePass*)env->GetIntField(thiz, gCMRetrievePassFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMRetrievePass* pCookie = (callback_cookie_CMRetrievePass *)env->GetIntField(
        thiz, gCMRetrievePassFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMRetrievePassFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMRetrievePassFieldID.jniData, 0);
}

static void CMRetrievePass_Commit(JNIEnv* env, jobject thiz, jstring emialorphone)
{
    CMRetrievePass* pObj = (CMRetrievePass*)env->GetIntField(thiz, gCMRetrievePassFieldID.nativeJavaObj);

    const jchar* jemialorphone = env->GetStringChars(emialorphone, NULL);
    jsize sizeemialorphone = env->GetStringLength(emialorphone);
    char* pemialorphone = UTF16toUTF8((jchar*)jemialorphone, (size_t*)&sizeemialorphone);
    pObj->Commit(pemialorphone);
    env->ReleaseStringChars(emialorphone, jemialorphone);
    free(pemialorphone);
}

static jstring CMRetrievePass_getPMsg(JNIEnv* env, jobject thiz)
{
    CMRetrievePass* pObj = (CMRetrievePass*)env->GetIntField(thiz, gCMRetrievePassFieldID.nativeJavaObj);

    char* ret = pObj->getPMsg();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

int register_com_wunding_mlplayer_business_CMRetrievePass(JNIEnv* env) {
    static JNINativeMethod CMRetrievePassMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMRetrievePass_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMRetrievePass_nativeDestructor },
        { "Commit", "(Ljava/lang/String;)V", (void*)CMRetrievePass_Commit },
        { "getPMsg", "()Ljava/lang/String;", (void*)CMRetrievePass_getPMsg }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMRetrievePass");
    if (clazz == 0) {
        CM_ERR("class CMRetrievePass no found");
        return -1;
    }

    gCMRetrievePassFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMRetrievePassFieldID.nativeJavaObj == 0) {
        CM_ERR("CMRetrievePass no found mNativeObj");
        return -1;
    }

    gCMRetrievePassFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMRetrievePassFieldID.jniData == 0) {
        CM_ERR("CMRetrievePass no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMRetrievePassFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMRetrievePassFieldID.callback == NULL) {
        CM_ERR("CMRetrievePass no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMRetrievePassMethods,
            sizeof(CMRetrievePassMethods) / sizeof(CMRetrievePassMethods[0]));
}


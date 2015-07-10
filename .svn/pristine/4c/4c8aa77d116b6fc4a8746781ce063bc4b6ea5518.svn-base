// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmfeedback_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmfeedback.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMFeedback {
    jclass      info_class;
    jobject     ref;
    CMSimpleResultListener* listener1;
};

fields_t gCMFeedbackFieldID;

static void CMFeedback_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMFeedback when setting up callback.");
        return;
    }
    callback_cookie_CMFeedback* pCookie = new callback_cookie_CMFeedback;
    pCookie->listener1 = new CMSimpleResultListener(gCMFeedbackFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMFeedbackFieldID.jniData, (int)pCookie);

    CMFeedback* pObj = new CMFeedback(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMFeedbackFieldID.nativeJavaObj, (int)pObj);
}

static void CMFeedback_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMFeedback *pObj = (CMFeedback*)env->GetIntField(thiz, gCMFeedbackFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMFeedback* pCookie = (callback_cookie_CMFeedback *)env->GetIntField(
        thiz, gCMFeedbackFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMFeedbackFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMFeedbackFieldID.jniData, 0);
}

static void CMFeedback_CommitFeedback(JNIEnv* env, jobject thiz, jstring sSuggestion, jstring sModel)
{
    CMFeedback* pObj = (CMFeedback*)env->GetIntField(thiz, gCMFeedbackFieldID.nativeJavaObj);

    const jchar* jsSuggestion = env->GetStringChars(sSuggestion, NULL);
    jsize sizesSuggestion = env->GetStringLength(sSuggestion);
    char* psSuggestion = UTF16toUTF8((jchar*)jsSuggestion, (size_t*)&sizesSuggestion);
    const jchar* jsModel = env->GetStringChars(sModel, NULL);
    jsize sizesModel = env->GetStringLength(sModel);
    char* psModel = UTF16toUTF8((jchar*)jsModel, (size_t*)&sizesModel);
    pObj->CommitFeedback(psSuggestion, psModel);
    env->ReleaseStringChars(sSuggestion, jsSuggestion);
    free(psSuggestion);
    env->ReleaseStringChars(sModel, jsModel);
    free(psModel);
}

int register_com_wunding_mlplayer_business_CMFeedback(JNIEnv* env) {
    static JNINativeMethod CMFeedbackMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMFeedback_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMFeedback_nativeDestructor },
        { "CommitFeedback", "(Ljava/lang/String;Ljava/lang/String;)V", (void*)CMFeedback_CommitFeedback }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMFeedback");
    if (clazz == 0) {
        CM_ERR("class CMFeedback no found");
        return -1;
    }

    gCMFeedbackFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMFeedbackFieldID.nativeJavaObj == 0) {
        CM_ERR("CMFeedback no found mNativeObj");
        return -1;
    }

    gCMFeedbackFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMFeedbackFieldID.jniData == 0) {
        CM_ERR("CMFeedback no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMFeedbackFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMFeedbackFieldID.callback == NULL) {
        CM_ERR("CMFeedback no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMFeedbackMethods,
            sizeof(CMFeedbackMethods) / sizeof(CMFeedbackMethods[0]));
}


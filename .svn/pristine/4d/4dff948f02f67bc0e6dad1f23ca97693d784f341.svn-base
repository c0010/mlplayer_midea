// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmresetpassword_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmresetpassword.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMResetPassword {
    jclass      info_class;
    jobject     ref;
    CMSimpleResultListener* listener1;
};

fields_t gCMResetPasswordFieldID;

static void CMResetPassword_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMResetPassword when setting up callback.");
        return;
    }
    callback_cookie_CMResetPassword* pCookie = new callback_cookie_CMResetPassword;
    pCookie->listener1 = new CMSimpleResultListener(gCMResetPasswordFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMResetPasswordFieldID.jniData, (int)pCookie);

    CMResetPassword* pObj = new CMResetPassword(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMResetPasswordFieldID.nativeJavaObj, (int)pObj);
}

static void CMResetPassword_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMResetPassword *pObj = (CMResetPassword*)env->GetIntField(thiz, gCMResetPasswordFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMResetPassword* pCookie = (callback_cookie_CMResetPassword *)env->GetIntField(
        thiz, gCMResetPasswordFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMResetPasswordFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMResetPasswordFieldID.jniData, 0);
}

static void CMResetPassword_Commit(JNIEnv* env, jobject thiz, jstring sOld, jstring sNew)
{
    CMResetPassword* pObj = (CMResetPassword*)env->GetIntField(thiz, gCMResetPasswordFieldID.nativeJavaObj);

    const jchar* jsOld = env->GetStringChars(sOld, NULL);
    jsize sizesOld = env->GetStringLength(sOld);
    char* psOld = UTF16toUTF8((jchar*)jsOld, (size_t*)&sizesOld);
    const jchar* jsNew = env->GetStringChars(sNew, NULL);
    jsize sizesNew = env->GetStringLength(sNew);
    char* psNew = UTF16toUTF8((jchar*)jsNew, (size_t*)&sizesNew);
    pObj->Commit(psOld, psNew);
    env->ReleaseStringChars(sOld, jsOld);
    free(psOld);
    env->ReleaseStringChars(sNew, jsNew);
    free(psNew);
}

int register_com_wunding_mlplayer_business_CMResetPassword(JNIEnv* env) {
    static JNINativeMethod CMResetPasswordMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMResetPassword_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMResetPassword_nativeDestructor },
        { "Commit", "(Ljava/lang/String;Ljava/lang/String;)V", (void*)CMResetPassword_Commit }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMResetPassword");
    if (clazz == 0) {
        CM_ERR("class CMResetPassword no found");
        return -1;
    }

    gCMResetPasswordFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMResetPasswordFieldID.nativeJavaObj == 0) {
        CM_ERR("CMResetPassword no found mNativeObj");
        return -1;
    }

    gCMResetPasswordFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMResetPasswordFieldID.jniData == 0) {
        CM_ERR("CMResetPassword no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMResetPasswordFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMResetPasswordFieldID.callback == NULL) {
        CM_ERR("CMResetPassword no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMResetPasswordMethods,
            sizeof(CMResetPasswordMethods) / sizeof(CMResetPasswordMethods[0]));
}


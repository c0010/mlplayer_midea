// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmexam_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmexam.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMExam {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gCMExamFieldID;

static void CMExam_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMExam when setting up callback.");
        return;
    }
    callback_cookie_CMExam* pCookie = new callback_cookie_CMExam;
    pCookie->listener1 = new CMUpdateDataListener(gCMExamFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gCMExamFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMExamFieldID.jniData, (int)pCookie);

    CMExam* pObj = new CMExam();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMExamFieldID.nativeJavaObj, (int)pObj);
}

static void CMExam_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMExam *pObj = (CMExam*)env->GetIntField(thiz, gCMExamFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMExam* pCookie = (callback_cookie_CMExam *)env->GetIntField(
        thiz, gCMExamFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMExamFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMExamFieldID.jniData, 0);
}

static void CMExam_SetListener(JNIEnv* env, jobject thiz, jobject pListener, jobject pSimpleResultListener)
{
    CMExam* pObj = (CMExam*)env->GetIntField(thiz, gCMExamFieldID.nativeJavaObj);

    callback_cookie_CMExam* pCookie = (callback_cookie_CMExam *)env->GetIntField(
        thiz, gCMExamFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMExamFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gCMExamFieldID.callback);
        }
        
        IMSimpleResultListener* para2 = NULL;
        if (pSimpleResultListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        pObj->SetListener(para1, para2);
    }

    return ;
}

static void CMExam_ViewExamQuestion(JNIEnv* env, jobject thiz, jstring sID)
{
    CMExam* pObj = (CMExam*)env->GetIntField(thiz, gCMExamFieldID.nativeJavaObj);

    const jchar* jsID = env->GetStringChars(sID, NULL);
    jsize sizesID = env->GetStringLength(sID);
    char* psID = UTF16toUTF8((jchar*)jsID, (size_t*)&sizesID);
    pObj->ViewExamQuestion(psID);
    env->ReleaseStringChars(sID, jsID);
    free(psID);
}

static void CMExam_StartExam(JNIEnv* env, jobject thiz, jstring sID)
{
    CMExam* pObj = (CMExam*)env->GetIntField(thiz, gCMExamFieldID.nativeJavaObj);

    const jchar* jsID = env->GetStringChars(sID, NULL);
    jsize sizesID = env->GetStringLength(sID);
    char* psID = UTF16toUTF8((jchar*)jsID, (size_t*)&sizesID);
    pObj->StartExam(psID);
    env->ReleaseStringChars(sID, jsID);
    free(psID);
}

static jint CMExam_GetDuration(JNIEnv* env, jobject thiz)
{
    CMExam* pObj = (CMExam*)env->GetIntField(thiz, gCMExamFieldID.nativeJavaObj);

    int ret = pObj->GetDuration();
    return ret;
}

static void CMExam_SetDuration(JNIEnv* env, jobject thiz, jint second)
{
    CMExam* pObj = (CMExam*)env->GetIntField(thiz, gCMExamFieldID.nativeJavaObj);

    pObj->SetDuration(second);
}

static jboolean CMExam_LoadFromDB(JNIEnv* env, jobject thiz)
{
    CMExam* pObj = (CMExam*)env->GetIntField(thiz, gCMExamFieldID.nativeJavaObj);

    BOOL ret = pObj->LoadFromDB();
    return ret;
}

int register_com_wunding_mlplayer_business_CMExam(JNIEnv* env) {
    static JNINativeMethod CMExamMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMExam_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMExam_nativeDestructor },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)CMExam_SetListener },
        { "ViewExamQuestion", "(Ljava/lang/String;)V", (void*)CMExam_ViewExamQuestion },
        { "StartExam", "(Ljava/lang/String;)V", (void*)CMExam_StartExam },
        { "GetDuration", "()I", (void*)CMExam_GetDuration },
        { "SetDuration", "(I)V", (void*)CMExam_SetDuration },
        { "LoadFromDB", "()Z", (void*)CMExam_LoadFromDB }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMExam");
    if (clazz == 0) {
        CM_ERR("class CMExam no found");
        return -1;
    }

    gCMExamFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMExamFieldID.nativeJavaObj == 0) {
        CM_ERR("CMExam no found mNativeObj");
        return -1;
    }

    gCMExamFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMExamFieldID.jniData == 0) {
        CM_ERR("CMExam no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMExamFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMExamFieldID.callback == NULL) {
        CM_ERR("CMExam no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMExamMethods,
            sizeof(CMExamMethods) / sizeof(CMExamMethods[0]));
}


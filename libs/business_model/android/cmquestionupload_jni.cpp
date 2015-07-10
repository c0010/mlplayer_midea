// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmquestionupload_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmquestionupload.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMQuestionUpload {
    jclass      info_class;
    jobject     ref;
    CMSimpleResultListener* listener1;
};

fields_t gCMQuestionUploadFieldID;

static void CMQuestionUpload_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMQuestionUpload when setting up callback.");
        return;
    }
    callback_cookie_CMQuestionUpload* pCookie = new callback_cookie_CMQuestionUpload;
    pCookie->listener1 = new CMSimpleResultListener(gCMQuestionUploadFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMQuestionUploadFieldID.jniData, (int)pCookie);

    CMQuestionUpload* pObj = CMQuestionUpload::GetInstance();
    pObj->SetListener(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMQuestionUploadFieldID.nativeJavaObj, (int)pObj);
}

static void CMQuestionUpload_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMQuestionUpload *pObj = (CMQuestionUpload*)env->GetIntField(thiz, gCMQuestionUploadFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMQuestionUpload* pCookie = (callback_cookie_CMQuestionUpload *)env->GetIntField(
        thiz, gCMQuestionUploadFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMQuestionUploadFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMQuestionUploadFieldID.jniData, 0);
}

static void CMQuestionUpload_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMQuestionUpload* pObj = (CMQuestionUpload*)env->GetIntField(thiz, gCMQuestionUploadFieldID.nativeJavaObj);

    callback_cookie_CMQuestionUpload* pCookie = (callback_cookie_CMQuestionUpload *)env->GetIntField(
        thiz, gCMQuestionUploadFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMSimpleResultListener(gCMQuestionUploadFieldID.callback);
        }
        
        IMSimpleResultListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

    }
}

static jboolean CMQuestionUpload_AskQuestion(JNIEnv* env, jobject thiz, jstring sCategoryID, jint nAnonymous, jint nValue, jstring sQuestion, jstring filename)
{
    CMQuestionUpload* pObj = (CMQuestionUpload*)env->GetIntField(thiz, gCMQuestionUploadFieldID.nativeJavaObj);

    const jchar* jsCategoryID = env->GetStringChars(sCategoryID, NULL);
    jsize sizesCategoryID = env->GetStringLength(sCategoryID);
    char* psCategoryID = UTF16toUTF8((jchar*)jsCategoryID, (size_t*)&sizesCategoryID);
    const jchar* jsQuestion = env->GetStringChars(sQuestion, NULL);
    jsize sizesQuestion = env->GetStringLength(sQuestion);
    char* psQuestion = UTF16toUTF8((jchar*)jsQuestion, (size_t*)&sizesQuestion);
    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->AskQuestion(psCategoryID, nAnonymous, nValue, psQuestion, pfilename);
    env->ReleaseStringChars(sCategoryID, jsCategoryID);
    free(psCategoryID);
    env->ReleaseStringChars(sQuestion, jsQuestion);
    free(psQuestion);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

static jboolean CMQuestionUpload_AnswerQuestion(JNIEnv* env, jobject thiz, jstring sQuestionID, jint nAnonymous, jstring sAnswer, jstring filename)
{
    CMQuestionUpload* pObj = (CMQuestionUpload*)env->GetIntField(thiz, gCMQuestionUploadFieldID.nativeJavaObj);

    const jchar* jsQuestionID = env->GetStringChars(sQuestionID, NULL);
    jsize sizesQuestionID = env->GetStringLength(sQuestionID);
    char* psQuestionID = UTF16toUTF8((jchar*)jsQuestionID, (size_t*)&sizesQuestionID);
    const jchar* jsAnswer = env->GetStringChars(sAnswer, NULL);
    jsize sizesAnswer = env->GetStringLength(sAnswer);
    char* psAnswer = UTF16toUTF8((jchar*)jsAnswer, (size_t*)&sizesAnswer);
    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->AnswerQuestion(psQuestionID, nAnonymous, psAnswer, pfilename);
    env->ReleaseStringChars(sQuestionID, jsQuestionID);
    free(psQuestionID);
    env->ReleaseStringChars(sAnswer, jsAnswer);
    free(psAnswer);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

static jboolean CMQuestionUpload_UpheadPhtho(JNIEnv* env, jobject thiz, jstring filename)
{
    CMQuestionUpload* pObj = (CMQuestionUpload*)env->GetIntField(thiz, gCMQuestionUploadFieldID.nativeJavaObj);

    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->UpheadPhtho(pfilename);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

int register_com_wunding_mlplayer_business_CMQuestionUpload(JNIEnv* env) {
    static JNINativeMethod CMQuestionUploadMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMQuestionUpload_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMQuestionUpload_nativeDestructor },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMQuestionUpload_SetListener },
        { "AskQuestion", "(Ljava/lang/String;IILjava/lang/String;Ljava/lang/String;)Z", (void*)CMQuestionUpload_AskQuestion },
        { "AnswerQuestion", "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;)Z", (void*)CMQuestionUpload_AnswerQuestion },
        { "UpheadPhtho", "(Ljava/lang/String;)Z", (void*)CMQuestionUpload_UpheadPhtho }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMQuestionUpload");
    if (clazz == 0) {
        CM_ERR("class CMQuestionUpload no found");
        return -1;
    }

    gCMQuestionUploadFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMQuestionUploadFieldID.nativeJavaObj == 0) {
        CM_ERR("CMQuestionUpload no found mNativeObj");
        return -1;
    }

    gCMQuestionUploadFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMQuestionUploadFieldID.jniData == 0) {
        CM_ERR("CMQuestionUpload no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMQuestionUploadFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMQuestionUploadFieldID.callback == NULL) {
        CM_ERR("CMQuestionUpload no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMQuestionUploadMethods,
            sizeof(CMQuestionUploadMethods) / sizeof(CMQuestionUploadMethods[0]));
}


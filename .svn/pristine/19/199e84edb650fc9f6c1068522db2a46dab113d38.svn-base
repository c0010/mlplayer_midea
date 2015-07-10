// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmexercise_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmexercise.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMExercise {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gCMExerciseFieldID;

static void CMExercise_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMExercise when setting up callback.");
        return;
    }
    callback_cookie_CMExercise* pCookie = new callback_cookie_CMExercise;
    pCookie->listener1 = new CMUpdateDataListener(gCMExerciseFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gCMExerciseFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMExerciseFieldID.jniData, (int)pCookie);

    CMExercise* pObj = new CMExercise();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMExerciseFieldID.nativeJavaObj, (int)pObj);
}

static void CMExercise_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMExercise *pObj = (CMExercise*)env->GetIntField(thiz, gCMExerciseFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMExercise* pCookie = (callback_cookie_CMExercise *)env->GetIntField(
        thiz, gCMExerciseFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMExerciseFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMExerciseFieldID.jniData, 0);
}

static void CMExercise_SetListener(JNIEnv* env, jobject thiz, jobject pListener, jobject pSimpleResultListener)
{
    CMExercise* pObj = (CMExercise*)env->GetIntField(thiz, gCMExerciseFieldID.nativeJavaObj);

    callback_cookie_CMExercise* pCookie = (callback_cookie_CMExercise *)env->GetIntField(
        thiz, gCMExerciseFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMExerciseFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gCMExerciseFieldID.callback);
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

static void CMExercise_GetExerciseQuestion(JNIEnv* env, jobject thiz, jstring sID)
{
    CMExercise* pObj = (CMExercise*)env->GetIntField(thiz, gCMExerciseFieldID.nativeJavaObj);

    const jchar* jsID = env->GetStringChars(sID, NULL);
    jsize sizesID = env->GetStringLength(sID);
    char* psID = UTF16toUTF8((jchar*)jsID, (size_t*)&sizesID);
    pObj->GetExerciseQuestion(psID);
    env->ReleaseStringChars(sID, jsID);
    free(psID);
}

static jboolean CMExercise_LoadFromDB(JNIEnv* env, jobject thiz)
{
    CMExercise* pObj = (CMExercise*)env->GetIntField(thiz, gCMExerciseFieldID.nativeJavaObj);

    BOOL ret = pObj->LoadFromDB();
    return ret;
}

static jint CMExercise_GetRightCountExcise(JNIEnv* env, jobject thiz, jstring questionID)
{
    CMExercise* pObj = (CMExercise*)env->GetIntField(thiz, gCMExerciseFieldID.nativeJavaObj);

    const jchar* jquestionID = env->GetStringChars(questionID, NULL);
    jsize sizequestionID = env->GetStringLength(questionID);
    char* pquestionID = UTF16toUTF8((jchar*)jquestionID, (size_t*)&sizequestionID);
    int ret = pObj->GetRightCountExcise(pquestionID);
    env->ReleaseStringChars(questionID, jquestionID);
    free(pquestionID);
    return ret;
}

static jint CMExercise_GetWrongCountExcise(JNIEnv* env, jobject thiz, jstring questionID)
{
    CMExercise* pObj = (CMExercise*)env->GetIntField(thiz, gCMExerciseFieldID.nativeJavaObj);

    const jchar* jquestionID = env->GetStringChars(questionID, NULL);
    jsize sizequestionID = env->GetStringLength(questionID);
    char* pquestionID = UTF16toUTF8((jchar*)jquestionID, (size_t*)&sizequestionID);
    int ret = pObj->GetWrongCountExcise(pquestionID);
    env->ReleaseStringChars(questionID, jquestionID);
    free(pquestionID);
    return ret;
}

static void CMExercise_SetCompleteNumber(JNIEnv* env, jobject thiz, jint nNum)
{
    CMExercise* pObj = (CMExercise*)env->GetIntField(thiz, gCMExerciseFieldID.nativeJavaObj);

    pObj->SetCompleteNumber(nNum);
}

int register_com_wunding_mlplayer_business_CMExercise(JNIEnv* env) {
    static JNINativeMethod CMExerciseMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMExercise_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMExercise_nativeDestructor },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)CMExercise_SetListener },
        { "GetExerciseQuestion", "(Ljava/lang/String;)V", (void*)CMExercise_GetExerciseQuestion },
        { "LoadFromDB", "()Z", (void*)CMExercise_LoadFromDB },
        { "GetRightCountExcise", "(Ljava/lang/String;)I", (void*)CMExercise_GetRightCountExcise },
        { "GetWrongCountExcise", "(Ljava/lang/String;)I", (void*)CMExercise_GetWrongCountExcise },
        { "SetCompleteNumber", "(I)V", (void*)CMExercise_SetCompleteNumber }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMExercise");
    if (clazz == 0) {
        CM_ERR("class CMExercise no found");
        return -1;
    }

    gCMExerciseFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMExerciseFieldID.nativeJavaObj == 0) {
        CM_ERR("CMExercise no found mNativeObj");
        return -1;
    }

    gCMExerciseFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMExerciseFieldID.jniData == 0) {
        CM_ERR("CMExercise no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMExerciseFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMExerciseFieldID.callback == NULL) {
        CM_ERR("CMExercise no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMExerciseMethods,
            sizeof(CMExerciseMethods) / sizeof(CMExerciseMethods[0]));
}


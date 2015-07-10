// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmwrongquestion_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmwrongquestion.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gCMWrongQuestionFieldID;

static void CMWrongQuestion_nativeConstructor(JNIEnv* env, jobject thiz)
{
    CMWrongQuestion* pObj = new CMWrongQuestion();

    env->SetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj, (int)pObj);
}

static void CMWrongQuestion_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);
}

static void CMWrongQuestion_GetWrongQuestion(JNIEnv* env, jobject thiz, jstring sID)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    const jchar* jsID = env->GetStringChars(sID, NULL);
    jsize sizesID = env->GetStringLength(sID);
    char* psID = UTF16toUTF8((jchar*)jsID, (size_t*)&sizesID);
    pObj->GetWrongQuestion(psID);
    env->ReleaseStringChars(sID, jsID);
    free(psID);
}

static jboolean CMWrongQuestion_isOptionAnswerRight(JNIEnv* env, jobject thiz)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    BOOL ret = pObj->isOptionAnswerRight();
    return ret;
}

static jboolean CMWrongQuestion_isOptionAnswerRight(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    BOOL ret = pObj->isOptionAnswerRight(nIndex);
    return ret;
}

static jboolean CMWrongQuestion_isMyAnswerRight(JNIEnv* env, jobject thiz)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    BOOL ret = pObj->isMyAnswerRight();
    return ret;
}

static jboolean CMWrongQuestion_isWrong(JNIEnv* env, jobject thiz)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    BOOL ret = pObj->isWrong();
    return ret;
}

static void CMWrongQuestion_SetWrong(JNIEnv* env, jobject thiz, jboolean isWrong)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    pObj->SetWrong(isWrong);
}

static jstring CMWrongQuestion_GetRightAnswer(JNIEnv* env, jobject thiz)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    const char* ret = pObj->GetRightAnswer();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMWrongQuestion_Commit(JNIEnv* env, jobject thiz)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    pObj->Commit();
}

static jint CMWrongQuestion_GetWrongCount(JNIEnv* env, jobject thiz, jstring questionID)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    const jchar* jquestionID = env->GetStringChars(questionID, NULL);
    jsize sizequestionID = env->GetStringLength(questionID);
    char* pquestionID = UTF16toUTF8((jchar*)jquestionID, (size_t*)&sizequestionID);
    int ret = pObj->GetWrongCount(pquestionID);
    env->ReleaseStringChars(questionID, jquestionID);
    free(pquestionID);
    return ret;
}

static void CMWrongQuestion_SaveExerciseStatus(JNIEnv* env, jobject thiz)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    pObj->SaveExerciseStatus();
}

static void CMWrongQuestion_SaveWrongStatus(JNIEnv* env, jobject thiz)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    pObj->SaveWrongStatus();
}

static jboolean CMWrongQuestion_ClearAnswer(JNIEnv* env, jobject thiz)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    BOOL ret = pObj->ClearAnswer();
    return ret;
}

static jboolean CMWrongQuestion_UpdateWrongTime(JNIEnv* env, jobject thiz, jint lasttime)
{
    CMWrongQuestion* pObj = (CMWrongQuestion*)env->GetIntField(thiz, gCMWrongQuestionFieldID.nativeJavaObj);

    BOOL ret = pObj->UpdateWrongTime(lasttime);
    return ret;
}

int register_com_wunding_mlplayer_business_CMWrongQuestion(JNIEnv* env) {
    static jboolean (*CMWrongQuestion_isOptionAnswerRight1)(JNIEnv*, jobject);
    CMWrongQuestion_isOptionAnswerRight1 = CMWrongQuestion_isOptionAnswerRight;
    static jboolean (*CMWrongQuestion_isOptionAnswerRight2)(JNIEnv*, jobject, jint);
    CMWrongQuestion_isOptionAnswerRight2 = CMWrongQuestion_isOptionAnswerRight;

    static JNINativeMethod CMWrongQuestionMethods[] = {
        { "nativeConstructor", "()V", (void*)CMWrongQuestion_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMWrongQuestion_nativeDestructor },
        { "GetWrongQuestion", "(Ljava/lang/String;)V", (void*)CMWrongQuestion_GetWrongQuestion },
        { "isOptionAnswerRight", "()Z", (void*)CMWrongQuestion_isOptionAnswerRight1 },
        { "isOptionAnswerRight", "(I)Z", (void*)CMWrongQuestion_isOptionAnswerRight2 },
        { "isMyAnswerRight", "()Z", (void*)CMWrongQuestion_isMyAnswerRight },
        { "isWrong", "()Z", (void*)CMWrongQuestion_isWrong },
        { "SetWrong", "(Z)V", (void*)CMWrongQuestion_SetWrong },
        { "GetRightAnswer", "()Ljava/lang/String;", (void*)CMWrongQuestion_GetRightAnswer },
        { "Commit", "()V", (void*)CMWrongQuestion_Commit },
        { "GetWrongCount", "(Ljava/lang/String;)I", (void*)CMWrongQuestion_GetWrongCount },
        { "SaveExerciseStatus", "()V", (void*)CMWrongQuestion_SaveExerciseStatus },
        { "SaveWrongStatus", "()V", (void*)CMWrongQuestion_SaveWrongStatus },
        { "ClearAnswer", "()Z", (void*)CMWrongQuestion_ClearAnswer },
        { "UpdateWrongTime", "(I)Z", (void*)CMWrongQuestion_UpdateWrongTime }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMWrongQuestion");
    if (clazz == 0) {
        CM_ERR("class CMWrongQuestion no found");
        return -1;
    }

    gCMWrongQuestionFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMWrongQuestionFieldID.nativeJavaObj == 0) {
        CM_ERR("CMWrongQuestion no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMWrongQuestionMethods,
            sizeof(CMWrongQuestionMethods) / sizeof(CMWrongQuestionMethods[0]));
}


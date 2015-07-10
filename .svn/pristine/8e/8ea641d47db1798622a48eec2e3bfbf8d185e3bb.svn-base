// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmfileinfo_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmfileinfo.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMFileInfo {
    jclass      info_class;
    jobject     ref;
    CMSimpleResultListener* listener1;
};

fields_t gCMFileInfoFieldID;

static void CMFileInfo_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMFileInfo when setting up callback.");
        return;
    }
    callback_cookie_CMFileInfo* pCookie = new callback_cookie_CMFileInfo;
    pCookie->listener1 = new CMSimpleResultListener(gCMFileInfoFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMFileInfoFieldID.jniData, (int)pCookie);

    CMFileInfo* pObj = new CMFileInfo();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj, (int)pObj);
}

static void CMFileInfo_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMFileInfo *pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMFileInfo* pCookie = (callback_cookie_CMFileInfo *)env->GetIntField(
        thiz, gCMFileInfoFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMFileInfoFieldID.jniData, 0);
}

static jobject CMFileInfo_CopyFromCMFileInfo(JNIEnv* env, jobject thiz, jobject right)
{
    CMFileInfo* pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);

    extern fields_t gCMFileInfoFieldID;
    CMFileInfo* pObjCopy = (CMFileInfo*)env->GetIntField(right, gCMFileInfoFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static void CMFileInfo_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMFileInfo* pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);

    callback_cookie_CMFileInfo* pCookie = (callback_cookie_CMFileInfo *)env->GetIntField(
        thiz, gCMFileInfoFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMSimpleResultListener(gCMFileInfoFieldID.callback);
        }
        
        IMSimpleResultListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        pObj->SetListener(para1);
    }

    return ;
}

static void CMFileInfo_CreateNewRoom(JNIEnv* env, jobject thiz, jstring name, jstring desc, jstring iconPath, jint flag)
{
    CMFileInfo* pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);

    const jchar* jname = env->GetStringChars(name, NULL);
    jsize sizename = env->GetStringLength(name);
    char* pname = UTF16toUTF8((jchar*)jname, (size_t*)&sizename);
    const jchar* jdesc = env->GetStringChars(desc, NULL);
    jsize sizedesc = env->GetStringLength(desc);
    char* pdesc = UTF16toUTF8((jchar*)jdesc, (size_t*)&sizedesc);
    const jchar* jiconPath = env->GetStringChars(iconPath, NULL);
    jsize sizeiconPath = env->GetStringLength(iconPath);
    char* piconPath = UTF16toUTF8((jchar*)jiconPath, (size_t*)&sizeiconPath);
    pObj->CreateNewRoom(pname, pdesc, piconPath, flag);
    env->ReleaseStringChars(name, jname);
    free(pname);
    env->ReleaseStringChars(desc, jdesc);
    free(pdesc);
    env->ReleaseStringChars(iconPath, jiconPath);
    free(piconPath);
}

static jboolean CMFileInfo_AskQuestion(JNIEnv* env, jobject thiz, jstring sCategoryID, jint nAnonymous, jint nValue, jstring sQuestion, jstring filename, jstring expertsID)
{
    CMFileInfo* pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);

    const jchar* jsCategoryID = env->GetStringChars(sCategoryID, NULL);
    jsize sizesCategoryID = env->GetStringLength(sCategoryID);
    char* psCategoryID = UTF16toUTF8((jchar*)jsCategoryID, (size_t*)&sizesCategoryID);
    const jchar* jsQuestion = env->GetStringChars(sQuestion, NULL);
    jsize sizesQuestion = env->GetStringLength(sQuestion);
    char* psQuestion = UTF16toUTF8((jchar*)jsQuestion, (size_t*)&sizesQuestion);
    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    const jchar* jexpertsID = env->GetStringChars(expertsID, NULL);
    jsize sizeexpertsID = env->GetStringLength(expertsID);
    char* pexpertsID = UTF16toUTF8((jchar*)jexpertsID, (size_t*)&sizeexpertsID);
    BOOL ret = pObj->AskQuestion(psCategoryID, nAnonymous, nValue, psQuestion, pfilename, pexpertsID);
    env->ReleaseStringChars(sCategoryID, jsCategoryID);
    free(psCategoryID);
    env->ReleaseStringChars(sQuestion, jsQuestion);
    free(psQuestion);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    env->ReleaseStringChars(expertsID, jexpertsID);
    free(pexpertsID);
    return ret;
}

static jboolean CMFileInfo_AnswerQuestion(JNIEnv* env, jobject thiz, jstring sQuestionID, jint nAnonymous, jstring sAnswer, jstring filename)
{
    CMFileInfo* pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);

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

static jboolean CMFileInfo_UploadImage(JNIEnv* env, jobject thiz, jstring filename, jint cmdID)
{
    CMFileInfo* pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);

    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->UploadImage(pfilename, cmdID);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

static jboolean CMFileInfo_UpheadPhoto(JNIEnv* env, jobject thiz, jstring filename)
{
    CMFileInfo* pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);

    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->UpheadPhoto(pfilename);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

static jboolean CMFileInfo_UpLoadMessageWithPicture(JNIEnv* env, jobject thiz, jstring filename)
{
    CMFileInfo* pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);

    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->UpLoadMessageWithPicture(pfilename);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

static jboolean CMFileInfo_UpLoadMessageWithPicture(JNIEnv* env, jobject thiz, jstring filename, jstring msgId)
{
    CMFileInfo* pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);

    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    const jchar* jmsgId = env->GetStringChars(msgId, NULL);
    jsize sizemsgId = env->GetStringLength(msgId);
    char* pmsgId = UTF16toUTF8((jchar*)jmsgId, (size_t*)&sizemsgId);
    BOOL ret = pObj->UpLoadMessageWithPicture(pfilename, pmsgId);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    env->ReleaseStringChars(msgId, jmsgId);
    free(pmsgId);
    return ret;
}

static jboolean CMFileInfo_UpLoadGroupHeader(JNIEnv* env, jobject thiz, jstring roomid, jstring filename)
{
    CMFileInfo* pObj = (CMFileInfo*)env->GetIntField(thiz, gCMFileInfoFieldID.nativeJavaObj);

    const jchar* jroomid = env->GetStringChars(roomid, NULL);
    jsize sizeroomid = env->GetStringLength(roomid);
    char* proomid = UTF16toUTF8((jchar*)jroomid, (size_t*)&sizeroomid);
    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->UpLoadGroupHeader(proomid, pfilename);
    env->ReleaseStringChars(roomid, jroomid);
    free(proomid);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

int register_com_wunding_mlplayer_business_CMFileInfo(JNIEnv* env) {
    static jboolean (*CMFileInfo_UpLoadMessageWithPicture1)(JNIEnv*, jobject, jstring);
    CMFileInfo_UpLoadMessageWithPicture1 = CMFileInfo_UpLoadMessageWithPicture;
    static jboolean (*CMFileInfo_UpLoadMessageWithPicture2)(JNIEnv*, jobject, jstring, jstring);
    CMFileInfo_UpLoadMessageWithPicture2 = CMFileInfo_UpLoadMessageWithPicture;

    static JNINativeMethod CMFileInfoMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMFileInfo_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMFileInfo_nativeDestructor },
        { "CopyFromCMFileInfo", "(Lcom/wunding/mlplayer/business/CMFileInfo;)Lcom/wunding/mlplayer/business/CMFileInfo;", (void*)CMFileInfo_CopyFromCMFileInfo },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMFileInfo_SetListener },
        { "CreateNewRoom", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V", (void*)CMFileInfo_CreateNewRoom },
        { "AskQuestion", "(Ljava/lang/String;IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMFileInfo_AskQuestion },
        { "AnswerQuestion", "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;)Z", (void*)CMFileInfo_AnswerQuestion },
        { "UploadImage", "(Ljava/lang/String;I)Z", (void*)CMFileInfo_UploadImage },
        { "UpheadPhoto", "(Ljava/lang/String;)Z", (void*)CMFileInfo_UpheadPhoto },
        { "UpLoadMessageWithPicture", "(Ljava/lang/String;)Z", (void*)CMFileInfo_UpLoadMessageWithPicture1 },
        { "UpLoadMessageWithPicture", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMFileInfo_UpLoadMessageWithPicture2 },
        { "UpLoadGroupHeader", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMFileInfo_UpLoadGroupHeader }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMFileInfo");
    if (clazz == 0) {
        CM_ERR("class CMFileInfo no found");
        return -1;
    }

    gCMFileInfoFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMFileInfoFieldID.nativeJavaObj == 0) {
        CM_ERR("CMFileInfo no found mNativeObj");
        return -1;
    }

    gCMFileInfoFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMFileInfoFieldID.jniData == 0) {
        CM_ERR("CMFileInfo no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMFileInfoFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMFileInfoFieldID.callback == NULL) {
        CM_ERR("CMFileInfo no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMFileInfoMethods,
            sizeof(CMFileInfoMethods) / sizeof(CMFileInfoMethods[0]));
}


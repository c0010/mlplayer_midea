// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmcomment_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmcomment.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMComment {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
    CMRatingListener* listener3;
};

fields_t gCMCommentFieldID;

static void CMComment_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMComment when setting up callback.");
        return;
    }
    callback_cookie_CMComment* pCookie = new callback_cookie_CMComment;
    pCookie->listener1 = new CMUpdateDataListener(gCMCommentFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gCMCommentFieldID.callback);
    pCookie->listener3 = new CMRatingListener(gCMCommentFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMCommentFieldID.jniData, (int)pCookie);

    CMComment* pObj = new CMComment();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMCommentFieldID.nativeJavaObj, (int)pObj);
}

static void CMComment_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMComment *pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMComment* pCookie = (callback_cookie_CMComment *)env->GetIntField(
        thiz, gCMCommentFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie->listener3;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMCommentFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMCommentFieldID.jniData, 0);
}

static jint CMComment_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMComment_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    extern fields_t gTCommentItemFieldID;
    TCommentItem* pItem = (TCommentItem*)env->GetIntField(item, gTCommentItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMComment_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    extern fields_t gTCommentItemFieldID;
    TCommentItem* pItem = (TCommentItem*)env->GetIntField(obj, gTCommentItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMComment_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    extern fields_t gTCommentItemFieldID;
    TCommentItem* pItem = (TCommentItem*)env->GetIntField(obj, gTCommentItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMComment_IsEnd(JNIEnv* env, jobject thiz)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMComment_RequestMore(JNIEnv* env, jobject thiz)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMComment_IsRunning(JNIEnv* env, jobject thiz)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMComment_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMComment_Cancel(JNIEnv* env, jobject thiz)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMComment_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMComment_setListener(JNIEnv* env, jobject thiz, jobject pUpdateDataListener, jobject pSimpleResultListener, jobject pRatingListener)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    callback_cookie_CMComment* pCookie = (callback_cookie_CMComment *)env->GetIntField(
        thiz, gCMCommentFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMCommentFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pUpdateDataListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gCMCommentFieldID.callback);
        }
        
        IMSimpleResultListener* para2 = NULL;
        if (pSimpleResultListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        if (pCookie->listener3 == NULL)
        {
            pCookie->listener3 = new CMRatingListener(gCMCommentFieldID.callback);
        }
        
        IMRatingListener* para3 = NULL;
        if (pRatingListener != NULL)
        {
            para3 = pCookie->listener3;
        }

        pObj->setListener(para1, para2, para3);
    }

    return ;
}

static jboolean CMComment_RequestCommentList(JNIEnv* env, jobject thiz, jstring sFlag, jstring ClassID, jstring CoursewareID)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jClassID = env->GetStringChars(ClassID, NULL);
    jsize sizeClassID = env->GetStringLength(ClassID);
    char* pClassID = UTF16toUTF8((jchar*)jClassID, (size_t*)&sizeClassID);
    const jchar* jCoursewareID = env->GetStringChars(CoursewareID, NULL);
    jsize sizeCoursewareID = env->GetStringLength(CoursewareID);
    char* pCoursewareID = UTF16toUTF8((jchar*)jCoursewareID, (size_t*)&sizeCoursewareID);
    BOOL ret = pObj->RequestCommentList(psFlag, pClassID, pCoursewareID);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(ClassID, jClassID);
    free(pClassID);
    env->ReleaseStringChars(CoursewareID, jCoursewareID);
    free(pCoursewareID);
    return ret;
}

static jboolean CMComment_SendComment(JNIEnv* env, jobject thiz, jstring sFlag, jstring ClassID, jstring CoursewareID, jstring sContent, jboolean bsyncqa)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jClassID = env->GetStringChars(ClassID, NULL);
    jsize sizeClassID = env->GetStringLength(ClassID);
    char* pClassID = UTF16toUTF8((jchar*)jClassID, (size_t*)&sizeClassID);
    const jchar* jCoursewareID = env->GetStringChars(CoursewareID, NULL);
    jsize sizeCoursewareID = env->GetStringLength(CoursewareID);
    char* pCoursewareID = UTF16toUTF8((jchar*)jCoursewareID, (size_t*)&sizeCoursewareID);
    const jchar* jsContent = env->GetStringChars(sContent, NULL);
    jsize sizesContent = env->GetStringLength(sContent);
    char* psContent = UTF16toUTF8((jchar*)jsContent, (size_t*)&sizesContent);
    BOOL ret = pObj->SendComment(psFlag, pClassID, pCoursewareID, psContent, bsyncqa);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(ClassID, jClassID);
    free(pClassID);
    env->ReleaseStringChars(CoursewareID, jCoursewareID);
    free(pCoursewareID);
    env->ReleaseStringChars(sContent, jsContent);
    free(psContent);
    return ret;
}

static jboolean CMComment_CommentLike(JNIEnv* env, jobject thiz, jstring sFlag, jstring ClassID, jstring CoursewareID, jstring sReplyID)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jClassID = env->GetStringChars(ClassID, NULL);
    jsize sizeClassID = env->GetStringLength(ClassID);
    char* pClassID = UTF16toUTF8((jchar*)jClassID, (size_t*)&sizeClassID);
    const jchar* jCoursewareID = env->GetStringChars(CoursewareID, NULL);
    jsize sizeCoursewareID = env->GetStringLength(CoursewareID);
    char* pCoursewareID = UTF16toUTF8((jchar*)jCoursewareID, (size_t*)&sizeCoursewareID);
    const jchar* jsReplyID = env->GetStringChars(sReplyID, NULL);
    jsize sizesReplyID = env->GetStringLength(sReplyID);
    char* psReplyID = UTF16toUTF8((jchar*)jsReplyID, (size_t*)&sizesReplyID);
    BOOL ret = pObj->CommentLike(psFlag, pClassID, pCoursewareID, psReplyID);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(ClassID, jClassID);
    free(pClassID);
    env->ReleaseStringChars(CoursewareID, jCoursewareID);
    free(pCoursewareID);
    env->ReleaseStringChars(sReplyID, jsReplyID);
    free(psReplyID);
    return ret;
}

static jboolean CMComment_RequestBriefComment(JNIEnv* env, jobject thiz, jstring sFlag, jstring ClassID, jstring CoursewareID)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jClassID = env->GetStringChars(ClassID, NULL);
    jsize sizeClassID = env->GetStringLength(ClassID);
    char* pClassID = UTF16toUTF8((jchar*)jClassID, (size_t*)&sizeClassID);
    const jchar* jCoursewareID = env->GetStringChars(CoursewareID, NULL);
    jsize sizeCoursewareID = env->GetStringLength(CoursewareID);
    char* pCoursewareID = UTF16toUTF8((jchar*)jCoursewareID, (size_t*)&sizeCoursewareID);
    BOOL ret = pObj->RequestBriefComment(psFlag, pClassID, pCoursewareID);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(ClassID, jClassID);
    free(pClassID);
    env->ReleaseStringChars(CoursewareID, jCoursewareID);
    free(pCoursewareID);
    return ret;
}

static jint CMComment_GetTotalCount(JNIEnv* env, jobject thiz)
{
    CMComment* pObj = (CMComment*)env->GetIntField(thiz, gCMCommentFieldID.nativeJavaObj);

    int ret = pObj->GetTotalCount();
    return ret;
}

int register_com_wunding_mlplayer_business_CMComment(JNIEnv* env) {
    static JNINativeMethod CMCommentMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMComment_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMComment_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMComment_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TCommentItem;)Z", (void*)CMComment_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TCommentItem;)Z", (void*)CMComment_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TCommentItem;)Z", (void*)CMComment_Update },
        { "IsEnd", "()Z", (void*)CMComment_IsEnd },
        { "RequestMore", "()Z", (void*)CMComment_RequestMore },
        { "IsRunning", "()Z", (void*)CMComment_IsRunning },
        { "IsRefresh", "()Z", (void*)CMComment_IsRefresh },
        { "Cancel", "()V", (void*)CMComment_Cancel },
        { "SetRequestType", "(I)V", (void*)CMComment_SetRequestType },
        { "nativesetListener", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)V", (void*)CMComment_setListener },
        { "RequestCommentList", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMComment_RequestCommentList },
        { "SendComment", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)Z", (void*)CMComment_SendComment },
        { "CommentLike", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMComment_CommentLike },
        { "RequestBriefComment", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMComment_RequestBriefComment },
        { "GetTotalCount", "()I", (void*)CMComment_GetTotalCount }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMComment");
    if (clazz == 0) {
        CM_ERR("class CMComment no found");
        return -1;
    }

    gCMCommentFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMCommentFieldID.nativeJavaObj == 0) {
        CM_ERR("CMComment no found mNativeObj");
        return -1;
    }

    gCMCommentFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMCommentFieldID.jniData == 0) {
        CM_ERR("CMComment no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMCommentFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMCommentFieldID.callback == NULL) {
        CM_ERR("CMComment no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMCommentMethods,
            sizeof(CMCommentMethods) / sizeof(CMCommentMethods[0]));
}


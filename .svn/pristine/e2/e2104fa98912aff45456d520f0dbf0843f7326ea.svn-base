// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmcourseinfo_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmcourseinfo.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMCourseInfo {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMRatingListener* listener2;
};

fields_t gCMCourseInfoFieldID;

static void CMCourseInfo_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMCourseInfo when setting up callback.");
        return;
    }
    callback_cookie_CMCourseInfo* pCookie = new callback_cookie_CMCourseInfo;
    pCookie->listener1 = new CMUpdateDataListener(gCMCourseInfoFieldID.callback);
    pCookie->listener2 = new CMRatingListener(gCMCourseInfoFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMCourseInfoFieldID.jniData, (int)pCookie);

    CMCourseInfo* pObj = new CMCourseInfo();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj, (int)pObj);
}

static void CMCourseInfo_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMCourseInfo *pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMCourseInfo* pCookie = (callback_cookie_CMCourseInfo *)env->GetIntField(
        thiz, gCMCourseInfoFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMCourseInfoFieldID.jniData, 0);
}

static jint CMCourseInfo_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMCourseInfo_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    extern fields_t gTCoursewareItemFieldID;
    TCoursewareItem* pItem = (TCoursewareItem*)env->GetIntField(item, gTCoursewareItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMCourseInfo_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    extern fields_t gTCoursewareItemFieldID;
    TCoursewareItem* pItem = (TCoursewareItem*)env->GetIntField(obj, gTCoursewareItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMCourseInfo_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    extern fields_t gTCoursewareItemFieldID;
    TCoursewareItem* pItem = (TCoursewareItem*)env->GetIntField(obj, gTCoursewareItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMCourseInfo_IsEnd(JNIEnv* env, jobject thiz)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMCourseInfo_RequestMore(JNIEnv* env, jobject thiz)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMCourseInfo_IsRunning(JNIEnv* env, jobject thiz)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMCourseInfo_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMCourseInfo_Cancel(JNIEnv* env, jobject thiz)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMCourseInfo_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMCourseInfo_SetListener(JNIEnv* env, jobject thiz, jobject pUpdateDataListener, jobject pRatingListener)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    callback_cookie_CMCourseInfo* pCookie = (callback_cookie_CMCourseInfo *)env->GetIntField(
        thiz, gCMCourseInfoFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMCourseInfoFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pUpdateDataListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMRatingListener(gCMCourseInfoFieldID.callback);
        }
        
        IMRatingListener* para2 = NULL;
        if (pRatingListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        pObj->SetListener(para1, para2);
    }

    return ;
}

static void CMCourseInfo_RequestCourseware(JNIEnv* env, jobject thiz, jstring sid)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    const jchar* jsid = env->GetStringChars(sid, NULL);
    jsize sizesid = env->GetStringLength(sid);
    char* psid = UTF16toUTF8((jchar*)jsid, (size_t*)&sizesid);
    pObj->RequestCourseware(psid);
    env->ReleaseStringChars(sid, jsid);
    free(psid);
}

static jboolean CMCourseInfo_GetClassItem(JNIEnv* env, jobject thiz, jobject item)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    extern fields_t gTClassItemFieldID;
    TClassItem* pItem = (TClassItem*)env->GetIntField(item, gTClassItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetClassItem(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMCourseInfo_Rating(JNIEnv* env, jobject thiz)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->Rating();
    return ret;
}

static jint CMCourseInfo_CoursewareCount(JNIEnv* env, jobject thiz)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    int ret = pObj->CoursewareCount();
    return ret;
}

static jboolean CMCourseInfo_GetCourseware(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    extern fields_t gTCoursewareItemFieldID;
    TCoursewareItem* pItem = (TCoursewareItem*)env->GetIntField(item, gTCoursewareItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetCourseware(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jint CMCourseInfo_GetCurrentCoursewareIndex(JNIEnv* env, jobject thiz)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    int ret = pObj->GetCurrentCoursewareIndex();
    return ret;
}

static jint CMCourseInfo_GetCoursewareFlag(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    int ret = pObj->GetCoursewareFlag(nIndex);
    return ret;
}

static void CMCourseInfo_SetCoursewareFlag(JNIEnv* env, jobject thiz, jint nIndex, jint nCheck)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    pObj->SetCoursewareFlag(nIndex, nCheck);
}

static jobject CMCourseInfo_CopyFromCMCourseInfo(JNIEnv* env, jobject thiz, jobject right)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    extern fields_t gCMCourseInfoFieldID;
    CMCourseInfo* pObjCopy = (CMCourseInfo*)env->GetIntField(right, gCMCourseInfoFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static jobject CMCourseInfo_CopyFromTBrowserItem(JNIEnv* env, jobject thiz, jobject right)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    extern fields_t gTBrowserItemFieldID;
    TBrowserItem* pObjCopy = (TBrowserItem*)env->GetIntField(right, gTBrowserItemFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static jint CMCourseInfo_HaveCourseware(JNIEnv* env, jobject thiz, jobject item)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    extern fields_t gTCoursewareItemFieldID;
    TCoursewareItem* pItem = (TCoursewareItem*)env->GetIntField(item, gTCoursewareItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jint ret = pObj->HaveCourseware(*pItem);
        return ret;
    }
    else {
        return -1;
    }
}

static jboolean CMCourseInfo_RequestCourseAndClass(JNIEnv* env, jobject thiz, jstring setid)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    const jchar* jsetid = env->GetStringChars(setid, NULL);
    jsize sizesetid = env->GetStringLength(setid);
    char* psetid = UTF16toUTF8((jchar*)jsetid, (size_t*)&sizesetid);
    BOOL ret = pObj->RequestCourseAndClass(psetid);
    env->ReleaseStringChars(setid, jsetid);
    free(psetid);
    return ret;
}

static jboolean CMCourseInfo_RatingCourseinfo(JNIEnv* env, jobject thiz, jstring CoursewareID)
{
    CMCourseInfo* pObj = (CMCourseInfo*)env->GetIntField(thiz, gCMCourseInfoFieldID.nativeJavaObj);

    const jchar* jCoursewareID = env->GetStringChars(CoursewareID, NULL);
    jsize sizeCoursewareID = env->GetStringLength(CoursewareID);
    char* pCoursewareID = UTF16toUTF8((jchar*)jCoursewareID, (size_t*)&sizeCoursewareID);
    BOOL ret = pObj->RatingCourseinfo(pCoursewareID);
    env->ReleaseStringChars(CoursewareID, jCoursewareID);
    free(pCoursewareID);
    return ret;
}

int register_com_wunding_mlplayer_business_CMCourseInfo(JNIEnv* env) {
    static JNINativeMethod CMCourseInfoMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMCourseInfo_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMCourseInfo_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMCourseInfo_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TCoursewareItem;)Z", (void*)CMCourseInfo_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TCoursewareItem;)Z", (void*)CMCourseInfo_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TCoursewareItem;)Z", (void*)CMCourseInfo_Update },
        { "IsEnd", "()Z", (void*)CMCourseInfo_IsEnd },
        { "RequestMore", "()Z", (void*)CMCourseInfo_RequestMore },
        { "IsRunning", "()Z", (void*)CMCourseInfo_IsRunning },
        { "IsRefresh", "()Z", (void*)CMCourseInfo_IsRefresh },
        { "Cancel", "()V", (void*)CMCourseInfo_Cancel },
        { "SetRequestType", "(I)V", (void*)CMCourseInfo_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)CMCourseInfo_SetListener },
        { "RequestCourseware", "(Ljava/lang/String;)V", (void*)CMCourseInfo_RequestCourseware },
        { "GetClassItem", "(Lcom/wunding/mlplayer/business/TClassItem;)Z", (void*)CMCourseInfo_GetClassItem },
        { "Rating", "()Z", (void*)CMCourseInfo_Rating },
        { "CoursewareCount", "()I", (void*)CMCourseInfo_CoursewareCount },
        { "GetCourseware", "(ILcom/wunding/mlplayer/business/TCoursewareItem;)Z", (void*)CMCourseInfo_GetCourseware },
        { "GetCurrentCoursewareIndex", "()I", (void*)CMCourseInfo_GetCurrentCoursewareIndex },
        { "GetCoursewareFlag", "(I)I", (void*)CMCourseInfo_GetCoursewareFlag },
        { "SetCoursewareFlag", "(II)V", (void*)CMCourseInfo_SetCoursewareFlag },
        { "CopyFromCMCourseInfo", "(Lcom/wunding/mlplayer/business/CMCourseInfo;)Lcom/wunding/mlplayer/business/CMCourseInfo;", (void*)CMCourseInfo_CopyFromCMCourseInfo },
        { "CopyFromTBrowserItem", "(Lcom/wunding/mlplayer/business/TBrowserItem;)Lcom/wunding/mlplayer/business/CMCourseInfo;", (void*)CMCourseInfo_CopyFromTBrowserItem },
        { "HaveCourseware", "(Lcom/wunding/mlplayer/business/TCoursewareItem;)I", (void*)CMCourseInfo_HaveCourseware },
        { "RequestCourseAndClass", "(Ljava/lang/String;)Z", (void*)CMCourseInfo_RequestCourseAndClass },
        { "RatingCourseinfo", "(Ljava/lang/String;)Z", (void*)CMCourseInfo_RatingCourseinfo }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMCourseInfo");
    if (clazz == 0) {
        CM_ERR("class CMCourseInfo no found");
        return -1;
    }

    gCMCourseInfoFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMCourseInfoFieldID.nativeJavaObj == 0) {
        CM_ERR("CMCourseInfo no found mNativeObj");
        return -1;
    }

    gCMCourseInfoFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMCourseInfoFieldID.jniData == 0) {
        CM_ERR("CMCourseInfo no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMCourseInfoFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMCourseInfoFieldID.callback == NULL) {
        CM_ERR("CMCourseInfo no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMCourseInfoMethods,
            sizeof(CMCourseInfoMethods) / sizeof(CMCourseInfoMethods[0]));
}


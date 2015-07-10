// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmcontenthandler_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmcontenthandler.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMContenthandler {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMRatingListener* listener2;
};

fields_t gCMContenthandlerFieldID;

static void CMContenthandler_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMContenthandler when setting up callback.");
        return;
    }
    callback_cookie_CMContenthandler* pCookie = new callback_cookie_CMContenthandler;
    pCookie->listener1 = new CMUpdateDataListener(gCMContenthandlerFieldID.callback);
    pCookie->listener2 = new CMRatingListener(gCMContenthandlerFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMContenthandlerFieldID.jniData, (int)pCookie);

    CMContenthandler* pObj = new CMContenthandler();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj, (int)pObj);
}

static void CMContenthandler_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMContenthandler *pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMContenthandler* pCookie = (callback_cookie_CMContenthandler *)env->GetIntField(
        thiz, gCMContenthandlerFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMContenthandlerFieldID.jniData, 0);
}

static jint CMContenthandler_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMContenthandler_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    extern fields_t gTBrowserItemFieldID;
    TBrowserItem* pItem = (TBrowserItem*)env->GetIntField(item, gTBrowserItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMContenthandler_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    extern fields_t gTBrowserItemFieldID;
    TBrowserItem* pItem = (TBrowserItem*)env->GetIntField(obj, gTBrowserItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMContenthandler_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    extern fields_t gTBrowserItemFieldID;
    TBrowserItem* pItem = (TBrowserItem*)env->GetIntField(obj, gTBrowserItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMContenthandler_IsEnd(JNIEnv* env, jobject thiz)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMContenthandler_RequestMore(JNIEnv* env, jobject thiz)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMContenthandler_IsRunning(JNIEnv* env, jobject thiz)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMContenthandler_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMContenthandler_Cancel(JNIEnv* env, jobject thiz)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMContenthandler_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static jint CMContenthandler_GetHeadItemCount(JNIEnv* env, jobject thiz)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    int ret = pObj->GetHeadItemCount();
    return ret;
}

static jboolean CMContenthandler_GetHeadItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    extern fields_t gTBrowserItemFieldID;
    TBrowserItem* pItem = (TBrowserItem*)env->GetIntField(item, gTBrowserItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetHeadItem(nIndex, pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMContenthandler_Rating(JNIEnv* env, jobject thiz, jstring sID)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    const jchar* jsID = env->GetStringChars(sID, NULL);
    jsize sizesID = env->GetStringLength(sID);
    char* psID = UTF16toUTF8((jchar*)jsID, (size_t*)&sizesID);
    BOOL ret = pObj->Rating(psID);
    env->ReleaseStringChars(sID, jsID);
    free(psID);
    return ret;
}

static jboolean CMContenthandler_RatingCourseinfo(JNIEnv* env, jobject thiz, jstring CoursewareID)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    const jchar* jCoursewareID = env->GetStringChars(CoursewareID, NULL);
    jsize sizeCoursewareID = env->GetStringLength(CoursewareID);
    char* pCoursewareID = UTF16toUTF8((jchar*)jCoursewareID, (size_t*)&sizeCoursewareID);
    BOOL ret = pObj->RatingCourseinfo(pCoursewareID);
    env->ReleaseStringChars(CoursewareID, jCoursewareID);
    free(pCoursewareID);
    return ret;
}

static void CMContenthandler_SetListener(JNIEnv* env, jobject thiz, jobject pListener, jobject pRatingListener)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    callback_cookie_CMContenthandler* pCookie = (callback_cookie_CMContenthandler *)env->GetIntField(
        thiz, gCMContenthandlerFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMContenthandlerFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMRatingListener(gCMContenthandlerFieldID.callback);
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

static jint CMContenthandler_GetItemModel(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    int ret = pObj->GetItemModel(nIndex);
    return ret;
}

static jint CMContenthandler_GetHeadItemModel(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMContenthandler* pObj = (CMContenthandler*)env->GetIntField(thiz, gCMContenthandlerFieldID.nativeJavaObj);

    int ret = pObj->GetHeadItemModel(nIndex);
    return ret;
}

int register_com_wunding_mlplayer_business_CMContenthandler(JNIEnv* env) {
    static JNINativeMethod CMContenthandlerMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMContenthandler_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMContenthandler_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMContenthandler_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TBrowserItem;)Z", (void*)CMContenthandler_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TBrowserItem;)Z", (void*)CMContenthandler_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TBrowserItem;)Z", (void*)CMContenthandler_Update },
        { "IsEnd", "()Z", (void*)CMContenthandler_IsEnd },
        { "RequestMore", "()Z", (void*)CMContenthandler_RequestMore },
        { "IsRunning", "()Z", (void*)CMContenthandler_IsRunning },
        { "IsRefresh", "()Z", (void*)CMContenthandler_IsRefresh },
        { "Cancel", "()V", (void*)CMContenthandler_Cancel },
        { "SetRequestType", "(I)V", (void*)CMContenthandler_SetRequestType },
        { "GetHeadItemCount", "()I", (void*)CMContenthandler_GetHeadItemCount },
        { "GetHeadItem", "(ILcom/wunding/mlplayer/business/TBrowserItem;)Z", (void*)CMContenthandler_GetHeadItem },
        { "Rating", "(Ljava/lang/String;)Z", (void*)CMContenthandler_Rating },
        { "RatingCourseinfo", "(Ljava/lang/String;)Z", (void*)CMContenthandler_RatingCourseinfo },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)CMContenthandler_SetListener },
        { "GetItemModel", "(I)I", (void*)CMContenthandler_GetItemModel },
        { "GetHeadItemModel", "(I)I", (void*)CMContenthandler_GetHeadItemModel }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMContenthandler");
    if (clazz == 0) {
        CM_ERR("class CMContenthandler no found");
        return -1;
    }

    gCMContenthandlerFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMContenthandlerFieldID.nativeJavaObj == 0) {
        CM_ERR("CMContenthandler no found mNativeObj");
        return -1;
    }

    gCMContenthandlerFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMContenthandlerFieldID.jniData == 0) {
        CM_ERR("CMContenthandler no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMContenthandlerFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMContenthandlerFieldID.callback == NULL) {
        CM_ERR("CMContenthandler no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMContenthandlerMethods,
            sizeof(CMContenthandlerMethods) / sizeof(CMContenthandlerMethods[0]));
}


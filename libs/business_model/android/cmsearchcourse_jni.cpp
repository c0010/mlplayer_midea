// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmsearchcourse_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmsearchcourse.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTSearchItemFieldID;

static void TSearchItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
}

static void TSearchItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    env->SetIntField(thiz, gTSearchItemFieldID.nativeJavaObj, 0);
}

static jint TSearchItem_ChildItemCount(JNIEnv* env, jobject thiz)
{
    TSearchItem* pObj = (TSearchItem*)env->GetIntField(thiz, gTSearchItemFieldID.nativeJavaObj);

    int ret = pObj->ChildItemCount();
    return ret;
}

static jobject TSearchItem_GetChildItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    TSearchItem* pObj = (TSearchItem*)env->GetIntField(thiz, gTSearchItemFieldID.nativeJavaObj);

    TSearchItem* pRet = pObj->GetChildItem(nIndex);
    if (pRet == NULL) return NULL;

    jclass retClazz = env->FindClass("com/wunding/mlplayer/business/TSearchItem");
    if (retClazz == NULL) {
        CM_ERR("Can't find class TSearchItem");
        return NULL;
    }

    jmethodID retConstructor = env->GetMethodID(retClazz, "<init>", "(I)V");
    if (retConstructor == NULL) {
        CM_ERR("Can't find class TSearchItem native constructor");
        return NULL;
    }

    return env->NewObject(retClazz,
            retConstructor, (int)pRet);
}

static void TSearchItem_SetSearchCountSign(JNIEnv* env, jobject thiz)
{
    TSearchItem* pObj = (TSearchItem*)env->GetIntField(thiz, gTSearchItemFieldID.nativeJavaObj);

    pObj->SetSearchCountSign();
}

static jint TSearchItem_GetSearchCount(JNIEnv* env, jobject thiz)
{
    TSearchItem* pObj = (TSearchItem*)env->GetIntField(thiz, gTSearchItemFieldID.nativeJavaObj);

    int ret = pObj->GetSearchCount();
    return ret;
}

static jstring TSearchItem_GetID(JNIEnv* env, jobject thiz)
{
    TSearchItem* pObj = (TSearchItem*)env->GetIntField(thiz, gTSearchItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSearchItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TSearchItem* pObj = (TSearchItem*)env->GetIntField(thiz, gTSearchItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TSearchItem_GetTitle(JNIEnv* env, jobject thiz)
{
    TSearchItem* pObj = (TSearchItem*)env->GetIntField(thiz, gTSearchItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTitle.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSearchItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    TSearchItem* pObj = (TSearchItem*)env->GetIntField(thiz, gTSearchItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTitle, NULL);
    jsize size = env->GetStringLength(sTitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTitle = data;

    env->ReleaseStringChars(sTitle, jChar);
    
    free(data);
    
    return true;
}

static jstring TSearchItem_GetFlag(JNIEnv* env, jobject thiz)
{
    TSearchItem* pObj = (TSearchItem*)env->GetIntField(thiz, gTSearchItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sFlag.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sFlag.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSearchItem_SetFlag(JNIEnv* env, jobject thiz, jstring sFlag)
{
    TSearchItem* pObj = (TSearchItem*)env->GetIntField(thiz, gTSearchItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sFlag, NULL);
    jsize size = env->GetStringLength(sFlag);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sFlag = data;

    env->ReleaseStringChars(sFlag, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TSearchItem(JNIEnv* env) {
    static JNINativeMethod TSearchItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TSearchItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TSearchItem_nativeDestructor },
        { "ChildItemCount", "()I", (void*)TSearchItem_ChildItemCount },
        { "GetChildItem", "(I)Lcom/wunding/mlplayer/business/TSearchItem;", (void*)TSearchItem_GetChildItem },
        { "SetSearchCountSign", "()V", (void*)TSearchItem_SetSearchCountSign },
        { "GetSearchCount", "()I", (void*)TSearchItem_GetSearchCount },
        { "GetID", "()Ljava/lang/String;", (void*)TSearchItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TSearchItem_SetID },
        { "GetTitle", "()Ljava/lang/String;", (void*)TSearchItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)TSearchItem_SetTitle },
        { "GetFlag", "()Ljava/lang/String;", (void*)TSearchItem_GetFlag },
        { "SetFlag", "(Ljava/lang/String;)Z", (void*)TSearchItem_SetFlag }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TSearchItem");
    if (clazz == 0) {
        CM_ERR("class TSearchItem no found");
        return -1;
    }

    gTSearchItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTSearchItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TSearchItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TSearchItemMethods,
            sizeof(TSearchItemMethods) / sizeof(TSearchItemMethods[0]));
}


struct callback_cookie_CMSearchCourse {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMSearchCourseFieldID;

static void CMSearchCourse_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMSearchCourse when setting up callback.");
        return;
    }
    callback_cookie_CMSearchCourse* pCookie = new callback_cookie_CMSearchCourse;
    pCookie->listener1 = new CMUpdateDataListener(gCMSearchCourseFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMSearchCourseFieldID.jniData, (int)pCookie);

    CMSearchCourse* pObj = new CMSearchCourse();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj, (int)pObj);
}

static void CMSearchCourse_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMSearchCourse *pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMSearchCourse* pCookie = (callback_cookie_CMSearchCourse *)env->GetIntField(
        thiz, gCMSearchCourseFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMSearchCourseFieldID.jniData, 0);
}

static jint CMSearchCourse_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMSearchCourse_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    extern fields_t gTSearchItemFieldID;
    TSearchItem* pItem = NULL;
    jboolean ret = pObj->GetItem(nIndex, pItem);

    env->SetIntField(item, gTSearchItemFieldID.nativeJavaObj, (int)pItem);

    return ret;
}

static jboolean CMSearchCourse_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    extern fields_t gTSearchItemFieldID;
    TSearchItem* pItem = (TSearchItem*)env->GetIntField(obj, gTSearchItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMSearchCourse_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    extern fields_t gTSearchItemFieldID;
    TSearchItem* pItem = (TSearchItem*)env->GetIntField(obj, gTSearchItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMSearchCourse_IsEnd(JNIEnv* env, jobject thiz)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMSearchCourse_RequestMore(JNIEnv* env, jobject thiz)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMSearchCourse_IsRunning(JNIEnv* env, jobject thiz)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMSearchCourse_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMSearchCourse_Cancel(JNIEnv* env, jobject thiz)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMSearchCourse_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMSearchCourse_SetListener(JNIEnv* env, jobject thiz, jobject pUpdateDataListener)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    callback_cookie_CMSearchCourse* pCookie = (callback_cookie_CMSearchCourse *)env->GetIntField(
        thiz, gCMSearchCourseFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMSearchCourseFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pUpdateDataListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        pObj->SetListener(para1);
    }

    return ;
}

static void CMSearchCourse_GetCourseKey(JNIEnv* env, jobject thiz)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    pObj->GetCourseKey();
}

static jobject CMSearchCourse_GetHighSearch(JNIEnv* env, jobject thiz)
{
    CMSearchCourse* pObj = (CMSearchCourse*)env->GetIntField(thiz, gCMSearchCourseFieldID.nativeJavaObj);

    TSearchItem* pRet = pObj->GetHighSearch();
    if (pRet == NULL) return NULL;

    jclass retClazz = env->FindClass("com/wunding/mlplayer/business/TSearchItem");
    if (retClazz == NULL) {
        CM_ERR("Can't find class TSearchItem");
        return NULL;
    }

    jmethodID retConstructor = env->GetMethodID(retClazz, "<init>", "(I)V");
    if (retConstructor == NULL) {
        CM_ERR("Can't find class TSearchItem native constructor");
        return NULL;
    }

    return env->NewObject(retClazz,
            retConstructor, (int)pRet);
}

int register_com_wunding_mlplayer_business_CMSearchCourse(JNIEnv* env) {
    static JNINativeMethod CMSearchCourseMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMSearchCourse_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMSearchCourse_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMSearchCourse_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TSearchItem;)Z", (void*)CMSearchCourse_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TSearchItem;)Z", (void*)CMSearchCourse_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TSearchItem;)Z", (void*)CMSearchCourse_Update },
        { "IsEnd", "()Z", (void*)CMSearchCourse_IsEnd },
        { "RequestMore", "()Z", (void*)CMSearchCourse_RequestMore },
        { "IsRunning", "()Z", (void*)CMSearchCourse_IsRunning },
        { "IsRefresh", "()Z", (void*)CMSearchCourse_IsRefresh },
        { "Cancel", "()V", (void*)CMSearchCourse_Cancel },
        { "SetRequestType", "(I)V", (void*)CMSearchCourse_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMSearchCourse_SetListener },
        { "GetCourseKey", "()V", (void*)CMSearchCourse_GetCourseKey },
        { "GetHighSearch", "()Lcom/wunding/mlplayer/business/TSearchItem;", (void*)CMSearchCourse_GetHighSearch }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMSearchCourse");
    if (clazz == 0) {
        CM_ERR("class CMSearchCourse no found");
        return -1;
    }

    gCMSearchCourseFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMSearchCourseFieldID.nativeJavaObj == 0) {
        CM_ERR("CMSearchCourse no found mNativeObj");
        return -1;
    }

    gCMSearchCourseFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMSearchCourseFieldID.jniData == 0) {
        CM_ERR("CMSearchCourse no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMSearchCourseFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMSearchCourseFieldID.callback == NULL) {
        CM_ERR("CMSearchCourse no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMSearchCourseMethods,
            sizeof(CMSearchCourseMethods) / sizeof(CMSearchCourseMethods[0]));
}


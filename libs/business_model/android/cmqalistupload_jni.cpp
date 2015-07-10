// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmqalistupload_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmqalistupload.h"
#include "imcommon_jni.h"



struct callback_cookie_CMQalistUpload {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMQalistUploadFieldID;

static void CMQalistUpload_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMQalistUpload when setting up callback.");
        return;
    }
    callback_cookie_CMQalistUpload* pCookie = new callback_cookie_CMQalistUpload;
    pCookie->listener1 = NULL;
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMQalistUploadFieldID.jniData, (int)pCookie);

    CMQalistUpload* pObj = CMQalistUpload::GetInstance();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj, (int)pObj);
}

static void CMQalistUpload_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMQalistUpload *pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMQalistUpload* pCookie = (callback_cookie_CMQalistUpload *)env->GetIntField(
        thiz, gCMQalistUploadFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMQalistUploadFieldID.jniData, 0);
}

static void CMQalistUpload_Release(JNIEnv* env, jobject thiz)
{
    CMQalistUpload* pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);

    pObj->Release();
}

static void CMQalistUpload_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMQalistUpload* pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);

    callback_cookie_CMQalistUpload* pCookie = (callback_cookie_CMQalistUpload *)env->GetIntField(
        thiz, gCMQalistUploadFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMQalistUploadFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        pObj->SetListener(para1);
    }

    return ;
}

static jint CMQalistUpload_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMQalistUpload* pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMQalistUpload_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMQalistUpload* pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);

    extern fields_t gTQAItemFieldID;
    TQAItem* pItem = (TQAItem*)env->GetIntField(item, gTQAItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static void CMQalistUpload_LoadFromFile(JNIEnv* env, jobject thiz)
{
    CMQalistUpload* pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);

    pObj->LoadFromFile();
}

static jint CMQalistUpload_Append(JNIEnv* env, jobject thiz, jobject tqa)
{
    CMQalistUpload* pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);

    extern fields_t gTQAItemFieldID;
    TQAItem* pItem = (TQAItem*)env->GetIntField(tqa, gTQAItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jint ret = pObj->Append(*pItem);
        return ret;
    }
    else {
        return -1;
    }
}

static void CMQalistUpload_Delete(JNIEnv* env, jobject thiz, jint nImageIndex)
{
    CMQalistUpload* pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);

    pObj->Delete(nImageIndex);
}

static jboolean CMQalistUpload_Start(JNIEnv* env, jobject thiz, jint nImageIndex)
{
    CMQalistUpload* pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);

    BOOL ret = pObj->Start(nImageIndex);
    return ret;
}

static void CMQalistUpload_Stop(JNIEnv* env, jobject thiz)
{
    CMQalistUpload* pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);

    pObj->Stop();
}

static jboolean CMQalistUpload_DoCreate(JNIEnv* env, jobject thiz, jobject db)
{
    CMQalistUpload* pObj = (CMQalistUpload*)env->GetIntField(thiz, gCMQalistUploadFieldID.nativeJavaObj);

    extern fields_t gsqlite3FieldID;
    sqlite3* pItem = (sqlite3*)env->GetIntField(db, gsqlite3FieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->DoCreate(*pItem
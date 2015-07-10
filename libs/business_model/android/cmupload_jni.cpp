// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmupload_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmupload.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMFileUpload {
    jclass      info_class;
    jobject     ref;
    CMSimpleResultListener* listener1;
};

fields_t gCMFileUploadFieldID;

static void CMFileUpload_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMFileUpload when setting up callback.");
        return;
    }
    callback_cookie_CMFileUpload* pCookie = new callback_cookie_CMFileUpload;
    pCookie->listener1 = new CMSimpleResultListener(gCMFileUploadFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMFileUploadFieldID.jniData, (int)pCookie);

    CMFileUpload* pObj = CMFileUpload::GetInstance();
    pObj->SetListener(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj, (int)pObj);
}

static void CMFileUpload_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMFileUpload *pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMFileUpload* pCookie = (callback_cookie_CMFileUpload *)env->GetIntField(
        thiz, gCMFileUploadFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMFileUploadFieldID.jniData, 0);
}

static jint CMFileUpload_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMFileUpload_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    extern fields_t gCMFileInfoFieldID;
    CMFileInfo* pItem = (CMFileInfo*)env->GetIntField(item, gCMFileInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMFileUpload_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    extern fields_t gCMFileInfoFieldID;
    CMFileInfo* pItem = (CMFileInfo*)env->GetIntField(obj, gCMFileInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMFileUpload_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    extern fields_t gCMFileInfoFieldID;
    CMFileInfo* pItem = (CMFileInfo*)env->GetIntField(obj, gCMFileInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMFileUpload_IsEnd(JNIEnv* env, jobject thiz)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMFileUpload_RequestMore(JNIEnv* env, jobject thiz)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMFileUpload_IsRunning(JNIEnv* env, jobject thiz)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMFileUpload_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMFileUpload_Cancel(JNIEnv* env, jobject thiz)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMFileUpload_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMFileUpload_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    callback_cookie_CMFileUpload* pCookie = (callback_cookie_CMFileUpload *)env->GetIntField(
        thiz, gCMFileUploadFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMSimpleResultListener(gCMFileUploadFieldID.callback);
        }
        
        IMSimpleResultListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

    }
}

static jint CMFileUpload_Append(JNIEnv* env, jobject thiz, jobject file)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    extern fields_t gCMFileInfoFieldID;
    CMFileInfo* pItem = (CMFileInfo*)env->GetIntField(file, gCMFileInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jint ret = pObj->Append(*pItem);
        return ret;
    }
    else {
        return -1;
    }
}

static void CMFileUpload_Delete(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    pObj->Delete(nIndex);
}

static jboolean CMFileUpload_Start(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    BOOL ret = pObj->Start(nIndex);
    return ret;
}

static void CMFileUpload_Stop(JNIEnv* env, jobject thiz)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);

    pObj->Stop();
}

static jstring CMFileUpload_Getrl(JNIEnv* env, jobject thiz)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->url.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->url.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMFileUpload_Setrl(JNIEnv* env, jobject thiz, jstring url)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(url, NULL);
    jsize size = env->GetStringLength(url);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->url = data;

    env->ReleaseStringChars(url, jChar);
    
    free(data);
    
    return true;
}

static jstring CMFileUpload_Gethumb_url(JNIEnv* env, jobject thiz)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->thumb_url.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->thumb_url.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMFileUpload_Sethumb_url(JNIEnv* env, jobject thiz, jstring thumb_url)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(thumb_url, NULL);
    jsize size = env->GetStringLength(thumb_url);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->thumb_url = data;

    env->ReleaseStringChars(thumb_url, jChar);
    
    free(data);
    
    return true;
}

static jstring CMFileUpload_GetMsgCode(JNIEnv* env, jobject thiz)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sMsgCode.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sMsgCode.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMFileUpload_SetMsgCode(JNIEnv* env, jobject thiz, jstring sMsgCode)
{
    CMFileUpload* pObj = (CMFileUpload*)env->GetIntField(thiz, gCMFileUploadFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sMsgCode, NULL);
    jsize size = env->GetStringLength(sMsgCode);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sMsgCode = data;

    env->ReleaseStringChars(sMsgCode, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_CMFileUpload(JNIEnv* env) {
    static JNINativeMethod CMFileUploadMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMFileUpload_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMFileUpload_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMFileUpload_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/CMFileInfo;)Z", (void*)CMFileUpload_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/CMFileInfo;)Z", (void*)CMFileUpload_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/CMFileInfo;)Z", (void*)CMFileUpload_Update },
        { "IsEnd", "()Z", (void*)CMFileUpload_IsEnd },
        { "RequestMore", "()Z", (void*)CMFileUpload_RequestMore },
        { "IsRunning", "()Z", (void*)CMFileUpload_IsRunning },
        { "IsRefresh", "()Z", (void*)CMFileUpload_IsRefresh },
        { "Cancel", "()V", (void*)CMFileUpload_Cancel },
        { "SetRequestType", "(I)V", (void*)CMFileUpload_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMFileUpload_SetListener },
        { "Append", "(Lcom/wunding/mlplayer/business/CMFileInfo;)I", (void*)CMFileUpload_Append },
        { "Delete", "(I)V", (void*)CMFileUpload_Delete },
        { "Start", "(I)Z", (void*)CMFileUpload_Start },
        { "Stop", "()V", (void*)CMFileUpload_Stop },
        { "Getrl", "()Ljava/lang/String;", (void*)CMFileUpload_Getrl },
        { "Setrl", "(Ljava/lang/String;)Z", (void*)CMFileUpload_Setrl },
        { "Gethumb_url", "()Ljava/lang/String;", (void*)CMFileUpload_Gethumb_url },
        { "Sethumb_url", "(Ljava/lang/String;)Z", (void*)CMFileUpload_Sethumb_url },
        { "GetMsgCode", "()Ljava/lang/String;", (void*)CMFileUpload_GetMsgCode },
        { "SetMsgCode", "(Ljava/lang/String;)Z", (void*)CMFileUpload_SetMsgCode }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMFileUpload");
    if (clazz == 0) {
        CM_ERR("class CMFileUpload no found");
        return -1;
    }

    gCMFileUploadFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMFileUploadFieldID.nativeJavaObj == 0) {
        CM_ERR("CMFileUpload no found mNativeObj");
        return -1;
    }

    gCMFileUploadFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMFileUploadFieldID.jniData == 0) {
        CM_ERR("CMFileUpload no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMFileUploadFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMFileUploadFieldID.callback == NULL) {
        CM_ERR("CMFileUpload no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMFileUploadMethods,
            sizeof(CMFileUploadMethods) / sizeof(CMFileUploadMethods[0]));
}


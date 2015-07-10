// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmcoursedownload_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmcoursedownload.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMCourseDownload {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMCourseDownloadFieldID;

static void CMCourseDownload_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMCourseDownload when setting up callback.");
        return;
    }
    callback_cookie_CMCourseDownload* pCookie = new callback_cookie_CMCourseDownload;
    pCookie->listener1 = new CMUpdateDataListener(gCMCourseDownloadFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMCourseDownloadFieldID.jniData, (int)pCookie);

    CMCourseDownload* pObj = CMCourseDownload::GetInstance();
    pObj->SetListener(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj, (int)pObj);
}

static void CMCourseDownload_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMCourseDownload *pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMCourseDownload* pCookie = (callback_cookie_CMCourseDownload *)env->GetIntField(
        thiz, gCMCourseDownloadFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMCourseDownloadFieldID.jniData, 0);
}

static jint CMCourseDownload_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMCourseDownload_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    extern fields_t gCMCourseInfoFieldID;
    CMCourseInfo* pItem = (CMCourseInfo*)env->GetIntField(item, gCMCourseInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMCourseDownload_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    extern fields_t gCMCourseInfoFieldID;
    CMCourseInfo* pItem = (CMCourseInfo*)env->GetIntField(obj, gCMCourseInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMCourseDownload_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    extern fields_t gCMCourseInfoFieldID;
    CMCourseInfo* pItem = (CMCourseInfo*)env->GetIntField(obj, gCMCourseInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMCourseDownload_IsEnd(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMCourseDownload_RequestMore(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMCourseDownload_IsRunning(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMCourseDownload_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMCourseDownload_Cancel(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMCourseDownload_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMCourseDownload_GoOnDownload(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    pObj->GoOnDownload();
}

static void CMCourseDownload_Release(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    pObj->Release();
}

static void CMCourseDownload_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    callback_cookie_CMCourseDownload* pCookie = (callback_cookie_CMCourseDownload *)env->GetIntField(
        thiz, gCMCourseDownloadFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMCourseDownloadFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

    }
}

static jint CMCourseDownload_Append(JNIEnv* env, jobject thiz, jobject course)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    extern fields_t gCMCourseInfoFieldID;
    CMCourseInfo* pItem = (CMCourseInfo*)env->GetIntField(course, gCMCourseInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jint ret = pObj->Append(*pItem);
        return ret;
    }
    else {
        return -1;
    }
}

static void CMCourseDownload_Delete(JNIEnv* env, jobject thiz, jint nCourseIndex)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    pObj->Delete(nCourseIndex);
}

static jboolean CMCourseDownload_Start(JNIEnv* env, jobject thiz, jint nCourseIndex)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    BOOL ret = pObj->Start(nCourseIndex);
    return ret;
}

static void CMCourseDownload_Stop(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    pObj->Stop();
}

static void CMCourseDownload_CheckCourseware(JNIEnv* env, jobject thiz, jint nCourseIndex, jint nCoursewareIndex)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    pObj->CheckCourseware(nCourseIndex, nCoursewareIndex);
}

static void CMCourseDownload_UnCheckCourseware(JNIEnv* env, jobject thiz, jint nCourseIndex, jint nCoursewareIndex)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    pObj->UnCheckCourseware(nCourseIndex, nCoursewareIndex);
}

static jint CMCourseDownload_Status(JNIEnv* env, jobject thiz, jint nCourseIndex)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    int ret = pObj->Status(nCourseIndex);
    return ret;
}

static jint CMCourseDownload_GetCurrent(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    int ret = pObj->GetCurrent();
    return ret;
}

static jboolean CMCourseDownload_isComplete(JNIEnv* env, jobject thiz, jint nCourseIndex, jint nCoursewareIndex)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    BOOL ret = pObj->isComplete(nCourseIndex, nCoursewareIndex);
    return ret;
}

static jstring CMCourseDownload_GetStatusText(JNIEnv* env, jobject thiz, jint nCourseIndex)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    const char* ret = pObj->GetStatusText(nCourseIndex);
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMCourseDownload_GetStatusText(JNIEnv* env, jobject thiz, jint nCourseIndex, jint nCoursewareIndex)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    const char* ret = pObj->GetStatusText(nCourseIndex, nCoursewareIndex);
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMCourseDownload_IsDonwloaded(JNIEnv* env, jobject thiz, jobject item)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    extern fields_t gTCoursewareItemFieldID;
    TCoursewareItem* pItem = (TCoursewareItem*)env->GetIntField(item, gTCoursewareItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->IsDonwloaded(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static void CMCourseDownload_LoadFromFile(JNIEnv* env, jobject thiz)
{
    CMCourseDownload* pObj = (CMCourseDownload*)env->GetIntField(thiz, gCMCourseDownloadFieldID.nativeJavaObj);

    pObj->LoadFromFile();
}

int register_com_wunding_mlplayer_business_CMCourseDownload(JNIEnv* env) {
    static jstring (*CMCourseDownload_GetStatusText1)(JNIEnv*, jobject, jint);
    CMCourseDownload_GetStatusText1 = CMCourseDownload_GetStatusText;
    static jstring (*CMCourseDownload_GetStatusText2)(JNIEnv*, jobject, jint, jint);
    CMCourseDownload_GetStatusText2 = CMCourseDownload_GetStatusText;

    static JNINativeMethod CMCourseDownloadMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMCourseDownload_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMCourseDownload_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMCourseDownload_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/CMCourseInfo;)Z", (void*)CMCourseDownload_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/CMCourseInfo;)Z", (void*)CMCourseDownload_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/CMCourseInfo;)Z", (void*)CMCourseDownload_Update },
        { "IsEnd", "()Z", (void*)CMCourseDownload_IsEnd },
        { "RequestMore", "()Z", (void*)CMCourseDownload_RequestMore },
        { "IsRunning", "()Z", (void*)CMCourseDownload_IsRunning },
        { "IsRefresh", "()Z", (void*)CMCourseDownload_IsRefresh },
        { "Cancel", "()V", (void*)CMCourseDownload_Cancel },
        { "SetRequestType", "(I)V", (void*)CMCourseDownload_SetRequestType },
        { "GoOnDownload", "()V", (void*)CMCourseDownload_GoOnDownload },
        { "Release", "()V", (void*)CMCourseDownload_Release },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMCourseDownload_SetListener },
        { "Append", "(Lcom/wunding/mlplayer/business/CMCourseInfo;)I", (void*)CMCourseDownload_Append },
        { "Delete", "(I)V", (void*)CMCourseDownload_Delete },
        { "Start", "(I)Z", (void*)CMCourseDownload_Start },
        { "Stop", "()V", (void*)CMCourseDownload_Stop },
        { "CheckCourseware", "(II)V", (void*)CMCourseDownload_CheckCourseware },
        { "UnCheckCourseware", "(II)V", (void*)CMCourseDownload_UnCheckCourseware },
        { "Status", "(I)I", (void*)CMCourseDownload_Status },
        { "GetCurrent", "()I", (void*)CMCourseDownload_GetCurrent },
        { "isComplete", "(II)Z", (void*)CMCourseDownload_isComplete },
        { "GetStatusText", "(I)Ljava/lang/String;", (void*)CMCourseDownload_GetStatusText1 },
        { "GetStatusText", "(II)Ljava/lang/String;", (void*)CMCourseDownload_GetStatusText2 },
        { "IsDonwloaded", "(Lcom/wunding/mlplayer/business/TCoursewareItem;)Z", (void*)CMCourseDownload_IsDonwloaded },
        { "LoadFromFile", "()V", (void*)CMCourseDownload_LoadFromFile }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMCourseDownload");
    if (clazz == 0) {
        CM_ERR("class CMCourseDownload no found");
        return -1;
    }

    gCMCourseDownloadFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMCourseDownloadFieldID.nativeJavaObj == 0) {
        CM_ERR("CMCourseDownload no found mNativeObj");
        return -1;
    }

    gCMCourseDownloadFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMCourseDownloadFieldID.jniData == 0) {
        CM_ERR("CMCourseDownload no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMCourseDownloadFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMCourseDownloadFieldID.callback == NULL) {
        CM_ERR("CMCourseDownload no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMCourseDownloadMethods,
            sizeof(CMCourseDownloadMethods) / sizeof(CMCourseDownloadMethods[0]));
}


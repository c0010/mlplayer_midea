// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmundone_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmundone.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTUnDoneItemFieldID;

static void TUnDoneItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TUnDoneItem* pObj = new TUnDoneItem();

    env->SetIntField(thiz, gTUnDoneItemFieldID.nativeJavaObj, (int)pObj);
}

static void TUnDoneItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TUnDoneItem*)env->GetIntField(thiz, gTUnDoneItemFieldID.nativeJavaObj);
}

static jstring TUnDoneItem_GetType(JNIEnv* env, jobject thiz)
{
    TUnDoneItem* pObj = (TUnDoneItem*)env->GetIntField(thiz, gTUnDoneItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sType.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sType.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TUnDoneItem_SetType(JNIEnv* env, jobject thiz, jstring sType)
{
    TUnDoneItem* pObj = (TUnDoneItem*)env->GetIntField(thiz, gTUnDoneItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sType, NULL);
    jsize size = env->GetStringLength(sType);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sType = data;

    env->ReleaseStringChars(sType, jChar);
    
    free(data);
    
    return true;
}

static jint TUnDoneItem_GetItemCount(JNIEnv* env, jobject thiz)
{
    TUnDoneItem* pObj = (TUnDoneItem*)env->GetIntField(thiz, gTUnDoneItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nItemCount;
}
                
static jboolean TUnDoneItem_SetItemCount(JNIEnv* env, jobject thiz, jint nItemCount)
{
    TUnDoneItem* pObj = (TUnDoneItem*)env->GetIntField(thiz, gTUnDoneItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nItemCount = nItemCount;
    return true;
}
                
int register_com_wunding_mlplayer_business_TUnDoneItem(JNIEnv* env) {
    static JNINativeMethod TUnDoneItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TUnDoneItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TUnDoneItem_nativeDestructor },
        { "GetType", "()Ljava/lang/String;", (void*)TUnDoneItem_GetType },
        { "SetType", "(Ljava/lang/String;)Z", (void*)TUnDoneItem_SetType },
        { "GetItemCount", "()I", (void*)TUnDoneItem_GetItemCount },
        { "SetItemCount", "(I)Z", (void*)TUnDoneItem_SetItemCount }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TUnDoneItem");
    if (clazz == 0) {
        CM_ERR("class TUnDoneItem no found");
        return -1;
    }

    gTUnDoneItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTUnDoneItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TUnDoneItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TUnDoneItemMethods,
            sizeof(TUnDoneItemMethods) / sizeof(TUnDoneItemMethods[0]));
}


struct callback_cookie_CMUnDone {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMUnDoneFieldID;

static void CMUnDone_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMUnDone when setting up callback.");
        return;
    }
    callback_cookie_CMUnDone* pCookie = new callback_cookie_CMUnDone;
    pCookie->listener1 = new CMUpdateDataListener(gCMUnDoneFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMUnDoneFieldID.jniData, (int)pCookie);

    CMUnDone* pObj = CMUnDone::GetInstance();
    pObj->SetListener(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj, (int)pObj);
}

static void CMUnDone_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMUnDone *pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMUnDone* pCookie = (callback_cookie_CMUnDone *)env->GetIntField(
        thiz, gCMUnDoneFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMUnDoneFieldID.jniData, 0);
}

static jint CMUnDone_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMUnDone_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    extern fields_t gTUnDoneItemFieldID;
    TUnDoneItem* pItem = (TUnDoneItem*)env->GetIntField(item, gTUnDoneItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMUnDone_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    extern fields_t gTUnDoneItemFieldID;
    TUnDoneItem* pItem = (TUnDoneItem*)env->GetIntField(obj, gTUnDoneItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMUnDone_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    extern fields_t gTUnDoneItemFieldID;
    TUnDoneItem* pItem = (TUnDoneItem*)env->GetIntField(obj, gTUnDoneItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMUnDone_IsEnd(JNIEnv* env, jobject thiz)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMUnDone_RequestMore(JNIEnv* env, jobject thiz)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMUnDone_IsRunning(JNIEnv* env, jobject thiz)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMUnDone_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMUnDone_Cancel(JNIEnv* env, jobject thiz)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMUnDone_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static jboolean CMUnDone_GetUnDone(JNIEnv* env, jobject thiz)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    BOOL ret = pObj->GetUnDone();
    return ret;
}

static void CMUnDone_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMUnDone* pObj = (CMUnDone*)env->GetIntField(thiz, gCMUnDoneFieldID.nativeJavaObj);

    callback_cookie_CMUnDone* pCookie = (callback_cookie_CMUnDone *)env->GetIntField(
        thiz, gCMUnDoneFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMUnDoneFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

    }
}

int register_com_wunding_mlplayer_business_CMUnDone(JNIEnv* env) {
    static JNINativeMethod CMUnDoneMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMUnDone_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMUnDone_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMUnDone_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TUnDoneItem;)Z", (void*)CMUnDone_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TUnDoneItem;)Z", (void*)CMUnDone_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TUnDoneItem;)Z", (void*)CMUnDone_Update },
        { "IsEnd", "()Z", (void*)CMUnDone_IsEnd },
        { "RequestMore", "()Z", (void*)CMUnDone_RequestMore },
        { "IsRunning", "()Z", (void*)CMUnDone_IsRunning },
        { "IsRefresh", "()Z", (void*)CMUnDone_IsRefresh },
        { "Cancel", "()V", (void*)CMUnDone_Cancel },
        { "SetRequestType", "(I)V", (void*)CMUnDone_SetRequestType },
        { "GetUnDone", "()Z", (void*)CMUnDone_GetUnDone },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMUnDone_SetListener }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMUnDone");
    if (clazz == 0) {
        CM_ERR("class CMUnDone no found");
        return -1;
    }

    gCMUnDoneFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMUnDoneFieldID.nativeJavaObj == 0) {
        CM_ERR("CMUnDone no found mNativeObj");
        return -1;
    }

    gCMUnDoneFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMUnDoneFieldID.jniData == 0) {
        CM_ERR("CMUnDone no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMUnDoneFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMUnDoneFieldID.callback == NULL) {
        CM_ERR("CMUnDone no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMUnDoneMethods,
            sizeof(CMUnDoneMethods) / sizeof(CMUnDoneMethods[0]));
}


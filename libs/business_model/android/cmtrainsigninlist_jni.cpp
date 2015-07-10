// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmtrainsigninlist_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmtrainsigninlist.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_TTrainSignInItem {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gTTrainSignInItemFieldID;

static void TTrainSignInItem_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find TTrainSignInItem when setting up callback.");
        return;
    }
    callback_cookie_TTrainSignInItem* pCookie = new callback_cookie_TTrainSignInItem;
    pCookie->listener1 = new CMUpdateDataListener(gTTrainSignInItemFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gTTrainSignInItemFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gTTrainSignInItemFieldID.jniData, (int)pCookie);

    TTrainSignInItem* pObj = new TTrainSignInItem();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj, (int)pObj);
}

static void TTrainSignInItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem *pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_TTrainSignInItem* pCookie = (callback_cookie_TTrainSignInItem *)env->GetIntField(
        thiz, gTTrainSignInItemFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gTTrainSignInItemFieldID.jniData, 0);
}

static jboolean TTrainSignInItem_Update(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);

    BOOL ret = pObj->Update();
    return ret;
}

static jboolean TTrainSignInItem_Refresh(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);

    BOOL ret = pObj->Refresh();
    return ret;
}

static jboolean TTrainSignInItem_RequestInfo(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestInfo();
    return ret;
}

static jboolean TTrainSignInItem_SignInTrain(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);

    BOOL ret = pObj->SignInTrain();
    return ret;
}

static void TTrainSignInItem_SetListener(JNIEnv* env, jobject thiz, jobject pUpdateDataListener, jobject pSimpleResultListener)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);

    callback_cookie_TTrainSignInItem* pCookie = (callback_cookie_TTrainSignInItem *)env->GetIntField(
        thiz, gTTrainSignInItemFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gTTrainSignInItemFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pUpdateDataListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gTTrainSignInItemFieldID.callback);
        }
        
        IMSimpleResultListener* para2 = NULL;
        if (pSimpleResultListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        pObj->SetListener(para1, para2);
    }

    return ;
}

static void TTrainSignInItem_Cancel(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);

    pObj->Cancel();
}

static jobject TTrainSignInItem_CopyFromTTrainSignInItem(JNIEnv* env, jobject thiz, jobject right)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);

    extern fields_t gTTrainSignInItemFieldID;
    TTrainSignInItem* pObjCopy = (TTrainSignInItem*)env->GetIntField(right, gTTrainSignInItemFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static jstring TTrainSignInItem_GetID(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainSignInItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainSignInItem_GetTitle(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTitle.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainSignInItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTitle, NULL);
    jsize size = env->GetStringLength(sTitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTitle = data;

    env->ReleaseStringChars(sTitle, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainSignInItem_GetTrainID(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTrainID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTrainID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainSignInItem_SetTrainID(JNIEnv* env, jobject thiz, jstring sTrainID)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTrainID, NULL);
    jsize size = env->GetStringLength(sTrainID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTrainID = data;

    env->ReleaseStringChars(sTrainID, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainSignInItem_GetImageURL(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sImageURL.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sImageURL.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainSignInItem_SetImageURL(JNIEnv* env, jobject thiz, jstring sImageURL)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sImageURL, NULL);
    jsize size = env->GetStringLength(sImageURL);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sImageURL = data;

    env->ReleaseStringChars(sImageURL, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainSignInItem_GetTime(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTime.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTime.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainSignInItem_SetTime(JNIEnv* env, jobject thiz, jstring sTime)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTime, NULL);
    jsize size = env->GetStringLength(sTime);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTime = data;

    env->ReleaseStringChars(sTime, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainSignInItem_GetAddress(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAddress.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAddress.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainSignInItem_SetAddress(JNIEnv* env, jobject thiz, jstring sAddress)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAddress, NULL);
    jsize size = env->GetStringLength(sAddress);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAddress = data;

    env->ReleaseStringChars(sAddress, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainSignInItem_GetSignInTime(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sSignInTime.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sSignInTime.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainSignInItem_SetSignInTime(JNIEnv* env, jobject thiz, jstring sSignInTime)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sSignInTime, NULL);
    jsize size = env->GetStringLength(sSignInTime);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sSignInTime = data;

    env->ReleaseStringChars(sSignInTime, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainSignInItem_GetFlag(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sFlag.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sFlag.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainSignInItem_SetFlag(JNIEnv* env, jobject thiz, jstring sFlag)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sFlag, NULL);
    jsize size = env->GetStringLength(sFlag);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sFlag = data;

    env->ReleaseStringChars(sFlag, jChar);
    
    free(data);
    
    return true;
}

static jint TTrainSignInItem_GetMode(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nMode;
}
                
static jboolean TTrainSignInItem_SetMode(JNIEnv* env, jobject thiz, jint nMode)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nMode = nMode;
    return true;
}
                
static jint TTrainSignInItem_GetSignInNum(JNIEnv* env, jobject thiz)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nSignInNum;
}
                
static jboolean TTrainSignInItem_SetSignInNum(JNIEnv* env, jobject thiz, jint nSignInNum)
{
    TTrainSignInItem* pObj = (TTrainSignInItem*)env->GetIntField(thiz, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nSignInNum = nSignInNum;
    return true;
}
                
int register_com_wunding_mlplayer_business_TTrainSignInItem(JNIEnv* env) {
    static JNINativeMethod TTrainSignInItemMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)TTrainSignInItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TTrainSignInItem_nativeDestructor },
        { "Update", "()Z", (void*)TTrainSignInItem_Update },
        { "Refresh", "()Z", (void*)TTrainSignInItem_Refresh },
        { "RequestInfo", "()Z", (void*)TTrainSignInItem_RequestInfo },
        { "SignInTrain", "()Z", (void*)TTrainSignInItem_SignInTrain },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)TTrainSignInItem_SetListener },
        { "Cancel", "()V", (void*)TTrainSignInItem_Cancel },
        { "CopyFromTTrainSignInItem", "(Lcom/wunding/mlplayer/business/TTrainSignInItem;)Lcom/wunding/mlplayer/business/TTrainSignInItem;", (void*)TTrainSignInItem_CopyFromTTrainSignInItem },
        { "GetID", "()Ljava/lang/String;", (void*)TTrainSignInItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TTrainSignInItem_SetID },
        { "GetTitle", "()Ljava/lang/String;", (void*)TTrainSignInItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)TTrainSignInItem_SetTitle },
        { "GetTrainID", "()Ljava/lang/String;", (void*)TTrainSignInItem_GetTrainID },
        { "SetTrainID", "(Ljava/lang/String;)Z", (void*)TTrainSignInItem_SetTrainID },
        { "GetImageURL", "()Ljava/lang/String;", (void*)TTrainSignInItem_GetImageURL },
        { "SetImageURL", "(Ljava/lang/String;)Z", (void*)TTrainSignInItem_SetImageURL },
        { "GetTime", "()Ljava/lang/String;", (void*)TTrainSignInItem_GetTime },
        { "SetTime", "(Ljava/lang/String;)Z", (void*)TTrainSignInItem_SetTime },
        { "GetAddress", "()Ljava/lang/String;", (void*)TTrainSignInItem_GetAddress },
        { "SetAddress", "(Ljava/lang/String;)Z", (void*)TTrainSignInItem_SetAddress },
        { "GetSignInTime", "()Ljava/lang/String;", (void*)TTrainSignInItem_GetSignInTime },
        { "SetSignInTime", "(Ljava/lang/String;)Z", (void*)TTrainSignInItem_SetSignInTime },
        { "GetFlag", "()Ljava/lang/String;", (void*)TTrainSignInItem_GetFlag },
        { "SetFlag", "(Ljava/lang/String;)Z", (void*)TTrainSignInItem_SetFlag },
        { "GetMode", "()I", (void*)TTrainSignInItem_GetMode },
        { "SetMode", "(I)Z", (void*)TTrainSignInItem_SetMode },
        { "GetSignInNum", "()I", (void*)TTrainSignInItem_GetSignInNum },
        { "SetSignInNum", "(I)Z", (void*)TTrainSignInItem_SetSignInNum }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TTrainSignInItem");
    if (clazz == 0) {
        CM_ERR("class TTrainSignInItem no found");
        return -1;
    }

    gTTrainSignInItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTTrainSignInItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TTrainSignInItem no found mNativeObj");
        return -1;
    }

    gTTrainSignInItemFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gTTrainSignInItemFieldID.jniData == 0) {
        CM_ERR("TTrainSignInItem no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gTTrainSignInItemFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gTTrainSignInItemFieldID.callback == NULL) {
        CM_ERR("TTrainSignInItem no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TTrainSignInItemMethods,
            sizeof(TTrainSignInItemMethods) / sizeof(TTrainSignInItemMethods[0]));
}


struct callback_cookie_CMTrainSignInList {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMTrainSignInListFieldID;

static void CMTrainSignInList_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMTrainSignInList when setting up callback.");
        return;
    }
    callback_cookie_CMTrainSignInList* pCookie = new callback_cookie_CMTrainSignInList;
    pCookie->listener1 = new CMUpdateDataListener(gCMTrainSignInListFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMTrainSignInListFieldID.jniData, (int)pCookie);

    CMTrainSignInList* pObj = new CMTrainSignInList();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj, (int)pObj);
}

static void CMTrainSignInList_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMTrainSignInList *pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMTrainSignInList* pCookie = (callback_cookie_CMTrainSignInList *)env->GetIntField(
        thiz, gCMTrainSignInListFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMTrainSignInListFieldID.jniData, 0);
}

static jint CMTrainSignInList_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMTrainSignInList_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    extern fields_t gTTrainSignInItemFieldID;
    TTrainSignInItem* pItem = (TTrainSignInItem*)env->GetIntField(item, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMTrainSignInList_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    extern fields_t gTTrainSignInItemFieldID;
    TTrainSignInItem* pItem = (TTrainSignInItem*)env->GetIntField(obj, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMTrainSignInList_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    extern fields_t gTTrainSignInItemFieldID;
    TTrainSignInItem* pItem = (TTrainSignInItem*)env->GetIntField(obj, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMTrainSignInList_IsEnd(JNIEnv* env, jobject thiz)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMTrainSignInList_RequestMore(JNIEnv* env, jobject thiz)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMTrainSignInList_IsRunning(JNIEnv* env, jobject thiz)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMTrainSignInList_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMTrainSignInList_Cancel(JNIEnv* env, jobject thiz)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMTrainSignInList_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMTrainSignInList_SetListener(JNIEnv* env, jobject thiz, jobject m_pListener)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    callback_cookie_CMTrainSignInList* pCookie = (callback_cookie_CMTrainSignInList *)env->GetIntField(
        thiz, gCMTrainSignInListFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMTrainSignInListFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (m_pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        pObj->SetListener(para1);
    }

    return ;
}

static jboolean CMTrainSignInList_RequestTrainApplyList(JNIEnv* env, jobject thiz, jstring mFlag)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    const jchar* jmFlag = env->GetStringChars(mFlag, NULL);
    jsize sizemFlag = env->GetStringLength(mFlag);
    char* pmFlag = UTF16toUTF8((jchar*)jmFlag, (size_t*)&sizemFlag);
    BOOL ret = pObj->RequestTrainApplyList(pmFlag);
    env->ReleaseStringChars(mFlag, jmFlag);
    free(pmFlag);
    return ret;
}

static jboolean CMTrainSignInList_RemoveSuccessItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMTrainSignInList* pObj = (CMTrainSignInList*)env->GetIntField(thiz, gCMTrainSignInListFieldID.nativeJavaObj);

    BOOL ret = pObj->RemoveSuccessItem(nIndex);
    return ret;
}

int register_com_wunding_mlplayer_business_CMTrainSignInList(JNIEnv* env) {
    static JNINativeMethod CMTrainSignInListMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMTrainSignInList_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMTrainSignInList_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMTrainSignInList_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TTrainSignInItem;)Z", (void*)CMTrainSignInList_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TTrainSignInItem;)Z", (void*)CMTrainSignInList_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TTrainSignInItem;)Z", (void*)CMTrainSignInList_Update },
        { "IsEnd", "()Z", (void*)CMTrainSignInList_IsEnd },
        { "RequestMore", "()Z", (void*)CMTrainSignInList_RequestMore },
        { "IsRunning", "()Z", (void*)CMTrainSignInList_IsRunning },
        { "IsRefresh", "()Z", (void*)CMTrainSignInList_IsRefresh },
        { "Cancel", "()V", (void*)CMTrainSignInList_Cancel },
        { "SetRequestType", "(I)V", (void*)CMTrainSignInList_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMTrainSignInList_SetListener },
        { "RequestTrainApplyList", "(Ljava/lang/String;)Z", (void*)CMTrainSignInList_RequestTrainApplyList },
        { "RemoveSuccessItem", "(I)Z", (void*)CMTrainSignInList_RemoveSuccessItem }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMTrainSignInList");
    if (clazz == 0) {
        CM_ERR("class CMTrainSignInList no found");
        return -1;
    }

    gCMTrainSignInListFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMTrainSignInListFieldID.nativeJavaObj == 0) {
        CM_ERR("CMTrainSignInList no found mNativeObj");
        return -1;
    }

    gCMTrainSignInListFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMTrainSignInListFieldID.jniData == 0) {
        CM_ERR("CMTrainSignInList no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMTrainSignInListFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMTrainSignInListFieldID.callback == NULL) {
        CM_ERR("CMTrainSignInList no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMTrainSignInListMethods,
            sizeof(CMTrainSignInListMethods) / sizeof(CMTrainSignInListMethods[0]));
}


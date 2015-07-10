// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmmytrainlist_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmmytrainlist.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_TMyTrainItem {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gTMyTrainItemFieldID;

static void TMyTrainItem_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find TMyTrainItem when setting up callback.");
        return;
    }
    callback_cookie_TMyTrainItem* pCookie = new callback_cookie_TMyTrainItem;
    pCookie->listener1 = new CMUpdateDataListener(gTMyTrainItemFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gTMyTrainItemFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gTMyTrainItemFieldID.jniData, (int)pCookie);

    TMyTrainItem* pObj = new TMyTrainItem();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj, (int)pObj);
}

static void TMyTrainItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    TMyTrainItem *pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_TMyTrainItem* pCookie = (callback_cookie_TMyTrainItem *)env->GetIntField(
        thiz, gTMyTrainItemFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gTMyTrainItemFieldID.jniData, 0);
}

static jboolean TMyTrainItem_Update(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);

    BOOL ret = pObj->Update();
    return ret;
}

static jboolean TMyTrainItem_Refresh(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);

    BOOL ret = pObj->Refresh();
    return ret;
}

static jboolean TMyTrainItem_RequestInfo(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestInfo();
    return ret;
}

static void TMyTrainItem_SetListener(JNIEnv* env, jobject thiz, jobject pUpdateDataListener, jobject pSimpleResultListener)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);

    callback_cookie_TMyTrainItem* pCookie = (callback_cookie_TMyTrainItem *)env->GetIntField(
        thiz, gTMyTrainItemFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gTMyTrainItemFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pUpdateDataListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gTMyTrainItemFieldID.callback);
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

static void TMyTrainItem_Cancel(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);

    pObj->Cancel();
}

static jobject TMyTrainItem_CopyFromTMyTrainItem(JNIEnv* env, jobject thiz, jobject right)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);

    extern fields_t gTMyTrainItemFieldID;
    TMyTrainItem* pObjCopy = (TMyTrainItem*)env->GetIntField(right, gTMyTrainItemFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static jstring TMyTrainItem_GetID(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetTitle(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTitle.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTitle, NULL);
    jsize size = env->GetStringLength(sTitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTitle = data;

    env->ReleaseStringChars(sTitle, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetIcon(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sIcon.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sIcon.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetIcon(JNIEnv* env, jobject thiz, jstring sIcon)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sIcon, NULL);
    jsize size = env->GetStringLength(sIcon);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sIcon = data;

    env->ReleaseStringChars(sIcon, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetTrainNumber(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTrainNumber.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTrainNumber.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetTrainNumber(JNIEnv* env, jobject thiz, jstring sTrainNumber)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTrainNumber, NULL);
    jsize size = env->GetStringLength(sTrainNumber);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTrainNumber = data;

    env->ReleaseStringChars(sTrainNumber, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetMode(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sMode.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sMode.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetMode(JNIEnv* env, jobject thiz, jstring sMode)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sMode, NULL);
    jsize size = env->GetStringLength(sMode);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sMode = data;

    env->ReleaseStringChars(sMode, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetTrainTime(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTrainTime.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTrainTime.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetTrainTime(JNIEnv* env, jobject thiz, jstring sTrainTime)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTrainTime, NULL);
    jsize size = env->GetStringLength(sTrainTime);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTrainTime = data;

    env->ReleaseStringChars(sTrainTime, jChar);
    
    free(data);
    
    return true;
}

static jint TMyTrainItem_GetUserCount(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nUserCount;
}
                
static jboolean TMyTrainItem_SetUserCount(JNIEnv* env, jobject thiz, jint nUserCount)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nUserCount = nUserCount;
    return true;
}
                
static jstring TMyTrainItem_GetDesc(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDesc.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sDesc.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetDesc(JNIEnv* env, jobject thiz, jstring sDesc)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDesc, NULL);
    jsize size = env->GetStringLength(sDesc);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sDesc = data;

    env->ReleaseStringChars(sDesc, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetRemark(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sRemark.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sRemark.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetRemark(JNIEnv* env, jobject thiz, jstring sRemark)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sRemark, NULL);
    jsize size = env->GetStringLength(sRemark);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sRemark = data;

    env->ReleaseStringChars(sRemark, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetRoomID(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sRoomID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sRoomID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetRoomID(JNIEnv* env, jobject thiz, jstring sRoomID)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sRoomID, NULL);
    jsize size = env->GetStringLength(sRoomID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sRoomID = data;

    env->ReleaseStringChars(sRoomID, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetRoomJID(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sRoomJID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sRoomJID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetRoomJID(JNIEnv* env, jobject thiz, jstring sRoomJID)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sRoomJID, NULL);
    jsize size = env->GetStringLength(sRoomJID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sRoomJID = data;

    env->ReleaseStringChars(sRoomJID, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetRoomPwd(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sRoomPwd.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sRoomPwd.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetRoomPwd(JNIEnv* env, jobject thiz, jstring sRoomPwd)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sRoomPwd, NULL);
    jsize size = env->GetStringLength(sRoomPwd);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sRoomPwd = data;

    env->ReleaseStringChars(sRoomPwd, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetTabList(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTabList.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTabList.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetTabList(JNIEnv* env, jobject thiz, jstring sTabList)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTabList, NULL);
    jsize size = env->GetStringLength(sTabList);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTabList = data;

    env->ReleaseStringChars(sTabList, jChar);
    
    free(data);
    
    return true;
}

static jstring TMyTrainItem_GetAddress(JNIEnv* env, jobject thiz)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAddress.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAddress.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TMyTrainItem_SetAddress(JNIEnv* env, jobject thiz, jstring sAddress)
{
    TMyTrainItem* pObj = (TMyTrainItem*)env->GetIntField(thiz, gTMyTrainItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAddress, NULL);
    jsize size = env->GetStringLength(sAddress);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAddress = data;

    env->ReleaseStringChars(sAddress, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TMyTrainItem(JNIEnv* env) {
    static JNINativeMethod TMyTrainItemMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)TMyTrainItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TMyTrainItem_nativeDestructor },
        { "Update", "()Z", (void*)TMyTrainItem_Update },
        { "Refresh", "()Z", (void*)TMyTrainItem_Refresh },
        { "RequestInfo", "()Z", (void*)TMyTrainItem_RequestInfo },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)TMyTrainItem_SetListener },
        { "Cancel", "()V", (void*)TMyTrainItem_Cancel },
        { "CopyFromTMyTrainItem", "(Lcom/wunding/mlplayer/business/TMyTrainItem;)Lcom/wunding/mlplayer/business/TMyTrainItem;", (void*)TMyTrainItem_CopyFromTMyTrainItem },
        { "GetID", "()Ljava/lang/String;", (void*)TMyTrainItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetID },
        { "GetTitle", "()Ljava/lang/String;", (void*)TMyTrainItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetTitle },
        { "GetIcon", "()Ljava/lang/String;", (void*)TMyTrainItem_GetIcon },
        { "SetIcon", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetIcon },
        { "GetTrainNumber", "()Ljava/lang/String;", (void*)TMyTrainItem_GetTrainNumber },
        { "SetTrainNumber", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetTrainNumber },
        { "GetMode", "()Ljava/lang/String;", (void*)TMyTrainItem_GetMode },
        { "SetMode", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetMode },
        { "GetTrainTime", "()Ljava/lang/String;", (void*)TMyTrainItem_GetTrainTime },
        { "SetTrainTime", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetTrainTime },
        { "GetUserCount", "()I", (void*)TMyTrainItem_GetUserCount },
        { "SetUserCount", "(I)Z", (void*)TMyTrainItem_SetUserCount },
        { "GetDesc", "()Ljava/lang/String;", (void*)TMyTrainItem_GetDesc },
        { "SetDesc", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetDesc },
        { "GetRemark", "()Ljava/lang/String;", (void*)TMyTrainItem_GetRemark },
        { "SetRemark", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetRemark },
        { "GetRoomID", "()Ljava/lang/String;", (void*)TMyTrainItem_GetRoomID },
        { "SetRoomID", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetRoomID },
        { "GetRoomJID", "()Ljava/lang/String;", (void*)TMyTrainItem_GetRoomJID },
        { "SetRoomJID", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetRoomJID },
        { "GetRoomPwd", "()Ljava/lang/String;", (void*)TMyTrainItem_GetRoomPwd },
        { "SetRoomPwd", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetRoomPwd },
        { "GetTabList", "()Ljava/lang/String;", (void*)TMyTrainItem_GetTabList },
        { "SetTabList", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetTabList },
        { "GetAddress", "()Ljava/lang/String;", (void*)TMyTrainItem_GetAddress },
        { "SetAddress", "(Ljava/lang/String;)Z", (void*)TMyTrainItem_SetAddress }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TMyTrainItem");
    if (clazz == 0) {
        CM_ERR("class TMyTrainItem no found");
        return -1;
    }

    gTMyTrainItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTMyTrainItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TMyTrainItem no found mNativeObj");
        return -1;
    }

    gTMyTrainItemFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gTMyTrainItemFieldID.jniData == 0) {
        CM_ERR("TMyTrainItem no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gTMyTrainItemFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gTMyTrainItemFieldID.callback == NULL) {
        CM_ERR("TMyTrainItem no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TMyTrainItemMethods,
            sizeof(TMyTrainItemMethods) / sizeof(TMyTrainItemMethods[0]));
}


struct callback_cookie_CMMyTrainList {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMMyTrainListFieldID;

static void CMMyTrainList_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMMyTrainList when setting up callback.");
        return;
    }
    callback_cookie_CMMyTrainList* pCookie = new callback_cookie_CMMyTrainList;
    pCookie->listener1 = new CMUpdateDataListener(gCMMyTrainListFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMMyTrainListFieldID.jniData, (int)pCookie);

    CMMyTrainList* pObj = new CMMyTrainList();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj, (int)pObj);
}

static void CMMyTrainList_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMMyTrainList *pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMMyTrainList* pCookie = (callback_cookie_CMMyTrainList *)env->GetIntField(
        thiz, gCMMyTrainListFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMMyTrainListFieldID.jniData, 0);
}

static jint CMMyTrainList_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMMyTrainList_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    extern fields_t gTMyTrainItemFieldID;
    TMyTrainItem* pItem = (TMyTrainItem*)env->GetIntField(item, gTMyTrainItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMMyTrainList_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    extern fields_t gTMyTrainItemFieldID;
    TMyTrainItem* pItem = (TMyTrainItem*)env->GetIntField(obj, gTMyTrainItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMMyTrainList_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    extern fields_t gTMyTrainItemFieldID;
    TMyTrainItem* pItem = (TMyTrainItem*)env->GetIntField(obj, gTMyTrainItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMMyTrainList_IsEnd(JNIEnv* env, jobject thiz)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMMyTrainList_RequestMore(JNIEnv* env, jobject thiz)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMMyTrainList_IsRunning(JNIEnv* env, jobject thiz)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMMyTrainList_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMMyTrainList_Cancel(JNIEnv* env, jobject thiz)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMMyTrainList_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMMyTrainList_SetListener(JNIEnv* env, jobject thiz, jobject m_pListener)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    callback_cookie_CMMyTrainList* pCookie = (callback_cookie_CMMyTrainList *)env->GetIntField(
        thiz, gCMMyTrainListFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMMyTrainListFieldID.callback);
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

static jboolean CMMyTrainList_RequestTrainApplyList(JNIEnv* env, jobject thiz)
{
    CMMyTrainList* pObj = (CMMyTrainList*)env->GetIntField(thiz, gCMMyTrainListFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestTrainApplyList();
    return ret;
}

int register_com_wunding_mlplayer_business_CMMyTrainList(JNIEnv* env) {
    static JNINativeMethod CMMyTrainListMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMMyTrainList_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMMyTrainList_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMMyTrainList_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TMyTrainItem;)Z", (void*)CMMyTrainList_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TMyTrainItem;)Z", (void*)CMMyTrainList_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TMyTrainItem;)Z", (void*)CMMyTrainList_Update },
        { "IsEnd", "()Z", (void*)CMMyTrainList_IsEnd },
        { "RequestMore", "()Z", (void*)CMMyTrainList_RequestMore },
        { "IsRunning", "()Z", (void*)CMMyTrainList_IsRunning },
        { "IsRefresh", "()Z", (void*)CMMyTrainList_IsRefresh },
        { "Cancel", "()V", (void*)CMMyTrainList_Cancel },
        { "SetRequestType", "(I)V", (void*)CMMyTrainList_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMMyTrainList_SetListener },
        { "RequestTrainApplyList", "()Z", (void*)CMMyTrainList_RequestTrainApplyList }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMMyTrainList");
    if (clazz == 0) {
        CM_ERR("class CMMyTrainList no found");
        return -1;
    }

    gCMMyTrainListFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMMyTrainListFieldID.nativeJavaObj == 0) {
        CM_ERR("CMMyTrainList no found mNativeObj");
        return -1;
    }

    gCMMyTrainListFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMMyTrainListFieldID.jniData == 0) {
        CM_ERR("CMMyTrainList no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMMyTrainListFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMMyTrainListFieldID.callback == NULL) {
        CM_ERR("CMMyTrainList no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMMyTrainListMethods,
            sizeof(CMMyTrainListMethods) / sizeof(CMMyTrainListMethods[0]));
}


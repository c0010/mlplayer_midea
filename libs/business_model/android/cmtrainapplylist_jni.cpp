// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmtrainapplylist_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmtrainapplylist.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_TTrainApplyItem {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gTTrainApplyItemFieldID;

static void TTrainApplyItem_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find TTrainApplyItem when setting up callback.");
        return;
    }
    callback_cookie_TTrainApplyItem* pCookie = new callback_cookie_TTrainApplyItem;
    pCookie->listener1 = new CMUpdateDataListener(gTTrainApplyItemFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gTTrainApplyItemFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gTTrainApplyItemFieldID.jniData, (int)pCookie);

    TTrainApplyItem* pObj = new TTrainApplyItem();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj, (int)pObj);
}

static void TTrainApplyItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem *pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_TTrainApplyItem* pCookie = (callback_cookie_TTrainApplyItem *)env->GetIntField(
        thiz, gTTrainApplyItemFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gTTrainApplyItemFieldID.jniData, 0);
}

static jboolean TTrainApplyItem_Update(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);

    BOOL ret = pObj->Update();
    return ret;
}

static jboolean TTrainApplyItem_Refresh(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);

    BOOL ret = pObj->Refresh();
    return ret;
}

static jboolean TTrainApplyItem_RequestInfo(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestInfo();
    return ret;
}

static jboolean TTrainApplyItem_Apply(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);

    BOOL ret = pObj->Apply();
    return ret;
}

static jboolean TTrainApplyItem_CancelApply(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);

    BOOL ret = pObj->CancelApply();
    return ret;
}

static void TTrainApplyItem_SetListener(JNIEnv* env, jobject thiz, jobject pUpdateDataListener, jobject pSimpleResultListener)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);

    callback_cookie_TTrainApplyItem* pCookie = (callback_cookie_TTrainApplyItem *)env->GetIntField(
        thiz, gTTrainApplyItemFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gTTrainApplyItemFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pUpdateDataListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gTTrainApplyItemFieldID.callback);
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

static void TTrainApplyItem_Cancel(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);

    pObj->Cancel();
}

static jobject TTrainApplyItem_CopyFromTTrainApplyItem(JNIEnv* env, jobject thiz, jobject right)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);

    extern fields_t gTTrainApplyItemFieldID;
    TTrainApplyItem* pObjCopy = (TTrainApplyItem*)env->GetIntField(right, gTTrainApplyItemFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static jstring TTrainApplyItem_GetID(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainApplyItem_GetTitle(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTitle.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTitle, NULL);
    jsize size = env->GetStringLength(sTitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTitle = data;

    env->ReleaseStringChars(sTitle, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainApplyItem_GetTrainID(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTrainID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTrainID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetTrainID(JNIEnv* env, jobject thiz, jstring sTrainID)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTrainID, NULL);
    jsize size = env->GetStringLength(sTrainID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTrainID = data;

    env->ReleaseStringChars(sTrainID, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainApplyItem_GetImageURL(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sImageURL.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sImageURL.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetImageURL(JNIEnv* env, jobject thiz, jstring sImageURL)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sImageURL, NULL);
    jsize size = env->GetStringLength(sImageURL);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sImageURL = data;

    env->ReleaseStringChars(sImageURL, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainApplyItem_GetTrainTime(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTrainTime.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTrainTime.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetTrainTime(JNIEnv* env, jobject thiz, jstring sTrainTime)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTrainTime, NULL);
    jsize size = env->GetStringLength(sTrainTime);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTrainTime = data;

    env->ReleaseStringChars(sTrainTime, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainApplyItem_GetApplyTime(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sApplyTime.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sApplyTime.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetApplyTime(JNIEnv* env, jobject thiz, jstring sApplyTime)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sApplyTime, NULL);
    jsize size = env->GetStringLength(sApplyTime);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sApplyTime = data;

    env->ReleaseStringChars(sApplyTime, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainApplyItem_GetAddress(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAddress.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAddress.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetAddress(JNIEnv* env, jobject thiz, jstring sAddress)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAddress, NULL);
    jsize size = env->GetStringLength(sAddress);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAddress = data;

    env->ReleaseStringChars(sAddress, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainApplyItem_GetFlag(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sFlag.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sFlag.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetFlag(JNIEnv* env, jobject thiz, jstring sFlag)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sFlag, NULL);
    jsize size = env->GetStringLength(sFlag);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sFlag = data;

    env->ReleaseStringChars(sFlag, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainApplyItem_GetDesc(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDesc.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sDesc.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetDesc(JNIEnv* env, jobject thiz, jstring sDesc)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDesc, NULL);
    jsize size = env->GetStringLength(sDesc);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sDesc = data;

    env->ReleaseStringChars(sDesc, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainApplyItem_GetAppliedTime(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAppliedTime.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAppliedTime.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetAppliedTime(JNIEnv* env, jobject thiz, jstring sAppliedTime)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAppliedTime, NULL);
    jsize size = env->GetStringLength(sAppliedTime);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAppliedTime = data;

    env->ReleaseStringChars(sAppliedTime, jChar);
    
    free(data);
    
    return true;
}

static jstring TTrainApplyItem_GetPlanPerson(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPlanPerson.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPlanPerson.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TTrainApplyItem_SetPlanPerson(JNIEnv* env, jobject thiz, jstring sPlanPerson)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPlanPerson, NULL);
    jsize size = env->GetStringLength(sPlanPerson);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPlanPerson = data;

    env->ReleaseStringChars(sPlanPerson, jChar);
    
    free(data);
    
    return true;
}

static jint TTrainApplyItem_GetEnableApply(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nEnableApply;
}
                
static jboolean TTrainApplyItem_SetEnableApply(JNIEnv* env, jobject thiz, jint nEnableApply)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nEnableApply = nEnableApply;
    return true;
}
                
static jint TTrainApplyItem_GetEnableCancelApply(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nEnableCancelApply;
}
                
static jboolean TTrainApplyItem_SetEnableCancelApply(JNIEnv* env, jobject thiz, jint nEnableCancelApply)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nEnableCancelApply = nEnableCancelApply;
    return true;
}
                
static jint TTrainApplyItem_GetIsPass(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nIsPass;
}
                
static jboolean TTrainApplyItem_SetIsPass(JNIEnv* env, jobject thiz, jint nIsPass)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nIsPass = nIsPass;
    return true;
}
                
static jint TTrainApplyItem_GetAppliedNum(JNIEnv* env, jobject thiz)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nAppliedNum;
}
                
static jboolean TTrainApplyItem_SetAppliedNum(JNIEnv* env, jobject thiz, jint nAppliedNum)
{
    TTrainApplyItem* pObj = (TTrainApplyItem*)env->GetIntField(thiz, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nAppliedNum = nAppliedNum;
    return true;
}
                
int register_com_wunding_mlplayer_business_TTrainApplyItem(JNIEnv* env) {
    static JNINativeMethod TTrainApplyItemMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)TTrainApplyItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TTrainApplyItem_nativeDestructor },
        { "Update", "()Z", (void*)TTrainApplyItem_Update },
        { "Refresh", "()Z", (void*)TTrainApplyItem_Refresh },
        { "RequestInfo", "()Z", (void*)TTrainApplyItem_RequestInfo },
        { "Apply", "()Z", (void*)TTrainApplyItem_Apply },
        { "CancelApply", "()Z", (void*)TTrainApplyItem_CancelApply },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)TTrainApplyItem_SetListener },
        { "Cancel", "()V", (void*)TTrainApplyItem_Cancel },
        { "CopyFromTTrainApplyItem", "(Lcom/wunding/mlplayer/business/TTrainApplyItem;)Lcom/wunding/mlplayer/business/TTrainApplyItem;", (void*)TTrainApplyItem_CopyFromTTrainApplyItem },
        { "GetID", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetID },
        { "GetTitle", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetTitle },
        { "GetTrainID", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetTrainID },
        { "SetTrainID", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetTrainID },
        { "GetImageURL", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetImageURL },
        { "SetImageURL", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetImageURL },
        { "GetTrainTime", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetTrainTime },
        { "SetTrainTime", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetTrainTime },
        { "GetApplyTime", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetApplyTime },
        { "SetApplyTime", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetApplyTime },
        { "GetAddress", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetAddress },
        { "SetAddress", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetAddress },
        { "GetFlag", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetFlag },
        { "SetFlag", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetFlag },
        { "GetDesc", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetDesc },
        { "SetDesc", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetDesc },
        { "GetAppliedTime", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetAppliedTime },
        { "SetAppliedTime", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetAppliedTime },
        { "GetPlanPerson", "()Ljava/lang/String;", (void*)TTrainApplyItem_GetPlanPerson },
        { "SetPlanPerson", "(Ljava/lang/String;)Z", (void*)TTrainApplyItem_SetPlanPerson },
        { "GetEnableApply", "()I", (void*)TTrainApplyItem_GetEnableApply },
        { "SetEnableApply", "(I)Z", (void*)TTrainApplyItem_SetEnableApply },
        { "GetEnableCancelApply", "()I", (void*)TTrainApplyItem_GetEnableCancelApply },
        { "SetEnableCancelApply", "(I)Z", (void*)TTrainApplyItem_SetEnableCancelApply },
        { "GetIsPass", "()I", (void*)TTrainApplyItem_GetIsPass },
        { "SetIsPass", "(I)Z", (void*)TTrainApplyItem_SetIsPass },
        { "GetAppliedNum", "()I", (void*)TTrainApplyItem_GetAppliedNum },
        { "SetAppliedNum", "(I)Z", (void*)TTrainApplyItem_SetAppliedNum }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TTrainApplyItem");
    if (clazz == 0) {
        CM_ERR("class TTrainApplyItem no found");
        return -1;
    }

    gTTrainApplyItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTTrainApplyItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TTrainApplyItem no found mNativeObj");
        return -1;
    }

    gTTrainApplyItemFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gTTrainApplyItemFieldID.jniData == 0) {
        CM_ERR("TTrainApplyItem no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gTTrainApplyItemFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gTTrainApplyItemFieldID.callback == NULL) {
        CM_ERR("TTrainApplyItem no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TTrainApplyItemMethods,
            sizeof(TTrainApplyItemMethods) / sizeof(TTrainApplyItemMethods[0]));
}


struct callback_cookie_CMTrainApplyList {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMTrainApplyListFieldID;

static void CMTrainApplyList_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMTrainApplyList when setting up callback.");
        return;
    }
    callback_cookie_CMTrainApplyList* pCookie = new callback_cookie_CMTrainApplyList;
    pCookie->listener1 = new CMUpdateDataListener(gCMTrainApplyListFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMTrainApplyListFieldID.jniData, (int)pCookie);

    CMTrainApplyList* pObj = new CMTrainApplyList();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj, (int)pObj);
}

static void CMTrainApplyList_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMTrainApplyList *pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMTrainApplyList* pCookie = (callback_cookie_CMTrainApplyList *)env->GetIntField(
        thiz, gCMTrainApplyListFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMTrainApplyListFieldID.jniData, 0);
}

static jint CMTrainApplyList_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMTrainApplyList_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    extern fields_t gTTrainApplyItemFieldID;
    TTrainApplyItem* pItem = (TTrainApplyItem*)env->GetIntField(item, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMTrainApplyList_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    extern fields_t gTTrainApplyItemFieldID;
    TTrainApplyItem* pItem = (TTrainApplyItem*)env->GetIntField(obj, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMTrainApplyList_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    extern fields_t gTTrainApplyItemFieldID;
    TTrainApplyItem* pItem = (TTrainApplyItem*)env->GetIntField(obj, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMTrainApplyList_IsEnd(JNIEnv* env, jobject thiz)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMTrainApplyList_RequestMore(JNIEnv* env, jobject thiz)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMTrainApplyList_IsRunning(JNIEnv* env, jobject thiz)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMTrainApplyList_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMTrainApplyList_Cancel(JNIEnv* env, jobject thiz)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMTrainApplyList_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMTrainApplyList_SetListener(JNIEnv* env, jobject thiz, jobject m_pListener)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    callback_cookie_CMTrainApplyList* pCookie = (callback_cookie_CMTrainApplyList *)env->GetIntField(
        thiz, gCMTrainApplyListFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMTrainApplyListFieldID.callback);
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

static jboolean CMTrainApplyList_RequestTrainApplyList(JNIEnv* env, jobject thiz, jstring mFlag)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    const jchar* jmFlag = env->GetStringChars(mFlag, NULL);
    jsize sizemFlag = env->GetStringLength(mFlag);
    char* pmFlag = UTF16toUTF8((jchar*)jmFlag, (size_t*)&sizemFlag);
    BOOL ret = pObj->RequestTrainApplyList(pmFlag);
    env->ReleaseStringChars(mFlag, jmFlag);
    free(pmFlag);
    return ret;
}

static jboolean CMTrainApplyList_RemoveSuccessItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMTrainApplyList* pObj = (CMTrainApplyList*)env->GetIntField(thiz, gCMTrainApplyListFieldID.nativeJavaObj);

    BOOL ret = pObj->RemoveSuccessItem(nIndex);
    return ret;
}

int register_com_wunding_mlplayer_business_CMTrainApplyList(JNIEnv* env) {
    static JNINativeMethod CMTrainApplyListMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMTrainApplyList_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMTrainApplyList_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMTrainApplyList_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TTrainApplyItem;)Z", (void*)CMTrainApplyList_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TTrainApplyItem;)Z", (void*)CMTrainApplyList_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TTrainApplyItem;)Z", (void*)CMTrainApplyList_Update },
        { "IsEnd", "()Z", (void*)CMTrainApplyList_IsEnd },
        { "RequestMore", "()Z", (void*)CMTrainApplyList_RequestMore },
        { "IsRunning", "()Z", (void*)CMTrainApplyList_IsRunning },
        { "IsRefresh", "()Z", (void*)CMTrainApplyList_IsRefresh },
        { "Cancel", "()V", (void*)CMTrainApplyList_Cancel },
        { "SetRequestType", "(I)V", (void*)CMTrainApplyList_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMTrainApplyList_SetListener },
        { "RequestTrainApplyList", "(Ljava/lang/String;)Z", (void*)CMTrainApplyList_RequestTrainApplyList },
        { "RemoveSuccessItem", "(I)Z", (void*)CMTrainApplyList_RemoveSuccessItem }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMTrainApplyList");
    if (clazz == 0) {
        CM_ERR("class CMTrainApplyList no found");
        return -1;
    }

    gCMTrainApplyListFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMTrainApplyListFieldID.nativeJavaObj == 0) {
        CM_ERR("CMTrainApplyList no found mNativeObj");
        return -1;
    }

    gCMTrainApplyListFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMTrainApplyListFieldID.jniData == 0) {
        CM_ERR("CMTrainApplyList no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMTrainApplyListFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMTrainApplyListFieldID.callback == NULL) {
        CM_ERR("CMTrainApplyList no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMTrainApplyListMethods,
            sizeof(CMTrainApplyListMethods) / sizeof(CMTrainApplyListMethods[0]));
}


// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmqacategory_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmqacategory.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMQACategory {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMQACategoryFieldID;

static void CMQACategory_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMQACategory when setting up callback.");
        return;
    }
    callback_cookie_CMQACategory* pCookie = new callback_cookie_CMQACategory;
    pCookie->listener1 = new CMUpdateDataListener(gCMQACategoryFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMQACategoryFieldID.jniData, (int)pCookie);

    CMQACategory* pObj = CMQACategory::GetInstance();
    pObj->SetListener(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj, (int)pObj);
}

static void CMQACategory_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMQACategory *pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMQACategory* pCookie = (callback_cookie_CMQACategory *)env->GetIntField(
        thiz, gCMQACategoryFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMQACategoryFieldID.jniData, 0);
}

static jint CMQACategory_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMQACategory_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    extern fields_t gCMQACategoryItemFieldID;
    CMQACategoryItem* pItem = NULL;
    jboolean ret = pObj->GetItem(nIndex, pItem);

    env->SetIntField(item, gCMQACategoryItemFieldID.nativeJavaObj, (int)pItem);

    return ret;
}

static jboolean CMQACategory_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    extern fields_t gCMQACategoryItemFieldID;
    CMQACategoryItem* pItem = (CMQACategoryItem*)env->GetIntField(obj, gCMQACategoryItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQACategory_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    extern fields_t gCMQACategoryItemFieldID;
    CMQACategoryItem* pItem = (CMQACategoryItem*)env->GetIntField(obj, gCMQACategoryItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQACategory_IsEnd(JNIEnv* env, jobject thiz)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMQACategory_RequestMore(JNIEnv* env, jobject thiz)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMQACategory_IsRunning(JNIEnv* env, jobject thiz)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMQACategory_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMQACategory_Cancel(JNIEnv* env, jobject thiz)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMQACategory_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMQACategory_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    callback_cookie_CMQACategory* pCookie = (callback_cookie_CMQACategory *)env->GetIntField(
        thiz, gCMQACategoryFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMQACategoryFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

    }
}

static jboolean CMQACategory_UpdateData(JNIEnv* env, jobject thiz)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->UpdateData();
    return ret;
}

static void CMQACategory_CancelUpdate(JNIEnv* env, jobject thiz)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    pObj->CancelUpdate();
}

static jint CMQACategory_TopItemCount(JNIEnv* env, jobject thiz)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    int ret = pObj->TopItemCount();
    return ret;
}

static jobject CMQACategory_GetTopItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    CMQACategoryItem* pRet = pObj->GetTopItem(nIndex);
    if (pRet == NULL) return NULL;

    jclass retClazz = env->FindClass("com/wunding/mlplayer/business/CMQACategoryItem");
    if (retClazz == NULL) {
        CM_ERR("Can't find class CMQACategoryItem");
        return NULL;
    }

    jmethodID retConstructor = env->GetMethodID(retClazz, "<init>", "(I)V");
    if (retConstructor == NULL) {
        CM_ERR("Can't find class CMQACategoryItem native constructor");
        return NULL;
    }

    return env->NewObject(retClazz,
            retConstructor, (int)pRet);
}

static void CMQACategory_ClearTree(JNIEnv* env, jobject thiz)
{
    CMQACategory* pObj = (CMQACategory*)env->GetIntField(thiz, gCMQACategoryFieldID.nativeJavaObj);

    pObj->ClearTree();
}

int register_com_wunding_mlplayer_business_CMQACategory(JNIEnv* env) {
    static JNINativeMethod CMQACategoryMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMQACategory_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMQACategory_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMQACategory_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/CMQACategoryItem;)Z", (void*)CMQACategory_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/CMQACategoryItem;)Z", (void*)CMQACategory_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/CMQACategoryItem;)Z", (void*)CMQACategory_Update },
        { "IsEnd", "()Z", (void*)CMQACategory_IsEnd },
        { "RequestMore", "()Z", (void*)CMQACategory_RequestMore },
        { "IsRunning", "()Z", (void*)CMQACategory_IsRunning },
        { "IsRefresh", "()Z", (void*)CMQACategory_IsRefresh },
        { "Cancel", "()V", (void*)CMQACategory_Cancel },
        { "SetRequestType", "(I)V", (void*)CMQACategory_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMQACategory_SetListener },
        { "UpdateData", "()Z", (void*)CMQACategory_UpdateData },
        { "CancelUpdate", "()V", (void*)CMQACategory_CancelUpdate },
        { "TopItemCount", "()I", (void*)CMQACategory_TopItemCount },
        { "GetTopItem", "(I)Lcom/wunding/mlplayer/business/CMQACategoryItem;", (void*)CMQACategory_GetTopItem },
        { "ClearTree", "()V", (void*)CMQACategory_ClearTree }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMQACategory");
    if (clazz == 0) {
        CM_ERR("class CMQACategory no found");
        return -1;
    }

    gCMQACategoryFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMQACategoryFieldID.nativeJavaObj == 0) {
        CM_ERR("CMQACategory no found mNativeObj");
        return -1;
    }

    gCMQACategoryFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMQACategoryFieldID.jniData == 0) {
        CM_ERR("CMQACategory no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMQACategoryFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMQACategoryFieldID.callback == NULL) {
        CM_ERR("CMQACategory no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMQACategoryMethods,
            sizeof(CMQACategoryMethods) / sizeof(CMQACategoryMethods[0]));
}

fields_t gCMQACategoryItemFieldID;

static void CMQACategoryItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
}

static void CMQACategoryItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    env->SetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj, 0);
}

static jint CMQACategoryItem_ChildItemCount(JNIEnv* env, jobject thiz)
{
    CMQACategoryItem* pObj = (CMQACategoryItem*)env->GetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj);

    int ret = pObj->ChildItemCount();
    return ret;
}

static jobject CMQACategoryItem_GetChildItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMQACategoryItem* pObj = (CMQACategoryItem*)env->GetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj);

    CMQACategoryItem* pRet = pObj->GetChildItem(nIndex);
    if (pRet == NULL) return NULL;

    jclass retClazz = env->FindClass("com/wunding/mlplayer/business/CMQACategoryItem");
    if (retClazz == NULL) {
        CM_ERR("Can't find class CMQACategoryItem");
        return NULL;
    }

    jmethodID retConstructor = env->GetMethodID(retClazz, "<init>", "(I)V");
    if (retConstructor == NULL) {
        CM_ERR("Can't find class CMQACategoryItem native constructor");
        return NULL;
    }

    return env->NewObject(retClazz,
            retConstructor, (int)pRet);
}

static jstring CMQACategoryItem_GetID(JNIEnv* env, jobject thiz)
{
    CMQACategoryItem* pObj = (CMQACategoryItem*)env->GetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID);
    jchar* data = UTF8toUTF16((char*)pObj->sID, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMQACategoryItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    CMQACategoryItem* pObj = (CMQACategoryItem*)env->GetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sID, (const char*)data, 63);
    pObj->sID[63] = '\0';

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring CMQACategoryItem_GetFlag(JNIEnv* env, jobject thiz)
{
    CMQACategoryItem* pObj = (CMQACategoryItem*)env->GetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sFlag);
    jchar* data = UTF8toUTF16((char*)pObj->sFlag, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMQACategoryItem_SetFlag(JNIEnv* env, jobject thiz, jstring sFlag)
{
    CMQACategoryItem* pObj = (CMQACategoryItem*)env->GetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sFlag, NULL);
    jsize size = env->GetStringLength(sFlag);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sFlag, (const char*)data, 19);
    pObj->sFlag[19] = '\0';

    env->ReleaseStringChars(sFlag, jChar);
    
    free(data);
    
    return true;
}

static jstring CMQACategoryItem_GetCategoryTitle(JNIEnv* env, jobject thiz)
{
    CMQACategoryItem* pObj = (CMQACategoryItem*)env->GetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sCategoryTitle);
    jchar* data = UTF8toUTF16((char*)pObj->sCategoryTitle, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMQACategoryItem_SetCategoryTitle(JNIEnv* env, jobject thiz, jstring sCategoryTitle)
{
    CMQACategoryItem* pObj = (CMQACategoryItem*)env->GetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sCategoryTitle, NULL);
    jsize size = env->GetStringLength(sCategoryTitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sCategoryTitle, (const char*)data, 99);
    pObj->sCategoryTitle[99] = '\0';

    env->ReleaseStringChars(sCategoryTitle, jChar);
    
    free(data);
    
    return true;
}

static jint CMQACategoryItem_GetQuestioncount(JNIEnv* env, jobject thiz)
{
    CMQACategoryItem* pObj = (CMQACategoryItem*)env->GetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nQuestioncount;
}
                
static jboolean CMQACategoryItem_SetQuestioncount(JNIEnv* env, jobject thiz, jint nQuestioncount)
{
    CMQACategoryItem* pObj = (CMQACategoryItem*)env->GetIntField(thiz, gCMQACategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nQuestioncount = nQuestioncount;
    return true;
}
                
int register_com_wunding_mlplayer_business_CMQACategoryItem(JNIEnv* env) {
    static JNINativeMethod CMQACategoryItemMethods[] = {
        { "nativeConstructor", "()V", (void*)CMQACategoryItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMQACategoryItem_nativeDestructor },
        { "ChildItemCount", "()I", (void*)CMQACategoryItem_ChildItemCount },
        { "GetChildItem", "(I)Lcom/wunding/mlplayer/business/CMQACategoryItem;", (void*)CMQACategoryItem_GetChildItem },
        { "GetID", "()Ljava/lang/String;", (void*)CMQACategoryItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)CMQACategoryItem_SetID },
        { "GetFlag", "()Ljava/lang/String;", (void*)CMQACategoryItem_GetFlag },
        { "SetFlag", "(Ljava/lang/String;)Z", (void*)CMQACategoryItem_SetFlag },
        { "GetCategoryTitle", "()Ljava/lang/String;", (void*)CMQACategoryItem_GetCategoryTitle },
        { "SetCategoryTitle", "(Ljava/lang/String;)Z", (void*)CMQACategoryItem_SetCategoryTitle },
        { "GetQuestioncount", "()I", (void*)CMQACategoryItem_GetQuestioncount },
        { "SetQuestioncount", "(I)Z", (void*)CMQACategoryItem_SetQuestioncount }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMQACategoryItem");
    if (clazz == 0) {
        CM_ERR("class CMQACategoryItem no found");
        return -1;
    }

    gCMQACategoryItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMQACategoryItemFieldID.nativeJavaObj == 0) {
        CM_ERR("CMQACategoryItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMQACategoryItemMethods,
            sizeof(CMQACategoryItemMethods) / sizeof(CMQACategoryItemMethods[0]));
}


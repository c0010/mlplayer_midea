// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmpushmsg_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmpushmsg.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTPushItemFieldID;

static void TPushItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TPushItem* pObj = new TPushItem();

    env->SetIntField(thiz, gTPushItemFieldID.nativeJavaObj, (int)pObj);
}

static void TPushItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
}

static jstring TPushItem_GetID(JNIEnv* env, jobject thiz)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TPushItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TPushItem_GetMsg(JNIEnv* env, jobject thiz)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sMsg.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sMsg.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TPushItem_SetMsg(JNIEnv* env, jobject thiz, jstring sMsg)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sMsg, NULL);
    jsize size = env->GetStringLength(sMsg);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sMsg = data;

    env->ReleaseStringChars(sMsg, jChar);
    
    free(data);
    
    return true;
}

static jstring TPushItem_GetType(JNIEnv* env, jobject thiz)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sType.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sType.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TPushItem_SetType(JNIEnv* env, jobject thiz, jstring sType)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sType, NULL);
    jsize size = env->GetStringLength(sType);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sType = data;

    env->ReleaseStringChars(sType, jChar);
    
    free(data);
    
    return true;
}

static jstring TPushItem_GetKey(JNIEnv* env, jobject thiz)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sKey.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sKey.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TPushItem_SetKey(JNIEnv* env, jobject thiz, jstring sKey)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sKey, NULL);
    jsize size = env->GetStringLength(sKey);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sKey = data;

    env->ReleaseStringChars(sKey, jChar);
    
    free(data);
    
    return true;
}

static jstring TPushItem_GetPubDate(JNIEnv* env, jobject thiz)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPubDate.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPubDate.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TPushItem_SetPubDate(JNIEnv* env, jobject thiz, jstring sPubDate)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPubDate, NULL);
    jsize size = env->GetStringLength(sPubDate);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPubDate = data;

    env->ReleaseStringChars(sPubDate, jChar);
    
    free(data);
    
    return true;
}

static jboolean TPushItem_GetIsRead(JNIEnv* env, jobject thiz)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bIsRead;
}
                
static jboolean TPushItem_SetIsRead(JNIEnv* env, jobject thiz, jboolean bIsRead)
{
    TPushItem* pObj = (TPushItem*)env->GetIntField(thiz, gTPushItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bIsRead = bIsRead;
    return true;
}
                
int register_com_wunding_mlplayer_business_TPushItem(JNIEnv* env) {
    static JNINativeMethod TPushItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TPushItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TPushItem_nativeDestructor },
        { "GetID", "()Ljava/lang/String;", (void*)TPushItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TPushItem_SetID },
        { "GetMsg", "()Ljava/lang/String;", (void*)TPushItem_GetMsg },
        { "SetMsg", "(Ljava/lang/String;)Z", (void*)TPushItem_SetMsg },
        { "GetType", "()Ljava/lang/String;", (void*)TPushItem_GetType },
        { "SetType", "(Ljava/lang/String;)Z", (void*)TPushItem_SetType },
        { "GetKey", "()Ljava/lang/String;", (void*)TPushItem_GetKey },
        { "SetKey", "(Ljava/lang/String;)Z", (void*)TPushItem_SetKey },
        { "GetPubDate", "()Ljava/lang/String;", (void*)TPushItem_GetPubDate },
        { "SetPubDate", "(Ljava/lang/String;)Z", (void*)TPushItem_SetPubDate },
        { "GetIsRead", "()Z", (void*)TPushItem_GetIsRead },
        { "SetIsRead", "(Z)Z", (void*)TPushItem_SetIsRead }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TPushItem");
    if (clazz == 0) {
        CM_ERR("class TPushItem no found");
        return -1;
    }

    gTPushItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTPushItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TPushItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TPushItemMethods,
            sizeof(TPushItemMethods) / sizeof(TPushItemMethods[0]));
}


struct callback_cookie_CMPushMsg {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMPushMsgFieldID;

static void CMPushMsg_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMPushMsg when setting up callback.");
        return;
    }
    callback_cookie_CMPushMsg* pCookie = new callback_cookie_CMPushMsg;
    pCookie->listener1 = new CMUpdateDataListener(gCMPushMsgFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMPushMsgFieldID.jniData, (int)pCookie);

    CMPushMsg* pObj = CMPushMsg::GetInstance();
    pObj->SetListener(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj, (int)pObj);
}

static void CMPushMsg_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMPushMsg *pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMPushMsg* pCookie = (callback_cookie_CMPushMsg *)env->GetIntField(
        thiz, gCMPushMsgFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMPushMsgFieldID.jniData, 0);
}

static jint CMPushMsg_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMPushMsg_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    extern fields_t gTPushItemFieldID;
    TPushItem* pItem = (TPushItem*)env->GetIntField(item, gTPushItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMPushMsg_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    extern fields_t gTPushItemFieldID;
    TPushItem* pItem = (TPushItem*)env->GetIntField(obj, gTPushItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMPushMsg_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    extern fields_t gTPushItemFieldID;
    TPushItem* pItem = (TPushItem*)env->GetIntField(obj, gTPushItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMPushMsg_IsEnd(JNIEnv* env, jobject thiz)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMPushMsg_RequestMore(JNIEnv* env, jobject thiz)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMPushMsg_IsRunning(JNIEnv* env, jobject thiz)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMPushMsg_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMPushMsg_Cancel(JNIEnv* env, jobject thiz)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMPushMsg_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMPushMsg_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    callback_cookie_CMPushMsg* pCookie = (callback_cookie_CMPushMsg *)env->GetIntField(
        thiz, gCMPushMsgFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMPushMsgFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

    }
}

static jboolean CMPushMsg_AddPushMsg(JNIEnv* env, jobject thiz, jobject item)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    extern fields_t gTPushItemFieldID;
    TPushItem* pItem = (TPushItem*)env->GetIntField(item, gTPushItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->AddPushMsg(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMPushMsg_LoadFromDB(JNIEnv* env, jobject thiz)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    BOOL ret = pObj->LoadFromDB();
    return ret;
}

static jboolean CMPushMsg_Clear(JNIEnv* env, jobject thiz)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    BOOL ret = pObj->Clear();
    return ret;
}

static jboolean CMPushMsg_ClearCache(JNIEnv* env, jobject thiz)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    BOOL ret = pObj->ClearCache();
    return ret;
}

static jboolean CMPushMsg_RemoveItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    BOOL ret = pObj->RemoveItem(nIndex);
    return ret;
}

static jint CMPushMsg_GetUnReadCount(JNIEnv* env, jobject thiz)
{
    CMPushMsg* pObj = (CMPushMsg*)env->GetIntField(thiz, gCMPushMsgFieldID.nativeJavaObj);

    int ret = pObj->GetUnReadCount();
    return ret;
}

int register_com_wunding_mlplayer_business_CMPushMsg(JNIEnv* env) {
    static JNINativeMethod CMPushMsgMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMPushMsg_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMPushMsg_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMPushMsg_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TPushItem;)Z", (void*)CMPushMsg_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TPushItem;)Z", (void*)CMPushMsg_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TPushItem;)Z", (void*)CMPushMsg_Update },
        { "IsEnd", "()Z", (void*)CMPushMsg_IsEnd },
        { "RequestMore", "()Z", (void*)CMPushMsg_RequestMore },
        { "IsRunning", "()Z", (void*)CMPushMsg_IsRunning },
        { "IsRefresh", "()Z", (void*)CMPushMsg_IsRefresh },
        { "Cancel", "()V", (void*)CMPushMsg_Cancel },
        { "SetRequestType", "(I)V", (void*)CMPushMsg_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMPushMsg_SetListener },
        { "AddPushMsg", "(Lcom/wunding/mlplayer/business/TPushItem;)Z", (void*)CMPushMsg_AddPushMsg },
        { "LoadFromDB", "()Z", (void*)CMPushMsg_LoadFromDB },
        { "Clear", "()Z", (void*)CMPushMsg_Clear },
        { "ClearCache", "()Z", (void*)CMPushMsg_ClearCache },
        { "RemoveItem", "(I)Z", (void*)CMPushMsg_RemoveItem },
        { "GetUnReadCount", "()I", (void*)CMPushMsg_GetUnReadCount }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMPushMsg");
    if (clazz == 0) {
        CM_ERR("class CMPushMsg no found");
        return -1;
    }

    gCMPushMsgFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMPushMsgFieldID.nativeJavaObj == 0) {
        CM_ERR("CMPushMsg no found mNativeObj");
        return -1;
    }

    gCMPushMsgFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMPushMsgFieldID.jniData == 0) {
        CM_ERR("CMPushMsg no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMPushMsgFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMPushMsgFieldID.callback == NULL) {
        CM_ERR("CMPushMsg no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMPushMsgMethods,
            sizeof(CMPushMsgMethods) / sizeof(CMPushMsgMethods[0]));
}


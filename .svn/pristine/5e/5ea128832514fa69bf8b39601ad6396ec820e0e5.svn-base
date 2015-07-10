// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmsurveylist_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmsurveylist.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTSurveyListItemFieldID;

static void TSurveyListItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TSurveyListItem* pObj = new TSurveyListItem();

    env->SetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj, (int)pObj);
}

static void TSurveyListItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
}

static jstring TSurveyListItem_GetID(JNIEnv* env, jobject thiz)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID);
    jchar* data = UTF8toUTF16((char*)pObj->sID, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSurveyListItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sID, (const char*)data, 99);
    pObj->sID[99] = '\0';

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TSurveyListItem_GetTitle(JNIEnv* env, jobject thiz)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle);
    jchar* data = UTF8toUTF16((char*)pObj->sTitle, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSurveyListItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTitle, NULL);
    jsize size = env->GetStringLength(sTitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sTitle, (const char*)data, 99);
    pObj->sTitle[99] = '\0';

    env->ReleaseStringChars(sTitle, jChar);
    
    free(data);
    
    return true;
}

static jint TSurveyListItem_GetInvitecount(JNIEnv* env, jobject thiz)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nInvitecount;
}
                
static jboolean TSurveyListItem_SetInvitecount(JNIEnv* env, jobject thiz, jint nInvitecount)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nInvitecount = nInvitecount;
    return true;
}
                
static jint TSurveyListItem_GetCompletecount(JNIEnv* env, jobject thiz)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nCompletecount;
}
                
static jboolean TSurveyListItem_SetCompletecount(JNIEnv* env, jobject thiz, jint nCompletecount)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nCompletecount = nCompletecount;
    return true;
}
                
static jstring TSurveyListItem_GetDesc(JNIEnv* env, jobject thiz)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDesc);
    jchar* data = UTF8toUTF16((char*)pObj->sDesc, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSurveyListItem_SetDesc(JNIEnv* env, jobject thiz, jstring sDesc)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDesc, NULL);
    jsize size = env->GetStringLength(sDesc);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sDesc, (const char*)data, 599);
    pObj->sDesc[599] = '\0';

    env->ReleaseStringChars(sDesc, jChar);
    
    free(data);
    
    return true;
}

static jstring TSurveyListItem_GetExpiredate(JNIEnv* env, jobject thiz)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sExpiredate);
    jchar* data = UTF8toUTF16((char*)pObj->sExpiredate, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSurveyListItem_SetExpiredate(JNIEnv* env, jobject thiz, jstring sExpiredate)
{
    TSurveyListItem* pObj = (TSurveyListItem*)env->GetIntField(thiz, gTSurveyListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sExpiredate, NULL);
    jsize size = env->GetStringLength(sExpiredate);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sExpiredate, (const char*)data, 99);
    pObj->sExpiredate[99] = '\0';

    env->ReleaseStringChars(sExpiredate, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TSurveyListItem(JNIEnv* env) {
    static JNINativeMethod TSurveyListItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TSurveyListItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TSurveyListItem_nativeDestructor },
        { "GetID", "()Ljava/lang/String;", (void*)TSurveyListItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TSurveyListItem_SetID },
        { "GetTitle", "()Ljava/lang/String;", (void*)TSurveyListItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)TSurveyListItem_SetTitle },
        { "GetInvitecount", "()I", (void*)TSurveyListItem_GetInvitecount },
        { "SetInvitecount", "(I)Z", (void*)TSurveyListItem_SetInvitecount },
        { "GetCompletecount", "()I", (void*)TSurveyListItem_GetCompletecount },
        { "SetCompletecount", "(I)Z", (void*)TSurveyListItem_SetCompletecount },
        { "GetDesc", "()Ljava/lang/String;", (void*)TSurveyListItem_GetDesc },
        { "SetDesc", "(Ljava/lang/String;)Z", (void*)TSurveyListItem_SetDesc },
        { "GetExpiredate", "()Ljava/lang/String;", (void*)TSurveyListItem_GetExpiredate },
        { "SetExpiredate", "(Ljava/lang/String;)Z", (void*)TSurveyListItem_SetExpiredate }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TSurveyListItem");
    if (clazz == 0) {
        CM_ERR("class TSurveyListItem no found");
        return -1;
    }

    gTSurveyListItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTSurveyListItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TSurveyListItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TSurveyListItemMethods,
            sizeof(TSurveyListItemMethods) / sizeof(TSurveyListItemMethods[0]));
}


struct callback_cookie_CMSurveyList {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMSurveyListFieldID;

static void CMSurveyList_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMSurveyList when setting up callback.");
        return;
    }
    callback_cookie_CMSurveyList* pCookie = new callback_cookie_CMSurveyList;
    pCookie->listener1 = new CMUpdateDataListener(gCMSurveyListFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMSurveyListFieldID.jniData, (int)pCookie);

    CMSurveyList* pObj = new CMSurveyList(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj, (int)pObj);
}

static void CMSurveyList_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMSurveyList *pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMSurveyList* pCookie = (callback_cookie_CMSurveyList *)env->GetIntField(
        thiz, gCMSurveyListFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMSurveyListFieldID.jniData, 0);
}

static jint CMSurveyList_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMSurveyList_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    extern fields_t gTSurveyListItemFieldID;
    TSurveyListItem* pItem = (TSurveyListItem*)env->GetIntField(item, gTSurveyListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMSurveyList_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    extern fields_t gTSurveyListItemFieldID;
    TSurveyListItem* pItem = (TSurveyListItem*)env->GetIntField(obj, gTSurveyListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMSurveyList_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    extern fields_t gTSurveyListItemFieldID;
    TSurveyListItem* pItem = (TSurveyListItem*)env->GetIntField(obj, gTSurveyListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMSurveyList_IsEnd(JNIEnv* env, jobject thiz)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMSurveyList_RequestMore(JNIEnv* env, jobject thiz)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMSurveyList_IsRunning(JNIEnv* env, jobject thiz)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMSurveyList_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMSurveyList_Cancel(JNIEnv* env, jobject thiz)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMSurveyList_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static jboolean CMSurveyList_GetList(JNIEnv* env, jobject thiz)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    BOOL ret = pObj->GetList();
    return ret;
}

static jboolean CMSurveyList_GetTrainSurveyList(JNIEnv* env, jobject thiz, jstring trainid)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    const jchar* jtrainid = env->GetStringChars(trainid, NULL);
    jsize sizetrainid = env->GetStringLength(trainid);
    char* ptrainid = UTF16toUTF8((jchar*)jtrainid, (size_t*)&sizetrainid);
    BOOL ret = pObj->GetTrainSurveyList(ptrainid);
    env->ReleaseStringChars(trainid, jtrainid);
    free(ptrainid);
    return ret;
}

static jboolean CMSurveyList_GetSurveyById(JNIEnv* env, jobject thiz, jstring surveyId)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    const jchar* jsurveyId = env->GetStringChars(surveyId, NULL);
    jsize sizesurveyId = env->GetStringLength(surveyId);
    char* psurveyId = UTF16toUTF8((jchar*)jsurveyId, (size_t*)&sizesurveyId);
    BOOL ret = pObj->GetSurveyById(psurveyId);
    env->ReleaseStringChars(surveyId, jsurveyId);
    free(psurveyId);
    return ret;
}

static jboolean CMSurveyList_RemoveItem(JNIEnv* env, jobject thiz, jint index)
{
    CMSurveyList* pObj = (CMSurveyList*)env->GetIntField(thiz, gCMSurveyListFieldID.nativeJavaObj);

    BOOL ret = pObj->RemoveItem(index);
    return ret;
}

int register_com_wunding_mlplayer_business_CMSurveyList(JNIEnv* env) {
    static JNINativeMethod CMSurveyListMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMSurveyList_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMSurveyList_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMSurveyList_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TSurveyListItem;)Z", (void*)CMSurveyList_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TSurveyListItem;)Z", (void*)CMSurveyList_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TSurveyListItem;)Z", (void*)CMSurveyList_Update },
        { "IsEnd", "()Z", (void*)CMSurveyList_IsEnd },
        { "RequestMore", "()Z", (void*)CMSurveyList_RequestMore },
        { "IsRunning", "()Z", (void*)CMSurveyList_IsRunning },
        { "IsRefresh", "()Z", (void*)CMSurveyList_IsRefresh },
        { "Cancel", "()V", (void*)CMSurveyList_Cancel },
        { "SetRequestType", "(I)V", (void*)CMSurveyList_SetRequestType },
        { "GetList", "()Z", (void*)CMSurveyList_GetList },
        { "GetTrainSurveyList", "(Ljava/lang/String;)Z", (void*)CMSurveyList_GetTrainSurveyList },
        { "GetSurveyById", "(Ljava/lang/String;)Z", (void*)CMSurveyList_GetSurveyById },
        { "RemoveItem", "(I)Z", (void*)CMSurveyList_RemoveItem }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMSurveyList");
    if (clazz == 0) {
        CM_ERR("class CMSurveyList no found");
        return -1;
    }

    gCMSurveyListFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMSurveyListFieldID.nativeJavaObj == 0) {
        CM_ERR("CMSurveyList no found mNativeObj");
        return -1;
    }

    gCMSurveyListFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMSurveyListFieldID.jniData == 0) {
        CM_ERR("CMSurveyList no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMSurveyListFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMSurveyListFieldID.callback == NULL) {
        CM_ERR("CMSurveyList no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMSurveyListMethods,
            sizeof(CMSurveyListMethods) / sizeof(CMSurveyListMethods[0]));
}


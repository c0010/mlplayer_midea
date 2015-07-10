// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmexerciselist_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmexerciselist.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTExerciseListItemFieldID;

static void TExerciseListItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = new TExerciseListItem();

    env->SetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj, (int)pObj);
}

static void TExerciseListItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
}

static jstring TExerciseListItem_GetExerciseListItemID(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetExerciseListItemID();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TExerciseListItem_GetExerciseListItemTitle(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetExerciseListItemTitle();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TExerciseListItem_GetExerciseListItemDesc(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetExerciseListItemDesc();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TExerciseListItem_GetExerciseListItemCategory(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetExerciseListItemCategory();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TExerciseListItem_GetExerciseListItemPubdate(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetExerciseListItemPubdate();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TExerciseListItem_GetID(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExerciseListItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TExerciseListItem_GetTitle(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTitle.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExerciseListItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTitle, NULL);
    jsize size = env->GetStringLength(sTitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTitle = data;

    env->ReleaseStringChars(sTitle, jChar);
    
    free(data);
    
    return true;
}

static jint TExerciseListItem_GetQuestioncount(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nQuestioncount;
}
                
static jboolean TExerciseListItem_SetQuestioncount(JNIEnv* env, jobject thiz, jint nQuestioncount)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nQuestioncount = nQuestioncount;
    return true;
}
                
static jint TExerciseListItem_GetCompleteCount(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nCompleteCount;
}
                
static jboolean TExerciseListItem_SetCompleteCount(JNIEnv* env, jobject thiz, jint nCompleteCount)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nCompleteCount = nCompleteCount;
    return true;
}
                
static jstring TExerciseListItem_GetDesc(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDesc.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sDesc.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExerciseListItem_SetDesc(JNIEnv* env, jobject thiz, jstring sDesc)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDesc, NULL);
    jsize size = env->GetStringLength(sDesc);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sDesc = data;

    env->ReleaseStringChars(sDesc, jChar);
    
    free(data);
    
    return true;
}

static jstring TExerciseListItem_GetCategory(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sCategory.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sCategory.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExerciseListItem_SetCategory(JNIEnv* env, jobject thiz, jstring sCategory)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sCategory, NULL);
    jsize size = env->GetStringLength(sCategory);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sCategory = data;

    env->ReleaseStringChars(sCategory, jChar);
    
    free(data);
    
    return true;
}

static jint TExerciseListItem_GetUsercompletecount(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nUsercompletecount;
}
                
static jboolean TExerciseListItem_SetUsercompletecount(JNIEnv* env, jobject thiz, jint nUsercompletecount)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nUsercompletecount = nUsercompletecount;
    return true;
}
                
static jstring TExerciseListItem_GetPubdate(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPubdate.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPubdate.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExerciseListItem_SetPubdate(JNIEnv* env, jobject thiz, jstring sPubdate)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPubdate, NULL);
    jsize size = env->GetStringLength(sPubdate);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPubdate = data;

    env->ReleaseStringChars(sPubdate, jChar);
    
    free(data);
    
    return true;
}

static jint TExerciseListItem_GetCurIndex(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nCurIndex;
}
                
static jboolean TExerciseListItem_SetCurIndex(JNIEnv* env, jobject thiz, jint nCurIndex)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nCurIndex = nCurIndex;
    return true;
}
                
static jint TExerciseListItem_GetWrongCount(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nWrongCount;
}
                
static jboolean TExerciseListItem_SetWrongCount(JNIEnv* env, jobject thiz, jint nWrongCount)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nWrongCount = nWrongCount;
    return true;
}
                
static jint TExerciseListItem_GetRightCount(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nRightCount;
}
                
static jboolean TExerciseListItem_SetRightCount(JNIEnv* env, jobject thiz, jint nRightCount)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nRightCount = nRightCount;
    return true;
}
                
static jstring TExerciseListItem_GetTrainID(JNIEnv* env, jobject thiz)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTrainID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTrainID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExerciseListItem_SetTrainID(JNIEnv* env, jobject thiz, jstring sTrainID)
{
    TExerciseListItem* pObj = (TExerciseListItem*)env->GetIntField(thiz, gTExerciseListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTrainID, NULL);
    jsize size = env->GetStringLength(sTrainID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTrainID = data;

    env->ReleaseStringChars(sTrainID, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TExerciseListItem(JNIEnv* env) {
    static JNINativeMethod TExerciseListItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TExerciseListItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TExerciseListItem_nativeDestructor },
        { "GetExerciseListItemID", "()Ljava/lang/String;", (void*)TExerciseListItem_GetExerciseListItemID },
        { "GetExerciseListItemTitle", "()Ljava/lang/String;", (void*)TExerciseListItem_GetExerciseListItemTitle },
        { "GetExerciseListItemDesc", "()Ljava/lang/String;", (void*)TExerciseListItem_GetExerciseListItemDesc },
        { "GetExerciseListItemCategory", "()Ljava/lang/String;", (void*)TExerciseListItem_GetExerciseListItemCategory },
        { "GetExerciseListItemPubdate", "()Ljava/lang/String;", (void*)TExerciseListItem_GetExerciseListItemPubdate },
        { "GetID", "()Ljava/lang/String;", (void*)TExerciseListItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TExerciseListItem_SetID },
        { "GetTitle", "()Ljava/lang/String;", (void*)TExerciseListItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)TExerciseListItem_SetTitle },
        { "GetQuestioncount", "()I", (void*)TExerciseListItem_GetQuestioncount },
        { "SetQuestioncount", "(I)Z", (void*)TExerciseListItem_SetQuestioncount },
        { "GetCompleteCount", "()I", (void*)TExerciseListItem_GetCompleteCount },
        { "SetCompleteCount", "(I)Z", (void*)TExerciseListItem_SetCompleteCount },
        { "GetDesc", "()Ljava/lang/String;", (void*)TExerciseListItem_GetDesc },
        { "SetDesc", "(Ljava/lang/String;)Z", (void*)TExerciseListItem_SetDesc },
        { "GetCategory", "()Ljava/lang/String;", (void*)TExerciseListItem_GetCategory },
        { "SetCategory", "(Ljava/lang/String;)Z", (void*)TExerciseListItem_SetCategory },
        { "GetUsercompletecount", "()I", (void*)TExerciseListItem_GetUsercompletecount },
        { "SetUsercompletecount", "(I)Z", (void*)TExerciseListItem_SetUsercompletecount },
        { "GetPubdate", "()Ljava/lang/String;", (void*)TExerciseListItem_GetPubdate },
        { "SetPubdate", "(Ljava/lang/String;)Z", (void*)TExerciseListItem_SetPubdate },
        { "GetCurIndex", "()I", (void*)TExerciseListItem_GetCurIndex },
        { "SetCurIndex", "(I)Z", (void*)TExerciseListItem_SetCurIndex },
        { "GetWrongCount", "()I", (void*)TExerciseListItem_GetWrongCount },
        { "SetWrongCount", "(I)Z", (void*)TExerciseListItem_SetWrongCount },
        { "GetRightCount", "()I", (void*)TExerciseListItem_GetRightCount },
        { "SetRightCount", "(I)Z", (void*)TExerciseListItem_SetRightCount },
        { "GetTrainID", "()Ljava/lang/String;", (void*)TExerciseListItem_GetTrainID },
        { "SetTrainID", "(Ljava/lang/String;)Z", (void*)TExerciseListItem_SetTrainID }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TExerciseListItem");
    if (clazz == 0) {
        CM_ERR("class TExerciseListItem no found");
        return -1;
    }

    gTExerciseListItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTExerciseListItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TExerciseListItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TExerciseListItemMethods,
            sizeof(TExerciseListItemMethods) / sizeof(TExerciseListItemMethods[0]));
}


struct callback_cookie_CMExerciseList {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMExerciseListFieldID;

static void CMExerciseList_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMExerciseList when setting up callback.");
        return;
    }
    callback_cookie_CMExerciseList* pCookie = new callback_cookie_CMExerciseList;
    pCookie->listener1 = new CMUpdateDataListener(gCMExerciseListFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMExerciseListFieldID.jniData, (int)pCookie);

    CMExerciseList* pObj = new CMExerciseList();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj, (int)pObj);
}

static void CMExerciseList_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMExerciseList *pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMExerciseList* pCookie = (callback_cookie_CMExerciseList *)env->GetIntField(
        thiz, gCMExerciseListFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMExerciseListFieldID.jniData, 0);
}

static jint CMExerciseList_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMExerciseList_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    extern fields_t gTExerciseListItemFieldID;
    TExerciseListItem* pItem = (TExerciseListItem*)env->GetIntField(item, gTExerciseListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMExerciseList_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    extern fields_t gTExerciseListItemFieldID;
    TExerciseListItem* pItem = (TExerciseListItem*)env->GetIntField(obj, gTExerciseListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMExerciseList_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    extern fields_t gTExerciseListItemFieldID;
    TExerciseListItem* pItem = (TExerciseListItem*)env->GetIntField(obj, gTExerciseListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMExerciseList_IsEnd(JNIEnv* env, jobject thiz)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMExerciseList_RequestMore(JNIEnv* env, jobject thiz)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMExerciseList_IsRunning(JNIEnv* env, jobject thiz)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMExerciseList_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMExerciseList_Cancel(JNIEnv* env, jobject thiz)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMExerciseList_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMExerciseList_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    callback_cookie_CMExerciseList* pCookie = (callback_cookie_CMExerciseList *)env->GetIntField(
        thiz, gCMExerciseListFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMExerciseListFieldID.callback);
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

static jboolean CMExerciseList_GetList(JNIEnv* env, jobject thiz)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    BOOL ret = pObj->GetList();
    return ret;
}

static jboolean CMExerciseList_GetTrainList(JNIEnv* env, jobject thiz, jstring sTrainId)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    const jchar* jsTrainId = env->GetStringChars(sTrainId, NULL);
    jsize sizesTrainId = env->GetStringLength(sTrainId);
    char* psTrainId = UTF16toUTF8((jchar*)jsTrainId, (size_t*)&sizesTrainId);
    BOOL ret = pObj->GetTrainList(psTrainId);
    env->ReleaseStringChars(sTrainId, jsTrainId);
    free(psTrainId);
    return ret;
}

static jboolean CMExerciseList_GetExerciseById(JNIEnv* env, jobject thiz, jstring exerciseId)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    const jchar* jexerciseId = env->GetStringChars(exerciseId, NULL);
    jsize sizeexerciseId = env->GetStringLength(exerciseId);
    char* pexerciseId = UTF16toUTF8((jchar*)jexerciseId, (size_t*)&sizeexerciseId);
    BOOL ret = pObj->GetExerciseById(pexerciseId);
    env->ReleaseStringChars(exerciseId, jexerciseId);
    free(pexerciseId);
    return ret;
}

static jboolean CMExerciseList_LoadFromDB(JNIEnv* env, jobject thiz)
{
    CMExerciseList* pObj = (CMExerciseList*)env->GetIntField(thiz, gCMExerciseListFieldID.nativeJavaObj);

    BOOL ret = pObj->LoadFromDB();
    return ret;
}

int register_com_wunding_mlplayer_business_CMExerciseList(JNIEnv* env) {
    static JNINativeMethod CMExerciseListMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMExerciseList_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMExerciseList_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMExerciseList_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TExerciseListItem;)Z", (void*)CMExerciseList_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TExerciseListItem;)Z", (void*)CMExerciseList_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TExerciseListItem;)Z", (void*)CMExerciseList_Update },
        { "IsEnd", "()Z", (void*)CMExerciseList_IsEnd },
        { "RequestMore", "()Z", (void*)CMExerciseList_RequestMore },
        { "IsRunning", "()Z", (void*)CMExerciseList_IsRunning },
        { "IsRefresh", "()Z", (void*)CMExerciseList_IsRefresh },
        { "Cancel", "()V", (void*)CMExerciseList_Cancel },
        { "SetRequestType", "(I)V", (void*)CMExerciseList_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMExerciseList_SetListener },
        { "GetList", "()Z", (void*)CMExerciseList_GetList },
        { "GetTrainList", "(Ljava/lang/String;)Z", (void*)CMExerciseList_GetTrainList },
        { "GetExerciseById", "(Ljava/lang/String;)Z", (void*)CMExerciseList_GetExerciseById },
        { "LoadFromDB", "()Z", (void*)CMExerciseList_LoadFromDB }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMExerciseList");
    if (clazz == 0) {
        CM_ERR("class CMExerciseList no found");
        return -1;
    }

    gCMExerciseListFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMExerciseListFieldID.nativeJavaObj == 0) {
        CM_ERR("CMExerciseList no found mNativeObj");
        return -1;
    }

    gCMExerciseListFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMExerciseListFieldID.jniData == 0) {
        CM_ERR("CMExerciseList no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMExerciseListFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMExerciseListFieldID.callback == NULL) {
        CM_ERR("CMExerciseList no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMExerciseListMethods,
            sizeof(CMExerciseListMethods) / sizeof(CMExerciseListMethods[0]));
}


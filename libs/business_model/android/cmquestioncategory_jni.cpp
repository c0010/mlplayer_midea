// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmquestioncategory_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmquestioncategory.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMQuestionCategory {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMQuestionCategoryFieldID;

static void CMQuestionCategory_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMQuestionCategory when setting up callback.");
        return;
    }
    callback_cookie_CMQuestionCategory* pCookie = new callback_cookie_CMQuestionCategory;
    pCookie->listener1 = new CMUpdateDataListener(gCMQuestionCategoryFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMQuestionCategoryFieldID.jniData, (int)pCookie);

    CMQuestionCategory* pObj = new CMQuestionCategory(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMQuestionCategoryFieldID.nativeJavaObj, (int)pObj);
}

static void CMQuestionCategory_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMQuestionCategory *pObj = (CMQuestionCategory*)env->GetIntField(thiz, gCMQuestionCategoryFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMQuestionCategory* pCookie = (callback_cookie_CMQuestionCategory *)env->GetIntField(
        thiz, gCMQuestionCategoryFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMQuestionCategoryFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMQuestionCategoryFieldID.jniData, 0);
}

static jboolean CMQuestionCategory_Update(JNIEnv* env, jobject thiz)
{
    CMQuestionCategory* pObj = (CMQuestionCategory*)env->GetIntField(thiz, gCMQuestionCategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->Update();
    return ret;
}

static void CMQuestionCategory_CancelUpdate(JNIEnv* env, jobject thiz)
{
    CMQuestionCategory* pObj = (CMQuestionCategory*)env->GetIntField(thiz, gCMQuestionCategoryFieldID.nativeJavaObj);

    pObj->CancelUpdate();
}

static jint CMQuestionCategory_TopItemCount(JNIEnv* env, jobject thiz)
{
    CMQuestionCategory* pObj = (CMQuestionCategory*)env->GetIntField(thiz, gCMQuestionCategoryFieldID.nativeJavaObj);

    int ret = pObj->TopItemCount();
    return ret;
}

static jobject CMQuestionCategory_GetTopItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMQuestionCategory* pObj = (CMQuestionCategory*)env->GetIntField(thiz, gCMQuestionCategoryFieldID.nativeJavaObj);

    CMQuestionCategoryItem* pRet = pObj->GetTopItem(nIndex);
    if (pRet == NULL) return NULL;

    jclass retClazz = env->FindClass("com/wunding/mlplayer/business/CMQuestionCategoryItem");
    if (retClazz == NULL) {
        CM_ERR("Can't find class CMQuestionCategoryItem");
        return NULL;
    }

    jmethodID retConstructor = env->GetMethodID(retClazz, "<init>", "(I)V");
    if (retConstructor == NULL) {
        CM_ERR("Can't find class CMQuestionCategoryItem native constructor");
        return NULL;
    }

    return env->NewObject(retClazz,
            retConstructor, (int)pRet);
}

int register_com_wunding_mlplayer_business_CMQuestionCategory(JNIEnv* env) {
    static JNINativeMethod CMQuestionCategoryMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMQuestionCategory_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMQuestionCategory_nativeDestructor },
        { "Update", "()Z", (void*)CMQuestionCategory_Update },
        { "CancelUpdate", "()V", (void*)CMQuestionCategory_CancelUpdate },
        { "TopItemCount", "()I", (void*)CMQuestionCategory_TopItemCount },
        { "GetTopItem", "(I)Lcom/wunding/mlplayer/business/CMQuestionCategoryItem;", (void*)CMQuestionCategory_GetTopItem }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMQuestionCategory");
    if (clazz == 0) {
        CM_ERR("class CMQuestionCategory no found");
        return -1;
    }

    gCMQuestionCategoryFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMQuestionCategoryFieldID.nativeJavaObj == 0) {
        CM_ERR("CMQuestionCategory no found mNativeObj");
        return -1;
    }

    gCMQuestionCategoryFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMQuestionCategoryFieldID.jniData == 0) {
        CM_ERR("CMQuestionCategory no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMQuestionCategoryFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMQuestionCategoryFieldID.callback == NULL) {
        CM_ERR("CMQuestionCategory no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMQuestionCategoryMethods,
            sizeof(CMQuestionCategoryMethods) / sizeof(CMQuestionCategoryMethods[0]));
}

fields_t gCMQuestionCategoryItemFieldID;

static void CMQuestionCategoryItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
}

static void CMQuestionCategoryItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    env->SetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj, 0);
}

static jint CMQuestionCategoryItem_ChildItemCount(JNIEnv* env, jobject thiz)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);

    int ret = pObj->ChildItemCount();
    return ret;
}

static jobject CMQuestionCategoryItem_GetChildItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);

    CMQuestionCategoryItem* pRet = pObj->GetChildItem(nIndex);
    if (pRet == NULL) return NULL;

    jclass retClazz = env->FindClass("com/wunding/mlplayer/business/CMQuestionCategoryItem");
    if (retClazz == NULL) {
        CM_ERR("Can't find class CMQuestionCategoryItem");
        return NULL;
    }

    jmethodID retConstructor = env->GetMethodID(retClazz, "<init>", "(I)V");
    if (retConstructor == NULL) {
        CM_ERR("Can't find class CMQuestionCategoryItem native constructor");
        return NULL;
    }

    return env->NewObject(retClazz,
            retConstructor, (int)pRet);
}

static jstring CMQuestionCategoryItem_GetID(JNIEnv* env, jobject thiz)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID);
    jchar* data = UTF8toUTF16((char*)pObj->sID, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMQuestionCategoryItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);
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

static jstring CMQuestionCategoryItem_GetTitle(JNIEnv* env, jobject thiz)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle);
    jchar* data = UTF8toUTF16((char*)pObj->sTitle, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMQuestionCategoryItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);
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

static jint CMQuestionCategoryItem_GetQuestioncount(JNIEnv* env, jobject thiz)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nQuestioncount;
}
                
static jboolean CMQuestionCategoryItem_SetQuestioncount(JNIEnv* env, jobject thiz, jint nQuestioncount)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nQuestioncount = nQuestioncount;
    return true;
}
                
static jint CMQuestionCategoryItem_GetUncompletecount(JNIEnv* env, jobject thiz)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nUncompletecount;
}
                
static jboolean CMQuestionCategoryItem_SetUncompletecount(JNIEnv* env, jobject thiz, jint nUncompletecount)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nUncompletecount = nUncompletecount;
    return true;
}
                
static jint CMQuestionCategoryItem_GetWrongcount(JNIEnv* env, jobject thiz)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nWrongcount;
}
                
static jboolean CMQuestionCategoryItem_SetWrongcount(JNIEnv* env, jobject thiz, jint nWrongcount)
{
    CMQuestionCategoryItem* pObj = (CMQuestionCategoryItem*)env->GetIntField(thiz, gCMQuestionCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nWrongcount = nWrongcount;
    return true;
}
                
int register_com_wunding_mlplayer_business_CMQuestionCategoryItem(JNIEnv* env) {
    static JNINativeMethod CMQuestionCategoryItemMethods[] = {
        { "nativeConstructor", "()V", (void*)CMQuestionCategoryItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMQuestionCategoryItem_nativeDestructor },
        { "ChildItemCount", "()I", (void*)CMQuestionCategoryItem_ChildItemCount },
        { "GetChildItem", "(I)Lcom/wunding/mlplayer/business/CMQuestionCategoryItem;", (void*)CMQuestionCategoryItem_GetChildItem },
        { "GetID", "()Ljava/lang/String;", (void*)CMQuestionCategoryItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)CMQuestionCategoryItem_SetID },
        { "GetTitle", "()Ljava/lang/String;", (void*)CMQuestionCategoryItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)CMQuestionCategoryItem_SetTitle },
        { "GetQuestioncount", "()I", (void*)CMQuestionCategoryItem_GetQuestioncount },
        { "SetQuestioncount", "(I)Z", (void*)CMQuestionCategoryItem_SetQuestioncount },
        { "GetUncompletecount", "()I", (void*)CMQuestionCategoryItem_GetUncompletecount },
        { "SetUncompletecount", "(I)Z", (void*)CMQuestionCategoryItem_SetUncompletecount },
        { "GetWrongcount", "()I", (void*)CMQuestionCategoryItem_GetWrongcount },
        { "SetWrongcount", "(I)Z", (void*)CMQuestionCategoryItem_SetWrongcount }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMQuestionCategoryItem");
    if (clazz == 0) {
        CM_ERR("class CMQuestionCategoryItem no found");
        return -1;
    }

    gCMQuestionCategoryItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMQuestionCategoryItemFieldID.nativeJavaObj == 0) {
        CM_ERR("CMQuestionCategoryItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMQuestionCategoryItemMethods,
            sizeof(CMQuestionCategoryItemMethods) / sizeof(CMQuestionCategoryItemMethods[0]));
}


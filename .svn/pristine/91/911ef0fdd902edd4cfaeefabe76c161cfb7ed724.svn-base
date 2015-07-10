// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmsearch_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmsearch.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMSearch {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMSearchFieldID;

static void CMSearch_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMSearch when setting up callback.");
        return;
    }
    callback_cookie_CMSearch* pCookie = new callback_cookie_CMSearch;
    pCookie->listener1 = new CMUpdateDataListener(gCMSearchFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMSearchFieldID.jniData, (int)pCookie);

    CMSearch* pObj = new CMSearch(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMSearchFieldID.nativeJavaObj, (int)pObj);
}

static void CMSearch_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMSearch *pObj = (CMSearch*)env->GetIntField(thiz, gCMSearchFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMSearch* pCookie = (callback_cookie_CMSearch *)env->GetIntField(
        thiz, gCMSearchFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMSearchFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMSearchFieldID.jniData, 0);
}

static jboolean CMSearch_Search(JNIEnv* env, jobject thiz, jstring sFlag, jstring skey)
{
    CMSearch* pObj = (CMSearch*)env->GetIntField(thiz, gCMSearchFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jskey = env->GetStringChars(skey, NULL);
    jsize sizeskey = env->GetStringLength(skey);
    char* pskey = UTF16toUTF8((jchar*)jskey, (size_t*)&sizeskey);
    BOOL ret = pObj->Search(psFlag, pskey);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(skey, jskey);
    free(pskey);
    return ret;
}

static jboolean CMSearch_QuickSearch(JNIEnv* env, jobject thiz, jstring sFlag, jstring skey)
{
    CMSearch* pObj = (CMSearch*)env->GetIntField(thiz, gCMSearchFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jskey = env->GetStringChars(skey, NULL);
    jsize sizeskey = env->GetStringLength(skey);
    char* pskey = UTF16toUTF8((jchar*)jskey, (size_t*)&sizeskey);
    BOOL ret = pObj->QuickSearch(psFlag, pskey);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(skey, jskey);
    free(pskey);
    return ret;
}

static jboolean CMSearch_CategorySearch(JNIEnv* env, jobject thiz, jstring sFlag, jstring categoryID, jstring categoryTitle)
{
    CMSearch* pObj = (CMSearch*)env->GetIntField(thiz, gCMSearchFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jcategoryID = env->GetStringChars(categoryID, NULL);
    jsize sizecategoryID = env->GetStringLength(categoryID);
    char* pcategoryID = UTF16toUTF8((jchar*)jcategoryID, (size_t*)&sizecategoryID);
    const jchar* jcategoryTitle = env->GetStringChars(categoryTitle, NULL);
    jsize sizecategoryTitle = env->GetStringLength(categoryTitle);
    char* pcategoryTitle = UTF16toUTF8((jchar*)jcategoryTitle, (size_t*)&sizecategoryTitle);
    BOOL ret = pObj->CategorySearch(psFlag, pcategoryID, pcategoryTitle);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(categoryID, jcategoryID);
    free(pcategoryID);
    env->ReleaseStringChars(categoryTitle, jcategoryTitle);
    free(pcategoryTitle);
    return ret;
}

static jint CMSearch_GetRecentKeyCount(JNIEnv* env, jobject thiz)
{
    CMSearch* pObj = (CMSearch*)env->GetIntField(thiz, gCMSearchFieldID.nativeJavaObj);

    int ret = pObj->GetRecentKeyCount();
    return ret;
}

static jstring CMSearch_GetRecentKeyItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMSearch* pObj = (CMSearch*)env->GetIntField(thiz, gCMSearchFieldID.nativeJavaObj);

    const char* ret = pObj->GetRecentKeyItem(nIndex);
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

int register_com_wunding_mlplayer_business_CMSearch(JNIEnv* env) {
    static JNINativeMethod CMSearchMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMSearch_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMSearch_nativeDestructor },
        { "Search", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMSearch_Search },
        { "QuickSearch", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMSearch_QuickSearch },
        { "CategorySearch", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMSearch_CategorySearch },
        { "GetRecentKeyCount", "()I", (void*)CMSearch_GetRecentKeyCount },
        { "GetRecentKeyItem", "(I)Ljava/lang/String;", (void*)CMSearch_GetRecentKeyItem }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMSearch");
    if (clazz == 0) {
        CM_ERR("class CMSearch no found");
        return -1;
    }

    gCMSearchFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMSearchFieldID.nativeJavaObj == 0) {
        CM_ERR("CMSearch no found mNativeObj");
        return -1;
    }

    gCMSearchFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMSearchFieldID.jniData == 0) {
        CM_ERR("CMSearch no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMSearchFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMSearchFieldID.callback == NULL) {
        CM_ERR("CMSearch no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMSearchMethods,
            sizeof(CMSearchMethods) / sizeof(CMSearchMethods[0]));
}


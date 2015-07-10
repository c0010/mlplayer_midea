// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmfavorites_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmfavorites.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMFavorites {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMFavoritesFieldID;

static void CMFavorites_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMFavorites when setting up callback.");
        return;
    }
    callback_cookie_CMFavorites* pCookie = new callback_cookie_CMFavorites;
    pCookie->listener1 = new CMUpdateDataListener(gCMFavoritesFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMFavoritesFieldID.jniData, (int)pCookie);

    CMFavorites* pObj = CMFavorites::GetInstance();
    pObj->SetListener(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMFavoritesFieldID.nativeJavaObj, (int)pObj);
}

static void CMFavorites_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMFavorites *pObj = (CMFavorites*)env->GetIntField(thiz, gCMFavoritesFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMFavorites* pCookie = (callback_cookie_CMFavorites *)env->GetIntField(
        thiz, gCMFavoritesFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMFavoritesFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMFavoritesFieldID.jniData, 0);
}

static jboolean CMFavorites_RemoveItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMFavorites* pObj = (CMFavorites*)env->GetIntField(thiz, gCMFavoritesFieldID.nativeJavaObj);

    BOOL ret = pObj->RemoveItem(nIndex);
    return ret;
}

static void CMFavorites_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMFavorites* pObj = (CMFavorites*)env->GetIntField(thiz, gCMFavoritesFieldID.nativeJavaObj);

    callback_cookie_CMFavorites* pCookie = (callback_cookie_CMFavorites *)env->GetIntField(
        thiz, gCMFavoritesFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMFavoritesFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

    }
}

static jint CMFavorites_AddFavorite(JNIEnv* env, jobject thiz, jobject item)
{
    CMFavorites* pObj = (CMFavorites*)env->GetIntField(thiz, gCMFavoritesFieldID.nativeJavaObj);

    extern fields_t gTBrowserItemFieldID;
    TBrowserItem* pItem = (TBrowserItem*)env->GetIntField(item, gTBrowserItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jint ret = pObj->AddFavorite(*pItem);
        return ret;
    }
    else {
        return -1;
    }
}

static jint CMFavorites_IsAdded(JNIEnv* env, jobject thiz, jstring sFlag, jstring sid)
{
    CMFavorites* pObj = (CMFavorites*)env->GetIntField(thiz, gCMFavoritesFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jsid = env->GetStringChars(sid, NULL);
    jsize sizesid = env->GetStringLength(sid);
    char* psid = UTF16toUTF8((jchar*)jsid, (size_t*)&sizesid);
    int ret = pObj->IsAdded(psFlag, psid);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(sid, jsid);
    free(psid);
    return ret;
}

static jboolean CMFavorites_LoadFromDB(JNIEnv* env, jobject thiz)
{
    CMFavorites* pObj = (CMFavorites*)env->GetIntField(thiz, gCMFavoritesFieldID.nativeJavaObj);

    BOOL ret = pObj->LoadFromDB();
    return ret;
}

int register_com_wunding_mlplayer_business_CMFavorites(JNIEnv* env) {
    static JNINativeMethod CMFavoritesMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMFavorites_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMFavorites_nativeDestructor },
        { "RemoveItem", "(I)Z", (void*)CMFavorites_RemoveItem },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMFavorites_SetListener },
        { "AddFavorite", "(Lcom/wunding/mlplayer/business/TBrowserItem;)I", (void*)CMFavorites_AddFavorite },
        { "IsAdded", "(Ljava/lang/String;Ljava/lang/String;)I", (void*)CMFavorites_IsAdded },
        { "LoadFromDB", "()Z", (void*)CMFavorites_LoadFromDB }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMFavorites");
    if (clazz == 0) {
        CM_ERR("class CMFavorites no found");
        return -1;
    }

    gCMFavoritesFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMFavoritesFieldID.nativeJavaObj == 0) {
        CM_ERR("CMFavorites no found mNativeObj");
        return -1;
    }

    gCMFavoritesFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMFavoritesFieldID.jniData == 0) {
        CM_ERR("CMFavorites no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMFavoritesFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMFavoritesFieldID.callback == NULL) {
        CM_ERR("CMFavorites no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMFavoritesMethods,
            sizeof(CMFavoritesMethods) / sizeof(CMFavoritesMethods[0]));
}


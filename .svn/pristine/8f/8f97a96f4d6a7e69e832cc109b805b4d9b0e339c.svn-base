// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmlogin_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmlogin.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTADImagesFieldID;

static void TADImages_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TADImages* pObj = new TADImages();

    env->SetIntField(thiz, gTADImagesFieldID.nativeJavaObj, (int)pObj);
}

static void TADImages_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TADImages*)env->GetIntField(thiz, gTADImagesFieldID.nativeJavaObj);
}

static jstring TADImages_GetImage(JNIEnv* env, jobject thiz)
{
    TADImages* pObj = (TADImages*)env->GetIntField(thiz, gTADImagesFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sImage);
    jchar* data = UTF8toUTF16((char*)pObj->sImage, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TADImages_SetImage(JNIEnv* env, jobject thiz, jstring sImage)
{
    TADImages* pObj = (TADImages*)env->GetIntField(thiz, gTADImagesFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sImage, NULL);
    jsize size = env->GetStringLength(sImage);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sImage, (const char*)data, 199);
    pObj->sImage[199] = '\0';

    env->ReleaseStringChars(sImage, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TADImages(JNIEnv* env) {
    static JNINativeMethod TADImagesMethods[] = {
        { "nativeConstructor", "()V", (void*)TADImages_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TADImages_nativeDestructor },
        { "GetImage", "()Ljava/lang/String;", (void*)TADImages_GetImage },
        { "SetImage", "(Ljava/lang/String;)Z", (void*)TADImages_SetImage }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TADImages");
    if (clazz == 0) {
        CM_ERR("class TADImages no found");
        return -1;
    }

    gTADImagesFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTADImagesFieldID.nativeJavaObj == 0) {
        CM_ERR("TADImages no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TADImagesMethods,
            sizeof(TADImagesMethods) / sizeof(TADImagesMethods[0]));
}

fields_t gCMEnterpriseInfoFieldID;

static void CMEnterpriseInfo_nativeConstructor(JNIEnv* env, jobject thiz)
{
    CMEnterpriseInfo* pObj = new CMEnterpriseInfo();

    env->SetIntField(thiz, gCMEnterpriseInfoFieldID.nativeJavaObj, (int)pObj);
}

static void CMEnterpriseInfo_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (CMEnterpriseInfo*)env->GetIntField(thiz, gCMEnterpriseInfoFieldID.nativeJavaObj);
}

static jstring CMEnterpriseInfo_GetID(JNIEnv* env, jobject thiz)
{
    CMEnterpriseInfo* pObj = (CMEnterpriseInfo*)env->GetIntField(thiz, gCMEnterpriseInfoFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID);
    jchar* data = UTF8toUTF16((char*)pObj->sID, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMEnterpriseInfo_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    CMEnterpriseInfo* pObj = (CMEnterpriseInfo*)env->GetIntField(thiz, gCMEnterpriseInfoFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sID, (const char*)data, 19);
    pObj->sID[19] = '\0';

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring CMEnterpriseInfo_GetTitle(JNIEnv* env, jobject thiz)
{
    CMEnterpriseInfo* pObj = (CMEnterpriseInfo*)env->GetIntField(thiz, gCMEnterpriseInfoFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle);
    jchar* data = UTF8toUTF16((char*)pObj->sTitle, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMEnterpriseInfo_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    CMEnterpriseInfo* pObj = (CMEnterpriseInfo*)env->GetIntField(thiz, gCMEnterpriseInfoFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTitle, NULL);
    jsize size = env->GetStringLength(sTitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sTitle, (const char*)data, 49);
    pObj->sTitle[49] = '\0';

    env->ReleaseStringChars(sTitle, jChar);
    
    free(data);
    
    return true;
}

static jstring CMEnterpriseInfo_GetSlogan(JNIEnv* env, jobject thiz)
{
    CMEnterpriseInfo* pObj = (CMEnterpriseInfo*)env->GetIntField(thiz, gCMEnterpriseInfoFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sSlogan);
    jchar* data = UTF8toUTF16((char*)pObj->sSlogan, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMEnterpriseInfo_SetSlogan(JNIEnv* env, jobject thiz, jstring sSlogan)
{
    CMEnterpriseInfo* pObj = (CMEnterpriseInfo*)env->GetIntField(thiz, gCMEnterpriseInfoFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sSlogan, NULL);
    jsize size = env->GetStringLength(sSlogan);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sSlogan, (const char*)data, 99);
    pObj->sSlogan[99] = '\0';

    env->ReleaseStringChars(sSlogan, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_CMEnterpriseInfo(JNIEnv* env) {
    static JNINativeMethod CMEnterpriseInfoMethods[] = {
        { "nativeConstructor", "()V", (void*)CMEnterpriseInfo_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMEnterpriseInfo_nativeDestructor },
        { "GetID", "()Ljava/lang/String;", (void*)CMEnterpriseInfo_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)CMEnterpriseInfo_SetID },
        { "GetTitle", "()Ljava/lang/String;", (void*)CMEnterpriseInfo_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)CMEnterpriseInfo_SetTitle },
        { "GetSlogan", "()Ljava/lang/String;", (void*)CMEnterpriseInfo_GetSlogan },
        { "SetSlogan", "(Ljava/lang/String;)Z", (void*)CMEnterpriseInfo_SetSlogan }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMEnterpriseInfo");
    if (clazz == 0) {
        CM_ERR("class CMEnterpriseInfo no found");
        return -1;
    }

    gCMEnterpriseInfoFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMEnterpriseInfoFieldID.nativeJavaObj == 0) {
        CM_ERR("CMEnterpriseInfo no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMEnterpriseInfoMethods,
            sizeof(CMEnterpriseInfoMethods) / sizeof(CMEnterpriseInfoMethods[0]));
}


struct callback_cookie_CMLogin {
    jclass      info_class;
    jobject     ref;
    CMLoginListener* listener1;
};

fields_t gCMLoginFieldID;

static void CMLogin_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMLogin when setting up callback.");
        return;
    }
    callback_cookie_CMLogin* pCookie = new callback_cookie_CMLogin;
    pCookie->listener1 = new CMLoginListener(gCMLoginFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMLoginFieldID.jniData, (int)pCookie);

    CMLogin* pObj = new CMLogin(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMLoginFieldID.nativeJavaObj, (int)pObj);
}

static void CMLogin_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMLogin *pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMLogin* pCookie = (callback_cookie_CMLogin *)env->GetIntField(
        thiz, gCMLoginFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMLoginFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMLoginFieldID.jniData, 0);
}

static jint CMLogin_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMLogin_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    extern fields_t gCMEnterpriseInfoFieldID;
    CMEnterpriseInfo* pItem = (CMEnterpriseInfo*)env->GetIntField(item, gCMEnterpriseInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMLogin_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    extern fields_t gCMEnterpriseInfoFieldID;
    CMEnterpriseInfo* pItem = (CMEnterpriseInfo*)env->GetIntField(obj, gCMEnterpriseInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMLogin_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    extern fields_t gCMEnterpriseInfoFieldID;
    CMEnterpriseInfo* pItem = (CMEnterpriseInfo*)env->GetIntField(obj, gCMEnterpriseInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMLogin_IsEnd(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMLogin_RequestMore(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMLogin_IsRunning(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMLogin_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMLogin_Cancel(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMLogin_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static jint CMLogin_GetImagesItemCount(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    int ret = pObj->GetImagesItemCount();
    return ret;
}

static jboolean CMLogin_GetImagesItem(JNIEnv* env, jobject thiz, jint nIndex, jobject image)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    extern fields_t gTADImagesFieldID;
    TADImages* pItem = (TADImages*)env->GetIntField(image, gTADImagesFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetImagesItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jstring CMLogin_GetUserName(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    const char* ret = pObj->GetUserName();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMLogin_GetPassWord(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    const char* ret = pObj->GetPassWord();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMLogin_GetAutoLogin(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    BOOL ret = pObj->GetAutoLogin();
    return ret;
}

static void CMLogin_LoginOffline(JNIEnv* env, jobject thiz, jstring sEid, jstring sUserName, jstring sPassWord, jboolean bAutoLogin)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    const jchar* jsEid = env->GetStringChars(sEid, NULL);
    jsize sizesEid = env->GetStringLength(sEid);
    char* psEid = UTF16toUTF8((jchar*)jsEid, (size_t*)&sizesEid);
    const jchar* jsUserName = env->GetStringChars(sUserName, NULL);
    jsize sizesUserName = env->GetStringLength(sUserName);
    char* psUserName = UTF16toUTF8((jchar*)jsUserName, (size_t*)&sizesUserName);
    const jchar* jsPassWord = env->GetStringChars(sPassWord, NULL);
    jsize sizesPassWord = env->GetStringLength(sPassWord);
    char* psPassWord = UTF16toUTF8((jchar*)jsPassWord, (size_t*)&sizesPassWord);
    pObj->LoginOffline(psEid, psUserName, psPassWord, bAutoLogin);
    env->ReleaseStringChars(sEid, jsEid);
    free(psEid);
    env->ReleaseStringChars(sUserName, jsUserName);
    free(psUserName);
    env->ReleaseStringChars(sPassWord, jsPassWord);
    free(psPassWord);
}

static void CMLogin_Login(JNIEnv* env, jobject thiz, jstring sEid, jstring sUserName, jstring sPassWord, jstring sUserId, jboolean bAutoLogin)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    const jchar* jsEid = env->GetStringChars(sEid, NULL);
    jsize sizesEid = env->GetStringLength(sEid);
    char* psEid = UTF16toUTF8((jchar*)jsEid, (size_t*)&sizesEid);
    const jchar* jsUserName = env->GetStringChars(sUserName, NULL);
    jsize sizesUserName = env->GetStringLength(sUserName);
    char* psUserName = UTF16toUTF8((jchar*)jsUserName, (size_t*)&sizesUserName);
    const jchar* jsPassWord = env->GetStringChars(sPassWord, NULL);
    jsize sizesPassWord = env->GetStringLength(sPassWord);
    char* psPassWord = UTF16toUTF8((jchar*)jsPassWord, (size_t*)&sizesPassWord);
    const jchar* jsUserId = env->GetStringChars(sUserId, NULL);
    jsize sizesUserId = env->GetStringLength(sUserId);
    char* psUserId = UTF16toUTF8((jchar*)jsUserId, (size_t*)&sizesUserId);
    pObj->Login(psEid, psUserName, psPassWord, psUserId, bAutoLogin);
    env->ReleaseStringChars(sEid, jsEid);
    free(psEid);
    env->ReleaseStringChars(sUserName, jsUserName);
    free(psUserName);
    env->ReleaseStringChars(sPassWord, jsPassWord);
    free(psPassWord);
    env->ReleaseStringChars(sUserId, jsUserId);
    free(psUserId);
}

static void CMLogin_LoginByMidea(JNIEnv* env, jobject thiz, jstring sEid, jstring sMideaUid, jstring sMideaPwd)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    const jchar* jsEid = env->GetStringChars(sEid, NULL);
    jsize sizesEid = env->GetStringLength(sEid);
    char* psEid = UTF16toUTF8((jchar*)jsEid, (size_t*)&sizesEid);
    const jchar* jsMideaUid = env->GetStringChars(sMideaUid, NULL);
    jsize sizesMideaUid = env->GetStringLength(sMideaUid);
    char* psMideaUid = UTF16toUTF8((jchar*)jsMideaUid, (size_t*)&sizesMideaUid);
    const jchar* jsMideaPwd = env->GetStringChars(sMideaPwd, NULL);
    jsize sizesMideaPwd = env->GetStringLength(sMideaPwd);
    char* psMideaPwd = UTF16toUTF8((jchar*)jsMideaPwd, (size_t*)&sizesMideaPwd);
    pObj->LoginByMidea(psEid, psMideaUid, psMideaPwd);
    env->ReleaseStringChars(sEid, jsEid);
    free(psEid);
    env->ReleaseStringChars(sMideaUid, jsMideaUid);
    free(psMideaUid);
    env->ReleaseStringChars(sMideaPwd, jsMideaPwd);
    free(psMideaPwd);
}

static void CMLogin_CancelLogin(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    pObj->CancelLogin();
}

static jboolean CMLogin_GetEnterpriseInfo(JNIEnv* env, jobject thiz, jobject item)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    extern fields_t gCMEnterpriseInfoFieldID;
    CMEnterpriseInfo* pItem = (CMEnterpriseInfo*)env->GetIntField(item, gCMEnterpriseInfoFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetEnterpriseInfo(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static void CMLogin_LoadFromDbs(JNIEnv* env, jobject thiz)
{
    CMLogin* pObj = (CMLogin*)env->GetIntField(thiz, gCMLoginFieldID.nativeJavaObj);

    pObj->LoadFromDbs();
}

int register_com_wunding_mlplayer_business_CMLogin(JNIEnv* env) {
    static JNINativeMethod CMLoginMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMLogin_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMLogin_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMLogin_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/CMEnterpriseInfo;)Z", (void*)CMLogin_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/CMEnterpriseInfo;)Z", (void*)CMLogin_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/CMEnterpriseInfo;)Z", (void*)CMLogin_Update },
        { "IsEnd", "()Z", (void*)CMLogin_IsEnd },
        { "RequestMore", "()Z", (void*)CMLogin_RequestMore },
        { "IsRunning", "()Z", (void*)CMLogin_IsRunning },
        { "IsRefresh", "()Z", (void*)CMLogin_IsRefresh },
        { "Cancel", "()V", (void*)CMLogin_Cancel },
        { "SetRequestType", "(I)V", (void*)CMLogin_SetRequestType },
        { "GetImagesItemCount", "()I", (void*)CMLogin_GetImagesItemCount },
        { "GetImagesItem", "(ILcom/wunding/mlplayer/business/TADImages;)Z", (void*)CMLogin_GetImagesItem },
        { "GetUserName", "()Ljava/lang/String;", (void*)CMLogin_GetUserName },
        { "GetPassWord", "()Ljava/lang/String;", (void*)CMLogin_GetPassWord },
        { "GetAutoLogin", "()Z", (void*)CMLogin_GetAutoLogin },
        { "LoginOffline", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V", (void*)CMLogin_LoginOffline },
        { "Login", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V", (void*)CMLogin_Login },
        { "LoginByMidea", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void*)CMLogin_LoginByMidea },
        { "CancelLogin", "()V", (void*)CMLogin_CancelLogin },
        { "GetEnterpriseInfo", "(Lcom/wunding/mlplayer/business/CMEnterpriseInfo;)Z", (void*)CMLogin_GetEnterpriseInfo },
        { "LoadFromDbs", "()V", (void*)CMLogin_LoadFromDbs }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMLogin");
    if (clazz == 0) {
        CM_ERR("class CMLogin no found");
        return -1;
    }

    gCMLoginFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMLoginFieldID.nativeJavaObj == 0) {
        CM_ERR("CMLogin no found mNativeObj");
        return -1;
    }

    gCMLoginFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMLoginFieldID.jniData == 0) {
        CM_ERR("CMLogin no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMLoginFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMLoginFieldID.callback == NULL) {
        CM_ERR("CMLogin no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMLoginMethods,
            sizeof(CMLoginMethods) / sizeof(CMLoginMethods[0]));
}


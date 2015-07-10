// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmgeneral_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmgeneral.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gCMGeneralFieldID;

static void CMGeneral_nativeConstructor(JNIEnv* env, jobject thiz)
{
    CMGeneral* pObj = new CMGeneral();

    env->SetIntField(thiz, gCMGeneralFieldID.nativeJavaObj, (int)pObj);
}

static void CMGeneral_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (CMGeneral*)env->GetIntField(thiz, gCMGeneralFieldID.nativeJavaObj);
}

static jstring CMGeneral_FormatUrlBySID(JNIEnv* env, jobject thiz, jstring sOrgUrl)
{
    CMGeneral* pObj = (CMGeneral*)env->GetIntField(thiz, gCMGeneralFieldID.nativeJavaObj);

    const jchar* jsOrgUrl = env->GetStringChars(sOrgUrl, NULL);
    jsize sizesOrgUrl = env->GetStringLength(sOrgUrl);
    char* psOrgUrl = UTF16toUTF8((jchar*)jsOrgUrl, (size_t*)&sizesOrgUrl);
    const char* ret = pObj->FormatUrlBySID(psOrgUrl);
    env->ReleaseStringChars(sOrgUrl, jsOrgUrl);
    free(psOrgUrl);
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMGeneral_ResetPasswordEnabled(JNIEnv* env, jobject thiz)
{
    CMGeneral* pObj = (CMGeneral*)env->GetIntField(thiz, gCMGeneralFieldID.nativeJavaObj);

    BOOL ret = pObj->ResetPasswordEnabled();
    return ret;
}

static jboolean CMGeneral_IsOffline(JNIEnv* env, jobject thiz)
{
    CMGeneral* pObj = (CMGeneral*)env->GetIntField(thiz, gCMGeneralFieldID.nativeJavaObj);

    BOOL ret = pObj->IsOffline();
    return ret;
}

static jboolean CMGeneral_ClearCache(JNIEnv* env, jobject thiz)
{
    CMGeneral* pObj = (CMGeneral*)env->GetIntField(thiz, gCMGeneralFieldID.nativeJavaObj);

    BOOL ret = pObj->ClearCache();
    return ret;
}

static void CMGeneral_setOffline(JNIEnv* env, jobject thiz, jboolean off)
{
    CMGeneral* pObj = (CMGeneral*)env->GetIntField(thiz, gCMGeneralFieldID.nativeJavaObj);

    pObj->setOffline(off);
}

static jboolean CMGeneral_IsSidExist(JNIEnv* env, jobject thiz)
{
    CMGeneral* pObj = (CMGeneral*)env->GetIntField(thiz, gCMGeneralFieldID.nativeJavaObj);

    BOOL ret = pObj->IsSidExist();
    return ret;
}

int register_com_wunding_mlplayer_business_CMGeneral(JNIEnv* env) {
    static JNINativeMethod CMGeneralMethods[] = {
        { "nativeConstructor", "()V", (void*)CMGeneral_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMGeneral_nativeDestructor },
        { "FormatUrlBySID", "(Ljava/lang/String;)Ljava/lang/String;", (void*)CMGeneral_FormatUrlBySID },
        { "ResetPasswordEnabled", "()Z", (void*)CMGeneral_ResetPasswordEnabled },
        { "IsOffline", "()Z", (void*)CMGeneral_IsOffline },
        { "ClearCache", "()Z", (void*)CMGeneral_ClearCache },
        { "setOffline", "(Z)V", (void*)CMGeneral_setOffline },
        { "IsSidExist", "()Z", (void*)CMGeneral_IsSidExist }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMGeneral");
    if (clazz == 0) {
        CM_ERR("class CMGeneral no found");
        return -1;
    }

    gCMGeneralFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMGeneralFieldID.nativeJavaObj == 0) {
        CM_ERR("CMGeneral no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMGeneralMethods,
            sizeof(CMGeneralMethods) / sizeof(CMGeneralMethods[0]));
}


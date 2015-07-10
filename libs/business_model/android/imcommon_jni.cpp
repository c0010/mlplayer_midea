// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: imcommon_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "imcommon_jni.h"
#include "android/env.h"


CMUpdateDataListener::CMUpdateDataListener(jmethodID funcID)
{
    mFuncID = funcID;
}

CMUpdateDataListener::~CMUpdateDataListener()
{
}

void CMUpdateDataListener::OnUpdateDataProgress(void* UserData, int nPercent)
{
    JNIEnv *env = NULL;
    int status = GetJavaVM()->GetEnv((void **) &env, JNI_VERSION_1_4);
    if(status < 0) {
        CM_ERR("CMUpdateDataListener OnUpdateDataProgress:failed to get JNI environment");
        return;
    }

    if (env) {
        callback_cookie* pCookie = (callback_cookie *)UserData;
        env->CallStaticVoidMethod(
                pCookie->info_class, mFuncID, pCookie->ref, 
                1, nPercent, 0);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
    }
}

void CMUpdateDataListener::OnUpdateDataFinish(void* UserData, int Result)
{
    JNIEnv *env = NULL;
    int status = GetJavaVM()->GetEnv((void **) &env, JNI_VERSION_1_4);
    if(status < 0) {
        CM_ERR("CMUpdateDataListener OnUpdateDataFinish:failed to get JNI environment");
        return;
    }

    if (env) {
        callback_cookie* pCookie = (callback_cookie *)UserData;
        env->CallStaticVoidMethod(
                pCookie->info_class, mFuncID, pCookie->ref, 
                2, Result, 0);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
    }
}

CMSimpleResultListener::CMSimpleResultListener(jmethodID funcID)
{
    mFuncID = funcID;
}

CMSimpleResultListener::~CMSimpleResultListener()
{
}

void CMSimpleResultListener::OnRequestFinish(void* UserData, int Result)
{
    JNIEnv *env = NULL;
    int status = GetJavaVM()->GetEnv((void **) &env, JNI_VERSION_1_4);
    if(status < 0) {
        CM_ERR("CMSimpleResultListener OnRequestFinish:failed to get JNI environment");
        return;
    }

    if (env) {
        callback_cookie* pCookie = (callback_cookie *)UserData;
        env->CallStaticVoidMethod(
                pCookie->info_class, mFuncID, pCookie->ref, 
                3, Result, 0);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
    }
}

CMLoginListener::CMLoginListener(jmethodID funcID)
{
    mFuncID = funcID;
}

CMLoginListener::~CMLoginListener()
{
}

void CMLoginListener::OnLogin(void* UserData, int Result, int HasNewVersion)
{
    JNIEnv *env = NULL;
    int status = GetJavaVM()->GetEnv((void **) &env, JNI_VERSION_1_4);
    if(status < 0) {
        CM_ERR("CMLoginListener OnLogin:failed to get JNI environment");
        return;
    }

    if (env) {
        callback_cookie* pCookie = (callback_cookie *)UserData;
        env->CallStaticVoidMethod(
                pCookie->info_class, mFuncID, pCookie->ref, 
                4, Result, HasNewVersion);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
    }
}

CMRatingListener::CMRatingListener(jmethodID funcID)
{
    mFuncID = funcID;
}

CMRatingListener::~CMRatingListener()
{
}

void CMRatingListener::OnRating(void* UserData, int nNewRating, int Result)
{
    JNIEnv *env = NULL;
    int status = GetJavaVM()->GetEnv((void **) &env, JNI_VERSION_1_4);
    if(status < 0) {
        CM_ERR("CMRatingListener OnRating:failed to get JNI environment");
        return;
    }

    if (env) {
        callback_cookie* pCookie = (callback_cookie *)UserData;
        env->CallStaticVoidMethod(
                pCookie->info_class, mFuncID, pCookie->ref, 
                5, nNewRating, Result);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
    }
}

CMGetImageListener::CMGetImageListener(jmethodID funcID)
{
    mFuncID = funcID;
}

CMGetImageListener::~CMGetImageListener()
{
}

void CMGetImageListener::OnFinish(void* UserData, int Result, int nID)
{
    JNIEnv *env = NULL;
    int status = GetJavaVM()->GetEnv((void **) &env, JNI_VERSION_1_4);
    if(status < 0) {
        CM_ERR("CMGetImageListener OnFinish:failed to get JNI environment");
        return;
    }

    if (env) {
        callback_cookie* pCookie = (callback_cookie *)UserData;
        env->CallStaticVoidMethod(
                pCookie->info_class, mFuncID, pCookie->ref, 
                6, Result, nID);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
    }
}

int initCustom(JNIEnv* env) {
//	CMLogger::GetLogger()->SetLevel(CM_LOGL_ERR);
	CMLogger::GetLogger()->SetLevel(CM_LOGL_TRACE);
	return 0;
}

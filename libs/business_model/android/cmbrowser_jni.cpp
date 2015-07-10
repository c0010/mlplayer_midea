// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmbrowser_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmbrowser.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMBrowser {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMBrowserFieldID;

static void CMBrowser_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMBrowser when setting up callback.");
        return;
    }
    callback_cookie_CMBrowser* pCookie = new callback_cookie_CMBrowser;
    pCookie->listener1 = new CMUpdateDataListener(gCMBrowserFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMBrowserFieldID.jniData, (int)pCookie);

    CMBrowser* pObj = new CMBrowser(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMBrowserFieldID.nativeJavaObj, (int)pObj);
}

static void CMBrowser_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMBrowser *pObj = (CMBrowser*)env->GetIntField(thiz, gCMBrowserFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMBrowser* pCookie = (callback_cookie_CMBrowser *)env->GetIntField(
        thiz, gCMBrowserFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMBrowserFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMBrowserFieldID.jniData, 0);
}

static jboolean CMBrowser_Request(JNIEnv* env, jobject thiz, jstring sFlag, jstring sID)
{
    CMBrowser* pObj = (CMBrowser*)env->GetIntField(thiz, gCMBrowserFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jsID = env->GetStringChars(sID, NULL);
    jsize sizesID = env->GetStringLength(sID);
    char* psID = UTF16toUTF8((jchar*)jsID, (size_t*)&sizesID);
    BOOL ret = pObj->Request(psFlag, psID);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(sID, jsID);
    free(psID);
    return ret;
}

static jboolean CMBrowser_RequestPisitionCourse(JNIEnv* env, jobject thiz)
{
    CMBrowser* pObj = (CMBrowser*)env->GetIntField(thiz, gCMBrowserFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestPisitionCourse();
    return ret;
}

static jboolean CMBrowser_RequestMarkClass(JNIEnv* env, jobject thiz, jstring markID)
{
    CMBrowser* pObj = (CMBrowser*)env->GetIntField(thiz, gCMBrowserFieldID.nativeJavaObj);

    const jchar* jmarkID = env->GetStringChars(markID, NULL);
    jsize sizemarkID = env->GetStringLength(markID);
    char* pmarkID = UTF16toUTF8((jchar*)jmarkID, (size_t*)&sizemarkID);
    BOOL ret = pObj->RequestMarkClass(pmarkID);
    env->ReleaseStringChars(markID, jmarkID);
    free(pmarkID);
    return ret;
}

static jboolean CMBrowser_RequestCoursewareById(JNIEnv* env, jobject thiz, jstring coursewareID)
{
    CMBrowser* pObj = (CMBrowser*)env->GetIntField(thiz, gCMBrowserFieldID.nativeJavaObj);

    const jchar* jcoursewareID = env->GetStringChars(coursewareID, NULL);
    jsize sizecoursewareID = env->GetStringLength(coursewareID);
    char* pcoursewareID = UTF16toUTF8((jchar*)jcoursewareID, (size_t*)&sizecoursewareID);
    BOOL ret = pObj->RequestCoursewareById(pcoursewareID);
    env->ReleaseStringChars(coursewareID, jcoursewareID);
    free(pcoursewareID);
    return ret;
}

static jboolean CMBrowser_RequestNewsById(JNIEnv* env, jobject thiz, jstring newsID)
{
    CMBrowser* pObj = (CMBrowser*)env->GetIntField(thiz, gCMBrowserFieldID.nativeJavaObj);

    const jchar* jnewsID = env->GetStringChars(newsID, NULL);
    jsize sizenewsID = env->GetStringLength(newsID);
    char* pnewsID = UTF16toUTF8((jchar*)jnewsID, (size_t*)&sizenewsID);
    BOOL ret = pObj->RequestNewsById(pnewsID);
    env->ReleaseStringChars(newsID, jnewsID);
    free(pnewsID);
    return ret;
}

static jboolean CMBrowser_RequestTrain(JNIEnv* env, jobject thiz, jstring sFlag, jstring sTrainID)
{
    CMBrowser* pObj = (CMBrowser*)env->GetIntField(thiz, gCMBrowserFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jsTrainID = env->GetStringChars(sTrainID, NULL);
    jsize sizesTrainID = env->GetStringLength(sTrainID);
    char* psTrainID = UTF16toUTF8((jchar*)jsTrainID, (size_t*)&sizesTrainID);
    BOOL ret = pObj->RequestTrain(psFlag, psTrainID);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(sTrainID, jsTrainID);
    free(psTrainID);
    return ret;
}

static jboolean CMBrowser_RequestTop(JNIEnv* env, jobject thiz, jstring sFlag, jstring sBrowerID)
{
    CMBrowser* pObj = (CMBrowser*)env->GetIntField(thiz, gCMBrowserFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jsBrowerID = env->GetStringChars(sBrowerID, NULL);
    jsize sizesBrowerID = env->GetStringLength(sBrowerID);
    char* psBrowerID = UTF16toUTF8((jchar*)jsBrowerID, (size_t*)&sizesBrowerID);
    BOOL ret = pObj->RequestTop(psFlag, psBrowerID);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(sBrowerID, jsBrowerID);
    free(psBrowerID);
    return ret;
}

int register_com_wunding_mlplayer_business_CMBrowser(JNIEnv* env) {
    static JNINativeMethod CMBrowserMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMBrowser_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMBrowser_nativeDestructor },
        { "Request", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMBrowser_Request },
        { "RequestPisitionCourse", "()Z", (void*)CMBrowser_RequestPisitionCourse },
        { "RequestMarkClass", "(Ljava/lang/String;)Z", (void*)CMBrowser_RequestMarkClass },
        { "RequestCoursewareById", "(Ljava/lang/String;)Z", (void*)CMBrowser_RequestCoursewareById },
        { "RequestNewsById", "(Ljava/lang/String;)Z", (void*)CMBrowser_RequestNewsById },
        { "RequestTrain", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMBrowser_RequestTrain },
        { "RequestTop", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMBrowser_RequestTop }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMBrowser");
    if (clazz == 0) {
        CM_ERR("class CMBrowser no found");
        return -1;
    }

    gCMBrowserFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMBrowserFieldID.nativeJavaObj == 0) {
        CM_ERR("CMBrowser no found mNativeObj");
        return -1;
    }

    gCMBrowserFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMBrowserFieldID.jniData == 0) {
        CM_ERR("CMBrowser no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMBrowserFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMBrowserFieldID.callback == NULL) {
        CM_ERR("CMBrowser no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMBrowserMethods,
            sizeof(CMBrowserMethods) / sizeof(CMBrowserMethods[0]));
}


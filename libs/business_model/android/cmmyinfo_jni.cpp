// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmmyinfo_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmmyinfo.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMMyInfo {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gCMMyInfoFieldID;

static void CMMyInfo_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMMyInfo when setting up callback.");
        return;
    }
    callback_cookie_CMMyInfo* pCookie = new callback_cookie_CMMyInfo;
    pCookie->listener1 = new CMUpdateDataListener(gCMMyInfoFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gCMMyInfoFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMMyInfoFieldID.jniData, (int)pCookie);

    CMMyInfo* pObj = CMMyInfo::GetInstance();
    pObj->SetListener(pCookie->listener1, pCookie->listener2);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj, (int)pObj);
}

static void CMMyInfo_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMMyInfo *pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMMyInfo* pCookie = (callback_cookie_CMMyInfo *)env->GetIntField(
        thiz, gCMMyInfoFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMMyInfoFieldID.jniData, 0);
}

static jint CMMyInfo_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMMyInfo_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    extern fields_t gTDummyItemFieldID;
    TDummyItem* pItem = (TDummyItem*)env->GetIntField(item, gTDummyItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMMyInfo_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    extern fields_t gTDummyItemFieldID;
    TDummyItem* pItem = (TDummyItem*)env->GetIntField(obj, gTDummyItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMMyInfo_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    extern fields_t gTDummyItemFieldID;
    TDummyItem* pItem = (TDummyItem*)env->GetIntField(obj, gTDummyItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMMyInfo_IsEnd(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMMyInfo_RequestMore(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMMyInfo_IsRunning(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMMyInfo_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMMyInfo_Cancel(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMMyInfo_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMMyInfo_SetListener(JNIEnv* env, jobject thiz, jobject pListener, jobject pListener2)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    callback_cookie_CMMyInfo* pCookie = (callback_cookie_CMMyInfo *)env->GetIntField(
        thiz, gCMMyInfoFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMMyInfoFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gCMMyInfoFieldID.callback);
        }
        
        IMSimpleResultListener* para2 = NULL;
        if (pListener2 != NULL)
        {
            para2 = pCookie->listener2;
        }

    }
}

static jboolean CMMyInfo_UpheadPhoto(JNIEnv* env, jobject thiz, jstring filename)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->UpheadPhoto(pfilename);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

static jboolean CMMyInfo_UpdatePushInfo(JNIEnv* env, jobject thiz, jstring tags, jstring uid)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const jchar* jtags = env->GetStringChars(tags, NULL);
    jsize sizetags = env->GetStringLength(tags);
    char* ptags = UTF16toUTF8((jchar*)jtags, (size_t*)&sizetags);
    const jchar* juid = env->GetStringChars(uid, NULL);
    jsize sizeuid = env->GetStringLength(uid);
    char* puid = UTF16toUTF8((jchar*)juid, (size_t*)&sizeuid);
    BOOL ret = pObj->UpdatePushInfo(ptags, puid);
    env->ReleaseStringChars(tags, jtags);
    free(ptags);
    env->ReleaseStringChars(uid, juid);
    free(puid);
    return ret;
}

static jboolean CMMyInfo_UpdateData(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->UpdateData();
    return ret;
}

static jboolean CMMyInfo_CompareTags(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->CompareTags();
    return ret;
}

static jboolean CMMyInfo_CompareAlias(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->CompareAlias();
    return ret;
}

static jboolean CMMyInfo_ClearTagsAlias(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->ClearTagsAlias();
    return ret;
}

static jboolean CMMyInfo_isFetched(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->isFetched();
    return ret;
}

static jstring CMMyInfo_GetJobnumber(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetJobnumber();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMMyInfo_GetHeadimage(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetHeadimage();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMMyInfo_GetFullName(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetFullName();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMMyInfo_GetOrg(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetOrg();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMMyInfo_GetDep(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetDep();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMMyInfo_GetPosition(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetPosition();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMMyInfo_GetTitle(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetTitle();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMMyInfo_GetRankUrl(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetRankUrl();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMMyInfo_GetDetailUrl(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetDetailUrl();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMMyInfo_GetUid(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetUid();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMMyInfo_GetTags(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    const char* ret = pObj->GetTags();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jint CMMyInfo_GetLevel(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetLevel();
    return ret;
}

static jint CMMyInfo_GetValue(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetValue();
    return ret;
}

static jint CMMyInfo_GetCredit(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetCredit();
    return ret;
}

static jint CMMyInfo_GetStudyrecord(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetStudyrecord();
    return ret;
}

static jint CMMyInfo_GetPositionCourseCount(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetPositionCourseCount();
    return ret;
}

static jint CMMyInfo_GetCurrentminvalue(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetCurrentminvalue();
    return ret;
}

static jint CMMyInfo_GetNextvalue(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetNextvalue();
    return ret;
}

static jint CMMyInfo_GetUndoExam(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetUndoExam();
    return ret;
}

static jint CMMyInfo_GetWrongQa(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetWrongQa();
    return ret;
}

static jboolean CMMyInfo_SetWrongQa(JNIEnv* env, jobject thiz, jint count)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    BOOL ret = pObj->SetWrongQa(count);
    return ret;
}

static void CMMyInfo_SetPositionCourseCount(JNIEnv* env, jobject thiz, jint count)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    pObj->SetPositionCourseCount(count);
}

static void CMMyInfo_SetStudyrecord(JNIEnv* env, jobject thiz, jint count)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    pObj->SetStudyrecord(count);
}

static jint CMMyInfo_GetSex(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);

    int ret = pObj->GetSex();
    return ret;
}

static jint CMMyInfo_GetContributeValue(JNIEnv* env, jobject thiz)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nContributeValue;
}
                
static jboolean CMMyInfo_SetContributeValue(JNIEnv* env, jobject thiz, jint nContributeValue)
{
    CMMyInfo* pObj = (CMMyInfo*)env->GetIntField(thiz, gCMMyInfoFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nContributeValue = nContributeValue;
    return true;
}
                
int register_com_wunding_mlplayer_business_CMMyInfo(JNIEnv* env) {
    static JNINativeMethod CMMyInfoMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMMyInfo_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMMyInfo_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMMyInfo_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TDummyItem;)Z", (void*)CMMyInfo_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TDummyItem;)Z", (void*)CMMyInfo_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TDummyItem;)Z", (void*)CMMyInfo_Update },
        { "IsEnd", "()Z", (void*)CMMyInfo_IsEnd },
        { "RequestMore", "()Z", (void*)CMMyInfo_RequestMore },
        { "IsRunning", "()Z", (void*)CMMyInfo_IsRunning },
        { "IsRefresh", "()Z", (void*)CMMyInfo_IsRefresh },
        { "Cancel", "()V", (void*)CMMyInfo_Cancel },
        { "SetRequestType", "(I)V", (void*)CMMyInfo_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)CMMyInfo_SetListener },
        { "UpheadPhoto", "(Ljava/lang/String;)Z", (void*)CMMyInfo_UpheadPhoto },
        { "UpdatePushInfo", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMMyInfo_UpdatePushInfo },
        { "UpdateData", "()Z", (void*)CMMyInfo_UpdateData },
        { "CompareTags", "()Z", (void*)CMMyInfo_CompareTags },
        { "CompareAlias", "()Z", (void*)CMMyInfo_CompareAlias },
        { "ClearTagsAlias", "()Z", (void*)CMMyInfo_ClearTagsAlias },
        { "isFetched", "()Z", (void*)CMMyInfo_isFetched },
        { "GetJobnumber", "()Ljava/lang/String;", (void*)CMMyInfo_GetJobnumber },
        { "GetHeadimage", "()Ljava/lang/String;", (void*)CMMyInfo_GetHeadimage },
        { "GetFullName", "()Ljava/lang/String;", (void*)CMMyInfo_GetFullName },
        { "GetOrg", "()Ljava/lang/String;", (void*)CMMyInfo_GetOrg },
        { "GetDep", "()Ljava/lang/String;", (void*)CMMyInfo_GetDep },
        { "GetPosition", "()Ljava/lang/String;", (void*)CMMyInfo_GetPosition },
        { "GetTitle", "()Ljava/lang/String;", (void*)CMMyInfo_GetTitle },
        { "GetRankUrl", "()Ljava/lang/String;", (void*)CMMyInfo_GetRankUrl },
        { "GetDetailUrl", "()Ljava/lang/String;", (void*)CMMyInfo_GetDetailUrl },
        { "GetUid", "()Ljava/lang/String;", (void*)CMMyInfo_GetUid },
        { "GetTags", "()Ljava/lang/String;", (void*)CMMyInfo_GetTags },
        { "GetLevel", "()I", (void*)CMMyInfo_GetLevel },
        { "GetValue", "()I", (void*)CMMyInfo_GetValue },
        { "GetCredit", "()I", (void*)CMMyInfo_GetCredit },
        { "GetStudyrecord", "()I", (void*)CMMyInfo_GetStudyrecord },
        { "GetPositionCourseCount", "()I", (void*)CMMyInfo_GetPositionCourseCount },
        { "GetCurrentminvalue", "()I", (void*)CMMyInfo_GetCurrentminvalue },
        { "GetNextvalue", "()I", (void*)CMMyInfo_GetNextvalue },
        { "GetUndoExam", "()I", (void*)CMMyInfo_GetUndoExam },
        { "GetWrongQa", "()I", (void*)CMMyInfo_GetWrongQa },
        { "SetWrongQa", "(I)Z", (void*)CMMyInfo_SetWrongQa },
        { "SetPositionCourseCount", "(I)V", (void*)CMMyInfo_SetPositionCourseCount },
        { "SetStudyrecord", "(I)V", (void*)CMMyInfo_SetStudyrecord },
        { "GetSex", "()I", (void*)CMMyInfo_GetSex },
        { "GetContributeValue", "()I", (void*)CMMyInfo_GetContributeValue },
        { "SetContributeValue", "(I)Z", (void*)CMMyInfo_SetContributeValue }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMMyInfo");
    if (clazz == 0) {
        CM_ERR("class CMMyInfo no found");
        return -1;
    }

    gCMMyInfoFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMMyInfoFieldID.nativeJavaObj == 0) {
        CM_ERR("CMMyInfo no found mNativeObj");
        return -1;
    }

    gCMMyInfoFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMMyInfoFieldID.jniData == 0) {
        CM_ERR("CMMyInfo no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMMyInfoFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMMyInfoFieldID.callback == NULL) {
        CM_ERR("CMMyInfo no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMMyInfoMethods,
            sizeof(CMMyInfoMethods) / sizeof(CMMyInfoMethods[0]));
}


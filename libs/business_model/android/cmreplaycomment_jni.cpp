// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmreplaycomment_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmreplaycomment.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTRepalymentItemFieldID;

static void TRepalymentItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TRepalymentItem* pObj = new TRepalymentItem();

    env->SetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj, (int)pObj);
}

static void TRepalymentItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
}

static jstring TRepalymentItem_GetUsername(JNIEnv* env, jobject thiz)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sUsername);
    jchar* data = UTF8toUTF16((char*)pObj->sUsername, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TRepalymentItem_SetUsername(JNIEnv* env, jobject thiz, jstring sUsername)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sUsername, NULL);
    jsize size = env->GetStringLength(sUsername);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sUsername, (const char*)data, 31);
    pObj->sUsername[31] = '\0';

    env->ReleaseStringChars(sUsername, jChar);
    
    free(data);
    
    return true;
}

static jstring TRepalymentItem_GetFullName(JNIEnv* env, jobject thiz)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sFullName);
    jchar* data = UTF8toUTF16((char*)pObj->sFullName, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TRepalymentItem_SetFullName(JNIEnv* env, jobject thiz, jstring sFullName)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sFullName, NULL);
    jsize size = env->GetStringLength(sFullName);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sFullName, (const char*)data, 31);
    pObj->sFullName[31] = '\0';

    env->ReleaseStringChars(sFullName, jChar);
    
    free(data);
    
    return true;
}

static jstring TRepalymentItem_GetHeadImage(JNIEnv* env, jobject thiz)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sHeadImage);
    jchar* data = UTF8toUTF16((char*)pObj->sHeadImage, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TRepalymentItem_SetHeadImage(JNIEnv* env, jobject thiz, jstring sHeadImage)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sHeadImage, NULL);
    jsize size = env->GetStringLength(sHeadImage);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sHeadImage, (const char*)data, 299);
    pObj->sHeadImage[299] = '\0';

    env->ReleaseStringChars(sHeadImage, jChar);
    
    free(data);
    
    return true;
}

static jstring TRepalymentItem_GetDepartment(JNIEnv* env, jobject thiz)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDepartment);
    jchar* data = UTF8toUTF16((char*)pObj->sDepartment, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TRepalymentItem_SetDepartment(JNIEnv* env, jobject thiz, jstring sDepartment)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDepartment, NULL);
    jsize size = env->GetStringLength(sDepartment);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sDepartment, (const char*)data, 99);
    pObj->sDepartment[99] = '\0';

    env->ReleaseStringChars(sDepartment, jChar);
    
    free(data);
    
    return true;
}

static jstring TRepalymentItem_GetDatetime(JNIEnv* env, jobject thiz)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDatetime);
    jchar* data = UTF8toUTF16((char*)pObj->sDatetime, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TRepalymentItem_SetDatetime(JNIEnv* env, jobject thiz, jstring sDatetime)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDatetime, NULL);
    jsize size = env->GetStringLength(sDatetime);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sDatetime, (const char*)data, 19);
    pObj->sDatetime[19] = '\0';

    env->ReleaseStringChars(sDatetime, jChar);
    
    free(data);
    
    return true;
}

static jstring TRepalymentItem_GetComment(JNIEnv* env, jobject thiz)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sComment.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sComment.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TRepalymentItem_SetComment(JNIEnv* env, jobject thiz, jstring sComment)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sComment, NULL);
    jsize size = env->GetStringLength(sComment);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sComment = data;

    env->ReleaseStringChars(sComment, jChar);
    
    free(data);
    
    return true;
}

static jstring TRepalymentItem_GetID(JNIEnv* env, jobject thiz)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID);
    jchar* data = UTF8toUTF16((char*)pObj->sID, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TRepalymentItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
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

static jint TRepalymentItem_Getreply(JNIEnv* env, jobject thiz)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nreply;
}
                
static jboolean TRepalymentItem_Setreply(JNIEnv* env, jobject thiz, jint nreply)
{
    TRepalymentItem* pObj = (TRepalymentItem*)env->GetIntField(thiz, gTRepalymentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nreply = nreply;
    return true;
}
                
int register_com_wunding_mlplayer_business_TRepalymentItem(JNIEnv* env) {
    static JNINativeMethod TRepalymentItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TRepalymentItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TRepalymentItem_nativeDestructor },
        { "GetUsername", "()Ljava/lang/String;", (void*)TRepalymentItem_GetUsername },
        { "SetUsername", "(Ljava/lang/String;)Z", (void*)TRepalymentItem_SetUsername },
        { "GetFullName", "()Ljava/lang/String;", (void*)TRepalymentItem_GetFullName },
        { "SetFullName", "(Ljava/lang/String;)Z", (void*)TRepalymentItem_SetFullName },
        { "GetHeadImage", "()Ljava/lang/String;", (void*)TRepalymentItem_GetHeadImage },
        { "SetHeadImage", "(Ljava/lang/String;)Z", (void*)TRepalymentItem_SetHeadImage },
        { "GetDepartment", "()Ljava/lang/String;", (void*)TRepalymentItem_GetDepartment },
        { "SetDepartment", "(Ljava/lang/String;)Z", (void*)TRepalymentItem_SetDepartment },
        { "GetDatetime", "()Ljava/lang/String;", (void*)TRepalymentItem_GetDatetime },
        { "SetDatetime", "(Ljava/lang/String;)Z", (void*)TRepalymentItem_SetDatetime },
        { "GetComment", "()Ljava/lang/String;", (void*)TRepalymentItem_GetComment },
        { "SetComment", "(Ljava/lang/String;)Z", (void*)TRepalymentItem_SetComment },
        { "GetID", "()Ljava/lang/String;", (void*)TRepalymentItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TRepalymentItem_SetID },
        { "Getreply", "()I", (void*)TRepalymentItem_Getreply },
        { "Setreply", "(I)Z", (void*)TRepalymentItem_Setreply }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TRepalymentItem");
    if (clazz == 0) {
        CM_ERR("class TRepalymentItem no found");
        return -1;
    }

    gTRepalymentItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTRepalymentItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TRepalymentItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TRepalymentItemMethods,
            sizeof(TRepalymentItemMethods) / sizeof(TRepalymentItemMethods[0]));
}


struct callback_cookie_CMRepalycomment {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gCMRepalycommentFieldID;

static void CMRepalycomment_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMRepalycomment when setting up callback.");
        return;
    }
    callback_cookie_CMRepalycomment* pCookie = new callback_cookie_CMRepalycomment;
    pCookie->listener1 = new CMUpdateDataListener(gCMRepalycommentFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gCMRepalycommentFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMRepalycommentFieldID.jniData, (int)pCookie);

    CMRepalycomment* pObj = new CMRepalycomment(pCookie->listener1, pCookie->listener2);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMRepalycommentFieldID.nativeJavaObj, (int)pObj);
}

static void CMRepalycomment_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMRepalycomment *pObj = (CMRepalycomment*)env->GetIntField(thiz, gCMRepalycommentFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMRepalycomment* pCookie = (callback_cookie_CMRepalycomment *)env->GetIntField(
        thiz, gCMRepalycommentFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMRepalycommentFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMRepalycommentFieldID.jniData, 0);
}

static jboolean CMRepalycomment_ReplyComment(JNIEnv* env, jobject thiz, jstring sFlag, jstring ClassID, jstring CoursewareID, jstring sReplyID, jstring sContent)
{
    CMRepalycomment* pObj = (CMRepalycomment*)env->GetIntField(thiz, gCMRepalycommentFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jClassID = env->GetStringChars(ClassID, NULL);
    jsize sizeClassID = env->GetStringLength(ClassID);
    char* pClassID = UTF16toUTF8((jchar*)jClassID, (size_t*)&sizeClassID);
    const jchar* jCoursewareID = env->GetStringChars(CoursewareID, NULL);
    jsize sizeCoursewareID = env->GetStringLength(CoursewareID);
    char* pCoursewareID = UTF16toUTF8((jchar*)jCoursewareID, (size_t*)&sizeCoursewareID);
    const jchar* jsReplyID = env->GetStringChars(sReplyID, NULL);
    jsize sizesReplyID = env->GetStringLength(sReplyID);
    char* psReplyID = UTF16toUTF8((jchar*)jsReplyID, (size_t*)&sizesReplyID);
    const jchar* jsContent = env->GetStringChars(sContent, NULL);
    jsize sizesContent = env->GetStringLength(sContent);
    char* psContent = UTF16toUTF8((jchar*)jsContent, (size_t*)&sizesContent);
    BOOL ret = pObj->ReplyComment(psFlag, pClassID, pCoursewareID, psReplyID, psContent);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(ClassID, jClassID);
    free(pClassID);
    env->ReleaseStringChars(CoursewareID, jCoursewareID);
    free(pCoursewareID);
    env->ReleaseStringChars(sReplyID, jsReplyID);
    free(psReplyID);
    env->ReleaseStringChars(sContent, jsContent);
    free(psContent);
    return ret;
}

static jboolean CMRepalycomment_RequestRepalyCommentList(JNIEnv* env, jobject thiz, jstring sFlag, jstring sID)
{
    CMRepalycomment* pObj = (CMRepalycomment*)env->GetIntField(thiz, gCMRepalycommentFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jsID = env->GetStringChars(sID, NULL);
    jsize sizesID = env->GetStringLength(sID);
    char* psID = UTF16toUTF8((jchar*)jsID, (size_t*)&sizesID);
    BOOL ret = pObj->RequestRepalyCommentList(psFlag, psID);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(sID, jsID);
    free(psID);
    return ret;
}

static jboolean CMRepalycomment_RequestMore(JNIEnv* env, jobject thiz)
{
    CMRepalycomment* pObj = (CMRepalycomment*)env->GetIntField(thiz, gCMRepalycommentFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jint CMRepalycomment_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMRepalycomment* pObj = (CMRepalycomment*)env->GetIntField(thiz, gCMRepalycommentFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMRepalycomment_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMRepalycomment* pObj = (CMRepalycomment*)env->GetIntField(thiz, gCMRepalycommentFieldID.nativeJavaObj);

    extern fields_t gTRepalymentItemFieldID;
    TRepalymentItem* pItem = (TRepalymentItem*)env->GetIntField(item, gTRepalymentItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static void CMRepalycomment_Cancel(JNIEnv* env, jobject thiz)
{
    CMRepalycomment* pObj = (CMRepalycomment*)env->GetIntField(thiz, gCMRepalycommentFieldID.nativeJavaObj);

    pObj->Cancel();
}

static jboolean CMRepalycomment_IsEnd(JNIEnv* env, jobject thiz)
{
    CMRepalycomment* pObj = (CMRepalycomment*)env->GetIntField(thiz, gCMRepalycommentFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

int register_com_wunding_mlplayer_business_CMRepalycomment(JNIEnv* env) {
    static JNINativeMethod CMRepalycommentMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMRepalycomment_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMRepalycomment_nativeDestructor },
        { "ReplyComment", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMRepalycomment_ReplyComment },
        { "RequestRepalyCommentList", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMRepalycomment_RequestRepalyCommentList },
        { "RequestMore", "()Z", (void*)CMRepalycomment_RequestMore },
        { "GetItemCount", "()I", (void*)CMRepalycomment_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TRepalymentItem;)Z", (void*)CMRepalycomment_GetItem },
        { "Cancel", "()V", (void*)CMRepalycomment_Cancel },
        { "IsEnd", "()Z", (void*)CMRepalycomment_IsEnd }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMRepalycomment");
    if (clazz == 0) {
        CM_ERR("class CMRepalycomment no found");
        return -1;
    }

    gCMRepalycommentFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMRepalycommentFieldID.nativeJavaObj == 0) {
        CM_ERR("CMRepalycomment no found mNativeObj");
        return -1;
    }

    gCMRepalycommentFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMRepalycommentFieldID.jniData == 0) {
        CM_ERR("CMRepalycomment no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMRepalycommentFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMRepalycommentFieldID.callback == NULL) {
        CM_ERR("CMRepalycomment no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMRepalycommentMethods,
            sizeof(CMRepalycommentMethods) / sizeof(CMRepalycommentMethods[0]));
}


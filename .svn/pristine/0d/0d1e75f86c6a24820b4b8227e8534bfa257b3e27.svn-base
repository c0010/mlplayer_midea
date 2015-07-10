// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmcommon_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmcommon.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTCommentItemFieldID;

static void TCommentItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = new TCommentItem();

    env->SetIntField(thiz, gTCommentItemFieldID.nativeJavaObj, (int)pObj);
}

static void TCommentItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
}

static jobject TCommentItem_CopyFromTCommentItem(JNIEnv* env, jobject thiz, jobject right)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);

    extern fields_t gTCommentItemFieldID;
    TCommentItem* pObjCopy = (TCommentItem*)env->GetIntField(right, gTCommentItemFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static jboolean TCommentItem_GetChildItem(JNIEnv* env, jobject thiz, jint index, jobject item)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);

    extern fields_t gTCommentItemFieldID;
    TCommentItem* pItem = (TCommentItem*)env->GetIntField(item, gTCommentItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetChildItem(index, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jint TCommentItem_GetChildItemCount(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);

    int ret = pObj->GetChildItemCount();
    return ret;
}

static jstring TCommentItem_GetUsername(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sUsername);
    jchar* data = UTF8toUTF16((char*)pObj->sUsername, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCommentItem_SetUsername(JNIEnv* env, jobject thiz, jstring sUsername)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
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

static jstring TCommentItem_GetFullName(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sFullName);
    jchar* data = UTF8toUTF16((char*)pObj->sFullName, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCommentItem_SetFullName(JNIEnv* env, jobject thiz, jstring sFullName)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
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

static jstring TCommentItem_GetHeadImage(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sHeadImage);
    jchar* data = UTF8toUTF16((char*)pObj->sHeadImage, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCommentItem_SetHeadImage(JNIEnv* env, jobject thiz, jstring sHeadImage)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
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

static jstring TCommentItem_GetDepartment(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDepartment);
    jchar* data = UTF8toUTF16((char*)pObj->sDepartment, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCommentItem_SetDepartment(JNIEnv* env, jobject thiz, jstring sDepartment)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
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

static jstring TCommentItem_GetDatetime(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDatetime);
    jchar* data = UTF8toUTF16((char*)pObj->sDatetime, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCommentItem_SetDatetime(JNIEnv* env, jobject thiz, jstring sDatetime)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
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

static jstring TCommentItem_GetComment(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sComment.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sComment.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCommentItem_SetComment(JNIEnv* env, jobject thiz, jstring sComment)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sComment, NULL);
    jsize size = env->GetStringLength(sComment);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sComment = data;

    env->ReleaseStringChars(sComment, jChar);
    
    free(data);
    
    return true;
}

static jstring TCommentItem_GetID(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID);
    jchar* data = UTF8toUTF16((char*)pObj->sID, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCommentItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
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

static jint TCommentItem_Getpv(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->npv;
}
                
static jboolean TCommentItem_Setpv(JNIEnv* env, jobject thiz, jint npv)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->npv = npv;
    return true;
}
                
static jint TCommentItem_Getreply(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nreply;
}
                
static jboolean TCommentItem_Setreply(JNIEnv* env, jobject thiz, jint nreply)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nreply = nreply;
    return true;
}
                
static jboolean TCommentItem_GetIsLiked(JNIEnv* env, jobject thiz)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bIsLiked;
}
                
static jboolean TCommentItem_SetIsLiked(JNIEnv* env, jobject thiz, jboolean bIsLiked)
{
    TCommentItem* pObj = (TCommentItem*)env->GetIntField(thiz, gTCommentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bIsLiked = bIsLiked;
    return true;
}
                
int register_com_wunding_mlplayer_business_TCommentItem(JNIEnv* env) {
    static JNINativeMethod TCommentItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TCommentItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TCommentItem_nativeDestructor },
        { "CopyFromTCommentItem", "(Lcom/wunding/mlplayer/business/TCommentItem;)Lcom/wunding/mlplayer/business/TCommentItem;", (void*)TCommentItem_CopyFromTCommentItem },
        { "GetChildItem", "(ILcom/wunding/mlplayer/business/TCommentItem;)Z", (void*)TCommentItem_GetChildItem },
        { "GetChildItemCount", "()I", (void*)TCommentItem_GetChildItemCount },
        { "GetUsername", "()Ljava/lang/String;", (void*)TCommentItem_GetUsername },
        { "SetUsername", "(Ljava/lang/String;)Z", (void*)TCommentItem_SetUsername },
        { "GetFullName", "()Ljava/lang/String;", (void*)TCommentItem_GetFullName },
        { "SetFullName", "(Ljava/lang/String;)Z", (void*)TCommentItem_SetFullName },
        { "GetHeadImage", "()Ljava/lang/String;", (void*)TCommentItem_GetHeadImage },
        { "SetHeadImage", "(Ljava/lang/String;)Z", (void*)TCommentItem_SetHeadImage },
        { "GetDepartment", "()Ljava/lang/String;", (void*)TCommentItem_GetDepartment },
        { "SetDepartment", "(Ljava/lang/String;)Z", (void*)TCommentItem_SetDepartment },
        { "GetDatetime", "()Ljava/lang/String;", (void*)TCommentItem_GetDatetime },
        { "SetDatetime", "(Ljava/lang/String;)Z", (void*)TCommentItem_SetDatetime },
        { "GetComment", "()Ljava/lang/String;", (void*)TCommentItem_GetComment },
        { "SetComment", "(Ljava/lang/String;)Z", (void*)TCommentItem_SetComment },
        { "GetID", "()Ljava/lang/String;", (void*)TCommentItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TCommentItem_SetID },
        { "Getpv", "()I", (void*)TCommentItem_Getpv },
        { "Setpv", "(I)Z", (void*)TCommentItem_Setpv },
        { "Getreply", "()I", (void*)TCommentItem_Getreply },
        { "Setreply", "(I)Z", (void*)TCommentItem_Setreply },
        { "GetIsLiked", "()Z", (void*)TCommentItem_GetIsLiked },
        { "SetIsLiked", "(Z)Z", (void*)TCommentItem_SetIsLiked }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TCommentItem");
    if (clazz == 0) {
        CM_ERR("class TCommentItem no found");
        return -1;
    }

    gTCommentItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTCommentItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TCommentItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TCommentItemMethods,
            sizeof(TCommentItemMethods) / sizeof(TCommentItemMethods[0]));
}


struct callback_cookie_TBrowserItem {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMRatingListener* listener2;
    CMSimpleResultListener* listener3;
};

fields_t gTBrowserItemFieldID;

static void TBrowserItem_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find TBrowserItem when setting up callback.");
        return;
    }
    callback_cookie_TBrowserItem* pCookie = new callback_cookie_TBrowserItem;
    pCookie->listener1 = new CMUpdateDataListener(gTBrowserItemFieldID.callback);
    pCookie->listener2 = new CMRatingListener(gTBrowserItemFieldID.callback);
    pCookie->listener3 = new CMSimpleResultListener(gTBrowserItemFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gTBrowserItemFieldID.jniData, (int)pCookie);

    TBrowserItem* pObj = new TBrowserItem();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj, (int)pObj);
}

static void TBrowserItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    TBrowserItem *pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_TBrowserItem* pCookie = (callback_cookie_TBrowserItem *)env->GetIntField(
        thiz, gTBrowserItemFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie->listener3;
        delete pCookie;
    }

    env->SetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gTBrowserItemFieldID.jniData, 0);
}

static jobject TBrowserItem_CopyFromTBrowserItem(JNIEnv* env, jobject thiz, jobject right)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);

    extern fields_t gTBrowserItemFieldID;
    TBrowserItem* pObjCopy = (TBrowserItem*)env->GetIntField(right, gTBrowserItemFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static jboolean TBrowserItem_Refresh(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);

    BOOL ret = pObj->Refresh();
    return ret;
}

static jboolean TBrowserItem_Update(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);

    BOOL ret = pObj->Update();
    return ret;
}

static void TBrowserItem_Cancel(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);

    pObj->Cancel();
}

static jboolean TBrowserItem_SendComment(JNIEnv* env, jobject thiz, jstring sContent, jboolean bsyncqa)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);

    const jchar* jsContent = env->GetStringChars(sContent, NULL);
    jsize sizesContent = env->GetStringLength(sContent);
    char* psContent = UTF16toUTF8((jchar*)jsContent, (size_t*)&sizesContent);
    BOOL ret = pObj->SendComment(psContent, bsyncqa);
    env->ReleaseStringChars(sContent, jsContent);
    free(psContent);
    return ret;
}

static void TBrowserItem_SetListener(JNIEnv* env, jobject thiz, jobject pUpdateDataListener, jobject pRatingListener, jobject pSimpleListener)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);

    callback_cookie_TBrowserItem* pCookie = (callback_cookie_TBrowserItem *)env->GetIntField(
        thiz, gTBrowserItemFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gTBrowserItemFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pUpdateDataListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMRatingListener(gTBrowserItemFieldID.callback);
        }
        
        IMRatingListener* para2 = NULL;
        if (pRatingListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        if (pCookie->listener3 == NULL)
        {
            pCookie->listener3 = new CMSimpleResultListener(gTBrowserItemFieldID.callback);
        }
        
        IMSimpleResultListener* para3 = NULL;
        if (pSimpleListener != NULL)
        {
            para3 = pCookie->listener3;
        }

        pObj->SetListener(para1, para2, para3);
    }

    return ;
}

static jboolean TBrowserItem_Rating(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);

    BOOL ret = pObj->Rating();
    return ret;
}

static jboolean TBrowserItem_RatingCourseinfo(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);

    BOOL ret = pObj->RatingCourseinfo();
    return ret;
}

static jstring TBrowserItem_GetID(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID);
    jchar* data = UTF8toUTF16((char*)pObj->sID, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
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

static jstring TBrowserItem_GetFlag(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sFlag);
    jchar* data = UTF8toUTF16((char*)pObj->sFlag, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetFlag(JNIEnv* env, jobject thiz, jstring sFlag)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sFlag, NULL);
    jsize size = env->GetStringLength(sFlag);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sFlag, (const char*)data, 15);
    pObj->sFlag[15] = '\0';

    env->ReleaseStringChars(sFlag, jChar);
    
    free(data);
    
    return true;
}

static jstring TBrowserItem_GetTitle(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle);
    jchar* data = UTF8toUTF16((char*)pObj->sTitle, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
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

static jstring TBrowserItem_GetBrief(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sBrief);
    jchar* data = UTF8toUTF16((char*)pObj->sBrief, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetBrief(JNIEnv* env, jobject thiz, jstring sBrief)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sBrief, NULL);
    jsize size = env->GetStringLength(sBrief);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sBrief, (const char*)data, 119);
    pObj->sBrief[119] = '\0';

    env->ReleaseStringChars(sBrief, jChar);
    
    free(data);
    
    return true;
}

static jstring TBrowserItem_GetLargeimage(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sLargeimage);
    jchar* data = UTF8toUTF16((char*)pObj->sLargeimage, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetLargeimage(JNIEnv* env, jobject thiz, jstring sLargeimage)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sLargeimage, NULL);
    jsize size = env->GetStringLength(sLargeimage);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sLargeimage, (const char*)data, 299);
    pObj->sLargeimage[299] = '\0';

    env->ReleaseStringChars(sLargeimage, jChar);
    
    free(data);
    
    return true;
}

static jstring TBrowserItem_GetImage(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sImage);
    jchar* data = UTF8toUTF16((char*)pObj->sImage, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetImage(JNIEnv* env, jobject thiz, jstring sImage)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sImage, NULL);
    jsize size = env->GetStringLength(sImage);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sImage, (const char*)data, 299);
    pObj->sImage[299] = '\0';

    env->ReleaseStringChars(sImage, jChar);
    
    free(data);
    
    return true;
}

static jstring TBrowserItem_GetThumbs(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sThumbs);
    jchar* data = UTF8toUTF16((char*)pObj->sThumbs, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetThumbs(JNIEnv* env, jobject thiz, jstring sThumbs)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sThumbs, NULL);
    jsize size = env->GetStringLength(sThumbs);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sThumbs, (const char*)data, 299);
    pObj->sThumbs[299] = '\0';

    env->ReleaseStringChars(sThumbs, jChar);
    
    free(data);
    
    return true;
}

static jstring TBrowserItem_GetType(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sType);
    jchar* data = UTF8toUTF16((char*)pObj->sType, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetType(JNIEnv* env, jobject thiz, jstring sType)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sType, NULL);
    jsize size = env->GetStringLength(sType);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sType, (const char*)data, 63);
    pObj->sType[63] = '\0';

    env->ReleaseStringChars(sType, jChar);
    
    free(data);
    
    return true;
}

static jint TBrowserItem_GetCoursewarecount(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nCoursewarecount;
}
                
static jboolean TBrowserItem_SetCoursewarecount(JNIEnv* env, jobject thiz, jint nCoursewarecount)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nCoursewarecount = nCoursewarecount;
    return true;
}
                
static jstring TBrowserItem_GetUrl(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sUrl);
    jchar* data = UTF8toUTF16((char*)pObj->sUrl, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetUrl(JNIEnv* env, jobject thiz, jstring sUrl)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sUrl, NULL);
    jsize size = env->GetStringLength(sUrl);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sUrl, (const char*)data, 299);
    pObj->sUrl[299] = '\0';

    env->ReleaseStringChars(sUrl, jChar);
    
    free(data);
    
    return true;
}

static jstring TBrowserItem_GetPubdate(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPubdate);
    jchar* data = UTF8toUTF16((char*)pObj->sPubdate, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetPubdate(JNIEnv* env, jobject thiz, jstring sPubdate)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPubdate, NULL);
    jsize size = env->GetStringLength(sPubdate);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sPubdate, (const char*)data, 99);
    pObj->sPubdate[99] = '\0';

    env->ReleaseStringChars(sPubdate, jChar);
    
    free(data);
    
    return true;
}

static jint TBrowserItem_GetVC(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nVC;
}
                
static jboolean TBrowserItem_SetVC(JNIEnv* env, jobject thiz, jint nVC)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nVC = nVC;
    return true;
}
                
static jint TBrowserItem_GetPV(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nPV;
}
                
static jboolean TBrowserItem_SetPV(JNIEnv* env, jobject thiz, jint nPV)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nPV = nPV;
    return true;
}
                
static jint TBrowserItem_GetCommentcount(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nCommentcount;
}
                
static jboolean TBrowserItem_SetCommentcount(JNIEnv* env, jobject thiz, jint nCommentcount)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nCommentcount = nCommentcount;
    return true;
}
                
static jboolean TBrowserItem_GetEnablecomment(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bEnablecomment;
}
                
static jboolean TBrowserItem_SetEnablecomment(JNIEnv* env, jobject thiz, jboolean bEnablecomment)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bEnablecomment = bEnablecomment;
    return true;
}
                
static jboolean TBrowserItem_GetEnabledownload(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bEnabledownload;
}
                
static jboolean TBrowserItem_SetEnabledownload(JNIEnv* env, jobject thiz, jboolean bEnabledownload)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bEnabledownload = bEnabledownload;
    return true;
}
                
static jboolean TBrowserItem_GetEnablerating(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bEnablerating;
}
                
static jboolean TBrowserItem_SetEnablerating(JNIEnv* env, jobject thiz, jboolean bEnablerating)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bEnablerating = bEnablerating;
    return true;
}
                
static jboolean TBrowserItem_GetEnableShare(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bEnableShare;
}
                
static jboolean TBrowserItem_SetEnableShare(JNIEnv* env, jobject thiz, jboolean bEnableShare)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bEnableShare = bEnableShare;
    return true;
}
                
static jstring TBrowserItem_GetDescription(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDescription);
    jchar* data = UTF8toUTF16((char*)pObj->sDescription, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetDescription(JNIEnv* env, jobject thiz, jstring sDescription)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDescription, NULL);
    jsize size = env->GetStringLength(sDescription);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sDescription, (const char*)data, 449);
    pObj->sDescription[449] = '\0';

    env->ReleaseStringChars(sDescription, jChar);
    
    free(data);
    
    return true;
}

static jstring TBrowserItem_GetTag(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTag);
    jchar* data = UTF8toUTF16((char*)pObj->sTag, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetTag(JNIEnv* env, jobject thiz, jstring sTag)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTag, NULL);
    jsize size = env->GetStringLength(sTag);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sTag, (const char*)data, 63);
    pObj->sTag[63] = '\0';

    env->ReleaseStringChars(sTag, jChar);
    
    free(data);
    
    return true;
}

static jstring TBrowserItem_GetFavoritedate(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sFavoritedate);
    jchar* data = UTF8toUTF16((char*)pObj->sFavoritedate, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetFavoritedate(JNIEnv* env, jobject thiz, jstring sFavoritedate)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sFavoritedate, NULL);
    jsize size = env->GetStringLength(sFavoritedate);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sFavoritedate, (const char*)data, 19);
    pObj->sFavoritedate[19] = '\0';

    env->ReleaseStringChars(sFavoritedate, jChar);
    
    free(data);
    
    return true;
}

static jboolean TBrowserItem_GetMyCompany(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bMyCompany;
}
                
static jboolean TBrowserItem_SetMyCompany(JNIEnv* env, jobject thiz, jboolean bMyCompany)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bMyCompany = bMyCompany;
    return true;
}
                
static jboolean TBrowserItem_GetIsRated(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bIsRated;
}
                
static jboolean TBrowserItem_SetIsRated(JNIEnv* env, jobject thiz, jboolean bIsRated)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bIsRated = bIsRated;
    return true;
}
                
static jint TBrowserItem_GetModel(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nModel;
}
                
static jboolean TBrowserItem_SetModel(JNIEnv* env, jobject thiz, jint nModel)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nModel = nModel;
    return true;
}
                
static jstring TBrowserItem_GetMarkID(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sMarkID);
    jchar* data = UTF8toUTF16((char*)pObj->sMarkID, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetMarkID(JNIEnv* env, jobject thiz, jstring sMarkID)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sMarkID, NULL);
    jsize size = env->GetStringLength(sMarkID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sMarkID, (const char*)data, 63);
    pObj->sMarkID[63] = '\0';

    env->ReleaseStringChars(sMarkID, jChar);
    
    free(data);
    
    return true;
}

static jstring TBrowserItem_GetMarkTitle(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sMarkTitle);
    jchar* data = UTF8toUTF16((char*)pObj->sMarkTitle, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetMarkTitle(JNIEnv* env, jobject thiz, jstring sMarkTitle)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sMarkTitle, NULL);
    jsize size = env->GetStringLength(sMarkTitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sMarkTitle, (const char*)data, 19);
    pObj->sMarkTitle[19] = '\0';

    env->ReleaseStringChars(sMarkTitle, jChar);
    
    free(data);
    
    return true;
}

static jstring TBrowserItem_GetMarkPicUrl(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sMarkPicUrl);
    jchar* data = UTF8toUTF16((char*)pObj->sMarkPicUrl, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TBrowserItem_SetMarkPicUrl(JNIEnv* env, jobject thiz, jstring sMarkPicUrl)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sMarkPicUrl, NULL);
    jsize size = env->GetStringLength(sMarkPicUrl);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sMarkPicUrl, (const char*)data, 299);
    pObj->sMarkPicUrl[299] = '\0';

    env->ReleaseStringChars(sMarkPicUrl, jChar);
    
    free(data);
    
    return true;
}

static jboolean TBrowserItem_GetIsHeadItem(JNIEnv* env, jobject thiz)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bIsHeadItem;
}
                
static jboolean TBrowserItem_SetIsHeadItem(JNIEnv* env, jobject thiz, jboolean bIsHeadItem)
{
    TBrowserItem* pObj = (TBrowserItem*)env->GetIntField(thiz, gTBrowserItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bIsHeadItem = bIsHeadItem;
    return true;
}
                
int register_com_wunding_mlplayer_business_TBrowserItem(JNIEnv* env) {
    static JNINativeMethod TBrowserItemMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)TBrowserItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TBrowserItem_nativeDestructor },
        { "CopyFromTBrowserItem", "(Lcom/wunding/mlplayer/business/TBrowserItem;)Lcom/wunding/mlplayer/business/TBrowserItem;", (void*)TBrowserItem_CopyFromTBrowserItem },
        { "Refresh", "()Z", (void*)TBrowserItem_Refresh },
        { "Update", "()Z", (void*)TBrowserItem_Update },
        { "Cancel", "()V", (void*)TBrowserItem_Cancel },
        { "SendComment", "(Ljava/lang/String;Z)Z", (void*)TBrowserItem_SendComment },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)V", (void*)TBrowserItem_SetListener },
        { "Rating", "()Z", (void*)TBrowserItem_Rating },
        { "RatingCourseinfo", "()Z", (void*)TBrowserItem_RatingCourseinfo },
        { "GetID", "()Ljava/lang/String;", (void*)TBrowserItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetID },
        { "GetFlag", "()Ljava/lang/String;", (void*)TBrowserItem_GetFlag },
        { "SetFlag", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetFlag },
        { "GetTitle", "()Ljava/lang/String;", (void*)TBrowserItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetTitle },
        { "GetBrief", "()Ljava/lang/String;", (void*)TBrowserItem_GetBrief },
        { "SetBrief", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetBrief },
        { "GetLargeimage", "()Ljava/lang/String;", (void*)TBrowserItem_GetLargeimage },
        { "SetLargeimage", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetLargeimage },
        { "GetImage", "()Ljava/lang/String;", (void*)TBrowserItem_GetImage },
        { "SetImage", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetImage },
        { "GetThumbs", "()Ljava/lang/String;", (void*)TBrowserItem_GetThumbs },
        { "SetThumbs", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetThumbs },
        { "GetType", "()Ljava/lang/String;", (void*)TBrowserItem_GetType },
        { "SetType", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetType },
        { "GetCoursewarecount", "()I", (void*)TBrowserItem_GetCoursewarecount },
        { "SetCoursewarecount", "(I)Z", (void*)TBrowserItem_SetCoursewarecount },
        { "GetUrl", "()Ljava/lang/String;", (void*)TBrowserItem_GetUrl },
        { "SetUrl", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetUrl },
        { "GetPubdate", "()Ljava/lang/String;", (void*)TBrowserItem_GetPubdate },
        { "SetPubdate", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetPubdate },
        { "GetVC", "()I", (void*)TBrowserItem_GetVC },
        { "SetVC", "(I)Z", (void*)TBrowserItem_SetVC },
        { "GetPV", "()I", (void*)TBrowserItem_GetPV },
        { "SetPV", "(I)Z", (void*)TBrowserItem_SetPV },
        { "GetCommentcount", "()I", (void*)TBrowserItem_GetCommentcount },
        { "SetCommentcount", "(I)Z", (void*)TBrowserItem_SetCommentcount },
        { "GetEnablecomment", "()Z", (void*)TBrowserItem_GetEnablecomment },
        { "SetEnablecomment", "(Z)Z", (void*)TBrowserItem_SetEnablecomment },
        { "GetEnabledownload", "()Z", (void*)TBrowserItem_GetEnabledownload },
        { "SetEnabledownload", "(Z)Z", (void*)TBrowserItem_SetEnabledownload },
        { "GetEnablerating", "()Z", (void*)TBrowserItem_GetEnablerating },
        { "SetEnablerating", "(Z)Z", (void*)TBrowserItem_SetEnablerating },
        { "GetEnableShare", "()Z", (void*)TBrowserItem_GetEnableShare },
        { "SetEnableShare", "(Z)Z", (void*)TBrowserItem_SetEnableShare },
        { "GetDescription", "()Ljava/lang/String;", (void*)TBrowserItem_GetDescription },
        { "SetDescription", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetDescription },
        { "GetTag", "()Ljava/lang/String;", (void*)TBrowserItem_GetTag },
        { "SetTag", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetTag },
        { "GetFavoritedate", "()Ljava/lang/String;", (void*)TBrowserItem_GetFavoritedate },
        { "SetFavoritedate", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetFavoritedate },
        { "GetMyCompany", "()Z", (void*)TBrowserItem_GetMyCompany },
        { "SetMyCompany", "(Z)Z", (void*)TBrowserItem_SetMyCompany },
        { "GetIsRated", "()Z", (void*)TBrowserItem_GetIsRated },
        { "SetIsRated", "(Z)Z", (void*)TBrowserItem_SetIsRated },
        { "GetModel", "()I", (void*)TBrowserItem_GetModel },
        { "SetModel", "(I)Z", (void*)TBrowserItem_SetModel },
        { "GetMarkID", "()Ljava/lang/String;", (void*)TBrowserItem_GetMarkID },
        { "SetMarkID", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetMarkID },
        { "GetMarkTitle", "()Ljava/lang/String;", (void*)TBrowserItem_GetMarkTitle },
        { "SetMarkTitle", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetMarkTitle },
        { "GetMarkPicUrl", "()Ljava/lang/String;", (void*)TBrowserItem_GetMarkPicUrl },
        { "SetMarkPicUrl", "(Ljava/lang/String;)Z", (void*)TBrowserItem_SetMarkPicUrl },
        { "GetIsHeadItem", "()Z", (void*)TBrowserItem_GetIsHeadItem },
        { "SetIsHeadItem", "(Z)Z", (void*)TBrowserItem_SetIsHeadItem }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TBrowserItem");
    if (clazz == 0) {
        CM_ERR("class TBrowserItem no found");
        return -1;
    }

    gTBrowserItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTBrowserItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TBrowserItem no found mNativeObj");
        return -1;
    }

    gTBrowserItemFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gTBrowserItemFieldID.jniData == 0) {
        CM_ERR("TBrowserItem no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gTBrowserItemFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gTBrowserItemFieldID.callback == NULL) {
        CM_ERR("TBrowserItem no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TBrowserItemMethods,
            sizeof(TBrowserItemMethods) / sizeof(TBrowserItemMethods[0]));
}


struct callback_cookie_TClassItem {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMRatingListener* listener2;
    CMSimpleResultListener* listener3;
};

fields_t gTClassItemFieldID;

static void TClassItem_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find TClassItem when setting up callback.");
        return;
    }
    callback_cookie_TClassItem* pCookie = new callback_cookie_TClassItem;
    pCookie->listener1 = new CMUpdateDataListener(gTClassItemFieldID.callback);
    pCookie->listener2 = new CMRatingListener(gTClassItemFieldID.callback);
    pCookie->listener3 = new CMSimpleResultListener(gTClassItemFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gTClassItemFieldID.jniData, (int)pCookie);

    TClassItem* pObj = new TClassItem();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gTClassItemFieldID.nativeJavaObj, (int)pObj);
}

static void TClassItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    TClassItem *pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_TClassItem* pCookie = (callback_cookie_TClassItem *)env->GetIntField(
        thiz, gTClassItemFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie->listener3;
        delete pCookie;
    }

    env->SetIntField(thiz, gTClassItemFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gTClassItemFieldID.jniData, 0);
}

static jboolean TClassItem_CommitStar(JNIEnv* env, jobject thiz, jint myStar)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);

    BOOL ret = pObj->CommitStar(myStar);
    return ret;
}

static jobject TClassItem_CopyFromTBrowserItem(JNIEnv* env, jobject thiz, jobject right)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);

    extern fields_t gTBrowserItemFieldID;
    TBrowserItem* pObjCopy = (TBrowserItem*)env->GetIntField(right, gTBrowserItemFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static void TClassItem_SetListener(JNIEnv* env, jobject thiz, jobject pUpdateDataListener, jobject pRatingListener, jobject pSimpleListener)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);

    callback_cookie_TClassItem* pCookie = (callback_cookie_TClassItem *)env->GetIntField(
        thiz, gTClassItemFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gTClassItemFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pUpdateDataListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMRatingListener(gTClassItemFieldID.callback);
        }
        
        IMRatingListener* para2 = NULL;
        if (pRatingListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        if (pCookie->listener3 == NULL)
        {
            pCookie->listener3 = new CMSimpleResultListener(gTClassItemFieldID.callback);
        }
        
        IMSimpleResultListener* para3 = NULL;
        if (pSimpleListener != NULL)
        {
            para3 = pCookie->listener3;
        }

        pObj->SetListener(para1, para2, para3);
    }

    return ;
}

static jstring TClassItem_GetSpecialtopic(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sSpecialtopic);
    jchar* data = UTF8toUTF16((char*)pObj->sSpecialtopic, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TClassItem_SetSpecialtopic(JNIEnv* env, jobject thiz, jstring sSpecialtopic)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sSpecialtopic, NULL);
    jsize size = env->GetStringLength(sSpecialtopic);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sSpecialtopic, (const char*)data, 63);
    pObj->sSpecialtopic[63] = '\0';

    env->ReleaseStringChars(sSpecialtopic, jChar);
    
    free(data);
    
    return true;
}

static jstring TClassItem_GetCredit(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sCredit);
    jchar* data = UTF8toUTF16((char*)pObj->sCredit, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TClassItem_SetCredit(JNIEnv* env, jobject thiz, jstring sCredit)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sCredit, NULL);
    jsize size = env->GetStringLength(sCredit);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sCredit, (const char*)data, 31);
    pObj->sCredit[31] = '\0';

    env->ReleaseStringChars(sCredit, jChar);
    
    free(data);
    
    return true;
}

static jint TClassItem_GetStudyduration(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nStudyduration;
}
                
static jboolean TClassItem_SetStudyduration(JNIEnv* env, jobject thiz, jint nStudyduration)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nStudyduration = nStudyduration;
    return true;
}
                
static jint TClassItem_GetStudyprogress(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nStudyprogress;
}
                
static jboolean TClassItem_SetStudyprogress(JNIEnv* env, jobject thiz, jint nStudyprogress)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nStudyprogress = nStudyprogress;
    return true;
}
                
static jstring TClassItem_GetLaststudydate(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sLaststudydate);
    jchar* data = UTF8toUTF16((char*)pObj->sLaststudydate, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TClassItem_SetLaststudydate(JNIEnv* env, jobject thiz, jstring sLaststudydate)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sLaststudydate, NULL);
    jsize size = env->GetStringLength(sLaststudydate);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sLaststudydate, (const char*)data, 31);
    pObj->sLaststudydate[31] = '\0';

    env->ReleaseStringChars(sLaststudydate, jChar);
    
    free(data);
    
    return true;
}

static jstring TClassItem_GetCommonStar(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->fCommonStar.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->fCommonStar.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TClassItem_SetCommonStar(JNIEnv* env, jobject thiz, jstring fCommonStar)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(fCommonStar, NULL);
    jsize size = env->GetStringLength(fCommonStar);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->fCommonStar = data;

    env->ReleaseStringChars(fCommonStar, jChar);
    
    free(data);
    
    return true;
}

static jint TClassItem_GetMyStar(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nMyStar;
}
                
static jboolean TClassItem_SetMyStar(JNIEnv* env, jobject thiz, jint nMyStar)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nMyStar = nMyStar;
    return true;
}
                
static jstring TClassItem_GetAuthor(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAuthor.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAuthor.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TClassItem_SetAuthor(JNIEnv* env, jobject thiz, jstring sAuthor)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAuthor, NULL);
    jsize size = env->GetStringLength(sAuthor);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAuthor = data;

    env->ReleaseStringChars(sAuthor, jChar);
    
    free(data);
    
    return true;
}

static jstring TClassItem_GetLanguage(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sLanguage.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sLanguage.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TClassItem_SetLanguage(JNIEnv* env, jobject thiz, jstring sLanguage)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sLanguage, NULL);
    jsize size = env->GetStringLength(sLanguage);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sLanguage = data;

    env->ReleaseStringChars(sLanguage, jChar);
    
    free(data);
    
    return true;
}

static jstring TClassItem_GetCourseType(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sCourseType.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sCourseType.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TClassItem_SetCourseType(JNIEnv* env, jobject thiz, jstring sCourseType)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sCourseType, NULL);
    jsize size = env->GetStringLength(sCourseType);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sCourseType = data;

    env->ReleaseStringChars(sCourseType, jChar);
    
    free(data);
    
    return true;
}

static jstring TClassItem_GetCourseLevel(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sCourseLevel.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sCourseLevel.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TClassItem_SetCourseLevel(JNIEnv* env, jobject thiz, jstring sCourseLevel)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sCourseLevel, NULL);
    jsize size = env->GetStringLength(sCourseLevel);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sCourseLevel = data;

    env->ReleaseStringChars(sCourseLevel, jChar);
    
    free(data);
    
    return true;
}

static jstring TClassItem_GetDevelopTime(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDevelopTime.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sDevelopTime.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TClassItem_SetDevelopTime(JNIEnv* env, jobject thiz, jstring sDevelopTime)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDevelopTime, NULL);
    jsize size = env->GetStringLength(sDevelopTime);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sDevelopTime = data;

    env->ReleaseStringChars(sDevelopTime, jChar);
    
    free(data);
    
    return true;
}

static jstring TClassItem_GetCourseVersion(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sCourseVersion.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sCourseVersion.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TClassItem_SetCourseVersion(JNIEnv* env, jobject thiz, jstring sCourseVersion)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sCourseVersion, NULL);
    jsize size = env->GetStringLength(sCourseVersion);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sCourseVersion = data;

    env->ReleaseStringChars(sCourseVersion, jChar);
    
    free(data);
    
    return true;
}

static jint TClassItem_GetStarCount(JNIEnv* env, jobject thiz)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nStarCount;
}
                
static jboolean TClassItem_SetStarCount(JNIEnv* env, jobject thiz, jint nStarCount)
{
    TClassItem* pObj = (TClassItem*)env->GetIntField(thiz, gTClassItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nStarCount = nStarCount;
    return true;
}
                
int register_com_wunding_mlplayer_business_TClassItem(JNIEnv* env) {
    static JNINativeMethod TClassItemMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)TClassItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TClassItem_nativeDestructor },
        { "CommitStar", "(I)Z", (void*)TClassItem_CommitStar },
        { "CopyFromTBrowserItem", "(Lcom/wunding/mlplayer/business/TBrowserItem;)Lcom/wunding/mlplayer/business/TClassItem;", (void*)TClassItem_CopyFromTBrowserItem },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)V", (void*)TClassItem_SetListener },
        { "GetSpecialtopic", "()Ljava/lang/String;", (void*)TClassItem_GetSpecialtopic },
        { "SetSpecialtopic", "(Ljava/lang/String;)Z", (void*)TClassItem_SetSpecialtopic },
        { "GetCredit", "()Ljava/lang/String;", (void*)TClassItem_GetCredit },
        { "SetCredit", "(Ljava/lang/String;)Z", (void*)TClassItem_SetCredit },
        { "GetStudyduration", "()I", (void*)TClassItem_GetStudyduration },
        { "SetStudyduration", "(I)Z", (void*)TClassItem_SetStudyduration },
        { "GetStudyprogress", "()I", (void*)TClassItem_GetStudyprogress },
        { "SetStudyprogress", "(I)Z", (void*)TClassItem_SetStudyprogress },
        { "GetLaststudydate", "()Ljava/lang/String;", (void*)TClassItem_GetLaststudydate },
        { "SetLaststudydate", "(Ljava/lang/String;)Z", (void*)TClassItem_SetLaststudydate },
        { "GetCommonStar", "()Ljava/lang/String;", (void*)TClassItem_GetCommonStar },
        { "SetCommonStar", "(Ljava/lang/String;)Z", (void*)TClassItem_SetCommonStar },
        { "GetMyStar", "()I", (void*)TClassItem_GetMyStar },
        { "SetMyStar", "(I)Z", (void*)TClassItem_SetMyStar },
        { "GetAuthor", "()Ljava/lang/String;", (void*)TClassItem_GetAuthor },
        { "SetAuthor", "(Ljava/lang/String;)Z", (void*)TClassItem_SetAuthor },
        { "GetLanguage", "()Ljava/lang/String;", (void*)TClassItem_GetLanguage },
        { "SetLanguage", "(Ljava/lang/String;)Z", (void*)TClassItem_SetLanguage },
        { "GetCourseType", "()Ljava/lang/String;", (void*)TClassItem_GetCourseType },
        { "SetCourseType", "(Ljava/lang/String;)Z", (void*)TClassItem_SetCourseType },
        { "GetCourseLevel", "()Ljava/lang/String;", (void*)TClassItem_GetCourseLevel },
        { "SetCourseLevel", "(Ljava/lang/String;)Z", (void*)TClassItem_SetCourseLevel },
        { "GetDevelopTime", "()Ljava/lang/String;", (void*)TClassItem_GetDevelopTime },
        { "SetDevelopTime", "(Ljava/lang/String;)Z", (void*)TClassItem_SetDevelopTime },
        { "GetCourseVersion", "()Ljava/lang/String;", (void*)TClassItem_GetCourseVersion },
        { "SetCourseVersion", "(Ljava/lang/String;)Z", (void*)TClassItem_SetCourseVersion },
        { "GetStarCount", "()I", (void*)TClassItem_GetStarCount },
        { "SetStarCount", "(I)Z", (void*)TClassItem_SetStarCount }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TClassItem");
    if (clazz == 0) {
        CM_ERR("class TClassItem no found");
        return -1;
    }

    gTClassItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTClassItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TClassItem no found mNativeObj");
        return -1;
    }

    gTClassItemFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gTClassItemFieldID.jniData == 0) {
        CM_ERR("TClassItem no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gTClassItemFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gTClassItemFieldID.callback == NULL) {
        CM_ERR("TClassItem no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TClassItemMethods,
            sizeof(TClassItemMethods) / sizeof(TClassItemMethods[0]));
}


struct callback_cookie_TCoursewareItem {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMRatingListener* listener2;
};

fields_t gTCoursewareItemFieldID;

static void TCoursewareItem_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find TCoursewareItem when setting up callback.");
        return;
    }
    callback_cookie_TCoursewareItem* pCookie = new callback_cookie_TCoursewareItem;
    pCookie->listener1 = new CMUpdateDataListener(gTCoursewareItemFieldID.callback);
    pCookie->listener2 = new CMRatingListener(gTCoursewareItemFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gTCoursewareItemFieldID.jniData, (int)pCookie);

    TCoursewareItem* pObj = new TCoursewareItem();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj, (int)pObj);
}

static void TCoursewareItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    TCoursewareItem *pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_TCoursewareItem* pCookie = (callback_cookie_TCoursewareItem *)env->GetIntField(
        thiz, gTCoursewareItemFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gTCoursewareItemFieldID.jniData, 0);
}

static jobject TCoursewareItem_CopyFromTBrowserItem(JNIEnv* env, jobject thiz, jobject right)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);

    extern fields_t gTBrowserItemFieldID;
    TBrowserItem* pObjCopy = (TBrowserItem*)env->GetIntField(right, gTBrowserItemFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static void TCoursewareItem_SetListener(JNIEnv* env, jobject thiz, jobject pUpdateDataListener, jobject pRatingListener)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);

    callback_cookie_TCoursewareItem* pCookie = (callback_cookie_TCoursewareItem *)env->GetIntField(
        thiz, gTCoursewareItemFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gTCoursewareItemFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pUpdateDataListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMRatingListener(gTCoursewareItemFieldID.callback);
        }
        
        IMRatingListener* para2 = NULL;
        if (pRatingListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        pObj->SetListener(para1, para2);
    }

    return ;
}

static jint TCoursewareItem_GetCheckStatus(JNIEnv* env, jobject thiz)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nCheckStatus;
}
                
static jboolean TCoursewareItem_SetCheckStatus(JNIEnv* env, jobject thiz, jint nCheckStatus)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nCheckStatus = nCheckStatus;
    return true;
}
                
static jboolean TCoursewareItem_GetIsLearned(JNIEnv* env, jobject thiz)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bIsLearned;
}
                
static jboolean TCoursewareItem_SetIsLearned(JNIEnv* env, jobject thiz, jboolean bIsLearned)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bIsLearned = bIsLearned;
    return true;
}
                
static jstring TCoursewareItem_GetSetID(JNIEnv* env, jobject thiz)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sSetID);
    jchar* data = UTF8toUTF16((char*)pObj->sSetID, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCoursewareItem_SetSetID(JNIEnv* env, jobject thiz, jstring sSetID)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sSetID, NULL);
    jsize size = env->GetStringLength(sSetID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sSetID, (const char*)data, 63);
    pObj->sSetID[63] = '\0';

    env->ReleaseStringChars(sSetID, jChar);
    
    free(data);
    
    return true;
}

static jstring TCoursewareItem_GetDownloadUrl(JNIEnv* env, jobject thiz)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDownloadUrl);
    jchar* data = UTF8toUTF16((char*)pObj->sDownloadUrl, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCoursewareItem_SetDownloadUrl(JNIEnv* env, jobject thiz, jstring sDownloadUrl)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDownloadUrl, NULL);
    jsize size = env->GetStringLength(sDownloadUrl);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sDownloadUrl, (const char*)data, 299);
    pObj->sDownloadUrl[299] = '\0';

    env->ReleaseStringChars(sDownloadUrl, jChar);
    
    free(data);
    
    return true;
}

static jboolean TCoursewareItem_GetDecompressed(JNIEnv* env, jobject thiz)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bDecompressed;
}
                
static jboolean TCoursewareItem_SetDecompressed(JNIEnv* env, jobject thiz, jboolean bDecompressed)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bDecompressed = bDecompressed;
    return true;
}
                
static jstring TCoursewareItem_GetEntryFilePath(JNIEnv* env, jobject thiz)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sEntryFilePath);
    jchar* data = UTF8toUTF16((char*)pObj->sEntryFilePath, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCoursewareItem_SetEntryFilePath(JNIEnv* env, jobject thiz, jstring sEntryFilePath)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sEntryFilePath, NULL);
    jsize size = env->GetStringLength(sEntryFilePath);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sEntryFilePath, (const char*)data, 299);
    pObj->sEntryFilePath[299] = '\0';

    env->ReleaseStringChars(sEntryFilePath, jChar);
    
    free(data);
    
    return true;
}

static jstring TCoursewareItem_GetLocalFilePath(JNIEnv* env, jobject thiz)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sLocalFilePath);
    jchar* data = UTF8toUTF16((char*)pObj->sLocalFilePath, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCoursewareItem_SetLocalFilePath(JNIEnv* env, jobject thiz, jstring sLocalFilePath)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sLocalFilePath, NULL);
    jsize size = env->GetStringLength(sLocalFilePath);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sLocalFilePath, (const char*)data, 299);
    pObj->sLocalFilePath[299] = '\0';

    env->ReleaseStringChars(sLocalFilePath, jChar);
    
    free(data);
    
    return true;
}

static jstring TCoursewareItem_GetOrientation(JNIEnv* env, jobject thiz)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sOrientation);
    jchar* data = UTF8toUTF16((char*)pObj->sOrientation, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TCoursewareItem_SetOrientation(JNIEnv* env, jobject thiz, jstring sOrientation)
{
    TCoursewareItem* pObj = (TCoursewareItem*)env->GetIntField(thiz, gTCoursewareItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sOrientation, NULL);
    jsize size = env->GetStringLength(sOrientation);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sOrientation, (const char*)data, 9);
    pObj->sOrientation[9] = '\0';

    env->ReleaseStringChars(sOrientation, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TCoursewareItem(JNIEnv* env) {
    static JNINativeMethod TCoursewareItemMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)TCoursewareItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TCoursewareItem_nativeDestructor },
        { "CopyFromTBrowserItem", "(Lcom/wunding/mlplayer/business/TBrowserItem;)Lcom/wunding/mlplayer/business/TCoursewareItem;", (void*)TCoursewareItem_CopyFromTBrowserItem },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)TCoursewareItem_SetListener },
        { "GetCheckStatus", "()I", (void*)TCoursewareItem_GetCheckStatus },
        { "SetCheckStatus", "(I)Z", (void*)TCoursewareItem_SetCheckStatus },
        { "GetIsLearned", "()Z", (void*)TCoursewareItem_GetIsLearned },
        { "SetIsLearned", "(Z)Z", (void*)TCoursewareItem_SetIsLearned },
        { "GetSetID", "()Ljava/lang/String;", (void*)TCoursewareItem_GetSetID },
        { "SetSetID", "(Ljava/lang/String;)Z", (void*)TCoursewareItem_SetSetID },
        { "GetDownloadUrl", "()Ljava/lang/String;", (void*)TCoursewareItem_GetDownloadUrl },
        { "SetDownloadUrl", "(Ljava/lang/String;)Z", (void*)TCoursewareItem_SetDownloadUrl },
        { "GetDecompressed", "()Z", (void*)TCoursewareItem_GetDecompressed },
        { "SetDecompressed", "(Z)Z", (void*)TCoursewareItem_SetDecompressed },
        { "GetEntryFilePath", "()Ljava/lang/String;", (void*)TCoursewareItem_GetEntryFilePath },
        { "SetEntryFilePath", "(Ljava/lang/String;)Z", (void*)TCoursewareItem_SetEntryFilePath },
        { "GetLocalFilePath", "()Ljava/lang/String;", (void*)TCoursewareItem_GetLocalFilePath },
        { "SetLocalFilePath", "(Ljava/lang/String;)Z", (void*)TCoursewareItem_SetLocalFilePath },
        { "GetOrientation", "()Ljava/lang/String;", (void*)TCoursewareItem_GetOrientation },
        { "SetOrientation", "(Ljava/lang/String;)Z", (void*)TCoursewareItem_SetOrientation }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TCoursewareItem");
    if (clazz == 0) {
        CM_ERR("class TCoursewareItem no found");
        return -1;
    }

    gTCoursewareItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTCoursewareItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TCoursewareItem no found mNativeObj");
        return -1;
    }

    gTCoursewareItemFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gTCoursewareItemFieldID.jniData == 0) {
        CM_ERR("TCoursewareItem no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gTCoursewareItemFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gTCoursewareItemFieldID.callback == NULL) {
        CM_ERR("TCoursewareItem no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TCoursewareItemMethods,
            sizeof(TCoursewareItemMethods) / sizeof(TCoursewareItemMethods[0]));
}

fields_t gTDummyItemFieldID;

static void TDummyItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TDummyItem* pObj = new TDummyItem();

    env->SetIntField(thiz, gTDummyItemFieldID.nativeJavaObj, (int)pObj);
}

static void TDummyItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TDummyItem*)env->GetIntField(thiz, gTDummyItemFieldID.nativeJavaObj);
}

static jint TDummyItem_GetDummy(JNIEnv* env, jobject thiz)
{
    TDummyItem* pObj = (TDummyItem*)env->GetIntField(thiz, gTDummyItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nDummy;
}
                
static jboolean TDummyItem_SetDummy(JNIEnv* env, jobject thiz, jint nDummy)
{
    TDummyItem* pObj = (TDummyItem*)env->GetIntField(thiz, gTDummyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nDummy = nDummy;
    return true;
}
                
int register_com_wunding_mlplayer_business_TDummyItem(JNIEnv* env) {
    static JNINativeMethod TDummyItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TDummyItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TDummyItem_nativeDestructor },
        { "GetDummy", "()I", (void*)TDummyItem_GetDummy },
        { "SetDummy", "(I)Z", (void*)TDummyItem_SetDummy }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TDummyItem");
    if (clazz == 0) {
        CM_ERR("class TDummyItem no found");
        return -1;
    }

    gTDummyItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTDummyItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TDummyItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TDummyItemMethods,
            sizeof(TDummyItemMethods) / sizeof(TDummyItemMethods[0]));
}


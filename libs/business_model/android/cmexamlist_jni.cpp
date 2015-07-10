// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmexamlist_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmexamlist.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTExamListItemFieldID;

static void TExamListItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = new TExamListItem();

    env->SetIntField(thiz, gTExamListItemFieldID.nativeJavaObj, (int)pObj);
}

static void TExamListItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
}

static jstring TExamListItem_GetID(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExamListItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TExamListItem_GetTitle(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTitle.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExamListItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTitle, NULL);
    jsize size = env->GetStringLength(sTitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTitle = data;

    env->ReleaseStringChars(sTitle, jChar);
    
    free(data);
    
    return true;
}

static jint TExamListItem_GetRequirecount(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nRequirecount;
}
                
static jboolean TExamListItem_SetRequirecount(JNIEnv* env, jobject thiz, jint nRequirecount)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nRequirecount = nRequirecount;
    return true;
}
                
static jint TExamListItem_GetUncompletecount(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nUncompletecount;
}
                
static jboolean TExamListItem_SetUncompletecount(JNIEnv* env, jobject thiz, jint nUncompletecount)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nUncompletecount = nUncompletecount;
    return true;
}
                
static jstring TExamListItem_GetTestscores(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTestscores.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sTestscores.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExamListItem_SetTestscores(JNIEnv* env, jobject thiz, jstring sTestscores)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sTestscores, NULL);
    jsize size = env->GetStringLength(sTestscores);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sTestscores = data;

    env->ReleaseStringChars(sTestscores, jChar);
    
    free(data);
    
    return true;
}

static jint TExamListItem_GetRanking(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nRanking;
}
                
static jboolean TExamListItem_SetRanking(JNIEnv* env, jobject thiz, jint nRanking)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nRanking = nRanking;
    return true;
}
                
static jstring TExamListItem_GetDesc(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDesc.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sDesc.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExamListItem_SetDesc(JNIEnv* env, jobject thiz, jstring sDesc)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDesc, NULL);
    jsize size = env->GetStringLength(sDesc);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sDesc = data;

    env->ReleaseStringChars(sDesc, jChar);
    
    free(data);
    
    return true;
}

static jstring TExamListItem_GetCategory(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sCategory.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sCategory.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExamListItem_SetCategory(JNIEnv* env, jobject thiz, jstring sCategory)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sCategory, NULL);
    jsize size = env->GetStringLength(sCategory);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sCategory = data;

    env->ReleaseStringChars(sCategory, jChar);
    
    free(data);
    
    return true;
}

static jboolean TExamListItem_GetViewAnswer(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bViewAnswer;
}
                
static jboolean TExamListItem_SetViewAnswer(JNIEnv* env, jobject thiz, jboolean bViewAnswer)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bViewAnswer = bViewAnswer;
    return true;
}
                
static jint TExamListItem_GetUsercompletecount(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nUsercompletecount;
}
                
static jboolean TExamListItem_SetUsercompletecount(JNIEnv* env, jobject thiz, jint nUsercompletecount)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nUsercompletecount = nUsercompletecount;
    return true;
}
                
static jstring TExamListItem_GetPubdate(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPubdate.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPubdate.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExamListItem_SetPubdate(JNIEnv* env, jobject thiz, jstring sPubdate)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPubdate, NULL);
    jsize size = env->GetStringLength(sPubdate);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPubdate = data;

    env->ReleaseStringChars(sPubdate, jChar);
    
    free(data);
    
    return true;
}

static jstring TExamListItem_GetCompletetime(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sCompletetime.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sCompletetime.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExamListItem_SetCompletetime(JNIEnv* env, jobject thiz, jstring sCompletetime)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sCompletetime, NULL);
    jsize size = env->GetStringLength(sCompletetime);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sCompletetime = data;

    env->ReleaseStringChars(sCompletetime, jChar);
    
    free(data);
    
    return true;
}

static jint TExamListItem_GetQuestioncount(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nQuestioncount;
}
                
static jboolean TExamListItem_SetQuestioncount(JNIEnv* env, jobject thiz, jint nQuestioncount)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nQuestioncount = nQuestioncount;
    return true;
}
                
static jint TExamListItem_GetDuration(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nDuration;
}
                
static jboolean TExamListItem_SetDuration(JNIEnv* env, jobject thiz, jint nDuration)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nDuration = nDuration;
    return true;
}
                
static jint TExamListItem_GetRemainTime(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nRemainTime;
}
                
static jboolean TExamListItem_SetRemainTime(JNIEnv* env, jobject thiz, jint nRemainTime)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nRemainTime = nRemainTime;
    return true;
}
                
static jint TExamListItem_GetCurrIndex(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nCurrIndex;
}
                
static jboolean TExamListItem_SetCurrIndex(JNIEnv* env, jobject thiz, jint nCurrIndex)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nCurrIndex = nCurrIndex;
    return true;
}
                
static jint TExamListItem_GetPassmark(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nPassmark;
}
                
static jboolean TExamListItem_SetPassmark(JNIEnv* env, jobject thiz, jint nPassmark)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nPassmark = nPassmark;
    return true;
}
                
static jint TExamListItem_GetFullmark(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nFullmark;
}
                
static jboolean TExamListItem_SetFullmark(JNIEnv* env, jobject thiz, jint nFullmark)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nFullmark = nFullmark;
    return true;
}
                
static jstring TExamListItem_GetRankurl(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sRankurl.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sRankurl.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExamListItem_SetRankurl(JNIEnv* env, jobject thiz, jstring sRankurl)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sRankurl, NULL);
    jsize size = env->GetStringLength(sRankurl);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sRankurl = data;

    env->ReleaseStringChars(sRankurl, jChar);
    
    free(data);
    
    return true;
}

static jint TExamListItem_GetTotalNumber(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nTotalNumber;
}
                
static jboolean TExamListItem_SetTotalNumber(JNIEnv* env, jobject thiz, jint nTotalNumber)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nTotalNumber = nTotalNumber;
    return true;
}
                
static jint TExamListItem_GetCurrNumber(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nCurrNumber;
}
                
static jboolean TExamListItem_SetCurrNumber(JNIEnv* env, jobject thiz, jint nCurrNumber)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nCurrNumber = nCurrNumber;
    return true;
}
                
static jstring TExamListItem_GetDstime(JNIEnv* env, jobject thiz)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDstime.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sDstime.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TExamListItem_SetDstime(JNIEnv* env, jobject thiz, jstring sDstime)
{
    TExamListItem* pObj = (TExamListItem*)env->GetIntField(thiz, gTExamListItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDstime, NULL);
    jsize size = env->GetStringLength(sDstime);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sDstime = data;

    env->ReleaseStringChars(sDstime, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TExamListItem(JNIEnv* env) {
    static JNINativeMethod TExamListItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TExamListItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TExamListItem_nativeDestructor },
        { "GetID", "()Ljava/lang/String;", (void*)TExamListItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TExamListItem_SetID },
        { "GetTitle", "()Ljava/lang/String;", (void*)TExamListItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)TExamListItem_SetTitle },
        { "GetRequirecount", "()I", (void*)TExamListItem_GetRequirecount },
        { "SetRequirecount", "(I)Z", (void*)TExamListItem_SetRequirecount },
        { "GetUncompletecount", "()I", (void*)TExamListItem_GetUncompletecount },
        { "SetUncompletecount", "(I)Z", (void*)TExamListItem_SetUncompletecount },
        { "GetTestscores", "()Ljava/lang/String;", (void*)TExamListItem_GetTestscores },
        { "SetTestscores", "(Ljava/lang/String;)Z", (void*)TExamListItem_SetTestscores },
        { "GetRanking", "()I", (void*)TExamListItem_GetRanking },
        { "SetRanking", "(I)Z", (void*)TExamListItem_SetRanking },
        { "GetDesc", "()Ljava/lang/String;", (void*)TExamListItem_GetDesc },
        { "SetDesc", "(Ljava/lang/String;)Z", (void*)TExamListItem_SetDesc },
        { "GetCategory", "()Ljava/lang/String;", (void*)TExamListItem_GetCategory },
        { "SetCategory", "(Ljava/lang/String;)Z", (void*)TExamListItem_SetCategory },
        { "GetViewAnswer", "()Z", (void*)TExamListItem_GetViewAnswer },
        { "SetViewAnswer", "(Z)Z", (void*)TExamListItem_SetViewAnswer },
        { "GetUsercompletecount", "()I", (void*)TExamListItem_GetUsercompletecount },
        { "SetUsercompletecount", "(I)Z", (void*)TExamListItem_SetUsercompletecount },
        { "GetPubdate", "()Ljava/lang/String;", (void*)TExamListItem_GetPubdate },
        { "SetPubdate", "(Ljava/lang/String;)Z", (void*)TExamListItem_SetPubdate },
        { "GetCompletetime", "()Ljava/lang/String;", (void*)TExamListItem_GetCompletetime },
        { "SetCompletetime", "(Ljava/lang/String;)Z", (void*)TExamListItem_SetCompletetime },
        { "GetQuestioncount", "()I", (void*)TExamListItem_GetQuestioncount },
        { "SetQuestioncount", "(I)Z", (void*)TExamListItem_SetQuestioncount },
        { "GetDuration", "()I", (void*)TExamListItem_GetDuration },
        { "SetDuration", "(I)Z", (void*)TExamListItem_SetDuration },
        { "GetRemainTime", "()I", (void*)TExamListItem_GetRemainTime },
        { "SetRemainTime", "(I)Z", (void*)TExamListItem_SetRemainTime },
        { "GetCurrIndex", "()I", (void*)TExamListItem_GetCurrIndex },
        { "SetCurrIndex", "(I)Z", (void*)TExamListItem_SetCurrIndex },
        { "GetPassmark", "()I", (void*)TExamListItem_GetPassmark },
        { "SetPassmark", "(I)Z", (void*)TExamListItem_SetPassmark },
        { "GetFullmark", "()I", (void*)TExamListItem_GetFullmark },
        { "SetFullmark", "(I)Z", (void*)TExamListItem_SetFullmark },
        { "GetRankurl", "()Ljava/lang/String;", (void*)TExamListItem_GetRankurl },
        { "SetRankurl", "(Ljava/lang/String;)Z", (void*)TExamListItem_SetRankurl },
        { "GetTotalNumber", "()I", (void*)TExamListItem_GetTotalNumber },
        { "SetTotalNumber", "(I)Z", (void*)TExamListItem_SetTotalNumber },
        { "GetCurrNumber", "()I", (void*)TExamListItem_GetCurrNumber },
        { "SetCurrNumber", "(I)Z", (void*)TExamListItem_SetCurrNumber },
        { "GetDstime", "()Ljava/lang/String;", (void*)TExamListItem_GetDstime },
        { "SetDstime", "(Ljava/lang/String;)Z", (void*)TExamListItem_SetDstime }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TExamListItem");
    if (clazz == 0) {
        CM_ERR("class TExamListItem no found");
        return -1;
    }

    gTExamListItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTExamListItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TExamListItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TExamListItemMethods,
            sizeof(TExamListItemMethods) / sizeof(TExamListItemMethods[0]));
}


struct callback_cookie_CMExamList {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMExamListFieldID;

static void CMExamList_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMExamList when setting up callback.");
        return;
    }
    callback_cookie_CMExamList* pCookie = new callback_cookie_CMExamList;
    pCookie->listener1 = new CMUpdateDataListener(gCMExamListFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMExamListFieldID.jniData, (int)pCookie);

    CMExamList* pObj = new CMExamList();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMExamListFieldID.nativeJavaObj, (int)pObj);
}

static void CMExamList_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMExamList *pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMExamList* pCookie = (callback_cookie_CMExamList *)env->GetIntField(
        thiz, gCMExamListFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMExamListFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMExamListFieldID.jniData, 0);
}

static jint CMExamList_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMExamList_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    extern fields_t gTExamListItemFieldID;
    TExamListItem* pItem = (TExamListItem*)env->GetIntField(item, gTExamListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMExamList_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    extern fields_t gTExamListItemFieldID;
    TExamListItem* pItem = (TExamListItem*)env->GetIntField(obj, gTExamListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMExamList_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    extern fields_t gTExamListItemFieldID;
    TExamListItem* pItem = (TExamListItem*)env->GetIntField(obj, gTExamListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMExamList_IsEnd(JNIEnv* env, jobject thiz)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMExamList_RequestMore(JNIEnv* env, jobject thiz)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMExamList_IsRunning(JNIEnv* env, jobject thiz)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMExamList_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMExamList_Cancel(JNIEnv* env, jobject thiz)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMExamList_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMExamList_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    callback_cookie_CMExamList* pCookie = (callback_cookie_CMExamList *)env->GetIntField(
        thiz, gCMExamListFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMExamListFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        pObj->SetListener(para1);
    }

    return ;
}

static jboolean CMExamList_GetList(JNIEnv* env, jobject thiz)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    BOOL ret = pObj->GetList();
    return ret;
}

static jboolean CMExamList_GetTrainList(JNIEnv* env, jobject thiz, jstring sTrainID)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    const jchar* jsTrainID = env->GetStringChars(sTrainID, NULL);
    jsize sizesTrainID = env->GetStringLength(sTrainID);
    char* psTrainID = UTF16toUTF8((jchar*)jsTrainID, (size_t*)&sizesTrainID);
    BOOL ret = pObj->GetTrainList(psTrainID);
    env->ReleaseStringChars(sTrainID, jsTrainID);
    free(psTrainID);
    return ret;
}

static jboolean CMExamList_GetExamById(JNIEnv* env, jobject thiz, jstring examId)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    const jchar* jexamId = env->GetStringChars(examId, NULL);
    jsize sizeexamId = env->GetStringLength(examId);
    char* pexamId = UTF16toUTF8((jchar*)jexamId, (size_t*)&sizeexamId);
    BOOL ret = pObj->GetExamById(pexamId);
    env->ReleaseStringChars(examId, jexamId);
    free(pexamId);
    return ret;
}

static jboolean CMExamList_UpdateItem(JNIEnv* env, jobject thiz, jobject item)
{
    CMExamList* pObj = (CMExamList*)env->GetIntField(thiz, gCMExamListFieldID.nativeJavaObj);

    extern fields_t gTExamListItemFieldID;
    TExamListItem* pItem = (TExamListItem*)env->GetIntField(item, gTExamListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->UpdateItem(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

int register_com_wunding_mlplayer_business_CMExamList(JNIEnv* env) {
    static JNINativeMethod CMExamListMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMExamList_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMExamList_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMExamList_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TExamListItem;)Z", (void*)CMExamList_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TExamListItem;)Z", (void*)CMExamList_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TExamListItem;)Z", (void*)CMExamList_Update },
        { "IsEnd", "()Z", (void*)CMExamList_IsEnd },
        { "RequestMore", "()Z", (void*)CMExamList_RequestMore },
        { "IsRunning", "()Z", (void*)CMExamList_IsRunning },
        { "IsRefresh", "()Z", (void*)CMExamList_IsRefresh },
        { "Cancel", "()V", (void*)CMExamList_Cancel },
        { "SetRequestType", "(I)V", (void*)CMExamList_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMExamList_SetListener },
        { "GetList", "()Z", (void*)CMExamList_GetList },
        { "GetTrainList", "(Ljava/lang/String;)Z", (void*)CMExamList_GetTrainList },
        { "GetExamById", "(Ljava/lang/String;)Z", (void*)CMExamList_GetExamById },
        { "UpdateItem", "(Lcom/wunding/mlplayer/business/TExamListItem;)Z", (void*)CMExamList_UpdateItem }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMExamList");
    if (clazz == 0) {
        CM_ERR("class CMExamList no found");
        return -1;
    }

    gCMExamListFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMExamListFieldID.nativeJavaObj == 0) {
        CM_ERR("CMExamList no found mNativeObj");
        return -1;
    }

    gCMExamListFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMExamListFieldID.jniData == 0) {
        CM_ERR("CMExamList no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMExamListFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMExamListFieldID.callback == NULL) {
        CM_ERR("CMExamList no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMExamListMethods,
            sizeof(CMExamListMethods) / sizeof(CMExamListMethods[0]));
}


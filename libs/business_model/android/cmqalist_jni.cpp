// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmqalist_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmqalist.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTQAItemFieldID;

static void TQAItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = new TQAItem();

    env->SetIntField(thiz, gTQAItemFieldID.nativeJavaObj, (int)pObj);
}

static void TQAItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
}

static jstring TQAItem_GetID(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQAItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TQAItem_GetQuestion(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sQuestion.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sQuestion.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQAItem_SetQuestion(JNIEnv* env, jobject thiz, jstring sQuestion)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sQuestion, NULL);
    jsize size = env->GetStringLength(sQuestion);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sQuestion = data;

    env->ReleaseStringChars(sQuestion, jChar);
    
    free(data);
    
    return true;
}

static jstring TQAItem_GetQuestioner_username(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sQuestioner_username.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sQuestioner_username.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQAItem_SetQuestioner_username(JNIEnv* env, jobject thiz, jstring sQuestioner_username)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sQuestioner_username, NULL);
    jsize size = env->GetStringLength(sQuestioner_username);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sQuestioner_username = data;

    env->ReleaseStringChars(sQuestioner_username, jChar);
    
    free(data);
    
    return true;
}

static jstring TQAItem_GetQuestioner_fullname(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sQuestioner_fullname.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sQuestioner_fullname.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQAItem_SetQuestioner_fullname(JNIEnv* env, jobject thiz, jstring sQuestioner_fullname)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sQuestioner_fullname, NULL);
    jsize size = env->GetStringLength(sQuestioner_fullname);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sQuestioner_fullname = data;

    env->ReleaseStringChars(sQuestioner_fullname, jChar);
    
    free(data);
    
    return true;
}

static jstring TQAItem_GetQuestioner_icon(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sQuestioner_icon.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sQuestioner_icon.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQAItem_SetQuestioner_icon(JNIEnv* env, jobject thiz, jstring sQuestioner_icon)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sQuestioner_icon, NULL);
    jsize size = env->GetStringLength(sQuestioner_icon);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sQuestioner_icon = data;

    env->ReleaseStringChars(sQuestioner_icon, jChar);
    
    free(data);
    
    return true;
}

static jstring TQAItem_GetPubdate(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPubdate.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPubdate.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQAItem_SetPubdate(JNIEnv* env, jobject thiz, jstring sPubdate)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPubdate, NULL);
    jsize size = env->GetStringLength(sPubdate);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPubdate = data;

    env->ReleaseStringChars(sPubdate, jChar);
    
    free(data);
    
    return true;
}

static jstring TQAItem_GetQcategorytitle(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sQcategorytitle.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sQcategorytitle.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQAItem_SetQcategorytitle(JNIEnv* env, jobject thiz, jstring sQcategorytitle)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sQcategorytitle, NULL);
    jsize size = env->GetStringLength(sQcategorytitle);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sQcategorytitle = data;

    env->ReleaseStringChars(sQcategorytitle, jChar);
    
    free(data);
    
    return true;
}

static jstring TQAItem_GetQcategoryid(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sQcategoryid.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sQcategoryid.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQAItem_SetQcategoryid(JNIEnv* env, jobject thiz, jstring sQcategoryid)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sQcategoryid, NULL);
    jsize size = env->GetStringLength(sQcategoryid);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sQcategoryid = data;

    env->ReleaseStringChars(sQcategoryid, jChar);
    
    free(data);
    
    return true;
}

static jboolean TQAItem_GetIsanonymity(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bIsanonymity;
}
                
static jboolean TQAItem_SetIsanonymity(JNIEnv* env, jobject thiz, jboolean bIsanonymity)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bIsanonymity = bIsanonymity;
    return true;
}
                
static jint TQAItem_GetVC(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nVC;
}
                
static jboolean TQAItem_SetVC(JNIEnv* env, jobject thiz, jint nVC)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nVC = nVC;
    return true;
}
                
static jint TQAItem_GetPV(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nPV;
}
                
static jboolean TQAItem_SetPV(JNIEnv* env, jobject thiz, jint nPV)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nPV = nPV;
    return true;
}
                
static jint TQAItem_GetAnswercount(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nAnswercount;
}
                
static jboolean TQAItem_SetAnswercount(JNIEnv* env, jobject thiz, jint nAnswercount)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nAnswercount = nAnswercount;
    return true;
}
                
static jint TQAItem_GetValue(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nValue;
}
                
static jboolean TQAItem_SetValue(JNIEnv* env, jobject thiz, jint nValue)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nValue = nValue;
    return true;
}
                
static jint TQAItem_GetAttention(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nAttention;
}
                
static jboolean TQAItem_SetAttention(JNIEnv* env, jobject thiz, jint nAttention)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nAttention = nAttention;
    return true;
}
                
static jboolean TQAItem_GetIsresolved(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bIsresolved;
}
                
static jboolean TQAItem_SetIsresolved(JNIEnv* env, jobject thiz, jboolean bIsresolved)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bIsresolved = bIsresolved;
    return true;
}
                
static jstring TQAItem_GetPic_url(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPic_url.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPic_url.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQAItem_SetPic_url(JNIEnv* env, jobject thiz, jstring sPic_url)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPic_url, NULL);
    jsize size = env->GetStringLength(sPic_url);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPic_url = data;

    env->ReleaseStringChars(sPic_url, jChar);
    
    free(data);
    
    return true;
}

static jstring TQAItem_GetThumburl(JNIEnv* env, jobject thiz)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sThumburl.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sThumburl.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQAItem_SetThumburl(JNIEnv* env, jobject thiz, jstring sThumburl)
{
    TQAItem* pObj = (TQAItem*)env->GetIntField(thiz, gTQAItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sThumburl, NULL);
    jsize size = env->GetStringLength(sThumburl);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sThumburl = data;

    env->ReleaseStringChars(sThumburl, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TQAItem(JNIEnv* env) {
    static JNINativeMethod TQAItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TQAItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TQAItem_nativeDestructor },
        { "GetID", "()Ljava/lang/String;", (void*)TQAItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TQAItem_SetID },
        { "GetQuestion", "()Ljava/lang/String;", (void*)TQAItem_GetQuestion },
        { "SetQuestion", "(Ljava/lang/String;)Z", (void*)TQAItem_SetQuestion },
        { "GetQuestioner_username", "()Ljava/lang/String;", (void*)TQAItem_GetQuestioner_username },
        { "SetQuestioner_username", "(Ljava/lang/String;)Z", (void*)TQAItem_SetQuestioner_username },
        { "GetQuestioner_fullname", "()Ljava/lang/String;", (void*)TQAItem_GetQuestioner_fullname },
        { "SetQuestioner_fullname", "(Ljava/lang/String;)Z", (void*)TQAItem_SetQuestioner_fullname },
        { "GetQuestioner_icon", "()Ljava/lang/String;", (void*)TQAItem_GetQuestioner_icon },
        { "SetQuestioner_icon", "(Ljava/lang/String;)Z", (void*)TQAItem_SetQuestioner_icon },
        { "GetPubdate", "()Ljava/lang/String;", (void*)TQAItem_GetPubdate },
        { "SetPubdate", "(Ljava/lang/String;)Z", (void*)TQAItem_SetPubdate },
        { "GetQcategorytitle", "()Ljava/lang/String;", (void*)TQAItem_GetQcategorytitle },
        { "SetQcategorytitle", "(Ljava/lang/String;)Z", (void*)TQAItem_SetQcategorytitle },
        { "GetQcategoryid", "()Ljava/lang/String;", (void*)TQAItem_GetQcategoryid },
        { "SetQcategoryid", "(Ljava/lang/String;)Z", (void*)TQAItem_SetQcategoryid },
        { "GetIsanonymity", "()Z", (void*)TQAItem_GetIsanonymity },
        { "SetIsanonymity", "(Z)Z", (void*)TQAItem_SetIsanonymity },
        { "GetVC", "()I", (void*)TQAItem_GetVC },
        { "SetVC", "(I)Z", (void*)TQAItem_SetVC },
        { "GetPV", "()I", (void*)TQAItem_GetPV },
        { "SetPV", "(I)Z", (void*)TQAItem_SetPV },
        { "GetAnswercount", "()I", (void*)TQAItem_GetAnswercount },
        { "SetAnswercount", "(I)Z", (void*)TQAItem_SetAnswercount },
        { "GetValue", "()I", (void*)TQAItem_GetValue },
        { "SetValue", "(I)Z", (void*)TQAItem_SetValue },
        { "GetAttention", "()I", (void*)TQAItem_GetAttention },
        { "SetAttention", "(I)Z", (void*)TQAItem_SetAttention },
        { "GetIsresolved", "()Z", (void*)TQAItem_GetIsresolved },
        { "SetIsresolved", "(Z)Z", (void*)TQAItem_SetIsresolved },
        { "GetPic_url", "()Ljava/lang/String;", (void*)TQAItem_GetPic_url },
        { "SetPic_url", "(Ljava/lang/String;)Z", (void*)TQAItem_SetPic_url },
        { "GetThumburl", "()Ljava/lang/String;", (void*)TQAItem_GetThumburl },
        { "SetThumburl", "(Ljava/lang/String;)Z", (void*)TQAItem_SetThumburl }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TQAItem");
    if (clazz == 0) {
        CM_ERR("class TQAItem no found");
        return -1;
    }

    gTQAItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTQAItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TQAItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TQAItemMethods,
            sizeof(TQAItemMethods) / sizeof(TQAItemMethods[0]));
}


struct callback_cookie_CMQAList {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
    CMRatingListener* listener3;
};

fields_t gCMQAListFieldID;

static void CMQAList_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMQAList when setting up callback.");
        return;
    }
    callback_cookie_CMQAList* pCookie = new callback_cookie_CMQAList;
    pCookie->listener1 = new CMUpdateDataListener(gCMQAListFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gCMQAListFieldID.callback);
    pCookie->listener3 = new CMRatingListener(gCMQAListFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMQAListFieldID.jniData, (int)pCookie);

    CMQAList* pObj = new CMQAList();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMQAListFieldID.nativeJavaObj, (int)pObj);
}

static void CMQAList_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMQAList *pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMQAList* pCookie = (callback_cookie_CMQAList *)env->GetIntField(
        thiz, gCMQAListFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie->listener3;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMQAListFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMQAListFieldID.jniData, 0);
}

static jint CMQAList_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMQAList_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    extern fields_t gTQAItemFieldID;
    TQAItem* pItem = (TQAItem*)env->GetIntField(item, gTQAItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQAList_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    extern fields_t gTQAItemFieldID;
    TQAItem* pItem = (TQAItem*)env->GetIntField(obj, gTQAItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQAList_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    extern fields_t gTQAItemFieldID;
    TQAItem* pItem = (TQAItem*)env->GetIntField(obj, gTQAItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQAList_IsEnd(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMQAList_RequestMore(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMQAList_IsRunning(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMQAList_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMQAList_Cancel(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMQAList_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMQAList_SetListener(JNIEnv* env, jobject thiz, jobject pListener, jobject pSimpleResultListener, jobject pRatingListener)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    callback_cookie_CMQAList* pCookie = (callback_cookie_CMQAList *)env->GetIntField(
        thiz, gCMQAListFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMQAListFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gCMQAListFieldID.callback);
        }
        
        IMSimpleResultListener* para2 = NULL;
        if (pSimpleResultListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        if (pCookie->listener3 == NULL)
        {
            pCookie->listener3 = new CMRatingListener(gCMQAListFieldID.callback);
        }
        
        IMRatingListener* para3 = NULL;
        if (pRatingListener != NULL)
        {
            para3 = pCookie->listener3;
        }

        pObj->SetListener(para1, para2, para3);
    }

    return ;
}

static jboolean CMQAList_GetNew(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    BOOL ret = pObj->GetNew();
    return ret;
}

static jboolean CMQAList_GetHot(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    BOOL ret = pObj->GetHot();
    return ret;
}

static jboolean CMQAList_GetQuestionbyId(JNIEnv* env, jobject thiz, jstring QaId)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    const jchar* jQaId = env->GetStringChars(QaId, NULL);
    jsize sizeQaId = env->GetStringLength(QaId);
    char* pQaId = UTF16toUTF8((jchar*)jQaId, (size_t*)&sizeQaId);
    BOOL ret = pObj->GetQuestionbyId(pQaId);
    env->ReleaseStringChars(QaId, jQaId);
    free(pQaId);
    return ret;
}

static jboolean CMQAList_GetAllQAByCategoryId(JNIEnv* env, jobject thiz, jstring categoryId)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    const jchar* jcategoryId = env->GetStringChars(categoryId, NULL);
    jsize sizecategoryId = env->GetStringLength(categoryId);
    char* pcategoryId = UTF16toUTF8((jchar*)jcategoryId, (size_t*)&sizecategoryId);
    BOOL ret = pObj->GetAllQAByCategoryId(pcategoryId);
    env->ReleaseStringChars(categoryId, jcategoryId);
    free(pcategoryId);
    return ret;
}

static jboolean CMQAList_GetMyQuestion(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    BOOL ret = pObj->GetMyQuestion();
    return ret;
}

static jboolean CMQAList_GetMyAnswer(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    BOOL ret = pObj->GetMyAnswer();
    return ret;
}

static jboolean CMQAList_GetMyAttention(JNIEnv* env, jobject thiz)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    BOOL ret = pObj->GetMyAttention();
    return ret;
}

static jboolean CMQAList_GetByCategory(JNIEnv* env, jobject thiz, jstring sCategoryID)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    const jchar* jsCategoryID = env->GetStringChars(sCategoryID, NULL);
    jsize sizesCategoryID = env->GetStringLength(sCategoryID);
    char* psCategoryID = UTF16toUTF8((jchar*)jsCategoryID, (size_t*)&sizesCategoryID);
    BOOL ret = pObj->GetByCategory(psCategoryID);
    env->ReleaseStringChars(sCategoryID, jsCategoryID);
    free(psCategoryID);
    return ret;
}

static jboolean CMQAList_Search(JNIEnv* env, jobject thiz, jstring sFlag, jstring sCategoryID, jstring sKey)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    const jchar* jsFlag = env->GetStringChars(sFlag, NULL);
    jsize sizesFlag = env->GetStringLength(sFlag);
    char* psFlag = UTF16toUTF8((jchar*)jsFlag, (size_t*)&sizesFlag);
    const jchar* jsCategoryID = env->GetStringChars(sCategoryID, NULL);
    jsize sizesCategoryID = env->GetStringLength(sCategoryID);
    char* psCategoryID = UTF16toUTF8((jchar*)jsCategoryID, (size_t*)&sizesCategoryID);
    const jchar* jsKey = env->GetStringChars(sKey, NULL);
    jsize sizesKey = env->GetStringLength(sKey);
    char* psKey = UTF16toUTF8((jchar*)jsKey, (size_t*)&sizesKey);
    BOOL ret = pObj->Search(psFlag, psCategoryID, psKey);
    env->ReleaseStringChars(sFlag, jsFlag);
    free(psFlag);
    env->ReleaseStringChars(sCategoryID, jsCategoryID);
    free(psCategoryID);
    env->ReleaseStringChars(sKey, jsKey);
    free(psKey);
    return ret;
}

static jboolean CMQAList_NewQuestion(JNIEnv* env, jobject thiz, jstring sCategoryID, jint nAnonymous, jint nValue, jstring sQuestion)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    const jchar* jsCategoryID = env->GetStringChars(sCategoryID, NULL);
    jsize sizesCategoryID = env->GetStringLength(sCategoryID);
    char* psCategoryID = UTF16toUTF8((jchar*)jsCategoryID, (size_t*)&sizesCategoryID);
    const jchar* jsQuestion = env->GetStringChars(sQuestion, NULL);
    jsize sizesQuestion = env->GetStringLength(sQuestion);
    char* psQuestion = UTF16toUTF8((jchar*)jsQuestion, (size_t*)&sizesQuestion);
    BOOL ret = pObj->NewQuestion(psCategoryID, nAnonymous, nValue, psQuestion);
    env->ReleaseStringChars(sCategoryID, jsCategoryID);
    free(psCategoryID);
    env->ReleaseStringChars(sQuestion, jsQuestion);
    free(psQuestion);
    return ret;
}

static jboolean CMQAList_AnswerQuestion(JNIEnv* env, jobject thiz, jstring sQuestionID, jint nAnonymous, jstring sAnswer)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    const jchar* jsQuestionID = env->GetStringChars(sQuestionID, NULL);
    jsize sizesQuestionID = env->GetStringLength(sQuestionID);
    char* psQuestionID = UTF16toUTF8((jchar*)jsQuestionID, (size_t*)&sizesQuestionID);
    const jchar* jsAnswer = env->GetStringChars(sAnswer, NULL);
    jsize sizesAnswer = env->GetStringLength(sAnswer);
    char* psAnswer = UTF16toUTF8((jchar*)jsAnswer, (size_t*)&sizesAnswer);
    BOOL ret = pObj->AnswerQuestion(psQuestionID, nAnonymous, psAnswer);
    env->ReleaseStringChars(sQuestionID, jsQuestionID);
    free(psQuestionID);
    env->ReleaseStringChars(sAnswer, jsAnswer);
    free(psAnswer);
    return ret;
}

static jboolean CMQAList_AnswerQuestion(JNIEnv* env, jobject thiz, jstring sQuestionID, jint nAnonymous, jstring sAnswer, jstring filename)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    const jchar* jsQuestionID = env->GetStringChars(sQuestionID, NULL);
    jsize sizesQuestionID = env->GetStringLength(sQuestionID);
    char* psQuestionID = UTF16toUTF8((jchar*)jsQuestionID, (size_t*)&sizesQuestionID);
    const jchar* jsAnswer = env->GetStringChars(sAnswer, NULL);
    jsize sizesAnswer = env->GetStringLength(sAnswer);
    char* psAnswer = UTF16toUTF8((jchar*)jsAnswer, (size_t*)&sizesAnswer);
    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->AnswerQuestion(psQuestionID, nAnonymous, psAnswer, pfilename);
    env->ReleaseStringChars(sQuestionID, jsQuestionID);
    free(psQuestionID);
    env->ReleaseStringChars(sAnswer, jsAnswer);
    free(psAnswer);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

static jboolean CMQAList_AskQuestion(JNIEnv* env, jobject thiz, jstring sCategoryID, jint nAnonymous, jint nValue, jstring sQuestion, jstring filename, jstring expertsID)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    const jchar* jsCategoryID = env->GetStringChars(sCategoryID, NULL);
    jsize sizesCategoryID = env->GetStringLength(sCategoryID);
    char* psCategoryID = UTF16toUTF8((jchar*)jsCategoryID, (size_t*)&sizesCategoryID);
    const jchar* jsQuestion = env->GetStringChars(sQuestion, NULL);
    jsize sizesQuestion = env->GetStringLength(sQuestion);
    char* psQuestion = UTF16toUTF8((jchar*)jsQuestion, (size_t*)&sizesQuestion);
    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    const jchar* jexpertsID = env->GetStringChars(expertsID, NULL);
    jsize sizeexpertsID = env->GetStringLength(expertsID);
    char* pexpertsID = UTF16toUTF8((jchar*)jexpertsID, (size_t*)&sizeexpertsID);
    BOOL ret = pObj->AskQuestion(psCategoryID, nAnonymous, nValue, psQuestion, pfilename, pexpertsID);
    env->ReleaseStringChars(sCategoryID, jsCategoryID);
    free(psCategoryID);
    env->ReleaseStringChars(sQuestion, jsQuestion);
    free(psQuestion);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    env->ReleaseStringChars(expertsID, jexpertsID);
    free(pexpertsID);
    return ret;
}

static jboolean CMQAList_AttentionQuestion(JNIEnv* env, jobject thiz, jstring sQuestionID)
{
    CMQAList* pObj = (CMQAList*)env->GetIntField(thiz, gCMQAListFieldID.nativeJavaObj);

    const jchar* jsQuestionID = env->GetStringChars(sQuestionID, NULL);
    jsize sizesQuestionID = env->GetStringLength(sQuestionID);
    char* psQuestionID = UTF16toUTF8((jchar*)jsQuestionID, (size_t*)&sizesQuestionID);
    BOOL ret = pObj->AttentionQuestion(psQuestionID);
    env->ReleaseStringChars(sQuestionID, jsQuestionID);
    free(psQuestionID);
    return ret;
}

int register_com_wunding_mlplayer_business_CMQAList(JNIEnv* env) {
    static jboolean (*CMQAList_AnswerQuestion1)(JNIEnv*, jobject, jstring, jint, jstring);
    CMQAList_AnswerQuestion1 = CMQAList_AnswerQuestion;
    static jboolean (*CMQAList_AnswerQuestion2)(JNIEnv*, jobject, jstring, jint, jstring, jstring);
    CMQAList_AnswerQuestion2 = CMQAList_AnswerQuestion;

    static JNINativeMethod CMQAListMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMQAList_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMQAList_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMQAList_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TQAItem;)Z", (void*)CMQAList_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TQAItem;)Z", (void*)CMQAList_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TQAItem;)Z", (void*)CMQAList_Update },
        { "IsEnd", "()Z", (void*)CMQAList_IsEnd },
        { "RequestMore", "()Z", (void*)CMQAList_RequestMore },
        { "IsRunning", "()Z", (void*)CMQAList_IsRunning },
        { "IsRefresh", "()Z", (void*)CMQAList_IsRefresh },
        { "Cancel", "()V", (void*)CMQAList_Cancel },
        { "SetRequestType", "(I)V", (void*)CMQAList_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;)V", (void*)CMQAList_SetListener },
        { "GetNew", "()Z", (void*)CMQAList_GetNew },
        { "GetHot", "()Z", (void*)CMQAList_GetHot },
        { "GetQuestionbyId", "(Ljava/lang/String;)Z", (void*)CMQAList_GetQuestionbyId },
        { "GetAllQAByCategoryId", "(Ljava/lang/String;)Z", (void*)CMQAList_GetAllQAByCategoryId },
        { "GetMyQuestion", "()Z", (void*)CMQAList_GetMyQuestion },
        { "GetMyAnswer", "()Z", (void*)CMQAList_GetMyAnswer },
        { "GetMyAttention", "()Z", (void*)CMQAList_GetMyAttention },
        { "GetByCategory", "(Ljava/lang/String;)Z", (void*)CMQAList_GetByCategory },
        { "Search", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMQAList_Search },
        { "NewQuestion", "(Ljava/lang/String;IILjava/lang/String;)Z", (void*)CMQAList_NewQuestion },
        { "AnswerQuestion", "(Ljava/lang/String;ILjava/lang/String;)Z", (void*)CMQAList_AnswerQuestion1 },
        { "AnswerQuestion", "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;)Z", (void*)CMQAList_AnswerQuestion2 },
        { "AskQuestion", "(Ljava/lang/String;IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMQAList_AskQuestion },
        { "AttentionQuestion", "(Ljava/lang/String;)Z", (void*)CMQAList_AttentionQuestion }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMQAList");
    if (clazz == 0) {
        CM_ERR("class CMQAList no found");
        return -1;
    }

    gCMQAListFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMQAListFieldID.nativeJavaObj == 0) {
        CM_ERR("CMQAList no found mNativeObj");
        return -1;
    }

    gCMQAListFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMQAListFieldID.jniData == 0) {
        CM_ERR("CMQAList no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMQAListFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMQAListFieldID.callback == NULL) {
        CM_ERR("CMQAList no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMQAListMethods,
            sizeof(CMQAListMethods) / sizeof(CMQAListMethods[0]));
}


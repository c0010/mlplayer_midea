// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmquestiondetail_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmquestiondetail.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTAnswerItemFieldID;

static void TAnswerItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = new TAnswerItem();

    env->SetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj, (int)pObj);
}

static void TAnswerItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
}

static jstring TAnswerItem_GetAnswerItemID(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetAnswerItemID();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TAnswerItem_GetAnswerItemAnswer(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetAnswerItemAnswer();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TAnswerItem_GetAnswerItemUserName(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetAnswerItemUserName();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TAnswerItem_GetAnswerItemFullName(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetAnswerItemFullName();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TAnswerItem_GetAnswerItemIcon(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetAnswerItemIcon();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TAnswerItem_GetAnswerItemPubdate(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetAnswerItemPubdate();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TAnswerItem_GetAnswerItemPicurl(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetAnswerItemPicurl();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TAnswerItem_GetAnswerItemThumburl(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetAnswerItemThumburl();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TAnswerItem_GetID(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TAnswerItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TAnswerItem_GetAnswer(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAnswer.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAnswer.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TAnswerItem_SetAnswer(JNIEnv* env, jobject thiz, jstring sAnswer)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAnswer, NULL);
    jsize size = env->GetStringLength(sAnswer);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAnswer = data;

    env->ReleaseStringChars(sAnswer, jChar);
    
    free(data);
    
    return true;
}

static jstring TAnswerItem_GetAnswerer_username(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAnswerer_username.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAnswerer_username.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TAnswerItem_SetAnswerer_username(JNIEnv* env, jobject thiz, jstring sAnswerer_username)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAnswerer_username, NULL);
    jsize size = env->GetStringLength(sAnswerer_username);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAnswerer_username = data;

    env->ReleaseStringChars(sAnswerer_username, jChar);
    
    free(data);
    
    return true;
}

static jstring TAnswerItem_GetAnswerer_fullname(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAnswerer_fullname.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAnswerer_fullname.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TAnswerItem_SetAnswerer_fullname(JNIEnv* env, jobject thiz, jstring sAnswerer_fullname)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAnswerer_fullname, NULL);
    jsize size = env->GetStringLength(sAnswerer_fullname);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAnswerer_fullname = data;

    env->ReleaseStringChars(sAnswerer_fullname, jChar);
    
    free(data);
    
    return true;
}

static jstring TAnswerItem_GetAnswerer_icon(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAnswerer_icon.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAnswerer_icon.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TAnswerItem_SetAnswerer_icon(JNIEnv* env, jobject thiz, jstring sAnswerer_icon)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAnswerer_icon, NULL);
    jsize size = env->GetStringLength(sAnswerer_icon);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAnswerer_icon = data;

    env->ReleaseStringChars(sAnswerer_icon, jChar);
    
    free(data);
    
    return true;
}

static jstring TAnswerItem_GetPubdate(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPubdate.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPubdate.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TAnswerItem_SetPubdate(JNIEnv* env, jobject thiz, jstring sPubdate)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPubdate, NULL);
    jsize size = env->GetStringLength(sPubdate);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPubdate = data;

    env->ReleaseStringChars(sPubdate, jChar);
    
    free(data);
    
    return true;
}

static jint TAnswerItem_GetAnswerflag(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nAnswerflag;
}
                
static jboolean TAnswerItem_SetAnswerflag(JNIEnv* env, jobject thiz, jint nAnswerflag)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nAnswerflag = nAnswerflag;
    return true;
}
                
static jint TAnswerItem_GetPV(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nPV;
}
                
static jboolean TAnswerItem_SetPV(JNIEnv* env, jobject thiz, jint nPV)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nPV = nPV;
    return true;
}
                
static jint TAnswerItem_GetIsliked(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nIsliked;
}
                
static jboolean TAnswerItem_SetIsliked(JNIEnv* env, jobject thiz, jint nIsliked)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nIsliked = nIsliked;
    return true;
}
                
static jstring TAnswerItem_GetPic_url(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPic_url.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPic_url.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TAnswerItem_SetPic_url(JNIEnv* env, jobject thiz, jstring sPic_url)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPic_url, NULL);
    jsize size = env->GetStringLength(sPic_url);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPic_url = data;

    env->ReleaseStringChars(sPic_url, jChar);
    
    free(data);
    
    return true;
}

static jstring TAnswerItem_GetThumburl(JNIEnv* env, jobject thiz)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sThumburl.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sThumburl.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TAnswerItem_SetThumburl(JNIEnv* env, jobject thiz, jstring sThumburl)
{
    TAnswerItem* pObj = (TAnswerItem*)env->GetIntField(thiz, gTAnswerItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sThumburl, NULL);
    jsize size = env->GetStringLength(sThumburl);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sThumburl = data;

    env->ReleaseStringChars(sThumburl, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TAnswerItem(JNIEnv* env) {
    static JNINativeMethod TAnswerItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TAnswerItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TAnswerItem_nativeDestructor },
        { "GetAnswerItemID", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerItemID },
        { "GetAnswerItemAnswer", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerItemAnswer },
        { "GetAnswerItemUserName", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerItemUserName },
        { "GetAnswerItemFullName", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerItemFullName },
        { "GetAnswerItemIcon", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerItemIcon },
        { "GetAnswerItemPubdate", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerItemPubdate },
        { "GetAnswerItemPicurl", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerItemPicurl },
        { "GetAnswerItemThumburl", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerItemThumburl },
        { "GetID", "()Ljava/lang/String;", (void*)TAnswerItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TAnswerItem_SetID },
        { "GetAnswer", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswer },
        { "SetAnswer", "(Ljava/lang/String;)Z", (void*)TAnswerItem_SetAnswer },
        { "GetAnswerer_username", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerer_username },
        { "SetAnswerer_username", "(Ljava/lang/String;)Z", (void*)TAnswerItem_SetAnswerer_username },
        { "GetAnswerer_fullname", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerer_fullname },
        { "SetAnswerer_fullname", "(Ljava/lang/String;)Z", (void*)TAnswerItem_SetAnswerer_fullname },
        { "GetAnswerer_icon", "()Ljava/lang/String;", (void*)TAnswerItem_GetAnswerer_icon },
        { "SetAnswerer_icon", "(Ljava/lang/String;)Z", (void*)TAnswerItem_SetAnswerer_icon },
        { "GetPubdate", "()Ljava/lang/String;", (void*)TAnswerItem_GetPubdate },
        { "SetPubdate", "(Ljava/lang/String;)Z", (void*)TAnswerItem_SetPubdate },
        { "GetAnswerflag", "()I", (void*)TAnswerItem_GetAnswerflag },
        { "SetAnswerflag", "(I)Z", (void*)TAnswerItem_SetAnswerflag },
        { "GetPV", "()I", (void*)TAnswerItem_GetPV },
        { "SetPV", "(I)Z", (void*)TAnswerItem_SetPV },
        { "GetIsliked", "()I", (void*)TAnswerItem_GetIsliked },
        { "SetIsliked", "(I)Z", (void*)TAnswerItem_SetIsliked },
        { "GetPic_url", "()Ljava/lang/String;", (void*)TAnswerItem_GetPic_url },
        { "SetPic_url", "(Ljava/lang/String;)Z", (void*)TAnswerItem_SetPic_url },
        { "GetThumburl", "()Ljava/lang/String;", (void*)TAnswerItem_GetThumburl },
        { "SetThumburl", "(Ljava/lang/String;)Z", (void*)TAnswerItem_SetThumburl }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TAnswerItem");
    if (clazz == 0) {
        CM_ERR("class TAnswerItem no found");
        return -1;
    }

    gTAnswerItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTAnswerItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TAnswerItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TAnswerItemMethods,
            sizeof(TAnswerItemMethods) / sizeof(TAnswerItemMethods[0]));
}


struct callback_cookie_CMQuestionDetail {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
    CMRatingListener* listener3;
};

fields_t gCMQuestionDetailFieldID;

static void CMQuestionDetail_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMQuestionDetail when setting up callback.");
        return;
    }
    callback_cookie_CMQuestionDetail* pCookie = new callback_cookie_CMQuestionDetail;
    pCookie->listener1 = new CMUpdateDataListener(gCMQuestionDetailFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gCMQuestionDetailFieldID.callback);
    pCookie->listener3 = new CMRatingListener(gCMQuestionDetailFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMQuestionDetailFieldID.jniData, (int)pCookie);

    CMQuestionDetail* pObj = new CMQuestionDetail(pCookie->listener1, pCookie->listener2, pCookie->listener3);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj, (int)pObj);
}

static void CMQuestionDetail_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMQuestionDetail *pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMQuestionDetail* pCookie = (callback_cookie_CMQuestionDetail *)env->GetIntField(
        thiz, gCMQuestionDetailFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie->listener3;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMQuestionDetailFieldID.jniData, 0);
}

static jint CMQuestionDetail_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMQuestionDetail_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    extern fields_t gTAnswerItemFieldID;
    TAnswerItem* pItem = (TAnswerItem*)env->GetIntField(item, gTAnswerItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQuestionDetail_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    extern fields_t gTAnswerItemFieldID;
    TAnswerItem* pItem = (TAnswerItem*)env->GetIntField(obj, gTAnswerItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQuestionDetail_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    extern fields_t gTAnswerItemFieldID;
    TAnswerItem* pItem = (TAnswerItem*)env->GetIntField(obj, gTAnswerItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQuestionDetail_IsEnd(JNIEnv* env, jobject thiz)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMQuestionDetail_RequestMore(JNIEnv* env, jobject thiz)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMQuestionDetail_IsRunning(JNIEnv* env, jobject thiz)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMQuestionDetail_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMQuestionDetail_Cancel(JNIEnv* env, jobject thiz)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMQuestionDetail_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static jboolean CMQuestionDetail_GetDetail(JNIEnv* env, jobject thiz, jstring sQuestionID)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    const jchar* jsQuestionID = env->GetStringChars(sQuestionID, NULL);
    jsize sizesQuestionID = env->GetStringLength(sQuestionID);
    char* psQuestionID = UTF16toUTF8((jchar*)jsQuestionID, (size_t*)&sizesQuestionID);
    BOOL ret = pObj->GetDetail(psQuestionID);
    env->ReleaseStringChars(sQuestionID, jsQuestionID);
    free(psQuestionID);
    return ret;
}

static jboolean CMQuestionDetail_SetBestAnswer(JNIEnv* env, jobject thiz, jstring sQuestionID, jstring sAnswerID)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    const jchar* jsQuestionID = env->GetStringChars(sQuestionID, NULL);
    jsize sizesQuestionID = env->GetStringLength(sQuestionID);
    char* psQuestionID = UTF16toUTF8((jchar*)jsQuestionID, (size_t*)&sizesQuestionID);
    const jchar* jsAnswerID = env->GetStringChars(sAnswerID, NULL);
    jsize sizesAnswerID = env->GetStringLength(sAnswerID);
    char* psAnswerID = UTF16toUTF8((jchar*)jsAnswerID, (size_t*)&sizesAnswerID);
    BOOL ret = pObj->SetBestAnswer(psQuestionID, psAnswerID);
    env->ReleaseStringChars(sQuestionID, jsQuestionID);
    free(psQuestionID);
    env->ReleaseStringChars(sAnswerID, jsAnswerID);
    free(psAnswerID);
    return ret;
}

static jboolean CMQuestionDetail_HasAnswerFlag(JNIEnv* env, jobject thiz)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    BOOL ret = pObj->HasAnswerFlag();
    return ret;
}

static jint CMQuestionDetail_GetHasFlagAnswerItem(JNIEnv* env, jobject thiz, jobject item)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    extern fields_t gTAnswerItemFieldID;
    TAnswerItem* pItem = (TAnswerItem*)env->GetIntField(item, gTAnswerItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jint ret = pObj->GetHasFlagAnswerItem(*pItem);
        return ret;
    }
    else {
        return -1;
    }
}

static jboolean CMQuestionDetail_LikeAnswer(JNIEnv* env, jobject thiz, jstring sQuestionID, jstring sAnswerID)
{
    CMQuestionDetail* pObj = (CMQuestionDetail*)env->GetIntField(thiz, gCMQuestionDetailFieldID.nativeJavaObj);

    const jchar* jsQuestionID = env->GetStringChars(sQuestionID, NULL);
    jsize sizesQuestionID = env->GetStringLength(sQuestionID);
    char* psQuestionID = UTF16toUTF8((jchar*)jsQuestionID, (size_t*)&sizesQuestionID);
    const jchar* jsAnswerID = env->GetStringChars(sAnswerID, NULL);
    jsize sizesAnswerID = env->GetStringLength(sAnswerID);
    char* psAnswerID = UTF16toUTF8((jchar*)jsAnswerID, (size_t*)&sizesAnswerID);
    BOOL ret = pObj->LikeAnswer(psQuestionID, psAnswerID);
    env->ReleaseStringChars(sQuestionID, jsQuestionID);
    free(psQuestionID);
    env->ReleaseStringChars(sAnswerID, jsAnswerID);
    free(psAnswerID);
    return ret;
}

int register_com_wunding_mlplayer_business_CMQuestionDetail(JNIEnv* env) {
    static JNINativeMethod CMQuestionDetailMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMQuestionDetail_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMQuestionDetail_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMQuestionDetail_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TAnswerItem;)Z", (void*)CMQuestionDetail_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TAnswerItem;)Z", (void*)CMQuestionDetail_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TAnswerItem;)Z", (void*)CMQuestionDetail_Update },
        { "IsEnd", "()Z", (void*)CMQuestionDetail_IsEnd },
        { "RequestMore", "()Z", (void*)CMQuestionDetail_RequestMore },
        { "IsRunning", "()Z", (void*)CMQuestionDetail_IsRunning },
        { "IsRefresh", "()Z", (void*)CMQuestionDetail_IsRefresh },
        { "Cancel", "()V", (void*)CMQuestionDetail_Cancel },
        { "SetRequestType", "(I)V", (void*)CMQuestionDetail_SetRequestType },
        { "GetDetail", "(Ljava/lang/String;)Z", (void*)CMQuestionDetail_GetDetail },
        { "SetBestAnswer", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMQuestionDetail_SetBestAnswer },
        { "HasAnswerFlag", "()Z", (void*)CMQuestionDetail_HasAnswerFlag },
        { "GetHasFlagAnswerItem", "(Lcom/wunding/mlplayer/business/TAnswerItem;)I", (void*)CMQuestionDetail_GetHasFlagAnswerItem },
        { "LikeAnswer", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMQuestionDetail_LikeAnswer }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMQuestionDetail");
    if (clazz == 0) {
        CM_ERR("class CMQuestionDetail no found");
        return -1;
    }

    gCMQuestionDetailFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMQuestionDetailFieldID.nativeJavaObj == 0) {
        CM_ERR("CMQuestionDetail no found mNativeObj");
        return -1;
    }

    gCMQuestionDetailFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMQuestionDetailFieldID.jniData == 0) {
        CM_ERR("CMQuestionDetail no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMQuestionDetailFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMQuestionDetailFieldID.callback == NULL) {
        CM_ERR("CMQuestionDetail no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMQuestionDetailMethods,
            sizeof(CMQuestionDetailMethods) / sizeof(CMQuestionDetailMethods[0]));
}


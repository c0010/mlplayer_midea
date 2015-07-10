// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmgroup_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmgroup.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_TGroupInfoItem {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gTGroupInfoItemFieldID;

static void TGroupInfoItem_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find TGroupInfoItem when setting up callback.");
        return;
    }
    callback_cookie_TGroupInfoItem* pCookie = new callback_cookie_TGroupInfoItem;
    pCookie->listener1 = new CMUpdateDataListener(gTGroupInfoItemFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gTGroupInfoItemFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gTGroupInfoItemFieldID.jniData, (int)pCookie);

    TGroupInfoItem* pObj = new TGroupInfoItem();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj, (int)pObj);
}

static void TGroupInfoItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem *pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_TGroupInfoItem* pCookie = (callback_cookie_TGroupInfoItem *)env->GetIntField(
        thiz, gTGroupInfoItemFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gTGroupInfoItemFieldID.jniData, 0);
}

static void TGroupInfoItem_SetListener(JNIEnv* env, jobject thiz, jobject pUpdateDataListener, jobject pSimpleListener)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    callback_cookie_TGroupInfoItem* pCookie = (callback_cookie_TGroupInfoItem *)env->GetIntField(
        thiz, gTGroupInfoItemFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gTGroupInfoItemFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pUpdateDataListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gTGroupInfoItemFieldID.callback);
        }
        
        IMSimpleResultListener* para2 = NULL;
        if (pSimpleListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        pObj->SetListener(para1, para2);
    }

    return ;
}

static void TGroupInfoItem_Cancel(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    pObj->Cancel();
}

static jboolean TGroupInfoItem_RequestDetailInfo(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestDetailInfo();
    return ret;
}

static jboolean TGroupInfoItem_RequestEnterGroup(JNIEnv* env, jobject thiz, jstring key)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jkey = env->GetStringChars(key, NULL);
    jsize sizekey = env->GetStringLength(key);
    char* pkey = UTF16toUTF8((jchar*)jkey, (size_t*)&sizekey);
    BOOL ret = pObj->RequestEnterGroup(pkey);
    env->ReleaseStringChars(key, jkey);
    free(pkey);
    return ret;
}

static jboolean TGroupInfoItem_ApplyEnterGroup(JNIEnv* env, jobject thiz, jstring reason)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jreason = env->GetStringChars(reason, NULL);
    jsize sizereason = env->GetStringLength(reason);
    char* preason = UTF16toUTF8((jchar*)jreason, (size_t*)&sizereason);
    BOOL ret = pObj->ApplyEnterGroup(preason);
    env->ReleaseStringChars(reason, jreason);
    free(preason);
    return ret;
}

static jboolean TGroupInfoItem_KickGroupOccupant(JNIEnv* env, jobject thiz, jstring sids)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jsids = env->GetStringChars(sids, NULL);
    jsize sizesids = env->GetStringLength(sids);
    char* psids = UTF16toUTF8((jchar*)jsids, (size_t*)&sizesids);
    BOOL ret = pObj->KickGroupOccupant(psids);
    env->ReleaseStringChars(sids, jsids);
    free(psids);
    return ret;
}

static jboolean TGroupInfoItem_InviteToGroup(JNIEnv* env, jobject thiz, jstring sids)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jsids = env->GetStringChars(sids, NULL);
    jsize sizesids = env->GetStringLength(sids);
    char* psids = UTF16toUTF8((jchar*)jsids, (size_t*)&sizesids);
    BOOL ret = pObj->InviteToGroup(psids);
    env->ReleaseStringChars(sids, jsids);
    free(psids);
    return ret;
}

static jboolean TGroupInfoItem_SetGroupAdmin(JNIEnv* env, jobject thiz, jstring sids)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jsids = env->GetStringChars(sids, NULL);
    jsize sizesids = env->GetStringLength(sids);
    char* psids = UTF16toUTF8((jchar*)jsids, (size_t*)&sizesids);
    BOOL ret = pObj->SetGroupAdmin(psids);
    env->ReleaseStringChars(sids, jsids);
    free(psids);
    return ret;
}

static jboolean TGroupInfoItem_RemoveGroupAdmin(JNIEnv* env, jobject thiz, jstring sids)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jsids = env->GetStringChars(sids, NULL);
    jsize sizesids = env->GetStringLength(sids);
    char* psids = UTF16toUTF8((jchar*)jsids, (size_t*)&sizesids);
    BOOL ret = pObj->RemoveGroupAdmin(psids);
    env->ReleaseStringChars(sids, jsids);
    free(psids);
    return ret;
}

static jboolean TGroupInfoItem_AcceptUserApply(JNIEnv* env, jobject thiz, jstring sids)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jsids = env->GetStringChars(sids, NULL);
    jsize sizesids = env->GetStringLength(sids);
    char* psids = UTF16toUTF8((jchar*)jsids, (size_t*)&sizesids);
    BOOL ret = pObj->AcceptUserApply(psids);
    env->ReleaseStringChars(sids, jsids);
    free(psids);
    return ret;
}

static jboolean TGroupInfoItem_RefuseUserApply(JNIEnv* env, jobject thiz, jstring sids, jstring reason)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jsids = env->GetStringChars(sids, NULL);
    jsize sizesids = env->GetStringLength(sids);
    char* psids = UTF16toUTF8((jchar*)jsids, (size_t*)&sizesids);
    const jchar* jreason = env->GetStringChars(reason, NULL);
    jsize sizereason = env->GetStringLength(reason);
    char* preason = UTF16toUTF8((jchar*)jreason, (size_t*)&sizereason);
    BOOL ret = pObj->RefuseUserApply(psids, preason);
    env->ReleaseStringChars(sids, jsids);
    free(psids);
    env->ReleaseStringChars(reason, jreason);
    free(preason);
    return ret;
}

static jobject TGroupInfoItem_CopyFromTGroupInfoItem(JNIEnv* env, jobject thiz, jobject right)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    extern fields_t gTGroupInfoItemFieldID;
    TGroupInfoItem* pObjCopy = (TGroupInfoItem*)env->GetIntField(right, gTGroupInfoItemFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

static jboolean TGroupInfoItem_ExitGroup(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    BOOL ret = pObj->ExitGroup();
    return ret;
}

static jboolean TGroupInfoItem_DisbandGroup(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    BOOL ret = pObj->DisbandGroup();
    return ret;
}

static jboolean TGroupInfoItem_updateGruopInfoWithName(JNIEnv* env, jobject thiz, jstring reason)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jreason = env->GetStringChars(reason, NULL);
    jsize sizereason = env->GetStringLength(reason);
    char* preason = UTF16toUTF8((jchar*)jreason, (size_t*)&sizereason);
    BOOL ret = pObj->updateGruopInfoWithName(preason);
    env->ReleaseStringChars(reason, jreason);
    free(preason);
    return ret;
}

static jboolean TGroupInfoItem_updateGruopInfoWithDesc(JNIEnv* env, jobject thiz, jstring reason)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jreason = env->GetStringChars(reason, NULL);
    jsize sizereason = env->GetStringLength(reason);
    char* preason = UTF16toUTF8((jchar*)jreason, (size_t*)&sizereason);
    BOOL ret = pObj->updateGruopInfoWithDesc(preason);
    env->ReleaseStringChars(reason, jreason);
    free(preason);
    return ret;
}

static jboolean TGroupInfoItem_updateGruopInfoWithPermis(JNIEnv* env, jobject thiz, jstring reason)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jreason = env->GetStringChars(reason, NULL);
    jsize sizereason = env->GetStringLength(reason);
    char* preason = UTF16toUTF8((jchar*)jreason, (size_t*)&sizereason);
    BOOL ret = pObj->updateGruopInfoWithPermis(preason);
    env->ReleaseStringChars(reason, jreason);
    free(preason);
    return ret;
}

static jboolean TGroupInfoItem_UploadHead(JNIEnv* env, jobject thiz, jstring filename)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);

    const jchar* jfilename = env->GetStringChars(filename, NULL);
    jsize sizefilename = env->GetStringLength(filename);
    char* pfilename = UTF16toUTF8((jchar*)jfilename, (size_t*)&sizefilename);
    BOOL ret = pObj->UploadHead(pfilename);
    env->ReleaseStringChars(filename, jfilename);
    free(pfilename);
    return ret;
}

static jstring TGroupInfoItem_GetID(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TGroupInfoItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TGroupInfoItem_GetJID(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sJID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sJID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TGroupInfoItem_SetJID(JNIEnv* env, jobject thiz, jstring sJID)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sJID, NULL);
    jsize size = env->GetStringLength(sJID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sJID = data;

    env->ReleaseStringChars(sJID, jChar);
    
    free(data);
    
    return true;
}

static jstring TGroupInfoItem_GetName(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sName.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sName.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TGroupInfoItem_SetName(JNIEnv* env, jobject thiz, jstring sName)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sName, NULL);
    jsize size = env->GetStringLength(sName);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sName = data;

    env->ReleaseStringChars(sName, jChar);
    
    free(data);
    
    return true;
}

static jstring TGroupInfoItem_GetDescription(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDescription.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sDescription.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TGroupInfoItem_SetDescription(JNIEnv* env, jobject thiz, jstring sDescription)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDescription, NULL);
    jsize size = env->GetStringLength(sDescription);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sDescription = data;

    env->ReleaseStringChars(sDescription, jChar);
    
    free(data);
    
    return true;
}

static jstring TGroupInfoItem_GetPwd(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPwd.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPwd.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TGroupInfoItem_SetPwd(JNIEnv* env, jobject thiz, jstring sPwd)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPwd, NULL);
    jsize size = env->GetStringLength(sPwd);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPwd = data;

    env->ReleaseStringChars(sPwd, jChar);
    
    free(data);
    
    return true;
}

static jstring TGroupInfoItem_GetNickName(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sNickName.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sNickName.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TGroupInfoItem_SetNickName(JNIEnv* env, jobject thiz, jstring sNickName)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sNickName, NULL);
    jsize size = env->GetStringLength(sNickName);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sNickName = data;

    env->ReleaseStringChars(sNickName, jChar);
    
    free(data);
    
    return true;
}

static jint TGroupInfoItem_GetUserCount(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nUserCount;
}
                
static jboolean TGroupInfoItem_SetUserCount(JNIEnv* env, jobject thiz, jint nUserCount)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nUserCount = nUserCount;
    return true;
}
                
static jstring TGroupInfoItem_GetIconUrl(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sIconUrl.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sIconUrl.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TGroupInfoItem_SetIconUrl(JNIEnv* env, jobject thiz, jstring sIconUrl)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sIconUrl, NULL);
    jsize size = env->GetStringLength(sIconUrl);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sIconUrl = data;

    env->ReleaseStringChars(sIconUrl, jChar);
    
    free(data);
    
    return true;
}

static jint TGroupInfoItem_GetFlag(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nFlag;
}
                
static jboolean TGroupInfoItem_SetFlag(JNIEnv* env, jobject thiz, jint nFlag)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nFlag = nFlag;
    return true;
}
                
static jstring TGroupInfoItem_GetRoomNumber(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sRoomNumber.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sRoomNumber.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TGroupInfoItem_SetRoomNumber(JNIEnv* env, jobject thiz, jstring sRoomNumber)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sRoomNumber, NULL);
    jsize size = env->GetStringLength(sRoomNumber);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sRoomNumber = data;

    env->ReleaseStringChars(sRoomNumber, jChar);
    
    free(data);
    
    return true;
}

static jstring TGroupInfoItem_GetOwner(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sOwner.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sOwner.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TGroupInfoItem_SetOwner(JNIEnv* env, jobject thiz, jstring sOwner)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sOwner, NULL);
    jsize size = env->GetStringLength(sOwner);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sOwner = data;

    env->ReleaseStringChars(sOwner, jChar);
    
    free(data);
    
    return true;
}

static jstring TGroupInfoItem_GetOwnerId(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sOwnerId.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sOwnerId.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TGroupInfoItem_SetOwnerId(JNIEnv* env, jobject thiz, jstring sOwnerId)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sOwnerId, NULL);
    jsize size = env->GetStringLength(sOwnerId);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sOwnerId = data;

    env->ReleaseStringChars(sOwnerId, jChar);
    
    free(data);
    
    return true;
}

static jint TGroupInfoItem_GetIsOccupant(JNIEnv* env, jobject thiz)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nIsOccupant;
}
                
static jboolean TGroupInfoItem_SetIsOccupant(JNIEnv* env, jobject thiz, jint nIsOccupant)
{
    TGroupInfoItem* pObj = (TGroupInfoItem*)env->GetIntField(thiz, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nIsOccupant = nIsOccupant;
    return true;
}
                
int register_com_wunding_mlplayer_business_TGroupInfoItem(JNIEnv* env) {
    static JNINativeMethod TGroupInfoItemMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)TGroupInfoItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TGroupInfoItem_nativeDestructor },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)TGroupInfoItem_SetListener },
        { "Cancel", "()V", (void*)TGroupInfoItem_Cancel },
        { "RequestDetailInfo", "()Z", (void*)TGroupInfoItem_RequestDetailInfo },
        { "RequestEnterGroup", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_RequestEnterGroup },
        { "ApplyEnterGroup", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_ApplyEnterGroup },
        { "KickGroupOccupant", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_KickGroupOccupant },
        { "InviteToGroup", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_InviteToGroup },
        { "SetGroupAdmin", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetGroupAdmin },
        { "RemoveGroupAdmin", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_RemoveGroupAdmin },
        { "AcceptUserApply", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_AcceptUserApply },
        { "RefuseUserApply", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)TGroupInfoItem_RefuseUserApply },
        { "CopyFromTGroupInfoItem", "(Lcom/wunding/mlplayer/business/TGroupInfoItem;)Lcom/wunding/mlplayer/business/TGroupInfoItem;", (void*)TGroupInfoItem_CopyFromTGroupInfoItem },
        { "ExitGroup", "()Z", (void*)TGroupInfoItem_ExitGroup },
        { "DisbandGroup", "()Z", (void*)TGroupInfoItem_DisbandGroup },
        { "updateGruopInfoWithName", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_updateGruopInfoWithName },
        { "updateGruopInfoWithDesc", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_updateGruopInfoWithDesc },
        { "updateGruopInfoWithPermis", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_updateGruopInfoWithPermis },
        { "UploadHead", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_UploadHead },
        { "GetID", "()Ljava/lang/String;", (void*)TGroupInfoItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetID },
        { "GetJID", "()Ljava/lang/String;", (void*)TGroupInfoItem_GetJID },
        { "SetJID", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetJID },
        { "GetName", "()Ljava/lang/String;", (void*)TGroupInfoItem_GetName },
        { "SetName", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetName },
        { "GetDescription", "()Ljava/lang/String;", (void*)TGroupInfoItem_GetDescription },
        { "SetDescription", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetDescription },
        { "GetPwd", "()Ljava/lang/String;", (void*)TGroupInfoItem_GetPwd },
        { "SetPwd", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetPwd },
        { "GetNickName", "()Ljava/lang/String;", (void*)TGroupInfoItem_GetNickName },
        { "SetNickName", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetNickName },
        { "GetUserCount", "()I", (void*)TGroupInfoItem_GetUserCount },
        { "SetUserCount", "(I)Z", (void*)TGroupInfoItem_SetUserCount },
        { "GetIconUrl", "()Ljava/lang/String;", (void*)TGroupInfoItem_GetIconUrl },
        { "SetIconUrl", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetIconUrl },
        { "GetFlag", "()I", (void*)TGroupInfoItem_GetFlag },
        { "SetFlag", "(I)Z", (void*)TGroupInfoItem_SetFlag },
        { "GetRoomNumber", "()Ljava/lang/String;", (void*)TGroupInfoItem_GetRoomNumber },
        { "SetRoomNumber", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetRoomNumber },
        { "GetOwner", "()Ljava/lang/String;", (void*)TGroupInfoItem_GetOwner },
        { "SetOwner", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetOwner },
        { "GetOwnerId", "()Ljava/lang/String;", (void*)TGroupInfoItem_GetOwnerId },
        { "SetOwnerId", "(Ljava/lang/String;)Z", (void*)TGroupInfoItem_SetOwnerId },
        { "GetIsOccupant", "()I", (void*)TGroupInfoItem_GetIsOccupant },
        { "SetIsOccupant", "(I)Z", (void*)TGroupInfoItem_SetIsOccupant }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TGroupInfoItem");
    if (clazz == 0) {
        CM_ERR("class TGroupInfoItem no found");
        return -1;
    }

    gTGroupInfoItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTGroupInfoItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TGroupInfoItem no found mNativeObj");
        return -1;
    }

    gTGroupInfoItemFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gTGroupInfoItemFieldID.jniData == 0) {
        CM_ERR("TGroupInfoItem no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gTGroupInfoItemFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gTGroupInfoItemFieldID.callback == NULL) {
        CM_ERR("TGroupInfoItem no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TGroupInfoItemMethods,
            sizeof(TGroupInfoItemMethods) / sizeof(TGroupInfoItemMethods[0]));
}


struct callback_cookie_CMGroup {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gCMGroupFieldID;

static void CMGroup_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMGroup when setting up callback.");
        return;
    }
    callback_cookie_CMGroup* pCookie = new callback_cookie_CMGroup;
    pCookie->listener1 = new CMUpdateDataListener(gCMGroupFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gCMGroupFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMGroupFieldID.jniData, (int)pCookie);

    CMGroup* pObj = new CMGroup();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMGroupFieldID.nativeJavaObj, (int)pObj);
}

static void CMGroup_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMGroup *pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMGroup* pCookie = (callback_cookie_CMGroup *)env->GetIntField(
        thiz, gCMGroupFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMGroupFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMGroupFieldID.jniData, 0);
}

static jint CMGroup_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMGroup_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    extern fields_t gTGroupInfoItemFieldID;
    TGroupInfoItem* pItem = (TGroupInfoItem*)env->GetIntField(item, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGroup_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    extern fields_t gTGroupInfoItemFieldID;
    TGroupInfoItem* pItem = (TGroupInfoItem*)env->GetIntField(obj, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGroup_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    extern fields_t gTGroupInfoItemFieldID;
    TGroupInfoItem* pItem = (TGroupInfoItem*)env->GetIntField(obj, gTGroupInfoItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGroup_IsEnd(JNIEnv* env, jobject thiz)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMGroup_RequestMore(JNIEnv* env, jobject thiz)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMGroup_IsRunning(JNIEnv* env, jobject thiz)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMGroup_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMGroup_Cancel(JNIEnv* env, jobject thiz)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMGroup_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMGroup_SetListener(JNIEnv* env, jobject thiz, jobject m_pListener, jobject m_pSimpleListener)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    callback_cookie_CMGroup* pCookie = (callback_cookie_CMGroup *)env->GetIntField(
        thiz, gCMGroupFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMGroupFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (m_pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gCMGroupFieldID.callback);
        }
        
        IMSimpleResultListener* para2 = NULL;
        if (m_pSimpleListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        pObj->SetListener(para1, para2);
    }

    return ;
}

static jboolean CMGroup_RequestMyGroup(JNIEnv* env, jobject thiz)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMyGroup();
    return ret;
}

static jboolean CMGroup_SearchGroup(JNIEnv* env, jobject thiz, jstring keyword)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    const jchar* jkeyword = env->GetStringChars(keyword, NULL);
    jsize sizekeyword = env->GetStringLength(keyword);
    char* pkeyword = UTF16toUTF8((jchar*)jkeyword, (size_t*)&sizekeyword);
    BOOL ret = pObj->SearchGroup(pkeyword);
    env->ReleaseStringChars(keyword, jkeyword);
    free(pkeyword);
    return ret;
}

static jboolean CMGroup_CreateNewGroup(JNIEnv* env, jobject thiz, jstring name, jstring desc, jstring iconPath, jint flag)
{
    CMGroup* pObj = (CMGroup*)env->GetIntField(thiz, gCMGroupFieldID.nativeJavaObj);

    const jchar* jname = env->GetStringChars(name, NULL);
    jsize sizename = env->GetStringLength(name);
    char* pname = UTF16toUTF8((jchar*)jname, (size_t*)&sizename);
    const jchar* jdesc = env->GetStringChars(desc, NULL);
    jsize sizedesc = env->GetStringLength(desc);
    char* pdesc = UTF16toUTF8((jchar*)jdesc, (size_t*)&sizedesc);
    const jchar* jiconPath = env->GetStringChars(iconPath, NULL);
    jsize sizeiconPath = env->GetStringLength(iconPath);
    char* piconPath = UTF16toUTF8((jchar*)jiconPath, (size_t*)&sizeiconPath);
    BOOL ret = pObj->CreateNewGroup(pname, pdesc, piconPath, flag);
    env->ReleaseStringChars(name, jname);
    free(pname);
    env->ReleaseStringChars(desc, jdesc);
    free(pdesc);
    env->ReleaseStringChars(iconPath, jiconPath);
    free(piconPath);
    return ret;
}

int register_com_wunding_mlplayer_business_CMGroup(JNIEnv* env) {
    static JNINativeMethod CMGroupMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMGroup_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMGroup_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMGroup_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TGroupInfoItem;)Z", (void*)CMGroup_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TGroupInfoItem;)Z", (void*)CMGroup_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TGroupInfoItem;)Z", (void*)CMGroup_Update },
        { "IsEnd", "()Z", (void*)CMGroup_IsEnd },
        { "RequestMore", "()Z", (void*)CMGroup_RequestMore },
        { "IsRunning", "()Z", (void*)CMGroup_IsRunning },
        { "IsRefresh", "()Z", (void*)CMGroup_IsRefresh },
        { "Cancel", "()V", (void*)CMGroup_Cancel },
        { "SetRequestType", "(I)V", (void*)CMGroup_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)CMGroup_SetListener },
        { "RequestMyGroup", "()Z", (void*)CMGroup_RequestMyGroup },
        { "SearchGroup", "(Ljava/lang/String;)Z", (void*)CMGroup_SearchGroup },
        { "CreateNewGroup", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)Z", (void*)CMGroup_CreateNewGroup }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMGroup");
    if (clazz == 0) {
        CM_ERR("class CMGroup no found");
        return -1;
    }

    gCMGroupFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMGroupFieldID.nativeJavaObj == 0) {
        CM_ERR("CMGroup no found mNativeObj");
        return -1;
    }

    gCMGroupFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMGroupFieldID.jniData == 0) {
        CM_ERR("CMGroup no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMGroupFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMGroupFieldID.callback == NULL) {
        CM_ERR("CMGroup no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMGroupMethods,
            sizeof(CMGroupMethods) / sizeof(CMGroupMethods[0]));
}


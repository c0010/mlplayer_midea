// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmcontacts_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmcontacts.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTContactsItemFieldID;

static void TContactsItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = new TContactsItem();

    env->SetIntField(thiz, gTContactsItemFieldID.nativeJavaObj, (int)pObj);
}

static void TContactsItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
}

static jstring TContactsItem_GetID(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetName(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sName.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sName.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetName(JNIEnv* env, jobject thiz, jstring sName)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sName, NULL);
    jsize size = env->GetStringLength(sName);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sName = data;

    env->ReleaseStringChars(sName, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetIcon(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sIcon.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sIcon.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetIcon(JNIEnv* env, jobject thiz, jstring sIcon)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sIcon, NULL);
    jsize size = env->GetStringLength(sIcon);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sIcon = data;

    env->ReleaseStringChars(sIcon, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetSex(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sSex.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sSex.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetSex(JNIEnv* env, jobject thiz, jstring sSex)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sSex, NULL);
    jsize size = env->GetStringLength(sSex);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sSex = data;

    env->ReleaseStringChars(sSex, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetOrg(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sOrg.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sOrg.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetOrg(JNIEnv* env, jobject thiz, jstring sOrg)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sOrg, NULL);
    jsize size = env->GetStringLength(sOrg);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sOrg = data;

    env->ReleaseStringChars(sOrg, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetDep(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDep.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sDep.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetDep(JNIEnv* env, jobject thiz, jstring sDep)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDep, NULL);
    jsize size = env->GetStringLength(sDep);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sDep = data;

    env->ReleaseStringChars(sDep, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetPosition(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPosition.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPosition.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetPosition(JNIEnv* env, jobject thiz, jstring sPosition)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPosition, NULL);
    jsize size = env->GetStringLength(sPosition);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPosition = data;

    env->ReleaseStringChars(sPosition, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetMobilenumber(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sMobilenumber.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sMobilenumber.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetMobilenumber(JNIEnv* env, jobject thiz, jstring sMobilenumber)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sMobilenumber, NULL);
    jsize size = env->GetStringLength(sMobilenumber);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sMobilenumber = data;

    env->ReleaseStringChars(sMobilenumber, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetShortnumber(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sShortnumber.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sShortnumber.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetShortnumber(JNIEnv* env, jobject thiz, jstring sShortnumber)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sShortnumber, NULL);
    jsize size = env->GetStringLength(sShortnumber);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sShortnumber = data;

    env->ReleaseStringChars(sShortnumber, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetPhonenumber(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sPhonenumber.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sPhonenumber.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetPhonenumber(JNIEnv* env, jobject thiz, jstring sPhonenumber)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sPhonenumber, NULL);
    jsize size = env->GetStringLength(sPhonenumber);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sPhonenumber = data;

    env->ReleaseStringChars(sPhonenumber, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetEmail(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sEmail.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sEmail.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetEmail(JNIEnv* env, jobject thiz, jstring sEmail)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sEmail, NULL);
    jsize size = env->GetStringLength(sEmail);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sEmail = data;

    env->ReleaseStringChars(sEmail, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetFax(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sFax.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sFax.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetFax(JNIEnv* env, jobject thiz, jstring sFax)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sFax, NULL);
    jsize size = env->GetStringLength(sFax);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sFax = data;

    env->ReleaseStringChars(sFax, jChar);
    
    free(data);
    
    return true;
}

static jstring TContactsItem_GetJid(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sJid.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sJid.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TContactsItem_SetJid(JNIEnv* env, jobject thiz, jstring sJid)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sJid, NULL);
    jsize size = env->GetStringLength(sJid);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sJid = data;

    env->ReleaseStringChars(sJid, jChar);
    
    free(data);
    
    return true;
}

static jint TContactsItem_GetIsManager(JNIEnv* env, jobject thiz)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nIsManager;
}
                
static jboolean TContactsItem_SetIsManager(JNIEnv* env, jobject thiz, jint nIsManager)
{
    TContactsItem* pObj = (TContactsItem*)env->GetIntField(thiz, gTContactsItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nIsManager = nIsManager;
    return true;
}
                
int register_com_wunding_mlplayer_business_TContactsItem(JNIEnv* env) {
    static JNINativeMethod TContactsItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TContactsItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TContactsItem_nativeDestructor },
        { "GetID", "()Ljava/lang/String;", (void*)TContactsItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetID },
        { "GetName", "()Ljava/lang/String;", (void*)TContactsItem_GetName },
        { "SetName", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetName },
        { "GetIcon", "()Ljava/lang/String;", (void*)TContactsItem_GetIcon },
        { "SetIcon", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetIcon },
        { "GetSex", "()Ljava/lang/String;", (void*)TContactsItem_GetSex },
        { "SetSex", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetSex },
        { "GetOrg", "()Ljava/lang/String;", (void*)TContactsItem_GetOrg },
        { "SetOrg", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetOrg },
        { "GetDep", "()Ljava/lang/String;", (void*)TContactsItem_GetDep },
        { "SetDep", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetDep },
        { "GetPosition", "()Ljava/lang/String;", (void*)TContactsItem_GetPosition },
        { "SetPosition", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetPosition },
        { "GetMobilenumber", "()Ljava/lang/String;", (void*)TContactsItem_GetMobilenumber },
        { "SetMobilenumber", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetMobilenumber },
        { "GetShortnumber", "()Ljava/lang/String;", (void*)TContactsItem_GetShortnumber },
        { "SetShortnumber", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetShortnumber },
        { "GetPhonenumber", "()Ljava/lang/String;", (void*)TContactsItem_GetPhonenumber },
        { "SetPhonenumber", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetPhonenumber },
        { "GetEmail", "()Ljava/lang/String;", (void*)TContactsItem_GetEmail },
        { "SetEmail", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetEmail },
        { "GetFax", "()Ljava/lang/String;", (void*)TContactsItem_GetFax },
        { "SetFax", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetFax },
        { "GetJid", "()Ljava/lang/String;", (void*)TContactsItem_GetJid },
        { "SetJid", "(Ljava/lang/String;)Z", (void*)TContactsItem_SetJid },
        { "GetIsManager", "()I", (void*)TContactsItem_GetIsManager },
        { "SetIsManager", "(I)Z", (void*)TContactsItem_SetIsManager }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TContactsItem");
    if (clazz == 0) {
        CM_ERR("class TContactsItem no found");
        return -1;
    }

    gTContactsItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTContactsItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TContactsItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TContactsItemMethods,
            sizeof(TContactsItemMethods) / sizeof(TContactsItemMethods[0]));
}


struct callback_cookie_CMContacts {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMContactsFieldID;

static void CMContacts_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMContacts when setting up callback.");
        return;
    }
    callback_cookie_CMContacts* pCookie = new callback_cookie_CMContacts;
    pCookie->listener1 = new CMUpdateDataListener(gCMContactsFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMContactsFieldID.jniData, (int)pCookie);

    CMContacts* pObj = new CMContacts(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMContactsFieldID.nativeJavaObj, (int)pObj);
}

static void CMContacts_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMContacts *pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMContacts* pCookie = (callback_cookie_CMContacts *)env->GetIntField(
        thiz, gCMContactsFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMContactsFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMContactsFieldID.jniData, 0);
}

static jint CMContacts_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMContacts_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    extern fields_t gTContactsItemFieldID;
    TContactsItem* pItem = (TContactsItem*)env->GetIntField(item, gTContactsItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMContacts_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    extern fields_t gTContactsItemFieldID;
    TContactsItem* pItem = (TContactsItem*)env->GetIntField(obj, gTContactsItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMContacts_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    extern fields_t gTContactsItemFieldID;
    TContactsItem* pItem = (TContactsItem*)env->GetIntField(obj, gTContactsItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMContacts_IsEnd(JNIEnv* env, jobject thiz)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMContacts_RequestMore(JNIEnv* env, jobject thiz)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMContacts_IsRunning(JNIEnv* env, jobject thiz)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMContacts_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMContacts_Cancel(JNIEnv* env, jobject thiz)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMContacts_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMContacts_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    callback_cookie_CMContacts* pCookie = (callback_cookie_CMContacts *)env->GetIntField(
        thiz, gCMContactsFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMContactsFieldID.callback);
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

static jboolean CMContacts_Search(JNIEnv* env, jobject thiz, jstring skey)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    const jchar* jskey = env->GetStringChars(skey, NULL);
    jsize sizeskey = env->GetStringLength(skey);
    char* pskey = UTF16toUTF8((jchar*)jskey, (size_t*)&sizeskey);
    BOOL ret = pObj->Search(pskey);
    env->ReleaseStringChars(skey, jskey);
    free(pskey);
    return ret;
}

static jboolean CMContacts_QuickSearch(JNIEnv* env, jobject thiz, jstring skey)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    const jchar* jskey = env->GetStringChars(skey, NULL);
    jsize sizeskey = env->GetStringLength(skey);
    char* pskey = UTF16toUTF8((jchar*)jskey, (size_t*)&sizeskey);
    BOOL ret = pObj->QuickSearch(pskey);
    env->ReleaseStringChars(skey, jskey);
    free(pskey);
    return ret;
}

static jboolean CMContacts_RequestByJid(JNIEnv* env, jobject thiz, jstring jid)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    const jchar* jjid = env->GetStringChars(jid, NULL);
    jsize sizejid = env->GetStringLength(jid);
    char* pjid = UTF16toUTF8((jchar*)jjid, (size_t*)&sizejid);
    BOOL ret = pObj->RequestByJid(pjid);
    env->ReleaseStringChars(jid, jjid);
    free(pjid);
    return ret;
}

static jboolean CMContacts_RequestById(JNIEnv* env, jobject thiz, jstring id)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    const jchar* jid = env->GetStringChars(id, NULL);
    jsize sizeid = env->GetStringLength(id);
    char* pid = UTF16toUTF8((jchar*)jid, (size_t*)&sizeid);
    BOOL ret = pObj->RequestById(pid);
    env->ReleaseStringChars(id, jid);
    free(pid);
    return ret;
}

static jboolean CMContacts_addRecentContact(JNIEnv* env, jobject thiz, jobject item)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    extern fields_t gTContactsItemFieldID;
    TContactsItem* pItem = (TContactsItem*)env->GetIntField(item, gTContactsItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->addRecentContact(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMContacts_isAdded(JNIEnv* env, jobject thiz, jobject item)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    extern fields_t gTContactsItemFieldID;
    TContactsItem* pItem = (TContactsItem*)env->GetIntField(item, gTContactsItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->isAdded(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMContacts_RequestOccupantsList(JNIEnv* env, jobject thiz, jstring groupid)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    const jchar* jgroupid = env->GetStringChars(groupid, NULL);
    jsize sizegroupid = env->GetStringLength(groupid);
    char* pgroupid = UTF16toUTF8((jchar*)jgroupid, (size_t*)&sizegroupid);
    BOOL ret = pObj->RequestOccupantsList(pgroupid);
    env->ReleaseStringChars(groupid, jgroupid);
    free(pgroupid);
    return ret;
}

static jboolean CMContacts_RequestTrainList(JNIEnv* env, jobject thiz, jstring trainId)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    const jchar* jtrainId = env->GetStringChars(trainId, NULL);
    jsize sizetrainId = env->GetStringLength(trainId);
    char* ptrainId = UTF16toUTF8((jchar*)jtrainId, (size_t*)&sizetrainId);
    BOOL ret = pObj->RequestTrainList(ptrainId);
    env->ReleaseStringChars(trainId, jtrainId);
    free(ptrainId);
    return ret;
}

static jboolean CMContacts_getRecentContacts(JNIEnv* env, jobject thiz)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    BOOL ret = pObj->getRecentContacts();
    return ret;
}

static jboolean CMContacts_SearchByQaCategory(JNIEnv* env, jobject thiz, jstring sCatID)
{
    CMContacts* pObj = (CMContacts*)env->GetIntField(thiz, gCMContactsFieldID.nativeJavaObj);

    const jchar* jsCatID = env->GetStringChars(sCatID, NULL);
    jsize sizesCatID = env->GetStringLength(sCatID);
    char* psCatID = UTF16toUTF8((jchar*)jsCatID, (size_t*)&sizesCatID);
    BOOL ret = pObj->SearchByQaCategory(psCatID);
    env->ReleaseStringChars(sCatID, jsCatID);
    free(psCatID);
    return ret;
}

int register_com_wunding_mlplayer_business_CMContacts(JNIEnv* env) {
    static JNINativeMethod CMContactsMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMContacts_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMContacts_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMContacts_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TContactsItem;)Z", (void*)CMContacts_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TContactsItem;)Z", (void*)CMContacts_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TContactsItem;)Z", (void*)CMContacts_Update },
        { "IsEnd", "()Z", (void*)CMContacts_IsEnd },
        { "RequestMore", "()Z", (void*)CMContacts_RequestMore },
        { "IsRunning", "()Z", (void*)CMContacts_IsRunning },
        { "IsRefresh", "()Z", (void*)CMContacts_IsRefresh },
        { "Cancel", "()V", (void*)CMContacts_Cancel },
        { "SetRequestType", "(I)V", (void*)CMContacts_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMContacts_SetListener },
        { "Search", "(Ljava/lang/String;)Z", (void*)CMContacts_Search },
        { "QuickSearch", "(Ljava/lang/String;)Z", (void*)CMContacts_QuickSearch },
        { "RequestByJid", "(Ljava/lang/String;)Z", (void*)CMContacts_RequestByJid },
        { "RequestById", "(Ljava/lang/String;)Z", (void*)CMContacts_RequestById },
        { "addRecentContact", "(Lcom/wunding/mlplayer/business/TContactsItem;)Z", (void*)CMContacts_addRecentContact },
        { "isAdded", "(Lcom/wunding/mlplayer/business/TContactsItem;)Z", (void*)CMContacts_isAdded },
        { "RequestOccupantsList", "(Ljava/lang/String;)Z", (void*)CMContacts_RequestOccupantsList },
        { "RequestTrainList", "(Ljava/lang/String;)Z", (void*)CMContacts_RequestTrainList },
        { "getRecentContacts", "()Z", (void*)CMContacts_getRecentContacts },
        { "SearchByQaCategory", "(Ljava/lang/String;)Z", (void*)CMContacts_SearchByQaCategory }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMContacts");
    if (clazz == 0) {
        CM_ERR("class CMContacts no found");
        return -1;
    }

    gCMContactsFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMContactsFieldID.nativeJavaObj == 0) {
        CM_ERR("CMContacts no found mNativeObj");
        return -1;
    }

    gCMContactsFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMContactsFieldID.jniData == 0) {
        CM_ERR("CMContacts no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMContactsFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMContactsFieldID.callback == NULL) {
        CM_ERR("CMContacts no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMContactsMethods,
            sizeof(CMContactsMethods) / sizeof(CMContactsMethods[0]));
}


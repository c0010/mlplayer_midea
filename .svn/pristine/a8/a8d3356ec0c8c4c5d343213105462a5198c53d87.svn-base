// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmsettings_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmsettings.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gCMSettingsFieldID;

static void CMSettings_nativeConstructor(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = CMSettings::GetInstance();

    env->SetIntField(thiz, gCMSettingsFieldID.nativeJavaObj, (int)pObj);
}

static void CMSettings_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);
}

static jboolean CMSettings_Load(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    BOOL ret = pObj->Load();
    return ret;
}

static jboolean CMSettings_Load(JNIEnv* env, jobject thiz, jstring customer, jstring user)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jcustomer = env->GetStringChars(customer, NULL);
    jsize sizecustomer = env->GetStringLength(customer);
    char* pcustomer = UTF16toUTF8((jchar*)jcustomer, (size_t*)&sizecustomer);
    const jchar* juser = env->GetStringChars(user, NULL);
    jsize sizeuser = env->GetStringLength(user);
    char* puser = UTF16toUTF8((jchar*)juser, (size_t*)&sizeuser);
    BOOL ret = pObj->Load(pcustomer, puser);
    env->ReleaseStringChars(customer, jcustomer);
    free(pcustomer);
    env->ReleaseStringChars(user, juser);
    free(puser);
    return ret;
}

static jboolean CMSettings_Save(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    BOOL ret = pObj->Save();
    return ret;
}

static jboolean CMSettings_DeleteCache(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    BOOL ret = pObj->DeleteCache();
    return ret;
}

static jint CMSettings_GetAPId(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    int ret = pObj->GetAPId();
    return ret;
}

static void CMSettings_SetAPId(JNIEnv* env, jobject thiz, jint nID)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    pObj->SetAPId(nID);
}

static jint CMSettings_GetBufTime(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    int ret = pObj->GetBufTime();
    return ret;
}

static void CMSettings_SetBufTime(JNIEnv* env, jobject thiz, jint nSecond)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    pObj->SetBufTime(nSecond);
}

static jint CMSettings_GetPlayMode(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    int ret = pObj->GetPlayMode();
    return ret;
}

static void CMSettings_SetPlayMode(JNIEnv* env, jobject thiz, jint nMode)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    pObj->SetPlayMode(nMode);
}

static jint CMSettings_GetFullScreenMode(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    int ret = pObj->GetFullScreenMode();
    return ret;
}

static void CMSettings_SetFullScreenMode(JNIEnv* env, jobject thiz, jint nMode)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    pObj->SetFullScreenMode(nMode);
}

static jboolean CMSettings_GetNewContent(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    BOOL ret = pObj->GetNewContent();
    return ret;
}

static void CMSettings_SetNewContent(JNIEnv* env, jobject thiz, jboolean nFlag)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    pObj->SetNewContent(nFlag);
}

static jboolean CMSettings_GetShake(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    BOOL ret = pObj->GetShake();
    return ret;
}

static void CMSettings_SetShake(JNIEnv* env, jobject thiz, jboolean nFlag)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    pObj->SetShake(nFlag);
}

static jboolean CMSettings_GetAutoLoadMore(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    BOOL ret = pObj->GetAutoLoadMore();
    return ret;
}

static void CMSettings_SetAutoLoadMore(JNIEnv* env, jobject thiz, jboolean nFlag)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    pObj->SetAutoLoadMore(nFlag);
}

static jboolean CMSettings_GetAutoLogin(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    BOOL ret = pObj->GetAutoLogin();
    return ret;
}

static void CMSettings_SetAutoLogin(JNIEnv* env, jobject thiz, jboolean bAutoLogin)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    pObj->SetAutoLogin(bAutoLogin);
}

static jstring CMSettings_GetUserName(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetUserName();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetUserName(JNIEnv* env, jobject thiz, jstring name)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jname = env->GetStringChars(name, NULL);
    jsize sizename = env->GetStringLength(name);
    char* pname = UTF16toUTF8((jchar*)jname, (size_t*)&sizename);
    pObj->SetUserName(pname);
    env->ReleaseStringChars(name, jname);
    free(pname);
}

static jstring CMSettings_GetUserPass(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetUserPass();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetUserPass(JNIEnv* env, jobject thiz, jstring pass)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jpass = env->GetStringChars(pass, NULL);
    jsize sizepass = env->GetStringLength(pass);
    char* ppass = UTF16toUTF8((jchar*)jpass, (size_t*)&sizepass);
    pObj->SetUserPass(ppass);
    env->ReleaseStringChars(pass, jpass);
    free(ppass);
}

static jint CMSettings_GetRotation(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    int ret = pObj->GetRotation();
    return ret;
}

static jstring CMSettings_GetCenterServerUrl(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetCenterServerUrl();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetCenterServerUrl(JNIEnv* env, jobject thiz, jstring name)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jname = env->GetStringChars(name, NULL);
    jsize sizename = env->GetStringLength(name);
    char* pname = UTF16toUTF8((jchar*)jname, (size_t*)&sizename);
    pObj->SetCenterServerUrl(pname);
    env->ReleaseStringChars(name, jname);
    free(pname);
}

static jstring CMSettings_GetServerUrl(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetServerUrl();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetServerUrl(JNIEnv* env, jobject thiz, jstring name)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jname = env->GetStringChars(name, NULL);
    jsize sizename = env->GetStringLength(name);
    char* pname = UTF16toUTF8((jchar*)jname, (size_t*)&sizename);
    pObj->SetServerUrl(pname);
    env->ReleaseStringChars(name, jname);
    free(pname);
}

static jstring CMSettings_GetCustomer(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetCustomer();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetCustomer(JNIEnv* env, jobject thiz, jstring name)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jname = env->GetStringChars(name, NULL);
    jsize sizename = env->GetStringLength(name);
    char* pname = UTF16toUTF8((jchar*)jname, (size_t*)&sizename);
    pObj->SetCustomer(pname);
    env->ReleaseStringChars(name, jname);
    free(pname);
}

static jboolean CMSettings_GetSelServer(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    BOOL ret = pObj->GetSelServer();
    return ret;
}

static void CMSettings_SetSelServer(JNIEnv* env, jobject thiz, jboolean bSelServer)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    pObj->SetSelServer(bSelServer);
}

static jstring CMSettings_GetUserId(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetUserId();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetUserId(JNIEnv* env, jobject thiz, jstring uid)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* juid = env->GetStringChars(uid, NULL);
    jsize sizeuid = env->GetStringLength(uid);
    char* puid = UTF16toUTF8((jchar*)juid, (size_t*)&sizeuid);
    pObj->SetUserId(puid);
    env->ReleaseStringChars(uid, juid);
    free(puid);
}

static jstring CMSettings_GetSID(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetSID();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetSID(JNIEnv* env, jobject thiz, jstring sid)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jsid = env->GetStringChars(sid, NULL);
    jsize sizesid = env->GetStringLength(sid);
    char* psid = UTF16toUTF8((jchar*)jsid, (size_t*)&sizesid);
    pObj->SetSID(psid);
    env->ReleaseStringChars(sid, jsid);
    free(psid);
}

static jstring CMSettings_GetXMPPJid(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetXMPPJid();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetXMPPJid(JNIEnv* env, jobject thiz, jstring jid)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jjid = env->GetStringChars(jid, NULL);
    jsize sizejid = env->GetStringLength(jid);
    char* pjid = UTF16toUTF8((jchar*)jjid, (size_t*)&sizejid);
    pObj->SetXMPPJid(pjid);
    env->ReleaseStringChars(jid, jjid);
    free(pjid);
}

static jstring CMSettings_GetXMPPPwd(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetXMPPPwd();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetXMPPPwd(JNIEnv* env, jobject thiz, jstring pwd)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jpwd = env->GetStringChars(pwd, NULL);
    jsize sizepwd = env->GetStringLength(pwd);
    char* ppwd = UTF16toUTF8((jchar*)jpwd, (size_t*)&sizepwd);
    pObj->SetXMPPPwd(ppwd);
    env->ReleaseStringChars(pwd, jpwd);
    free(ppwd);
}

static jstring CMSettings_GetXMPPHostname(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetXMPPHostname();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetXMPPHostname(JNIEnv* env, jobject thiz, jstring hostname)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jhostname = env->GetStringChars(hostname, NULL);
    jsize sizehostname = env->GetStringLength(hostname);
    char* phostname = UTF16toUTF8((jchar*)jhostname, (size_t*)&sizehostname);
    pObj->SetXMPPHostname(phostname);
    env->ReleaseStringChars(hostname, jhostname);
    free(phostname);
}

static jstring CMSettings_GetXMPPManager(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetXMPPManager();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static void CMSettings_SetXMPPManager(JNIEnv* env, jobject thiz, jstring managerjid)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const jchar* jmanagerjid = env->GetStringChars(managerjid, NULL);
    jsize sizemanagerjid = env->GetStringLength(managerjid);
    char* pmanagerjid = UTF16toUTF8((jchar*)jmanagerjid, (size_t*)&sizemanagerjid);
    pObj->SetXMPPManager(pmanagerjid);
    env->ReleaseStringChars(managerjid, jmanagerjid);
    free(pmanagerjid);
}

static jstring CMSettings_GetDefautlEnterpriseID(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetDefautlEnterpriseID();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMSettings_GetDefautlEnterpriseTitle(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetDefautlEnterpriseTitle();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring CMSettings_GetDefautlEnterpriseSlogan(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    const char* ret = pObj->GetDefautlEnterpriseSlogan();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMSettings_Logout(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    BOOL ret = pObj->Logout();
    return ret;
}

static jboolean CMSettings_LogoutWithClearSid(JNIEnv* env, jobject thiz)
{
    CMSettings* pObj = (CMSettings*)env->GetIntField(thiz, gCMSettingsFieldID.nativeJavaObj);

    BOOL ret = pObj->LogoutWithClearSid();
    return ret;
}

int register_com_wunding_mlplayer_business_CMSettings(JNIEnv* env) {
    static jboolean (*CMSettings_Load1)(JNIEnv*, jobject);
    CMSettings_Load1 = CMSettings_Load;
    static jboolean (*CMSettings_Load2)(JNIEnv*, jobject, jstring, jstring);
    CMSettings_Load2 = CMSettings_Load;

    static JNINativeMethod CMSettingsMethods[] = {
        { "nativeConstructor", "()V", (void*)CMSettings_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMSettings_nativeDestructor },
        { "Load", "()Z", (void*)CMSettings_Load1 },
        { "Load", "(Ljava/lang/String;Ljava/lang/String;)Z", (void*)CMSettings_Load2 },
        { "Save", "()Z", (void*)CMSettings_Save },
        { "DeleteCache", "()Z", (void*)CMSettings_DeleteCache },
        { "GetAPId", "()I", (void*)CMSettings_GetAPId },
        { "SetAPId", "(I)V", (void*)CMSettings_SetAPId },
        { "GetBufTime", "()I", (void*)CMSettings_GetBufTime },
        { "SetBufTime", "(I)V", (void*)CMSettings_SetBufTime },
        { "GetPlayMode", "()I", (void*)CMSettings_GetPlayMode },
        { "SetPlayMode", "(I)V", (void*)CMSettings_SetPlayMode },
        { "GetFullScreenMode", "()I", (void*)CMSettings_GetFullScreenMode },
        { "SetFullScreenMode", "(I)V", (void*)CMSettings_SetFullScreenMode },
        { "GetNewContent", "()Z", (void*)CMSettings_GetNewContent },
        { "SetNewContent", "(Z)V", (void*)CMSettings_SetNewContent },
        { "GetShake", "()Z", (void*)CMSettings_GetShake },
        { "SetShake", "(Z)V", (void*)CMSettings_SetShake },
        { "GetAutoLoadMore", "()Z", (void*)CMSettings_GetAutoLoadMore },
        { "SetAutoLoadMore", "(Z)V", (void*)CMSettings_SetAutoLoadMore },
        { "GetAutoLogin", "()Z", (void*)CMSettings_GetAutoLogin },
        { "SetAutoLogin", "(Z)V", (void*)CMSettings_SetAutoLogin },
        { "GetUserName", "()Ljava/lang/String;", (void*)CMSettings_GetUserName },
        { "SetUserName", "(Ljava/lang/String;)V", (void*)CMSettings_SetUserName },
        { "GetUserPass", "()Ljava/lang/String;", (void*)CMSettings_GetUserPass },
        { "SetUserPass", "(Ljava/lang/String;)V", (void*)CMSettings_SetUserPass },
        { "GetRotation", "()I", (void*)CMSettings_GetRotation },
        { "GetCenterServerUrl", "()Ljava/lang/String;", (void*)CMSettings_GetCenterServerUrl },
        { "SetCenterServerUrl", "(Ljava/lang/String;)V", (void*)CMSettings_SetCenterServerUrl },
        { "GetServerUrl", "()Ljava/lang/String;", (void*)CMSettings_GetServerUrl },
        { "SetServerUrl", "(Ljava/lang/String;)V", (void*)CMSettings_SetServerUrl },
        { "GetCustomer", "()Ljava/lang/String;", (void*)CMSettings_GetCustomer },
        { "SetCustomer", "(Ljava/lang/String;)V", (void*)CMSettings_SetCustomer },
        { "GetSelServer", "()Z", (void*)CMSettings_GetSelServer },
        { "SetSelServer", "(Z)V", (void*)CMSettings_SetSelServer },
        { "GetUserId", "()Ljava/lang/String;", (void*)CMSettings_GetUserId },
        { "SetUserId", "(Ljava/lang/String;)V", (void*)CMSettings_SetUserId },
        { "GetSID", "()Ljava/lang/String;", (void*)CMSettings_GetSID },
        { "SetSID", "(Ljava/lang/String;)V", (void*)CMSettings_SetSID },
        { "GetXMPPJid", "()Ljava/lang/String;", (void*)CMSettings_GetXMPPJid },
        { "SetXMPPJid", "(Ljava/lang/String;)V", (void*)CMSettings_SetXMPPJid },
        { "GetXMPPPwd", "()Ljava/lang/String;", (void*)CMSettings_GetXMPPPwd },
        { "SetXMPPPwd", "(Ljava/lang/String;)V", (void*)CMSettings_SetXMPPPwd },
        { "GetXMPPHostname", "()Ljava/lang/String;", (void*)CMSettings_GetXMPPHostname },
        { "SetXMPPHostname", "(Ljava/lang/String;)V", (void*)CMSettings_SetXMPPHostname },
        { "GetXMPPManager", "()Ljava/lang/String;", (void*)CMSettings_GetXMPPManager },
        { "SetXMPPManager", "(Ljava/lang/String;)V", (void*)CMSettings_SetXMPPManager },
        { "GetDefautlEnterpriseID", "()Ljava/lang/String;", (void*)CMSettings_GetDefautlEnterpriseID },
        { "GetDefautlEnterpriseTitle", "()Ljava/lang/String;", (void*)CMSettings_GetDefautlEnterpriseTitle },
        { "GetDefautlEnterpriseSlogan", "()Ljava/lang/String;", (void*)CMSettings_GetDefautlEnterpriseSlogan },
        { "Logout", "()Z", (void*)CMSettings_Logout },
        { "LogoutWithClearSid", "()Z", (void*)CMSettings_LogoutWithClearSid }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMSettings");
    if (clazz == 0) {
        CM_ERR("class CMSettings no found");
        return -1;
    }

    gCMSettingsFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMSettingsFieldID.nativeJavaObj == 0) {
        CM_ERR("CMSettings no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMSettingsMethods,
            sizeof(CMSettingsMethods) / sizeof(CMSettingsMethods[0]));
}


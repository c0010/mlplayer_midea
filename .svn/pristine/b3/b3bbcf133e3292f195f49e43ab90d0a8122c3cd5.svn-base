// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmcategory_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmcategory.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"


struct callback_cookie_CMCategory {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMCategoryFieldID;

static void CMCategory_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMCategory when setting up callback.");
        return;
    }
    callback_cookie_CMCategory* pCookie = new callback_cookie_CMCategory;
    pCookie->listener1 = new CMUpdateDataListener(gCMCategoryFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMCategoryFieldID.jniData, (int)pCookie);

    CMCategory* pObj = CMCategory::GetInstance();
    pObj->SetListener(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMCategoryFieldID.nativeJavaObj, (int)pObj);
}

static void CMCategory_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMCategory *pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMCategory* pCookie = (callback_cookie_CMCategory *)env->GetIntField(
        thiz, gCMCategoryFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMCategoryFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMCategoryFieldID.jniData, 0);
}

static jint CMCategory_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMCategory_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    extern fields_t gCMCategoryItemFieldID;
    CMCategoryItem* pItem = NULL;
    jboolean ret = pObj->GetItem(nIndex, pItem);

    env->SetIntField(item, gCMCategoryItemFieldID.nativeJavaObj, (int)pItem);

    return ret;
}

static jboolean CMCategory_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    extern fields_t gCMCategoryItemFieldID;
    CMCategoryItem* pItem = (CMCategoryItem*)env->GetIntField(obj, gCMCategoryItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMCategory_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    extern fields_t gCMCategoryItemFieldID;
    CMCategoryItem* pItem = (CMCategoryItem*)env->GetIntField(obj, gCMCategoryItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMCategory_IsEnd(JNIEnv* env, jobject thiz)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMCategory_RequestMore(JNIEnv* env, jobject thiz)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMCategory_IsRunning(JNIEnv* env, jobject thiz)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMCategory_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMCategory_Cancel(JNIEnv* env, jobject thiz)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMCategory_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMCategory_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    callback_cookie_CMCategory* pCookie = (callback_cookie_CMCategory *)env->GetIntField(
        thiz, gCMCategoryFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMCategoryFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

    }
}

static jboolean CMCategory_UpdateData(JNIEnv* env, jobject thiz)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->UpdateData();
    return ret;
}

static jboolean CMCategory_UpdateCategoryList(JNIEnv* env, jobject thiz)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->UpdateCategoryList();
    return ret;
}

static jint CMCategory_TopItemCount(JNIEnv* env, jobject thiz)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    int ret = pObj->TopItemCount();
    return ret;
}

static jobject CMCategory_GetTopItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    CMCategoryItem* pRet = pObj->GetTopItem(nIndex);
    if (pRet == NULL) return NULL;

    jclass retClazz = env->FindClass("com/wunding/mlplayer/business/CMCategoryItem");
    if (retClazz == NULL) {
        CM_ERR("Can't find class CMCategoryItem");
        return NULL;
    }

    jmethodID retConstructor = env->GetMethodID(retClazz, "<init>", "(I)V");
    if (retConstructor == NULL) {
        CM_ERR("Can't find class CMCategoryItem native constructor");
        return NULL;
    }

    return env->NewObject(retClazz,
            retConstructor, (int)pRet);
}

static void CMCategory_SetExamSurveyCount(JNIEnv* env, jobject thiz, jint count, jstring type)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    const jchar* jtype = env->GetStringChars(type, NULL);
    jsize sizetype = env->GetStringLength(type);
    char* ptype = UTF16toUTF8((jchar*)jtype, (size_t*)&sizetype);
    pObj->SetExamSurveyCount(count, ptype);
    env->ReleaseStringChars(type, jtype);
    free(ptype);
}

static jboolean CMCategory_GetCacheData(JNIEnv* env, jobject thiz)
{
    CMCategory* pObj = (CMCategory*)env->GetIntField(thiz, gCMCategoryFieldID.nativeJavaObj);

    BOOL ret = pObj->GetCacheData();
    return ret;
}

int register_com_wunding_mlplayer_business_CMCategory(JNIEnv* env) {
    static JNINativeMethod CMCategoryMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMCategory_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMCategory_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMCategory_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/CMCategoryItem;)Z", (void*)CMCategory_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/CMCategoryItem;)Z", (void*)CMCategory_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/CMCategoryItem;)Z", (void*)CMCategory_Update },
        { "IsEnd", "()Z", (void*)CMCategory_IsEnd },
        { "RequestMore", "()Z", (void*)CMCategory_RequestMore },
        { "IsRunning", "()Z", (void*)CMCategory_IsRunning },
        { "IsRefresh", "()Z", (void*)CMCategory_IsRefresh },
        { "Cancel", "()V", (void*)CMCategory_Cancel },
        { "SetRequestType", "(I)V", (void*)CMCategory_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMCategory_SetListener },
        { "UpdateData", "()Z", (void*)CMCategory_UpdateData },
        { "UpdateCategoryList", "()Z", (void*)CMCategory_UpdateCategoryList },
        { "TopItemCount", "()I", (void*)CMCategory_TopItemCount },
        { "GetTopItem", "(I)Lcom/wunding/mlplayer/business/CMCategoryItem;", (void*)CMCategory_GetTopItem },
        { "SetExamSurveyCount", "(ILjava/lang/String;)V", (void*)CMCategory_SetExamSurveyCount },
        { "GetCacheData", "()Z", (void*)CMCategory_GetCacheData }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMCategory");
    if (clazz == 0) {
        CM_ERR("class CMCategory no found");
        return -1;
    }

    gCMCategoryFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMCategoryFieldID.nativeJavaObj == 0) {
        CM_ERR("CMCategory no found mNativeObj");
        return -1;
    }

    gCMCategoryFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMCategoryFieldID.jniData == 0) {
        CM_ERR("CMCategory no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMCategoryFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMCategoryFieldID.callback == NULL) {
        CM_ERR("CMCategory no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMCategoryMethods,
            sizeof(CMCategoryMethods) / sizeof(CMCategoryMethods[0]));
}

fields_t gCMCategoryItemFieldID;

static void CMCategoryItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
}

static void CMCategoryItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    env->SetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj, 0);
}

static jint CMCategoryItem_FrontChildItemCount(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    int ret = pObj->FrontChildItemCount();
    return ret;
}

static jint CMCategoryItem_ChildItemCount(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    int ret = pObj->ChildItemCount();
    return ret;
}

static jobject CMCategoryItem_GetChildItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    CMCategoryItem* pRet = pObj->GetChildItem(nIndex);
    if (pRet == NULL) return NULL;

    jclass retClazz = env->FindClass("com/wunding/mlplayer/business/CMCategoryItem");
    if (retClazz == NULL) {
        CM_ERR("Can't find class CMCategoryItem");
        return NULL;
    }

    jmethodID retConstructor = env->GetMethodID(retClazz, "<init>", "(I)V");
    if (retConstructor == NULL) {
        CM_ERR("Can't find class CMCategoryItem native constructor");
        return NULL;
    }

    return env->NewObject(retClazz,
            retConstructor, (int)pRet);
}

static jint CMCategoryItem_GetPositionCourseItem(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    int ret = pObj->GetPositionCourseItem();
    return ret;
}

static jint CMCategoryItem_EnablesubscriptionChildItemCount(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    int ret = pObj->EnablesubscriptionChildItemCount();
    return ret;
}

static jint CMCategoryItem_SelectedChildItemCount(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    int ret = pObj->SelectedChildItemCount();
    return ret;
}

static jobject CMCategoryItem_GetSelectedChildItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    CMCategoryItem* pRet = pObj->GetSelectedChildItem(nIndex);
    if (pRet == NULL) return NULL;

    jclass retClazz = env->FindClass("com/wunding/mlplayer/business/CMCategoryItem");
    if (retClazz == NULL) {
        CM_ERR("Can't find class CMCategoryItem");
        return NULL;
    }

    jmethodID retConstructor = env->GetMethodID(retClazz, "<init>", "(I)V");
    if (retConstructor == NULL) {
        CM_ERR("Can't find class CMCategoryItem native constructor");
        return NULL;
    }

    return env->NewObject(retClazz,
            retConstructor, (int)pRet);
}

static void CMCategoryItem_RemoveChildItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    pObj->RemoveChildItem(nIndex);
}

static jobject CMCategoryItem_GetEnablesubscriptionChildItem(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    CMCategoryItem* pRet = pObj->GetEnablesubscriptionChildItem(nIndex);
    if (pRet == NULL) return NULL;

    jclass retClazz = env->FindClass("com/wunding/mlplayer/business/CMCategoryItem");
    if (retClazz == NULL) {
        CM_ERR("Can't find class CMCategoryItem");
        return NULL;
    }

    jmethodID retConstructor = env->GetMethodID(retClazz, "<init>", "(I)V");
    if (retConstructor == NULL) {
        CM_ERR("Can't find class CMCategoryItem native constructor");
        return NULL;
    }

    return env->NewObject(retClazz,
            retConstructor, (int)pRet);
}

static jboolean CMCategoryItem_GetSubscription(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    BOOL ret = pObj->GetSubscription();
    return ret;
}

static void CMCategoryItem_SetSubscription(JNIEnv* env, jobject thiz, jboolean bFlag)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);

    pObj->SetSubscription(bFlag);
}

static jstring CMCategoryItem_GetID(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID);
    jchar* data = UTF8toUTF16((char*)pObj->sID, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMCategoryItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
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

static jstring CMCategoryItem_GetType(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sType);
    jchar* data = UTF8toUTF16((char*)pObj->sType, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMCategoryItem_SetType(JNIEnv* env, jobject thiz, jstring sType)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sType, NULL);
    jsize size = env->GetStringLength(sType);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sType, (const char*)data, 15);
    pObj->sType[15] = '\0';

    env->ReleaseStringChars(sType, jChar);
    
    free(data);
    
    return true;
}

static jstring CMCategoryItem_GetTitle(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle);
    jchar* data = UTF8toUTF16((char*)pObj->sTitle, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMCategoryItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
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

static jstring CMCategoryItem_GetImage(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sImage);
    jchar* data = UTF8toUTF16((char*)pObj->sImage, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMCategoryItem_SetImage(JNIEnv* env, jobject thiz, jstring sImage)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
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

static jboolean CMCategoryItem_GetEnablesubscription(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bEnablesubscription;
}
                
static jboolean CMCategoryItem_SetEnablesubscription(JNIEnv* env, jobject thiz, jboolean bEnablesubscription)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bEnablesubscription = bEnablesubscription;
    return true;
}
                
static jint CMCategoryItem_GetItemcount(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nItemcount;
}
                
static jboolean CMCategoryItem_SetItemcount(JNIEnv* env, jobject thiz, jint nItemcount)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nItemcount = nItemcount;
    return true;
}
                
static jboolean CMCategoryItem_GetIsSelected(JNIEnv* env, jobject thiz)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bIsSelected;
}
                
static jboolean CMCategoryItem_SetIsSelected(JNIEnv* env, jobject thiz, jboolean bIsSelected)
{
    CMCategoryItem* pObj = (CMCategoryItem*)env->GetIntField(thiz, gCMCategoryItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bIsSelected = bIsSelected;
    return true;
}
                
int register_com_wunding_mlplayer_business_CMCategoryItem(JNIEnv* env) {
    static JNINativeMethod CMCategoryItemMethods[] = {
        { "nativeConstructor", "()V", (void*)CMCategoryItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMCategoryItem_nativeDestructor },
        { "FrontChildItemCount", "()I", (void*)CMCategoryItem_FrontChildItemCount },
        { "ChildItemCount", "()I", (void*)CMCategoryItem_ChildItemCount },
        { "GetChildItem", "(I)Lcom/wunding/mlplayer/business/CMCategoryItem;", (void*)CMCategoryItem_GetChildItem },
        { "GetPositionCourseItem", "()I", (void*)CMCategoryItem_GetPositionCourseItem },
        { "EnablesubscriptionChildItemCount", "()I", (void*)CMCategoryItem_EnablesubscriptionChildItemCount },
        { "SelectedChildItemCount", "()I", (void*)CMCategoryItem_SelectedChildItemCount },
        { "GetSelectedChildItem", "(I)Lcom/wunding/mlplayer/business/CMCategoryItem;", (void*)CMCategoryItem_GetSelectedChildItem },
        { "RemoveChildItem", "(I)V", (void*)CMCategoryItem_RemoveChildItem },
        { "GetEnablesubscriptionChildItem", "(I)Lcom/wunding/mlplayer/business/CMCategoryItem;", (void*)CMCategoryItem_GetEnablesubscriptionChildItem },
        { "GetSubscription", "()Z", (void*)CMCategoryItem_GetSubscription },
        { "SetSubscription", "(Z)V", (void*)CMCategoryItem_SetSubscription },
        { "GetID", "()Ljava/lang/String;", (void*)CMCategoryItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)CMCategoryItem_SetID },
        { "GetType", "()Ljava/lang/String;", (void*)CMCategoryItem_GetType },
        { "SetType", "(Ljava/lang/String;)Z", (void*)CMCategoryItem_SetType },
        { "GetTitle", "()Ljava/lang/String;", (void*)CMCategoryItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)CMCategoryItem_SetTitle },
        { "GetImage", "()Ljava/lang/String;", (void*)CMCategoryItem_GetImage },
        { "SetImage", "(Ljava/lang/String;)Z", (void*)CMCategoryItem_SetImage },
        { "GetEnablesubscription", "()Z", (void*)CMCategoryItem_GetEnablesubscription },
        { "SetEnablesubscription", "(Z)Z", (void*)CMCategoryItem_SetEnablesubscription },
        { "GetItemcount", "()I", (void*)CMCategoryItem_GetItemcount },
        { "SetItemcount", "(I)Z", (void*)CMCategoryItem_SetItemcount },
        { "GetIsSelected", "()Z", (void*)CMCategoryItem_GetIsSelected },
        { "SetIsSelected", "(Z)Z", (void*)CMCategoryItem_SetIsSelected }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMCategoryItem");
    if (clazz == 0) {
        CM_ERR("class CMCategoryItem no found");
        return -1;
    }

    gCMCategoryItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMCategoryItemFieldID.nativeJavaObj == 0) {
        CM_ERR("CMCategoryItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMCategoryItemMethods,
            sizeof(CMCategoryItemMethods) / sizeof(CMCategoryItemMethods[0]));
}


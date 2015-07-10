// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmgetnewcontent_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmgetnewcontent.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTNewContentItemFieldID;

static void TNewContentItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TNewContentItem* pObj = new TNewContentItem();

    env->SetIntField(thiz, gTNewContentItemFieldID.nativeJavaObj, (int)pObj);
}

static void TNewContentItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TNewContentItem*)env->GetIntField(thiz, gTNewContentItemFieldID.nativeJavaObj);
}

static jstring TNewContentItem_GetType(JNIEnv* env, jobject thiz)
{
    TNewContentItem* pObj = (TNewContentItem*)env->GetIntField(thiz, gTNewContentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sType);
    jchar* data = UTF8toUTF16((char*)pObj->sType, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TNewContentItem_SetType(JNIEnv* env, jobject thiz, jstring sType)
{
    TNewContentItem* pObj = (TNewContentItem*)env->GetIntField(thiz, gTNewContentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sType, NULL);
    jsize size = env->GetStringLength(sType);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sType, (const char*)data, 19);
    pObj->sType[19] = '\0';

    env->ReleaseStringChars(sType, jChar);
    
    free(data);
    
    return true;
}

static jstring TNewContentItem_GetTitle(JNIEnv* env, jobject thiz)
{
    TNewContentItem* pObj = (TNewContentItem*)env->GetIntField(thiz, gTNewContentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sTitle);
    jchar* data = UTF8toUTF16((char*)pObj->sTitle, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TNewContentItem_SetTitle(JNIEnv* env, jobject thiz, jstring sTitle)
{
    TNewContentItem* pObj = (TNewContentItem*)env->GetIntField(thiz, gTNewContentItemFieldID.nativeJavaObj);
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

static jstring TNewContentItem_GetDescription(JNIEnv* env, jobject thiz)
{
    TNewContentItem* pObj = (TNewContentItem*)env->GetIntField(thiz, gTNewContentItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDescription);
    jchar* data = UTF8toUTF16((char*)pObj->sDescription, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TNewContentItem_SetDescription(JNIEnv* env, jobject thiz, jstring sDescription)
{
    TNewContentItem* pObj = (TNewContentItem*)env->GetIntField(thiz, gTNewContentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDescription, NULL);
    jsize size = env->GetStringLength(sDescription);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    utf8ncpy(pObj->sDescription, (const char*)data, 249);
    pObj->sDescription[249] = '\0';

    env->ReleaseStringChars(sDescription, jChar);
    
    free(data);
    
    return true;
}

static jint TNewContentItem_GetModel(JNIEnv* env, jobject thiz)
{
    TNewContentItem* pObj = (TNewContentItem*)env->GetIntField(thiz, gTNewContentItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nModel;
}
                
static jboolean TNewContentItem_SetModel(JNIEnv* env, jobject thiz, jint nModel)
{
    TNewContentItem* pObj = (TNewContentItem*)env->GetIntField(thiz, gTNewContentItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nModel = nModel;
    return true;
}
                
int register_com_wunding_mlplayer_business_TNewContentItem(JNIEnv* env) {
    static JNINativeMethod TNewContentItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TNewContentItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TNewContentItem_nativeDestructor },
        { "GetType", "()Ljava/lang/String;", (void*)TNewContentItem_GetType },
        { "SetType", "(Ljava/lang/String;)Z", (void*)TNewContentItem_SetType },
        { "GetTitle", "()Ljava/lang/String;", (void*)TNewContentItem_GetTitle },
        { "SetTitle", "(Ljava/lang/String;)Z", (void*)TNewContentItem_SetTitle },
        { "GetDescription", "()Ljava/lang/String;", (void*)TNewContentItem_GetDescription },
        { "SetDescription", "(Ljava/lang/String;)Z", (void*)TNewContentItem_SetDescription },
        { "GetModel", "()I", (void*)TNewContentItem_GetModel },
        { "SetModel", "(I)Z", (void*)TNewContentItem_SetModel }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TNewContentItem");
    if (clazz == 0) {
        CM_ERR("class TNewContentItem no found");
        return -1;
    }

    gTNewContentItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTNewContentItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TNewContentItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TNewContentItemMethods,
            sizeof(TNewContentItemMethods) / sizeof(TNewContentItemMethods[0]));
}


struct callback_cookie_CMGetNewContent {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
};

fields_t gCMGetNewContentFieldID;

static void CMGetNewContent_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMGetNewContent when setting up callback.");
        return;
    }
    callback_cookie_CMGetNewContent* pCookie = new callback_cookie_CMGetNewContent;
    pCookie->listener1 = new CMUpdateDataListener(gCMGetNewContentFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMGetNewContentFieldID.jniData, (int)pCookie);

    CMGetNewContent* pObj = CMGetNewContent::GetInstance();
    pObj->SetListener(pCookie->listener1);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj, (int)pObj);
}

static void CMGetNewContent_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMGetNewContent *pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMGetNewContent* pCookie = (callback_cookie_CMGetNewContent *)env->GetIntField(
        thiz, gCMGetNewContentFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMGetNewContentFieldID.jniData, 0);
}

static void CMGetNewContent_SetListener(JNIEnv* env, jobject thiz, jobject pListener)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    callback_cookie_CMGetNewContent* pCookie = (callback_cookie_CMGetNewContent *)env->GetIntField(
        thiz, gCMGetNewContentFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMGetNewContentFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

    }
}

static void CMGetNewContent_Update(JNIEnv* env, jobject thiz)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    pObj->Update();
}

static void CMGetNewContent_GetNewContent(JNIEnv* env, jobject thiz, jstring sID, jstring sType)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    const jchar* jsID = env->GetStringChars(sID, NULL);
    jsize sizesID = env->GetStringLength(sID);
    char* psID = UTF16toUTF8((jchar*)jsID, (size_t*)&sizesID);
    const jchar* jsType = env->GetStringChars(sType, NULL);
    jsize sizesType = env->GetStringLength(sType);
    char* psType = UTF16toUTF8((jchar*)jsType, (size_t*)&sizesType);
    pObj->GetNewContent(psID, psType);
    env->ReleaseStringChars(sID, jsID);
    free(psID);
    env->ReleaseStringChars(sType, jsType);
    free(psType);
}

static jboolean CMGetNewContent_IsRunning(JNIEnv* env, jobject thiz)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static void CMGetNewContent_Cancel(JNIEnv* env, jobject thiz)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    pObj->Cancel();
}

static jboolean CMGetNewContent_Load(JNIEnv* env, jobject thiz)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    BOOL ret = pObj->Load();
    return ret;
}

static jint CMGetNewContent_GetBrowserItemModel(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    int ret = pObj->GetBrowserItemModel(nIndex);
    return ret;
}

static jint CMGetNewContent_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jint CMGetNewContent_GetItemType(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    int ret = pObj->GetItemType(nIndex);
    return ret;
}

static jboolean CMGetNewContent_GetContentItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    extern fields_t gTNewContentItemFieldID;
    TNewContentItem* pItem = (TNewContentItem*)env->GetIntField(item, gTNewContentItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetContentItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGetNewContent_GetBrowserItem(JNIEnv* env, jobject thiz, jint nIndex, jobject bitem)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    extern fields_t gTBrowserItemFieldID;
    TBrowserItem* pItem = (TBrowserItem*)env->GetIntField(bitem, gTBrowserItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetBrowserItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGetNewContent_GetSurveyItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    extern fields_t gTSurveyListItemFieldID;
    TSurveyListItem* pItem = (TSurveyListItem*)env->GetIntField(item, gTSurveyListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetSurveyItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGetNewContent_GetExamItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    extern fields_t gTExamListItemFieldID;
    TExamListItem* pItem = (TExamListItem*)env->GetIntField(item, gTExamListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetExamItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGetNewContent_GetExerciseItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    extern fields_t gTExerciseListItemFieldID;
    TExerciseListItem* pItem = (TExerciseListItem*)env->GetIntField(item, gTExerciseListItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetExerciseItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGetNewContent_GetQuestionItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    extern fields_t gTQAItemFieldID;
    TQAItem* pItem = (TQAItem*)env->GetIntField(item, gTQAItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetQuestionItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGetNewContent_GetApplyItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    extern fields_t gTTrainApplyItemFieldID;
    TTrainApplyItem* pItem = (TTrainApplyItem*)env->GetIntField(item, gTTrainApplyItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetApplyItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGetNewContent_GetSignInItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    extern fields_t gTTrainSignInItemFieldID;
    TTrainSignInItem* pItem = (TTrainSignInItem*)env->GetIntField(item, gTTrainSignInItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetSignInItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGetNewContent_GetMyTrainItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);

    extern fields_t gTMyTrainItemFieldID;
    TMyTrainItem* pItem = (TMyTrainItem*)env->GetIntField(item, gTMyTrainItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetMyTrainItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMGetNewContent_Get_isPush(JNIEnv* env, jobject thiz)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->m_isPush;
}
                
static jboolean CMGetNewContent_Set_isPush(JNIEnv* env, jobject thiz, jboolean m_isPush)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->m_isPush = m_isPush;
    return true;
}
                
static jstring CMGetNewContent_Get_cmdtype(JNIEnv* env, jobject thiz)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->m_cmdtype.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->m_cmdtype.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMGetNewContent_Set_cmdtype(JNIEnv* env, jobject thiz, jstring m_cmdtype)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(m_cmdtype, NULL);
    jsize size = env->GetStringLength(m_cmdtype);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->m_cmdtype = data;

    env->ReleaseStringChars(m_cmdtype, jChar);
    
    free(data);
    
    return true;
}

static jstring CMGetNewContent_Get_cmdID(JNIEnv* env, jobject thiz)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->m_cmdID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->m_cmdID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean CMGetNewContent_Set_cmdID(JNIEnv* env, jobject thiz, jstring m_cmdID)
{
    CMGetNewContent* pObj = (CMGetNewContent*)env->GetIntField(thiz, gCMGetNewContentFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(m_cmdID, NULL);
    jsize size = env->GetStringLength(m_cmdID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->m_cmdID = data;

    env->ReleaseStringChars(m_cmdID, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_CMGetNewContent(JNIEnv* env) {
    static JNINativeMethod CMGetNewContentMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMGetNewContent_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMGetNewContent_nativeDestructor },
        { "nativeSetListener", "(Ljava/lang/Object;)V", (void*)CMGetNewContent_SetListener },
        { "Update", "()V", (void*)CMGetNewContent_Update },
        { "GetNewContent", "(Ljava/lang/String;Ljava/lang/String;)V", (void*)CMGetNewContent_GetNewContent },
        { "IsRunning", "()Z", (void*)CMGetNewContent_IsRunning },
        { "Cancel", "()V", (void*)CMGetNewContent_Cancel },
        { "Load", "()Z", (void*)CMGetNewContent_Load },
        { "GetBrowserItemModel", "(I)I", (void*)CMGetNewContent_GetBrowserItemModel },
        { "GetItemCount", "()I", (void*)CMGetNewContent_GetItemCount },
        { "GetItemType", "(I)I", (void*)CMGetNewContent_GetItemType },
        { "GetContentItem", "(ILcom/wunding/mlplayer/business/TNewContentItem;)Z", (void*)CMGetNewContent_GetContentItem },
        { "GetBrowserItem", "(ILcom/wunding/mlplayer/business/TBrowserItem;)Z", (void*)CMGetNewContent_GetBrowserItem },
        { "GetSurveyItem", "(ILcom/wunding/mlplayer/business/TSurveyListItem;)Z", (void*)CMGetNewContent_GetSurveyItem },
        { "GetExamItem", "(ILcom/wunding/mlplayer/business/TExamListItem;)Z", (void*)CMGetNewContent_GetExamItem },
        { "GetExerciseItem", "(ILcom/wunding/mlplayer/business/TExerciseListItem;)Z", (void*)CMGetNewContent_GetExerciseItem },
        { "GetQuestionItem", "(ILcom/wunding/mlplayer/business/TQAItem;)Z", (void*)CMGetNewContent_GetQuestionItem },
        { "GetApplyItem", "(ILcom/wunding/mlplayer/business/TTrainApplyItem;)Z", (void*)CMGetNewContent_GetApplyItem },
        { "GetSignInItem", "(ILcom/wunding/mlplayer/business/TTrainSignInItem;)Z", (void*)CMGetNewContent_GetSignInItem },
        { "GetMyTrainItem", "(ILcom/wunding/mlplayer/business/TMyTrainItem;)Z", (void*)CMGetNewContent_GetMyTrainItem },
        { "Get_isPush", "()Z", (void*)CMGetNewContent_Get_isPush },
        { "Set_isPush", "(Z)Z", (void*)CMGetNewContent_Set_isPush },
        { "Get_cmdtype", "()Ljava/lang/String;", (void*)CMGetNewContent_Get_cmdtype },
        { "Set_cmdtype", "(Ljava/lang/String;)Z", (void*)CMGetNewContent_Set_cmdtype },
        { "Get_cmdID", "()Ljava/lang/String;", (void*)CMGetNewContent_Get_cmdID },
        { "Set_cmdID", "(Ljava/lang/String;)Z", (void*)CMGetNewContent_Set_cmdID }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMGetNewContent");
    if (clazz == 0) {
        CM_ERR("class CMGetNewContent no found");
        return -1;
    }

    gCMGetNewContentFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMGetNewContentFieldID.nativeJavaObj == 0) {
        CM_ERR("CMGetNewContent no found mNativeObj");
        return -1;
    }

    gCMGetNewContentFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMGetNewContentFieldID.jniData == 0) {
        CM_ERR("CMGetNewContent no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMGetNewContentFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMGetNewContentFieldID.callback == NULL) {
        CM_ERR("CMGetNewContent no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMGetNewContentMethods,
            sizeof(CMGetNewContentMethods) / sizeof(CMGetNewContentMethods[0]));
}


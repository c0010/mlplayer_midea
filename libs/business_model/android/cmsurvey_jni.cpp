// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmsurvey_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmsurvey.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTSurveyItemFieldID;

static void TSurveyItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TSurveyItem* pObj = new TSurveyItem();

    env->SetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj, (int)pObj);
}

static void TSurveyItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
}

static jstring TSurveyItem_GetID(JNIEnv* env, jobject thiz)
{
    TSurveyItem* pObj = (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSurveyItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TSurveyItem* pObj = (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jint TSurveyItem_GetType(JNIEnv* env, jobject thiz)
{
    TSurveyItem* pObj = (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nType;
}
                
static jboolean TSurveyItem_SetType(JNIEnv* env, jobject thiz, jint nType)
{
    TSurveyItem* pObj = (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nType = nType;
    return true;
}
                
static jstring TSurveyItem_GetCategory(JNIEnv* env, jobject thiz)
{
    TSurveyItem* pObj = (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sCategory.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sCategory.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSurveyItem_SetCategory(JNIEnv* env, jobject thiz, jstring sCategory)
{
    TSurveyItem* pObj = (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sCategory, NULL);
    jsize size = env->GetStringLength(sCategory);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sCategory = data;

    env->ReleaseStringChars(sCategory, jChar);
    
    free(data);
    
    return true;
}

static jstring TSurveyItem_GetQuestion(JNIEnv* env, jobject thiz)
{
    TSurveyItem* pObj = (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sQuestion.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sQuestion.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSurveyItem_SetQuestion(JNIEnv* env, jobject thiz, jstring sQuestion)
{
    TSurveyItem* pObj = (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sQuestion, NULL);
    jsize size = env->GetStringLength(sQuestion);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sQuestion = data;

    env->ReleaseStringChars(sQuestion, jChar);
    
    free(data);
    
    return true;
}

static jstring TSurveyItem_GetAnswer(JNIEnv* env, jobject thiz)
{
    TSurveyItem* pObj = (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAnswer.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAnswer.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSurveyItem_SetAnswer(JNIEnv* env, jobject thiz, jstring sAnswer)
{
    TSurveyItem* pObj = (TSurveyItem*)env->GetIntField(thiz, gTSurveyItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAnswer, NULL);
    jsize size = env->GetStringLength(sAnswer);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAnswer = data;

    env->ReleaseStringChars(sAnswer, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TSurveyItem(JNIEnv* env) {
    static JNINativeMethod TSurveyItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TSurveyItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TSurveyItem_nativeDestructor },
        { "GetID", "()Ljava/lang/String;", (void*)TSurveyItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TSurveyItem_SetID },
        { "GetType", "()I", (void*)TSurveyItem_GetType },
        { "SetType", "(I)Z", (void*)TSurveyItem_SetType },
        { "GetCategory", "()Ljava/lang/String;", (void*)TSurveyItem_GetCategory },
        { "SetCategory", "(Ljava/lang/String;)Z", (void*)TSurveyItem_SetCategory },
        { "GetQuestion", "()Ljava/lang/String;", (void*)TSurveyItem_GetQuestion },
        { "SetQuestion", "(Ljava/lang/String;)Z", (void*)TSurveyItem_SetQuestion },
        { "GetAnswer", "()Ljava/lang/String;", (void*)TSurveyItem_GetAnswer },
        { "SetAnswer", "(Ljava/lang/String;)Z", (void*)TSurveyItem_SetAnswer }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TSurveyItem");
    if (clazz == 0) {
        CM_ERR("class TSurveyItem no found");
        return -1;
    }

    gTSurveyItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTSurveyItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TSurveyItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TSurveyItemMethods,
            sizeof(TSurveyItemMethods) / sizeof(TSurveyItemMethods[0]));
}

fields_t gTSurveyOptionFieldID;

static void TSurveyOption_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TSurveyOption* pObj = new TSurveyOption();

    env->SetIntField(thiz, gTSurveyOptionFieldID.nativeJavaObj, (int)pObj);
}

static void TSurveyOption_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TSurveyOption*)env->GetIntField(thiz, gTSurveyOptionFieldID.nativeJavaObj);
}

static jstring TSurveyOption_GetID(JNIEnv* env, jobject thiz)
{
    TSurveyOption* pObj = (TSurveyOption*)env->GetIntField(thiz, gTSurveyOptionFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSurveyOption_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TSurveyOption* pObj = (TSurveyOption*)env->GetIntField(thiz, gTSurveyOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jboolean TSurveyOption_GetCheck(JNIEnv* env, jobject thiz)
{
    TSurveyOption* pObj = (TSurveyOption*)env->GetIntField(thiz, gTSurveyOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bCheck;
}
                
static jboolean TSurveyOption_SetCheck(JNIEnv* env, jobject thiz, jboolean bCheck)
{
    TSurveyOption* pObj = (TSurveyOption*)env->GetIntField(thiz, gTSurveyOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bCheck = bCheck;
    return true;
}
                
static jstring TSurveyOption_GetText(JNIEnv* env, jobject thiz)
{
    TSurveyOption* pObj = (TSurveyOption*)env->GetIntField(thiz, gTSurveyOptionFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sText.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sText.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TSurveyOption_SetText(JNIEnv* env, jobject thiz, jstring sText)
{
    TSurveyOption* pObj = (TSurveyOption*)env->GetIntField(thiz, gTSurveyOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sText, NULL);
    jsize size = env->GetStringLength(sText);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sText = data;

    env->ReleaseStringChars(sText, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TSurveyOption(JNIEnv* env) {
    static JNINativeMethod TSurveyOptionMethods[] = {
        { "nativeConstructor", "()V", (void*)TSurveyOption_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TSurveyOption_nativeDestructor },
        { "GetID", "()Ljava/lang/String;", (void*)TSurveyOption_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TSurveyOption_SetID },
        { "GetCheck", "()Z", (void*)TSurveyOption_GetCheck },
        { "SetCheck", "(Z)Z", (void*)TSurveyOption_SetCheck },
        { "GetText", "()Ljava/lang/String;", (void*)TSurveyOption_GetText },
        { "SetText", "(Ljava/lang/String;)Z", (void*)TSurveyOption_SetText }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TSurveyOption");
    if (clazz == 0) {
        CM_ERR("class TSurveyOption no found");
        return -1;
    }

    gTSurveyOptionFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTSurveyOptionFieldID.nativeJavaObj == 0) {
        CM_ERR("TSurveyOption no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TSurveyOptionMethods,
            sizeof(TSurveyOptionMethods) / sizeof(TSurveyOptionMethods[0]));
}


struct callback_cookie_CMSurvey {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gCMSurveyFieldID;

static void CMSurvey_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMSurvey when setting up callback.");
        return;
    }
    callback_cookie_CMSurvey* pCookie = new callback_cookie_CMSurvey;
    pCookie->listener1 = new CMUpdateDataListener(gCMSurveyFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gCMSurveyFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMSurveyFieldID.jniData, (int)pCookie);

    CMSurvey* pObj = new CMSurvey(pCookie->listener1, pCookie->listener2);
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMSurveyFieldID.nativeJavaObj, (int)pObj);
}

static void CMSurvey_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMSurvey *pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMSurvey* pCookie = (callback_cookie_CMSurvey *)env->GetIntField(
        thiz, gCMSurveyFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMSurveyFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMSurveyFieldID.jniData, 0);
}

static void CMSurvey_GetSurvey(JNIEnv* env, jobject thiz, jstring sSurveyID)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    const jchar* jsSurveyID = env->GetStringChars(sSurveyID, NULL);
    jsize sizesSurveyID = env->GetStringLength(sSurveyID);
    char* psSurveyID = UTF16toUTF8((jchar*)jsSurveyID, (size_t*)&sizesSurveyID);
    pObj->GetSurvey(psSurveyID);
    env->ReleaseStringChars(sSurveyID, jsSurveyID);
    free(psSurveyID);
}

static jint CMSurvey_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jint CMSurvey_GetItemOptionCount(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    int ret = pObj->GetItemOptionCount();
    return ret;
}

static jboolean CMSurvey_GetItemOption(JNIEnv* env, jobject thiz, jint nIndex, jobject option)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    extern fields_t gTSurveyOptionFieldID;
    TSurveyOption* pItem = (TSurveyOption*)env->GetIntField(option, gTSurveyOptionFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItemOption(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static void CMSurvey_SetAnswer(JNIEnv* env, jobject thiz, jstring answer)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    const jchar* janswer = env->GetStringChars(answer, NULL);
    jsize sizeanswer = env->GetStringLength(answer);
    char* panswer = UTF16toUTF8((jchar*)janswer, (size_t*)&sizeanswer);
    pObj->SetAnswer(panswer);
    env->ReleaseStringChars(answer, janswer);
    free(panswer);
}

static void CMSurvey_SetAnswer(JNIEnv* env, jobject thiz, jint nIndex, jboolean checked)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    pObj->SetAnswer(nIndex, checked);
}

static void CMSurvey_CommitAnswer(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    pObj->CommitAnswer();
}

static jint CMSurvey_GetCurIndex(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    int ret = pObj->GetCurIndex();
    return ret;
}

static jboolean CMSurvey_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    extern fields_t gTSurveyItemFieldID;
    TSurveyItem* pItem = (TSurveyItem*)env->GetIntField(item, gTSurveyItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMSurvey_GetCurItem(JNIEnv* env, jobject thiz, jobject item)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    extern fields_t gTSurveyItemFieldID;
    TSurveyItem* pItem = (TSurveyItem*)env->GetIntField(item, gTSurveyItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetCurItem(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMSurvey_GetCurIsAchieve(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    BOOL ret = pObj->GetCurIsAchieve();
    return ret;
}

static jboolean CMSurvey_Prev(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    BOOL ret = pObj->Prev();
    return ret;
}

static jboolean CMSurvey_Next(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    BOOL ret = pObj->Next();
    return ret;
}

static jboolean CMSurvey_isFirst(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    BOOL ret = pObj->isFirst();
    return ret;
}

static jboolean CMSurvey_isLast(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    BOOL ret = pObj->isLast();
    return ret;
}

static jboolean CMSurvey_SaveStatus(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    BOOL ret = pObj->SaveStatus();
    return ret;
}

static void CMSurvey_Cancel(JNIEnv* env, jobject thiz)
{
    CMSurvey* pObj = (CMSurvey*)env->GetIntField(thiz, gCMSurveyFieldID.nativeJavaObj);

    pObj->Cancel();
}

int register_com_wunding_mlplayer_business_CMSurvey(JNIEnv* env) {
    static void (*CMSurvey_SetAnswer1)(JNIEnv*, jobject, jstring);
    CMSurvey_SetAnswer1 = CMSurvey_SetAnswer;
    static void (*CMSurvey_SetAnswer2)(JNIEnv*, jobject, jint, jboolean);
    CMSurvey_SetAnswer2 = CMSurvey_SetAnswer;

    static JNINativeMethod CMSurveyMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMSurvey_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMSurvey_nativeDestructor },
        { "GetSurvey", "(Ljava/lang/String;)V", (void*)CMSurvey_GetSurvey },
        { "GetItemCount", "()I", (void*)CMSurvey_GetItemCount },
        { "GetItemOptionCount", "()I", (void*)CMSurvey_GetItemOptionCount },
        { "GetItemOption", "(ILcom/wunding/mlplayer/business/TSurveyOption;)Z", (void*)CMSurvey_GetItemOption },
        { "SetAnswer", "(Ljava/lang/String;)V", (void*)CMSurvey_SetAnswer1 },
        { "SetAnswer", "(IZ)V", (void*)CMSurvey_SetAnswer2 },
        { "CommitAnswer", "()V", (void*)CMSurvey_CommitAnswer },
        { "GetCurIndex", "()I", (void*)CMSurvey_GetCurIndex },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TSurveyItem;)Z", (void*)CMSurvey_GetItem },
        { "GetCurItem", "(Lcom/wunding/mlplayer/business/TSurveyItem;)Z", (void*)CMSurvey_GetCurItem },
        { "GetCurIsAchieve", "()Z", (void*)CMSurvey_GetCurIsAchieve },
        { "Prev", "()Z", (void*)CMSurvey_Prev },
        { "Next", "()Z", (void*)CMSurvey_Next },
        { "isFirst", "()Z", (void*)CMSurvey_isFirst },
        { "isLast", "()Z", (void*)CMSurvey_isLast },
        { "SaveStatus", "()Z", (void*)CMSurvey_SaveStatus },
        { "Cancel", "()V", (void*)CMSurvey_Cancel }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMSurvey");
    if (clazz == 0) {
        CM_ERR("class CMSurvey no found");
        return -1;
    }

    gCMSurveyFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMSurveyFieldID.nativeJavaObj == 0) {
        CM_ERR("CMSurvey no found mNativeObj");
        return -1;
    }

    gCMSurveyFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMSurveyFieldID.jniData == 0) {
        CM_ERR("CMSurvey no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMSurveyFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMSurveyFieldID.callback == NULL) {
        CM_ERR("CMSurvey no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMSurveyMethods,
            sizeof(CMSurveyMethods) / sizeof(CMSurveyMethods[0]));
}


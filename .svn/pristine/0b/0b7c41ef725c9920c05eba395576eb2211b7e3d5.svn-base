// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName: cmquestionhandler_jni.cpp
//  Description: This file is auto generated.
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "cmquestionhandler.h"
#include "imcommon_jni.h"
#include "utf8ncpy.h"

fields_t gTQuestionItemFieldID;

static void TQuestionItem_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = new TQuestionItem();

    env->SetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj, (int)pObj);
}

static void TQuestionItem_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
}

static jstring TQuestionItem_GetQuestionItemID(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetQuestionItemID();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jint TQuestionItem_GetQuestionItemType(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    int ret = pObj->GetQuestionItemType();
    return ret;
}

static jstring TQuestionItem_GetQuestionItemCategory(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetQuestionItemCategory();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TQuestionItem_GetQuestionItemQuestion(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetQuestionItemQuestion();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TQuestionItem_GetQuestionItemDescription(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetQuestionItemDescription();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jint TQuestionItem_GetQuestionItemValue(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    int ret = pObj->GetQuestionItemValue();
    return ret;
}

static jstring TQuestionItem_GetQuestionItemRightAnswer(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetQuestionItemRightAnswer();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TQuestionItem_GetQuestionItemMyAnswer(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetQuestionItemMyAnswer();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TQuestionItem_GetQuestionItemAnswer(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    const char* ret = pObj->GetQuestionItemAnswer();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQuestionItem_GetQuestionItemRight(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    BOOL ret = pObj->GetQuestionItemRight();
    return ret;
}

static jboolean TQuestionItem_GetQuestionItemChecked(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);

    BOOL ret = pObj->GetQuestionItemChecked();
    return ret;
}

static jstring TQuestionItem_GetID(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQuestionItem_SetID(JNIEnv* env, jobject thiz, jstring sID)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sID, NULL);
    jsize size = env->GetStringLength(sID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sID = data;

    env->ReleaseStringChars(sID, jChar);
    
    free(data);
    
    return true;
}

static jint TQuestionItem_GetType(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nType;
}
                
static jboolean TQuestionItem_SetType(JNIEnv* env, jobject thiz, jint nType)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nType = nType;
    return true;
}
                
static jstring TQuestionItem_GetCategory(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sCategory.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sCategory.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQuestionItem_SetCategory(JNIEnv* env, jobject thiz, jstring sCategory)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sCategory, NULL);
    jsize size = env->GetStringLength(sCategory);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sCategory = data;

    env->ReleaseStringChars(sCategory, jChar);
    
    free(data);
    
    return true;
}

static jstring TQuestionItem_GetQuestion(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sQuestion.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sQuestion.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQuestionItem_SetQuestion(JNIEnv* env, jobject thiz, jstring sQuestion)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sQuestion, NULL);
    jsize size = env->GetStringLength(sQuestion);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sQuestion = data;

    env->ReleaseStringChars(sQuestion, jChar);
    
    free(data);
    
    return true;
}

static jstring TQuestionItem_GetDescription(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sDescription.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sDescription.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQuestionItem_SetDescription(JNIEnv* env, jobject thiz, jstring sDescription)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sDescription, NULL);
    jsize size = env->GetStringLength(sDescription);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sDescription = data;

    env->ReleaseStringChars(sDescription, jChar);
    
    free(data);
    
    return true;
}

static jint TQuestionItem_GetValue(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return -1;

    return pObj->nValue;
}
                
static jboolean TQuestionItem_SetValue(JNIEnv* env, jobject thiz, jint nValue)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->nValue = nValue;
    return true;
}
                
static jboolean TQuestionItem_GetsWrong(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->isWrong;
}
                
static jboolean TQuestionItem_SetsWrong(JNIEnv* env, jobject thiz, jboolean isWrong)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->isWrong = isWrong;
    return true;
}
                
static jstring TQuestionItem_GetRightAnswer(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sRightAnswer.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sRightAnswer.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQuestionItem_SetRightAnswer(JNIEnv* env, jobject thiz, jstring sRightAnswer)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sRightAnswer, NULL);
    jsize size = env->GetStringLength(sRightAnswer);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sRightAnswer = data;

    env->ReleaseStringChars(sRightAnswer, jChar);
    
    free(data);
    
    return true;
}

static jstring TQuestionItem_GetMyAnswer(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sMyAnswer.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sMyAnswer.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQuestionItem_SetMyAnswer(JNIEnv* env, jobject thiz, jstring sMyAnswer)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sMyAnswer, NULL);
    jsize size = env->GetStringLength(sMyAnswer);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sMyAnswer = data;

    env->ReleaseStringChars(sMyAnswer, jChar);
    
    free(data);
    
    return true;
}

static jstring TQuestionItem_GetAnswer(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sAnswer.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sAnswer.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TQuestionItem_SetAnswer(JNIEnv* env, jobject thiz, jstring sAnswer)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sAnswer, NULL);
    jsize size = env->GetStringLength(sAnswer);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sAnswer = data;

    env->ReleaseStringChars(sAnswer, jChar);
    
    free(data);
    
    return true;
}

static jboolean TQuestionItem_GetsWrongOrig(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->isWrongOrig;
}
                
static jboolean TQuestionItem_SetsWrongOrig(JNIEnv* env, jobject thiz, jboolean isWrongOrig)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->isWrongOrig = isWrongOrig;
    return true;
}
                
static jboolean TQuestionItem_GetsRight(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->isRight;
}
                
static jboolean TQuestionItem_SetsRight(JNIEnv* env, jobject thiz, jboolean isRight)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->isRight = isRight;
    return true;
}
                
static jboolean TQuestionItem_GetsChecked(JNIEnv* env, jobject thiz)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->isChecked;
}
                
static jboolean TQuestionItem_SetsChecked(JNIEnv* env, jobject thiz, jboolean isChecked)
{
    TQuestionItem* pObj = (TQuestionItem*)env->GetIntField(thiz, gTQuestionItemFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->isChecked = isChecked;
    return true;
}
                
int register_com_wunding_mlplayer_business_TQuestionItem(JNIEnv* env) {
    static JNINativeMethod TQuestionItemMethods[] = {
        { "nativeConstructor", "()V", (void*)TQuestionItem_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TQuestionItem_nativeDestructor },
        { "GetQuestionItemID", "()Ljava/lang/String;", (void*)TQuestionItem_GetQuestionItemID },
        { "GetQuestionItemType", "()I", (void*)TQuestionItem_GetQuestionItemType },
        { "GetQuestionItemCategory", "()Ljava/lang/String;", (void*)TQuestionItem_GetQuestionItemCategory },
        { "GetQuestionItemQuestion", "()Ljava/lang/String;", (void*)TQuestionItem_GetQuestionItemQuestion },
        { "GetQuestionItemDescription", "()Ljava/lang/String;", (void*)TQuestionItem_GetQuestionItemDescription },
        { "GetQuestionItemValue", "()I", (void*)TQuestionItem_GetQuestionItemValue },
        { "GetQuestionItemRightAnswer", "()Ljava/lang/String;", (void*)TQuestionItem_GetQuestionItemRightAnswer },
        { "GetQuestionItemMyAnswer", "()Ljava/lang/String;", (void*)TQuestionItem_GetQuestionItemMyAnswer },
        { "GetQuestionItemAnswer", "()Ljava/lang/String;", (void*)TQuestionItem_GetQuestionItemAnswer },
        { "GetQuestionItemRight", "()Z", (void*)TQuestionItem_GetQuestionItemRight },
        { "GetQuestionItemChecked", "()Z", (void*)TQuestionItem_GetQuestionItemChecked },
        { "GetID", "()Ljava/lang/String;", (void*)TQuestionItem_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TQuestionItem_SetID },
        { "GetType", "()I", (void*)TQuestionItem_GetType },
        { "SetType", "(I)Z", (void*)TQuestionItem_SetType },
        { "GetCategory", "()Ljava/lang/String;", (void*)TQuestionItem_GetCategory },
        { "SetCategory", "(Ljava/lang/String;)Z", (void*)TQuestionItem_SetCategory },
        { "GetQuestion", "()Ljava/lang/String;", (void*)TQuestionItem_GetQuestion },
        { "SetQuestion", "(Ljava/lang/String;)Z", (void*)TQuestionItem_SetQuestion },
        { "GetDescription", "()Ljava/lang/String;", (void*)TQuestionItem_GetDescription },
        { "SetDescription", "(Ljava/lang/String;)Z", (void*)TQuestionItem_SetDescription },
        { "GetValue", "()I", (void*)TQuestionItem_GetValue },
        { "SetValue", "(I)Z", (void*)TQuestionItem_SetValue },
        { "GetsWrong", "()Z", (void*)TQuestionItem_GetsWrong },
        { "SetsWrong", "(Z)Z", (void*)TQuestionItem_SetsWrong },
        { "GetRightAnswer", "()Ljava/lang/String;", (void*)TQuestionItem_GetRightAnswer },
        { "SetRightAnswer", "(Ljava/lang/String;)Z", (void*)TQuestionItem_SetRightAnswer },
        { "GetMyAnswer", "()Ljava/lang/String;", (void*)TQuestionItem_GetMyAnswer },
        { "SetMyAnswer", "(Ljava/lang/String;)Z", (void*)TQuestionItem_SetMyAnswer },
        { "GetAnswer", "()Ljava/lang/String;", (void*)TQuestionItem_GetAnswer },
        { "SetAnswer", "(Ljava/lang/String;)Z", (void*)TQuestionItem_SetAnswer },
        { "GetsWrongOrig", "()Z", (void*)TQuestionItem_GetsWrongOrig },
        { "SetsWrongOrig", "(Z)Z", (void*)TQuestionItem_SetsWrongOrig },
        { "GetsRight", "()Z", (void*)TQuestionItem_GetsRight },
        { "SetsRight", "(Z)Z", (void*)TQuestionItem_SetsRight },
        { "GetsChecked", "()Z", (void*)TQuestionItem_GetsChecked },
        { "SetsChecked", "(Z)Z", (void*)TQuestionItem_SetsChecked }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TQuestionItem");
    if (clazz == 0) {
        CM_ERR("class TQuestionItem no found");
        return -1;
    }

    gTQuestionItemFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTQuestionItemFieldID.nativeJavaObj == 0) {
        CM_ERR("TQuestionItem no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TQuestionItemMethods,
            sizeof(TQuestionItemMethods) / sizeof(TQuestionItemMethods[0]));
}

fields_t gTOptionFieldID;

static void TOption_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TOption* pObj = new TOption();

    env->SetIntField(thiz, gTOptionFieldID.nativeJavaObj, (int)pObj);
}

static void TOption_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
}

static jstring TOption_GetOptionItemsID(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);

    const char* ret = pObj->GetOptionItemsID();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TOption_GetOptionItemnID(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);

    const char* ret = pObj->GetOptionItemnID();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jstring TOption_GetOptionItemText(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);

    const char* ret = pObj->GetOptionItemText();
    size_t size = strlen(ret);
    jchar* data = UTF8toUTF16((char*)ret, &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TOption_GetOptionItemCheck(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);

    BOOL ret = pObj->GetOptionItemCheck();
    return ret;
}

static jboolean TOption_GetOptionItemMyAnswer(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);

    BOOL ret = pObj->GetOptionItemMyAnswer();
    return ret;
}

static jboolean TOption_GetOptionItemRightAnswer(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);

    BOOL ret = pObj->GetOptionItemRightAnswer();
    return ret;
}

static jstring TOption_GetSID(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sSID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sSID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TOption_SetSID(JNIEnv* env, jobject thiz, jstring sSID)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sSID, NULL);
    jsize size = env->GetStringLength(sSID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sSID = data;

    env->ReleaseStringChars(sSID, jChar);
    
    free(data);
    
    return true;
}

static jstring TOption_GetID(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->nID.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->nID.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TOption_SetID(JNIEnv* env, jobject thiz, jstring nID)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(nID, NULL);
    jsize size = env->GetStringLength(nID);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->nID = data;

    env->ReleaseStringChars(nID, jChar);
    
    free(data);
    
    return true;
}

static jboolean TOption_GetCheck(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bCheck;
}
                
static jboolean TOption_SetCheck(JNIEnv* env, jobject thiz, jboolean bCheck)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bCheck = bCheck;
    return true;
}
                
static jboolean TOption_GetMyAnswer(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bMyAnswer;
}
                
static jboolean TOption_SetMyAnswer(JNIEnv* env, jobject thiz, jboolean bMyAnswer)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bMyAnswer = bMyAnswer;
    return true;
}
                
static jboolean TOption_GetRightAnswer(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    return pObj->bRightAnswer;
}
                
static jboolean TOption_SetRightAnswer(JNIEnv* env, jobject thiz, jboolean bRightAnswer)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    pObj->bRightAnswer = bRightAnswer;
    return true;
}
                
static jstring TOption_GetText(JNIEnv* env, jobject thiz)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return NULL;

    size_t size = strlen(pObj->sText.c_str());
    jchar* data = UTF8toUTF16((char*)pObj->sText.c_str(), &size);
    jstring str = env->NewString((const jchar*)data, size);
    free(data);
    return str;
}

static jboolean TOption_SetText(JNIEnv* env, jobject thiz, jstring sText)
{
    TOption* pObj = (TOption*)env->GetIntField(thiz, gTOptionFieldID.nativeJavaObj);
    if (pObj == 0) return false;

    const jchar* jChar = env->GetStringChars(sText, NULL);
    jsize size = env->GetStringLength(sText);
    char* data = UTF16toUTF8((jchar*)jChar, (size_t*)&size);
    pObj->sText = data;

    env->ReleaseStringChars(sText, jChar);
    
    free(data);
    
    return true;
}

int register_com_wunding_mlplayer_business_TOption(JNIEnv* env) {
    static JNINativeMethod TOptionMethods[] = {
        { "nativeConstructor", "()V", (void*)TOption_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TOption_nativeDestructor },
        { "GetOptionItemsID", "()Ljava/lang/String;", (void*)TOption_GetOptionItemsID },
        { "GetOptionItemnID", "()Ljava/lang/String;", (void*)TOption_GetOptionItemnID },
        { "GetOptionItemText", "()Ljava/lang/String;", (void*)TOption_GetOptionItemText },
        { "GetOptionItemCheck", "()Z", (void*)TOption_GetOptionItemCheck },
        { "GetOptionItemMyAnswer", "()Z", (void*)TOption_GetOptionItemMyAnswer },
        { "GetOptionItemRightAnswer", "()Z", (void*)TOption_GetOptionItemRightAnswer },
        { "GetSID", "()Ljava/lang/String;", (void*)TOption_GetSID },
        { "SetSID", "(Ljava/lang/String;)Z", (void*)TOption_SetSID },
        { "GetID", "()Ljava/lang/String;", (void*)TOption_GetID },
        { "SetID", "(Ljava/lang/String;)Z", (void*)TOption_SetID },
        { "GetCheck", "()Z", (void*)TOption_GetCheck },
        { "SetCheck", "(Z)Z", (void*)TOption_SetCheck },
        { "GetMyAnswer", "()Z", (void*)TOption_GetMyAnswer },
        { "SetMyAnswer", "(Z)Z", (void*)TOption_SetMyAnswer },
        { "GetRightAnswer", "()Z", (void*)TOption_GetRightAnswer },
        { "SetRightAnswer", "(Z)Z", (void*)TOption_SetRightAnswer },
        { "GetText", "()Ljava/lang/String;", (void*)TOption_GetText },
        { "SetText", "(Ljava/lang/String;)Z", (void*)TOption_SetText }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TOption");
    if (clazz == 0) {
        CM_ERR("class TOption no found");
        return -1;
    }

    gTOptionFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTOptionFieldID.nativeJavaObj == 0) {
        CM_ERR("TOption no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TOptionMethods,
            sizeof(TOptionMethods) / sizeof(TOptionMethods[0]));
}

fields_t gTQuestionFieldID;

static void TQuestion_nativeConstructor(JNIEnv* env, jobject thiz)
{
    TQuestion* pObj = new TQuestion();

    env->SetIntField(thiz, gTQuestionFieldID.nativeJavaObj, (int)pObj);
}

static void TQuestion_nativeDestructor(JNIEnv* env, jobject thiz)
{
    delete (TQuestion*)env->GetIntField(thiz, gTQuestionFieldID.nativeJavaObj);
}

static jobject TQuestion_CopyFromTQuestion(JNIEnv* env, jobject thiz, jobject right)
{
    TQuestion* pObj = (TQuestion*)env->GetIntField(thiz, gTQuestionFieldID.nativeJavaObj);

    extern fields_t gTQuestionFieldID;
    TQuestion* pObjCopy = (TQuestion*)env->GetIntField(right, gTQuestionFieldID.nativeJavaObj);
    pObj->operator=(*pObjCopy);

    return thiz;
}

int register_com_wunding_mlplayer_business_TQuestion(JNIEnv* env) {
    static JNINativeMethod TQuestionMethods[] = {
        { "nativeConstructor", "()V", (void*)TQuestion_nativeConstructor},
        { "nativeDestructor", "()V", (void*)TQuestion_nativeDestructor },
        { "CopyFromTQuestion", "(Lcom/wunding/mlplayer/business/TQuestion;)Lcom/wunding/mlplayer/business/TQuestion;", (void*)TQuestion_CopyFromTQuestion }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/TQuestion");
    if (clazz == 0) {
        CM_ERR("class TQuestion no found");
        return -1;
    }

    gTQuestionFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gTQuestionFieldID.nativeJavaObj == 0) {
        CM_ERR("TQuestion no found mNativeObj");
        return -1;
    }

    return env->RegisterNatives(clazz,
            TQuestionMethods,
            sizeof(TQuestionMethods) / sizeof(TQuestionMethods[0]));
}


struct callback_cookie_CMQuestionhandler {
    jclass      info_class;
    jobject     ref;
    CMUpdateDataListener* listener1;
    CMSimpleResultListener* listener2;
};

fields_t gCMQuestionhandlerFieldID;

static void CMQuestionhandler_nativeConstructor(JNIEnv* env, jobject thiz, jobject weak_this)
{
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        CM_ERR("Can't find CMQuestionhandler when setting up callback.");
        return;
    }
    callback_cookie_CMQuestionhandler* pCookie = new callback_cookie_CMQuestionhandler;
    pCookie->listener1 = new CMUpdateDataListener(gCMQuestionhandlerFieldID.callback);
    pCookie->listener2 = new CMSimpleResultListener(gCMQuestionhandlerFieldID.callback);
    pCookie->info_class = (jclass)env->NewGlobalRef(clazz);
    pCookie->ref = env->NewGlobalRef(weak_this);
    env->SetIntField(thiz, gCMQuestionhandlerFieldID.jniData, (int)pCookie);

    CMQuestionhandler* pObj = new CMQuestionhandler();
    pObj->SetUserData(pCookie);
    env->SetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj, (int)pObj);
}

static void CMQuestionhandler_nativeDestructor(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler *pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);
    if (pObj) {
        //add your release function here

        delete pObj;
    }

    callback_cookie_CMQuestionhandler* pCookie = (callback_cookie_CMQuestionhandler *)env->GetIntField(
        thiz, gCMQuestionhandlerFieldID.jniData);
    if (pCookie) {
        env->DeleteGlobalRef(pCookie->info_class);
        env->DeleteGlobalRef(pCookie->ref);
        delete pCookie->listener1;
        delete pCookie->listener2;
        delete pCookie;
    }

    env->SetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj, 0);
    env->SetIntField(thiz, gCMQuestionhandlerFieldID.jniData, 0);
}

static jint CMQuestionhandler_GetItemCount(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    int ret = pObj->GetItemCount();
    return ret;
}

static jboolean CMQuestionhandler_GetItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    extern fields_t gTQuestionFieldID;
    TQuestion* pItem = (TQuestion*)env->GetIntField(item, gTQuestionFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQuestionhandler_Refresh(JNIEnv* env, jobject thiz, jobject obj)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    extern fields_t gTQuestionFieldID;
    TQuestion* pItem = (TQuestion*)env->GetIntField(obj, gTQuestionFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Refresh(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQuestionhandler_Update(JNIEnv* env, jobject thiz, jobject obj)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    extern fields_t gTQuestionFieldID;
    TQuestion* pItem = (TQuestion*)env->GetIntField(obj, gTQuestionFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->Update(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQuestionhandler_IsEnd(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->IsEnd();
    return ret;
}

static jboolean CMQuestionhandler_RequestMore(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->RequestMore();
    return ret;
}

static jboolean CMQuestionhandler_IsRunning(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRunning();
    return ret;
}

static jboolean CMQuestionhandler_IsRefresh(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->IsRefresh();
    return ret;
}

static void CMQuestionhandler_Cancel(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    pObj->Cancel();
}

static void CMQuestionhandler_SetRequestType(JNIEnv* env, jobject thiz, jint nType)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    pObj->SetRequestType(nType);
}

static void CMQuestionhandler_SetListener(JNIEnv* env, jobject thiz, jobject pListener, jobject pSimpleResultListener)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    callback_cookie_CMQuestionhandler* pCookie = (callback_cookie_CMQuestionhandler *)env->GetIntField(
        thiz, gCMQuestionhandlerFieldID.jniData);
    if (pCookie)
    {
        if (pCookie->listener1 == NULL)
        {
            pCookie->listener1 = new CMUpdateDataListener(gCMQuestionhandlerFieldID.callback);
        }
        
        IMUpdateDataListener* para1 = NULL;
        if (pListener != NULL)
        {
            para1 = pCookie->listener1;
        }

        if (pCookie->listener2 == NULL)
        {
            pCookie->listener2 = new CMSimpleResultListener(gCMQuestionhandlerFieldID.callback);
        }
        
        IMSimpleResultListener* para2 = NULL;
        if (pSimpleResultListener != NULL)
        {
            para2 = pCookie->listener2;
        }

        pObj->SetListener(para1, para2);
    }

    return ;
}

static jint CMQuestionhandler_GetItemOptionCount(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    int ret = pObj->GetItemOptionCount();
    return ret;
}

static jboolean CMQuestionhandler_GetItemOption(JNIEnv* env, jobject thiz, jint nIndex, jobject option)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    extern fields_t gTOptionFieldID;
    TOption* pItem = (TOption*)env->GetIntField(option, gTOptionFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetItemOption(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static void CMQuestionhandler_SetAnswer(JNIEnv* env, jobject thiz, jstring answer)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    const jchar* janswer = env->GetStringChars(answer, NULL);
    jsize sizeanswer = env->GetStringLength(answer);
    char* panswer = UTF16toUTF8((jchar*)janswer, (size_t*)&sizeanswer);
    pObj->SetAnswer(panswer);
    env->ReleaseStringChars(answer, janswer);
    free(panswer);
}

static void CMQuestionhandler_SetAnswer(JNIEnv* env, jobject thiz, jint nIndex, jboolean checked)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    pObj->SetAnswer(nIndex, checked);
}

static jint CMQuestionhandler_GetCurIndex(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    int ret = pObj->GetCurIndex();
    return ret;
}

static void CMQuestionhandler_SetCurIndex(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    pObj->SetCurIndex(nIndex);
}

static jboolean CMQuestionhandler_GetCurItem(JNIEnv* env, jobject thiz, jobject item)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    extern fields_t gTQuestionItemFieldID;
    TQuestionItem* pItem = (TQuestionItem*)env->GetIntField(item, gTQuestionItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetCurItem(*pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQuestionhandler_GetQuestionItem(JNIEnv* env, jobject thiz, jint nIndex, jobject item)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    extern fields_t gTQuestionItemFieldID;
    TQuestionItem* pItem = (TQuestionItem*)env->GetIntField(item, gTQuestionItemFieldID.nativeJavaObj);
    if (pItem != NULL) {
        jboolean ret = pObj->GetQuestionItem(nIndex, *pItem);
        return ret;
    }
    else {
        return false;
    }
}

static jboolean CMQuestionhandler_Prev(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->Prev();
    return ret;
}

static jboolean CMQuestionhandler_Next(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->Next();
    return ret;
}

static jboolean CMQuestionhandler_isFirst(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->isFirst();
    return ret;
}

static jboolean CMQuestionhandler_isLast(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->isLast();
    return ret;
}

static jboolean CMQuestionhandler_SaveStatus(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->SaveStatus();
    return ret;
}

static void CMQuestionhandler_SetExerciseAnswer(JNIEnv* env, jobject thiz, jboolean checked)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    pObj->SetExerciseAnswer(checked);
}

static void CMQuestionhandler_SetIsChecked(JNIEnv* env, jobject thiz, jboolean checked)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    pObj->SetIsChecked(checked);
}

static jint CMQuestionhandler_GetDoneCount(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    int ret = pObj->GetDoneCount();
    return ret;
}

static jboolean CMQuestionhandler_IsQuestionComplete(JNIEnv* env, jobject thiz, jint nIndex)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->IsQuestionComplete(nIndex);
    return ret;
}

static jint CMQuestionhandler_GetRightCount(JNIEnv* env, jobject thiz, jstring questionID)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    const jchar* jquestionID = env->GetStringChars(questionID, NULL);
    jsize sizequestionID = env->GetStringLength(questionID);
    char* pquestionID = UTF16toUTF8((jchar*)jquestionID, (size_t*)&sizequestionID);
    int ret = pObj->GetRightCount(pquestionID);
    env->ReleaseStringChars(questionID, jquestionID);
    free(pquestionID);
    return ret;
}

static jboolean CMQuestionhandler_isExciseCommit(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    BOOL ret = pObj->isExciseCommit();
    return ret;
}

static void CMQuestionhandler_setRight(JNIEnv* env, jobject thiz)
{
    CMQuestionhandler* pObj = (CMQuestionhandler*)env->GetIntField(thiz, gCMQuestionhandlerFieldID.nativeJavaObj);

    pObj->setRight();
}

int register_com_wunding_mlplayer_business_CMQuestionhandler(JNIEnv* env) {
    static void (*CMQuestionhandler_SetAnswer1)(JNIEnv*, jobject, jstring);
    CMQuestionhandler_SetAnswer1 = CMQuestionhandler_SetAnswer;
    static void (*CMQuestionhandler_SetAnswer2)(JNIEnv*, jobject, jint, jboolean);
    CMQuestionhandler_SetAnswer2 = CMQuestionhandler_SetAnswer;

    static JNINativeMethod CMQuestionhandlerMethods[] = {
        { "nativeConstructor", "(Ljava/lang/Object;)V", (void*)CMQuestionhandler_nativeConstructor},
        { "nativeDestructor", "()V", (void*)CMQuestionhandler_nativeDestructor },
        { "GetItemCount", "()I", (void*)CMQuestionhandler_GetItemCount },
        { "GetItem", "(ILcom/wunding/mlplayer/business/TQuestion;)Z", (void*)CMQuestionhandler_GetItem },
        { "Refresh", "(Lcom/wunding/mlplayer/business/TQuestion;)Z", (void*)CMQuestionhandler_Refresh },
        { "Update", "(Lcom/wunding/mlplayer/business/TQuestion;)Z", (void*)CMQuestionhandler_Update },
        { "IsEnd", "()Z", (void*)CMQuestionhandler_IsEnd },
        { "RequestMore", "()Z", (void*)CMQuestionhandler_RequestMore },
        { "IsRunning", "()Z", (void*)CMQuestionhandler_IsRunning },
        { "IsRefresh", "()Z", (void*)CMQuestionhandler_IsRefresh },
        { "Cancel", "()V", (void*)CMQuestionhandler_Cancel },
        { "SetRequestType", "(I)V", (void*)CMQuestionhandler_SetRequestType },
        { "nativeSetListener", "(Ljava/lang/Object;Ljava/lang/Object;)V", (void*)CMQuestionhandler_SetListener },
        { "GetItemOptionCount", "()I", (void*)CMQuestionhandler_GetItemOptionCount },
        { "GetItemOption", "(ILcom/wunding/mlplayer/business/TOption;)Z", (void*)CMQuestionhandler_GetItemOption },
        { "SetAnswer", "(Ljava/lang/String;)V", (void*)CMQuestionhandler_SetAnswer1 },
        { "SetAnswer", "(IZ)V", (void*)CMQuestionhandler_SetAnswer2 },
        { "GetCurIndex", "()I", (void*)CMQuestionhandler_GetCurIndex },
        { "SetCurIndex", "(I)V", (void*)CMQuestionhandler_SetCurIndex },
        { "GetCurItem", "(Lcom/wunding/mlplayer/business/TQuestionItem;)Z", (void*)CMQuestionhandler_GetCurItem },
        { "GetQuestionItem", "(ILcom/wunding/mlplayer/business/TQuestionItem;)Z", (void*)CMQuestionhandler_GetQuestionItem },
        { "Prev", "()Z", (void*)CMQuestionhandler_Prev },
        { "Next", "()Z", (void*)CMQuestionhandler_Next },
        { "isFirst", "()Z", (void*)CMQuestionhandler_isFirst },
        { "isLast", "()Z", (void*)CMQuestionhandler_isLast },
        { "SaveStatus", "()Z", (void*)CMQuestionhandler_SaveStatus },
        { "SetExerciseAnswer", "(Z)V", (void*)CMQuestionhandler_SetExerciseAnswer },
        { "SetIsChecked", "(Z)V", (void*)CMQuestionhandler_SetIsChecked },
        { "GetDoneCount", "()I", (void*)CMQuestionhandler_GetDoneCount },
        { "IsQuestionComplete", "(I)Z", (void*)CMQuestionhandler_IsQuestionComplete },
        { "GetRightCount", "(Ljava/lang/String;)I", (void*)CMQuestionhandler_GetRightCount },
        { "isExciseCommit", "()Z", (void*)CMQuestionhandler_isExciseCommit },
        { "setRight", "()V", (void*)CMQuestionhandler_setRight }
    };


    jclass clazz = env->FindClass("com/wunding/mlplayer/business/CMQuestionhandler");
    if (clazz == 0) {
        CM_ERR("class CMQuestionhandler no found");
        return -1;
    }

    gCMQuestionhandlerFieldID.nativeJavaObj = env->GetFieldID(clazz, "mNativeObj", "I");
    if (gCMQuestionhandlerFieldID.nativeJavaObj == 0) {
        CM_ERR("CMQuestionhandler no found mNativeObj");
        return -1;
    }

    gCMQuestionhandlerFieldID.jniData = env->GetFieldID(clazz, "mJniData", "I");
    if (gCMQuestionhandlerFieldID.jniData == 0) {
        CM_ERR("CMQuestionhandler no found mJniData");
        return -1;
    }

    // Get the postEvent method
    gCMQuestionhandlerFieldID.callback = env->GetStaticMethodID(
            clazz, "callback", "(Ljava/lang/Object;III)V");
    if (gCMQuestionhandlerFieldID.callback == NULL) {
        CM_ERR("CMQuestionhandler no found callback");
        return -1;
    }

    return env->RegisterNatives(clazz,
            CMQuestionhandlerMethods,
            sizeof(CMQuestionhandlerMethods) / sizeof(CMQuestionhandlerMethods[0]));
}


// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:全局对象类，不允许其他全局函数/变量存在
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmglobal.h"
#include <jni.h>
#include "cmnetwork.h"
#include "cmsettings.h"
#include "android/env.h"

CMSystemInfo& CMGlobal::SystemInfo()
{
	if (m_pSystemInfo != NULL)
    {
        return *m_pSystemInfo;
    }
	m_pSystemInfo = new CMSystemInfo();
	m_pSystemInfo->ScreenWidth = 0;
	m_pSystemInfo->ScreenHeight = 0;

	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("GetEnv failed");
		return *m_pSystemInfo;
	}

	jmethodID getScreenSize = env->GetStaticMethodID(GetGlobalCls(), "getScreenSize", "()V");
	jfieldID wID = env->GetStaticFieldID(GetGlobalCls(), "mWidth", "I");
	jfieldID hID = env->GetStaticFieldID(GetGlobalCls(), "mHeight", "I");	
	if(getScreenSize && wID && hID)
	{
		env->CallStaticVoidMethod(GetGlobalCls(), getScreenSize);
		m_pSystemInfo->ScreenWidth = (int) env->GetStaticIntField(GetGlobalCls(), wID);
		m_pSystemInfo->ScreenHeight = (int) env->GetStaticIntField(GetGlobalCls(), hID);
	}
	////////////////////////////////////////////////////////////
	jmethodID IsFlashEnabled = env->GetStaticMethodID(GetGlobalCls(), "IsFlashEnabled", "()Z");
	if(IsFlashEnabled)
	{
		strcpy(m_pSystemInfo->AcceptType, "text/html,text/vnd.wap.wml,video/3mv,audio/3ma,audio/aac");
		if(env->CallStaticBooleanMethod(GetGlobalCls(), IsFlashEnabled))
			strcat(m_pSystemInfo->AcceptType, ",application/x-shockwave-flash");
	}
	//拿到当前的语言
	jmethodID getCurrLang = env->GetStaticMethodID(GetGlobalCls(), "getCurrLang", "()V");
	jfieldID CurrLang = env->GetStaticFieldID(GetGlobalCls(), "mCurrLang", "Ljava/lang/String;");
	if (getCurrLang)
	{
		env->CallStaticVoidMethod(GetGlobalCls(), getCurrLang);
		jstring jstr = (jstring)env->GetStaticObjectField(GetGlobalCls(), CurrLang);
		if (jstr){
			jboolean *bo = new jboolean;
			const char *buff = env->GetStringUTFChars(jstr, bo);
			bzero(m_pSystemInfo->CurrLang, sizeof(m_pSystemInfo->CurrLang));
			strcpy(m_pSystemInfo->CurrLang, buff);
			delete bo;
		}
	}
	return *m_pSystemInfo;
}

BOOL CMGlobal::IsExistNetwork()
{
	//不使用
	return FALSE;
}

// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmgloballistener.h"

///////////////////////////////////////////////////////////////
CMGlobalListener* CMGlobalListener::m_pTHIS = NULL;

void CMGlobalListener::SetListener(CMGlobalListener* pListener)
{
	m_pTHIS = pListener;
}

CMGlobalListener* CMGlobalListener::GetListener()
{
	return m_pTHIS;
}

CMGlobalListener::CMGlobalListener()
{
}

CMGlobalListener::~CMGlobalListener()
{
}

#if defined(PLAT_AND)
#include <jni.h>
#include "android/env.h"
void CMGlobalListenerAnd::OnKicked(int nErr)
{
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
		return ;
	jmethodID method = env->GetStaticMethodID(GetGlobalCls(), "getInstance", "()Lcom/wunding/mlplayer/CMGlobal;");
	if(!method)
		return;
	jobject obj = (jobject)env->CallStaticObjectMethod(GetGlobalCls(), method);
	if(!obj)
		return;
	method = env->GetMethodID(GetGlobalCls(), "KickOut", "()V");
	const char * buf = NULL;
	if(method)
	{
		env->CallVoidMethod(obj, method);
	}
}
#endif

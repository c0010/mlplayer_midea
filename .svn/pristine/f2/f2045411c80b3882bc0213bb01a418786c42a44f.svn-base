// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmversion.h"

#if defined(PLAT_SYMBIAN)
#include <aknenv.h>
#elif defined(PLAT_AND)
#include <jni.h>
#include "android/env.h"
#endif
CMVersion* CMVersion::m_pSystemVersion = NULL;

CMVersion::CMVersion()
{

}

CMVersion::~CMVersion()
{

}


CMVersion& CMVersion::SystemVersion()
{
	if (m_pSystemVersion != NULL)
    {
        return *m_pSystemVersion;        
    }
	m_pSystemVersion = new CMVersion;
/////////////////////////////////////////////////////
#if defined(PLAT_AND)
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
	{
		CM_ERR("GetEnv failed");
	}
	else
	{
		jmethodID method = env->GetStaticMethodID(GetGlobalCls(), "GetPlatID", "()I");
		if(method)
			m_pSystemVersion->Platform = env->CallStaticIntMethod(GetGlobalCls(), method);
	}
#elif defined(PLAT_IOS)
	m_pSystemVersion->Platform = m_pSystemVersion->GetPlatID();
#else
	m_pSystemVersion->Platform = PLAT_ID;
#endif
/////////////////////////////////////////////////////
#if defined(PLAT_SYMBIAN)
	_LIT(KProductIDFile, "Series60v*.sis");
	_LIT(KROMInstallDir, "z:\\system\\install\\");

	TFindFile ff( CCoeEnv::Static()->FsSession() );
	CDir* result;
	if( ff.FindWildByDir( KProductIDFile, KROMInstallDir, result ) == KErrNone)
	{
		CleanupStack::PushL( result );
		//该目录下可能同时存在series60v3.0.sis series60v3.1.sis ,其中较大值的才是当前版本
		User::LeaveIfError( result->Sort( ESortByName|EDescending ) );
		m_pSystemVersion->Major = (*result)[0].iName[9] - '0';
		m_pSystemVersion->Minor = (*result)[0].iName[11] - '0';
		m_pSystemVersion->Build = 0;
		CleanupStack::PopAndDestroy(); // result
	}
#elif defined(PLAT_WINCE)
	OSVERSIONINFO versionInfo;
	versionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
	::GetVersionEx(&versionInfo); 

	m_pSystemVersion->Major = versionInfo.dwMajorVersion;
	m_pSystemVersion->Minor = versionInfo.dwMinorVersion;
	m_pSystemVersion->Build = versionInfo.dwBuildNumber;
#else
	m_pSystemVersion->Major = 1;
	m_pSystemVersion->Minor = 0;
	m_pSystemVersion->Build = 0;
#endif	

	return *m_pSystemVersion;
}

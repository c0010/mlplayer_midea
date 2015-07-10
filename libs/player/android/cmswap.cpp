#include "stdafx.h"
#include "cmswap.h"
#include "android/env.h"
#include "cmplayerutility.h"

CMSwap::CMSwap(jobject obj)
{
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
		return ;

	SwapObj = (jclass)env->NewGlobalRef(obj);
}

CMSwap::~CMSwap()
{
	JNIEnv*  env ;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
		return ;

	if(SwapObj)
	{
		env->DeleteGlobalRef(SwapObj);
		SwapObj = NULL;
	}
}

void CMSwap::StateChange(void* UserData, INT32 nNew, INT32 nOld)
{
	Post(1, nNew,nOld);
}

void CMSwap::ProgressChange(void* UserData, INT32 nBufPer, INT32 nPlayPos)
{
	Post(2, nBufPer,nPlayPos);
}

void CMSwap::OnAllCompleted(void* UserData)
{
	Post(3, 0, 0);
}

void CMSwap::OnError(void* UserData, INT32 nErrorCode)
{
	Post(4, nErrorCode, 0);
}
#include "cmaudioplay.h"

void CMSwap::VideoDraw(UINT8* data, INT32 width, INT32 height)
{
//	JNIEnv*  env ;
//	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
//		return ;
//
//	jintArray jarray = NULL;
//	if(data)
//	{
//			env->CallVoidMethod(SwapObj,CMPlayerUtility::field.VideoDrawFunc, (jintArray)data, width,height);
//	}
}

void CMSwap::NotifyStop()
{
	Post(5, 0, 0);
}

void CMSwap::Post(int no, int one, int two)
{
	JNIEnv*  env;
	if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
		return ;

	env->CallVoidMethod(SwapObj,CMPlayerUtility::field.PostToFunc,no,one,two);
}

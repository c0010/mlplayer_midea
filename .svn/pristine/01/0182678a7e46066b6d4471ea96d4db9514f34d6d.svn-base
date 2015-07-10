// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include <jni.h>


static JavaVM* gJavaVM = 0;

static jclass  gGlobalCls = 0;

void SetJavaVM(JavaVM* vm)
{
	gJavaVM = vm;
}

JavaVM* GetJavaVM()
{
	return gJavaVM;
}


void SetGlobalCls(jclass cls)
{
	gGlobalCls = cls;
}

jclass GetGlobalCls()
{
	return gGlobalCls;
}


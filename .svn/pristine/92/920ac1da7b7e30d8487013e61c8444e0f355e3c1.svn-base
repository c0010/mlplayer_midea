// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////
#ifndef __ENV_H__
#define __ENV_H__

//只在JNI_OnLoad里调用
void SetJavaVM(JavaVM* vm);

//一般在新建native线程里调用，用来获取env以回调java层
JavaVM* GetJavaVM();

 void SetGlobalCls(jclass cls);

 jclass GetGlobalCls();

#endif

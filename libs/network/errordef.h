////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009,
// All rights reserved.
// 
// FileName:errordef.h
// Description:通用错误定义
// Author:roy
////////////////////////////////////////////////////////////////////////////////
#ifndef __ERRORDEF_H__
#define __ERRORDEF_H__

//整形类型的错误返回定义
//采用分段方式，常用从0开始

//没有错误
#define MER_OK   0
//没有找到
const UINT32 MER_NOFOUND = 1;
//没有实现
const UINT32 MER_NOIMP   = 2;
//文件打开失败
const UINT32 MER_FILEOPEN = 3;
//已被使用
const UINT32 MER_ALREADYUSED = 4;

//---------------------下面开始网络错误定义-------------------------------------
//http返回 100-600
//自行定义错误不能使用以上范围

//网络错误700-799
const UINT32 MERN_CONN_REFUSED                          = 700;        //ConnectionRefused
const UINT32 MERN_HOST_CLOSED                           = 701;        //RemoteHostClosed
const UINT32 MERN_HOST_NO_FOUND                         = 702;        //HostNotFound
const UINT32 MERN_SOCKET_TIMEOUT                        = 703;        //SocketTimeout
const UINT32 MERN_ERROR                                 = 704;        //默认网络错误
const UINT32 MERN_NOT_CONNECTED                         = 705;        //还未连接
const UINT32 MERN_SENDING                               = 706;        //正在发送，不能操作
const UINT32 MERN_RECVING                               = 707;        //正在接收，不能操作
const UINT32 MERN_CONNECTED                             = 708;        //已经连接成功
const UINT32 MERN_WRONG_PARAM                           = 709;        //参数错误
const UINT32 MERN_PART                                  = 710;        //部分数据
const UINT32 MERN_INITIALIZE                            = 711;        //初始化失败
const UINT32 MERN_WRONG_RSP                             = 712;        //返回http头错误，或尚未返回
const UINT32 MERN_NOT_REQ                               = 713;        //尚未请求
const UINT32 MERN_RECV_FAILED                           = 714;        //接收失败
const UINT32 MERN_TIMEOUT                               = 715;        //操作超时
const UINT32 MERN_ACCEPT                                = 716;        //侦听错误
const UINT32 MERN_CONN_CLOSED                           = 717;        //连接被中断
const UINT32 MERN_AP_WRONG                              = 718;        //接入点无响应
const UINT32 MERN_OFFLINE                               = 719;        //离线状态，网络不可用
//const UINT32 MERN_CANCELD                               = 315;        //http操作canceled，需要重连
//const UINT32 MERN_MORE_DATA                             = 304;        //


//服务器返回自定义错误
const INT32 MERS_SERVER                                  = -1;
const INT32 MERS_NEEDLOGIN                               = -2;
const INT32 MERS_VERSION                                 = -3;
const INT32 MERS_USERNAMEPWD                             = -10;
const INT32 MERS_ALTERPSW                                = -11;
const INT32 MERS_USERUSING                               = -12;
const INT32 MERS_BOUNDED                                 = -16;
const INT32 MERS_IDNOTFOUND                              = -20;
const INT32 MERS_NOTRETURN                               = -21;

//SessionMgr错误800-899
const UINT32 MERE_NOT_ENOUGH_RESOURCE                   = 800;
const UINT32 MERE_SERVER                                = 801;
#endif //__ERRORDEF_H__

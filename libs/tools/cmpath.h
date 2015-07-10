// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description: 文件路径类
//  Author:roy, lss
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMPATH_H_HEADER_INCLUDED_B5BD3A0B
#define CMPATH_H_HEADER_INCLUDED_B5BD3A0B

#include "cmstring.h"

#if defined(PLAT_IOS) || defined(PLAT_AND)
	#define  FILESEPARATOR		L"/"
#elif defined(PLAT_SYMBIAN) || defined(PLAT_WINCE)
	#define  FILESEPARATOR		L"\\"
#endif


class CMPath
{
public:
	typedef enum _DEF_TYPE{
		SYS_CONF_PATH,		//系统配置文件路径
       // CONF_PATH,			//用户配置文件路径
		DATA_PATH,			//数据路径，可配（未实现）
		CARD_PATH,			//存储卡根目录
		WSYS_PATH,          //系统盘根目录
		APP_PATH,			//应用程序目录
		TEMP_PATH,			//临时目录
		DOWNLOAD_PATH,		//下载存储目录
		DOWNLOAD_OLD,		//旧的下载存储目录
        UNZIP_PATH          //课件下载后解压缩目录
	}DEF_TYPE;

	typedef enum _DRV_TYPE{
	    CARD,              //卡路径
        WSYS,              //可写系统盘路径
        ROM                //rom路径
	}DRV_TYPE;


	//通过名称构造
    CMPath(const CMString& sPathName);

	//通过已有Path构造
	CMPath(const CMPath& cPath);

	//自定义的系统路径构造
	CMPath(DEF_TYPE nDefType = DATA_PATH);

    ~CMPath();

	//在已有目录上添加子目录
	//如果已存在，也返回成功
	//成功，路径会变化成新路径
    BOOL AddDir(const CMString& sPathName);

    //判断路径是否存在
    static BOOL PathExist(const CMString& sPathName);
	//返回字符串类型的路径
    const CMString& String();

    //返回当前路径属于的驱动器类型
	DRV_TYPE DriverType();

private:
	CMString m_sPath;
};



#endif /* CMPATH_H_HEADER_INCLUDED_B5BD3A0B */

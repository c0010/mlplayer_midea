// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description: 文件路径类
//  Author:roy, lss
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmpath.h"
//#include <sys/types.h>
#include <sys/stat.h> 
#include <errno.h>
#include <fcntl.h>
#include <jni.h>
#include "android/env.h"

// http://stackoverflow.com/questions/675039/how-can-i-create-directory-tree-in-c-linux
static int do_mkdir(const char *path, mode_t mode)
{
	struct stat            st;
    int             status = 0;

    if (stat(path, &st) != 0)
    {
        /* Directory does not exist. EEXIST for race condition */
        if (mkdir(path, mode) != 0 && errno != EEXIST)
            status = -1;
    }
    else if (!S_ISDIR(st.st_mode))
    {
        errno = ENOTDIR;
        status = -1;
    }

    return(status);
}

/**
** mkpath - ensure all directories in path exist
** Algorithm takes the pessimistic view and works top-down to ensure
** each directory in path exists, rather than optimistically creating
** the last element and working backwards.
*/
int mkpath(const char *path, mode_t mode)
{
    char           *pp;
    char           *sp;
    int             status;
    char           *copypath = strdup(path);

    status = 0;
    pp = copypath;
    while (status == 0 && (sp = strchr(pp, '/')) != 0)
    {
        if (sp != pp)
        {
            /* Neither root nor double slash in path */
            *sp = '\0';
            status = do_mkdir(copypath, mode);
            *sp = '/';
        }
        pp = sp + 1;
    }
    if (status == 0)
        status = do_mkdir(path, mode);
    free(copypath);
    return (status);
}

CMPath::CMPath(const CMString& sPathName)
{
    m_sPath = sPathName;
}

CMPath::CMPath(const CMPath& cPath)
{
    m_sPath = cPath.m_sPath;
}

CMPath::CMPath(DEF_TYPE nDefType)
{
    switch(nDefType)
    {
       /* 该功能放到CMGlobal中
       
        case CONF_PATH://用户配置文件路径
         {
		 	m_sPath = CMPath(DATA_PATH).String();
			CMString sID;
            if(CMGlobal::TheOne().GetSessionID(sID) && !(CMSettings::GetInstance().m_sName.IsEmpty()))
                AddDir(CMSettings::GetInstance().m_sName + L"/");
            break;
        }*/
        case SYS_CONF_PATH://系统配置文件路径
        case DATA_PATH://数据路径
		{
		   /*     char buf[260];
		        memset(buf,0,260);
		        int ret = readlink("proc/self/exe", buf, 260);
		        if(ret < 0 || ret >= 1024)
		        	break;
			for(INT32 i=strlen(buf)-1;i>0;i--)
			{
				if(buf[i]=='/')
				{
					buf[i+1]=L'\0';
					break;
				}
			}*/
			//CM_ERRP("DATA_PATH%s",buf);
			JNIEnv*  env ;
			if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
				return ;
			jmethodID method = env->GetStaticMethodID(GetGlobalCls(), "getInstance", "()Lcom/wunding/mlplayer/CMGlobal;");
			if(!method)
				return;
			jobject obj = (jobject)env->CallStaticObjectMethod(GetGlobalCls(), method); 
			if(!obj)
				return;
			method = env->GetMethodID(GetGlobalCls(), "GetDataDir", "()Ljava/lang/String;");
			const char * buf = NULL;
			if(method)
			{
				jstring jstr = (jstring)env->CallObjectMethod(obj, method); 
				if(jstr)
				{
					buf = env->GetStringUTFChars(jstr, NULL);
					m_sPath = buf;
					if(buf) 
						env->ReleaseStringUTFChars(jstr, buf);
				}
			}
			m_sPath += L"/";
			//CM_ERRP("DATA_PATH:%s",(const char*)m_sPath);
			break;
		}
		case TEMP_PATH:
		{
			m_sPath = CMPath(DATA_PATH).String();
			AddDir(L"tmp/");
			break;
		}
		case DOWNLOAD_PATH:
		{
			m_sPath = CMPath(DATA_PATH).String();
			if(!m_sPath.IsEmpty())
				AddDir(L"dld/");
			break;
//			m_sPath = CMPath(CARD_PATH).String();
//			if(!m_sPath.IsEmpty()){
//				AddDir(L"wunding_ulp/");
//			}
//			break;
		}
		case DOWNLOAD_OLD:
		{
			m_sPath = CMPath(CARD_PATH).String()+L"wunding_ulp/";
			break;
		}
		case UNZIP_PATH: //下载课件解压缩后目录
		{
			m_sPath = CMPath::CMPath(DOWNLOAD_PATH).String();
			if (!m_sPath.IsEmpty()) {
				AddDir(L"download/");
			}
			break;
		}

		case APP_PATH:
	    {
			m_sPath = CMPath(DATA_PATH).String();
		    break;
		}
	    case CARD_PATH://存储卡根目录
	    {
	    	JNIEnv*  env ;
		if (GetJavaVM()->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
			return ;
		jclass cls = (jclass)env->FindClass("android/os/Environment");
    		if(!cls)
       			return;
		jmethodID method = env->GetStaticMethodID(cls, "getExternalStorageDirectory", "()Ljava/io/File;");
		if(!method)
			return;
		jobject obj = (jobject)env->CallStaticObjectMethod(cls, method); 
		if(!obj)
			return;
			
		cls = (jclass)env->FindClass("java/io/File");
    		if(!cls)
       			return;
		method = env->GetMethodID(cls, "getPath", "()Ljava/lang/String;");
		if(!method)
			return;
		const char * buf = NULL;
		if(method)
		{
			jstring jstr = (jstring)env->CallObjectMethod(obj, method); 
			if(jstr)
			{
				buf = env->GetStringUTFChars(jstr, NULL);
				m_sPath = buf;
				if(buf) 
					env->ReleaseStringUTFChars(jstr, buf);
			}
		}
		m_sPath += L"/";
	        break;
	    }
	    case WSYS_PATH://系统盘根目录
	    {
			m_sPath = L"/";
	        break;
	    }
	    default:
	        break;
    }
}

CMPath::~CMPath()
{
}

BOOL CMPath::AddDir(const CMString& sPathName)
{
    CMString strPath=m_sPath+sPathName;
	if(!PathExist(strPath))
	{
		//权限700
		if (mkpath((const char*)strPath, 0700) != 0) {
			CM_ERRP("mkdir %s error no %d",(const char*)strPath, errno);
			return FALSE;
		}
	}
    m_sPath = strPath;
    return TRUE;
}

BOOL CMPath::PathExist(const CMString& sPathName)
{
    CMString str = sPathName;
    if(access(str,0) != 0)
	return FALSE;
    return TRUE;
}

const CMString& CMPath::String()
{
    return m_sPath;
}

CMPath::DRV_TYPE CMPath::DriverType()
{
    return CMPath::CARD;
}

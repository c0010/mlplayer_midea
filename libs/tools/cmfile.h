// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName: 
//  Description: 文件处理类
//  Author: Tim
// //////////////////////////////////////////////////////////////////////////////
#ifndef CMFILE_H
#define CMFILE_H


#include "cmstring.h"

#if defined(PLAT_IOS) || defined(PLAT_AND)
BOOL CopyFile(const char* src, const char* dst);
BOOL DeleteFile(const char* src);
BOOL RenameFile(const char* src, const char* dst);
BOOL DeleteFileList(const char* src);
#endif

class CMFile
{
public:
    //打开模式
    enum 
    {
        CREATE_W        = 0x1,      //创建新文件，原来存在的删除
        OPEN_R_EXIST    = 0x2,      //打开文件，不存在则出错，存在则可读
        OPEN_W_EXIST    = 0x3,      //打开文件，不存在则出错，存在则可写
        OPEN_RW_EXIST   = 0x4,      //打开文件，不存在则出错，存在则可读写
        OPEN_RW_ALWAYS  = 0x7       //打开文件，不存在则创建，然后读写
    };
    //共享模式
    enum
    {
        SHARE_R     = 0x01,         //共享文件读
        SHARE_W     = 0x02,         //共享文件写
        SHARE_RW        = 0x03,     //共享文件读写
        SHARE_NONE  = 0x04          //不共享文件读写
        
    };
    //文件seek位置
    enum
    {
        FILESEEK_BEGIN,
        FILESEEK_END,
        FILESEEK_CURRENT
    };
public:
    BOOL  Open(const CMString& path,UINT8 openMode = OPEN_RW_ALWAYS,UINT8 shareMode = SHARE_RW);
    INT32 GetPosition()const;
    BOOL  Seek(INT32 pos,UINT8 from = FILESEEK_BEGIN);
    INT32 GetLength()const;
    VOID  Close();
	VOID  Flush();
    INT32 Read(CHAR* buf,INT32 readlen);
    INT32 Write(const CHAR* data,INT32 len);
    static BOOL CopyFile(const CMString& srcpath ,const CMString& destpath);
    static BOOL DeleteFile(const CMString& path);
	static BOOL DeleteFileList(const CMString& path);
    static BOOL FileExist(const CMString& path);
	static BOOL ChangeFileName(const CMString& srcpath ,const CMString& destpath);
    static CMString GetFileExt(const CMString& sFileName);
    static CMString GetTempFileName(const CMString& src, const CMString& ext);

public:
    CMFile();
    ~CMFile();
private:
    BOOL    m_bOpen;
#if defined(PLAT_SYMBIAN)
    RFile   m_cFile;         
    RFs     m_cFfs;
    BOOL    m_bConnect;
#elif defined(PLAT_WINCE) || defined(PLAT_IOS) || defined(PLAT_AND)
    FILE*   m_pFile;
    INT32   m_nLen;
#endif
};// END CLASS DEFINITION CXFile


#endif // CMFILE_H

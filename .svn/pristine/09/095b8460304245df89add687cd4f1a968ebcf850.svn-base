#include "stdafx.h"
#include "cmfile.h"
#include "md5.h"

#ifdef PLAT_SYMBIAN
    #include <BAUTILS.H>
	#include <EIKENV.H>
#elif defined(PLAT_AND)
    #include <errno.h>
	#include <unistd.h>
#endif

// FuncName: Open
// Description: 打开文件
// Variables: path 路径，openMode 打开模式，shareMode共享模式
// Return:状态
BOOL CMFile::Open(const CMString& path,UINT8 openMode,UINT8 shareMode)
{
    if(path.IsEmpty())
        return FALSE;
    if(m_bOpen)
        Close();
    const WCHAR   *pFileName = path;
#ifdef PLAT_SYMBIAN
    if(!m_bConnect)
        return FALSE;
    UINT32  flag = 0;
    INT32   fileret;
    TPtrC ptr((const UINT16*)pFileName);
    if(openMode == CREATE_W||openMode==OPEN_W_EXIST||openMode==OPEN_RW_EXIST||openMode==OPEN_RW_ALWAYS)
    {
        switch(shareMode)
        {
        case SHARE_R:
            flag = EFileShareAny|EFileRead;
            break;
        case SHARE_W:
            flag = EFileShareAny|EFileWrite;
            break;
        case SHARE_RW:
            flag = EFileShareAny|EFileWrite;
            break;
        case SHARE_NONE:
            flag = EFileShareAny|EFileWrite;
            break;
        }
    }
    else if(openMode == OPEN_R_EXIST)
    {
        switch(shareMode)
        {
        case SHARE_R:
            flag = EFileShareReadersOnly|EFileRead;
            break;
        case SHARE_W:
            flag = EFileShareAny|EFileWrite;
            break;
        case SHARE_RW:
            flag = EFileShareAny|EFileWrite;
            break;
        case SHARE_NONE:
            flag = EFileShareAny|EFileWrite;
            break;
        }
    }
    else
        return FALSE;
    if(openMode == CREATE_W)
    {
        fileret = m_cFile.Open(m_cFfs,ptr,flag);
        if(fileret == KErrNone)
        {
            m_cFile.Close();
            if(DeleteFile(path))
            {       
                fileret = m_cFile.Create(m_cFfs,ptr,flag);
                if(fileret != KErrNone)     
                    m_bOpen = FALSE;
                else
                    m_bOpen=TRUE;
            }
            else
                m_bOpen = FALSE;
        }
        if(fileret != KErrNone)
        {
            fileret = m_cFile.Create(m_cFfs,ptr,flag);
            if(fileret != KErrNone)     
                m_bOpen = FALSE;
            else
                m_bOpen=TRUE;
        }
    }
    if(openMode == OPEN_RW_ALWAYS )
    {
        fileret = m_cFile.Open(m_cFfs,ptr,flag);
        if(fileret != KErrNone)
        {
            fileret = m_cFile.Create(m_cFfs,ptr,flag);
            if(fileret != KErrNone)     
                m_bOpen = FALSE;
            else
                m_bOpen=TRUE;
        }
        else
            m_bOpen=TRUE;
    }
    else if(openMode == OPEN_W_EXIST || openMode == OPEN_RW_EXIST ||openMode == OPEN_R_EXIST)
    {
        fileret = m_cFile.Open(m_cFfs,ptr,flag);
        if(fileret != KErrNone)
            m_bOpen = FALSE;
        else{
            m_bOpen=TRUE;
        }
    }
#else
    CHAR szMode[8]={0};
    switch(openMode)
    {
    case CREATE_W:
		if(FileExist(path))
			this->DeleteFile(path);
        strcpy(szMode, "wb");
        break;
    case OPEN_R_EXIST:
        strcpy(szMode, "rb");
        break;
    case OPEN_W_EXIST:
        strcpy(szMode, "ab");
        break;
    case OPEN_RW_EXIST:
        strcpy(szMode, "rwb");
        break;
    case OPEN_RW_ALWAYS:
        strcpy(szMode, "a+b");
        break;
    default:
        return FALSE;
    }
	char filename[MAX_PATH] = {0};
	ConvertUnicodeToAnsi(path, filename, MAX_PATH);
    m_pFile = fopen(filename, szMode);
    if(!m_pFile)
        return FALSE;
    fseek(m_pFile,0,SEEK_END);   
    m_nLen=ftell(m_pFile);
    fseek(m_pFile,0,SEEK_SET);
    m_bOpen=TRUE;
#endif
    return m_bOpen;
}
CMFile::CMFile(void)
{
    m_bOpen = FALSE;
#ifdef PLAT_SYMBIAN
    INT32 ret = m_cFfs.Connect();
    if(ret != KErrNone)
       m_bConnect = FALSE;
    else
        m_bConnect = TRUE;
#else
    m_pFile = NULL;
    m_nLen = 0;
#endif
 }

CMFile::~CMFile(void)
{
    if(m_bOpen)
        Close();
#ifdef PLAT_SYMBIAN
    if(m_bConnect )
        m_cFfs.Close();
#endif
}
void CMFile::Close()
{
#ifdef PLAT_SYMBIAN
    if(m_bOpen)
        m_cFile.Close();
#else
    if(m_pFile)
        ::fclose(m_pFile);
    m_pFile = NULL;
    m_nLen = 0;
#endif
    m_bOpen = FALSE;
}
// FuncName:DeleteFile
// Description: 删除文件
// Variables: path 路径
// Return:状态
BOOL CMFile::DeleteFile(const CMString & path)
{
    const WCHAR *pFileName = path;
    if(pFileName == NULL)
        return FALSE;
#if defined(PLAT_SYMBIAN)
    TPtrC ptr((const UINT16*)pFileName);
    RFs   rfs;
    INT32 ret = rfs.Connect();
    BOOL iOpen = FALSE;
    if(ret != KErrNone) 
        return FALSE;
    rfs.IsFileOpen(ptr,iOpen);
    if(iOpen)
    {
        rfs.Close();
        return FALSE;
    }
    ret = rfs.Delete(ptr);
    rfs.Close();
    if(ret != KErrNone) 
        return FALSE;
#elif defined(PLAT_WINCE)
    return ::DeleteFile(path);
#elif defined(PLAT_IOS) || defined(PLAT_AND)
	CMString& sPath = (CMString&)path;
	return ::DeleteFile((const CHAR*)sPath);
#endif
    return TRUE;
}

//删除遍历出的文件
BOOL CMFile::DeleteFileList(const CMString &path)
{	
	const WCHAR *pFileName = path;
    if(pFileName == NULL)
        return FALSE;
	CMString& sPath = (CMString&)path;
#if defined(PLAT_SYMBIAN)
	TPtrC ptr((const UINT16*)pFileName);
	CFileMan* fileMan = CFileMan::NewL( CEikonEnv::Static()->FsSession());
	fileMan->RmDir(ptr);
	delete fileMan;
	return TRUE;
#elif defined(PLAT_WINCE)
	TCHAR	szFile[MAX_PATH]		= {0};
	TCHAR	szFindFile[MAX_PATH]	= {0};
	WIN32_FIND_DATA findData;
	HANDLE fileHandle;

	_tcscpy(szFindFile, pFileName);
	_tcscat(szFindFile, _T("*.*"));

	fileHandle = ::FindFirstFile(szFindFile, &findData);
	if (fileHandle == INVALID_HANDLE_VALUE) 
	{
		return TRUE;
	} 
	else 
	{
		do
		{
			memset(szFile, 0x00, sizeof(TCHAR) * MAX_PATH);
			_stprintf(szFile,_T("%s%s"), pFileName, findData.cFileName);
			::DeleteFile(szFile);
		}while (FindNextFile(fileHandle, &findData) != 0);
		FindClose(fileHandle);
	}
    return TRUE;
#elif defined(PLAT_IOS) || defined(PLAT_AND)
	return ::DeleteFileList((const CHAR*)sPath);
#endif	
}


// FuncName:Read
// Description: 读取文件
// Variables: buf 缓冲区，readlen读取长度
// Return:-1,读取文件失败否则成功，返回长度
INT32 CMFile::Read(CHAR* buf,INT32 readlen)
{
    if(buf == NULL || readlen <= 0)
        return -1;
    INT32 length = 0;
#ifdef PLAT_SYMBIAN
    if(!m_bOpen || !m_bConnect)
        return -1;
    INT32 filesize = 0;
    m_cFile.Size(filesize);
    INT32 CurrentPos = 0;
    m_cFile.Seek(ESeekCurrent,CurrentPos);
    if(CurrentPos + readlen > filesize)
    {
        readlen = filesize - CurrentPos;
    }
    TPtr8 temp((UINT8*)buf,readlen,readlen);
    INT32 ret = m_cFile.Read(temp,readlen);
    if(ret != KErrNone)
        return -1;
    length = temp.Length();
    //pBuf[length] = '\0';
#else
    // http://stackoverflow.com/questions/16632889/feof-detecting-false-end-of-file
    // not use feof
    if(!m_bOpen)
        return -1;
    length = fread((void*)buf,1,readlen,m_pFile);
#endif
     return length;
}
// FuncName:GetPosition
// Description: 获取文件当前位置
// Variables: 
// Return:-1失败否则返回位置
INT32  CMFile::GetPosition()const
{
    if(!m_bOpen)
        return -1;
    INT32 pos = 0;
#ifdef PLAT_SYMBIAN
    TInt err = m_cFile.Seek(ESeekCurrent,pos);
    if(err != KErrNone)
        return -1;
#else
    //fseek(m_pFile,0,FILESEEK_CURRENT);   
    pos=ftell(m_pFile);//失败ftell 返回 -1
#endif
    return pos;
}
// FuncName:Seek
// Description: 文件指针定位
// Variables: pos 偏移位置，from 定位点
// Return:状态
BOOL CMFile::Seek(INT32 pos,UINT8 from)
{
    if(!m_bOpen)
        return FALSE;
#ifdef PLAT_SYMBIAN
    INT32 error = 0;
    INT32 size = 0;
    m_cFile.Size(size);
    INT32 CurrentPos = 0;
    switch(from)
    {
    case FILESEEK_BEGIN:
    {
        if(pos > size)
            return FALSE;
        error = m_cFile.Seek(ESeekStart,pos);
        break;
    }
    case FILESEEK_END:
    {
        error = m_cFile.Seek(ESeekEnd,pos);
        break;
    }
    case FILESEEK_CURRENT:
    {
        m_cFile.Seek(ESeekCurrent,CurrentPos);
        if(CurrentPos + pos > size)
            return FALSE;
        m_cFile.Seek(ESeekCurrent,pos);
        break;
    }
    default:
        break;
    }
    if(error != KErrNone)
        return FALSE;
#else
    INT32 nret=0;
    switch(from)
    {
    case FILESEEK_BEGIN:
        nret=fseek(m_pFile,pos,SEEK_SET);
        break;
    case FILESEEK_END:
        nret=fseek(m_pFile,pos,SEEK_END);
        break;
    case FILESEEK_CURRENT:
        nret=fseek(m_pFile,pos,SEEK_CUR);
        break;
    default:
        return FALSE;
    }
    if(nret!=0)
        return FALSE;
#endif
    return TRUE;
}
// FuncName:GetLength
// Description: 获取文件长度
// Variables: 
// Return:-1文件没打开，否则返回长度
INT32 CMFile::GetLength()const
{
    if(!m_bOpen)
        return -1;
#ifdef PLAT_SYMBIAN
    INT32 size = -1;
    m_cFile.Size(size);
    return size;
#else
    return m_nLen;    
#endif
}
// FuncName:Write
// Description: 写文件
// Variables: data缓冲数据，len长度
// Return:-1无法写入否则为写入长度
INT32 CMFile::Write(const CHAR* data,INT32 len)
{
    if(data == NULL || len <= 0)
        return -1;
    if(!m_bOpen)
        return -1;
#ifdef PLAT_SYMBIAN
    TPtrC8 temp((UINT8*)data,len);
    INT32 pos = 0;
    m_cFile.Seek(ESeekCurrent,pos);
    INT32 ret = m_cFile.Write(pos,temp);
    if(ret != KErrNone) 
        return -1;
#else
    INT32 size=fwrite(data,1,len,m_pFile);
    return size;    
#endif
    return len;
}
// FuncName:FileExist
// Description: 判断文件存在
// Variables: path 路径
// Return:状态
BOOL CMFile::FileExist(const CMString& path)
{
    const WCHAR* spath=path;
#ifdef PLAT_SYMBIAN
     TPtrC ptr((const TUint16*)spath,path.GetLength());
    if(BaflUtils::FileExists(CCoeEnv::Static()->FsSession(), ptr)==EFalse)  
        return FALSE;
#else
	char filename[MAX_PATH] = {0};
	ConvertUnicodeToAnsi(path, filename, MAX_PATH);
#ifdef PLAT_AND
	if( access( filename, F_OK ) == -1 ) {
	    // file doesn't exist
		int e = errno;
		CM_LOGP(CM_LOGL_TRACE, "file %s does not exist, errno:%d", filename, e);
		return FALSE;
	}
#else
    FILE *fp = fopen(filename, "r");
    if(!fp)
        return FALSE;
    fclose(fp);
    fp = NULL;
#endif
#endif
    return TRUE;
}
VOID CMFile::Flush()
{
	if(!m_bOpen)
		return;
#ifdef PLAT_SYMBIAN
	m_cFile.Flush();
#else
	fflush(m_pFile);
#endif

}
BOOL CMFile::ChangeFileName(const CMString& src ,const CMString& dest)
{
	if(src.IsEmpty() || dest.IsEmpty())
		return FALSE;
	const WCHAR* wsrc = src;
	const WCHAR* wdest = dest;
#if defined(PLAT_WINCE)
	return ::MoveFile(wsrc,wdest);
#elif defined(PLAT_SYMBIAN)
	RFs fs;
	fs.Connect();
    TPtrC ptr1((const UINT16*)wsrc,src.GetLength());
    TPtrC ptr2((const UINT16*)wdest,dest.GetLength());
	INT32 err=fs.Rename(ptr1,ptr2);
	fs.Close();
	if(err==KErrNone)
		return TRUE;
	else
		return FALSE;
#elif defined(PLAT_IOS) || defined(PLAT_AND)
	CMString& sSrc = (CMString&)src;
	CMString& sDst = (CMString&)dest;
	return ::RenameFile((const CHAR*)sSrc, (const CHAR*)sDst);
#endif
	
}

BOOL CMFile::CopyFile(const CMString& src ,const CMString& dest)
{
	if(src.IsEmpty() || dest.IsEmpty())
		return FALSE;
	const WCHAR* wsrc = src;
	const WCHAR* wdest = dest;
#if defined(PLAT_WINCE)
	return ::CopyFile(wsrc,wdest, FALSE);
#elif defined(PLAT_SYMBIAN)
    TPtrC ptrSrc((const UINT16*)wsrc,src.GetLength());
    TPtrC ptrDst((const UINT16*)wdest,dest.GetLength());
    return (BaflUtils::CopyFile(CCoeEnv::Static()->FsSession(), ptrSrc, ptrDst) == KErrNone);
#elif defined(PLAT_IOS) || defined(PLAT_AND)
	CMString& sSrc = (CMString&)src;
	CMString& sDst = (CMString&)dest;
	return ::CopyFile((const CHAR*)sSrc, (const CHAR*)sDst);
#endif
	
}
CMString CMFile::GetFileExt(const CMString& sFileName)
{
    INT32 pos = sFileName.ReverseFind(L".");
	if(pos < 0)
		return L"";
	CMString sExt = sFileName.Mid(pos+1);
    if(sExt.GetLength() > 4)
        sExt = L"";
	return sExt;
}

CMString CMFile::GetTempFileName(const CMString& src, const CMString& ext)
{
    char digest[33] = {0};
    MD5_CTX ctx;

	MD5Init(&ctx , 0);

    MD5Update (&ctx, (unsigned char *)(const WCHAR*)src, src.GetLength()*sizeof(WCHAR));

	MD5Final (&ctx) ;

    for(INT32 i = 0;i < 16;i++)
        sprintf(digest, "%s%02X", digest, ctx.digest[i]);

    CMString ret(digest);
    if(!ext.IsEmpty())
    {
        ret += L".";
        ret += ext;
    }

	return ret;
}

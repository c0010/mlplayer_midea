// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:日志类。可以控制级别、模块进行日志输出
//  Author:roy
// //////////////////////////////////////////////////////////////////////////////

#ifndef __CMLOGGER__
#define __CMLOGGER__

//使用方法
//CM_LOGP(CM_LOGL_ERR, "error no is %d", d);
//CM_LOG(CM_LOGL_DEBUG, "I'm back")
//为统一，以及效率，只支持char
//目前使用全局唯一实例

#if defined(PLAT_SYMBIAN)
typedef __e32_va_list va_list;
#endif

#define FILNAME_TYPE  const char*

//#define NO_LOG 1
#define CM_LOG_MAX_LINE    1024*20

// loglevel
typedef enum _LOG_LVL{
CM_LOGL_CRIT,         /* critical conditions              */
CM_LOGL_ERR,          /* error conditions                 */
CM_LOGL_WARNING,      /* warning conditions               */
CM_LOGL_INFO,         /* informational                    */
CM_LOGL_DEBUG,        /* debug-level messages             */
CM_LOGL_TRACE         /* trace-level messages             */
} LOG_LVL;

// logtype
typedef enum _LOG_TYPE{
CM_LOGT_FILE = 0,
CM_LOGT_CONSOLE,
CM_LOGT_DEBUGER,
CM_LOGT_SCREEN
} LOG_TYPE;

// logmod
// if used,don't change
#define CM_LOGM_COMMON   1           //used
#define CM_LOGM_PLAT     2
#define CM_LOGM_SERVICE  4
#define CM_LOGM_NET      8           //used
#define CM_LOGM_BUFFER   16          //used
#define CM_LOGM_SOUND    32          //used
#define CM_LOGM_DEBUG    32768          //used    用于临时指定某个文件的日志可以输出
#define CM_LOGM_ALL      65535 

#ifndef FILE_MOD
#define FILE_MOD  CM_LOGM_COMMON
#endif


//#if defined(NO_LOG)
//#define CM_TRACE(fmt)
//#define CM_ERRP(fmt, ...)
//#define CM_ERR(fmt)
//#define CM_LOGP(lvl, fmt, ...)
//#define CM_LOG(lvl, fmt)
//#define CM_DUMP(lvl, mem, len)
//#else
#if defined(PLAT_WINCE)
//日志等级低或者不属于指定模块范畴的日志都不输出
#define CM_TRACE(fmt) \
    if (CMLogger::GetLogger()->m_logmod & FILE_MOD) \
	    CMLogger::GetLogger()->Log(CM_LOGL_TRACE, __LINE__, __FILE__, fmt)

#define CM_ERRP(fmt, ...) \
    if (CM_LOGL_ERR <= CMLogger::GetLogger()->m_loglvl &&  CMLogger::GetLogger()->m_logmod & FILE_MOD) \
	    CMLogger::GetLogger()->Log(CM_LOGL_ERR, __LINE__, __FILE__, fmt, __VA_ARGS__)

#define CM_ERR(fmt) \
    if (CM_LOGL_ERR <= CMLogger::GetLogger()->m_loglvl &&  CMLogger::GetLogger()->m_logmod & FILE_MOD) \
        CMLogger::GetLogger()->Log(CM_LOGL_ERR, __LINE__, __FILE__, fmt)

#define CM_LOGP(lvl, fmt, ...) \
    if (lvl <= CMLogger::GetLogger()->m_loglvl &&  CMLogger::GetLogger()->m_logmod & FILE_MOD) \
	    CMLogger::GetLogger()->Log(lvl, __LINE__, __FILE__, fmt, __VA_ARGS__)

#define CM_LOG(lvl, fmt) \
    if (lvl <= CMLogger::GetLogger()->m_loglvl &&  CMLogger::GetLogger()->m_logmod & FILE_MOD) \
        CMLogger::GetLogger()->Log(lvl, __LINE__, __FILE__, fmt)
#elif defined(PLAT_SYMBIAN) || defined(PLAT_IOS) || defined(PLAT_AND)
#define CM_TRACE(fmt) \
    if (CMLogger::GetLogger()->m_logmod & FILE_MOD) \
        CMLogger::GetLogger()->Log(CM_LOGL_TRACE, __LINE__, __FILE__, sTmp)

#define CM_ERRP(fmt, arg...) \
    if (CM_LOGL_ERR <= CMLogger::GetLogger()->m_loglvl &&  CMLogger::GetLogger()->m_logmod & FILE_MOD) \
        CMLogger::GetLogger()->Log(CM_LOGL_ERR, __LINE__, __FILE__, fmt, arg)

#define CM_ERR(fmt) \
    if (CM_LOGL_ERR <= CMLogger::GetLogger()->m_loglvl &&  CMLogger::GetLogger()->m_logmod & FILE_MOD) \
        CMLogger::GetLogger()->Log(CM_LOGL_ERR, __LINE__, __FILE__, fmt)

#define CM_LOGP(lvl, fmt, arg...) \
    if (lvl <= CMLogger::GetLogger()->m_loglvl &&  CMLogger::GetLogger()->m_logmod & FILE_MOD) \
        CMLogger::GetLogger()->Log(lvl, __LINE__, __FILE__, fmt, arg)

#define CM_LOG(lvl, fmt) \
    if (lvl <= CMLogger::GetLogger()->m_loglvl &&  CMLogger::GetLogger()->m_logmod & FILE_MOD) \
        CMLogger::GetLogger()->Log(lvl, __LINE__, __FILE__, fmt)
#endif
#define CM_DUMP(lvl, mem, len) \
    if (lvl <= CMLogger::GetLogger()->m_loglvl &&  CMLogger::GetLogger()->m_logmod & FILE_MOD) \
        CMLogger::GetLogger()->Dump(lvl, __LINE__, __FILE__, mem, len)
//#endif

#define CM_LOGRELEASE CMLogger::Release()

class CMFile;
class CMMutex;
class CMLogger
{
public:
	~CMLogger(void);
	static void Release();
	static CMLogger* GetLogger();
//interface
public:
	void Log(LOG_LVL lvl, UINT32 line, FILNAME_TYPE pathname, const CHAR* fmt, ...);
	void Dump(LOG_LVL lvl, UINT32 line, FILNAME_TYPE pathname, INT8* mem, UINT32 len);

	void SetLevel(LOG_LVL lvl) {m_loglvl = lvl;}
	void SetMod(UINT16 mod) {m_logmod = mod;}
	void SetType(LOG_TYPE type) {m_logtype = type;}

//inherit
protected:

//implement
private:
	//default: LOG_LVL lvl=CM_LOGL_ERR, LOG_TYPE type=CM_LOGT_FILE, LOG_MOD mod=CM_LOGM_ALL
	CMLogger();
	CMFile* GetLogFile();
	void Output(const CHAR* s);

    CMMutex*  m_pMutex;
//variable
public:
	LOG_LVL  m_loglvl;
	LOG_TYPE m_logtype;
	UINT16   m_logmod;

	CMFile*  m_logfile;
};

#if defined(PLAT_IOS)
void IPHLog (const char *format, ...);
void IPHLogColor (const char *content, LOG_LVL lvl );

#endif

#endif //__CMLOGGER__

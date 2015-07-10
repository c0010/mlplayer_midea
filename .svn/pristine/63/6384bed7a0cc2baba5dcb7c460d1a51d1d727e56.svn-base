#ifndef _MVLOCALDATASOURCE_INCLUDE
#define _MVLOCALDATASOURCE_INCLUDE
#include "cmtimer.h"
#include "cmfile.h"
#include "mplayerinterface.h"
class CMStreamBuffer;
class CMAnalyze;
class CMLocalDataSource:public IMNotifyTimer,public IMDataInter
{
public:
	CMLocalDataSource();
	~CMLocalDataSource();
	virtual BOOL Init(IMDataNotify* pNetworkNotify, CMStreamBuffer* pStreamBuffer);
	virtual BOOL Open(const CMString& sUrl, int mtype);
	virtual BOOL IsRunning(){return m_bRunning;};
	virtual void Start();
	virtual void Stop() ;
	virtual void Seek(UINT32 msec) ;
	virtual void GetHeadInfo(Med_Info& HeadInfo) ;

	void OnTimer(CMTimer &cTimer) ;
private:
	void Reset();
	//user for 3MV
	BOOL ParseData();
	int  ParsePacket(CHAR* buf,int len);
	//user for AAC
	BOOL ParseAAC();

private:
	CMFile			m_File;
	BOOL            m_bRunning;
	Med_Packet*		m_pMedPacket;
	IMDataNotify*   m_pNotify;
	CMStreamBuffer* m_pStreamBuffer;
	CMTimer*        m_pTimer;
	CMAnalyze*      m_pAnalyze;
	CHAR*			m_pReadBuf; 
	BOOL            m_bHeadComplete;
	BOOL            m_bSeek;
	int             m_nParseLen;//解析长度
	int             m_nMode;

};
#endif

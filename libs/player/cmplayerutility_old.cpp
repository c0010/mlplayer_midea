// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "cmsetting.h"
//#include "cmglobal.h"
#include "cmplayerutility.h"
#include "cmaudioplay.h"
//#include "cmrect.h"
#include "cmstreambuffer.h"
#include "cmnetdatasource.h"
#include "cmaacdatasource.h"
#include "cmlocaldatasource.h"
#include "cmvideoplay.h"
#include "cmpath.h"


CMPlayerUtility::CMPlayerUtility(IMPlayerUtilityObserver& rPlayerObserver)
 : m_PlayerObserver(rPlayerObserver)
 , m_UserData(NULL)
 , m_pStreamBuffer(NULL)
 , m_pMediaData(NULL)
 , m_pAudioPlay(NULL)
 , m_pVideoPlay(NULL)
 , m_nState(EUnKnown)
 , m_nDuration(0)
 , m_nPosition(0)
 , m_nBufTime(60)
 , m_bOnlyAudio(FALSE)
 , m_bDataCompleted(FALSE)
 , m_bOpened(FALSE)
 , m_bManuPause(FALSE)
{
}

CMPlayerUtility::~CMPlayerUtility()
{
    this->Close();
    SAFEDELETE(m_pMediaData);
    SAFEDELETE(m_pVideoPlay);
    SAFEDELETE(m_pAudioPlay);
    SAFEDELETE(m_pStreamBuffer);
}

BOOL CMPlayerUtility::Init()
{
    if(m_nState == EUnKnown)
    {
        m_pStreamBuffer = new CMStreamBuffer;
        if(m_pStreamBuffer)
            m_pAudioPlay = new CMAudioPlay(*this, m_pStreamBuffer);
        if(m_pAudioPlay)
            m_pVideoPlay = new CMVideoPlay(*this, *m_pAudioPlay, m_pStreamBuffer);
        
        if(m_pStreamBuffer && m_pAudioPlay && m_pVideoPlay)
        {
            m_PlayerObserver.StateChange(m_UserData, EReady, m_nState);
            m_nState = EReady;
            return TRUE;
        }
        else
        {
            SAFEDELETE(m_pStreamBuffer);
            SAFEDELETE(m_pAudioPlay);
            SAFEDELETE(m_pVideoPlay);
            return FALSE;
        }
    }
    else
        return FALSE;
}

void CMPlayerUtility::OpenUrl(CMString sUrl, const UINT32 nMode/* = EMode_3mv*/, const char* coursewareID )
{
    
    string path = CMCourseDownload::GetInstance()->GetLocalFilePath(coursewareID);
    
    //先检查本地文件在不在
    if(path.size() !=0 && CMFile::FileExist(CMString(path.c_str())))
    {
    	OpenFile(CMString(path.c_str()), nMode);
    	return;
    }
    
	CMPath tmpPath(CMPath::DOWNLOAD_PATH);
    CMString sOrgUrl;

    INT32 pos = sUrl.ReverseFind(L"?sid=");
    if(pos < 0)
    	pos = sUrl.ReverseFind(L"&sid=");
    if(pos > 0)
    	sOrgUrl = sUrl.Left(pos);
    else
    	sOrgUrl = sUrl;
    
    
    CMString filename = tmpPath.String()+CMFile::GetTempFileName(sOrgUrl, "");
	if(CMFile::FileExist(filename))
    {
    	OpenFile(filename, nMode);
    	return;
    }
    //本地无此文件，去数据库读取
    if(m_nState == EReady)
    {
        m_bDataCompleted = FALSE;
        SAFEDELETE(m_pMediaData);
        m_bOnlyAudio = nMode != EMode_3mv;
        if(nMode == EMode_3mv || nMode == EMode_3ma)
            m_pMediaData = new CMNetDataSource;
		else if(nMode == EMode_aac)
			 m_pMediaData = new CMAACDataSource;
		else
			return;
        BOOL ret = FALSE;
        
//        sUrl = CMString("http://42.96.138.63/Upload/Files/root/CourseWareFile/201401/201401101233202695248e5b93f75f4685af/201401161429192546803cd48b08aa3daf7f_(960x640).3mv");
        printf("surl:%s \n",(const CHAR*)sUrl);
        
        if(m_pMediaData && m_pMediaData->Init(this, m_pStreamBuffer))
            ret = m_pMediaData->Open(sUrl, NET_VOD);
        if(ret)
        {
            m_pMediaData->Start();
            m_PlayerObserver.StateChange(m_UserData, EOpening, m_nState);
            m_nState = EOpening;
        }
        else
            SAFEDELETE(m_pMediaData);
    }
}

void CMPlayerUtility::OpenFile(CMString sFileName, const UINT32 nMode/* = EMode_3mv*/)
{
    if(m_nState == EReady)
    {
        m_bDataCompleted = FALSE;
        SAFEDELETE(m_pMediaData);

        m_pMediaData = new CMLocalDataSource;
        BOOL ret = FALSE;
        m_bOnlyAudio = nMode != EMode_3mv;
        if(m_pMediaData && m_pMediaData->Init(this, m_pStreamBuffer))
            ret = m_pMediaData->Open(sFileName, nMode);
        if(ret)
        {
            m_PlayerObserver.StateChange(m_UserData, EOpening, m_nState);
            m_nState = EOpening;
            m_pMediaData->Start();
        }
        else
            SAFEDELETE(m_pMediaData);
    }
}

void CMPlayerUtility::Play()
{
	if (m_bManuPause)
		return;
    if(m_nState == EPaused || m_nState == EStopped)
    {
        if(m_nState == EStopped)
        {
            m_bDataCompleted = FALSE;
            m_PlayerObserver.StateChange(m_UserData, EOpening, m_nState);
            m_nState =  EOpening;
            m_pMediaData->Start();
        }
        else
        {
            m_PlayerObserver.StateChange(m_UserData, EPlaying, m_nState);
            m_nState = EPlaying;
            m_pAudioPlay->Play();
			if(!m_bOnlyAudio && m_pStreamBuffer->StreamCount() > 1)
				m_pVideoPlay->Play();
        }
    }
}

void CMPlayerUtility::Pause()
{
    if(m_nState == EPlaying)
    {
        m_pAudioPlay->Pause();
		if(!m_bOnlyAudio && m_pStreamBuffer->StreamCount() > 1)
			m_pVideoPlay->Pause();
        m_PlayerObserver.StateChange(m_UserData, EPaused, m_nState);
        m_nState = EPaused;
    }
}

void CMPlayerUtility::Stop()
{
    if(m_nState == EPlaying || m_nState == EPaused || m_nState == EOpening )
    {
        m_pMediaData->Stop();
        if(m_nState == EPlaying || m_nState == EPaused)
        {
            m_pAudioPlay->Stop();
			if(!m_bOnlyAudio && m_pStreamBuffer->StreamCount() > 1)
				m_pVideoPlay->Stop();
        }
        m_nPosition = 0;
        m_bManuPause = FALSE;
        m_PlayerObserver.StateChange(m_UserData, EStopped, m_nState);
        m_nState = EStopped;
    }
}

void CMPlayerUtility::Close()
{
    this->Stop();
    if(m_nState == EStopped)
    {
        if(m_bOpened)
        {
            m_pAudioPlay->Close();
			if(!m_bOnlyAudio && m_pStreamBuffer->StreamCount() > 1)
				m_pVideoPlay->Close();
            m_bOpened = FALSE;
        }
        m_PlayerObserver.StateChange(m_UserData, EReady, m_nState);
        m_nState = EReady;        
    }
}

INT32 CMPlayerUtility::Duration()
{
    return m_nDuration;
}

INT32 CMPlayerUtility::GetPosition()
{
    return m_nPosition;
}

void CMPlayerUtility::SetPosition(INT32 nPos)
{
    if(m_pMediaData)
    {
        m_bDataCompleted = FALSE;
        m_pMediaData->Seek(nPos);
    }
}

INT32 CMPlayerUtility::MaxVolume()
{
    INT32 nVol = 0;
    if(m_pAudioPlay)
        nVol = m_pAudioPlay->MaxVolume();
    return nVol;
}

INT32 CMPlayerUtility::GetVolume()
{
    INT32 nVol = 0;
    if(m_pAudioPlay)
        nVol = m_pAudioPlay->GetVolume();
    return nVol;
}

void CMPlayerUtility::SetVolume(INT32 nVolume)
{
    if(m_pAudioPlay)
        m_pAudioPlay->SetVolume(nVolume);
}

void CMPlayerUtility::SetVolPer(UINT32 nPer)
{
	if (nPer > 100) nPer = 100;
	
	int nVol = nPer * MaxVolume() / 100;
	SetVolume(nVol);
}

void CMPlayerUtility::VolUp()
{
	INT32 nOldVol = GetVolume();
	INT32 nMaxVol = MaxVolume();
	
	INT32 nNewVol = nOldVol + 10 * nMaxVol / 100;
	if (nNewVol > nMaxVol) nNewVol = nMaxVol;
	SetVolume(nNewVol);
}

void CMPlayerUtility::VolDown()
{
	INT32 nOldVol = GetVolume();
	INT32 nMaxVol = MaxVolume();

	INT32 nNewVol = nOldVol - 10 * nMaxVol / 100;
	if (nNewVol < 0) nNewVol = 0;
	SetVolume(nNewVol);
}

INT32 CMPlayerUtility::GetRotation()
{
    INT32 nRotation = 0;
    if(m_pVideoPlay)
        nRotation = m_pVideoPlay->GetRotation();
    return nRotation;
}

void CMPlayerUtility::SetRotation(INT32 nRotation)
{
    if(m_pVideoPlay)
        m_pVideoPlay->SetRotation(nRotation);
}

void CMPlayerUtility::SetDrawSize(INT32 nWidth, INT32 nHeight)
{
    if(m_pVideoPlay)
        m_pVideoPlay->SetDrawSize(nWidth, nHeight);
}

void CMPlayerUtility::SetDrawPoint(INT32 nLeft, INT32 nTop)
{
	if(m_pVideoPlay)
		m_pVideoPlay->SetDrawPoint(nLeft, nTop);
}

//void CMPlayerUtility::GetDrawRect(CMRect& rcDraw)
//{
//    if(m_pVideoPlay)
//        m_pVideoPlay->GetDrawRect(rcDraw);
//}
//
//void CMPlayerUtility::SetDrawRect(CMRect& rcDraw)
//{
//    if(m_pVideoPlay)
//        m_pVideoPlay->SetDrawRect(rcDraw);
//}

void CMPlayerUtility::SetManuPause(BOOL pause)
{
	m_bManuPause = pause;
}

BOOL CMPlayerUtility::IsManuPause()
{
	return m_bManuPause;
}

void CMPlayerUtility::OnHeadCompleted(Med_Info& HeadInfo)
{
    if(m_nState == EOpening)
    {
        BOOL ret = FALSE;

        m_nDuration = HeadInfo.duration;

        UINT32 nStreamCount = 0;
        if(HeadInfo.acodec != CODECID_NONE)
            nStreamCount++;
        if(HeadInfo.vcodec != CODECID_NONE)
            nStreamCount++;
        UINT32 nBufferInSecond = m_nBufTime;
        ret = m_pStreamBuffer->Init(((HeadInfo.bitRate+10)*1000/8)*nBufferInSecond, nStreamCount);

//        CM_LOGP(CM_LOGL_DEBUG, "m_pStreamBuffer->Init ret = %d", ret);
        if(ret)
            ret = m_pAudioPlay->Open(HeadInfo.acodec, HeadInfo.channels, HeadInfo.samplerate, HeadInfo.samplebit);

        CM_LOGP(CM_LOGL_DEBUG, "m_pAudioPlay->Open ret = %d", ret);
        if(ret && !m_bOnlyAudio &&  m_pStreamBuffer->StreamCount() > 1)
        {
            ret = m_pVideoPlay->Open(HeadInfo.vcodec, HeadInfo.weight, HeadInfo.height);
            if(ret == FALSE)
                m_pAudioPlay->Close();
        }
        CM_LOGP(CM_LOGL_DEBUG, "m_pVideoPlay->Open ret = %d", ret);

        if(ret)
        {
			m_PlayerObserver.StateChange(m_UserData, EOpening, m_nState);
            m_nState = EOpening;
            m_bOpened = TRUE;
        }
        else
        {
            m_pMediaData->Stop();
            m_PlayerObserver.StateChange(m_UserData, EReady, m_nState);
            m_nState = EReady;
        }
    }
}

void CMPlayerUtility::OnProgressChanged()
{
    UINT32 nPercent = m_pStreamBuffer->GetPercent();

	//自动播放、自动暂停控制
	if(!m_bManuPause && (nPercent >= 80 || IsDataCompleted()))
		Play();
	else if(nPercent < 10 && !IsDataCompleted())
		Pause();
}

void CMPlayerUtility::OnAllCompleted()
{
    m_bDataCompleted = TRUE;
    Play();
    m_PlayerObserver.OnAllCompleted(m_UserData);
}

void CMPlayerUtility::OnSeekTime(UINT32 msec)
{
    m_nPosition = msec;
	if(m_pAudioPlay)
		m_pAudioPlay->PacketClear();
	m_PlayerObserver.ProgressChange(m_UserData, m_pStreamBuffer->GetPercent(), m_nPosition);
}

void CMPlayerUtility::OnError(UINT32 err)
{
    m_PlayerObserver.OnError(m_UserData, err);
    CM_ERRP("OnError            err = %d", err);
}

void CMPlayerUtility::VideoDraw(UINT8* data, INT32 width, INT32 height)
{
	m_PlayerObserver.VideoDraw(data, width, height);
}

void CMPlayerUtility::ProgressChange(INT32 nBufPer, INT32 nPlayPos)
{
    m_nPosition += nPlayPos;

    m_PlayerObserver.ProgressChange(m_UserData, nBufPer, m_nPosition);
}
void CMPlayerUtility::NeedMoreData()
{
    if(m_bDataCompleted)
    {
    	this->Stop();
    }
}

//
//  cmquestionupload.cpp
//  MLPlayer
//
//  Created by sunjj on 13-8-6.
//  Copyright (c) 2013年 w. All rights reserved.
//
#include "stdafx.h"
#include "cmquestionupload.h"


CMQuestionUpload *CMQuestionUpload::m_pTHIS = NULL;


CMQuestionUpload* CMQuestionUpload::GetInstance()
{
	if(m_pTHIS == NULL)
	{
		m_pTHIS = new CMQuestionUpload();
	}
	return m_pTHIS;
}

void  CMQuestionUpload::SetListener(IMSimpleResultListener* pListener)
{
    m_pSimpleListener=pListener;
    
}

CMQuestionUpload::CMQuestionUpload()
{
    m_pSimpleListener=NULL;
    UserData=NULL;
    m_pSession=NULL;
    
}


CMQuestionUpload::~CMQuestionUpload()
{
	m_pTHIS = NULL; //收藏有删除的需求
}



BOOL CMQuestionUpload::AskQuestion(const char* sCategoryID, int nAnonymous, int nValue, const char* sQuestion,const char* filename)
{
    if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
    
    char param[640];
    //构造url
	snprintf(param,sizeof(param),"&categoryid=%s&anonymous=%d&value=%d", sCategoryID, nAnonymous, nValue);
    //构造form数据
    CMList<FormData>* list= new CMList<FormData>;
    //加入文件
    FormData data;
    if(filename!=NULL&&strlen(filename)!=0)
    {
        data.key=CMString("pic");
        data.value=CMString(filename);
        data.dataType=2;
        list->push_back(data);
    }
    //加入文本内容
    data.key=CMString("content");
    data.value=sQuestion;
    data.dataType=1;
    list->push_back(data);

    m_pSession->CommandPost(SERVICE_NEWQUESTION, param,*list);
    SAFEDELETE(list);

    return TRUE;
}

BOOL CMQuestionUpload::AnswerQuestion(const char* sQuestionID, int nAnonymous, const char* sAnswer,const char* filename)
{
    
    if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
    
	char param[640];
	snprintf(param,sizeof(param),"&questionid=%s&anonymous=%d", sQuestionID, nAnonymous);
    //构造form数据
    CMList<FormData>* list= new CMList<FormData>;
	//加入文本内容
    FormData data;

    if(filename!=NULL&&strlen(filename)!=0)
    {
        data.key=CMString("pic");
        data.value=CMString(filename);
        data.dataType=2;
        list->push_back(data);
    }

    data.key=CMString("content");
    data.value=CMString(sAnswer);
    data.dataType=1;
    list->push_back(data);

    m_pSession->CommandPost(SERVICE_ANSWERQUESTION, param,*list);
    SAFEDELETE(list);
    
    return TRUE;
}


BOOL CMQuestionUpload::UpheadPhtho(const char* filename)
{
    if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;

    //构造form数据
    CMList<FormData>* list= new CMList<FormData>;
    //加入filename
    FormData data;
    if(filename!=NULL&&strlen(filename)!=0)
    {
        data.key=CMString("pic");
        data.value=CMString(filename);
        data.dataType=2;
        list->push_back(data);
    }

    m_pSession->CommandPost(SERVICE_UPHEADPHTHO,"",*list);
    SAFEDELETE(list);

    return TRUE;
}




void CMQuestionUpload::SetUserData(void* userdata)
{
    UserData=userdata;
    
}

void CMQuestionUpload::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{

    INT32 result = TResult::EUnknownError;
	if (nCode == MER_OK)
	{
        TiXmlElement *pItem = pDoc->RootElement();
        
		INT32 nErr = -1;
        INT32 nCmdID = 0;
        pItem->QueryIntAttribute("no", &nCmdID);
        
	
		pItem->QueryIntAttribute("errno", &nErr);
        if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
        {
            if (nErr == 0)
            {
                if(m_pSimpleListener)
                    m_pSimpleListener->OnRequestFinish(UserData, TResult::ESuccess);
                return;
            }else
                result = nErr;
        }else
            result = TResult::EProtocolFormatError;

        
    }else if(nCode == MERN_INITIALIZE)
		result = TResult::ENetDisconnect;
	else if(nCode == MERN_OFFLINE)
		result = TResult::ENotSupportOffline;
	else
		result = TResult::ENetTimeout;
    
    if(m_pSimpleListener)
        m_pSimpleListener->OnRequestFinish(UserData, result);
    
}






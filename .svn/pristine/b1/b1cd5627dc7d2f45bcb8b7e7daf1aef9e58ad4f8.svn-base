//
//  cmfileinfo.cpp
//  MLPlayer
//
//  Created by wmgwd on 13-11-11.
//  Copyright (c) 2013年 w. All rights reserved.
//

#include "stdafx.h"
#include "cmfileinfo.h"
#include "cmsession.h"
#include "utf8ncpy.h"
#include "cmglobal.h"

CMFileInfo::CMFileInfo()
{
    m_pSimpleListener = NULL;

    m_pUserData = NULL;

    m_nCmdID = 0;
}

CMFileInfo::CMFileInfo(const CMFileInfo& right)
{
	m_nCmdID = right.m_nCmdID;
	m_sParm = right.m_sParm;
	m_list = right.m_list;
	sMsgCode = right.sMsgCode;
	m_pUserData = right.m_pUserData;
	m_pSimpleListener = right.m_pSimpleListener;
}

CMFileInfo& CMFileInfo::operator=(const CMFileInfo& right)
{
	m_nCmdID = right.m_nCmdID;
	m_sParm = right.m_sParm;
	m_list = right.m_list;
	sMsgCode = right.sMsgCode;
	m_pUserData = right.m_pUserData;
	m_pSimpleListener = right.m_pSimpleListener;
	return *this;
}

CMFileInfo::~CMFileInfo()
{

}

void CMFileInfo::SetListener(IMSimpleResultListener* pListener)
{
    m_pSimpleListener = pListener;
}

void CMFileInfo::SetUserData(void* UserData)
{
    m_pUserData = UserData;
}

void CMFileInfo::OnSimpleResultFinish(int Result)
{
	if(m_pSimpleListener)
		m_pSimpleListener->OnRequestFinish(m_pUserData,Result);
}

void CMFileInfo::CreateNewRoom(const char* name,const char* desc,const char* iconPath,int flag)
{
    char param[300];
    
    const CHAR* sName = CMGlobal::TheOne().Encode(name);

    snprintf(param, 300,"&flag=%d&name=%s", flag, sName);  //有修改

    m_list.clear();

    if (iconPath && strlen(iconPath) > 0)
    {
    	FormData data;
        data.key = "pic";
        data.value = iconPath;
        data.dataType = 2;
        m_list.push_back(data);
    }

    FormData data1;
    data1.key = "desc";
    data1.value = desc;
    data1.dataType = 1;
    m_list.push_back(data1);


    m_nCmdID = SERVICE_CREATEGROUP;
    m_sParm = param;

}

BOOL CMFileInfo::AskQuestion(const char* sCategoryID, int nAnonymous, int nValue, const char* sQuestion, const char* filename, const char* expertsID)  //有修改，添加了参数
{
    char param[640];
    snprintf(param, 640,"&categoryid=%s&anonymous=%d&value=%d", sCategoryID, nAnonymous, nValue);  //有修改

    m_list.clear();

    if (filename && strlen(filename) > 0)
    {
    	FormData data;
        data.key = CMString("pic");
        data.value = CMString(filename);
        data.dataType = 2;
        m_list.push_back(data);
    }
    
    FormData data1;
    data1.key = CMString("content");
    data1.value = sQuestion;
    data1.dataType = 1;
    m_list.push_back(data1);
    
    FormData data2;
    data2.key = CMString("categorytitle");
    data2.value = CMString(sCategoryID);
    data2.dataType = 1;
    m_list.push_back(data2);
    
    FormData data3;
    data3.key = CMString("expertsid");
    data3.value = CMString(expertsID);
    data3.dataType = 1;
    m_list.push_back(data3);

    m_nCmdID = SERVICE_NEWQUESTION;
    m_sParm = param;

    //m_pSession->CommandPost(SERVICE_NEWQUESTION, param, *m_list);   //新添加
    //SAFEDELETE(m_list);
    
    return TRUE;
}

BOOL CMFileInfo::AnswerQuestion(const char* sQuestionID, int nAnonymous, const char* sAnswer, const char* filename)
{
    char param[640];
    snprintf(param, 640,"&questionid=%s&anonymous=%d", sQuestionID, nAnonymous);
    
    m_list.clear();

    if (filename && strlen(filename) > 0)
    {
    	FormData data;
        data.key = CMString("pic");
        data.value = CMString(filename);
        data.dataType = 2;
        m_list.push_back(data);
    }
    
    FormData data;
    data.key = "content";
    data.value = sAnswer;
    data.dataType = 1;
    m_list.push_back(data);
    
    m_nCmdID = SERVICE_ANSWERQUESTION;
    m_sParm = param;
    
    return TRUE;
}

BOOL CMFileInfo::UploadImage(const char* filename,int cmdID){
    m_list.clear();
    
    FormData data;
    
    if(filename && strlen(filename) > 0)
    {
        data.key = CMString("pic");
        data.value = CMString(filename);
        data.dataType = 2;
        m_list.push_back(data);
    }
    
    m_nCmdID = cmdID;
    m_sParm = "";
    
    //m_pSession->CommandPost(SERVICE_UPHEADPHTHO,"",*list);
    //SAFEDELETE(list);
    return TRUE;
}

BOOL CMFileInfo::UpheadPhoto(const char* filename)
{
	return this->UploadImage(filename, SERVICE_UPHEADPHTHO);
}

BOOL CMFileInfo::UpLoadMessageWithPicture(const char* filename)
{
    return this->UploadImage(filename, SERVICE_UPMESSAGEPICTURE);
}

BOOL CMFileInfo::UpLoadMessageWithPicture(const char* filename,const char* msgCode)
{

	this->sMsgCode = msgCode;
    return this->UploadImage(filename, SERVICE_UPMESSAGEPICTURE);
}

BOOL CMFileInfo::UpLoadGroupHeader(const char* roomid , const char* filename)
{
    if(strlen(roomid)==0)
        return false;
    
    char param[640];
    snprintf(param, 640,"id=%s", roomid);
    
    m_list.clear();
    
    FormData data;
    
    if(filename && strlen(filename) > 0)
    {
        data.key = CMString("pic");
        data.value = CMString(filename);
        data.dataType = 2;
        m_list.push_back(data);
    }
    
    m_nCmdID = SERVICE_UPGROUPHEADER;
    m_sParm = param;
    
    return TRUE;
}

BOOL CMFileInfo::operator==(const CMFileInfo &right)
{
    if (this->m_nCmdID == right.m_nCmdID && this->m_sParm == right.m_sParm && this->m_list == right.m_list)
    {
        return TRUE;
    }
    
    return FALSE;
}



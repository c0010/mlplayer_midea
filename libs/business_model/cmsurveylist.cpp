// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmsurveylist.h"
#include "cmglobal.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "utf8ncpy.h"

CMSurveyList::CMSurveyList(IMUpdateDataListener* pListener)
:CMHandler<TSurveyListItem>()
{
	m_pListener = pListener;
}

CMSurveyList::~CMSurveyList()
{

}

BOOL CMSurveyList::GetList()
{
	CMString sParam;
	return Request(SERVICE_GETSURVEYLIST, sParam);
}

BOOL CMSurveyList::RemoveItem(int index)
{
	BOOL ret = FALSE;

	if (!m_lstItem || index < 0 || index >= m_lstItem->size()) {
		return ret;
	}

	m_lstItem->removeAt(index);
	ret = TRUE;
	m_bRefresh=TRUE;
	if(m_pListener)
		m_pListener->OnUpdateDataFinish( m_UserData, TResult::ESuccess);

	return ret;
}

BOOL CMSurveyList::GetTrainSurveyList(const char* trainid)
{
    //CMString sParam;
    
    char sParam[200];
    memset(sParam, 0, 200);
    
    snprintf(sParam, 200, "id=%s",trainid);
    
    return Request(SERVICE_GETMYTRAINSURVEYLIST, sParam);
}

BOOL CMSurveyList::GetSurveyById(const char* surveyId)
{
    if (strlen(surveyId) == 0) {
        return FALSE;
    }
    
    char sParam[200];
    snprintf(sParam,200,"id=%s",surveyId);
    
    return Request(SERVICE_GETSERVEYBYID, sParam);
    m_pSession->Command(SERVICE_GETSERVEYBYID, sParam);

}

//缓存建表
BOOL CMSurveyList::DoCreate(sqlite3* db)
{
	//目前不支持缓存
	return false;
}

//网络回来数据，要入缓存并刷新对象
BOOL CMSurveyList::DoPutItem(TiXmlElement* pItem, sqlite3* db, TSurveyListItem& item)
{
	memset(&item,0,sizeof(TSurveyListItem));
	const char* pstr = pItem->Attribute("id");
	if(pstr)
        utf8ncpy(item.sID, pstr, 99);

	pstr = pItem->Attribute("title");
	if(pstr)
        utf8ncpy(item.sTitle, pstr, 99);

	pItem->Attribute("invitecount", &item.nInvitecount);

	pItem->Attribute("completecount", &item.nCompletecount);

	pstr = pItem->Attribute("desc");
	if(pstr)
        utf8ncpy(item.sDesc, pstr, 599);

	pstr = pItem->Attribute("expiredate");
	if(pstr)
        utf8ncpy(item.sExpiredate, pstr, 99);
    
    return TRUE;
}

//缓存回来数据，读取缓存到对象列表
BOOL CMSurveyList::DoGetCacheItems(sqlite3* db)
{
	return false;
}

//从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
BOOL CMSurveyList::DoRefresh(TSurveyListItem& obj)
{
	return false;
}

//更新缓存，一般先GetItem或者Refresh后，修改，再Update
BOOL CMSurveyList::DoUpdate(TSurveyListItem const & obj)
{
	return false;
}


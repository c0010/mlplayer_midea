// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// /////////////////////////////////////////////////////////////////////////////

#include "cmcourseinfo.h"
#include "cmsession.h"
#include "tinyxml.h"
#include "utf8ncpy.h"
#include "cmlog.h"
#include "cmcontenthandler.h"

//绑定属性,sql中使用
void TCoursewareItem::bindItem(sqlite3_stmt * stmt) const
{
    BindParam(stmt, 1,  sID);
    BindParam(stmt, 2,  sFlag);
    BindParam(stmt, 3,  sTitle);
    BindParam(stmt, 4,  sBrief);
    BindParam(stmt, 5,  sLargeimage);
    BindParam(stmt, 6,  sImage);
    BindParam(stmt, 7,  sThumbs);
    BindParam(stmt, 8,  sType);
    BindParam(stmt, 9,  nCoursewarecount);
    BindParam(stmt, 10, sUrl);
    BindParam(stmt, 11, sPubdate);
    BindParam(stmt, 12, nVC);
    BindParam(stmt, 13, nPV);
    BindParam(stmt, 14, nCommentcount);
    BindParam(stmt, 15, bEnablecomment);
    BindParam(stmt, 16, bEnabledownload);
    BindParam(stmt, 17, bEnablerating);
    BindParam(stmt, 19, sDescription);
    BindParam(stmt, 20, sTag);
    BindParam(stmt, 26, sFavoritedate);
    BindParam(stmt, 27, bMyCompany);
    BindParam(stmt, 28, bIsRated);
    BindParam(stmt, 29, sMarkID);
    BindParam(stmt, 30, sMarkTitle);
    BindParam(stmt, 31, nModel);

    BindParam(stmt, 32, sSetID);

    BindParam(stmt, 33, bIsLearned);
    
    BindParam(stmt, 34, sDownloadUrl);
    
    BindParam(stmt, 35, sMarkPicUrl);
    
    BindParam(stmt, 36, sOrientation);

}

//取出数据,sql中使用
void TCoursewareItem::fetchItem(sqlite3_stmt * stmt)
{
    
    utf8ncpy(sID, (const char*)sqlite3_column_text(stmt, 1), 63);
    
    utf8ncpy(sFlag, (const char*)sqlite3_column_text(stmt, 2), 15);
    
    utf8ncpy(sTitle, (const char*)sqlite3_column_text(stmt, 3), 99);
    
    utf8ncpy(sBrief, (const char*)sqlite3_column_text(stmt, 4), 119);
    
    utf8ncpy(sLargeimage, (const char*)sqlite3_column_text(stmt, 5) ,299);
    
    utf8ncpy(sImage, (const char*)sqlite3_column_text(stmt, 6) ,299);
    
    utf8ncpy(sThumbs, (const char*)sqlite3_column_text(stmt, 7) ,299);
    
    utf8ncpy(sType , (const char*)sqlite3_column_text(stmt, 8) ,63);
    
    nCoursewarecount = sqlite3_column_int(stmt, 9);
    
    utf8ncpy(sUrl, (const char*)sqlite3_column_text(stmt, 10) ,299);
    
    utf8ncpy(sPubdate, (const char*)sqlite3_column_text(stmt, 11) ,19);
    
    nVC = sqlite3_column_int(stmt, 12);
    
    nPV = sqlite3_column_int(stmt, 13);
    
    nCommentcount = sqlite3_column_int(stmt, 14);
    
    bEnablecomment = sqlite3_column_int(stmt, 15);
    
    bEnabledownload = sqlite3_column_int(stmt, 16);
    
    bEnablerating = sqlite3_column_int(stmt, 17);
    
    bEnableShare = sqlite3_column_int(stmt, 18);

    utf8ncpy(sDescription,  (const char*)sqlite3_column_text(stmt, 19) , 449);
    
    utf8ncpy(sTag,  (const char*)sqlite3_column_text(stmt, 20) , 63);
    
    utf8ncpy(sFavoritedate,  (const char*)sqlite3_column_text(stmt, 26) , 19);
    
    bMyCompany = sqlite3_column_int(stmt, 27);
    
    bIsRated=sqlite3_column_int(stmt, 28);
    
    utf8ncpy(sMarkID,  (const char*)sqlite3_column_text(stmt, 29) , 63);
    
    utf8ncpy(sMarkTitle,  (const char*)sqlite3_column_text(stmt, 30) , 19);
    
    nModel=sqlite3_column_int(stmt, 31);
    
    utf8ncpy(sSetID,  (const char*)sqlite3_column_text(stmt, 32) , 63);

    bIsLearned=sqlite3_column_int(stmt, 33);
    
    utf8ncpy(sDownloadUrl,  (const char*)sqlite3_column_text(stmt, 34) , 299);
    
    utf8ncpy(sMarkPicUrl,  (const char*)sqlite3_column_text(stmt, 35) , 299);

    utf8ncpy(sOrientation,  (const char*)sqlite3_column_text(stmt, 36) , 9);

}

TCoursewareItem& TCoursewareItem::operator=(const TBrowserItem& right)
{
    TBrowserItem::operator=(right);

    nCheckStatus=((TCoursewareItem&)right).nCheckStatus;
    
    bIsLearned=((TCoursewareItem&)right).bIsLearned;
    
	utf8ncpy(sSetID, ((TCoursewareItem&)right).sSetID,63);
    
    bDecompressed=((TCoursewareItem&)right).bDecompressed;

	utf8ncpy(sEntryFilePath, ((TCoursewareItem&)right).sEntryFilePath,299);
    
	utf8ncpy(sDownloadUrl, ((TCoursewareItem&)right).sDownloadUrl,299);
    
    utf8ncpy(sLocalFilePath, ((TCoursewareItem&)right).sLocalFilePath,299);

    utf8ncpy(sOrientation, ((TCoursewareItem&)right).sOrientation, 9);


	return *this;
}

BOOL TCoursewareItem::operator==(const TBrowserItem& right)
{
	if (strcmp(this->sID, right.sID) == 0)
	{
		return TRUE;
	}
    
	return FALSE;
    
}




TCoursewareItem& TCoursewareItem::operator=(const TiXmlElement* right)
{
    TBrowserItem::operator=(right);
    
    const CHAR* pStr = NULL;
    
    pStr = right->Attribute("setid");
    
	if(pStr)
	{
		utf8ncpy(sSetID,pStr,63);
		sSetID[63] = '\0';
	}
	else
		sSetID[0] = '\0';
    
    int ret=0;
    right->QueryIntAttribute("islearned", &ret);

    if(ret==1)
        bIsLearned=TRUE;
    else
        bIsLearned=FALSE;
    
    pStr = NULL;
    
    pStr = right->Attribute("zipurl");
    
    
//    snprintf(sDownloadUrl, 299, "http://192.168.0.140:8888/testzip.zip");

	if(pStr)
	{
		utf8ncpy(sDownloadUrl,pStr,299);
	}
	else
		sDownloadUrl[0] = '\0';
    
    
    pStr = right->Attribute("orientation");
    if (pStr) {
        utf8ncpy(sOrientation, pStr, 9);
    }
    
    if(strcmp(sType, "text/html") == 0)
        bDecompressed = FALSE;
    else
        bDecompressed = TRUE;
    
    return *this;
}


TCoursewareItem::TCoursewareItem():TBrowserItem()
{
    nCheckStatus=0;
    memset(sSetID, 0, 64);
    
    memset(sDownloadUrl, 0, 300);
    
    bIsLearned = FALSE;
    
    bDecompressed = FALSE;
    
    memset(sEntryFilePath, 0, 300);
    
    memset(sLocalFilePath, 0, 300);
    
    memset(sOrientation, 0, 10);

}

TCoursewareItem::~TCoursewareItem()
{

}

void TCoursewareItem::SetListener(IMUpdateDataListener* pUpdateDataListener,IMRatingListener* pRatingListener)
{
	m_pListener = pUpdateDataListener;
	m_pRatingListener = pRatingListener;
}


BOOL TCoursewareItem::DoComment(const char* sContent, BOOL bsyncqa)
{
    if(!sContent || !sID ||!sSetID ||!sFlag)
    {
        CM_ERR("send comment fail!");
		return FALSE;
    }
    if(strcmp(sFlag, "course")!=0)
        return FALSE;
    
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
    
    char sComment[1600];
    
    snprintf(sComment,1600,"flag=%s&id=%s&enablesyncqa=%d&cwid=%s",sFlag,sSetID,bsyncqa,sID);
    
    CMString sParam = sComment;
    
    CMList<FormData>* list= new CMList<FormData>;
    FormData data;
    data.key=CMString("content");
    data.value=sContent;
    data.dataType=1;
    list->push_back(data);
    
    m_pSession->CommandPost(SERVICE_MAKECOMMENT, sParam, *list);
    SAFEDELETE(list);
	return TRUE;
    
}

CMCourseInfo::CMCourseInfo()
:CMHandler<TCoursewareItem>()
,m_pRatingListener(NULL)
,m_nCurrentCourseware(0)
,m_bRatting(FALSE)
,m_nStatus(0)
{
    m_pClassItem = new TClassItem();

    memset(m_ClassTablename, 0, 64);
    snprintf(m_ClassTablename, 64,"tempclassinfo");
    
    memset(operatingID, 0, 64);
}

CMCourseInfo::~CMCourseInfo()
{
    SAFEDELETE(m_pClassItem);
}

CMCourseInfo::CMCourseInfo(const CMCourseInfo& other)
:CMHandler<TCoursewareItem>()
,m_pRatingListener(NULL)
,m_nCurrentCourseware(0)
,m_bRatting(FALSE)
,m_nStatus(0)
{
    m_pClassItem = new TClassItem();
    memset(m_ClassTablename, 0, 64);
    memset(operatingID, 0, 64);

	*this = other;
}

//void CMCourseInfo::RequestRelevantcourse()
//{
//}

void CMCourseInfo::SetListener(IMUpdateDataListener* pUpdateDataListener,IMRatingListener* pRatingListener)
{
	m_pListener = pUpdateDataListener;
	m_pRatingListener = pRatingListener;
}


BOOL CMCourseInfo::RatingCourseinfo(const char* CoursewareID)
{
    if(strlen(CoursewareID)==0)
        return FALSE;
    
	if(!m_pSession)
		m_pSession = new CMSession(this);
    
	if(m_pSession->IsRunning())
		return FALSE;
    
	char str[64];
	snprintf(str,64,"&id=%s",CoursewareID);
    utf8ncpy(operatingID, CoursewareID, 63);
    
	m_bRatting = TRUE;
    
    m_nServiceNo=SERVICE_RATINGCOURSEWARE;
    
	m_pSession->Command(SERVICE_RATINGCOURSEWARE,str);
	return TRUE;
}


BOOL CMCourseInfo::RequestCourseAndClass(const char* setid )
{

    if(!setid || strlen(setid)==0)
        return FALSE;
    
    //setid就是课程id(系列id)
    if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
    
	char str[64];
	snprintf(str,64,"&id=%s",setid);
    snprintf(m_tablename, 64,"coursewareall");//先不缓存
    utf8ncpy(operatingID, setid, 63);
    SetPaging(FALSE);
	m_bRatting = FALSE;
    m_nCacheDuration = 0;
    m_nServiceNo = SERVICE_GETCOURSEANDCLASS;
    
    return CMHandler<TCoursewareItem>::Request(SERVICE_GETCOURSEANDCLASS, str);
}

BOOL CMCourseInfo::GetClassItem(TClassItem& item)
{
	item = *m_pClassItem;
	return TRUE;
}

void CMCourseInfo::RequestCourseware(const char* sid)
{
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return;
	char str[64];
	snprintf(str,64,"&id=%s",sid);
    snprintf(m_tablename, 64,"coursewareall");
    SetPaging(FALSE);
	m_bRatting = FALSE;
    
    m_nServiceNo = SERVICE_GETCOURSEWARELIST;

    CMHandler<TCoursewareItem>::Request(SERVICE_GETCOURSEWARELIST, str);

}

void CMCourseInfo::SetUserData(void* UserData)
{
	m_UserData = UserData;
}
BOOL CMCourseInfo::Rating()
{
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
	char str[64];
	snprintf(str,64,"&id=%s",m_pClassItem->sID);
	m_bRatting = TRUE;
    
    utf8ncpy(m_tablename, "", 63);
    
	m_pSession->Command(SERVICE_RATING,str);
	return TRUE;
}
int CMCourseInfo::CoursewareCount() const
{
	if (m_lstItem)
	{
		return m_lstItem->size();
	}

	return 0;
}

BOOL CMCourseInfo::GetCourseware(int nIndex, TCoursewareItem& item) const
{
	if(!m_lstItem){
		return FALSE;

	}
	if(nIndex >= m_lstItem->size() || nIndex < 0){
		return FALSE;

	}
	item = m_lstItem->at(nIndex);
	return TRUE;
}

int CMCourseInfo::GetCurrentCoursewareIndex()
{
	return m_nCurrentCourseware;
}

int CMCourseInfo::GetCoursewareFlag(int nIndex)
{
	if (m_lstItem && nIndex >= 0 && nIndex < m_lstItem->size())
	{
		const TCoursewareItem& item = m_lstItem->at(nIndex);
		return item.nCheckStatus;
	}

	return -1;
}

void CMCourseInfo::SetCoursewareFlag(int nIndex, int nCheck)
{

	if (m_lstItem && nIndex >= 0 && nIndex < m_lstItem->size())
	{
		TCoursewareItem& item = m_lstItem->at(nIndex);
		item.nCheckStatus = nCheck;
	}
}

CMCourseInfo& CMCourseInfo::operator=(const CMCourseInfo& right)
{

    *m_pClassItem=*right.m_pClassItem;
    
	m_nStatus = right.m_nStatus;
	m_nCurrentCourseware = right.m_nCurrentCourseware;

	if(right.m_lstItem)
	{
		if(m_lstItem)
			m_lstItem->clear();
		else
			m_lstItem = new CMList<TCoursewareItem>;

        
		m_lstItem->append(*right.m_lstItem);
	}
	return *this;
}

CMCourseInfo& CMCourseInfo::operator=(const TBrowserItem& right)
{
	*((TClassItem*)m_pClassItem)=right;
	return *this;
}

CMCourseInfo& CMCourseInfo::operator=(const TiXmlElement* right)
{
	*((TClassItem*)m_pClassItem)=right;
	DoCoursewareItemList(right);
	return *this;
}

BOOL CMCourseInfo::operator==(const CMCourseInfo& right)
{
	if (strcmp(this->m_pClassItem->sID, right.m_pClassItem->sID) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

TiXmlElement* CMCourseInfo::CreateXmlElement()
{
    TBrowserItem *item = new TBrowserItem();
	TiXmlElement* pItem = item->CreateXmlElement();
    
	if(pItem && m_lstItem)
	{
		pItem->SetAttribute("currentcourseware", m_nCurrentCourseware);
		pItem->SetAttribute("status", m_nStatus);
		for(int i = 0;i < m_lstItem->size();i++)
		{
			TCoursewareItem& item = m_lstItem->at(i);
			TiXmlElement* pCoursewareItem = new TiXmlElement("item");
			pCoursewareItem->SetAttribute("id", item.sID);
			pCoursewareItem->SetAttribute("title", item.sTitle);
			pCoursewareItem->SetAttribute("type", item.sType);	
			pCoursewareItem->SetAttribute("url", item.sUrl);
			pCoursewareItem->SetAttribute("status", item.nCheckStatus);
			pItem->LinkEndChild(pCoursewareItem);
		}
	}
	return pItem;
}


void CMCourseInfo::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;
	if (nCode == MER_OK)
	{
		ASSERT(pDoc);
		TiXmlElement *pItem = pDoc->RootElement();

		INT32 nErr = 0;
		INT32 nCmdID = 0;
		pItem->QueryIntAttribute("no", &nCmdID);
		if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
		{
			if (nErr == 0)
			{
                if(nCmdID==SERVICE_GETCOURSEANDCLASS)
                {
                    //处理课程信息

                    if(pItem->NoChildren())
                    {
                        result = TResult::ENothing;
                        
                        if(m_pListener)
                            m_pListener->OnUpdateDataFinish(m_UserData, result);

                        return;
                    }

                    *((TClassItem*)m_pClassItem) = pItem->FirstChildElement("item");
                    
                    utf8ncpy(m_pClassItem->sFlag, "course", 63);
                    
                    SaveClassInfo(*m_pClassItem);
                    
                    pItem->QueryIntAttribute("currentcourseware", &m_nCurrentCourseware);
                    m_nCurrentCourseware--;
                    
                    if(m_nCurrentCourseware < 0)
                        m_nCurrentCourseware = 0;
                    
                    pItem->QueryIntAttribute("status", &m_nStatus);
                    
                    pItem=pItem->FirstChildElement("item");
                    
                    if(!pItem->NoChildren())
                    {
                        
                        if (!m_bPaging || m_nPageNo == 1)
                        {
                            Clear();
                        }
                        //更新缓存时间
                        UpdateCacheTime();
                        
                        sqlite3* db = CheckTable(m_tablename);
                        if(nCmdID==m_nServiceNo)
                        {
                            char* errorMsg;
                            
                            if (db != NULL && sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
                            {
                                CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
                            }
                            
                            pItem = pItem->FirstChildElement("item");
                      
                            m_mutex.Lock();
                            while(pItem)
                            {
                                
                                TCoursewareItem t;
                                
                                if (DoPutItem(pItem, db, t))
                                {
                                    m_lstItem->push_back(t);
                                }
                                
                                    pItem = pItem->NextSiblingElement("item");
                            
                            }
                            m_mutex.UnLock();
                            
                            if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
                            {
                                CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
                            }
                            
                            
                            if(GetItemCount() > 0)
                                result = TResult::ESuccess;
                            else
                                result = TResult::ENothing;
                        }
                    }
                    else
                        result=TResult::ENothing;

                }
				else if(nCmdID == SERVICE_GETCOURSEWARELIST)
				{
//                    *((TClassItem*)m_pClassItem) = pItem->FirstChildElement("item");
//
//                    utf8ncpy(m_pClassItem->sFlag, "course", 15);

                    pItem->QueryIntAttribute("currentcourseware", &m_nCurrentCourseware);
                    m_nCurrentCourseware--;
                    if(m_nCurrentCourseware < 0)
                        m_nCurrentCourseware = 0;
                    pItem->QueryIntAttribute("status", &m_nStatus);
                    
                    CMHandler<TCoursewareItem>::OnSessionCmd(nCmdID, nCode, pDoc);
                    return;
                    
				}
				else if(nCmdID == SERVICE_RATING)
				{					
                    INT32 nRatting = 0;
					pItem->QueryIntAttribute("rating", &nRatting);
                    m_pRatingListener->OnRating(m_UserData,nRatting,TResult::ESuccess);
                    
					return;
				}
                else if(nCmdID == SERVICE_RATINGCOURSEWARE)
                {
                    
                    INT32 nRatting = 0;
                    pItem->QueryIntAttribute("rating", &nRatting);
                    
                    //要修改
                    TCoursewareItem item;
                    
                    utf8ncpy(item.sID, operatingID, 63);
                    
                    Refresh(item);
                    //     CM_ERRP("ready update %s . title: %s  \n", item->sID,item->sTitle);
                    
                    if(!item.bIsRated)
                    {
                        item.bIsRated=TRUE;
                        item.nPV +=1;
                        Update(item);
                    }
                    
                    if(m_pRatingListener)
                        m_pRatingListener->OnRating(m_UserData,nRatting,TResult::ESuccess);
                    return;

                }
				else
					result = TResult::EProtocolFormatError;
			}
			else if(nErr == -14 && nCmdID == SERVICE_RATING)
            {
//                TCoursewareItem item;
//                memset(&item, 0, sizeof(item));
//                utf8ncpy(item.sID, this->sID, 63);
//                Refresh(item);
                
				result = TResult::EDuplicaterating;
            }
            else if(nErr == -17 && nCmdID == SERVICE_GETCOURSEANDCLASS)
            {
                result = TResult::ENoPowerCourse;
            }
			else
				result = TResult::EUnknownError;
		}
		else
			result = TResult::EProtocolFormatError;		
	}
	else if(nCode == MERN_INITIALIZE)
	{
		result = TResult::ENetDisconnect;
	}
	else if(nCode==MERN_OFFLINE)
    {
        result=TResult::ENotSupportOffline;
    }
    else
		result = TResult::ENetTimeout;
    
	if(m_bRatting)
	{
		m_pRatingListener->OnRating(m_UserData,0,result);
	}
	else
	{
		if(m_pListener)
			m_pListener->OnUpdateDataFinish(m_UserData, result);
	}
}

void CMCourseInfo::DoCoursewareItemList(const TiXmlElement* pItemList)
{
	if(!pItemList)
		return;

	if(m_lstItem)
		m_lstItem->clear();
	else
		m_lstItem = new CMList<TCoursewareItem>;

	pItemList->QueryIntAttribute("currentcourseware", &m_nCurrentCourseware);
	m_nCurrentCourseware--;
	if(m_nCurrentCourseware < 0)
		m_nCurrentCourseware = 0;
	pItemList->QueryIntAttribute("status", &m_nStatus);

	const TiXmlElement* pItem = pItemList->FirstChildElement("item");
	const CHAR* pStr = NULL;
	TCoursewareItem bItem;
	while(pItem)
	{

		pStr = pItem->Attribute("id");
		if(pStr)
            utf8ncpy(bItem.sID, pStr, 63);

		pStr = pItem->Attribute("title");
		if(pStr)
            utf8ncpy(bItem.sTitle, pStr, 99);
        
        utf8ncpy(bItem.sFlag, "course", 15);
        
		pStr = pItem->Attribute("type");
		if(pStr)
            utf8ncpy(bItem.sType, pStr, 63);

		pStr = pItem->Attribute("url");
		if(pStr)
            utf8ncpy(bItem.sUrl, pStr, 299);


		int nCheckStatus = 1; //默认选中
		if (NULL == pItem->Attribute("status", &nCheckStatus))
		{
			bItem.nCheckStatus = 1;
		}
		else
		{
			bItem.nCheckStatus = nCheckStatus;
		}

		if(m_lstItem)
			m_lstItem->push_back(bItem);

		pItem = pItem->NextSiblingElement("item");
	}	
}
BOOL CMCourseInfo::GetClassInfo(TClassItem& item,const char* SID)
{
    sqlite3* db = CheckTable();

    return CMContenthandler::DoGetTBrowseitem(db, SID, item);
    
}


BOOL CMCourseInfo::SaveClassInfo(TClassItem& item)
{

    sqlite3* db = CheckTable();
    
    return CMContenthandler::DoSaveTBrowseitem(db, item);

}

//网络回来数据，要入缓存并刷新对象
BOOL CMCourseInfo::DoPutItem(TiXmlElement* pItem, sqlite3* db, TCoursewareItem& item)
{
    
    if(pItem == NULL)
        return FALSE;
    
    item = pItem;//xml解析
    

    if(strlen(m_pClassItem->sID)!=0)
        utf8ncpy(item.sSetID, m_pClassItem->sID, 63);
    
    item.nModel=1;
    
    int nCheckStatus = 1; //默认选中
    if (NULL == pItem->Attribute("status", &nCheckStatus))
    {
        item.nCheckStatus = 1;
    }
    else
    {
        item.nCheckStatus = nCheckStatus;
    }

    BOOL ret = FALSE;

	CHAR sql[2048];
	sqlite3_stmt *stmt;
    snprintf(sql, 2048,"REPLACE INTO %s(id,status,browseid) VALUES (?,?,?)", m_tablename);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        CMHandler<TCoursewareItem>::BindParam(stmt, 1, item.sID);
        CMHandler<TCoursewareItem>::BindParam(stmt, 2, item.nCheckStatus);
        CMHandler<TCoursewareItem>::BindParam(stmt, 3, m_pClassItem->sID);

        
        if(sqlite3_step(stmt) == SQLITE_DONE)
        {
        	ret = TRUE;
        }
        else
        {
        	CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
        }
        
        sqlite3_finalize(stmt);
    }
    else {
    	CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
    }
    
    memset(sql, 0, 2048);
    stmt = NULL;

	snprintf(sql, 2048,"REPLACE INTO %s(id,flag,title,brief,largeimage,image,thumb,type,coursewarecount,url,pubdate,vc,pv,commentcount,enablecomment,enabledownload,enablerating,description,tag,specialtopic,credit,studyduration,studyprogress,laststudydate,favoritedate,mycompany,israted,markid,marktitle,model,setid,islearned,downloadurl,markpicurl,orientation) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)", kCourseTable);
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        
        
    	CMHandler<TCoursewareItem>::BindParam(stmt, 1,  item.sID);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 2,  item.sFlag);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 3,  item.sTitle);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 4,  item.sBrief);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 5,  item.sLargeimage);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 6,  item.sImage);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 7,  item.sThumbs);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 8,  item.sType);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 9,  item.nCoursewarecount);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 10, item.sUrl);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 11, item.sPubdate);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 12, item.nVC);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 13, item.nPV);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 14, item.nCommentcount);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 15, item.bEnablecomment);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 16, item.bEnabledownload);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 17, item.bEnablerating);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 18, item.sDescription);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 19, item.sTag);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 25, item.sFavoritedate);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 26, item.bMyCompany);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 27, item.bIsRated);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 28, item.sMarkID);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 29, item.sMarkTitle);
    	CMHandler<TCoursewareItem>::BindParam(stmt, 30, item.nModel);
        
    	CMHandler<TCoursewareItem>::BindParam(stmt, 31, item.sSetID);
        
    	CMHandler<TCoursewareItem>::BindParam(stmt, 32, item.bIsLearned);

    	CMHandler<TCoursewareItem>::BindParam(stmt, 33, item.sDownloadUrl);
        
        CMHandler<TCoursewareItem>::BindParam(stmt, 34, item.sMarkPicUrl);

        CMHandler<TCoursewareItem>::BindParam(stmt, 35, item.sOrientation);

        
        if(sqlite3_step(stmt) == SQLITE_DONE)
        {
        	ret = TRUE;
        }
        else
        {
        	CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
        }
        
        sqlite3_finalize(stmt);
    }
    else {
    	CM_ERRP("exec %s failed.error:%s", sql, sqlite3_errmsg(db));
    }
    
    return  TRUE;
}

//缓存回来数据，读取缓存到对象列表
BOOL CMCourseInfo::DoGetCacheItems(sqlite3* db)
{
    
    if(m_nServiceNo == SERVICE_GETCOURSEANDCLASS)
    {
        if(!GetClassInfo(*m_pClassItem, operatingID))
            return FALSE;
    }
    
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
	
//    sprintf(sql, "SELECT * FROM %s WHERE browseid = ?  ORDER BY _id ASC ", m_tablename);
    snprintf(sql,1024,"SELECT main.*,  sub.status , sub.browseid   FROM %s AS sub  LEFT JOIN %s AS main ON sub.id = main.id WHERE sub.browseid = ? ",m_tablename,kCourseTable);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
        
        CMHandler<TCoursewareItem>::BindParam(stmt, 1, m_pClassItem->sID);
        
        //无分页
        m_mutex.Lock();
        m_lstItem->clear();
        m_mutex.UnLock();

        m_mutex.Lock();
        while(sqlite3_step(stmt) == SQLITE_ROW)
        {
        	TCoursewareItem item;
            
            item.fetchItem(stmt);
            
            item.nCheckStatus=sqlite3_column_int(stmt,kDbColumnIndex+1);
            
        	m_lstItem->push_back(item);
            
            ret = TRUE;

        }
        m_nTotalCount = m_lstItem->size();
        m_mutex.UnLock();
        
        sqlite3_finalize(stmt);
        
	}
    
	return ret;

}

BOOL CMCourseInfo::DoRefresh(TCoursewareItem& obj)
{
    //根据obj的sID属性更新
	BOOL ret = FALSE;
	sqlite3_stmt *stmt;
	CHAR sql[1024];
	sql[0] = '\0';
    
	sqlite3*db=CheckTable(m_tablename);
	if (db == NULL)
		return FALSE;
    
	snprintf(sql, 1024,"SELECT * FROM %s WHERE id = ?", m_tablename);
    
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK)
	{
		CMHandler<TCoursewareItem>::BindParam(stmt, 1, obj.sID);
        
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            
			utf8ncpy(obj.sID, (const char*)sqlite3_column_text(stmt, 1), 63);
            
		
			obj.nCheckStatus=sqlite3_column_int(stmt, 2);

                        
			m_mutex.Lock();
			for (int i = 0; i < m_lstItem->size(); i++) {
				TCoursewareItem& item = m_lstItem->at(i);
                
				if (strcmp(item.sID, obj.sID) == 0) {
					item = obj;
					ret = TRUE;
					CM_ERRP("DoRefresh %s success", item.sID);
					break;
				}
			}
			m_mutex.UnLock();
        }
        else
        {
        	CM_ERRP("sqlite3_prepare_v2 %s failed.error:%s", sql, sqlite3_errmsg(db));
        }
        
        sqlite3_finalize(stmt);
	}
	else
	{
		CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
	}
    
    
	return ret;

}




BOOL CMCourseInfo::DoUpdate(const TCoursewareItem& obj)
{
    BOOL ret = FALSE;
    //保存入数据库
    sqlite3*db=CheckTable(m_tablename);
    if(db)
    {
		sqlite3_stmt *stmt;
		CHAR sql[512];
		snprintf(sql, 512,"REPLACE %s SET id=?, status=? WHERE id=? ", m_tablename);
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            CMHandler<TCoursewareItem>::BindParam(stmt, 1, obj.sID);

            CMHandler<TCoursewareItem>::BindParam(stmt, 2, obj.nCheckStatus);

     
            if(sqlite3_step(stmt)==SQLITE_DONE)
            {
            	//更新对象
            	m_mutex.Lock();
        		for (int i = 0; i < m_lstItem->size(); i++) {
        			TCoursewareItem& item = m_lstItem->at(i);
                    
        			if (strcmp(item.sID, obj.sID) == 0) {
        				item = obj;
        				ret = TRUE;
        				CM_ERRP("DoUpdate %s success", item.sID);
        				break;
        			}
        		}
        		m_mutex.UnLock();
            }
            else {
            	CM_ERRP("sqlite3_step %s failed.error:%s", sql, sqlite3_errmsg(db));
            }
        }
        else {
        	CM_ERRP("prepare %s failed.error:%s", sql, sqlite3_errmsg(db));
        }
        
        sqlite3_finalize(stmt);
    }
    
    return ret;
}

BOOL CMCourseInfo::DoCreate(sqlite3* db)
{
    
    BOOL ret= FALSE;
    char *errorMsg = NULL;
	char sql[1024];
	snprintf(sql, 1024,"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT UNIQUE,status INTEGER,browseid TEXT)", m_tablename);
    
    
	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
		ret= TRUE ;
	}
	else
	{
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		ret =FALSE;
	}
    
        return ret;
}


void CMCourseInfo::DoClear()
{
    //do nothing on db
    m_mutex.Lock();
    m_lstItem->clear();
    m_mutex.UnLock();
    
}

int CMCourseInfo::HaveCourseware(const TCoursewareItem& item)
{
    int ret = -1;
	for (int i = 0; i < GetItemCount(); i++)
	{
		TCoursewareItem citem;
		if (GetItem(i, citem))
		{
			if (strcmp(item.sID, citem.sID) == 0 && strcmp(item.sTitle, citem.sTitle) == 0 )
			{
				ret = i;
				break;
			}
		}
	}
    
    return ret;
}







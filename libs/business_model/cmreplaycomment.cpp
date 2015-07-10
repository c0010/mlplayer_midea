#include "stdafx.h"
#include "cmreplaycomment.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "cmglobal.h"
#include "utf8ncpy.h"
#include "cmsettings.h"

CMRepalycomment::CMRepalycomment(IMUpdateDataListener* pUpdateDataListener,IMSimpleResultListener* pSimpleResultListener)
:m_pUpdateDataListener(pUpdateDataListener)
,m_pSimpleResultListener(pSimpleResultListener)
,m_UserData(NULL)
,m_lstItem(NULL)
,m_pSession(NULL)
,m_nPageNo(0)
,m_nPageSize(30)
,m_nPageCount(0)
,m_nCmdId(0)
{
    memset(ratingReplyID, 0, 64);
}
CMRepalycomment::~CMRepalycomment()
{
	if(m_lstItem)
	{
		m_lstItem->clear();
		SAFEDELETE(m_lstItem);
	}
	SAFEDELETE(m_pSession);
}

void CMRepalycomment::SetUserData(void* UserData)
{
	m_UserData = UserData;
}
void CMRepalycomment::MakeTempItem(const char* sFlag,const char* sID,const char* sReplyID,const char* sContent,TRepalymentItem &item)
{
//    utf8ncpy(item.sID, sReplyID, 63);

    utf8ncpy(item.sUsername,CMSettings::GetInstance()->GetUserName(), 31);

    utf8ncpy(item.sFullName, CMMyInfo::GetInstance()->GetFullName(), 31);

    
    utf8ncpy(item.sHeadImage, CMMyInfo::GetInstance()->GetHeadimage(), 299);
    utf8ncpy(item.sDepartment, CMMyInfo::GetInstance()->GetDep(), 99);

    utf8ncpy(item.sDatetime, "", 19);

    //utf8ncpy(item.sComment, sContent, 699);

    item.sComment = sContent;
    
    item.nreply=0;
    
//    item.nStatus=1;
}


BOOL CMRepalycomment::ReplyComment(const char* sFlag,const char* ClassID,const char* CoursewareID, const char* sReplyID,const char* sContent)
{
	if(!sFlag || !ClassID || !sReplyID || !sContent)
		return FALSE;
	
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
     const CHAR* pContent =  CMGlobal::TheOne().Encode(sContent);
     char sComment[4000];
    
    
    if(!CoursewareID || strlen(CoursewareID)==0)
        snprintf(sComment,sizeof(sComment),"flag=%s&id=%s&replyid=%s",sFlag,ClassID,sReplyID);
    else
        snprintf(sComment,sizeof(sComment),"flag=%s&id=%s&replyid=%s&cwid=%s",sFlag,ClassID,sReplyID,CoursewareID);
	SAFEDELETE(pContent);
	CMString sParam = sComment;
	m_nCmdId = SERVICE_REPLYCOMMENT;
    

//    TRepalymentItem item;
//
//    MakeTempItem(sFlag,ClassID,sReplyID,sContent,item);
//
//    if(!m_lstItem)
//        m_lstItem=new CMList<TRepalymentItem>;
//
//    m_lstItem->push_front(item);
    
    
    
    CMList<FormData>* list= new CMList<FormData>;
    FormData data;
    data.key=CMString("content");
    data.value=sContent;
    data.dataType=1;
    list->push_back(data);
    
    m_pSession->CommandPost(SERVICE_REPLYCOMMENT, sParam, *list);
    SAFEDELETE(list);

    return TRUE;
}


BOOL CMRepalycomment::RequestRepalyCommentList(const char* sFlag, const char* sID)
{
	if(!sFlag || !sID)
		return FALSE;
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
    
	snprintf(m_sReqComment,sizeof(m_sReqComment),"flag=%s&id=%s",sFlag,sID);
	m_nPageNo = 1;
      m_nPageCount = 0;
	  		
	return CurrentRepalyComment(m_sReqComment, 1, m_nPageSize);
}

BOOL CMRepalycomment::RequestMore()
{
	if(m_nPageCount <= 1)
		return FALSE;
	if(m_pSession->IsRunning())
		return FALSE;
	if(m_nPageNo < m_nPageCount)	
	{
		int count = m_nPageNo + 1;
        return CurrentRepalyComment(m_sReqComment,count,m_nPageSize);
	}
	return FALSE;
}

int  CMRepalycomment::GetItemCount()
{
	if(m_lstItem)
	{
		return m_lstItem->size();	
	}
	return 0;
}

BOOL  CMRepalycomment::GetItem(int nIndex, TRepalymentItem& item)
{
	if(!m_lstItem)
		return FALSE;
	if(nIndex >= m_lstItem->size() || nIndex < 0)
		return FALSE;
	item = m_lstItem->at(nIndex);
	return TRUE;
}


void CMRepalycomment::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}
BOOL CMRepalycomment::CurrentRepalyComment(const char* param,int pageno,int pagesize)
{
	char smid[200];
	snprintf(smid,sizeof(smid),"%s&pageno=%d&pagesize=%d",param,pageno,pagesize);
	CMString sParam = smid;
	m_nCmdId = SERVICE_GETCOMMENTREPLAY;
	if(m_pSession)
		
		m_pSession->Command(SERVICE_GETCOMMENTREPLAY,sParam);
	return TRUE;
}
void CMRepalycomment::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
	INT32 result = TResult::EUnknownError;
	if (nCode == MER_OK)
	{
	      
		ASSERT(pDoc);
		TiXmlElement *pItem = pDoc->RootElement();
		INT32 nErr = 0;
		INT32 nCmdID = 0;
		pItem->QueryIntAttribute("no", &nCmdID);
//		CM_ERRP("DoRefresh %d success", nCmdID);
		if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
		{
			if (nErr == 0)
			{	
					if(nCmdID == SERVICE_GETCOMMENTREPLAY)
					{
						INT32 nCount = 0;
						INT32 nTotal = 0;
						pItem->QueryIntAttribute("count", &nCount);
						pItem->QueryIntAttribute("totalcount", &nTotal);
						pItem->QueryIntAttribute("pageno", &m_nPageNo);
						if(nCount != 0 && nTotal != 0)
						{
							if(nTotal%30 > 0)
								m_nPageCount = nTotal/30 +1;
							else
								m_nPageCount = nTotal/30;
						}
                        
                        if(m_nPageNo==1)
                            if(m_lstItem)
                                m_lstItem->clear();
						if(!pItem->NoChildren())
						{
							if(!m_lstItem)
								m_lstItem = new CMList<TRepalymentItem>;
							pItem = pItem->FirstChildElement("item");
							const CHAR* pStr = NULL;
							TRepalymentItem bItem;
							while(pItem)
							{
								pStr = pItem->Attribute("username");
								if(pStr)
									utf8ncpy(bItem.sUsername,pStr,31);
								pStr = pItem->Attribute("fullname");
								if(pStr)
									utf8ncpy(bItem.sFullName,pStr,31);
								if(strlen(bItem.sFullName) <= 0)
                                    utf8ncpy(bItem.sFullName, bItem.sUsername, 31);
                                
								pStr = pItem->Attribute("headimage");
								if(pStr)
									utf8ncpy(bItem.sHeadImage,pStr,299);
								pStr = pItem->Attribute("department");
								if(pStr)
									utf8ncpy(bItem.sDepartment,pStr,99);
								pStr = pItem->Attribute("datetime");
					
								if(pStr)
									utf8ncpy(bItem.sDatetime,pStr,19);
								pStr = pItem->Attribute("comment");
								if(pStr)
									bItem.sComment = pStr;
								pStr = pItem->Attribute("id");
								if(pStr)
									utf8ncpy(bItem.sID,pStr,63);
								pItem->QueryIntAttribute("reply",&bItem.nreply);

								m_lstItem->push_back(bItem);
                                
								pItem = pItem->NextSiblingElement("item");
							}
						}
						if(m_lstItem && m_lstItem->size() > 0)
							result = TResult::ESuccess;
						else
							result = TResult::ENothing;
					}
				else if( nCmdID == SERVICE_REPLYCOMMENT)
					{
						result = TResult::ESuccess;
//                        if(!m_lstItem)
//                            return;
//
//
//                        TRepalymentItem *item=&m_lstItem->at(0);
//                        if(item)
//                            item->nStatus=0;
//
//
                        
                        if(m_pSimpleResultListener)
                            m_pSimpleResultListener->OnRequestFinish(m_UserData, result);
                        
                        return;
					}
					else
						result = TResult::EProtocolFormatError;
			}
			else
				result = nErr;
		}
		else
			result = TResult::EProtocolFormatError;			
	}
	else if(nCode == MERN_INITIALIZE)
		result = TResult::ENetDisconnect;
	else if(nCode == MERN_OFFLINE)
		result = TResult::ENotSupportOffline;
	else
		result = TResult::ENetTimeout;
	
	if(m_nCmdId == SERVICE_GETCOMMENTREPLAY)
	{
		if(m_pUpdateDataListener)
			m_pUpdateDataListener->OnUpdateDataFinish(m_UserData, result);
	}
	else if( m_nCmdId == SERVICE_REPLYCOMMENT)
	{

//        TRepalymentItem *item=&m_lstItem->at(0);
//        if(item)
//            item->nStatus=2;
        
		if(m_pSimpleResultListener)
			m_pSimpleResultListener->OnRequestFinish(m_UserData, result);
	}
}

BOOL  CMRepalycomment::IsEnd()
{
	return m_nPageNo >= m_nPageCount;	
}


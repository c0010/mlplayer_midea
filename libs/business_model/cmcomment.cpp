// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmcomment.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "cmglobal.h"
#include "utf8ncpy.h"
#include <string>

TCommentItem& TCommentItem::operator=(const TCommentItem& right)
{
    if(right.m_lstChildItem)
    {
        if(m_lstChildItem)
			DoClear();
		else
			m_lstChildItem = new CMList<TCommentItem*>;


		for (int i = 0; i < right.m_lstChildItem->size(); i++)
		{
            TCommentItem* item=new TCommentItem();
            *item=*right.m_lstChildItem->at(i);
			m_lstChildItem->push_back(item);

//            m_lstChildItem->push_back(right.m_lstChildItem->at(i));


		}
    }
    else
    {
        if (m_lstChildItem) {
            DoClear();
            delete m_lstChildItem;
            m_lstChildItem = NULL;
        }
    }
    utf8ncpy(sUsername , right.sUsername,31);
	sUsername[31] = '\0';

    utf8ncpy(sFullName, right.sFullName,31);
    sFullName[31] = '\0';

    utf8ncpy(sHeadImage, right.sHeadImage,299);
    sHeadImage[299] = '\0';

    utf8ncpy(sDepartment, right.sDepartment,99);
    sDepartment[99] = '\0';

    utf8ncpy(sDatetime, right.sDatetime,19);
    sDatetime[19] = '\0';

    /*utf8ncpy(sComment, right.sComment,699);
    sComment[699] = '\0';*/
    sComment = right.sComment;

    utf8ncpy(sID, right.sID,63);
    sID[63] = '\0';

    npv=right.npv;

    nreply=right.nreply;

    bIsLiked=right.bIsLiked;

	return *this;
}
void TCommentItem::DoClear()
{
    if(!m_lstChildItem)
        return;

    for(int i = 0; i < m_lstChildItem->size(); i++)
    {
        TCommentItem* ptr = m_lstChildItem->at(i);
        SAFEDELETE(ptr);
    }

    m_lstChildItem->clear();
}

TCommentItem::TCommentItem()
{
    memset(sUsername, 0, 32);

    memset(sFullName, 0, 32);

    memset(sHeadImage, 0, 300);


    memset(sDepartment, 0, 100);

    memset(sDatetime, 0, 20);

    //memset(sComment, 0, 699);
    sComment = "";

    memset(sID, 0, 64);

    npv=0;

    nreply=0;

    bIsLiked=FALSE;

    m_lstChildItem=NULL;
}

TCommentItem::~TCommentItem()
{
    if(!m_lstChildItem)
        return;
    for (int i = 0; i < m_lstChildItem->size(); i++)
    {
        TCommentItem* ptr = m_lstChildItem->at(i);
        if(ptr)
        {
            delete ptr;
            ptr = NULL;
        }
    }
    m_lstChildItem->clear();
    SAFEDELETE(m_lstChildItem);
}

BOOL TCommentItem::GetChildItem(int index, TCommentItem& item)
{

    if(!m_lstChildItem)
        return FALSE;

    if(index < m_lstChildItem->size() && index >= 0)
    {
        item=*m_lstChildItem->at(index);
        return TRUE;
    }
    else
        return FALSE;

}

int TCommentItem::GetChildItemCount()
{
    if(!m_lstChildItem)
        return 0;
    else
        return m_lstChildItem->size();
}



//////////////////////////////////////////////////////////////////

CMComment::CMComment()
:CMHandler<TCommentItem>(){
	SetPaging(TRUE);
    memset(ratingReplyID, 0, 64);
}


CMComment::~CMComment()
{
	if(m_lstItem)
	{
		m_lstItem->clear();
		SAFEDELETE(m_lstItem);
	}
	SAFEDELETE(m_pSession);
}

void CMComment::setListener(IMUpdateDataListener* pUpdateDataListener, IMSimpleResultListener* pSimpleResultListener,IMRatingListener* pRatingListener)
{
	m_pSimpleResultListener = pSimpleResultListener;
	m_pRatingListener = pRatingListener;
	m_pListener = pUpdateDataListener;
}


//void CMComment::SetUserData(void* UserData)
//{
//	m_UserData = UserData;
//}

BOOL CMComment::RequestBriefComment(const char* sFlag, const char* ClassID, const char* CoursewareID)
{
	if(!sFlag || !ClassID )
		return FALSE;

	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;

    //	if(m_lstItem)
    //		m_lstItem->clear();

    if(!CoursewareID || strlen(CoursewareID)==0)
        snprintf(m_sReqComment,500,"flag=%s&id=%s",sFlag,ClassID);
    else
        snprintf(m_sReqComment,500,"flag=%s&id=%s&cwid=%s",sFlag,ClassID,CoursewareID);


//	m_nPageNo = 1;
//    m_nPageCount = 0;
    //只要2�?

    return Request(SERVICE_GETCOMMENT, m_sReqComment);

//	return CurrentComment(m_sReqComment, 1, 2);
}

BOOL CMComment::RequestCommentList(const char* sFlag, const char* ClassID, const char* CoursewareID)
{
	if(!sFlag || !ClassID)
		return FALSE;
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;

//	if(m_lstItem)
//		m_lstItem->clear();

    if (!CoursewareID ||strlen(CoursewareID)==0)
        snprintf(m_sReqComment,500,"flag=%s&id=%s",sFlag,ClassID);
    else
        snprintf(m_sReqComment,500,"flag=%s&id=%s&cwid=%s",sFlag,ClassID,CoursewareID);

//	m_nPageNo = 0;
//    m_nPageCount = 0;

    return Request(SERVICE_GETCOMMENT, m_sReqComment);
//	return CurrentComment(m_sReqComment, 1, m_nPageSize);
}

//BOOL CMComment::RequestMore()
//{
//	if(m_nPageCount <= 1)
//		return FALSE;
//	if(m_pSession->IsRunning())
//		return FALSE;
//	if(m_nPageNo < m_nPageCount)
//	{
//		int count = m_nPageNo + 1;
//        return CurrentComment(m_sReqComment,count,m_nPageSize);
//	}
//	return FALSE;
//}

//int CMComment::GetItemCount()
//{
//	if(m_lstItem)
//	{
//		return m_lstItem->size();
//	}
//	return 0;
//}

//BOOL CMComment::GetItem(int nIndex, TCommentItem& item)
//{
//	if(!m_lstItem)
//		return FALSE;
//	if(nIndex >= m_lstItem->size() || nIndex < 0)
//		return FALSE;
//	item = m_lstItem->at(nIndex);
//	return TRUE;
//}





BOOL CMComment::SendComment(const char* sFlag, const char* ClassID,  const char* CoursewareID,const char* sContent, BOOL bsyncqa)
{
	if(!sFlag || !ClassID || !sContent)
		return FALSE;
	if(!m_pSession)
		m_pSession = new CMSession(this);
	if(m_pSession->IsRunning())
		return FALSE;
    char sComment[1600];

    if(!CoursewareID || strlen(CoursewareID)==0)
        snprintf(sComment,1600,"flag=%s&id=%s&enablesyncqa=%d",sFlag,ClassID,bsyncqa);
    else
        snprintf(sComment,1600,"flag=%s&id=%s&enablesyncqa=%d&cwid=%s",sFlag,ClassID,bsyncqa,CoursewareID);


	CMString sParam = sComment;
	m_nCmdId = SERVICE_MAKECOMMENT;

    //post传输内容
    CMList<FormData>* list= new CMList<FormData>;
    FormData data;
    data.key="content";
    data.value=sContent;
    data.dataType=1;
    list->push_back(data);

    m_pSession->CommandPost(SERVICE_MAKECOMMENT, sParam, *list);
    SAFEDELETE(list);
	return TRUE;
}


BOOL CMComment::CommentLike(const char* sFlag,const char* ClassID,const char* CoursewareID ,const char* sReplyID)
{
	if(!m_pSession)
		m_pSession = new CMSession(this);

	if(m_pSession->IsRunning())
		return FALSE;

	char sParam[200];

    if(!CoursewareID || strlen(CoursewareID)==0)
        snprintf(sParam,200,"flag=%s&id=%s&replyid=%s",sFlag,ClassID,sReplyID);
    else
        snprintf(sParam,200,"flag=%s&id=%s&replyid=%s&cwid=%s",sFlag,ClassID,sReplyID,CoursewareID);

    utf8ncpy(ratingReplyID, sReplyID, 63);
    ratingReplyID[63]='\0';

	m_nCmdId = SERVICE_LIKECOMMENT;

	m_pSession->Command(SERVICE_LIKECOMMENT,sParam);
	return TRUE;
}

//void CMComment::CMComment::Cancel()
//{
//	if(m_pSession)
//		m_pSession->Cancel();
//}
//BOOL CMComment::CurrentComment(const char* param,int pageno,int pagesize)
//{
//	char smid[200];
//	snprintf(smid,200,"%s&pageno=%d&pagesize=%d",param,pageno,pagesize);
//	CMString sParam = smid;
//	m_nCmdId = SERVICE_GETCOMMENT;
//	if(m_pSession)
//		m_pSession->Command(SERVICE_GETCOMMENT,sParam);
//	return TRUE;
//}

void CMComment::DoItem(TCommentItem& bItem,TiXmlElement* pItem )
{
    const CHAR* pStr = NULL;

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
        //utf8ncpy(bItem.sComment,pStr,699);
    pStr = pItem->Attribute("id");
    if(pStr)
        utf8ncpy(bItem.sID,pStr,63);

    pItem->QueryIntAttribute("pv",&bItem.npv);

    pItem->QueryIntAttribute("reply",&bItem.nreply);

    int tmp = 0;
    pItem->QueryIntAttribute("isliked",&tmp);
    bItem.bIsLiked = tmp;

    //得到回复信息
    TiXmlElement *pChildItem= pItem->FirstChildElement("item");
    while (pChildItem) {
        TCommentItem *cItem= new TCommentItem();


        DoItem(*cItem ,pChildItem);
        if(bItem.m_lstChildItem==NULL)
        {
            bItem.m_lstChildItem = new CMList<TCommentItem*>;
        }
        bItem.m_lstChildItem->push_back(cItem);

        pChildItem=pChildItem->NextSiblingElement("item");
    }

}
void CMComment::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
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
					if(nCmdID == SERVICE_GETCOMMENT)
					{

//						CMHandler<TCommentItem>::OnSessionCmd(nCmdID, nCode, pDoc);

						if(m_bPaging)
						{
							pItem->QueryIntAttribute("totalcount", &m_nTotalCount);
							pItem->QueryIntAttribute("pageno", &m_nPageNo);
							int count = m_nTotalCount/m_nPageSize;
							if(m_nTotalCount%m_nPageSize > 0)
								count++;
							m_bEnd = (m_nPageNo >= count);
						}

						//清除以前缓存数据
						if (!m_bPaging || m_nPageNo == 1)
						{
							Clear();
						}

//						INT32 nCount = 0;
//						INT32 nTotal = 0;
//
//
//						pItem->QueryIntAttribute("count", &nCount);
//						pItem->QueryIntAttribute("totalcount", &nTotal);
//						pItem->QueryIntAttribute("pageno", &m_nPageNo);
//
//						if(nCount != 0 && nTotal != 0)
//						{
//							if(nTotal%30 > 0)
//								m_nPageCount = nTotal/30 +1;
//							else
//								m_nPageCount = nTotal/30;
//						}
//
//						m_bEnd = (m_nPageNo >= m_nPageCount);

//                        if(m_nPageNo==1)
//                            if(m_lstItem)
//                                m_lstItem->clear();


						if(!pItem->NoChildren())
						{
							if(!m_lstItem)
								m_lstItem = new CMList<TCommentItem>;
							pItem = pItem->FirstChildElement("item");

							while(pItem)
							{
                                TCommentItem *bItem= new TCommentItem();

                                DoItem(*bItem, pItem);

								m_lstItem->push_back(*bItem);
								pItem = pItem->NextSiblingElement("item");
							}
						}
						if(m_lstItem && m_lstItem->size() > 0)
							result = TResult::ESuccess;
						else
							result = TResult::ENothing;




					}
					else if(nCmdID == SERVICE_MAKECOMMENT || nCmdID == SERVICE_REPLYCOMMENT)
					{
						result = TResult::ESuccess;
					}
					else if(nCmdID == SERVICE_LIKECOMMENT)
					{
						INT32 npv = 0;
						pItem->QueryIntAttribute("pv", &npv);

                        if(m_lstItem)
                        {
                            for (int i = 0; i < m_lstItem->size(); i++) {
                                TCommentItem& item = m_lstItem->at(i);
                                if (strcmp(item.sID, ratingReplyID) == 0) {
                                    item.bIsLiked = TRUE;
                                    item.npv += 1;
                                    CM_ERRP("Like %s success ", item.sID);
                                    break;
                                }
                            }
                        }

						if(m_pRatingListener)
							m_pRatingListener->OnRating(m_UserData,npv,TResult::ESuccess);
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

	if(nCmdID == SERVICE_GETCOMMENT)
	{
		if(m_pListener)
			m_pListener->OnUpdateDataFinish(m_UserData,result);
	}
	else if(nCmdID == SERVICE_MAKECOMMENT || nCmdID == SERVICE_REPLYCOMMENT)
	{
		if(m_pSimpleResultListener)
			m_pSimpleResultListener->OnRequestFinish(m_UserData, result);
	}
	else if(nCmdID == SERVICE_LIKECOMMENT)
	{
		if(m_pRatingListener)
			m_pRatingListener->OnRating(m_UserData,0,result);
	}
}

int CMComment::GetTotalCount()
{
	return m_nTotalCount;
}

// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmgetnewcontent.h"
#include "cmsession.h"
#include "tinyxml.h"
#include "utf8ncpy.h"

#ifdef PLAT_WINCE
#include "cmfile.h"
#include "cmpath.h"

class CMNewContentListener:public IMUpdateDataListener
{
public:
	virtual void OnUpdateDataProgress(void* UserData, int nPercent){};

	virtual void OnUpdateDataFinish(void* UserData, int Result);

};

void CMNewContentListener::OnUpdateDataFinish(void* UserData, int Result)
{
	if(CMGetNewContent::GetInstance()->GetItemCount() > 0)
	{

		CMString sFilePath = CMPath(CMPath::APP_PATH).String() + L"newcontent.xml";
		//创建一个XML的文档对象。
		TiXmlDocument *pContentDoc = new TiXmlDocument(sFilePath);
		TiXmlElement* pRootElement = NULL;
		if(pContentDoc)
		{
			pContentDoc->Parse("<?xml version=\"1.0\" encoding=\"utf-8\" ?><content/>",NULL,TIXML_ENCODING_UTF8);
			if(pContentDoc->Error())
				return;
			pRootElement = pContentDoc->RootElement();
		}
		if(pRootElement)
		{
			TBrowserItem item;
			for(int i=0; i<CMGetNewContent::GetInstance()->GetItemCount(); i++)
			{
				if(CMGetNewContent::GetInstance()->GetItem(i,item))
				{
					TiXmlElement* pAddItem = item.CreateXmlElement();
					if(pAddItem)
					{
						TiXmlElement*pItem = pRootElement->FirstChildElement("item");
						if (pItem) {
							pRootElement->InsertBeforeChild(pItem, *pAddItem);
							SAFEDELETE(pAddItem);
						}
						else
							pRootElement->LinkEndChild(pAddItem);
					}
				}
			}
			pContentDoc->SaveFile();
		}
		SAFEDELETE(pContentDoc);

		/////////////////////////////////////////////////////
		HKEY	hOpenKey;
		long	lResult		= 0;
		LPCTSTR	keyName		= _T("Software\\Microsoft\\Today\\Items\\\"MLPlayer\"");		
		lResult = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyName, 0, 0, &hOpenKey);
		if(lResult != ERROR_SUCCESS)
			return;
		DWORD	iTemp = 1;
		lResult = ::RegSetValueEx(hOpenKey, _T("NewContent"),0, REG_DWORD, (BYTE*)&iTemp, sizeof(iTemp));
		::RegCloseKey(hOpenKey);
		if(lResult != ERROR_SUCCESS)
			return;
	}
}
#endif
///////////////////////////////////////////////////////////////
CMGetNewContent* CMGetNewContent::m_pTHIS = NULL;

CMGetNewContent* CMGetNewContent::GetInstance()
{
	if(m_pTHIS == NULL)
		m_pTHIS = new CMGetNewContent();
	return m_pTHIS;
}

CMGetNewContent::CMGetNewContent()
{
	m_isPush=FALSE;
	m_pListener=NULL;
	m_pSession = NULL;
    m_lstItem = new CMList<TNewContentItem*>;

#ifdef PLAT_WINCE
	SetListener(new CMNewContentListener());
#endif
}

CMGetNewContent::~CMGetNewContent()
{
#ifdef PLAT_WINCE
	SAFEDELETE(m_pListener);
#endif
    
    m_pSession->Cancel();
    SAFEDELETE(m_pSession);
    
    if (m_lstItem) {
        
		for(CMList<TNewContentItem*>::iterator i = m_lstItem->begin();i < m_lstItem->end();i++)
		{
			TNewContentItem* pItem = (TNewContentItem*)*i;
			SAFEDELETE(pItem);
		}
		m_lstItem->clear();
		
	}
    SAFEDELETE(m_lstItem);
}


void CMGetNewContent::SetListener(IMUpdateDataListener* pListener)
{
	m_pListener = pListener;
}


void CMGetNewContent::SetUserData(void *UserData)
{
    m_pUserData = UserData;
}


//请求数据
void CMGetNewContent::Update()
{
	//CMString sParam;
    //sprintf(m_tablename, "newscontent");
	//this->Request(SERVICE_GETNEWCONTENT,sParam);
    

    if (m_lstItem->size() > 0)
    {
        m_lstItem->clear();
    }
    
    char str[128];
    str[0] = '\0';

    
    if (m_pSession == NULL)
    {
        m_pSession = new CMSession(this);
    }
    
    if (m_pSession && !m_pSession->IsRunning())
    {
        m_pSession->Command(SERVICE_GETNEWCONTENT, str);
    }
}

void CMGetNewContent::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}

BOOL CMGetNewContent::IsRunning()
{
	if(m_pSession)
		return m_pSession->IsRunning();
	else
		return FALSE;
}

void CMGetNewContent::GetNewContent(const char* sID, const char* sType)
{
    
    if (m_lstItem->size() > 0)
    {
        m_lstItem->clear();
    }
    
    char str[128];
    snprintf(str,128,"&cmdtype=%s&cmdkeys=%s",sType,sID);
    
    if (m_pSession == NULL)
    {
        m_pSession = new CMSession(this);
    }
    
    if (m_pSession && !m_pSession->IsRunning())
    {
        m_pSession->Command(SERVICE_GETNEWCONTENT, str);
    }
}

BOOL CMGetNewContent::Load()
{
#ifdef PLAT_WINCE
	if(this->GetItemCount() > 0)
		return TRUE;

	BOOL bRet = FALSE;
	CMString sPath = CMPath(CMPath::APP_PATH).String() + L"newcontent.xml";
	TiXmlDocument *pDoc = new TiXmlDocument(sPath);
	if(!pDoc)
		return bRet;
	pDoc->LoadFile(TIXML_ENCODING_UTF8);
	if(!pDoc->Error())
	{
		if(m_lstItem)
			m_lstItem->clear();
		else
			m_lstItem = new CMList<TBrowserItem>;
		TiXmlElement *pRoot = pDoc->RootElement();
		if(pRoot)
		{
			this->DoItemList(pRoot);
			bRet = TRUE;					
		}

	}
	SAFEDELETE(pDoc);
    return bRet;
#endif
	return TRUE;
}


//网络返回数据 刷新内存
void CMGetNewContent::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument *pDoc)
{
    if (nCode == MER_OK)
    {
        TiXmlElement* pItem = pDoc->RootElement();
        
        if (pItem)
        {
            INT32 nCmdID = 0;
            
            pItem->QueryIntAttribute("no", &nCmdID);
            
            INT32 nErr = 0;
            
            if (pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
            {
                if (nErr == 0)
                {
                    if (nCmdID == SERVICE_GETNEWCONTENT)
                    {
                        pItem = pItem->FirstChildElement();
                        
                        const char* pstr = NULL;
                        
                        while (pItem)
                        {
                            TNewContentItem* newContentItem = new TNewContentItem;
                            memset(newContentItem, 0, sizeof(TNewContentItem));
                            
                            pstr = pItem->Attribute("tx_type");
                            if (pstr)
                            {
                                utf8ncpy(newContentItem->sType, pstr, 20);
                                CM_LOGP(CM_LOGL_DEBUG, "stype==%s",newContentItem->sType);
                            }
                            
                            pstr = pItem->Attribute("tx_title");
                            if (pstr)
                            {
                                utf8ncpy(newContentItem->sTitle, pstr, 100);
                            }
                            
                            pstr = pItem->Attribute("tx_desc");
                            if (pstr)
                            {
                                utf8ncpy(newContentItem->sDescription, pstr, 250);
                            }
                            
                            if (strcmp(newContentItem->sType, "course") == 0)
                            {
                                if (newContentItem->nModel == 0) {
                                    TClassItem* bItem = new TClassItem;
                                    *bItem = pItem;
                                    newContentItem->item = bItem;
                                }
                                else
                                {
                                    TCoursewareItem* bItem = new TCoursewareItem;
                                    *bItem = pItem;
                                    newContentItem->item = bItem;
                                }
                            }
                            else if (strcmp(newContentItem->sType, "news") == 0)
                            {
                                TBrowserItem* bItem = new TBrowserItem;
                                *bItem = pItem;
                                newContentItem->item = bItem;
                            }
                            else if (strcmp(newContentItem->sType, "exam") == 0)
                            {
                                
                            }
                            else if (strcmp(newContentItem->sType, "exercise") == 0)
                            {
                                TExerciseListItem* exerciseItem = new TExerciseListItem;
                                
                                pstr = pItem->Attribute("id");
                                if (!pstr)
                                {
                                    continue;
                                }
                                exerciseItem->sID = pstr;
                                
                                pstr = pItem->Attribute("title");
                                if (pstr)
                                {
                                    exerciseItem->sTitle = pstr;
                                }
                                
                                pItem->QueryIntAttribute("questioncount", &exerciseItem->nQuestioncount);
                                pItem->QueryIntAttribute("uncompletecount", &exerciseItem->nCompleteCount);
                                pstr = pItem->Attribute("desc");
                                if(pstr)
                                    exerciseItem->sDesc = pstr;
                                
                                pstr = pItem->Attribute("category");
                                if(pstr)
                                    exerciseItem->sCategory = pstr;
                                
                                pItem->QueryIntAttribute("usercompletecount", &exerciseItem->nUsercompletecount);
                                
                                pstr = pItem->Attribute("pubdate");
                                if(pstr)
                                    exerciseItem->sPubdate = pstr;
                                
                                newContentItem->item = exerciseItem;
                            }
                            else if (strcmp(newContentItem->sType, "survey") == 0)
                            {
                                TSurveyListItem* surveyItem = new TSurveyListItem;
                                memset(surveyItem, 0, sizeof(TSurveyListItem));
                                
                                pstr = pItem->Attribute("id");
                                if (!pstr)
                                {
                                    continue;
                                }
                                utf8ncpy(surveyItem->sID, pstr, 99);
                                
                                pstr = pItem->Attribute("title");
                                if (pstr)
                                {
                                    utf8ncpy(surveyItem->sTitle, pstr, 99);
                                }
                                
                                pItem->QueryIntAttribute("invitecount", &surveyItem->nInvitecount);
                                pItem->QueryIntAttribute("completecount", &surveyItem->nCompletecount);
                                pstr = pItem->Attribute("desc");
                                if(pstr)
                                    utf8ncpy(surveyItem->sDesc,pstr, 599);
                                
                                pstr = pItem->Attribute("expiredate");
                                if(pstr)
                                    utf8ncpy(surveyItem->sExpiredate,pstr, 99);
                                
                                newContentItem->item = surveyItem;
                            }
                            else if (strcmp(newContentItem->sType, "qa") == 0)
                            {
                                
                                
                                TQAItem* qaItem=new TQAItem;
                                
                                pstr = pItem->Attribute("id");
                                if (!pstr)
                                {
                                    continue;
                                }
                               qaItem->sID = pstr;
                                
                                pstr=pItem->Attribute("question");
                                if(pstr)
                                    qaItem->sQuestion=pstr;
                                
                                
                                pstr=pItem->Attribute("categorytitle");
                                if(pstr)
                                    qaItem->sQcategorytitle=pstr;
                                
                                pstr=pItem->Attribute("questioner_username");
                                if(pstr)
                                    qaItem->sQuestioner_username=pstr;
                                
                                pstr=pItem->Attribute("questioner_fullname");
                                if(pstr)
                                    qaItem->sQuestioner_fullname=pstr;
                                
                                pstr=pItem->Attribute("question_icon");
                                if(pstr)
                                    qaItem->sQuestioner_icon=pstr;
                                
                                pstr=pItem->Attribute("pubdate");
                                if(pstr)
                                    qaItem->sPubdate=pstr;
                                
                                pItem->QueryIntAttribute("vc",&qaItem->nVC);
                                
                                pItem->QueryIntAttribute("pv", &qaItem->nPV);
                                
                                pItem->QueryIntAttribute("answercount", &qaItem->nAnswercount);
                                
                                pItem->QueryIntAttribute("value", &qaItem->nValue);
                                
                                pstr=pItem->Attribute("url");
                                if(pstr)
                                    qaItem->sPic_url=pstr;
                                
                                pstr=pItem->Attribute("Thumurl");
                                if(pstr)
                                    qaItem->sThumburl=pstr;
                                
                                
                                newContentItem->item=qaItem;
                                
                                
                                
                            }
                            else if(strcmp(newContentItem->sType, "apply") == 0)//报名
							{
                            	TTrainApplyItem* bItem = new TTrainApplyItem;
                            	*bItem = pItem;
                            	newContentItem->item = bItem;
							}
                            else if(strcmp(newContentItem->sType, "signin") == 0)//报名
							{
								TTrainSignInItem* bItem = new TTrainSignInItem();
								*bItem = pItem;
								newContentItem->item = bItem;
							}
                            else if(strcmp(newContentItem->sType, "trainclass") == 0)//报名
							{
								TMyTrainItem* bItem = new TMyTrainItem();
								*bItem = pItem;
								newContentItem->item = bItem;
							}
                            m_lstItem->push_back(newContentItem);
                            pItem = pItem->NextSiblingElement("item");
                        }
                        if (m_lstItem && m_lstItem->size() > 0)
                        {
                        	if(m_pListener)
                        		m_pListener->OnUpdateDataFinish(m_pUserData, TResult::ESuccess);
                            return ;
                        }
                        else
                        {
                        	if(m_pListener)
                        		m_pListener->OnUpdateDataFinish(m_pUserData, TResult::ENothing);
                            return ;
                        }
                    }
                }
            }
        }
    }
    if(m_pListener)
    	m_pListener->OnUpdateDataFinish(m_pUserData, TResult::EUnknownError);
}


int CMGetNewContent::GetBrowserItemModel(int nIndex)
{
    if(m_lstItem)
    {
        if(nIndex >= 0 && nIndex < m_lstItem->size())
        {
            TNewContentItem * temp ;
            
            temp=m_lstItem->at(nIndex);
            
            return temp->nModel;
        }
        else
            return -1;
        
    }
    else
        return -1;
    
}


//item总数
int CMGetNewContent::GetItemCount()
{
    if (!m_lstItem)
    {
        return 0;
    }
    
    return m_lstItem->size();
}


//item类型
int CMGetNewContent::GetItemType(int nIndex)
{
    if (nIndex < 0 || nIndex > m_lstItem->size())
    {
        return 0;
        
        
    }
    if(m_lstItem->size() == 0){
        return 0;
    }
    
    TNewContentItem* item = m_lstItem->at(nIndex);
    
    
    CM_LOGP(CM_LOGL_DEBUG, "CMGetNewContent item type==%s",item->sType);

    if (strcmp(item->sType, "course") == 0)
    {
        return TContentType::TCourse;
    }
    else if (strcmp(item->sType, "news") == 0)
    {
        return TContentType::TNews;
    }
    else if (strcmp(item->sType, "exam") == 0)
    {
        return TContentType::TExam;
    }
    else if (strcmp(item->sType, "exercise") == 0)
    {
        return TContentType::TExercise;
    }
    else if (strcmp(item->sType, "survey") == 0)
    {
        return TContentType::TSurvey;
    }
    else if (strcmp(item->sType, "qa") == 0)
    {
        return TContentType::TQuestion;
        
        
    }
    else
    {
        
        
        
        return 0;
        
        
    }
}


//通用item
BOOL CMGetNewContent::GetContentItem(int nIndex, TNewContentItem& item)
{
    if (nIndex < 0 || nIndex >= m_lstItem->size())
    {
        return FALSE;
    }
    
    item = *m_lstItem->at(nIndex);

    return TRUE;
}


//course and news
BOOL CMGetNewContent::GetBrowserItem(int nIndex, TBrowserItem& item)
{
    if (nIndex < 0 || nIndex >= m_lstItem->size())
    {
        return FALSE;
    }
    TNewContentItem* contentItem = m_lstItem->at(nIndex);
    
    item = *((TBrowserItem*)contentItem->item);
    
    return TRUE;
}


//survey
BOOL CMGetNewContent::GetSurveyItem(int nIndex, TSurveyListItem& item)
{
    if (nIndex < 0 || nIndex >= m_lstItem->size())
    {
        return FALSE;
    }
    
    TNewContentItem* contentItem = m_lstItem->at(nIndex);
    
    item = *((TSurveyListItem*)contentItem->item);
    
    return TRUE;
}


//exam
BOOL CMGetNewContent::GetExamItem(int nIndex, TExamListItem& item)
{
    if (nIndex < 0 || nIndex >= m_lstItem->size())
    {
        return FALSE;
    }
    
    TNewContentItem* contentItem = m_lstItem->at(nIndex);
    
    item = *((TExamListItem*)contentItem->item);
    
    return TRUE;
}


//exercise
BOOL CMGetNewContent::GetExerciseItem(int nIndex, TExerciseListItem& item)
{
    if (nIndex < 0 || nIndex >= m_lstItem->size())
    {
        return FALSE;
    }
    
    TNewContentItem* contentItem = m_lstItem->at(nIndex);
    
    item = *((TExerciseListItem*)contentItem->item);
    
    return TRUE;
}

//qa
BOOL CMGetNewContent::GetQuestionItem(int nIndex, TQAItem &item)
{
    if (nIndex < 0 || nIndex >= m_lstItem->size())
    {
        return FALSE;
    }
    
    TNewContentItem* contentItem = m_lstItem->at(nIndex);
    
    item = *((TQAItem*)contentItem->item);
    
    return TRUE;
}

BOOL CMGetNewContent::GetApplyItem(int nIndex, TTrainApplyItem &item)
{
	if (nIndex < 0 || nIndex >= m_lstItem->size())
	{
		return FALSE;
	}

	TNewContentItem* contentItem = m_lstItem->at(nIndex);

	item = *((TTrainApplyItem*)contentItem->item);

	return TRUE;

}


BOOL CMGetNewContent::GetSignInItem(int nIndex, TTrainSignInItem &item)
{
	if (nIndex < 0 || nIndex >= m_lstItem->size())
	{
		return FALSE;
	}

	TNewContentItem* contentItem = m_lstItem->at(nIndex);

	item = *((TTrainSignInItem*)contentItem->item);

	return TRUE;

}


BOOL CMGetNewContent::GetMyTrainItem(int nIndex, TMyTrainItem &item)
{
	if (nIndex < 0 || nIndex >= m_lstItem->size())
	{
		return FALSE;
	}

	TNewContentItem* contentItem = m_lstItem->at(nIndex);

	item = *((TMyTrainItem*)contentItem->item);

	return TRUE;

}

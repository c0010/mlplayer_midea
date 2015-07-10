// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmsurvey.h"
#include "cmglobal.h"
#include "tinyxml.h"
#include "cmpath.h"
#include "cmfile.h"
#include "cmsession.h"
#include "utf8ncpy.h"

CMSurvey::CMSurvey(IMUpdateDataListener* pUpdateDataListener, IMSimpleResultListener* pSimpleResultListener)
{
	m_pUpdateDataListener = pUpdateDataListener;
    m_pSimpleResultListener = pSimpleResultListener;
	m_UserData = NULL;
	m_nCurIndex = 0;
	m_pSession = NULL;

	m_lstSurVeyItemOption = new CMList<TSurveyItemOption*>;
}

CMSurvey::~CMSurvey()
{
	Clear();
	SAFEDELETE(m_lstSurVeyItemOption);
}
void CMSurvey::Clear()
{
	if (m_lstSurVeyItemOption) {

		for(CMList<TSurveyItemOption*>::iterator i = m_lstSurVeyItemOption->begin();i < m_lstSurVeyItemOption->end();i++)
		{
			TSurveyItemOption* pItem = (TSurveyItemOption*)*i;
			for (CMList<TSurveyOption*>::iterator it1 = pItem->m_lstOption->begin(); it1 != pItem->m_lstOption->end(); it1++)
			{
				TSurveyOption* option = (TSurveyOption*)*it1;
				SAFEDELETE(option);
			}
			pItem->m_lstOption->clear();
			SAFEDELETE(pItem->m_lstOption);
			SAFEDELETE(pItem);
		}
		m_lstSurVeyItemOption->clear();

	}

	SAFEDELETE(m_pSession);
}
void CMSurvey::SetUserData(void* UserData)
{
	m_UserData = UserData;
}

void CMSurvey::Cancel()
{
	if(m_pSession)
		m_pSession->Cancel();
}

void CMSurvey::GetSurvey(const char* sSurveyID)
{
	Clear();
	//开始发送获取调研问卷请求
    utf8ncpy(m_sSurveyID, sSurveyID, 99);
	char str[128];
    snprintf(str,sizeof(str),"&surveyid=%s", sSurveyID);

	if (m_pSession == NULL) {
		 m_pSession = new CMSession(this);//CMGlobal::TheOne().HttpMgr().GetSession(this);
	}
	if (m_pSession && !m_pSession->IsRunning()) {
		 m_pSession->Command(SERVICE_GETSURVEY, str);
	}

}

int CMSurvey::GetCurIndex()
{
	return m_nCurIndex;
}

BOOL CMSurvey::GetCurItem(TSurveyItem& item)
{
	if(m_nCurIndex < 0)
		m_nCurIndex = 0;
	return GetItem(m_nCurIndex, item);
}

BOOL CMSurvey::Prev()
{
	if (m_nCurIndex <= 0)
	{
		return FALSE;
	}
	else
	{
		m_nCurIndex--;
		return TRUE;
	}
}

BOOL CMSurvey::Next()
{
	if (m_nCurIndex >= GetItemCount()-1)
	{
		return FALSE;
	}
	else
	{
		m_nCurIndex++;
		return TRUE;
	}
}

BOOL CMSurvey::isFirst()
{
	return m_nCurIndex <= 0;
}

BOOL CMSurvey::isLast()
{
	return m_nCurIndex >= GetItemCount() - 1;
}

//获取当前题是否处理 Ｔ已处理 Ｆ 未处理
BOOL CMSurvey::GetCurIsAchieve()
{
	TSurveyItemOption* itemoption = m_lstSurVeyItemOption->at(m_nCurIndex);
	if(itemoption->tSurveyItem.nType != TSurveyQuestionType::EText)
	{
		for (CMList<TSurveyOption*>::iterator it1 = itemoption->m_lstOption->begin(); it1 != itemoption->m_lstOption->end(); it1++)
		{
			TSurveyOption* option = (TSurveyOption*)*it1;
			if(option && option->bCheck) {
				return TRUE;
			}
		}
		return FALSE;
	}
	else
		return TRUE;
}

int CMSurvey::GetItemCount()
{
	return m_lstSurVeyItemOption->size();
}

BOOL CMSurvey::GetItem(int nIndex, TSurveyItem& item)
{
	if(nIndex < 0 || nIndex >= m_lstSurVeyItemOption->size())
		return FALSE;
	TSurveyItemOption* pItemoption = m_lstSurVeyItemOption->at(nIndex);
	item = pItemoption->tSurveyItem;
	return TRUE;
}

int CMSurvey::GetItemOptionCount()
{
	if(m_nCurIndex < 0)
		return 0;
	TSurveyItemOption* pItemoption = m_lstSurVeyItemOption->at(m_nCurIndex);
	return pItemoption->m_lstOption->size();
}

BOOL CMSurvey::GetItemOption(int nIndex, TSurveyOption& option)
{
	if(m_nCurIndex < 0 || nIndex < 0)
		return FALSE;
	TSurveyItemOption* pItemoption = m_lstSurVeyItemOption->at(m_nCurIndex);
	if(nIndex > pItemoption->m_lstOption->size())
		return FALSE;
	option = *pItemoption->m_lstOption->at(nIndex);
	return TRUE;
}

void CMSurvey::SetAnswer(const char* answer)
{
//	ASSERT(strlen(answer) < 200);
	TSurveyItemOption* pItemoption = m_lstSurVeyItemOption->at(m_nCurIndex);
//    utf8ncpy(pItemoption->tSurveyItem.sAnswer, answer, 699);
    pItemoption->tSurveyItem.sAnswer = answer;
}

void CMSurvey::SetAnswer(int nIndex, BOOL checked)
{
	TSurveyItemOption* itemoption = m_lstSurVeyItemOption->at(m_nCurIndex);
	if(itemoption->tSurveyItem.nType == TSurveyQuestionType::ESingle)
	{
		int nCount = itemoption->m_lstOption->size();

		for (int i = 0; i < nCount; i++)
		{
			TSurveyOption* option = itemoption->m_lstOption->at(i);
			if (i == nIndex)
				option->bCheck = TRUE;
			else
				option->bCheck = FALSE;
		}
	}
	else
	{
		TSurveyOption* option = itemoption->m_lstOption->at(nIndex);
		option->bCheck = checked;
	}
}

BOOL CMSurvey::SetAnswerItem(TSurveyItemOption *itemoption, TiXmlElement *pItem)
{
	pItem->SetAttribute("type", itemoption->tSurveyItem.nType);

	if (itemoption->tSurveyItem.nType == TSurveyQuestionType::EText)
	{
		pItem->SetAttribute("answer", itemoption->tSurveyItem.sAnswer.c_str());
	}
	else
	{
		for (CMList<TSurveyOption*>::iterator it1 = itemoption->m_lstOption->begin(); it1 != itemoption->m_lstOption->end(); it1++)
		{
			TSurveyOption* option = (TSurveyOption*)*it1;

			TiXmlElement *pItem1    = new TiXmlElement("option");
			pItem1->SetAttribute("id", option->sID.c_str());
			if (option->bCheck)
				pItem1->SetAttribute("selected", 1);
			else
				pItem1->SetAttribute("selected", 0);
			pItem->LinkEndChild(pItem1);
		}
	}
	return TRUE;
}

BOOL CMSurvey::SaveStatus()
{
	int ret = FALSE;

	//创建一个XML的文档对象。
	TiXmlDocument *pDoc = new TiXmlDocument(CMGlobal::TheOne().GetUserDir() + L"survey.xml");
	if(!pDoc)
		return ret;

	pDoc->LoadFile(TIXML_ENCODING_UTF8);
	if(!pDoc->Error())
	{
		//获得根元素
		TiXmlElement *pRootElement = pDoc->RootElement();

		if(pRootElement)
		{
			TiXmlElement* pQuestion = pRootElement->FirstChildElement("question");
			while(pQuestion)
			{
				if(strcmp(pQuestion->Attribute("id"), m_sSurveyID) == 0)
				{
					ret = TRUE;
					pQuestion->SetAttribute("index", m_nCurIndex);
					break;
				}
				pQuestion = pQuestion->NextSiblingElement("question");
			}

			if(!ret)
			{
				pQuestion = new TiXmlElement("question");
				if(pQuestion)
				{
					pQuestion->SetAttribute("id", m_sSurveyID);
					pQuestion->SetAttribute("index", m_nCurIndex);

					pRootElement->LinkEndChild(pQuestion);

				}
			}

			SaveItemStatus(pQuestion);

			ret = pDoc->SaveFile();
		}
	}
	SAFEDELETE(pDoc);
    return ret;
}

//保存状态，可重载，必须先调用父类的此方法
BOOL CMSurvey::SaveItemStatus(TiXmlElement *pQuestion)
{
	for(CMList<TSurveyItemOption*>::iterator it = m_lstSurVeyItemOption->begin(); it != m_lstSurVeyItemOption->end(); it++)
	{
		TSurveyItemOption* itemoption = (TSurveyItemOption*)*it;
		TiXmlElement *pItem = new TiXmlElement("item");
		pItem->SetAttribute("id", itemoption->tSurveyItem.sID.c_str());
		if(SetAnswerItem(itemoption, pItem))
			pQuestion->LinkEndChild(pItem);
		else
			SAFEDELETE(pItem);
	}

	return true;
}


BOOL CMSurvey::LoadStatus()
{
    BOOL bRet = FALSE;
	CMString sPath = CMGlobal::TheOne().GetUserDir() + L"survey.xml";
	TiXmlDocument *pDoc = new TiXmlDocument(sPath);
	if(!pDoc)
		return bRet;
	if(!CMFile::FileExist(sPath))
	{
		pDoc->Parse("<?xml version=\"1.0\" encoding=\"utf-8\" ?><survey/>",NULL,TIXML_ENCODING_UTF8);
		bRet = !pDoc->Error();
		if(bRet)
			pDoc->SaveFile();
	}
	else
	{
		pDoc->LoadFile(TIXML_ENCODING_UTF8);
		if(!pDoc->Error())
		{
			TiXmlElement *pRoot = pDoc->RootElement();
			if(pRoot)
			{
				TiXmlElement* pQuestion = pRoot->FirstChildElement("question");
				while(pQuestion)
				{
					const char* sid = pQuestion->Attribute("id");
					if (strcmp(sid, m_sSurveyID) == 0)
					{
						bRet = LoadItemStatus(pQuestion);
						break;
					}

					pQuestion = pQuestion->NextSiblingElement("question");
				}

			}

		}

	}

	SAFEDELETE(pDoc);
    return bRet;
}

//读取状态，可重载，必须先调用父类的此方法
BOOL CMSurvey::LoadItemStatus(TiXmlElement *pQuestion)
{
	int index = 0;
	pQuestion->QueryIntAttribute("index", &index);
	if (m_lstSurVeyItemOption->size() <= index)
	{
		//取出的id错误,可能是题目数发生变化
		index = 0;
	}
	m_nCurIndex = index;

	//读取选项值
    //const char *pstr = NULL;
    TiXmlElement* pItem = pQuestion->FirstChildElement("item");
    while (pItem)
    {
		for(CMList<TSurveyItemOption*>::iterator it = m_lstSurVeyItemOption->begin(); it != m_lstSurVeyItemOption->end(); it++)
		{
			TSurveyItemOption* itemoption = (TSurveyItemOption*)*it;

			if(strcmp(pItem->Attribute("id"), itemoption->tSurveyItem.sID.c_str()) == 0)
			{
                if (itemoption->tSurveyItem.nType == TSurveyQuestionType::EText)
                {
//                	utf8ncpy(itemoption->tSurveyItem.sAnswer, pItem->Attribute("answer"), 699);
                    itemoption->tSurveyItem.sAnswer =pItem->Attribute("answer");

                }
                else
                {
                	//不是问答题
                    TiXmlElement* pOptionItem = pItem->FirstChildElement();
                    while (pOptionItem)
                    {

						const char* id = NULL;
						id = pOptionItem->Attribute("id");
						int selected = 0;
						pOptionItem->Attribute("selected", &selected);
						for (CMList<TSurveyOption*>::iterator it1 = itemoption->m_lstOption->begin(); it1 != itemoption->m_lstOption->end(); it1++)
						{
							TSurveyOption* option = (TSurveyOption*)*it1;

							if(strcmp(id, option->sID.c_str()) == 0) {
								option->bCheck = (selected == 0?FALSE:TRUE);
								break;
							}

						}

                        pOptionItem = pOptionItem->NextSiblingElement("option");
                    }

                }
				break;
			}
		}


    	pItem = pItem->NextSiblingElement("item");
    }

    return true;
}

BOOL CMSurvey::ClearStatus()
{
	BOOL bRet = FALSE;

	//创建一个XML的文档对象。
	TiXmlDocument *pDoc = new TiXmlDocument(CMGlobal::TheOne().GetUserDir() + L"survey.xml");
	if(!pDoc)
		return bRet;

	pDoc->LoadFile(TIXML_ENCODING_UTF8);
	if(!pDoc->Error())
	{

		TiXmlElement *pRoot = pDoc->RootElement();
		if(pRoot)
		{
			TiXmlElement* pQuestion = pRoot->FirstChildElement("question");
			while(pQuestion)
			{
				const char* sid = pQuestion->Attribute("id");
				if (strcmp(sid, m_sSurveyID) == 0)
				{
					bRet = TRUE;
					break;
				}
				pQuestion = pQuestion->NextSiblingElement("question");
			}

			if (bRet)
			{
				pRoot->RemoveChild(pQuestion);
				bRet = pDoc->SaveFile();
			}
		}

	}

	SAFEDELETE(pDoc);
    return bRet;
}

void CMSurvey::CommitAnswer()
{
	if (m_pSession && m_pSession->IsRunning())
		return;
	//开发发送结果，并返回
	TiXmlElement *pRoot    = new TiXmlElement("body");

	for(CMList<TSurveyItemOption*>::iterator it = m_lstSurVeyItemOption->begin(); it != m_lstSurVeyItemOption->end(); it++)
	{
		TSurveyItemOption* itemoption = (TSurveyItemOption*)*it;
		TiXmlElement *pItem    = new TiXmlElement("item");
		pItem->SetAttribute("id", itemoption->tSurveyItem.sID.c_str());
		pItem->SetAttribute("type", itemoption->tSurveyItem.nType);

		if (itemoption->tSurveyItem.nType == TSurveyQuestionType::EText)
		{
			pItem->SetAttribute("answer", itemoption->tSurveyItem.sAnswer.c_str());
		}
		else
		{
			for (CMList<TSurveyOption*>::iterator it1 = itemoption->m_lstOption->begin(); it1 != itemoption->m_lstOption->end(); it1++)
			{
				TSurveyOption* option = (TSurveyOption*)*it1;

				TiXmlElement *pItem1    = new TiXmlElement("option");
				pItem1->SetAttribute("id", option->sID.c_str());
				if (option->bCheck)
					pItem1->SetAttribute("selected", 1);
				else
					pItem1->SetAttribute("selected", 0);
				pItem->LinkEndChild(pItem1);
			}
		}
		pRoot->LinkEndChild(pItem);
	}

	TiXmlPrinter printer;
	pRoot->Accept(&printer);
//	CM_ERRP("survey commit %d %s", printer.Size(), printer.CStr());
	char str[128];
	snprintf(str,sizeof(str),"&surveyid=%s", m_sSurveyID);
		//CMSession& session = CMGlobal::TheOne().HttpMgr().GetSession(this);
	if (m_pSession) {
		m_pSession->CommandPost(SERVICE_PUTSURVEYRESULT, str, printer.CStr(), printer.Size());
	}

	//清除本地保存的数据
	ClearStatus();
}

//读取状态 可重载 必须调用父类的此方法
void CMSurvey::OnCmdResult(TiXmlElement *pItem)
{
    //添加item到显示list
    pItem = pItem->FirstChildElement();

    const char *pstr = NULL;
    while (pItem)
    {
        TSurveyItemOption* itemoption = new TSurveyItemOption;
        itemoption->m_lstOption = new CMList<TSurveyOption*>;

        pstr = pItem->Attribute("id");
        if (!pstr)
            continue;

        itemoption->tSurveyItem.sID = pstr;

        pItem->Attribute("type", &itemoption->tSurveyItem.nType);

        pstr =  pItem->Attribute("question");
        if(pstr)
            itemoption->tSurveyItem.sQuestion = pstr;

        pstr = pItem->Attribute("category");
        if(pstr)
            itemoption->tSurveyItem.sCategory = pstr;

        if (itemoption->tSurveyItem.nType != TSurveyQuestionType::EText) //不是问答题
        {
            TiXmlElement* pOptionItem = pItem->FirstChildElement();
            while (pOptionItem)
            {
                TSurveyOption* option = new TSurveyOption;
                option->bCheck = FALSE;

                const char* pstr = NULL;
                pstr = pOptionItem->Attribute("id");
                if(pstr)
                	option->sID = pstr;
                pstr = pOptionItem->Attribute("description");
                if(pstr)
                    option->sText = pstr;

                itemoption->m_lstOption->push_back(option);

                pOptionItem = pOptionItem->NextSiblingElement("option");
            }

        }
        m_lstSurVeyItemOption->push_back(itemoption);
        pItem = pItem->NextSiblingElement("item");
    }
}

void CMSurvey::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
    if(nCode == MER_OK)
    {
        //获得根元素res。
        TiXmlElement *pItem = pDoc->RootElement();

        if(pItem)
        {
            INT32 nCmdID = 0;
            pItem->QueryIntAttribute("no", &nCmdID);

			if (pItem->QueryIntAttribute("count", &m_nCount) != TIXML_SUCCESS) {
				m_nCount = 0;
			}

            INT32 nErr = 0;
            if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
            {
                if (nErr == 0)
                {
                    if (nCmdID  ==  SERVICE_GETSURVEY)
                    {
                        OnCmdResult(pItem);

                        if (m_lstSurVeyItemOption->size() == 0)
                        {
                            //错误的空的调研列表
                            //goto ERR;
                            m_pUpdateDataListener->OnUpdateDataFinish(m_UserData, TResult::ENothing);
                        }
                        else
                        {
                            //获取本地保存的当前位置
                            LoadStatus();
                            m_pUpdateDataListener->OnUpdateDataFinish(m_UserData, TResult::ESuccess);
                        }
                        return;
                    }
                    else if (nCmdID == SERVICE_PUTSURVEYRESULT)
                    {
						m_pSimpleResultListener->OnRequestFinish(m_UserData, TResult::ESuccess);
                        return;
                    }
                }
                else if (nErr == MERS_NOTRETURN)
                {
					goto ERR;
                    CM_ERR("MERS_NOTRETURN");
                }
                else
                    goto ERR;
            }
        }
    }
    else
    {
		goto ERR;
        CM_ERR("CMSurveyUI OnSessionCmd not ok");
    }

ERR:
    if (nCmdID == SERVICE_PUTSURVEYRESULT)
	{
			m_pSimpleResultListener->OnRequestFinish(m_UserData, TResult::EUnknownError);
	}
    else if (nCmdID == SERVICE_GETSURVEY)
        m_pUpdateDataListener->OnUpdateDataFinish(m_UserData, TResult::EUnknownError);
}

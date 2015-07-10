// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmquestionhandler.h"
#include "tinyxml.h"
#include "cmfile.h"
#include "cmwrongquestion.h"
#include "cmsession.h"
#include "cmglobal.h"
#include "utf8ncpy.h"
#include "cmexamlist.h"


TQuestionItem::TQuestionItem()
{
    nType = 0;
    nValue = 0;
    isWrong = FALSE;
    isWrongOrig = FALSE;
    isRight = FALSE;
    isChecked = FALSE;
    sAnswer = "";
}

int TQuestionItem::BindParam(sqlite3_stmt* stmt,int col,int value) const
{
    return  sqlite3_bind_int(stmt, col, value);
}

int TQuestionItem::BindParam(sqlite3_stmt* stmt,int col,const char* value) const
{
    if(value)
        return  sqlite3_bind_text(stmt, col, value, -1,NULL);
    
    return sqlite3_bind_null(stmt, col);
    
}
int TQuestionItem::BindParam(sqlite3_stmt* stmt,int col,float value) const
{
    return  sqlite3_bind_double(stmt, col, value);
}

void TQuestionItem::bindItem(sqlite3_stmt* stmt) const
{
    BindParam(stmt, 1, sID.c_str());
    BindParam(stmt, 2, nType);
    BindParam(stmt, 3, sQuestion.c_str());
    BindParam(stmt, 4, sDescription.c_str());
    BindParam(stmt, 5, nValue);
    BindParam(stmt, 6, isWrong);
    BindParam(stmt, 7, sRightAnswer.c_str());
    
    BindParam(stmt, 8, sMyAnswer.c_str());
    BindParam(stmt, 9, sAnswer.c_str());
    BindParam(stmt, 10, isWrongOrig);
    BindParam(stmt, 11, isRight);
    BindParam(stmt, 13, isChecked);
}

TQuestionItem::~TQuestionItem()
{
    
}

const char* TQuestionItem::GetQuestionItemID()const
{
    return sID.c_str();
}

int TQuestionItem::GetQuestionItemType() const
{
    return nType;
}

const char* TQuestionItem::GetQuestionItemCategory() const
{
    return sCategory.c_str();
}

const char* TQuestionItem::GetQuestionItemQuestion() const
{
    return sQuestion.c_str();
}

const char* TQuestionItem::GetQuestionItemDescription() const
{
    return sDescription.c_str();
}

int TQuestionItem::GetQuestionItemValue() const
{
    return nValue;
}

const char* TQuestionItem::GetQuestionItemRightAnswer() const
{
    return sRightAnswer.c_str();
}

const char* TQuestionItem::GetQuestionItemMyAnswer() const
{
    return sMyAnswer.c_str();
}

const char* TQuestionItem::GetQuestionItemAnswer() const
{
    return sAnswer.c_str();
}

BOOL TQuestionItem::GetQuestionItemRight() const
{
    return isRight;
}

BOOL TQuestionItem::GetQuestionItemChecked() const
{
    return isChecked;
}

TOption::TOption()
{
    nID = "";
    bCheck = FALSE;
    bMyAnswer = FALSE;
    bRightAnswer = FALSE;
}

int TOption::BindParam(sqlite3_stmt* stmt,int col,int value) const
{
    return  sqlite3_bind_int(stmt, col, value);
}

int TOption::BindParam(sqlite3_stmt* stmt,int col,const char* value) const
{
    if(value)
        return  sqlite3_bind_text(stmt, col, value, -1,NULL);
    
    return sqlite3_bind_null(stmt, col);
    
}

int TOption::BindParam(sqlite3_stmt* stmt,int col,float value) const
{
    return  sqlite3_bind_double(stmt, col, value);
}

void TOption::bindItem(sqlite3_stmt* stmt) const
{
    char sumid[128];
    sprintf(sumid, "%s%s",sSID.c_str(),nID.c_str());
    BindParam(stmt, 1, sumid);
    BindParam(stmt, 2, sSID.c_str());
    BindParam(stmt, 3, nID.c_str());
    BindParam(stmt, 4, bCheck);
    BindParam(stmt, 5, sText.c_str());
    BindParam(stmt, 6, bRightAnswer);
    BindParam(stmt, 7, bMyAnswer);
}

const char* TOption::GetOptionItemsID()const
{
    return sSID.c_str();
}

const char* TOption::GetOptionItemnID() const
{
    return nID.c_str();
}

const char* TOption::GetOptionItemText()const
{
    return sText.c_str();
}

BOOL TOption::GetOptionItemCheck() const
{
    return bCheck;
}

BOOL TOption::GetOptionItemRightAnswer() const
{
    return bRightAnswer;
}

BOOL TOption::GetOptionItemMyAnswer() const
{
    return bMyAnswer;
}

TOption::~TOption()
{
    
}

CMQuestionhandler::CMQuestionhandler()
:CMHandler<TQuestion>()
{
    nRightCount = 0;
	m_nCurIndex = 0;
    isExCommit = FALSE;
}


CMQuestionhandler::~CMQuestionhandler()
{
	Clear();
}

void CMQuestionhandler::Clear()
{
//	for(CMList<TQuestion>::iterator i = m_lstItem->begin();i < m_lstItem->end();i++)
//	{
//		TQuestion pItem = (TQuestion)*i;
//        
//        if (pItem.m_lisOption)
//		pItem.m_lisOption->clear();
//		SAFEDELETE(pItem.m_lisOption);
//	}
    m_lstItem->clear();
//    SAFEDELETE(m_lstItem);
}

void CMQuestionhandler::SetListener(IMUpdateDataListener *pListener, IMSimpleResultListener *pSimpleResultListener)
{
    m_pListener = pListener;
    m_pSimpleResultListener = pSimpleResultListener;
}

void CMQuestionhandler::GetQuestion(int nServiceNo, const char* sID , BOOL isView)
{    
	char sParam[256] = {0};
	if(!isView)
		snprintf(sParam,sizeof(sParam),"id=%s", sID);
	else
		snprintf(sParam,sizeof(sParam),"id=%s&flag=view", sID);

    Request(nServiceNo, sParam);
}

void CMQuestionhandler::GetQuestionStart(int nServiceNo, const char* sID ,const char* sDst)
{

	char sParam[512] = {0};
	if(sDst&&strlen(sDst) > 0){
		snprintf(sParam,sizeof(sParam),"id=%s&_dts_=%s", sID ,sDst);
	}
	else
		snprintf(sParam,sizeof(sParam),"id=%s", sID);

    Request(nServiceNo, sParam);
}

TQuestion::TQuestion(const TQuestion& right)
{
    item = right.item;
    
    if (right.m_lisOption)
    {

        m_lisOption = new CMList<TOption>;
        
        m_lisOption->append(*(right.m_lisOption));
    }
    else
        m_lisOption =NULL;

}

TQuestion::TQuestion()
{
    m_lisOption =NULL;
}

TQuestion::~TQuestion()
{
    if (m_lisOption)
    {
        m_lisOption->clear();
    }
    SAFEDELETE(m_lisOption);
}

TQuestion& TQuestion::operator=(const TQuestion& right)
{
    item = right.item;
    
    if (right.m_lisOption)
    {
        if (m_lisOption)
            m_lisOption->clear();
        else
            m_lisOption = new CMList<TOption>;
        
        m_lisOption->append(*(right.m_lisOption));
    }
    return *this;
}

BOOL CMQuestionhandler::GetQuestionItem(int nIndex, TQuestionItem& item)
{
    if (nIndex < 0 || nIndex >= GetItemCount())
        return FALSE;
    TQuestion& questionItem = m_lstItem->at(nIndex);
    if (&questionItem && &questionItem.item)
    {
        item = questionItem.item;
        return TRUE;
    }
	return FALSE;
}

int CMQuestionhandler::GetItemOptionCount()
{
    TQuestion& questionItem = m_lstItem->at(GetCurIndex());
    
    if (&questionItem && questionItem.m_lisOption)
    {
        if (!questionItem.m_lisOption) {
            return 0;
        }
        return questionItem.m_lisOption->size();
    }
	return 0;
}

BOOL CMQuestionhandler::GetItemOption(int nIndex, TOption& option)
{
	if(nIndex < 0)
		return FALSE;
    
    TQuestion& questionItem = m_lstItem->at(GetCurIndex());
    
    if (&questionItem)
    {
        if (nIndex >= questionItem.m_lisOption->size())
            return FALSE;
        option = questionItem.m_lisOption->at(nIndex);

        return TRUE;
    }
	return FALSE;
}

void CMQuestionhandler::SetAnswer(const char* answer)
{

	if(GetItemCount()==0)
		return;

    if (GetCurIndex() >= 0 && GetCurIndex() < GetItemCount())
        m_lstItem->at(GetCurIndex()).item.sAnswer = answer;
    
    if (strlen(answer) > 0)
    {
        m_lstItem->at(GetCurIndex()).item.isChecked = TRUE;
    }
    else
    {
        m_lstItem->at(GetCurIndex()).item.isChecked = FALSE;
    }
        
}

void CMQuestionhandler::SetAnswer(int nIndex, BOOL checked)
{

	if(GetItemCount() == 0)
		return;

    TQuestion& questionItem = m_lstItem->at(GetCurIndex());
    
    //if (GetItem(GetCurIndex(), questionItem))
    
        if (questionItem.item.nType == TQuestionType::ESingle)
        {
            for (int i = 0; i < questionItem.m_lisOption->size(); i++)
            {
                TOption& option = questionItem.m_lisOption->at(i);
                if (i == nIndex)
                {
                    option.bCheck = TRUE;
                    questionItem.item.isChecked = TRUE;
                }
                else
                {
                    option.bCheck = FALSE;
                }
            }
        }
        else
        {
            TOption& option = questionItem.m_lisOption->at(nIndex);
            option.bCheck = checked;
        }
    
}

int CMQuestionhandler::GetCurIndex()
{
	return m_nCurIndex;
}

void CMQuestionhandler::SetCurIndex(int nIndex)
{
    m_nCurIndex = nIndex;
}

BOOL CMQuestionhandler::IsQuestionComplete(int nIndex)
{
    BOOL ret = FALSE;
    
    TQuestion question;
    
    if (GetItem(nIndex, question))
    {
        if (question.item.nType == TQuestionType::EText)
        {
            if (strcmp(question.item.sAnswer.c_str(), "") == 0)
            {
                ret = FALSE;
            }
            else
            {
                ret = TRUE;
            }
        }
        else
        {
            for(CMList<TOption>::iterator it = question.m_lisOption->begin(); it != question.m_lisOption->end(); it++)
            {
                TOption option = (TOption)*it;
                if (option.bCheck)
                {
                    ret = TRUE;
                    break;
                }
            }
        }
    }
    
    return ret;
}

int CMQuestionhandler::GetRightCount(const char* questionID)
{
    mID = questionID;
    return DoGetRightCount(questionID);
}

BOOL CMQuestionhandler::IsItemSaved()
{
    TQuestion questionItem;
    
    if (GetItem(GetCurIndex(), questionItem))
    {
        return questionItem.item.isRight;
    }
    
    return FALSE;
}

BOOL CMQuestionhandler::isExciseCommit()
{
	return isExCommit;
}

void CMQuestionhandler::setRight()
{
    if (!IsItemSaved())
    {
        if (GetCurIndex() >= 0 && GetCurIndex() < GetItemCount()) {
            TQuestion& questionItem = m_lstItem->at(GetCurIndex());
            questionItem.item.isRight = TRUE;
            nRightCount++;
        }
    }
}

BOOL CMQuestionhandler::GetCurItem(TQuestionItem& item)
{
	if(m_nCurIndex < 0)
		m_nCurIndex = 0;
	return GetQuestionItem(m_nCurIndex, item);
}

void CMQuestionhandler::SetExerciseAnswer(BOOL checked)
{
    
    if (GetCurIndex() >= 0 && GetCurIndex() < GetItemCount())
    {
        TQuestion& questionItem = m_lstItem->at(GetCurIndex());
        if (questionItem.item.nType == TQuestionType::EMultiple)
        {
            questionItem.item.isChecked = checked;
        }
    }
}

void CMQuestionhandler::SetIsChecked(BOOL checked)
{
    if (GetCurIndex() >= 0 && GetCurIndex() < GetItemCount())
    {
        TQuestion& questionItem = m_lstItem->at(GetCurIndex());
        questionItem.item.isChecked = checked;
    }
}

int CMQuestionhandler::GetDoneCount()
{
    int nCount = 0;
    
	for(CMList<TQuestion>::iterator it = m_lstItem->begin(); it != m_lstItem->end(); it++)
	{
		TQuestion question = (TQuestion)*it;
        
        TQuestionItem item = question.item;
        
        //练习 不选择答案,直接点击查看答案(此时该题已加入错题库 isChecked = TRUE),该题算入已做
        if (item.isChecked) {
            nCount++;
            continue;
        }
        
        if (question.item.nType != TQuestionType::EText)
        {
            for(CMList<TOption>::iterator it = question.m_lisOption->begin(); it != question.m_lisOption->end(); it++)
            {
                TOption& option = (TOption&)*it;
                if (option.bCheck)
                {
                    nCount++;
                    break;
                }
            }
        }
        else
        {
            if (strlen(question.item.sAnswer.c_str()) > 0)
            {
                nCount++;
            }
        }
	}
    
    return nCount;
}

BOOL CMQuestionhandler::Prev()
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

BOOL CMQuestionhandler::Next()
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

BOOL CMQuestionhandler::isFirst()
{
	return m_nCurIndex <= 0;
}

BOOL CMQuestionhandler::isLast()
{
	return m_nCurIndex >= GetItemCount() - 1;
}

BOOL CMQuestionhandler::DoCreate(sqlite3* db)
{
    return TRUE;
}

BOOL CMQuestionhandler::DoRefresh(TQuestion& obj)
{
    return TRUE;
}

BOOL CMQuestionhandler::DoUpdate(const TQuestion& obj)
{
    return  TRUE;
}

BOOL CMQuestionhandler::DoPutItem(TiXmlElement* pItem, sqlite3* db, TQuestion& item)
{
    return TRUE;
}

BOOL CMQuestionhandler::DoGetCacheItems(sqlite3* db)
{
    return TRUE;
}

void CMQuestionhandler::DoClear()
{
}

BOOL CMQuestionhandler::SetAnswerItem(TQuestion* itemoption, TiXmlElement* pItem)
{
    pItem->SetAttribute("type", itemoption->item.nType);
    
//    pItem->SetAttribute("correct", itemoption->item.isRight);
    
    pItem->SetAttribute("value",itemoption->item.nValue);

	if (itemoption->item.nType == TQuestionType::EText)
	{
		pItem->SetAttribute("answer", (const CHAR*)itemoption->item.sAnswer.c_str());
	}
	else
	{
		for (CMList<TOption>::iterator it1 = itemoption->m_lisOption->begin(); it1 != itemoption->m_lisOption->end(); it1++)
		{
			TOption& option = (TOption&)*it1;
			
			TiXmlElement *pItem1    = new TiXmlElement("option");
			pItem1->SetAttribute("id", option.nID.c_str());

			string answer = "";

            char s[3] = {0};
            s[0] = option.sText[0];
            answer.append(s);

			pItem1->SetAttribute("answer",answer.c_str());
			if (option.bCheck)
				pItem1->SetAttribute("selected", 1);
			else
				pItem1->SetAttribute("selected", 0);
			pItem->LinkEndChild(pItem1);
		}
	}
    
	return TRUE;
}

BOOL CMQuestionhandler::SaveStatus()
{
    BOOL ret = TRUE;
    
    sqlite3*db = CheckTable();
    
	char *errorMsg;
    
    if (sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("Failed begin transaction:%s", sqlite3_errmsg(db));
    }
    
    for (int i = 0; i < GetItemCount(); i++)
    {
        TQuestion question;
        GetItem(i, question);
        DoUpdate(question);
    }
    
    if (sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, &errorMsg) != SQLITE_OK)
    {
        ret = FALSE;
        
        CM_ERRP("Failed to commit transaction: %s", errorMsg);
        
        if (sqlite3_exec(db, "ROLLBACK TRANSACTION", NULL, NULL, &errorMsg) != SQLITE_OK)
        {
            CM_ERRP("Failed to ROLLBACK transaction: %s", errorMsg);
        }
    }
    
    return ret;
}

BOOL CMQuestionhandler::LoadStatus()
{
    BOOL bRet = FALSE;
	CMString sPath = CMGlobal::TheOne().GetUserDir() + L"examexercise.xml";
	TiXmlDocument *pDoc = new TiXmlDocument(sPath);
	if(!pDoc)
		return bRet;
	if(!CMFile::FileExist(sPath))
	{
		bRet = FALSE;
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
					if (strcmp(sid, mID.c_str()) == 0)
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

BOOL CMQuestionhandler::ClearStatus()
{
	BOOL bRet = FALSE;

	TiXmlDocument *pDoc = new TiXmlDocument(CMGlobal::TheOne().GetUserDir() + L"examexercise.xml");
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
				if (strcmp(sid, mID.c_str()) == 0)
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

BOOL CMQuestionhandler::SaveItemStatus(TiXmlElement* pQuestion)
{
	for(CMList<TQuestion>::iterator it = m_lstItem->begin(); it != m_lstItem->end(); it++)
	{
		TQuestion itemoption = (TQuestion&)*it;
		TiXmlElement *pItem = new TiXmlElement("item");
		pItem->SetAttribute("id", (const char*)itemoption.item.sID.c_str());

		if(SetAnswerItem(&itemoption, pItem))
			pQuestion->LinkEndChild(pItem);
		else
			SAFEDELETE(pItem);
	}

	return true;
}


 BOOL CMQuestionhandler:: LoadItemStatus(TiXmlElement* pQuestion)
 {
     int index = 0;
     pQuestion->QueryIntAttribute("index", &index);
     if (GetItemCount() <= index)
     {
         index = 0;
     }
     m_nCurIndex = index;
     
     pQuestion->QueryIntAttribute("rightcount", &nRightCount);
     
     int nComplete = 0;
     pQuestion->QueryIntAttribute("iscomplete", &nComplete);
     
     isExCommit = (nComplete == 1 ? TRUE : FALSE);
     
     TiXmlElement* pItem = pQuestion->FirstChildElement("item");
     while (pItem)
     {
         for(CMList<TQuestion>::iterator it = m_lstItem->begin(); it != m_lstItem->end(); it++)
     {
     TQuestion& itemoption = (TQuestion&)*it;
     
     if(strcmp(pItem->Attribute("id"), (const char*)itemoption.item.sID.c_str()) == 0)
     {
         int nRight = 0;
         pItem->Attribute("correct", &nRight);
         
         itemoption.item.isRight = (nRight == 1 ? TRUE : FALSE);
     
         if (itemoption.item.nType == TQuestionType::EText)
         {
             itemoption.item.sAnswer = pItem->Attribute("answer");
             
             if (strlen(itemoption.item.sAnswer.c_str()) > 0) {
                 itemoption.item.isChecked = TRUE;
             }
         }
     else
     {
    	 //不是问答题
     TiXmlElement* pOptionItem = pItem->FirstChildElement();
     while (pOptionItem)
     {
    	 string id = "";

    	 const char* pStr = NULL;

    	 pStr = pOptionItem->Attribute("id");
    	 if(pStr)
    		 id = pStr;


         int selected = 0;
         pOptionItem->Attribute("selected", &selected);
     
         for (CMList<TOption>::iterator it1 = itemoption.m_lisOption->begin(); it1 != itemoption.m_lisOption->end(); it1++)
         {
             TOption& option = (TOption&)*it1;
     
         if(strcasecmp(id.c_str(),option.nID.c_str())) {
             option.bCheck = (selected == 0?FALSE:TRUE);
             option.bMyAnswer = option.bCheck;
             
             if (option.bCheck) {
                 itemoption.item.isChecked = option.bCheck;
             }
             
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

void CMQuestionhandler::Commit(int sServiceNo, const char* sParam)
{
	if (m_pSession && m_pSession->IsRunning())
		return;

	TiXmlElement *pRoot    = new TiXmlElement("body");

	for(CMList<TQuestion>::iterator it = m_lstItem->begin(); it != m_lstItem->end(); it++)
	{
		TQuestion itemoption = (TQuestion)*it;
        
		TiXmlElement *pItem = new TiXmlElement("item");
		pItem->SetAttribute("id",itemoption.item.sID.c_str());
        
		if(SetAnswerItem(&itemoption, pItem))
        {
			pRoot->LinkEndChild(pItem);
        }
		else
			SAFEDELETE(pItem);
	}
	
	TiXmlPrinter printer;
	pRoot->Accept(&printer);
	

	SaveStatus();
	if (m_pSession) {
		m_pSession->CommandPost(sServiceNo, sParam, printer.CStr(), printer.Size());
	}

}


int CMQuestionhandler::DoGetRightCount(const char* questionID)
{
    return FALSE;
}

void CMQuestionhandler::OnCmdResult(TiXmlElement* pItem)
{
}

void CMQuestionhandler::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc)
{
    if(nCode == MER_OK)
    {
        TiXmlElement *pItem = pDoc->RootElement();
		
        if(pItem)
        {
            INT32 nCmdID = 0;
            pItem->QueryIntAttribute("no", &nCmdID);
			
            INT32 nErr = 0;
            if(pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS)
            {
                if (nErr == 0)
                {
                    if (nCmdID  ==  SERVICE_COMMITEXAM)
                    {
//						for(CMList<TQuestion>::iterator it = m_lstItem->begin(); it != m_lstItem->end(); it++)
//						{
//							TQuestion itemoption = (TQuestion&)*it;
//                            DoRefresh(itemoption);
//							itemoption.item.isWrongOrig = itemoption.item.isWrong;
//							if(itemoption.item.nType == TQuestionType::EText){
//                                itemoption.item.sMyAnswer = itemoption.item.sAnswer;
//                                itemoption.item.sAnswer = "";
//							}
//							else
//							{
//								for (CMList<TOption>::iterator it1 = itemoption.m_lisOption->begin(); it1 != itemoption.m_lisOption->end(); it1++)
//								{
//									TOption& option = (TOption&)*it1;
//                                    option.bMyAnswer = option.bCheck;
//                                    option.bCheck = FALSE;
//								}
//							}
//
//							ClearStatus();
//
//                            DoUpdate(itemoption);
//						}
						DoClear();
						m_pSimpleResultListener->OnRequestFinish(m_UserData, TResult::ESuccess);
                        return;
                    }
                }
                else
                    m_pSimpleResultListener->OnRequestFinish(m_UserData, TResult::EUnknownError);
            }
        }
    }
    else
    {
        CM_ERR("CMQuestionhandlerUI OnSessionCmd not ok");
        m_pSimpleResultListener->OnRequestFinish(m_UserData, TResult::EUnknownError);
    }
}

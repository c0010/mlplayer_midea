// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cmwrongquestion.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "utf8ncpy.h"

CMWrongQuestion::CMWrongQuestion()
	: CMQuestionhandler()
{
    m_nWrongs = 0;
    sLastUpdate = 0;
}

CMWrongQuestion::~CMWrongQuestion()
{
}

void CMWrongQuestion::GetWrongQuestion(const char* sID)
{
    DoGetWrongQuestion(sID);
}

int CMWrongQuestion::GetWrongCount(const char *questionID)
{
    return m_nWrongs;
}

void CMWrongQuestion::SaveExerciseStatus()
{
    DoSaveExerciseStatus();
}

void CMWrongQuestion::SaveWrongStatus()
{
    DoSaveWrongStatus();
}

BOOL CMWrongQuestion::DoSaveExerciseStatus()
{
    return FALSE;
}

BOOL CMWrongQuestion::DoSaveWrongStatus()
{
    return FALSE;
}

BOOL CMWrongQuestion::isOptionAnswerRight()
{
	BOOL isRight = TRUE;
    
    TQuestion question;
    GetItem(GetCurIndex(), question);
    
    if (!question.m_lisOption) {
        return FALSE;
    }
    
    if (question.item.nType != TQuestionType::EText)
    {
        if (!question.m_lisOption)
            return FALSE;
		for (CMList<TOption>::iterator it1 = question.m_lisOption->begin(); it1 != question.m_lisOption->end(); it1++)
		{
			TOption& option = (TOption&)*it1;
			if(&option && option.bRightAnswer != option.bCheck)
			{
				isRight = FALSE;
				break;
			}
		}
    }
    
	return isRight;
}

BOOL CMWrongQuestion::isOptionAnswerRight(int nIndex)
{
	BOOL isRight = TRUE;
    
    TQuestion question;
    GetItem(nIndex, question);
    
    if (question.item.nType != TQuestionType::EText)
    {
		for (CMList<TOption>::iterator it1 = question.m_lisOption->begin(); it1 != question.m_lisOption->end(); it1++)
		{
			TOption& option = (TOption&)*it1;
			if(&option && option.bRightAnswer != option.bCheck)
			{
				isRight = FALSE;
				break;
			}
		}
    }
    
	return isRight;
}


BOOL CMWrongQuestion::isMyAnswerRight()
{
	BOOL isRight = TRUE;
    
    TQuestion question;
    GetItem(GetCurIndex(), question);
    
    if (question.item.nType != TQuestionType::EText)
    {
		for (CMList<TOption>::iterator it1 = question.m_lisOption->begin(); it1 != question.m_lisOption->end(); it1++)
		{
			TOption& option = (TOption&)*it1;
			if(&option && option.bRightAnswer != option.bMyAnswer)
			{
				isRight = FALSE;
				break;
			}
		}
    }
    
	return isRight;
}

BOOL CMWrongQuestion::isWrong()
{
	TQuestionItem item;
	if(GetCurItem(item))
		return item.isWrong;
	else
		return FALSE;
}

void CMWrongQuestion::SetWrong(BOOL isWrong)
{
    if (GetCurIndex() >= 0 && GetCurIndex() < m_lstItem->size()) {
        TQuestion& question = m_lstItem->at(GetCurIndex());
        question.item.isWrong = isWrong;
    }
}

const char* CMWrongQuestion::GetRightAnswer()
{
	m_sRightAnswer = "";
    //TQuestion& question = m_lstItem->at(GetCurIndex());

    TQuestion question;
    GetItem(GetCurIndex(), question);
    
    if (question.item.nType == TQuestionType::EText)
    {
        m_sRightAnswer = question.item.sRightAnswer;
    }
    else
    {
        if (!question.m_lisOption)
            return m_sRightAnswer.c_str();
        for (int i = 0; i < question.m_lisOption->size(); i++)
        {


            TOption& option = question.m_lisOption->at(i);
            if(&option && option.bRightAnswer && strlen(option.sText.c_str()) > 0)
            {
//                if(question.item.nType == TQuestionType::EYesNo)
//                    m_sRightAnswer = option.sText;
//                else
//                {

                    char s[3] = {0};
                    s[0] = option.sText[0];
                    s[1] = ' ';
                    //m_sRightAnswer += s;
                    m_sRightAnswer.append(s);
//                }
            }
        }
    }

	return m_sRightAnswer.c_str();
}

BOOL CMWrongQuestion::SetAnswerItem(TQuestion* itemoption, TiXmlElement* pItem)
{
	int iswrong = 2;

	if(itemoption->item.isWrong == itemoption->item.isWrongOrig)
    {
        if(itemoption->item.nType==TQuestionType::EText)
            iswrong = 2;//未改动，不标�?        else
            iswrong = itemoption->item.isWrong;
    }
	else
		iswrong = itemoption->item.isWrong;

	pItem->SetAttribute("iswrong", iswrong);

	int flag = 2;
	if(pItem->QueryIntAttribute("flag", &flag) != TIXML_SUCCESS)
	{
		flag = 2;
		pItem->SetAttribute("flag", flag);
	}

	if(iswrong == 0 || iswrong == 1 || flag == 0 || flag == 1)
		return CMQuestionhandler::SetAnswerItem(itemoption, pItem);
	else
		return FALSE;
}

void CMWrongQuestion::DoGetWrongQuestion(const char *sID)
{
    ;
}

BOOL CMWrongQuestion::DoLastUpdate(int lasttime)
{
    return TRUE;
}

BOOL CMWrongQuestion::ClearAnswer()
{
    BOOL ret = FALSE;
    sqlite3* db = CheckTable();
    char* errorMsg;
    
    if (sqlite3_exec(db, "BEGIN TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("BEGIN TRANSACTION failed.error:%s", errorMsg);
    }
    
    SetCurIndex(0);
    
    for (int i = 0; i < GetItemCount(); i++) {
        TQuestion& qitem = m_lstItem->at(i);
        qitem.item.isChecked = FALSE;
        qitem.item.isRight = FALSE;
        qitem.item.sMyAnswer = "";
        qitem.item.sAnswer = "";
        sLastUpdate = 0;
        DoClearAnswer(qitem);
        ret = TRUE;
    }
    
    if (db != NULL && sqlite3_exec(db, "COMMIT TRANSACTION;", 0,0, &errorMsg) != SQLITE_OK)
    {
        CM_ERRP("COMMIT TRANSACTION failed.error:%s", errorMsg);
    }
    
    return ret;
}

BOOL CMWrongQuestion::UpdateWrongTime(int lasttime)
{
    return DoLastUpdate(lasttime);
}

BOOL CMWrongQuestion::DoClearAnswer(TQuestion &obj)
{
    return TRUE;
}

void CMWrongQuestion::Commit()
{
    DoCommit();
}

void CMWrongQuestion::DoCommit()
{
//	CMQuestionhandler::Commit(SERVICE_UPDATEQUESTION, "");
}


#include "stdafx.h"
#include "cmqalistupload.h"
#include "cmqalist.h"
#include "cmlist.h"
#include "cmfile.h"
#include "cmpath.h"
#include "tinyxml.h"
#include "cmglobal.h"
#include "cmgeneral.h"

CMQalistUpload*CMQalistUpload::m_pTHIS = NULL;

CMQalistUpload* CMQalistUpload::GetInstance()
{
	if(m_pTHIS == NULL)
	{
		m_pTHIS = new CMQalistUpload();
	}
	return m_pTHIS;
}

CMQalistUpload::CMQalistUpload()
{
	m_lstItem = NULL;
       m_pUpdateListener=NULL;
}

CMQalistUpload::~CMQalistUpload()
{
       m_pUpdateListener=NULL;
	SAFEDELETE(m_lstItem);
}


void CMQalistUpload::SetListener(IMUpdateDataListener* pListener)
{
    m_pUpdateListener = pListener;
}


void CMQalistUpload::Release()
{
	SAFEDELETE(m_pTHIS);
}

int CMQalistUpload::GetItemCount()
{
	if(m_lstItem)
		return m_lstItem->size();
	else
		return 0;
}

BOOL CMQalistUpload::GetItem(int nIndex, TQAItem& item)
{
	if(m_lstItem && nIndex >= 0 && nIndex < m_lstItem->size())
	{
		item = m_lstItem->at(nIndex);
		return TRUE;
	}
	else
		return FALSE;
}

int CMQalistUpload::Append(const TQAItem& tqa)
{
  INT32 nIndex = -1;
	if(m_lstItem)
	{
		nIndex = m_lstItem->indexOf(tqa);
        
		if(nIndex == -1)
		{
			m_lstItem->push_back(tqa);
			SaveToFile();
			nIndex = m_lstItem->size() - 1;
			Start(nIndex);
		}
	}
	return nIndex;
}

void CMQalistUpload::Delete(int nImageIndex)
{
	if (m_lstItem && nImageIndex >= 0 &&nImageIndex< m_lstItem->size())
	{
		if (nImageIndex!= -1)
		{
			if (nImageIndex == m_nImageIndex)
			{
				Stop();
				m_lstItem->removeAt(nImageIndex );
				Start(nImageIndex );
			}
			else if (nImageIndex< m_nImageIndex)
			{
				m_lstItem->removeAt(nImageIndex);
				m_nImageIndex--;
			}
			else
			{
				m_lstItem->removeAt(nImageIndex);
			}
		}
		else
		{
			m_lstItem->removeAt(nImageIndex);
		}
		SaveToFile();
	}
}

BOOL  CMQalistUpload::Start(int nImageIndex)
{
if (m_lstItem &&nImageIndex>= 0 && nImageIndex < m_lstItem->size())
	{
        
		 m_nImageIndex= nImageIndex;
        
		TQAItem& info = m_lstItem->at(nImageIndex);
        
		//找到当前应该下载的课件
		 m_nImageIndex= -1;

		return TRUE;
     }
	return FALSE;
}

int CMQalistUpload::GetCurrent()
{
    return m_nImageIndex;
}

BOOL CMQalistUpload::IsComplete(int nImageIndex)
{
	if (m_lstItem &&nImageIndex>= 0 &&nImageIndex < m_lstItem->size())
	{
		TQAItem& info = m_lstItem->at(nImageIndex);
		if (nImageIndex >= m_pTHIS . GetItemCount()||nImageIndex< 0)
			return FALSE;
		TQAItem item;
		if (m_pTHIS .GetCourseware(nImageIndex , item))
		{
			return item.nFlag == 2;
		}
	}
	return FALSE;
}
int  CMQalistUpload::Status(int nImageIndex)
{
	if (m_lstItem && nImageIndex>= 0 && nImageIndex< m_lstItem->size())
	{
		const TQAItem& info = m_lstItem->at( nImageIndex);
        
		if (info.m_nStatus == 2)
		{
			return EStatusComplete;
		}
		}
	
	return EStatusError;
}

void CMQalistUpload::OnUpload(unsigned int nCode)
{
	if (nCode == MER_OK)
	{
		TQAItem& info = m_lstItem->at( nImageIndex);
		if (info.m_nStatus == 0)
			info.m_nStatus = 1;
        
		if (m_nImageIndex< m_pTHIS .GetItemCount())
		{
			TQAItem item;
			m_pTHIS.GetItem(m_nImageIndex, item);
		}
		else
		{
			info.m_nStatus = 2;
            
			if (m_nImageIndex< m_lstItem->size() - 1)
			{
				//继续下一个
				m_nImageIndex++;
				Start(m_nImageIndex);
			}
			else
			{
				//全部下载完成
				m_nImageIndex= -1;
			}
		}
        
        if(m_pUpdateListener)
            m_pUpdateListener->OnUpdateDataFinish(m_UserData, 1);
		SaveToFile();
		return;
	}
}

BOOL  CMQalistUpload::IsUpwloaded(const TQAItem& item)
{
	for (int i = 0; i < GetItemCount(); i++)
	{
		TQAItem citem;
                if(citem.nFlag==2)
                    return TRUE;
                else
                    return FALSE;
                
       }
    return FALSE;
}
BOOL CMQAList::DoCreate(sqlite3* db)
{
	if (db == NULL)  return FALSE;
	if (strcmp(m_tablename, "") == 0) return FALSE;

	char *errorMsg;
	char sql[512];
	snprintf(sql,sizeof(sql),"CREATE TABLE IF NOT EXISTS %s(_id INTEGER PRIMARY KEY AUTOINCREMENT,id TEXT,question TEXT,questioner_username TEXT,questioner_fullname TEXT,questioner_icon TEXT,pubdate TEXT,vc INTEGER,pv INTEGER,answercount INTEGER,value INTEGER,attention INTEGER,isresolved INTEGER,category TEXT)", m_tablename);


	if (sqlite3_exec(db, sql, NULL, NULL, &errorMsg)==SQLITE_OK) {
		return TRUE ;
	}
	else
	{
		CM_ERRP("exec %s failed.error:%s", sql, errorMsg);
		return FALSE;
	}

}
void CMQalistUpload::SaveToFile()
{

}

void CMQalistUpload::LoadFromFile()
{

}




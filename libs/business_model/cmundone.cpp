//
//  cmundone.cpp
//  MLPlayer
//
//  Created by hushengwu on 14/11/17.
//  Copyright (c) 2014年 w. All rights reserved.
//

#include "cmundone.h"
#include "cmsession.h"
#include "cmmyinfo.h"
#include "cmcategory.h"

CMUnDone* CMUnDone::m_pTHIS = NULL;

TUnDoneItem::TUnDoneItem()
{
	nItemCount = 0;
}

TUnDoneItem::~TUnDoneItem()
{

}

CMUnDone* CMUnDone::GetInstance()
{
    if(m_pTHIS == NULL)
        m_pTHIS = new CMUnDone();
    return m_pTHIS;
}

CMUnDone::CMUnDone():CMHandler<TUnDoneItem>()
{
    m_lstItem = new CMList<TUnDoneItem>;
    
}

CMUnDone::~CMUnDone()
{

}

void CMUnDone::SetListener(IMUpdateDataListener *pListener)
{
    m_pSimpleListener = pListener;
}

BOOL CMUnDone::GetUnDone()
{
    if(m_pSession == NULL)
        m_pSession = new CMSession(this);
    
    if(IsRunning())
        return FALSE;
    
   	return Request(SERVICE_GETUNDONE, "");

}


void CMUnDone::OnSessionCmd(unsigned int nCmdID, unsigned int nCode, tinyxml::TiXmlDocument *pDoc)
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
            if (nErr == 0 && nCmdID == SERVICE_GETUNDONE)
            {
                if (m_lstItem) {
                    m_lstItem->clear();
                }
                pItem = pItem->FirstChildElement();
                const char* pstr = NULL;
                while (pItem)
                {
                    TUnDoneItem item;
                    pstr = pItem->Attribute("type");
                    if (pstr) {
                        item.sType = pstr;
                    }
                   	pItem->QueryIntAttribute("itemcount",&item.nItemCount);
                    
                    //更新个人信息相关数据
                    if (strcasecmp(item.sType.c_str(), "positioncoursecount") == 0) {
                        CMMyInfo::GetInstance()->SetPositionCourseCount(item.nItemCount);
                    }
                    else if(strcasecmp(item.sType.c_str(), "studyrecord") == 0){
                        CMMyInfo::GetInstance()->SetStudyrecord(item.nItemCount);
                    }
//                    else if(strcasecmp(item.sType.c_str(), "exam") == 0){
//                    	CMCategory::GetInstance()->SetExamSurveyCount(item.nItemCount, item.sType.c_str());
//                    }
                    else{
                        //更新200协议里的测验，调研未完成数目
                        CMCategory::GetInstance()->SetExamSurveyCount(item.nItemCount, item.sType.c_str());
                       
                    }
                    
                    m_lstItem->push_back(item);
                    
                    pItem = pItem->NextSiblingElement("item");

                }
                
                if (m_lstItem->size() > 0) {
                    result = TResult::ESuccess;
                }
                else
                    result = TResult::ENothing;
                
            }
            else
                result = TResult::EProtocolFormatError;
        }
        else
            result = TResult::EUnknownError;
        
    }
    else if (nCode == MERN_OFFLINE)
    {
        result = TResult::ENotSupportOffline;
    }
    else if(nCode == MERN_INITIALIZE)
        result = TResult::ENetDisconnect;
    else
        result = TResult::ENetTimeout;
    
    if(m_pSimpleListener)
        m_pSimpleListener->OnUpdateDataFinish(m_UserData, result);
}


//缓存建表
BOOL CMUnDone::DoCreate(sqlite3* db)
{
    return FALSE;

}

//网络回来数据，要入缓存并刷新对象
BOOL CMUnDone::DoPutItem(TiXmlElement* pItem, sqlite3* db, TUnDoneItem& item)
{
    return FALSE;

}

//缓存回来数据，读取缓存到对象列表
BOOL CMUnDone::DoGetCacheItems(sqlite3* db)
{
    return FALSE;

}

//从缓存更新对象，根据哪个属性确定并更新对象由T实现决定
BOOL CMUnDone::DoRefresh(TUnDoneItem& obj)
{
    return FALSE;

}

//更新缓存，一般先GetItem或者Refresh后，修改，再Update
BOOL CMUnDone::DoUpdate(const TUnDoneItem& obj)
{
    return FALSE;
}

//清除内存以及缓存里的相关数据
void CMUnDone::DoClear()
{
   
}






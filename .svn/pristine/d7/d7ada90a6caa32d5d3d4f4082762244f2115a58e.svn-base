// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.

//  获取专题课程

//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMSPECIALTOPIC_H_HEADER_INCLUDED_B19A5625
#define CMSPECIALTOPIC_H_HEADER_INCLUDED_B19A5625
#include "cmcontenthandler.h"

class CMSpecialTopic : public CMContenthandler
{
  public:
    CMSpecialTopic(IMUpdateDataListener* pListener);

    virtual ~CMSpecialTopic();

    // 调用父类Request方法
    void GetSpecialTopic(const char* sID);
	
	const char* GetTitle();

	const char* GetImage();

  protected:
	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
    virtual BOOL DoCreate(sqlite3 * db);
    
    virtual void DoClear();
    
//    virtual BOOL DoRefresh();
//    
//    virtual BOOL DoUpdate();
    
    virtual BOOL DoGetCacheItems(sqlite3 * db);
    
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TBrowserItem*& item);


  private:
	char m_sTitle[100];

    char m_sImage[300];
    
    char sParentSpecId[64];
    
};



#endif /* CMSPECIALTOPIC_H_HEADER_INCLUDED_B19A5625 */

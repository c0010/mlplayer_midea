// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMSEARCH_H_HEADER_INCLUDED_B19B1A23
#define CMSEARCH_H_HEADER_INCLUDED_B19B1A23

#include "cmcontenthandler.h"

class CMSearch:public CMContenthandler
{
  public:
    CMSearch(IMUpdateDataListener* pListener);

    virtual ~CMSearch();

    BOOL Search(const char* sFlag, const char* skey);
    
    BOOL QuickSearch(const char* sFlag, const char* skey);
    
    BOOL CategorySearch(const char* sFlag, const char* categoryID, const char* categoryTitle);  //分类搜索,保存分类名

	int GetRecentKeyCount();

	const char* GetRecentKeyItem(int nIndex);//返回临时指针，不得保存延后使用

private:

	CMList<char*>* m_lstKey;

	BOOL LoadKey();
	void SaveKey(const char* skey);
};



#endif /* CMSEARCH_H_HEADER_INCLUDED_B19B1A23 */

// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMFAVORITES_H_HEADER_INCLUDED_B19A444B
#define CMFAVORITES_H_HEADER_INCLUDED_B19A444B

#include "cmcontenthandler.h"

class CMFavorites : public CMContenthandler
{
public:
    static CMFavorites* GetInstance();

    virtual ~CMFavorites();

    BOOL RemoveItem(int nIndex);

    void SetListener(IMUpdateDataListener* pListener);
    // 加一项收藏到收藏列表顶部，返回值：0失败，1成功，2已收藏
//    int AddFavorite(const TBrowserItem& item);
    int AddFavorite(const TBrowserItem& item);

    // 是否已收藏 -1未收藏；>=0为收藏位置，不固定
    int IsAdded(const char* sFlag, const char* sid);
    
    BOOL LoadFromDB();

//    friend class CMDBHelper;
    
protected:
    CMFavorites();
	void SaveToFile();
    
//	// 从本地文件装载，每用户保存一个文件。内部处理调用父类DoItemList方法
//    BOOL Load();
    
    // 从数据库装载，每用户保存一个文件。内部处理调用父类DoItemList方法

  //  virtual BOOL DoCreate(sqlite3 *db);

protected:
    friend class CMDBHelper;

    virtual void DoClear();
    
  private:
    static CMFavorites* m_pTHIS;	
    int IsInDB(const TBrowserItem& item);
};



#endif /* CMFAVORITES_H_HEADER_INCLUDED_B19A444B */

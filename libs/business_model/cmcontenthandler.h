// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMCONTENTHANDLER_H_HEADER_INCLUDED_B19A5307
#define CMCONTENTHANDLER_H_HEADER_INCLUDED_B19A5307

#include "cmcommon.h"
#include "cmdbhelper.h"
#include "cmhandler.h"
#include "cmmutex.h"

#define kCourseTable  "courseAll"

template <typename T> class CMList;

class CMContenthandler:public CMHandler<TBrowserItem*>
{
  public:
    CMContenthandler();
  
    virtual ~CMContenthandler();

	/**
	 *	得到头条item数量
	 *
	 *	@param
	 *
	 *	@return
	 */
	int GetHeadItemCount();
    
    
    /**
     *	得到头条item
     *
     *	@param	nIndex	item在list中的index
     *	@param	item	要赋值的item,操作完后，数据在此item中
     *
     *	@return
     */
    BOOL GetHeadItem(int nIndex, TBrowserItem*& item);
    
    
    BOOL Rating(const char* sID);
    
    BOOL RatingCourseinfo(const char* CoursewareID); //课件喜欢
    
    void SetListener(IMUpdateDataListener* pListener, IMRatingListener* pRatingListener);
    
    int GetItemModel(int nIndex);
    
    int GetHeadItemModel(int nIndex);

  protected:
    
//    CMContenthandler& operator=(const CMContenthandler& right);

	CMList<TBrowserItem*>* m_lstHeadItem;
    
    /**
     *	http回调方法
     *
     *	@param	nCmdID	请求接口号
     *	@param	nCode	返回参数
     *	@param	pDoc	返回的xml
     */
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

    
    /**
     *	处理网络传回的数据
     *
     *	@param	pItem	传回的xml
     *	@param	db	可操作的数据库指针
     *	@param	item	要接受处理的item,处理后数据存入其中
     *
     *	@return
     */
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TBrowserItem*& item);
    
    //GetItem的扩展实现，这是实现的目的是实现指针对象拷贝
    virtual BOOL DoGetItem(int nIndex, TBrowserItem*& item);

    /**
     *	获得数据库中缓存的数据
     *
     *	@param	db	数据库指针
     *
     *	@return
     */
    virtual BOOL DoGetCacheItems(sqlite3* db);
    
    
    /**
     *	更新数据库和内存中的数据
     *
     *	@param	obj	需要更新的item
     *
     *	@return
     */
    virtual BOOL DoRefresh(TBrowserItem*& obj);
    
    /**
     *	用数据库数据刷新item
     *
     *	@param	obj	要刷新数据的item
     *
     *	@return
     */
    virtual BOOL DoUpdate(TBrowserItem* const & obj);
    
    /**
     *	建立表
     *
     *	@param	db	可操作的数据库指针
     *
     *	@return
     */
    virtual BOOL DoCreate(sqlite3* db);
    
    /**
     *	清空list数据和数据库中的数据
     *
     *	@param
     */
    virtual void DoClear();
    
    
    BOOL m_bRatting;
    
    char ratingID[64];
    
    IMRatingListener* m_pRatingListener;

    static BOOL DoSaveTBrowseitem(sqlite3* db, TBrowserItem&item);

    static BOOL DoGetTBrowseitem(sqlite3* db,const char* id, TBrowserItem&item);

  private:

	friend class CMGetNewContent;
	friend class CMCourseInfo;
};



#endif /* CMCONTENTHANDLER_H_HEADER_INCLUDED_B19A5307 */

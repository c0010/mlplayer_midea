/*
 * cmpushmsg.h
 *
 *  Created on: 2015年5月25日
 *      Author: Administrator
 */

#ifndef CMPUSHMSG_H_
#define CMPUSHMSG_H_

#include "cmhandler.h"
#include <string>

using namespace std;

class TPushItem
{
public:
	TPushItem();
	~TPushItem();

	string sID;

	string sMsg;

	string sType;

	string sKey;

	string sPubDate;

	BOOL bIsRead;

protected:
	friend class CMPushMsg;

	void fetchItem(sqlite3_stmt* stmt);

	void bindItem(sqlite3_stmt* stmt ) const;

};

class CMPushMsg : public CMHandler<TPushItem>
{
public:

	static CMPushMsg* GetInstance();


	virtual ~CMPushMsg();

	void SetListener(IMUpdateDataListener* pListener);

	/**
	 * 加入消息盒子
	 */
	BOOL AddPushMsg(const TPushItem& item);

	/**
	 * 读取缓存
	 */
	BOOL LoadFromDB();

	/**
	 * 清除内存数据
	 */
	BOOL Clear();

	/**
	 * 清除内存和缓存数据
	 */
	BOOL ClearCache();

	/**
	 * 移除数据
	 */
	BOOL RemoveItem(int nIndex);

	/**
	 * 获取未读消息数量
	 */
	int GetUnReadCount();

protected:
	virtual BOOL DoGetCacheItems(sqlite3* db);

	virtual BOOL DoRefresh(TPushItem& obj);

	virtual BOOL DoUpdate(const TPushItem& obj);

	virtual BOOL DoCreate(sqlite3* db);

	virtual void DoClear();

private:
	CMPushMsg();

	static CMPushMsg* m_pTHIS;

};

#endif /* CMPUSHMSG_H_ */

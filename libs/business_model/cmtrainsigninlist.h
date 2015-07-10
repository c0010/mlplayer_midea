/*
 * cmtrainapplylist.h
 *
 *  Created on: 2014年12月15日
 *      Author: Administrator
 */

#ifndef CMTRAINSIGNINLIST_H_
#define CMTRAINSIGNINLIST_H_

#include "cmcommon.h"
#include "cmhandler.h"
#include <string>
using namespace std;

class TTrainSignInItem : public IMNotifySession
{
public:

	TTrainSignInItem();
	~TTrainSignInItem();

	string sID;//签到id
	string sTitle;//标题
	string sTrainID;//培训班id
	string sImageURL;//培训签到 图片  备用
	string sTime;//签到时段
	string sAddress;//签到地点
	string sSignInTime;// 已签到情况下   用户的签到时间
	string sFlag;//分类标识  nosignin signin
	int nMode;//已报名情况下  用户的报名时间
	int nSignInNum;//以签到人数

	BOOL Update();
	BOOL Refresh();

	//根据id请求培训签到详情
	BOOL RequestInfo();

	BOOL SignInTrain();

	void SetListener(IMUpdateDataListener* pUpdateDataListener,IMSimpleResultListener* pSimpleResultListener);

	void SetUserData(void* userdata);

	void Cancel();

	TTrainSignInItem& operator=(const TTrainSignInItem& right);

protected:
	friend class CMTrainSignInList;

	friend class CMGetNewContent;

	TTrainSignInItem& operator=(const TiXmlElement* right);

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

	CMSession *m_pSession;

	IMUpdateDataListener* m_pListener;

	IMSimpleResultListener* m_sListener;

	void*    m_UserData;

	BOOL m_bUpdateData;

	void fetchItem(sqlite3_stmt* stmt);

	void bindItem(sqlite3_stmt* stmt) const;

	int BindParam(sqlite3_stmt* stmt,int col,int value) const;

	int BindParam(sqlite3_stmt* stmt,int col,const char* value) const;

	int BindParam(sqlite3_stmt* stmt,int col,float value) const;

};


class CMTrainSignInList : public CMHandler<TTrainSignInItem>
{
public:
	CMTrainSignInList();

	virtual ~CMTrainSignInList();

	void SetListener(IMUpdateDataListener* m_pListener);

	BOOL RequestTrainApplyList(const char* mFlag);

	BOOL RemoveSuccessItem(int nIndex);

protected:
	//缓存建表
	virtual BOOL DoCreate(sqlite3* db) ;
	//网络回来数据，要加入缓存并刷新对象
	virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TTrainSignInItem& item) ;
	//清除内存以及缓存里的相关数据
	virtual void DoClear();

};

#endif /* CMTRAINAPPLYLIST_H_ */

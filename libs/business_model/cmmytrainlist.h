/*
 * cmtrainapplylist.h
 *
 *  Created on: 2014年12月15日
 *      Author: Administrator
 */

#ifndef CMMYTRAINLIST_H_
#define CMMYTRAINLIST_H_

#include "cmcommon.h"
#include "cmhandler.h"
#include <string>

using namespace std;

class TMyTrainItem : public IMNotifySession
{
public:

	TMyTrainItem();
	~TMyTrainItem();

	string sID;//培训班id
	string sTitle;//标题
	string sIcon;//图标
	string sTrainNumber;//编号
	string sMode;//培训方式  面授
	string sTrainTime;// 培训时间
	int nUserCount;//成员数量
	string sDesc;//培训内容
	string sRemark;//备注
	string sRoomID;//聊天室id
	string sRoomJID;//聊天室jid
	string sRoomPwd;//聊天室密码
	string sTabList;//栏位信息
	string sAddress;//培训地点

	BOOL Update();
	BOOL Refresh();

	//根据id请求培训报名详情
	BOOL RequestInfo();

	void SetListener(IMUpdateDataListener* pUpdateDataListener,IMSimpleResultListener* pSimpleResultListener);

	void SetUserData(void* userdata);

	void Cancel();

	TMyTrainItem& operator=(const TMyTrainItem& right);

protected:
	friend class CMMyTrainList;

	friend class CMGetNewContent;

	TMyTrainItem& operator=(const TiXmlElement* right);

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

	CMSession *m_pSession;

	IMUpdateDataListener* m_pListener;

	IMSimpleResultListener* m_sListener;

	void*    m_UserData;

	void fetchItem(sqlite3_stmt* stmt);

	void bindItem(sqlite3_stmt* stmt) const;

	int BindParam(sqlite3_stmt* stmt,int col,int value) const;

	int BindParam(sqlite3_stmt* stmt,int col,const char* value) const;

	int BindParam(sqlite3_stmt* stmt,int col,float value) const;

};


class CMMyTrainList : public CMHandler<TMyTrainItem>
{
public:
	CMMyTrainList();

	virtual ~CMMyTrainList();

	void SetListener(IMUpdateDataListener* m_pListener);

	BOOL RequestTrainApplyList();

protected:
	//缓存建表
	virtual BOOL DoCreate(sqlite3* db) ;
	//网络回来数据，要加入缓存并刷新对象
	virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TMyTrainItem& item) ;
	//清除内存以及缓存里的相关数据
	virtual void DoClear();

};

#endif /* CMTRAINAPPLYLIST_H_ */

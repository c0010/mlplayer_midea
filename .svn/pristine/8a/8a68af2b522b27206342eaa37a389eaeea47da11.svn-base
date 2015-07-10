/*
 * cmtrainapplylist.h
 *
 *  Created on: 2014年12月15日
 *      Author: Administrator
 */

#ifndef CMTRAINAPPLYLIST_H_
#define CMTRAINAPPLYLIST_H_

#include "cmcommon.h"
#include "cmhandler.h"
#include <string>
using namespace std;

class TTrainApplyItem : public IMNotifySession
{
public:

	TTrainApplyItem();
	~TTrainApplyItem();

	string sID;//报名id
	string sTitle;//标题
	string sTrainID;//培训班id
	string sImageURL;//培训报名 图片  备用
	string sTrainTime;//培训时段
	string sApplyTime;//报名时段
	string sAddress;//培训地点
	string sFlag;//分类标识 未报名 已报名  已结束
	string sDesc;//简介
	string sAppliedTime;//已报名情况下  用户的报名时间
    string sPlanPerson; //计划人数
    int nEnableApply;//是否能报名 0 报名人数已满 1 可以报名
	int nEnableCancelApply;//是否可取消报名 0 不可以  1可以
	int  nIsPass;//审核信息 0:正在审核 1:审核通过 2:审核不通过
	int nAppliedNum;//报名人数
	BOOL Update();
	BOOL Refresh();

	//根据id请求培训报名详情
	BOOL RequestInfo();

	//报名
	BOOL Apply();
	//取消报名
	BOOL CancelApply();


	void SetListener(IMUpdateDataListener* pUpdateDataListener,IMSimpleResultListener* pSimpleResultListener);

	void SetUserData(void* userdata);

	void Cancel();

	virtual TTrainApplyItem& operator=(const TTrainApplyItem& right);

protected:
	friend class CMTrainApplyList;

	friend class CMGetNewContent;

	virtual TTrainApplyItem& operator=(const TiXmlElement* right);

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


class CMTrainApplyList : public CMHandler<TTrainApplyItem>
{

public:
	CMTrainApplyList();

	virtual ~CMTrainApplyList();

	void SetListener(IMUpdateDataListener* m_pListener);

	BOOL RequestTrainApplyList(const char* mFlag);

	BOOL RemoveSuccessItem(int nIndex);
protected:
	//缓存建表
	virtual BOOL DoCreate(sqlite3* db) ;
	//网络回来数据，要加入缓存并刷新对象
	virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TTrainApplyItem& item) ;
	//清除内存以及缓存里的相关数据
	virtual void DoClear();

};

#endif /* CMTRAINAPPLYLIST_H_ */

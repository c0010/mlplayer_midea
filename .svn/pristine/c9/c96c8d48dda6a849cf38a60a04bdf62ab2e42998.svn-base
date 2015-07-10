// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMCUSTOMERLIST_H_HEADER_INCLUDED_B235FC36
#define CMCUSTOMERLIST_H_HEADER_INCLUDED_B235FC36

#include "cmcommon.h"

template <typename T> class CMList;

class TCustomerListItem
{
  public:
    char sID[100];

    char sName[100];

    char sServer[100];

	BOOL bcheck;
};

class CMCustomerList:public IMNotifySession
{
  public:
    CMCustomerList(IMUpdateDataListener* pListener);

    ~CMCustomerList();

    void SetUserData(void* UserData);

    // 异步方法，获取调研问卷列表
    void GetList();
	
	void GetList(const char* skey);
	
    int GetItemCount();

    BOOL GetItem(int nIndex, TCustomerListItem& item);	
		//设置客户服务器地址
		//sName：客户名称
		//sUrl：客户服务器地址
    void SetServerUrl(char* sName, char* sUrl);
    
		//得到客户名称
		//返回值： TRUE返回设置的客户名称，FALSE没有设置过客户服务器地址
    BOOL GetCustomerName(char* sName, int nBufLen);
	
  private:
   	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
   
    IMUpdateDataListener* m_pListener;

    void* m_UserData;
	CMSession* m_pSession;
	CMList<TCustomerListItem>*	m_lstCustomerListItem;

};



#endif /* CMCUSTOMERLIST_H_HEADER_INCLUDED_B235FC36 */

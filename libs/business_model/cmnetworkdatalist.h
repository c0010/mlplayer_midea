// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMNETWORKDATALIST_H_HEADER_INCLUDED_B17FAB0B
#define CMNETWORKDATALIST_H_HEADER_INCLUDED_B17FAB0B

#include "cmcommon.h"

template <typename T> class CMList;

template <typename T>
class CMNetworkDataList : public IMNotifySession
{
  public:

    virtual ~CMNetworkDataList();

    void SetUserData(void* UserData);

    void SetPaging(BOOL bPaging);

    BOOL RequestMore();

    void Cancel();

    int GetItemCount();

    BOOL GetItem(int nIndex, T& item);

	BOOL IsEnd();
	
	BOOL IsRunning();
  protected:
	void CompileTemplate() {
		this->SetUserData(NULL);
		this->SetPaging(FALSE);
		this->RequestMore();
		this->Cancel();
		this->GetItemCount();
		T t;
		this->GetItem(0, t);
	}

    CMNetworkDataList(IMUpdateDataListener* pListener);

	void Clear();

    BOOL Request(int nServiceNo, const char* sParam);

    virtual BOOL DoItem(TiXmlElement* pItem, T& item) = 0;

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
	//直接返回list供应用层使用
	CMList<T>* GetList();

	void* m_UserData;
	
	CMSession* m_pSession;

	IMUpdateDataListener *m_pListener;

  private:

   BOOL CurrentRequest(const char* param,int pageno,int pagesize);

    BOOL m_bPaging;

    CMList<T>* m_lstItem;

	//为分页使用
	int m_nPageNo;
	int m_nPageSize;
    int m_nTotalCount;

	int  m_nServiceNo;
	char m_sParam[1800];

};

#include "cmnetworkdatalist.cpp"

#endif /* CMNETWORKDATALIST_H_HEADER_INCLUDED_B17FAB0B */

// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMSEARCHHOTKEY_H_HEADER_INCLUDED_B235FB61
#define CMSEARCHHOTKEY_H_HEADER_INCLUDED_B235FB61
#include "cmcommon.h"

template <typename T> class CMList;

class CMSearchHotKey:public IMNotifySession
{
  public:
	static CMSearchHotKey* GetInstance();

    virtual ~CMSearchHotKey();

    void SetListener(IMUpdateDataListener* pListener);

    void SetUserData(void* UserData);

    //获取热词
    BOOL GetHotKey();

	//课程热词
    int GetCourseHotKeyItemCount();
	
	const char* GetCourseHotKeyItem(int nIndex);
	
	//资讯热词
	int GetNewsHotKeyItemCount();
	
	const char* GetNewsHotKeyItem(int nIndex);
	
	//问答热词
	int GetQaHotKeyItemCount();
	const char* GetQaHotKeyItem(int nIndex);

  protected:
	CMSearchHotKey();

  private:
	static CMSearchHotKey* m_pTHIS;

	int GetItemCount(const char* sflag);
	const char* GetItem(const char* sflag,int nIndex);
	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
	void Clear();
  private:
	struct THotKey
	{
		char		flag[100];
		CMList<char*>* m_lstItem;
	};
    
	IMUpdateDataListener* m_pListener;

    void* m_UserData;
		
	CMList<THotKey*>* m_lstHotKey;

	CMSession* m_pSession;
};



#endif /* CMSEARCHHOTKEY_H_HEADER_INCLUDED_B235FB61 */

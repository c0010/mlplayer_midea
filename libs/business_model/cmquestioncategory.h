// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMQUESTIONCATEGORY_H_HEADER_INCLUDED_B1865D3B
#define CMQUESTIONCATEGORY_H_HEADER_INCLUDED_B1865D3B

#include "cmcommon.h"

class CMQuestionCategoryItem;
template <typename T> class CMList;

class CMQuestionCategory : public IMNotifySession
{
  public:
    CMQuestionCategory(IMUpdateDataListener* pListener);

    virtual ~CMQuestionCategory();

    void SetUserData(void* UserData);

    BOOL Update();

    void CancelUpdate();

    int TopItemCount();

    CMQuestionCategoryItem* GetTopItem(int nIndex);

  private:
    void* m_UserData;

    CMList<CMQuestionCategoryItem*> *m_lstCategoryItem;

    IMUpdateDataListener *m_pListener;

	CMSession* m_pSession;

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

	void Clear(CMList<CMQuestionCategoryItem*>* plist);

	void CycParser(TiXmlElement *pItem, CMQuestionCategoryItem* pfather);

};

class CMQuestionCategoryItem
{
  public:
    CMQuestionCategoryItem();

    virtual ~CMQuestionCategoryItem();

    int ChildItemCount();

    CMQuestionCategoryItem* GetChildItem(int nIndex);

    char sID[64];

    char sTitle[100];

    int nQuestioncount;

    int nUncompletecount;

    int nWrongcount;

	friend class CMQuestionCategory;
  private:
    CMList<CMQuestionCategoryItem*> *m_lstCategoryItem;

};

#endif /* CMQUESTIONCATEGORY_H_HEADER_INCLUDED_B1865D3B */

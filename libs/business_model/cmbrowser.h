// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMBROWSER_H_HEADER_INCLUDED_B19B17D3
#define CMBROWSER_H_HEADER_INCLUDED_B19B17D3

#include "cmcontenthandler.h"
#include "cmcommon.h"

class CMBrowser : public CMContenthandler
{
public:
    CMBrowser(IMUpdateDataListener* pListener);
    

    virtual ~CMBrowser();

    BOOL Request(const char* sFlag, const char* sID);

    BOOL RequestPisitionCourse();
    BOOL RequestMarkClass(const char* markID);
    BOOL RequestCoursewareById(const char* coursewareID);

    BOOL RequestNewsById(const char* newsID);
    
    /**
     *获取培训班下的课程资讯
     */
    BOOL RequestTrain(const char* sFlag, const char* sTrainID);

    /**
     * 获取关联课程/资讯top sFlag:course or news
     */
    BOOL RequestTop(const char* sFlag,const char* sBrowerID);

protected:
    
    CMBrowser& operator=(const CMBrowser& right);

    
    void DoClearList();

    
    virtual BOOL DoCreate(sqlite3 * db);
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TBrowserItem*& item);
    virtual void DoClear();
    
    virtual BOOL DoGetCacheItems(sqlite3* db);

    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);


    
private:
    char sCategoryID[64];


};

#endif /* CMBROWSER_H_HEADER_INCLUDED_B19B17D3 */

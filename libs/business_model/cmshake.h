//
//  cmshake.h
//  MLPlayer
//
//  Created by wmgwd on 13-6-20.
//  Copyright (c) 2013定 w. All rights reserved.
//

#ifndef __MLPlayer__cmshake__
#define __MLPlayer__cmshake__


#include "cmcontenthandler.h"
#include "cmcommon.h"

class CMShake : public CMContenthandler
{
public:
    CMShake(IMUpdateDataListener* pListener);
    
    virtual ~CMShake();
    
    BOOL Request();
    
protected:
    
    virtual BOOL DoCreate(sqlite3* db);
    virtual void DoClear();
    virtual BOOL DoGetCacheItems(sqlite3* db);
    
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
private:

    char sCategoryID[64];
};


#endif /* defined(__MLPlayer__cmshake__) */

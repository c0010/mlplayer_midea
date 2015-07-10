// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2015,
//  All rights reserved.
//
//  FileName:
//  Description:网络Http层接口序列类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#ifndef MLPlayer_cmsessionsequence_h
#define MLPlayer_cmsessionsequence_h

#include "cmcommon.h"
#include <map>
#include <list>
#include "cmmutex.h"
using namespace std;

class CMSession;

class CMSessionSequence //: public IMNotifySession
{
public:
    static CMSessionSequence* GetInstance();
    
    BOOL Append(CMSession* pSession);
    BOOL Remove(CMSession* pSession);
    
private:
    map<string, list<CMSession*> > m_map;
    
  	static CMSessionSequence* m_pTHIS;
    
    CMMutex m_mutex;
    
//    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
};

#endif

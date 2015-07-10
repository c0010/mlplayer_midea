//
//  cmsessionMid.h
//  MLPlayer
//
//  Created by whf on 13-8-19.
//  Copyright (c) 2013. All rights reserved.
//

#ifndef CMSESSION_IPH_HEADER_INCLUDED_B249D7FB
#define CMSESSION_IPH_HEADER_INCLUDED_B249D7FB

#import "tinyxml.h"
#include "cmcommon.h"

class CMNotifySessionIos: public IMNotifySession {

public:
    CMNotifySessionIos(IMNotifySession* pNotify);
    
    virtual ~CMNotifySessionIos();
    
    void OnSessionCmd(unsigned int nCmdID,unsigned int nCode , TiXmlDocument* pDoc);
    
private:
    void* mid;

};


#endif

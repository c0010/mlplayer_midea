//
//  CMBrowser.m
//  MLPlayer
//
//  Created by water on 14-10-21.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMBrowserHandler.h"

@implementation CMBrowserHandler

+ (id)handler{
    return [[CMBrowserHandler alloc] init];
}

- (id)init
{
    self = [super init];
    if (self) {
       
        
        if(m_handlerListener == NULL)
            m_handlerListener = new CMBrowserHandlerListener();
               
    }
    return self;
}

- (void) initBrowser {
    
    if(m_browser == NULL)
        m_browser = new CMBrowser(m_handlerListener);
    
    m_browser->SetUserData((__bridge void*)self);
}

- (void) initExam {
    
    if(m_examlist == NULL)
        m_examlist = new CMExamList();
    
    m_examlist->SetListener(m_handlerListener);
    
    m_examlist->SetUserData((__bridge void*)self);
}

- (void)doRequestNewsById:(NSString *)newsId success:(HandlerSuccess)success failure:(HandlerFailure)failure{

    if (!newsId || [newsId isEqualToString:@""]) {
        return;
    }
    [self initBrowser];
    
    self.m_handlerSuccess = success;
    self.m_handlerFailure = failure;

    m_browser->RequestNewsById([newsId UTF8String]);
}

- (void)doRequestCoursewareById:(NSString *)wareId success:(HandlerSuccess)success failure:(HandlerFailure)failure{

    if (!wareId || [wareId isEqualToString:@""]) {
        return;
    }
    [self initBrowser];
    
    self.m_handlerSuccess = success;
    self.m_handlerFailure = failure;
    
    m_browser->RequestCoursewareById([wareId UTF8String]);
}

- (void)doRequestExamById:(NSString *)examId success:(HandlerExamListSuccess)success failure:(HandlerFailure)failure;
{
    
    if (!examId || [examId isEqualToString:@""]) {
        return;
    }
    
    [self initExam];
    
    self.m_handlerExamSuccess = success;
    self.m_handlerFailure = failure;
    
    m_examlist->GetExamById([examId UTF8String]);
}

- (void)doHandlerSuccess{

    if (self.m_handlerSuccess) {
        self.m_handlerSuccess(m_browser);
        self.m_handlerSuccess = nil;
    }
    if ( self.m_handlerExamSuccess ) {
        self.m_handlerExamSuccess(m_examlist);
        self.m_handlerExamSuccess = nil;
    }
}

- (void)doHandlerFailure:(int) errorCode{

    if (self.m_handlerFailure) {
        self.m_handlerFailure(errorCode);
        self.m_handlerFailure = nil;
    }
}

@end

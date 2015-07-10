//
//  cmcoursedownload_iph.m
//  MLPlayer
//
//  Created by 王浩沣 on 14-2-25.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "cmcoursedownload_iph.h"
#include "cmcoursedownload.h"


@interface cmcoursedownloadMid : NSObject{
    CMCourseDownload* m_pCourseDownload;
    
}

- (id)initWithCourseDownloadObj:(CMCourseDownload*)obj;
- (void)GoOnDownload_mid;
@end


@implementation cmcoursedownloadMid

- (id)initWithCourseDownloadObj:(CMCourseDownload*)obj
{
    self = [super init];
    if (self) {
        m_pCourseDownload = obj;
    }
    return self;
}

-(void)GoOnDownload_mid
{
    
    //主线程调用Cmcoursedownload中的GoOnDownload
    [self performSelectorOnMainThread:@selector(process) withObject:nil waitUntilDone:NO];

}

-(void)process
{
    if (m_pCourseDownload != NULL) {
        m_pCourseDownload->GoOnDownload();
    }
    
}

@end



void CMCourseDownload_Iph::GoOnDownload_iph()
{
    if(coursedownload_mid != nil)
        [(__bridge cmcoursedownloadMid*)coursedownload_mid GoOnDownload_mid];
}

CMCourseDownload_Iph::CMCourseDownload_Iph(CMCourseDownload* obj)
{
    if(obj == NULL)
    {
        CM_ERR("cmcoursedownload is null!");
    }
    
    coursedownload = obj;
    
    coursedownload_mid =  (__bridge_retained void *)[[cmcoursedownloadMid alloc]initWithCourseDownloadObj:obj];
}

CMCourseDownload_Iph::~CMCourseDownload_Iph()
{
    if(coursedownload_mid != nil)
        (__bridge cmcoursedownloadMid*)coursedownload_mid;
    
}


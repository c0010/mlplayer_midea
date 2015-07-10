//
//  CMNavgateItem.h
//  MLPlayer
//
//  Created by sunjj on 12-2-24.
//  Copyright 2012 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "cmbrowser.h"
#import "cmcourseinfo.h"
#import "cmglobal.h"
#include "utf8ncpy.h"
#import "cmhandler.h"


@protocol CMNavgateItemDelegate 

@required
-(CMContenthandler*)GetContenthandler;

@optional

-(CMContenthandler*)GetShakeContenthandler;

-(CMHandler<TCoursewareItem>)GetCourseDetailContenthandler;

@end


@interface CMNavgateItem : NSObject {

@public
    BOOL bIsShake;
    BOOL bIsPush;
    BOOL bAppStateIsBackground;
}
-(void) NavgateItem:(UIViewController*)control item:(TBrowserItem&)item;

@end

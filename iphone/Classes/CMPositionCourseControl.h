//
//  CMPositionCourseControl.h
//  MLPlayer
//
//  Created by sunjj on 13-7-15.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMPositionCourseView.h"
#import "CMViewController.h"

@interface CMPositionCourseControl : CMViewController<CMNavgateItemDelegate>
{
    
    CMPositionCourseView* controlview;
    
    
}
@property(nonatomic,strong)     CMPositionCourseView* controlview;


@end

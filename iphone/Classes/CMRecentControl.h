//
//  CMBrowserControl.h
//  MLPlayer
//
//  Created by sunjj on 11-9-27.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMRecentView.h"
#import "CMNavgateItem.h"

@interface CMRecentControl : CMViewController<CMNavgateItemDelegate>{
	CMRecentView* recentview;
}
@end

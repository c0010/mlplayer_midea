//
//  CMBufferTimeControl.h
//  MLPlayer
//
//  Created by sunjj on 11-7-12.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "cmsettings.h"

@interface CMSettingCommControl : CMViewController<UITableViewDelegate,UITableViewDataSource> {
	UITableView* tableViews;
	NSString* m_type;
}
-(void)setSettingType:(NSString*)type;

@property(nonatomic,strong) UITableView *tableViews;


@end

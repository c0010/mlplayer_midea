//
//  CMHomeControl.h
//  MLPlayer
//
//  Created by sunjj on 11-8-18.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "cmcommon.h"
#import "CMImage.h"
#import "CMQListView.h"
#import "CMViewController.h"

@interface CMQContentControl: CMViewController {
	
	CMQListView* qlistview;
	NSString* category;
} 
@property(nonatomic,strong)NSString* category;
@property(nonatomic,strong)CMQListView* qlistview;
-(void)onAppFocus:(BOOL)isForeground;
@end
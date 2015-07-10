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

@interface CMQaSearchControl: CMViewController<UISearchBarDelegate> {
	
	UISearchBar* searchbar;
	CMQListView* qlistview;
	UILabel *lbltxt;
	
	MLPlayerAppDelegate *appDelegate;
} 
@property(nonatomic,strong)CMQListView* qlistview;
@property(nonatomic,copy)UILabel *lbltxt;
@property(nonatomic,strong)NSString* key;
-(void)onAppFocus:(BOOL)isForeground;
@end
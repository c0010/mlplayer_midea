//
//  CMSearchControl.m
//  OCplusplus
//
//  Created by sunjj on 11-4-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
// 搜索

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMSearchView.h"
#import "SuggestionsList.h"
#import "CMNavgateItem.h"
@interface CMSearchControl :CMViewController <UISearchBarDelegate,PassValueDelegate,CMNavgateItemDelegate>{

	UISearchBar *searchBar;
	UIView *myGroundView;
	CMSearchView* searchview;
	SuggestionsList *suggList;
	
	NSMutableArray* autoarray;
    BOOL isCategorySearch;
}
@property (nonatomic,copy)   NSString * type;
@property (nonatomic,copy)   NSString * key;
@property (nonatomic,copy)   NSString * title;
@property (nonatomic,assign) BOOL       isCategorySearch;
-(void)gotoSearch:(NSString *)value;
-(void)hidKeyBoard;
-(void)setSugestListHidden:(BOOL)hidden;
-(NSMutableArray*)GetAutoList;
@end


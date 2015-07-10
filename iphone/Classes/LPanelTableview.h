//
//  LPanelTableview.h
//  MLPlayer
//
//  Created by hfwang on 13-3-11.
//  Copyright 2013 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>



@interface LPanelTableview : UIView <UITableViewDelegate,UITableViewDataSource>{
	
	UITableView * _mytableview;	
	NSMutableArray * _dataArray;
	NSInteger  _selected;
	
}


@property(nonatomic,strong)		UITableView * mytableview;
@property(nonatomic,copy) 	NSMutableArray * dataArray;
@property(nonatomic,assign)   	NSInteger  selected;

+(LPanelTableview *)sharedLpanel;
@end

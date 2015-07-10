//
//  UIAlertTableView.h
//  AlertTable
//
//  Created by gao guilong on 10-5-21.
//  Copyright 2010 encompass. All rights reserved.
//

//
//  UIAlertTableView.h
//  UIAlertTableView
//
//  Created by Marc Ammann on 7/15/09.
//  Copyright 2009 Codesofa. All rights reserved.
//

#import <UIKit/UIKit.h>

@class UIAlertView;

@interface UIAlertTableView : UIAlertView {
	// The Alert View to decorate
    UIAlertView *alertView;
	
	// The Table View to display
	UITableView *tableView;
	
	// Height of the table
	int tableHeight;
	
	// Space the Table requires (incl. padding)
	int tableExtHeight;
	
	id<UITableViewDataSource> dataSourceS;
	id<UITableViewDelegate> tableDelegate;
}

@property (nonatomic, assign) id dataSourceS;
@property (nonatomic, assign) id tableDelegate;

@property (nonatomic, readonly) UITableView *tableView;
@property (nonatomic, assign) int tableHeight;

- (void)prepare;

@end


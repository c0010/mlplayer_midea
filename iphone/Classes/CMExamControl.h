//
//  CMExamControl.h
//  MLPlayer
//
//  Created by sunjj on 11-9-26.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMWrongControl.h"
#import "CMPracticeControl.h"
#import "CMMyExamControl.h"

@interface CMExamControl : CMViewController {//<UITableViewDelegate,UITableViewDataSource>{
	
	UIImageView* selview;
	UIButton *firbtn;
	UIButton *secbtn;
	UIButton *thrbtn;
	
	CMWrongControl* wrongControl;
	CMPracticeControl* practiceControl;
	CMMyExamControl* myExamControl;
    
    NSInteger selectedIndex;
	
	//UIView * myExamControl;
}
-(void)onselect:(int)pos;
//- (IBAction)gotoWrong:(id)sender;
//- (void)refreshWrongCount:(id)sender;
@end





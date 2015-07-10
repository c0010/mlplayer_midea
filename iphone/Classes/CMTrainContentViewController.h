//
//  CMTrainContentViewController.h
//  MLPlayer
//
//  Created by 张永兵 on 14/12/24.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"
#import "cmmytrainlist.h"
#import "CMTableView.h"

@interface CMTrainContentViewController : CMViewController<UITableViewDataSource,UITableViewDelegate>
{
    CMTableView *tableviewlist;
    
    TMyTrainItem curItem;
    
}

-(void)setInfoItem:(TMyTrainItem &)item;
@end

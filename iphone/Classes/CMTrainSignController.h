//
//  CMTrainSignController.h
//  MLPlayer
//
//  Created by 张永兵 on 14/12/22.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"
#import "CMTrainSignView.h"

@interface CMTrainSignController : CMViewController<UITableViewDataSource,UITableViewDelegate>
{
    UITableView *m_pTableView;
    UIImageView *selview;
    
    
    
    NSInteger nSelectRow;
    
    NSMutableArray  *m_pData;
    
@public
    CMTrainSignView *listView;
}
@end

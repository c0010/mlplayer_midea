//
//  CMGroupInfoExitViewController.h
//  MLPlayer
//
//  Created by kyp on 14-6-17.
//  Copyright (c) 2014年 w. All rights reserved.
//
#import "cmgroup.h"
#import "CMViewController.h"
#import "SDWebImage/SDWebImageDownloader.h"
#import "SDWebImage/SDWebImageManager.h"

@interface CMGroupInfoExitViewController : CMViewController <UITableViewDelegate,UITableViewDataSource,UIActionSheetDelegate,UINavigationControllerDelegate,UIImagePickerControllerDelegate>
{
    UITableView *thetableView;
    TGroupInfoItem m_TGroupInfoItem;
    
}

-(void)loadTableList;
@property(nonatomic,strong) UITableView *thetableView;
@property(nonatomic,strong) UIButton *btnExit;

@property(nonatomic,strong)NSString* roomID,*roomJid;  //聊天室id

@property(nonatomic,strong) CMGroupItem *currGroupItem;

@end



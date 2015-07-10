//
//  CMPersonDetailyViewController.h
//  MLPlayer
//
//  Created by water on 14-9-29.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "cmgroup.h"
#import "CMViewController.h"
#import "SDWebImage/SDWebImageDownloader.h"
#import "SDWebImage/SDWebImageManager.h"
#import "cmcontacts.h"

@interface CMPersonDetailyViewController : CMViewController <UITableViewDelegate,UITableViewDataSource,UIActionSheetDelegate,UINavigationControllerDelegate,UIImagePickerControllerDelegate>
{
    UITableView *thetableView;
    TContactsItem tContactsItem;
    
    CMContacts *m_pContacts;
        
    BOOL isOwner;//是否是自己
}

@property(nonatomic,strong) UITableView *thetableView;

@property(nonatomic,strong) NSString* jid;

@property(nonatomic,assign) BOOL isFromChat;//是否来自聊天界面

@property(nonatomic,assign) BOOL isFromGroupChat;//是否来自群聊

- (void)setTContactsItem:(TContactsItem &)item;


@end



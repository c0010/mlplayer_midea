//
//  CMImagePreviewViewController.h
//  MLPlayer
//
//  Created by water on 14-8-7.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"
#import "CMChatViewController.h"

typedef void (^ButtonListener)(NSString *path);

@interface CMImagePreviewViewController : CMViewController{
    
}

@property(nonatomic,strong) UIImage *selectedImage;//从相册选取图片后的本地地址;
@property(nonatomic,strong) UIImageView *imageview;

@property(nonatomic,strong) ButtonListener buttonListener;
@property(nonatomic,strong) CMBaseItem *currItem;

@property(nonatomic,weak) id<CMChatMessageDelegate> delegate;

@end

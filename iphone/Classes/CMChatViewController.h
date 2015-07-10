//
//  CMChatViewController.h
//  MLPlayer
//
// 单人聊天界面
//
//  Created by 王浩沣 on 14-6-9.
//  Copyright (c) 2014年 w. All rights reserved.
//


#import <UIKit/UIKit.h>
#import "CMChatMessageCell.h"
#import "XMPPFramework.h"
#import "CMViewController.h"
#import "CMWebImage.h"
#import "faceView/FaceBoard.h"
#import "CMInteractViewController.h"
#import "SDWebImage/UIImageView+WebCache.h"
#import "SDWebImage/SDWebImageDownloader.h"
#import "SDWebImage/SDImageCache.h"
#import "CMAlertView.h"
#include "cmbrowser.h"
#import "AAPullToRefresh.h"
#import "CMTextView.h"
#import "CMMsgManager.h"
#import "CMImage.h"
#import "CMMsgBlock.h"
#import "FLXFluidTextView.h"
#import "cmqalist.h"
#import "HPGrowingTextView.h"
#define NotificationCenteUpdateIcon @"update icon"//更新头像

//发送图片消息回调
@protocol CMChatMessageDelegate <NSObject>
@optional

- (void)didSendMessage:(UIImage *)image;
@end

@interface CMChatViewController : CMViewController<UITableViewDataSource,UITableViewDelegate,UIScrollViewDelegate,NSFetchedResultsControllerDelegate,UINavigationControllerDelegate,UIImagePickerControllerDelegate,FaceBoardDelegate,CMChatMessageCellDelegate,UIGestureRecognizerDelegate,CMChatMessageDelegate,UITextViewDelegate,HPGrowingTextViewDelegate>
{    
    NSMutableDictionary *timetmps;
    
    CGFloat keyBoardHieght;
    
    NSInteger msgCount;
    TGroupInfoItem *m_pGroupInfoItem;

    int mcount;
    
    BOOL shareAlertHide;//分享课件对话框是否隐藏
    
    NSMutableDictionary *iconDictionary;
    
    BOOL iskeyBoardShow ;//系统键盘是否显示
        
    BOOL hasDraft;
    
    int topHeight; //顶端40个像素
    
@public
    TBrowserItem* currItem;
    
    TQAItem* currQaItem;
}
@property(nonatomic,strong)UINavigationController *navigationControl;

@property(nonatomic,assign)BOOL isTrainChat;
@property(nonatomic,assign)BOOL didSendMessage; //判断是否发送了消息，未发送消息返回上个                                    界面不生成会话窗口
@property(nonatomic,strong)UITableView* chatTableViewList;

@property(nonatomic,strong) UIView* inputView;

//@property(nonatomic,strong) FLXFluidTextView* inputTextView;

@property(nonatomic,strong) HPGrowingTextView* inputTextView;

@property(nonatomic,strong) UIView *faceBoardView;
@property(nonatomic,strong) UIImageView *toolsView;

@property(nonatomic,strong) FaceBoard *faceBoard;
@property(nonatomic,strong) UIButton *avatarBtn,*commitBtn,*addToolsButton;
@property(nonatomic,strong) NSFetchRequest *filterLastFetchRequest;
@property(nonatomic,strong) UIImageView* inputTextViewBackView;
@property(nonatomic,strong) AAPullToRefresh *tv;
@property(nonatomic,assign) CMChatType chatType;

@property(nonatomic,strong)NSString* icon;
@property(nonatomic,strong)NSFetchedResultsController* fetchedResultsController;
@property(nonatomic,strong)NSString* toName;
@property(nonatomic,strong)NSString* toJid;//单聊:对话人jid/群聊:群roomjid
@property(nonatomic,strong)NSString* toUid;//单聊:对话人id/群聊:群roomid
@property(nonatomic,strong)NSString* draft;//草稿
@property(nonatomic,strong)NSString* password;//草稿


@property(nonatomic,assign)BOOL isGotoRootView;

- (id)initWithTBrowserItem:(TBrowserItem *)startitem;
- (id)initWithTQaItem:(TQAItem *)startitem;

@end

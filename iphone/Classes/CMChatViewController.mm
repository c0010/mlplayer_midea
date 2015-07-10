//
//  CMChatViewController.m
//  MLPlayer
//  单人聊天界面
//  Created by 王浩沣 on 14-6-9.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMChatViewController.h"
#import "CMMyInfo.h"
#import "CMImage.h"
#import "cmwebimage.h"
#import "SDWebImage/UIButton+WebCache.h"
#import "CMCourseDetailControl.h"
#import "tool.h"
#import "AAPullToRefresh.h"
#import "CMGroupInfoExitViewController.h"
#import "CMGroupManager.h"
#import "NSDate+Helper.h"
#import "CMImagePreviewViewController.h"
#import "CMContactManager.h"
#import "CMMsgPackageUtils.h"
#import "CMCoreDataUtils.h"
#import "CMFileUtils.h"
#import "CMImageDetailViewControl.h"
#import "CMPersonDetailyViewController.h"
#import "CMBrowserHandler.h"
#import "CMQuestionDetailControl.h"
#import "CMMainControl.h"
#import "CMBrowserControl.h"

#define SHARE_MODE_COURSE @"course"
#define SHARE_MODE_NEWS @"news"

#define ANIMATEDURATIONDEFAULT 0.3
#define kChatCellIdentifier   @"com.apple.CMChatViewController.ChatCellIdentifier"

#define kChatInputViewHeight 45

static const int  kChatInputTextViewMaxHeight  = __iOS7 ? 59 : 68;//输入框最大高度
static const int  kChatInputTextViewMinHeight  = __iOS7 ? 29 : 32;//输入框最小高度

#define KEYBOARDHEIGHT @"keyBoardHieght"
#define KEYBOARDHEIGHT_DEFALUT 216

#import "MLPlayerAppDelegate.h"
#import "tool.h"

@implementation CMChatViewController
@synthesize toJid = _toJid;

- (id)initWithTBrowserItem:(TBrowserItem *)startitem;
{
   currItem = startitem;
    
    return [self init];
}

- (id)initWithTQaItem:(TQAItem *)startitem;
{
    currQaItem = startitem;
    
    return [self init];
}

- (id)init
{
    self = [super init];
    if (self) {
        
        self.chatTableViewList = [[UITableView alloc]initWithFrame:CGRectMake(0, 0,UI_IOS_WINDOW_WIDTH , UI_IOS_WINDOW_HEIGHT-kChatInputViewHeight-20-44) style:UITableViewStylePlain];
        self.chatTableViewList.backgroundColor = kColorBackground;
        [self.chatTableViewList setDelegate:self];
        [self.chatTableViewList setDataSource:self];
        [self.chatTableViewList setSeparatorStyle:UITableViewCellSeparatorStyleNone];
        
        MLPlayerAppDelegate* appDelegate = (MLPlayerAppDelegate*)[[UIApplication sharedApplication] delegate];

        self.faceBoard = appDelegate.faceBoard;
        mcount = CacheMaxForChatCount;
    }
    return self;
}

- (void)gotoBack{
    if (self.isGotoRootView) {
        [self.navigationController popToRootViewControllerAnimated:YES];
    }else{
        [self.navigationController popViewControllerAnimated:YES];
    }
}


//初始化查找条件，用于获取最后分组时间
- (void)setToJid:(NSString *)toJid{
    
    _toJid = toJid;
}

- (int) msgTotal{
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init] ;
    NSEntityDescription *entity = [NSEntityDescription entityForName:MBlock.chatTypeStr(self.chatType) inManagedObjectContext:MessageObjectContext];
    [fetchRequest setEntity:entity];
    
    //设定以时间排序
    NSSortDescriptor *sortDescriptor = [NSSortDescriptor sortDescriptorWithKey:@"sendTime" ascending:YES];
    [fetchRequest setSortDescriptors:[NSArray arrayWithObjects:sortDescriptor, nil]];
    
    
    //过滤数据
    NSPredicate *predicate;
    if (self.chatType == CMSingleChatType) {
        predicate = [NSPredicate predicateWithFormat:@" (fromJID == %@)  OR (toJID == %@) ",_toJid,_toJid];
    }else if(self.chatType == CMGroupChatType){
        predicate = [NSPredicate predicateWithFormat:@"roomJID== %@",_toJid];
    }
    [fetchRequest setPredicate:predicate];
    NSError *error = NULL;
    
    return [MessageObjectContext countForFetchRequest:fetchRequest error:&error];
}

// to load older messages
-(void) loadMoreContent{
    
    _fetchedResultsController = nil;

    int offsetIndex;//刷新后定位到行
    int rCount = [self msgTotal];//数据库总数
    int rowcount = [self.chatTableViewList numberOfRowsInSection:0];//当前tableview数量

    if (rCount > rowcount) {

        //剩余加载量 大于分页加载量，还可以加载更多
        if (rCount - rowcount > CacheMaxForChatCount) {
            
            mcount = rowcount + CacheMaxForChatCount;

            offsetIndex = CacheMaxForChatCount;

        }else{
        
            //剩余加载量 小于分页所需加载量，禁止继续加重
            mcount = rCount;
            
            offsetIndex = rCount - rowcount;
            
            [self.tv removeSelf];
        }
    }

    NSError *error = NULL;
    //--making a performFetch Request to fill up above cells--
    if ([self.fetchedResultsController performFetch:&error]) {
        [self.chatTableViewList reloadData];
        [self scrollToUpWithIndex:offsetIndex animated:NO];
        [self.tv performSelector:@selector(stopIndicatorAnimation) withObject:nil afterDelay:1.0f];
    }
}

//更新头像通知
- (void)updateUserIcon:(NSNotification *)aNotification{

    CMUserItem *user = (CMUserItem *)aNotification.object;
    
    
    NSString *newIcon = [iconDictionary objectForKey:user.jid];
    
    if ( newIcon ) {
        
        [iconDictionary setValue:user.icon forKey:user.jid];
    }
    
}

//更新lastmessage
- (void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    
    [self tapPressed:nil];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NotificationCenteUpdateIcon object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:FLXFluidTextViewHeightConstraintDidChangeNotification object:nil];
    

    
    NSError *error = NULL;
    NSString *lastMessage = @"";
    
    NSUInteger sessionCount = [self msgTotal];
    
    if (self.chatType == CMSingleChatType) {
        CMDialogueItem *dialogueItem =[[XMPPChatMessageCoreDataStorage sharedInstance] dialogueItemExistForJid:_toJid];
        
        id <NSFetchedResultsSectionInfo> sectionInfo = [[self.fetchedResultsController sections] objectAtIndex:0];
        CMMessageItem* messageItem = [[sectionInfo objects] lastObject];
        
        if (messageItem.type == CMMessageCourseType) {
            lastMessage = [NSString stringWithFormat:@"%@ %@",I(@"[分享]"),messageItem.coursemessage.title];
        }else if (messageItem.type == CMMessageQAType){
            lastMessage = [NSString stringWithFormat:@"%@ %@",I(@"[分享]"),messageItem.qamessage.question];
        }else if (messageItem.type == CMMessageImageType){
            lastMessage = I(@"[图片]");
        }else{
            lastMessage = messageItem.content;
        }
        
        if ( dialogueItem ) {
            
            dialogueItem.unread = 0;
            
            if ( messageItem ) {
                
                dialogueItem.lastMessage = lastMessage;
                dialogueItem.sendTime = messageItem.sendTime;
            }
            
            if ( self.inputTextView.text.length > 0 ) {
                
                dialogueItem.sendTime = [NSDate date];
                
            }else{
            
                if ( sessionCount <= 0 ) {
                    [MessageObjectContext deleteObject:dialogueItem];
                }
            }
            
            dialogueItem.draft = self.inputTextView.text;

            
            [MessageObjectContext save:&error];
            
            [CMCoreDataUtils updateBadgeValueWithTabBar:self.navigationController.tabBarItem];
            
        }else{
            
            if ( ( self.inputTextView.text.length == 0) &&  ( !messageItem ) ){
//                NSFetchRequest *FectchRequest=[NSFetchRequest fetchRequestWithEntityName:[CMDialogueItem class]];
//                FectchRequest.predicate=[NSPredicate predicateWithFormat:@"fromJID == %@",_toJid];
//                NSArray *arr=[MessageObjectContext executeFetchRequest:FectchRequest error:nil];
//                for (NSManagedObject *obj in arr) {
//                    [MessageObjectContext deleteObject:obj];
//                }
//                [MessageObjectContext save:NULL];
                return;
            }
                
            CMDialogueItem * dialogueItem = [NSEntityDescription insertNewObjectForEntityForName:NSStringFromClass([CMDialogueItem class]) inManagedObjectContext:MessageObjectContext];
            dialogueItem.fromJID = _toJid;
            dialogueItem.fromName = self.toName;
            dialogueItem.icon = self.icon;
            dialogueItem.flag = 0;
            dialogueItem.fromID = self.toUid;

            if ( messageItem ) {
                
                dialogueItem.lastMessage = lastMessage;
            }
            
            dialogueItem.draft = self.inputTextView.text;
            
            [MessageObjectContext save:&error];
        }
    }else if (self.chatType == CMGroupChatType){
        //如果此时被T
        if ( !self.isTrainChat && ![CMCoreDataUtils existManagedObject:NSStringFromClass([CMGroupItem class]) withPredicate:Pre_RoomJid(self.toJid)]) {
            return;
        }
        id <NSFetchedResultsSectionInfo> sectionInfo = [[self.fetchedResultsController sections] objectAtIndex:0];
        CMGroupMessageItem* messageItem = [[sectionInfo objects] lastObject];
        
        if (messageItem.type == CMMessageCourseType) {
            lastMessage = [NSString stringWithFormat:@"%@ %@",I(@"[分享]") , messageItem.coursemessage.title];
        }else if (messageItem.type == CMMessageQAType){
            lastMessage = [NSString stringWithFormat:@"%@ %@",I(@"[分享]") , messageItem.qamessage.question];
        }else if (messageItem.type == CMMessageImageType){
            lastMessage = I(@"[图片]");
        }else{
            lastMessage = messageItem.content;
        }
        
        CMDialogueItem *dialogueItem =[[XMPPChatMessageCoreDataStorage sharedInstance] dialogueItemExistForRoomJid:_toJid];
        
        if ( dialogueItem ) {
            dialogueItem.roomName = self.toName;
            
            if (self.isTrainChat) {
                dialogueItem.roomJID = self.toJid;
                dialogueItem.password = self.password;
            }

            dialogueItem.unread = 0;
            dialogueItem.sendTime = messageItem.sendTime;

            if ( messageItem ) {
                
                dialogueItem.lastMessage = lastMessage;
                dialogueItem.sendTime = messageItem.sendTime;
            }
            
            if ( self.inputTextView.text.length > 0 ) {
                
                dialogueItem.sendTime = [NSDate date];
                
            }else{
                
                if ( sessionCount <= 0 ) {
                    [MessageObjectContext deleteObject:dialogueItem];
                }
            }
            
            if ( !self.isTrainChat ) {
                dialogueItem.draft = self.inputTextView.text;
            }
            
            [MessageObjectContext save:&error];
            

            if (self.isTrainChat) {
                for (int i =0; i<[self.navigationControl viewControllers].count; i++) {
                    UIViewController *viewcontroller = [[self.navigationControl viewControllers] objectAtIndex:i];
                    if ([viewcontroller isKindOfClass:[CMMainControl class]]) {
                        CMMainControl *mainController = (CMMainControl*)viewcontroller;
                        UIViewController *vCtrl = [[mainController viewControllers] objectAtIndex:2];
                        [CMCoreDataUtils updateBadgeValueWithTabBar:vCtrl.tabBarItem];
                    }
                    else if ([viewcontroller isKindOfClass:[CMBrowserControl class]])
                    {
                        NSString *q11 = viewcontroller.navigationController.tabBarItem.title;
                        NSString *fa12 = viewcontroller.tabBarController.tabBarItem.title;
                    }

                    else if ([viewcontroller isKindOfClass:[CMInteractViewController class]])
                    {
                        [CMCoreDataUtils updateBadgeValueWithTabBar:self.navigationControl.tabBarItem];
                    }
                    
                    
                }

            }else
                [CMCoreDataUtils updateBadgeValueWithTabBar:self.navigationController.tabBarItem];
        }else if(self.didSendMessage){
            
            if ( (self.inputTextView.text.length == 0) &&  ( !messageItem ) ){
                
                return;
            }
            
            CMDialogueItem * dialogueItem = [NSEntityDescription insertNewObjectForEntityForName:NSStringFromClass([CMDialogueItem class]) inManagedObjectContext:MessageObjectContext];
            dialogueItem.roomName = self.toName;
            dialogueItem.roomJID = self.toJid;
            dialogueItem.fromJID = kXMPPJid;
            dialogueItem.flag = 1;
            
            //根据roomjid查找群组
            CMGroupItem *groupItem = (CMGroupItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMGroupItem class]) withPredicate:Pre_RoomJid(dialogueItem.roomJID)];
            dialogueItem.roomID = groupItem.roomID;
            dialogueItem.password = groupItem.password;
            //从交流区返回传self.password，因为此时groupitem为nil
            if (self.isTrainChat) {
                dialogueItem.password = self.password;
            }
            dialogueItem.icon = groupItem.icon;
            
            if ( !self.isTrainChat ) {
                dialogueItem.draft = self.inputTextView.text;
            }
            if ( messageItem ) {
                
                dialogueItem.lastMessage = lastMessage;
            }
            
            [MessageObjectContext save:&error];
        }
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.openAutoKeyboard = YES;
    
    if (self.isTrainChat) {
        topHeight = 40;
    }else
        topHeight = 0;
    
    self.chatTableViewList.frame = CGRectMake(0,0+topHeight  ,UI_IOS_WINDOW_WIDTH , UI_IOS_WINDOW_HEIGHT-kChatInputViewHeight-20-44-topHeight);
    
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    keyBoardHieght = [[ud objectForKey:KEYBOARDHEIGHT] floatValue];
    if (keyBoardHieght == 0) {
        keyBoardHieght = KEYBOARDHEIGHT_DEFALUT;
    }
    
    [self.view addSubview:self.chatTableViewList];
    
    __weak CMChatViewController *blockSelf = self;
    
    if ([self msgTotal] >  CacheMaxForChatCount) {
        self.tv = [self.chatTableViewList addPullToRefreshPosition:AAPullToRefreshPositionTop actionHandler:^(AAPullToRefresh *v){
            [blockSelf performSelector:@selector(loadMoreContent) withObject:nil afterDelay:1.0];
        }];
    }
    
    self.tv.imageIcon = nil;
    self.tv.borderColor = [UIColor clearColor];
    
    [self createInputView];

    if (currItem || currQaItem) {
        
        WEAKSELF;
        CMAlertView *alertView = [[CMAlertView alloc]initWithTitle:nil message:nil cancelButtonTitle:I(@"取消") otherButtonTitles:I(@"发送") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
            STRONGSELF;
            if (buttonIndex != CMAlertViewCancel) {
                CMBaseItem *baseItem;
                if (currItem) {
                    baseItem = [CMMsgPackageUtils packageMessageWithCourse:currItem chatType:sself.chatType toName:sself.toName toJid:_toJid];
                }else if (currQaItem){
                    baseItem = [CMMsgPackageUtils packageMessageWithQa:currQaItem chatType:sself.chatType toName:sself.toName toJid:_toJid];
                }
                
                self.didSendMessage = YES;

                CMMsgManager *manage = [CMMsgManager manager];
                
                [MsgManager doSendMessage:baseItem completion:^(enum CMSendMessageState sendState) {
                    
                    [ self.navigationController dismissViewControllerAnimated:YES completion:^{
                        
                        if (sendState == CMSendMessageStateSuccess) {
                            [tool ShowAlert:I(@"分享成功")];
                        }else if(sendState == CMSendMessageStateFailure){
                            [tool ShowAlert:I(@"分享失败")];
                        }
                        
                    }];
                }];
                
                if (alertView.textfield.text && alertView.textfield.text.length > 0 ) {
                    [sself sendMessageWithContent:alertView.textfield.text];
                }
                
            }else{
                [sself.navigationController popViewControllerAnimated:YES];
            }
        }];
        
        alertView.disabledOutSide = YES;

        if (currItem) {
            alertView.customView = [alertView customShareViewWithTitle:[NSString stringWithUTF8String:currItem->sTitle] message:[NSString stringWithUTF8String:currItem->sDescription] imageUrl:[NSString stringWithUTF8String:currItem->sThumbs]isQa:NO];
        }else if (currQaItem){
            
            alertView.customView = [alertView customShareViewWithTitle:[NSString stringWithFormat:@"%@的问题",[NSString stringWithUTF8String:currQaItem->sQuestioner_fullname.c_str()]] message:[NSString stringWithUTF8String:currQaItem->sQuestion.c_str()] imageUrl:[NSString stringWithUTF8String:currQaItem->sThumburl.c_str()] isQa:YES];
        }
        
        [alertView show];
        
        shareAlertHide = YES;
    }
    
    [self scrollToBottomAnimated:NO];
    
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapPressed:)];
    tapGesture.numberOfTapsRequired = 1;
    tapGesture.delegate = self;
    [self.chatTableViewList addGestureRecognizer:tapGesture];
    
    UIButton *rightBtn = [[UIButton alloc]initWithFrame:CGRectMake(0, 10, kBarItemWidth, 24)];
    [rightBtn setImageEdgeInsets:UIEdgeInsetsMake(0, 18, 0, 0)];
    [rightBtn setImage:[UIImage imageNamed:(self.chatType == CMGroupChatType) ? @"interact_group_btn_normal" : @"interact_person_btn_normal"] forState:UIControlStateNormal];
    [rightBtn setImage:[UIImage imageNamed:(self.chatType == CMGroupChatType) ? @"interact_group_btn_highlight" : @"interact_person_btn_highlight"] forState:UIControlStateHighlighted];
    [rightBtn addTarget:self action:@selector(gotoAddGroupPage) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem * rightBtnItem = [[UIBarButtonItem alloc]initWithCustomView:rightBtn];
    
    self.navigationItem.rightBarButtonItem=rightBtnItem;
    
    if (self.chatType == CMGroupChatType) {
        iconDictionary = [NSMutableDictionary dictionary];
    }
    
}

- (void)doButtonPressed:(UIButton *)sender{
    switch (sender.tag) {
        case 0:
        {
            UIImagePickerController *picker =[[UIImagePickerController alloc] init];
            picker.delegate = self;
            picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
            picker.allowsEditing = NO;
            
            if (__iOS7)
            {
                //[[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
                MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
                appDelegate.window.tintColor = [UIColor whiteColor];
            }
            [self presentViewController:picker animated:YES completion:nil];
        }
            break;
        case 1:
        {
            if ([UIImagePickerController isSourceTypeAvailable: UIImagePickerControllerSourceTypeCamera])
            {
                UIImagePickerController *picker = [[UIImagePickerController alloc] init];
                picker.delegate = self;
                picker.allowsEditing = NO;
                picker.sourceType = UIImagePickerControllerSourceTypeCamera;
                [self presentModalViewController:picker animated:YES];
            }
            else
            {
                UIAlertView *alert = [[UIAlertView alloc]
                                      initWithTitle:@"Error accessing photo library"
                                      message:@"Device does not support a photo library"
                                      delegate:nil
                                      cancelButtonTitle:@"ok!"
                                      otherButtonTitles:nil];
                [alert show];
            }
        }
            break;
        case 2:
           
            break;
        default:
            break;
    }
}

-(void)gotoAddGroupPage
{
    if (CMGlobal::TheOne().IsOffline()) {
        [tool ShowError:-1];  //离线不进入
        return;
    }
    
    if (self.chatType == CMGroupChatType) {
        //群组信息界面
        CMGroupInfoExitViewController * controller = [[CMGroupInfoExitViewController alloc]init];
        controller.roomID = self.toUid;
        controller.roomJid = self.toJid;
        controller.title = I(@"群信息");
        [self.navigationController pushViewController:controller animated:YES];
    }else{
        //个人信息界面
        CMPersonDetailyViewController * controller = [[CMPersonDetailyViewController alloc]init];
        controller.jid = _toJid;
        controller.title = self.toName;
        controller.isFromChat = YES;
        [self.navigationController pushViewController:controller animated:YES];
    }
}

- (void)tapPressed:(UITapGestureRecognizer *)gestureRecognizer{
    self.avatarBtn.selected = NO;
    self.addToolsButton.selected = NO;
    [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
        self.addToolsButton.transform = CGAffineTransformMakeRotation(M_PI / 180.0);
    }];
    [self.avatarBtn setImage:[UIImage imageNamed:@"interact_emoji_btn_normal"] forState:UIControlStateNormal];
    [self hideFaceView];
    [self.inputTextView resignFirstResponder];
    if (![self keyBoardHide]) {
        [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
            [self.chatTableViewList setFrameY:0+topHeight Height:UI_IOS_WINDOW_HEIGHT-CGRectGetHeight(self.inputView.frame)-64-topHeight];
            [self scrollToBottomAnimated:NO];
        }];
    }
    [self moveViewToYIn:ANIMATEDURATIONDEFAULT yCoordinate:UI_IOS_WINDOW_HEIGHT-CGRectGetHeight(self.inputView.frame)-20-44  target:self.inputView];
}

//tableview content大于frame时，tableview上移距离
- (CGFloat)keyBoardFromLastCell_distance
{
    int count = [self.chatTableViewList numberOfRowsInSection:0];
    if (count > 0) {
        //最后一行相对于tableview contentsize的frame
        CGRect rectInTableView = [self.chatTableViewList rectForRowAtIndexPath:[NSIndexPath indexPathForRow:count - 1 inSection:0]];
        //键盘的高度
        CGFloat keyBoardY = UI_IOS_WINDOW_HEIGHT-20-44-CGRectGetHeight(self.inputView.frame)-keyBoardHieght;
        //最后一行高度与键盘高度差，大于零没超出，小于零超出
        CGFloat lastIndexPathY = keyBoardY - CGRectGetMaxY(rectInTableView);
        if (lastIndexPathY < 0) {
            if (fabsf(lastIndexPathY) >= keyBoardHieght) {
                return keyBoardHieght + (CGRectGetHeight(self.inputView.frame) - kChatInputViewHeight);

            }else{
                return fabsf(lastIndexPathY);
            }
        }
    }
    return 0;
}

//键盘/表情盘 是否隐藏
- (BOOL)keyBoardHide{
    
    CGFloat inputMainY = CGRectGetMaxY(self.inputView.frame);
    NSUInteger height = 0;
    
    //培训班减去状态栏和导航栏高度
    if (self.isTrainChat) {
        if (__iOS7) {
            height = 64;
        }
    }
    if (__iOS7) {
        return (inputMainY == CGRectGetHeight(self.view.frame)-height);

    }else{
        return (inputMainY == CGRectGetHeight(self.view.frame)-height);

    }
}

//tableview content高度大于frame高度,最后一行是否可见
- (BOOL)beyondTableviewHeight{
    CGFloat distance = fabsf([self keyBoardFromLastCell_distance]);
    if (distance > 0 ) {
        return YES;
    }
    return NO;
}

#pragma mark - UIGestureRecognizerDelegate
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch
{
    // 输出点击的view的类名
    // 若为UITableViewCellContentView（即点击了tableViewCell），则不截获Touch事件
    if ([touch.view isKindOfClass:[UIButton class]]) {
        return NO;
    }
    return  YES;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    
    
    
    if (self.chatType == CMGroupChatType) {
        
        
        
        if (self.isTrainChat) {
            
            
            if (self.password && self.toJid) {
                //xmpp进入群组
                [[CMGroupManager managerDelegate] joinWithJid:self.toJid withPassword:self.password success:^(XMPPRoom *room){
                }];
            }
            
            
            self.titleLabel.text = self.toName;
        }
        
        else
        {
            CMGroupItem *groupItem = (CMGroupItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMGroupItem class]) withPredicate:Pre_RoomJid(self.toJid)];
            
            if (!groupItem.isJoined || (![groupItem.isJoined boolValue])) {
                if (groupItem.password && groupItem.roomJID) {
                    //xmpp进入群组
                    [[CMGroupManager managerDelegate] joinWithJid:groupItem.roomJID withPassword:groupItem.password success:nil];
                }
            }
            
            //此处可能会更新群组名称
            NSString *roomName = groupItem.roomName;
            self.titleLabel.text = roomName;
            self.toName = roomName;
        }
        
       
    }else{
        self.titleLabel.text = self.toName;
    }
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(updateUserIcon:)
                                                     name:NotificationCenteUpdateIcon object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(textviewdidChange:)
                                                     name:FLXFluidTextViewHeightConstraintDidChangeNotification
                                                   object:nil];

    if ( !hasDraft ) {

        if ( self.draft && self.draft.length > 0 ) {

            hasDraft = YES;
            
            self.inputTextView.text = self.draft;

            self.commitBtn.enabled = (self.draft != nil);
            
            self.draft = nil;

//            [self.inputTextView becomeFirstResponder];
        }
    }
    
}

- (void)keyboarddidShow:(NSNotification *)aNotification{
//    [self.faceBoardView setContentOffset:CGPointMake(UI_IOS_WINDOW_WIDTH * 2, 0) animated:YES];
}

- (void)keyboardWillShow:(NSNotification *)aNotification
{
//    if (self.navigationController.topViewController != self) {
//        return;
//    }
    iskeyBoardShow = YES;
    
    if ((! currItem || !shareAlertHide)) {
        NSDictionary* info=[aNotification userInfo];
        keyBoardHieght=[[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size.height;
        
        [self moveViewToYIn:ANIMATEDURATIONDEFAULT yCoordinate:UI_IOS_WINDOW_HEIGHT-20-44-CGRectGetHeight(self.inputView.frame)-keyBoardHieght target:self.inputView];
        if ([self beyondTableviewHeight]) {
            [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
                CGFloat distance = fabsf([self keyBoardFromLastCell_distance]);

                [self.chatTableViewList setFrameY:-fabsf(distance)+topHeight Height:UI_IOS_WINDOW_HEIGHT-64-kChatInputViewHeight-topHeight];
                [self scrollToBottomAnimated:NO];
            }];
        }
        //保存键盘高度
        NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
        CGFloat keyHeight = [[ud objectForKey:KEYBOARDHEIGHT] floatValue];
        if (keyHeight == 0) {
            keyHeight = keyBoardHieght;
            [ud setObject:[NSNumber numberWithFloat:keyBoardHieght] forKey:KEYBOARDHEIGHT];
            [ud synchronize];
        }
    }
}

-(void)keyboardWillHide:(NSNotification *)aNotification
{
    
    iskeyBoardShow = NO;

    if ( ![self keyBoardHide] ) {
        [self tapPressed:nil];
    }

    
//    if (self.navigationController.topViewController != self) {
//        if (![self keyBoardHide]) {
//            [self.inputTextView becomeFirstResponder];
//        }
//    }
//    
   
//   [self moveViewToYIn:ANIMATEDURATIONDEFAULT yCoordinate:UI_IOS_WINDOW_HEIGHT-kChatInputViewHeight-20-44 target:self.inputView];
//    if (self.faceBoardView.hidden) {
//        if ([self beyondTableviewHeight]) {
//            [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
//                [self.chatTableViewList setFrameY:0];
//            }];
//        }
//    }
}

-(void)moveViewToYIn:(CGFloat)seconds yCoordinate:(CGFloat)y target:(UIView*)view
{
    if(!view)
        return;
    __block typeof(self) bself= self;

	[UIView animateWithDuration:0.25
					 animations:^{

                         [bself slideViewToY:view yCoordinate:y];
					 }
                     completion:^(BOOL finished){
					 }];

}

-(void)slideViewToY:(UIView*)v yCoordinate:(CGFloat)y
{
    [v setFrameY:y];
}

-(void)createInputView
{
    //底
    self.inputView =[[UIView alloc]initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-20-kChatInputViewHeight-44, UI_IOS_WINDOW_WIDTH, kChatInputViewHeight)];
    self.inputView.layer.shadowColor=UIColorRGB(0xa2a2a2).CGColor;
	self.inputView.layer.shadowOffset=CGSizeMake(0,-1);
	self.inputView.layer.shadowOpacity=0.4;
    self.inputView.backgroundColor = UIColorRGB(0xefefef);
    [self.inputView setUserInteractionEnabled:YES];
    
//    UIView *seqView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, 0.3)];
//    seqView.backgroundColor = UIColorRGB(0xa2a2a2);
//    seqView.tag = 10;
//    [self.inputView addSubview:seqView];

    //发送按钮
    self.commitBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.commitBtn setFrame:CGRectMake(255, 8, 55, 29)];
    self.commitBtn.titleLabel.font = [UIFont systemFontOfSize:16.f];
    [self.commitBtn setTitle:I(@"发送") forState:UIControlStateNormal];
    [self.commitBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [self.commitBtn setTitleColor:[UIColor darkGrayColor] forState:UIControlStateDisabled];
    [self.commitBtn setBackgroundImage:[UIImage imageNamed:@"sendreply_btn_nor"] forState:UIControlStateNormal];
    [self.commitBtn setBackgroundImage:[UIImage imageNamed:@"sendreply_btn_sel"] forState:UIControlStateHighlighted];
    [self.commitBtn setBackgroundImage:[UIImage imageNamed:@"sendreply_btn_dis"] forState:UIControlStateDisabled];
    [self.commitBtn addTarget:self action:@selector(sendMessage) forControlEvents:UIControlEventTouchUpInside];
   
//    self.commitBtn.enabled = NO;
    self.commitBtn.enabled = YES;

    [self.inputView addSubview:self.commitBtn];

    //图片按钮
    self.addToolsButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.addToolsButton setFrame:CGRectMake(8, 10, 25, 25)];
    [self.addToolsButton setImage:[UIImage imageNamed:@"interact_tools_add_normal"] forState:UIControlStateNormal];
//    [self.addToolsButton setBackgroundImage:[UIImage imageNamed:@"interact_tools_add_highlight"] forState:UIControlStateHighlighted];
    [self.addToolsButton addTarget:self action:@selector(toolsButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [self.addToolsButton setAdjustsImageWhenHighlighted:NO];
    [self.addToolsButton setAdjustsImageWhenDisabled:NO];
    [self.inputView addSubview:self.addToolsButton];
    

//    self.inputTextViewBackView = [[UIImageView alloc]initWithFrame:CGRectMake(70, 10, 175, 29)];
////    inputTextViewBackView.image=[UIImage imageNamed:@"interact_input_bar_bg"];
//    self.inputTextViewBackView.autoresizingMask = UIViewAutoresizingFlexibleHeight;
//    self.inputTextViewBackView.backgroundColor = [UIColor whiteColor];
//    self.inputTextViewBackView.userInteractionEnabled = YES;
//    self.inputTextViewBackView.layer.borderColor = UIColorRGB(0x858585).CGColor;
//    self.inputTextViewBackView.layer.borderWidth = 0.5f;
//    self.inputTextViewBackView.layer.masksToBounds = YES;
//    self.inputTextViewBackView.layer.cornerRadius = 3.0f;
    //输入框
  
    /*
    self.inputTextView=[[FLXFluidTextView alloc]initWithFrame:CGRectMake(70, 8, 175, 29)];
    
    self.inputTextView.autoresizingMask = UIViewAutoresizingFlexibleHeight;
    self.inputTextView.delegate = self;
//    [self.inputTextView addTarget:self action:@selector(inputTextViewReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
//    [self.inputTextView addTarget:self action:@selector(inputTextViewBeginEdit:) forControlEvents:UIControlEventEditingDidBegin];
    self.inputTextView.backgroundColor = [UIColor whiteColor];
    self.inputTextView.font = [UIFont systemFontOfSize:15.0];
    self.inputTextView.textAlignment = UITextAlignmentLeft;
    self.inputTextView.returnKeyType = UIReturnKeyDone;
    self.inputTextView.maximumNumberOfLines = 3;
    self.inputTextView.minimumNumberOfLines = 1;
    
   
    
    if ([self.inputTextView respondsToSelector:@selector(setTextContainerInset:)]) {
        self.inputTextView.textContainerInset = UIEdgeInsetsMake(5.f, 0.f, 5.0f, 0.f);
    }else{
        self.inputTextView.contentInset = UIEdgeInsetsMake(5.f, 0.f, 5.0f, 0.f);
    }
    
    self.inputTextView.layer.borderColor = UIColorRGB(0x858585).CGColor;
    self.inputTextView.layer.borderWidth = 0.5f;
    self.inputTextView.layer.masksToBounds = YES;
    self.inputTextView.layer.cornerRadius = 3.0f;

     */
    self.avatarBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [self.avatarBtn setFrame:CGRectMake(40, 10, 25, 25)];
    [self.avatarBtn setImage:[UIImage imageNamed:@"interact_emoji_btn_normal"] forState:UIControlStateNormal];
    [self.avatarBtn addTarget:self action:@selector(avatarBtnPressed:) forControlEvents:UIControlEventTouchUpInside];
    
//    [self.inputView addSubview:self.inputTextViewBackView];
    [self.inputView addSubview:self.avatarBtn];
    
   
//    [self.inputView addSubview:self.inputTextView];
    self.inputTextView =[[HPGrowingTextView alloc] initWithFrame:CGRectMake(70, 8, 175, 29)];
    self.inputTextView.isScrollable = NO;
    self.inputTextView.contentInset = UIEdgeInsetsMake(0, 5, 0, 5);
    self.inputTextView.minNumberOfLines = 1;
    self.inputTextView.maxNumberOfLines = 3;
    self.inputTextView.returnKeyType = UIReturnKeyDone;
    self.inputTextView.font = [UIFont systemFontOfSize:15.0];
    self.inputTextView.internalTextView.scrollIndicatorInsets = UIEdgeInsetsMake(5, 0, 5, 0);
    self.inputTextView.backgroundColor = [UIColor whiteColor];
    [self.inputView addSubview:self.inputTextView];
    self.inputTextView.delegate = self;
   
    [self.view addSubview:self.inputView];
    
    self.faceBoardView = [[UIView alloc]initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT, UI_IOS_WINDOW_WIDTH,KEYBOARDHEIGHT_DEFALUT)];
    self.faceBoardView.backgroundColor = UIColorRGB(0xe6e6e6);

    self.faceBoardView.hidden = YES;
    
    self.faceBoard.frame = self.faceBoardView.bounds;
    self.faceBoard.backgroundColor = [UIColor clearColor];
    self.faceBoard.delegate = self;
    self.faceBoard.hidden = YES;
   
  
//    self.faceBoard.inputTextView = self.inputTextView;
    self.faceBoard.inputTextView =(UITextView *) self.inputTextView;
    
    self.toolsView = [[UIImageView alloc]initWithFrame:self.faceBoardView.bounds];
    [self.toolsView setFrameX:0];
    self.toolsView.backgroundColor = [UIColor clearColor];
    self.toolsView.userInteractionEnabled = YES;
    
    CGFloat beginX = 15;
    CGFloat offsetX = 30;
    CGFloat imageWidth = 50;
    
    for (int i = 0; i < 2; i++) {
        CMButton *button = [CMButton buttonWithType:UIButtonTypeCustom];
        button.frame = CGRectMake(beginX + (i * (imageWidth + offsetX)), 20, imageWidth, imageWidth);
        button.image = [UIImage imageNamed:[NSString stringWithFormat:@"interact_tools_%d",i]];
        button.tag = i;
        
        WEAKSELF;
        [button setOnClickListener:^(UIButton * sender){
            STRONGSELF;
            [sself doButtonPressed:sender];
        }];
        
        //添加文字提示
        UILabel *lab = [[UILabel alloc]initWithFrame:CGRectMake(beginX + (i * (imageWidth + offsetX)), 25+imageWidth, imageWidth, 20)];
        
        [lab setBackgroundColor:[UIColor clearColor]];
        [lab setTextColor:[UIColor lightGrayColor]];
        [lab setFont:[UIFont systemFontOfSize:12]];
        [lab setTextAlignment:NSTextAlignmentCenter];
        if (i==0) {
            [lab setText:I(@"图片")];
        }else
            [lab setText:I(@"拍照")];
        
        [self.toolsView addSubview:lab];
        CMRELEASE(lab);
        
        [self.toolsView addSubview:button];
    }
    
    [self.faceBoardView addSubview:self.faceBoard];
    [self.faceBoardView addSubview:self.toolsView];
    
    [self.view addSubview:self.faceBoardView];
}

#pragma mark - HPGrowingTextViewDelegate
- (void)growingTextView:(HPGrowingTextView *)growingTextView willChangeHeight:(float)height
{
   
    float diff = (growingTextView.frame.size.height - height);
    // 改变输入框的高度
    CGRect textViewFrame = self.inputTextView.frame;
    textViewFrame.size.height -= diff;
    self.inputTextView.frame = textViewFrame;
 
    if (self.avatarBtn.selected) {
        //输入表情时，键盘高度。
        [self.inputView setFrameY:(UI_IOS_WINDOW_HEIGHT-20-kChatInputViewHeight-44-KEYBOARDHEIGHT_DEFALUT - (height - kChatInputTextViewMinHeight)) Height:(kChatInputViewHeight + (height - kChatInputTextViewMinHeight))];
        if ([self beyondTableviewHeight]) {
            //tableview跟着输入盘调整
            int beyondKeyBoardHeight = keyBoardHieght - KEYBOARDHEIGHT_DEFALUT;
            if ( beyondKeyBoardHeight > 0) {
                [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance]) + beyondKeyBoardHeight + topHeight];
            }else{
                [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance]) + topHeight];
            }
        }
        
    }else{
        //文字输入，键盘高度;中文键盘keyBoardHieght =252
        
        CGFloat inputViewY = UI_IOS_WINDOW_HEIGHT- 20 - 44 -kChatInputViewHeight - (height - kChatInputTextViewMinHeight);
        
        if ( ![self keyBoardHide] ) {
            
            inputViewY -= keyBoardHieght;
            
            [self.inputView setFrameY:inputViewY Height:(kChatInputViewHeight + (height - kChatInputTextViewMinHeight))];
            
            if ([self beyondTableviewHeight]) {
                //tableview跟着输入盘调整
                [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance]) + topHeight];
            }
            
        }else{
            
            [self.inputView setFrameY:inputViewY Height:(kChatInputViewHeight + (height - kChatInputTextViewMinHeight))];
            
            if ([self beyondTableviewHeight]) {
                //tableview跟着输入盘调整
                [self.chatTableViewList setFrameY:0+topHeight Height:UI_IOS_WINDOW_HEIGHT-CGRectGetHeight(self.inputView.frame)-64-topHeight];
            }
        }
    }
    
    [self scrollToBottomAnimated:NO];
    
}
- (BOOL)growingTextView:(HPGrowingTextView *)growingTextView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    
    if( [text isEqualToString:@"" ] ) {
        //删除文本情况
        NSString* text = growingTextView.text;
        
        BOOL hasCommaLeft = NO;
        BOOL hasCommaRight = NO;
        
        for( int i = range.location; i< text.length; i++ ) {
            if( [text characterAtIndex:i] == '[' && i != range.location )
                break;
            if( [text characterAtIndex:i] == ']' ) {
                hasCommaRight = YES;
                break;
            }
        }
        
        if( !hasCommaRight )
            return YES;
        
        for( int i = range.location; i>=0; i-- ) {
            if( [text characterAtIndex:i] == ']' && i != range.location )
                break;
            if( [text characterAtIndex:i] == '[' ) {
                hasCommaLeft = YES;
                break;
            }
        }
        
        if( !hasCommaLeft )
            return YES;
        
        NSNumber* location = [NSNumber numberWithInt:range.location];
        //删除表情字段
        [self performSelectorOnMainThread:@selector(deleteFaceInEditor:) withObject:location waitUntilDone:NO];
        
        return NO;
    }
    return YES;

}
-(void) deleteFaceInEditor:(NSNumber*) location
{
    NSRange range = NSMakeRange([location intValue], 0);
    NSString* text = self.inputTextView.text;
    
    BOOL hasCommaLeft = NO;
    BOOL hasCommaRight = NO;
    
    for( int i = range.location; i>=0; i-- ) {
        if( [text characterAtIndex:i] == ']' && i != range.location )
            break;
        if( [text characterAtIndex:i] == '[' ) {
            range.location = i;
            hasCommaLeft = YES;
            break;
        }
    }
    if( !hasCommaLeft )
        return;
    
    for( int i = range.location+1; i< text.length; i++ ) {
        if( [text characterAtIndex:i] == '[' && i != range.location )
            break;
        if( [text characterAtIndex:i] == ']' ) {
            range.length = i - range.location +1;
            hasCommaRight = YES;
            break;
        }
    }
    
    if( !hasCommaRight )
        return;
    
    NSString* newText = [text stringByReplacingCharactersInRange: range withString:@""];
    self.inputTextView.text = newText;
    
}


//- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text{
//
//    NSLog(@"textView: %@,range:%@,text:%@",textView.text,NSStringFromRange(range),text);
//    return YES;
//}

- (void)textviewdidChange:(NSNotification *)aNotification{
    
    [self handlerTextHeightWithAnimations: ! hasDraft ];
    
    if ( self.draft && self.draft.length > 0 && hasDraft) {
    
        hasDraft = NO;
    }
}

- (void)handlerTextHeightWithAnimations :(BOOL)animations{

    if ( animations ) {
        
        [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
            
            [self handlerTextHeight];
        }];
    }else{
    
        [self handlerTextHeight];
    }
}

- (void)handlerTextHeight{
  
//    CGFloat height = self.inputTextView.contentSize.height;
    CGFloat height = self.inputTextView.frame.size.height;
    
    if (height > kChatInputTextViewMaxHeight) {
        height = kChatInputTextViewMaxHeight;
        
    }
    
    if (self.avatarBtn.selected) {
        //输入表情时，键盘高度。
        [self.inputView setFrameY:(UI_IOS_WINDOW_HEIGHT-20-kChatInputViewHeight-44-KEYBOARDHEIGHT_DEFALUT - (height - kChatInputTextViewMinHeight)) Height:(kChatInputViewHeight + (height - kChatInputTextViewMinHeight))];
        if ([self beyondTableviewHeight]) {
            //tableview跟着输入盘调整
            int beyondKeyBoardHeight = keyBoardHieght - KEYBOARDHEIGHT_DEFALUT;
            if ( beyondKeyBoardHeight > 0) {
                [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance]) + beyondKeyBoardHeight + topHeight];
            }else{
                [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance]) + topHeight];
            }
        }
        
    }else{
        //文字输入，键盘高度;中文键盘keyBoardHieght =252
        
        CGFloat inputViewY = UI_IOS_WINDOW_HEIGHT- 20 - 44 -kChatInputViewHeight - (height - kChatInputTextViewMinHeight);
        
        if ( ![self keyBoardHide] ) {
            
            inputViewY -= keyBoardHieght;
            
            [self.inputView setFrameY:inputViewY Height:(kChatInputViewHeight + (height - kChatInputTextViewMinHeight))];

            if ([self beyondTableviewHeight]) {
                //tableview跟着输入盘调整
                [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance]) + topHeight];
            }

        }else{
            
            [self.inputView setFrameY:inputViewY Height:(kChatInputViewHeight + (height - kChatInputTextViewMinHeight))];
            
            if ([self beyondTableviewHeight]) {
                //tableview跟着输入盘调整
                [self.chatTableViewList setFrameY:0+topHeight Height:UI_IOS_WINDOW_HEIGHT-CGRectGetHeight(self.inputView.frame)-64-topHeight];
            }
        }
    }
    
    [self scrollToBottomAnimated:NO];
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
	if([text isEqualToString:@"\n"])
	{
		[textView endEditing:YES];
        
		 [self tapPressed:nil];
        
		return NO;
    }else if([text isEqualToString:@""]){
    
        [self.faceBoard backFace];
        
        return NO;
    }
    
	return YES;
}

- (void)textViewDidBeginEditing:(UITextView *)textView{
    self.avatarBtn.selected = NO;
    self.addToolsButton.selected = NO;

    [self.avatarBtn setImage:[UIImage imageNamed:@"interact_emoji_btn_normal"] forState:UIControlStateNormal];
    [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
        self.addToolsButton.transform = CGAffineTransformMakeRotation(M_PI / 180.0);
    }];
}

- (void)textViewDidChange:(UITextView *)textView{
    
    self.commitBtn.enabled = (textView.text.length != 0);
  
    if (textView.text.length > 0) {
        
       
    }
}

- (float) heightForTextView: (UITextView *)textView{
    float fPadding = 16.0; // 8.0px x 2
    CGSize constraint = CGSizeMake(textView.contentSize.width - fPadding, 70);
    
    CGSize size = [textView.text sizeWithFont: textView.font constrainedToSize:constraint lineBreakMode:UILineBreakModeWordWrap];
    
    float fHeight = size.height + 16.0;
    
    return fHeight;
}

-(void)avatarBtnPressed:(UIButton *)sender
{
    sender.selected = !sender.selected;

    if ([self keyBoardHide]) {

        if (sender == self.addToolsButton) {
            self.toolsView.hidden = NO;
            self.faceBoard.hidden = YES;
            [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
                self.addToolsButton.transform = CGAffineTransformMakeRotation(45 * M_PI / 180.0);
            }];
        }else{
            self.toolsView.hidden = YES;
            self.faceBoard.hidden = NO;
            [self.avatarBtn setImage:[UIImage imageNamed:@"interact_keyboard_btn_normal"] forState:UIControlStateNormal];
        }

        [self showFaceView];
       
    }else{
        if (sender.selected) {
            [self showFaceView];
            if (sender == self.addToolsButton) {
                
                [self.inputTextView resignFirstResponder];

                self.toolsView.hidden = NO;
                self.faceBoard.hidden = YES;
                
                self.avatarBtn.selected = NO;

                [self.avatarBtn setImage:[UIImage imageNamed:@"interact_emoji_btn_normal"] forState:UIControlStateNormal];
                [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
                    self.addToolsButton.transform = CGAffineTransformMakeRotation(45 * M_PI / 180.0);
                }];
            }else{
                
                [self.inputTextView resignFirstResponder];

                self.toolsView.hidden = YES;
                self.faceBoard.hidden = NO;
                self.addToolsButton.selected = NO;

                [self.avatarBtn setImage:[UIImage imageNamed:@"interact_keyboard_btn_normal"] forState:UIControlStateNormal];
                [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
                    self.addToolsButton.transform = CGAffineTransformMakeRotation(M_PI / 180.0);
                }];
            }
        }else{
            if (sender == self.addToolsButton) {

                self.avatarBtn.selected = NO;

                if (!self.toolsView.hidden) {
                 
                    [self.inputTextView becomeFirstResponder];
                 
                    [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
                        self.addToolsButton.transform = CGAffineTransformMakeRotation(M_PI / 180.0);
                    }];
                }else{
                   
                    [self.inputTextView resignFirstResponder];
                   

                    self.toolsView.hidden = NO;
                    self.faceBoard.hidden = YES;
                    [self.avatarBtn setImage:[UIImage imageNamed:@"interact_emoji_btn_normal"] forState:UIControlStateNormal];
                    [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
                        self.addToolsButton.transform = CGAffineTransformMakeRotation(45 * M_PI / 180.0);
                    }];
                }
            }else{
                
                self.addToolsButton.selected = NO;

                if (!self.faceBoard.hidden) {
                   
                    [self.inputTextView becomeFirstResponder];
                   
                    [self.avatarBtn setImage:[UIImage imageNamed:@"interact_emoji_btn_normal"] forState:UIControlStateNormal];
                }else{
                    self.toolsView.hidden = YES;
                    self.faceBoard.hidden = NO;
                    
                    [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
                        self.addToolsButton.transform = CGAffineTransformMakeRotation(M_PI / 180.0);
                    }];
                }
            }
        }
    }
}

- (void)hideFaceView{
    [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
        [self.faceBoardView setFrameY:UI_IOS_WINDOW_HEIGHT];
        self.addToolsButton.transform = CGAffineTransformMakeRotation(M_PI / 180.0);

    }completion:^(BOOL finished) {
        self.faceBoardView.hidden = YES;
    }];
}

- (void)showFaceView{
    self.faceBoardView.hidden = NO;
    
    [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
        
        [self moveViewToYIn:ANIMATEDURATIONDEFAULT yCoordinate:UI_IOS_WINDOW_HEIGHT-20-44-CGRectGetHeight(self.inputView.frame)-KEYBOARDHEIGHT_DEFALUT target:self.inputView];
       
        [self.faceBoardView setFrameY:UI_IOS_WINDOW_HEIGHT-20-44-KEYBOARDHEIGHT_DEFALUT];
        
        if ([self beyondTableviewHeight]) {
            [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
                
                int beyondKeyBoardHeight = keyBoardHieght - KEYBOARDHEIGHT_DEFALUT;
                if ( beyondKeyBoardHeight > 0) {
                    [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance]) + beyondKeyBoardHeight + topHeight];
                }else{
                    [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance])+topHeight];
                }
                [self scrollToBottomAnimated:NO];
            }];
        }
    }];
}

#pragma mark -
#pragma mark UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{


    id <NSFetchedResultsSectionInfo> sectionInfo = [[self.fetchedResultsController sections] objectAtIndex:section];

	NSInteger count = [sectionInfo numberOfObjects];

    return count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{

    NSString* cellIdentifier = NULL;
    CMBaseItem* item = [self.fetchedResultsController objectAtIndexPath:indexPath];
   
    CMChatMessageCell * cell = (CMChatMessageCell*)[self.chatTableViewList dequeueReusableCellWithIdentifier:kMyMessageCell];

    if(cell == nil)
    {
        cell = [[CMChatMessageCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier withItem:item] ;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    
    cell.messageBtn.tag = indexPath.row;
    cell.iconImgView.tag = indexPath.row;
    cell.afreshButton.tag = indexPath.row;
    cell.icon = self.icon;
    
    WEAKSELF;
    [cell.afreshButton setOnClickListener:^(UIButton *sender){
        
        [[[CMAlertView alloc]initWithTitle:nil message:I(@"重新发送？") cancelButtonTitle:I(@"取消") otherButtonTitles:I(@"确定") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
            STRONGSELF;
            if (buttonIndex != CMAlertViewCancel) {
                
                
                CMGroupMessageItem *item = [sself.fetchedResultsController objectAtIndexPath:[NSIndexPath indexPathForRow:indexPath.row inSection:0]];
                
                [MsgManager doSendMessageWithRepeat:item];
            }
        }]show];
    }];
    
    cell.cellDelegate = self;
    [cell setMessageItem:item];
    
    //设置头像
    NSString *imageicon ;
    if (MBlock.isFromMe(item)) {
        imageicon = kCurrUser.icon;
    }else{
        if (MBlock.isGroup(item)) {
            
            NSString *fromJid = ((CMGroupMessageItem *)item).fromJID;
            
            imageicon = [iconDictionary objectForKey:fromJid];
            
            if ( !imageicon ) {
                
                //去数据库中取icon
                __block CMUserItem *theUser = (CMUserItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMUserItem class]) withPredicate:Pre_UserJid(fromJid)];
                
                
                if ( !theUser ) {
                    
                    //数据库中没有保存此用户，则通过jid去请求，（一般都会存在，只是3.0.1升级后使用新的用户表）
                    [[CMContactManager manager] doRequestUserInfoWithJid:fromJid listener:^(CMContacts *contacts) {
                        
                        TContactsItem item;
                        
                        if(contacts && contacts->GetItem(0, item)){
                            
                            theUser = [NSEntityDescription insertNewObjectForEntityForName:@"CMUserItem" inManagedObjectContext:MessageObjectContext];

                            theUser.jid = fromJid;
                            theUser.uid = [NSString stringWithUTF8String:item.sID.c_str()];
                            theUser.icon = [NSString stringWithUTF8String:item.sIcon.c_str()];
                            theUser.name = [NSString stringWithUTF8String:item.sName.c_str()];
                            
                            [MessageObjectContext save:NULL];
                            
                            [iconDictionary setValue:theUser.icon forKey:fromJid];

                            [MsgManager  setButtton:cell.iconImgView withUrl:imageicon];


                        }
                    }];
                }
                
                imageicon = theUser.icon;
                
                [iconDictionary setValue:imageicon forKey:fromJid];

            }
            
        }else{
            imageicon= self.icon;
        }
    }
    
    [MsgManager  setButtton:cell.iconImgView withUrl:imageicon];
    
    
    cell.backgroundView = [[UIView alloc]initWithFrame:CGRectZero];
    cell.backgroundColor = [UIColor clearColor];
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 1;
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{
    return 1;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section
{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

#pragma mark -
#pragma mark CMChatMessageCellDelegate
- (void)CMChatMessageCell:(CMChatMessageCell *)chatMessageCell didSelectedAtIndex:(NSInteger)row{
    
    if (chatMessageCell.pressedState == [chatMessageCell singleTap]) {
        CMBaseItem* baseItem = [self.fetchedResultsController objectAtIndexPath:[NSIndexPath indexPathForRow:row inSection:0]];

        if (MBlock.type(baseItem) == CMMessageCourseType) {
            if ([MBlock.coursemessage(baseItem).model intValue] == 0) {
                if ([MBlock.coursemessage(baseItem).flag isEqualToString:SHARE_MODE_COURSE]) {
                    //跳转到课程
                    TClassItem item;
                    item.nModel = [MBlock.coursemessage(baseItem).model intValue];
                    strcpy(item.sID, [MBlock.coursemessage(baseItem).sID UTF8String]);
                    strcpy(item.sFlag, "course");
                    
                    CMCourseDetailControl* coursedetailControl = [[CMCourseDetailControl alloc] init];
                    [coursedetailControl setInfo:item];
                    coursedetailControl.isFromInteract = YES;
                    if (!self.isTrainChat) {
                        [self.navigationController pushViewController:coursedetailControl animated:YES];
                    }else{
                        [[(UIViewController *)[[self.view superview] nextResponder] navigationController] pushViewController:coursedetailControl animated:YES];
                    }
                        
                }else if ([MBlock.coursemessage(baseItem).flag isEqualToString:SHARE_MODE_NEWS]){
                    //跳转到资讯
                    
                    [tool ShowActivityIndicator:chatMessageCell.messageBtn];

                    WEAKSELF;
                    [[CMBrowserHandler handler] doRequestNewsById:MBlock.coursemessage(baseItem).sID success:^(CMBrowser *browser) {
                        STRONGSELF;
                        [sself gotoNews:browser];
                    } failure:^(int errorCode) {
                        if (errorCode == TResult::ENoPowerCourse) {
                            [tool ShowAlert:I(@"您无权限访问此课程")];
                           
                            
                        }else{
                            [tool ShowError:errorCode];
                        }
                    }];
                }
            }else if([MBlock.coursemessage(baseItem).model intValue]== 1){
                //跳转到课件
                [tool ShowActivityIndicator:chatMessageCell.messageBtn];
                chatMessageCell.messageBtn.enabled = NO;
                
                WEAKSELF;
                [[CMBrowserHandler handler] doRequestCoursewareById:MBlock.coursemessage(baseItem).sID success:^(CMBrowser *browser) {
                    STRONGSELF;
                    [sself gotoCourseware:browser];
                    chatMessageCell.messageBtn.enabled = YES;
                } failure:^(int errorCode) {
                    chatMessageCell.messageBtn.enabled = YES;
                    if (errorCode == TResult::ENoPowerCourse) {
                        [tool ShowAlert:I(@"您无权限访问此课程")];
                    
                    }else{
                        [tool ShowError:errorCode];
                    }
                }];
            }
        }else if (MBlock.type(baseItem) == CMMessageQAType) {
            TQAItem qaitem;
            qaitem.sID=[MBlock.qamessage(baseItem).sID UTF8String];
            qaitem.sQuestioner_fullname=[MBlock.qamessage(baseItem).name UTF8String];
            qaitem.sQuestion=[MBlock.qamessage(baseItem).question UTF8String];
            
            CMQuestionDetailControl* questiondetailcontrol = [[CMQuestionDetailControl alloc] init];               //问题的详细界面
            
            [questiondetailcontrol SetQuestionItem:qaitem];
            if(_stricmp(qaitem.sQuestioner_username.c_str(),SETTING.GetUserName()) != 0){
                questiondetailcontrol.title = [NSString stringWithFormat:I(@"%@的问题"),[NSString stringWithUTF8String:qaitem.sQuestioner_fullname.c_str()]];
            }
            else{
                questiondetailcontrol.title = [NSString stringWithFormat:I(@"我的提问")];
            }
            questiondetailcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
            questiondetailcontrol.navigationController.navigationBarHidden = NO;
            questiondetailcontrol.tabBarController.tabBar.hidden = YES;
            questiondetailcontrol.hidesBottomBarWhenPushed = YES;
            //qasearchcontrol.navigationController.delegate = self;
            //添加判断textanswer 是否第一响应标记
            NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
            [ud setObject:@"1" forKey:@"isFirstResponder"];
            
            questiondetailcontrol.view.backgroundColor = [UIColor clearColor];
            if (!self.isTrainChat) {
                [self.navigationController pushViewController:questiondetailcontrol animated:YES];
            }else{
                [[(UIViewController *)[[self.view superview] nextResponder] navigationController] pushViewController:questiondetailcontrol animated:YES];
            }
            CMRELEASE(questiondetailcontrol);
            
            
            
            
        }else if (MBlock.type(baseItem) == CMMessageImageType) {
//            CMImagePreviewViewController *controller = [[CMImagePreviewViewController alloc]init];
//            controller.currItem = baseItem;
//            [controller setTitle:I(@"预览")];
//            [self.navigationController pushViewController:controller animated:YES];
            
            CMImageMessageItem *imageMessageItem = MBlock.imagemessage(baseItem);
            if (imageMessageItem && imageMessageItem.url && imageMessageItem.thumb_url) {
                //图片上传成功
                CMImageDetailViewControl *cmimageController = [[CMImageDetailViewControl alloc]init];
                cmimageController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
                cmimageController.isURL = YES;
                [cmimageController setCMImageURL:imageMessageItem.url thumbURL:imageMessageItem.thumb_url];
                [self presentViewController:cmimageController animated:YES completion:^{
                    // presentViewController方式会隐藏键盘，所以也还原输入框到初始位置
                    [self tapPressed:nil];
                }];
            }else{
                //图片上传失败，读取本地文件
                CMImageDetailViewControl *cmimageController = [[CMImageDetailViewControl alloc]init];
                cmimageController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
                cmimageController.isURL = YES;
                cmimageController.isShowLocationImage = YES;
                [cmimageController setImage:[CMImage imageWithContentsOfFile:MBlock.content(baseItem)]];
                [self presentViewController:cmimageController animated:YES completion:^{
                    [self tapPressed:nil];
                }];
            }
            
        }else{
//            [MessageObjectContext deleteObject:baseItem];
//            [MessageObjectContext save:NULL];
        }
            
    }else{
//        UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
//        [pasteboard setString:chatMessageCell.messageLbl.text];
    }
}

- (void) CMChatMessageCell:(CMChatMessageCell *)chatMessageCell didSelectedIconAtIndex:(NSInteger)row{
    
    if (self.chatType == CMGroupChatType) {
        CMGroupMessageItem* messageItem = [self.fetchedResultsController objectAtIndexPath:[NSIndexPath indexPathForRow:row inSection:0]];
        
        CMPersonDetailyViewController * controller = [[CMPersonDetailyViewController alloc]init];
        controller.jid = messageItem.fromJID;
        controller.title = messageItem.fromName;
        controller.isFromGroupChat = YES;
        controller.isFromChat = YES;
        if (!self.isTrainChat) {
            [self.navigationController pushViewController:controller animated:YES];
        }else
            [[(UIViewController *)[self.view superview].nextResponder  navigationController] pushViewController:controller animated:YES];
    }
}

- (void)ShowImageView:(NSString*)url thumbView:(NSString *)thumburl{
    
    
}

#pragma mark -
#pragma mark UITableViewDataDelegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    CMBaseItem* item = [self.fetchedResultsController objectAtIndexPath:indexPath];
    CMChatMessageCell *cell = (CMChatMessageCell *)[self tableView:tableView cellForRowAtIndexPath:indexPath];
    
    CGFloat cellHeight = [cell getCellHeight:item];
    return cellHeight;

}

#pragma mark -
#pragma mark XMPPMethod

-(void)sendMessage
{
//    NSString *content = [self.inputTextView.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
//    if([content isEqualToString:@""]){
//        [tool ShowAlert:@"不能发送空白消息！"];
//        self.inputTextView.text = @"";
//        return;
//    }
    
//    [self sendMessageWithContent:self.inputTextView.text];
    if ([self.inputTextView.text isEqualToString:@""]) {
        [tool ShowAlert:@"不能发送空白消息！"];
        return;
    }
    [self sendMessageWithContent:self.inputTextView.text];
}

//发送文字
-(void)sendMessageWithContent:(NSString *)content
{
    self.didSendMessage = YES;
    CMBaseItem *baseItem = [CMMsgPackageUtils packageMessageWithContent:content chatType:self.chatType toName:self.toName toJid:_toJid];
    
    [MsgManager doSendMessage:baseItem];

}

//发送图片
-(void)sendMessageWithImage:(NSString *)path withVertical:(BOOL)isVertical
{
    self.didSendMessage = YES;
    
    CMBaseItem *baseItem = [CMMsgPackageUtils packageMessageWithImage:path chatType:self.chatType toName:self.toName toJid:_toJid vertical:isVertical];
    
    
    [MsgManager doSendMessage:baseItem];
}

//分享课程课件
- (void)sendMessageWithCourse{
    
    self.didSendMessage = YES;
    
    CMBaseItem *baseItem = [CMMsgPackageUtils packageMessageWithCourse:currItem chatType:self.chatType toName:self.toName toJid:_toJid];
    
    
    [MsgManager doSendMessage:baseItem];
}

- (void)finishSend
{
    [self scrollToBottomAnimated:YES];
   
}

-(void)toolsButtonPressed:(UIButton *)sender
{
    
    [self avatarBtnPressed:sender];
}

#pragma mark UIImagePickerControllerDelegate
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
    
    UIImage* oralImg=[info objectForKey:UIImagePickerControllerOriginalImage];
    [self.chatTableViewList reloadData];
    
    [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:UIStatusBarAnimationNone];
    picker.navigationBarHidden = NO;
    picker.navigationBar.translucent = NO;
    


    if (picker.sourceType == UIImagePickerControllerSourceTypePhotoLibrary) {
        
        //  保存到本地
        CMImagePreviewViewController *controller = [[CMImagePreviewViewController alloc]init];
        controller.selectedImage = oralImg;
        [controller setTitle:I(@"预览")];
        controller.delegate = self;
        [picker pushViewController:controller animated:YES];
        
    }else if (picker.sourceType == UIImagePickerControllerSourceTypeCamera){
        [picker dismissViewControllerAnimated:YES completion:^{
            [self didSendMessage:oralImg];
        }];
    }
}

//生成原图，发送
- (void)didSendMessage:(UIImage *)image
{
    WEAKSELF;
    [CMFileUtils makeAndFetchOriginalWithImage:image done:^(NSString *originalPath, BOOL isVertical) {
        STRONGSELF;
        [sself sendMessageWithImage:originalPath withVertical:isVertical];

    }];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    [picker dismissModalViewControllerAnimated:YES];
    if (__iOS7)
    {
        //[[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
        
        MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
        appDelegate.window.tintColor = UIColorRGB(0x1a6cc3);
    }
}

#pragma mark -
#pragma mark XMPPDelegate

- (void)xmppStream:(XMPPStream *)sender didReceiveMessage:(XMPPMessage *)message
{
	// A simple example of inbound message handling.

    if ([message isChatMessageWithBody])
    {
        if(![_toJid isEqualToString:[[message from] bare]])
            return;


    }
}

#pragma mark -
#pragma mark ScrollviewDelegate

- (void)scrollViewDidScroll:(UIScrollView *)scrollView{

//    if (scrollView.contentOffset.y >=0 && scrollView.contentOffset.y <= 44) {
//    
//        [self.tv setValue: forKey:];
//    }
//    NSLog(@"scrollView --->> %f",scrollView.contentOffset.y);
}

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
//    [self tapPressed:nil];
}

#pragma mark -
#pragma mark FetchResultsController
- (NSFetchedResultsController *)fetchedResultsController
{
    if (nil != _fetchedResultsController) {
        return _fetchedResultsController;
    }
    
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init] ;
    NSEntityDescription *entity = [NSEntityDescription entityForName:MBlock.chatTypeStr(self.chatType) inManagedObjectContext:MessageObjectContext];
    [fetchRequest setEntity:entity];

    //设定以时间排序
    NSSortDescriptor *sortDescriptor = [NSSortDescriptor sortDescriptorWithKey:@"sendTime" ascending:YES];
    [fetchRequest setSortDescriptors:[NSArray arrayWithObjects:sortDescriptor, nil]];
    
    //过滤数据
    NSPredicate *predicate;
    if (self.chatType == CMSingleChatType) {
        
        if ([_toJid isEqualToString:kXMPPJid]) {
            //自己发送给自己
            predicate = [NSPredicate predicateWithFormat:@" (fromJID == %@)  AND (toJID == %@) ",_toJid,_toJid];
            
        }else{
            predicate = [NSPredicate predicateWithFormat:@" (fromJID == %@)  OR (toJID == %@) ",_toJid,_toJid];
        }
        
    }else if(self.chatType == CMGroupChatType){
        
        predicate = [NSPredicate predicateWithFormat:@"roomJID== %@",_toJid];
    }
    
    [fetchRequest setPredicate:predicate];
    
    NSError *error = NULL;
    int rCount = [MessageObjectContext countForFetchRequest:fetchRequest error:&error];

    [fetchRequest setFetchBatchSize:CacheMaxForChatCount];
    
    if (rCount - mcount > 0) {
        [fetchRequest setFetchOffset:rCount - mcount];
    } else {
        [fetchRequest setFetchOffset:0];
    }
    
    _fetchedResultsController = [[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest managedObjectContext:MessageObjectContext sectionNameKeyPath:nil cacheName:nil];
    _fetchedResultsController.delegate = self;
   
    if (![_fetchedResultsController performFetch:&error]) {
        NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        abort();
    }
    return _fetchedResultsController;
}

#pragma mark -
#pragma mark FetchResultsControllerDelegate

- (void)controllerWillChangeContent:(NSFetchedResultsController *)controller {
    // The fetch controller is about to start sending change notifications, so prepare the table view for updates.
//    [self.chatTableViewList beginUpdates];
}

- (void)controller:(NSFetchedResultsController *)controller didChangeObject:(id)anObject atIndexPath:(NSIndexPath *)indexPath forChangeType:(NSFetchedResultsChangeType)type newIndexPath:(NSIndexPath *)newIndexPath {
//    switch(type) {
//            
//        case NSFetchedResultsChangeInsert:
//        {
//            [self.chatTableViewList insertRowsAtIndexPaths:[NSArray arrayWithObject:newIndexPath] withRowAnimation:UITableViewRowAnimationNone];
//        }
//            break;
//            
//        case NSFetchedResultsChangeDelete:
//            [self.chatTableViewList deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationNone];
//            break;
//        case NSFetchedResultsChangeUpdate:
//            [self.chatTableViewList reloadRowsAtIndexPaths:[NSArray arrayWithObject:newIndexPath] withRowAnimation:UITableViewRowAnimationNone];
//            break;
//        default:
//            break;
//    }
}

- (void)controllerDidChangeContent:(NSFetchedResultsController *)controller {
    // The fetch controller has sent all current change notifications, so tell the table view to process all updates.
//    id <NSFetchedResultsSectionInfo> sectionInfo = [[self.fetchedResultsController sections] objectAtIndex:0];
//
//    NSInteger count = [sectionInfo numberOfO  bjects];
//    [self.chatTableViewList endUpdates];
   
    [self didsendMessage];
}

- (void) didsendMessage {

    [self.chatTableViewList reloadData];
    
    if ( shareAlertHide && self.draft && self.draft.length > 0 ) {
        
        //避免分享课件时,丢失已保存的草稿
        return;
    }
   
//    self.inputTextView.text = @"";
//    self.commitBtn.enabled = NO;
    self.inputTextView.text = @"";
    self.commitBtn.enabled = YES;
    
    [UIView animateWithDuration:ANIMATEDURATIONDEFAULT animations:^{
        //是否为输入状态
        if ([self keyBoardHide]) {
            [self.inputView setFrameY:UI_IOS_WINDOW_HEIGHT - 20 - kChatInputViewHeight - 44 Height:kChatInputViewHeight ];
            [self.chatTableViewList setFrameY:0+topHeight Height: UI_IOS_WINDOW_HEIGHT-kChatInputViewHeight-20-44-topHeight];
            [self scrollToBottomAnimated:YES];
            
        }else{
            //输入状态，tableview是否超出frame
            if ([self beyondTableviewHeight]) {
                //当前是键盘输入，还是表情输入
                if (self.avatarBtn.selected) {
                    [self.inputView setFrameY:UI_IOS_WINDOW_HEIGHT - 20 - kChatInputViewHeight - 44 - KEYBOARDHEIGHT_DEFALUT Height:kChatInputViewHeight ];
                    
                    int beyondKeyBoardHeight = keyBoardHieght - KEYBOARDHEIGHT_DEFALUT;
                    if ( beyondKeyBoardHeight > 0) {
                        //中文键盘
                        [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance]) + beyondKeyBoardHeight + topHeight Height:UI_IOS_WINDOW_HEIGHT-64-kChatInputViewHeight-topHeight];
                    }else{
                        //非中文键盘
                        [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance])+topHeight Height:UI_IOS_WINDOW_HEIGHT-64-kChatInputViewHeight-topHeight];
                    }
                }else{
                    [self.inputView setFrameY:UI_IOS_WINDOW_HEIGHT - 20 - kChatInputViewHeight - 44 - keyBoardHieght Height:kChatInputViewHeight ];
                    [self.chatTableViewList setFrameY:-fabsf([self keyBoardFromLastCell_distance]) Height:UI_IOS_WINDOW_HEIGHT-64-kChatInputViewHeight];
                }
                [self scrollToBottomAnimated:YES];
            }
        }
    }];
}

//tableview滑到最后一行
- (void)scrollToBottomAnimated:(BOOL)animated
{
    NSInteger rows = [self.chatTableViewList numberOfRowsInSection:0];
    
    if(rows > 0) {
        [self.chatTableViewList scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:rows - 1 inSection:0]
                                      atScrollPosition:UITableViewScrollPositionBottom
                                              animated:animated];
    }
}

- (void)scrollToUpWithIndex:(int)index animated:(BOOL)animated
{
    
    [self.chatTableViewList scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:index inSection:0]
                                  atScrollPosition:UITableViewScrollPositionTop
                                          animated:animated];
}

-(void)gotoCourseware:( CMBrowser* )tempBrowser
{
    
    [tool DisimissActivityIndicator];
    
    TBrowserItem* item = new TCoursewareItem();
    
    if(!tempBrowser->GetItem(0, item))
        return;
    
    CMNavgateItem* nav = [[CMNavgateItem alloc] init];
    
    
	[nav NavgateItem:(UIViewController*)self item:*item];
    
    SAFEDELETE(item);
	
    CMRELEASE(nav);
    
}

-(void)gotoNews:( CMBrowser* )tempBrowser
{
    [tool DisimissActivityIndicator];
    
    TBrowserItem *item = new TBrowserItem();
    
    if(!tempBrowser->GetItem(0, item))
    {
        SAFEDELETE(item);
        return;
    }
    
    CMNavgateItem* nav = [[CMNavgateItem alloc] init];
    
	[nav NavgateItem:(UIViewController*)self item:*item];
    
    SAFEDELETE(item);
	
    CMRELEASE(nav);
    
}

- (void)dealloc{
    _fetchedResultsController.delegate = nil;
    
}
@end
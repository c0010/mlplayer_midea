//
//  CMGroupManager.m
//  MLPlayer
//
//  Created by water on 14-7-23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMGroupManager.h"
#import "MLPlayerAppDelegate.h"
#include "cmsettings.h"
#include "cmmyinfo.h"
#import "cmfileinfo.h"
#import "cmupload.h"
#import "CMCoreDataUtils.h"
#import "NSDate+Helper.h"

#define HistoryElement_Header @"history"
#define HistoryElement_Maxchars @"maxchars"
#define HistoryElement_Since @"since"

@implementation CMGroupManager

+ (id)manager{
    return [[CMGroupManager alloc] init];
}

+ (id)managerDelegate{
    return [[CMGroupManager alloc] initDelegate];
}

- (id)initDelegate
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

-(void)joinWithJid:(NSString *)jid withPassword:(NSString *)pwd
{
    [self joinWithJid:jid withPassword:pwd isNewAdd:NO];
}

-(void)joinWithJid:(NSString *)jid withPassword:(NSString *)pwd success:(Success)success
{
    [self joinWithJid:jid withPassword:pwd isNewAdd:NO success:success];
}

-(void)joinWithJid:(NSString *)jid withPassword:(NSString *)pwd isNewAdd:(BOOL)isNewAdd success:(Success)success
{
    if (!jid || [jid isEqualToString:@""]) {
        return;
    }
    
    self.success = success;
    
    [self joinWithJid:jid withPassword:pwd isNewAdd:isNewAdd];
}

-(void)joinWithJid:(NSString *)jid withPassword:(NSString *)pwd isNewAdd:(BOOL)isNewAdd
{
    
    if (!jid || [jid isEqualToString:@""]) {
        return;
    }
    
    XMPPRoom *room = [[XMPPRoom alloc]initWithRoomStorage:self jid:[XMPPJID jidWithString:jid]];
    [room activate:XmppHandler.xmppStream];
    
    NSXMLElement *historyElement = [NSXMLElement elementWithName:HistoryElement_Header];
    
    if ( isNewAdd ) {
        
        //新加入群，不接收离线消息
        [historyElement addAttributeWithName:HistoryElement_Maxchars numberValue:[NSNumber numberWithInt:0]];
        [historyElement addAttributeWithName:HistoryElement_Since stringValue:[NSDate stringFromDate:[NSDate date]]];
    }else{
        
        //已存在的群，离线消息从 该群最后一条缓存消息为始 开始接收离线消息
        
        //设定以时间排序
        NSSortDescriptor *sortDescriptor = [NSSortDescriptor sortDescriptorWithKey:@"sendTime" ascending:NO];
        //获取最后一条消息
        CMGroupMessageItem* messageItem = (CMGroupMessageItem *)[CMCoreDataUtils fetchManagedObject:@"CMGroupMessageItem" withPredicate:Pre_RoomJid(jid) sortDescriptor:sortDescriptor];
        
        NSDate *lastDate ;
        
        if ( messageItem ) {
            lastDate = messageItem.sendTime;
        }else{
            lastDate = [NSDate date];
        }
        
        [historyElement addAttributeWithName:HistoryElement_Maxchars numberValue:[NSNumber numberWithInt:20]];
        [historyElement addAttributeWithName:HistoryElement_Since stringValue:[NSDate stringFromDate:lastDate]];
        
    }
    
    [room joinRoomUsingNickname:kXMPPJid history:historyElement password:pwd];
}


- (void)leaveWithJid:(NSString *)jid{
    
    if (!jid || [jid isEqualToString:@""]) {
        return;
    }
//    XMPPRoom *xmppRoom = [[XMPPRoom alloc]initWithRoomStorage:self jid:[XMPPJID jidWithString:jid]];
//    [xmppRoom activate:nil];
//    
//    [xmppRoom leaveRoom];
//    
}

- (void)leaveWithJid:(NSString *)jid success:(Success)success{

    self.success = success;
    
    [self leaveWithJid:jid];
}

#pragma mark -
#pragma mark XMPPRoomStorage

- (BOOL)configureWithParent:(XMPPRoom *)aParent queue:(dispatch_queue_t)queue{
    return YES;
}

- (void)handlePresence:(XMPPPresence *)presence room:(XMPPRoom *)room{
    
}

- (void)handleIncomingMessage:(XMPPMessage *)message room:(XMPPRoom *)room{
    
}

- (void)handleOutgoingMessage:(XMPPMessage *)message room:(XMPPRoom *)room{
    
}

- (void)handleDidLeaveRoom:(XMPPRoom *)xmppRoom{
    
    [self executeBlock:xmppRoom];
    
    [xmppRoom removeDelegate:self];
}



- (void)handleDidJoinRoom:(XMPPRoom *)xmppRoom withNickname:(NSString *)nickname{
    [self performSelectorOnMainThread:@selector(updateJoinState:) withObject:xmppRoom waitUntilDone:NO];
    [self executeBlock:xmppRoom];
    
    [xmppRoom removeDelegate:self];
}

- (void)updateJoinState:(XMPPRoom *)room{
    NSError *error = NULL;

    NSString *roomJid = [room.roomJID bare];
    //保存是否登入群
    CMGroupItem *item = (CMGroupItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMGroupItem class]) withPredicate:Pre_RoomJid(roomJid)];

    if (item) {
        item.isJoined = [NSNumber numberWithBool:room.isJoined];
        [MessageObjectContext save:&error];
    }
    CMDialogueItem *dialogueItem =[[XMPPChatMessageCoreDataStorage sharedInstance] dialogueItemExistForRoomJid:roomJid];
    
    if (dialogueItem) {
        dialogueItem.isJoined = [NSNumber numberWithBool:room.isJoined];
        [MessageObjectContext save:&error];
    }
}

- (void)executeBlock:(XMPPRoom *)room{
    
    if (self.success) {
        self.success(room);
        self.success = nil;
    }
    
}


//初始化群
- (void)initGroupInfoItem{
    if(!groupManagerListener){
        groupManagerListener=new CMGroupManagerListener();
    }
    if (!m_TGroupInfoItem) {
        m_TGroupInfoItem = new TGroupInfoItem();
    }
    
    m_TGroupInfoItem->SetUserData((__bridge void *)self);
    m_TGroupInfoItem->SetListener(groupManagerListener, NULL);
}

//初始化群
- (void)initGroup{
    if(!groupManagerListener){
        groupManagerListener=new CMGroupManagerListener();
    }
    if (!m_pGroup) {
        m_pGroup = new CMGroup();
    }
    
    m_pGroup->SetUserData((__bridge void *)self);
    m_pGroup->SetListener(groupManagerListener, NULL);
}


//创建群
- (void)doCreateGroupWithName:(NSString *)name desc:(NSString *)desc flag:(int)flag success:(GroupManagerSuccess)success failure:(GroupManagerFailure)failure
{
    self.groupManagerSuccess = success;
    self.groupManagerFailure = failure;

    if (!createGroupListener) {
        createGroupListener = new CMCreateGroupListener();
    }
    CMFileInfo *file = new CMFileInfo();
    CMFileUpload::GetInstance()->SetListener(createGroupListener);
    CMFileUpload::GetInstance()->SetUserData( (__bridge void*)self);
    
    file->CreateNewRoom([name UTF8String], [desc UTF8String], NULL, flag);
    
    CMFileUpload::GetInstance()->Append(*file);
}

//上传群头像
- (void)doUploadGroupHeaderWithRoomid:(NSString *)rommid imagePath:(NSString *)imagePath success:(UploadGroupHeaderSuccessCallBack)success failure:(UploadGroupHeaderFailureCallBack)failure{
    
    self.uploadGroupHeaderSuccessCallBack = success;
    self.uploadGroupHeaderFailureCallBack = failure;
    
    CMFileInfo *file = new CMFileInfo();
    if (!uploadGroupHeaderListener) {
        uploadGroupHeaderListener = new CMUploadGroupHeaderListener();
    }
    CMFileUpload::GetInstance()->SetListener(uploadGroupHeaderListener);
    CMFileUpload::GetInstance()->SetUserData((__bridge void*)self);
    
    file->UpLoadGroupHeader([rommid UTF8String], [imagePath UTF8String]);
    
    CMFileUpload::GetInstance()->Append(*file);
}

//退出群
- (void)doExitGroup:(NSString*)roomID success:(GroupManagerSuccessNone)success{
    
    self.groupManagerSuccessNone = success;
    
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    m_TGroupInfoItem->ExitGroup();
}

//解散群
- (void)doDisblanGroup:(NSString*)roomID success:(GroupManagerSuccessNone)success{
    
    self.groupManagerSuccessNone = success;
    
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    m_TGroupInfoItem->DisbandGroup();
}

//邀请群成员
- (void)doInviteToGroup:(NSString*)roomID sidarray:(NSString *)sidarray success:(GroupManagerSuccessNone)success{
    
    self.groupManagerSuccessNone = success;
    
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    m_TGroupInfoItem->InviteToGroup([sidarray cStringUsingEncoding:NSUTF8StringEncoding]);
}


//请求入群
- (void)doRequestEnterGroup:(NSString*)roomID key:(NSString *)key success:(GroupManagerSuccessNone)success failure:(GroupManagerFailureNone)failure{
    
    self.groupManagerSuccessNone = success;
    self.groupManagerFailureNone = failure;

    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    if (key) {
        m_TGroupInfoItem->RequestEnterGroup([key UTF8String]);
    }else{
        m_TGroupInfoItem->RequestEnterGroup(NULL);
    }
}

//申请加入群
- (void)doApplyEnterGroup:(NSString *)roomID key:(NSString *)key success:(GroupManagerSuccessNone)success
{
    
    self.groupManagerSuccessNone = success;

    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    if (key) {
        m_TGroupInfoItem->ApplyEnterGroup([key UTF8String]);
    }else{
        m_TGroupInfoItem->ApplyEnterGroup(NULL);
    }
}

//通过某用户的进群申请
- (void)doAcceptUserApply:(NSString *)roomID sid:(NSString *)sid success:(GroupManagerSuccessNone)success failure:(GroupManagerFailureNone)failure{
    
    self.groupManagerSuccessNone = success;
    
    self.groupManagerFailureNone = failure;
    
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    
    m_TGroupInfoItem->AcceptUserApply([sid UTF8String]);
}

//拒绝某用户的进群申请
- (void)doRefuseUserApply:(NSString*)roomID sid:(NSString *)sid success:(GroupManagerSuccessNone)success{

    self.groupManagerSuccessNone = success;
    
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    
    m_TGroupInfoItem->RefuseUserApply([sid UTF8String],NULL);
}

//踢人
- (void)doKickGroupOccupant:(NSString*)roomID sid:(NSString *)sid success:(GroupManagerSuccessNone)success{
    
    self.groupManagerSuccessNone = success;
    
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    m_TGroupInfoItem->KickGroupOccupant([sid UTF8String]);
}

//设置管理员
- (void)doSetGroupAdmin:(NSString*)roomID sid:(NSString *)sid success:(GroupManagerSuccessNone)success{
    
    self.groupManagerSuccessNone = success;
    
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    m_TGroupInfoItem->SetGroupAdmin([sid UTF8String]);
}

//取消管理员
- (void)doRemoveGroupAdmin:(NSString*)roomID sid:(NSString *)sid success:(GroupManagerSuccessNone)success{
    
    self.groupManagerSuccessNone = success;
    
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    m_TGroupInfoItem->RemoveGroupAdmin([sid UTF8String]);
}

//获取群详细信息
- (void)doDetailyGroup:(NSString*)roomID success:(GroupManagerSuccess)success failure:(GroupManagerFailure)failure{
    
    if (!roomID) {
        return;
    }
    
    self.groupManagerSuccess = success;
    self.groupManagerFailure = failure;

    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    m_TGroupInfoItem->RequestDetailInfo();
}

//更新名称
- (void)doUpdateNameWithroomID:(NSString*)roomID name:(NSString *)name success:(GroupManagerSuccessNone)success
{
    self.groupManagerSuccessNone = success;
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    m_TGroupInfoItem->sName = [name UTF8String];
    
    m_TGroupInfoItem->updateGruopInfoWithName([name UTF8String]);
}

//更新简介
- (void)doUpdateDescWithroomID:(NSString*)roomID desc:(NSString *)desc success:(GroupManagerSuccessNone)success
{
    self.groupManagerSuccessNone = success;
    
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    m_TGroupInfoItem->sDescription = [desc UTF8String];
    
    m_TGroupInfoItem->updateGruopInfoWithDesc([desc UTF8String]);
}

//更新权限
- (void)doUpdateFlagWithroomID:(NSString*)roomID flag:(int)flag success:(GroupManagerSuccessNone)success
{
    self.groupManagerSuccessNone = success;
    
    [self initGroupInfoItem];
    
    m_TGroupInfoItem->sID = [roomID UTF8String];
    m_TGroupInfoItem->nFlag = flag;
    
    char sflag[16];
    sprintf(sflag, "%d", flag);
    
    m_TGroupInfoItem->updateGruopInfoWithPermis(sflag);
}

//搜索群
- (void)doSearchGroup:(NSString *)searchText success:(GroupManagerGroupSuccess)success failure:(GroupManagerFailure)failure{
    
    self.groupManagerGroupSuccess = success;
    self.groupManagerFailure = failure;

    [self initGroup];
    
    m_pGroup->SearchGroup([searchText UTF8String]);
}

//获取群列表
- (void)doRequestMyGroup:(GroupManagerGroupSuccess)success failure:(GroupManagerFailureNone)failure{
    
    self.groupManagerGroupSuccess = success;
    self.groupManagerFailureNone = failure;

    [self initGroup];
    
    m_pGroup->RequestMyGroup();
}

- (void)doGroupManagerSuccess{
    
    if (self.groupManagerSuccess) {
        self.groupManagerSuccess(m_TGroupInfoItem);
    }
    
    if (self.groupManagerSuccessNone) {
        self.groupManagerSuccessNone();
    }
    
    if (self.groupManagerGroupSuccess) {
        self.groupManagerGroupSuccess(m_pGroup);
    }
}

- (void)doGroupManagerFailure:(int) errorCode{
    
    if (!self.groupManagerFailureNone) {
        
        if (self.groupManagerFailure) {
            self.groupManagerFailure(errorCode);
            self.groupManagerFailure = nil;
        }
        
        //自动显示对话框
        if (errorCode != TResult::ENothing) {
            
            [tool ShowError:errorCode];

        }
    }else{
        self.groupManagerFailureNone(errorCode);
        self.groupManagerFailureNone = nil;
    }
}

- (void) clear {

//    SAFEDELETE(m_pGroup);
//    SAFEDELETE(m_TGroupInfoItem);
//    SAFEDELETE(createGroupListener);
//    SAFEDELETE(uploadGroupHeaderListener);
//    SAFEDELETE(groupManagerListener);

    if (self.groupManagerSuccess) {
        self.groupManagerSuccess = nil;
    }
    
    if (self.groupManagerSuccessNone) {
        self.groupManagerSuccessNone = nil;
    }
    
    if (self.groupManagerGroupSuccess) {
        self.groupManagerGroupSuccess = nil;
    }
    
    if (self.groupManagerFailureNone) {
        self.groupManagerFailureNone = nil;
    }
    
    if (self.groupManagerFailure) {
        self.groupManagerFailure = nil;
    }
}
@end

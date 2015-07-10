//
//  CMXmppHandler.m
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-5.
//  Copyright (c) 2014年 w. All rights reserved.
//
#import "cmsettings.h"

#import "CMXmppHandler.h"
#import "CMCoreDataUtils.h"
#import "CMInteractModel.h"
#import "CMGroupManager.h"
#import "CMContactManager.h"
#import "CMParseXmppMessage.h"
#import "CMChatViewController.h"
#import "CMSysMessageDetailyViewController.h"

#define kRealUserIdLenght 36//正确的用户id长度36，错误id（极光）32

@implementation CMXmppHandler


+ (CMXmppHandler*)sharedInstance
{
    static CMXmppHandler *sharedInstance;
    //检查是否运行过
    static dispatch_once_t predicate;
    
    dispatch_once(&predicate, ^{
        if(sharedInstance == nil)
            sharedInstance = [[CMXmppHandler alloc] init];
    });
    
    return sharedInstance;
    
}

- (id)init
{
    self = [super init];
    if (self) {
        self.xmppStream = [[XMPPStream alloc]init];

#if !TARGET_IPHONE_SIMULATOR
        self.xmppStream.enableBackgroundingOnSocket = YES;
#endif

        self.xmppReconnect = [[XMPPReconnect alloc] init];

        [self.xmppReconnect activate:self.xmppStream];
        [self.xmppStream addDelegate:self delegateQueue:dispatch_get_main_queue()];

        self.xmppRosterStorage = [[XMPPRosterCoreDataStorage alloc]init];

        customCertEvaluation = YES;
        
    }
    return self;
}

-(void)addDelegateToXMPPStream:(id<XMPPStreamDelegate>)object
{
    [self.xmppStream addDelegate:object delegateQueue:dispatch_get_main_queue()];

}

- (BOOL)connectWithSuccess:(ConnectSuccess)success failure:(ConnectFailure)failure{

    self.connectSuccess = success;
    self.connectFailure = failure;

    
   return  [self connect];

}


- (BOOL)connect
{
	if (![self.xmppStream isDisconnected]) {
		return YES;
	}

    self.hostname = [NSString stringWithUTF8String:SETTING.GetXMPPHostname()];

    self.jid = [NSString stringWithFormat:@"%@/ios",kXMPPJid];

    self.pwd = [NSString stringWithUTF8String:SETTING.GetXMPPPwd()];


    [self.xmppStream setHostName:self.hostname];


	if(self.jid == nil || self.pwd == nil || self.hostname == nil || [self.jid length] == 0 || [self.pwd length]==0 || [self.hostname length]==0) {
		return NO;
	}

    //初始化Jid
	[self.xmppStream setMyJID:[XMPPJID jidWithString:self.jid]];

    //连接xmpp服务器
	NSError *error = nil;
	if (![self.xmppStream connectWithTimeout:XMPPStreamTimeoutNone error:&error])
	{
		UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Error connecting"
		                                                    message:@"See console for error details."
		                                                   delegate:nil
		                                          cancelButtonTitle:@"Ok"
		                                          otherButtonTitles:nil];
		[alertView show];

        [self loginXmppServiceFailure];
		return NO;
	}
    
	return YES;
}

//身份认证
- (void)xmppStreamDidConnect:(XMPPStream *)sender
{
    isXmppConnected = YES;
    
    NSError *error = nil;
    if (![[self xmppStream] authenticateWithPassword:self.pwd error:&error])
    {
        NSLog(@"authenticate error:%@",error.description);
    }
}

- (void)xmppStreamDidSecure:(XMPPStream *)sender{
    
}

//身份认证成功
- (void)xmppStreamDidAuthenticate:(XMPPStream *)sender{
    
    //上线
    [self goOnline];
    
    [self loginXmppServiceSuccess];
}

- (void)xmppStream:(XMPPStream *)sender didNotAuthenticate:(NSXMLElement *)error
{
    [self loginXmppServiceFailure];
    
}

- (void)xmppStreamConnectDidTimeout:(XMPPStream *)sender{
    
    [self loginXmppServiceFailure];
    
}

//xmpp连接成功
- (void)loginXmppServiceSuccess{
    
    if (self.connectSuccess) {
        self.connectSuccess();
    }
    
    NSArray *dataArray = [CMCoreDataUtils fetchManagedObjects:NSStringFromClass([CMGroupItem class])];

    for (CMGroupItem *item in dataArray) {
        //进入房间
        //[[CMGroupManager manager] joinWithJid:item.roomJID withPassword:item.password];
        [[CMGroupManager managerDelegate] joinWithJid:item.roomJID withPassword:item.password success:^(XMPPRoom *room){
            
        }];

    }
    
    //培训班交流区进入房间
    NSArray *trainDataArray = [CMCoreDataUtils fetchManagedObjects:NSStringFromClass([CMDialogueItem class])];
    
    for (CMDialogueItem *item in trainDataArray) {
        if ([item.roomJID rangeOfString:@"@train"].location != NSNotFound) {
            //进入房间
            [[CMGroupManager managerDelegate] joinWithJid:item.roomJID withPassword:item.password];
        }
    }
}

//xmpp连接失败
- (void)loginXmppServiceFailure{
    if (self.connectFailure) {
        self.connectFailure();
    }
}

-(void)setJid:(NSString*)jid andPwd:(NSString*)pwd
{
    self.jid = jid;
    self.pwd = pwd;

    [self.xmppStream setMyJID:[XMPPJID jidWithString:self.jid]];
}
#pragma mark -
#pragma mark XMPP XMPPRoomStorage


- (BOOL)configureWithParent:(XMPPRoom *)aParent queue:(dispatch_queue_t)queue
{

    return YES;
}

/**
 * Updates and returns the occupant for the given presence element.
 * If the presence type is "available", and the occupant doesn't already exist, then one should be created.
 **/
- (void)handlePresence:(XMPPPresence *)presence room:(XMPPRoom *)room
{

}

/**
 * Stores or otherwise handles the given message element.
 **/
- (void)handleIncomingMessage:(XMPPMessage *)message room:(XMPPRoom *)room
{

}
- (void)handleOutgoingMessage:(XMPPMessage *)message room:(XMPPRoom *)room
{

}

/**
 * Handles leaving the room, which generally means clearing the list of occupants.
 **/
- (void)handleDidLeaveRoom:(XMPPRoom *)room
{

}
#pragma mark -
#pragma mark XMPP ReconnectDelegate


- (void)xmppReconnect:(XMPPReconnect *)sender didDetectAccidentalDisconnect:(SCNetworkReachabilityFlags)connectionFlags{


}

- (BOOL)xmppReconnect:(XMPPReconnect *)sender shouldAttemptAutoReconnect:(SCNetworkReachabilityFlags)reachabilityFlags{
    return YES;
}

- (void)xmppRoomDidJoin:(XMPPRoom *)sender{

}

#pragma mark -
#pragma mark XMPP StreamDelegate

- (void)xmppStream:(XMPPStream *)sender socketDidConnect:(GCDAsyncSocket *)socket
{
//	DDLogVerbose(@"%@: %@", THIS_FILE, THIS_METHOD);
}

- (void)xmppStream:(XMPPStream *)sender willSecureWithSettings:(NSMutableDictionary *)settings
{

	NSString *expectedCertName = [self.xmppStream.myJID domain];
	if (expectedCertName)
	{
		[settings setObject:expectedCertName forKey:(NSString *)kCFStreamSSLPeerName];
	}

	if (customCertEvaluation)
	{
//		[settings setObject:@(YES) forKey:GCDAsyncSocketManuallyEvaluateTrust];
	}
}

//上线
-(void)goOnline
{
    XMPPPresence *presence = [XMPPPresence presence]; // type="available" is implicit

    NSString *domain = [self.xmppStream.myJID domain];

	[[self xmppStream] sendElement:presence];

}

//离线
-(void)goOffline
{
	XMPPPresence *presence = [XMPPPresence presenceWithType:@"unavailable"];

	[[self xmppStream] sendElement:presence];

    [[self xmppStream] disconnect];

}

- (BOOL)xmppStream:(XMPPStream *)sender didReceiveIQ:(XMPPIQ *)iq
{

	return NO;
}

- (void)xmppStream:(XMPPStream *)sender didReceiveMessage:(XMPPMessage *)message
{

	// A simple example of inbound message handling.

    NSString *type = [message type] ;
    
    if([type isEqualToString:MsgTypeError])
    {
        return;
    }
    
    if([type isEqualToString:MsgTypeGroupChat])
    {
        if(![[[message from] resource] isEqualToString:kXMPPJid]){
            [self doWithGroupChatMessage:sender XMPPMessage:message];
        }
        else{
            //离线消息接收自己的
            if ([message wasDelayed]) {
                [self doWithGroupChatMessage:sender XMPPMessage:message];
            }
        }
        return;
    }
    
    NSString *fromJID = [[message from] bare];
    
    if(![fromJID isEqualToString:kXMPPJid]){
        
        
        if([fromJID isEqualToString:kXMPPManager])
        {
            //保存到系统消息
            [self saveSystemMessage:message];
        }else
        {
            //保存到普通消息
            [self saveNormalMessage:message];
        }
    }
    
    
}

- (void)xmppStream:(XMPPStream *)sender didFailToSendMessage:(XMPPMessage *)message error:(NSError *)error{


}

- (void)xmppStream:(XMPPStream *)sender didReceivePresence:(XMPPPresence *)presence
{

}

- (void)xmppStream:(XMPPStream *)sender didReceiveError:(id)error
{

}

- (void)xmppStreamDidDisconnect:(XMPPStream *)sender withError:(NSError *)error
{

	if (!isXmppConnected)
	{

	}
    
}

- (void) saveRecentContactInfo:(CMMessageItem *)messageItem{
    
    
    NSError *error = NULL;
    
    int type = messageItem.type;
    NSString *icon = messageItem.icon;
    NSString *fromName = messageItem.fromName;
    NSString *content;
    
    if (type == CMMessageCourseType) {
        content = [NSString stringWithFormat:@"%@ %@",I(@"[分享]"),messageItem.coursemessage.title];
    }else if(type == CMMessageQAType){
        content = [NSString stringWithFormat:@"%@ %@",I(@"[分享]"),messageItem.qamessage.question];
    }else if(type == CMMessageImageType){
        content = I(@"[图片]");
    }else{
        content = messageItem.content;
    }
    
    //存入对话信息
    CMDialogueItem *dialogueItem =[[XMPPChatMessageCoreDataStorage sharedInstance] dialogueItemExistForJid:messageItem.fromJID];
    
    BOOL unread;//此条消息是否为未读消息；
    if(!dialogueItem)
    {
        unread = YES;
        
        dialogueItem = [NSEntityDescription insertNewObjectForEntityForName:@"CMDialogueItem" inManagedObjectContext:MessageObjectContext];
        
        dialogueItem.icon = icon;
        dialogueItem.fromName = fromName;
        dialogueItem.fromJID= messageItem.fromJID;
        dialogueItem.unread = 1;
        dialogueItem.flag = 0;
        dialogueItem.fromID = messageItem.uID;
        
        if([dialogueItem.fromJID isEqualToString:kXMPPManager]){
            dialogueItem.fromName = I(@"系统信息");
        }
        dialogueItem.lastMessage = content;
        
        [MessageObjectContext save:&error];
    }
    else
    {
        dialogueItem.icon = [icon isEqualToString:@""] ? dialogueItem.icon : icon;
        dialogueItem.lastMessage = content;
        dialogueItem.fromName = [fromName isEqualToString:@""] ? dialogueItem.fromName : fromName;
        dialogueItem.sendTime = [NSDate date];
        dialogueItem.flag = 0;
        
        if([dialogueItem.fromJID isEqualToString:kXMPPManager]){
            dialogueItem.fromName = I(@"系统信息");
            if (![self isSystemFront] && (!messageItem.sysmessage.skip)) {
                //收到系统消息标记为未读消息
                
                dialogueItem.unread += 1;
                
                unread = YES;
            }
        }else{
            if (![self isChatFront:dialogueItem.fromJID]) {
                //当前界面可见时，收到消息为未读消息
                dialogueItem.unread += 1;
                
                unread = YES;
            }
        }
        
        if (![MessageObjectContext save:&error]) {
            //            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
    }
    
    if (unread) {
        //未读消息，更新Badge；
        [CMCoreDataUtils updateBadgeValueWithTabBar:self.interactNavigationController.tabBarItem];
    }
}

- (void) saveNormalMessage:(XMPPMessage *)message
{
    CMMessageItem* messageItem = [NSEntityDescription insertNewObjectForEntityForName:@"CMMessageItem" inManagedObjectContext:MessageObjectContext];
    messageItem.content = [message body];
    messageItem.fromJID = [[message from] bare];
    messageItem.mID = [message elementID];
    
    messageItem.isFromMe = [messageItem.fromJID isEqualToString:kXMPPJid];
    messageItem.toJID = kXMPPJid;
    messageItem.toName = kCurrUser.name;
    
    //存入用户信息
    NSXMLElement *userInfo  = [message elementForName:@"userinfo" xmlns:@"xmpp:wunding"];
    
    NSString *uid = [userInfo attributeStringValueForName:@"id"];
    NSString *icon = [userInfo attributeStringValueForName:@"icon"];
    NSString *name = [userInfo attributeStringValueForName:@"name"];
    
    CMUserItem *user = (CMUserItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMUserItem class]) withPredicate:Pre_UserJid(messageItem.fromJID)];
    
    if (!user || (user && !user.uid)) {
        user = [NSEntityDescription insertNewObjectForEntityForName:@"CMUserItem" inManagedObjectContext:MessageObjectContext];
        user.icon = icon;
        user.name = name;
        user.jid = messageItem.fromJID;
        
        //接收到错误的userid，极光id
        if (uid.length != kRealUserIdLenght) {
            
            WEAKSELF;
            [[CMContactManager manager] doRequestUserInfoWithJid:messageItem.fromJID listener:^(CMContacts *contacts) {
                STRONGSELF;
                TContactsItem item;
                
                if(contacts && contacts->GetItem(0, item)){
                    
                    user.uid = [NSString stringWithUTF8String:item.sID.c_str()];
                    user.name = [NSString stringWithUTF8String:item.sName.c_str()];
                    user.icon = [NSString stringWithUTF8String:item.sIcon.c_str()];

                    
                    [sself handleMessage:messageItem :user :message];
                    
                    //保存到最近联系人
                    [sself saveRecentContactInfo:messageItem];
                }
            }];
        }else{
            
            user.uid = uid;
            
            
            
            [self handleMessage:messageItem :user :message];
            
            //保存到最近联系人
            [self saveRecentContactInfo:messageItem];
        }
    }else{
        if (icon && icon.length > 0 && (![user.icon isEqualToString:icon])) {
            user.icon = icon;
        }
        
        
        
        [self handleMessage:messageItem :user :message];
        
        //保存到最近联系人
        [self saveRecentContactInfo:messageItem];
    }
}

//保存消息
- (CMMessageItem *)handleMessage:(CMMessageItem *)item :(CMUserItem *)user :(XMPPMessage *)message{
    
    
    item.uID = user.uid;
    item.icon = user.icon;
    item.fromName = user.name;
    
    item.sendTime = [NSDate date];
    item.isShowSendTime = [CMCoreDataUtils isRequireSortMsgWithJid:item.fromJID type:CMSingleChatType date:item.sendTime];
    //存入课程，课件，资讯分享信息
    NSXMLElement *browseitem  = [message elementForName:@"browseitem" xmlns:@"xmpp:wunding:share"];
    
    if ((![message isChatMessageWithBody]) &&  browseitem) {
        item.type = CMMessageCourseType;
        
        item.coursemessage = [CMParseXmppMessage parseXmppMessageToCourse:message];
    }
    
    //存入问答分享信息
    NSXMLElement *qaitem  = [message elementForName:@"qaitem" xmlns:@"xmpp:wunding:qa"];
    
    if ((![message isChatMessageWithBody]) &&  qaitem) {
        item.type = CMMessageQAType;
        
        item.qamessage = [CMParseXmppMessage parseXmppMessageToQa:message];
    }
    
    NSXMLElement *imageitem  = [message elementForName:@"imageitem" xmlns:@"xmpp:wunding:image"];
    if ((![message isChatMessageWithBody]) &&  imageitem) {
        item.type = CMMessageImageType;
        
        item.imageMessage = [CMParseXmppMessage parseXmppMessageToImage:message];
    }
    
    NSError *error = NULL;
    if (![MessageObjectContext save:&error]) {
        //        NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        abort();
    }
    
    return item;
    
}

-(void)doWithGroupChatMessage:(XMPPStream *)sender XMPPMessage:(XMPPMessage*)message
{
    NSString *roomJID = [[message from] bare];
    
    //此条消息的群是否存在
    if ( NonTrain(roomJID) && ![CMCoreDataUtils existManagedObject:NSStringFromClass([CMGroupItem class]) withPredicate:Pre_RoomJid(roomJID)]) {
        
        return;
    }
    
    //本地是否存在此条信息
    if ([CMCoreDataUtils existManagedObject:NSStringFromClass([CMGroupMessageItem class]) withPredicate:Pre_MsgID([message elementID])]) {
        return;
    }
    
    //保存聊天记录
    CMGroupMessageItem * messageItem = [NSEntityDescription insertNewObjectForEntityForName:NSStringFromClass([CMGroupMessageItem class]) inManagedObjectContext:MessageObjectContext];
    
    messageItem.content = [message body];
    messageItem.roomJID = roomJID;
    messageItem.fromJID  = [[message from]resource];
    messageItem.mID = [message elementID];
    
    NSXMLElement *userInfo = [message elementForName:@"userinfo"];
    
    NSString *uid = [userInfo attributeStringValueForName:@"id"];
    NSString *icon = [userInfo attributeStringValueForName:@"icon"];
    NSString *name = [userInfo attributeStringValueForName:@"name"];
    
    CMUserItem *user = (CMUserItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMUserItem class]) withPredicate:Pre_UserJid(messageItem.fromJID)];
    
    
    if (!user || (user && !user.uid)) {
        user = [NSEntityDescription insertNewObjectForEntityForName:NSStringFromClass([CMUserItem class]) inManagedObjectContext:MessageObjectContext];
        user.icon = icon;
        user.name = name;
        user.jid = messageItem.fromJID;
        
        //接收到错误的userid，（极光id）
        if (uid.length != kRealUserIdLenght) {
            
            WEAKSELF;
            [[CMContactManager manager] doRequestUserInfoWithJid:messageItem.fromJID listener:^(CMContacts *contacts) {
                STRONGSELF;
                TContactsItem item;
                
                if(contacts && contacts->GetItem(0, item)){
                    
                    user.uid = [NSString stringWithUTF8String:item.sID.c_str()];
                    user.name = [NSString stringWithUTF8String:item.sName.c_str()];
                    user.icon = [NSString stringWithUTF8String:item.sIcon.c_str()];
                    
                    [sself handleGroupMessage:messageItem :user :message];
                    
                }
            }];
        }else{
            
            user.uid = uid;
            
            [self handleGroupMessage:messageItem :user :message];
        }
    }else{
        //更新头像
        if (icon && icon.length > 0 && (![user.icon isEqualToString:icon])) {
            user.icon = icon;
            
            
            NSPredicate *predicate = [NSPredicate predicateWithFormat:@"(fromJID == %@) AND (flag == 0)",user.jid];
            
            CMDialogueItem *dialogueItem = (CMDialogueItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMDialogueItem class]) withPredicate:predicate];
            if (dialogueItem) {
                dialogueItem.icon = icon;
                
                [MessageObjectContext save:NULL];
            }
            
            [[NSNotificationCenter defaultCenter] postNotificationName:NotificationCenteUpdateIcon object:user];
            
        }
        
        if (!user.name) {
            user.name = name;
        }
        
        [ self handleGroupMessage:messageItem :user :message];
    }
}

//保存群消息
- (void)handleGroupMessage:(CMGroupMessageItem *)item :(CMUserItem *)user :(XMPPMessage *)message{
    
    item.fromID = user.uid;
    item.icon = user.icon;
    item.fromName = user.name;
    
    item.isFromMe = [item.fromJID isEqualToString:kXMPPJid];
    
    item.sendTime = [NSDate date];
    BOOL isShowSendTime =  [CMCoreDataUtils isRequireSortMsgWithJid:item.roomJID type:CMGroupChatType date:item.sendTime];
    
    item.isShowSendTime = isShowSendTime;
    
    if ( [item.roomJID isEqualToString:@"20150205102350734375089bd49fd94e56f7@conference.cmb.wd.test.trylose.cn"]) {
        
    }
    if ([message wasDelayed]) {
        item.sendTime = [message delayedDeliveryDate];
        if([[[message from] resource] isEqualToString:kXMPPJid]){
            item.sent = [NSNumber numberWithInt:CMSendMessageStateSuccess];
        }
    }
    
    
    NSXMLElement *browseitem  = [message elementForName:@"browseitem" xmlns:@"xmpp:wunding:share"];
    if ((![message isChatMessageWithBody]) &&  browseitem) {
        item.type = CMMessageCourseType;
        
        item.coursemessage = [CMParseXmppMessage parseXmppMessageToCourse:message];
    }
    
    //存入问答分享信息
    NSXMLElement *qaitem  = [message elementForName:@"qaitem" xmlns:@"xmpp:wunding:qa"];
    
    if ((![message isChatMessageWithBody]) &&  qaitem) {
        item.type = CMMessageQAType;
        
        item.qamessage = [CMParseXmppMessage parseXmppMessageToQa:message];
    }
    
    NSXMLElement *imageitem  = [message elementForName:@"imageitem" xmlns:@"xmpp:wunding:image"];
    if ((![message isChatMessageWithBody]) &&  imageitem) {
        item.type = CMMessageImageType;
        
        item.imageMessage = [CMParseXmppMessage parseXmppMessageToImage:message];
    }
    
    NSString *content;
    if (item.type == CMMessageCourseType) {
        content = [NSString stringWithFormat:@"%@ %@",I(@"[分享]"),item.coursemessage.title];
    }else if (item.type == CMMessageQAType) {
        content = [NSString stringWithFormat:@"%@ %@",I(@"[分享]"),item.qamessage.question];
    }else if(item.type == CMMessageImageType){
        content = I(@"[图片]");
    }else{
        content = [message body];
    }
    
    NSError *error = NULL;
    [MessageObjectContext save:&error];
    
    BOOL unread;//此条消息是否为未读消息；
    
    CMDialogueItem *dialogueItem =[[XMPPChatMessageCoreDataStorage sharedInstance] dialogueItemExistForRoomJid:item.roomJID];
    //保存会话记录
    if(dialogueItem)
    {
        dialogueItem.lastMessage = content;
        dialogueItem.sendTime = [NSDate date];
        
        if (![self isChatFront:dialogueItem.roomJID]) {
            //次条消息不正在最前端，收到消息为未读消息
            dialogueItem.unread += 1;
            
            unread = YES;
        }
        
        if (![MessageObjectContext save:&error]) {
            //            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
        
        if ([message wasDelayed]) {
            dialogueItem.sendTime = [message delayedDeliveryDate];
            
            if (![MessageObjectContext save:&error]) {
                //                NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
                abort();
            }
        }
    }
    else
    {
        unread = YES;
        
        //根据roomjid查找群组
        CMGroupItem *groupItem = (CMGroupItem *)[CMCoreDataUtils fetchManagedObject:NSStringFromClass([CMGroupItem class]) withPredicate:Pre_RoomJid(item.roomJID)];
        
        CMDialogueItem * dialogueItem = [NSEntityDescription insertNewObjectForEntityForName:@"CMDialogueItem" inManagedObjectContext:MessageObjectContext];
        
        dialogueItem.flag = 1;
        dialogueItem.fromJID = item.fromJID;
        dialogueItem.fromName = item.fromName;
        dialogueItem.roomJID = item.roomJID;
        dialogueItem.icon = groupItem.icon;
        dialogueItem.roomID = groupItem.roomID;
        dialogueItem.roomName = groupItem.roomName;
        dialogueItem.password = groupItem.password;
        dialogueItem.lastMessage = [message body];
        dialogueItem.unread = 1;
        dialogueItem.isJoined = [NSNumber numberWithBool:0];
        
        if (![MessageObjectContext save:&error]) {
            //            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            abort();
        }
        if ([message wasDelayed]) {
            dialogueItem.sendTime = [message delayedDeliveryDate];
            
            if (![MessageObjectContext save:&error]) {
                //                NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
                abort();
            }
        }
    }
    
    if (unread) {
        if ( self.interactNavigationController ) {
            
            //未读消息，更新Badge
            [CMCoreDataUtils updateBadgeValueWithTabBar:self.interactNavigationController.tabBarItem];
        }
    }
}

//判断当前回话是否在最前端
- (BOOL)isChatFront:(NSString *)toJid{
    UIViewController *viewController = self.interactNavigationController.topViewController;
    if ([viewController isKindOfClass:[CMChatViewController class]]) {
        CMChatViewController *chatViewController = (CMChatViewController *)viewController;
        if ([toJid isEqualToString:chatViewController.toJid]) {
            return YES;//正在最前端聊天
        }
    }
    return NO;
}

//系统消息界面 是否在最前端
- (BOOL)isSystemFront{
    UIViewController *viewController = self.interactNavigationController.topViewController;
    if ([viewController isKindOfClass:[CMSysMessageViewController class]] || [viewController isKindOfClass:[CMSysMessageDetailyViewController class]]) {
        return YES;
    }
    return NO;
}

- (void) saveSystemMessage:(XMPPMessage *)message
{
    
    CMMessageItem* item = [NSEntityDescription insertNewObjectForEntityForName:@"CMMessageItem" inManagedObjectContext:MessageObjectContext];
    item.fromJID = [[message from] bare];
    item.sendTime = [NSDate date];
    
    NSXMLElement * custom=    [message elementForName:@"custom_content"];
    item.type = [[custom elementForName:@"no"] stringValueAsInt32];
    
    CMSysMessageItem* sysitem = [NSEntityDescription insertNewObjectForEntityForName:@"CMSysMessageItem" inManagedObjectContext:MessageObjectContext];
    
    switch (item.type) {
            
        case CMInteractSystemMessageTypeInvite://告知用户被邀请
        {
            
            NSXMLElement *invite = [custom elementForName:@"Invite"];
            NSXMLElement * room =[ invite elementForName:@"Room"];
            
            sysitem.rawSenderName = [invite attributeStringValueForName:@"from"];
            sysitem.rawSenderID = [invite attributeStringValueForName:@"fromid"];
            
            sysitem.key = [room attributeStringValueForName:@"key"];
            sysitem.roomID =[room attributeStringValueForName:@"id"];
            sysitem.roomName = [room attributeStringValueForName:@"name"];
            sysitem.roomJID = [room attributeStringValueForName:@"jid"];
            sysitem.password = [room attributeStringValueForName:@"pwd"];
            
            item.content = [NSString stringWithFormat:@"%@ 邀请您加入群 %@",sysitem.rawSenderName,sysitem.roomName];
            
            //过滤重复消息
            sysitem.skip = [CMCoreDataUtils existSystemMessageWithRoomJid:sysitem.roomJID type:CMInteractSystemMessageTypeInvite];
            
        }
            break;
            
        case CMInteractSystemMessageTypeApply://告知管理员申请消息
        {
            NSXMLElement *apply = [custom elementForName:@"Apply"];
            sysitem.rawSenderName = [apply attributeStringValueForName:@"from"];
            sysitem.rawSenderID = [apply attributeStringValueForName:@"fromid"];
            
            NSXMLElement * room =[ apply elementForName:@"Room"];
            sysitem.roomID =[room attributeStringValueForName:@"id"];
            sysitem.roomName = [room attributeStringValueForName:@"name"];
            
            NSXMLElement * content =[apply elementForName:@"Content"];
            sysitem.key = [content stringValue];
            
            item.content = [NSString stringWithFormat:I(@"%@ 申请加入 %@"),sysitem.rawSenderName,sysitem.roomName];
            
            //过滤重复消息
            sysitem.skip = [CMCoreDataUtils existSystemMessageWithRoomJid:sysitem.roomJID type:CMInteractSystemMessageTypeApply];
        }
            
            break;
        case CMInteractSystemMessageTypeCreate://群创建成功
        {
            NSXMLElement *notify = [custom elementForName:@"Notify"];
            NSXMLElement * room =[ notify elementForName:@"Room"];
            sysitem.key = [room attributeStringValueForName:@"key"];
            sysitem.roomID =[room attributeStringValueForName:@"id"];
            sysitem.roomName = [room attributeStringValueForName:@"name"];
            sysitem.roomJID =[room attributeStringValueForName:@"jid"];
            sysitem.password = [room attributeStringValueForName:@"pwd"];
            
            item.content = [NSString stringWithFormat:@"%@ 创建成功",sysitem.roomName];
            
            [CMCoreDataUtils saveGruopCacheFromSystemMessage:sysitem];
            [[CMGroupManager managerDelegate] joinWithJid:sysitem.roomJID withPassword:sysitem.password];
        }
            
            break;
            
        case CMInteractSystemMessageTypePassApply:
        {
            //申请人通过，可进入群
            NSXMLElement *notify = [custom elementForName:@"Notify"];
            sysitem.rawSenderName = [notify attributeStringValueForName:@"from"];
            sysitem.rawSenderID = [notify attributeStringValueForName:@"fromid"];
            
            NSXMLElement * room =[ notify elementForName:@"Room"];
            sysitem.roomID =[room attributeStringValueForName:@"id"];
            sysitem.roomJID =[room attributeStringValueForName:@"jid"];
            sysitem.roomName = [room attributeStringValueForName:@"name"];
            sysitem.key = [room attributeStringValueForName:@"key"];
            sysitem.password = [room attributeStringValueForName:@"pwd"];
            
            item.content = [NSString stringWithFormat:I(@"您已被同意加入群 %@") ,sysitem.roomName];
            
            CMGroupManager *groupManager = [CMGroupManager manager];
            [groupManager doRequestEnterGroup:sysitem.roomID key:sysitem.key success:^{
                [CMCoreDataUtils saveGruopCacheFromSystemMessage:sysitem];
                [groupManager joinWithJid:sysitem.roomJID withPassword:sysitem.password];
            }failure:nil];
        }
            break;
            
        case CMInteractSystemMessageTypeRefuse:
        {
            //入群申请被拒绝
            NSXMLElement *notify = [custom elementForName:@"Notify"];
            sysitem.rawSenderName = [notify attributeStringValueForName:@"from"];
            sysitem.rawSenderID = [notify attributeStringValueForName:@"fromid"];
            
            NSXMLElement * room =[ notify elementForName:@"Room"];
            sysitem.roomID =[room attributeStringValueForName:@"id"];
            sysitem.roomJID =[room attributeStringValueForName:@"jid"];
            sysitem.roomName = [room attributeStringValueForName:@"name"];
            sysitem.key = [room attributeStringValueForName:@"key"];
            
            item.content = [NSString stringWithFormat:I(@"您已被拒绝加入群 %@") ,sysitem.roomName];
            
        }
            break;
            
        case CMInteractSystemMessageTypeKick:
        {
            //告知用户已被踢
            NSXMLElement *notify = [custom elementForName:@"Notify"];
            NSXMLElement * room =[ notify elementForName:@"Room"];
            
            sysitem.roomID =[room attributeStringValueForName:@"id"];
            sysitem.roomJID =[room attributeStringValueForName:@"jid"];
            sysitem.roomName = [room attributeStringValueForName:@"name"];
            sysitem.key = [room attributeStringValueForName:@"key"];
            
            item.content = [NSString stringWithFormat:@"您已被移出群 %@",sysitem.roomName];
            
            //发送xmpp协议，离开此群
            [[CMGroupManager managerDelegate] leaveWithJid:sysitem.roomJID];
            [CMCoreDataUtils clearAllCacheWithRoomJid:sysitem.roomJID];

            //检测用户是否在此群聊天
            [self popRootViewControllerWithKicked:sysitem.roomJID type:CMInteractSystemMessageTypeKick];
        }
            break;
            
        case CMInteractSystemMessageTypeSetManager:
        {
            //告知用户已被设置为管理员
            NSXMLElement *notify = [custom elementForName:@"Notify"];
            NSXMLElement * room =[ notify elementForName:@"Room"];
            
            sysitem.roomID =[room attributeStringValueForName:@"id"];
            sysitem.roomJID =[room attributeStringValueForName:@"jid"];
            sysitem.roomName = [room attributeStringValueForName:@"name"];
            sysitem.key = [room attributeStringValueForName:@"key"];
            
            item.content = [NSString stringWithFormat:@"您已成为群 %@ 的管理员",sysitem.roomName];
            
        }
            break;
        case CMInteractSystemMessageTypeCancelManager:
        {
            //告知用户已取消管理员
            NSXMLElement *notify = [custom elementForName:@"Notify"];
            NSXMLElement * room =[ notify elementForName:@"Room"];
            
            sysitem.roomID =[room attributeStringValueForName:@"id"];
            sysitem.roomJID =[room attributeStringValueForName:@"jid"];
            sysitem.roomName = [room attributeStringValueForName:@"name"];
            sysitem.key = [room attributeStringValueForName:@"key"];
            
            item.content = [NSString stringWithFormat:@"您已被取消群 %@ 的管理员",sysitem.roomName];
            
        }
            break;
        case CMInteractSystemMessageTypeQuit:
        {
            //告知管理员有人退群
            NSXMLElement *notify = [custom elementForName:@"Notify"];
            
            sysitem.rawSenderID = [notify attributeStringValueForName:@"fromid"];
            sysitem.rawSenderName = [notify attributeStringValueForName:@"from"];
            
            NSXMLElement * room =[ notify elementForName:@"Room"];
            sysitem.key = [room attributeStringValueForName:@"key"];
            sysitem.roomID =[room attributeStringValueForName:@"id"];
            sysitem.roomName = [room attributeStringValueForName:@"name"];
            
            item.content = [NSString stringWithFormat:@"%@ 退出群 %@",sysitem.rawSenderName,sysitem.roomName];
        }
            break;
        case CMInteractSystemMessageTypeDisBand:
        {
            //告知所以成员解散群
            NSXMLElement *notify = [custom elementForName:@"Notify"];
            NSXMLElement * room =[ notify elementForName:@"Room"];
            
            sysitem.roomID =[room attributeStringValueForName:@"id"];
            sysitem.roomJID =[room attributeStringValueForName:@"jid"];
            sysitem.roomName = [room attributeStringValueForName:@"name"];
            sysitem.key = [room attributeStringValueForName:@"key"];
            
            item.content = [NSString stringWithFormat:@"%@ 已解散",sysitem.roomName];
            
            //移除缓存,包括聊天记录
            [CMCoreDataUtils clearAllCacheWithRoomJid:sysitem.roomJID];
            //检测用户是否在此群聊天
            [self popRootViewControllerWithKicked:sysitem.roomJID type:CMInteractSystemMessageTypeDisBand];
            
        }
            break;
        default:
            
            break;
    }
    item.sysmessage = sysitem;
    
    NSError *error = NULL;
    if (![MessageObjectContext save:&error]) {
        //            NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        abort();
    }
    
    
    //保存到最近联系人
    [self saveRecentContactInfo:item];
}

- (void)popRootViewControllerWithKicked:(NSString *)kickJid type:(enum CMInteractSystemMessageType)type{
    
    for (UIViewController *viewController in self.interactNavigationController.viewControllers) {
        if ([viewController isKindOfClass:[CMChatViewController class]]) {
            
            CMChatViewController *chatViewController = (CMChatViewController *)viewController;
            
            WEAKSELF
            if ([kickJid isEqualToString:chatViewController.toJid]) {
                CMAlertView *alertView = [[CMAlertView alloc]initWithTitle:I(@"提示") message: (type == CMInteractSystemMessageTypeKick) ? I(@"你被移出该群组！") : I(@"该群组已解散！")  cancelButtonTitle:nil otherButtonTitles:I(@"确定") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
                    STRONGSELF;
                    [sself.interactNavigationController popToRootViewControllerAnimated:YES];
                }];
                alertView.disabledOutSide = YES;
                [alertView show];
            }
        }
    }
}

#pragma mark Core Data
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

- (NSManagedObjectContext *)managedObjectContext_roster
{
	return [self.xmppRosterStorage mainThreadManagedObjectContext];
}

@end


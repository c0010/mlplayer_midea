//
//  CMXmppHandler.h
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-5.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GCDAsyncSocket.h"

#import "XMPPFramework.h"
#import <CFNetwork/CFNetwork.h>

typedef void(^ConnectSuccess)();
typedef void(^ConnectFailure)();

@interface CMXmppHandler : NSObject<XMPPStreamDelegate,XMPPRoomStorage,XMPPRoomDelegate>
{

    BOOL isXmppConnected;//是否已经连接
    BOOL customCertEvaluation;//是否和服务器进行自定义认证
}

@property(nonatomic,copy)NSString* jid;
@property(nonatomic,copy)NSString* pwd;
@property(nonatomic,copy)NSString* hostname;

@property (nonatomic,strong)XMPPStream * xmppStream;
@property (nonatomic,strong)XMPPReconnect* xmppReconnect;
@property (nonatomic,strong)XMPPRosterCoreDataStorage * xmppRosterStorage;

@property (nonatomic,strong)ConnectSuccess connectSuccess;
@property (nonatomic,strong)ConnectFailure connectFailure;


@property (nonatomic,strong)UINavigationController *interactNavigationController;
-(void)goOffline;
-(BOOL)connect;
-(BOOL)connectWithSuccess:(ConnectSuccess)success failure:(ConnectFailure)failure;
-(void)setJid:(NSString*)jid andPwd:(NSString*)pwd;


+ (CMXmppHandler*)sharedInstance;

@end

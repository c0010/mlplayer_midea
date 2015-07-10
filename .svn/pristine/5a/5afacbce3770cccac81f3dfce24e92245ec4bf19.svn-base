//
//  CMGroupManager.h
//  MLPlayer
//  群管理
//  Created by water on 14-7-23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XMPPFramework.h"
#import "NSXMLElement+XEP_0203.h"
#import "tool.h"
#include "cmmyinfo.h"
#import "cmfileinfo.h"
#import "cmupload.h"
#import "cmgroup.h"

typedef void(^UploadGroupHeaderSuccessCallBack)(NSString *url);//
typedef void(^UploadGroupHeaderFailureCallBack)(int errorCode);

typedef void(^GroupManagerSuccess)(TGroupInfoItem *);
typedef void(^GroupManagerSuccessNone)();
typedef void(^GroupManagerGroupSuccess)(CMGroup *);

typedef void(^GroupManagerFailureNone)(int errorCode);//不需要显示提示对话框
typedef void(^GroupManagerFailure)(int errorCode);//需要自动显示对话框

typedef void(^Success)(XMPPRoom *room);

class CMCreateGroupListener;
class CMUploadGroupHeaderListener;
class CMGroupManagerListener;

@interface CMGroupManager : NSObject<XMPPStreamDelegate,XMPPRoomStorage,XMPPRoomDelegate>{
    
    CMCreateGroupListener *createGroupListener;
    CMUploadGroupHeaderListener *uploadGroupHeaderListener;
    CMGroupManagerListener *groupManagerListener;
    
    TGroupInfoItem *m_TGroupInfoItem;
    CMGroup *m_pGroup;
}

@property(nonatomic,strong)Success success;

@property(nonatomic,strong)UploadGroupHeaderSuccessCallBack uploadGroupHeaderSuccessCallBack;
@property(nonatomic,strong)UploadGroupHeaderFailureCallBack uploadGroupHeaderFailureCallBack;

@property(nonatomic,strong)GroupManagerSuccess groupManagerSuccess;
@property(nonatomic,strong)GroupManagerFailure groupManagerFailure;
@property(nonatomic,strong)GroupManagerGroupSuccess groupManagerGroupSuccess;
@property(nonatomic,strong)GroupManagerSuccessNone groupManagerSuccessNone;
@property(nonatomic,strong)GroupManagerFailureNone groupManagerFailureNone;

+ (id)manager;
+ (id)managerDelegate;

- (void) clear;
/**
 *  向xmpp请求离群，退出群，被移除都需要调用，不然还是会收到该群的消息
 *
 *  @param jid  群jid，roomjid
 */
- (void)leaveWithJid:(NSString *)jid;
- (void)leaveWithJid:(NSString *)jid success:(Success)success;

/**
 *  向xmpp请求入群，每次进入程序都会调用，不然收到不到群消息
 *
 *  @param jid  群jid，roomjid
 */
-(void)joinWithJid:(NSString *)jid withPassword:(NSString *)pwd;
-(void)joinWithJid:(NSString *)jid withPassword:(NSString *)pwd success:(Success)success;

/**
 *  向xmpp请求入群，每次进入程序都会调用，不然收到不到群消息
 *
 *  @param jid  群jid，roomjid
 *  @param isNewAdd  是否为第一次进群,YES 不接收历史消息，NO，接收历史消息
 *
 */
-(void)joinWithJid:(NSString *)jid withPassword:(NSString *)pwd isNewAdd:(BOOL)isNewAdd;
-(void)joinWithJid:(NSString *)jid withPassword:(NSString *)pwd isNewAdd:(BOOL)isNewAdd success:(Success)success;

/**
 *  群管理的回调方法
 *
 */
- (void)doGroupManagerSuccess;
- (void)doGroupManagerFailure:(int) errorCode;

/**
 *  创建群
 *
 *  @param name  群名称
 *  @param desc  群简介
 *  @param flag  群权限
 */
- (void)doCreateGroupWithName:(NSString *)name desc:(NSString *)desc flag:(int)flag success:(GroupManagerSuccess)success failure:(GroupManagerFailure)failure;

/**
 *  退出群
 *
 *  @param roomID  群id
 */
- (void)doExitGroup:(NSString*)roomID success:(GroupManagerSuccessNone)success;

/**
 *  解散群
 *
 *  @param roomID  群id
 */
- (void)doDisblanGroup:(NSString*)roomID success:(GroupManagerSuccessNone)success;

/**
 *  邀请群成员
 *
 *  @param roomID  群id
 *  @param sidarray 被邀请的好友id，可为多人
 */
- (void)doInviteToGroup:(NSString*)roomID sidarray:(NSString *)sidarray success:(GroupManagerSuccessNone)success;

/**
 *  移除成员
 *
 *  @param roomID  群id
 *  @param sid  被移除成员id 只是单人
 */
- (void)doKickGroupOccupant:(NSString*)roomID sid:(NSString *)sid success:(GroupManagerSuccessNone)success;

/**
 *  设置管理员
 *
 *  @param roomID  群id
 *  @param sid  成员id
 */
- (void)doSetGroupAdmin:(NSString*)roomID sid:(NSString *)sid success:(GroupManagerSuccessNone)success;

/**
 *  取消管理员
 *
 *  @param roomID  群id
 *  @param sid  成员id
 */
- (void)doRemoveGroupAdmin:(NSString*)roomID sid:(NSString *)sid success:(GroupManagerSuccessNone)success;

/**
 *  请求入群/不需要验证
 *
 *  @param roomID  群id
 *  @param key  此处信息为空
 */
- (void)doRequestEnterGroup:(NSString*)roomID key:(NSString *)key success:(GroupManagerSuccessNone)success failure:(GroupManagerFailureNone)failure;

/**
 *  申请加入群/需要验证
 *
 *  @param roomID  群id
 *  @param key  验证信息
 */
- (void)doApplyEnterGroup:(NSString*)roomID key:(NSString *)key success:(GroupManagerSuccessNone)success;

/**
 *  通过某用户的进群申请
 *
 *  @param roomID  群id
 *  @param sid  用户id
 */
- (void)doAcceptUserApply:(NSString*)roomID sid:(NSString *)sid success:(GroupManagerSuccessNone)success failure:(GroupManagerFailureNone)failure;

/**
 *  拒绝某用户的进群申请
 *
 *  @param roomID  群id
 *  @param sid  用户id
 */
- (void)doRefuseUserApply:(NSString*)roomID sid:(NSString *)sid success:(GroupManagerSuccessNone)success;

/**
 *  获取群详细信息
 *
 *  @param roomID  群id
 */
- (void)doDetailyGroup:(NSString*)roomID success:(GroupManagerSuccess)success failure:(GroupManagerFailure)failure;

/**
 *  通过关键字搜索群
 *
 *  @param searchText 关键字
 */
- (void)doSearchGroup:(NSString *)searchText success:(GroupManagerGroupSuccess)success failure:(GroupManagerFailure)failure;

/**
 *  更新群信息
 *
 *  @param roomID  群id
 *  @param name  群名称
 *  @param desc  群简介
 *  @param flag  群权限
 */
- (void)doUpdateNameWithroomID:(NSString*)roomID name:(NSString *)name success:(GroupManagerSuccessNone)success;
- (void)doUpdateDescWithroomID:(NSString*)roomID desc:(NSString *)desc success:(GroupManagerSuccessNone)success;
- (void)doUpdateFlagWithroomID:(NSString*)roomID flag:(int)flag success:(GroupManagerSuccessNone)success;

/**
 *  更新群头像
 *
 *  @param roomID  群id
 *  @param imagePath 群头像的本地路径
 */
- (void)doUploadGroupHeaderWithRoomid:(NSString *)rommid imagePath:(NSString *)imagePath success:(UploadGroupHeaderSuccessCallBack)success failure:(UploadGroupHeaderFailureCallBack)failure;

/**
 *  获取我的群列表
 *
 */
- (void)doRequestMyGroup:(GroupManagerGroupSuccess)success failure:(GroupManagerFailureNone)failure;
@end

/**
 *  创建群回调
 *
 */
class CMCreateGroupListener: public IMSimpleResultListener
{
    void OnRequestFinish(void* UserData, int Result)
	{
		CMGroupManager* groupManager = (__bridge CMGroupManager*)UserData;
		[tool DisimissActivityIndicator];
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
            [groupManager doGroupManagerSuccess];
        }
        else {
            [groupManager doGroupManagerFailure:Result];
		}
	}
};

/**
 *  上传群头像回调
 *
 */
class CMUploadGroupHeaderListener: public IMSimpleResultListener
{
    void OnRequestFinish(void* UserData, int Result)
	{
		CMGroupManager* groupManager = (__bridge CMGroupManager*)UserData;
		[tool DisimissActivityIndicator];
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
            NSString *url = [NSString stringWithUTF8String:CMFileUpload::GetInstance()->url.c_str()];
            groupManager.uploadGroupHeaderSuccessCallBack(url);
        }
        else {
            groupManager.uploadGroupHeaderFailureCallBack(Result);
		}
	}
};

/**
 *  群管理操作回调
 *
 */
class CMGroupManagerListener: public IMUpdateDataListener
{
public:
	CMGroupManagerListener(){};
	~CMGroupManagerListener(){};
	
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{
        //CMMainControl* mainControl = (CMMainControl*)UserData;
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
        [tool DisimissActivityIndicator];

		CMGroupManager* groupManager = (__bridge id)UserData;
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
            [groupManager doGroupManagerSuccess];
		}else {
            [groupManager doGroupManagerFailure:Result];
		}
	}
    
};
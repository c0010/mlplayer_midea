//
//  CMMsgManager.h
//  MLPlayer
//  消息发送
//  Created by water on 14-7-17.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "XMPPFramework.h"
#import "CMXmppHandler.h"
#import "tool.h"
#import "cmcontacts.h"
#import "SDWebImage/SDWebImageManager.h"

typedef void(^XMPPMCallBack)(enum CMSendMessageState state);
typedef void(^UserInfoCallBack)(TContactsItem item);
typedef void(^UploadSuccessCallBack)(NSString *url,NSString *thumb_url);
typedef void(^UploadFailureCallBack)(int errorCode);


typedef void(^Completion)(enum CMSendMessageState sendState);

typedef void(^DownLoadSuccessCallBack)(UIImage *image);
typedef void(^DownLoadFailureCallBack)();

class CMMsgManagerUploadDataListener;
@interface CMMsgManager : NSObject<SDWebImageManagerDelegate>
{
    CMMsgManagerUploadDataListener *m_pListener;
    
}

@property (nonatomic, strong)XMPPMCallBack xmppCallback;//发送消息回调
@property(nonatomic,strong)UploadSuccessCallBack uploadSuccCallBack;
@property(nonatomic,strong)UploadFailureCallBack uploadFailureCallBack;

@property(nonatomic,strong)DownLoadSuccessCallBack downLoadSuccessCallBack;
@property(nonatomic,strong)DownLoadFailureCallBack downLoadFailureCallBack;

@property(nonatomic,strong)UserInfoCallBack userInfoCallBack;

@property(nonatomic,strong)Completion completion;

+ (id)manager;

- (void)doSendMessage:(CMBaseItem *)item;
- (void)doSendMessage:(CMBaseItem *)item completion:(Completion)completion;

//发送失败，重新发送
- (void)doSendMessageWithRepeat:(CMBaseItem *)item ;

//上传图片成功;
- (void)doneUploadPictureSucc;
//上传图片失败;
- (void)doneUploadPictureFailure:(int)errCode;

- (void)setButtton:(UIButton *)button withUrl:(NSString *)url;
- (void)downloadImageWithUrl:(NSString *)imageUrl download:(DownLoadSuccessCallBack)dcallback;
- (void)setImageView:(UIImageView *)imageview withUrl:(NSString *)url withErrorImage:(UIImage *)errorImage;
- (void)downloadImageWithUrl:(NSString *)imageUrl success:(DownLoadSuccessCallBack)success failure:(DownLoadFailureCallBack)failure;

@end


class CMMsgManagerUploadDataListener: public IMSimpleResultListener
{
    void OnRequestFinish(void* UserData, int Result)
	{
		CMMsgManager* msgManager = (__bridge CMMsgManager*)UserData;
		[tool DisimissActivityIndicator];
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
            [msgManager doneUploadPictureSucc];
        }
        else {
            [msgManager doneUploadPictureFailure:Result];
		}
	}
};

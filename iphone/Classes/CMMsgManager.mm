//
//  CMMsgManager.m
//  MLPlayer
//
//  Created by water on 14-7-17.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMMsgManager.h"
#import "CMInteractModel.h"
#import "MLPlayerAppDelegate.h"
#include "cmmyinfo.h"
#import "cmfileinfo.h"
#import "cmupload.h"
#import "GlobalAlertCenter.h"
#import "SDWebImage/SDImageCache.h"
#import "cmsettings.h"
#import "CMGroupManager.h"
#import "CMContactManager.h"
#import "CMMsgBlock.h"
#import "CMMsgPackageUtils.h"

#define DelaySendReturnTime 20 //等待发送成功，可以设置最长等待时间

@implementation CMMsgManager
@synthesize xmppCallback;

+ (id)manager{
    return [[CMMsgManager alloc] init];
}

- (id)init
{
    self = [super init];
    if (self) {

    }
    return self;
}

- (void)doSendMessage:(CMBaseItem *)item
{
    [self doSendMessage:item completion:nil];
}

- (void)doSendMessageWithRepeat:(CMBaseItem *)item
{

    [self updateMessageState:item sendState:CMSendMessageStateSending];

    [self doSendMessage:item completion:nil];
}

- (void)doSendMessage:(CMBaseItem *)item completion:(Completion)completion{

    self .completion = completion;
    
    XMPPMessage *message = [CMMsgPackageUtils packageXmppMessage:item];
    
    WEAKSELF;
    [self sendMessage:message listener:^(enum CMSendMessageState sendState) {
        STRONGSELF;
        //发送成功，更新发送状态
        [sself updateMessageState:item sendState:sendState];
        
        if (sself.completion) {
            sself.completion(sendState);
        }
        
    } withItem:item];
}

- (void)sendMessage:(XMPPMessage *)message listener:(XMPPMCallBack)mcallback withItem:(CMBaseItem *)item
{
    self.xmppCallback = mcallback;
    
    if (MBlock.type(item) == CMMessageImageType) {
        
        if (MBlock.imagemessage(item).url && MBlock.imagemessage(item).thumb_url) {
           
            [message addChild:[self packageImageXMLElement:MBlock.imagemessage(item)]];
            //发送图片移除body
            [message removeElementForName:@"body"];
            
            [self sendXmppMessage:message];
        }else{
            //发送图片时，用content暂时存放上传图片的本地地址
            NSString *localPath = [message body];
            [self sendImageMessage:message uploadPath:localPath success:^(NSString *url, NSString *thumb_url) {
                
                [self saveImageItem:item url:url thumb_url:thumb_url];

                [message addChild:[self packageImageXMLElement:MBlock.imagemessage(item)]];
                //发送图片移除body
                [message removeElementForName:@"body"];
                //保存图片信息
                
                [self sendXmppMessage:message];
            } failure:^(int errorCode) {
                [self saveImageItem:item url:nil thumb_url:nil];
                
                [self executeXmppBlock:CMSendMessageStateFailure];

            }];
        }
    }else{
        [self sendXmppMessage:message];
    }
}

- (void)sendXmppMessage:(XMPPMessage *)message{
    
    
    XMPPElementReceipt *receipt;
    //发送消息
    [ XmppHandler.xmppStream sendElement:message andGetReceipt:&receipt];
    
    if ([receipt wait:DelaySendReturnTime]) {
        //会延迟几秒
        [self executeXmppBlock:CMSendMessageStateSuccess];
    }else {
        [self executeXmppBlock:CMSendMessageStateFailure];
    }
    
    
}

//发送状态返回
- (void)executeXmppBlock:(enum CMSendMessageState)state{
    
    if (self.xmppCallback) {
        self.xmppCallback(state);
        self.xmppCallback = nil;
    }
}

//更新消息状态
- (void) updateMessageState:(CMBaseItem *)item sendState:(enum CMSendMessageState )sendState{

    NSError *error = NULL;
    
    if ( ! MBlock.isGroup(item) ) {
        CMMessageItem *mitem = (CMMessageItem *)item;
        mitem.sent = [NSNumber numberWithInteger:sendState];
    }else{
        CMGroupMessageItem *gitem = (CMGroupMessageItem *)item;
        gitem.sent = [NSNumber numberWithInteger:sendState];
    }
    
    if (![MessageObjectContext save:&error]) {
        NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        abort();
    }
}

//上传图片
- (void)sendImageMessage:(XMPPMessage *)message uploadPath:(NSString *)path success:(UploadSuccessCallBack)success failure:(UploadFailureCallBack)failure
{
    self.uploadSuccCallBack = success;
    self.uploadFailureCallBack = failure;
    
    CMFileInfo *file = new CMFileInfo();
    if (!m_pListener) {
        m_pListener = new CMMsgManagerUploadDataListener();
    }
    CMFileUpload::GetInstance()->SetListener(m_pListener);
    CMFileUpload::GetInstance()->SetUserData((__bridge void*)self);
    
    file->UpLoadMessageWithPicture([path UTF8String]);
    
    CMFileUpload::GetInstance()->Append(*file);
    
}

//图片上传成功
- (void)doneUploadPictureSucc{
    NSString *url = [NSString stringWithUTF8String:CMFileUpload::GetInstance()->url.c_str()];
    NSString *thumb_url = [NSString stringWithUTF8String:CMFileUpload::GetInstance()->thumb_url.c_str()];
    
    if (self.uploadSuccCallBack) {
        self.uploadSuccCallBack(url,thumb_url);
        self.uploadSuccCallBack = nil;
    }
}

//图片上传成功失败
- (void)doneUploadPictureFailure:(int)errCode{
    if (self.uploadFailureCallBack) {
        self.uploadFailureCallBack(errCode);
        self.uploadFailureCallBack = nil;
    }
}

//设置图片
- (void)setImageView:(UIImageView *)imageview withUrl:(NSString *)url withErrorImage:(UIImage *)errorImage{
    
    if (!url) {
        return;
    }
    
    UIImage *image = [[SDImageCache sharedImageCache] imageFromDiskCacheForKey:url];
    if (image) {
        imageview.image = image;
    }else{
        [self downloadImageWithUrl:url success:^(UIImage *image) {
            imageview.image = image;
        } failure:^{
            if (errorImage) {
                imageview.image = errorImage;
            }
        }];
    }
}

- (void)setButtton:(UIButton *)button withUrl:(NSString *)url{
    if (!url) {
        return;
    }
    UIImage *image = [[SDImageCache sharedImageCache] imageFromDiskCacheForKey:url];
    if (image) {
        [button setImage:image forState:UIControlStateNormal];
    }else{
        [self downloadImageWithUrl:url download:^(UIImage *image) {
            [button setImage:image forState:UIControlStateNormal];
        }];
    }
}

//下载图片
- (void)downloadImageWithUrl:(NSString *)imageUrl download:(DownLoadSuccessCallBack)dcallback
{
    __weak typeof(self) weakSelf = self;
    self.downLoadSuccessCallBack = dcallback;
    [[SDWebImageManager sharedManager] downloadImageWithURL:[NSURL URLWithString:imageUrl] options:0 progress:nil completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType, BOOL finished, NSURL *imageURL)
     {
         if (!weakSelf) return;

         dispatch_main_sync_safe(^{
             if (image) {
                 //下载完成后进入这里执行
                 NSString *key = [imageURL absoluteString];
                 [[SDImageCache sharedImageCache] storeImage:image forKey:key toDisk:YES];
                 if (weakSelf.downLoadSuccessCallBack) {
                     weakSelf.downLoadSuccessCallBack(image);
                     weakSelf.downLoadSuccessCallBack = nil;
                 }

             }
         });
        
     }];
}

- (void)downloadImageWithUrl:(NSString *)imageUrl success:(DownLoadSuccessCallBack)success failure:(DownLoadFailureCallBack)failure
{
    [self downloadImageWithUrl:imageUrl download:success];
    self.downLoadFailureCallBack = failure;
}

//下载成功
- (void)webImageManager:(SDWebImageManager *)imageManager didFinishWithImage:(UIImage *)image forURL:(NSURL *)url{
    NSString *key = [url absoluteString];
    [[SDImageCache sharedImageCache] storeImage:image forKey:key toDisk:YES];
    if (self.downLoadSuccessCallBack) {
        self.downLoadSuccessCallBack(image);
        self.downLoadSuccessCallBack = nil;
    }
}

//下载失败
- (void)webImageManager:(SDWebImageManager *)imageManager didFailWithError:(NSError *)error forURL:(NSURL *)url{
    if (self.downLoadFailureCallBack) {
        self.downLoadFailureCallBack();
        self.downLoadFailureCallBack = nil;
    }
}

- (NSXMLElement *) packageImageXMLElement:(CMImageMessageItem *)imageMessageItem{
    
    //添加图片子节点 <imageitem xmlns="xmpp:wunding:image" vertical="横向/竖向" url="原图地址" thumb_url="缩略图地址" />
    NSXMLElement *imageitem = [NSXMLElement elementWithName:@"imageitem" xmlns:@"xmpp:wunding:image"];
    [imageitem addAttributeWithName:@"vertical" boolValue:[imageMessageItem.isVertical boolValue]];
    [imageitem addAttributeWithName:@"url" stringValue:imageMessageItem.url];
    [imageitem addAttributeWithName:@"thumb_url" stringValue:imageMessageItem.thumb_url];
    
    return imageitem;
}

- (void)saveImageItem:(CMBaseItem *)item url:(NSString *)url thumb_url:(NSString *)thumb_url{
    if (! MBlock.isGroup(item)) {
        CMMessageItem *messageItem = (CMMessageItem *)item;
        CMImageMessageItem* imageMessageItem = messageItem.imageMessage;
        imageMessageItem.url = url;
        imageMessageItem.thumb_url = thumb_url;
        
        messageItem.imageMessage = imageMessageItem;
        
        NSError *error = NULL;
        [MessageObjectContext save:&error];
    }else{
        CMGroupMessageItem *messageGroupItem = (CMGroupMessageItem *)item;
        CMImageMessageItem* imageMessageItem = messageGroupItem.imageMessage;
        messageGroupItem.imageMessage.url = url;
        messageGroupItem.imageMessage.thumb_url = thumb_url;
        
        messageGroupItem.imageMessage = imageMessageItem;
        
        NSError *error = NULL;
        [MessageObjectContext save:&error];
    }
}
@end

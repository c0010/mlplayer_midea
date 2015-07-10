//
//  CMSearchQRCode.h
//  MLPlayer
//
//  Created by sunjj on 14/12/19.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"
#import "ZBarSDK.h"
#import <AVFoundation/AVFoundation.h>
#import "cmtrainsigninlist.h"
#import "CMTrainSignView.h"
#import "CMTrainDetailSignController.h"
#import "CMTrainSignController.h"

class CMTrainQRSignUpdateDataListener;
@interface CMSearchQRCode : CMViewController<AVCaptureMetadataOutputObjectsDelegate,ZBarReaderViewDelegate>
{
    int num;
    
    BOOL upOrDown;
    NSTimer *time;
    
    TTrainSignInItem *curItem;
    
    CMTrainQRSignUpdateDataListener *m_pUpdataDataListerner;
    
    int stateFlag; //判断往前一个页面pop还是push到下一个页面
    
    BOOL isRunning; // 判断是否已经扫描完
    
    
    UILabel *guideLabel;
}

@property (nonatomic,strong)UIImageView *line;

@property (nonatomic,strong)AVCaptureDevice *device;
@property (nonatomic,strong)AVCaptureDeviceInput *input;
@property (nonatomic,strong)AVCaptureMetadataOutput *output;
@property (nonatomic,strong)AVCaptureSession *session;
@property (nonatomic,strong)AVCaptureVideoPreviewLayer *preview;
@property (nonatomic,strong)ZBarReaderView *readerView;
@property (nonatomic,strong)UIActivityIndicatorView *waitActivity;

@property(nonatomic,strong)CMTrainSignView *TrainSignView;
@property(nonatomic,strong)CMTrainDetailSignController *signControl;
@property(nonatomic,strong)CMTrainSignController *signViewControl;

-(void)setInfo:(TTrainSignInItem &)item;
-(void)callBack:(NSString *)message;
-(void)callError;

@end

class CMTrainQRSignUpdateDataListener : public IMSimpleResultListener
{
    
    virtual  void OnRequestFinish(void* UserData, int Result)
    {
        CMSearchQRCode* trainview = (__bridge CMSearchQRCode*)UserData;
        
        
        [tool DisimissActivityIndicator];
        [trainview.waitActivity stopAnimating];
        
        if (Result == TResult::ESuccess ) {
            [trainview callBack:I(@"签到成功")];
            [[NSNotificationCenter defaultCenter]postNotificationName:@"signcountchange" object:nil];
        }
        else if (Result == TResult::EDuplicaterating) {
            [trainview callBack:I(@"您已签过到了")];
        }
        else if (Result == TResult::ENothing) {
            [trainview callBack:I(@"此签到不存在")];
        }
        else if(Result == TResult::ETimeNotStart){
            [trainview callBack:I(@"签到还未开始")];
        }
        else if(Result == TResult::ETimeEnd){
            [trainview callBack:I(@"签到时间已过期")];
        }
        else if(Result == TResult::EBeCancel){
            [trainview callBack:I(@"此签到已被取消")];
        }
        else if(Result == TResult::ENotBelong){
            [trainview callBack:I(@"您不在签到名单内")];
        }
        else{
            [trainview callError];
            //[tool ShowError:Result];
        }
        
    }
};



//
//  CMTrainDetailSignController.h
//  MLPlayer
//
//  Created by 张永兵 on 14/12/23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"
#import "cmtrainsigninlist.h"
#import "CMTrainSignView.h"

class CMTrainSignUpdateDataListener;
class CMTrainSigninViewUpdateDataListener;

@interface CMTrainDetailSignController : CMViewController
{
    TTrainSignInItem *curItem;
    
    UIScrollView *scrollView;
    
    CMTrainSignUpdateDataListener *m_pUpdataDataListerner;
    
    CMTrainSigninViewUpdateDataListener *m_prefreshViewListerner;
}

@property(nonatomic,strong)CMTrainSignView *TrainSignView;
@property(nonatomic,assign)BOOL isSweepPush; //是否从扫二维码页面push过来的

-(void)setInfo:(TTrainSignInItem &)item;
-(void)setInfoWithString:(NSString *)sid;
-(void)callBack;
-(void)initView;
@end


class CMTrainSignUpdateDataListener : public IMSimpleResultListener
{
    
    virtual  void OnRequestFinish(void* UserData, int Result)
    {
        CMTrainDetailSignController* trainview = (__bridge CMTrainDetailSignController*)UserData;
        
        
        [tool DisimissActivityIndicator];
        
        if (Result == TResult::ESuccess) {
            [[NSNotificationCenter defaultCenter]postNotificationName:@"signcountchange" object:nil];
            [trainview callBack];
        }
        else if(Result == TResult::ETimeNotStart){
            [tool ShowAlert:I(@"签到还未开始")];
        }
        else if(Result == TResult::ETimeEnd){
            [tool ShowAlert:I(@"签到时间已过期")];
        }
        else if(Result == TResult::EBeCancel){
            [tool ShowAlert:I(@"此签到已被取消")];
        }
        else if (Result == TResult::EDuplicaterating) {
            [tool ShowAlert:I(@"您已签过到了")];
        }
        else if (Result == TResult::ENothing) {
            [tool ShowAlert:I(@"此签到不存在")];
        }
        else if(Result == TResult::ENotBelong){
            [tool ShowAlert:I(@"您不在签到名单内")];
        }
        else{
            [tool ShowAlert:I(@"签到失败,请与管理员联系")];
        }
        
    }
};

class CMTrainSigninViewUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMTrainDetailSignController* trainview = (__bridge CMTrainDetailSignController*)UserData;
        
        
        [tool DisimissActivityIndicator];
        
        if (Result == TResult::ESuccess || Result == TResult::ENothing) {
            [trainview initView];
        }
        else{
            [tool ShowError:Result];
        }
        
    }
};



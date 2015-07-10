//
//  CMTrainApplyDetailController.h
//  MLPlayer
//
//  Created by 张永兵 on 14/12/23.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"
#import "cmtrainapplylist.h"

@class CMTrainApplyView;

class CMTrainApplyUpdateDataListener;
class CMTrainCancelApplyUpdateDataListener;
class CMTrainInfoUpdateDataListener;

@interface CMTrainApplyDetailController : CMViewController<UIAlertViewDelegate>
{
    TTrainApplyItem *curItem;
        
    CMTrainApplyUpdateDataListener *m_pUpdataDataListerner;
    
    CMTrainCancelApplyUpdateDataListener *m_pCancelApplyListerner;
    
    CMTrainInfoUpdateDataListener *m_refreshViewListerner;
    
    NSString *stateStr;
}

@property(nonatomic,strong)CMTrainApplyView *TrainApplyView;
-(void)setInfo:(TTrainApplyItem &)item;
-(void)setInfoWithString:(NSString *)sid;
-(void)CallBackSuccess;
-(void)initView;
@end

class CMTrainApplyUpdateDataListener : public IMSimpleResultListener
{
    
    virtual  void OnRequestFinish(void* UserData, int Result)
    {
        CMTrainApplyDetailController* trainview = (__bridge CMTrainApplyDetailController*)UserData;
        
        
        [tool DisimissActivityIndicator];
        
        if (Result == TResult::ESuccess || Result == TResult::ENothing) {
            [trainview CallBackSuccess];
        }
        else if(Result == TResult::ETimeNotStart) {
            [tool ShowAlert:I(@"报名还未开始")];
            
        }
        else if(Result == TResult::ETimeEnd) {
            [tool ShowAlert:I(@"报名已结束")];
            
        }
        else if(Result == TResult::EBeCancel) {
            [tool ShowAlert:I(@"此报名已被取消")];
            
        }
        else if(Result == TResult::EDuplicaterating) {
            [tool ShowAlert:I(@"不能重复报名")];
            
        }
        else if(Result == TResult::EOutNum) {
            [tool ShowAlert:I(@"报名人数已满")];
            
        }
        else if(Result == TResult::ENotBelong){
            [tool ShowAlert:I(@"您不在报名名单内")];
        }
        else{
            [tool ShowError:Result];
        }
        
    }	
};

class CMTrainCancelApplyUpdateDataListener : public IMSimpleResultListener
{
    
    virtual  void OnRequestFinish(void* UserData, int Result)
    {
        CMTrainApplyDetailController* trainview = (__bridge CMTrainApplyDetailController*)UserData;
        
        
        [tool DisimissActivityIndicator];
        
        if (Result == TResult::ESuccess || Result == TResult::ENothing) {
            [trainview CallBackSuccess];
        }
//        else if(Result == TResult::ETimeNotStart){
//            [tool ShowAlert:I(@"报名还未开始")];
//        }
//        else if(Result == TResult::ETimeEnd){
//            [tool ShowAlert:I(@"报名已结束")];
//        }
//        else if(Result == TResult::EBeCancel){
//            [tool ShowAlert:I(@"此报名已被取消")];
//        }
        else{
            [tool ShowError:Result];
        }
        
    }
};

class CMTrainInfoUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMTrainApplyDetailController* trainview = (__bridge CMTrainApplyDetailController*)UserData;
        
        
        [tool DisimissActivityIndicator];
        
        if (Result == TResult::ESuccess || Result == TResult::ENothing) {
            [trainview initView];
        }
        else{
            [tool ShowError:Result];
        }
        
    }	
};



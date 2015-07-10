//
//  CMTrainInfoViewController.h
//  MLPlayer
//
//  Created by 张永兵 on 14-12-19.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMViewController.h"
#import "CMMyExamControl.h"
#import "CMBrowserView.h"
#import "cmmytrainlist.h"
#import "CMChatViewController.h"
#import "CMPracticeControl.h"

@class CMSurveyListControl;
class CMTrainInfoViewUpdateDataListener;

@interface CMTrainInfoViewController : CMViewController<UITableViewDataSource,UITableViewDelegate>
{
    UITableView *m_pTableView;
    
    UIImageView *selview;
    
    int nSelectRow;
    
    CMBrowserView * browserview;//课程列表
    
    CMBrowserView * browsernewsview; //资讯列表
    
    CMMyExamControl *examControl;//测验列表
    
    CMChatViewController *chatControl;//交流区界面
    
    CMPracticeControl *practiceControl;//练习列表
    
    CMSurveyListControl *surveyControl;//调研列表
    
    TMyTrainItem  *curItem;
    
    CMTrainInfoViewUpdateDataListener *m_pUpdataDataListerner;
    
    NSMutableArray *topItemArr;//顶端栏目
    
    NSMutableArray *subviewsArr;
    
    UIButton *rightBarBtn;
    
@public
    TBrowserItem* currItem;
    
    TQAItem* currQaItem;
    
}

-(void)setItem:(TMyTrainItem &)item;
-(void)initView;

@property(nonatomic,strong)NSString *trainID;
@property(nonatomic,strong)NSString *draft;
@property(nonatomic,assign)BOOL isChatEnter;//是否从互动界面进入

@end


class CMTrainInfoViewUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMTrainInfoViewController* trainview = (__bridge CMTrainInfoViewController*)UserData;
        
        [tool DisimissActivityIndicator];
        
        if (Result == TResult::ESuccess || Result == TResult::ENothing) {
            [trainview initView];
        }
        else{
            [tool ShowError:Result];
        }
        
    }	
};




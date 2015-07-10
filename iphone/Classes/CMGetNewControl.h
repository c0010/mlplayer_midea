//
//  CMBrowserControl.h
//  MLPlayer
//
//  Created by sunjj on 11-9-27.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CustomBGAlert.h"
#import "cmgetnewcontent.h"
#import "CMItemView.h"
#import "CMAlertView.h"

class CMPushGotoCoursewareListener;
class CMPushGotoNewsListener;
class CMPushGotoSurveyListener;
class CMPushGotoExamListener;
class CMPushGotoExerciseListener;
class CMPushGotoQAListener;
class CMGetNewUpdateDataListener;
@interface CMGetNewView : CMItemView {
	CustomBGAlert* alert;
	CMGetNewUpdateDataListener* m_pUpdataDataListerner;
}
@property(nonatomic,strong)CustomBGAlert* alert;

-(id)initWithFrame:(CGRect)frame;
-(void)LoadData;
@end


//////////////////////////////////////////

@interface CMGetNewControl :  CMViewController
<UINavigationBarDelegate>
{
	CMGetNewView* getnewview;
	MLPlayerAppDelegate* appDelegate;
    
	BOOL bAppStateIsBackground;
    BOOL bIsPush;      //推送的判断
    BOOL bViewExist;   //view是否还存在
    BOOL bShouldPush;
    
    CMPushGotoCoursewareListener *m_pGotoCoursewareListener;
    CMPushGotoNewsListener *m_pCMGotoNewsListener;
    CMPushGotoSurveyListener *m_pCMGotoSurveyListener;
    CMPushGotoExamListener *m_pCMGotoExamListener;
    CMPushGotoExerciseListener * m_pCMGotoExerciseListener;
    CMPushGotoQAListener * m_pCMGotoQAListener;
    
    CMBrowser* tempBrowser;
    CMExamList* m_pExamlist;
    CMSurveyList * m_pSurveylist;
    CMQAList* m_pQalist;
    
    NSString *_sType;   //推送类型
    NSString *_sId;     //推送内容 id
    
    CMGetNewContent *m_pGetNewContent;
	CMGetNewUpdateDataListener* m_pUpdataDataListerner;
}
@property (nonatomic, assign) NSInteger model;
@property (nonatomic, assign) BOOL bAppStateIsBackground;  //推送来时 app状态
@property (nonatomic, strong) UILabel *titleLabel;
@property (nonatomic, strong) NSString *sType;
@property (nonatomic, strong) NSString *sId;

-(void)LoadData;

-(void)gotoPush;

-(void)gotoCourseware;
-(void)gotoNews;
-(void)gotoSurvey;
-(void)gotoQA;
-(void)gotoExercise;
-(void)gotoExam;

- (void)popWhenNoNermission;

@end

class CMGetNewUpdateDataListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        [tool DisimissActivityIndicator];
		CMGetNewControl* getnewview = (__bridge CMGetNewControl*)UserData;
        
		if (Result == TResult::ESuccess || Result == TResult::ENothing)
        {
            [getnewview gotoPush];
            
		}
        else
        {
			[tool ShowError:Result];
		}
		
	}	
};

//#pragma mark - 跳转到课件
//
//class CMPushGotoCoursewareListener : public IMUpdateDataListener
//{
//    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
//    {
//        NSLog(@"CMClassInfoBrowserListener OnUpdateDataProgress");
//    }
//    
//    virtual void OnUpdateDataFinish(void* UserData, int Result)
//    {
//        NSLog(@"CMClassInfoBrowserListener OnUpdateDataFinish");
//        if(Result == TResult::ESuccess )
//        {
//            CMGetNewControl* classInfoControl = (__bridge CMGetNewControl*)UserData;
//            [classInfoControl gotoCourseware];
//        }
//        else
//        {
//            
//            [tool DisimissActivityIndicator];
//        }
//        
//    }
//    
//};

#pragma mark - 跳转到资讯

class CMPushGotoNewsListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        NSLog(@"CMClassInfoBrowserListener OnUpdateDataProgress");
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        NSLog(@"CMClassInfoBrowserListener OnUpdateDataFinish");
        [tool DisimissActivityIndicator];
        CMGetNewControl* classInfoControl = (__bridge CMGetNewControl*)UserData;
        if(Result == TResult::ESuccess )
        {
            [classInfoControl gotoNews];
        }
        else if(Result == TResult::ENoPowerCourse){
            CMAlertView *alert = [[CMAlertView alloc] initWithTitle:I(@"提示") message:I(@"该资讯已经在后台进行下架") cancelButtonTitle:nil otherButtonTitles:I(@"确定") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
                if (buttonIndex == BUTTON_CONFIRM_TAG){
                    [classInfoControl popWhenNoNermission];
                }
            }] ;
            [alert setDisabledOutSide:YES];
            [alert show];
        }
        else
        {
            [tool ShowError:Result];
        }
    }
};


#pragma mark - 跳转到调研

class CMPushGotoSurveyListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        NSLog(@"CMClassInfoBrowserListener OnUpdateDataProgress");
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        NSLog(@"CMClassInfoBrowserListener OnUpdateDataFinish");
        [tool DisimissActivityIndicator];
        CMGetNewControl* classInfoControl = (__bridge CMGetNewControl*)UserData;
        if(Result == TResult::ESuccess )
        {
            [classInfoControl gotoSurvey];
        }
        else if(Result == TResult::ENoPowerCourse){
            CMAlertView *alert = [[CMAlertView alloc] initWithTitle:I(@"提示") message:I(@"该调研已经在后台进行下架") cancelButtonTitle:nil otherButtonTitles:I(@"确定") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
                if (buttonIndex == BUTTON_CONFIRM_TAG){
                    [classInfoControl popWhenNoNermission];
                }
            }] ;
            [alert setDisabledOutSide:YES];
            [alert show];
        }
        
        else
        {
            [tool ShowError:Result];
        }
        
    }
    
};

#pragma mark - 跳转到考试

class CMPushGotoExamListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        NSLog(@"CMClassInfoBrowserListener OnUpdateDataProgress");
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        NSLog(@"CMClassInfoBrowserListener OnUpdateDataFinish");
        [tool DisimissActivityIndicator];
        CMGetNewControl* classInfoControl = (__bridge CMGetNewControl*)UserData;
        if(Result == TResult::ESuccess )
        {
            [classInfoControl gotoExam];
        }
        else if(Result == TResult::ENoPowerCourse){
            CMAlertView *alert = [[CMAlertView alloc] initWithTitle:I(@"提示") message:I(@"该测验已经在后台进行下架") cancelButtonTitle:nil otherButtonTitles:I(@"确定") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
                if (buttonIndex == BUTTON_CONFIRM_TAG){
                    [classInfoControl popWhenNoNermission];
                }
            }] ;
            [alert setDisabledOutSide:YES];
            [alert show];
        }
        
        else
        {
            [tool ShowError:Result];
        }
        
    }
    
};

//#pragma mark - 跳转到练习
//
//class CMPushGotoExerciseListener : public IMUpdateDataListener
//{
//    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
//    {
//        NSLog(@"CMClassInfoBrowserListener OnUpdateDataProgress");
//    }
//    
//    virtual void OnUpdateDataFinish(void* UserData, int Result)
//    {
//        NSLog(@"CMClassInfoBrowserListener OnUpdateDataFinish");
//        if(Result == TResult::ESuccess )
//        {
//            CMGetNewControl* classInfoControl = (__bridge CMGetNewControl*)UserData;
//            [classInfoControl gotoExercise];
//        }
//        else
//        {
//            
//            [tool DisimissActivityIndicator];
//        }
//        
//    }
//    
//};

#pragma mark - 跳转到问答

class CMPushGotoQAListener : public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        NSLog(@"CMClassInfoBrowserListener OnUpdateDataProgress");
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        NSLog(@"CMClassInfoBrowserListener OnUpdateDataFinish");
        [tool DisimissActivityIndicator];
        if(Result == TResult::ESuccess )
        {
            CMGetNewControl* classInfoControl = (__bridge CMGetNewControl*)UserData;
            [classInfoControl gotoQA];
        }
        else
        {
            [tool ShowError:Result];
        }
        
    }
    
};


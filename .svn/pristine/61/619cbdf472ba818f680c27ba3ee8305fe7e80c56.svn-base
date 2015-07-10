//
//  CMSurveyControl.h
//  MLPlayer
//
//  Created by sunjj on 11-5-4.
//  Copyright 2011 w. All rights reserved.

//栏目设备

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "cmsurvey.h"
#import "cmcommon.h"
#import "ComplexButton.h"
#import "CMIntrodocutionViewController.h"
#import "CMMainControl.h"
#import "CMAlertView.h"

//#import "CMSurveyListControl.h"

@class CMSurveyListControl;

class CMSurveyUpdateDataListener;
class CMSurveySimpleResultListener;

@interface CMSurveyControl : CMViewController <UITextViewDelegate,UITableViewDelegate,UITableViewDataSource> {
	
	CMSurveyUpdateDataListener *m_pUpdateDataListener;
	CMSurveySimpleResultListener* m_pSimpleResultListener;
	CMSurvey *m_survey;
	
	UITableView* tableView;
	UITextView* answerView;
    UIView *bg_view;

	ComplexButton* prebtn;
	ComplexButton* nextbtn;
    
    UILabel* words_Num;
    NSUInteger input_words_num;
    BOOL isBeyond;
    float keyboardHeight;
    
    UIGestureRecognizer *textViewGesture;
    
    BOOL isDataReady;
    
    UIToolbar *toolbar;
}

@property(nonatomic,strong) UITableView *tableView;
@property(nonatomic,strong) UITextView *answerView;
@property(nonatomic,strong) UILabel *words_Num;
@property(nonatomic,strong) CMSurveyListControl *surveyListControl;
@property(nonatomic,assign)     BOOL isDataReady;


-(void)OpenSurvey:(NSString*)title surveyid: (const char*)surveyid;
-(void)UpdateView;
-(void)click:(id)sender;
-(UIButton*)GetBtn:(bool)bcheck type:(int)ntype;
- (void)reportHoriziontalSwipe:(UISwipeGestureRecognizer *)tap;
@end

class CMSurveySimpleResultListener : public IMSimpleResultListener {
	
public:
	CMSurveySimpleResultListener(){};
	~CMSurveySimpleResultListener(){};
	
    //提交回调
	void OnRequestFinish(void* UserData, int Result)
	{
		NSLog(@"CMSurveySimpleResultListener OnRequestFinish Result=%d",Result);
		
		CMSurveyControl* listView = (__bridge CMSurveyControl*)UserData;
        
        [tool DismissAtEnd];
	
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{	
//            [MessageBox DoModalWithTitle:[NSString stringWithFormat:I(@"提交成功")] message:nil mode:MODE_OK confirm:^{
//                
//                NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
//                NSString *openpush = [ud objectForKey:kUDOpenPush];
//                if ([openpush isEqualToString:@"1"]) {
//                    CMMainControl* mainController = [[[CMMainControl alloc] init] autorelease];
//
//                    [ud setObject:@"0" forKey:kUDOpenPush];
//                    NSString *type = [ud objectForKey:kUDPushType];
//                    
//                    int selectRow = 0;
//                    if ([type isEqualToString:@"course"] || [type isEqualToString:@"position_course"]) {
//                        selectRow = 0;
//                    }
//                    else if ([type isEqualToString:@"news"]){
//                        selectRow = 1;
//                    }
//                    else if ([type isEqualToString:@"exam"] || [type isEqualToString:@"exercise"]){
//                        selectRow = 4;
//                    }
//                    else if ([type isEqualToString:@"survey"]){
//                        selectRow = 4;
//                    }
//                    [mainController setSelectedIndex:selectRow];
//                    
//                    [listView.navigationController pushViewController:mainController animated:NO];
//                }
//                else{
//                
//                    NSMutableArray *arr = [[NSMutableArray alloc] initWithArray:listView.navigationController.viewControllers];
//                    
//                    int nIndex = -1;
//                    
//                    for (int i = 0; i < [arr count]; i++)
//                    {
//                        if ([[arr objectAtIndex:i] isKindOfClass:[CMIntrodocutionViewController class]])
//                        {
//                            nIndex = i;
//                            break;
//                        }
//                    }
//                    
//                    if (nIndex >= 0)
//                    {
//                        [listView.navigationController popToViewController:[listView.navigationController.viewControllers objectAtIndex:nIndex-1] animated:YES];
//                        [listView.surveyListControl refreshTableView];
//                        [[NSNotificationCenter defaultCenter] postNotificationName:@"finishsurvey" object:nil];
//                    }
//                    else
//                    {
//                        [listView.navigationController popViewControllerAnimated:YES];
//                    }
//                }
//            } cancel:^{
//                
//            }];
            

            
           CMAlertView *alert = [[CMAlertView alloc] initWithTitle:[NSString stringWithFormat:I(@"提交成功")] message:nil cancelButtonTitle:nil otherButtonTitles:I(@"确定") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
                if (buttonIndex == BUTTON_CONFIRM_TAG) {
                    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
                    NSString *openpush = [ud objectForKey:kUDOpenPush];
                    if ([openpush isEqualToString:@"1"]) {
                        CMMainControl* mainController = [[CMMainControl alloc] init];
                        
                        [ud setObject:@"0" forKey:kUDOpenPush];
                        NSString *type = [ud objectForKey:kUDPushType];
                        
                        int selectRow = 0;
                        if ([type isEqualToString:@"course"] || [type isEqualToString:@"position_course"]) {
                            selectRow = 0;
                        }
                        else if ([type isEqualToString:@"news"]){
                            selectRow = 1;
                        }
                        else if ([type isEqualToString:@"exam"] || [type isEqualToString:@"exercise"]){
                            selectRow = 4;
                        }
                        else if ([type isEqualToString:@"survey"]){
                            selectRow = 4;
                        }
                        [mainController setSelectedIndex:selectRow];
                        
                        [listView.navigationController pushViewController:mainController animated:NO];
                    }
                    else{
                        
                        NSMutableArray *arr = [[NSMutableArray alloc] initWithArray:listView.navigationController.viewControllers];
                        
                        int nIndex = -1;
                        
                        for (int i = 0; i < [arr count]; i++)
                        {
                            if ([[arr objectAtIndex:i] isKindOfClass:[CMIntrodocutionViewController class]])
                            {
                                nIndex = i;
                                break;
                            }
                        }
                        
                        if (nIndex >= 0)
                        {
                            [listView.navigationController popToViewController:[listView.navigationController.viewControllers objectAtIndex:nIndex-1] animated:YES];
                            [listView.surveyListControl refreshTableView];
                            [[NSNotificationCenter defaultCenter] postNotificationName:@"finishsurvey" object:nil];
                        }
                        else
                        {
                            [listView.navigationController popViewControllerAnimated:YES];
                        }
                    }
                }
                else if (buttonIndex == BUTTON_CANCEL_TAG){
                }
            }] ;
            [alert setDisabledOutSide:YES];
            [alert show];
		}
		else
		{
            [tool ShowAlert:[NSString stringWithFormat:I(@"提交%@失败"),I(@"调研")]];
		}
	}
};

class CMSurveyUpdateDataListener :public IMUpdateDataListener
{
public:
	CMSurveyUpdateDataListener(){};
	~CMSurveyUpdateDataListener(){};
	
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{
		//CMMainControl* mainControl = (CMMainControl*)UserData;
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		NSLog(@"CMSurveyUpdateDataListener OnUpdateDataFinish Result=%d",Result);
		
        CMSurveyControl* listView = (__bridge CMSurveyControl*)UserData;
		
        [tool DisimissActivityIndicator];
		
        if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
            listView.isDataReady=YES;

			[listView UpdateView];
		}else {
			[tool ShowError:Result];
		}
	}
	
	
};

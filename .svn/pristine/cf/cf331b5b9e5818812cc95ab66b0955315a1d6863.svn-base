//
//  CMExamInfoControl.h
//  MLPlayer
//
//  Created by sunjj on 11-9-27.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMTableViewCell.h"
#import "cmcommon.h"
#import "cmexercise.h"
#import "cmwrongquestion.h"
#import "cmexam.h"
#import "tool.h"
#import "cmquestionhandler.h"
#import "CMIntrodocutionViewController.h"

#define CommitStatusAuto 1
#define CommitStatusManual 2
#define CommitStatusNone 0

class CMExamInfoUpdateDataListener;
class CMExamInfoSimpleResultListener;
class CMQuestionUpdateDataListener;

class CMQuestionInfoSimpleResultListener;
@class ComplexButton;
@interface CMExamInfoControl : CMViewController <UITextViewDelegate,UITableViewDelegate,UITableViewDataSource>{
	
	UIToolbar *toolbar;
	ComplexButton* prebtn;
	ComplexButton* nextbtn;
	ComplexButton* knowbtn;

	BOOL m_type;
	BOOL hit;
	BOOL m_bKnow;
    BOOL bIsMultiple; //多选题时,如果未显示答案,点击下一题显示当前答案不进入下一题(未做,已显示 情况直接进入下一题)
	NSString* m_model;
	NSString* m_oper;//start review
	char m_surveyid[64];
	
	UITableView* TableViewList;
	UITextView* answerView;

    float keyboardHeight;

    UILabel* words_Num;
    NSUInteger input_words_num;
    BOOL isBeyond;
	
	CMExamInfoUpdateDataListener *m_pUpdateDataListener;
	CMExamInfoSimpleResultListener *m_pSimpleResultListener;
    
    CMQuestionUpdateDataListener  *m_qUpdateDataListener;
    
    CMQuestionInfoSimpleResultListener  *m_qSimpleResultListener;
    
    NSTimer *_examTimer;
    
    UILabel *_lbltimer;
    
    CMExam *exam;
    
    NSInteger examDuration;
    
    NSInteger timePast;
    
    int nCompleteNum;
    
    BOOL GuideDisplay;
    
    BOOL showAnswer;
    
    UIGestureRecognizer *textViewGesture;
    
    BOOL finished;
    
    NSMutableDictionary * _hitDict;
    
    BOOL isDataReady;
    
    NSInteger nDuration;//测验总时长
    NSInteger nExamRemainTime; //测验剩余时间 秒为单位
    NSInteger nCurIndex;//当前第几题
    
    @public
    CMWrongQuestion * m_pExercise;

    NSInteger commitStatus;
}

@property (nonatomic,weak)id <CMExamControlDelegate> delegate;
@property(nonatomic,strong)  NSTimer *examTimer;
@property(nonatomic,strong) UILabel *lbltimer;
@property(nonatomic,assign)      NSInteger examDuration;
@property(nonatomic,assign)      NSInteger timePast;
@property(nonatomic,strong)      NSMutableDictionary * hitDict;
@property(nonatomic,assign)      NSInteger nCurIndex;
@property(nonatomic,assign)      int nCompleteNum;


-(void)Commit;
- (void)judgeBack;
-(void)OpenSurvey:(NSString*)model surveyid:(const char*)surveyid oper:(NSString*)oper;
-(void)UpdateView;
-(void)setbtn:(BOOL)type;
-(void)sendResult:(int)Result;
-(bool)IsChecked;
- (void)reportHoriziontalSwipe:(UISwipeGestureRecognizer *)tap;
-(void)setDuration;
- (void)setDuration:(NSInteger)duration ReaminTime:(NSInteger)remainTime index:(int)nIndex;
- (void)updateDisplayTimer;
- (void)saveQuestion;
- (void)gotoIndex:(id)sender;
- (void)pauseExam:(id)sender;
- (void)continueExam:(id)sender;
@end



class CMQuestionUpdateDataListener :public IMUpdateDataListener
{
public:
	CMQuestionUpdateDataListener(){};
	~CMQuestionUpdateDataListener(){};
	
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{
        //CMMainControl* mainControl = (CMMainControl*)UserData;
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		NSLog(@"QUESTION UPDATE = %d",Result);
        
	//	CMExamInfoControl* listView = (CMExamInfoControl*)UserData;
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
	//		[listView UpdateView];
		}
		else {
	//		[tool ShowError:Result];
		}
	}
	
};

class CMQuestionInfoSimpleResultListener : public IMSimpleResultListener {
	
public:
	CMQuestionInfoSimpleResultListener(){};
	~CMQuestionInfoSimpleResultListener(){};
	
	void OnRequestFinish(void* UserData, int Result)
	{        
	}
};



class CMExamInfoSimpleResultListener : public IMSimpleResultListener {
	
public:
	CMExamInfoSimpleResultListener(){};
	~CMExamInfoSimpleResultListener(){};
	
	void OnRequestFinish(void* UserData, int Result)
	{ 		NSLog(@"CMExamInfoSimpleResultListener OnRequestFinish Result = %d",Result);

		CMExamInfoControl* listView = (__bridge CMExamInfoControl*)UserData;
//		[[listView prevBarItem] setEnabled:TRUE];
//		[[listView nextBarItem] setEnabled:TRUE];
        
        
        [tool DismissAtEnd];
        
		if(Result != TResult::ESuccess)
        {
			[listView sendResult:Result];
        
            listView->commitStatus=CommitStatusNone;
        }
		else
		{
			//commitsuccess
			[listView sendResult:Result];
			[listView.delegate willRershTableListView];
			[listView judgeBack];
		}
	}
};

class CMExamInfoUpdateDataListener :public IMUpdateDataListener
{
public:
	CMExamInfoUpdateDataListener(){};
	~CMExamInfoUpdateDataListener(){};
	
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{
			//CMMainControl* mainControl = (CMMainControl*)UserData;
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{	
		NSLog(@"CMExamInfoUpdateDataListener OnUpdateDataFinish Result = %d",Result);

        [tool DisimissActivityIndicator];
		CMExamInfoControl* listView = (__bridge CMExamInfoControl*)UserData;
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
            if(listView->m_pExercise->GetItemCount()<=0)
            {
                [tool ShowAlert:I(@"暂无题目信息")];
            }
            
            [listView setDuration];

			[listView UpdateView];
            
		}
		else {

			[tool ShowError:Result];
            if (CMGlobal::TheOne().IsOffline()) {
                [listView.navigationController popToRootViewControllerAnimated:YES];
            }
		}
	}
	
};
//
//  CMIntrodocutionViewController.h
//  MLPlayer
//
//  Created by wmgwd on 13-11-6.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "cmgetnewcontent.h"
#import "cmexercise.h"
#import "cmexamlist.h"
#import "CMSurveyListControl.h"

//@class CMSurveyListControl;

@interface CMIntrodocutionViewController : CMViewController
{
    UIScrollView *mScrollView;
    CMExercise *m_pExercise;
    
    CMExamList *m_pExamList;

    NSInteger nCurindex;
    
    NSInteger nRow;
    
    //错题库数
    NSInteger nWrongCount;
    
    //剩余时间（推送使用）
    NSInteger nLastTime;
    
    @public
    CMExerciseList *m_pExerciseList;
}

@property (nonatomic, strong) NSMutableDictionary *itemDic;
@property (nonatomic, strong) CMSurveyListControl *surveyListControl;
@property (nonatomic, assign) NSInteger nRow;
- (IBAction)gotoRank:(id)sender;
- (IBAction)gotoWrong:(id)sender;
- (IBAction)startBtnPressed:(id)sender;
- (void)examback:(id)sender;
- (void)continuePractice:(id)sender;
- (void)setHanlder:(CMExamList *)hanler row:(int)index;
@end

    //
//  CMExamInfoControl.m
//  MLPlayer
//
//  Created by sunjj on 11-9-27.
//  Copyright 2011 w. All rights reserved.
//
#import "stdafx.h"
#import "CMExamInfoControl.h"
#import <QuartzCore/QuartzCore.h>
#import "ComplexButton.h"
#import "CMMainControl.h"
#import "CMCardViewController.h"
#import "CMAlertView.h"

#define kCellIdentifierEdit @"cellIdEdit"
#define kCellIdentifierCheck @"cellIdCheck"

@implementation CMExamInfoControl

@synthesize delegate;
@synthesize examTimer=_examTimer;
@synthesize lbltimer=_lbltimer;
@synthesize examDuration;
@synthesize timePast;
@synthesize hitDict=_hitDict;
@synthesize nCurIndex;
@synthesize nCompleteNum;
-(void)setbtn:(BOOL)type
{
	m_type = type;
}


//设置时间
- (void)setDuration:(NSInteger)duration ReaminTime:(NSInteger)remainTime index:(int)nIndex
{
    nDuration = duration;
    nExamRemainTime = remainTime;
    nCurIndex = nIndex;
    
    self.examDuration = nExamRemainTime;//exam->GetDuration();
    
}

#pragma mark -timerOperator

-(void)setDuration
{
    if([m_model isEqualToString:@"exam"]&&[m_oper isEqualToString:@"start"])
    {
//        self.examDuration = nExamRemainTime;//exam->GetDuration();
        
        if(GuideDisplay==YES)
        {
            [[NSNotificationCenter defaultCenter] addObserver:self
                                                     selector:@selector(startTimer)
                                                        name:@"GuideDismiss" object:nil];
        }
        else
        [self startTimer];
        
    }
}

-(void)startTimer
{
    if(GuideDisplay==YES)
    {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:@"GuideDismiss" object:nil];
        GuideDisplay =NO;

    }

    self.lbltimer.hidden = NO;
    
    if(self.examDuration > 0)
    {
        if (self.examTimer) {
            [self.examTimer invalidate];
            self.examTimer = nil;
        }
        self.examTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(updateDisplayTimer) userInfo:nil repeats:YES];
    }
    else
    {
//	    self.lbltimer.hidden = YES;  //删除原来的多余代码，不需在这里实现自动交卷。而且原代码还会导致测验时长为0时（不限制时长），开始测验就立即自动交卷的bug.
        if ([m_oper isEqualToString:@"start"] && !CMGlobal::TheOne().IsOffline())
        {
            [self performSelectorOnMainThread:@selector(CommitWihtoutAsk) withObject:nil waitUntilDone:NO];
        }
    }
    
    
}

-(void)updateDisplayTimer
{
    NSCalendar *calendar = [NSCalendar currentCalendar];

    
    self.timePast++;
    NSInteger restAllSeconds=self.examDuration-self.timePast;
    NSDateComponents *restTime=[[NSDateComponents alloc]init];
    
    NSInteger tempInt;
    NSInteger restHour=(NSInteger)(restAllSeconds/(60*60));
    
    tempInt= restAllSeconds-(restHour*(60*60));//减去小时
    NSInteger restMinute=(NSInteger)(tempInt/60);
    
    
    tempInt -= restMinute*60;//减去分钟
    NSInteger restSecond=(NSInteger)(tempInt);
    
    [restTime setHour:restHour];
    [restTime setMinute:restMinute];
    [restTime setSecond:restSecond];
    
    NSDate *restDate = [calendar dateFromComponents:restTime];//目标时间
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    
    //zzz表这样返回的日期字符将不包含时区信息。
    [dateFormatter setDateFormat:@"HH:mm:ss"];
    
    NSString *destDateString = [dateFormatter stringFromDate:restDate];
    
    self.lbltimer.text=destDateString;
    CMRELEASE(dateFormatter);
    CMRELEASE(restTime);
    
    
    if(self.timePast>=self.examDuration)
    {
        [self performSelectorOnMainThread:@selector(CommitWihtoutAsk) withObject:nil waitUntilDone:NO];
        
    }
    
}

-(void)stopTimer
{
    [self.examTimer setFireDate:[NSDate date]];//继续时间

    [self.examTimer invalidate];
    self.examTimer=nil;
    
    return;
}

#pragma mark -operator
-(void)addWrong
{
    
	[knowbtn setTitle:I(@"移除错题")// @"我懂了"
             forState:UIControlStateNormal];
	[knowbtn addTarget:self action:@selector(btnknow) forControlEvents:UIControlEventTouchUpInside];
	[knowbtn setImage:[UIImage imageNamed:@"know_n"] forState:UIControlStateNormal];
	[knowbtn setImage:[UIImage imageNamed:@"know_p"] forState:UIControlStateHighlighted];
	m_pExercise->SetWrong(TRUE);
    m_bKnow = NO;
}


-(void)btnknow
{
    //我懂了
    
        m_pExercise->SetWrong(FALSE);
    
        if(m_pExercise->isWrong()&&[m_model isEqualToString:@"wrong"])//判断是否在错题库
        {
            m_bKnow = NO;//yes未懂
            [knowbtn setTitle:I(@"移除错题")// @"我懂了"
                     forState:UIControlStateNormal];
            [knowbtn addTarget:self action:@selector(btnknow) forControlEvents:UIControlEventTouchUpInside];
            [knowbtn setImage:[UIImage imageNamed:@"know_n"] forState:UIControlStateNormal];
            [knowbtn setImage:[UIImage imageNamed:@"know_p"] forState:UIControlStateHighlighted];
            
        }else {
            
            m_bKnow = YES;//yes已懂
            [knowbtn setTitle:I(@"加入错题")//@"加入错题库"
                     forState:UIControlStateNormal];
            [knowbtn addTarget:self action:@selector(addWrong) forControlEvents:UIControlEventTouchUpInside];
            [knowbtn setImage:[UIImage imageNamed:@"unknow_n"] forState:UIControlStateNormal];
            [knowbtn setImage:[UIImage imageNamed:@"unknow_p"] forState:UIControlStateHighlighted];

        }

}

-(void)btnanser
{
	hit = TRUE;//显示答案
    
    if(![m_model isEqualToString:@"exam"])
    {
        [self.hitDict setObject:[NSNumber numberWithBool:YES] forKey:[NSString stringWithFormat:@"%d",m_pExercise->GetCurIndex()]];
        m_pExercise->SetIsChecked(hit);
        if (![self IsChecked]) {
            m_pExercise->SetWrong(TRUE);
        }
    }
    
	//m_oper = strTmp;
	if([m_model isEqualToString:@"wrong"])
    {
        //错题答对，自动移除
        if(m_pExercise->isOptionAnswerRight())
        {
            m_pExercise->SetWrong(FALSE);
        }
        
        [knowbtn setTitle:I(@"移除错题")// @"我懂了"
                 forState:UIControlStateNormal];
        [knowbtn addTarget:self action:@selector(btnknow) forControlEvents:UIControlEventTouchUpInside];
        [knowbtn setImage:[UIImage imageNamed:@"know_n"] forState:UIControlStateNormal];
        [knowbtn setImage:[UIImage imageNamed:@"know_p"] forState:UIControlStateHighlighted];
        
    }else
    {
        if(![m_model isEqualToString:@"exam"])
            knowbtn.hidden=YES;
    }
	
	[TableViewList reloadData];
}

-(void)sendResult:(int)Result
{
	NSString *strValue=nil;
	
	if ([m_model isEqualToString:@"practice"]) {
		strValue =[NSString stringWithString:I(@"练习")];
		
	}else if ([m_model isEqualToString:@"wrong"]) {
		
		strValue =[NSString stringWithString:I(@"错题")];
	}else if ([m_model isEqualToString:@"exam"]) {
		
		strValue =[NSString stringWithString:I(@"测验")];
	}
	
	if(Result != TResult::ESuccess)				
        [tool ShowAlert:[NSString stringWithFormat:I(@"提交%@失败"),strValue]];

	else
	{
        if([m_model isEqualToString:@"exam"]&&[m_oper isEqualToString:@"start"]&&commitStatus==CommitStatusAuto){
            
            [[NSNotificationCenter defaultCenter] postNotificationName:@"examcountchange" object:nil];

//            [MessageBox DoModalWithTitle:[NSString stringWithFormat:I(@"考试时间到，系统自动交卷"),strValue] message:nil mode:MODE_OK];
            
            CMAlertView *alert = [[CMAlertView alloc] initWithTitle:[NSString stringWithFormat:I(@"考试时间到，系统自动交卷"),strValue] message:nil cancelButtonTitle:nil otherButtonTitles:I(@"确定") completionBlock:nil];
            [alert setDisabledOutSide:YES];
            [alert show];
        }
        else
            [tool ShowAlert:[NSString stringWithFormat:I(@"提交%@成功"),strValue]];

	}
    
}

- (void)judgeBack
{
    NSArray *arr = self.navigationController.viewControllers;
    
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSString *openpush = [ud objectForKey:kUDOpenPush];
    if ([openpush isEqualToString:@"1"]) {
# if ! __has_feature(objc_arc)
        CMMainControl* mainController = [[[CMMainControl alloc] init] autorelease];
# else
        CMMainControl* mainController = [[CMMainControl alloc] init];
# endif

//        MLPlayerAppDelegate *appdelegate = [UIApplication sharedApplication].delegate;
//        appdelegate.navigationController.navigationBarHidden = YES;
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
        
		[self.navigationController pushViewController:mainController animated:NO];
        return;

    }
    
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
        [[NSNotificationCenter defaultCenter] postNotificationName:@"completeexam" object:nil];
        [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:nIndex] animated:YES];
    }
    else
    {
        [self.navigationController popViewControllerAnimated:YES];
    }
}

-(void)prevQ{
    if(isDataReady==NO)
        return;
    
    if ([m_model isEqualToString:@"practice"]) {
        hit = FALSE;
        if (!m_pExercise->isOptionAnswerRight() && [self IsChecked])
        {
            m_pExercise->SetWrong(true);
        }
        
        //选择下一题时 判断当前题目是否做对
        if (m_pExercise->isOptionAnswerRight() && [self IsChecked])
        {
            m_pExercise->setRight();
        }
        
        TQuestionItem items;
        m_pExercise->GetCurItem(items);
        if (items.nType == TQuestionType::EMultiple)
        {
            bIsMultiple = items.isChecked;
            //多选题 下一题时,查看答案显示
            if ([self IsChecked] && !bIsMultiple) {
                m_pExercise->SetExerciseAnswer(TRUE);
                [self UpdateMultipleView]; //刷新 多选(不需要 重置tableview位置)
                return;
            }
        }
        if (items.nType == TQuestionType::EText)
        {
            if ([NSStringFrom(items.sAnswer) isEqualToString:NSStringFrom(items.sRightAnswer)])
            {
                m_pExercise->setRight();
                m_pExercise->SetIsChecked(TRUE);
            }
            else if (NSStringFrom(items.sAnswer).length > 0)
            {
                m_pExercise->SetWrong(TRUE);
                m_pExercise->SetIsChecked(TRUE);
            }
        }
        
    }else if ([m_model isEqualToString:@"wrong"]) {
        
        if ([m_oper isEqualToString:@"start"]) {
            hit = FALSE;
            
            //			if (!m_pExercise->isOptionAnswerRight() && [self IsChecked]) {
            //				m_pExercise->SetWrong(true);
            //			}
            
            //错题答对，自动移除
            if(m_pExercise->isOptionAnswerRight())
            {
                m_pExercise->SetWrong(FALSE);
            }
            else{
                if ([self IsChecked]) {
                    m_pExercise->SetWrong(true);
                }
            }
            
        }else if ([m_oper isEqualToString:@"view"]) {
            hit = TRUE;
        }
        
        TQuestionItem items;
        m_pExercise->GetCurItem(items);
        if (items.nType == TQuestionType::EMultiple)
        {
            bIsMultiple = items.isChecked
            ;
            //多选题 下一题时,查看答案显示
            if ([self IsChecked] && !bIsMultiple) {
                m_pExercise->SetExerciseAnswer(TRUE);
                [self UpdateMultipleView]; //刷新 多选(不需要 重置tableview位置)
                return;
            }
        }
        if (items.nType == TQuestionType::EText)
        {
            if ([NSStringFrom(items.sAnswer) isEqualToString:NSStringFrom(items.sRightAnswer)])
            {
                m_pExercise->SetWrong(FALSE);
            }
            else if (NSStringFrom(items.sAnswer).length > 0)
            {
                m_pExercise->SetWrong(TRUE);
            }
        }
        
        if ([self IsChecked])
        {
            m_pExercise->UpdateWrongTime((int)[NSDate timeIntervalSinceReferenceDate]);
        }
        
    }else if ([m_model isEqualToString:@"exam"]) {
        
        if ([m_oper isEqualToString:@"start"]) {
            hit = FALSE;
            
        }else if ([m_oper isEqualToString:@"view"]) {
            hit = TRUE;
        }
    }

    
	if(m_pExercise)
	{		
		if(m_pExercise->Prev()==FALSE)
        {
            [tool ShowAlert:I(@"已至第一题！")];
            return;//不刷新界面
        }
	}
	[self UpdateView];
    
}
-(void)nextQ
{
    
    if(isDataReady==NO)
        return;
    
    
	if ([m_model isEqualToString:@"practice"]) {
		hit = FALSE;
		if (!m_pExercise->isOptionAnswerRight() && [self IsChecked])
        {
			m_pExercise->SetWrong(true);
		}
        
        //选择下一题时 判断当前题目是否做对
        if (m_pExercise->isOptionAnswerRight() && [self IsChecked])
        {
            m_pExercise->setRight();
        }
        
        TQuestionItem items;
        m_pExercise->GetCurItem(items);
        if (items.nType == TQuestionType::EMultiple)
        {
            bIsMultiple = items.isChecked;
            //多选题 下一题时,查看答案显示
            if ([self IsChecked] && !bIsMultiple) {
                m_pExercise->SetExerciseAnswer(TRUE);
                [self UpdateMultipleView]; //刷新 多选(不需要 重置tableview位置)
                return;
            }
        }
        if (items.nType == TQuestionType::EText)
        {
            if ([NSStringFrom(items.sAnswer) isEqualToString:NSStringFrom(items.sRightAnswer)])
            {
                m_pExercise->setRight();
                m_pExercise->SetIsChecked(TRUE);
            }
            else if (NSStringFrom(items.sAnswer).length > 0)
            {
                m_pExercise->SetWrong(TRUE);
                m_pExercise->SetIsChecked(TRUE);
            }
        }
		
	}else if ([m_model isEqualToString:@"wrong"]) {
		
		if ([m_oper isEqualToString:@"start"]) {
			hit = FALSE;
			
//			if (!m_pExercise->isOptionAnswerRight() && [self IsChecked]) {
//				m_pExercise->SetWrong(true);
//			}
            
            //错题答对，自动移除
            if(m_pExercise->isOptionAnswerRight())
            {
                m_pExercise->SetWrong(FALSE);
            }
            else{
                if ([self IsChecked]) {
                    m_pExercise->SetWrong(true);
                }
            }
            
		}else if ([m_oper isEqualToString:@"view"]) {
			hit = TRUE;
		}
        
        TQuestionItem items;
        m_pExercise->GetCurItem(items);
        if (items.nType == TQuestionType::EMultiple)
        {
            bIsMultiple = items.isChecked
            ;
            //多选题 下一题时,查看答案显示
            if ([self IsChecked] && !bIsMultiple) {
                m_pExercise->SetExerciseAnswer(TRUE);
                [self UpdateMultipleView]; //刷新 多选(不需要 重置tableview位置)
                return;
            }
        }
        if (items.nType == TQuestionType::EText)
        {
            if ([NSStringFrom(items.sAnswer) isEqualToString:NSStringFrom(items.sRightAnswer)])
            {
                m_pExercise->SetWrong(FALSE);
            }
            else if (NSStringFrom(items.sAnswer).length > 0)
            {
                m_pExercise->SetWrong(TRUE);
            }
        }
        
        if ([self IsChecked])
        {
            m_pExercise->UpdateWrongTime((int)[NSDate timeIntervalSinceReferenceDate]);
        }
		
	}else if ([m_model isEqualToString:@"exam"]) {
		
		if ([m_oper isEqualToString:@"start"]) {
			hit = FALSE;
			
		}else if ([m_oper isEqualToString:@"view"]) {
			hit = TRUE;
			}
	}
	
	if(m_pExercise)
	{
		if(m_pExercise->Next() == FALSE)
		{
            [tool ShowAlert:I(@"已至最后一题！")];
            return;//不刷新界面
//            if([m_model isEqualToString:@"exam"]&&[m_oper isEqualToString:@"view"])
//            {
//            //如果是查看测试，则不提交
//                [MessageBox DoModalWithTitle:I(@"已至最后一题！") message:nil mode:MODE_OK];
//            }
//            else
//            {
//                [self Commit];
//            }
		}
	}
	[self UpdateView];
}
-(bool)IsChecked
{
	TOption item;

	for(int i=0;i<m_pExercise->GetItemOptionCount(); i++)
	{
		if(m_pExercise->GetItemOption(i, item))
		{
			if(item.bCheck)
				return YES;
		}
	}
	return NO;
}

-(void)CommitWihtoutAsk
{
    [self stopTimer];
    
    if(m_pExercise)
	{
        [answerView endEditing:YES];

        finished=YES;
       
        if(commitStatus==CommitStatusNone)
        {
            NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
            [ud removeObjectForKey:@"exam"];
            [ud setObject:@"0" forKey:kUDOpenPush];
            
            [tool ShowBeforeBack];
            m_pExercise->Commit();
            
            commitStatus=CommitStatusAuto;
        }
	}
}

- (void)Commit
{
    [self saveQuestion];
    
    CMCardViewController *cardControl = [[CMCardViewController alloc] init];
    cardControl.title = I(@"答题卡");
    [cardControl setHandler:m_pExercise questionType:m_model questionId:[NSString stringWithUTF8String:m_surveyid]];
    
    if ([m_model isEqualToString:@"exam"])
    {
        [cardControl setPassTime:nDuration*60-(self.examDuration-self.timePast)];
    }

    [self.navigationController pushViewController:cardControl animated:YES];
    CMRELEASE(cardControl);
    return;
}


-(void)hideKeyboard
{
    [self.view removeGestureRecognizer:textViewGesture];
    
    [answerView resignFirstResponder];
}


- (void)textViewDidEndEditing:(UITextView *)textView
{
	TQuestionItem items;
	if(m_pExercise && m_pExercise->GetCurItem(items))
	{
		if(items.nType == TQuestionType::EText)
		{
			m_pExercise->SetAnswer([answerView.text UTF8String]);
		}
	}
    [self hideKeyboard];

    
}

- (void)textViewDidBeginEditing:(UITextView *)textView
{
    UITapGestureRecognizer *gesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(hideKeyboard)];
    gesture.numberOfTapsRequired = 1;
    textViewGesture=gesture;
    [self.view addGestureRecognizer:gesture];
    CMRELEASE(gesture);
}

- (void)textViewDidChange:(UITextView *)textView
{
    [self remindWordLabel:textView.text];
}
- (void)remindWordLabel:(NSString *)string
{
    input_words_num = [string length];
   // NSAutoreleasePool *pool = [[NSAutoreleasePool alloc]init];
    if (input_words_num <= kTextMaxLength) {
        NSUInteger Remaining_words = kTextMaxLength - input_words_num;
        words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
        isBeyond = NO;
        words_Num.text = [NSString stringWithFormat:I(@"还能输入%d个字"),Remaining_words];
    }
    else{
        NSUInteger Beyond_words = input_words_num - kTextMaxLength;
        words_Num.textColor = [UIColor redColor];
        isBeyond = YES;
        words_Num.text = [NSString stringWithFormat:I(@"超出%d个字"),Beyond_words];
    }
    //[pool drain];
}


- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
	// Any new character added is passed in as the "text" parameter
    if ([text isEqualToString:@"\n"]) {
		// Be sure to test for equality using the "isEqualToString" message
        [textView endEditing:YES];
		
		// Return FALSE so that the final '\n' character doesn't get added
        return NO;
    }
	
	// For any other character return TRUE so that the text gets added to the view
    return YES;
}
  
-(void)OpenSurvey:(NSString*)model surveyid:(const char*)surveyid oper:(NSString*)oper
{
	//practice,wrong,exam
	m_model = model;
    
    
    utf8ncpy(m_surveyid, surveyid, 63);


    //view or start
	m_oper = oper;
}

-(void)UpdateView
{
    if(m_pExercise->GetItemCount()<=0)
    {
      //  [tool ShowAlert:I(@"暂无题目信息")];
        isDataReady=NO;
        
    }else
        isDataReady=YES;
	toolbar.hidden = NO;
	self.navigationItem.rightBarButtonItem.enabled = YES;
	TQuestionItem items;
	if(m_pExercise && m_pExercise->GetCurItem(items))
	{
		if(items.nType == TQuestionType::EText)			
			[TableViewList setAllowsSelection: NO];
		else
			[TableViewList setAllowsSelection: YES];
	}
	
	int curindex = m_pExercise->GetCurIndex();
	int itemcount = m_pExercise->GetItemCount();
    
	
	if (itemcount >=1 )
    {
		if(curindex == itemcount-1)
		{
			[nextbtn setTitle:I(@"下一题") forState:UIControlStateNormal];
		}
		
		if ([m_model isEqualToString:@"practice"]) 
		{
            //错题 操作为查看答案
			[knowbtn setTitle:I(@"查看答案") forState: UIControlStateNormal];
			[knowbtn addTarget:self action:@selector(btnanser) forControlEvents:UIControlEventTouchUpInside];
			[knowbtn setImage:[UIImage imageNamed:@"answer_n"] forState:UIControlStateNormal];
			[knowbtn setImage:[UIImage imageNamed:@"answer_p"] forState:UIControlStateHighlighted];
            knowbtn.hidden=items.isChecked;
		}
        else if ([m_model isEqualToString:@"wrong"])
		{
            knowbtn.hidden=NO;
            hit = NO;
            if (items.isChecked) {
                
                //判断该题 当前状态（是否在错题库）
                if (items.isWrong) {
                    [knowbtn setTitle:I(@"移除错题")// @"我懂了"
                             forState:UIControlStateNormal];
                    [knowbtn addTarget:self action:@selector(btnknow) forControlEvents:UIControlEventTouchUpInside];
                    [knowbtn setImage:[UIImage imageNamed:@"know_n"] forState:UIControlStateNormal];
                    [knowbtn setImage:[UIImage imageNamed:@"know_p"] forState:UIControlStateHighlighted];
                }
                else{
                    [knowbtn setTitle:I(@"加入错题")//@"加入错题库"
                             forState:UIControlStateNormal];
                    [knowbtn addTarget:self action:@selector(addWrong) forControlEvents:UIControlEventTouchUpInside];
                    [knowbtn setImage:[UIImage imageNamed:@"unknow_n"] forState:UIControlStateNormal];
                    [knowbtn setImage:[UIImage imageNamed:@"unknow_p"] forState:UIControlStateHighlighted];
                }
                
            }
            else{
                [knowbtn setTitle:I(@"查看答案") forState: UIControlStateNormal];
                [knowbtn addTarget:self action:@selector(btnanser) forControlEvents:UIControlEventTouchUpInside];
                [knowbtn setImage:[UIImage imageNamed:@"answer_n"] forState:UIControlStateNormal];
                [knowbtn setImage:[UIImage imageNamed:@"answer_p"] forState:UIControlStateHighlighted];
            }
        }
    }
    else if ([m_model isEqualToString:@"exam"])
    {
        if ([m_oper isEqualToString:@"start"])
        {
            hit = FALSE;
        }
        else if ([m_oper isEqualToString:@"view"])
        {
            hit = TRUE;
        }
    }
		
    //若显示了答案，则继续显示
//    if([m_model isEqualToString:@"practice"])
//    {
//        if([self.hitDict objectForKey:[NSString stringWithFormat:@"%d",curindex]]==nil)
//            [self.hitDict setObject:[NSNumber numberWithBool:NO] forKey:[NSString stringWithFormat:@"%d",curindex]];
//        else
//            hit=[[self.hitDict objectForKey:[NSString stringWithFormat:@"%d",curindex]] boolValue];
//    }
	
    TableViewList.contentOffset = CGPointMake(0, 0);       //uitableview
	[TableViewList reloadData];
}

- (void)UpdateMultipleView{
    if(m_pExercise->GetItemCount()<=0)
    {
        [tool ShowAlert:I(@"暂无题目信息")];
        isDataReady=NO;
        
    }else
        isDataReady=YES;
	toolbar.hidden = NO;
	self.navigationItem.rightBarButtonItem.enabled = YES;
	TQuestionItem items;
	if(m_pExercise && m_pExercise->GetCurItem(items))
	{
        [TableViewList setAllowsSelection: YES];
	}
	
	int curindex = m_pExercise->GetCurIndex();
	int itemcount = m_pExercise->GetItemCount();
    
	if (itemcount >=1 )
    {
		if(curindex == itemcount-1)
		{
			[nextbtn setTitle:I(@"下一题") forState:UIControlStateNormal];
		}
		
        if ([m_model isEqualToString:@"practice"])
		{
            //错题 操作为查看答案
			[knowbtn setTitle:I(@"查看答案") forState: UIControlStateNormal];
			[knowbtn addTarget:self action:@selector(btnanser) forControlEvents:UIControlEventTouchUpInside];
			[knowbtn setImage:[UIImage imageNamed:@"answer_n"] forState:UIControlStateNormal];
			[knowbtn setImage:[UIImage imageNamed:@"answer_p"] forState:UIControlStateHighlighted];
            knowbtn.hidden=items.isChecked;
		}
        else if ([m_model isEqualToString:@"wrong"])
		{
            knowbtn.hidden=NO;
            hit = NO;
            if (items.isChecked) {
                if (items.isWrong) {
                    [knowbtn setTitle:I(@"移除错题")// @"我懂了"
                             forState:UIControlStateNormal];
                    [knowbtn addTarget:self action:@selector(btnknow) forControlEvents:UIControlEventTouchUpInside];
                    [knowbtn setImage:[UIImage imageNamed:@"know_n"] forState:UIControlStateNormal];
                    [knowbtn setImage:[UIImage imageNamed:@"know_p"] forState:UIControlStateHighlighted];
                }
                else{
                    [knowbtn setTitle:I(@"加入错题")//@"加入错题库"
                             forState:UIControlStateNormal];
                    [knowbtn addTarget:self action:@selector(addWrong) forControlEvents:UIControlEventTouchUpInside];
                    [knowbtn setImage:[UIImage imageNamed:@"unknow_n"] forState:UIControlStateNormal];
                    [knowbtn setImage:[UIImage imageNamed:@"unknow_p"] forState:UIControlStateHighlighted];
                }

            }
            else{
                [knowbtn setTitle:I(@"查看答案") forState: UIControlStateNormal];
                [knowbtn addTarget:self action:@selector(btnanser) forControlEvents:UIControlEventTouchUpInside];
                [knowbtn setImage:[UIImage imageNamed:@"answer_n"] forState:UIControlStateNormal];
                [knowbtn setImage:[UIImage imageNamed:@"answer_p"] forState:UIControlStateHighlighted];
            }
        }
    }
    
	[TableViewList reloadData];
}


// the table's selection has changed, switch to that item's UIViewController
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	TQuestionItem items;
	if(m_pExercise && m_pExercise->GetCurItem(items))
	{
        if (!items.isChecked || [m_model isEqualToString:@"exam"]) {
		if(items.nType != TQuestionType::EText)
		{
			TOption item;
			if(m_pExercise && m_pExercise->GetItemOption(indexPath.row, item))
			{		
				m_pExercise->SetAnswer(indexPath.row, !item.bCheck);

				if(items.nType == TQuestionType::ESingle )//|| items.nType == TQuestionType::EYesNo)
				{	
					if([m_model isEqualToString:@"practice"] || ([m_model isEqualToString:@"wrong"] && [m_oper isEqualToString:@"start"]))
					{
						[self btnanser];
						return;
					}
                    
                    if([m_model isEqualToString:@"exam"]&&[m_oper isEqualToString:@"start"])
                    {
                        [self nextQ];//若为测验，则直接跳到下一题
                        
                    }
                    
				}
             
				[TableViewList reloadData];
			}
		}
        }
	}
    [tableView deselectRowAtIndexPath:indexPath animated:NO];

}

#pragma mark UITableView data source methods

// tell our table how many sections or groups it will have (always 1(our case)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 2;
}

// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	TQuestionItem items;
	if(m_pExercise && m_pExercise->GetCurItem(items))
	{
		if (section == 0) {
			if(items.nType == TQuestionType::EText)
				return 1;
			else
            {
				return m_pExercise->GetItemOptionCount();
            }
			
		}else {
			return 0;
			
		}
		
	}
	else
		return 1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
	if(section == 0)
	{
		TQuestionItem items;
		if(m_pExercise && m_pExercise->GetCurItem(items))
		{
			NSString* str = I(@"[单选题]");//用于计算高度
			if(strlen(items.GetQuestionItemCategory()) > 0)
				str = [str stringByAppendingString:[[[NSString stringWithUTF8String:items.GetQuestionItemCategory()] stringByAppendingString:@"\n"] stringByAppendingString:[NSString stringWithUTF8String:items.GetQuestionItemQuestion()]]];
			else
				str = [str stringByAppendingString:[NSString stringWithUTF8String:items.GetQuestionItemQuestion()]];
			UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
			CGSize constraintSize = CGSizeMake(TableViewList.frame.size.width-20, MAXFLOAT);
			CGSize labelSize = [str sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
			return labelSize.height + 20;			
		}
		return 10.0;
	}
    else
    {
        
		TQuestionItem items;
		if(m_pExercise && m_pExercise->GetCurItem(items))
		{
            NSString *strAnswer = [NSString stringWithFormat:I(@"正确答案：%@"),[NSString stringWithUTF8String:m_pExercise->GetRightAnswer()]];
            CGSize answerSize = [strAnswer sizeWithFont:[UIFont boldSystemFontOfSize:13] constrainedToSize:CGSizeMake(300, MAXFLOAT) lineBreakMode:[tool TextBreakMode:TEXTBREAKMODEWORD]];
            NSString *strDesc = nil;
            if(strlen(items.GetQuestionItemDescription()) > 0)
            {
                strDesc = [NSString stringWithFormat:@"%@%@", I(@"题目解析："),[NSString stringWithUTF8String:items.GetQuestionItemDescription()]];

            }
            else
                strDesc = [NSString stringWithFormat:@"%@%@", I(@"题目解析："),I(@"暂无")];
            CGSize descSize = [strDesc sizeWithFont:[UIFont boldSystemFontOfSize:13] constrainedToSize:CGSizeMake(300, MAXFLOAT) lineBreakMode:[tool TextBreakMode:TEXTBREAKMODEWORD]];
            return answerSize.height + descSize.height+40;
        }
        return  10;
    }
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
	// create the parent view that will hold header Label
	UIView* customView = nil;
	customView.backgroundColor=[UIColor clearColor];
	
	CGRect f = TableViewList.bounds;
    UILabel * headerLabel = nil;

	if (section == 0) {
		customView = [[UIView alloc] initWithFrame:CGRectMake(10.0, 0.0, f.size.width-20, 150.0)];
		// create the button object
        headerLabel = [[UILabel alloc] initWithFrame:CGRectZero];
        
		headerLabel.opaque = NO;
		headerLabel.textColor = UIColorRGB(0x2e2e2e);
		headerLabel.highlightedTextColor = [UIColor whiteColor];
		headerLabel.font = [UIFont systemFontOfSize:15];
		headerLabel.lineBreakMode = UILineBreakModeCharacterWrap;
		headerLabel.numberOfLines = 0;
        headerLabel.backgroundColor = [UIColor clearColor];
		
		TQuestionItem items;
		float Labelheight = 10.0;
		if(m_pExercise && m_pExercise->GetCurItem(items))
		{
            NSString *headerStr;
            if (items.nType == TQuestionType::ESingle)
            {
                headerStr = I(@"[单选]");
            }
            else if (items.nType == TQuestionType::EMultiple)
            {
                headerStr = I(@"[多选]");
            }
            else if (items.nType == TQuestionType::EText)
            {
                headerStr = I(@"[填空]");
            }
			if(strlen(items.GetQuestionItemCategory()) > 0)
			{
                headerStr = [headerStr stringByAppendingString:[[[NSString stringWithUTF8String:items.GetQuestionItemCategory()] stringByAppendingString:@"\n"] stringByAppendingString:[NSString stringWithUTF8String:items.GetQuestionItemQuestion()]]];
//				headerLabel.text = [[[NSString stringWithUTF8String:items.GetQuestionItemCategory()] stringByAppendingString:@"\n"] stringByAppendingString:[NSString stringWithUTF8String:items.GetQuestionItemQuestion()]];
				//headerLabel.numberOfLines = 2;
			}
			else
			{
                headerStr = [headerStr stringByAppendingString:[NSString stringWithUTF8String:items.GetQuestionItemQuestion()]];
//				headerLabel.text = [NSString stringWithUTF8String:items.GetQuestionItemQuestion()];
				//headerLabel.numberOfLines = 2;
			}
            NSMutableAttributedString *attrbutedString = [[NSMutableAttributedString alloc]initWithString:headerStr];
            [attrbutedString addAttribute:NSForegroundColorAttributeName value:kColorButtonTitle range:NSMakeRange(0,4)];
            headerLabel.attributedText = attrbutedString;
            
			UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
			CGSize constraintSize = CGSizeMake(f.size.width-20, MAXFLOAT);
			CGSize labelSize = [headerLabel.text sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
			Labelheight = labelSize.height + 10;
            
            CGRect frame = CGRectMake(10.0, 10.0, f.size.width-20, Labelheight);
            headerLabel.frame = frame;
            customView.frame = frame;
            [customView addSubview:headerLabel];
            
            if(items.nType != TQuestionType::EText)
            {
                UIView* sepview = [[UIView alloc] init];
                sepview.backgroundColor = kTextColorNormal;
                sepview.frame = CGRectMake(0, frame.origin.y+frame.size.height, f.size.width, 1);
                [customView addSubview:sepview];
                CMRELEASE(sepview);
            }
		}
        
        CMRELEASE(headerLabel)
	}
    else if (section == 1)
	{
		UIImageView * imageView;
		UILabel * lblDesc;
		UILabel* lbStatus;
		
		customView = [[UIView alloc] initWithFrame:CGRectMake(10.0, 10.0, f.size.width-20, 150.0)] ;  //答案部分底层
       // [customView setBackgroundColor:[UIColor clearColor]];
         [customView setBackgroundColor:[UIColor clearColor]];

		
		if (!hit) {
            [customView setAlpha:0];
			//customView.alpha = 0;
		}else {
            [customView setAlpha:1];

			//customView.alpha = 1;
		}
		
		// create the button object
		headerLabel = [[UILabel alloc] init];
		
		imageView = [[UIImageView alloc] init];
		
		lblDesc = [[UILabel alloc] initWithFrame:CGRectMake(10, 30, f.size.width-20, 15)];
		lblDesc.backgroundColor = [UIColor clearColor];
		lblDesc.numberOfLines = 0;
        lblDesc.lineBreakMode = [tool TextBreakMode:TEXTBREAKMODEWORD];
		
		lblDesc.textColor = kTextColorDark;
		lblDesc.font = [UIFont boldSystemFontOfSize:13];
		
		headerLabel.backgroundColor = [UIColor clearColor];
		headerLabel.textColor = kTextColorDark;
		headerLabel.font = [UIFont boldSystemFontOfSize:13];
		headerLabel.frame = CGRectMake(10.0, 10.0, f.size.width-20, 15);
		headerLabel.numberOfLines = 0;
        headerLabel.lineBreakMode = [tool TextBreakMode:TEXTBREAKMODEWORD];
        
		///
		lbStatus = [[UILabel alloc] initWithFrame:CGRectZero];
		lbStatus.backgroundColor = [UIColor clearColor];
		lbStatus.textColor = kTextColorDark;
		lbStatus.font = [UIFont boldSystemFontOfSize:13];
		TQuestionItem items;
		
		if(m_pExercise && m_pExercise->GetCurItem(items))
		{
			headerLabel.text = [NSString stringWithFormat:I(@"正确答案：%@"),[NSString stringWithUTF8String:m_pExercise->GetRightAnswer()]];
            
            if (![m_model isEqualToString:@"exam"])
            {
                hit = items.isChecked;
                if (!hit) {
                    [customView setAlpha:0];
                }else {
                    [customView setAlpha:1];
                }
            }
            
			if(items.nType != TQuestionType::EText) {
				UIImage * imageType;
                
                NSString * str =@"";
                
                if([m_model isEqualToString:@"exam"]&&[m_oper isEqualToString:@"view"])
                {
                    if(m_pExercise->isMyAnswerRight())
                    {
                        imageType = [UIImage imageNamed:@"examright"];
                        str = I(@"答对了");
                        
                        
                    }
                    else
                    {
                        imageType = [UIImage imageNamed:@"examwrong"];
                        str = I(@"答错了");

                    }
                }else
                {
                    if(m_pExercise->isOptionAnswerRight())
                    {
                        imageType = [UIImage imageNamed:@"examright"];
                        str = I(@"答对了");

                    }
                    else
                    {
                        imageType = [UIImage imageNamed:@"examwrong"];
                        str = I(@"答错了");

                    }
                }
                
				imageView.image = imageType;
                imageView.frame = CGRectMake(254, 6, imageType.size.width, imageType.size.height);
                
                UILabel* lbl = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, imageView.frame.size.width, imageView.frame.size.height)];
                
                lbl.text = str;
                
                [lbl setBackgroundColor:[UIColor clearColor]];
                
                [imageView addSubview:lbl];
                
                lbl.font = [UIFont systemFontOfSize:13];
                
                lbl.textColor = [UIColor whiteColor];
                
                lbl.textAlignment= NSTextAlignmentRight;
                
            }
            else
            {
                UIImage * imageType;
                
                NSString * str =@"";
                if(items.nType == TQuestionType::EText&&[m_model isEqualToString:@"exam"]&&[m_oper isEqualToString:@"view"])
                {
                    if(strcmp(items.GetQuestionItemMyAnswer(), m_pExercise->GetRightAnswer())==0)
                    {
                        imageType = [UIImage imageNamed:@"examright"];
                        str = I(@"答对了");

                    }
                    else
                    {
                        imageType = [UIImage imageNamed:@"examwrong"];
                        str = I(@"答错了");

                    }
                    
                    imageView.image = imageType;
                    imageView.frame = CGRectMake(254, 6, imageType.size.width, imageType.size.height);
                    
                    UILabel* lbl = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, imageView.frame.size.width, imageView.frame.size.height)];
                    
                    lbl.text = str;
                    
                    [lbl setBackgroundColor:[UIColor clearColor]];
                    
                    [imageView addSubview:lbl];
                    
                    lbl.font = [UIFont systemFontOfSize:13];
                    
                    lbl.textColor = [UIColor whiteColor];

                    
                    lbl.textAlignment= NSTextAlignmentRight;
            
                }
            }
            CGSize answerSize = [headerLabel.text sizeWithFont:headerLabel.font constrainedToSize:CGSizeMake(300, MAXFLOAT) lineBreakMode:headerLabel.lineBreakMode];
            headerLabel.frame = CGRectMake(10, 32, answerSize.width, answerSize.height);
            
			if(strlen(items.GetQuestionItemDescription()) > 0)
				lblDesc.text = [NSString stringWithFormat:@"%@%@",I(@"题目解析："),[NSString stringWithUTF8String:items.GetQuestionItemDescription()]];
			else
				lblDesc.text = [NSString stringWithFormat:@"%@%@",I(@"题目解析："),I(@"暂无")];
            
            CGSize descSize = [lblDesc.text sizeWithFont:lblDesc.font constrainedToSize:CGSizeMake(300, MAXFLOAT) lineBreakMode:lblDesc.lineBreakMode];
            lblDesc.frame = CGRectMake(10, headerLabel.frame.origin.y+headerLabel.frame.size.height + 6, 300, descSize.height);
		}
		
		[customView addSubview:headerLabel];
		[customView addSubview:imageView];
		[customView addSubview:lbStatus];
		[customView addSubview:lblDesc];	
        CMRELEASE(headerLabel);
        CMRELEASE(imageView);
        CMRELEASE(lbStatus);
        CMRELEASE(lblDesc);
	}
    
# if ! __has_feature(objc_arc)
    return [customView autorelease];
# else
    return customView;
# endif
}

// to determine specific row height for each cell, override this.
// In this example, each row is determined by its subviews that are embedded.
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	TQuestionItem items;
	if(m_pExercise && m_pExercise->GetCurItem(items))
	{
		if(items.nType == TQuestionType::EText)
		{
			return 140.0;
		}
        else
        {
            TOption item;
            if(m_pExercise && m_pExercise->GetItemOption(indexPath.row, item))
            {
                UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
                CGSize constraintSize = CGSizeMake(TableViewList.frame.size.width-50, MAXFLOAT);
                CGSize labelSize = [[NSString stringWithUTF8String:item.GetOptionItemText()] sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
                return labelSize.height + 40;
            }
        }
	}
    
    return 0;
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	TQuestionItem items;
    
	if(m_pExercise && m_pExercise->GetCurItem(items))
	{
		if(items.nType == TQuestionType::EText)	//题目为填空题
		{
# if ! __has_feature(objc_arc)
            UITableViewCell *cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifierEdit] autorelease];
# else
            UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifierEdit];
# endif
            
            cell.accessoryType = UITableViewCellAccessoryNone;
            cell.selectionStyle = UITableViewCellSelectionStyleNone;

            float cellWidth = 0;
            
            //7.0下 默认cell是白色背景 且是占满整个屏幕宽度的
            if (__iOS7)
            {
                cellWidth = UI_IOS_WINDOW_WIDTH;
            }
            else
            {
                cellWidth = UI_IOS_WINDOW_WIDTH - 20;
                
                UIView *bgView = [[UIView alloc] init];
                bgView.frame = CGRectMake(-1, -1, UI_IOS_WINDOW_WIDTH - 20 + 2, 140 + 2);
                bgView.backgroundColor = [UIColor whiteColor];
                bgView.layer.cornerRadius = 2.0;
                bgView.layer.borderWidth = 1.0;
                bgView.layer.borderColor = [UIColor colorWithRed:195/255.0 green:195/255.0 blue:195/255.0 alpha:1.0].CGColor;
                bgView.layer.shadowColor   = [UIColor colorWithRed:195/255.0 green:195/255.0 blue:195/255.0 alpha:1.0].CGColor;
                [cell.contentView addSubview:bgView];
                CMRELEASE(bgView);
            }
            
            answerView = [[UITextView alloc] initWithFrame:CGRectMake(0, 5,cellWidth,110)];
            answerView.textColor = [UIColor blackColor];
            answerView.font = [UIFont systemFontOfSize:12.0];
            answerView.text=@"";
            answerView.backgroundColor = [UIColor clearColor];
            answerView.autocorrectionType = UITextAutocorrectionTypeNo;
            answerView.keyboardType = UIKeyboardTypeDefault;
            answerView.returnKeyType = UIReturnKeyDone;
            answerView.layer.cornerRadius = 2.0;
            answerView.delegate = self;
            
            if([m_model isEqualToString:@"exam"] && [m_oper isEqualToString:@"view"])
            {
                [answerView setEditable:NO];
            }
            [cell.contentView addSubview:answerView];
            
            
            words_Num = [[UILabel alloc]initWithFrame:CGRectMake(0, 120, cellWidth-5, 20)];
            words_Num.backgroundColor = [UIColor clearColor];
            words_Num.font = [UIFont systemFontOfSize:12.0];
            words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
            words_Num.text = [NSString stringWithFormat:I(@"还能输入%d个字"),100];
            words_Num.textAlignment = UITextAlignmentRight;
            [cell.contentView addSubview:words_Num];
            
            if([m_oper isEqualToString:@"view"] &&[m_model isEqualToString:@"exam"])
                [answerView setText:[NSString stringWithUTF8String:items.GetQuestionItemMyAnswer()]];
            else
                [answerView setText:[NSString stringWithUTF8String:items.GetQuestionItemAnswer()]];
            [answerView setBackgroundColor:[UIColor clearColor]];
            
            if([m_model isEqualToString:@"practice"] && items.isChecked)
            {
                answerView.editable = NO;
            }
            
            [self remindWordLabel:answerView.text];
            
            return cell;
        }
        else                                      //题目为选择题
        {
# if ! __has_feature(objc_arc)
            UITableViewCell *cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifierCheck] autorelease];
# else
            UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifierCheck];
# endif
            
            cell.accessoryType = UITableViewCellAccessoryNone;
            cell.selectionStyle = UITableViewCellSelectionStyleNone;
            
            TOption item;
			if(m_pExercise && m_pExercise->GetItemOption(indexPath.row, item))
			{
				//start view
				UILabel*lbtxt = [[UILabel alloc] init];
				lbtxt.textColor = [UIColor blackColor];
				lbtxt.highlightedTextColor = [UIColor blackColor];
				lbtxt.font = [UIFont systemFontOfSize:15.0];
				lbtxt.numberOfLines = 0;
				lbtxt.text = [NSString stringWithUTF8String:item.GetOptionItemText()];
                [lbtxt setBackgroundColor:[UIColor clearColor]];
                
                BOOL isCheck;
                
				if ([m_oper isEqualToString:@"view"])
				{
                    isCheck = item.bMyAnswer;
				}
				else
                {
                    isCheck = item.bCheck;
                }
                
                UIImageView *imageView = [[UIImageView alloc] init];
                if (isCheck) //选中
                {
                    if(items.nType == TQuestionType::ESingle)// || items.nType == TQuestionType::EYesNo)      //单选或判断
                        imageView.image = [UIImage imageNamed:@"examradio"];
                    else
                        imageView.image = [UIImage imageNamed:@"examcheck"];
                }
                else
                {
                    if(items.nType == TQuestionType::ESingle )// || items.nType == TQuestionType::EYesNo)
                        imageView.image = [UIImage imageNamed:@"examunradio"];
                    else
                        imageView.image = [UIImage imageNamed:@"examuncheck"];
                }
                
                if (![m_model isEqualToString:@"exam"])
                {
                    hit = items.isChecked;
                }
                
                if(hit && item.bRightAnswer)
                {
                    lbtxt.textColor=[UIColor colorWithRed:27.0f/255.0f green:109.0f/255.0f blue:179.0f/255.0f alpha:1];
                }
				
				UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
				CGSize constraintSize = CGSizeMake(TableViewList.frame.size.width-50, MAXFLOAT);
				CGSize labelSize = [lbtxt.text sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
				int hg = labelSize.height+40;
                imageView.frame = CGRectMake(10, (hg-24)/2, 24, 24);
				lbtxt.frame = CGRectMake(40, 20, TableViewList.frame.size.width-50, labelSize.height);
				UIImageView* lv = [[UIImageView alloc] init];
				lv.image = [UIImage imageNamed:@"examsep"];
				lv.frame = CGRectMake(10, hg-1, TableViewList.frame.size.width-20, 1);
				[cell.contentView addSubview:imageView];
				[cell.contentView addSubview:lbtxt];
				[cell.contentView addSubview:lv];             //lv是个uiimageview
                CMRELEASE(lv);
                CMRELEASE(lbtxt);
                CMRELEASE(imageView);
            }
            
            return cell;
        }
    }
# if ! __has_feature(objc_arc)
    UITableViewCell *cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"nilcell"] autorelease];
# else
    UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"nilcell"];
# endif
    return cell;
}

//重写返回按钮按下事件 用于在练习返回时刷新显示
- (void)gotoBack
{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud removeObjectForKey:@"exam"];
    [ud setObject:@"0" forKey:kUDOpenPush];
    //保存答题情况
    
    if ([m_model isEqualToString:@"exam"])
    {
        if ([m_oper isEqualToString:@"start"])
        {
            if((int)(self.examDuration-self.timePast)>=0&&self.examDuration!=-1)
            {
                int examtime = self.examDuration - self.timePast;
                if (examtime <= 1 && examtime > 0) {
                    return;
                }
            }
        }
    }
    [self saveQuestion];
    
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)gotoIndex:(id)sender
{
    if([m_model isEqualToString:@"practice"])
    {
        [self.hitDict removeAllObjects];
        hit = FALSE;
        
    }
    
    int nIndex = [[[sender userInfo] objectForKey:@"index"] intValue];
    m_pExercise->SetCurIndex(nIndex);
    [self UpdateView];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:YES];
    [self.examTimer invalidate];
    self.examTimer=nil;
}

- (void)saveQuestion
{
    if ([m_model isEqualToString:@"exam"])
    {
        if(!finished&&m_pExercise)
            m_pExercise->SaveStatus();
        
        if ([m_oper isEqualToString:@"start"])
        {
            if((int)(self.examDuration-self.timePast)>=0&&self.examDuration!=-1)
            {
                exam->SetDuration((int)(self.examDuration-self.timePast));
                [[NSNotificationCenter defaultCenter] postNotificationName:@"examback" object:nil userInfo:[NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:@"%d",self.examDuration-self.timePast], @"remaintime",[NSString stringWithFormat:@"%d",m_pExercise->GetCurIndex()],@"index",nil]];
                nExamRemainTime = self.examDuration - self.timePast;
            }
        }
    }
    else if ([m_model isEqualToString:@"practice"])
    {
        if (m_pExercise->GetItemCount() <=0 || !m_pExercise) {
            return;
        }
        //做到某一题返回时 判断当前题目是否做对
        if (m_pExercise->isOptionAnswerRight() && [self IsChecked])
        {
            m_pExercise->setRight();
        }
        else
        {
            TQuestionItem items;
            if(m_pExercise && m_pExercise->GetCurItem(items))
            {
                if(items.nType != TQuestionType::EText && [self IsChecked])
                    m_pExercise->SetWrong(YES);

            }
        }
        
        //多选题 下一题时,查看答案显示
        if ([self IsChecked]) {
            m_pExercise->SetExerciseAnswer(TRUE);
        }
        
        if(!finished&&m_pExercise)
            m_pExercise->SaveExerciseStatus();
        
        [[NSNotificationCenter defaultCenter] postNotificationName:@"continuepractice" object:nil];
        [[NSNotificationCenter defaultCenter] postNotificationName:@"refreshwrongcount" object:nil];
    }
    else if ([m_model isEqualToString:@"wrong"])
    {
        if(!finished&&m_pExercise)
            m_pExercise->SaveWrongStatus();
        
        [[NSNotificationCenter defaultCenter] postNotificationName:@"refreshwrongcount" object:nil];
    }
}


- (void)pauseExam:(id)sender
{
    nExamRemainTime = self.examDuration - self.timePast;
    NSLog(@"nExamRemainTime = %d",nExamRemainTime);
    NSLog(@"examDuration = %d",examDuration);
    NSLog(@"timePast = %d",timePast);
    [self.examTimer invalidate];
    //self.examTimer = nil;
}


- (void)continueExam:(id)sender
{
//    self.timePast = 0;
    [self setDuration];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];

    
    if (isDataReady)
    {
        if ([m_model isEqualToString:@"exam"])
        {
            exam->SetUserData(BridgeObjectToC(self));
            exam->SetListener(m_pUpdateDataListener,m_pSimpleResultListener);
        }
//        self.timePast = 0;
        [self setDuration];
    }
    
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@"exam" forKey:@"exam"];
    
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    
    //是否已请求到数据
    isDataReady = NO;

# if ! __has_feature(objc_arc)

    self.hitDict = [[[NSMutableDictionary alloc]init] autorelease];
#else
    
    self.hitDict = [[NSMutableDictionary alloc]init] ;

#endif
    //初始值:未懂
    m_bKnow = NO;
    
	hit = FALSE;

	NSString *stitle = nil;
    
	if (m_type) 
		stitle = I(@"交卷"); 
	else
		stitle =  I(@"答题卡");
    
	//右上角按钮
	UIView* rightview = [[UIView alloc] init];
	rightview.frame = CGRectMake(0, 0, 60, 44);

	UIButton *commitBtn = [UIButton buttonWithType:UIButtonTypeCustom];
	commitBtn.frame = CGRectMake(3, 0, 55, 44);
	[commitBtn setTitle:stitle forState:UIControlStateNormal];
	[commitBtn setTitleColor:kColorButtonTitle forState:UIControlStateNormal];
	[commitBtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
	[commitBtn addTarget:self action:@selector(Commit) forControlEvents:UIControlEventTouchUpInside];
    
	UIImageView* vsep = [[UIImageView alloc] init];
	vsep.image = [UIImage imageNamed:@"navsep"];
	vsep.frame = CGRectMake(0, 0, 2, 44);
    
    if (__iOS7)
    {
        if(![m_oper isEqualToString:@"view"])//查看测验的时候不显示提交
        {
            commitBtn.frame = CGRectMake(0, 0, 55, 45);
            [rightview addSubview:commitBtn];
        }
    }
    else
    {
        if(![m_oper isEqualToString:@"view"])//查看测验的时候不显示提交
        {
            [rightview addSubview:commitBtn];
            
            [rightview addSubview:vsep];
        }
    }
    CMRELEASE(vsep);
	UIBarButtonItem *rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:rightview];
    
    if (![m_model isEqualToString:@"wrong"])
    {
        self.navigationItem.rightBarButtonItem = rightBarButtonItem;
    }
    CMRELEASE(rightview);
    CMRELEASE(rightBarButtonItem);
	
	CGRect viewframe = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT - 64 - 44);
    
    if (__iOS7)
    {
        //viewframe = CGRectMake(0, -35, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT - 64 - 44 + 35);
    }
	TableViewList = [[UITableView alloc] initWithFrame:viewframe style:UITableViewStyleGrouped];
    UIView *bakgroundView=[[UIView alloc]initWithFrame:viewframe];
    [bakgroundView setBackgroundColor:[UIColor colorWithRed:247.0f/255.0f green:247.0f/255.0f blue:247.0f/255.0f alpha:1]];
    [TableViewList setBackgroundView:bakgroundView];
    CMRELEASE(bakgroundView);
    TableViewList.backgroundColor = [UIColor clearColor];
	TableViewList.separatorColor = [UIColor clearColor];
	[TableViewList setDelegate:self];
	[TableViewList setDataSource:self];
	[self.view addSubview:TableViewList];
	
    UIImageView * toolbarbak= [[UIImageView alloc]initWithFrame:CGRectMake(0, -3.5, UI_IOS_WINDOW_WIDTH, 51.5
                                                                           )];
    [toolbarbak setImage:[UIImage imageNamed:@"bottombk"]];
    
	toolbar = [[UIToolbar alloc] initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-44-48-20, UI_IOS_WINDOW_WIDTH, 48)];
	
    
    
    [toolbar setContentMode:UIViewContentModeScaleAspectFill];
    if (!__iOS7)
    {
        [toolbar addSubview:toolbarbak];
    }
    CMRELEASE(toolbarbak);

	[self.view addSubview:toolbar];
	
	
	prebtn = [[ComplexButton alloc] init];
	prebtn.frame = CGRectMake(0, 0, 80, 44);
	[prebtn setTitle:I(@"上一题") forState:UIControlStateNormal];
	[prebtn setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
	[prebtn setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateHighlighted];
	[prebtn setImage:[UIImage imageNamed:@"pre_n"] forState:UIControlStateNormal];
	[prebtn setImage:[UIImage imageNamed:@"pre_p"] forState:UIControlStateHighlighted];
	[prebtn addTarget:self action:@selector(prevQ) forControlEvents:UIControlEventTouchUpInside];

	UIBarButtonItem* prevBarItem = [[UIBarButtonItem alloc] initWithCustomView:prebtn];

	UIBarButtonItem* FlexibleBarItem1 = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:self action:nil];
	UIBarButtonItem* FlexibleBarItem2 = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:self action:nil];
	
	
	nextbtn = [[ComplexButton alloc] init];
	nextbtn.frame = CGRectMake(0, 0,100, 44);
	[nextbtn setTitle:I(@"下一题") forState:UIControlStateNormal];
	[nextbtn setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
	[nextbtn setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateHighlighted];
	[nextbtn setImage:[UIImage imageNamed:@"next_n"] forState:UIControlStateNormal];
	[nextbtn setImage:[UIImage imageNamed:@"next_p"] forState:UIControlStateHighlighted];
	[nextbtn addTarget:self action:@selector(nextQ) forControlEvents:UIControlEventTouchUpInside];
	
	UIBarButtonItem*nextBarItem = [[UIBarButtonItem alloc] initWithCustomView:nextbtn];
    
	//声明回调接口
	m_pUpdateDataListener=new CMExamInfoUpdateDataListener();
	m_pSimpleResultListener = new CMExamInfoSimpleResultListener();
    
    m_qUpdateDataListener=new  CMQuestionUpdateDataListener();
    m_qSimpleResultListener=new CMQuestionInfoSimpleResultListener();
    
    
	knowbtn = [[ComplexButton alloc] init];
	knowbtn.frame = CGRectMake(0, 0, 100, 44);
    [knowbtn setCenter:CGPointMake(UI_IOS_WINDOW_WIDTH/2+10, UI_IOS_WINDOW_HEIGHT/2)];
    
	[knowbtn setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
	[knowbtn setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateHighlighted];
	UIBarButtonItem* KnowBarItem = [[UIBarButtonItem alloc]initWithCustomView:knowbtn];
	KnowBarItem.style = UIBarButtonItemStyleBordered;
    
    
    [knowbtn setBounds:CGRectMake(knowbtn.bounds.origin.x-10, knowbtn.bounds.origin.y, 100, 44)];
    [nextbtn setBounds:CGRectMake(nextbtn.bounds.origin.x-10, nextbtn.bounds.origin.y, 100, 44)];
    
    
    [tool ShowActivityIndicator:self.view];
    
    
	//[prebtn setEnabled:NO];
    [prebtn setEnabled:YES];

	[nextbtn setEnabled:YES];
	toolbar.hidden = YES;
	self.navigationItem.rightBarButtonItem.enabled = NO;
	
	//TableViewList.userInteractionEnabled = YES;
    
	UISwipeGestureRecognizer *horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];  
	horizontal.direction = UISwipeGestureRecognizerDirectionLeft;  
	//[TableViewList addGestureRecognizer:horizontal];
    CMRELEASE(horizontal);
	
	horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];  
	horizontal.direction = UISwipeGestureRecognizerDirectionRight;  
	//[TableViewList addGestureRecognizer:horizontal];
    CMRELEASE(horizontal);
    
    UIView *coverView=[[UIView alloc]initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-44-20, 320, UI_IOS_WINDOW_HEIGHT-44-20-44)];
    [coverView setBackgroundColor:[UIColor clearColor]];
    
    if([m_oper isEqualToString:@"view"])
    {
        [self.view addSubview:coverView];
    }
    
    CMRELEASE(coverView);
    
    
//    if(![tool isFirstTimeToDisplay:NeedGuideViewExam])
//    {
//        ((MLPlayerAppDelegate*)[UIApplication sharedApplication].delegate).guideWindow.windowLevel=UIWindowLevelStatusBar+1;
//
//        [((MLPlayerAppDelegate*)[UIApplication sharedApplication].delegate).guideWindow addSubview:[tool generateGuideView:NeedGuideViewExam]];
//        [((MLPlayerAppDelegate*)[UIApplication sharedApplication].delegate).guideWindow makeKeyAndVisible];
//        
//    }
# if ! __has_feature(objc_arc)
    self.lbltimer=[[[UILabel alloc]initWithFrame:CGRectMake(UI_IOS_WINDOW_WIDTH/2-50, UI_IOS_WINDOW_HEIGHT-100, 80, 30)] autorelease];
#else
    self.lbltimer=[[UILabel alloc]initWithFrame:CGRectMake(UI_IOS_WINDOW_WIDTH/2-50, UI_IOS_WINDOW_HEIGHT-100, 80, 30)] ;

    
#endif
    [self.lbltimer setCenter:CGPointMake(UI_IOS_WINDOW_WIDTH/2+10, UI_IOS_WINDOW_HEIGHT-90)];
    [self.lbltimer setBackgroundColor:[UIColor clearColor]];
    [self.lbltimer setTextColor:[UIColor blueColor]];
    [self.lbltimer setTextColor:[UIColor colorWithRed:27.0f/255.0f green:109.0f/255.0f blue:179.0f/255.0f alpha:1]];
    [self.view addSubview:self.lbltimer];
    
    
    ////practice,wrong
	if ([m_model isEqualToString:@"practice"])
    {
		CMExercise*	exercise =new CMExercise();
		exercise->SetUserData(BridgeObjectToC(self));
        exercise->SetListener(m_pUpdateDataListener, nil);
        exercise->SetCurIndex(nCurIndex);
        exercise->SetCompleteNumber(nCompleteNum);
		m_pExercise = exercise;
        exercise->GetExerciseQuestion(m_surveyid);
        
		[toolbar setItems:[NSArray arrayWithObjects:prevBarItem,FlexibleBarItem1,KnowBarItem,FlexibleBarItem2,nextBarItem,nil]];
	}
    else if ([m_model isEqualToString:@"wrong"])
    {
		CMExercise*	exercise =new CMExercise();
		exercise =new CMExercise();
		exercise->SetUserData(BridgeObjectToC(self));
        exercise->SetListener(m_pUpdateDataListener, nil);
        m_pExercise = exercise;
        exercise->GetWrongQuestion(m_surveyid);
        exercise->SetCompleteNumber(nCompleteNum);
		      
        
		[toolbar setItems:[NSArray arrayWithObjects:prevBarItem,FlexibleBarItem1,KnowBarItem,FlexibleBarItem2,nextBarItem,nil]];
	}
    else if ([m_model isEqualToString:@"exam"])
    {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(pauseExam:)
                                                     name:@"ExamTimePause" object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(continueExam:)
                                                     name:@"ExamTimeContinue" object:nil];
        
		exam =new CMExam();
		exam->SetUserData(BridgeObjectToC(self));
        exam->SetListener(m_pUpdateDataListener,m_pSimpleResultListener);
		exam->SetCurIndex(nCurIndex);
        
		if ([m_oper isEqualToString:@"start"])
        {
			hit = FALSE;
			exam->StartExam(m_surveyid);
			[toolbar setItems:[NSArray arrayWithObjects:prevBarItem,FlexibleBarItem1,nextBarItem,nil]];
		}
        else if ([m_oper isEqualToString:@"view"])
        {
			hit = TRUE;
			exam->ViewExamQuestion(m_surveyid);
			[toolbar setItems:[NSArray arrayWithObjects:prevBarItem,FlexibleBarItem1,KnowBarItem,FlexibleBarItem2,nextBarItem,nil]];
		}
		m_pExercise = exam;
	}
	
    CMRELEASE(prevBarItem);
    CMRELEASE(FlexibleBarItem1);
    CMRELEASE(KnowBarItem);
    CMRELEASE(FlexibleBarItem2);
    CMRELEASE(nextBarItem);
    
     if ([m_model isEqualToString:@"wrong"])
     {
         [self UpdateView];
         [tool DisimissActivityIndicator];
     }
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(gotoIndex:) name:@"gotoindex" object:nil];
    
}
- (void)reportHoriziontalSwipe:(UISwipeGestureRecognizer *)tap
{
    if(!m_pExercise || m_pExercise->GetItemCount() <= 0)
		return;
	if(tap.direction  == UISwipeGestureRecognizerDirectionLeft)
	{
		[self nextQ];
	}
	else if(tap.direction == UISwipeGestureRecognizerDirectionRight)
	{
		[self prevQ];
	}
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    
    CMRELEASE(toolbar);
    CMRELEASE(prebtn);
    CMRELEASE(nextbtn);
    CMRELEASE(knowbtn);
    CMRELEASE(_hitDict);
    
    if(_examTimer!=nil )
    {
        [_examTimer invalidate];
        CMRELEASE(_examTimer);
        
    }

    CMRELEASE(_lbltimer);
	CMRELEASE(answerView);
	SAFEDELETE(m_pExercise);
	SAFEDELETE(m_pUpdateDataListener);
	SAFEDELETE(m_pSimpleResultListener);
    
    
    CMRELEASE(words_Num);
# if ! __has_feature(objc_arc)
	[super dealloc];
# endif

}


@end
//
//  CMIntrodocutionViewController.m
//  MLPlayer
//
//  Created by wmgwd on 13-11-6.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMIntrodocutionViewController.h"
#import "CMExamInfoControl.h"
#import "CMSurveyControl.h"
#import "CMExamRankViewController.h"
#import "CMWrongViewController.h"
#import "tool.h"
#import "CMLabel.h"
#import "CMBrowserHandler.h"

#define FONT_SIZE 14 //除标题及按钮外文字字体大小
#define EXAM_ANSWER_HEIGHT   45
#define EPSILON 0.0001

typedef NS_ENUM(NSUInteger, ExamState) {
    ExamStateContinue = 0, //继续考试
    ExamStateStart,        //开始考试
    ExamStateViewAnswer,   //查看答案与解析
    ExamStatePassed,       //考试已通过
    ExamStateFailed,       //考试次数已满
    ExamStateMarking,      //改卷中
};

@interface CMIntrodocutionViewController ()

@end

@implementation CMIntrodocutionViewController

@synthesize itemDic,nRow,surveyListControl;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.

    m_pExercise = new CMExercise();
    
    //页面内容过多不够显示时发挥作用
    mScrollView = [[UIScrollView alloc] init];
    mScrollView.backgroundColor = [UIColor whiteColor];
    mScrollView.frame = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT - 64);
    [self.view addSubview:mScrollView];
    
    //练习、测验或调研名称
    UILabel *titleLablel = [[UILabel alloc] init];
    titleLablel.frame = CGRectMake(20, 20, UI_IOS_WINDOW_WIDTH - 40, 30);
    titleLablel.font = [UIFont systemFontOfSize:kTextSizeMid];
    titleLablel.text = [itemDic objectForKey:@"title"];
    [mScrollView addSubview:titleLablel];
    mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, titleLablel.frame.origin.y + titleLablel.frame.size.height);
    CMRELEASE(titleLablel);
    
    NSString *strTitle;
    NSString *strBtnTitle;
    
    //不显示查看答案按钮时，UI缩进像素（默认 为0）
    double exam_answer_height = 0;
    UIButton *startButton = [UIButton buttonWithType:UIButtonTypeCustom];
    
    
    startButton.frame = CGRectMake(20, 100, UI_IOS_WINDOW_WIDTH - 40, 46);
    [startButton setBackgroundImage:[UIImage imageNamed:@"sign_n"] forState:UIControlStateNormal];
    [startButton setBackgroundImage:[UIImage imageNamed:@"sign_p"] forState:UIControlStateHighlighted];
    [startButton setBackgroundImage:[UIImage imageNamed:@"sign_d"] forState:UIControlStateDisabled];
    startButton.tag = 2013;
    [startButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [startButton setTitleColor:kColorGrayText forState:UIControlStateDisabled];
    [startButton.titleLabel setFont:[UIFont boldSystemFontOfSize:20]];
    [startButton addTarget:self action:@selector(startBtnPressed:) forControlEvents:UIControlEventTouchUpInside];
    [mScrollView addSubview:startButton];
    
    //练习
    if ([[itemDic objectForKey:@"type"] isEqual:@"practice"])
    {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(continuePractice:) name:@"continuepractice" object:nil];

        [self refreshExerciseList];
        [self refreshWrongCount:nil];

        //已答
        CMLabel *answeredLabel = [[CMLabel alloc] init];
        answeredLabel.frame = CGRectMake(20, 60, 90, 20);
        [answeredLabel setText:[NSString stringWithFormat:I(@"已答%@/%@"),[itemDic objectForKey:@"completecount"],[itemDic objectForKey:@"totalcount"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
        [answeredLabel setKeyWordTextArray:[NSArray arrayWithObject:[itemDic objectForKey:@"completecount"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
        answeredLabel.tag = 100001;
        [mScrollView addSubview:answeredLabel];
        CMRELEASE(answeredLabel);
        
        
        //正确率
        CMLabel *correctLabel = [[CMLabel alloc] init];
        correctLabel.frame = CGRectMake(115, 60, 90, 20);
        int nRightCount = m_pExercise->GetRightCount([[itemDic objectForKey:@"id"] UTF8String]);
        int nTotalCount = [[itemDic objectForKey:@"completecount"] integerValue];
        
        NSString *strRightPercent;
        
        if (nTotalCount <= 0)
        {
            strRightPercent = @"0%";
        }
        else
        {
            NSString *str = [NSString stringWithFormat:@"%.0f",(float)(nRightCount*100/nTotalCount)];
            strRightPercent = [NSString stringWithFormat:@"%@%@",str,@"%"];
        }
        NSString *strCorrect = [NSString stringWithFormat:I(@"正确率%@"),strRightPercent];
        CGSize correctSize = [strCorrect sizeWithFont:[UIFont systemFontOfSize:FONT_SIZE] constrainedToSize:CGSizeMake(90, MAXFLOAT) lineBreakMode:NSLineBreakByWordWrapping];
        correctLabel.frame = CGRectMake(0, 0, correctSize.width, 20);
        correctLabel.tag = 100000;
        correctLabel.center = CGPointMake(UI_IOS_WINDOW_WIDTH/2, 70);
        [correctLabel setText:strCorrect WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
        //[correctLabel setKeyWordTextArray:[NSArray arrayWithObject:strRightPercent] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
        [correctLabel setKeyWordRange:NSMakeRange(3, strRightPercent.length-1) WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
        [mScrollView addSubview:correctLabel];
        CMRELEASE(correctLabel);
        /*
        //参与人数
        CMLabel *totalLabel = [[CMLabel alloc] init];
        totalLabel.frame = CGRectMake(210, 60, 90, 20);
        NSString *strTotal = [NSString stringWithFormat:@"%@人参与", [itemDic objectForKey:@"completeuser"]];
        
        CGSize totalSize = [strTotal sizeWithFont:[UIFont systemFontOfSize:FONT_SIZE] constrainedToSize:CGSizeMake(90, MAXFLOAT) lineBreakMode:NSLineBreakByWordWrapping];
        totalLabel.frame = CGRectMake(300 - totalSize.width,60,totalSize.width,20);
        [totalLabel setText:strTotal WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
        [totalLabel setKeyWordTextArray:[NSArray arrayWithObject:[itemDic objectForKey:@"completeuser"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
        [mScrollView addSubview:totalLabel];
        mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, totalLabel.frame.origin.y + totalLabel.frame.size.height);
         */
        
        
        if ([[itemDic objectForKey:@"completecount"] integerValue] == 0)
        {
            strBtnTitle = [NSString stringWithFormat:@"%@%@",I(@"开始"),I(@"练习")];
        }
        else
        {
            strBtnTitle = [NSString stringWithFormat:@"%@%@",I(@"继续"),I(@"练习")];
        }
        strTitle = [NSString stringWithFormat:@"%@%@",I(@"练习"),I(@"详情")];
        [startButton setTitle:strBtnTitle forState:UIControlStateNormal];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshWrongCount:) name:@"refreshwrongcount" object:nil];

    }
    else if ([[itemDic objectForKey:@"type"] isEqual:@"exam"]) //测验
    {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(examback:) name:@"examback" object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(completeexam:) name:@"completeexam" object:nil];
        
        
        
        
        nLastTime = [[itemDic objectForKey:@"duration"] intValue]*60;
        nCurindex = [[itemDic objectForKey:@"index"] intValue];

        strTitle = [NSString stringWithFormat:@"%@%@",I(@"测验"),I(@"详情")];
        
        UIView *rightView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 45, 44)];
        rightView.backgroundColor = [UIColor clearColor];
        
        //排名
        UIButton *rankbtn = [UIButton buttonWithType:UIButtonTypeCustom];
        rankbtn.frame = CGRectMake(0, 0, 45, 44);
        [rankbtn setTitle:I(@"排名") forState:UIControlStateNormal];
        [rankbtn setTitleColor:kColorButtonTitle forState:UIControlStateNormal];
        [rankbtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
        [rankbtn addTarget:self action:@selector(gotoRank:) forControlEvents:UIControlEventTouchUpInside];
        
        UIImageView* vsep = [[UIImageView alloc] init];
        vsep.image = [UIImage imageNamed:@"navsep"];
        vsep.frame = CGRectMake(0, 0, 2, 44);
        
        if (__iOS7)
        {
            [rightView addSubview:rankbtn];
        }
        else
        {
            [rightView addSubview:vsep];
            [rightView addSubview:rankbtn];
        }
        CMRELEASE(vsep);
        
        UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:rightView];
        self.navigationItem.rightBarButtonItem = rightItem;
        CMRELEASE(rightItem);
        CMRELEASE(rightView);
        
        //完成情况
        CMLabel *descLabel = [[CMLabel alloc] init];
        descLabel.frame = CGRectMake(20, 60, UI_IOS_WINDOW_WIDTH - 40, 20);
        descLabel.tag = 210000;
        

        [mScrollView addSubview:descLabel];
        
        //更新显示数据
        [self updateData];
        
        
        CMRELEASE(descLabel);
     
    }
    else if ([[itemDic objectForKey:@"type"] isEqual:@"survey"]) //调研
    {
        strTitle = I(@"详情");
        strBtnTitle = I(@"开始");
        [startButton setTitle:strBtnTitle forState:UIControlStateNormal];
        
        //完成情况
        CMLabel *descLabel = [[CMLabel alloc] init];
        descLabel.frame = CGRectMake(20, 60, UI_IOS_WINDOW_WIDTH - 40, 20);
        [descLabel setText:[NSString stringWithFormat:I(@"共%@人，%@人已完成"),[itemDic objectForKey:@"requirecount"],[itemDic objectForKey:@"completecount"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
        
        //此时不能调用setKeyWordTextArray 需要指定变色文字的范围
        [descLabel setKeyWordRange:NSMakeRange(3+((NSString *)[itemDic objectForKey:@"requirecount"]).length, ((NSString *)[itemDic objectForKey:@"completecount"]).length) WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
        [mScrollView addSubview:descLabel];
        CMRELEASE(descLabel);
    }
    
    self.titleLabel.text = strTitle;
    

    
    
    mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, startButton.frame.origin.y + startButton.frame.size.height);
    

    
    if ([[itemDic objectForKey:@"type"] isEqual:@"practice"] || [[itemDic objectForKey:@"type"] isEqual:@"exam"])
    {
        //所属分类
        CMLabel *categoryLabel = [[CMLabel alloc] init];
        categoryLabel.tag = 50001;
        categoryLabel.frame = CGRectMake(20, 170, 140, 20);
        NSString *strCategory = [NSString stringWithFormat:@"%@  %@",I(@"所属分类"),[itemDic objectForKey:@"category"]];
        CGSize categorySize = [strCategory sizeWithFont:[UIFont systemFontOfSize:FONT_SIZE] constrainedToSize:CGSizeMake(UI_IOS_WINDOW_WIDTH - 40, MAXFLOAT) lineBreakMode:NSLineBreakByWordWrapping];
        categoryLabel.frame = CGRectMake(20, 170 + exam_answer_height, UI_IOS_WINDOW_WIDTH - 40, 20);
        [categoryLabel setText:strCategory WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
        [categoryLabel setKeyWordTextArray:[NSArray arrayWithObject:[itemDic objectForKey:@"category"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x2f2f2f)];
        
        if (((NSString*)[itemDic objectForKey:@"category"]).length > 0)
        {
            [mScrollView addSubview:categoryLabel];
            CMRELEASE(categoryLabel);
        }
        
        //发布时间 如果所属分类名称过长 则换行显示
        CMLabel *publishTimeLabel = [[CMLabel alloc] init];
        
        NSString *completetime = [itemDic objectForKey:@"pubdate"];
        
        publishTimeLabel.tag = 50002;
        if (categorySize.width > 140)
        {
            publishTimeLabel.frame = CGRectMake(20, 200 + exam_answer_height, UI_IOS_WINDOW_WIDTH - 40, 20);
            mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, publishTimeLabel.frame.origin.y + publishTimeLabel.frame.size.height);
        }
        else if (((NSString*)[itemDic objectForKey:@"category"]).length <= 0)
        {
            publishTimeLabel.frame = CGRectMake(20, 170 + exam_answer_height, UI_IOS_WINDOW_WIDTH - 40, 20);
            mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, categoryLabel.frame.origin.y + categoryLabel.frame.size.height);
        }
        else
        {
            publishTimeLabel.frame = CGRectMake(160, 170 + exam_answer_height, 140, 20);
            
            if ([[itemDic objectForKey:@"type"] isEqual:@"practice"])
            {
                NSString *strPub = [NSString stringWithFormat:@"%@  %@", I(@"发布时间") ,completetime];
                CGSize pubSize = [strPub sizeWithFont:[UIFont systemFontOfSize:FONT_SIZE] constrainedToSize:CGSizeMake(140, MAXFLOAT) lineBreakMode:NSLineBreakByWordWrapping];
                publishTimeLabel.frame = CGRectMake(300 - pubSize.width,170,pubSize.width,20);
                
            }
            mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, categoryLabel.frame.origin.y + categoryLabel.frame.size.height);
        }
        
        [publishTimeLabel setText:[NSString stringWithFormat:@"%@  %@", I(@"发布时间") ,completetime] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
        [publishTimeLabel setKeyWordTextArray:[NSArray arrayWithObject:completetime] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x2f2f2f)];
        [mScrollView addSubview:publishTimeLabel];
        CMRELEASE(publishTimeLabel);
        
        if ([[itemDic objectForKey:@"type"] isEqual:@"exam"]) //测验
        {

            //题目总数
            CMLabel *countLabel = [[CMLabel alloc] init];
            countLabel.tag = 50003;
            countLabel.frame = CGRectMake(20, mScrollView.contentSize.height + 10, 140, 20);
            [countLabel setText:[NSString stringWithFormat:@"%@  %@",I(@"题目总数"),[itemDic objectForKey:@"questioncount"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
            [countLabel setKeyWordTextArray:[NSArray arrayWithObject:[itemDic objectForKey:@"questioncount"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x2f2f2f)];
            [mScrollView addSubview:countLabel];
            CMRELEASE(countLabel);
            
            //时长
            CMLabel *durationLabel = [[CMLabel alloc] init];
            durationLabel.tag = 50004;
            durationLabel.frame = CGRectMake(160, mScrollView.contentSize.height + 10, 140, 20);
            if ([[itemDic objectForKey:@"duration"] isEqualToString:@"-1"]) {
                
                [durationLabel setText:[NSString stringWithFormat:@"%@  %@",I(@"时长"),I(@"无计时")] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
                [durationLabel setKeyWordTextArray:[NSArray arrayWithObject:[NSString stringWithFormat:@"%@",[itemDic objectForKey:@"duration"]]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x2f2f2f)];
            }else{
                
                [durationLabel setText:[NSString stringWithFormat:@"%@  %@%@",I(@"时长"),[itemDic objectForKey:@"duration"],I(@"分钟")] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
                [durationLabel setKeyWordTextArray:[NSArray arrayWithObject:[NSString stringWithFormat:@"%@%@",[itemDic objectForKey:@"duration"],I(@"分钟")]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x2f2f2f)];
            }

            [mScrollView addSubview:durationLabel];
            mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, durationLabel.frame.origin.y + durationLabel.frame.size.height);
            CMRELEASE(durationLabel);
            
            //总分
            CMLabel *fullScoreLabel = [[CMLabel alloc] init];
            fullScoreLabel.tag = 50005;
            fullScoreLabel.frame = CGRectMake(20, mScrollView.contentSize.height + 10, 140, 20);
            [fullScoreLabel setText:[NSString stringWithFormat:@"%@  %@%@",I(@"总分"),[itemDic objectForKey:@"fullmark"],I(@"分")] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
            [fullScoreLabel setKeyWordTextArray:[NSArray arrayWithObject:[NSString stringWithFormat:@"%@%@",[itemDic objectForKey:@"fullmark"],I(@"分")]] WithFont:[UIFont systemFontOfSize:14] AndColor:UIColorRGB(0x2f2f2f)];
            [mScrollView addSubview:fullScoreLabel];
            CMRELEASE(fullScoreLabel);
            
            //及格分
            CMLabel *passScoreLabel = [[CMLabel alloc] init];
            passScoreLabel.tag = 50006;
            passScoreLabel.frame = CGRectMake(160, mScrollView.contentSize.height + 10, 140, 20);
            [passScoreLabel setText:[NSString stringWithFormat:@"%@  %@%@",I(@"及格分"),[itemDic objectForKey:@"passmark"],I(@"分")] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
            [passScoreLabel setKeyWordTextArray:[NSArray arrayWithObject:[NSString stringWithFormat:@"%@%@",[itemDic objectForKey:@"passmark"],I(@"分")]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x2f2f2f)];
            [mScrollView addSubview:passScoreLabel];
            mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, passScoreLabel.frame.origin.y + passScoreLabel.frame.size.height);
            CMRELEASE(passScoreLabel);
        }
    }
    else if ([[itemDic objectForKey:@"type"] isEqual:@"survey"]) //调研
    {
        //截止时间
        CMLabel *endTimeLabel = [[CMLabel alloc] init];
        endTimeLabel.frame = CGRectMake(20, 170, UI_IOS_WINDOW_WIDTH - 40, 20);
        
        NSString *strExpireDate = [itemDic objectForKey:@"expiredate"];
        
        //若返回时间中带有0:00:00字符串 则去掉此部分
        if ([[itemDic objectForKey:@"expiredate"] rangeOfString:@"0:00:00" options:NSBackwardsSearch].location != NSNotFound)
        {
            //strExpireDate = [strExpireDate substringToIndex:[[itemDic objectForKey:@"expiredate"] rangeOfString:@"0:00:00" options:NSBackwardsSearch].location];
        }
        [endTimeLabel setText:[NSString stringWithFormat:I(@"截止时间  %@"),strExpireDate] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
        mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, endTimeLabel.frame.origin.y + endTimeLabel.frame.size.height);
        [mScrollView addSubview:endTimeLabel];
        CMRELEASE(endTimeLabel);
    }
    
    //简介
    UILabel *descLabel = [[UILabel alloc] init];
    descLabel.tag = 50007;
    descLabel.frame = CGRectMake(20, mScrollView.contentSize.height + 10, UI_IOS_WINDOW_WIDTH - 40, 20);
    descLabel.font = [UIFont systemFontOfSize:FONT_SIZE];
    descLabel.textColor = UIColorRGB(0x7f7f7f);
    descLabel.lineBreakMode = NSLineBreakByWordWrapping;
    descLabel.numberOfLines = 0;
    NSString *str = [itemDic objectForKey:@"desc"];
    if (str.length > 0)
    {
        str = [NSString stringWithFormat:I(@"简介  %@"),str];
    }
    CGSize size = [str sizeWithFont:descLabel.font constrainedToSize:CGSizeMake(UI_IOS_WINDOW_WIDTH - 40, MAXFLOAT) lineBreakMode:NSLineBreakByWordWrapping];
    descLabel.frame = CGRectMake(20, mScrollView.contentSize.height + 10, UI_IOS_WINDOW_WIDTH - 40, size.height);
    descLabel.text = str;
    [mScrollView addSubview:descLabel];
    mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, descLabel.frame.origin.y + descLabel.frame.size.height +10);
    CMRELEASE(descLabel);
    
}

  //判断考试状态
- (ExamState)stateOfExam{
    float fTestScores = [self.itemDic[@"scores"] floatValue];
    float fPassMark = [self.itemDic[@"passmark"] floatValue];
    int nCurrNumber = [self.itemDic[@"currnumber"] intValue];
    int nTotalNumber = [self.itemDic[@"totalnumber"] intValue];
    int nRemainTime = [self.itemDic[@"remaintime"] intValue];
    int nDuration = [self.itemDic[@"duration"] intValue];
    
    if (fTestScores >= -EPSILON && fTestScores < fPassMark && nCurrNumber < nTotalNumber) {
        if (nRemainTime >= 0 && nRemainTime < nDuration * 60) {
            return ExamStateContinue;
        }
        else {
            return ExamStateStart;
        }
    }
    else {
        if ( fabs(fTestScores + 1) <= EPSILON){
            return ExamStateMarking;
        }
        else {
            BOOL bViewAnswer = [self.itemDic[@"viewanswer"] boolValue];
            if (bViewAnswer) {
                return ExamStateViewAnswer;
            }
            else {
                if (fTestScores >= fPassMark) {
                    return ExamStatePassed;
                }
                else {
                    return ExamStateFailed;
                }
            }
        }
    }
}


- (void)setHanlder:(CMExamList *)hanler row:(int)index
{
    m_pExamList = hanler;
    nRow = index;
}

- (void)examback:(id)sender
{
    UIButton *btn = (UIButton*)[self.view viewWithTag:2013];
    
    //测验完成后 显示为查看答案与解析
    int nTotalNumber = [self.itemDic[@"totalnumber"] intValue];
    int nCurrNumber = [self.itemDic[@"currnumber"] intValue];
    NSString *strBtnTitle = [NSString stringWithFormat:@"%@%d%@", I(@"继续考试(还可以考试"), (nTotalNumber - nCurrNumber),I(@"次)")];
    [btn setTitle:strBtnTitle forState:UIControlStateNormal];
    
    //测验刷新剩余时间和 当前答题位置
    int nRemainTime = [[[sender userInfo] objectForKey:@"remaintime"] intValue];
    int nIndex = [[[sender userInfo] objectForKey:@"index"] intValue];
    
    [self.itemDic setObject:[NSString stringWithFormat:@"%d", nRemainTime] forKey:@"remaintime"];
    
    if (!m_pExamList) {
        nCurindex = nIndex;
        nLastTime = nRemainTime;
        return;
    }
    TExamListItem item;
    m_pExamList->GetItem(nRow, item);
    item.nRemainTime = nRemainTime;
    item.nCurrIndex = nIndex;
    m_pExamList->UpdateItem(item);
}

- (void)completeexam:(id)sender
{
    
    if (!m_pExamList) {
        nCurindex = 0;
        nLastTime = [self.itemDic[@"duration"] intValue] * 60;
        return;
    }
    TExamListItem item;
    m_pExamList->GetItem(nRow, item);
    item.nRemainTime = [self.itemDic[@"duration"] intValue] * 60;
    item.nCurrIndex = 0;
    item.sTestscores = [NSString stringWithFormat:@"%d", -1].UTF8String;
    item.nCurrNumber = item.nCurrNumber + 1;
    item.nUsercompletecount = item.nUsercompletecount + 1;
    m_pExamList->UpdateItem(item);
    
    
    [self.itemDic setObject:[NSString stringWithFormat:@"%d", -1] forKey:@"scores"];
    [self.itemDic setObject:[NSString stringWithFormat:@"%d", [self.itemDic[@"currnumber"] intValue] + 1] forKey:@"currnumber"];
    [self.itemDic setObject:[NSString stringWithFormat:@"%d", [self.itemDic[@"duration"] intValue] * 60] forKey:@"remaintime"];
    
    ExamState state = [self stateOfExam];
    
    
    UIButton *btn = (UIButton*)[self.view viewWithTag:2013];
    
    //测验完成后 显示为查看答案与解析
    [btn setTitle:I(@"改卷中") forState:UIControlStateNormal];
    btn.enabled = NO;
    [itemDic setObject:@"1" forKey:@"complete"];
    [itemDic setObject:[NSString stringWithFormat:@"%d",[[itemDic objectForKey:@"completecount"] intValue]+1] forKey:@"completecount"];
    
    double exam_answer_height = 0;
//    //是否能查看答案
//    if ([[itemDic objectForKey:@"viewanswer"] isEqual:@"0"] && [[itemDic objectForKey:@"complete"] isEqual:@"1"])
//    {
//        btn.hidden = YES;
//        UIView *seperator = [[UIView alloc]initWithFrame:CGRectMake(20, 100, 280, 1.0)];
//        seperator.backgroundColor = UIColorRGB(0xd8d8d8);
//        [mScrollView addSubview:seperator];
//        CMRELEASE(seperator);
//        exam_answer_height = -45;
//        mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, btn.frame.origin.y + btn.frame.size.height + exam_answer_height);
//        [self refreshFrameLabel];
//    }
    
    WEAKSELF;
    [[CMBrowserHandler handler] doRequestExamById:[itemDic objectForKey:@"id"] success:^(CMExamList *examlist) {
        
//        m_pExamList = examlist;
        
        TExamListItem item;
        examlist->GetItem(0, item);
        NSString *strTitle = [NSString stringWithUTF8String:item.sTitle.c_str()];
        NSString *scores = [NSString stringWithFormat:@"%@",NSStringFrom(item.sTestscores)];
        NSString *strID = [NSString stringWithUTF8String:item.sID.c_str()];
        NSString *strDesc = [NSString stringWithUTF8String:item.sDesc.c_str()];
        NSString *strCategory = [NSString stringWithUTF8String:item.sCategory.c_str()];
        NSString *strPubdate = [NSString stringWithUTF8String:item.sPubdate.c_str()];
        NSString *strRequireCount = [NSString stringWithFormat:@"%d",item.nRequirecount];
        NSString *strCompleteCount = [NSString stringWithFormat:@"%d",item.nRequirecount - item.nUncompletecount];
        NSString *strQuestionCount = [NSString stringWithFormat:@"%d",item.nQuestioncount];
        NSString *strDuration = [NSString stringWithFormat:@"%d",item.nDuration];
        NSString *strRemainTime = [NSString stringWithFormat:@"%d",item.nRemainTime];
        NSString *strFullMark = [NSString stringWithFormat:@"%d",item.nFullmark];
        NSString *strPassMark = [NSString stringWithFormat:@"%d",item.nPassmark];
        NSString *strRankUrl = [NSString stringWithUTF8String:item.sRankurl.c_str()];
        //NSString *strComplete = [NSString stringWithFormat:@"%i",item.bIsComplete];
        NSString *strViewAnswer = [NSString stringWithFormat:@"%i",item.bViewAnswer];
        NSString *strCurrNumber = [NSString stringWithFormat:@"%i", item.nCurrNumber];
        NSString *strTotalNumber = [NSString stringWithFormat:@"%i", item.nTotalNumber];
        NSString *strCompleteTime = NSStringFrom(item.sCompletetime);
        
        
        NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"exam",@"type",strTitle,@"title",scores,@"scores",strID,@"id",strDesc,@"desc",strCategory,@"category",strPubdate,@"pubdate",strRequireCount,@"requirecount",strCompleteCount,@"completecount",strQuestionCount,@"questioncount",strDuration,@"duration",strRemainTime,@"remaintime",strFullMark,@"fullmark",strPassMark,@"passmark",strRankUrl,@"rank",/*strComplete,@"complete",*/ strViewAnswer,@"viewanswer", strCurrNumber, @"currnumber", strTotalNumber, @"totalnumber", strCompleteTime, @"completetime", nil];
        [self.itemDic removeAllObjects];
        self.itemDic = dic;
        
        
        
        [self updateData];
        
        //更新缓存
        m_pExamList->UpdateItem(item);
        
    } failure:^(int errorCode) {
        
    }];

}

- (void)updateData
{
    ExamState state = [self stateOfExam];
    
    NSString *strBtnTitle;
    UIButton *startButton = (UIButton*)[self.view viewWithTag:2013];
    switch (state) {
        case ExamStateContinue:
        {
            int nTotalNumber = [self.itemDic[@"totalnumber"] intValue];
            int nCurrNumber = [self.itemDic[@"currnumber"] intValue];
            strBtnTitle = [NSString stringWithFormat:@"%@%d%@", I(@"继续考试(还可以考试"), (nTotalNumber - nCurrNumber),I(@"次)")];
            startButton.enabled = YES;
        }
            break;
            
        case ExamStateStart:
        {
            int nTotalNumber = [self.itemDic[@"totalnumber"] intValue];
            int nCurrNumber = [self.itemDic[@"currnumber"] intValue];
            strBtnTitle = [NSString stringWithFormat:@"%@%d%@", I(@"开始考试(还可以考试"), (nTotalNumber - nCurrNumber),I(@"次)")];
            startButton.enabled = YES;
        }
            break;
            
        case ExamStateViewAnswer:
        {
            strBtnTitle = I(@"查看答案与解析");
            
            startButton.hidden = NO;
            startButton.enabled = YES;
//            UIView *seperator = [[UIView alloc]initWithFrame:CGRectMake(20, 100, 280, 1.0)];
//            seperator.backgroundColor = UIColorRGB(0xd8d8d8);
//            [mScrollView addSubview:seperator];
//            CMRELEASE(seperator);
//            // exam_answer_height = -45;
//            mScrollView.contentSize = CGSizeMake(UI_IOS_WINDOW_WIDTH, startButton.frame.origin.y + startButton.frame.size.height + 0);
        }
            break;
            
        case ExamStatePassed:
        {
            strBtnTitle = I(@"考试已通过");
            startButton.enabled = NO;
        }
            break;
            
        case ExamStateFailed:
        {
            strBtnTitle = I(@"考试次数已满");
            startButton.enabled = NO;
        }
            break;
            
        case ExamStateMarking:
        {
            strBtnTitle = I(@"改卷中");
            startButton.enabled = NO;
        }
            break;
            
        default:
            break;
    }
    [startButton setTitle:strBtnTitle forState:UIControlStateNormal];

    
    //完成情况
    CMLabel *descLabel = (CMLabel*)[self.view viewWithTag:210000];
    if ([self.itemDic[@"currnumber"] intValue] == 0)
    {
        
        [descLabel setText:[NSString stringWithFormat:I(@"共%d人    %d人已交卷"),[[itemDic objectForKey:@"requirecount"] intValue],[[itemDic objectForKey:@"completecount"] intValue]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
        
        
        [descLabel setKeyWordTextArray:[NSArray arrayWithObjects:[NSString stringWithFormat:@"%d",[[itemDic objectForKey:@"requirecount"] intValue]], nil] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
        NSString *sdesc = descLabel.text;
        int l = [sdesc rangeOfString:I(@"人已交卷")].location - [NSString stringWithFormat:@"%d",[[itemDic objectForKey:@"completecount"] intValue]].length;
        [descLabel setKeyWordRange:NSMakeRange(l, [NSString stringWithFormat:@"%d",[[itemDic objectForKey:@"completecount"] intValue]].length) WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
        
    }
    else if (state == ExamStateMarking)
    {
        [descLabel setText:[NSString stringWithFormat:I(@"%@    交卷时间%@"),I(@"改卷中"),[itemDic objectForKey:@"completetime"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
        
        
        [descLabel setKeyWordTextArray:[NSArray arrayWithObjects:I(@"改卷中"),[itemDic objectForKey:@"completetime"], nil] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
    }
    else
    {
        NSString *sortes = [itemDic objectForKey:@"scores"];
        
        [descLabel setText:[NSString stringWithFormat:I(@"得分%@    交卷时间%@"),sortes,[itemDic objectForKey:@"completetime"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
        
        
        [descLabel setKeyWordTextArray:[NSArray arrayWithObjects:sortes,[itemDic objectForKey:@"completetime"], nil] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
        
    }
}

- (void)refreshFrameLabel
{
    CGRect frame;
    double exam_answer_height = 45;

    CMLabel *categoryLabel = (CMLabel*)[self.view viewWithTag:50001];
    frame = categoryLabel.frame;
    frame.origin.y -= exam_answer_height;
    categoryLabel.frame = frame;
    
    CMLabel *publishTimeLabel = (CMLabel*)[self.view viewWithTag:50002];
    frame = publishTimeLabel.frame;
    frame.origin.y -= exam_answer_height;
    publishTimeLabel.frame = frame;
    
    CMLabel *countLabel = (CMLabel*)[self.view viewWithTag:50003];
    frame = countLabel.frame;
    frame.origin.y -= exam_answer_height;
    countLabel.frame = frame;
    
    CMLabel *durationLabel = (CMLabel*)[self.view viewWithTag:50004];
    frame = durationLabel.frame;
    frame.origin.y -= exam_answer_height;
    durationLabel.frame = frame;
    
    CMLabel *fullScoreLabel = (CMLabel*)[self.view viewWithTag:50005];
    frame = fullScoreLabel.frame;
    frame.origin.y -= exam_answer_height;
    fullScoreLabel.frame = frame;
    
    CMLabel *passScoreLabel = (CMLabel*)[self.view viewWithTag:50006];
    frame = passScoreLabel.frame;
    frame.origin.y -= exam_answer_height;
    passScoreLabel.frame = frame;
    
    CMLabel *descLabel = (CMLabel*)[self.view viewWithTag:50007];
    frame = descLabel.frame;
    frame.origin.y -= exam_answer_height;
    descLabel.frame = frame;

}

- (void)refreshExerciseList{
    if (!m_pExerciseList) {
        return;
    }
    TExerciseListItem item;
    m_pExerciseList->GetItem(nRow,item);
    m_pExerciseList->Refresh(item);
    nCurindex = item.nCurIndex;
    int totalcount = [[itemDic objectForKey:@"totalcount"] integerValue];
    int completecount = item.nCompleteCount;
    
    [itemDic setObject:[NSString stringWithFormat:@"%d",completecount] forKey:@"completecount"];

}

- (void)continuePractice:(id)sender
{
    UIButton *btn = (UIButton*)[self.view viewWithTag:2013];
    
    [self refreshExerciseList];
    //练习未完成时 显示为继续练习
    if ([[itemDic objectForKey:@"completecount"] integerValue] == 0)
    {
        [btn setTitle:[NSString stringWithFormat:@"%@%@",I(@"开始"),I(@"练习")] forState:UIControlStateNormal];
    }
    else
    {
        [btn setTitle:[NSString stringWithFormat:@"%@%@",I(@"继续"),I(@"练习")] forState:UIControlStateNormal];
    }
    
    //刷新已答
    CMLabel *answeredLabel = (CMLabel *)[self.view viewWithTag:100001];
    [answeredLabel setText:[NSString stringWithFormat:I(@"已答%@/%@"),[itemDic objectForKey:@"completecount"],[itemDic objectForKey:@"totalcount"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
    [answeredLabel setKeyWordTextArray:[NSArray arrayWithObject:[itemDic objectForKey:@"completecount"]] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
    
    //刷新正确率
    CMLabel *lablel = (CMLabel *)[self.view viewWithTag:100000];

    int nRightCount = m_pExercise->GetRightCountExcise([[itemDic objectForKey:@"id"] UTF8String]);
    int nTotalCount = [[itemDic objectForKey:@"completecount"] intValue];
    
    NSString *strRightPercent;
    
    if (nTotalCount <= 0)
    {
        strRightPercent = @"0%";
    }
    else
    {
        NSString *str = [NSString stringWithFormat:@"%.0f",(float)(nRightCount*100/nTotalCount)];
        strRightPercent = [NSString stringWithFormat:@"%@%@",str,@"%"];
    }
    NSString *strCorrect = [NSString stringWithFormat:I(@"正确率%@"),strRightPercent];
    [lablel setText:strCorrect WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0x7f7f7f)];
    [lablel setKeyWordTextArray:[NSArray arrayWithObject:strRightPercent] WithFont:[UIFont systemFontOfSize:FONT_SIZE] AndColor:UIColorRGB(0xfe883f)];
    CGSize correctSize = [strCorrect sizeWithFont:[UIFont systemFontOfSize:FONT_SIZE] constrainedToSize:CGSizeMake(90, MAXFLOAT) lineBreakMode:NSLineBreakByWordWrapping];
    lablel.frame = CGRectMake(0, 0, correctSize.width, 20);
    lablel.center = CGPointMake(UI_IOS_WINDOW_WIDTH/2, 70);
}

- (IBAction)gotoRank:(id)sender
{
    CMExamRankViewController *examRank = [[CMExamRankViewController alloc] init];
    examRank.title = I(@"排名");
    examRank.strURL = [itemDic objectForKey:@"rank"];
    [self.navigationController pushViewController:examRank animated:YES];
    CMRELEASE(examRank);
}

- (IBAction)startBtnPressed:(id)sender
{
    if ([[itemDic objectForKey:@"type"] isEqual:@"practice"])
    {
        if ([[itemDic objectForKey:@"totalcount"] intValue] <= 0)
        {
			[tool ShowAlert:I(@"无题目")];
			return;
		}
				
        //如果是菜单项处理相关操作
		CMExamInfoControl* examControl = [[CMExamInfoControl alloc] init];
		examControl.title = [itemDic objectForKey:@"title"];
		examControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
		examControl.navigationController.navigationBarHidden = NO;
		examControl.tabBarController.tabBar.hidden = YES;
		examControl.hidesBottomBarWhenPushed = YES;
		examControl.nCurIndex = nCurindex;
        examControl.nCompleteNum = [[itemDic objectForKey:@"completeuser"] integerValue];
		[examControl setbtn:FALSE];
		[examControl OpenSurvey:@"practice" surveyid:[[itemDic objectForKey:@"id"] UTF8String] oper:I(@"开始")];
		[self.navigationController pushViewController:examControl animated:YES];
        CMRELEASE(examControl);
    }
    else if ([[itemDic objectForKey:@"type"] isEqual:@"exam"])
    {
        if (CMGlobal::TheOne().IsOffline()) {
            [tool ShowError:-1];
            return;
        }
        
		if ([[itemDic objectForKey:@"questioncount"] intValue] <= 0)
        {
			[tool ShowAlert:I(@"无题目")];
			return;
		}
		NSString * strValue;
		
        //如果是菜单项处理相关操作
		CMExamInfoControl* examControl = [[CMExamInfoControl alloc] init];
		examControl.title = [itemDic objectForKey:@"title"];
		examControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
		examControl.navigationController.navigationBarHidden = NO;
		examControl.tabBarController.tabBar.hidden = YES;
		examControl.hidesBottomBarWhenPushed = YES;
		
		[examControl setbtn:TRUE];
        
        int nTime = [[itemDic objectForKey:@"remaintime"] integerValue];
        
        TExamListItem item;
        
        if (m_pExamList && m_pExamList->GetItem(nRow, item)) {
            if (nTime > item.nRemainTime);
            {
                nTime = item.nRemainTime;
            }
        }
        else{
            nTime = [[itemDic objectForKey:@"duration"] integerValue];
        }
        
        if ([[itemDic objectForKey:@"currnumber"] intValue] == [[itemDic objectForKey:@"totalnumber"] intValue]
            || [[itemDic objectForKey:@"scores"] floatValue] >= [[itemDic objectForKey:@"passmark"] floatValue])
        {
			strValue = @"view";//测验已完成
            
            //查看测验从第一个开始
            [examControl setDuration:[[itemDic objectForKey:@"duration"] integerValue] ReaminTime:nTime index:0];
		}
        else
        {
			strValue = @"start";//测验未完成，开始测验
            
            
            if (!m_pExamList) {
                [examControl setDuration:[[itemDic objectForKey:@"duration"] integerValue] ReaminTime:nLastTime index:nCurindex];
            }
            else{
                [examControl setDuration:[[itemDic objectForKey:@"duration"] integerValue] ReaminTime:nTime index:item.nCurrIndex];
            }
		}
    
		[examControl OpenSurvey:@"exam" surveyid:[[itemDic objectForKey:@"id"] UTF8String] oper:strValue];
		[self.navigationController pushViewController:examControl animated:YES];
        CMRELEASE(examControl);
    }
    else if ([[itemDic objectForKey:@"type"] isEqual:@"survey"])
    {
		CMSurveyControl *SurveyView = [[CMSurveyControl alloc] init];
		[SurveyView OpenSurvey:[itemDic objectForKey:@"title"] surveyid:[[itemDic objectForKey:@"id"] UTF8String]];
        SurveyView.surveyListControl = self.surveyListControl;
		[self.navigationController pushViewController:SurveyView animated:YES];
		
        CMRELEASE(SurveyView);
    }
}

- (void)refreshWrongCount:(id)sender
{
    UIView *wrongView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 45, 44)];
    wrongView.backgroundColor = [UIColor clearColor];
    
	UIButton *wrongbtn = [UIButton buttonWithType:UIButtonTypeCustom];
	wrongbtn.frame = CGRectMake(0, 0, 45, 44);
	[wrongbtn setTitle:I(@"错题") forState:UIControlStateNormal];
	[wrongbtn setTitleColor:kColorButtonTitle forState:UIControlStateNormal];
	[wrongbtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
	[wrongbtn addTarget:self action:@selector(gotoWrong:) forControlEvents:UIControlEventTouchUpInside];
    [wrongView addSubview:wrongbtn];
    
     nWrongCount = m_pExercise->GetWrongCountExcise([[itemDic objectForKey:@"id"] UTF8String]);
    
    if (nWrongCount > 0)
    {
        UIImageView *tipsimage = [[UIImageView alloc] init];
        tipsimage.frame = CGRectMake(27, 2, 20, 20);
        tipsimage.image = [UIImage imageNamed:@"wrongTips"];
        
        UILabel *wronglabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 20, 20)];
        wronglabel.backgroundColor = [UIColor clearColor];
        wronglabel.textColor = [UIColor whiteColor];
        wronglabel.text = [NSString stringWithFormat:@"%d",nWrongCount];
        wronglabel.textAlignment = [tool TextAlignment:ALIGNMENTCENTER];
        wronglabel.font = [UIFont systemFontOfSize:12];
        [tipsimage addSubview:wronglabel];
        [wrongView addSubview:tipsimage];
        CMRELEASE(wronglabel);
        CMRELEASE(tipsimage);
    }
    
	UIImageView* vsep = [[UIImageView alloc] init];
	vsep.image = [UIImage imageNamed:@"navsep"];
	vsep.frame = CGRectMake(0, 0, 2, 44);
    
    if (!__iOS7)
    {
        [wrongView addSubview:vsep];
    }
    CMRELEASE(vsep);
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:wrongView];
    
    if (nWrongCount > 0) {
        self.navigationItem.rightBarButtonItem = rightItem;
    }
    else{
        self.navigationItem.rightBarButtonItem = nil;
    }
    
    CMRELEASE(rightItem);
    CMRELEASE(wrongView);
}

- (IBAction)gotoWrong:(id)sender
{
   // nWrongCount = m_pExercise->GetWrongCountExcise([[itemDic objectForKey:@"id"] UTF8String]);

    if (nWrongCount <= 0) {
        [tool ShowAlert:I(@"无题目")];
        return;
    }
    
    CMExamInfoControl* examControl = [[CMExamInfoControl alloc] init];
    
    examControl.title = [itemDic objectForKey:@"title"];
    examControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
    examControl.navigationController.navigationBarHidden = NO;
    examControl.tabBarController.tabBar.hidden = YES;
    examControl.hidesBottomBarWhenPushed = YES;
    examControl.nCurIndex = 0;
    examControl.nCompleteNum = [[itemDic objectForKey:@"completeuser"] integerValue];
    [examControl setbtn:FALSE];
    [examControl OpenSurvey:@"wrong" surveyid:[[itemDic objectForKey:@"id"] UTF8String] oper:@"start"];
    [self.navigationController pushViewController:examControl animated:YES];
    CMRELEASE(examControl);
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc
{
    CMRELEASE(mScrollView);
    SAFEDELETE(m_pExercise);
    
    CMRELEASE(itemDic)
    
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}

@end

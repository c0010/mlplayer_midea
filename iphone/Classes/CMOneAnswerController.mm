//
//  CMViewController.h
//  OCplusplus
//
//  Created by Tim on 13-1-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.

#import "CMOneAnswerController.h"
#import "CMImage.h"
#import <QuartzCore/QuartzCore.h> 
#import "CMAnswerTableViewCell.h"
#import "ComplexButton.h"
#include "cmmyinfo.h"
#include "cmsettings.h"

@implementation CMOneAnswerController
@synthesize questionid,questionusername,needrefresh,bestanswer;

-(void)setitem:(TAnswerItem&)item
{
	answeritem = item;
}
-(void)refreshimage
{
	[self updateView];	
}
-(void)updateView
{
	if(!headview || !answerview)
		return;
	CGRect f = self.view.bounds;
	[headview.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
	
	UIImageView* headimageview = [[UIImageView alloc] init];
	if(m_pWebImage->GetFromUrl(0, CMMyInfo::GetInstance()->GetHeadimage()))
	{
		UIImage* headimage =  [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(CMMyInfo::GetInstance()->GetHeadimage())]];// m_image;
		headimageview.image = headimage;
	}
	else
		headimageview.image = [UIImage imageNamed:@"headbig"];
	
	CGFloat h = headimageview.image.size.height;
	CGFloat w = headimageview.image.size.width;
	CGFloat xoff = 10;
	CGFloat yoff = 20;
	headimageview.frame = CGRectMake(xoff, yoff, w, h);
	
	xoff += w+10;
	UILabel*fullname = [self GetLabel:[NSString stringWithUTF8String: CMMyInfo::GetInstance()->GetFullName()] textcolor:UIColorRGB(0x2e2e2e) fontsize:16];
	fullname.font = [UIFont boldSystemFontOfSize:18];
	fullname.frame = CGRectMake(xoff,yoff, f.size.width-xoff,20);
	if([fullname.text length] > 0)
		yoff += 20;
	UILabel*lbjobnumber = [self GetLabel:I(@"帐号:")
                               textcolor:UIColorRGB(0x7f7f7f) fontsize:14];
	UILabel*jobnumber = [self GetLabel:[NSString stringWithUTF8String: CMMyInfo::GetInstance()->GetJobnumber()] textcolor:UIColorRGB(0x595959) fontsize:14];
	lbjobnumber.frame = CGRectMake(xoff,yoff, 50, 20);
	jobnumber.frame = CGRectMake(xoff + 50, yoff, 80, 20);
	
	UILabel*lbdep = [self GetLabel:I(@"部门:")// @"部门："
                         textcolor:UIColorRGB(0x7f7f7f) fontsize:14];
	UILabel*dep = [self GetLabel:[NSString stringWithUTF8String: CMMyInfo::GetInstance()->GetDep()] textcolor:UIColorRGB(0x595959) fontsize:14];
	lbdep.frame = CGRectMake(xoff+130,yoff, 50, 20);
	dep.frame = CGRectMake(xoff + 180, yoff, 80, 20);
	
	yoff += 20;
	UILabel*lbcredit = [self GetLabel:I(@"学分")// @"学分："
                            textcolor:UIColorRGB(0x7f7f7f) fontsize:14];
	UILabel*credit = [self GetLabel:[NSString stringWithFormat:@"%d",CMMyInfo::GetInstance()->GetCredit()] textcolor:UIColorRGB(0x595959) fontsize:14];
	lbcredit.frame = CGRectMake(xoff,yoff, 50, 20);
	credit.frame = CGRectMake(xoff + 50, yoff, 80, 20);
	
	UILabel*lbvalue = [self GetLabel:I(@"积分:")// @"积分："
                           textcolor:UIColorRGB(0x7f7f7f) fontsize:15];
	UILabel*value = [self GetLabel:[NSString stringWithFormat:@"%d",CMMyInfo::GetInstance()->GetValue()]  textcolor:UIColorRGB(0x595959) fontsize:15];
	lbvalue.frame = CGRectMake(xoff+130,yoff, 50, 20);
	value.frame = CGRectMake(xoff + 180, yoff, 80, 20);
	
	yoff += 20;
	yoff += 20;
	f.size.height = yoff;
	headview.frame = f;
	
    
    
	[headview addSubview:headimageview];
	[headview addSubview:fullname];
	[headview addSubview:lbjobnumber];
	[headview addSubview:jobnumber];
	[headview addSubview:lbdep];
	[headview addSubview: dep];
	[headview addSubview:lbcredit];
	[headview addSubview:credit];
	[headview addSubview:lbvalue];
	[headview addSubview:value];
    CMRELEASE(headimageview);
	
	f = sepview.frame;
	f.origin.y = yoff;
	sepview.frame = f;
	f = answerview.frame;
	f.origin.y = yoff + 10;
	answerview.frame = f;
	[answerview layoutSubviews];
}
-(UILabel*)GetLabel:(NSString*)title textcolor: (UIColor*)textcolor fontsize:(int)size
{
#if !__has_feature(obj_arc)
	UILabel* lb = [[UILabel alloc] init];
#else
    UILabel* lb = [[UILabel alloc] init];
#endif
	lb.backgroundColor = [UIColor clearColor];
	lb.textAlignment = UITextAlignmentLeft;
	lb.font = [UIFont systemFontOfSize:size];
	lb.textColor = textcolor;
	lb.text = title;
	return lb;
}
-(void)gotoBack
{
	if(needrefresh)
		[[NSNotificationCenter defaultCenter] postNotificationName:@"questiondetailrefresh" object:nil userInfo:nil];
	[[self navigationController] popViewControllerAnimated:	YES];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    UIView *newBak=[[UIView alloc]initWithFrame:self.view.frame];
    [newBak setBackgroundColor:[UIColor whiteColor]];
    [self.view addSubview:newBak];
    CMRELEASE(newBak);
    
	CGRect f = self.view.bounds;
	
	headview = [[UIView alloc] init];
	//headview.backgroundColor = UIColorRGB(0xe9e9e9);
	
	sepview = [[UIView alloc] init];
	sepview.backgroundColor = UIColorRGB(0xcbcbcb);
	sepview.frame = CGRectMake(10, 0, f.size.width-20, 2);
	
	answerview = [[CMAnswerTableViewCell alloc] init];
	answerview.contentView.backgroundColor = [UIColor clearColor];
	if(answeritem.nAnswerflag == 1)
		answerview.LeftImageView.image = [UIImage imageNamed:@"bestanswer"];
	else 
		answerview.LeftImageView.image = [UIImage imageNamed:@"otheranswer"];

	
	NSString *cellText = [NSString stringWithUTF8String:answeritem.GetAnswerItemAnswer()];

	UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
	CGSize constraintSize = CGSizeMake(f.size.width-10-answerview.LeftImageView.image.size.width, MAXFLOAT);
	CGSize labelSize = [cellText sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeTailTruncation];
	int h = labelSize.height + 40;	
	
	answerview.frame = CGRectMake(5, 0, f.size.width-10, h);
	answerview.lbname.text = [NSString stringWithUTF8String:answeritem.GetAnswerItemFullName()];
	answerview.lbpubdate.text=[NSString stringWithUTF8String:answeritem.GetAnswerItemPubdate()];
	answerview.lblike.text = [NSString stringWithFormat:@"%d",answeritem.nPV];
	answerview.lbanswer.text = [NSString stringWithUTF8String:answeritem.GetAnswerItemAnswer()];
	
	m_pGetImageListener = new CMOneAnswerGetImageListener();
	m_pWebImage = new CMWebImage(m_pGetImageListener);
	m_pWebImage->SetUserData(BridgeObjectToC(self));

	[self updateView];

	
	[self.view addSubview:headview];
	[self.view addSubview:sepview];
	[self.view addSubview:answerview];
    CMRELEASE(headview);
    CMRELEASE(answerview);
	[self createTabbar];
    
}
-(void)gotolike
{
	if(!m_pOneAnswerRatingListener)
		m_pOneAnswerRatingListener = new CMOneAnswerRatingListener();
	if(!m_pQuestionDetail)
	{
		m_pQuestionDetail = new CMQuestionDetail(nil,nil,m_pOneAnswerRatingListener);
		m_pQuestionDetail->SetUserData(BridgeObjectToC(self));
	}
    
    [tool Wait];

    
	if(m_pQuestionDetail->LikeAnswer([questionid UTF8String], answeritem.GetAnswerItemID()))
		[tool CancelWait];
    
}
-(void)gotobest
{
	if(!m_pOneAnswerSimpleResultListener)
		m_pOneAnswerSimpleResultListener = new CMOneAnswerSimpleResultListener();
	if(!m_pQuestionDetail)
	{
		m_pQuestionDetail = new CMQuestionDetail(nil,m_pOneAnswerSimpleResultListener,nil);
		m_pQuestionDetail->SetUserData(BridgeObjectToC(self));
	}
    
    [tool Wait];

	if(!m_pQuestionDetail->SetBestAnswer([questionid UTF8String], answeritem.GetAnswerItemID()))
		[tool CancelWait];
}
-(void)createTabbar
{
	//CGRect frame = CGRectMake(0, self.view.frame.size.height-44-20, self.view.frame.size.width, 44);
    
    CGRect frame = CGRectMake(0, 300, self.view.frame.size.width, 44);

    
	UIView*tabbar = [[UIView alloc]initWithFrame:frame];
	tabbar.backgroundColor = [UIColor clearColor];
	tabbar.layer.contents = (id)[UIImage imageNamed:@"bottombk"].CGImage;
	
	frame.origin.y = 0;
	ComplexButton* btnlike = [[ComplexButton alloc] init];
	frame.origin.x = 50;
	frame.size.width = 80;
	btnlike.frame = frame;
	[btnlike addTarget:self action:@selector(gotolike) forControlEvents:UIControlEventTouchUpInside];
	[btnlike setTitle:I(@"喜欢")
             forState:UIControlStateNormal];
	[btnlike setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
	[btnlike setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateHighlighted];
	[btnlike setImage:[UIImage imageNamed:@"likeanswer_n"] forState:UIControlStateNormal];
	[btnlike setImage:[UIImage imageNamed:@"likeanswer_p"] forState:UIControlStateHighlighted];
	
	ComplexButton* btnbest = [[ComplexButton alloc] init];
	frame.origin.x = self.view.frame.size.width - 140;
	btnbest.frame = frame;
	[btnbest addTarget:self action:@selector(gotobest) forControlEvents:UIControlEventTouchUpInside];
	[btnbest setTitle:I(@"设置最佳答案成功")
             forState:UIControlStateNormal];
	[btnbest setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
	[btnbest setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateHighlighted];
	[btnbest setImage:[UIImage imageNamed:@"bestanswer_n"] forState:UIControlStateNormal];
	[btnbest setImage:[UIImage imageNamed:@"bestanswer_p"] forState:UIControlStateHighlighted];
	
	if(bestanswer || strcmp([questionusername UTF8String],SETTING.GetUserName()) != 0)
		btnbest.enabled = NO;
	[tabbar addSubview:btnlike];
	[tabbar addSubview:btnbest];
	[self.view addSubview:tabbar];
    CMRELEASE(btnbest);
    CMRELEASE(btnlike);
    CMRELEASE(tabbar);
}
- (void)dealloc {
	SAFEDELETE(m_pGetImageListener);
	SAFEDELETE(m_pWebImage);
	SAFEDELETE(m_pQuestionDetail);
	SAFEDELETE(m_pOneAnswerRatingListener);
	SAFEDELETE(m_pOneAnswerSimpleResultListener);	
    CMRELEASE(questionid);
    CMRELEASE(questionusername);
    
#if !__has_feature(obj_arc)
#endif
}

@end

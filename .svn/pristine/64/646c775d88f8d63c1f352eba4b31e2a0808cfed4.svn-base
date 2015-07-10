#include "stdafx.h"
#import "CMEditCommentControl.h"
#import <QuartzCore/QuartzCore.h>

@implementation CMEditCommentControl
@synthesize sflag,sid,sreplyid,type;

- (void)viewWillAppear:(BOOL)animated {
	[textcomment becomeFirstResponder];
	[super viewWillAppear:animated];
    
}
//-(void)sendcomment
//{
//    
//	if(!m_pComment)
//		return;
//    
//    //去除开头和结尾的空格
//    NSString *strComment = [textcomment.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
//    
//    //内容为空时 不允许提交评论和回复
//    if ([strComment isEqualToString:I(@"添加评论不超过200个字")]
//        || [strComment isEqualToString:I(@"回复评论不超过200个字")]
//        || [strComment isEqualToString:@""])
//    {
//        [tool ShowAlert:I(@"请输入评论内容!")];
//        return;
//    }
//    
//    if (isBeyond) {
//        [tool ShowAlert:words_Num.text];
//        return;
//    }
//	BOOL ret = NO;
//    [tool Wait];
//		ret = m_pComment->SendComment([sflag UTF8String], [sid UTF8String], [textcomment.text UTF8String], syncbtn.Check);
//	
//	if(ret)
//	{
//		[tool CancelWait];
//	}
//}
//
//- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
//{
//    if ([textcomment.text isEqualToString:@""])
//    {
//        [self SetPlaceholder];
//    }
//    [textcomment resignFirstResponder];
//}
//
//
//- (void)viewDidLoad
//{
//	[super viewDidLoad];
//    
//    
//    UIView *newBak=[[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT)];
//    [newBak setBackgroundColor:[UIColor whiteColor]];
//    [self.view addSubview:newBak];
//    [newBak release];
//    
//    
//    UIView* rightview = [[UIView alloc] init];
//	rightview.frame = CGRectMake(0, 0, 60, 44);
//	UIButton *commitBtn = [UIButton buttonWithType:UIButtonTypeCustom];
//	commitBtn.frame = CGRectMake(15, 0, 45, 44);
//	[commitBtn setTitle:I(@"发布") forState:UIControlStateNormal];
//	[commitBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
//	[commitBtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
//	[commitBtn addTarget:self action:@selector(sendcomment) forControlEvents:UIControlEventTouchUpInside];
//    
//	
//	UIImageView* vsep = [[UIImageView alloc] init];
//	vsep.image = [UIImage imageNamed:@"navsep"];
//	vsep.frame = CGRectMake(13, 0, 2, 44);
//    
//    
//    [rightview addSubview:commitBtn];
//    
//    [rightview addSubview:vsep];
//    
//    [vsep release];
//	UIBarButtonItem *rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:rightview];
//	self.navigationItem.rightBarButtonItem = rightBarButtonItem;
//	[rightview release];
//	[rightBarButtonItem release];
//    
//    
//    //	UIButton *commentBtn = [UIButton buttonWithType:UIButtonTypeCustom];
//    //	commentBtn.frame = CGRectMake(0, 0, 40, 44);
//    //	[commentBtn setImage:[UIImage imageNamed:@"发评论"] forState:UIControlStateNormal];
//    //	[commentBtn addTarget:self action:@selector(sendcomment) forControlEvents:UIControlEventTouchUpInside];
//    //
//    //	UIBarButtonItem *commentBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:commentBtn];
//    //	self.navigationItem.rightBarButtonItem = commentBarButtonItem;
//    //	[commentBarButtonItem release];
//    
//	CGRect f = self.view.bounds;
//	//question
//	int h = 20;
//	CGRect frame = CGRectMake(20, h,f.size.width-40,100);
//	textcomment = [[UITextView alloc] initWithFrame:frame];
//    textcomment.layer.borderColor = [UIColor grayColor].CGColor;
//    textcomment.layer.borderWidth = 1.0;
//    textcomment.layer.cornerRadius = 2.0;
//	textcomment.font = [UIFont systemFontOfSize:12.0];
//	textcomment.backgroundColor = [UIColor whiteColor];
//	//textcomment.autocorrectionType = UITextAutocorrectionTypeNo;
//	//textcomment.keyboardType = UIKeyboardTypeDefault;
//	textcomment.returnKeyType = UIReturnKeyDone;
//	//textFieldFeedback.clearButtonMode = UITextFieldViewModeWhileEditing;	// has a clear 'x' button to the right
//	textcomment.delegate = self;

//	//[self SetPlaceholder];
//    
//    words_Num = [[UILabel alloc]initWithFrame:CGRectMake(CGRectGetMaxX(textcomment.frame) - 130.0, CGRectGetMaxY(textcomment.frame) - 28.0, 125.0, 25.0)];
//    words_Num.backgroundColor = [UIColor clearColor];
//    words_Num.font = [UIFont systemFontOfSize:12.0];
//    words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
//    words_Num.text = @"还能输入200个字";
//    words_Num.textAlignment = UITextAlignmentRight;
//
//    
//	if(type == 2)
//	{
//		frame = CGRectMake(20, h+120, 120, 25.0);
//		syncbtn = [[CheckBoxButton alloc] initWithFrame:frame];
//		[syncbtn setTitle:I(@"同步提问到问答")];// @"同步提问到问答"
//		[self.view addSubview:syncbtn];
//	}
//	[self.view addSubview:textcomment];
//    [self.view addSubview:words_Num];
//	[words_Num release];
//    
//	if (m_pComment== NULL) {
//		m_pListener = new CMEditCommentSimpleResultListener();
//		m_pComment = new CMComment(nil,m_pListener,nil);
//		m_pComment->SetUserData(BridgeObjectToC(self));
//	}
//}
////
////-(void)gotorespond:(id)sender
////{
////	UIBarButtonItem*bar = (UIBarButtonItem*)sender;
////	if(bar.tag == 1)//设置分类
////	{
////		CMQaCategoryControl* qacategorycontrol = [[CMQaCategoryControl alloc] init];
////		qacategorycontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
////		qacategorycontrol.navigationController.navigationBarHidden = NO;
////		qacategorycontrol.tabBarController.tabBar.hidden = YES;
////		qacategorycontrol.hidesBottomBarWhenPushed = YES;
////		//qasearchcontrol.navigationController.delegate = self;
////		qacategorycontrol.view.backgroundColor = [UIColor clearColor];
////		qacategorycontrol.type = 2;
////		[self.navigationController pushViewController:qacategorycontrol animated:YES];
////		[qacategorycontrol release];
////	}
////	else if(bar.tag == 3)//悬赏
////	{
////		CMCreditControl* creditcontrol = [[CMCreditControl alloc] init];
////		creditcontrol.title = @"选择悬赏";
////		creditcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
////		creditcontrol.navigationController.navigationBarHidden = NO;
////		creditcontrol.tabBarController.tabBar.hidden = YES;
////		creditcontrol.hidesBottomBarWhenPushed = YES;
////		creditcontrol.view.backgroundColor = [UIColor clearColor];
////		[self.navigationController pushViewController:creditcontrol animated:YES];
////		[creditcontrol release];
////	}
////}
////-(void)commitquestion
////{
////	if([textquestion.text length] <= 0 || textquestion.tag == 1)
////	{
////		[tool ShowAlert:@"请输入问题."];
////		return;
////	}
////	[textquestion endEditing:YES];
////	if(!m_pListener)
////		m_pListener = new CMQuestionSimpleResultListener();
////	if(!m_pQalist)
////	{
////		m_pQalist = new CMQAList(nil,m_pListener);
////		m_pQalist->SetUserData(BridgeObjectToC(self));
////	}
////	const char* sc = (categoryid == nil)? "":[categoryid UTF8String];
////	if(m_pQalist->NewQuestion(sc,switchctrl.on,value,[textquestion.text UTF8String]))
////	{
////		[alert show];
////		[alert.indicatorView startAnimating];
////	}
////}
//- (void)viewDidUnload
//{
//	[super viewDidUnload];
//}
//- (BOOL)textViewShouldBeginEditing:(UITextView *)textView
//{
//	if(textcomment.tag == 1)
//	{
//		textcomment.text = @"";
//		textcomment.tag = 2;
//		textcomment.textColor = [UIColor blackColor];
//	}
//	return YES;
//}
//- (void)textViewDidChange:(UITextView *)textView
//{
//	input_words_num = [textView.text length];
//    if (input_words_num <= 200) {
//        NSUInteger Remaining_words = 200 - input_words_num;
//        words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
//        isBeyond = NO;
//        words_Num.text = [NSString stringWithFormat:@"还能输入%d个字",Remaining_words];
//    }
//    else{
//        NSUInteger Beyond_words = input_words_num - 200;
//        words_Num.textColor = [UIColor redColor];
//        isBeyond = YES;
//        words_Num.text = [NSString stringWithFormat:@"超出%d个字",Beyond_words];
//    }
//}
//-(void)SetPlaceholder
//{
//    
//	textcomment.textColor = [UIColor lightGrayColor];
//	if(type == 2)
//		textcomment.text = I(@"添加评论不超过200个字");// @"添加评论不超过140个字";
//	else
//		textcomment.text = I(@"回复评论不超过200个字");// @"回复评论不超过140个字";
//	textcomment.tag = 1;
//}
//- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
//{
//	if([text isEqualToString:@"\n"])
//	{
//		[textcomment endEditing:YES];
//		if(textcomment.text.length == 0)
//			[self SetPlaceholder];
//		return NO;
//	}
////	if(range.location >= 140)
////		return NO;
//    //	if([textView.text length] == 1 && range.length == 1 && [text length] == 0)
//    //	{
//    //		[self SetPlaceholder];
//    //		[textcomment resignFirstResponder];
//    //	}
//    //	else if(textcomment.tag == 1)
//    //	{
//    //		textcomment.text = @"";
//    //		textcomment.tag = 2;
//    //		textcomment.textColor = [UIColor blackColor];
//    //	}
//    
//	return YES;
//}
//- (void)dealloc
//{
//	[textcomment release];
//	[syncbtn release];
//	SAFEDELETE(m_pListener);
//	SAFEDELETE(m_pComment);
//	[super dealloc];
//}
@end
//
//  CMBrowserInfoControl.m
//  MLPlayer
//
//  课程详情
//
//  Created by sunjj on 11-5-12.
//  Copyright 2011 w. All rights reserved.
//
#import "stdafx.h"
#import "CMNewsInfoControl.h"
#include "cmgeneral.h"
//#import "MobClick.h"
#import "CMPlayerControl.h"
#import "CMCommentReplyControl.h"
#import "CMCourseDetailControl.h"
#include "cmpath.h"
#import "CMPracticeControl.h"
#import "CMExamControl.h"
#import "CMIntrodocutionViewController.h"
#import "CMQuestionDetailControl.h"
#import "cmsettings.h"
#import "CMInteractViewController.h"

#define kCellIdentifier @"com.apple.CMClassCommentControl.CellIdentifier"

static const int  kChatInputTextViewMaxHeight  = __iOS7 ? 59 : 68;//输入框最大高度
static const int  kChatInputTextViewMinHeight  = __iOS7 ? 29 : 32;//输入框最小高度
#define kChatInputViewHeight 45

#define kLestCellHeight 50
#define kInputViewHeight 45

@implementation CMNewsInfoControl

//@synthesize webView;
@synthesize backView;
@synthesize bottomView;
@synthesize sflag,classid,coursewareid;
@synthesize israted,pv,pubdate;
@synthesize commentlist;
@synthesize likebtn;
@synthesize CommentCountBtn;
@synthesize CommentCountLb;
@synthesize isLiked;

@synthesize m_sUrl;
@synthesize inputView;
@synthesize webView;

-(id)init
{    
        self = [super init];
        if (self) {
            
            isLiked=NO;
            ;
        }
        return self;    
}

-(id)initWithOrientation:(NSString *)orientation
{
    
    NSAssert(orientation != nil, @"Argument must be non-nil");
    
    sOrientation = [[NSString alloc] initWithString:orientation];
    
    if ([sOrientation isEqualToString:@"L"]) {
        
        return [self initWithNibName:@"CMNewsInfoControl_L" bundle: nil];
        
    }
    else{
        self = [super init];
        if (self) {
            ;
        }
        return self;
        
    }
    
}


#pragma mark - Orientation

//-(void)setOrientationFrom:(UIInterfaceOrientation) orienFr To:(UIInterfaceOrientation) orienTo {
//    //	UIDeviceOrientation curOrientation = [UIDevice currentDevice].orientation;
//	CGRect bounds = [[UIScreen mainScreen] bounds];
//	CGAffineTransform t;
//	CGFloat r = 0;
//	if (orienFr == UIInterfaceOrientationPortrait) {
//		switch (orienTo) {
//			case UIInterfaceOrientationLandscapeLeft:
//				r = -(M_PI / 2);
//				break;
//			case UIInterfaceOrientationLandscapeRight:
//				r = (M_PI / 2);
//				break;
//			default:
//				break;
//		}
//	}
//	else if (orienFr == UIInterfaceOrientationLandscapeRight){
//		switch (orienTo) {
//			case UIInterfaceOrientationPortrait:
//				r = -(M_PI / 2);
//				break;
//			case UIInterfaceOrientationLandscapeLeft:
//				r = M_PI;
//				break;
//			default:
//				break;
//		}
//	}
//	else {//UIInterfaceOrientationLandscapeLeft
//		switch (orienTo) {
//			case UIInterfaceOrientationPortrait:
//				r = (M_PI / 2);
//				break;
//			case UIInterfaceOrientationLandscapeRight:
//				r = M_PI;
//				break;
//			default:
//				break;
//		}
//	}
//	
//	
//	if (r != 0 && r!= M_PI) {
//		CGSize sz = bounds.size;
//		bounds.size.width = sz.height;
//		bounds.size.height =sz.width;
//	}
//	
//	t = CGAffineTransformMakeRotation(r);
//	
//	UIApplication * application = [UIApplication sharedApplication];
//	
//	[UIView beginAnimations:@"InterfaceOrientation" context:nil];
//	[UIView setAnimationDuration:[application statusBarOrientationAnimationDuration]];
//	self.view.transform = t;
//	self.view.bounds = bounds;
//	self.view.center = CGPointMake(UI_IOS_WINDOW_WIDTH/2, UI_IOS_WINDOW_HEIGHT/2);
//	[UIView commitAnimations];
//	[application setStatusBarOrientation:orienTo animated:YES];
//}

//- (BOOL)shouldAutorotate{
//    return NO;
//}

//-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
//	
//	if(toInterfaceOrientation == UIInterfaceOrientationLandscapeRight){
//		return YES;
//	}
//	else
//		return NO;
//}

-(void)gotoCommentList
{
    [self dismissKeyboard];
    
# if ! __has_feature(objc_arc)
	CMInfoCommentControl* InfoCommentControl = [[[CMInfoCommentControl alloc] init] autorelease];
# else
    CMInfoCommentControl* InfoCommentControl = [[CMInfoCommentControl alloc] init];
# endif
    
	if(strcmp(m_CourseInfo->sFlag, "course") == 0)
    {
        [InfoCommentControl setCourseID:[classid UTF8String] type:@"course"];
    }
	else
		[InfoCommentControl setCourseID:m_CourseInfo->sID type:@"news"];
    
	InfoCommentControl.title = [NSString stringWithUTF8String:m_CourseInfo->sTitle];
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@"1" forKey:@"CommentReplyAdd"];

    
    [InfoCommentControl setBrowserItem:*m_CourseInfo];

	InfoCommentControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
	InfoCommentControl.navigationController.navigationBarHidden = NO;
	InfoCommentControl.tabBarController.tabBar.hidden = YES;
	InfoCommentControl.hidesBottomBarWhenPushed = YES;
    
    InfoCommentControl.classID=classid;
    InfoCommentControl.coursewareID=coursewareid;
    InfoCommentControl.cannotComment = !m_CourseInfo->bEnablecomment;
	InfoCommentControl.view.backgroundColor = [UIColor clearColor];
	[self.navigationController pushViewController:InfoCommentControl animated:YES];
}

#pragma mark -InputView

-(UIView*)createInputView
{
    commentListHeight=0;
    
    CGRect f = CGRectMake(0, 0, UI_IOS_WINDOW_HEIGHT, UI_IOS_WINDOW_WIDTH);
    //底
    UIImageView* inputBack=[[UIImageView alloc]initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-45-20, UI_IOS_WINDOW_WIDTH, kInputViewHeight)];
    UIImage *replyImage = [UIImage imageNamed:@"replyInput"];
    replyImage = [replyImage resizableImageWithCapInsets:UIEdgeInsetsMake(6, 35, 6, 150)];
    //[inputBack setImage:replyImage];
    [inputBack setBackgroundColor:[UIColor colorWithRed:241/255.0 green:241/255.0 blue:241/255.0 alpha:1]];
    if ([sOrientation isEqualToString:@"L"]) {
        [inputBack setFrame:CGRectMake(0, f.size.height - 45, f.size.width, 45)];
    }
    else{
        [inputBack setFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-20-45-44, UI_IOS_WINDOW_WIDTH, 45)];
    }
    [inputBack setUserInteractionEnabled:YES];
    inputBack.layer.shadowColor=[UIColor grayColor].CGColor;
	inputBack.layer.shadowOffset=CGSizeMake(0,-1);
	inputBack.layer.shadowOpacity=0.4;
    
//    //输入框
//    inputField=[[UITextField alloc]initWithFrame:CGRectMake(10, 10,235, 25)];
//    if ([sOrientation isEqualToString:@"L"]) {
//        [inputField setFrame:CGRectMake(10, 10,f.size.width - 85, 25)];
//    }
//    [inputField setBackgroundColor:[UIColor clearColor]];
//    inputField.font = [UIFont systemFontOfSize:17.0];
//    
//    [inputBack addSubview:inputField];
    
    
    //输入框
    
    inputField=[[FLXFluidTextView alloc]initWithFrame:CGRectMake(10, 8, 235, 29)];
    
    inputField.autoresizingMask = UIViewAutoresizingFlexibleHeight;
    inputField.delegate = self;
    //    [self.inputTextView addTarget:self action:@selector(inputTextViewReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    //    [self.inputTextView addTarget:self action:@selector(inputTextViewBeginEdit:) forControlEvents:UIControlEventEditingDidBegin];
    inputField.backgroundColor = [UIColor whiteColor];
    inputField.font = [UIFont systemFontOfSize:15.0];
    inputField.textAlignment = UITextAlignmentLeft;
    inputField.returnKeyType = UIReturnKeyDone;
    inputField.maximumNumberOfLines = 3;
    inputField.minimumNumberOfLines = 1;
    
    if ([inputField respondsToSelector:@selector(setTextContainerInset:)]) {
        inputField.textContainerInset = UIEdgeInsetsMake(5.f, 0.f, 5.0f, 0.f);
    }else{
        inputField.contentInset = UIEdgeInsetsMake(5.f, 0.f, 5.0f, 0.f);
    }
    
    inputField.layer.borderColor = UIColorRGB(0x858585).CGColor;
    inputField.layer.borderWidth = 0.5f;
    inputField.layer.masksToBounds = YES;
    inputField.layer.cornerRadius = 3.0f;
    
    [inputBack addSubview:inputField];
    //[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(textviewdidChange:) name:FLXFluidTextViewHeightConstraintDidChangeNotification object:nil];

    
    
    //发送按钮
    UIButton *commitBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    
    if ([sOrientation isEqualToString:@"L"]) {
        [commitBtn setFrame:CGRectMake(f.size.width - 65, 8, 55, 29)];
    }
    else{
        [commitBtn setFrame:CGRectMake(255, 8, 55, 29)];
    }
    [commitBtn setBackgroundImage:[UIImage imageNamed:@"sendreply_btn_nor"] forState:UIControlStateNormal];
    [commitBtn setBackgroundImage:[UIImage imageNamed:@"sendreply_btn_sel"] forState:UIControlStateHighlighted];
    
    [commitBtn setBackgroundImage:[UIImage imageNamed:@"sendreply_btn_dis"] forState:UIControlStateDisabled];
    
    [commitBtn addTarget:self action:@selector(sendcomment) forControlEvents:UIControlEventTouchUpInside];
    //    [commitBtn setTitle:I(@"发送") forState:UIControlStateNormal];
    
    [commitBtn setAdjustsImageWhenHighlighted:NO];
    [commitBtn setAdjustsImageWhenDisabled:NO];
    
    
    //加上"发送"文字说明
    UILabel *lbl_Send = [[UILabel alloc]init];
    
    CGSize size_Send =[I(@"发送") sizeWithFont:[UIFont boldSystemFontOfSize:16] constrainedToSize:CGSizeMake(NSIntegerMax, commitBtn.frame.size.height) lineBreakMode:NSLineBreakByTruncatingTail];
    [lbl_Send setText:I(@"发送")];
    [lbl_Send setFont:[UIFont boldSystemFontOfSize:16]];
    [lbl_Send setTextColor:[UIColor whiteColor]];
    [lbl_Send setBackgroundColor:[UIColor clearColor]];
    
    [lbl_Send setFrame:CGRectMake(0, 0, size_Send.width, size_Send.height)];
    [lbl_Send setCenter:CGPointMake(commitBtn.frame.size.width/2, commitBtn.frame.size.height/2)];
    [commitBtn addSubview:lbl_Send];
    
    
    [inputBack addSubview:commitBtn];
# if ! __has_feature(objc_arc)
    
    return [inputBack autorelease];
    
#else
    return inputBack;
    
#endif
}



-(void)sendcomment
{
    if(!m_pComment)
		return;
    
    if(CMGlobal::TheOne().IsOffline()){
        [tool ShowError:-1];
        return;
    }
    
    //去除开头和结尾的空格
    NSString *strComment = [inputField.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
    //内容为空时 不允许提交评论和回复
    if ([strComment isEqualToString:I(@"添加评论不超过200个字")]
        || [strComment isEqualToString:I(@"回复评论不超过200个字")]
        || [strComment isEqualToString:@""])
    {
        [tool ShowAlert:I(@"请输入评论内容!")];
        return;
    }
    if ([inputField.text length] > kTextMaxLength) {
        NSString *beyond_str = [NSString stringWithFormat:I(@"超出%d个字"),[inputField.text length] - kTextMaxLength];
        [tool ShowAlert:beyond_str];
        return;
    }
    
    BOOL ret = NO;
    
    if(m_CourseInfo == NULL)
        return;
    
    if(m_pUpdateDataListener == NULL)
        m_pUpdateDataListener = new CMNewsInfoUpdateDataListener();

    m_CourseInfo->SetListener(m_pUpdateDataListener, NULL, NULL);
    m_CourseInfo->SetUserData((__bridge void*)self);
    
    ret = m_CourseInfo->SendComment([inputField.text UTF8String],false);
    
    if(ret)
    {
        [self dismissKeyboard];
        inputField.text=@"";
        [inputView setFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-45-20-44, UI_IOS_WINDOW_WIDTH, 45)];
        
    }else
    {
        
    }
}

- (void)keyboardWillHide:(NSNotification *)aNotification{
    
    backBtn.hidden=YES;
    
    
    
    if(inputField.isFirstResponder)
    {
        //点击背后按钮
        inputView.hidden = YES;
    }
    
    [inputField resignFirstResponder];
    
    
    if(self.willShowInputView)
        [self moveViewToYIn:0.3 yCoordinate:UI_IOS_WINDOW_HEIGHT target:inputView];
    
    self.willShowInputView = NO;
}



- (void)keyboardWillShow:(NSNotification *)aNotification {
    
    
    if(self.willShowInputView)
    {
        NSDictionary* info=[aNotification userInfo];
        
        CGSize kbSize=[[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;
        
        keyBoardHieght = kbSize.height;

        if ([sOrientation isEqualToString:@"L"]) {
            [self moveViewToYIn:0.3 yCoordinate:self.view.bounds.size.height-inputView.frame.size.height-kbSize.width target:inputView];
        }
        else{
            [self moveViewToYIn:0.3 yCoordinate:UI_IOS_WINDOW_HEIGHT-20-44-inputView.frame.size.height-kbSize.height target:inputView];
        }
    }


}


-(void)moveViewToYIn:(CGFloat)seconds yCoordinate:(CGFloat)y target:(UIView*)view
{
    if(!view)
        return;
    __block typeof(self) bself= self;
    
	[UIView animateWithDuration:0.25
					 animations:^{
                         
                         [bself slideViewToY:view yCoordinate:y];
					 }
                     completion:^(BOOL finished){
					 }];
    
}
-(void)slideViewToY:(UIView*)v yCoordinate:(CGFloat)y
{
	CGRect navframe=v.frame;
	navframe.origin.y=y;
	v.frame=navframe;
    
}


-(void)showInput
{
    if(inputView.isHidden)
    {
        
        self.willShowInputView = YES;
        
        inputView.hidden=NO;
      
        [inputField becomeFirstResponder];
        
        backBtn.hidden=NO;
    }else
    {
        
        backBtn.hidden=YES;
        inputView.hidden=YES;
        
        [inputField resignFirstResponder];
        

    }
}





-(void)doComment:(id)sender event:(id)event
{
    
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
    CGPoint point= [touch locationInView:commentlist];
    
    NSInteger row=[commentlist indexPathForRowAtPoint:point].row;
    
    
    selectedIndex=row;
    
    [self gotoComment];

}

- (void)gotoComment{
    TCommentItem* item =new TCommentItem() ;
    if(!m_pComment->GetItem(selectedIndex, *item))
        return;
    
    //进入回复页面
    CMCommentReplyControl* CommentReplyControl = [[CMCommentReplyControl alloc] init] ;
    CommentReplyControl.type = 1;
    CommentReplyControl.title = I(@"回复");
    
    CommentReplyControl.classid=classid;
    CommentReplyControl.coursewareid=coursewareid;
    CommentReplyControl.sreplyid = [NSString stringWithUTF8String:item->sID];
    SAFEDELETE(item);
    
    CommentReplyControl.sflag = [NSString stringWithUTF8String:m_CourseInfo->sFlag];
    CommentReplyControl.sid = classid;
    CommentReplyControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
    CommentReplyControl.navigationController.navigationBarHidden = NO;
    CommentReplyControl.tabBarController.tabBar.hidden = YES;
    CommentReplyControl.hidesBottomBarWhenPushed = YES;
    CommentReplyControl.commentIndex=selectedIndex;
    CommentReplyControl->m_pComment=m_pComment;
    //qasearchcontrol.navigationController.delegate = self;
    //	CommentReplyControl.view.backgroundColor = [UIColor clearColor];
    [self.navigationController pushViewController:CommentReplyControl animated:YES];
    CMRELEASE(CommentReplyControl);
}

-(void)gotoShare
{
	CMInteractViewController *shareController = [[CMInteractViewController alloc]initWithTBrowserItem:m_CourseInfo];
    UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:shareController];
    [self presentModalViewController:navigationController animated:YES];
    CMRELEASE(navigationController);
    CMRELEASE(shareController);
}

-(void)dolikeCourseware
{
    if(isLiked)
        return;
    
    isLiked = YES;
    
    if(m_pRatingListener==NULL)
        m_pRatingListener= new CMNewsInfoRatingListener();
    
    m_CourseInfo->SetListener(NULL, m_pRatingListener, NULL);
    m_CourseInfo->SetUserData((__bridge void*)self);
    
    if([sflag isEqualToString:@"news"])
    {
        if(!m_CourseInfo->Rating())
        {
            [tool ShowAlert:I(@"喜欢失败")];
        }
        
    }
    else
    {
        if(!m_CourseInfo->RatingCourseinfo())
        {
            [tool ShowAlert:I(@"喜欢失败")];
        }
    }


}


-(void)doLike:(id)sender event:(id)event
{
    if(CMGlobal::TheOne().IsOffline())
        return;
    
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
    CGPoint point= [touch locationInView:commentlist];
    
    UIButton* btn=(UIButton*)sender;
    
    if(btn.selected)
        return;
    
    [btn setSelected:YES];
    
  //  [qa_ChoiceList changeImageAtIndex:2 AtView:self.navigationController.view To:[UIImage imageNamed:@"newslike_sel"]];
    
    NSInteger row=[commentlist indexPathForRowAtPoint:point].row;
    
    CMCommentTableViewCell*cell=(CMCommentTableViewCell*)[commentlist cellForRowAtIndexPath:[NSIndexPath indexPathForRow:row inSection:0]];
    
    UILabel* pvlabel=((UILabel*)[cell viewWithTag:kLblPvTag]);
    
    NSInteger tempInt=[pvlabel.text integerValue];
    
    tempInt += 1;
    
    [pvlabel setText:[NSString stringWithFormat:@"%ld",tempInt]];
    
    TCommentItem *Item= new TCommentItem();
    if(!m_pComment || !m_pComment->GetItem(row, *Item))
        return;
    
    
    if(Item->bIsLiked)
        return;
    
    
    if(!m_pComment->CommentLike(m_CourseInfo->sFlag,[classid UTF8String],[coursewareid UTF8String],Item->sID))
    {
    }
    SAFEDELETE(Item);
}


- (BOOL)textField:(UITextField *)textField shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    if ([textField.text length] < 140) {//判断字符个数
        return YES;
    }  
	
    return NO;
}

- (IBAction)tappedMe:(id)sender {
		
	if ([txtcomment.text length] <= 0) {
		
		[tool ShowAlert:I(@"评论内容不能为空!")];
		
	}else {
		if (m_pComment== NULL) {
			m_pUpdateDataListener = new CMNewsInfoUpdateDataListener();
			m_pSimpleResultListener = new CMNewsSimpleResultListener();
			
            m_pComment = new CMComment();

			m_pComment->SetUserData((__bridge void*)self);
			
		}
				
		if (![txtcomment.text isEqualToString: @""])
		{			
			
			if (strcmp(m_CourseInfo->sFlag, "course") == 0) {
				NSString *strComment = @"course";

				m_pComment->SendComment([strComment UTF8String], m_CourseInfo->sID,nil, [txtcomment.text UTF8String],false);

			}else {
				NSString *strComment = @"news";

				m_pComment->SendComment([strComment UTF8String], m_CourseInfo->sID,nil, [txtcomment.text UTF8String],false);
			}

		}
		else {
			[tool ShowAlert:I(@"评论内容不能为空!")];
		}
		txtcomment.text = @"";
		[txtcomment becomeFirstResponder];
		[txtcomment resignFirstResponder];
	}
}

-(void)loadTableList
{ 
		//[TableViewList reloadData];
}

	//1 course 0 news
-(void)setInfo:(TBrowserItem&)item url:(NSString*)url
{
	if (m_CourseInfo == nil)
    {
        if (item.nModel == 0) {
            m_CourseInfo = new TBrowserItem();
            *m_CourseInfo = (TBrowserItem&)item;
        }
        else{
            m_CourseInfo = new TCoursewareItem();
            *m_CourseInfo = (TCoursewareItem&)item;
        }
        
        isLiked=m_CourseInfo->bIsRated;
        self.m_sUrl = url;
	}
}

- (void) viewWillAppear:(BOOL)animated {

    [[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(keyboardWillShow:)
												 name:UIKeyboardWillShowNotification object:nil];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(dismissKeyboard)
												 name:UIKeyboardWillHideNotification object:nil];
    
//    [webView.scrollView addObserver:self forKeyPath:@"contentSize" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:nil];//监控webview高度改变

   // [MobClick beginEvent:@"NewsDetail"];

    if (strcmp(m_CourseInfo->sFlag, "news")==0 && m_CourseInfo->bEnablecomment) {
        [self displayCommentCount];
        CommentCountBtn.hidden = NO;
        CommentCountLb.hidden = NO;
    }
    
	[super viewWillAppear:animated];
    
    if ([sOrientation isEqualToString:@"L"])
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
        [self.navigationController setNavigationBarHidden:YES animated:NO];
    //    [self setOrientationFrom:UIInterfaceOrientationPortrait To:UIInterfaceOrientationLandscapeRight];
    }
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self dismissKeyboard];

    
    //[MobClick endEvent:@"NewsDetail"];
    
    
    CommentCountBtn.hidden = YES;
    CommentCountLb.hidden = YES;
    
    [super viewWillDisappear:animated];
    
    
    if ([sOrientation isEqualToString:@"L"])
    {
     //   [self setOrientationFrom:UIInterfaceOrientationLandscapeRight To:UIInterfaceOrientationPortrait];
        
        [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:UIStatusBarAnimationNone];
        
        [self.navigationController setNavigationBarHidden:NO animated:NO];
        
    }
}


-(void)textViewDidChange:(UITextView *)textView
{
    
    if (textView.contentSize.height != inputField.frame.size.height ) {
        if (![self keyBoardHide]) {
            
            [UIView animateWithDuration:.3f animations:^{
                CGFloat iheight=textView.contentSize.height;
                
                
                if (iheight > kChatInputTextViewMaxHeight) {
                    iheight = kChatInputTextViewMaxHeight;
                    
                }
                
                
                //文字输入，键盘高度;中文键盘keyBoardHieght =252
                [inputView setFrameY:UI_IOS_WINDOW_HEIGHT- 20 - kChatInputViewHeight - 44 - keyBoardHieght - (iheight - kChatInputTextViewMinHeight) Height:kChatInputViewHeight + (iheight - kChatInputTextViewMinHeight)];
                
                
            }];
        }
    }
}


- (void)textviewdidChange:(NSNotification *)aNotification{
    
    FLXFluidTextView *textview = (FLXFluidTextView *)aNotification.object;
    
    if (backBtn.hidden==NO) {
        
        [UIView animateWithDuration:.3f animations:^{
            CGFloat iheight=textview.contentSize.height;
            //            //解决ios7下contentsize.height计算不准确的问题
            //            if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7) {
            //
            //                CGRect textFrame=[[textview layoutManager]usedRectForTextContainer:[textview textContainer]];
            //                iheight = textFrame.size.height;
            //
            //            }else {
            //
            //                iheight = textview.contentSize.height;
            //            }
            
            
            if (iheight > kChatInputTextViewMaxHeight) {
                iheight = kChatInputTextViewMaxHeight;
                
            }
            
            
            //文字输入，键盘高度;中文键盘keyBoardHieght =252
            [inputView setFrameY:UI_IOS_WINDOW_HEIGHT- 20 - kChatInputViewHeight - 44 - keyBoardHieght - (iheight - kChatInputTextViewMinHeight) Height:kChatInputViewHeight + (iheight - kChatInputTextViewMinHeight)];
            
            
        }];
    }
}

#pragma mark -Show List Action
- (void)showChoiceList:(UIButton *)sender{
    
    if(strcmp(m_CourseInfo->sFlag, "news")==0)
    {
      
        [self showInput];
        return;

    }
        
//    NSArray *menuItems=
//    @[
//      [qa_ChoiceListItem menuItem:I(@"发表评论")
//                            image:[UIImage imageNamed:@"learn_postcomment"]
//                           target:self
//                           action:[sOrientation isEqualToString:@"L"] ? @selector(gotoCommentList) : @selector(showInput)],
//      
//      [qa_ChoiceListItem menuItem:I(@"加入收藏")
//                            image:[UIImage imageNamed:@"learn_addfavorites"]
//                           target:self
//                           action:@selector(MyFavoriteFun)],
//      
//      [qa_ChoiceListItem menuItem:I(@"喜欢")
//                            image:[UIImage imageNamed:(isLiked ? @"newslike_sel" : @"play_like")]
//                           target:self
//                           action:@selector(dolikeCourseware)],
//      [qa_ChoiceListItem menuItem:I(@"分享")
//                            image:[UIImage imageNamed:@"share_p"]
//                           target:self
//                           action:@selector(gotoShare)]
//      ];
    NSMutableArray *menuItems = [[NSMutableArray alloc]init];
    
    if (m_CourseInfo->bEnablecomment) {
        [menuItems addObject:[qa_ChoiceListItem menuItem:I(@"发表评论")
                                                   image:[UIImage imageNamed:@"learn_postcomment"]
                                                  target:self
                                                  action:[sOrientation isEqualToString:@"L"] ? @selector(gotoCommentList) : @selector(showInput)]];
    }
    [menuItems addObject:[qa_ChoiceListItem menuItem:I(@"加入收藏")
                                               image:[UIImage imageNamed:@"learn_addfavorites"]
                                              target:self
                                              action:@selector(MyFavoriteFun)]];
    if (m_CourseInfo->bEnablerating) {
        [menuItems addObject:[qa_ChoiceListItem menuItem:I(@"喜欢")
                                                   image:[UIImage imageNamed:(isLiked ? @"newslike_sel" : @"play_like")]
                                                  target:self
                                                  action:@selector(dolikeCourseware)]];
    }
    [menuItems addObject:[qa_ChoiceListItem menuItem:I(@"分享")
                                               image:[UIImage imageNamed:@"share_p"]
                                              target:self
                                              action:@selector(gotoShare)]];
    
    NSMutableArray *realMenuItems =[NSMutableArray arrayWithArray:menuItems];
    if ( NOShareInteract ) {
        [realMenuItems removeObjectAtIndex:realMenuItems.count - 1];
    }
    
    CGRect frame;
    if ([sOrientation isEqualToString:@"L"])
    {
        frame = CGRectMake(195, UI_IOS_WINDOW_HEIGHT - 20, 30, 62.0);
    }
    else{
        frame = CGRectMake(280.0, 0.0, 30, 62.0);
    }
    [qa_ChoiceList showMenuInView:self.navigationController.view
                         fromRect:frame
                        menuItems:[NSArray arrayWithArray:realMenuItems]
                        transform:self.view.transform];

}

-(void)displayCommentCount
{
    if ( !m_CourseInfo->bEnablecomment )
    {
    
        return;
    }
    //算出label大小
    NSString* countStr=[NSString stringWithFormat:@"%d%@",m_CourseInfo->nCommentcount , I(@"评论")];
//    NSString* countStr=[NSString stringWithFormat:@"11111%@", I(@"评论")];

    
    CGSize labelSize=[countStr sizeWithFont:[UIFont systemFontOfSize:12] ];

    if ([sOrientation isEqualToString:@"L"]){
        self.CommentCountBtn = [[UIButton alloc] initWithFrame:CGRectMake(UI_IOS_WINDOW_HEIGHT-50-(labelSize.width+12),12, labelSize.width+12, 22)] ;
    }
    else{
        self.CommentCountBtn = [[UIButton alloc] initWithFrame:CGRectMake(UI_IOS_WINDOW_WIDTH-50-(labelSize.width+12),12, labelSize.width+12, 22)] ;
    }
    
//    UIImage *CourewareCountImg =[UIImage imageNamed:@"CooursewareCommentCount"];
//    
//    CourewareCountImg=[CourewareCountImg resizableImageWithCapInsets:UIEdgeInsetsMake(0, 4, 0, 2)];
    
    [CommentCountBtn setBackgroundImage:[UIImage imageNamed:@"CooursewareCommentCount"] forState:UIControlStateNormal];
    
#if !__has_feature(obj_arc)

    self.CommentCountLb = [[UILabel alloc]initWithFrame:CGRectMake(4, 1, labelSize.width  , labelSize.height)];
#else
    self.CommentCountLb = [[UILabel alloc]initWithFrame:CGRectMake(4, 1, labelSize.width  , labelSize.height)];

#endif
    
    [CommentCountLb setText:countStr];
    
    [CommentCountLb setFont:[UIFont systemFontOfSize:12]];
    
    [CommentCountLb setTextAlignment:NSTextAlignmentCenter];
    
    [CommentCountLb setTextColor:[UIColor colorWithRed:82.0/255.0f green:131/255.0f blue:188/255.0f alpha:1]];
    
    [CommentCountBtn addSubview:CommentCountLb];
    
    [CommentCountBtn addTarget:self action:@selector(gotoCommentList) forControlEvents:UIControlEventTouchUpInside];
    
    if (![sOrientation isEqualToString:@"L"]) {
        
        [self.navigationController.navigationBar addSubview:CommentCountBtn];
    }
    else{
        [self.titleBar addSubview:CommentCountBtn];
    }
}
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    UITouch *touch = [touches anyObject];
    
    
}
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    
}
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    
}
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    
}

- (void)setNavigationBarCustom{
    //自定义navigationBar
    
    self.titleBar = [[UINavigationBar alloc] initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_HEIGHT, 44)];
    
    float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    
    if (version >= 5.0)
    {
        if (version >= 7.0)
        {
            [self.titleBar setBackgroundImage:[UIImage imageNamed:@"background"] forBarPosition:UIBarPositionTopAttached barMetrics:UIBarMetricsDefault];
        }
        else
        {
            [self.titleBar setBackgroundImage:[UIImage imageNamed:@"NaviBg"] forBarMetrics:UIBarMetricsDefault];
        }
        //self.backgroundColor=[UIColor colorWithPatternImage:[UIImage imageNamed:@"NaviBg"]];
        
    }else{
        
        self.titleBar.layer.contents=(id)[UIImage imageNamed:@"NaviBg"].CGImage;
    }
    [self.view addSubview:self.titleBar];
    self.view.transform = CGAffineTransformMakeRotation(M_PI / 2);

    self.titleItem = [[UINavigationItem alloc] initWithTitle:[NSString stringWithUTF8String:m_CourseInfo->sTitle]];
    
    [self.titleBar setItems:[NSArray arrayWithObjects:self.titleItem, nil]];
    
    UIButton *_backBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    _backBtn.frame = CGRectMake(0, 0, 40, 44);
    [_backBtn setImage:[UIImage imageNamed:@"back"] forState:UIControlStateNormal];
    [_backBtn addTarget:self action:@selector(gotoBack) forControlEvents:UIControlEventTouchUpInside];
    _backBtn.imageEdgeInsets = [self itemFitDifferentVersion:YES];
    
    UIBarButtonItem *backBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:_backBtn];
    self.titleItem.leftBarButtonItem = backBarButtonItem;
    CMRELEASE(backBarButtonItem);
    
    
    [self.titleBar setTitleTextAttributes:[NSDictionary dictionaryWithObjectsAndKeys:
                                           [UIColor whiteColor], UITextAttributeTextColor,
                                           [UIColor whiteColor], UITextAttributeTextShadowColor,
                                           [NSValue valueWithUIOffset:UIOffsetMake(0, 0)], UITextAttributeTextShadowOffset,
                                           [UIFont systemFontOfSize:20], UITextAttributeFont,
                                           nil]];
    
    
    UITapGestureRecognizer* singleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleSingleTap:)];
    singleTap.numberOfTapsRequired = 1;
    [self.webView addGestureRecognizer:singleTap];
    singleTap.delegate = self;
    singleTap.cancelsTouchesInView = NO;
    
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}

- (void)handleSingleTap:(UITapGestureRecognizer *)gesture
{
    self.titleBar.hidden = !self.titleBar.hidden;
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {

    [super viewDidLoad];
    
    self.openAutoKeyboard = YES;
    
    self.title=@"";
    
    m_CourseInfo->Refresh();
    isLiked=m_CourseInfo->bIsRated;
    
    isRespondToObserver = NO;
    if (!m_pWebImage) {
        m_pWebImage = new CMWebImage(m_pGetImageListener);
        m_pWebImage->SetUserData((__bridge void*)self);
    }
    
    if(m_pSimpleResultListener==NULL)
        m_pSimpleResultListener= new CMNewsSimpleResultListener();
    
    if (m_pComment== NULL) {
        m_pUpdateDataListener = new CMNewsInfoUpdateDataListener();
        
        m_pComment = new CMComment();
        m_pComment->setListener(m_pUpdateDataListener, m_pSimpleResultListener, nil);
        m_pComment->SetUserData((__bridge void*)self);
    }
    
    CGRect webFrame;
    
    if (![sOrientation isEqualToString:@"L"]) {
        webFrame = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-44-20);
        webView = [[CMWebView alloc] initWithFrame:webFrame];
        
        [self.view addSubview:webView];
        
    }
    else{
        
        [self setNavigationBarCustom];
        
    }
    
    
	toolbar = [[UIToolbar alloc] initWithFrame:CGRectMake(0, (UI_IOS_WINDOW_HEIGHT)-35, UI_IOS_WINDOW_WIDTH, 35)];
    
	[toolbar setBarStyle:UIBarStyleDefault];
    
	txtcomment = [[UITextField alloc] initWithFrame:CGRectMake(2, (35-28)/2, UI_IOS_WINDOW_WIDTH-120, 28)];
	txtcomment.placeholder = I(@"写评论");
	//	txtcomment.contentInset = UIEdgeInsetsZero;
	[txtcomment setBorderStyle:UITextBorderStyleRoundedRect];
	[txtcomment setFont:[UIFont fontWithName:@"Helvetica" size:14.0]];
	txtcomment.keyboardType = UIKeyboardTypeDefault;
	txtcomment.delegate = self;
	[txtcomment setBackgroundColor:[UIColor clearColor]];
	
	CGFloat wd ;
	CGFloat hg ;
	
	btncomment = [UIButton buttonWithType:UIButtonTypeCustom];
	[btncomment addTarget:self action:@selector(tappedMe:) forControlEvents:UIControlEventTouchUpInside];
	UIImage* commentImage=[UIImage imageNamed:@"learn_comment_btn.png"];
	btncomment.backgroundColor = [UIColor clearColor];
	
	wd = commentImage.size.width;
	hg = commentImage.size.height;
	
	btncomment.frame = CGRectMake(0, (35-hg)/2, wd, hg);
	[btncomment setBackgroundImage:commentImage forState:UIControlStateNormal];
	
	btnFavorite= [UIButton buttonWithType:UIButtonTypeCustom];
	[btnFavorite addTarget:self action:@selector(MyFavoriteFun) forControlEvents:UIControlEventTouchUpInside];
	UIImage* favoriteImage=[UIImage imageNamed:@"learn_favorite_btn.png"];
	btnFavorite.backgroundColor = [UIColor clearColor];
	
	wd = favoriteImage.size.width;
	hg = favoriteImage.size.height;
	
	btnFavorite.frame = CGRectMake(0, (35-hg)/2, wd, hg);
	[btnFavorite setBackgroundImage:favoriteImage forState:UIControlStateNormal];
	
	BarButtontxtComment = [[UIBarButtonItem alloc] initWithCustomView:txtcomment];
	BarButtonFlexibleSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:self action:nil];
	BarButtonbtnComment = [[UIBarButtonItem alloc] initWithCustomView:btncomment];
	BarButtonbtnFavorite = [[UIBarButtonItem alloc] initWithCustomView:btnFavorite];
	
	[toolbar setItems:[NSArray arrayWithObjects:BarButtontxtComment,BarButtonbtnFavorite,BarButtonFlexibleSpace,nil]];
    
	NSString* sFlag = [NSString stringWithUTF8String:m_CourseInfo->sFlag];
	
	UIBarButtonItem *endexamBarButtonItem = nil ;
	
	if ([sFlag isEqualToString:@"kb"])
    {
		endexamBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:I(@"我的收藏")
                                                                style:UIBarButtonItemStyleBordered
                                                               target:self action:@selector(MyFavoriteFun)];
	}
    else
    {
        //判断是否支持评论功能
        if (m_CourseInfo->bEnablecomment)
        {
            UIButton *commentBtn = [UIButton buttonWithType:UIButtonTypeCustom];
            commentBtn.frame = CGRectMake(0, 0, kBarItemWidth, kBarItemHeight);
            commentBtn.imageEdgeInsets = [self itemFitDifferentVersion:NO];
            [commentBtn setImage:[UIImage imageNamed:@"publishcomment"] forState:UIControlStateNormal];
            [commentBtn addTarget:self action:@selector(gotoCommentList) forControlEvents:UIControlEventTouchUpInside];
            
            endexamBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:commentBtn];
            
            if (CMGlobal::TheOne().IsOffline())
            {
                endexamBarButtonItem.enabled = NO;
            }
        }
	}
    
    
    UIButton *listBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    
    listBtn.frame = CGRectMake(0, 0, kBarItemWidth, kBarItemHeight);
    
    listBtn.imageEdgeInsets = [self itemFitDifferentVersion:NO];
    
    [listBtn setImage:[UIImage imageNamed:@"learn_postcomment"] forState:UIControlStateNormal];
    
    [listBtn addTarget:self action:[sOrientation isEqualToString:@"L"] ? @selector(gotoCommentList) : @selector(showInput) forControlEvents:UIControlEventTouchUpInside];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc]initWithCustomView:listBtn];
    
    if ([sFlag isEqualToString:@"news"] && m_CourseInfo->bEnablecomment)
    {
        if (![sOrientation isEqualToString:@"L"]) {
            self.navigationItem.rightBarButtonItem = rightItem;
        }
        else{
            self.titleItem.rightBarButtonItem = rightItem;
        }
    }
    
    CMRELEASE(rightItem);
    
	
    CMRELEASE(endexamBarButtonItem)
    
    
    [webView setScalesPageToFit:YES];
    
    [webView setBackgroundColor:[UIColor whiteColor]];
    
    [webView.scrollView setShowsVerticalScrollIndicator:YES];
    
    [webView.scrollView setShowsHorizontalScrollIndicator:YES];
    
	const char* sUrl = NULL;
    
    //course and news have different url
    if (strcmp(m_CourseInfo->sFlag, "course") == 0)
    {
        sUrl = m_CourseInfo->sUrl;
    }
    else
    {
        sUrl = m_CourseInfo->sUrl;
    }
    
    
   // NSURL *desturl = nil;
    
    if(m_CourseInfo->nModel==0 && strcmp(m_CourseInfo->sFlag, "news")==0 )
    {
        
        CMGeneral general;
        sUrl = general.FormatUrlBySID(sUrl);
        
        NSString *strUrl = [NSString stringWithUTF8String:sUrl];
        
       self.desturl = [NSURL URLWithString:strUrl];
        
    }
    else if(m_CourseInfo->nModel==1 && strlen(((TCoursewareItem*)m_CourseInfo)->sEntryFilePath)==0)
    {
        
        CMGeneral general;
        sUrl = general.FormatUrlBySID(sUrl);
        
        NSString *strUrl = [NSString stringWithUTF8String:sUrl];
        
        self.desturl = [NSURL URLWithString:strUrl];
        
    }
    else if(strlen(((TCoursewareItem*)m_CourseInfo)->sEntryFilePath)!=0)
    {
        CMPath dstPath(CMPath::UNZIP_PATH);
        string path = (const char*)(CMString&)dstPath.String();
        path.append(m_CourseInfo->sID);
        path.append("/");
        path.append(((TCoursewareItem*)m_CourseInfo)->sEntryFilePath);
        
        self.desturl = [NSURL fileURLWithPath:[NSString stringWithUTF8String:path.c_str()]];
    }
    
	NSURLRequest *requestObj = [NSURLRequest requestWithURL:self.desturl];
    
	[webView loadRequest:requestObj];
    webView.delegate = self;
    
    [webView setBackgroundColor:[UIColor whiteColor]];
    
    
    //加入退回键盘按钮
    backBtn=[[UIButton alloc]initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, self.view.bounds.size.height-44-20)];
    
    [backBtn setBackgroundColor:[UIColor clearColor]];
    
    [backBtn addTarget:self action:@selector(dismissKeyboard) forControlEvents:UIControlEventTouchUpInside];
    backBtn.hidden=YES;
    [self.view addSubview:backBtn];
    
    //
    [webView.scrollView setIndicatorStyle:UIScrollViewIndicatorStyleBlack];
    
    bgview = [[UIView alloc] initWithFrame:webView.bounds];
    [webView addSubview:bgview];
    [tool addGeneratePlaceholderView:PlaceholderActionClickRefresh target:self action:@selector(loadWebviewData) on:bgview];
    bgview.hidden = YES;
    
    //输入部分
    self.inputView=[self createInputView];
    [self.view addSubview:inputView];
    [inputView setHidden:YES];
    self.willShowInputView = NO;
}

- (void)loadWebviewData{
    NSURLRequest *requestObj = [NSURLRequest requestWithURL:self.desturl];
    [webView loadRequest:requestObj];
    
}

- (void)webViewDidFinishLoad:(UIWebView *)awebView{
    NSString *bodyWidth= [awebView stringByEvaluatingJavaScriptFromString: @"document.body.scrollWidth "];
    CGFloat scale = awebView.frame.size.width/[bodyWidth intValue];
    //修改服务器页面的meta的值
    NSString *meta = [NSString stringWithFormat:@"document.getElementsByName(\"viewport\")[0].content = \"width=%f, initial-scale=1.0, minimum-scale=0.%f, maximum-scale=1.0, user-scalable=no\"", awebView.frame.size.width,scale,scale];
    [awebView stringByEvaluatingJavaScriptFromString:meta];
    
    [tool DisimissActivityIndicator];
    
    [bgview setHidden:YES];
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error{
    [bgview setHidden:NO];
    [tool DisimissActivityIndicator];

}

-(void)resetHeight
{
    
//    if(bottomView)
//      [ bottomView setFrame:CGRectMake(0, webView.scrollView.contentSize.height, UI_IOS_WINDOW_WIDTH, 43)];
//
//    if(commentlist)
//        [commentlist setFrame:CGRectMake(0, webView.scrollView.contentSize.height-5, UI_IOS_WINDOW_WIDTH, commentlist.frame.size.height)];
    
    if(bottomView)
    {
        
      [ bottomView setFrame:CGRectMake(0, webView.scrollView.contentSize.height, UI_IOS_WINDOW_WIDTH, 43)];
        
        
        isRespondToObserver = NO;

        CGSize temp = webView.scrollView.contentSize;
        
        temp.height =  43 + temp.height;
        
        
        
        [webView.scrollView setContentSize:CGSizeMake(temp.width,  temp.height)];
        
        isRespondToObserver = YES;
        
//        [webView.scrollView addObserver:self forKeyPath:@"contentSize" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:nil];

    }
    
    if( commentlist &&commentListHeight!=0 )
    {
        [ commentlist setFrame:CGRectMake(0, webView.scrollView.contentSize.height-5, UI_IOS_WINDOW_WIDTH, commentListHeight)];
        
        isRespondToObserver = NO;

        CGSize temp = webView.scrollView.contentSize;
        
        temp.height =  commentlist.frame.size.height + temp.height;
        
        [webView.scrollView setContentSize:CGSizeMake(temp.width, temp.height)];
        
        isRespondToObserver = YES;

    }
    
}
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    // 如果改变的属性是"name"
    if ([keyPath isEqualToString:@"contentSize"]) {
//        if(isRespondToObserver)
//            [self resetHeight];
          }
}

-(void)updateCommentCount
{
    [CommentCountLb setText:[NSString stringWithFormat:@"%d%@",m_CourseInfo->nCommentcount , I(@"评论")]];
}

-(void)dismissKeyboard
{
    
    [self keyboardWillHide:nil];


}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(m_pComment)
        return m_pComment->GetItemCount()+1;
    else
        return 0;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	if (indexPath.row == m_pComment->GetItemCount()) {
		return kLestCellHeight;
	}
	
	TCommentItem *Item= new TCommentItem();
   
    
    NSInteger cellheight=0;
	if(m_pComment->GetItem(indexPath.row, *Item))
    {
        cellheight=  [CMCommentTableViewCell GetCellHeight:*Item webimage:m_pWebImage width:UI_IOS_WINDOW_WIDTH];
    }
    SAFEDELETE(Item);
	return cellheight;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	CMCommentTableViewCell *cell = (CMCommentTableViewCell*)[tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
	if (cell == nil) {
# if ! __has_feature(objc_arc)
        cell = [[[CMCommentTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifier] autorelease];
# else
         cell = [[CMCommentTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifier];
# endif
    }
	
    
	if (indexPath.row == m_pComment->GetItemCount() &&  m_pComment->GetItemCount()!= 0) {
		
		UITableViewCell* cellmore = [tableView dequeueReusableCellWithIdentifier:@"infocommentmore"];
		if (cellmore == nil) {
# if ! __has_feature(objc_arc)
			cellmore = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"infocommentmore"] autorelease];
# else
           cellmore = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"infocommentmore"];
# endif
		}
        
        
        btnMore = [UIButton buttonWithType:UIButtonTypeCustom];
        [btnMore setImage:[UIImage imageNamed:@"loadMoreComment_nor"] forState:UIControlStateNormal];
        [btnMore setImage:[UIImage imageNamed:@"loadMoreComment_sel"] forState:UIControlStateHighlighted];
        [btnMore addTarget:self action:@selector(gotoCommentList) forControlEvents:UIControlEventTouchUpInside];
        
        [btnMore setHidden:NO];
        btnMore.frame = CGRectMake(15, 1.5, 290, 44);
        [cellmore.contentView addSubview:btnMore];
        
        cellmore.selectionStyle = UITableViewCellSelectionStyleNone;
        cellmore.accessoryType = UITableViewCellAccessoryNone;
        
        return cellmore;
    }
  
	TCommentItem *item=new TCommentItem();
    
	if (m_pComment->GetItem(indexPath.row, *item))
    {
        [cell setcellinfo:*item webimage:m_pWebImage];
        [((UIButton*)[cell viewWithTag:kBtnLikeTag]) addTarget:self action:@selector(doLike:event:) forControlEvents:UIControlEventTouchUpInside];
        
        cell.lblsepview.hidden=NO;
        
        if(indexPath.row == (m_pComment->GetItemCount()-1))
            cell.lblsepview.hidden=YES;
        
        if (item->bIsLiked)
        {
            [((UIButton*)[cell viewWithTag:kBtnLikeTag]) setSelected:YES];
        }
        else
        {
            [((UIButton*)[cell viewWithTag:kBtnLikeTag]) setSelected:NO];
        }
        [((UIButton*)[cell viewWithTag:kBtnCommentTag]) addTarget:self action:@selector(doComment:event:) forControlEvents:UIControlEventTouchUpInside];
        
    }
    
    SAFEDELETE(item);
    
	return cell;
}
-(void)updateComment
{
    
    [tool DisimissActivityIndicator];

    NSInteger tableviewHeight = 0;
    
    if (m_pComment->GetItemCount()==0) {
		tableviewHeight = 0;

        return;
	}
	
    //计算第一个
	TCommentItem *Item= new TCommentItem();
    
    NSInteger cellheight=0;
    
	if(m_pComment->GetItem(0, *Item))
    {
        cellheight=  [CMCommentTableViewCell GetCellHeight:*Item webimage:m_pWebImage width:UI_IOS_WINDOW_WIDTH];
        
        tableviewHeight=tableviewHeight+cellheight;

    }
        
    SAFEDELETE(Item);

    //计算第二个
    Item= new TCommentItem();
    
	if(m_pComment->GetItem(1, *Item))
    {
        cellheight=  [CMCommentTableViewCell GetCellHeight:*Item webimage:m_pWebImage width:UI_IOS_WINDOW_WIDTH];
        
        tableviewHeight=tableviewHeight+cellheight;

    }
    
    SAFEDELETE(Item);

    tableviewHeight=tableviewHeight+kLestCellHeight;
    
    //建立table
    commentlist = [[UITableView alloc]initWithFrame:CGRectMake(0, webView.scrollView.contentSize.height-5, UI_IOS_WINDOW_WIDTH,tableviewHeight)];
    
    [commentlist setBackgroundColor:[UIColor colorWithRed:244.0/255.0f green:244.0/255.0f blue:244.0/255.0f alpha:1]];

    [commentlist setScrollEnabled:NO];
    [commentlist setDataSource:self];
    [commentlist setDelegate:self];
    
    commentlist.separatorStyle =UITableViewCellSeparatorStyleNone;
    
    [webView.scrollView insertSubview:commentlist belowSubview:bottomView];
    
    CGSize temp= webView.scrollView.contentSize;
    isRespondToObserver=NO;
    webView.scrollView.contentSize= CGSizeMake(temp.width, temp.height+tableviewHeight);
    isRespondToObserver=YES;
    commentListHeight= tableviewHeight;
}


- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    [tool DisimissActivityIndicator];
    
    if (navigationType == UIWebViewNavigationTypeLinkClicked)
    {
        //判断格式是否为3mv
        if ((request.URL.absoluteString.length > 3 && ([[request.URL.absoluteString substringFromIndex:request.URL.absoluteString.length - 3] isEqualToString:@"3mv"] || [[request.URL.absoluteString substringFromIndex:request.URL.absoluteString.length - 3] isEqualToString:@"mp4"])) || [request.URL.absoluteString rangeOfString:@"flag=course&_cwid="].location != NSNotFound)
        {
            CMPlayerControl* playerControl=[[CMPlayerControl alloc] init];
                        
            //设置url和视频类型
            playerControl.sflag=sflag;
            playerControl.classid=classid;
            playerControl.coursewareid=coursewareid;
            
			[playerControl startPlay:request.URL.absoluteString];
            
            if([sflag isEqualToString:@"course"])
                playerControl.typeFlag=typeCourse;
            else
                playerControl.typeFlag=typeNews;
            
            //设置标题
            playerControl.title = self.title;
            
            playerControl.navigationController.navigationBarHidden = NO;
            playerControl.tabBarController.tabBar.hidden = YES;
            playerControl.hidesBottomBarWhenPushed = YES;
            
            [self.navigationController pushViewController:playerControl animated:YES];
            
            CMRELEASE(playerControl);
            return NO;
        }
        
        
        //判断scheme是不是ulp：//
        
            BOOL compareScheme = [[[request URL] scheme] caseInsensitiveCompare:@"ulp"] == NSOrderedSame;

            if(compareScheme)
            {
                NSURL *tempurl = [request URL];

                //得到sid
                NSArray *array = [[tempurl query] componentsSeparatedByString:@"&"];
                NSString* sidquery = [array objectAtIndex:0];
                
                NSRange range = [sidquery rangeOfString:@"="];
                
                NSString* sid = [sidquery substringFromIndex:range.location+range.length];

                //判断路径
                //跳转到课件
                BOOL compareCourseware = [[tempurl host] caseInsensitiveCompare:@"gotoCourseware"] == NSOrderedSame;
                
                //跳转到课程
                BOOL compareClass = [[tempurl host] caseInsensitiveCompare:@"gotoClass"] == NSOrderedSame;
                
                //跳转到资讯
                BOOL compareNews = [[tempurl host] caseInsensitiveCompare:@"gotoNews"] == NSOrderedSame;
                                
                //跳转到调研
                BOOL compareSurvey= [[tempurl host] caseInsensitiveCompare:@"gotoSurvey"] == NSOrderedSame;
                
                //跳转到测验
                BOOL compareExam = [[tempurl host] caseInsensitiveCompare:@"gotoExam"] == NSOrderedSame;
                
                //跳转到练习
                BOOL compareExercise = [[tempurl host] caseInsensitiveCompare:@"gotoExercise"] == NSOrderedSame;
                
                //跳转到问答
                BOOL  compareQuestion = [[tempurl host] caseInsensitiveCompare:@"gotoQA"] == NSOrderedSame;
                
                if(compareCourseware)
                {
                    
                    if(m_pGotoCoursewareListener == NULL)
                        m_pGotoCoursewareListener = new CMGotoCoursewareListener();
                    
                    if(tempBrowser == NULL)
                        tempBrowser = new CMBrowser(m_pGotoCoursewareListener);
                    
                    tempBrowser->SetUserData((__bridge void*)self);
                    
                    if(tempBrowser->RequestCoursewareById([sid UTF8String]))
                       [tool ShowActivityIndicator:self.view];
                    else
                        [tool DisimissActivityIndicator];
                    
                    return NO;
                }

                if(compareClass)
                {
                    TClassItem item;
                    item.nModel = 0;
                    strcpy(item.sID, [sid UTF8String]);
                    strcpy(item.sFlag, "course");
                    
                    CMCourseDetailControl* coursedetailControl = [[CMCourseDetailControl alloc] init];
                    [coursedetailControl setInfo:item];
                    [self.navigationController pushViewController:coursedetailControl animated:YES];
                    CMRELEASE(coursedetailControl);

                    return NO;
                }
                
                if(compareNews)
                {
                    
                    if(m_pCMGotoNewsListener == NULL)
                        m_pCMGotoNewsListener = new CMGotoNewsListener();
                    
                    if(tempBrowser == NULL)
                        tempBrowser = new CMBrowser(m_pCMGotoNewsListener);
                    
                    tempBrowser->SetUserData((__bridge void*)self);
                    
                    if(tempBrowser->RequestNewsById([sid UTF8String]))
                        [tool ShowActivityIndicator:self.view];
                    else
                        [tool DisimissActivityIndicator];
                    
                    return NO;
                }
                
                
                if(compareExercise)
                {
                    
                    if(m_pCMGotoExerciseListener == NULL)
                        m_pCMGotoExerciseListener = new CMGotoExerciseListener();
                    
                    if(m_pExerciselist == NULL)
                        m_pExerciselist = new CMExerciseList();
                    
                    m_pExerciselist->SetListener(m_pCMGotoExerciseListener);
                    
                    m_pExerciselist->SetUserData((__bridge void*)self);
                    
                    if (m_pExerciselist->GetExerciseById([sid UTF8String]))
                    {
                        [tool ShowActivityIndicator:self.view];
                    }
                    else
                        [tool DisimissActivityIndicator];
                    
                    return NO;
                    
                }
                
                if(compareExam)
                {
                    if(m_pCMGotoExamListener == NULL)
                        m_pCMGotoExamListener = new CMGotoExamListener();
                    
                    if(m_pExamlist == NULL)
                        m_pExamlist = new CMExamList();
                    
                    m_pExamlist->SetListener(m_pCMGotoExamListener);
                    
                    m_pExamlist->SetUserData((__bridge void*)self);
                    
                    if (m_pExamlist->GetExamById([sid UTF8String])) {
                        [tool ShowActivityIndicator:self.view];
                    }
                    else
                        [tool DisimissActivityIndicator];
                    
                    return NO;
                }
                
                if(compareSurvey)
                {
                    if(m_pCMGotoSurveyListener == NULL)
                        m_pCMGotoSurveyListener = new CMGotoSurveyListener();
                    
                    if(m_pSurveylist == NULL)
                        m_pSurveylist = new CMSurveyList(m_pCMGotoSurveyListener);
                    
                    m_pSurveylist->SetUserData((__bridge void*)self);
                    
                    if (m_pSurveylist->GetSurveyById([sid UTF8String])) {
                        [tool ShowActivityIndicator:self.view];
                    }
                    else
                        [tool DisimissActivityIndicator];
                    
                    return NO;
                }
                
                if(compareQuestion)
                {
                    
                    if(m_pCMGotoQAListener == NULL)
                        m_pCMGotoQAListener = new CMGotoQAListener();
                    
                    if(m_pQAlist == NULL)
                        m_pQAlist = new CMQAList();
                    
                    m_pQAlist->SetListener(m_pCMGotoQAListener,NULL,NULL);
                    
                    m_pQAlist->SetUserData((__bridge void*)self);
                    
                    if (m_pQAlist->GetQuestionbyId([sid UTF8String])) {
                        [tool ShowActivityIndicator:self.view];
                    }
                    else
                        [tool DisimissActivityIndicator];
                    
                }
                
                
                
                
                return NO;
            }
        return YES;
    }
    return YES;
}

#pragma mark - 下架时自动跳回

- (void)popWhenNoNermission
{
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark - url跳转到app

-(void)gotoCourseware
{
    
    [tool DisimissActivityIndicator];
    
    TBrowserItem* item = new TCoursewareItem();
    
    if(!tempBrowser->GetItem(0, item))
        return;

    CMNavgateItem* nav = [[CMNavgateItem alloc] init];
    
 
	[nav NavgateItem:(UIViewController*)self item:*item];

    SAFEDELETE(item);
	
    CMRELEASE(nav);
    
}

-(void)gotoNews
{
    [tool DisimissActivityIndicator];
    
    TBrowserItem *item = new TCoursewareItem();
    
    if(!tempBrowser->GetItem(0, item))
    {
        SAFEDELETE(item);
        return;
    }
    
    CMNavgateItem* nav = [[CMNavgateItem alloc] init];

	[nav NavgateItem:(UIViewController*)self item:*item];

    SAFEDELETE(item);
	
    CMRELEASE(nav);
    
}

-(void)gotoExam
{
    
    CMIntrodocutionViewController *intro = [[CMIntrodocutionViewController alloc] init];
    intro.hidesBottomBarWhenPushed = YES;
    TExamListItem item;
	m_pExamlist->GetItem(0,item);
    
    NSString *strTitle = [NSString stringWithUTF8String:item.sTitle.c_str()];
    NSString *sortes = [NSString stringWithFormat:@"%@",NSStringFrom(item.sTestscores)];
    NSString *strID = [NSString stringWithUTF8String:item.sID.c_str()];
    NSString *strDesc = [NSString stringWithUTF8String:item.sDesc.c_str()];
    NSString *strCategory = [NSString stringWithUTF8String:item.sDesc.c_str()];
    NSString *strPubdate = [NSString stringWithUTF8String:item.sPubdate.c_str()];
    NSString *strRequireCount = [NSString stringWithFormat:@"%d",item.nRequirecount];
    NSString *strCompleteCount = [NSString stringWithFormat:@"%d",item.nRequirecount - item.nUncompletecount];
    NSString *strQuestionCount = [NSString stringWithFormat:@"%d",item.nQuestioncount];
    NSString *strDuration = [NSString stringWithFormat:@"%d",item.nDuration];
    NSString *strRemainTime = [NSString stringWithFormat:@"%d",item.nRemainTime];
    NSString *strFullMark = [NSString stringWithFormat:@"%d",item.nFullmark];
    NSString *strPassMark = [NSString stringWithFormat:@"%d",item.nPassmark];
    NSString *strRankUrl = [NSString stringWithUTF8String:item.sRankurl.c_str()];
   // NSString *strComplete = [NSString stringWithFormat:@"%i",item.bIsComplete];
    NSString *strViewAnswer = [NSString stringWithFormat:@"%i",item.bViewAnswer];
    NSString *strCurrNumber = [NSString stringWithFormat:@"%i", item.nCurrNumber];
    NSString *strTotalNumber = [NSString stringWithFormat:@"%i", item.nTotalNumber];
    NSString *strCompleteTime = NSStringFrom(item.sCompletetime);
    
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"exam",@"type",strTitle,@"title",sortes,@"scores",strID,@"id",strDesc,@"desc",strCategory,@"category",strPubdate,@"pubdate",strRequireCount,@"requirecount",strCompleteCount,@"completecount",strQuestionCount,@"questioncount",strDuration,@"duration",strRemainTime,@"remaintime",strFullMark,@"fullmark",strPassMark,@"passmark",strRankUrl,@"rank",/*strComplete,@"complete",*/ strViewAnswer,@"viewanswer", strCurrNumber, @"currnumber", strTotalNumber, @"totalnumber", strCompleteTime, @"completetime", nil];
    intro.itemDic = dic;
    CMRELEASE(dic);
    [intro setHanlder:m_pExamlist row:0];
    [self.navigationController pushViewController:intro animated:YES];
    CMRELEASE(intro);
    
}


-(void)gotoExercise
{
    CMIntrodocutionViewController *intro = [[CMIntrodocutionViewController alloc] init];
    intro.hidesBottomBarWhenPushed = YES;
    
	TExerciseListItem item;
    if(m_pExerciselist == NULL)
    {
        CMRELEASE(intro);
        return;
    }
    
	m_pExerciselist->GetItem(0,item);
    
    NSString *strTitle = [NSString stringWithUTF8String:item.GetExerciseListItemTitle()];
    NSString *strID = [NSString stringWithUTF8String:item.GetExerciseListItemID()];
    NSString *strDesc = [NSString stringWithUTF8String:item.GetExerciseListItemDesc()];
    NSString *strCategory = [NSString stringWithUTF8String:item.GetExerciseListItemCategory()];
    NSString *strPubdate = [NSString stringWithUTF8String:item.GetExerciseListItemPubdate()];
    NSString *strTotalCount = [NSString stringWithFormat:@"%d",item.nQuestioncount];
    NSString *strCompleteCount = [NSString stringWithFormat:@"%d",item.nUsercompletecount];
    NSString *strCompleteUser = [NSString stringWithFormat:@"%d",item.nUsercompletecount];
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"practice",@"type",strTitle,@"title",strID,@"id",strDesc,@"desc",strCategory,@"category",strPubdate,@"pubdate",strTotalCount,@"totalcount",strCompleteCount,@"completecount",strCompleteUser,@"completeuser", nil];
    intro.itemDic = dic;
    intro->m_pExerciseList = m_pExerciselist;
    intro.nRow = 0;
    CMRELEASE(dic);
    [self.navigationController pushViewController:intro animated:YES];
	//[self gotoNav_start:indexPath.row];
    CMRELEASE(intro);
    
    
}



-(void)gotoSurvey
{
    CMIntrodocutionViewController *intro = [[CMIntrodocutionViewController alloc] init];
    intro.hidesBottomBarWhenPushed = YES;
	TSurveyListItem item;
	m_pSurveylist->GetItem(0,item);
    NSString *strTitle = [NSString stringWithUTF8String:item.sTitle];
    NSString *strID = [NSString stringWithUTF8String:item.sID];
    NSString *strDesc = [NSString stringWithUTF8String:item.sDesc];
    NSString *strRequireCount = [NSString stringWithFormat:@"%d",item.nInvitecount];
    NSString *strCompleteCount = [NSString stringWithFormat:@"%d",item.nCompletecount];
    NSString *strExpiredate = [NSString stringWithUTF8String:item.sExpiredate];
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithObjectsAndKeys:@"survey",@"type",strTitle,@"title",strID,@"id",strDesc,@"desc",strExpiredate,@"expiredate",strRequireCount,@"requirecount",strCompleteCount,@"completecount", nil];
    intro.itemDic = dic;
    [self.navigationController pushViewController:intro animated:YES];

    
}


-(void)gotoQA
{
    
    TQAItem qaitem;
    if(!m_pQAlist->GetItem(0, qaitem))
        return;
    
        
    CMQuestionDetailControl* questiondetailcontrol = [[CMQuestionDetailControl alloc] init];
    
	[questiondetailcontrol SetQuestionItem:qaitem];
    questiondetailcontrol->m_pQalist=m_pQAlist;
    if(_stricmp(qaitem.sQuestioner_username.c_str(),SETTING.GetUserName()) != 0){
        questiondetailcontrol.title = [NSString stringWithFormat:I(@"%@的问题"),[NSString stringWithUTF8String:qaitem.sQuestioner_fullname.c_str()]];
    }
    else{
        questiondetailcontrol.title = [NSString stringWithFormat:I(@"我的提问")];
    }
	questiondetailcontrol.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
	questiondetailcontrol.navigationController.navigationBarHidden = NO;
	questiondetailcontrol.tabBarController.tabBar.hidden = YES;
	questiondetailcontrol.hidesBottomBarWhenPushed = YES;
	//qasearchcontrol.navigationController.delegate = self;
    //添加判断textanswer 是否第一响应标记
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@"1" forKey:@"isFirstResponder"];
    
   	questiondetailcontrol.view.backgroundColor = [UIColor clearColor];
	[self.navigationController pushViewController:questiondetailcontrol animated:YES];
    CMRELEASE(questiondetailcontrol);
    

    
}

-(void)MyFavoriteFun
{
    int returnvalue;
    
    //未添加到收藏，则收藏
    
    returnvalue = CMFavorites::GetInstance()->AddFavorite(*m_CourseInfo);
    
    if ([sOrientation isEqualToString:@"L"]) {
        if (returnvalue == 0) {
            [self showAlertView:I(@"收藏失败")];
        }else if (returnvalue == 1) {
            [self showAlertView:I(@"收藏成功")];
        } else {
            [self showAlertView:I(@"已收藏")];
            
        }
    }
    else{
        if (returnvalue == 1) {
            [tool ShowAlert:I(@"收藏成功")];
            
        }else if (returnvalue == 2) {
            [tool ShowAlert:I(@"已收藏")];
            
        }else {
            [tool ShowAlert:I(@"收藏失败")];
        }
    }
    
	//NSLog(@"return value = %d",returnvalue);
    //加一项收藏到收藏列表顶部，返回值：0失败，1成功，2已收藏
}

#pragma mark - AlertView
- (void)showAlertView:(NSString *)string{
    UILabel* label = [[UILabel alloc]initWithFrame:CGRectMake(0, 5, 220, 20)];
    label.textAlignment=UITextAlignmentCenter;
    label.text = string;
    label.font = [UIFont systemFontOfSize:14];
    label.textColor = [UIColor whiteColor];
    label.backgroundColor = [UIColor clearColor];
    UIImage *theImage = [UIImage imageNamed:@"textHintBG.png"];
    
    CGRect frame = CGRectMake((UI_IOS_WINDOW_HEIGHT - 220)/2.0, (UI_IOS_WINDOW_WIDTH - 40)/2.0, 220, 30);
    UIImageView *bg = [[UIImageView alloc]initWithFrame:frame];
    bg.alpha = 0.0;
    bg.hidden = YES;
    [bg setImage:theImage];
    [bg addSubview:label];
    [self.view addSubview:bg];
    CMRELEASE(label);
    
    [UIView animateWithDuration:0.5 animations:^(void){
        bg.alpha = 1.0;
        bg.hidden = NO;
    } completion:^(BOOL f1){
        [UIView animateWithDuration:0.5 animations:^(void){
            bg.alpha = 0.0;
            bg.hidden = YES;
        } completion:^(BOOL f2){
            ;
        }];
    }];
    CMRELEASE(bg);
}



//键盘/表情盘 是否隐藏
- (BOOL)keyBoardHide{
    
    CGFloat inputMainY = CGRectGetMaxY(inputView.frame);
    
    if (__iOS7) {
        //NSLog(@"gaodu:%f",CGRectGetHeight(self.view.frame));
        return (inputMainY == CGRectGetHeight(self.view.frame));
        
    }else{
        return (inputMainY + 44 == CGRectGetHeight(self.view.frame));
        
    }
}


/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

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
//	[activity release];
//	[quartzView release];
//    m_pGotoCoursewareListener
    
    m_CourseInfo->SetListener(NULL, NULL, NULL);
    
    m_CourseInfo->SetUserData(NULL);
    
    [webView loadHTMLString:@"" baseURL:nil];
    if([webView isLoading]){
        [webView stopLoading];
    }
    [webView setDelegate:nil];
    
    CMRELEASE(m_sUrl);
    
    CMRELEASE(txtcomment);
    
    SAFEDELETE(m_pGotoCoursewareListener);
    SAFEDELETE(tempBrowser);
    
    SAFEDELETE(m_pRatingListener);
    SAFEDELETE(m_CourseInfo);
    
    CMRELEASE(self.desturl);
	CMRELEASE(backView);
    CMRELEASE(bottomView);
    CMRELEASE(sflag);
    CMRELEASE(classid);
    CMRELEASE(coursewareid);
    CMRELEASE(pubdate);
    CMRELEASE(commentlist);
    CMRELEASE(sOrientation);
    CMRELEASE(self.titleBar);
    CMRELEASE(self.titleItem);
    CMRELEASE(inputView);
    CMRELEASE(bgview);
    CMRELEASE(backBtn);
    
    CMRELEASE(webView);
	CMRELEASE(BarButtonFlexibleSpace);		
	CMRELEASE(BarButtontxtComment);
	CMRELEASE(BarButtonbtnComment);
	CMRELEASE(BarButtonbtnFavorite);
	CMRELEASE(toolbar);
	
	
	SAFEDELETE(m_pComment);
	SAFEDELETE(m_pUpdateDataListener);
	SAFEDELETE(m_pRatingListener);
	SAFEDELETE(m_pSimpleResultListener);
    
# if ! __has_feature(objc_arc)
	[super dealloc];
# endif
	
}


@end

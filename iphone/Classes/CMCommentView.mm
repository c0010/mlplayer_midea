//
//  CMCommentView.m
//  MLPlayer
//
//  Created by wangjianbin on 15/6/12.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import "CMCommentView.h"
#import "cmsettings.h"
#import "CMCommentReplyControl.h"
#import "cmglobal.h"
#import "CMEditCommentControl.h"
#import "UIScrollView+SVPullToRefresh.h"
#import "CMAlertView.h"

static const int  kChatInputTextViewMaxHeight  = __iOS7 ? 59 : 68;//输入框最大高度
static const int  kChatInputTextViewMinHeight  = __iOS7 ? 29 : 32;//输入框最小高度
#define kChatInputViewHeight 45

@implementation CMCommentView

@synthesize classID;
@synthesize coursewareID;

#define kCellIdentifier @"com.apple.CMClassCommentControl.CellIdentifier"

-(UIView*)createInputView
{
    //底
    UIImageView* inputBack=[[UIImageView alloc]initWithFrame:CGRectMake(0, self.frame.size.height - 45, self.frame.size.width, 45)];
    
    //[inputBack setImage:[[UIImage imageNamed:@"replyInput"] stretchableImageWithLeftCapWidth:15 topCapHeight:15]];
    [inputBack setBackgroundColor:[UIColor colorWithRed:241.0/255.0 green:241.0/255.0 blue:241.0/255.0 alpha:1]];
    [inputBack setUserInteractionEnabled:YES];
    inputBack.layer.shadowColor=[UIColor grayColor].CGColor;
    inputBack.layer.shadowOffset=CGSizeMake(0,-1);
    inputBack.layer.shadowOpacity=0.4;
    
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
    //    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(textviewdidChange:) name:FLXFluidTextViewHeightConstraintDidChangeNotification object:nil];
    
    
    //发送按钮
    UIButton *commitBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    
    [commitBtn setFrame:CGRectMake(255, 8, 55, 29)];
    [commitBtn setBackgroundImage:[UIImage imageNamed:@"sendreply_btn_nor"] forState:UIControlStateNormal];
    [commitBtn setBackgroundImage:[UIImage imageNamed:@"sendreply_btn_sel"] forState:UIControlStateHighlighted];
    
    [commitBtn setBackgroundImage:[UIImage imageNamed:@"sendreply_btn_dis"] forState:UIControlStateDisabled];
    
    
    [commitBtn addTarget:self action:@selector(sendcomment) forControlEvents:UIControlEventTouchUpInside];
    
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
    
#if !__has_feature(obj_arc)
    return inputBack;
    
#else
    return inputBack;
    
    
#endif
}

- (void)upDateCourseItemComment{
    if (m_CourseInfo) {
        m_CourseInfo->Refresh();
        m_CourseInfo->nCommentcount++;
        m_CourseInfo->Update();
    }
}

-(void) AutoFresh{
    //自动下拉刷新
    
    if (TableViewList.pullToRefreshView.state != SVPullToRefreshStateLoading) {
        [TableViewList triggerPullToRefresh];
    }
}

-(void)setBrowserItem:(TClassItem&)item
{
    if (m_CourseInfo)
    {
        SAFEDELETE(m_CourseInfo);
    }
    m_CourseInfo = new TClassItem();
    *m_CourseInfo = item;
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@"1" forKey:@"CommentReplyAdd"];
}


//-(void)viewDidAppear:(BOOL)animated
//{
//    [super viewDidAppear:animated];
//    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
//    NSString *str = [ud objectForKey:@"CommentReplyAdd"];
//    if ([str isEqualToString:@"1"]) {
//        [ud removeObjectForKey:@"CommentReplyAdd"];
//        [self AutoFresh];
//    }
//}

- (void)viewDidShow
{
    if ( !self.cannotComment ) {
        TableViewList.frame = CGRectMake(0, 0, self.bounds.size.width,self.bounds.size.height - kChatInputViewHeight);
    }
    else{
        TableViewList.frame = CGRectMake(0, 0, self.bounds.size.width,self.bounds.size.height);
        [inputView setHidden:YES];
    }
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    NSString *str = [ud objectForKey:@"CommentReplyAdd"];
    if ([str isEqualToString:@"1"]) {
        [ud removeObjectForKey:@"CommentReplyAdd"];
        [self AutoFresh];
    }
    
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(AutoFresh) name:@"AutoFresh" object:nil];
}

-(void)LoadTableList
{
    //    if(m_pComment->GetItemCount() > 0)
    //	{
    //		bgview.hidden = YES;
    //		[TableViewList reloadData];
    //	}
    //	else
    //		bgview.hidden = NO;
    //
    //
    
    [TableViewList reloadData];
    
    [self performSelector:@selector(doneLoadingTableViewData) withObject:nil afterDelay:0.5];
    
}

-(void)RershTableList:(UITableViewCell*)mycell
{
    if (!SETTING.GetAutoLoadMore()) {
        [btnMore setHidden:YES];
    }
    
    dwActiveView.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-150)/2, (44-20)/2, 20, 20);
    
    UILabel * lblview = [[UILabel alloc] initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-150)/2+25, (44-20)/2, 150, 20)];
    lblview.text = I(@"加载更多...");// @"加载更多...";
    lblview.backgroundColor = [UIColor clearColor];
    
    [mycell.contentView addSubview:dwActiveView];
    [mycell.contentView addSubview:lblview];
    CMRELEASE(lblview);
    
    mycell.selectionStyle = UITableViewCellSelectionStyleNone;
    mycell.accessoryType = UITableViewCellAccessoryNone;
    
    [dwActiveView startAnimating];
    
    m_pComment->RequestMore();
}


-(void)RershTableList
{
    if(m_pComment)
        m_pComment->RequestMore();
}
-(void)LoadComment
{
    [TableViewList reloadData];
    //NSString *strComment = [NSString stringWithString:@"course"];
    //m_pComment->RequestCommentList([m_type UTF8String], m_courseid);
    //[alert dismissWithClickedButtonIndex:0 animated:YES];
}


-(void)setCourseID:(const char*)courseid type:(NSString*)type
{
    m_type = [type copy];
    
    utf8ncpy(m_courseid, courseid, 63);
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesBegan:touches withEvent:event];
}


- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesMoved:touches withEvent:event];
    //[self hiddenkeyword];
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
    //	[super touchesEnded:touches withEvent:event];
    //	//[self hiddenkeyword];
    //	UITouch *touch = [[event allTouches] anyObject];
    //	CGPoint touchPoint = [touch locationInView:TableViewList];
    //	NSIndexPath*indexPath = [TableViewList indexPathForRowAtPoint:touchPoint];
    //
    //	//if(!popview.hidden)
    //	//	popview.hidden = YES;
    //
    //
    //    if(popview.alpha==1)
    //        popview.alpha=0;
    //	else if(indexPath)
    //	{
    //		touchPoint = [touch locationInView:self.view];
    //		CGRect rc = popview.frame;
    //		rc.origin.y = touchPoint.y-rc.size.height;
    //		if(rc.origin.y < 0)
    //			rc.origin.y = 10;
    //		popview.frame = rc;
    //		//popview.hidden = NO;
    //
    //        popview.alpha=1;
    //		popview.tag = indexPath.row;
    //	}
}

- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
    
    [super touchesCancelled:touches withEvent:event];
    
    //[self hiddenkeyword];
}

- (BOOL)hiddenkeyword{
    
    txtcomment.placeholder = I(@"写评论");
    [txtcomment becomeFirstResponder];
    [txtcomment resignFirstResponder];
    
    return YES;
}

#pragma mark Responding to keyboard events

//- (void)keyboardWillShow:(NSNotification *)aNotification {
//	NSDictionary* info = [aNotification userInfo];
//
//    NSValue* aValue = [info objectForKey:UIKeyboardBoundsUserInfoKey];
//    //键盘的大小
//    CGSize keyboardRect = [aValue CGRectValue].size;
//
//	height = keyboardRect.height;
//	width = keyboardRect.width;
//
//	[UIView beginAnimations:nil context:NULL];
//	[UIView setAnimationDuration:0.3];
//
//	// we need to perform some post operations after the animation is complete
//	[UIView setAnimationDelegate:self];
//
//	// shrink the table vertical size to make room for the date picker
//	CGRect newFrame = toolbar.frame;
//	newFrame.origin.y =UI_IOS_WINDOW_HEIGHT-height-44-20-35;
//	toolbar.frame = newFrame;
//	[UIView commitAnimations];
//	if (layView== nil) {
//		layView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-height-35-44-20)];
//		layView.backgroundColor = [UIColor blackColor];
//
//		[self.view addSubview:layView];
//	}
//	layView.alpha = 0.1;
//
//	txtcomment.text = @"";
//
//}


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
                [inputView setFrameY:self.bounds.size.height - kChatInputViewHeight - keyBoardHieght - (iheight - kChatInputTextViewMinHeight) Height:kChatInputViewHeight + (iheight - kChatInputTextViewMinHeight)];
                
                
            }];
        }
    }
}


- (void)textviewdidChange:(NSNotification *)aNotification{
    
    FLXFluidTextView *textview = (FLXFluidTextView *)aNotification.object;
    
    
    if (![self keyBoardHide]) {
        
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
            [inputView setFrameY:self.bounds.size.height - kChatInputViewHeight - keyBoardHieght - (iheight - kChatInputTextViewMinHeight) Height:kChatInputViewHeight + (iheight - kChatInputTextViewMinHeight)];
            
            
        }];
    }
}

- (BOOL)textViewShouldBeginEditing:(UITextView *)textView
{
    return YES;
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField {
    
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)textField {
    
    layView.alpha = 0;
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.3];
    [UIView setAnimationDelegate:self];
    
    CGRect newFrame = toolbar.frame;
    newFrame.origin.y =UI_IOS_WINDOW_HEIGHT-44-35-20;
    toolbar.frame = newFrame;
    [UIView commitAnimations];
    
    
    return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    if ([textField.text length] < 140) {//判断字符个数
        return YES;
    }
    
    return NO;
}


-(void)btn_Cancle
{
    if (isComment) {
        txtcomment.text = @"";
        [txtcomment becomeFirstResponder];
        [txtcomment resignFirstResponder];
    }
    isComment = FALSE;
}

- (IBAction)tappedMe:(id)sender {
    
    if ([txtcomment.text length] <= 0) {
        
        [tool ShowAlert:I(@"评论内容不能为空!")];
        
    }else {
        
        if (m_pComment!= nil && ![txtcomment.text isEqual: @""])
        {
            m_pComment->SendComment([m_type UTF8String], m_courseid,nil, [txtcomment.text UTF8String],false);
        }
        
        txtcomment.text = @"";
        [txtcomment becomeFirstResponder];
        [txtcomment resignFirstResponder];
    }
}


#pragma mark table function

-(void)tableView:(CMTableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    
    selectedIndex=indexPath.row;
    
    [self startcomment:1];
}



-(void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    
    switch (buttonIndex) {
        case 0://喜欢
        {
            TCommentItem Item;
            if(!m_pComment || !m_pComment->GetItem(selectedIndex, Item))
                return;
            
            if(m_pComment->CommentLike([m_type UTF8String],m_courseid,[coursewareID UTF8String],Item.sID))
                [tool Wait];
            
            break;
        }
            //	case 1://评论
            //	{
            //        [self startcomment:1];
            //
            //		break;
            //	}
            
        default:
            NSLog(@"undefault");
            break;
    }
    
    
}



- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 125.0f;
}

- (UIView*)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    UIView *headerView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, 91.0)];
    headerView.backgroundColor = kColorBackground;
    
    CGFloat edgeSpace = 15.0;
    UIFont *textFont = [UIFont systemFontOfSize:14];
    UIImage *starIma_N = [UIImage imageNamed:@"star_n"];
    UIImage *starIma_S = [UIImage imageNamed:@"star_s"];
    
    starView = [[UIView alloc]initWithFrame:CGRectMake(0, 1, self.bounds.size.width, 78)];
    starView.backgroundColor = [UIColor whiteColor];
    [headerView addSubview:starView];
    
    NSString *str = I(@"综合星级");
    CGSize labSize = [str sizeWithFont:textFont];
    UILabel *labelStarLevel = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, labSize.width + 20, labSize.height)];
    labelStarLevel.text = str;
    labelStarLevel.textColor = [UIColor grayColor];
    
    UIImageView *starIma = [[UIImageView alloc]initWithFrame:CGRectMake(0, 0, starIma_N.size.width, starIma_N.size.height)];
    starIma.image = starIma_S;
    
    textFieldStarLevel = [[UITextField alloc]initWithFrame:CGRectMake(edgeSpace, edgeSpace, labelStarLevel.frame.size.width + 50, labSize.height)];
    textFieldStarLevel.textColor = [UIColor grayColor];
    textFieldStarLevel.leftView = labelStarLevel;
    textFieldStarLevel.leftViewMode = UITextFieldViewModeAlways;
    textFieldStarLevel.rightView = starIma;
    textFieldStarLevel.rightViewMode = UITextFieldViewModeAlways;
    textFieldStarLevel.enabled = NO;
    textFieldStarLevel.borderStyle = UITextBorderStyleNone;
    textFieldStarLevel.text = NSStringFrom(m_CourseInfo->fCommonStar).length > 0 ? NSStringFrom(m_CourseInfo->fCommonStar) : @"0";
    [starView addSubview:textFieldStarLevel];
    
    UILabel *labelStarPeople = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, labSize.width + 20, labSize.height)];
    labelStarPeople.text = I(@"评星人数");
    labelStarPeople.textColor = [UIColor grayColor];
    
    textFieldStarPeople = [[UITextField alloc]initWithFrame:CGRectMake(textFieldStarLevel.frame.size.width + edgeSpace + 35, edgeSpace, labelStarPeople.frame.size.width + 60, labSize.height)];
    textFieldStarPeople.textColor = [UIColor grayColor];
    textFieldStarPeople.leftView = labelStarPeople;
    textFieldStarPeople.leftViewMode = UITextFieldViewModeAlways;
    textFieldStarPeople.enabled = NO;
    textFieldStarPeople.borderStyle = UITextBorderStyleNone;
    textFieldStarPeople.text = m_CourseInfo->nStarCount > 0 ? [NSString stringWithFormat:@"%d",m_CourseInfo->nStarCount] : @"0";
    [starView addSubview:textFieldStarPeople];
    
    UILabel *labelMyStars = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, labSize.width + 20, labSize.height)];
    labelMyStars.text = I(@"自评星级");
    labelMyStars.textColor = [UIColor grayColor];
    
    UIView *starBtnView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, starIma_N.size.width * 5 + 20, starIma_N.size.height)];
    for (int i =1 ; i <= 5 ; i++)
    {
        UIButton *starBtn = [UIButton buttonWithType:UIButtonTypeCustom];
        [starBtn setFrame:CGRectMake((i - 1) * (starIma_N.size.width + 5), 0, starIma_N.size.width, starIma_N.size.height)];
        [starBtn setTag:i];
        [starBtn addTarget:self action:@selector(commitMyStars:) forControlEvents:UIControlEventTouchUpInside];
        [starBtn setImage:i > m_CourseInfo->nMyStar ? starIma_N : starIma_S forState:UIControlStateNormal];
        [starBtn setImage:i > m_CourseInfo->nMyStar ? starIma_N : starIma_S forState:UIControlStateDisabled];
        
        starBtn.enabled = !m_CourseInfo->nMyStar;
        
        
        [starBtnView addSubview:starBtn];
    }
    
    textFieldMyStar = [[UITextField alloc]initWithFrame:CGRectMake(edgeSpace , edgeSpace + labSize.height + 19, labelMyStars.frame.size.width + starBtnView.frame.size.width, labSize.height)];
    textFieldMyStar.leftView = labelMyStars;
    textFieldMyStar.leftViewMode = UITextFieldViewModeAlways;
    textFieldMyStar.rightView = starBtnView;
    textFieldMyStar.rightViewMode = UITextFieldViewModeAlways;
    textFieldMyStar.delegate = self;
    textFieldMyStar.borderStyle = UITextBorderStyleNone;
    [starView addSubview:textFieldMyStar];
    
    UIView *separatorView = [[UIView alloc]initWithFrame:CGRectMake(0, starView.frame.origin.y + starView.frame.size.height, self.frame.size.width, 8)];
    separatorView.backgroundColor = kColorBackground;
    [headerView addSubview:separatorView];
    
    UIView *commentCountView = [[UIView alloc]initWithFrame:CGRectMake(0, separatorView.frame.origin.y + separatorView.frame.size.height, self.frame.size.width, 38)];
    commentCountView.backgroundColor = [UIColor whiteColor];
    
    labelCommentCount = [[UILabel alloc]initWithFrame:CGRectMake(edgeSpace, 0, commentCountView.frame.size.width - edgeSpace, commentCountView.frame.size.height)];
    labelCommentCount.text = [NSString stringWithFormat:@"%@ %d",I(@"评论"),m_CourseInfo->nCommentcount];
    labelCommentCount.textColor = [UIColor grayColor];
    labelCommentCount.font = textFont;
    [commentCountView addSubview:labelCommentCount];
    
    [headerView addSubview:commentCountView];
    
    UIView *endSeparatorView = [[UIView alloc]initWithFrame:CGRectMake(0, commentCountView.frame.origin.y + commentCountView.frame.size.height, self.frame.size.width, 1)];
    endSeparatorView.backgroundColor = kColorBackground;
    [headerView addSubview:endSeparatorView];
    
    return headerView;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(m_pComment->GetItemCount()==0)
    {
        bgview.hidden=NO;
        tableView.separatorStyle =UITableViewCellSeparatorStyleNone;
        
    }else
    {
        tableView.separatorStyle =     UITableViewCellSeparatorStyleNone;
        
        bgview.hidden=YES;
    }
    
    if (m_pComment->IsEnd()) {
        return m_pComment->GetItemCount();
    }
    return m_pComment->GetItemCount()+1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row == m_pComment->GetItemCount()) {
        return 44;
    }
    
    TCommentItem *Item= new TCommentItem();
    
    NSInteger cellheight=0;
    if(m_pComment->GetItem(indexPath.row, *Item))
    {
        cellheight=  [CMCommentTableViewCell GetCellHeight:*Item webimage:m_pWebImage width:TableViewList.frame.size.width]+5;
    }
    SAFEDELETE(Item);
    return cellheight;
}



//初始化评论背景
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
    [dwActiveView stopAnimating];
    
    if (indexPath.row == m_pComment->GetItemCount() &&  m_pComment->GetItemCount()!= 0) {
        
        UITableViewCell* cellmore = [tableView dequeueReusableCellWithIdentifier:@"infocommentmore"];
        if (cellmore == nil) {
# if ! __has_feature(objc_arc)
            cellmore = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"infocommentmore"] autorelease];
# else
            cellmore = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"infocommentmore"];
# endif
        }
        
        if(SETTING.GetAutoLoadMore())
        {
            [self RershTableList:cellmore];
        }
        else
        {
            
            btnMore = [UIButton buttonWithType:UIButtonTypeCustom];
            [btnMore setImage:[UIImage imageNamed:@"Load_More_nor"] forState:UIControlStateNormal];
            [btnMore setImage:[UIImage imageNamed:@"Load_More_sel"] forState:UIControlStateHighlighted];
            [btnMore addTarget:self action:@selector(RershTableList) forControlEvents:UIControlEventTouchUpInside];
            
            [btnMore setHidden:NO];
            btnMore.frame = CGRectMake(15, 1.5, 290, 44);
            [cellmore.contentView addSubview:btnMore];
            
            cellmore.selectionStyle = UITableViewCellSelectionStyleNone;
            cellmore.accessoryType = UITableViewCellAccessoryNone;
        }
        return cellmore;
    }
    
    TCommentItem *item=new TCommentItem();
    if (m_pComment->GetItem(indexPath.row, *item))
    {
        [cell setcellinfo:*item webimage:m_pWebImage];
        [((UIButton*)[cell viewWithTag:kBtnLikeTag]) addTarget:self action:@selector(doLike:event:) forControlEvents:UIControlEventTouchUpInside];
        
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


-(void)doLike:(id)sender event:(id)event
{
    if(CMGlobal::TheOne().IsOffline())
        return;
    
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
    CGPoint point= [touch locationInView:TableViewList];
    
    UIButton* btn=(UIButton*)sender;
    
    if(btn.selected)
        return;
    
    [btn setSelected:YES];
    
    NSInteger row=[TableViewList indexPathForRowAtPoint:point].row;
    
    CMCommentTableViewCell*cell=(CMCommentTableViewCell*)[TableViewList cellForRowAtIndexPath:[NSIndexPath indexPathForRow:row inSection:0]];
    
    UILabel* pv=((UILabel*)[cell viewWithTag:kLblPvTag]);
    
    NSInteger tempInt=[pv.text integerValue];
    
    tempInt += 1;
    
    [pv setText:[NSString stringWithFormat:@"%d",tempInt]];
    
    TCommentItem *Item= new TCommentItem();
    if(!m_pComment || !m_pComment->GetItem(row, *Item))
        return;
    
    if(Item->bIsLiked)
        return;
    
    if(!m_pComment->CommentLike([m_type UTF8String],m_courseid,[coursewareID UTF8String],Item->sID))
    {
    }
    SAFEDELETE(Item);
}

-(void)doComment:(id)sender event:(id)event
{
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
    CGPoint point= [touch locationInView:TableViewList];
    
    NSInteger row=[TableViewList indexPathForRowAtPoint:point].row;
    
    selectedIndex=row;
    
    [self startcomment:1];
    
    
}
// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
 - (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
 self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
 if (self) {
 // Custom initialization.
 }
 return self;
 }
 */

/*
 // Implement loadView to create a view hierarchy programmatically, without using a nib.
 - (void)loadView {
 }
 */
//-(void)viewWillAppear:(BOOL)animated
//{
//    [super viewWillAppear:animated];
//    
//    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(keyboardWillShow:)name:UIKeyboardWillShowNotification object:nil];
//    
//}

//-(void)viewWillDisappear:(BOOL)animated
//{
//    [[NSNotificationCenter defaultCenter]removeObserver:self];
//    
//    [self dismissKeyboard];
//    [inputField resignFirstResponder];
//    [super viewWillDisappear:animated];
//    
//}

#pragma mark -
#pragma mark refresh

#pragma mark -
#pragma mark Data Source Loading / Reloading Methods

- (void)reloadTableViewDataSource{
    
    //  should be calling your tableviews data source model to reload
    //  put here just for demo
    
    m_pComment->RequestCommentList([m_type UTF8String], m_courseid,[coursewareID UTF8String]);
}

- (void)doneLoadingTableViewData{
    
    //  model should call this when its done loading
    [TableViewList.pullToRefreshView refreshLastUpdatedDate];
    [TableViewList.pullToRefreshView stopAnimating];
}



//- (void)scrollViewDidScroll:(UIScrollView *)scrollView{
//	popview.hidden = YES;
//	[refreshView scrollViewDidScroll:scrollView:YES:YES];
//}
//- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate{
//
//	[refreshView scrollViewDidEndDragging:scrollView willDecelerate:decelerate];
//}
//
//-(void)willRershTableListView{
//
//	m_pComment->RequestCommentList([m_type UTF8String], m_courseid);
//	[self LoadTableList];
//
//}

- (void)touchBegan:(UIControl *)c withEvent:ev {
    //    NSLog(@"dragBegan......");
    //    UITouch *touch = [[ev allTouches] anyObject];
    //    CGPoint touchPoint = [touch locationInView:self.view];
    //    NSLog(@"Touch x : %f y : %f", touchPoint.x, touchPoint.y);
    //
    //	CGRect left = popview.frame;
    //	left.size.width = left.size.width/2;
    //
    //    if(CGRectContainsPoint(left, touchPoint))
    //    {
    //		UIImage*image = [UIImage imageNamed:@"like_p"];
    //		[popview setBackgroundImage:image forState:UIControlStateNormal];
    //		[popview setBackgroundImage:image forState:UIControlStateHighlighted];
    //
    //    }
    //	else
    //	{
    //		UIImage*image = [UIImage imageNamed:@"reply_p"];
    //		[popview setBackgroundImage:image forState:UIControlStateNormal];
    //		[popview setBackgroundImage:image forState:UIControlStateHighlighted];
    //
    //
    //	}
    //
}

- (void)touchEnded:(UIControl *)c withEvent:ev
{
    //	TCommentItem Item;
    //	if(!m_pComment || !m_pComment->GetItem(popview.tag, Item))
    //		return;
    //	UITouch *touch = [[ev allTouches] anyObject];
    //    CGPoint touchPoint = [touch locationInView:self.view];
    //    NSLog(@"Touch x : %f y : %f", touchPoint.x, touchPoint.y);
    //
    //	CGRect left = popview.frame;
    //	left.size.width = left.size.width/2;
    //
    //    if(CGRectContainsPoint(left, touchPoint))
    //    {//喜欢
    //		if(m_pComment->CommentLike([m_type UTF8String],m_courseid,Item.sID))
    //			[tool Wait];
    //    }
    //	else
    //	{//评论
    //		[self startcomment:1];
    //
    //	}
    //	UIImage*image = [UIImage imageNamed:@"likereply"];
    //	[popview setBackgroundImage:image forState:UIControlStateNormal];
    //	//popview.hidden = YES;
    //
    //    popview.alpha=0;
    
}

-(void)sendcomment
{
    if(!m_pEditComment)
        return;
    
    if (CMGlobal::TheOne().IsOffline()) {
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
    
    BOOL ret = m_pEditComment->SendComment([m_type UTF8String],m_courseid,[coursewareID UTF8String],[inputField.text UTF8String],false);
    
    if(ret)
    {
        [tool ShowActivityIndicator:self];
        inputField.text=@"";
        [self dismissKeyboard];
        [inputView setFrameY:self.bounds.size.height - kChatInputViewHeight Height:45];
        
        
    }else
    {
        
    }
    
}

-(void)startcomment:(int)type
{
    if(type == 1)
    {
        
        CMCommentReplyControl* CommentReplyControl = [[CMCommentReplyControl alloc] init] ;
        CommentReplyControl.type = type;
        CommentReplyControl.title = I(@"回复");
        TCommentItem* item =new TCommentItem() ;
        if(!m_pComment->GetItem(selectedIndex, *item))
        {
            CMRELEASE(CommentReplyControl);
            
            return;
            
        }
        
        
        CommentReplyControl.sreplyid = [NSString stringWithUTF8String:item->sID];
        SAFEDELETE(item);
        
        
        CommentReplyControl.classid = [NSString stringWithUTF8String:m_courseid];
        CommentReplyControl.coursewareid=coursewareID;
        CommentReplyControl.cannotComment = self.cannotComment;
        CommentReplyControl.sflag = m_type;
        CommentReplyControl.sid = [NSString stringWithUTF8String:m_courseid];
        CommentReplyControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        CommentReplyControl.navigationController.navigationBarHidden = NO;
        CommentReplyControl.tabBarController.tabBar.hidden = YES;
        CommentReplyControl.hidesBottomBarWhenPushed = YES;
        CommentReplyControl.commentIndex=selectedIndex;
        CommentReplyControl->m_pComment=m_pComment;
        CommentReplyControl->m_CourseInfo = m_CourseInfo;
        //qasearchcontrol.navigationController.delegate = self;
        //	CommentReplyControl.view.backgroundColor = [UIColor clearColor];
        
        for (UIView *next = [self superview] ; next ; next = next.superview)
        {
            UIResponder *nextResponder = [next nextResponder];
            if ([nextResponder isKindOfClass:[UIViewController class]])
            {
                if (((UIViewController*)nextResponder).navigationController.navigationBar != nil)
                {
                    [((UIViewController*)nextResponder).navigationController pushViewController:CommentReplyControl animated:YES];
                    break;
                }
            }
        }
        
        CMRELEASE(CommentReplyControl);
    }
    else
    {
        
        CMEditCommentControl* CommentReplyControl = [[CMEditCommentControl alloc] init];
        CommentReplyControl.type = type;
//        CommentReplyControl.title = self.title;
        CommentReplyControl.sflag = m_type;
        CommentReplyControl.sid = [NSString stringWithUTF8String:m_courseid];
        CommentReplyControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
        CommentReplyControl.navigationController.navigationBarHidden = NO;
        CommentReplyControl.tabBarController.tabBar.hidden = YES;
        CommentReplyControl.hidesBottomBarWhenPushed = YES;
        //        CommentReplyControl.commentIndex=selectedIndex;
        //        CommentReplyControl->m_pComment=m_pComment;
        //qasearchcontrol.navigationController.delegate = self;
        //	CommentReplyControl.view.backgroundColor = [UIColor clearColor];
        for (UIView *next = [self superview] ; next ; next = next.superview)
        {
            UIResponder *nextResponder = [next nextResponder];
            if ([nextResponder isKindOfClass:[UIViewController class]])
            {
                if (((UIViewController*)nextResponder).navigationController.navigationBar != nil)
                {
                    [((UIViewController*)nextResponder).navigationController pushViewController:CommentReplyControl animated:YES];
                    break;
                }
            }
        }
        
        CMRELEASE(CommentReplyControl);
        
    }
}
-(void)writecomment
{
    //if(!popview.hidden)
    //	popview.hidden = YES;
    
    [self startcomment:2];
}

-(void)showInput
{
    if(inputView.isHidden)
    {
        // inputView.hidden=NO;
        [TableViewList setFrame:CGRectMake(0,0, self.frame.size.width, self.frame.size.height)];
        [inputField becomeFirstResponder];
        
    }else
    {
        // inputView.hidden=YES;
        [TableViewList setFrame:CGRectMake(0,0, self.frame.size.width, self.frame.size.height - kChatInputViewHeight)];
        [inputField resignFirstResponder];
    }
}

-(void)keyboardWillShow:(NSNotification*)notification{
    NSDictionary* info=[notification userInfo];
    CGSize kbSize=[[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;
    NSLog(@"keyboard changed, keyboard width = %f, height = %f",
          kbSize.width,kbSize.height);
    
    keyBoardHieght=[[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size.height;
    [self moveViewToYIn:0.3 yCoordinate:self.bounds.size.height - inputView.frame.size.height-kbSize.height target:inputView];
    //在这里调整UI位置
    backBtn.hidden=NO;
    
}

-(void)moveViewToYIn:(CGFloat)seconds yCoordinate:(CGFloat)y target:(UIView*)view
{
    
    if(!view)
        return;
    __block typeof(self) bself= self;
    
    [UIView animateWithDuration:0.25
                     animations:^{
                         
                         [bself slideViewToY:view yCoordinate:y];
                     } completion:^(BOOL finished){
                         
                         
                     }];
    
    
}
-(void)slideViewToY:(UIView*)v yCoordinate:(CGFloat)y
{
    CGRect navframe=v.frame;
    navframe.origin.y=y;
    v.frame=navframe;
}
-(void)dismissKeyboard
{
    backBtn.hidden=YES;
    [inputField resignFirstResponder];
    [self moveViewToYIn:0.3 yCoordinate:self.bounds.size.height -inputView.frame.size.height target:inputView];
    
    //    [inputView setFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-22-44-45, UI_IOS_WINDOW_WIDTH, 45)];
}


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    
    try {
        if ( !self.cannotComment ) {
            
            //            UIButton *commentBtn = [UIButton buttonWithType:UIButtonTypeCustom];
            //            commentBtn.frame = CGRectMake(0, 0, 40, 44);
            //            [commentBtn setImage:[UIImage imageNamed:@"writecomment"] forState:UIControlStateNormal];
            //            [commentBtn addTarget:self action:@selector(showInput) forControlEvents:UIControlEventTouchUpInside];
            //
            //            UIBarButtonItem *commentBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:commentBtn];
            //            self.navigationItem.rightBarButtonItem = commentBarButtonItem;
            //            CMRELEASE(commentBarButtonItem);
        }
        
        //[tool Wait];
        
        //数据列表

        CGRect f = self.bounds;
        f.size.height = self.bounds.size.height;
        TableViewList = [[CMTableView alloc] initWithFrame:f style:UITableViewStylePlain];
        [TableViewList setDelegate:self];
        [TableViewList setDataSource:self];
        TableViewList.separatorStyle = UITableViewCellSeparatorStyleNone;
        [TableViewList setBackgroundColor:kColorBackground];
        [self setUserInteractionEnabled:YES];
        [self addSubview:TableViewList];
        
        WEAKSELF;
        [TableViewList addPullToRefreshWithActionHandler:^{
            STRONGSELF;
            [sself reloadTableViewDataSource];
        }];
        
        
        dwActiveView = [[UIActivityIndicatorView alloc]init];
        [dwActiveView setActivityIndicatorViewStyle:UIActivityIndicatorViewStyleGray];
        [dwActiveView  stopAnimating];
        
        //		popview = [[UIButton alloc] init];
        //		UIImage*image = [UIImage imageNamed:@"likereply"];
        //		popview.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-image.size.width)/2, 0, image.size.width, image.size.height);
        //        popview.alpha=0;
        //		//popview.hidden = YES;
        //		popview.userInteractionEnabled = YES;
        //		[popview setBackgroundImage:image forState:UIControlStateNormal];
        //		[popview addTarget:self action:@selector(touchBegan:withEvent:) forControlEvents: UIControlEventTouchDown];
        //		[popview addTarget:self action:@selector(touchEnded:withEvent:) forControlEvents: UIControlEventTouchUpInside | UIControlEventTouchUpOutside];
        //		[self.view addSubview:popview];
        
        UILabel* lbRemind = [[UILabel alloc] init];
        lbRemind.text = I(@"沙发好寂寞，说点儿什么吧...");// @"沙发好寂寞,说点儿什么吧...";
        lbRemind.textColor = UIColorRGB(0xb8b8b8);
        lbRemind.font = [UIFont systemFontOfSize:18];
        lbRemind.frame = CGRectMake(0, 40, frame.size.width, 30);
        lbRemind.textAlignment = UITextAlignmentCenter;
        [lbRemind setBackgroundColor:[UIColor clearColor]];
        
        UIImageView* smileview = [[UIImageView alloc] init];
        smileview.image = [UIImage imageNamed:@"smile"];
        smileview.frame = CGRectMake(( frame.size.width-smileview.image.size.width)/2, 120, smileview.image.size.width,  smileview.image.size.height);
        
        bgview = [[UIView alloc] initWithFrame:CGRectMake(0, 0, TableViewList.bounds.size.width, TableViewList.bounds.size.height)];
        [bgview addSubview:lbRemind];
        [bgview addSubview:smileview];
        [TableViewList addSubview:bgview];
        CMRELEASE(lbRemind);
        CMRELEASE(smileview);
        CMRELEASE(bgview);
        bgview.userInteractionEnabled=NO;
        bgview.hidden = YES;
        
        
        //加入退回键盘按钮
        backBtn=[[UIButton alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-44-20)];
        
        [backBtn setBackgroundColor:[UIColor clearColor]];
        
        [backBtn addTarget:self action:@selector(dismissKeyboard) forControlEvents:UIControlEventTouchUpInside];
        backBtn.hidden=YES;
        [self addSubview:backBtn];
        
        //输入部分
        inputView=[self createInputView];
        [self addSubview:inputView];
        if ( !self.cannotComment ) {
            TableViewList.frame = CGRectMake(0, 0, self.bounds.size.width,self.bounds.size.height - kChatInputViewHeight);
        }
        else{
            [inputView setHidden:YES];
        }
        
        
        if (!m_pGetImageListener) {
            m_pGetImageListener = new CMClassInfoCommentGetImageListener();
        }
        
        if (!m_pWebImage) {
            m_pWebImage = new CMWebImage(m_pGetImageListener);
            m_pWebImage->SetUserData((__bridge void*)self);
        }
        
        if (m_pComment== NULL) {
            m_pUpdateDataListener = new CMClassCommentUpdateDataListener();
            //m_pSimpleResultListener = new CMCommentSimpleResultListener();
            m_pRatingListener = new CMClassCommentRatingListener();
            m_pComment = new CMComment();
            m_pComment->setListener(m_pUpdateDataListener, nil, m_pRatingListener);			m_pComment->SetUserData((__bridge void*)self);
        }
        
        if (m_pEditComment== NULL) {
            m_pListener = new CMClassEditCommentSimpleResultListener();
            m_pEditComment = new CMComment();
            m_pEditComment->setListener(nil, m_pListener, nil);
            m_pEditComment->SetUserData((__bridge void*)self);
        }
        //m_pComment->RequestCommentList([m_type UTF8String], m_courseid);
        //写入手动刷新
    }
    catch (NSException* ex) {
        NSLog(@"exception= %@",ex);
    }
    //[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshfunc) name:@"commentrefresh" object:nil];
    
    //testcode
//    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(keyboardWillShow:)name:UIKeyboardWillShowNotification object:nil];
//    [[NSNotificationCenter defaultCenter]removeObserver:self];

    [self dismissKeyboard];
    [inputField resignFirstResponder];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWillShow:)
                                                 name:UIKeyboardWillShowNotification object:nil];
    
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(dismissKeyboard)name:UIKeyboardWillHideNotification object:nil];
    
    return self;
}

- (void)commitMyStars:(id)sender
{
    
    int myStars = [(UIButton*)sender tag];
    CMAlertView *alertView = [[CMAlertView alloc]initWithTitle:I(@"美课")
                                                       message:[NSString stringWithFormat:@"%@%d,%@",I(@"评星分数为"),myStars,I(@"确定提交？")]
                                             cancelButtonTitle:I(@"取消")
                                             otherButtonTitles:I(@"确定")
                                               completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
                                                   if (buttonIndex == BUTTON_CONFIRM_TAG)
                                                   {
                                                       for (int i = 1 ; i <= 5 ; i++)
                                                       {
                                                           UIButton *starBtn = (UIButton*)[self viewWithTag:i];
                                                           [starBtn setImage:i <= myStars ? [UIImage imageNamed:@"star_s"] : [UIImage imageNamed:@"star_n"]
                                                                    forState:UIControlStateNormal];
                                                           starBtn.enabled = NO;
                                                       }
                                                       if (m_pCommitStarListener == nil)
                                                       {
                                                           m_pCommitStarListener = new CMClassCommitStarsSimpleResultListener;
                                                       }
                                                       m_CourseInfo->SetUserData(BridgeObjectToC(self));
                                                       m_CourseInfo->SetListener(nil, nil, m_pCommitStarListener);
                                                       if (m_CourseInfo->CommitStar(myStars))
                                                       {
                                                           [tool ShowActivityIndicator:self];
                                                       }
                                                   };
                                               }];
    [alertView show];
    
    
//    for (int i = 1 ; i <= 5 ; i++)
//    {
//        UIButton *starBtn = (UIButton*)[self viewWithTag:i];
//        [starBtn setImage:i <= myStars ? [UIImage imageNamed:@"star_s"] : [UIImage imageNamed:@"star_n"]
//                 forState:UIControlStateNormal];
//        starBtn.enabled = NO;
//    }
//    if (m_commitStar == nil)
//    {
//        m_commitStar = new TClassItem;
//    }
//    if (m_pCommitStarListener == nil)
//    {
//        m_pCommitStarListener = new CMClassCommitStarsSimpleResultListener;
//    }
//    *m_commitStar = *m_CourseInfo;
//    m_commitStar->SetUserData(BridgeObjectToC(self));
//    m_commitStar->SetListener(nil, nil, m_pCommitStarListener);
//    if (m_commitStar->CommitStar(myStars))
//    {
//        [tool ShowActivityIndicator:self];
//    }
}

-(void)refreshfunc
{
    [self reloadTableViewDataSource];
}


//键盘/表情盘 是否隐藏
- (BOOL)keyBoardHide{
    
    CGFloat inputMainY = CGRectGetMaxY(inputView.frame);
    
    if (__iOS7) {
        //NSLog(@"gaodu:%f",CGRectGetHeight(self.view.frame));
        return (inputMainY == CGRectGetHeight(self.frame));
        
    }else{
        return (inputMainY + 44 == CGRectGetHeight(self.frame));
        
    }
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    
}

- (void)dealloc
{
    SAFEDELETE(m_pGetImageListener);
    SAFEDELETE(m_pWebImage);
    SAFEDELETE(m_pUpdateDataListener);
    SAFEDELETE(m_pRatingListener);
    SAFEDELETE(m_pComment);
    SAFEDELETE(m_pListener);
    SAFEDELETE(m_pEditComment);
    SAFEDELETE(m_pCommitStarListener);
    SAFEDELETE(m_CourseInfo);
    [[NSNotificationCenter defaultCenter]removeObserver:self];
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
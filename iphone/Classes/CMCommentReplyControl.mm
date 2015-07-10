#include "stdafx.h"
#import "CMCommentReplyControl.h"
#import <QuartzCore/QuartzCore.h> 
#import "cmglobal.h"
#import "cmsettings.h"


@implementation CMCommentReplyControl
@synthesize sflag,sid,sreplyid,type,replyList,headView,commentIndex;
@synthesize classid,coursewareid,m_bHasMore;

#define kCellIdentifier @"com.apple.CMClassCommentControl.CellIdentifier"

#define kRefreshCellIdentifier @"com.apple.CMRefreshMoreView.CellIdentifier"


static const int  kChatInputTextViewMaxHeight  = __iOS7 ? 59 : 68;//输入框最大高度
static const int  kChatInputTextViewMinHeight  = __iOS7 ? 29 : 32;//输入框最小高度
#define kChatInputViewHeight 45


- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    //添加键盘通知
	[textcomment becomeFirstResponder];

}
-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [[NSNotificationCenter defaultCenter]postNotificationName:@"AutoFresh" object:nil];
    [self dismissKeyboard];
}

-(void)showInput
{
    if(inputView.isHidden)
    {
        [replyList setFrame:CGRectMake(0,0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-20-44)];

        inputView.hidden=NO;
        [inputField becomeFirstResponder];

    }else
    {
        inputView.hidden=YES;
        [replyList setFrame:CGRectMake(0,0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-20-44)];
        [inputField resignFirstResponder];

    }
}



-(void)doLike:(id)sender event:(id)event
{
    if(CMGlobal::TheOne().IsOffline())
        return;

    
    TCommentItem* item = new TCommentItem();
    
    if (m_pComment) {
        m_pComment->GetItem(commentIndex, *item);
    }
    
    if(item->bIsLiked)
        return;
    
//    [tool Wait];
    
    
    UIButton *tempbtn=(UIButton*)sender;
    UILabel * templbl=(UILabel*)[tempbtn viewWithTag:9];
    
    NSInteger  countlike=[templbl.text integerValue];
    countlike ++;
    [templbl setText:[NSString stringWithFormat:@"%d",countlike]];
    
    [tempbtn setSelected:YES];
    [tempbtn setUserInteractionEnabled:NO];
    
    
    if(!m_pComment->CommentLike([sflag UTF8String],[sid UTF8String],[coursewareid UTF8String],item->sID))
    {
        [tool CancelWait];
    }
    
    SAFEDELETE(item);
    
}


-(void)sendcomment
{

    
    if(!m_pComment)
		return;
    
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
        
        if ( __iPhone4_4S ) {
            [self dismissKeyboard];
        }
        
        NSString *beyond_str = [NSString stringWithFormat:I(@"超出%d个字"),[inputField.text length] - kTextMaxLength];
        [tool ShowAlert:beyond_str];
        return;
    }
    
    BOOL ret = NO;
    
    [tool ShowActivityIndicator:self.view];

    ret = m_pReply->ReplyComment([sflag UTF8String],[sid UTF8String],nil,[sreplyid UTF8String],[inputField.text UTF8String]);
    
    if(ret)
    {
        [self dismissKeyboard];
        [self refreshView];
        inputField.text=@"";
        [inputView setFrameY:UI_IOS_WINDOW_HEIGHT-20-45-44 Height:45];
    }else
    {
        
    }

}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if ([textcomment.text isEqualToString:@""])
    {
        [self SetPlaceholder];    
    }
    [textcomment resignFirstResponder];
}
-(void)refreshView
{
    [replyList reloadData];
    lblcount.text=[NSString stringWithFormat:I(@"%d条回复"),m_pReply->GetItemCount()];
                   
    [replyList setContentOffset:CGPointMake(0, 0) animated:YES];
}
-(UIView*)createHeadView:(TCommentItem*)item
{
    UIImageView* tempHeadView=[[UIImageView alloc]init];
    
    CGFloat headHeight=0;
    
    //添加评论者
    UILabel* lblAuthor=[[UILabel alloc]initWithFrame:CGRectMake(70, 2, 100, 18)];
    [lblAuthor setBackgroundColor:[UIColor clearColor]];
    [lblAuthor setFont:[UIFont systemFontOfSize:14]];
    [lblAuthor setTextAlignment:NSTextAlignmentLeft];
    [lblAuthor setText:[NSString stringWithUTF8String:item->sFullName]];
    [lblAuthor setTextColor:[UIColor colorWithRed:164.0/255.0f green:164.0/255.0f blue:164.0/255.0f alpha:1]];
    [tempHeadView addSubview:lblAuthor];
    CMRELEASE(lblAuthor);
    
    //添加发布时间
    UILabel* lblTime=[[UILabel alloc]initWithFrame:CGRectMake(160, 2, 150, 18)];
    [lblTime setBackgroundColor:[UIColor clearColor]];
    [lblTime setFont:[UIFont systemFontOfSize:14]];
    [lblTime setTextAlignment:NSTextAlignmentRight];
    [lblTime setText:[NSString stringWithUTF8String:item->sDatetime]];
    [lblTime setTextColor:[UIColor colorWithRed:164.0/255.0f green:164.0/255.0f blue:164.0/255.0f alpha:1]];

    [tempHeadView addSubview:lblTime];
    CMRELEASE(lblTime);
    
    //添加头像
    UIImageView* headimg=[[UIImageView alloc]initWithFrame:CGRectMake(10, 5, 50, 50)];
    UIImage* Image;
    if(m_pWebImage->GetFromUrl(0,item->sHeadImage))
    {
       Image =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(item->sHeadImage)]];// m_image;
    }
    else
    {
       Image = [UIImage imageNamed:@"head"];
    }
    
    [headimg setImage:Image];
    
    [tempHeadView addSubview:headimg];
    CMRELEASE(headimg);

    headHeight += 12;
    headHeight += 10;//间距
    
    //添加内容
    CGSize lblsize=[[NSString stringWithUTF8String:item->sComment.c_str()] sizeWithFont:[UIFont systemFontOfSize:16] constrainedToSize:CGSizeMake(UI_IOS_WINDOW_WIDTH-70-10, MAXFLOAT) lineBreakMode:NSLineBreakByWordWrapping];
    
    UILabel* lblComment=[[UILabel alloc]initWithFrame:CGRectMake(70, headHeight, UI_IOS_WINDOW_WIDTH-70-10, lblsize.height)];
    [lblComment setBackgroundColor:[UIColor clearColor]];
    [lblComment setFont:[UIFont systemFontOfSize:16]];
    [lblComment setText:[NSString stringWithUTF8String:item->sComment.c_str()]];
    [lblComment setLineBreakMode:NSLineBreakByWordWrapping];
    [lblComment setNumberOfLines:0];
    [tempHeadView addSubview:lblComment];
    CMRELEASE(lblComment);
    
    headHeight += lblsize.height;
    headHeight += 10;//间距
    
    //添加赞按钮
    btnLike=[[UIButton alloc]initWithFrame:CGRectMake(255, headHeight, 55, 23)];
    [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_nor"] forState:UIControlStateNormal];
    [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_sel"] forState:UIControlStateHighlighted];
    
    [btnLike setBackgroundImage:[UIImage imageNamed:@"btn_sel"] forState:UIControlStateSelected];

    
    [btnLike setImage:[UIImage imageNamed:@"like_nor"] forState:UIControlStateNormal];
    [btnLike setImage:[UIImage imageNamed:@"like_sel"] forState:UIControlStateHighlighted];
    [btnLike setImage:[UIImage imageNamed:@"like_sel"] forState:UIControlStateSelected];

    [btnLike setTag:10];
    [btnLike addTarget:self action:@selector(doLike:event:) forControlEvents:UIControlEventTouchUpInside];

    btnLike.imageEdgeInsets=UIEdgeInsetsMake(0, -25, 0, 0);
    if(item->bIsLiked)
    {
        [btnLike setSelected:YES];
        [btnLike setUserInteractionEnabled:NO];
    }

    //添加赞数量
    lblLikeCount=[[UILabel alloc]initWithFrame:CGRectMake(25, 0, 20, 23)];
    [lblLikeCount setTag:9];
    [lblLikeCount setBackgroundColor:[UIColor clearColor]];
    [lblLikeCount setTextAlignment:NSTextAlignmentCenter];
    [lblLikeCount setText:[NSString stringWithFormat:@"%d",item->npv]];
    [lblLikeCount setFont:[UIFont systemFontOfSize:14]];
    [lblLikeCount setTextColor:[UIColor colorWithRed:164.0/255.0f green:164.0/255.0f blue:164.0/255.0f alpha:1]];
    [btnLike addSubview:lblLikeCount];
    CMRELEASE(lblLikeCount);
    [tempHeadView addSubview:btnLike];
    
    headHeight += btnLike.frame.size.height;
    headHeight += 10;//间距
    
    //添加白色底部
    UIView* backView=[[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, headHeight)];
    [backView setBackgroundColor:[UIColor whiteColor]];
        
    [tempHeadView insertSubview:backView atIndex:0];
    CMRELEASE(backView);
    
    //添加底下
    UIImageView* headBottom=[[UIImageView alloc]initWithFrame:CGRectMake(0, headHeight-1, UI_IOS_WINDOW_WIDTH, 7)];
    [headBottom setImage:[UIImage imageNamed:@"headBottom"]];
//    headBottom.layer.shadowColor=[UIColor blackColor].CGColor;
//	headBottom.layer.shadowOffset=CGSizeMake(0,1);
//	headBottom.layer.shadowOpacity=0.2;
//	headBottom.layer.shadowRadius=1;
//	headBottom.layer.shadowPath = [UIBezierPath bezierPathWithRect:headBottom.bounds].CGPath;
    
    //添加底下数目
    lblcount = [[UILabel alloc]initWithFrame:CGRectMake(140, headHeight-30, 100, 16)];
    
    [lblcount setTextAlignment:NSTextAlignmentRight];
    
    [lblcount setText:[NSString stringWithFormat:@"%d条回复",item->nreply]];
    [lblcount setFont:[UIFont systemFontOfSize:14]];
    [lblcount setBackgroundColor:[UIColor clearColor]];
    [lblcount setTextColor:[UIColor grayColor]];
    [tempHeadView addSubview:lblcount];
    
    [tempHeadView addSubview:headBottom];
    CMRELEASE(headBottom);
    
    [tempHeadView setBackgroundColor:[UIColor clearColor]];
    [tempHeadView setFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, headHeight+7)];
# if ! __has_feature(objc_arc)

    return [tempHeadView autorelease];
#else
    return tempHeadView ;

#endif
    
}

-(UIView*)createInputView
{
    //底
    UIImageView* inputBack=[[UIImageView alloc]initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-45-20, UI_IOS_WINDOW_WIDTH, 45)];
    
    //[inputBack setImage:[UIImage imageNamed:@"replyInput"]];
    [inputBack setFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-20-45-44, UI_IOS_WINDOW_WIDTH, 45)];
    [inputBack setUserInteractionEnabled:YES];
    [inputBack setBackgroundColor:[UIColor colorWithRed:241.0/255.0 green:241.0/255.0 blue:241.0/255.0 alpha:1]];
    
    inputBack.layer.shadowColor=[UIColor grayColor].CGColor;
	inputBack.layer.shadowOffset=CGSizeMake(0,-1);
	inputBack.layer.shadowOpacity=0.4;

//    //输入框
//    inputField=[[UITextField alloc]initWithFrame:CGRectMake(10, 10, 235, 25)];
//        [inputField setBackgroundColor:[UIColor clearColor]];
//    inputField.delegate = self;
//    inputField.font = [UIFont systemFontOfSize:17.0];
//
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
# if ! __has_feature(objc_arc)
    return [inputBack autorelease];
#else
    return inputBack;

#endif
}

-(void)keyboardWillShow:(NSNotification*)notification{
    NSDictionary* info=[notification userInfo];
    CGSize kbSize=[[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;
    NSLog(@"keyboard changed, keyboard width = %f, height = %f",
          kbSize.width,kbSize.height);
    
    keyBoardHieght=[[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size.height;
    [self moveViewToYIn:0.3 yCoordinate:UI_IOS_WINDOW_HEIGHT-20-44-45-kbSize.height target:inputView];
    //在这里调整UI位置
    backBtn.hidden=NO;
    
}

- (void)keyboardWillHide:(NSNotification *)aNotification{
    
    [self dismissKeyboard];
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
    [self moveViewToYIn:0.3 yCoordinate:UI_IOS_WINDOW_HEIGHT-20-44-45 target:inputView];

//    [inputView setFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT-22-44-45, UI_IOS_WINDOW_WIDTH, 45)];
}

- (void)viewDidLoad
{
	[super viewDidLoad];
    
    self.openAutoKeyboard = YES;
    
    self.titleLabel.text = self.navigationItem.title;
    
    m_bHasMore = NO;
    btnMore = nil;
    
    if(!m_pImageListener)
        m_pImageListener = new CMCommentGetImageListener();
    m_pWebImage = new CMWebImage(m_pImageListener);
	m_pWebImage->SetUserData((__bridge void*)self);
    
    TCommentItem* item = new TCommentItem();
    
    if (m_pComment) {
        m_pComment->GetItem(commentIndex, *item);
    }

    self.headView=[self createHeadView:item];
    
    SAFEDELETE(item);
    
    [headView setTag:11];
    
    replyList=[[UITableView alloc]initWithFrame:CGRectMake(0,0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-20-44)];
    
    [replyList setSeparatorStyle:UITableViewCellSelectionStyleNone];
    [replyList setBackgroundColor:[UIColor colorWithRed:240.0/255.0f green:240.0/255.0f blue:240.0/255.0f alpha:1]];

    //45为输入框高度
    [replyList setDelegate:self];
    [replyList setDataSource:self];
    
    [self.view addSubview:replyList];
//    [self.view addSubview:headView];

    //加入退回键盘按钮
    backBtn=[[UIButton alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_VC_HEIGHT)];
    
    [backBtn setBackgroundColor:[UIColor clearColor]];
    
    [backBtn addTarget:self action:@selector(dismissKeyboard) forControlEvents:UIControlEventTouchUpInside];
    backBtn.hidden=YES;
    [self.view addSubview:backBtn];
    
    //输入部分
# if ! __has_feature(objc_arc)
    inputView=[[self createInputView] retain];
    [self.view addSubview:inputView];
    
    if (!self.cannotComment) {
        replyList.frame = CGRectMake(0,0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-20-44-45);
    }
    else{
        [inputView setHidden:YES];
    }
    CMRELEASE(inputView);
#else
    inputView=[self createInputView] ;
    [self.view addSubview:inputView];
    
    
    if (!self.cannotComment) {
        replyList.frame = CGRectMake(0,0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-20-44-45);
    }
    else{
        [inputView setHidden:YES];
    }
#endif
 
    

	CGRect f = self.view.bounds;
	//question
	int h = 20;
	CGRect frame = CGRectMake(20, h,f.size.width-40,100);
	textcomment = [[UITextView alloc] initWithFrame:frame];
    textcomment.layer.borderColor = [UIColor grayColor].CGColor;
    textcomment.layer.borderWidth = 1.0;
    textcomment.layer.cornerRadius = 2.0;
	textcomment.font = [UIFont systemFontOfSize:12.0];
	textcomment.backgroundColor = [UIColor whiteColor];
	//textcomment.autocorrectionType = UITextAutocorrectionTypeNo;
	//textcomment.keyboardType = UIKeyboardTypeDefault;
	textcomment.returnKeyType = UIReturnKeyDone;
	//textFieldFeedback.clearButtonMode = UITextFieldViewModeWhileEditing;	// has a clear 'x' button to the right
	textcomment.delegate = self;
	//[self SetPlaceholder];
    
	if(type == 2)
	{
		frame = CGRectMake(20, h+120, 120, 25.0);
		syncbtn = [[CheckBoxButton alloc] initWithFrame:frame];
		[syncbtn setTitle:I(@"同步提问到问答")];
//		[self.view addSubview:syncbtn];
	}
//	[self.view addSubview:textcomment];
   	if(m_pUpdateListener==NULL)
    {
        m_pUpdateListener= new CMRepalyUpdateListener();
    }
    
    if(m_pListener==NULL)
        m_pListener = new CMCommentReplySimpleResultListener();

    
    
    if (m_pComment== NULL) {
        m_pComment = new CMComment();
        m_pComment->setListener(nil, m_pListener, nil);
		m_pComment->SetUserData((__bridge void*)self);
	}
    
    if(m_pReply==NULL)
    {
        m_pReply = new CMRepalycomment(m_pUpdateListener,m_pListener);
    }

    m_pReply -> SetUserData((__bridge  void*)self);
    
    NSLog(@"sflag:%@   replyid: %@  \n",sflag,sreplyid);
    
    [tool ShowActivityIndicator:self.view];
    if(!m_pReply -> RequestRepalyCommentList([sflag UTF8String], [sreplyid UTF8String]))
    {
        [tool DisimissActivityIndicator];            
    }
    
}

#pragma mark -
#pragma mark UITextView delegate methods

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


#pragma mark -
#pragma mark UITableView delegate methods

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    if(m_pReply)
    {
        NSInteger count=m_pReply->GetItemCount();
        if(count==0)
            return m_pReply->GetItemCount()+1;
        else
        {
            if(m_pReply->IsEnd())
                return m_pReply->GetItemCount()+1;
            else
                return m_pReply->GetItemCount()+2;
        }
    }
    else
        return 1;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{

}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    TRepalymentItem item;
    
    if(indexPath.row==0)
        return headView.frame.size.height;
    
    if(m_pReply)
        m_pReply->GetItem(indexPath.row-1, item);
    if(&item)
    {
        NSString*str =[NSString   stringWithFormat:@"%@: %@",[NSString stringWithUTF8String:item.sFullName],[NSString stringWithUTF8String:item.sComment.c_str()]] ;
      
        return [CMReplyTableViewCell calculateCellHeight:str];
    }
    else
        return 0;
}

- (void)updateData{
    [self.replyList reloadData];
  
    lblcount.text=[NSString stringWithFormat:I(@"%d条回复"),m_pReply->GetItemCount()];
    
}

- (void)refreshCommentList{
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@"1" forKey:@"CommentReplyAdd"];
    
    [tool ShowActivityIndicator:self.view];
    
    if(!m_pReply -> RequestRepalyCommentList([sflag UTF8String], [sreplyid UTF8String]))
    {
        [tool DisimissActivityIndicator];
    }


}

-(void)upDateCourseItemComment
{
    if (m_CourseInfo) {
        m_CourseInfo->Refresh();
        m_CourseInfo->nCommentcount++;
        m_CourseInfo->Update();
    }
}

-(BOOL)RefreshMore
{
	if(!m_pReply->IsEnd())
    {
        return m_pReply->RequestMore();
    }
    
    return NO;
}
-(void)RequestMore:(UITableViewCell*)cell
{
	if (!SETTING.GetAutoLoadMore())
	{
		if(btnMore)
			[btnMore setHidden:YES];
	}
	UIActivityIndicatorView* dwActiveView = [[UIActivityIndicatorView alloc]init];
	[dwActiveView setActivityIndicatorViewStyle:UIActivityIndicatorViewStyleGray];
	
	dwActiveView.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-150)/2, (44-20)/2, 20, 20);
	
	UILabel * lblview = [[UILabel alloc] initWithFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-150)/2+25, (44-20)/2, 150, 20)];
	lblview.text = I(@"加载更多...");// @"加载更多...";
    [lblview setBackgroundColor:[UIColor clearColor]];
	
	[cell.contentView addSubview:dwActiveView];
	[cell.contentView addSubview:lblview];
    CMRELEASE(lblview);
    CMRELEASE(dwActiveView);
	
	cell.selectionStyle = UITableViewCellSelectionStyleNone;
	cell.accessoryType = UITableViewCellAccessoryNone;
	
	[dwActiveView startAnimating];
    
	[self RefreshMore];
}
-(void)RershTableList
{
    activityView = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    activityView.frame = CGRectMake(80.0, 15.0, 10.0, 10.0);
    [btnMore addSubview:activityView];
    [activityView startAnimating];
    CMRELEASE(activityView);
	[self RefreshMore];
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    CMReplyTableViewCell *cell = (CMReplyTableViewCell*)[tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
    
    if (cell == nil) {
# if ! __has_feature(objc_arc)
        cell = [[[CMReplyTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifier] autorelease];
# else
         cell = [[CMReplyTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifier];
# endif
    }
   
    [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
    [cell.LeftImageView setHidden:NO];
    [cell.sep setHidden:NO];
    cell.backgroundColor = [UIColor clearColor];

    if([cell.contentView viewWithTag:10]!=nil)
    {
     UIView* tempv=   [cell.contentView viewWithTag:10];
        [tempv removeFromSuperview];
    }
    
    if([cell.contentView viewWithTag:11]!=nil)
    {
        UIView* tempv=   [cell.contentView viewWithTag:11];
        [tempv removeFromSuperview];
    }

    if(indexPath.row==0)    {
        
        TCommentItem *item = new TCommentItem();
        
        if (m_pComment) {
            m_pComment->GetItem(commentIndex, *item);
        }
        
        cell.lblcomment.text=@"";
        cell.lbltime.text=@"";
        [cell.LeftImageView setHidden:YES];
        [cell.sep setHidden:YES];
        [cell.contentView addSubview:headView];
        [cell.contentView addSubview:btnLike];
      //  [lblcount setText:[NSString stringWithFormat:@"%d条回复",item->nreply]];
        SAFEDELETE(item);
        return cell;
    }
    
    
    
    if (indexPath.row == m_pReply->GetItemCount()+1 &&  m_pReply->GetItemCount()!= 0)
    {
        UITableViewCell *lastcell = (UITableViewCell*)[tableView dequeueReusableCellWithIdentifier:kRefreshCellIdentifier];
        
        if (lastcell == nil) {
# if ! __has_feature(objc_arc)
            lastcell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kRefreshCellIdentifier] autorelease];
# else
           lastcell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kRefreshCellIdentifier];
# endif
        }
        
        if(SETTING.GetAutoLoadMore())
            [self RequestMore:lastcell];
        else
        {
            
            btnMore = [UIButton buttonWithType:UIButtonTypeCustom];
            [btnMore setImage:[UIImage imageNamed:@"Load_More_nor"] forState:UIControlStateNormal];
            [btnMore setImage:[UIImage imageNamed:@"Load_More_sel"] forState:UIControlStateHighlighted];
            
            [btnMore addTarget:self action:@selector(RershTableList) forControlEvents:UIControlEventTouchUpInside];
			
            [btnMore setHidden:NO];
            btnMore.frame = CGRectMake(15, 1.5, 290, 44);
            [lastcell.contentView addSubview:btnMore];
			
            lastcell.selectionStyle = UITableViewCellSelectionStyleNone;
            lastcell.accessoryType = UITableViewCellAccessoryNone;
        }
        return lastcell;
        
    }

    
    TRepalymentItem item;
    m_pReply->GetItem(indexPath.row-1,item);
    
    if(&item)
    {
        [cell setcellinfo:item];
    }
    return cell;
}

- (void)viewDidUnload
{

	[super viewDidUnload];
}
- (BOOL)textViewShouldBeginEditing:(UITextView *)textView
{
	if(textcomment.tag == 1)
	{
		textcomment.text = @"";
		textcomment.tag = 2;
		textcomment.textColor = [UIColor blackColor];
	}
	return YES;
}
//- (void)textViewDidChange:(UITextView *)textView
//{
//	if(textquestion.text.length == 0)
//	{
//		[self SetPlaceholder];
//		[textquestion resignFirstResponder];
//	}
//}
-(void)SetPlaceholder
{

	textcomment.textColor = [UIColor lightGrayColor];
	if(type == 2)
		textcomment.text = I(@"添加评论不超过200个字");// @"添加评论不超过140个字";
	else
		textcomment.text = I(@"回复评论不超过200个字");// @"回复评论不超过140个字";
	textcomment.tag = 1;
}
- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{	
	if([text isEqualToString:@"\n"])
	{
		[textcomment endEditing:YES];
		if(textcomment.text.length == 0)
			[self SetPlaceholder];
		return NO;
	}
//	if(range.location >= 140)
//		return NO;  
//	if([textView.text length] == 1 && range.length == 1 && [text length] == 0)
//	{
//		[self SetPlaceholder];
//		[textcomment resignFirstResponder];
//	}
//	else if(textcomment.tag == 1)
//	{
//		textcomment.text = @"";
//		textcomment.tag = 2;
//		textcomment.textColor = [UIColor blackColor];
//	}

	return YES;
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


- (void)dealloc
{
    
    
    SAFEDELETE(m_pUpdateListener);
    SAFEDELETE(m_pImageListener);
    SAFEDELETE(m_pListener);

    SAFEDELETE(m_pReply);
    CMRELEASE(textcomment);
    CMRELEASE(syncbtn);
# if ! __has_feature(objc_arc)
	[super dealloc];
# endif
}
@end
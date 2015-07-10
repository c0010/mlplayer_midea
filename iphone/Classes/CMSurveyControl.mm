 //
//  CMSurveyControl.m
//  MLPlayer
//
//  Created by sunjj on 11-5-4.
//  Copyright 2011 w. All rights reserved.
//

#import "CMSurveyControl.h"
#import <QuartzCore/QuartzCore.h> 

#define kCellIdentifierEdit @"surveycelledit"
#define kCellIdentifierCheck @"surveycellcheck"

@interface CMSurveyControl ()
-(void)Commit;
- (void)cofigureCell:(UITableViewCell*)cell forIndexPath:(NSIndexPath*)indexPath;
@end
@implementation CMSurveyControl
@synthesize isDataReady;

@synthesize tableView;
@synthesize answerView;
@synthesize words_Num;



-(void)hidenKeyboard
{
    [self.view removeGestureRecognizer:textViewGesture];
    
    [answerView resignFirstResponder];
}

- (void)keyboardWillShow:(NSNotification *)aNotification {
    NSDictionary *info = [aNotification userInfo];
    
    //获取高度
    NSValue *value = [info objectForKey:@"UIKeyboardBoundsUserInfoKey"];
    CGSize keyboardSize = [value CGRectValue].size;
    keyboardHeight = keyboardSize.height;

}


- (void)textViewDidBeginEditing:(UITextView *)textView
{
    
    UITapGestureRecognizer *gesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(hidenKeyboard)];
    gesture.numberOfTapsRequired = 1;
    textViewGesture=gesture;
    [self.view addGestureRecognizer:gesture];
    
}

- (void)textViewDidEndEditing:(UITextView *)textView
{
	TSurveyItem item ;
	if(m_survey && m_survey->GetCurItem(item))
	{
		if(item.nType == TSurveyQuestionType::EText)
		{
			m_survey->SetAnswer([[self answerView].text UTF8String]);
		}
	}
    
    [self.view removeGestureRecognizer:textViewGesture];

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
	
//	if(range.location >= 50)
//		return NO; // return NO to not change text
    // For any other character return TRUE so that the text gets added to the view
    return YES;
}

- (void)textViewDidChange:(UITextView *)textView
{
	[self remindWordLabel:textView.text];
}

- (void)remindWordLabel:(NSString *)string{
    input_words_num = [string length];
    @autoreleasepool {
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
    }
}


-(void)OpenSurvey:(NSString*)title surveyid: (const char*)surveyid
{
	[self setTitle:title];
	if(m_survey == nil)
	{
		m_pUpdateDataListener=new CMSurveyUpdateDataListener();
		m_pSimpleResultListener = new CMSurveySimpleResultListener();
		
		m_survey =new CMSurvey(m_pUpdateDataListener,m_pSimpleResultListener);
		m_survey->SetUserData(BridgeObjectToC(self));
		m_survey->GetSurvey(surveyid);
        
        [tool ShowActivityIndicator:self.view];
	}
}

-(void)UpdateView
{
	toolbar.hidden = NO;
    
	TSurveyItem item ;
	if(m_survey && m_survey->GetCurItem(item))
	{
		if(item.nType == TSurveyQuestionType::EText)			
			[[self tableView] setAllowsSelection: NO];
		else
			[[self tableView] setAllowsSelection: YES];
	}	
	int curindex = m_survey->GetCurIndex();
	int itemcount = m_survey->GetItemCount();
	
	if (itemcount >=1 ) {
		
		if(curindex == itemcount-1)
		{
			[nextbtn setTitle:I(@"完成") forState:UIControlStateNormal];
			
		}else {
			[nextbtn setTitle:I(@"下一题") forState:UIControlStateNormal];
		}
	}
    self.tableView.contentOffset = CGPointMake(.0, .0);
	[self.tableView reloadData];
}

-(void)prevQ
{
    if(!isDataReady)
        return;
    
    if (isBeyond) {
        NSUInteger Beyond_words = input_words_num - kTextMaxLength;
        [tool ShowAlert:[NSString stringWithFormat:I(@"超出%d个字"),Beyond_words]];
        return;
    }
    
	if(m_survey && !m_survey->Prev())
    {
        [tool ShowAlert:I(@"已至第一页！")];
    }
    
	[self UpdateView];
}

-(void)nextQ
{
    if(!isDataReady)
        return;
    
    if (isBeyond) {
        NSUInteger Beyond_words = input_words_num - kTextMaxLength;
        [tool ShowAlert:[NSString stringWithFormat:I(@"超出%d个字"),Beyond_words]];
        return;
    }
    
	if(m_survey)
	{
		if (!m_survey->GetCurIsAchieve())
        {
			[tool ShowAlert:I(@"请选择答案")];
			return;
		}
		
		if(m_survey->Next() == FALSE)
		{
            WEAKSELF;
            CMAlertView *alert = [[CMAlertView alloc] initWithTitle:I(@"确定提交？") message:nil cancelButtonTitle:I(@"取消") otherButtonTitles:I(@"确定") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
                STRONGSELF;
                if (buttonIndex == CMAlertViewOk)
                {
                    [sself Commit];
                }
            }] ;
            [alert setDisabledOutSide:YES];
            [alert show];
		}
	}
	[self UpdateView];
}

- (void)viewWillDisappear:(BOOL)animated
{
    //保存状态
    if(m_survey)
        m_survey->SaveStatus();
    
    [super viewWillDisappear:animated];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    self.isDataReady=NO;

    NSNotificationCenter *defaultCenter = [NSNotificationCenter defaultCenter];
    [defaultCenter addObserver:self
                      selector:@selector(keyboardWillShow:)
                          name:UIKeyboardWillShowNotification
                        object:nil];
    
	CGRect viewframe = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT - 64 - 44);
    
    if (__iOS7)
    {
        //viewframe = CGRectMake(0, -35, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT - 64 - 44 + 35);
    }
	tableView = [[UITableView alloc] initWithFrame:viewframe style:UITableViewStyleGrouped] ;
	[tableView setBackgroundColor:[UIColor clearColor]];
	tableView.separatorColor = [UIColor clearColor];
    
    UIView *bakgroundView=[[UIView alloc]initWithFrame:self.view.bounds];
    [bakgroundView setBackgroundColor:kColorBackground];
    [tableView setBackgroundView:bakgroundView];
	[self.tableView setDelegate:self];
	[self.tableView setDataSource:self];
    
	[self.view addSubview:tableView];
	
	UIImageView * toolbarbak= [[UIImageView alloc]initWithFrame:CGRectMake(0, -3.5, UI_IOS_WINDOW_WIDTH, 51.5)];
    [toolbarbak setImage:[UIImage imageNamed:@"bottombk"]];
    
	toolbar = [[UIToolbar alloc] initWithFrame:CGRectMake(0, UI_IOS_WINDOW_HEIGHT - 44-48-20, UI_IOS_WINDOW_WIDTH, 48)];
    [toolbar setContentMode:UIViewContentModeScaleAspectFill];
	toolbar.backgroundColor = [UIColor clearColor];
    
    if (!__iOS7)
    {
        [toolbar addSubview:toolbarbak];
    }
	[self.view addSubview:toolbar];
	
	prebtn = [[ComplexButton alloc] init];
	prebtn.frame = CGRectMake(0, 0, 80, 44);
	[prebtn setTitle:I(@"上一题") forState:UIControlStateNormal];
	[prebtn setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
	[prebtn setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateHighlighted];
	[prebtn setImage:[UIImage imageNamed:@"pre_n"] forState:UIControlStateNormal];
	[prebtn setImage:[UIImage imageNamed:@"pre_p"] forState:UIControlStateHighlighted];
	[prebtn addTarget:self action:@selector(prevQ) forControlEvents:UIControlEventTouchUpInside];
	
	UIBarButtonItem*prevBarItem = [[UIBarButtonItem alloc] initWithCustomView:prebtn];

	nextbtn = [[ComplexButton alloc] init];
	nextbtn.frame = CGRectMake(0, 0, 80, 44);
	[nextbtn setTitle:I(@"下一题") forState:UIControlStateNormal];
	[nextbtn setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
	[nextbtn setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateHighlighted];
	[nextbtn setImage:[UIImage imageNamed:@"next_n"] forState:UIControlStateNormal];
	[nextbtn setImage:[UIImage imageNamed:@"next_p"] forState:UIControlStateHighlighted];
	[nextbtn addTarget:self action:@selector(nextQ) forControlEvents:UIControlEventTouchUpInside];
	
	UIBarButtonItem*nextBarItem = [[UIBarButtonItem alloc] initWithCustomView:nextbtn];
	
	UIBarButtonItem*FlexibleBarItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:self action:nil];
	
	[toolbar setItems:[NSArray arrayWithObjects:prevBarItem,FlexibleBarItem,nextBarItem,nil]];

	[prebtn setEnabled:YES];
	[nextbtn setEnabled:YES];
	toolbar.hidden = YES;

	tableView.userInteractionEnabled = YES;
	UISwipeGestureRecognizer *horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];  
	horizontal.direction = UISwipeGestureRecognizerDirectionLeft;  
	[tableView addGestureRecognizer:horizontal];
	
	horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];  
	horizontal.direction = UISwipeGestureRecognizerDirectionRight;  
	[tableView addGestureRecognizer:horizontal];
}

- (void)reportHoriziontalSwipe:(UISwipeGestureRecognizer *)tap
{
	if(!m_survey || m_survey->GetItemCount() <= 0)
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

#pragma mark UITableView delegate methods

// the table's selection has changed, switch to that item's UIViewController
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	TSurveyItem item ;
	if(m_survey && m_survey->GetCurItem(item))
	{
		if(item.nType != TSurveyQuestionType::EText)
		{
			TSurveyOption item;
			if(m_survey && m_survey->GetItemOption(indexPath.row, item))
			{		
				UITableViewCell* cell = [self.tableView cellForRowAtIndexPath:indexPath]; 
				if(cell)
				{
					m_survey->SetAnswer(indexPath.row, !item.bCheck);
					[self.tableView reloadData];
				}
			}
		}
	}
}

#pragma mark UITableView data source methods

// tell our table how many sections or groups it will have (always 1(our case)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	TSurveyItem item ;
	if(m_survey && m_survey->GetCurItem(item))
	{
		if(item.nType == TSurveyQuestionType::EText)
			return 1;
		else
			return m_survey->GetItemOptionCount();
	}
	else
		return 1;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section;
{
	if(section == 0)
	{
		TSurveyItem items ;
		if(m_survey && m_survey->GetCurItem(items))
		{
			NSString* str = @"[单选题]";//用于计算高度
			if(strlen(items.sCategory.c_str()) > 0)
				str = [str stringByAppendingString:[[[NSString stringWithUTF8String:items.sCategory.c_str()] stringByAppendingString:@"\n"] stringByAppendingString:[NSString stringWithUTF8String:items.sQuestion.c_str()]]];
			else
				str = [str stringByAppendingString:[NSString stringWithUTF8String:items.sQuestion.c_str()]];
			UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
			CGSize constraintSize = CGSizeMake(self.tableView.frame.size.width-20, MAXFLOAT);
			CGSize labelSize = [str sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
			return labelSize.height + 20;			
		}
		return 10.0;
	}
	return 150.0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
	// create the parent view that will hold header Label
	UIView* customView = nil;
	customView = [[UIView alloc] initWithFrame:CGRectMake(10.0, 0.0, self.tableView.frame.size.width-20, 150.0)];
	
	customView.backgroundColor=[UIColor clearColor];
	UILabel * headerLabel = [[UILabel alloc] initWithFrame:CGRectZero];
	headerLabel.backgroundColor = [UIColor clearColor];
	headerLabel.opaque = NO;
	headerLabel.textColor = UIColorRGB(0x2e2e2e);
	headerLabel.highlightedTextColor = [UIColor whiteColor];
	headerLabel.font = [UIFont systemFontOfSize:15];
	headerLabel.lineBreakMode = UILineBreakModeCharacterWrap;
	headerLabel.numberOfLines = 0;
	
	TSurveyItem items ;
	float Labelheight = 10.0;
	if(m_survey && m_survey->GetCurItem(items))
	{
        NSString *headerStr;
        if (items.nType == TSurveyQuestionType::ESingle)
        {
            headerStr = I(@"[单选]");
        }
        else if (items.nType == TSurveyQuestionType::EMultiple)
        {
            headerStr = I(@"[多选]");
        }
        else if (items.nType == TSurveyQuestionType::EText)
        {
            headerStr = I(@"[填空]");
        }
		if(strlen(items.sCategory.c_str()) > 0)
		{
            headerStr = [headerStr stringByAppendingString:[[[NSString stringWithUTF8String:items.sCategory.c_str()] stringByAppendingString:@"\n"] stringByAppendingString:[NSString stringWithUTF8String:items.sQuestion.c_str()]]];
//			headerLabel.text = [[[NSString stringWithUTF8String:items.sCategory.c_str()] stringByAppendingString:@"\n"] stringByAppendingString:[NSString stringWithUTF8String:items.sQuestion.c_str()]];
				//headerLabel.numberOfLines = 2;
		}
		else
        {
            headerStr = [headerStr stringByAppendingString:[NSString stringWithUTF8String:items.sQuestion.c_str()]];
//			headerLabel.text = [NSString stringWithUTF8String:items.sQuestion.c_str()];
			//headerLabel.numberOfLines = 2;
		}
        NSMutableAttributedString *attrbutedString = [[NSMutableAttributedString alloc]initWithString:headerStr];
        [attrbutedString addAttribute:NSForegroundColorAttributeName value:kColorButtonTitle range:NSMakeRange(0,4)];
        headerLabel.attributedText = attrbutedString;
        
		UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
		CGSize constraintSize = CGSizeMake(self.tableView.frame.size.width-20, MAXFLOAT);
		CGSize labelSize = [headerLabel.text sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
		Labelheight = labelSize.height + 10;
        
        CGRect frame = CGRectMake(10.0, 10.0, self.tableView.frame.size.width-20, Labelheight);
        headerLabel.frame = frame;
        customView.frame = frame;
        
        [customView addSubview:headerLabel];
        if(items.nType != TSurveyQuestionType::EText)
        {
            UIView* sepview = [[UIView alloc] init];
            sepview.backgroundColor = kTextColorNormal;
            sepview.frame = CGRectMake(0, frame.origin.y+frame.size.height, self.tableView.frame.size.width, 1);
            [customView addSubview:sepview];
        }
	}
    return customView;
}

// to determine specific row height for each cell, override this.
// In this example, each row is determined by its subviews that are embedded.
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	TSurveyItem items ;
	if(m_survey && m_survey->GetCurItem(items))
	{
		if(items.nType == TSurveyQuestionType::EText)
		{
			return 140.0;
		}
        else
        {
            TSurveyOption item ;
            if(m_survey && m_survey->GetItemOption(indexPath.row, item))
            {
                UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
                CGSize constraintSize = CGSizeMake(self.tableView.frame.size.width-50, MAXFLOAT);
                CGSize labelSize = [[NSString stringWithUTF8String:item.sText.c_str()] sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
                return labelSize.height + 40;
            }
        }
	}
    
    return 0;
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	TSurveyItem items;
    
	if(m_survey && m_survey->GetCurItem(items))
	{
		if(items.nType == TSurveyQuestionType::EText)	//题目为填空题
		{
            UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifierEdit];
            
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
            [cell.contentView addSubview:answerView];
            
            words_Num = [[UILabel alloc]initWithFrame:CGRectMake(0, 120, cellWidth-5, 20)];
            words_Num.backgroundColor = [UIColor clearColor];
            words_Num.font = [UIFont systemFontOfSize:12.0];
            words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
            words_Num.text = [NSString stringWithFormat:I(@"还能输入%d个字"),100];
            words_Num.textAlignment = UITextAlignmentRight;
            [cell.contentView addSubview:words_Num];
            
            [answerView setText:[NSString stringWithUTF8String:items.sAnswer.c_str()]];
            [answerView setBackgroundColor:[UIColor clearColor]];
            [self remindWordLabel:answerView.text];
            
            return cell;
        }
        else
        {
            UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCellIdentifierCheck];
            
            cell.accessoryType = UITableViewCellAccessoryNone;
            cell.selectionStyle = UITableViewCellSelectionStyleNone;
            
            TSurveyOption item ;
			if(m_survey && m_survey->GetItemOption(indexPath.row, item))
			{
				UILabel*lbtxt = [[UILabel alloc] init];
				lbtxt.textColor = [UIColor blackColor];
				lbtxt.highlightedTextColor = [UIColor blackColor];
				lbtxt.font = [UIFont systemFontOfSize:15.0];
				lbtxt.numberOfLines = 0;
				lbtxt.text = [NSString stringWithUTF8String:item.sText.c_str()];
                [lbtxt setBackgroundColor:[UIColor clearColor]];
                
                UIImageView *imageView = [[UIImageView alloc] init];
                
                if (item.bCheck) //选中
                {
                    if(items.nType == TSurveyQuestionType::ESingle/* || items.nType == TSurveyQuestionType::EYesNo*/)
                        imageView.image = [UIImage imageNamed:@"examradio"];
                    else
                        imageView.image = [UIImage imageNamed:@"examcheck"];
                }
                else
                {
                    if(items.nType == TSurveyQuestionType::ESingle/* || items.nType == TSurveyQuestionType::EYesNo*/)
                        imageView.image = [UIImage imageNamed:@"examunradio"];
                    else
                        imageView.image = [UIImage imageNamed:@"examuncheck"];
                }
				
				UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
				CGSize constraintSize = CGSizeMake(self.tableView.frame.size.width-50, MAXFLOAT);
				CGSize labelSize = [lbtxt.text sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
				int hg = labelSize.height+40;
                imageView.frame = CGRectMake(10, (hg-24)/2, 24, 24);
				lbtxt.frame = CGRectMake(40, 20, self.tableView.frame.size.width-50, labelSize.height);
				UIImageView* lv = [[UIImageView alloc] init];
				lv.image = [UIImage imageNamed:@"examsep"];
				lv.frame = CGRectMake(10, hg-1, self.tableView.frame.size.width-20, 1);
				[cell.contentView addSubview:imageView];
				[cell.contentView addSubview:lbtxt];
				[cell.contentView addSubview:lv];
            }
            
            return cell;
        }
    }
    
    UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"nilcell"];
    return cell;
}

- (void)cofigureCell:(UITableViewCell*)cell forIndexPath:(NSIndexPath*)indexPath {
	TSurveyItem items ;
	if(m_survey && m_survey->GetCurItem(items))
	{
		if(items.nType == TSurveyQuestionType::EText)			
		{
			[self answerView];
			//answerView.text = @"";
            
            [cell addSubview:bg_view];
			[cell addSubview:answerView];
            [cell addSubview:words_Num];
            [answerView setText:[NSString stringWithUTF8String:items.sAnswer.c_str()]];
            [self remindWordLabel:answerView.text];
		}
		else
		{
			TSurveyOption item ;
			if(m_survey && m_survey->GetItemOption(indexPath.row, item))
			{
				UIButton* btn = [self GetBtn:item.bCheck type:items.nType];
				UILabel*lbtxt = [[UILabel alloc] init];
                [lbtxt setBackgroundColor:[UIColor clearColor]];
				lbtxt.textColor = [UIColor blackColor];
				lbtxt.highlightedTextColor = [UIColor blackColor];
				lbtxt.font = [UIFont systemFontOfSize:15.0];
				lbtxt.numberOfLines = 0;
				lbtxt.text = [NSString stringWithUTF8String:item.sText.c_str()];
				
				UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
				CGSize constraintSize = CGSizeMake(self.tableView.frame.size.width-50, MAXFLOAT);
				CGSize labelSize = [lbtxt.text sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
				int hg = labelSize.height+40;
				btn.tag = indexPath.row;
				btn.frame = CGRectMake(10, (hg-24)/2, 24, 24);
				lbtxt.frame = CGRectMake(40, 20, self.tableView.frame.size.width-50, labelSize.height);
				UIImageView* lv = [[UIImageView alloc] init];
				lv.image = [UIImage imageNamed:@"examsep"];
				lv.frame = CGRectMake(10, hg-1, self.tableView.frame.size.width-20, 1);
				[cell addSubview:btn];
				[cell addSubview:lbtxt];
				[cell addSubview:lv];
			}
		}
	}
	cell.accessoryType = UITableViewCellAccessoryNone;
	cell.selectionStyle = UITableViewCellSelectionStyleNone;
    //cell.backgroundColor=[UIColor colorWithRed:247.0f/255.0f green:247.0f/255.0f blue:247.0f/255.0f alpha:1];
}
-(void)click:(id)sender
{
	UIButton *tempButton = (UIButton*)sender;
	TSurveyOption item ;
	if(m_survey && m_survey->GetItemOption(tempButton.tag, item))
	{		
		m_survey->SetAnswer(tempButton.tag, !item.bCheck);
		[tableView reloadData];
	}
}
-(UIButton*)GetBtn:(bool)bcheck type:(int)ntype
{
	UIButton *tempButton = [UIButton buttonWithType:UIButtonTypeCustom];
	if (bcheck) 
	{
		if(ntype == TSurveyQuestionType::ESingle/* || ntype == TSurveyQuestionType::EYesNo*/)
			[tempButton setImage:[UIImage imageNamed:@"examradio"] forState:UIControlStateNormal];
		else 
			[tempButton setImage:[UIImage imageNamed:@"examcheck"] forState:UIControlStateNormal];
		
	}
	else
	{
		if(ntype == TSurveyQuestionType::ESingle/* || ntype == TSurveyQuestionType::EYesNo*/)
			[tempButton setImage:[UIImage imageNamed:@"examunradio"] forState:UIControlStateNormal];
		else 
			[tempButton setImage:[UIImage imageNamed:@"examuncheck"] forState:UIControlStateNormal];
	}
	[tempButton addTarget:self action:@selector(click:) forControlEvents:UIControlEventTouchUpInside];
	return tempButton;
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

- (void)Commit
{
	if(m_survey)
	{
        
        if (isBeyond) {
            NSUInteger Beyond_words = input_words_num - kTextMaxLength;
            [tool ShowAlert:[NSString stringWithFormat:I(@"超出%d个字"),Beyond_words]];
            return;
        }
        
        [tool ShowBeforeBack];

		m_survey->CommitAnswer();
	
	}
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {

    [self.view removeGestureRecognizer:textViewGesture];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];

    
	SAFEDELETE(m_pUpdateDataListener);
	SAFEDELETE(m_pSimpleResultListener);
	SAFEDELETE(m_survey);
	CMRELEASE(bg_view);
	CMRELEASE(answerView);
    CMRELEASE(words_Num);
    CMRELEASE(bg_view);
    CMRELEASE(toolbar);

}


@end


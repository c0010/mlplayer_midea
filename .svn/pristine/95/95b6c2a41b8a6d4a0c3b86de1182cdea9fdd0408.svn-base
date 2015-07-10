
#import "CMFeedbackControl.h"

#define FEEDBACK_WORDNUM   50

const NSInteger kViewTag = 1;

@implementation CMFeedbackControl

@synthesize textFieldFeedback,CommitButton;
@synthesize FeedbackTableView,words_Num;


- (void)dealloc
{
    CMRELEASE(bg_view);
	CMRELEASE(FeedbackTableView);	
	CMRELEASE(textFieldFeedback);
    CMRELEASE(words_Num);
	SAFEDELETE(m_pListener);
	SAFEDELETE(m_pFeedback);
}

-(void)updateWordCount:(NSString*)text
{
    
    input_words_num = [text length];
    if (input_words_num <= FEEDBACK_WORDNUM) {
        NSUInteger Remaining_words = FEEDBACK_WORDNUM - input_words_num;
        words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
        isBeyond = NO;
        words_Num.text=[NSString stringWithFormat:I(@"还能输入%d字"),Remaining_words];
    }
    else{
        NSUInteger Beyond_words = input_words_num - FEEDBACK_WORDNUM;
        words_Num.textColor = [UIColor redColor];
        isBeyond = YES;
        words_Num.text=[NSString stringWithFormat:I(@"超过%d字"),Beyond_words];
    }
    
}

- (void)textViewDidChange:(UITextView *)textView
{
    [self updateWordCount:textView.text];
}

- (void)viewWillAppear:(BOOL)animated {
	
	[super viewWillAppear:animated];
}

- (void)viewDidLoad
{
	[super viewDidLoad];
    
    self.navigationController.navigationBarHidden = NO;
    
    //保存到本地
    CMString sPath = CMGlobal::TheOne().GetUserDir() + L"feedback.plist";
    
    filePath = [[NSString alloc] initWithUTF8String:(const char*)sPath];
    
    UIView *bakview=[[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT)];
    
	self.FeedbackTableView.backgroundColor= UIColorRGB(0xf5f5f5);
	self.view.backgroundColor=UIColorRGB(0xf5f5f5);
	
	FeedbackTableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT - 64) style:UITableViewStyleGrouped];
	FeedbackTableView.backgroundColor=UIColorRGB(0xf5f5f5);
	[FeedbackTableView setDelegate:self];
	[FeedbackTableView setDataSource:self];
    FeedbackTableView.separatorStyle =UITableViewCellSeparatorStyleNone;
    [FeedbackTableView setBackgroundView:bakview];
    
	[self.view addSubview:FeedbackTableView];
	
	[FeedbackTableView reloadData];
}


- (void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    
    CMString sPath = CMGlobal::TheOne().GetUserDir() + L"feedback.plist";
    
    NSString* _filePath = [NSString stringWithUTF8String:(const char*)sPath];

    NSMutableDictionary *data = [NSMutableDictionary dictionaryWithObjectsAndKeys:self.textFieldFeedback.text,@"feedback", nil];
    
    [data writeToFile:_filePath atomically:YES];

}

-(IBAction)btnCommit:(id) sender
{
    if (CMGlobal::TheOne().IsOffline()) {
        [tool ShowError:-1];
        return;
    }
    
	if ([textFieldFeedback.text length] == 0)
	{
		[tool ShowAlert:I(@"建议不能为空！")];
		return;
	}
    
    NSString *content = [textFieldFeedback.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
    if([content isEqualToString:@""]){
        textFieldFeedback.text = @"";
        [tool ShowAlert:@"建议不能为空！"];
        return;
    }
    
    
    if ([textFieldFeedback.text length] > FEEDBACK_WORDNUM) {
        [tool ShowAlert:words_Num.text];
        return;
    }
    
	m_pListener = new CMFeedbackListener();
	m_pFeedback = new CMFeedback(m_pListener);
	m_pFeedback->SetUserData(BridgeObjectToC(self));
	m_pFeedback->CommitFeedback([textFieldFeedback.text UTF8String],"");
    
    UIButton *btn = (UIButton*)sender;
    btn.enabled = NO;
}


- (void)viewDidUnload
{
	[super viewDidUnload];
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{	
	if([text isEqualToString:@"\n"])
	{
		[textView endEditing:YES];
		
		return NO;
	}
    
	return YES;
}
	

#pragma mark -
#pragma mark UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	return 1;
}

// to determine specific row height for each cell, override this.
// In this example, each row is determined by its subviews that are embedded.
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 90.0;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
	return 40.0;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    // create the parent view that will hold header Label
    UIView* customView = [[UIView alloc] initWithFrame:CGRectMake(10.0, 0.0, UI_IOS_WINDOW_WIDTH-20, 40.0)];
	
	customView.backgroundColor=[UIColor clearColor];
	
    // create the button object
    UILabel * headerLabel = [[UILabel alloc] init];
    headerLabel.frame = CGRectMake(10.0, 0.0, UI_IOS_WINDOW_WIDTH - 20, 40.0);
    headerLabel.backgroundColor = [UIColor clearColor];
    headerLabel.opaque = NO;
    headerLabel.textColor = [UIColor blackColor];
    headerLabel.highlightedTextColor = [UIColor whiteColor];
    headerLabel.font = [UIFont systemFontOfSize:14];
	headerLabel.lineBreakMode = UILineBreakModeCharacterWrap;
	headerLabel.textAlignment = UITextAlignmentCenter;
    headerLabel.text = I(@"您的意见和建议是我们前进的动力，谢谢。");
    headerLabel.numberOfLines = 2;
	
    [customView addSubview:headerLabel];
    
    return customView;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 80;
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section
{
    UIView* customView = [[UIView alloc] initWithFrame:CGRectMake(0.0, 0.0, UI_IOS_WINDOW_WIDTH, 80)];
    
    CommitButton= [UIButton buttonWithType:UIButtonTypeCustom];
    UIImage* image = [UIImage imageNamed:@"feedback_n"];
    CommitButton.frame = CGRectMake((UI_IOS_WINDOW_WIDTH - image.size.width)/2, 200, image.size.width, image.size.height);
    CommitButton.frame = CGRectMake((UI_IOS_WINDOW_WIDTH - image.size.width)/2, 20, image.size.width, image.size.height);
    [CommitButton setBackgroundImage:image forState:UIControlStateNormal];
    image = [UIImage imageNamed:@"feedback_p"];
    [CommitButton setBackgroundImage:image forState:UIControlStateHighlighted];
    [CommitButton addTarget:(id)self action:@selector(btnCommit:) forControlEvents:UIControlEventTouchUpInside];
    CommitButton.tag=kViewTag;
    CommitButton.userInteractionEnabled=YES;
    [CommitButton setAccessibilityLabel:I(@"提交")];
    [customView addSubview:CommitButton];
	
    return customView;
}


// to determine which UITableViewCell to be used on a given row.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	static NSString *CellIdentifier = @"Cell";
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
	
	if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
		
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
	}
    
	if(indexPath.section == 0)
    {
        float cellWidth = 0;
        
        //7.0下 默认cell是白色背景 且是占满整个屏幕宽度的
        if (__iOS7)
        {
            cellWidth = UI_IOS_WINDOW_WIDTH;
        }
        else
        {
            cellWidth = UI_IOS_WINDOW_WIDTH - 20;
            
            bg_view = [[UIView alloc] init];
            bg_view.frame = CGRectMake(-1, -1, UI_IOS_WINDOW_WIDTH - 20 + 2, 90 + 2);
            bg_view.backgroundColor = [UIColor whiteColor];
            bg_view.layer.cornerRadius = 2.0;
            bg_view.layer.borderWidth = 1.0;
            bg_view.layer.borderColor = [UIColor colorWithRed:195/255.0 green:195/255.0 blue:195/255.0 alpha:1.0].CGColor;
            bg_view.layer.shadowColor   = [UIColor colorWithRed:195/255.0 green:195/255.0 blue:195/255.0 alpha:1.0].CGColor;
            [cell.contentView addSubview:bg_view];
        }
        
        NSDictionary *data = [NSDictionary dictionaryWithContentsOfFile:filePath];
        
		CGRect frame = CGRectMake(0, 5,cellWidth,60);
		textFieldFeedback = [[UITextView alloc] initWithFrame:frame];
		textFieldFeedback.textColor = [UIColor blackColor];
		textFieldFeedback.font = [UIFont systemFontOfSize:12.0];
		textFieldFeedback.text=@"";
		textFieldFeedback.backgroundColor = [UIColor whiteColor];
		textFieldFeedback.autocorrectionType = UITextAutocorrectionTypeNo;
		textFieldFeedback.keyboardType = UIKeyboardTypeDefault;
		textFieldFeedback.returnKeyType = UIReturnKeyDone;
		textFieldFeedback.tag = kViewTag;
		textFieldFeedback.delegate = self;
		[cell.contentView addSubview:textFieldFeedback];
        textFieldFeedback.text = [data objectForKey:@"feedback"];
        
        words_Num = [[UILabel alloc]initWithFrame:CGRectMake(0, 70, cellWidth-5, 20)];
        words_Num.backgroundColor = [UIColor clearColor];
        words_Num.font = [UIFont systemFontOfSize:12.0];
        words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
        words_Num.text = [NSString stringWithFormat:I(@"还能输入%d个字"),FEEDBACK_WORDNUM];
        words_Num.textAlignment = UITextAlignmentRight;
        [cell.contentView addSubview:words_Num];
        
        [self updateWordCount:textFieldFeedback.text];
    }
    
	return cell;
}

@end
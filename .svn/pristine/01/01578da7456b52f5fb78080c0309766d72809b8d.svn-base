    //
//  CMPasswdControl.m
//  MLPlayer
//
//  Created by sunjj on 11-11-9.
//  Copyright 2011 w. All rights reserved.
//

#import "CMPasswdControl.h"
#import "cmglobal.h"

@implementation CMNoCopyTextField

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

- (BOOL)canPerformAction:(SEL)action withSender:(id)sender {
    UIMenuController *menuController = [UIMenuController sharedMenuController];
    if (menuController) {
        [UIMenuController sharedMenuController].menuVisible = NO;
    }
    return NO;
}

@end

@implementation CMPasswdControl
@synthesize textFieldOldPasswd,textFieldNewPasswd,textFieldAgainNewPasswd,PasswordButton,scrollView;
@synthesize PasswordTableView;

- (void)dealloc
{
	if (m_pListener) {
		delete m_pListener;
		m_pListener = NULL;
	}
	if(m_pResetPassword)
	{
		delete m_pResetPassword;
		m_pResetPassword = NULL;
	}
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    //imageViewlog.frame=CGRectMake(50, -100, 220, 100);
    //scrollView.frame=CGRectMake(0.0f, 20.0f, 240.0f, 300.0f);
	
//	[UIView beginAnimations:nil context:NULL];
//	[UIView setAnimationDuration:0.3];
//	
//		// we need to perform some post operations after the animation is complete
//	[UIView setAnimationDelegate:self];
//	
//		// shrink the table vertical size to make room for the date picker
//		//	CGRect imageFrame = imageViewlog.frame;
//		//	imageFrame.origin.y=-100;
//		//	imageViewlog.frame=imageFrame;
//	
//	CGRect newFrame = scrollView.frame;
//	newFrame.origin.y =10;
//	scrollView.frame = newFrame;
//	[UIView commitAnimations];
	
		//[UIView beginAnimations:@"animationID" context:nil];
		//[UIView setAnimationDuration:0.5f];
		//[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
		//[UIView setAnimationRepeatAutoreverses:YES];
	return YES;
}

- (void)viewWillAppear:(BOOL)animated {
	
	[super viewWillAppear:animated];
}
- (void)viewDidLoad
{
	[super viewDidLoad];
	
	[self textFieldOldPasswd];
	[self textFieldNewPasswd];
	[self textFieldAgainNewPasswd];
	[self PasswordButton];
	[self scrollView];
		//[self imageViewlog];
	
	PasswordTableView = [[UITableView alloc] initWithFrame:CGRectMake(10, 0, self.view.bounds.size.width-20, 44*3) style:UITableViewStylePlain];
	//[PasswordTableView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
	PasswordTableView.layer.borderColor = UIColorRGB(0xcbcbcb).CGColor;
	PasswordTableView.layer.borderWidth = 1.0;
	PasswordTableView.scrollEnabled = NO;
	//PasswordTableView.bounces=NO;
	PasswordTableView.backgroundColor=[UIColor whiteColor];
	
	[PasswordTableView setDelegate:self];
	[PasswordTableView setDataSource:self];
	[PasswordTableView setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
	
	
	[scrollView addSubview:PasswordButton];
	[scrollView addSubview:PasswordTableView];
	[self.view addSubview:scrollView];
	
	[PasswordTableView reloadData];
}

-(IBAction)btnPassword :(id) sender
{
    NSString *oldpasswd = [textFieldOldPasswd.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    NSString *newpasswd = [textFieldNewPasswd.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    NSString *againnewpasswd = [textFieldAgainNewPasswd.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
    if (CMGlobal::TheOne().IsOffline())
    {
        NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
        [tool ShowAlert:str];
        return ;
    }
	if ([oldpasswd length] == 0 || [newpasswd length] == 0 || [againnewpasswd length] == 0)
	{
		[tool ShowAlert:I(@"新密码不能为空")];
		return;
	}
    if ( [newpasswd length] > 16 )
    {
        [tool ShowAlert:I(@"新密码不能多于16位")];
        return;
    }
    if ([newpasswd length] < 6)
    {
        [tool ShowAlert:I(@"新密码不能少于6位")];
        return;
    }
	if(![newpasswd  isEqualToString:againnewpasswd])
	{
		[tool ShowAlert:I(@"确认密码输入有误")];
		return;
	}
	if(!m_pResetPassword)
	{
		m_pListener = new CMResetPasswordListener();
		m_pResetPassword = new CMResetPassword(m_pListener);
	}
	m_pResetPassword->SetUserData(BridgeObjectToC(self));
	m_pResetPassword->Commit([textFieldOldPasswd.text UTF8String],[textFieldNewPasswd.text UTF8String]);
	
    PasswordButton.enabled = NO;
}

- (void)viewDidUnload
{
	[super viewDidUnload];
}

-(BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{	
	if(range.location > 15)
		return NO; // return NO to not change text
	return YES;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
	[self btnPassword:textField];
	return NO;
}


#pragma mark -
#pragma mark UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	return 3;
}

	// to determine specific row height for each cell, override this.
	// In this example, each row is determined by its subviews that are embedded.
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 44;
}

	// to determine which UITableViewCell to be used on a given row.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	static NSString *CellIdentifier = @"Cell";
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    cell.backgroundColor=[UIColor clearColor];
	
	if (cell == nil) {
	
		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
		
		cell.textLabel.textAlignment = UITextAlignmentLeft;
		cell.textLabel.textColor = [UIColor grayColor];
		cell.textLabel.highlightedTextColor = [UIColor blackColor];
		cell.textLabel.font = [UIFont systemFontOfSize:14.0];
		
	} 
	
	
	if(indexPath.row == 0){
		cell.textLabel.text= I(@"当前密码");
		[cell.contentView addSubview:textFieldOldPasswd];		
	}
	else if(indexPath.row == 1){
		cell.textLabel.text=I(@"新密码");
		[cell.contentView addSubview:textFieldNewPasswd];
	}
	else if(indexPath.row == 2){
		cell.textLabel.text= I(@"确认密码");
		[cell.contentView addSubview:textFieldAgainNewPasswd];
	}
	return cell;
}



-(UIScrollView *) scrollView
{
	if (scrollView ==nil) {
		CGRect frame =CGRectMake(0,10, 320, 300);
		scrollView = [[UIScrollView alloc] initWithFrame:frame];
		
		[scrollView setBackgroundColor:[UIColor clearColor]];
	}
	return scrollView;
}
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
//	[textFieldNewPasswd endEditing:YES];
//	[textFieldAgainNewPasswd endEditing:YES];
//	[textFieldOldPasswd endEditing:YES];
//	[UIView beginAnimations:nil context:NULL];
//	[UIView setAnimationDuration:0.3];
//	
//	// we need to perform some post operations after the animation is complete
//	[UIView setAnimationDelegate:self];
//	
//	// shrink the table vertical size to make room for the date picker
//	
//	CGRect newFrame = scrollView.frame;
//	newFrame.origin.y =70;
//	scrollView.frame = newFrame;
//	[UIView commitAnimations];
}

- (UITextField *)textFieldOldPasswd
{
	if (textFieldOldPasswd== nil)
	{
		CGRect frame = CGRectMake(78.0, 13.0, 150.0, 25.0);
		textFieldOldPasswd = [[CMNoCopyTextField alloc] initWithFrame:frame];
		
		textFieldOldPasswd.borderStyle = UITextBorderStyleNone;
		textFieldOldPasswd.textColor = [UIColor blackColor];
		textFieldOldPasswd.font = [UIFont systemFontOfSize:12.0];
		//textFieldOldPasswd.placeholder = I(@"当前密码");
		textFieldOldPasswd.text=@"";
		textFieldOldPasswd.backgroundColor = [UIColor whiteColor];
		textFieldOldPasswd.autocorrectionType = UITextAutocorrectionTypeNo;	// no auto correction support
		
		textFieldOldPasswd.keyboardType = UIKeyboardTypeDefault;	// use the default type input method (entire keyboard)
		textFieldOldPasswd.returnKeyType = UIReturnKeyDone;
		
		textFieldOldPasswd.clearButtonMode = UITextFieldViewModeWhileEditing;	// has a clear 'x' button to the right
		textFieldOldPasswd.secureTextEntry = YES;
		textFieldOldPasswd.delegate = self;	// let us be the delegate so we know when the keyboard's "Done" button is pressed
		
			// Add an accessibility label that describes what the text field is for.
	}
	return textFieldOldPasswd;
}

- (UITextField *)textFieldNewPasswd
{
	if (textFieldNewPasswd == nil)
	{
		CGRect frame = CGRectMake(78.0, 13.0, 150.0, 25.0);
		textFieldNewPasswd = [[CMNoCopyTextField alloc] initWithFrame:frame];
		
		textFieldNewPasswd.borderStyle = UITextBorderStyleNone;
		textFieldNewPasswd.textColor = [UIColor blackColor];
		textFieldNewPasswd.font = [UIFont systemFontOfSize:12.0];
		//textFieldNewPasswd.placeholder =  I(@"新密码");
		textFieldNewPasswd.text=@"";
		textFieldNewPasswd.backgroundColor = [UIColor whiteColor];
		textFieldNewPasswd.autocorrectionType = UITextAutocorrectionTypeNo;	// no auto correction support
		
		textFieldNewPasswd.keyboardType = UIKeyboardTypeDefault;
		textFieldNewPasswd.returnKeyType = UIReturnKeyDone;
		
		textFieldNewPasswd.clearButtonMode = UITextFieldViewModeWhileEditing;	// has a clear 'x' button to the right
		textFieldNewPasswd.secureTextEntry = YES;

		textFieldNewPasswd.delegate = self;	// let us be the delegate so we know when the keyboard's "Done" button is pressed
	}
	return textFieldNewPasswd;
}

- (UITextField *)textFieldAgainNewPasswd
{
	if (textFieldAgainNewPasswd == nil)
	{
		CGRect frame = CGRectMake(78.0, 13.0, 150.0, 25.0);
		textFieldAgainNewPasswd = [[CMNoCopyTextField alloc] initWithFrame:frame];
		
		textFieldAgainNewPasswd.borderStyle = UITextBorderStyleNone;
		textFieldAgainNewPasswd.textColor = [UIColor blackColor];
		textFieldAgainNewPasswd.font = [UIFont systemFontOfSize:12.0];
		//textFieldAgainNewPasswd.placeholder = I(@"确认密码");
		textFieldAgainNewPasswd.text=@"";
		textFieldAgainNewPasswd.backgroundColor = [UIColor whiteColor];
		textFieldAgainNewPasswd.autocorrectionType = UITextAutocorrectionTypeNo;	// no auto correction support
		
		textFieldAgainNewPasswd.keyboardType = UIKeyboardTypeDefault;
		textFieldAgainNewPasswd.returnKeyType = UIReturnKeyDone;
		
		textFieldAgainNewPasswd.clearButtonMode = UITextFieldViewModeWhileEditing;	// has a clear 'x' button to the right
		textFieldAgainNewPasswd.secureTextEntry = YES;
		
		textFieldAgainNewPasswd.delegate = self;	// let us be the delegate so we know when the keyboard's "Done" button is pressed
	}
	return textFieldAgainNewPasswd;
}

-(UIButton *)PasswordButton{
	
    if (PasswordButton ==nil) {
		
		PasswordButton= [UIButton buttonWithType:UIButtonTypeCustom];
		[PasswordButton setBackgroundImage:[UIImage imageNamed:@"ok_n"] forState:UIControlStateNormal];
		[PasswordButton setBackgroundImage:[UIImage imageNamed:@"ok_p"] forState:UIControlStateHighlighted];

		[PasswordButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];

		PasswordButton.titleLabel.font = [UIFont systemFontOfSize:16];
		UIImage* image = [UIImage imageNamed:@"ok_n"];
		PasswordButton.frame = CGRectMake((UI_IOS_WINDOW_WIDTH - image.size.width)/2, 145.00, image.size.width, image.size.height);

		//PasswordButton.frame = CGRectMake((UI_IOS_WINDOW_WIDTH - 105)/2, 145.00, 105.0, 37.0);
		[PasswordButton addTarget:(id)self action:@selector(btnPassword:) forControlEvents:UIControlEventTouchUpInside];

		PasswordButton.userInteractionEnabled=YES;

	}
	
	return PasswordButton;
	
	
}

@end
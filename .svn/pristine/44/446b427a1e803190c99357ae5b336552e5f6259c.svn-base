#include "stdafx.h"
#include "cmsettings.h"
#import "tool.h"
#import "CMLoginControl.h"
//#import "MobClick.h"
#import "cmglobal.h"
//#import "JPushSDK/APService.h"
#import "CMMailViewController.h"
#import "CMServiceViewController.h"
#import "CMConfig.h"

int loginstate = 0;

const NSInteger kViewTag = 1;

@implementation UICusTextField

- (instancetype)init{
    if((self =[super init])){
        self.bIsHighLighted = NO;
    }
    return self;
}

-(CGRect)textRectForBounds:(CGRect)bounds
{
	int margin =8 + self.leftView.frame.size.width + 15;
    CGRect inset =CGRectMake(bounds.origin.x + margin, bounds.origin.y, bounds.size.width - margin, bounds.size.height);
    return inset;
}
-(CGRect)editingRectForBounds:(CGRect)bounds {
    int margin =8 + self.leftView.frame.size.width + 15;
    CGRect inset =CGRectMake(bounds.origin.x + margin, bounds.origin.y, bounds.size.width - margin, bounds.size.height);
    return inset;
}
- (CGRect)leftViewRectForBounds:(CGRect)bounds{
    int margin = 8;
    CGRect inset =CGRectMake(bounds.origin.x + margin, bounds.origin.y + 8, self.leftView.frame.size.width, self.leftView.frame.size.height);
    return inset;
}

-(void)drawRect:(CGRect)rect

{
    [super drawRect:rect];
    
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    CGContextClearRect(ctx, rect);
    
    // 设置线条颜色
    if (!self.bIsHighLighted) {
        CGContextSetRGBStrokeColor(ctx, 204.0f/255.0f, 204.0f/255.0f, 204.0f/255.0f, 1.0f);
    }
    else {
        CGContextSetStrokeColorWithColor(ctx, kColorForeground.CGColor);
    }
    
    CGContextMoveToPoint(ctx, 2, rect.size.height-3);
    
    CGContextAddLineToPoint(ctx, rect.size.width-2, rect.size.height-3);
    
    
    
   // CGContextMoveToPoint(ctx, 1, rect.size.height-10);
    
   // CGContextAddLineToPoint(ctx, 1, rect.size.height-2);
    
    
    
   // CGContextMoveToPoint(ctx, rect.size.width-1, rect.size.height-10);
    
   // CGContextAddLineToPoint(ctx, rect.size.width-1, rect.size.height-2);
    
    // 开始绘图
    
    CGContextStrokePath(ctx);
    

    
}


@end

@implementation CMLoginControl

@synthesize textFieldPasswd,textFieldUserName,textFieldEid,loginButton,mySwitch,scrollView;
@synthesize imageViewlog,imageViewSlogan;
@synthesize bIsPush;
@synthesize lblSlogan,lblTitle;
- (void)dealloc
{
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationWillResignActiveNotification object:nil];
	
    SAFEDELETE(m_pLogin);
	SAFEDELETE(m_pListener);
}

-(void)keyboardWillShow:(NSNotification*)notification{
    
    NSDictionary*info=[notification userInfo];
    NSInteger KeyboardHeight =[[info objectForKey:UIKeyboardFrameEndUserInfoKey]CGRectValue].size.height;
    
    CGRect newFrame = self.view.frame;
    
    if (__iOS7) {
        KeyboardHeight += 20.0;
    }
    
    newFrame.origin.y  = UI_IOS_WINDOW_HEIGHT-(KeyboardHeight+100+275);
    
    [UIView animateWithDuration:0.3f animations:^{
        self.view.frame = newFrame;
    }];
}

- (void)keyboardWillHide:(NSNotification *)aNotification{

    [self hideKeyboard];
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    /*
	[UIView beginAnimations:nil context:NULL];loginLabelY-KeyboardHeight
	[UIView setAnimationDuration:0.3];
	[UIView setAnimationDelegate:self];

	CGRect newFrame = scrollView.frame;
    NSInteger loginLabelY = [scrollView viewWithTag:10].frame.origin.y;
    
    
	newFrame.origin.y  =-(UI_IOS_WINDOW_HEIGHT/3-loginLabelY);
	scrollView.frame = newFrame;
	[UIView commitAnimations];
    */
    
    if (textField == textFieldUserName) {
        UIImageView *textFieldLeftImageUser = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"username_selected"]];
        self.textFieldUserName.leftView = textFieldLeftImageUser;
    }
    else if (textField == textFieldPasswd){
        UIImageView *textFieldLeftImagePasswd = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"passwd_selected"]];
        self.textFieldPasswd.leftView = textFieldLeftImagePasswd;
    }
    
    ((UICusTextField *)textField).bIsHighLighted = YES;
    [textField setNeedsDisplay];
    
	return YES;
}


- (BOOL)textFieldShouldEndEditing:(UITextField *)textField{
    if (textField == textFieldUserName) {
        UIImageView *textFieldLeftImageUser = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"username"]];
        self.textFieldUserName.leftView = textFieldLeftImageUser;
    }
    else if (textField == textFieldPasswd){
        UIImageView *textFieldLeftImagePasswd = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"passwd"]];
        self.textFieldPasswd.leftView = textFieldLeftImagePasswd;
    }
    ((UICusTextField *)textField).bIsHighLighted = NO;
    [textField setNeedsDisplay];
    
    return YES;
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    if ([textFieldEid isFirstResponder]) {
        [textFieldEid resignFirstResponder];
    }
    
    if ([textFieldUserName isFirstResponder]) {
        [textFieldUserName resignFirstResponder];
    }
    
    if ([textFieldPasswd isFirstResponder]) {
        [textFieldPasswd resignFirstResponder];
    }
    
}


- (void)viewWillAppear:(BOOL)animated {
        
    CMEnterpriseInfo info;
    utf8ncpy(info.sID, SETTING.GetCustomer(), 19);
    
    if(m_pLogin)
        m_pLogin->GetEnterpriseInfo( info);
//    
//    if(lblTitle)
//    {
//        if(!info.sTitle ||  strlen(info.sTitle)==0)
//            [lblTitle setText:I(@"美课")];
//        else
//            [lblTitle setText:[NSString stringWithUTF8String:info.sTitle]];
//    }
//    
//    if(lblSlogan)
//    {
//        if(!info.sSlogan ||  strlen(info.sSlogan)==0)
//            [lblSlogan setText:I(@"轻松学习 愉悦提升")];
//        else
//            [lblSlogan setText:[NSString stringWithUTF8String:info.sSlogan]];
//    }
    
	[super viewWillAppear:animated];
	self.navigationController.navigationBarHidden=YES;
	
}
- (void)viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
	
	if (loginstate == 0 ) {
		
		if(m_pLogin)
		{
			[self textFieldUserName].text = [NSString stringWithUTF8String:m_pLogin->GetUserName()];
            
            CMString sID;
            if (!bFindPwdBack && [self isViewLoaded] && strlen(m_pLogin->GetUserName()) > 0 && CMGlobal::TheOne().GetSessionID(sID))
            {
                
                [self textFieldPasswd].text = [NSString stringWithUTF8String:m_pLogin->GetPassWord()];
				
				[self btnLogin:self];
                
			}
		}
        
	}else if (loginstate == 1) {
		[self textFieldUserName].text = @"";
		[self textFieldPasswd].text = @"";
		
	}else if (loginstate == 2) {
		[self textFieldUserName].text = [NSString stringWithUTF8String:m_pLogin->GetUserName()];
        bIsPush = NO;
		[self textFieldPasswd].text = @"";

	}else {
		if(m_pLogin)
		{
			//[self textFieldUserName].text = [NSString stringWithUTF8String:m_pLogin->GetUserName()];
			//[self textFieldPasswd].text = [NSString stringWithUTF8String:m_pLogin->GetPassWord()];
		}
	}
    if ([self.textFieldEid.text isEqualToString:@""]) {
        [self.textFieldEid becomeFirstResponder];
    }else if ([self.textFieldUserName.text isEqualToString:@""]){
        [self.textFieldUserName becomeFirstResponder];
    }else if ([self.textFieldPasswd.text isEqualToString:@""]){
        [self.textFieldPasswd becomeFirstResponder];
    }
    
    
    scrollView.hidden = NO;
    
}

- (void)viewDidLoad
{
	[super viewDidLoad];
    self.openAutoKeyboard = YES;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillResignActive) name:UIApplicationWillResignActiveNotification object:nil];
	
    //判断保存的用户名是否为空 为空则不自动登陆
    NSString *strUser = [NSString stringWithUTF8String:SETTING.GetUserName()];
    
    if ([strUser isEqualToString:@""])
    {
        loginstate = 2;
    }
    else
    {
        loginstate = 0;
    }

    
    UIButton *bakBtn=[[UIButton alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT)];
    [bakBtn setBackgroundColor:[UIColor clearColor]];
    [bakBtn addTarget:self action:@selector(hideKeyboard) forControlEvents:UIControlEventTouchUpInside];
  //  [self.view addSubview:bakBtn];
    
    UIImageView *imgView=[[UIImageView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT)];
//    if(UI_IOS_WINDOW_HEIGHT==1136)
//        [imgView setImage:[UIImage imageNamed:@"sysbackground-568h.png"]];
//    else
//        [imgView setImage:[UIImage imageNamed:@"sysbackground.png"]];


    CGRect f = self.view.bounds;
	f.size.height = UI_IOS_WINDOW_HEIGHT-20;

	
	[self.view addSubview:imgView];
	
	m_pListener = new CMloginListener();
	m_pLogin = new CMLogin(m_pListener);
	
	int yoff = 94;
    
//    lblTitle=[[UILabel alloc]init];
//    [lblTitle setFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-kBigSloganWidth)/2, yoff, kBigSloganWidth, kBigSloganHeight)];
//    [lblTitle setBackgroundColor:[UIColor clearColor]];
//    [lblTitle setTextColor:[UIColor whiteColor]];
//    [lblTitle setTextAlignment:NSTextAlignmentCenter];
//    [lblTitle setFont:[UIFont systemFontOfSize:40]];
//    

    UIImage *logoImage = [UIImage  imageNamed:@"iconLogo"];
    UIImageView *logo = [[UIImageView alloc] initWithImage: logoImage];
   logo.frame = CGRectMake((UI_IOS_WINDOW_WIDTH-logoImage.size.width)/2, yoff, logoImage.size.width, logoImage.size.height);
    //self.
    
    
	UIImage* image = [UIImage imageNamed:@"syslog_2.png"];//“美课”图
	imageViewlog = [[UIImageView alloc] initWithImage:image];
	imageViewlog.frame=CGRectMake((UI_IOS_WINDOW_WIDTH-image.size.width)/2, yoff + logoImage.size.height + 12 , image.size.width, image.size.height);
	yoff += image.size.height;
	
//    lblSlogan=[[UILabel alloc]init];
//    [lblSlogan setFrame:CGRectMake((UI_IOS_WINDOW_WIDTH-kSmallSloganWidth)/2, 110,kSmallSloganWidth, kSmallSloganHeight)];
//    [lblSlogan setBackgroundColor:[UIColor clearColor]];
//    [lblSlogan setTextColor:[UIColor whiteColor]];
//    [lblSlogan setTextAlignment:NSTextAlignmentCenter];
//    [lblSlogan setFont:[UIFont systemFontOfSize:20]];
    
//	image = [UIImage imageNamed:@"sysSlogan_2.png"];
//	imageViewSlogan = [[UIImageView alloc] initWithImage:image];
//	imageViewSlogan.frame=CGRectMake(UI_IOS_WINDOW_WIDTH/2-330/4, 152, 330/2, 36/2);
	
	yoff += 75;
	UIImage* editbk = [UIImage imageNamed:@"editbk"];
	CGRect frame = CGRectMake(40, yoff, f.size.width-80, editbk.size.height);
	textFieldEid = [[UICusTextField alloc] initWithFrame:frame];
	textFieldEid.background = editbk;
	textFieldEid.borderStyle = UITextBorderStyleNone;
	textFieldEid.textColor = [UIColor blackColor];
	textFieldEid.font = [UIFont systemFontOfSize:14];
	textFieldEid.placeholder = I(@"企业ID");//@"企业ID";
	textFieldEid.text = [NSString stringWithUTF8String:SETTING.GetCustomer()];
	textFieldEid.backgroundColor = [UIColor clearColor];
    textFieldEid.returnKeyType = UIReturnKeyNext;

	textFieldEid.contentVerticalAlignment=UIControlContentVerticalAlignmentCenter;
	textFieldEid.tag = 1000;		// tag this control so we can remove it later for recycled cells
	textFieldEid.delegate = self;	// let us be the delegate so we know when the keyboard's "Done" button is pressed

    if(!ShowEidInput)
    {
        textFieldEid.hidden=YES;
        textFieldEid.text=[NSString stringWithUTF8String:defaultEid];
    }

	frame = textFieldEid.bounds;
	frame.origin.x += 10;
	frame.size.width -= 10;
	//[textFieldEid drawPlaceholderInRect:frame];
	
	yoff += 90;
	frame = CGRectMake(32, yoff, f.size.width-64, editbk.size.height);
	textFieldUserName = [[UICusTextField alloc] initWithFrame:frame];
	//textFieldUserName.background = editbk;
	textFieldUserName.borderStyle = UITextBorderStyleBezel;
	textFieldUserName.textColor = [UIColor blackColor];
	textFieldUserName.font = [UIFont systemFontOfSize:14];
//	textFieldUserName.placeholder =[I(@"帐号或手机号码") stringByReplacingOccurrencesOfString:@"："  withString:@""];
    textFieldUserName.placeholder =I(@"输入员工帐号");
    textFieldUserName.text = @"test500";
    
    textFieldUserName.leftViewMode = UITextFieldViewModeAlways;
    UIImageView *textFieldLeftImageUser = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"username"]];
    self.textFieldUserName.leftView = textFieldLeftImageUser;
    
    
    

	textFieldUserName.text=@"";
 //   textFieldUserName.text = [NSString stringWithUTF8String:SETTING.GetUserName()];
	textFieldUserName.backgroundColor = [UIColor clearColor];
	textFieldUserName.autocorrectionType = UITextAutocorrectionTypeNo;	// no auto correction support
	textFieldUserName.keyboardType = UIKeyboardTypeDefault;	// use the default type input method (entire keyboard)
	textFieldUserName.returnKeyType = UIReturnKeyNext;
	textFieldUserName.contentVerticalAlignment=UIControlContentVerticalAlignmentCenter;
	textFieldUserName.clearButtonMode = UITextFieldViewModeWhileEditing;	// has a clear 'x' button to the right
	
	textFieldUserName.tag = 1001;		// tag this control so we can remove it later for recycled cells
	
	textFieldUserName.delegate = self;	// let us be the delegate so we know when the keyboard's "Done" button is pressed
	
	
	yoff += 50;
	frame = CGRectMake(32, yoff, f.size.width-64, editbk.size.height);
	textFieldPasswd = [[UICusTextField alloc] initWithFrame:frame];
	//textFieldPasswd.background = editbk;
	textFieldPasswd.borderStyle = UITextBorderStyleBezel;
	textFieldPasswd.textColor = [UIColor blackColor];
	textFieldPasswd.font = [UIFont systemFontOfSize:14];
//	textFieldPasswd.placeholder =  [I(@"密  码") stringByReplacingOccurrencesOfString:@"："  withString:@""];
    textFieldPasswd.placeholder =  I(@"输入密码");
    textFieldPasswd.text = @"111111";
    
    textFieldPasswd.leftViewMode = UITextFieldViewModeAlways;
    UIImageView *textFieldLeftImagePasswd = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"passwd"]];
    self.textFieldPasswd.leftView = textFieldLeftImagePasswd;

	textFieldPasswd.text=@"";
  //  textFieldPasswd.text = [NSString stringWithUTF8String:SETTING.GetUserPass()];

	textFieldPasswd.backgroundColor = [UIColor clearColor];
	textFieldPasswd.autocorrectionType = UITextAutocorrectionTypeNo;	// no auto correction support
	textFieldPasswd.contentVerticalAlignment=UIControlContentVerticalAlignmentCenter;
	
	textFieldPasswd.keyboardType = UIKeyboardTypeDefault;
	textFieldPasswd.returnKeyType = UIReturnKeyGo;
	
	textFieldPasswd.clearButtonMode = UITextFieldViewModeWhileEditing;	// has a clear 'x' button to the right
	textFieldPasswd.secureTextEntry = YES;
	
	textFieldPasswd.tag = 1002;		// tag this control so we can remove it later for recycled cells
	
	textFieldPasswd.delegate = self;	// let us be the delegate so we know when the keyboard's "Done" button is pressed
	
	yoff += 70;
	frame = CGRectMake(32, yoff, f.size.width-64, 46);
	loginButton= [UIButton buttonWithType:UIButtonTypeCustom];
	loginButton.frame = frame;
	[loginButton addTarget:(id)self action:@selector(btnLogin:) forControlEvents:UIControlEventTouchUpInside];
	loginButton.tag=kViewTag;
	
	//[loginButton setBackgroundImage:[UIImage imageNamed:@"Loginbtn_n.png"] forState:UIControlStateNormal];
    [loginButton setBackgroundColor:UIColorRGB(0x128de1)];
    
    [loginButton setTitle:I(@"登录") forState:UIControlStateNormal];
    [loginButton setTitle:I(@"登录") forState:UIControlStateHighlighted];
    [loginButton setTitle:I(@"登录") forState:UIControlStateSelected];

    [loginButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [loginButton setTitleColor:[UIColor whiteColor] forState:UIControlStateHighlighted];
    [loginButton setTitleColor:[UIColor whiteColor] forState:UIControlStateSelected];

    
	
	//[loginButton setBackgroundImage:[UIImage imageNamed:@"Loginbtn_n.png"] forState:UIControlStateHighlighted];

	yoff += 45;
	
	frame = CGRectMake(40, yoff, 100, 30);
	mySwitch= [[CheckBoxButton alloc] initWithFrame:frame];
	[mySwitch setTitle:I(@"自动登录")];
	[mySwitch setColor:[UIColor whiteColor]];
    [mySwitch setTag:10];
    
	mySwitch.Check =  m_pLogin->GetAutoLogin();
	
	scrollView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT)];
    
	[scrollView setBackgroundColor:[UIColor clearColor]];
    [scrollView addSubview:bakBtn];

    //设置企业信息
    CMEnterpriseInfo info;
    utf8ncpy(info.sID, SETTING.GetCustomer(), 19);
    
    if(m_pLogin)
        m_pLogin->GetEnterpriseInfo( info);
    
//    if(lblTitle)
//    {
//        if(!info.sTitle ||  strlen(info.sTitle)==0)
//            [lblTitle setText:I(@"美课")];
//        else
//            [lblTitle setText:[NSString stringWithUTF8String:info.sTitle]];
//    }
//    
//    if(lblSlogan)
//    {
//        if(!info.sSlogan ||  strlen(info.sSlogan)==0)
//            [lblSlogan setText:I(@"轻松学习 愉悦提升")];
//        else
//            [lblSlogan setText:[NSString stringWithUTF8String:info.sSlogan]];
//    }
    
//    UIButton *findPasswordBtn = [UIButton buttonWithType:UIButtonTypeCustom];
//    //findPasswordBtn.backgroundColor = [UIColor redColor];
//    findPasswordBtn.frame = CGRectMake(0, 0, 60, 30);
//    findPasswordBtn.center = CGPointMake(UI_IOS_WINDOW_WIDTH/2 - 50, UI_IOS_WINDOW_HEIGHT - 40);
//    [findPasswordBtn setTitle:I(@"找回密码") forState:UIControlStateNormal];
//    [findPasswordBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
//    [findPasswordBtn.titleLabel setFont:[UIFont systemFontOfSize:14]];
//    [findPasswordBtn addTarget:self action:@selector(findPasswordPressed:) forControlEvents:UIControlEventTouchUpInside];
//    
//    UILabel *lineLbl = [[UILabel alloc] init];
//    lineLbl.frame = CGRectMake(0, 0, 1, 16);
//    lineLbl.center = CGPointMake(UI_IOS_WINDOW_WIDTH/2, UI_IOS_WINDOW_HEIGHT - 40);
//    lineLbl.backgroundColor = [UIColor whiteColor];
//    
//    UIButton *serviceBtn = [UIButton buttonWithType:UIButtonTypeCustom];
//    //serviceBtn.backgroundColor = [UIColor blueColor];
//    serviceBtn.frame = CGRectMake(0, 0, 60, 30);
//    serviceBtn.center = CGPointMake(UI_IOS_WINDOW_WIDTH/2 + 50, UI_IOS_WINDOW_HEIGHT - 40);
//    [serviceBtn setTitle:I(@"服务支持") forState:UIControlStateNormal];
//    [serviceBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
//    [serviceBtn.titleLabel setFont:[UIFont systemFontOfSize:14]];
//    [serviceBtn addTarget:self action:@selector(serviceBtnPressed:) forControlEvents:UIControlEventTouchUpInside];
    
//    [scrollView addSubview:findPasswordBtn];
//    [scrollView addSubview:lineLbl];
//    [scrollView addSubview:serviceBtn];
    //[scrollView addSubview:lblTitle];
    //[scrollView addSubview:lblSlogan];
	[scrollView addSubview:imageViewlog];
    [scrollView addSubview:logo];
	[scrollView addSubview:imageViewSlogan];
	[scrollView addSubview:textFieldEid];
	[scrollView addSubview:textFieldUserName];
	[scrollView addSubview:textFieldPasswd];
	
	[scrollView addSubview:loginButton];
	//[scrollView addSubview:mySwitch];

    CMString sID;
    if (CMGlobal::TheOne().GetSessionID(sID)) {
        scrollView.hidden = YES;
    }
    else{
        scrollView.hidden = NO;
    }

    
	[self.view addSubview:scrollView];
	
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(backLoginState:) 
												 name:@"loginstate" 
											   object:nil];
}


- (IBAction)findPasswordPressed:(id)sender
{
    self.navigationController.navigationBarHidden = NO;

    //后续添加通过手机号找回密码 先做通过邮箱找回
    CMMailViewController *mailControl = [[CMMailViewController alloc] init];
    mailControl.title =I(@"找回密码");
    bFindPwdBack = YES;
    [self.navigationController pushViewController:mailControl animated:YES];
}


- (IBAction)serviceBtnPressed:(id)sender
{
    self.navigationController.navigationBarHidden = NO;
    
    CMServiceViewController *serviceControl = [[CMServiceViewController alloc] init];
    serviceControl.title = I(@"服务支持");
    [self.navigationController pushViewController:serviceControl animated:YES];
}




-(void)hideKeyboard
{
    if ([textFieldEid isFirstResponder]) {
        [textFieldEid resignFirstResponder];
    }
    
    if ([textFieldUserName isFirstResponder]) {
        [textFieldUserName resignFirstResponder];
    }
    
    if ([textFieldPasswd isFirstResponder]) {
        [textFieldPasswd resignFirstResponder];
    }
    
    CGContext *context = UIGraphicsGetCurrentContext();
    [UIView beginAnimations:nil context:context];
	[UIView setAnimationDuration:0.3];
	[UIView setAnimationDelegate:self];
    
	self.view.frame = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT);
	[UIView commitAnimations];

}

-(IBAction)btnLogin :(id) sender
{
    
//    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"welite://"]];

    
//    NSURL * myURL_APP_A = [NSURL URLWithString:@"wd_welite://"];
//    if ([[UIApplication sharedApplication] canOpenURL:myURL_APP_A]) {
//        NSLog(@"canOpenURL");
//        [[UIApplication sharedApplication] openURL:myURL_APP_A];
//    }
    
//    NSURL *url = [NSURL URLWithString:@"wd_welite://openapp"];
//    [[UIApplication sharedApplication] openURL:url];
//    
//    return;
    
	[self hideKeyboard];
    
//	if ([textFieldEid.text length] ==0) {
//		[tool ShowAlert:I(@"企业ID不能为空")];//@"企业ID不能为空"
//		return;
//	}
	
	if ([textFieldUserName.text length] == 0 || [textFieldPasswd.text length] == 0)
	{
		[tool ShowAlert:I(@"员工帐号或密码不能为空")];
		return;
	}

    CMLoadingControl* cmLoadingControl = [[CMLoadingControl alloc] init];
	cmLoadingControl.bIsPush = bIsPush;
	cmLoadingControl.eid = textFieldEid.text;
	cmLoadingControl.username=textFieldUserName.text;
	cmLoadingControl.passwd = textFieldPasswd.text;
	cmLoadingControl.checkAuto = mySwitch.tag;
	cmLoadingControl.checkpass = mySwitch.tag;

	cmLoadingControl.navigationController.navigationBarHidden = YES;
	//[MobClick event:@"Login"];
	[self.navigationController pushViewController:cmLoadingControl animated:NO];
	
}

- (void)viewDidUnload
{
	[super viewDidUnload];
}

// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	// Return YES for supported orientations.
	return NO;
}

//退出前台状态
- (void)applicationWillResignActive {
    [self hideKeyboard];
}

//1 取消登录 2 注销 3 密码错误
-(void)backLoginState:(id)state
{	
	NSLog(@"backLoginState");
	
	NSString* value = [[state userInfo] objectForKey:@"name"];//[NSString stringWithFormat:@"%@",[state object]];

	if([value isEqualToString:@"1"])
	{
		loginstate = [value intValue];
		
	}else if ([value isEqualToString:@"2"]) {
		loginstate = [value intValue];
	}else {
		loginstate = [value intValue];
	}
	
}


-(BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{	
	if(range.location >= 50)
		return NO; // return NO to not change text
	return YES;
}
- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
	if (textField.tag == 1000) {
		[textFieldUserName becomeFirstResponder];
	}
    if (textField.tag == 1001) {
        [textFieldPasswd becomeFirstResponder];
    }
    else if (textField.tag == 1002) {
		[self btnLogin:textField];
	} 

	return NO;
}

@end
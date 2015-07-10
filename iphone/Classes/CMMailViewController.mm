//
//  CMMailViewController.m
//  MLPlayer
//
//  Created by wmgwd on 13-12-5.
//  Copyright (c) 2013年 w. All rights reserved.
//

#import "CMMailViewController.h"
#import "CMSuccessViewController.h"
#import "cmretrievepass.h"
#import "tool.h"

@interface CMMailViewController ()
- (IBAction)nextBtnPressed:(id)sender;
- (BOOL)validateEmail:(NSString *)email;
@end

@implementation CMMailViewController
@synthesize nextBtn;

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
    
    self.titleLabel.text = self.navigationItem.title;
    self.view.backgroundColor = [UIColor whiteColor];
    
    UILabel *topLabel = [[UILabel alloc] init];
    topLabel.frame = CGRectMake(20, 30, UI_IOS_WINDOW_WIDTH - 40, 20);
    topLabel.backgroundColor = [UIColor clearColor];
    topLabel.text = I(@"输入您的邮箱");
    topLabel.font = [UIFont systemFontOfSize:14];
    topLabel.textColor = UIColorRGB(0x747474);
    [self.view addSubview:topLabel];
    CMRELEASE(topLabel);
    
    UITextField *mailTextField = [[UITextField alloc] init];
    mailTextField.frame = CGRectMake(20, 60, UI_IOS_WINDOW_WIDTH - 40, 39);
    mailTextField.backgroundColor = [UIColor clearColor];
    mailTextField.background = [UIImage imageNamed:@"findpwdback@2x"];
    mailTextField.tag = 1000;
    mailTextField.delegate = self;
    mailTextField.clearButtonMode = UITextFieldViewModeWhileEditing;
    mailTextField.textColor = UIColorRGB(0x000000);
    
    UIButton *mailBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    mailBtn.frame = CGRectMake(0, 0, 42, 32);
    mailBtn.backgroundColor = [UIColor clearColor];
    [mailBtn setImage:[UIImage imageNamed:@"findpwdmail"] forState:UIControlStateNormal];
    [mailBtn setImage:[UIImage imageNamed:@"findpwdmail"] forState:UIControlStateHighlighted];
    mailBtn.imageEdgeInsets = UIEdgeInsetsMake(3.5, 4, 3.5, 4);
    
    mailTextField.leftView = mailBtn;
    mailTextField.leftViewMode = UITextFieldViewModeAlways;
    [self.view addSubview:mailTextField];
    CMRELEASE(mailTextField);
    
    nextBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    nextBtn.frame = CGRectMake(20, 130, UI_IOS_WINDOW_WIDTH - 40, 39);
    nextBtn.backgroundColor = [UIColor clearColor];
    [nextBtn setBackgroundImage:[UIImage imageNamed:@"introductionstart_n@2x"] forState:UIControlStateNormal];
    [nextBtn setBackgroundImage:[UIImage imageNamed:@"introductionstart_p@2x"] forState:UIControlStateHighlighted];
    [nextBtn setTitle:I(@"下一步") forState:UIControlStateNormal];
    [nextBtn addTarget:self action:@selector(nextBtnPressed:) forControlEvents:UIControlEventTouchUpInside];
    [nextBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [self.view addSubview:nextBtn];
}

- (void)showResult:(int)result
{
    if (result == TResult::ESuccess)
    {
        CMSuccessViewController *success = [[CMSuccessViewController alloc] init];
        success.title = I(@"找回密码");
        success.strMail = [NSString stringWithUTF8String:m_pRetrievePass->getPMsg()];
        [self.navigationController pushViewController:success animated:YES];
        CMRELEASE(success);
    }
    else
    {
        NSString *errMsg = [NSString stringWithUTF8String:m_pRetrievePass->getPMsg()];
        
        if ( errMsg.length > 0 ) {
            [tool ShowAlert:errMsg];
        }
    }
}

- (IBAction)nextBtnPressed:(id)sender
{
    UITextField *textField = (UITextField*)[self.view viewWithTag:1000];
    
    //验证是否为空
    if (textField.text.length <= 0)
    {
        [tool ShowAlert:I(@"输入您的邮箱")];
        return;
    }
    else
    {
        //验证是否符合邮箱规则
        if (![self validateEmail:textField.text])
        {
            [textField resignFirstResponder];
            [tool ShowAlert:I(@"请输入正确的邮箱")];
            return;
        }
    }
    
    if (!m_pListener)
    {
        m_pListener = new MailSimpleResultListener;
    }
    
    if (!m_pRetrievePass)
    {
        m_pRetrievePass = new CMRetrievePass(m_pListener);
    }
    
    nextBtn.enabled = NO;
    m_pRetrievePass->SetUserData(BridgeObjectToC(self));
    m_pRetrievePass->Commit([textField.text UTF8String]);
}

- (BOOL)validateEmail:(NSString *)email
{
    NSString *emailRegex = @"[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}";
    NSPredicate *emailTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", emailRegex];
    return [emailTest evaluateWithObject:email];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc
{
    SAFEDELETE(m_pRetrievePass)
    SAFEDELETE(m_pListener)
    
# if ! __has_feature(objc_arc)
    [super dealloc];
# endif
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITextField *textField = (UITextField*)[self.view viewWithTag:1000];
    [textField resignFirstResponder];
}

#pragma mark - TextField delegate

- (BOOL)textFieldShouldClear:(UITextField *)textField
{
    textField.text = @"";
    return YES;
}


- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

@end

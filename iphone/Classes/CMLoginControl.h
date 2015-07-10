#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <QuartzCore/CAMediaTiming.h>
#import <UIKit/UIStringDrawing.h>
#import "CMViewController.h"
#import "CMLoadingControl.h"
#import "CMServersInfoControl.h"
#import "cmlogin.h"
#import "CMImage.h"
#include "cmcommon.h"
#import "cmcourseinfo.h"
#import "CheckBoxButton.h"

class CMloginListener;
class CMCustomerList;
@interface UICusTextField : UITextField
{
	
}

@property (assign, nonatomic) BOOL bIsHighLighted;

@end

@interface CMLoginControl : CMViewController <UITextFieldDelegate>
{
	MLPlayerAppDelegate *appDelegate;
	
	UICusTextField *textFieldEid;
	UICusTextField *textFieldPasswd;
	UICusTextField *textFieldUserName;
	UIButton *loginButton;
	UIView *scrollView;

    
   // UILabel *lblTitle;
   // UILabel *lblSlogan;
    
	UIImageView *imageViewlog;
	UIImageView *imageViewSlogan;
	CheckBoxButton* mySwitch;
	
	CMLogin* m_pLogin;
	CMloginListener* m_pListener;
    
    BOOL bFindPwdBack; //用于控制 从找回密码页面返回时 不能自动登录
    BOOL bIsPush;
}

@property(nonatomic,strong) UILabel *lblTitle;
@property(nonatomic,strong) UILabel *lblSlogan;


@property (nonatomic, strong, readonly) UIView *scrollView;
@property (nonatomic, strong) UIImageView *imageViewlog;
@property (nonatomic, strong) UIImageView *imageViewSlogan;
@property (nonatomic, strong, readonly) UIButton* mySwitch;

@property (nonatomic, strong, readonly) UITextField *textFieldPasswd;
@property (nonatomic, strong, readonly) UITextField *textFieldUserName;
@property (nonatomic, strong, readonly) UITextField *textFieldEid;
@property (nonatomic, strong, readonly) UIButton *loginButton;
@property (nonatomic, assign) BOOL bIsPush;


-(IBAction)btnLogin :(id) sender;
@end
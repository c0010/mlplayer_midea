//
//  CMPasswdControl.h
//  MLPlayer
//
//  Created by sunjj on 11-11-9.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <QuartzCore/CAMediaTiming.h>
#import <UIKit/UIStringDrawing.h>
#import "CMViewController.h"
#import "cmlogin.h"
#import "CMImage.h"
#include "cmcommon.h"
#import "cmresetpassword.h"

@interface CMNoCopyTextField : UITextField

@end

class CMResetPasswordListener;

@interface CMPasswdControl : CMViewController <UITextFieldDelegate,UITableViewDelegate,UITableViewDataSource>
{
	UITableView *PasswordTableView;
	CMNoCopyTextField *textFieldOldPasswd;
	CMNoCopyTextField *textFieldNewPasswd;
	CMNoCopyTextField *textFieldAgainNewPasswd;
	UIButton *PasswordButton;
	UIScrollView *scrollView;
	
	CMResetPasswordListener *m_pListener;
	CMResetPassword* m_pResetPassword;
}
	
@property (nonatomic, strong) UITableView *PasswordTableView;
@property (nonatomic, strong) UIScrollView *scrollView;
	//@property (nonatomic, retain) UIImageView *imageViewlog;

@property (nonatomic, strong, readonly) UITextField *textFieldOldPasswd;
@property (nonatomic, strong, readonly) UITextField *textFieldNewPasswd;
@property (nonatomic, strong, readonly) UITextField *textFieldAgainNewPasswd;
@property (nonatomic, strong, readonly) UIButton *PasswordButton;

-(IBAction)btnPassword :(id) sender;
@end

class CMResetPasswordListener : public IMSimpleResultListener {
public:
	CMResetPasswordListener(){};
	~CMResetPasswordListener(){};
	
	void  OnRequestFinish(void* UserData, int Result){
		CMPasswdControl* ResetPassword= (__bridge CMPasswdControl*)UserData;
        
        ResetPassword.PasswordButton.enabled = YES;

		if(Result == TResult::ESuccess)
		{
            
            [tool ShowAlert:I(@"修改成功！")];

            
			[[NSNotificationCenter defaultCenter] postNotificationName:@"loadinggetcategory" 
																object:nil
															  userInfo:nil];
			[ResetPassword.navigationController popViewControllerAnimated:YES];
		}
		else
			[tool ShowAlert:I(@"修改密码失败")];
	};
};
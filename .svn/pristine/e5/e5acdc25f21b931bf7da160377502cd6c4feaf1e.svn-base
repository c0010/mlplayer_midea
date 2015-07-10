//
//  CMGroupNameViewController.m
//  MLPlayer
//
//  Created by kyp on 14-6-21.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMGroupNameViewController.h"
#import "CMGroupManager.h"
#import "CMGroupInfoExitViewController.h"

@interface CMGroupNameViewController ()

@end

@implementation CMGroupNameViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (id)initWithGroupItem:(NSString *)info
{
    self = [super init];
    if (self) {
        self.textContent = info;
    }
    return self;
}

- (void)doneUpdate{
    [[NSNotificationCenter defaultCenter] postNotificationName:RefreshGroupInfoNSNotification object:nil];
    [self.navigationController popViewControllerAnimated:YES];
}

//更新群信息
- (void)commitBtnPressed:(UIButton *)sender{
    
    [tool ShowActivityIndicator:self.view];
    if (self.editType == CMGroupEditNameType) {
        if ([self stringContainsEmoji:theTextView.text]) {
            [tool ShowAlert:NSLocalizedString(@"群名称不支持表情", @"")];
            [tool DisimissActivityIndicator];
            return;
        }
        [[CMGroupManager manager] doUpdateNameWithroomID:self.roomID name:theTextView.text success:^() {
            [self doneUpdate];
        }];
    }else if(self.editType == CMGroupEditDescType){
        [[CMGroupManager manager] doUpdateDescWithroomID:self.roomID desc:theTextView.text success:^() {
            [self doneUpdate];
        }];
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    totalNum = (self.editType == CMGroupEditNameType) ? 20 : 150;

    UIView *newBak=[[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-20)];
    [newBak setBackgroundColor:kColorBackground];
    [self.view addSubview:newBak];
    CMRELEASE(newBak);
    
    UIView* rightview = [[UIView alloc] init];
	rightview.frame = CGRectMake(0, 0, 60, 44);
	commitBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    commitBtn.titleLabel.font = [UIFont boldSystemFontOfSize:18.f];
	commitBtn.frame = CGRectMake(15, 0, 45, 44);                  //发布按钮
	[commitBtn setTitle:I(@"完成") forState:UIControlStateNormal];
	[commitBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
	[commitBtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
    [commitBtn setTitleColor:[UIColor colorWithWhite:0.8 alpha:1.0] forState:UIControlStateDisabled];
	[commitBtn addTarget:self action:@selector(commitBtnPressed:) forControlEvents:UIControlEventTouchUpInside];
    
	
	UIImageView* vsep = [[UIImageView alloc] init];
	vsep.image = [UIImage imageNamed:@"navsep"];
	vsep.frame = CGRectMake(13, 0, 2, 44);
    
    [rightview addSubview:commitBtn];
    
    if (__iOS7) {
        ;
        
    }
    else{
        [rightview addSubview:vsep];
        CMRELEASE(vsep);
    }
	
	UIBarButtonItem *rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:commitBtn];
	self.navigationItem.rightBarButtonItem = rightBarButtonItem;
    CMRELEASE(rightview);
    CMRELEASE(rightBarButtonItem);
    
    UIView *backView = [[UIView alloc]initWithFrame:CGRectMake(10, 10, 300, 180)];
    backView.userInteractionEnabled = YES;
    backView.backgroundColor = [UIColor whiteColor];
    
    theTextView=[[CMTextView alloc] initWithFrame:CGRectMake(0, 0, 300, 160)];
    theTextView.textColor = [UIColor blackColor];
    theTextView.font = [UIFont systemFontOfSize:18.0];
    [theTextView setText:self.textContent];  //这里要注意要用self
    theTextView.backgroundColor = [UIColor clearColor];
    theTextView.autocorrectionType = UITextAutocorrectionTypeNo;
    theTextView.keyboardType = UIKeyboardTypeDefault;
    theTextView.returnKeyType = UIReturnKeyDone;
    theTextView.delegate = self;
    [theTextView becomeFirstResponder];

    words_Num = [[UILabel alloc]initWithFrame:CGRectMake(190, 160, 100, 15)];
    words_Num.backgroundColor = [UIColor clearColor];
    words_Num.font = [UIFont systemFontOfSize:12.0];
    words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
    words_Num.text = [NSString stringWithFormat:I(@"还能输入%d个字"),totalNum - theTextView.text.length];
    words_Num.textAlignment = UITextAlignmentRight;
    
    [backView addSubview:theTextView];
    [backView addSubview:words_Num];
    [self.view addSubview:backView];

}

- (void)textViewDidChange:(UITextView *)textView
{
	input_words_num = [textView.text length];
    if (input_words_num <= totalNum) {
        NSUInteger Remaining_words = totalNum - input_words_num;
        words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
        isBeyond = NO;
        words_Num.text = [NSString stringWithFormat:I(@"还能输入%d个字"),Remaining_words];
        commitBtn.enabled = YES;
    }
    else{
        NSUInteger Beyond_words = input_words_num - totalNum;
        words_Num.textColor = [UIColor redColor];
        isBeyond = YES;
        words_Num.text = [NSString stringWithFormat:I(@"超出%d个字"),Beyond_words];
        commitBtn.enabled = NO;
    }
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

/**判断是否输入了emoji表情
 */
- (BOOL)stringContainsEmoji:(NSString *)string
{
    __block BOOL returnValue = NO;
    
    [string enumerateSubstringsInRange:NSMakeRange(0, [string length])
                               options:NSStringEnumerationByComposedCharacterSequences
                            usingBlock:^(NSString *substring, NSRange substringRange, NSRange enclosingRange, BOOL *stop) {
                                const unichar hs = [substring characterAtIndex:0];
                                if (0xd800 <= hs && hs <= 0xdbff) {
                                    if (substring.length > 1) {
                                        const unichar ls = [substring characterAtIndex:1];
                                        const int uc = ((hs - 0xd800) * 0x400) + (ls - 0xdc00) + 0x10000;
                                        if (0x1d000 <= uc && uc <= 0x1f77f) {
                                            returnValue = YES;
                                        }
                                    }
                                } else if (substring.length > 1) {
                                    const unichar ls = [substring characterAtIndex:1];
                                    if (ls == 0x20e3) {
                                        returnValue = YES;
                                    }
                                } else {
                                    if (0x2100 <= hs && hs <= 0x27ff) {
                                        returnValue = YES;
                                    } else if (0x2B05 <= hs && hs <= 0x2b07) {
                                        returnValue = YES;
                                    } else if (0x2934 <= hs && hs <= 0x2935) {
                                        returnValue = YES;
                                    } else if (0x3297 <= hs && hs <= 0x3299) {
                                        returnValue = YES;
                                    } else if (hs == 0xa9 || hs == 0xae || hs == 0x303d || hs == 0x3030 || hs == 0x2b55 || hs == 0x2b1c || hs == 0x2b1b || hs == 0x2b50) {
                                        returnValue = YES;
                                    }
                                }
                            }];
    
    return returnValue;
}


- (void)viewDidDisappear:(BOOL)animated{
    [theTextView resignFirstResponder];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end

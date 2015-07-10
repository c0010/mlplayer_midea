//
//  CMNewGroupViewController.m
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-16.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMNewGroupViewController.h"
#import "stdafx.h"
#import "UITableViewCell+Helpper.h"
#import "CMGroupManager.h"
#import "tool.h"
#import "CMImage.h"

#define kCMNewGroupCellIdentifier @"com.apple.CMNewGroupViewController.CellIdentifier"

#define MaxDesc_Count 150
@implementation PlaceholderTextView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    if (self) {
        
    }
    return self;
    
}

- (void)setPlaceholder:(NSString *)placeholder{
    _placeholder = placeholder;
    self.text = placeholder;
    self.textColor = UIColorRGB(0xcfcfcf);
}

@end

@interface CMNewGroupViewController ()
@end

@implementation CMNewGroupViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.verArray = @[I(@"不允许加入"),I(@"不需要身份验证"),I(@"需要身份验证")];

    poisition = 2;
    
    self.currImage = DefaultGroupImage;
    m_pGroup = new CMGroup();

    m_pGroup->SetUserData((__bridge void*)self);

    if (!m_pCmGroupDataListener) {
        m_pCmGroupDataListener = new CMGroupDataUpdateListener();
    }
    m_pGroup->SetListener(m_pCmGroupDataListener, NULL);
    
    thetableView = [[UITableView alloc] initWithFrame:CGRectMake(10,0,UI_IOS_WINDOW_WIDTH - 20, UI_IOS_WINDOW_HEIGHT-20) style:UITableViewStylePlain];
	thetableView.delegate = self;
	thetableView.dataSource = self;
    [thetableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    thetableView.backgroundColor = kColorBackground;

    [self.view addSubview:thetableView];
    
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];

    return YES;

}

#pragma mark UITableView data source methods

// tell our table how many sections or groups it will have (always 1(our case)
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 2;
}


- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0 && indexPath.row == 1) {
        return 150;
    }
    return 44;
}
// tell our table how many rows it will have,(our case the size of our menuList
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	switch (section) {
		case 0:
			return 3;
		case 1:
            return 1;
		default:
			break;
	}
    
	return 0;
}

// tell our table what kind of cell to use and its title for the given row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = (UITableViewCell*)[thetableView dequeueReusableCellWithIdentifier:kCMNewGroupCellIdentifier];
    
	if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kCMNewGroupCellIdentifier];
        cell.accessoryType = UITableViewCellAccessoryNone;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    [cell setRoundSection:[self tableView:tableView numberOfRowsInSection:indexPath.section] atIndex:indexPath.row height:[self tableView:tableView heightForRowAtIndexPath:indexPath]];
    
    for (UIView *subView in cell.contentView.subviews) {
        [subView removeFromSuperview];
    }
    
    switch (indexPath.section) {
        case 0:
        {
            switch (indexPath.row) {
                case 0:
                {
                    self.nameTextfield = [[UITextField alloc] initWithFrame:CGRectMake(10, 5, 273, 34)];
                    [self.nameTextfield addTarget:self action:@selector(textFieldDone:) forControlEvents:UIControlEventEditingDidEndOnExit];
                    self.nameTextfield.returnKeyType = UIReturnKeyDone;
                    self.nameTextfield.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
                    self.nameTextfield.backgroundColor = [UIColor clearColor];
                    self.nameTextfield.clearButtonMode = UITextFieldViewModeWhileEditing;
                    self.nameTextfield.font = [UIFont systemFontOfSize:18];
                    self.nameTextfield.placeholder = I(@"群组名称");
                    self.nameTextfield.delegate = self;
                    self.nameTextfield.text =nameText;
                    [cell.contentView addSubview:self.nameTextfield];
                }
                    break;
//                case 1:
//                {
//                    UIImageView *imageView = [[UIImageView alloc] initWithFrame:CGRectMake(230, 5, 34, 34)];
//                    imageView.image = self.currImage;
//                    imageView.layer.masksToBounds = YES;
//                    imageView.layer.cornerRadius =2.f;
//                    [cell.contentView addSubview:imageView];
//                    
//                    UILabel *subLabel = [[UILabel alloc] init];
//                    subLabel.frame = CGRectMake(10, 0, 100, 44);
//                    subLabel.backgroundColor = [UIColor clearColor];
//                    subLabel.font = [UIFont systemFontOfSize:18];
//                    subLabel.textColor = [UIColor blackColor];
//                    subLabel.text = I(@"群头像");
//                    [cell.contentView addSubview:subLabel];
//                    
//                    cell.detailTextLabel.text = nil;
//                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
//                    cell.selectionStyle = UITableViewCellSelectionStyleGray;
//                    cell.selectionStyle = UITableViewCellSelectionStyleNone;
//                }
//                    break;
                case 1:
                {
                    self.descTextView = [[PlaceholderTextView alloc] init];
                    self.descTextView.frame = CGRectMake(3, 5, 290, 115);
                    self.descTextView.font = [UIFont systemFontOfSize:18];
                    self.descTextView.backgroundColor = [UIColor clearColor];
                    self.descTextView.placeholder=I(@"群组简介（不能超过150个字）");
                    self.descTextView.autocorrectionType = UITextAutocorrectionTypeNo;
                    self.descTextView.keyboardType = UIKeyboardTypeDefault;
                    self.descTextView.returnKeyType = UIReturnKeyDone;
                    
                    self.descTextView.delegate = self;
                    [cell.contentView addSubview:self.descTextView];
                    
                    words_Num = [[UILabel alloc]initWithFrame:CGRectMake(90, 125, 200, 20)];
                    words_Num.backgroundColor = [UIColor clearColor];
                    words_Num.font = [UIFont systemFontOfSize:12.0];
                    words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
                    words_Num.text = [NSString stringWithFormat:I(@"还能输入%d个字"),MaxDesc_Count];
                    words_Num.textAlignment = UITextAlignmentRight;
                    [cell.contentView addSubview:words_Num];
                }
                    break;
                case 2:
                {
                    UILabel *titleLabel = [[UILabel alloc] init];
                    titleLabel.frame = CGRectMake(110, 10, 160, 24);
                    titleLabel.textAlignment = NSTextAlignmentRight;
                    titleLabel.backgroundColor = [UIColor clearColor];
                    titleLabel.font = [UIFont systemFontOfSize:18];
                    titleLabel.textColor = [UIColor lightGrayColor];
                    titleLabel.text = [self.verArray objectAtIndex:poisition];
                    [cell.contentView addSubview:titleLabel];

                    
                    UILabel *subLabel = [[UILabel alloc] init];
                    subLabel.frame = CGRectMake(10, 0, 100, 44);
                    subLabel.backgroundColor = [UIColor clearColor];
                    subLabel.font = [UIFont systemFontOfSize:18];
                    subLabel.textColor = [UIColor blackColor];
                    subLabel.text = I(@"身份验证");
                    [cell.contentView addSubview:subLabel];
                    
                    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
                    cell.selectionStyle = UITableViewCellSelectionStyleGray;

                }
                    break;
                default:
                    break;
            }
        }
            
            break;
            
        case 1:
        {
//            UILabel *titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(100, 0, 100, 44)];
//            titleLabel.textAlignment = UITextAlignmentCenter;
//            titleLabel.backgroundColor = [UIColor clearColor];
//            titleLabel.font = [UIFont systemFontOfSize:18];
//            titleLabel.textColor = [UIColor colorWithRed:27.0/255.0 green:109.0/255.0 blue:179.0/255.0 alpha:1.0f];
//            titleLabel.text = I(@"保存");
//            [cell.contentView addSubview:titleLabel];
//            
//            cell.selectionStyle = UITableViewCellSelectionStyleGray;
            
            UIButton *agreeButton= [UIButton buttonWithType:UIButtonTypeCustom];
            agreeButton.tag = 1;
            agreeButton.frame = CGRectMake(0, 0, 300, 44);
            [agreeButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            [agreeButton setBackgroundImage:[CMImage imageWithColor:UIColorRGB(0x085ba1)] forState:UIControlStateNormal];
            [agreeButton setBackgroundImage:[CMImage imageWithColor:UIColorRGB(0x065a91)] forState:UIControlStateHighlighted];
            [agreeButton setTitle:I(@"保存") forState:UIControlStateNormal];
            [agreeButton addTarget:(id)self action:@selector(createNewGroup:) forControlEvents:UIControlEventTouchUpInside];
            [agreeButton setAccessibilityLabel:I(@"提交")];
            [cell.contentView addSubview:agreeButton];
        }
            break;
        default:
            break;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [thetableView deselectRowAtIndexPath:indexPath animated:YES];
    
    [self hideKeyBoard];
    
    if (indexPath.section == 0 && indexPath.row == 2) {
        UIActionSheet *action = [[UIActionSheet alloc]initWithTitle:nil
                                                           delegate:self
                                                  cancelButtonTitle:I(@"取消")
                                             destructiveButtonTitle:nil
                                                  otherButtonTitles:I(@"不允许加入"),I(@"不需要身份验证"),I(@"需要身份验证"), nil];
        action.tag =101;
        [action showInView:self.view];
    }
}

- ( CGFloat )tableView:( UITableView *)tableView heightForHeaderInSection:(NSInteger )section
{
    
    if (section == 1) {
        return 30.0 ;
    }
    return 10.0 ;
    
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
    return [[UIView alloc]initWithFrame:CGRectZero];
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if (range.location >= 20){
        return NO; // return NO to not change text
    }
    nameText = [textField.text stringByReplacingCharactersInRange:range withString:string];
    return YES;
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex{
    if (buttonIndex != actionSheet.cancelButtonIndex) {
        switch (actionSheet.tag) {
            case 100:
            {
                switch (buttonIndex) {
                    case 0:
                    {
                        UIImagePickerController *picker =[[UIImagePickerController alloc] init];
                        picker.delegate = self;
                        picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
                        picker.allowsEditing = YES;
                        
                        if (__iOS7)
                        {
                          //  [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
                            MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
                            appDelegate.window.tintColor = [UIColor whiteColor];
                        }
                        [self presentModalViewController:picker animated:YES];
                    }
                        break;
                    case 1:
                    {
                        if ([UIImagePickerController isSourceTypeAvailable: UIImagePickerControllerSourceTypeCamera])
                        {
                            UIImagePickerController *picker = [[UIImagePickerController alloc] init];
                            picker.delegate = self;
                            picker.allowsEditing = YES;
                            picker.sourceType = UIImagePickerControllerSourceTypeCamera;
                            [self presentModalViewController:picker animated:YES];
                        }
                        else
                        {
                            UIAlertView *alert = [[UIAlertView alloc]
                                                  initWithTitle:@"Error accessing photo library"
                                                  message:@"Device does not support a photo library"
                                                  delegate:nil
                                                  cancelButtonTitle:@"ok!"
                                                  otherButtonTitles:nil];
                            [alert show];
                        }
                    }
                        break;
                    default:
                        break;
                }
            }
                break;
            case 101:
            {
                poisition = buttonIndex;
                [thetableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:2 inSection:0]] withRowAnimation:UITableViewRowAnimationFade];
            }
                break;
            default:
                break;
        }
       
    }
}

- (void)textViewDidChangeSelection:(PlaceholderTextView *)textView
{
    if ([textView.text isEqualToString:textView.placeholder] && !endEdit) {
        textView.text = @"";
        textView.textColor = [UIColor blackColor];
    }
}

- (void)textViewDidBeginEditing:(PlaceholderTextView *)textView{
    if ([textView.text isEqualToString:textView.placeholder]) {
        textView.text = @"";
        endEdit = NO;
    }
    textView.textColor = [UIColor blackColor];
    [thetableView setContentOffset:CGPointMake(0, 50) animated:YES];
    thetableView.scrollEnabled = NO;
}

//自定义TextView的placeholder
- (void)textViewDidChange:(PlaceholderTextView *)textView{
    input_words_num = [textView.text length];
    if (input_words_num == 0) {
        textView.text = textView.placeholder;
        textView.textColor = UIColorRGB(0xcfcfcf);
        textView.selectedRange = NSMakeRange(0, 0);
    }else{
        if ([[textView.text substringFromIndex:1] isEqualToString:textView.placeholder]) {
            textView.text = [textView.text substringToIndex:1];
            textView.textColor = [UIColor blackColor];
        }
    }
    
    if (input_words_num <= MaxDesc_Count) {
        NSUInteger Remaining_words = MaxDesc_Count - input_words_num;
        words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
        words_Num.text = [NSString stringWithFormat:I(@"还能输入%d个字"),Remaining_words];
    }
    else{
        NSUInteger Beyond_words = input_words_num - MaxDesc_Count;
        words_Num.textColor = [UIColor redColor];
        words_Num.text = [NSString stringWithFormat:I(@"超出%d个字"),Beyond_words];
    }
}

- (void)textViewDidEndEditing:(PlaceholderTextView *)textView{
    if ([textView.text length] == 0) {
        endEdit = YES;
        textView.text = textView.placeholder;
        textView.textColor = UIColorRGB(0xcfcfcf);
    }
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
	if([text isEqualToString:@"\n"])
	{
		[textView endEditing:YES];
		[thetableView setContentOffset:CGPointMake(0, 0) animated:YES];
        thetableView.scrollEnabled = YES;
		return NO;
	}
    
	return YES;
}

- (void)textFieldDone:(UITextField *)sender{
    nameText = sender.text;
    [sender resignFirstResponder];
}

-(void)createNewGroup:(UIButton *)sender
{
    NSString* name = [self.nameTextfield.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];;
    NSString* desc = self.descTextView.text;
    
    if([self stringContainsEmoji:self.nameTextfield.text])
    {
        [tool ShowAlert:NSLocalizedString(@"群名称不支持表情", @"")];
        return;
    }
    
    if ([desc isEqualToString:self.descTextView.placeholder]) {
        desc = @"";
    }
    
    if (!name || [name isEqualToString:@""]) {
        [tool ShowAlert:I(@"群组名称不能为空！")];
        nameText = @"";
        self.nameTextfield.text = @"";
        return;
    }
    
    if (!desc || [desc length] == 0){
        [tool ShowAlert:I(@"群组简介名称不能为空")];
        return;
    }
    
    if (desc && desc.length > MaxDesc_Count) {
        [tool ShowAlert:I(@"群组简介不能超过150个字!")];
        return;
    }
    
    CMGroupManager *p_Manager = [CMGroupManager manager];
    [tool ShowActivityIndicator:self.view];
//cancel:^{
//
//        CMFileUpload::GetInstance()->Stop();
////        [p_Manager clear];
//    }];
    sender.userInteractionEnabled = NO;
    [p_Manager doCreateGroupWithName:name desc:desc flag:poisition success:^(TGroupInfoItem *) {
        
        sender.userInteractionEnabled = YES;

        [self.navigationController popToRootViewControllerAnimated:YES];
        
        [[NSNotificationCenter defaultCenter] postNotificationName:RefreshGroupListNSNotification object:nil];
        [tool ShowAlert:I(@"创建成功")];
    } failure:^(int errorCode) {
        
        sender.userInteractionEnabled = YES;
    }];
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


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark UIImagePickerControllerDelegate
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
    
    UIImage* oralImg=[info objectForKey:UIImagePickerControllerEditedImage];
    
    double image_w = oralImg.size.width;
    double image_h = oralImg.size.height;

    if (image_h > 110)
    {
        image_h = 110;
    }

    if (image_w > 100)
    {
        image_w = 110;
    }

    self.currImage = [self scaleFromImage:oralImg toSize:CGSizeMake(image_w, image_h)];
    [thetableView reloadRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:1 inSection:0]] withRowAnimation:UITableViewRowAnimationFade];

//保存到本地
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString *cachesDir = [paths objectAtIndex:0];

    imagePath = [cachesDir stringByAppendingPathComponent:@"grouptemp.png"];
    NSError* err=nil;

    if(![UIImagePNGRepresentation(oralImg) writeToFile:imagePath options:NSDataWritingAtomic error:&err])
        NSLog(@"save file failed :err%@",[err localizedFailureReason]);

    [picker dismissModalViewControllerAnimated:YES];
    
    if (__iOS7)
    {
      //  [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
        MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
        appDelegate.window.tintColor = UIColorRGB(0x1a6cc3);
    }
}

- (UIImage *) scaleFromImage: (UIImage *) image toSize: (CGSize) size
{
    UIGraphicsBeginImageContext(size);
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    [picker dismissModalViewControllerAnimated:YES];
    
    if (__iOS7)
    {
       // [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
        
        MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
        appDelegate.window.tintColor = UIColorRGB(0x1a6cc3);
    }
}

- (void)hideKeyBoard{
    [thetableView setContentOffset:CGPointMake(0, 0) animated:YES];
    thetableView.scrollEnabled = YES;
    [self.nameTextfield resignFirstResponder];
    [self.descTextView resignFirstResponder];
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

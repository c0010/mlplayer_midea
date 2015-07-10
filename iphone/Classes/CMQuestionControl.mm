#import "CMQuestionControl.h"
#import <QuartzCore/QuartzCore.h>
#import "CMQaCategoryControl.h"
#import "CMCreditControl.h"
#import "ImageRightButton.h"
#import "CMImageDetailViewControl.h"
#import "GlobalAlertCenter.h"
#import "tool.h"
#import "cmfileinfo.h"
#include "cmqacategory.h"
#include "cmhandler.h"
#import "CMAddressControl.h"
#import "CMExpertsController.h"
#define KEYBOARDHIDE_HEIGHT  [[UIScreen mainScreen] bounds].size.height * 2/5
#define IMAGE_WIDE  41
#define IMAGE_HEIGHT 41





const int h = 20;
const int ContentOffset = 280;
const int ContentMinOffset = 60;
const float MoveAnimationDuration = 0.3;

@implementation CMQuestionControl{
    float KEYBOARDSHOW_HEIGHT;
}
@synthesize categoryid;
@synthesize imagepath;
@synthesize sTextview;

- (id)init
{
    self = [super init];
    if (self) {
        
        self.expertsDict = [[NSMutableDictionary alloc]init];
        self.expertsNameLocDict = [[NSMutableDictionary alloc]init];
        
        

        scoreview=[[UIView alloc]init];
        scoreview.frame=CGRectMake(0, 235,UI_IOS_WINDOW_WIDTH, 330);
        scoreview.backgroundColor=[UIColor whiteColor];
        scoreview.hidden = YES;
        
        
        
        
        
    }
    return self;
}

- (void)viewWillAppear:(BOOL)animated {
	
    //    [textquestion becomeFirstResponder];
	[super viewWillAppear:animated];
    
}

-(void)viewWillDisappear:(BOOL)animated
{
    [textquestion resignFirstResponder];
    
    CMString sPath = CMGlobal::TheOne().GetUserDir() + L"question.plist";
    
    NSString* _filePath = [NSString stringWithUTF8String:(const char*)sPath];
    
    if ( textquestion.text.length == 0 ) {
        [self.expertsDict removeAllObjects];
        [self.expertsNameLocDict removeAllObjects];
    }
    
    NSMutableDictionary *data = [NSMutableDictionary dictionaryWithObjectsAndKeys:textquestion.text,@"text",self.expertsDict,@"experts",self.expertsNameLocDict,@"expertsRange", nil];
    
    if (![data writeToFile:_filePath atomically:YES]) {
        NSLog(@"wirte error");
    }
    
    
    [super viewWillDisappear:YES];
}


- (void)keyboardWillShow:(NSNotification *)aNotification {
    NSDictionary *info = [aNotification userInfo];
    
    //获取高度
    NSValue *value = [info objectForKey:@"UIKeyboardBoundsUserInfoKey"];
    CGSize keyboardSize = [value CGRectValue].size;
    float keyboardHeight = keyboardSize.height;
    KEYBOARDSHOW_HEIGHT = UI_IOS_WINDOW_HEIGHT - 150.0 - keyboardHeight;
    
}

-(void)loadTableList
{
    
    [tool DisimissActivityIndicator];
    
    if(!m_pQcategory)
	{
		m_pQcategory =CMQACategory::GetInstance();
        
	}
    NSInteger itemCount =  m_pQcategory->TopItemCount();
    
    CGFloat tableViewHeight = itemCount * 44;
    
    if (tableViewHeight > self.view.bounds.size.height - 56 - 10)
    {
        [tableviewlist setFrame:CGRectMake(10, 56, UI_IOS_WINDOW_WIDTH-20, self.view.bounds.size.height - 56 - 10)];
        tableviewlist.scrollEnabled = YES;
    }
    else
    {
        [tableviewlist setFrame:CGRectMake(10, 56, UI_IOS_WINDOW_WIDTH-20, tableViewHeight)];
        tableviewlist.scrollEnabled = NO;
    }
    
//    if(itemCount <=5)
//    
//        [tableviewlist setFrame:CGRectMake(10, 56, UI_IOS_WINDOW_WIDTH-20, itemCount*44)];
//    
//    else
//         [tableviewlist setFrame:CGRectMake(10, 56, UI_IOS_WINDOW_WIDTH-20, 5*44)];
    


    
   [self->tableviewlist reloadData];
    
        
}


- (void)viewDidLoad
{
	[super viewDidLoad];
    
    
    UIView *newBak=[[UIView alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-20)];
    
    [newBak setBackgroundColor:kColorBackground];
    [self.view addSubview:newBak];
    CMRELEASE(newBak);
    
    NSNotificationCenter *defaultCenter = [NSNotificationCenter defaultCenter];
    [defaultCenter addObserver:self
                      selector:@selector(keyboardWillShow:)
                          name:UIKeyboardWillShowNotification
                        object:nil];
    
    [defaultCenter addObserver:self
                      selector:@selector(ImageDelect)
                          name:@"image_delect"
                        object:nil];
    
    
//    UIView* rightview = [[UIView alloc] init];
//	rightview.frame = CGRectMake(0, 0, 60, 44);
	UIButton *commitBtn = [UIButton buttonWithType:UIButtonTypeCustom];
	commitBtn.frame = CGRectMake(15, 0, 45, 44);                  //发布按钮
	[commitBtn setTitle:I(@"提交") forState:UIControlStateNormal];
	[commitBtn setTitleColor:kColorButtonTitle forState:UIControlStateNormal];
	[commitBtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
	[commitBtn addTarget:self action:@selector(commitquestion) forControlEvents:UIControlEventTouchUpInside];
    
	
//	UIImageView* vsep = [[UIImageView alloc] init];
//	vsep.image = [UIImage imageNamed:@"navsep"];
//	vsep.frame = CGRectMake(13, 0, 2, 44);
//    
//    
//    [rightview addSubview:commitBtn];
    
//    if (__iOS7) {
//        ;
//
//    }
//    else{
//        [rightview addSubview:vsep];
//        CMRELEASE(vsep);
//    }
	
	UIBarButtonItem *rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:commitBtn];
	self.navigationItem.rightBarButtonItem = rightBarButtonItem;
    CMRELEASE(rightview);
    CMRELEASE(rightBarButtonItem);
    
   
	self.title = I(@"提问");
    self.titleLabel.text = self.navigationItem.title;
	
	CGRect f = self.view.bounds;
	//question
	
    //文本输入框上方的UIView
    CGRect top_frame=CGRectMake(10, 12, f.size.width-20, 44);
    top_view=[[UIView alloc]initWithFrame:top_frame];
    top_view.backgroundColor = [UIColor whiteColor];
    top_view.layer.cornerRadius = 2.0;
    top_view.layer.borderWidth = 1.0;
    top_view.layer.borderColor = [UIColor colorWithRed:195/255.0 green:195/255.0 blue:195/255.0 alpha:1.0].CGColor;
    top_view.layer.shadowColor   = [UIColor colorWithRed:195/255.0 green:195/255.0 blue:195/255.0 alpha:1.0].CGColor;
    [self.view addSubview:top_view];
  
    //top_view中的button
    btnqcategory=[[ImageRightButton alloc] init];
    btnqcategory.titleLabel.font = [UIFont systemFontOfSize:15.0];
	[btnqcategory setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateNormal];
	[btnqcategory setTitle:I(@"选择问题分类")  forState:UIControlStateNormal];
    [btnqcategory setImage:[UIImage imageNamed:@"downarrow"] forState:UIControlStateNormal];
	[btnqcategory addTarget:self action:@selector(gotoqcategory) forControlEvents:UIControlEventTouchUpInside];
    //btnqcategory.frame = CGRectMake(100.0, CGRectGetMaxY(bg_view.frame) + h-20, 80, 25.0);
    btnqcategory.frame = CGRectMake(10, 10, top_view.frame.size.width, 25.0);
	[top_view addSubview:btnqcategory];
    CMRELEASE(top_view);

	CGRect frame = CGRectMake(10, 68,f.size.width-20,115.0);        //控制文本输入框的坐标
    bg_view = [[UIView alloc]initWithFrame:frame];
    bg_view.backgroundColor = [UIColor whiteColor];
    bg_view.layer.cornerRadius = 2.0;
    bg_view.layer.borderWidth = 1.0;
    bg_view.layer.borderColor = [UIColor colorWithRed:195/255.0 green:195/255.0 blue:195/255.0 alpha:1.0].CGColor;
    bg_view.layer.shadowColor   = [UIColor colorWithRed:195/255.0 green:195/255.0 blue:195/255.0 alpha:1.0].CGColor;
    [self.view addSubview:bg_view];
    
    textquestion = [[CMTextView alloc] initWithFrame:frame];
	textquestion.font = [UIFont systemFontOfSize:12.0];
	textquestion.backgroundColor = [UIColor clearColor];
	textquestion.autocorrectionType = UITextAutocorrectionTypeNo;
	textquestion.keyboardType = UIKeyboardTypeDefault;
	textquestion.returnKeyType = UIReturnKeyDone;
    
    CMString sPath = CMGlobal::TheOne().GetUserDir() + L"question.plist";
    
    NSString* _filePath = [NSString stringWithUTF8String:(const char*)sPath];
    
    NSMutableDictionary *data = [NSMutableDictionary dictionaryWithContentsOfFile:_filePath];
    
    textquestion.text = [data objectForKey:@"text"];
    
    self.expertsDict = [data objectForKey:@"experts"];
    
    if (!self.expertsDict) {
        self.expertsDict = [[NSMutableDictionary alloc]init];
    }
    
    self.expertsNameLocDict = [data objectForKey:@"expertsRange"];

    if (!self.expertsNameLocDict) {
        self.expertsNameLocDict = [[NSMutableDictionary alloc]init];
    }

    if(DeviceSystemMajorVersion() < 6)
    {
        
    }
    else
    {
        textquestion.clearsOnInsertion = NO;
    }
    
	textquestion.delegate = self;
    
    words_Num = [[UILabel alloc]initWithFrame:CGRectMake(CGRectGetMaxX(textquestion.frame) - 130.0, CGRectGetMaxY(bg_view.frame) - 28.0, 125.0, 25.0)];
    words_Num.backgroundColor = [UIColor clearColor];
    words_Num.font = [UIFont systemFontOfSize:12.0];
    words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
    //words_Num.text = @"还能输入200个字";
    words_Num.text=I(@"还能输入200字");
    words_Num.textAlignment = UITextAlignmentRight;
    
	   
    [self.view addSubview:textquestion];
    [self.view addSubview:imgView1];
    [self.view addSubview:words_Num];
    
  	
	
    
    
    
	//[tableviewlist release];
    checkpos = -1;
    
    btnteacher = [UIButton buttonWithType:UIButtonTypeCustom];
    btnteacher.frame = CGRectMake(152, 195, 80, 33);
    [btnteacher setBackgroundImage:[UIImage imageNamed:@"teacher_n"] forState:UIControlStateNormal];
    [btnteacher setBackgroundImage:[UIImage imageNamed:@"teacher_p"] forState:UIControlStateHighlighted];
    [btnteacher setTitle:I(@"@专家") forState:UIControlStateNormal];
    [btnteacher addTarget:self action:@selector(segselected:) forControlEvents:UIControlEventTouchUpInside];
    btnteacher.titleLabel.font = [UIFont systemFontOfSize:15.0];
    [btnteacher setTitleColor:UIColorRGB(0x333333) forState:UIControlStateNormal];
    btnteacher.tag = 1;
    [self.view addSubview:btnteacher];
    
    btn_credit = [UIButton buttonWithType:UIButtonTypeCustom];
    btn_credit.frame = CGRectMake(152 + 79, 195, 80, 33);
    [btn_credit setBackgroundImage:[UIImage imageNamed:@"credit_n"] forState:UIControlStateNormal];
    [btn_credit setBackgroundImage:[UIImage imageNamed:@"credit_p"] forState:UIControlStateHighlighted];
    [btn_credit setTitle:I(@"悬赏分值") forState:UIControlStateNormal];
    [btn_credit addTarget:self action:@selector(segselected:) forControlEvents:UIControlEventTouchUpInside];
    btn_credit.tag = 2;
    btn_credit.titleLabel.font = [UIFont systemFontOfSize:15.0];
    [btn_credit setTitleColor:UIColorRGB(0x333333) forState:UIControlStateNormal];
    [self.view addSubview:btn_credit];

    
    btnuploadimage=[[UIButton alloc]init];
    btnuploadimage.frame=CGRectMake(10, 197, 27, 27 );
    //[btnuploadimage setTitle:I(@"图片按钮") forState:UIControlStateNormal];
    [btnuploadimage setImage:[UIImage imageNamed:@"photo_normal"] forState:UIControlStateNormal];
    [self.view addSubview:btnuploadimage];
    [btnuploadimage addTarget:self action:@selector(uploadimage:) forControlEvents:UIControlEventTouchUpInside];
    
    //
    if (!anonymity_btn) {
        anonymity_btn= [[CheckBoxButton alloc] initWithFrame:CGRectMake(CGRectGetMaxX(btnuploadimage.frame) + 20, btnuploadimage.frame.origin.y + 3, 80.0, 27.0)];
        anonymity_btn.CheckType = 1;
        
        anonymity_btn.Check = NO;
    }
    [anonymity_btn setTitle:I(@"匿名")];
    [anonymity_btn setColor:UIColorRGB(0x999999)];
    [self.view addSubview:anonymity_btn];
    
    //image for loading photo
    imgView1 = [[UIImageView alloc]initWithFrame:CGRectMake(CGRectGetMinX(bg_view.frame) + 10.0, CGRectGetMaxY(bg_view.frame) - 40.0, 35.0, 35.0)];
    imgView1.backgroundColor = [UIColor clearColor];
    imgView1.contentMode = UIViewContentModeScaleAspectFit;
    imgView1.layer.shadowOpacity = 0.3;
    imgView1.userInteractionEnabled = YES;
    imgView1.layer.cornerRadius = 4.0;
    imgView1.layer.masksToBounds = YES;
    imgView1.layer.shadowColor = [UIColor colorWithWhite:0.0 alpha:0.5].CGColor;
    [imgView1.layer setShadowOffset:CGSizeMake(0, 1)];
    imgView1.hidden = YES;
    // imgView1.image = [UIImage imageNamed:@"test_image"];
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(ShowImageView)];
    [imgView1 addGestureRecognizer:tap];
    [imgView1 addObserver:self forKeyPath:@"image" options:NSKeyValueObservingOptionInitial context:nil];
    CMRELEASE(tap);
    [self.view addSubview:imgView1];
    
    tableviewlist = [[CMTableView alloc] initWithFrame:CGRectMake(10,56,f.size.width-20,300) style:UITableViewStylePlain];
	[tableviewlist setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
	tableviewlist.backgroundColor = [UIColor whiteColor];
	tableviewlist.scrollEnabled = YES;
	tableviewlist.delegate = self;
	tableviewlist.dataSource = self;
    tableviewlist.hidden=YES;
    [tableviewlist  setSeparatorStyle:UITableViewCellSeparatorStyleSingleLine];
    
    
    [self.view addSubview:scoreview];

    [self.view addSubview:tableviewlist];


    //显示颜色
    [textquestion setAllKeyWordTextArray:[self.expertsDict allValues] WithFont:[UIFont systemFontOfSize:12] AndColor:[UIColor blueColor]];
    
    
    //更新字数
    [self updateWordCount:textquestion.text];

}



-(void)uploadimage:(id)sender
{
    UIActionSheet *action = [[UIActionSheet alloc] initWithTitle:I(@"添加图片")
                                                        delegate:self
                                               cancelButtonTitle:I(@"取消")
                                          destructiveButtonTitle:nil
                                               otherButtonTitles:I(@"相册"),I(@"拍照"), nil];
    [action showInView:self.view.superview];

}



- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0)
    {
        UIImagePickerController *picker =[[UIImagePickerController alloc] init];
        picker.delegate = self;
        picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;

        //提问上传用原图，不允许编辑
        picker.allowsEditing = NO;

        if (__iOS7)
        {
          //  [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
            MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
            appDelegate.window.tintColor = [UIColor whiteColor];
        }
        [self presentModalViewController:picker animated:YES];
        
    }
    else if (buttonIndex == 1)
    {
        if ([UIImagePickerController isSourceTypeAvailable: UIImagePickerControllerSourceTypeCamera])
        {
            UIImagePickerController *picker = [[UIImagePickerController alloc] init];
            picker.delegate = self;
            //提问上传用原图，不允许编辑
            picker.allowsEditing = NO;
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
    else if (buttonIndex == 2)
    {
        [actionSheet dismissWithClickedButtonIndex:buttonIndex animated:YES];
    }
}


#pragma mark UIImagePickerControllerDelegate
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    //  imgView1.hidden = NO;
    [picker dismissModalViewControllerAnimated:YES];
    
    if (__iOS7)
    {
      //  [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
        
        MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
        appDelegate.window.tintColor = UIColorRGB(0x1a6cc3);
    }
}


- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
    
    @autoreleasepool {
        imgView1.image=nil;
        UIImage* oralImg=[info objectForKey:UIImagePickerControllerOriginalImage];
        
        double image_w = oralImg.size.width;
        double image_h = oralImg.size.height;
        
        if (image_h < kImgUploadSizeMax && image_w < kImgUploadSizeMax) {
            ;
        }
        else{
            double wide_per = image_w/kImgUploadSizeMax;
            double height_per = image_h/kImgUploadSizeMax;
            if (wide_per >= height_per) {
                image_w = kImgUploadSizeMax;
                image_h = image_h / wide_per;
            }
            else{
                image_h = kImgUploadSizeMax;
                image_w = image_w / height_per;
            }
            oralImg = [self scaleFromImage:oralImg toSize:CGSizeMake(image_w, image_h)];
        }

        
        //保存到本地
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
        NSString *cachesDir = [paths objectAtIndex:0];
        
        NSDate *date = [NSDate date];
        NSDateFormatter *format = [[NSDateFormatter alloc] init];
        [format setDateFormat:@"yyyyMMddHHmmss"];
        NSString *strDate = [format stringFromDate:date];
        
        // concatenate the file name "contacts" to the end of the path
        NSString * strImageName;
        strImageName = [cachesDir stringByAppendingPathComponent:[strDate stringByAppendingString:@".png"]];
        strImageName = [cachesDir stringByAppendingPathComponent:@"temp.png"];
        
        NSError* err=nil;
        if(![UIImagePNGRepresentation(oralImg) writeToFile:strImageName options:NSDataWritingAtomic error:&err])
            NSLog(@"save file failed :err%@",[err localizedFailureReason]);
        
        self.imagepath=strImageName;
        imgView1.hidden=NO;
        imgView1.image=oralImg;
    }
    [picker dismissModalViewControllerAnimated:YES];
    
    if (__iOS7)
    {
       // [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
        
        MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
        appDelegate.window.tintColor = UIColorRGB(0x1a6cc3);
    }
}


- (void)ShowImageView{
    CMImageDetailViewControl *cmimageController = [[CMImageDetailViewControl alloc]init];
    [cmimageController setImage:imgView1.image];
    cmimageController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    cmimageController.isURL = NO;
    //    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationFade];
    [self presentModalViewController:cmimageController animated:YES];
    CMRELEASE(cmimageController);
}

- (void)ImageDelect{
    imgView1.hidden = YES;
    if(![[NSFileManager defaultManager]removeItemAtPath:imagepath error:NULL])
    {
        CM_ERR("imagepath delete error!");
    }
    
    imagepath = nil;
    imgView1.image = nil;
}

- (UIImage *) scaleFromImage:(UIImage *)image toSize:(CGSize) size
{
    UIGraphicsBeginImageContext(size);
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}


-(void)didSelectCredit:(UIButton*)btn
{
    int previousTag = 0;
    
    if(creditnum>0)
        previousTag = creditnum/5;
    
    
    NSInteger creditPoint =btn.tag*5;
    
    
    //比较分值
    
    if(CMMyInfo::GetInstance()->GetValue()<creditPoint)
    {
        [tool ShowAlert:I(@"积分不足！")];
        return;
        
    }
    
    
    //若比较分值没问题，则设置分值
    creditnum=btn.tag*5;
    
    
    //显示设置的分值
    NSString *str=[NSString stringWithFormat:I(@"悬赏%d分"),creditnum];
    [btn_credit setTitle:str forState:UIControlStateNormal];
    
    scoreview.hidden=YES;
    
}

-(void)showcreditview
{
    
    double btn_w = 75;
    double btn_h = 36;
    CGRect frame = scoreview.bounds;
    //double btn_space = ((frame.size.width - 2 * 40) - 3 * btn_w)/2;
    double btn_space=20;
    
    if (UI_IOS_WINDOW_HEIGHT > 480) {
        ;
    }
    else{
        btn_h = 34;
        btn_space = 18;
    }
    
    int selTag =    creditnum/5;
    
    for (int i = 1; i <= 9; i ++)
    {
        UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
        btn.layer.borderWidth=1.0f;
        btn.layer.borderColor=[[UIColor grayColor] CGColor];
        btn.layer.cornerRadius=5.0f;
        [btn setTitle:[NSString stringWithFormat:@"%d分",i * 5] forState:UIControlStateNormal];
        [btn setTitle:[NSString stringWithFormat:@"%d分",i * 5] forState:UIControlStateHighlighted];
        [btn setTitle:[NSString stringWithFormat:@"%d分",i * 5] forState:UIControlStateSelected];

        btn.tag = i;
        [btn setBackgroundColor:[UIColor whiteColor]];
        [btn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
  
        
        if(i == selTag)
        {
            [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
            
            [btn setBackgroundColor:[UIColor colorWithRed:33.0f/255.0f green:110.0/255.0f blue:177.0/255.0f alpha:1]];
            
            [btn.layer setBorderWidth:0.0f];
        }
        
        
        [btn addTarget:self action:@selector(didSelectCredit:) forControlEvents:UIControlEventTouchUpInside];
        if (i <=3) {
            btn.frame = CGRectMake(25 + (btn_w + btn_space) * (i - 1), 35, btn_w, btn_h);
        }
        else if(i > 3 && i <= 6){
            btn.frame = CGRectMake(25 + (btn_w + btn_space) * (i - 4), 90, btn_w, btn_h);
        }
        else if(i > 6){
            btn.frame = CGRectMake(25 + (btn_w + btn_space) * (i - 7), 145, btn_w, btn_h);
        }
        [scoreview addSubview:btn];
    }
    
    
}


-(void )segselected:(id)sender
{
     UIButton* control = (UIButton*)sender;
     switch (control.tag)
    {
            
        case 1:
            
            if(scoreview.hidden==NO)
                scoreview.hidden=YES;
            
            [self gotoexpertsControl];
            break;
            
        case 2:
            if(scoreview.hidden==YES)
            {
                //退掉键盘
                [textquestion resignFirstResponder];
                
                if(scoreview==nil)
                {
                    scoreview=[[UIView alloc]init];
                    scoreview.frame=CGRectMake(0, 235,UI_IOS_WINDOW_WIDTH, 330);
                    scoreview.backgroundColor=[UIColor whiteColor];
                    [self.view addSubview:scoreview];
                    
                }
                
                scoreview.hidden = NO;
                
                if(lblcredit==nil)
                {
                    
                    lblcredit=[[UILabel alloc]init];
                    lblcredit.frame=CGRectMake(12, 0, 150, 35);
                    lblcredit.textAlignment = UITextAlignmentLeft;
                    lblcredit.backgroundColor = [UIColor clearColor];
                    
                    lblcredit.text=I(@"我的积分:");

                    lblcredit.textColor = [UIColor blackColor];
                    [scoreview addSubview:lblcredit];
                }
                
                if(self.lbCreditPoint ==nil)
                {
                    self.lbCreditPoint = [[UILabel alloc]initWithFrame:CGRectMake(90, 2, 200, 30)];
                    
                    self.lbCreditPoint.textColor=[UIColor colorWithRed:0.0f/255.0f green:100.0/255.0f blue:174.0/255.0f alpha:1];
                    [scoreview addSubview:self.lbCreditPoint];

                }
                
                self.lbCreditPoint .text=[NSString stringWithFormat:@"%d", CMMyInfo::GetInstance()->GetValue()];

            
                [self showcreditview];
            
            }
            else
            {
                scoreview.hidden=YES;
            }
            
            break;
     
    }
}

- (void)gotoexpertsControl
{
    if (self.categoryid == nil ) {
        [tool ShowAlert:I(@"请选择问题分类")];
        return;
    }
    
    CMExpertsController* expertsControl = [[CMExpertsController alloc] init];
    expertsControl.categoryID = self.categoryid;
    
    expertsControl.title = @"";
    expertsControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
    expertsControl.navigationController.navigationBarHidden = NO;
    expertsControl.tabBarController.tabBar.hidden = YES;
    expertsControl.hidesBottomBarWhenPushed = YES;
    expertsControl.navigationController.delegate = self;
    expertsControl.questionctrl=self;
    [self.navigationController pushViewController:expertsControl animated:YES];

}



- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context{
    if ([keyPath isEqualToString:@"image"]) {
        if (imgView1.hidden) {
            textquestion.frame = CGRectMake(CGRectGetMinX(textquestion.frame), CGRectGetMinY(textquestion.frame), CGRectGetWidth(textquestion.frame), 115.0 - 25.0);
        }
        else{
            textquestion.frame = CGRectMake(CGRectGetMinX(textquestion.frame), CGRectGetMinY(textquestion.frame), CGRectGetWidth(textquestion.frame), 115.0 - 45.0);
            
        }
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch *touch = [[event allTouches] anyObject];
	CGPoint touchPoint = [touch locationInView:self.view];
	if(!CGRectContainsPoint(popview.frame, touchPoint))
	{
		popview.hidden = YES;
		[btncredit setImage:[UIImage imageNamed:@"downarrow"] forState:UIControlStateNormal];
	}
	[textquestion resignFirstResponder];
    NSLog(@"key board hide %f",KEYBOARDHIDE_HEIGHT);
    
    
	if(textquestion.text.length == 0)
		[self SetPlaceholder];
}

-(void)gotoqcategory                    //要在此函数中进行，问题类别的数据请求
{
    if (CMGlobal::TheOne().IsOffline()) {
        [tool ShowError:-1];
        return;
    }
	    
    if(!m_pUpdataDataListerner)
		m_pUpdataDataListerner = new CMQCategoryUpdateDataListener();           //设置回调的类
	
	if(!m_pQcategory)
	{
		m_pQcategory =CMQACategory::GetInstance();
        
	}
       m_pQcategory->SetUserData(BridgeObjectToC(self));
       m_pQcategory->SetListener(m_pUpdataDataListerner);
    
    
    [tool ShowActivityIndicator:tableviewlist at:CGPointMake((UI_IOS_WINDOW_WIDTH-20)/2,80)];        //新增的活动指示器

    if(m_pQcategory->UpdateData())
           [tool DisimissActivityIndicator];
           
	if(!tableviewlist.hidden)
	{
		tableviewlist.hidden = YES;
        [btnqcategory setImage:[UIImage imageNamed:@"downarrow"] forState:UIControlStateNormal];
        
        bg_view.hidden=NO;
        textquestion.hidden=NO;
        words_Num.hidden=NO;
        btnteacher.hidden=NO;
        btn_credit.hidden = NO;
        seg_bgview.hidden=NO;
        btnuploadimage.hidden=NO;
        anonymity_btn.hidden = NO;
        imgView1.hidden=NO;
        
	}
	else
	{
		[textquestion resignFirstResponder];
		tableviewlist.hidden = NO;
        bg_view.hidden=YES;
        textquestion.hidden=YES;
        words_Num.hidden=YES;
        btn_credit.hidden=YES;
        btnteacher.hidden = YES;
        seg_bgview.hidden=YES;
        btnuploadimage.hidden=YES;
        anonymity_btn.hidden = YES;
        
       // imgView1.hidden=YES;
        
        [btnqcategory setImage:[UIImage imageNamed:@"uparrow"] forState:UIControlStateNormal];
    }
    
}




-(void)clearData{
    imgView1.image = nil;
    imgView1.hidden = YES;
}


#pragma mark -
#pragma mark Table view

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	
	//return 6;
    if(!m_pQcategory)
		return 0;
	else 	return m_pQcategory->TopItemCount();
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
#if !__has_feature(obj_arc)
	UITableViewCell *cell =  [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"qcategory"];
    #else
    UITableViewCell *cell =  [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"qcategory"];
    #endif
	CMQACategoryItem qcategoryItem;
	qcategoryItem=*m_pQcategory->GetTopItem(indexPath.row);        //数据源与视图关联的代码
    //NSString *str=[[NSString alloc]init];
    NSString * str=[NSString  stringWithUTF8String:qcategoryItem.sCategoryTitle];
    
	cell.textLabel.text = [NSString stringWithFormat:@"%@",str];
    cell.textLabel.textAlignment = UITextAlignmentCenter;
	
	cell.textLabel.font = [UIFont systemFontOfSize:15.0];
	cell.textLabel.textColor = kTextColorDark;
	cell.textLabel.backgroundColor = [UIColor clearColor];
	
    cell.selectionStyle = UITableViewCellSelectionStyleGray;
	return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return 44;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    bg_view.hidden=NO;
    textquestion.hidden=NO;
    words_Num.hidden=NO;
    btnteacher.hidden=NO;
    btn_credit.hidden =NO;
    seg_bgview.hidden=NO;
    btnuploadimage.hidden=NO;
    imgView1.hidden=NO;
    anonymity_btn.hidden=NO;
    CMQACategoryItem qcategoryItem ;
	qcategoryItem=*m_pQcategory->GetTopItem(indexPath.row);        //数据源与视图关联的代码
  
    self.categoryid=[NSString stringWithUTF8String:qcategoryItem.sID];//问题类别ID
    
    NSString * str=[NSString  stringWithUTF8String:qcategoryItem.sCategoryTitle];
   	
    tableviewlist.hidden=YES;
    
	[btnqcategory setImage:[UIImage imageNamed:@"downarrow"] forState:UIControlStateNormal];
	
    [btnqcategory setTitle:str forState:UIControlStateNormal];
   
	[tableView reloadData];
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
}


-(void)commitquestion
{
    
    //检测有没有选问题分类
    if(self.categoryid == nil || [self.categoryid isEqualToString:@""] /*|| [self.categoryid isEqualToString:@"800"]*/)
    {
        [tool ShowAlert:I(@"请选择问题分类!")];
        return;
    }
    
    //NSString *strQcategory=btnqcategory.titleLabel.text;
    //去除开头和结尾的空格
    NSString *strCommit = [textquestion.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
	if([strCommit length] <= 0 || textquestion.tag == 1)
	{
		[tool ShowAlert:I(@"请输入问题!")];// @"请输入问题."
		return;
	}
    if (isBeyond) {
        [tool ShowAlert:words_Num.text];
        return;
    }
    
	[textquestion endEditing:YES];
    
    if (CMGlobal::TheOne().IsOffline())
    {
        return;
    }
    
	if(!m_pListener)
		m_pListener = new CMQuestionSimpleResultListener();

    //设置回调
    CMFileInfo *file = new CMFileInfo();
    [[GlobalAlertCenter sharedAlertCenter] setType:@"askquestion"];
    file->SetListener([[GlobalAlertCenter sharedAlertCenter] GetCallBack]);
    file->SetUserData(BridgeObjectToC([GlobalAlertCenter sharedAlertCenter]));
    
    CMFileUpload::GetInstance()->SetListener([[GlobalAlertCenter sharedAlertCenter] GetCallBack]);
     CMFileUpload::GetInstance()->SetUserData(BridgeObjectToC([GlobalAlertCenter sharedAlertCenter]));
    
    NSArray *expertsKeyArray = [[self.expertsNameLocDict allKeys] copy];
    NSString *sid =@"";
    
    for(NSString* key in expertsKeyArray)
    {
        if(key != nil)
        {
            NSRange strRange = NSRangeFromString([self.expertsNameLocDict objectForKey:key]);//[[self.expertsNameLocDict objectForKey:key] rangeValue];
            
            NSString* name =[self.expertsDict objectForKey:key];
            
            //检查位置是否有这个名字
            if([[textquestion.text substringWithRange:strRange] isEqualToString:name])
            {
                sid = [sid stringByAppendingString:@","];

                //若有，则添加到字符串中
                sid = [sid stringByAppendingString:key];
                
            }
            else
            {
                //若没有则删除
                [self.expertsDict removeObjectForKey:key];
                
            }
        }
    }
    
    if(![sid isEqualToString:@""])
        sid = [sid substringFromIndex:1];
    
    
    file->AskQuestion([self.categoryid UTF8String] , anonymity_btn.Check, creditnum, [textquestion.text UTF8String], [self.imagepath UTF8String], [sid UTF8String]);
    
    
    
    if (CMFileUpload::GetInstance()->Append(*file) >= 0)
    {
        textquestion.text = @"";
        [self.expertsDict removeAllObjects];
        [self.expertsNameLocDict removeAllObjects];
        [self.navigationController popViewControllerAnimated:YES];
    }
    
    
}

- (void)viewDidUnload
{
	[super viewDidUnload];
}

#pragma mark - UITextViewDelegate

- (BOOL)textViewShouldBeginEditing:(UITextView *)textView
{
    
    if(scoreview)
        scoreview.hidden = YES;
    
    
    NSString *tempStr = textView.text;
    
	if(!popview.hidden)
	{
		popview.hidden = YES;
		[btncredit setImage:[UIImage imageNamed:@"downarrow"] forState:UIControlStateNormal];
	}
	if(textquestion.tag == 1)
	{
		textquestion.text = @"";
		textquestion.tag = 2;
		textquestion.textColor = [UIColor blackColor];
	}
    
    if(DeviceSystemMajorVersion() < 6)
    {
        textView.text =tempStr;

    }
  
    return YES;
}

- (BOOL)textViewShouldEndEditing:(UITextView *)textView{
    
   

    return YES;
}


-(void)updateWordCount:(NSString*)text
{
    
    input_words_num = [text length];
    if (input_words_num <= kTextMaxLength) {
        NSUInteger Remaining_words = kTextMaxLength - input_words_num;
        words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
        isBeyond = NO;
        words_Num.text = [NSString stringWithFormat:@"还能输入%d个字",Remaining_words];
        words_Num.text=[NSString stringWithFormat:I(@"还能输入%d字"),Remaining_words];
    }
    else{
        NSUInteger Beyond_words = input_words_num - kTextMaxLength;
        words_Num.textColor = [UIColor redColor];
        isBeyond = YES;
        words_Num.text = [NSString stringWithFormat:@"超出%d个字",Beyond_words];
        words_Num.text=[NSString stringWithFormat:I(@"超过%d字"),Beyond_words];
    }

}

- (void)textViewDidChange:(UITextView *)textView           //当进行输入时，调用该函数
{
    
    
    self.sTextview=textView.text;
    [self updateWordCount:textView.text];
    
    NSRange selRange =textView.selectedRange;
    
    
    
    
    if(textView.markedTextRange==nil)
    {
//        //关键字变色
        [textquestion setText:textView.text];
        [textquestion setAllKeyWordTextArray:[self.expertsDict allValues] WithFont:[UIFont systemFontOfSize:12] AndColor:[UIColor blueColor]];
    }
    
    textView.selectedRange = selRange;

    self.isShouldChangeText = NO;
    
}

-(void)adjustKeywordPosition:(NSRange)inputRange  replacementText:(NSString *)text
{
    NSArray * keyArray = [[self.expertsNameLocDict allKeys] copy];
    
    //得到文字长度变化，可为正或负
    NSInteger changedLength = text.length-inputRange.length;
    
    for(NSString *str in keyArray)
    {
        
        if([self.expertsNameLocDict objectForKey:str]!=nil)
        {
            //遍历每个关键词的地点
            NSString * val = [self.expertsNameLocDict objectForKey:str];
            NSRange range = NSRangeFromString(val);

            if(inputRange.location > range.location)
            {
                if(NSLocationInRange(inputRange.location, range))
                {
                    
                    //在中间添加,则去除
                    [self.expertsNameLocDict removeObjectForKey:str];
                    [self.expertsDict removeObjectForKey:str];
                    
                }
                else
                {
                    
                    //在后面添加,则不处理
                    
                }
            }
            else
            {
                //先判断是否把整个关键字都覆盖了
                //inputRange.length=0的时候是插入，大于0的时候是覆盖
                if(inputRange.location==range.location && inputRange.length >0)
                {
                    [self.expertsNameLocDict removeObjectForKey:str];
                    [self.expertsDict removeObjectForKey:str];

                }
                else
                {
                    
                    if((inputRange.location+inputRange.length)>range.location)
                    {
                        [self.expertsNameLocDict removeObjectForKey:str];
                        [self.expertsDict removeObjectForKey:str];
                    }
                    else
                    {
                        int tempInt= -changedLength;
                        
                        //在前面添加，位置变化
                        if((int(range.location)<tempInt))
                        {
                            [self.expertsNameLocDict removeObjectForKey:str];
                            [self.expertsDict removeObjectForKey:str];
                        }
                        else
                        {
                            range.location = range.location+changedLength;
                            [self.expertsNameLocDict setObject:NSStringFromRange(range) forKey:str];
                            
                        }

                    }
                    
                    
                }
        
                
            }
            
        }
    }
    
    
}


-(void)SetPlaceholder
{
//	textquestion.textColor = [UIColor lightGrayColor];
//	textquestion.text = @"";// @"提问不超过50个字";
//	textquestion.tag = 1;
}


-(void)getExpertsName:(NSString*)name    Id:(NSString*)Id
{
    //如果 已经@了，不重复显示
    if ([self.expertsDict objectForKey:Id]) {
        return;
    }
    
    //存储被@人的信息
    [self.expertsDict setObject:[@"@" stringByAppendingString:name] forKey:Id];
    
    //得到位置
    NSString* str_temp;
    NSString* str_textquestion=textquestion.text;
    
    NSRange range =NSMakeRange([str_textquestion length],[name length]+1);
    
    //存储name在textview的位置
    [self.expertsNameLocDict setObject:NSStringFromRange(range) forKey:Id];
    
    //处理后将被@人名显示在输入框
    if([textquestion.text hasSuffix:@"@"])
        str_temp=[str_textquestion stringByAppendingString:@""];
    else
        str_temp=[str_textquestion stringByAppendingString:@"@"];
    
    NSString* str_final=[str_temp stringByAppendingString:name];
    
    str_final=[str_final stringByAppendingString:@" "];
    
    
    textquestion.text=str_final;
    
    [textquestion setText:str_final];
    
    //显示颜色
    [textquestion setAllKeyWordTextArray:[self.expertsDict allValues] WithFont:[UIFont systemFontOfSize:12] AndColor:[UIColor blueColor]];
    
    
    //更新字数
    [self updateWordCount:str_final];
    
    
}



- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    self.isShouldChangeText = NO;
    
	if([text isEqualToString:@"\n"])
	{
		[textquestion endEditing:YES];
		if(textquestion.text.length == 0)
			[self SetPlaceholder];
        
        self.isShouldChangeText = NO;

		return NO;
	}
    
    if([text isEqualToString:@"@"])
        [self gotoexpertsControl];
    
    [self adjustKeywordPosition:range  replacementText:text];
    
  
    self.isShouldChangeText = YES;

	return YES;
}

#pragma mark - animation method


- (void)dealloc
{
    
    if(m_pQcategory)
    {
        m_pQcategory->CancelUpdate();
        m_pQcategory->SetUserData(NULL);
        m_pQcategory->SetListener(NULL);
    }
    
    CMRELEASE(textquestion);
	SAFEDELETE(m_pListener);
    CMRELEASE(words_Num);
    
    [imgView1 removeObserver:self forKeyPath:@"image"];
    
    CMRELEASE(imgView1);
    CMRELEASE(bg_view);
    CMRELEASE(btnqcategory);
    CMRELEASE(tableviewlist);
    CMRELEASE(btnuploadimage);
    CMRELEASE(self.expertsDict);
    CMRELEASE(self.expertsNameLocDict);
    CMRELEASE(scoreview);
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"image_delect" object:nil];
#if !__has_feature(obj_arc)
#endif
}
@end
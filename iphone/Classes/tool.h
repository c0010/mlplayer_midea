//
//  tool.h
//  iphone_Learning
//
//  Created by sunjj on 11-4-15.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//



#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>


///////////颜色
#define UIColorMakeRGBA(nRed, nGreen, nBlue, nAlpha) [UIColor colorWithRed:(nRed)/255.0f \
green:(nGreen)/255.0f \
blue:(nBlue)/255.0f \
alpha:nAlpha]
#define UIColorMakeRGB(nRed, nGreen, nBlue) UIColorMakeRGBA(nRed, nGreen, nBlue, 1.0f)
#define UIColorRGB(color) UIColorMakeRGB(color>>16, (color&0x00ff00)>>8,color&0x0000ff)

//前景色，app的主色调
#define kColorForeground         UIColorRGB(0x0092dd)//UIColorRGB(0x1b6db3)
//所有页面view背景色，已在CMViewController里定义
#define kColorBackground         UIColorRGB(0xf9f9f9)//UIColorRGB(0xefefef)
//按钮文字颜色
#define kColorButtonTitle        UIColorRGB(0x0092dd)
//灰色文字颜色
#define kColorGrayText           UIColorRGB(0x858585)



///////////文字
#define kTextColorLight     UIColorRGB(0x888888)
#define kTextColorNormal    UIColorRGB(0x2e2e2e);//[UIColor colorWithRed:136.0f/255.0f green:136.0f/255.0f blue:136.0f/255.0f alpha:1.0f];
#define kTextColorDark      [UIColor colorWithRed:51.0f/255.0f green:51.0f/255.0f blue:51.0f/255.0f alpha:1.0f];//0X333333
#define kTextColorImport    UIColorRGB(0x0092dd)
#define kTextColorReverse
#define kTextColorLink
#define kTextColorTitle
#define kTextSizeBig         18.0   //大字体，标题等
#define kTextSizeBigLess     16.0
#define kTextSizeMid         15.0   //中等字体，列表内容等
#define kTextSizeMidLess     14.0
#define kTextSizeSml         12.0   //小字体，属性等
#define kTextSizeSmlLess     10.0
#define kTextSizeTitle

#define kTextMaxLength    500



///////////尺寸
#define UI_IOS_WINDOW_WIDTH (isPad?1024:320)
#define UI_IOS_WINDOW_HEIGHT (isPad?768:([[UIScreen mainScreen] bounds].size.height))


#define UI_IOS_STATUSBAR_HEIGHT CGRectGetHeight([[UIApplication sharedApplication] statusBarFrame])//状态栏高度
#define UI_IOS_NAVIBAR_HEIGHT self.navibarHeight//导航栏高度
#define UI_IOS_TABBAR_HEIGHT self.tabbarHeight//底部tab栏高度
#define UI_IOS_TAGBAR_HEIGHT self.tagbarHeight//顶部标签栏高度

#define UI_IOS_VC_HEIGHT (UI_IOS_WINDOW_HEIGHT - UI_IOS_NAVIBAR_HEIGHT - UI_IOS_STATUSBAR_HEIGHT - UI_IOS_TABBAR_HEIGHT - UI_IOS_TAGBAR_HEIGHT) //界面可自定义区域高度


#define kMarginTop				20.0
#define kMarginLeftRight		20.0

#define kImgUploadSizeMax  1200 //上传图片最大边尺寸

#define kBarItemWidth   40  //baritem宽度
#define kBarItemHeight  44  //baritem高度

#define LABEL_WIDTH    280       //问答lbquestion宽度
#define Course_News_LeftImageView_Height     72



///////////缩写
#define AppVersion      [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]//版本字符串
#define AppBuildVersion [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]//int用于比较版本高低
#define CurrentDeviceIosVersion [[[UIDevice currentDevice] systemVersion] floatValue] //获取当前系统版本号，不直接使用
//获取MLPlayerAppDelegate 操作句柄
#define AppDelegate ((MLPlayerAppDelegate *)[UIApplication sharedApplication].delegate)
//获取CMMainControl 操作句柄
#define  CMMainControlHandler     ((CMMainControl*)self.tabBarController)

//将char* 转为NSString
#define NSStringFrom(string) [NSString stringWithUTF8String:string.c_str()]

#define __iOS8  ((CurrentDeviceIosVersion >= 8.0) ? YES : NO)

#define __iOS7  ((CurrentDeviceIosVersion >= 7.0) ? YES : NO)

#define __iOS6  ((CurrentDeviceIosVersion >= 6.0) ? YES : NO)

#define __iOS5  ((CurrentDeviceIosVersion >= 5.0 && CurrentDeviceIosVersion < 6.0) ? YES : NO)

#define isPad (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)

#define __iPhone5 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136),[[UIScreen mainScreen] currentMode].size) : NO)

#define __iPhone4_4S ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 960),[[UIScreen mainScreen] currentMode].size) : NO)

///////////常量
#define ModuleCourse         @"course"       //课程
#define ModuleNews			@"news"          //资讯
#define ModuleKB             @"kb"		     //知识
#define ModuleExam			@"exam"		     //测验
#define ModuleSurvey         @"survey"	     //调研
#define ModuleExercise		@"exercise"	     //练习
#define ModuleInteract       @"interact"	 //互动
#define ModuleApp	        @"app"	         //应用

#define kUDOpenPush   @"OpenPush"       //判断是否推送，1:是，0不是
#define kUDPushType   @"PushType"       //推送类型
#define kUDPushID     @"PushID"         //推送id

//2000协议未完成通知界面更新(服务器主动推送通知)
#define  CM_NotificationCenter_ItemCategory        @"NotificationCenter_Item_Category"

//2000协议未完成通知界面更新
#define  CM_NotificationCenter_ReloadView        @"NotificationCenter_Myinfo_Application"

//2001协议未完成通知界面更新
#define  CM_NotificationCenter_ReloadCategory    @"NotificationCenter_Category"

//左滑动栏目结束通知
#define  LeftVcFinishMove      @"LeftVcFinishMove"

//获取个心信息成功
#define  CM_NotificationCenter_HeadImageUpdate   @"NotificationCenter_HeadImageUpdate"

//头像上传成功
#define  CM_NotificationCenter_HeadImageUpload   @"NotificationCenter_HeadImageUpload"



///////////宏
# if ! __has_feature(objc_arc)
#define CMRELEASE(x) if (x != nil) {[x release];}
# else
#define CMRELEASE(__x)
# endif

#ifndef __OPTIMIZE__

#define NSLog(...) NSLog(__VA_ARGS__)

#else

#define NSLog(...) {}
#endif

#define WEAKSELF     WEAKOBJ(self) //typeof(self) __weak wself = self;
#define STRONGSELF   STRONGOBJ(self,)

//增加非ARC下block的wself, sself的宏定义
// ！注意，对于非ARC情况下，WEAKSELF, STRONGSELF的宏定义简化,只适合一次使用的block.
// 对于会被多次使用的block，第二次及之后取wself时已经是nil,会有问题,不能用这里的宏定义。
// 对于多次使用的block的情况要自行分析对象关系，自写代码。
# if ! __has_feature(objc_arc)
#define WEAKOBJ(obj) \
typeof(obj) __block w##obj = obj;
#define STRONGOBJ(obj,ret) \
typeof(w##obj) s##obj = nil; \
if (w##obj != nil ){ \
s##obj = [[w##obj retain] autorelease]; \
w##obj = nil; \
} \
if (!s##obj) { \
CM_ERR("strong "#obj" failed"); \
return ret; \
}
# else
#define WEAKOBJ(obj) \
typeof(obj) __weak w##obj = obj;
#define STRONGOBJ(obj,ret) \
typeof(w##obj) __strong s##obj = w##obj; \
if (!s##obj) { \
CM_ERR("strong "#obj" failed"); \
return ret; \
}
# endif



#define BridgeObjectToC(object) ((__bridge void *) object)
#define BridgeObjectToOC(object) ((__bridge id) object)

#define I(s)   NSLocalizedString(s, @"")


//需要添加引导的页面
typedef enum{
    NeedGuideViewMoviePlayer=0,
    NeedGuideViewExam,
    NeedGuideViewSearch,
    NeedGuideViewComment,
    NeedGuideViewCourse,
    NeedGuideViewLearn,
    NeedGuideViewPerson,
    NeedGuideViewPush,
} NeedGuideView;


typedef enum _PlaceholderInfo{
    Placeholder_NoDataText,         /* “暂无数据”             */
    Placeholder_NoSurveyText,
} PlaceholderInfo;


typedef enum _PlaceholderActionType{
    PlaceholderActionClickRefresh        //点击刷新
} PlaceholderActionType;

//对齐方式
typedef enum{
    ALIGNMENTLEFT=0,  // Visually left aligned
    ALIGNMENTCENTER,  // Visually centered
    ALIGNMENTRIGHT,   // Visually right aligned
} ALIGNMENT;


//换行方式
typedef enum{
    TEXTBREAKMODEWORD=0, // Wrap at word boundaries, default
    TEXTBREAKMODECHAR,   // Wrap at character boundaries
    TEXTBREAKMODECLIP,   // Simply clip
    TEXTBREAKMODETRUNCATINGHEAD,   // Truncate at head of line: "...wxyz"
    TEXTBREAKMODETRUNCATINGTAIL,   // Truncate at tail of line: "abcd..."
    TEXTBREAKMODETRUNCATINGMIDDLE, // Truncate middle of line:  "ab...yz"
} TEXTBREAKMODE;





@interface tool : NSObject {
    

}

/**
 *  生产tableview的背景view，生成的view.orgin为（0，0）
 *
 *  @param info 占位符类型：现在有nodata
 *
 *  @return 返回
 */

+(UIView* )generatePlaceholderView: (PlaceholderInfo)info;

//生产tableview的背景view，生成的view.orgin为（0，0）


/**
 *  生产tableview的背景view，生成的view.center为targetView的偏上的中心点

 *
 *  @param info       占位符类型：现在有nodata
 *  @param targetView
 *
 *  @return
 */

+(UIView *)generatePlaceholderView:(PlaceholderInfo)info on:(UIView*)targetView;



/**
 *  生产tableview的背景view，生成的view.orgin为（0，0）
 *
 *  @param actiontype 占位符类型：点击屏幕刷新
 *  @param target 持有对象
 *  @param action 响应事件
 *  @param targetView 目标视图
 *
 *  @return 返回
 */

+(void)addGeneratePlaceholderView: (PlaceholderActionType)actiontype
                            target:(id)target
                            action:(SEL) action
                                on:(UIView*)targetView;
//不会阻塞

//展示转圈圈


+(void)ShowActivityIndicator:(UIView*)view at:(CGPoint)pos;
+(void)ShowActivityIndicator:(UIView*)view;
+(void)DisimissActivityIndicator;

+(void)ShowAlert:(NSString*) text;
+(void)ShowError:(int)Result;


//会阻塞
+(void)Wait;
+(void)CancelWait;
+(BOOL)GetIsBack;
+(void)SetIsBack:(BOOL)istrue;
+(void)willPresentAlertView:(UIAlertView *)alertView;

//是否有点击we工具
+(BOOL)hasClickedWE;
+(void)clickedWE;
+(void)revertWE;

//引导页
+(NSString *)NeedGuideViewToString:(NeedGuideView)name;
+(void)dismissGuide:(id)sender event:(id)event;
+(UIView *)generateGuideView:(NeedGuideView)name;
+(void)SetDisplayed:(NeedGuideView )name;
+(BOOL)isFirstTimeToDisplay:(NeedGuideView)name;

//文字对齐方式
+ (NSInteger)TextAlignment:(ALIGNMENT)alignment;

//文字换行方式
+ (NSInteger)TextBreakMode:(TEXTBREAKMODE)mode;

//提交内容不能及时返回时页面添加等待状态
+ (void)ShowBeforeBack;

//返回时去掉等待
+ (void)DismissAtEnd;

//网络是否可用
+ (bool)isExistNetwork;

//是否wifi环境
+ (BOOL)isExistWifi;
@end


//@interface WaitingView : UIView
//{
//    
//}
//
//+ (void)WaitingStart;
//
//+ (void)WaitingStop;
//
//+ (void)WaitingFail;
//
//@end


/** @Deprecated
 * 废弃MessageBox这个类，统一用CMAlertView代替
 * 暂时只是注释掉与MessageBox相关代码，待长时间考证没问题后，再删掉相关代码
 */
/***********************************
#define MODE_OK 0
#define MODE_OKCANCEL 1
#define MODE_YESNO 3
@interface MessageBox : NSObject {
	int result;
    bool isUseBlock;
    void (^_confirmBlock)();
    void (^_cancelBlock)();
}

@property(copy,nonatomic) void (^_confirmBlock)();
@property(copy,nonatomic) void (^_cancelBlock)();


+(void)DoModalWithTitle:(NSString*)title message:(NSString*)message mode:(int)mode  confirm:(void (^)())myconfirmBlock cancel:(void (^)())mycancelBlock;
+(BOOL)DoModalWithTitle:(NSString*)title message:(NSString*)message mode:(int)mode; //Deprecated
+(void)dimissAlertView;
@end
*******************************************/

//@protocol CMListMoreDelegate
//-(void)selectseg:(NSString*)sid index:(NSInteger)index;
//
//@end

@protocol CMExamControlDelegate
-(void)willRershTableListView;

@end

//@protocol CMClearViewDelegate
//-(void)closeView;
//-(void)hiddeView:(CGRect)f;
//-(void)disbleView:(CGRect)f;
//-(void)refreshView;
//@end

//@protocol CMCustom2ControlDelegate
//
//-(void)closeBackGround:(id)state;
//
//@end


//@protocol IMLoginListenerDelegate
//
//-(void) OnLoginResult : (int)Result HasNewVersion:(BOOL)HasNewVersion;
//-(void) display;
//
//@end





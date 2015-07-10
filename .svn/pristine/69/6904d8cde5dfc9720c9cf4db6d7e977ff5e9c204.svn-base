//
//  CMClassInfoControl.h
//  MLPlayer
//
//  Created by sunjj on 11-9-20.
//  Copyright 2011 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMTableViewCell.h"
#import "CMTableView.h"
#import "CMPlayerControl.h"
#import "CMDownLoadControl.h"
#import "CMInfoCommentControl.h"
#include "cmcategory.h"

#import "cmcourseinfo.h"
#import "CMBrowser.h"
#import "cmcommon.h"
#import "cmfavorites.h"
#import "cmcoursedownload.h"
#include "tool.h"
#import "CMNewsInfoControl.h"
#import "CMImage.h"
#import "CMTextView.h"
#import "ComplexButton.h"
#import "CMAlertView.h"
#import "CMClassInfoCell.h"
#import "CMClassIntroductionView.h"
#import "CMCommentView.h"
#import "CMClassTopView.h"

#import "QCSlideSwitchView.h"

class CMClassInfoUpdateDataListener;
class CMClassInfoRatingListener;
class CMClassInfoGetImageListener;


@interface CMClassInfoControl : UIView <UIActionSheetDelegate,UITableViewDelegate,UITableViewDataSource,QCSlideSwitchViewDelegate,QCSlideSwitchViewDataSource>{
	UIScrollView * scrollView;
    UIView* downPartView;
    
	
	CMClassInfoUpdateDataListener *m_pUpdateDataListener;
	CMClassInfoRatingListener *m_pRatingListener;
	
	CMClassInfoGetImageListener *m_pGetImageListener;
	CMWebImage * m_pWebImage;

	UIImageView* sImage;
	UIImageView* viewimage;
	UIImageView* likeimage;
	UIButton* btnplay;
	UILabel* lblview;
	UILabel* lbllike;
	UILabel* lblcredittl;
	UILabel* lblcredit;
	UIImageView* txtbg;
	UILabel* txtcontent;
	UILabel* lbltime;
    UIButton* btnMark;
    
    UILabel* lblviewtl;
    
    UIImageView * _infoBack;
    UIButton *_infoBackBtn;
    
    
	UIImageView*  lblsep;
    
    UILabel * _lbclassName;
    
    
    NSString * _courseName;
    
    UIImageView *_arrowHead;
    
    UIButton *_infoBtn;
	
	ComplexButton* btnlike;
    
    BOOL courseDisplayed;
    
    CMClassInfoCell *classInfoCell;
    
    NSInteger nindex;
    
    NSString* setid;
    
    NSInteger nModel;
    
    
    CMTableView *TableViewList;
    CMClassIntroductionView *introView;
    CMCommentView *commentView;
    CMClassTopView *topView;
    
    QCSlideSwitchView *slideSwitchView;
    
    
    @public
    CMCourseInfo *m_CourseInfo;
    
    TClassItem *item;
}

@property(nonatomic,strong) IBOutlet  UITableView* TableViewList;
@property(nonatomic,strong) IBOutlet  UIImageView* sImage;

@property(nonatomic,strong) IBOutlet  UILabel* lblview;
@property(nonatomic,strong) UIButton  *btnMark;
@property(nonatomic,strong) UILabel   *txtcontent;

@property(nonatomic,strong) IBOutlet  UILabel* lbllike;

@property(nonatomic,strong) IBOutlet  UILabel* lblcredittl;

@property(nonatomic,strong) IBOutlet  UILabel* lblcredit;

@property(nonatomic,copy)   NSString* setid;

@property(nonatomic,assign) NSInteger nModel;

@property(nonatomic,strong) IBOutlet  UILabel* lblviewtl;

@property(nonatomic,strong) IBOutlet  ComplexButton* btnlike;

@property(nonatomic,strong) IBOutlet  UILabel *lbclassName;

@property (nonatomic,copy)  NSString *courseName;
@property(nonatomic,strong) UIImageView *infoBack;
@property(nonatomic,strong) UIImageView *arrowHead;
@property(nonatomic,strong) UIButton *infoBtn;
@property(nonatomic,strong) UIButton *infoBackBtn;
@property(nonatomic,strong) IBOutlet CMClassInfoCell *classInfoCell;
@property(nonatomic,assign)  NSInteger nindex;

-(CMCourseInfo*)getCourseInfo;

-(void)setInfo:(TBrowserItem&)item;
-(void)loadTableList;
-(void)courseInit;      // 此方法初始化视图
- (void)courseDataFillIn;   //此方法填充数据
-(void)setViewsFrame;
-(BOOL)GetCourseList;
-(void)updateview;
-(BOOL)gotoFavorite;
-(void)gotoDown;

-(void)refreshCourseInfo;//刷新上部分课程UI的数据

-(void)gotoComment;
-(UILabel*)GetLabel:(NSString*)title textcolor: (UIColor*)textcolor fontsize:(int)size;

-(void)popWhenNoNermission;

@end

class CMClassInfoUpdateDataListener: public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
	{
		NSLog(@"CMClassInfoBrowserListener OnUpdateDataProgress");
	}
	
    virtual void OnUpdateDataFinish(void* UserData, int Result) 
	{
		NSLog(@"CMClassInfoBrowserListener OnUpdateDataFinish Result =%d",Result);
		
		CMClassInfoControl* classInfoControl = (__bridge CMClassInfoControl*)UserData;
		
        [tool DisimissActivityIndicator];
       
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
            [classInfoControl courseDataFillIn];
			[classInfoControl loadTableList];
            
            [[NSNotificationCenter defaultCenter] postNotificationName:@"refreshTabarStatus" object:[NSNumber numberWithInt:Result]];
            
		}
        else if(Result == TResult::ENoPowerCourse){
            CMAlertView *alert = [[CMAlertView alloc] initWithTitle:I(@"提示") message:I(@"该课程已经在后台进行下架") cancelButtonTitle:nil otherButtonTitles:I(@"确定") completionBlock:^(NSUInteger buttonIndex, CMAlertView *alertView) {
                if (buttonIndex == BUTTON_CONFIRM_TAG){
                    [classInfoControl popWhenNoNermission];
                }
            }] ;
            [alert setDisabledOutSide:YES];
            [alert show];
        }
        else {
			[tool ShowError:Result];
		}
	}	
};


class CMClassInfoGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		NSLog(@"CMLearnGetImageListener OnFinish result=%d",Result);
		
		CMClassInfoControl* classInfoControl = (__bridge CMClassInfoControl*)UserData;
		
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
			
            [classInfoControl refreshCourseInfo];

		}else {
		}
	}
};

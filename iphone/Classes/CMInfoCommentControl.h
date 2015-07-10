//
//  CMClassCommentControl.h
//  MLPlayer
// 评论列表
//  Created by sunjj on 11-10-13.
//  Copyright 2011 w. All rights reserved.
//


#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMTableViewCell.h"
#import "CMCommentTableViewCell.h"
#import "CMTableView.h"
#import "cmcomment.h"
#import "cmcommon.h"
#import "cmwebimage.h"
#import "CMImage.h"
#import "FLXFluidTextView.h"

class CMCommentUpdateDataListener;
class CMInfoCommentGetImageListener;
class CMCommentRatingListener;
class CMEditCommentSimpleResultListener;
@interface CMInfoCommentControl : CMViewController <UITableViewDelegate,UITableViewDataSource,UITextFieldDelegate,UITextViewDelegate,UIActionSheetDelegate,UITextViewDelegate>
{

    NSString* classID;
    NSString* coursewareID;
    
    
	CMTableView* TableViewList;
	
	CGFloat width;
	CGFloat height;
	
	UIActivityIndicatorView *activeView;
	UIActivityIndicatorView* dwActiveView;
	
	
	BOOL isComment;
	UIButton* btnMore;
	
	UIButton* btncomment;
	UITextField* txtcomment;
	UIBarButtonItem* BarButtontxtComment;
	UIBarButtonItem* BarButtonbtnComment;
	UIToolbar *toolbar;
	UIView * layView;
	
	CMCommentUpdateDataListener * m_pUpdateDataListener;
	CMCommentRatingListener* m_pRatingListener;
    CMEditCommentSimpleResultListener *m_pListener;
	
	CMComment * m_pComment;
    CMComment * m_pEditComment;
	char m_courseid[64];
	
	CMInfoCommentGetImageListener *m_pGetImageListener;
	CMWebImage * m_pWebImage;
    
    TBrowserItem *m_CourseInfo;

	
	NSString* m_type;
	
	UIView* bgview;
	UIButton* popview;
    
    NSInteger selectedIndex;
    //底下输入条
    UIView* inputView;
    FLXFluidTextView* inputField;
    UIButton* backBtn;
	
    CGFloat keyBoardHieght;
}

@property(nonatomic,copy)   NSString* classID;
@property(nonatomic,copy)   NSString* coursewareID;

@property(nonatomic,assign)   bool cannotComment;//不能评论

-(void)setCourseID:(const char*)courseid type:(NSString*)type;
-(void)LoadTableList;
-(void)LoadComment;
-(BOOL)hiddenkeyword;
-(void)startcomment:(int)type;
-(void) AutoFresh;
-(void)setBrowserItem:(TBrowserItem&)item;
-(void)upDateCourseItemComment;

@end


//更新数据监听器接口
class CMCommentUpdateDataListener : public IMUpdateDataListener
{
    void OnUpdateDataProgress(void* UserData, int nPercent)
	{
		NSLog(@"CMCommentUpdateDataListener OnUpdateDataProgress Result");
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{	
		NSLog(@"CMCommentUpdateDataListener OnUpdateDataFinish Result= %d",Result);
		
		CMInfoCommentControl * infoCommentControl= (__bridge CMInfoCommentControl*)UserData;
				
        [infoCommentControl LoadTableList];

		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
			
		}
        else if (Result == TResult::ENotSupportOffline)
        {
            
        }
        else {
			[tool ShowError:Result];
		}
	}	
};

class CMCommentRatingListener : public IMRatingListener
{
	void OnRating(void* UserData, int nNewRating, int Result)
	{
		CMInfoCommentControl * infoCommentControl= (__bridge CMInfoCommentControl*)UserData;
		[tool CancelWait];
		
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
			[infoCommentControl LoadComment];			
		}else {
			[tool ShowAlert:I(@"只能喜欢一次")];
		}
	}
};
class CMInfoCommentGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		NSLog(@"CMClassCommentGetImageListener OnFinish Result=%d",Result);
		
		CMInfoCommentControl* infoCommentControl = (__bridge CMInfoCommentControl*)UserData;
		
		if (Result == TResult::ESuccess || Result == TResult::ENothing) {
			
			[infoCommentControl LoadTableList];
		}else {
			//[tool ShowError:Result];
		}
	}
};
class CMEditCommentSimpleResultListener: public IMSimpleResultListener
{
    void OnRequestFinish(void* UserData, int Result)
	{
		CMInfoCommentControl* comment = (__bridge CMInfoCommentControl*)UserData;
		[tool DisimissActivityIndicator];
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
            [comment upDateCourseItemComment];

            [comment AutoFresh];
        }
        else if (Result == TResult::ENotSupportOffline)
        {
            NSString *str = nil;
            str = [NSString stringWithFormat:I(@"网络不给力")];
			[tool ShowAlert:str];
        }
		else
		{
            NSString *str = nil;
            str=  [NSString stringWithFormat:I(@"提交%@失败"),I(@"评论")];
           
			[tool ShowAlert:str];
		}
	}
};

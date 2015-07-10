//
//  cmitemcontroller.h
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CMRefreshMoreView.h"
#import "CMAnswerTableViewCell.h"
#include "cmquestiondetail.h"
#import "cmcommon.h"
#include "cmqalist.h"
#include "cmwebimage.h"
#import "CMViewController.h"
#import "AKButton.h"
#import "SDWebImage/SDWebImageDownloader.h"
#import "SDWebImage/SDWebImageManager.h"
#import "SDWebImage/UIImageView+WebCache.h"
#import "GlobalAlertCenter.h"
#import "cmquestionupload.h"
#import "tool.h"
#import "CMQuestionTableViewCell.h"
#import "cmupload.h"
#import "CheckBoxButton.h"

class CMAnswerUpdateDataListener;
class CMAnswerDetailRatingListener;
class CMAnswerDetailSimpleResultListener;
class CMQuestionRatingListener;

@interface CMQuestionDetailView : CMRefreshMoreView <UIActionSheetDelegate,AKButtonDelegate,UITextViewDelegate,UIScrollViewDelegate,UINavigationControllerDelegate,UIImagePickerControllerDelegate,SDWebImageManagerDelegate>
{
	CMWebImage * m_pWebImage;
	CMQuestionDetail* m_pQuestionDetail;
	CMQuestionRatingListener* m_pQuestionRatingListener;
    CMAnswerUpdateDataListener* m_pAnswerUpdateListener;
    CMAnswerDetailSimpleResultListener* m_pAnswerBestUpdateListener;
    CMAnswerDetailRatingListener* m_pOneAnswerRatingListener;
	
	UITableViewCell* questioncell;
	TQAItem curqaItem;
	UIButton* attentionbtn;
    AKButton *akbtn;
    UITextView *textanswer;//输入框
    UIView *bg_view;

    UIButton *photo_btn;
    UIButton *picture_btn;
    CheckBoxButton *anonymity_btn;

    UIImageView *imageView1;  //  装载分享图片
    UILabel* words_Num;
    NSUInteger input_words_num;
    BOOL isBeyond;//字数判断
    
    UIView *shadeView;
    BOOL isOpen;//判断回答框是否打开
    BOOL isHiddenBestbtn; //是否已设置最佳答案
    BOOL isEnableLike;//添加like后 likebtn设置enable为NO
    
    CGPoint point; //获取当前光标坐标再tableviewlist坐标系里的坐标
    CGPoint point_view; //获取当前光标再self.view坐标系里的坐标
    
    
    BOOL needrefresh;
    
    TAnswerItem answeritem;
    NSString* imagepath;
    CMQuestionUpload* m_pQaUpload;
    
@public
    CMQAList* m_pQalist;
}

@property(nonatomic, copy) NSString* imagepath;
@property (nonatomic, strong) UIImageView *imageView1;
@property (nonatomic, strong) UIButton *photo_btn;
@property (nonatomic, strong) UIButton *picture_btn;
@property(nonatomic,strong)  UITextView *textanswer;
@property(nonatomic,assign)  BOOL needrefresh;
@property(nonatomic,assign)  BOOL isOpen;
@property(nonatomic,strong)NSString* questionid;
//@property(nonatomic)CMQuestionDetail* questiondetail;
-(id)initWithFrame:(CGRect)frame;
-(void)RefreshList;
-(BOOL)RefreshMore;
-(CGFloat)GetCellHeight:(TAnswerItem&)answerItem width:(int)width shareImage:(CMWebImage *)shareimage;
-(CGFloat)GetHeight:(int)width text:(NSString*)stxt;
-(void)LoadData;
-(void)SetWegImage:(CMWebImage*)webimage;

-(void)setQuestionDetail:(CMQuestionDetail*)pQuestionDetail;
-(void)SetCellInfo:(CMAnswerTableViewCell*)cell item:(TAnswerItem&)answerItem shareImage:(CMWebImage*)shareImage;
-(void)SetQuestionItem:(TQAItem&)item;
-(int) AttentionStatus;
-(void)AttentionSuccess;
-(void)onAttention;
-(void)Refresh;
-(void)setAnswer:(BOOL)show;

-(void)showAttentionErr;
-(void)txtanswerResignFirstResponder;

@end

class CMQuestionRatingListener: public IMRatingListener
{
    void OnRating(void* UserData, int nNewRating, int Result)
	{
		CMQuestionDetailView* question = (__bridge CMQuestionDetailView*)UserData;
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
			[question AttentionSuccess];
			[question GetBrowserList];
		}
		else if (Result==TResult::ENotSupportOffline) {
            [tool ShowAlert:[NSString stringWithFormat:I(@"网络不给力"),@""]];
        }
        else
            [question showAttentionErr];
	}
};

class CMAnswerDetailSimpleResultListener : public IMSimpleResultListener
{
	void OnRequestFinish(void* UserData, int Result)
	{
        CMQuestionDetailView * AnswerController=(__bridge CMQuestionDetailView*)UserData;
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
			AnswerController.needrefresh = true;
            [AnswerController.tableviewlist reloadData];
			[tool ShowAlert:I(@"设置最佳答案成功")];
		}
		else if(Result == TResult::EDuplicaterating)
			[tool ShowAlert:I(@"已设置")];
		else
            if (Result==TResult::ENotSupportOffline) {
                
                NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
                
                [tool ShowAlert:str];
            }else
                [tool ShowAlert:I(@"设置最佳答案失败")];
	}
};


class CMAnswerDetailRatingListener: public IMRatingListener
{
    void OnRating(void* UserData, int nNewRating, int Result)
	{
        
       // CMQuestionDetailView * AnswerController=(__bridge CMQuestionDetailView*)UserData;
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
           // [AnswerController.tableviewlist reloadData];
		}
        else{
                ;
        }
	}
};



class CMAnswerUpdateDataListener: public IMUpdateDataListener
{
    virtual void OnUpdateDataProgress(void* UserData, int nPercent)
    {
    }
    
    virtual void OnUpdateDataFinish(void* UserData, int Result)
    {
        CMQuestionDetailView* answer = (__bridge CMQuestionDetailView*)UserData;
        [tool DisimissActivityIndicator];
        
        if (Result == TResult::ESuccess || Result == TResult::ENothing) {
            [answer GetBrowserList];
        }
        else if (Result == TResult::ENotSupportOffline)
        {
            [answer GetBrowserList];
        }
        else
        {
            [tool ShowError:Result];
        }
        
    }	
};



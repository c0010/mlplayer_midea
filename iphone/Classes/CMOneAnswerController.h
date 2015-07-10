//
//  CMViewController.h
//  OCplusplus
//
//  Created by Tim on 13-1-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
 #include "cmcommon.h"
#include "cmwebimage.h"
#include "cmquestiondetail.h"
#include "CMViewController.h"

@class CMAnswerTableViewCell;
class CMOneAnswerGetImageListener;
class CMOneAnswerRatingListener;
class CMOneAnswerSimpleResultListener;
@interface CMOneAnswerController : CMViewController{

	UIView* headview;
	UIView* sepview;
	CMAnswerTableViewCell* answerview;
	CMOneAnswerGetImageListener *m_pGetImageListener;
	CMWebImage * m_pWebImage;
	TAnswerItem answeritem;
	
	CMQuestionDetail* m_pQuestionDetail;
	CMOneAnswerRatingListener* m_pOneAnswerRatingListener;
	CMOneAnswerSimpleResultListener* m_pOneAnswerSimpleResultListener;
}
@property(nonatomic,assign)BOOL needrefresh;
@property(nonatomic,assign)BOOL bestanswer;
@property(nonatomic,strong)NSString* questionid;
@property(nonatomic,strong)NSString* questionusername;
-(void)refreshimage;
-(void)updateView;
-(UILabel*)GetLabel:(NSString*)title textcolor: (UIColor*)textcolor fontsize:(int)size;
-(void)setitem:(TAnswerItem&)item;
-(void)createTabbar;
-(void)gotobest;
-(void)gotolike;
@end

class CMOneAnswerGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		
		CMOneAnswerController* OneAnswerController = (__bridge CMOneAnswerController*)UserData;
		
		if (Result == TResult::ESuccess || Result == TResult::ENothing)
		{
			[OneAnswerController refreshimage];
		}
		else
		{
			
		}
	}
};
class CMOneAnswerSimpleResultListener : public IMSimpleResultListener
{
	void OnRequestFinish(void* UserData, int Result)
	{
		CMOneAnswerController* OneAnswerController = (__bridge CMOneAnswerController*)UserData;
		[tool CancelWait];
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
			OneAnswerController.needrefresh = true;
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
class CMOneAnswerRatingListener: public IMRatingListener
{
    void OnRating(void* UserData, int nNewRating, int Result)
	{
		CMOneAnswerController* OneAnswerController = (__bridge CMOneAnswerController*)UserData;
		[tool CancelWait];
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
			OneAnswerController.needrefresh = true;
			[tool ShowAlert:I(@"喜欢成功")];
		}
		else if(Result == TResult::EDuplicaterating)
			[tool ShowAlert:I(@"已喜欢")];
		else
            if (Result==TResult::ENotSupportOffline) {
                
                NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
                
                [tool ShowAlert:str];
            }else
                [tool ShowAlert:I(@"喜欢失败")];
	}
};

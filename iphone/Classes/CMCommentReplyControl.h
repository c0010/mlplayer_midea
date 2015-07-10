#import <UIKit/UIKit.h>
#import "CMViewController.h"
#include "cmcomment.h"
#import "CheckBoxButton.h"
#include "cmwebimage.h"
#import "CMImage.h"
#import "CMReplyTableViewCell.h"
#import "FLXFluidTextView.h"

class CMRepalyUpdateListener;
class CMCommentReplySimpleResultListener;
class CMCommentGetImageListener;
@interface CMCommentReplyControl: CMViewController <UITextViewDelegate,UITableViewDataSource,UITableViewDelegate,UITextFieldDelegate>
{
    
    NSString* classid;
    NSString* coursewareid;
    
    
    UIButton* btnMore;
    UIActivityIndicatorView *activityView;

	BOOL  m_bHasMore;
    
	UITextView *textcomment;
	CheckBoxButton* syncbtn;
	
    NSInteger commentIndex;
	NSString* sflag; //course或者news
	NSString* sid; //课程或资讯id
	NSString* sreplyid;//回复评论id
	NSInteger type; //1回复，2发表
    UITableView* replyList;
    
    UIView* headView;
    UIView* inputView;
    FLXFluidTextView* inputField;
    
    CGFloat keyBoardHieght;
    
    
    UIButton* backBtn;
	
    UILabel* lblcount;
    UILabel* lblLikeCount;
    UIButton* btnLike;
    CMWebImage* m_pWebImage;
    
    CMRepalyUpdateListener* m_pUpdateListener;
    
    CMCommentGetImageListener* m_pImageListener;

	CMCommentReplySimpleResultListener *m_pListener;
    
    
    
@public
    CMRepalycomment* m_pReply;
    TClassItem *m_CourseInfo;
	CMComment* m_pComment;
}
@property(nonatomic,copy)NSString* classid;
@property(nonatomic,copy)NSString* coursewareid;

@property(nonatomic,copy)NSString* sflag;
@property(nonatomic,copy)NSString* sid;
@property(nonatomic,copy)NSString* sreplyid;
@property(nonatomic,assign)NSInteger type;
@property(nonatomic,strong)UITableView* replyList;
@property(nonatomic,strong) UIView* headView;
@property(nonatomic,assign)     NSInteger commentIndex;
@property(nonatomic,assign) BOOL m_bHasMore;
@property(nonatomic,assign)   bool cannotComment;//不能评论

-(void)refreshCommentList;
-(void)SetPlaceholder;
-(void)updateData;
-(void)upDateCourseItemComment;
@end


class CMRepalyUpdateListener : public IMUpdateDataListener
{
   void OnUpdateDataFinish(void* UserData, int Result)
    {
		CMCommentReplyControl* replycontrol = (__bridge CMCommentReplyControl*)UserData;
        [tool DisimissActivityIndicator];
        
        if(replycontrol && replycontrol->m_pReply)
        {
            if(replycontrol->m_pReply->IsEnd())
                replycontrol.m_bHasMore=NO;
            else
                replycontrol.m_bHasMore=YES;
            
        }
        
        if(Result == TResult::ESuccess|| Result == TResult::ENothing)
        {
            [replycontrol updateData];
            
        }
    }
    
    void OnUpdateDataProgress(void* UserData, int nPercent)
    {
        
        return;
    }
    
};


class CMCommentGetImageListener:public IMGetImageListener
{
	void OnFinish(void* UserData, int Result, int nID)
	{
		CMCommentReplyControl* replycontrol = (__bridge CMCommentReplyControl*)UserData;
		
		if (Result == TResult::ESuccess || Result == TResult::ENothing)
		{
            [replycontrol.replyList reloadData];
		}else {
		}
	}
};

class CMCommentReplySimpleResultListener: public IMSimpleResultListener
{
    void OnRequestFinish(void* UserData, int Result)
	{
		CMCommentReplyControl* replycontrol = (__bridge CMCommentReplyControl*)UserData;
        
        [tool DisimissActivityIndicator];

		if(Result == TResult::ESuccess || Result == TResult::ENothing)
        {
            [replycontrol upDateCourseItemComment];
            [replycontrol refreshCommentList];
          
		}
        else if (Result == TResult::ENotSupportOffline)
        {
            NSString *str = nil;
            if (replycontrol.type == 2)
            {
                str = [NSString stringWithFormat:I(@"网络不给力")];
            }
            else
            {
                str = [NSString stringWithFormat:I(@"网络不给力")];
            }
			[tool ShowAlert:str];
        }
		else
		{
            NSString *str = nil;
            if (replycontrol.type == 2)
            {
                str = [NSString stringWithFormat:I(@"提交%@失败"),I(@"回复")];
            }
            else
            {
                str = [NSString stringWithFormat:I(@"提交%@失败"),I(@"回复")];
            }
			[tool ShowAlert:str];
		}
	}	
};
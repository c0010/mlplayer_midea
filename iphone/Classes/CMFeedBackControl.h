#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "cmfeedback.h"


@class CMViewControl;
class CMFeedbackListener;


@interface CMFeedbackControl : CMViewController <UITextViewDelegate,UITableViewDelegate,UITableViewDataSource>
{
	UITableView *FeedbackTableView;

	UITextView *textFieldFeedback;
	UIButton *CommitButton;
    
    UILabel* words_Num;//字数提示
    NSUInteger input_words_num;
    BOOL isBeyond;//是否超过限制
    UIView *bg_view;

    NSString *filePath;
    
	CMFeedbackListener *m_pListener;
	CMFeedback* m_pFeedback;
}

@property (nonatomic, retain) UITableView *FeedbackTableView;

@property (nonatomic, retain, readonly) UITextView *textFieldFeedback;
@property (nonatomic, retain, readonly) UIButton *CommitButton;
@property(nonatomic,retain) UILabel *words_Num;

-(IBAction)btnCommit:(id) sender;

@end

class CMFeedbackListener : public IMSimpleResultListener
{
    void OnRequestFinish(void* UserData, int Result)
	{
		NSLog(@"CMFeedbackListener OnRequestFinish Result=%d",Result);
		
		CMFeedbackControl* feedback= (__bridge CMFeedbackControl*)UserData;
        feedback.CommitButton.enabled = YES;
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
			[tool ShowAlert:[NSString stringWithFormat:I(@"提交%@成功"),I(@"建议")]];
            feedback.textFieldFeedback.text = @"";
			[feedback.navigationController popViewControllerAnimated:YES];
		}else{	
            [feedback.CommitButton setEnabled:YES];
			[tool ShowAlert:[NSString stringWithFormat:I(@"提交%@失败"),I(@"建议")]];		
			
		}
	}	
	
	
};

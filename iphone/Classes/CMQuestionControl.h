#import <UIKit/UIKit.h>
#import "CMViewController.h"
#import "CMImage.h"
#include "cmqalist.h"
#import "CMTableView.h"
//#import "PhotoView.h"
#import "cmquestionupload.h"
#import "cmupload.h"
#import "cmqacategory.h"         //新增，支持获取问题类别
#include "cmhandler.h"
#include "cmcontacts.h"
#import "CMTextView.h"
#import "CheckBoxButton.h"


class CMQCategoryUpdateDataListener;
class CMQuestionSimpleResultListener;
@class ImageRightButton;
@interface CMQuestionControl: CMViewController <UITextViewDelegate,UITableViewDataSource,UITableViewDelegate,UINavigationControllerDelegate,UIImagePickerControllerDelegate,UIActionSheetDelegate>
{
	CMTextView *textquestion;
	ImageRightButton* btncredit;
    ImageRightButton* btnqcategory;        //top_view中的button,单击该按钮问题类别列表
    UIButton *photo_btn;
    UIButton *picture_btn;
    UILabel* lblcredit;
    UILabel* words_Num;//字数提示
    CMQACategory   *m_pQcategory;
    
    CheckBoxButton *anonymity_btn;//匿名
    NSUInteger input_words_num;
    BOOL isBeyond;//是否超过限制
    
    UIImageView *imgView1;//加载分享发布的图片
	
    UIView *bg_view;
    UIView *seg_bgview;
    UIView *top_view;
	UIView * popview;
	NSInteger checkpos;
	CMTableView*tableviewlist;
    UIButton *btnteacher;
    UIButton *btn_credit;
    UIButton *btnuploadimage;
    
    UIView *scoreview;
    int  creditnum;
    UIButton * btnok;
    
	CMQuestionSimpleResultListener *m_pListener;
   
    CMQCategoryUpdateDataListener *m_pUpdataDataListerner;       //新增，支持获取问题类别
    
    CMQuestionUpload* m_pQaUpload;
    
    CMFileUpload *m_pFileUpload;
    
    TContactsItem m_TContactsItem;
    
    NSMutableDictionary *dict;
    
    

    
    @public
	CMQAList* m_pQalist;
    NSString* categoryid;
    NSString* sTextview;
    
       }
@property(nonatomic,copy)NSString* categoryid;
@property(nonatomic,copy)NSString* imagepath;
@property(nonatomic,copy)NSString* sTextview;
@property(nonatomic,strong) NSMutableDictionary *expertsDict;
@property(nonatomic,strong) NSMutableDictionary *expertsNameLocDict;
@property(nonatomic,strong)UILabel *lbCreditPoint;
@property(nonatomic,assign)BOOL isShouldChangeText;


-(void)SetPlaceholder;
-(void)clearData;

-(void)getExpertsName:(NSString*)name    Id:(NSString*)Id;
-(void)loadTableList;

@end
class CMQuestionSimpleResultListener: public IMSimpleResultListener
{
    void OnRequestFinish(void* UserData, int Result)
	{
		//CMQuestionControl* question = (CMQuestionControl*)UserData;
		[tool CancelWait];
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
            
            [[NSNotificationCenter defaultCenter] postNotificationName:@"submit_success" object:nil];
            
		}
		else
		{
			[tool ShowAlert:[NSString stringWithFormat:I(@"提交%@失败"),I(@"提问")]];
		}
	}
};

class CMQCategoryUpdateDataListener: public IMUpdateDataListener             //新增，支持获取问题类别
{
public:
	CMQCategoryUpdateDataListener(){};
	~CMQCategoryUpdateDataListener(){};
	
	void OnUpdateDataProgress(void* UserData, int nPercent)
	{
        //CMMainControl* mainControl = (CMMainControl*)UserData;
	}
	
    void OnUpdateDataFinish(void* UserData, int Result)
	{
		NSLog(@"CMSurveyUpdateDataListener OnUpdateDataFinish Result=%d",Result);
		
		CMQuestionControl* control = (__bridge CMQuestionControl*)UserData;
		
		//[tool CancelWait];
        
		if(Result == TResult::ESuccess )
		{
			[control loadTableList];
		}else if (Result == TResult::ENothing) {
            [control loadTableList];
            
            //			[tool ShowAlert:I(@"没有搜索到内容!")];
		}else {
			[tool ShowError:Result];
		}
	}

};

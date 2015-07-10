#import <UIKit/UIKit.h>
#import "CMViewController.h"
#include "cmcomment.h"
#import "CheckBoxButton.h"


class CMEditCommentSimpleResultListener;
@interface CMEditCommentControl: CMViewController <UITextViewDelegate>
{
	UITextView *textcomment;
	CheckBoxButton* syncbtn;
	
	NSString* sflag; //course或者news
	NSString* sid; //课程或资讯id
	NSString* sreplyid;//回复评论id
	NSInteger type; //1回复，2发表
    
    UILabel* words_Num;
    NSUInteger input_words_num;
    BOOL isBeyond;
	
//	CMEditCommentSimpleResultListener *m_pListener;
	//CMComment* m_pComment;
}
@property(nonatomic,strong)NSString* sflag;
@property(nonatomic,strong)NSString* sid;
@property(nonatomic,strong)NSString* sreplyid;
@property(nonatomic,assign)NSInteger type;
//-(void)SetPlaceholder;
@end

//
//  SuggestionMenu.h
//  AutoComplete
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
@protocol PassValueDelegate
- (void)passValue:(NSString *)value;
@end
@interface SuggestionsList : UITableViewController 
{
	NSMutableArray *stringsArray;
	NSMutableArray *matchedStrings;
	
}
//-(id)initWithArray:(NSArray*)array;
@property(nonatomic,weak)id <PassValueDelegate> delegate;
@property(nonatomic,strong)NSMutableArray* matchedStrings;
@property(nonatomic,strong)NSMutableArray* stringsArray;
-(bool)ChangeText:(NSString*)string;
-(void)updateView;

@end

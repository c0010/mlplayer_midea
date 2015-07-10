//
//  SuggestionMenu.m
//  AutoComplete
#import "SuggestionsList.h"
#import "tool.h"
@implementation SuggestionsList
@synthesize delegate,matchedStrings,stringsArray;

//- (id)initWithArray:(NSArray*)array;
//{
//    self = [super init];
//    if (self) {
//        
//        stringsArray = [array retain];//[NSArray array];//系统读取
//        matchedStrings = nil;
//    }
//    return self;
//}
-(bool)ChangeText:(NSString *)string
{
    if(matchedStrings){
        [matchedStrings removeAllObjects];
    }
    matchedStrings = [[NSMutableArray alloc]initWithCapacity:10];
    
    for (NSString * e_str in stringsArray){
        NSString * str = [e_str lowercaseString];
        NSArray * array = [str componentsSeparatedByString:@" "];
        NSRange range;
        for (NSString * str1 in array){
            range = [str1 rangeOfString:[string lowercaseString]];
            if (range.location == 0 && range.length > 0) {
                [matchedStrings addObject:e_str];
            }
        }
    }
    if([matchedStrings count] > 0)
		self.tableView.hidden = NO;
	[self.tableView reloadData];
	return [matchedStrings count] > 0;
    
//    if(matchedStrings)
//		[matchedStrings release];
//    matchedStrings = [[stringsArray filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self beginswith[cd] %@",string]] retain];
//	if([matchedStrings count] > 0)
//		self.tableView.hidden = NO;
//	[self.tableView reloadData];
//	return [matchedStrings count] > 0;
}

-(void)updateView{
    self.tableView.hidden = NO;
    [self.tableView reloadData];
}


- (void)viewDidLoad {
    [super viewDidLoad];
	self.tableView.layer.borderWidth = 0.3;
	self.tableView.layer.borderColor = [[UIColor colorWithRed:180/255.0 green:180/255.0 blue:180/255.0 alpha:1.0] CGColor];
	self.tableView.hidden = YES;
    
}

//iOS8上 cell分割线置顶
-(void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    if ([self.tableView respondsToSelector:@selector(setSeparatorInset:)]) {
        [self.tableView setSeparatorInset:UIEdgeInsetsZero];
    }
    
    if ([self.tableView respondsToSelector:@selector(setLayoutMargins:)]) {
        [self.tableView setLayoutMargins:UIEdgeInsetsZero];
    }
}

-(void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([cell respondsToSelector:@selector(setSeparatorInset:)]) {
        [cell setSeparatorInset:UIEdgeInsetsZero];
    }
    
    if ([cell respondsToSelector:@selector(setLayoutMargins:)]) {
        [cell setLayoutMargins:UIEdgeInsetsZero];
    }
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	int count = [matchedStrings count];
    return count;
}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{
	return 30;
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Cell"];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"Cell"];
        UILabel *label = [[UILabel alloc]initWithFrame:CGRectMake(3.0, 5.0, self.tableView.frame.size.width - 6.0, 20.0)];
        label.tag = 10;
        label.font = [UIFont systemFontOfSize:15];
        label.textColor = UIColorRGB(0x5c5c5c);
        [cell.contentView addSubview:label];
    }
    
    UILabel *label = (UILabel *)[cell.contentView viewWithTag:10];
    label.text = [matchedStrings objectAtIndex:indexPath.row];
	cell.accessoryType = UITableViewCellAccessoryNone;
	cell.selectionStyle = UITableViewCellSelectionStyleGray;
    return cell;
    
}

#pragma mark - Table view delegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	NSString* value = [matchedStrings objectAtIndex:indexPath.row];
	[delegate passValue:value];
}
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return YES;
}


@end

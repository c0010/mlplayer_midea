//
//  CMTrainInfoViewController.m
//  MLPlayer
//
//  Created by 张永兵 on 14-12-19.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainInfoViewController.h"
#import "CMTrainContentViewController.h"

#import "CMSurveyListControl.h"


@interface CMTrainInfoViewController ()

@end

@implementation CMTrainInfoViewController

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    rightBarBtn.enabled = YES ;
    
}
-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.titleLabel.text = self.title;
    
    UIImageView *bgimg= [[UIImageView alloc] init];
    bgimg.backgroundColor = [UIColor clearColor];
    bgimg.image = [UIImage imageNamed:@"learn_tab_background"];
    bgimg.frame = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, bgimg.image.size.height);
    bgimg.tag = 1000;
    [self.view addSubview:bgimg];
    CMRELEASE(bgimg);
    
    rightBarBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [rightBarBtn setFrame:CGRectMake(0, 0, 40, 44)];
    rightBarBtn.imageEdgeInsets=[self itemFitDifferentVersion:NO];
    [rightBarBtn setImage:[UIImage imageNamed:@"top_but_trainiinfo_n"] forState:UIControlStateNormal];
    //[rightBarBtn setImage:[UIImage imageNamed:@"traininfo"] forState:UIControlStateHighlighted];
    [rightBarBtn addTarget:self action:@selector(gotoTrainDetail:) forControlEvents:UIControlEventTouchUpInside];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc]initWithCustomView:rightBarBtn];
    self.navigationItem.rightBarButtonItem = rightItem;
    
    topItemArr = [[NSMutableArray alloc]init];
    subviewsArr = [[NSMutableArray alloc]init];
    
    
    [self.view setBackgroundColor:[UIColor whiteColor]];
    if (self.isChatEnter || self.bIsPush) {
        if (!curItem) {
            curItem = new TMyTrainItem();
            curItem->sID = [self.trainID UTF8String];
        }
        if (!m_pUpdataDataListerner) {
            m_pUpdataDataListerner = new CMTrainInfoViewUpdateDataListener();
        }
        
        curItem->SetListener(m_pUpdataDataListerner, NULL);
        curItem->SetUserData((__bridge void*)self);
        
        [tool ShowActivityIndicator:self.view];
        
        curItem->RequestInfo();
        
        
        
    }else
        [self initView];
}

-(void)initView
{
    
    NSString *topItem = [NSString stringWithUTF8String:curItem->sTabList.c_str()];
    NSArray *array = [topItem componentsSeparatedByString:@"|"];
    
    if (array.count>1) {
        NSArray *titleArray = [[array objectAtIndex:0] componentsSeparatedByString:@","];
        NSArray *itemArray = [[array objectAtIndex:1] componentsSeparatedByString:@","];
        
        [self layoutTopItem:itemArray:titleArray];
    }
    
    
    m_pTableView = [[UITableView alloc] init];
    m_pTableView.backgroundColor = [UIColor clearColor];
    m_pTableView.frame = CGRectMake(0, 0, 42.5, UI_IOS_WINDOW_WIDTH);
    m_pTableView.center = CGPointMake(UI_IOS_WINDOW_WIDTH/2, 20);
    m_pTableView.transform = CGAffineTransformMakeRotation(-M_PI/2);
    m_pTableView.showsHorizontalScrollIndicator = NO;
    m_pTableView.showsVerticalScrollIndicator = NO;
    m_pTableView.delegate = self;
    m_pTableView.dataSource = self;
    m_pTableView.separatorColor = [UIColor clearColor];
    [self.view addSubview:m_pTableView];
    
    //标签
    CGSize size = [self getTabCategoryTitleSizeAtIndex:nSelectRow];
    selview = [[UIImageView alloc] init];
    selview.frame = CGRectMake(1.8, 6, 3.0, size.width + 10);
    selview.backgroundColor = kColorForeground;
    [m_pTableView addSubview:selview];
    
    self.titleLabel.text = [NSString stringWithUTF8String:curItem->sTitle.c_str()];
    
    if (self.isChatEnter  && !self.bIsPush) {
        for (int i=0; i<subviewsArr.count; i++ ) {
            UIView *subview = [subviewsArr objectAtIndex:i];
            if ([subview.nextResponder isKindOfClass:[CMChatViewController  class]])
            {
                nSelectRow = i;
            }
        }
        [self reportHoriziontalSwipe:nil];
        
    }
    
}

-(void)layoutTopItem:(NSArray *)itemArray :(NSArray *)titleArray
{
    
    for (int i=0; i<itemArray.count; i++) {
        NSString *titleStr = [itemArray objectAtIndex:i];
        if ([titleStr isEqualToString:@"Info"]) {
            
            browsernewsview = [[CMBrowserView alloc] initWithFrame:CGRectMake(0, 40, UI_IOS_WINDOW_WIDTH,UI_IOS_WINDOW_HEIGHT-44-20 - 40)];
            browsernewsview.tableviewlist.userInteractionEnabled = YES;
            browsernewsview.TrainID = [NSString stringWithUTF8String:curItem->sID.c_str()];
            
            utf8ncpy(browsernewsview->m_sFlag, "news", 15);
            
            [topItemArr addObject:[titleArray objectAtIndex:i]];
            [subviewsArr addObject:browsernewsview];
            
            UISwipeGestureRecognizer *horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionLeft;
            [browsernewsview.tableviewlist addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
            horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionRight;
            [browsernewsview.tableviewlist addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
            
        }else if ([titleStr isEqualToString:@"Course"]){
            browserview = [[CMBrowserView alloc] initWithFrame:CGRectMake(0, 40, UI_IOS_WINDOW_WIDTH,UI_IOS_WINDOW_HEIGHT-44-20 - 40)];
            //[[self view] addSubview:browserview];
            browserview.tableviewlist.userInteractionEnabled = YES;
            browserview.TrainID = [NSString stringWithUTF8String:curItem->sID.c_str()];
            
            utf8ncpy(browserview->m_sFlag, "course", 15);
            
            
            [topItemArr addObject:[titleArray objectAtIndex:i]];
            [subviewsArr addObject:browserview];
            
            
            UISwipeGestureRecognizer *horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionLeft;
            [browserview.tableviewlist addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
            horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionRight;
            [browserview.tableviewlist addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
            
        }else if ([titleStr isEqualToString:@"Survey"]){
            
            surveyControl = [[CMSurveyListControl alloc]init];
            surveyControl.view.frame = CGRectMake(0, 40, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-40-64);
            surveyControl.trainID = [NSString stringWithUTF8String:curItem->sID.c_str()];
            
            
            [topItemArr addObject:[titleArray objectAtIndex:i]];
            [subviewsArr addObject:surveyControl.view];
            
            UISwipeGestureRecognizer *horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionLeft;
            [surveyControl.view addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
            horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionRight;
            [surveyControl.view addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
        }else if ([titleStr isEqualToString:@"Exam"]){
            
            examControl= [[CMMyExamControl alloc]initWithFrame:CGRectMake(0, 40, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-64-40)];
            [examControl setTrainID:[NSString stringWithUTF8String:curItem->sID.c_str()]];
            
            [topItemArr addObject:[titleArray objectAtIndex:i]];
            [subviewsArr addObject:examControl];
            
            UISwipeGestureRecognizer *horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionLeft;
            [examControl addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
            horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionRight;
            [examControl addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
            
        }else if ([titleStr isEqualToString:@"Exercise"]){
            
            practiceControl = [[CMPracticeControl alloc]initWithFrame:CGRectMake(0, 40, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-64-40)];
            [practiceControl setTrainID:[NSString stringWithUTF8String:curItem->sID.c_str()]];
            
            [topItemArr addObject:[titleArray objectAtIndex:i]];
            [subviewsArr addObject:practiceControl];
            
            UISwipeGestureRecognizer *horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionLeft;
            [practiceControl addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
            horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionRight;
            [practiceControl addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
        }else if ([titleStr isEqualToString:@"Group"]){
        
            if (currItem || currQaItem) {
                if(currItem)
                    chatControl = [[CMChatViewController alloc]initWithTBrowserItem:currItem];
                else if(currQaItem)
                    chatControl=[[CMChatViewController alloc]initWithTQaItem:currQaItem];
            }else{
                chatControl = [[CMChatViewController alloc]init];
            }
            chatControl.isTrainChat = YES;
            chatControl.chatType = CMGroupChatType;
            
            //jid为空是交流区创建失败，不需要此栏位
            if (!NSStringFrom(curItem->sRoomJID) || [NSStringFrom(curItem->sRoomJID) isEqualToString:@""]) {
                continue;
            }
            chatControl.toName =[NSString stringWithUTF8String: curItem->sTitle.c_str()];
            chatControl.icon = [NSString stringWithUTF8String:curItem->sIcon.c_str()];
            chatControl.toJid = [NSString stringWithUTF8String:curItem->sRoomJID.c_str()];
            chatControl.toUid = [NSString stringWithUTF8String:curItem->sRoomID.c_str()];
            chatControl.password = [NSString stringWithUTF8String:curItem->sRoomPwd.c_str()];
            chatControl.draft = self.draft;
            
            chatControl.navigationControl = self.navigationController;

            chatControl.view.frame = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT);
            
            [topItemArr addObject:[titleArray objectAtIndex:i]];
            [subviewsArr addObject:chatControl.view];
            
            
            UISwipeGestureRecognizer *horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionLeft;
            [chatControl.view addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
            horizontal = [[UISwipeGestureRecognizer alloc]initWithTarget:self action:@selector(reportHoriziontalSwipe:)];
            horizontal.direction = UISwipeGestureRecognizerDirectionRight;
            [chatControl.view addGestureRecognizer:horizontal];
            CMRELEASE(horizontal);
            
        }
        
        
        
        
        
    }
    
    [self selectIndex:0];
    
    
}

- (CGSize)getTabCategoryTitleSizeAtIndex:(NSInteger)index{
    
    if (topItemArr.count == 0) {
        return CGSizeMake(0, 0);
    }
    
    CGSize size;
    NSString *strTitle = [topItemArr objectAtIndex:index];
    if ([topItemArr count] <= 4) {
        //size.width = 60.0;
        size.width = UI_IOS_WINDOW_WIDTH/[topItemArr count]-20;
    }
    else{
        if ([strTitle length]<=4) {
            size.width = 60.0;
        }else
            size = [strTitle sizeWithFont:[UIFont systemFontOfSize:16] forWidth:UI_IOS_WINDOW_WIDTH lineBreakMode:NSLineBreakByWordWrapping];
    }
    return size;
    
    
}

-(void)setItem:(TMyTrainItem &)item
{
    if (!curItem) {
        curItem = new TMyTrainItem();
    }
    
    *curItem = item;
}


-(void)gotoTrainDetail:(UIButton *)sender
{
    rightBarBtn.enabled = NO ; //只允许点击一次，否则会多次push造成crash
    CMTrainContentViewController *contentControl = [[CMTrainContentViewController alloc]init];
    contentControl.title = I(@"培训班信息");
    [contentControl setInfoItem:*curItem];
    [self.navigationController pushViewController:contentControl animated:YES];
    
}

-(void)reportHoriziontalSwipe:(UISwipeGestureRecognizer *)tap
{
    
    NSInteger index = nSelectRow;
    if(tap.direction  == UISwipeGestureRecognizerDirectionLeft)
    {
        index ++;
        
    }
    else if(tap.direction == UISwipeGestureRecognizerDirectionRight)
    {
        index--;
        
    }
    if(index < 0 || index >= subviewsArr.count)
        return;
    if (self.isChatEnter || nSelectRow != index)
    {
        [UIView animateWithDuration:0.3 animations:^(void){
            //判断左右滑动手势，对应减去不同的宽度，UISwipeGestureRecognizerDirectionLeft 加上当前tab高度，UISwipeGestureRecognizerDirectionRight 减去将要滑向的tab 高度
            float width;
            float cellwidth;
            CGSize size = [self getTabCategoryTitleSizeAtIndex:index];
            width = size.width + 10;
            
            CGSize size_Current = [self getTabCategoryTitleSizeAtIndex:nSelectRow];
            cellwidth = size_Current.width;
            
            if(tap.direction  == UISwipeGestureRecognizerDirectionLeft)
            {
                cellwidth = size_Current.width + 20;
            }
            else if(tap.direction == UISwipeGestureRecognizerDirectionRight)
            {
                cellwidth = width + 10;
            }
            
            CGRect newframe = selview.frame;
            newframe.origin.y = newframe.origin.y + (index - nSelectRow) * cellwidth;  //
            newframe.size.height = width;
            selview.frame = newframe;
        } completion:^(BOOL finish){
            nSelectRow = index;
            [m_pTableView reloadData];
            
            UITableViewCell *cell = [m_pTableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:nSelectRow inSection:0]];
            CGRect rect = cell.frame;
            if(tap.direction  == UISwipeGestureRecognizerDirectionLeft)
            {
                if (rect.size.width == 0 && rect.size.height == 0.0) {
                    [m_pTableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:index inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:YES];
                    
                }
                
            }
            else if(tap.direction == UISwipeGestureRecognizerDirectionRight)
            {
                if (rect.size.width == 0 && rect.size.height == 0.0) {
                    [m_pTableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:index inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:YES];
                }
            }
            [m_pTableView scrollRectToVisible:rect animated:YES];
            
            [self selectIndex:nSelectRow];
        }];
    }

    
}

- (IBAction)btnPressed:(id)sender
{
    UIButton *btn = (UIButton*)sender;
    UITableViewCell *cell = [self buttonSuperCell:btn];
    NSIndexPath *indexPath = [m_pTableView indexPathForCell:cell];
    if (nSelectRow != indexPath.row)
    {
        CGRect frame = [m_pTableView  convertRect:btn.frame fromView:btn.superview];
        [UIView animateWithDuration:0.3 animations:^(void){
            CGRect newframe = selview.frame;
            newframe.origin.y = frame.origin.y;  //由于tableview，transform与 selview.transform 差异，正好他们的x，y对应
            newframe.size.height = btn.frame.size.width;
            selview.frame = newframe;
        } completion:^(BOOL finish){
            nSelectRow = (int)indexPath.row;
            [m_pTableView reloadData];
            
            UITableViewCell *cell = [m_pTableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:nSelectRow inSection:0]];
            CGRect rect = cell.frame;
            [m_pTableView scrollRectToVisible:rect animated:YES];
            
            
            [self selectIndex:nSelectRow];
                        
            }];
        
    }
    
    // UITableViewCell *cell = [m_pTableView cellForRowAtIndexPath:indexPath];
}



-(void)selectIndex:(int)index
{
    
    for (int i=0; i<subviewsArr.count; i++) {
        UIView *subview = [subviewsArr objectAtIndex:i];
        if (i == index) {
            if ([subview.nextResponder isKindOfClass:[CMChatViewController  class]]){
                UIView *view = [self.view viewWithTag:1000];
                 [self addChildViewController:(UIViewController*)subview.nextResponder];
                [self.view insertSubview:subview belowSubview:view];
                [(UIViewController*)subview.nextResponder viewWillAppear:YES];
               
            }
            else
                [self.view addSubview:subview];
            
            if ([subview isKindOfClass:[CMBrowserView class]]) {
                CMBrowserView *b = (CMBrowserView *)subview;
                //b->_reloading=NO;
                [b automaticRefreshUseCache:YES];
            }else if ([subview isKindOfClass:[CMMyExamControl class]]){
                
                [(CMMyExamControl *)subview startFlash];
            }else if ([subview isKindOfClass:[CMPracticeControl class]]){
                [(CMPracticeControl *)subview startFlash];
            }
            
        }else{
            if ([subview superview]) {
                [subview removeFromSuperview];

            }
        }
        
    }
    
}

#pragma mark TableView delegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return [topItemArr count];
    
}
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    CGSize size = [self getTabCategoryTitleSizeAtIndex:indexPath.row];
    return size.width + 20;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    float width;
    float cellwidth;

    NSString *strTitle_ = [topItemArr objectAtIndex:indexPath.row];
    if ([topItemArr count] < 4) {
        //width = 70;
        cellwidth =UI_IOS_WINDOW_WIDTH/[topItemArr count];
        width = cellwidth-10;
    }
    else{
        if ([strTitle_ length] <= 4) {
            width = 70;
            cellwidth = width + 10;
        }else{
            
            CGSize size = [strTitle_ sizeWithFont:[UIFont systemFontOfSize:16] forWidth:UI_IOS_WINDOW_WIDTH lineBreakMode:NSLineBreakByWordWrapping];
            width = size.width + 10;
            cellwidth = width + 10;
        }
        
        
    }
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"browsecell"];
    
    if (cell == nil)
    {
#if ! __has_feature(objc_arc)
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                       reuseIdentifier:@"browsecell"] autorelease];
#else
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                      reuseIdentifier:@"browsecell"];
#endif
        UIButton *button = [[UIButton alloc] init];
        button.tag = 2013;
        [button addTarget:self action:@selector(btnPressed:) forControlEvents:UIControlEventTouchUpInside];
        [cell.contentView addSubview:button];
        CMRELEASE(button);
        cell.backgroundColor = [UIColor clearColor];
        
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    cell.transform = CGAffineTransformMakeRotation(M_PI/2);
    
    UIButton *btn = (UIButton *)[cell.contentView viewWithTag:2013];
    cell.frame = CGRectMake(0, 0, cellwidth, 42.5);
    btn.frame = CGRectMake(0, 0, width, 28);
    btn.center = cell.center;
    btn.backgroundColor = [UIColor clearColor];
    [btn setTitleColor:UIColorRGB(0x3a3a3a) forState:UIControlStateNormal];
    [btn.titleLabel setFont:[UIFont systemFontOfSize:16]];
    
    if (nSelectRow == indexPath.row)
    {
        CGRect frame = selview.frame;
        CGRect cell_frame = [m_pTableView  rectForRowAtIndexPath:indexPath];
        frame.origin.y = cell_frame.origin.y + 6;
        selview.frame = frame;
        [btn setTitleColor:kColorForeground forState:UIControlStateNormal];
        
    }
    else
    {
        [btn setBackgroundImage:nil forState:UIControlStateNormal];
        [btn setBackgroundImage:nil forState:UIControlStateHighlighted];
    }
    
    [btn setTitle:strTitle_ forState:UIControlStateNormal];
    return cell;
    
}
-(void)dealloc
{
    CMRELEASE(topItemArr);
    CMRELEASE(subviewsArr);
    
    
    curItem->Cancel();
    curItem->SetUserData(NULL);
    curItem->SetListener(NULL, NULL);
    SAFEDELETE(curItem);
    SAFEDELETE(m_pUpdataDataListerner);
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end

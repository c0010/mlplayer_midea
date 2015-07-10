//
//  CMTrainApplyController.m
//  MLPlayer
//
//  Created by 张永兵 on 14/12/22.
//  Copyright (c) 2014年 w. All rights reserved.
//

#import "CMTrainApplyController.h"
#import "CMTrainApplyView.h"

@interface CMTrainApplyController ()

@end

@implementation CMTrainApplyController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    
    UIImageView *bgimg= [[UIImageView alloc] init];
    bgimg.backgroundColor = [UIColor clearColor];
    bgimg.image = [UIImage imageNamed:@"learn_tab_background"];
    bgimg.frame = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, bgimg.image.size.height);
    [self.view addSubview:bgimg];
    CMRELEASE(bgimg);
    
    m_pTableView = [[UITableView alloc] init];
    m_pTableView.backgroundColor = [UIColor clearColor];
    m_pTableView.frame = CGRectMake(0, 0, 40, UI_IOS_WINDOW_WIDTH);
    m_pTableView.center = CGPointMake(UI_IOS_WINDOW_WIDTH/2, 20);
    m_pTableView.transform = CGAffineTransformMakeRotation(-M_PI/2);
    m_pTableView.delegate = self;
    m_pTableView.dataSource = self;
    m_pTableView.showsHorizontalScrollIndicator = NO;
    m_pTableView.showsVerticalScrollIndicator = NO;
    m_pTableView.separatorColor = [UIColor clearColor];
    [self.view addSubview:m_pTableView];
    
    m_pData = [[NSMutableArray alloc] init];
    [m_pData addObject:I(@"未报名")];
    [m_pData addObject:I(@"已报名")];
    [m_pData addObject:I(@"已结束")];
    
    nSelectRow = 0;
    if (selview) {
        [selview removeFromSuperview];
        CMRELEASE(selview);
    }
    //标签
    selview = [[UIImageView alloc] init];
    selview.frame = CGRectMake(0, 5, 3.0, UI_IOS_WINDOW_WIDTH/3.0 - 10);
    selview.backgroundColor = kColorForeground;
    [m_pTableView addSubview:selview];
    
    //数据列表
    listView = [[CMTrainApplyView alloc]initWithFrame:CGRectMake(0, 40, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-60-44)];
    listView.tableviewlist.userInteractionEnabled = YES;
    listView.tableviewlist.backgroundColor = kColorBackground;
    
    UISwipeGestureRecognizer *swipeGesture = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(swipeResult:)];
    swipeGesture.direction = UISwipeGestureRecognizerDirectionRight;
    [listView.tableviewlist addGestureRecognizer:swipeGesture];
    
    swipeGesture = [[UISwipeGestureRecognizer alloc] initWithTarget:self action:@selector(swipeResult:)];
    swipeGesture.direction = UISwipeGestureRecognizerDirectionLeft;
    [listView.tableviewlist addGestureRecognizer:swipeGesture];
    
    [[self view] addSubview:listView];
    strcpy(listView->m_sFlag, "noapply");
    [listView automaticRefresh];

    
}

- (void)swipeResult:(UISwipeGestureRecognizer *)tap
{
    NSInteger index = nSelectRow;
    if(tap.direction  == UISwipeGestureRecognizerDirectionRight)
    {
        if (nSelectRow==0) {
            return;
        }
        index--;
    }
    else if(tap.direction == UISwipeGestureRecognizerDirectionLeft)
    {
        if (nSelectRow==2) {
            return;
        }
        index++;
    }
    if(index < 0 || index >= 4)
        return;
    if (nSelectRow != index)
    {

        //CGRect frame = [m_pTableView  convertRect:btn.frame fromView:btn.superview];
        [UIView animateWithDuration:0.3 animations:^(void){
            float width;
            float cellwidth;
            width = UI_IOS_WINDOW_WIDTH/3.0 - 10;
            
            cellwidth = UI_IOS_WINDOW_WIDTH/3.0;
            
            CGRect newframe = selview.frame;
            newframe.origin.y = newframe.origin.y + (index - nSelectRow)*cellwidth;  //
            newframe.size.height = width;
            selview.frame = newframe;
            
            
        } completion:^(BOOL finish){
            nSelectRow = index;
            [m_pTableView reloadData];
            
            UITableViewCell *cell = [m_pTableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:nSelectRow inSection:0]];
            CGRect rect = cell.frame;
            [m_pTableView scrollRectToVisible:rect animated:YES];
            
            [self tabChange:index];
            
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
            newframe.origin.y = frame.origin.y + 5;  //由于tableview，transform与 selview.transform 差异，正好他们的x，y对应
            newframe.size.height = UI_IOS_WINDOW_WIDTH / 3.0 - 10;
            selview.frame = newframe;
            
            
        } completion:^(BOOL finish){
            nSelectRow = indexPath.row;
            [m_pTableView reloadData];
            
            UITableViewCell *cell = [m_pTableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:nSelectRow inSection:0]];
            CGRect rect = cell.frame;
            [m_pTableView scrollRectToVisible:rect animated:YES];
            
            [self tabChange:indexPath.row];
            
        }];
        
    }
    
}

- (void)tabChange:(NSInteger)tabIndex
{
    if (tabIndex == 0) {
        strcpy(listView->m_sFlag, "noapply");
        listView.flag = 0;
    }else if(tabIndex == 1){
        strcpy(listView->m_sFlag, "applied");
        listView.flag = 1;
    }else if(tabIndex == 2){
        strcpy(listView->m_sFlag, "over");
        listView.flag = 2;
    }
    
    [listView automaticRefresh];
    
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    
    return [m_pData count];
}


-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([m_pData count] < 4)
    {
        return UI_IOS_WINDOW_WIDTH/[m_pData count];
    }
    else
    {
        NSString *title = [m_pData objectAtIndex:indexPath.row];
        
        if (title.length > 2)
        {
            CGSize size = [title sizeWithFont:[UIFont systemFontOfSize:18] forWidth:100 lineBreakMode:NSLineBreakByWordWrapping];
            return size.width + 20;
        }
        
        return 70;
    }
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    float cellwidth;
    
    
    NSString *title = [m_pData objectAtIndex:indexPath.row];
    
    if ([m_pData count] < 4)
    {
        cellwidth = UI_IOS_WINDOW_WIDTH/[m_pData count];
    }
    else
    {
        CGSize size = [title sizeWithFont:[UIFont systemFontOfSize:18] forWidth:UI_IOS_WINDOW_WIDTH lineBreakMode:NSLineBreakByWordWrapping];
        
        if (size.width > 60)
        {
            cellwidth = size.width + 10;
        }
    }
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"browsecell"];
    
    if (cell == nil)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                       reuseIdentifier:@"browsecell"];
        cell.frame = CGRectMake(0, 0, cellwidth, 40);
        UIButton *button = [[UIButton alloc] init];
        button.frame = CGRectMake(0, 0, cellwidth, 28);
        button.center = cell.center;
        button.tag = 2013;
        [button addTarget:self action:@selector(btnPressed:) forControlEvents:UIControlEventTouchUpInside];
        [cell.contentView addSubview:button];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        cell.backgroundColor = [UIColor clearColor];
    }
    cell.transform = CGAffineTransformMakeRotation(M_PI/2);
    
    UIButton *btn = (UIButton *)[cell.contentView viewWithTag:2013];
    btn.backgroundColor = [UIColor clearColor];
    [btn setTitleColor:UIColorRGB(0x3a3a3a) forState:UIControlStateNormal];
    [btn.titleLabel setFont:[UIFont systemFontOfSize:16]];
    
    if (nSelectRow == indexPath.row)
    {
        CGRect frame = selview.frame;
        CGRect cell_frame = [m_pTableView  rectForRowAtIndexPath:indexPath];
        frame.origin.y = cell_frame.origin.y + 5;
        selview.frame = frame;
        [btn setTitleColor:kColorForeground forState:UIControlStateNormal];
    }
    else
    {
        [btn setBackgroundImage:nil forState:UIControlStateNormal];
        [btn setBackgroundImage:nil forState:UIControlStateHighlighted];
    }
    
    [btn setTitle:title forState:UIControlStateNormal];
    
    return cell;
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

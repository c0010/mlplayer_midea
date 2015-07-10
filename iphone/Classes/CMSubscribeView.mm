//
//  CMSubscribeView.m
//  MLPlayer
//
//  Created by lhx on 15/5/26.
//  Copyright (c) 2015年 w. All rights reserved.
//

#import "CMSubscribeView.h"
#import "tool.h"

#define BUTTON_WIDTH_TWO     80
#define BUTTON_WIDTH_THREE   80
#define BUTTON_WIDTH_FOUR    80
#define BUTTON_WIDTH_DEFAULTE  80
#define BUTTON_HEIGHT        28.0

@implementation CMSubscribeView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

- (id)initWithFrame:(CGRect)frame CMCategoryItem :(CMCategoryItem *)item
{
    self = [super initWithFrame:frame];
    if (self) {
        [self createUI:item];
    }
    return self;
}

- (void)setCMSubscribeViewFrame:(CGRect)frame
{
    [self setFrame:frame];
    
    CGRect bF = frame;
    bF.origin.x = 0;
    bF.origin.y = 0;
    
    [_blankView setFrame:bF];
}

-(void)layoutSubviews
{
    [super layoutSubviews];
    //[_blankView setFrame:self.bounds];
}

-(void)createUI:(CMCategoryItem *)item
{
    categoryItem = item;
    
    _blankView=[[UIScrollView alloc]initWithFrame: CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT - 64 - 37)];
    [_blankView setBackgroundColor:[UIColor clearColor]];
    _blankView.clipsToBounds = YES;
    _blankView.pagingEnabled = YES;
    [_blankView setAutoresizesSubviews:YES];
    _blankView.showsHorizontalScrollIndicator = NO;
    _blankView.showsVerticalScrollIndicator = NO;
    _blankView.canCancelContentTouches = YES;
    [self addSubview:_blankView];
    
    [_blankView.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    
    UIImageView *bg = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, 40)];
    [bg setImage:[UIImage imageNamed:@"learn_subscribe_blank"]];
    [_blankView addSubview:bg];
    
    double spaceHeight = 10.0;
    double spaceWidth  = 20.0;
    
    int count  = item->FrontChildItemCount();
    
    // Set our initial origin.
    int x = spaceWidth;
    int y = spaceHeight;
    
    for (int i = 0; i < count; i ++) {
        CMCategoryItem* nItem = item->GetChildItem(i);
        
        NSString *title = [NSString stringWithUTF8String: nItem->sTitle];
        BOOL isSubscribe = nItem->bIsSelected;
        
        int length = [title length];
        
        UIButton* btn = [self getbtn:title tag:(NSInteger)nItem length:length isSubscribe:isSubscribe];
        
        // Adjust the position.
        if ( x + CGRectGetWidth(btn.frame) > UI_IOS_WINDOW_WIDTH - spaceWidth) {
            // Start new row.
            x = spaceWidth;
            y += CGRectGetHeight(btn.frame) + spaceHeight;
        }
        
        CGRect newFrame = CGRectMake(x, y, btn.frame.size.width, btn.frame.size.height);
        [btn setFrame:newFrame];
        
        x += CGRectGetWidth(btn.frame) + spaceWidth;
        
        [_blankView addSubview:btn];
        
    }
    if (y < UI_IOS_WINDOW_HEIGHT-64-37-10) {
        
        [bg setFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, y + BUTTON_HEIGHT + spaceHeight)];
        
        y = _blankView.frame.size.height + spaceHeight;
    }
    else{
        
        [bg setFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, y + BUTTON_HEIGHT + spaceHeight)];
        
        y += spaceHeight + BUTTON_HEIGHT + spaceHeight;
        
    }
    
    [_blankView setContentSize:CGSizeMake(UI_IOS_WINDOW_WIDTH, y)];
    
    self.blankButton = [[UIButton alloc] initWithFrame:CGRectMake(0, bg.frame.size.height, UI_IOS_WINDOW_WIDTH, _blankView.frame.size.height - bg.frame.size.height)];
    self.blankButton.backgroundColor = [UIColor clearColor];
    [_blankView addSubview:self.blankButton];
}

- (UIButton*)getbtn:(NSString*)txt tag:(NSInteger)tag length:(int)length isSubscribe: (BOOL)isSubscribe
{
    UIButton* btn = [UIButton buttonWithType:UIButtonTypeCustom];
    btn.tag = tag;
    [btn addTarget:self action:@selector(seletCategory:) forControlEvents:UIControlEventTouchUpInside];
    btn.titleLabel.font = [UIFont systemFontOfSize:13];
    btn.titleLabel.text = txt;
    
    [btn setBackgroundImage:[UIImage imageNamed:@"learn_subscribe_btn_bg"] forState:UIControlStateNormal];
    
    if (isSubscribe) {
        [btn setTitleColor:UIColorRGB(0x0092DD) forState:UIControlStateNormal];
        //  [btn setBackgroundImage:[UIImage imageNamed:@"learn_subscribe_btn_bg"] forState:UIControlStateNormal];
        //  [btn setBackgroundImage:[UIImage imageNamed:@"learn_subscribe_btn_bg"] forState:UIControlStateHighlighted];
    }else
    {
        [btn setTitleColor:UIColorRGB(0x676767) forState:UIControlStateNormal];
        //  [btn setBackgroundImage:[UIImage imageNamed:@"cancelattention_n"] forState:UIControlStateNormal];
        //  [btn setBackgroundImage:[UIImage imageNamed:@"cancelattention_p"] forState:UIControlStateHighlighted];
    }
    [btn setTitle:txt forState:UIControlStateNormal];
    switch (length) {
        case 2:
        {
            btn.frame = CGRectMake(0, 0, BUTTON_WIDTH_TWO, BUTTON_HEIGHT);
        }
            break;
        case 3:
        {
            btn.frame = CGRectMake(0, 0, BUTTON_WIDTH_THREE, BUTTON_HEIGHT);
        }
            break;
        case 4:
        {
            btn.frame = CGRectMake(0, 0, BUTTON_WIDTH_FOUR, BUTTON_HEIGHT);
        }
            break;
        default:
            btn.frame = CGRectMake(0, 0, BUTTON_WIDTH_DEFAULTE, BUTTON_HEIGHT);
            break;
    }
    return btn;
}

-(void)seletCategory: (UIButton *)sender
{
    CMCategoryItem* item=(CMCategoryItem *)sender.tag;
    item->bIsSelected = !item->bIsSelected;
    
    if(categoryItem->SelectedChildItemCount() == 0)
    {
        [tool ShowAlert:@"至少选择一个栏目"];
        item->bIsSelected = !item->bIsSelected;
    }
    
    
    CMCategory::GetInstance()->Update(item);
    
    // [sender setBackgroundImage: !item->bIsSubscribe ?[UIImage imageNamed:@"cancelattention_n"] : [UIImage imageNamed:@"cancelattention_p"] forState:UIControlStateNormal];
    [sender setTitleColor: item->bIsSelected ? UIColorRGB(0x0092DD) : UIColorRGB(0x676767)  forState:UIControlStateNormal];
    
}

/*
 // Only override drawRect: if you perform custom drawing.
 // An empty implementation adversely affects performance during animation.
 - (void)drawRect:(CGRect)rect
 {
 // Drawing code
 }
 */

@end
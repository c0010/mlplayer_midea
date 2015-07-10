//
//  cmitemcontroller.m
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import "CMQuestionDetailView.h"
#import "CMOneAnswerController.h"
#include "cmsettings.h"
#import "CellAnswerTitleCell.h"
#import "CMImageDetailViewControl.h"
#import "SDWebImage/SDImageCache.h"
#import "tool.h"
#import "cmfileinfo.h"

@implementation CMQuestionDetailView
@synthesize imageView1;
@synthesize questionid;
@synthesize needrefresh;
@synthesize textanswer;
@synthesize photo_btn,picture_btn;
@synthesize isOpen;
@synthesize imagepath;

#define kCellIdentifier @"com.apple.CMQuestionDetailView.CellIdentifier"
#define SPINNER_HEIGHT 5.0
#define SHARE_IMAGE_WIDTH 220.0
#define SHARE_IMAGE_HEIGHT 75.0
#pragma mark -
#pragma mark View init
int answer_num;
float KEYBOARDSHOW_HEIGHT;
float keyboardHeight;

-(id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame refresh:false];
	CGRect rc = self.tableviewlist.bounds;

    rc.origin.y = 0;
	rc.origin.x = 0;
	self.tableviewlist.frame = rc;
    self.tableviewlist.delegate = self;
	self.tableviewlist.backgroundColor = kColorBackground;
	self.tableviewlist.separatorStyle = UITableViewCellSeparatorStyleNone;
    NSNotificationCenter *defaultCenter = [NSNotificationCenter defaultCenter];
    
    [defaultCenter addObserver:self
                      selector:@selector(keyboardWillShow:)
                          name:UIKeyboardWillShowNotification
                        object:nil];
    [defaultCenter addObserver:self
                      selector:@selector(keyboardWillHide:)
                          name:UIKeyboardWillHideNotification
                        object:nil];
    [defaultCenter addObserver:self selector:@selector(SubmitFaild) name:@"submit_answer_faild" object:nil];
    
    if (!m_pAnswerUpdateListener) {
        m_pAnswerUpdateListener = new CMAnswerUpdateDataListener();
    }
    
    if (!m_pAnswerBestUpdateListener) {
        m_pAnswerBestUpdateListener = new CMAnswerDetailSimpleResultListener();
    }
    
    if (!m_pOneAnswerRatingListener) {
        m_pOneAnswerRatingListener = new CMAnswerDetailRatingListener();
    }
    
    if (!m_pQuestionDetail) {
        m_pQuestionDetail = new CMQuestionDetail(m_pAnswerUpdateListener,m_pAnswerBestUpdateListener,m_pOneAnswerRatingListener);
        m_pQuestionDetail->SetUserData((__bridge void*)self);
    }
    
	return self;
}

#pragma mark - KEYBOARD SHOW HIDE
- (void)keyboardWillShow:(NSNotification *)aNotification {
    NSDictionary *info = [aNotification userInfo];
    //获取高度
    NSValue *value = [info objectForKey:@"UIKeyboardBoundsUserInfoKey"];
    CGSize keyboardSize = [value CGRectValue].size;
    
    keyboardHeight = keyboardSize.height;
   
   self.tableviewlist.frame = CGRectMake(0.0, 0.0, 320.0, UI_IOS_WINDOW_HEIGHT-44-20);
   if (UI_IOS_WINDOW_HEIGHT == 568.0) {
       double y = 0.0;
       if(m_pQuestionDetail->HasAnswerFlag()){
           CGPoint point_ = [textanswer convertPoint:textanswer.center toView:self.window];
           point_view.y = point_.y-30.0;
           y = UI_IOS_WINDOW_HEIGHT - keyboardHeight - point_view.y - 115.0;
       }
       else{
           CGPoint point_ = [textanswer convertPoint:textanswer.center toView:self.window];
           point_view.y = point_.y-30.0;
           y = UI_IOS_WINDOW_HEIGHT - keyboardHeight - point_view.y - 115.0;
       }
       self.tableviewlist.contentOffset = CGPointMake(0.0, self.tableviewlist.contentOffset.y - y);
   }
   else{
       double y = 0.0;
       if(m_pQuestionDetail->HasAnswerFlag()){
           CGPoint point_ = [textanswer convertPoint:textanswer.center toView:self.window];
           point_view.y = point_.y-30.0;
           y = UI_IOS_WINDOW_HEIGHT - keyboardHeight - point_view.y - 115.0;
       }
       else{
           CGPoint point_ = [textanswer convertPoint:textanswer.center toView:self.window];
           point_view.y = point_.y-30.0;
           y = UI_IOS_WINDOW_HEIGHT - keyboardHeight - point_view.y - 115.0;
       }

       self.tableviewlist.contentOffset = CGPointMake(0.0, self.tableviewlist.contentOffset.y - y);
   }

    CGRect frame = self.tableviewlist.frame;
    frame.size.height -= keyboardHeight;
    self.tableviewlist.frame = frame;
    
    //    // 获取键盘弹出的时间
    //    NSValue *animationDurationValue = [[aNotification userInfo] objectForKey:UIKeyboardAnimationDurationUserInfoKey];
    //    NSTimeInterval animationDuration;
    //    [animationDurationValue getValue:&animationDuration];
}

- (void)keyboardWillHide:(NSNotification *)aNotification {
    [UIView beginAnimations:@"ResizeForKeyBoard" context:nil];
    [UIView setAnimationDuration:0.3f];
    self.tableviewlist.contentOffset = CGPointMake(0.0, 0.0);
    CGRect frame = self.tableviewlist.frame;
    frame.size.height += keyboardHeight;
    self.tableviewlist.frame = frame;

    [UIView commitAnimations];
}
#pragma mark -
#pragma mark UITableView delegate methods


- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath
{	
    return UITableViewCellEditingStyleNone;
}

- (NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return I(@"满意回答");
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle 
forRowAtIndexPath:(NSIndexPath *)indexPath 
{
	if (editingStyle == UITableViewCellEditingStyleDelete) 
	{
		if(!m_pQuestionDetail)
			return;
		int row = indexPath.row;
		row--;
		TAnswerItem answerItem;
		if(!m_pQuestionDetail->GetItem(row,answerItem))
			return;
		if(m_pQuestionDetail->SetBestAnswer([questionid UTF8String],answerItem.GetAnswerItemID()))
		{
            [tableviewlist reloadData];
		}
        
	}
	else if(editingStyle == UITableViewCellEditingStyleInsert)
	{
		
	}
}
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section 
{
    
	if(!m_pQuestionDetail)
		return 1;

    int i;
    if (m_pQuestionDetail->GetItemCount() == 0) {
        i = 1;
    }
    else{
        i = 2;
    }

	if(m_pQuestionDetail->HasAnswerFlag()){
        if (m_pQuestionDetail->GetItemCount() == 0) {
            i += 2;
        }
        else
            i++;
    }
	if (m_pQuestionDetail->IsEnd() || (SETTING.GetAutoLoadMore() && !isOpen))
		return m_pQuestionDetail->GetItemCount()+i;
    if (isOpen && !SETTING.GetAutoLoadMore()) {
        return m_pQuestionDetail->GetItemCount()+2+i;
    }
	return m_pQuestionDetail->GetItemCount()+1+i;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	if(indexPath.row == 0)
		return;
    
    
	int row = indexPath.row;
    row--;
	if(row == (m_pQuestionDetail->HasAnswerFlag() ? m_pQuestionDetail->GetItemCount()+1:m_pQuestionDetail->GetItemCount()))
		return;
	//TAnswerItem answerItem;
	if(m_pQuestionDetail->HasAnswerFlag() && row == 0)
		m_pQuestionDetail->GetHasFlagAnswerItem(answeritem);
	else
	{
		if(m_pQuestionDetail->HasAnswerFlag())
			row--;
		m_pQuestionDetail->GetItem(row, answeritem);
	}
    
  
    [tableView deselectRowAtIndexPath:indexPath animated:NO];

		
}



- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	int width = self.tableviewlist.bounds.size.width-10;
	UIImage* image = nil;
	if(indexPath.row == 0)
	{
        width = LABEL_WIDTH;
        if (isOpen) {
            //回答框打开时
            if (point_view.y == 0.0) {
                point_view = CGPointMake(0.0, [CMQuestionTableViewCell GetCellHeight:curqaItem webimage:m_pWebImage shareimage:nil width:width hideimage:true] + 70.0);//30.0
                }
            
            return  [CMQuestionTableViewCell GetCellHeight:curqaItem webimage:m_pWebImage shareimage:nil width:width hideimage:true ]+126.0;
        }
        //其他用户
		return [CMQuestionTableViewCell GetCellHeight:curqaItem webimage:m_pWebImage shareimage:nil width:width hideimage:true ]+5;
	}
	int row = indexPath.row;
	row--;
    row--;
	if(row == (m_pQuestionDetail->HasAnswerFlag() ? m_pQuestionDetail->GetItemCount()+1:m_pQuestionDetail->GetItemCount()))
		return 44;
    
	TAnswerItem answerItem;

    //回答列表标题
    if (indexPath.row == 1) {
        return 33.0;
    }

  //最佳答案
	if(m_pQuestionDetail->HasAnswerFlag() && row == 0)
	{
		image = [UIImage imageNamed:@"bestanswer"];
		m_pQuestionDetail->GetHasFlagAnswerItem(answerItem);
        if (m_pQuestionDetail->GetItemCount() == 0) {
            return  [self GetCellHeight:answerItem width:width-image.size.width shareImage:nil] + 5.0;
        }
        return  [self GetCellHeight:answerItem width:width-image.size.width shareImage:nil] + 38.0;
	}
	else
	{	
		image = [UIImage imageNamed:@"bestanswer"]; //固定高宽作用
		if(m_pQuestionDetail->HasAnswerFlag())
			row--;
        else{
            //无最佳答案，用户本身进入
            if(_stricmp(curqaItem.sQuestioner_username.c_str(),SETTING.GetUserName())== 0){
                m_pQuestionDetail->GetItem(row, answerItem);
                return  [self GetCellHeight:answerItem width:width-image.size.width shareImage:nil] + 10.0;
            }
        }
		m_pQuestionDetail->GetItem(row, answerItem);
        
	}
	
	return  [self GetCellHeight:answerItem width:width-image.size.width shareImage:nil] - 15.0;
} 

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    self.tableviewlist.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.tableviewlist.separatorColor = [UIColor clearColor];
	int width = self.tableviewlist.bounds.size.width-10;
	if(indexPath.row == 0)
	{
		if(!questioncell)
		{
			CMQuestionTableViewCell* questionview = [[CMQuestionTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"questiondetail"];
			questionview.hideimage = YES;
            [questionview.showImageView addTarget:self action:@selector(pressQuestionImg:event:) forControlEvents:UIControlEventTouchUpInside];
            if(_stricmp(curqaItem.sQuestioner_username.c_str(),SETTING.GetUserName()) != 0)
            {
                questionview.isUserSelf = NO;
            }
            else{
                questionview.isUserSelf = YES;
            }
            questionview.tag = 2013;
			[questionview setcellinfo:curqaItem webimage:m_pWebImage shareimage:nil index:indexPath.row];
			UIImage* image = [UIImage imageNamed:@"question"];
            questionview.questionImageView.image = image;
            width = LABEL_WIDTH;

			int h = [CMQuestionTableViewCell GetCellHeight:curqaItem webimage:m_pWebImage shareimage:nil width:width hideimage:true];
            questionview.frame = CGRectMake(0,0,320,h);

			questioncell = [[UITableViewCell alloc]init];
			questioncell.contentView.backgroundColor = [UIColor whiteColor];
       
            [questioncell.contentView addSubview:questionview];
            
            //阴影分割
			UIView* blankview = [[UIView alloc] init];
			blankview.frame = CGRectMake(0, h,self.tableviewlist.bounds.size.width,6.0);
            blankview.backgroundColor = UIColorRGB(0xe7e7e7);
            blankview.tag = 2022;
            blankview.layer.shadowColor=[UIColor blackColor].CGColor;
            blankview.layer.shadowOffset=CGSizeMake(0,-1);
            blankview.layer.shadowOpacity=0.4;
            blankview.layer.shadowRadius=0;
            blankview.layer.shadowPath = [UIBezierPath bezierPathWithRect:blankview.bounds].CGPath;
            
            [questioncell addSubview:blankview];

            image = [UIImage imageNamed:@"addattention_n"];

            attentionbtn = [UIButton buttonWithType:UIButtonTypeCustom];
            attentionbtn.frame = CGRectMake(self.tableviewlist.bounds.size.width-10.0-image.size.width, h-image.size.height-SPINNER_HEIGHT, image.size.width, image.size.height);
            [questioncell addSubview:attentionbtn];
            [attentionbtn addTarget:self action:@selector(onAttention) forControlEvents:UIControlEventTouchUpInside];
            [attentionbtn setTitleColor:[UIColor colorWithRed:58.0/255.0f green:130.0/255.0f blue:15.0/255.0f alpha:1] forState:UIControlStateNormal];
            [attentionbtn setTitleColor:[UIColor colorWithRed:58.0/255.0f green:130.0/255.0f blue:15.0/255.0f alpha:1] forState:UIControlStateHighlighted];

            akbtn = [[AKButton alloc]initWithFrame:CGRectMake(10.0, h-image.size.height-SPINNER_HEIGHT, 95.0, image.size.height)];
            akbtn.delegate = self;
            [akbtn setAKButtonStatus:isOpen];
            [questioncell addSubview:akbtn];
        
            UIView *answer_bg = [[UIView alloc]initWithFrame:CGRectMake(0.0, CGRectGetMaxY(blankview.frame), 320.0, 115.0)];
            answer_bg.backgroundColor = UIColorRGB(0xf5f5f5);
            answer_bg.tag = 2014;
        
            CGRect frame1 = CGRectMake(10.0, SPINNER_HEIGHT,300.0,75.0);
            bg_view = [[UIView alloc]initWithFrame:frame1];
            bg_view.backgroundColor = [UIColor whiteColor];
            bg_view.layer.cornerRadius = 2.0;
            bg_view.layer.borderWidth = 1.0;
            bg_view.layer.borderColor = [UIColor colorWithRed:195/255.0 green:195/255.0 blue:195/255.0 alpha:1.0].CGColor;
            bg_view.layer.shadowColor   = [UIColor colorWithRed:195/255.0 green:195/255.0 blue:195/255.0 alpha:1.0].CGColor;
            [answer_bg addSubview:bg_view];
            
            textanswer = [[UITextView alloc] initWithFrame:CGRectMake(10.0, SPINNER_HEIGHT,300.0,75.0 - 27.0)];
            textanswer.font = [UIFont systemFontOfSize:12.0];
            textanswer.backgroundColor = [UIColor clearColor];
            textanswer.autocorrectionType = UITextAutocorrectionTypeNo;
            textanswer.keyboardType = UIKeyboardTypeDefault;
            textanswer.returnKeyType = UIReturnKeyDone;
            //textFieldFeedback.clearButtonMode = UITextFieldViewModeWhileEditing;	// has a clear 'x' button to the right
            textanswer.delegate = self;
            [answer_bg addSubview:textanswer];
            
            words_Num = [[UILabel alloc]initWithFrame:CGRectMake(CGRectGetMaxX(bg_view.frame) - 130.0, CGRectGetMaxY(bg_view.frame) - 28.0, 125.0, 25.0)];
            words_Num.backgroundColor = [UIColor clearColor];
            words_Num.font = [UIFont systemFontOfSize:12.0];
            words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
            words_Num.text = I(@"还能输入500字");
            words_Num.textAlignment = UITextAlignmentRight;
            [answer_bg addSubview:words_Num];
            
            //image for loading photo
            imageView1 = [[UIImageView alloc]initWithFrame:CGRectMake(CGRectGetMinX(bg_view.frame) + 8.0, CGRectGetMaxY(bg_view.frame) - 28.0, 22.0, 22.0)];
            imageView1.backgroundColor = [UIColor clearColor];
            imageView1.contentMode = UIViewContentModeScaleAspectFit;
            imageView1.layer.shadowOpacity = 0.3;
            imageView1.layer.cornerRadius = 4.0;
            imageView1.layer.masksToBounds = YES;
            imageView1.layer.shadowColor = [UIColor colorWithWhite:0.0 alpha:0.5].CGColor;
            imageView1.userInteractionEnabled = YES;
            [imageView1.layer setShadowOffset:CGSizeMake(0, 1)];
            UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(ShowImageView)];
            [imageView1 addGestureRecognizer:tap];
            [answer_bg addSubview:imageView1];
            
            //photo button
            photo_btn = [[UIButton alloc]initWithFrame:CGRectMake(CGRectGetMinX(bg_view.frame) + SPINNER_HEIGHT, CGRectGetMaxY(bg_view.frame) + SPINNER_HEIGHT, 27.0, 27.0)];
            [photo_btn setImage:[UIImage imageNamed:@"photo_normal"] forState:UIControlStateNormal];
            [photo_btn setImage:[UIImage imageNamed:@"photo_select"] forState:UIControlStateHighlighted];
            [photo_btn setBackgroundColor:[UIColor clearColor]];
            [photo_btn addTarget:self action:@selector(uploadimage:) forControlEvents:UIControlEventTouchUpInside];
            [answer_bg addSubview:photo_btn];
            
            if (!anonymity_btn) {
                anonymity_btn= [[CheckBoxButton alloc] initWithFrame:CGRectMake(181.0, CGRectGetMaxY(bg_view.frame) + SPINNER_HEIGHT, 80.0, 27.0)];
                anonymity_btn.CheckType = 1;
                
                anonymity_btn.Check = NO;
            }
            [anonymity_btn setTitle:I(@"匿名")];
            [anonymity_btn setColor:UIColorRGB(0x999999)];
            [answer_bg addSubview:anonymity_btn];

            
            UIButton *submit_btn = [[UIButton alloc]initWithFrame:CGRectMake(251.0, CGRectGetMaxY(bg_view.frame) + SPINNER_HEIGHT, 59.0, 28.0)];
            [submit_btn setBackgroundImage:[UIImage imageNamed:@"submit_normal"] forState:UIControlStateNormal];
            [submit_btn setBackgroundImage:[UIImage imageNamed:@"submit_select"] forState:UIControlStateHighlighted];
            [submit_btn setTitle:I(@"提交") forState:UIControlStateNormal];
            [submit_btn.titleLabel setFont:[UIFont systemFontOfSize:13]];
            [submit_btn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
            [submit_btn addTarget:self action:@selector(commitanswer) forControlEvents:UIControlEventTouchUpInside];
            [answer_bg addSubview:submit_btn];
            
            UIView* blankview1 = [[UIView alloc] init];
            blankview1.frame = CGRectMake(0, CGRectGetMaxY(submit_btn.frame) + SPINNER_HEIGHT,self.tableviewlist.bounds.size.width,5);
            blankview1.backgroundColor = UIColorRGB(0xe7e7e7);
            blankview1.layer.shadowColor=[UIColor blackColor].CGColor;
            blankview1.layer.shadowOffset=CGSizeMake(0,-1);
            blankview1.layer.shadowOpacity=0.4;
            blankview1.layer.shadowRadius=0;
            blankview1.layer.shadowPath = [UIBezierPath bezierPathWithRect:blankview.bounds].CGPath;
            [answer_bg addSubview:blankview1];
            

            [questioncell addSubview:answer_bg];
            answer_bg.hidden = YES;
            if (isOpen) {
                answer_bg.hidden = NO;
                blankview.backgroundColor = UIColorRGB(0xf5f5f5);
            }
            else{
                answer_bg.hidden = YES;
                blankview.backgroundColor = UIColorRGB(0xe7e7e7);
            }

            //shade view
            shadeView = [[UIView alloc]initWithFrame:CGRectMake(CGRectGetMaxX(akbtn.frame), 0.0, 140.0, h)];
            shadeView.backgroundColor = [UIColor clearColor];
            shadeView.hidden = YES;
            UITapGestureRecognizer *shade_tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(didTapShadeView)];
            [shadeView addGestureRecognizer:shade_tap];
            [questioncell addSubview:shadeView];

			questioncell.accessoryType = UITableViewCellAccessoryNone;
			questioncell.selectionStyle = UITableViewCellSelectionStyleNone;
		}
        else
        {
            //点击添加关注或者取消关注后页面需要刷新显示当前关注人数
            CMQuestionTableViewCell *view = (CMQuestionTableViewCell *)[questioncell viewWithTag:2013];
            [view setcellinfo:curqaItem webimage:m_pWebImage shareimage:nil index:indexPath.row];
            UIView *answer_bg = [questioncell viewWithTag:2014];
            
            //打开关闭回答框时，更改分割blankview的backgroundColor
            if (isOpen)
            {
                answer_bg.hidden = NO;
                UIView *blankview = [questioncell viewWithTag:2022];
                blankview.backgroundColor = UIColorRGB(0xf5f5f5);
            }
            else
            {
                answer_bg.hidden = YES;
                UIView *blankview = [questioncell viewWithTag:2022];
                blankview.backgroundColor = UIColorRGB(0xe7e7e7);
            }
        }
        
		if(curqaItem.nAttention)//已经关注
		{
            [attentionbtn setTitle:I(@"取消关注") forState:UIControlStateNormal];
            [attentionbtn setTitle:I(@"取消关注") forState:UIControlStateHighlighted];

            [attentionbtn setTitleColor:UIColorRGB(0x307f00) forState:UIControlStateNormal];

            [attentionbtn.titleLabel setFont:[UIFont systemFontOfSize:14.0]];

			[attentionbtn setBackgroundImage:[UIImage imageNamed:@"cancelattention_n"] forState:UIControlStateNormal];
			[attentionbtn setBackgroundImage:[UIImage imageNamed:@"cancelattention_p"] forState:UIControlStateHighlighted];				
		}
		else
		{
            [attentionbtn setTitle:I(@"关注") forState:UIControlStateNormal];
            
            [attentionbtn setTitle:I(@"关注") forState:UIControlStateHighlighted];

            [attentionbtn setTitleColor:UIColorRGB(0x307f00) forState:UIControlStateNormal];
            
            [attentionbtn.titleLabel setFont:[UIFont systemFontOfSize:14.0]];
			[attentionbtn setBackgroundImage:[UIImage imageNamed:@"cancelattention_n"] forState:UIControlStateNormal];
			[attentionbtn setBackgroundImage:[UIImage imageNamed:@"cancelattention_p"] forState:UIControlStateHighlighted];				
		}
		return questioncell;
		
	}   
	
	int row = indexPath.row;
    
    // 如果有多个答案，需减去row为0的 questiondetail，row为1的回答标题
	row--;
    row--;
	if (row == (m_pQuestionDetail->HasAnswerFlag() ? m_pQuestionDetail->GetItemCount()+1:m_pQuestionDetail->GetItemCount()))
		return [super tableView:tableView cellForRowAtIndexPath:indexPath];
	
    CMAnswerTableViewCell *cell = [[CMAnswerTableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kCellIdentifier] ;
    
	TAnswerItem answerItem;

    if (indexPath.row == 1) {
        CellAnswerTitleCell *cell_title = [[CellAnswerTitleCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:@"Cell_title"] ;
        
        if(m_pQuestionDetail->HasAnswerFlag()){
            cell_title.imageView.image = [UIImage imageNamed:@"bestanswer"];
            cell_title.label.text = I(@"最佳答案");
        }
        else{
            cell_title.imageView.image = [UIImage imageNamed:@"answer"];
            cell_title.label.text = I(@"答案");
        }
        cell_title.label.font = [UIFont boldSystemFontOfSize:15.0];
        cell_title.label.textColor = [UIColor colorWithRed:181/255.0 green:181/255.0 blue:181/255.0 alpha:0.95];
        return cell_title;
    }
    cell.LeftImageView.image = [UIImage imageNamed:@"user_image"];
    cell.contentView.backgroundColor = UIColorRGB(0xe7e7e7);
	 if(m_pQuestionDetail->HasAnswerFlag() && row == 0)
	{
		m_pQuestionDetail->GetHasFlagAnswerItem(answerItem);

          int width = self.tableviewlist.bounds.size.width-10;
          UIImage *image = [UIImage imageNamed:@"bestanswer"];
          width -= image.size.width;

          double h = [self GetCellHeight:answerItem width:width shareImage:nil];
            UIView* blankview = [[UIView alloc] init];
            blankview.frame = CGRectMake(10.0, h,self.tableviewlist.bounds.size.width - 20.0,5);
            blankview.backgroundColor = UIColorRGB(0xe7e7e7);
            blankview.layer.shadowColor=[UIColor blackColor].CGColor;
            blankview.layer.shadowOffset=CGSizeMake(0,-1);
            blankview.layer.shadowOpacity=0.4;
            blankview.layer.shadowRadius=0;
            blankview.layer.shadowPath = [UIBezierPath bezierPathWithRect:blankview.bounds].CGPath;
   
        
            [cell addSubview:blankview];
        
        
        //其他答案title cell
        if (m_pQuestionDetail->GetItemCount() > 0) {
            UIView *otheranswer_v = [[UIView alloc]initWithFrame:CGRectMake(10.0, CGRectGetMaxY(blankview.frame),self.tableviewlist.bounds.size.width - 20.0,33.0)];
            otheranswer_v.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"cell_title_bg"]];
        
            UIImageView *imageView = [[UIImageView alloc]initWithFrame:CGRectMake(10.0, 6.0, 21.0, 21.0)];
            imageView.backgroundColor = [UIColor clearColor];
            imageView.image = [UIImage imageNamed:@"otheranswer"];
            [otheranswer_v addSubview:imageView];
            
           UILabel *label = [[UILabel alloc]initWithFrame:CGRectMake(41.0, 0.0, 100.0, 33.0)];
            label.backgroundColor = [UIColor clearColor];
            label.text = I(@"其他回答");
            label.textColor = [UIColor colorWithRed:181/255.0 green:181/255.0 blue:181/255.0 alpha:0.95];
            label.font = [UIFont boldSystemFontOfSize:15.0];
            [otheranswer_v addSubview:label];
        
            [cell addSubview:otheranswer_v];
        }
        
        cell.btnLike.tag = row;
	}
	else
	{
        cell.btnLike.tag = row;

		if(m_pQuestionDetail->HasAnswerFlag())
			row--;
		if(m_pQuestionDetail->GetItemCount() > 0 && row == 0)
		{
		}
		m_pQuestionDetail->GetItem(row, answerItem);

	}
    

    
    if(!m_pQuestionDetail->HasAnswerFlag()&&_stricmp(curqaItem.sQuestioner_username.c_str(),SETTING.GetUserName())== 0 && (_stricmp(answerItem.GetAnswerItemUserName(),SETTING.GetUserName()) != 0 || curqaItem.bIsanonymity))
    {
        
        [cell.btnSetBest addTarget:self action:@selector(doSetBest:event:) forControlEvents:UIControlEventTouchUpInside];
        
        NSString *best_str = [NSString stringWithFormat:@"1%d",row];
        NSUInteger best_tag = [best_str integerValue];
        cell.btnSetBest.tag = best_tag;
        cell.btnSetBest.hidden = NO;
        isHiddenBestbtn = NO;
        
    }
    else
    {
        cell.btnSetBest.hidden = YES;
        [cell.btnSetBest removeFromSuperview];
        isHiddenBestbtn = YES;
    }
    
    NSUInteger like_sep = answerItem.nIsliked;
    if (like_sep == 1) {
        [cell setBtnLikeHighlighted:YES];
    }
    else{
        [cell setBtnLikeHighlighted:NO];
    }
    [cell.btnLike addTarget:self action:@selector(doLike:event:) forControlEvents:UIControlEventTouchUpInside];
    
    NSString *image_str = [NSString stringWithFormat:@"2%d",row];
    NSUInteger image_tag = [image_str integerValue];
    cell.showImageView.tag = image_tag;
   

	[self SetCellInfo:cell item:answerItem shareImage:nil];
    
    [cell.showImageView addTarget:self action:@selector(pressImg:event:) forControlEvents:UIControlEventTouchUpInside];
    return cell;
}
-(void)pressImg:(id)sender event:(id)event
{
    
    NSSet *touches =[event allTouches];
    UITouch *touch =[touches anyObject];
	CGPoint touchPoint=[touch locationInView:self.tableviewlist];
    
    NSInteger select=[self.tableviewlist indexPathForRowAtPoint:touchPoint].row;
    select -= 2;
    UIButton *btn = (UIButton *)sender;
    NSString *image_str = [NSString stringWithFormat:@"%d",btn.tag];
    NSString *image_tag = [image_str substringFromIndex:1];
    NSUInteger row = [image_tag integerValue];

    
    TAnswerItem answerItem;
    if(m_pQuestionDetail)
    {
        if (m_pQuestionDetail->HasAnswerFlag() && select == 0) {
            if (m_pQuestionDetail->GetHasFlagAnswerItem(answerItem)){
               NSString *url = [NSString stringWithUTF8String:answerItem.GetAnswerItemPicurl()];
            if(answerItem.GetAnswerItemPicurl() && answerItem.GetAnswerItemPicurl() != '\0' && ![url isEqualToString:@""])
            {
                [self ShowImageView:url thumbView:[NSString stringWithUTF8String:answerItem.GetAnswerItemThumburl()]];
            }
            }
        }
       if(m_pQuestionDetail->GetItem(row, answerItem))
       {
           NSString *url = [NSString stringWithUTF8String:answerItem.GetAnswerItemPicurl()];
           if(answerItem.GetAnswerItemPicurl() && answerItem.GetAnswerItemPicurl() != '\0' && ![url isEqualToString:@""])
           {
               [self ShowImageView:url thumbView:[NSString stringWithUTF8String:answerItem.GetAnswerItemThumburl()]];
           }
       }    
    }
    
}

-(void)pressQuestionImg:(id)sender event:(id)event
{
            NSString *url = [NSString stringWithUTF8String:curqaItem.sPic_url.c_str()];
            if(curqaItem.sPic_url.c_str() && curqaItem.sPic_url.c_str() != '\0' && ![url isEqualToString:@""])
            {
                [self ShowImageView:url thumbView:[NSString stringWithUTF8String:curqaItem.sThumburl.c_str()]];
            }
    
}



- (void)didSelectButtonControl:(NSSet *)touches withEvent:(UIEvent *)event{

    point = self.tableviewlist.contentOffset;

    if (akbtn.isOpen) {
        isOpen = NO;
        akbtn.isOpen = NO;
        shadeView.hidden = YES;
        [self.tableviewlist reloadData];
    }
    else{
        isOpen = YES;
        akbtn.isOpen = YES;
        shadeView.hidden = NO;
        [self.tableviewlist reloadData];
        [textanswer becomeFirstResponder];
    }
}

-(void)doLike:(id)sender event:(id)event
{
    if(CMGlobal::TheOne().IsOffline())
        return;
    
    UIButton *btn = (UIButton *)sender;
   //根据tag 判断点击对象
    NSInteger row = btn.tag;
    
	if(row == (m_pQuestionDetail->HasAnswerFlag() ? m_pQuestionDetail->GetItemCount()+1:m_pQuestionDetail->GetItemCount()))
		return;
	TAnswerItem anItem;
	if(m_pQuestionDetail->HasAnswerFlag() && row == 0)
		m_pQuestionDetail->GetHasFlagAnswerItem(anItem);
	else
	{
		if(m_pQuestionDetail->HasAnswerFlag())
			row--;
		m_pQuestionDetail->GetItem(row, anItem);
	}

    if(!m_pOneAnswerRatingListener)
        m_pOneAnswerRatingListener = new CMAnswerDetailRatingListener();
    
    CMAnswerTableViewCell *cell;
    for (UIView* next = [[sender superview] superview]; next; next = next.superview) {
        if ([next isKindOfClass:[CMAnswerTableViewCell class]]) {
            cell = (CMAnswerTableViewCell*)next;
            break;
        }
    }
    
    NSUInteger likes = [cell.lblike.text integerValue];
    likes ++;
    [cell setBtnLikeHighlighted:YES];
    cell.lblike.text = [NSString stringWithFormat:@"%d",likes];
    anItem.nIsliked = 1;
    anItem.nPV = likes;
    m_pQuestionDetail->Update(anItem);
    if(!m_pQuestionDetail->LikeAnswer(curqaItem.sID.c_str(), anItem.GetAnswerItemID()))
    {
        [tool CancelWait];
    }
    
}
- (void)ShowImageView{
    //获取当前view的响应接受者
    UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]]) {
			break;
		}
	}
	if(!nextResponder)
		return;
    
    CMImageDetailViewControl *cmimageController = [[CMImageDetailViewControl alloc]init];
    cmimageController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    cmimageController.isURL = NO;
    [cmimageController setImage:imageView1.image];
    [((UIViewController*)nextResponder) presentModalViewController:cmimageController animated:YES];

}


- (void)ShowImageView:(NSString*)url thumbView:(NSString *)thumburl{
    //获取当前view的响应接受者
    UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]]) {
			break;
		}
	}
	if(!nextResponder)
		return;
    
    CMImageDetailViewControl *cmimageController = [[CMImageDetailViewControl alloc]init];
    cmimageController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    cmimageController.isURL = YES;
    [cmimageController setCMImageURL:url thumbURL:thumburl];
    [((UIViewController*)nextResponder) presentModalViewController:cmimageController animated:YES];
    
}


-(void)uploadimage:(id)sender
{
    UIActionSheet *action = [[UIActionSheet alloc] initWithTitle:I(@"添加图片")
                                                        delegate:self
                                               cancelButtonTitle:I(@"取消")
                                          destructiveButtonTitle:nil
                                               otherButtonTitles:I(@"相册"),I(@"拍照"), nil];
    [action showInView:self];
    
}

- (void)gotoPhoto{
    UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]]) {
			break;
		}
	}
	if(!nextResponder)
		return;
    
    try {
        UIImagePickerControllerSourceType sourceType = UIImagePickerControllerSourceTypeCamera;
        if ([UIImagePickerController isSourceTypeAvailable: UIImagePickerControllerSourceTypeCamera]) {
            UIImagePickerController *picker = [[UIImagePickerController alloc] init];
            picker.delegate = self;
            //问题回答上传用原图，不允许编辑
            picker.allowsEditing = NO;
            picker.sourceType = sourceType;
            [(UIViewController *)nextResponder presentModalViewController:picker animated:YES];
        }
        else
        {
            UIAlertView *alert = [[UIAlertView alloc]
                                  initWithTitle:@"Error accessing photo library"
                                  message:@"Device does not support a photo library"
                                  delegate:nil
                                  cancelButtonTitle:@"ok!"
                                  otherButtonTitles:nil];
            [alert show];
        }
    } catch (NSException *exception) {
        UIAlertView *alert = [[UIAlertView alloc]initWithTitle:I(@"错误") message:I(@"打开相机失败") delegate:self cancelButtonTitle:I(@"确定") otherButtonTitles:nil];
        [alert show];
    }
}

- (void)gotoPicture{
    UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]]) {
			break;
		}
	}
	if(!nextResponder)
		return;
    
    UIImagePickerController *picker =[[UIImagePickerController alloc] init];
    //问题回答上传用原图，不允许编辑
    picker.allowsEditing = NO;
    picker.delegate = self;
    picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    
    if (__iOS7)
    {
      //  [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
        MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
        appDelegate.window.tintColor = [UIColor whiteColor];
    }
    [((UIViewController*)nextResponder)  presentModalViewController:picker animated:YES];
    
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) {
        [self gotoPicture];
    }
    else if (buttonIndex == 1){
        [self gotoPhoto];
    }
}

#pragma mark UIImagePickerControllerDelegate
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
    UIImage* oralImg=[info objectForKey:UIImagePickerControllerOriginalImage];
    
    double image_w = oralImg.size.width;
    double image_h = oralImg.size.height;
    
    if (image_h < kImgUploadSizeMax && image_w < kImgUploadSizeMax) {
        ;
    }
    else{
        double wide_per = image_w/kImgUploadSizeMax;
        double height_per = image_h/kImgUploadSizeMax;
        if (wide_per >= height_per) {
            image_w = kImgUploadSizeMax;
            image_h = image_h / wide_per;
        }
        else{
            image_h = kImgUploadSizeMax;
            image_w = image_w / height_per;
        }
        oralImg = [self scaleFromImage:oralImg toSize:CGSizeMake(image_w, image_h)];
    }
    //保存到本地
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString *cachesDir = [paths objectAtIndex:0];
    // concatenate the file name "contacts" to the end of the path
    
    imagepath =[[cachesDir stringByAppendingPathComponent:@"temp.png"] copy];
    
    NSError* err=nil;
    
    if(![UIImageJPEGRepresentation(oralImg,0.8) writeToFile:imagepath options:NSDataWritingAtomic error:&err])
        NSLog(@"err%@",err);
    imageView1.image = nil;
    imageView1.image = oralImg;
    imageView1.hidden = NO;
    
    [picker dismissModalViewControllerAnimated:YES];
    
    if (__iOS7)
    {
     //   [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
        
        MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
        appDelegate.window.tintColor = UIColorRGB(0x1a6cc3);
    }
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
	[picker dismissModalViewControllerAnimated:YES];
    
    if (__iOS7)
    {
      //  [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent animated:YES];
        
        MLPlayerAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
        appDelegate.window.tintColor = UIColorRGB(0x1a6cc3);
    }
}

- (UIImage *) scaleFromImage: (UIImage *) image toSize: (CGSize) size
{
    UIGraphicsBeginImageContext(size);
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}
#pragma mark - addLike setBest

-(void)doSetBest:(id)sender event:(id)event
{

    UIButton *btn = (UIButton *)sender;
    NSString *best_str = [NSString stringWithFormat:@"%d",btn.tag];
    NSString *best_tag = [best_str substringFromIndex:1];
    NSUInteger row = [best_tag integerValue];
    
    
	if(row == (m_pQuestionDetail->HasAnswerFlag() ? m_pQuestionDetail->GetItemCount()+1:m_pQuestionDetail->GetItemCount()))
		return;
	//TAnswerItem answerItem;
	if(m_pQuestionDetail->HasAnswerFlag() && row == 0)
		m_pQuestionDetail->GetHasFlagAnswerItem(answeritem);
	else
	{
		if(m_pQuestionDetail->HasAnswerFlag())
			row--;
		m_pQuestionDetail->GetItem(row, answeritem);
	}
    
    if(!m_pQuestionDetail->SetBestAnswer(curqaItem.sID.c_str(), answeritem.GetAnswerItemID()))
    {
    }
}

-(void)onAttention
{
    if(!m_pQuestionRatingListener)
        m_pQuestionRatingListener = new CMQuestionRatingListener();
    
    if( !m_pQalist )
    {
        m_pQalist = new CMQAList();
    }
    
    m_pQalist->SetListener(nil,nil,m_pQuestionRatingListener);
    m_pQalist->SetUserData((__bridge void*)self);
    
    if(!m_pQalist->AttentionQuestion(curqaItem.sID.c_str()))
        ;
}

-(void)showAttentionErr
{    
	if(curqaItem.nAttention)
		[tool ShowAlert:I(@"取消关注失败")];
	else
		[tool ShowAlert:I(@"加关注失败")];
}

- (void)didTapShadeView{
    [textanswer resignFirstResponder];
}

- (void)didAnswerImageView:(UIImageView *)imageview{
    UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]]) {
			break;
		}
	}
	if(!nextResponder)
		return;
    
    CMImageDetailViewControl *cmimageController = [[CMImageDetailViewControl alloc]init];
    [cmimageController setImage:imageview.image];
    cmimageController.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    cmimageController.isURL = YES;
    [((UIViewController*)nextResponder)  presentModalViewController:cmimageController animated:YES];
    
}

- (void)webImageManager:(SDWebImageManager *)imageManager didFinishWithImage:(UIImage *)image
{
    if(self.tableviewlist)
        [self.tableviewlist reloadData];
}


-(void)SetCellInfo:(CMAnswerTableViewCell*)cell item:(TAnswerItem&)answerItem shareImage:(CMWebImage*)shareimage
{
	CGRect cellFrame = [cell frame];
    NSString *url = [NSString stringWithUTF8String:answerItem.GetAnswerItemThumburl()];
    if(answerItem.GetAnswerItemThumburl() && answerItem.GetAnswerItemThumburl() != '\0' && ![url isEqualToString:@""])
    {
        SDWebImageManager *manager = [SDWebImageManager sharedManager];
        UIImage *cachedImage =[[SDImageCache sharedImageCache] imageFromMemoryCacheForKey:[NSString stringWithUTF8String:answerItem.GetAnswerItemThumburl() ]];// 将需要缓存的图片加载进来
        if (cachedImage) {
            // 如果Cache命中，则直接利用缓存的图片进行有关操作
            [cell.showImageView setImage:cachedImage forState:UIControlStateNormal];
        } else {
            // 如果Cache没有命中，则去下载指定网络位置的图片，并且给出一个委托方法
            // Start an async download
         //   [manager downloadWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:answerItem.GetAnswerItemThumburl()]] delegate:self];
            __weak typeof(self) blockSelf = self;
            [manager downloadImageWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:answerItem.GetAnswerItemThumburl()]] options:0 progress:nil completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType, BOOL finished, NSURL *imageURL) {
                if (!blockSelf) {
                    return ;
                }
                dispatch_main_sync_safe(^{
                    if (image) {
                        if(blockSelf.tableviewlist)
                            [blockSelf.tableviewlist reloadData];
                    }
                });
            }];
            [cell.showImageView setImage:[UIImage imageNamed:@"placeholder_loading"] forState:UIControlStateNormal];
        }
	}
    
	cell.lbname.text = [NSString stringWithUTF8String:answerItem.GetAnswerItemFullName()];
	cell.lbpubdate.text=[NSString stringWithUTF8String:answerItem.GetAnswerItemPubdate()];
	cell.lblike.text = [NSString stringWithFormat:@"%d",answerItem.nPV];
	cell.lbanswer.text = [NSString stringWithUTF8String:answerItem.GetAnswerItemAnswer()];
	[cell setFrame:cellFrame];
	cell.accessoryType = UITableViewCellAccessoryNone;
	cell.selectionStyle = UITableViewCellSelectionStyleNone;
}



-(CGFloat)GetCellHeight:(TAnswerItem&)answerItem width:(int)width shareImage:(CMWebImage *)shareimage
{
	CGFloat hg = 0 ;
    CGFloat img_h = 0.0;
	CGFloat blank = 5;

    NSString *url = [NSString stringWithUTF8String:answerItem.GetAnswerItemPicurl()];
    if(answerItem.GetAnswerItemPicurl() && answerItem.GetAnswerItemPicurl() != '\0' && ![url isEqualToString:@""])
    {
        img_h = SHARE_IMAGE_HEIGHT;
    }
    
	blank += 5;
	NSString *cellText = [NSString stringWithUTF8String:answerItem.GetAnswerItemAnswer()];
    

	hg = MAX(hg+10,[self GetHeight:width-blank text:cellText]+30);

	return hg+25 + img_h + 5.0;

}
-(CGFloat)GetHeight:(int)width text:(NSString*)stxt
{
	UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
	CGSize constraintSize = CGSizeMake(width, MAXFLOAT);
	CGSize labelSize = [stxt sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];
	return labelSize.height;	
}

#pragma mark - Public method


-(void)Refresh
{
    if (akbtn.isOpen) {
        isOpen = NO;
        akbtn.isOpen = NO;
    }
    else{
        isOpen = YES;
        akbtn.isOpen = YES;
        [textanswer becomeFirstResponder];
    }
    textanswer.text = @"";
    [akbtn CloseAnimaon];
}

-(void)setAnswer:(BOOL)show{
  //  [textanswer becomeFirstResponder];
}


#pragma mark - UITextViewDelegate
-(void)commitanswer
{
    //去除开头和结尾的空格
    NSString *strAnswer = [textanswer.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
	if([strAnswer length] <= 0 || textanswer.tag == 1)
	{
		[tool ShowAlert:I(@"请输入回答!")];//@"请输入回答."
		return;
	}
    if (isBeyond) {
        [tool ShowAlert:words_Num.text];
        return;
    }
    if (CMGlobal::TheOne().IsOffline())
    {
        [tool ShowError:-1];
        return;
    }
    
	[textanswer endEditing:YES];
    
	if(!m_pQalist)
	{
		m_pQalist = new CMQAList();
	}
    
    CMFileInfo *file = new CMFileInfo();
    [[GlobalAlertCenter sharedAlertCenter] setType:@"answerquestion"];
    CMFileUpload::GetInstance()->SetListener([[GlobalAlertCenter sharedAlertCenter] GetCallBack]);
    CMFileUpload::GetInstance()->SetUserData((__bridge void*)[GlobalAlertCenter sharedAlertCenter]);
    
    [tool ShowActivityIndicator:self];
    file->AnswerQuestion(curqaItem.sID.c_str(), anonymity_btn.Check, [textanswer.text UTF8String], [imagepath UTF8String]);

    
    if (CMFileUpload::GetInstance()->Append(*file) >= 0)
    {
        [self SetPlaceholder];
        anonymity_btn.Check = NO;
        self.imageView1.hidden = YES;
        self.imageView1.image = nil;
        self.imagepath = nil;
    }
}

-(void)SubmitFaild
{
    [tool DisimissActivityIndicator];
}

- (BOOL)textViewShouldBeginEditing:(UITextView *)textView
{
    shadeView.hidden = NO;
    CGPoint point_ = [textanswer convertPoint:textanswer.center toView:self.window];

    point_view.y = point_.y-30.0;

	if(textanswer.tag == 1)
	{
		textanswer.text = @"";
		textanswer.tag = 2;
		textanswer.textColor = [UIColor blackColor];
	}
	
	return YES;
}

- (void)textViewDidEndEditing:(UITextView *)textView{
    shadeView.hidden = YES;
}

- (void)textViewDidChange:(UITextView *)textView
{
    input_words_num = [textView.text length];
    if (input_words_num <= kTextMaxLength) {
        NSUInteger Remaining_words = kTextMaxLength - input_words_num;
        words_Num.textColor = [UIColor colorWithRed:167/255.0 green:167/255.0 blue:167/255.0 alpha:1.0];
        isBeyond = NO;
        words_Num.text = [NSString stringWithFormat:I(@"还能输入%d个字"),Remaining_words];
    }
    else{
        NSUInteger Beyond_words = input_words_num - kTextMaxLength;
        words_Num.textColor = [UIColor redColor];
        isBeyond = YES;
        words_Num.text = [NSString stringWithFormat:I(@"超出%d个字"),Beyond_words];
    }

}

-(void)SetPlaceholder
{
	textanswer.textColor = [UIColor lightGrayColor];
	textanswer.text = @"";// @"回答不超过140个字";
    words_Num.text = I(@"还能输入500字");
	textanswer.tag = 1;
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
	if([text isEqualToString:@"\n"])
	{
		[textanswer endEditing:YES];
		if(textanswer.text.length == 0)
			[self SetPlaceholder];
		return NO;
	}

	return YES;
}

-(void) LoadData
{
    
    //关闭再推送
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@"0" forKey:kUDOpenPush];

	if(questionid == nil || [questionid length] <= 0)
		return;
    
    
  //  UITableViewCell* cell=[self.tableviewlist cellForRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0]];
    
    
  //  [tool ShowActivityIndicator:self.tableviewlist at:CGPointMake(UI_IOS_WINDOW_WIDTH/2-20, cell.frame.size.height+5)];
    [tool ShowActivityIndicator:self];
	if(m_pQuestionDetail->GetDetail([questionid UTF8String]))
	{
	//	[self GetBrowserList];
	}
}

-(void)GetBrowserList
{
    if(m_pQuestionDetail)
        [self setHasMore:!m_pQuestionDetail->IsEnd()];
    [super GetBrowserList];
}

-(void)SetWegImage:(CMWebImage*)webimage
{
	m_pWebImage = webimage;
}

-(void)setQuestionDetail:(CMQuestionDetail*)pQuestionDetail
{
	m_pQuestionDetail = pQuestionDetail;
}

-(void)RefreshList
{
	[self LoadData];
}

-(BOOL)RefreshMore
{
	if([self HasMore])
    {
		return m_pQuestionDetail->RequestMore();
    }
    
    return NO;
}

-(void)SetQuestionItem:(TQAItem&)item
{
	curqaItem = item;
}

-(void)AttentionSuccess
{
	curqaItem.nAttention = !curqaItem.nAttention;
    curqaItem.nPV = curqaItem.nAttention ? curqaItem.nPV += 1: curqaItem.nPV -= 1;
}

-(int) AttentionStatus
{
	return curqaItem.nAttention;
}

-(void)txtanswerResignFirstResponder{
    if (textanswer) {
        [textanswer resignFirstResponder];
    }
}


- (void)dealloc
{
   
    if(m_pQuestionDetail){
        m_pQuestionDetail->Cancel();
    }
    SAFEDELETE(m_pQuestionDetail);
    
    if (m_pQalist) {
        m_pQalist->Cancel();
    }
    
	SAFEDELETE(m_pQuestionRatingListener);
    SAFEDELETE(m_pOneAnswerRatingListener);
    SAFEDELETE(m_pAnswerBestUpdateListener);
    SAFEDELETE(m_pAnswerUpdateListener);
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillHideNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self];


	
}
@end
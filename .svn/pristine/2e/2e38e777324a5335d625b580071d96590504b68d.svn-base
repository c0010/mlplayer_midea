    //
//  CMClassInfoControl.m
//  MLPlayer
//
//  Created by sunjj on 11-9-20.
//  Copyright 2011 w. All rights reserved.
//

#import "CMClassInfoControl.h"
#import "CMNavgateItem.h"
#import <CoreText/CoreText.h>
#import "CMMarkViewController.h"
#import "SDWebImage/UIButton+WebCache.h"
#import "CMBrowserControl.h"

#define kCellIdentifier @"com.apple.CMClassInfoControl.CellIdentifier"
#pragma mark operator



@implementation NSString(TRIM)


- (NSString *)trimString {
    NSMutableString *mStr = [self mutableCopy];
    CFStringTrimWhitespace((CFMutableStringRef)mStr);
    
#if ! __has_feature(objc_arc)
    NSString *result = [[mStr copy] autorelease];
#else
    NSString *result = [mStr copy];
#endif
    
    CMRELEASE(mStr);
    return result;
}

@end

@implementation CMClassInfoControl
@synthesize lbclassName=_lbclassName;
@synthesize courseName=_courseName;
@synthesize infoBack=_infoBack;
@synthesize arrowHead=_arrowHead;
@synthesize infoBtn=_infoBtn;
@synthesize infoBackBtn=_infoBackBtn;
@synthesize classInfoCell;
@synthesize nindex;
@synthesize TableViewList,sImage,lblviewtl,lbllike,lblcredit,lblcredittl,btnlike,lblview;
@synthesize setid,nModel;
@synthesize btnMark;
@synthesize txtcontent;
-(void)gotoDown
{
    if (item == NULL) {    //修复当还没刷新到数据时点击下载会崩的bug  ＃廖宏兴
        return;
    }
    
	if(item->bEnabledownload)
	{
        //Append为－1时 表示添加到下载队列失败 >=0表示其在下载队列中的排序号
		if(CMCourseDownload::GetInstance()->Append(*m_CourseInfo) >= 0)
			[tool ShowAlert:I(@"已开始下载")];
	}
    else
    {
        [tool ShowAlert:I(@"此课程不支持下载!")];
    }
    
}


//-(void)gotoPlay:(id)sender
//{		
//	;
//}


-(BOOL)gotoFavorite
{
    int returnvalue;
    
    BOOL ret=NO;
    
    if (item == NULL) {     //修复当还没刷新到数据时点击收藏会崩的bug  ＃廖宏兴
        return ret;
    }

    int pos=CMFavorites::GetInstance()->IsAdded(item->sFlag,item->sID);
    
    if(pos>=0)
    {//已添加到收藏，则取消收藏
        
        ret=YES;
        returnvalue = CMFavorites::GetInstance()->RemoveItem(pos);
        
        if (returnvalue) {
            [tool ShowAlert:I(@"取消收藏成功")];
            ret=NO;
            return  ret;
      
        }else {
            [tool ShowAlert:I(@"取消收藏失败")];
            return ret;
        }
        
    }else
    {
        //未添加到收藏，则收藏
        ret=NO;
        
        returnvalue = CMFavorites::GetInstance()->AddFavorite(*item);
        
        if (returnvalue == 1) {
            [tool ShowAlert:I(@"收藏成功")];
            ret=YES;
            return ret;
        }else if (returnvalue == 2) {
            [tool ShowAlert:I(@"已收藏")];
            ret=YES;
            return ret;
        }else {
            [tool ShowAlert:I(@"收藏失败")];
            return ret;
        }

        
	}
	//NSLog(@"return value = %d",returnvalue);
		//加一项收藏到收藏列表顶部，返回值：0失败，1成功，2已收藏
	return ret;
}

-(void)gotoComment
{
	CMInfoCommentControl* InfoCommentControl = [[CMInfoCommentControl alloc] init];

	[InfoCommentControl setCourseID:item->sID type:@"course"];
    [InfoCommentControl setBrowserItem:*item];
    InfoCommentControl.cannotComment = !item->bEnablecomment;
	InfoCommentControl.title =[NSString stringWithUTF8String:item->sTitle];// I(@"课程评论");
	InfoCommentControl.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];
    [ud setObject:@"1" forKey:@"CommentReplyAdd"];

	[[((UIViewController*)self.superview.nextResponder) navigationController] pushViewController:InfoCommentControl animated:YES];
    CMRELEASE(InfoCommentControl);
	
}

- (void)popWhenNoNermission{
    [[((UIViewController*)self.superview.nextResponder) navigationController] popViewControllerAnimated:YES];
}

#pragma mark table function

-(void)tableView:(CMTableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	CMNavgateItem* nav = [[CMNavgateItem alloc] init];
    
    TCoursewareItem courseitem;
    if (!m_CourseInfo->GetCourseware(indexPath.row, courseitem))
    {
        CMRELEASE(nav);
        return;
    }
    
	[nav NavgateItem:(UIViewController*)self.superview.nextResponder item:courseitem];
	
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    CMRELEASE(nav);
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	return m_CourseInfo->CoursewareCount();
}
//	//每段头高
//-(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section{
//	return 20.0;
//}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath   
{
    /*
	TCoursewareItem Item;
	if(!m_CourseInfo->GetCourseware(indexPath.row, Item))
		return 0.0;
	NSString *cellText = [NSString stringWithUTF8String:Item.sTitle];
	UIFont *cellFont = [UIFont systemFontOfSize:kTextSizeMid];
	CGSize constraintSize = CGSizeMake(tableView.frame.size.width-30, MAXFLOAT);
	CGSize labelSize = [cellText sizeWithFont:cellFont constrainedToSize:constraintSize lineBreakMode:UILineBreakModeWordWrap];

	return MAX(labelSize.height+10,50);
     
     */
    
    return 60;
    
    
 	
}

-(UITableViewCell *)tableView:(CMTableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    CMClassInfoCell*cell = [tableView dequeueReusableCellWithIdentifier:kCellIdentifier];
    if (cell == nil) {
        NSArray *nib=[[NSBundle mainBundle] loadNibNamed:@"CMClassInfoCell" owner:self options:nil];
        
        if([nib count]>0)
        {
            cell=self.classInfoCell;
        }
        else
        {
            NSLog(@"load nib failed");
        }
    }
    
	TCoursewareItem citem;
	m_CourseInfo->GetCourseware(indexPath.row, citem);
    
    [cell setcellinfo:citem];
    
    cell.contentView.backgroundColor=UIColorMakeRGBA(242.0f, 242.0f, 242.0f, 1);
    
	cell.selectionStyle = UITableViewCellSelectionStyleGray;
    
    UIImageView *s_bg = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 300, 60)];
    s_bg.image = [UIImage imageNamed:@"courseinfo_cell"];
    
    cell.selectedBackgroundView = s_bg;
    CMRELEASE(s_bg);
    
    cell.textLabel.highlightedTextColor = [UIColor blackColor];

	cell.accessoryType = UITableViewCellAccessoryNone;

	return cell;
}

#pragma mark system function

-(void)loadTableList
{
	[self setViewsFrame];
	[TableViewList setDelegate:self];
	[TableViewList setDataSource:self];
	[TableViewList reloadData];
    self.infoBtn.enabled = YES;
}



-(UILabel*)GetLabel:(NSString*)title textcolor: (UIColor*)textcolor fontsize:(int)size
{
# if ! __has_feature(objc_arc)
    UILabel* lb        = [[[UILabel alloc] init] autorelease];
# else
    UILabel* lb        = [[UILabel alloc] init];
# endif
    lb.backgroundColor = [UIColor clearColor];
    lb.textAlignment   = UITextAlignmentLeft;
    lb.font            = [UIFont systemFontOfSize:size];
    lb.textColor       = textcolor;
    lb.text            = title;
	return lb;
}

-(void)refreshCourseInfo
{
    if(m_pWebImage != NULL && m_pWebImage->GetFromUrl(0,item->sThumbs))
    {
        UIImage* loadImage = [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(item->sThumbs)]];
        sImage.image = loadImage;
    }
    if(sImage.image == nil || sImage.image.size.width == 0 ||  sImage.image.size.height == 0)
        sImage.image = [UIImage imageNamed:@"ulp"];
}

/**
 *  listener侦听到数据传回后调用此方法填充数据   #廖宏兴
 */
- (void)courseDataFillIn{
    SAFEDELETE(item);
    item = new TClassItem();
    if (m_CourseInfo->GetClassItem(*item)) {
        ;
    }
    item->Refresh();
    
    if(m_pWebImage != NULL && m_pWebImage->GetFromUrl(0,item->sThumbs))
    {
        UIImage* loadImage = [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(item->sThumbs)]];
        sImage.image = loadImage;
    }

    self.lbclassName.text=[NSString stringWithUTF8String:item->sTitle];

    if (![[NSString stringWithUTF8String:item->sMarkID] integerValue])
    {
        btnMark.hidden = YES;
        
    }
    else
    {
        self.btnMark.hidden = NO;
        [self.btnMark addTarget:self action:@selector(searchByMarkid:event:) forControlEvents:UIControlEventTouchUpInside];
        
        NSURL *url = [NSURL URLWithString:[NSString stringWithUTF8String:item->sMarkPicUrl]];
        
        [self.btnMark sd_setBackgroundImageWithURL:url forState:UIControlStateNormal];
        [self.btnMark sd_setBackgroundImageWithURL:url forState:UIControlStateHighlighted];
        
        btnMark.tag = [[NSString stringWithUTF8String:item->sMarkID] integerValue];
        [btnMark setTitle:[NSString stringWithUTF8String:item->sMarkTitle] forState:UIControlStateNormal];
    }
    
    //学分为0时不显示学分项
    if ([[NSString stringWithUTF8String:item->sCredit] isEqualToString:@"0"] || [[NSString stringWithUTF8String:item->sCredit] isEqualToString:@""])
    {
        lblcredit.text = @"0";
        //            lblcredittl.hidden = YES;
        //            lblcredit.hidden = YES;
    }
    else{
        lblcredit.text=[NSString stringWithUTF8String:item->sCredit];
        //            lblcredittl.hidden = NO;
        //            lblcredit.hidden = NO;
    }
    lblview.text=[NSString stringWithFormat:@"%d",item->nVC];
    lbllike.text = [NSString stringWithFormat:@"%d",item->nPV];
    
    [slideSwitchView setUserInteractionEnabled:YES];
    
    introView.authorName = NSStringFrom(item->sAuthor);
    introView.language = NSStringFrom(item->sLanguage);
    introView.classType = NSStringFrom(item->sCourseType);
    introView.classLevel = NSStringFrom(item->sCourseLevel);
    introView.developTime = NSStringFrom(item->sDevelopTime);
    introView.versionCode = NSStringFrom(item->sCourseVersion);
    introView.introduction = [NSString stringWithUTF8String:item->sDescription];
    
    
    commentView.cannotComment = !item->bEnablecomment;
    [commentView setCourseID:item->sID type:@"course"];
    [commentView setBrowserItem:*item];
    
    [introView setNeedsLayout];

}


/**
 *  此方法只管视图布局，不填数据
 */
-(void)courseInit
{
	try {
//        SAFEDELETE(item);
//        item = new TClassItem();
//        if (m_CourseInfo->GetClassItem(*item)) {
//            ;
//        }
//        item->Refresh();
        
       
		CGRect contentRect = self.bounds;
	//	contentRect.size.height -= 64;
		CGFloat boundsX ;
		CGFloat boundsY ;
		int X = 0;
		//int Y = 0;
		int blank = 10;
		
		boundsX = blank ;
		boundsY = blank ;
		
		//左图
		if (sImage == nil)
			sImage = [[UIImageView alloc] init];
	
		if(sImage.image == nil || sImage.image.size.width == 0 ||  sImage.image.size.height == 0)
			sImage.image = [UIImage imageNamed:@"ulp"];
		
        
        sImage.layer.cornerRadius=8.0;
        sImage.layer.masksToBounds=YES;
		//CGFloat wd = sImage.image.size.width;
		//CGFloat hg = sImage.image.size.height;
        
        CGFloat wd = 72.0;
		CGFloat hg = 72.0;
		
//		if (btnplay == nil) 
//		{
//			btnplay = [[UIButton alloc] init];
//			[btnplay addTarget:self action:@selector(gotoPlay:) forControlEvents:UIControlEventTouchUpInside];
//		}
//		NSString*sType = [NSString stringWithUTF8String:item->sType];
//		if([sType isEqualToString:@"text/html"] || [sType isEqualToString:@"text/vnd.wap.wml"])	
//		{	
//			[btnplay setBackgroundImage:[UIImage imageNamed:@"above_explorer_p.png"] forState:UIControlStateHighlighted];
//			[btnplay setBackgroundImage:[UIImage imageNamed:@"above_explorer_n.png"] forState:UIControlStateNormal];	
//			//sType = @"above_explorer_p.png";
//		}
//		else 
//		{
//			[btnplay setBackgroundImage:[UIImage imageNamed:@"above_play_p.png"] forState:UIControlStateHighlighted];
//			[btnplay setBackgroundImage:[UIImage imageNamed:@"above_play_n.png"] forState:UIControlStateNormal];
//			//sType = @"above_play_p.png";
//		}
		
		//UIImage* image = [UIImage imageNamed:sType];
  //      btnplay.frame=CGRectMake((wd-36)/2+blank, (hg-36)/2+blank, 36, 36);

		//sImage.frame = CGRectMake(boundsX, boundsY, wd, hg);
        sImage.frame = CGRectMake(boundsX, boundsY, 72, 72);
        
# if ! __has_feature(objc_arc)
        self.lbclassName =[[[UILabel alloc]init] autorelease];
# else
        self.lbclassName = [[UILabel alloc] init];
#endif
        self.lbclassName.frame=CGRectMake(sImage.frame.origin.x+sImage.frame.size.width+10, sImage.frame.origin.y, UI_IOS_WINDOW_WIDTH-wd-30 - 93/2.0, 40);
        self.lbclassName.font=[UIFont systemFontOfSize:15];
        
        
        self.lbclassName.numberOfLines=2;
        self.lbclassName.lineBreakMode=UILineBreakModeTailTruncation;
        
        self.lbclassName.backgroundColor=[UIColor clearColor];

        btnMark = [[UIButton alloc]initWithFrame:CGRectMake(UI_IOS_WINDOW_WIDTH - 93/2.0 + 1.5, sImage.frame.origin.y - 3.0, 93/2.0, 53/2.0)];
        btnMark.backgroundColor = [UIColor clearColor];
        [btnMark setTitleEdgeInsets:UIEdgeInsetsMake(0, 0, 0, -10)];
        [btnMark.titleLabel setFont:[UIFont systemFontOfSize:15.0]];
//        [self setMarkTitle:[NSString stringWithUTF8String:item->sMarkTitle] markId:[[NSString stringWithUTF8String:item->sMarkID] integerValue]];

		//wd = MAX(wd,36);
		//hg = MAX(hg,36);
		
		boundsX += wd + blank;	

//		//观看人次
//		if(!viewimage)
//		{
//			viewimage = [[UIImageView alloc] init];
//			viewimage.image = [UIImage imageNamed:@"view"];
//		}
//		viewimage.frame = CGRectMake(UI_IOS_WINDOW_WIDTH-120, (sImage.frame.origin.y+sImage.frame.size.height)-viewimage.image.size.height, viewimage.image.size.width, viewimage.image.size.height);

        if(!lblview)
        {
# if ! __has_feature(objc_arc)
            lblview = [[self GetLabel:[NSString stringWithFormat:@"%d",/*item->nVC*/0] textcolor:UIColorRGB(0xa7a7a7) fontsize:14] retain];
# else
            lblview = [self GetLabel:[NSString stringWithFormat:@"%d",/*item->nVC*/0] textcolor:UIColorRGB(0xa7a7a7) fontsize:14];
# endif
        }
        else
            lblview.text=[NSString stringWithFormat:@"%d",/*item->nVC*/0];
        
        
        if(!lblcredit){
# if ! __has_feature(objc_arc)
            lblcredit = [[self GetLabel:[NSString stringWithUTF8String:/*item->sCredit*/"0"] textcolor:UIColorRGB(0xa7a7a7) fontsize:14] retain];
# else
            lblcredit = [self GetLabel:[NSString stringWithUTF8String:/*item->sCredit*/"0"] textcolor:UIColorRGB(0xa7a7a7) fontsize:14];
# endif
        }
        else
            lblcredit.text=[NSString stringWithUTF8String:/*item->sCredit*/"0"];
        
        
//        	lblview = [[self GetLabel:[NSString stringWithFormat:@"%d%@",m_CourseInfo->nVC,I(@"人")] textcolor:UIColorRGB(0xa7a7a7) fontsize:14] retain];
        
        
		X = boundsX/*+viewimage.image.size.width */+ 2;
		lblview.frame = CGRectMake(viewimage.frame.origin.x+viewimage.image.size.width+4, viewimage.frame.origin.y, 50, 14);
        
        
        if(!lblviewtl)
            lblviewtl=[self GetLabel:I(@"浏览:") textcolor:UIColorRGB(0xa7a7a7) fontsize:14];
        
        lblviewtl.frame=  CGRectMake(self.lbclassName.frame.origin.x, self.lbclassName.frame.origin.y+40, 40, 15);
        
        lblview.frame=   CGRectMake(self.lblviewtl.frame.origin.x+35, self.lbclassName.frame.origin.y+40, 50, 15);
        
		X+= 40;
//		//喜欢人次
//		if(!likeimage)
//		{
//			likeimage = [[UIImageView alloc] init];
//			likeimage.image = [UIImage imageNamed:@"Like"];
//		}
//		likeimage.frame = CGRectMake(lblview.frame.origin.x+40,viewimage.frame.origin.y, viewimage.image.size.width, viewimage.image.size.height);
		
	//	X =contentRect.size.width - 100;
 	//	if(X < lbllike.frame.origin.x + 50)
	//		X = lbllike.frame.origin.x + 50;
		//积分
		if(!lblcredittl){
# if ! __has_feature(objc_arc)
			lblcredittl = [[self GetLabel:[NSString stringWithFormat:@"%@:",I(@"学分")] textcolor:UIColorRGB(0xa7a7a7) fontsize:14] retain];
# else
            lblcredittl = [self GetLabel:[NSString stringWithFormat:@"%@:",I(@"学分")] textcolor:UIColorRGB(0xa7a7a7) fontsize:14];
# endif
        }
        
		lblcredittl.frame = CGRectMake(self.lbclassName.frame.origin.x+80, self.lbclassName.frame.origin.y+40, 40, 15);
		
        
        //	X += 47;
		lblcredit.frame = CGRectMake(self.lbclassName.frame.origin.x+115, self.lbclassName.frame.origin.y+40, 30, 15);
		
		boundsY += 30;
		
//		if(!lbltime){
//# if ! __has_feature(objc_arc)
//			lbltime = [[self GetLabel:[NSString stringWithUTF8String:item->sPubdate] textcolor:UIColorRGB(0xa7a7a7) fontsize:14] retain];
//# else
//            lbltime = [self GetLabel:[NSString stringWithUTF8String:item->sPubdate] textcolor:UIColorRGB(0xa7a7a7) fontsize:14];
//# endif
//        }
//        else
//            lbltime.text=[NSString stringWithUTF8String:item->sPubdate] ;
//		lbltime.frame = CGRectMake(boundsX, boundsY, 150, 15);
        
        //课程介绍按钮
        if(self.infoBtn==nil)
        {
#if ! __has_feature(objc_arc)
            self.infoBtn=[[[UIButton alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, sImage.frame.origin.y+sImage.frame.size.height)] autorelease];
#else
            self.infoBtn=[[UIButton alloc]initWithFrame:CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, sImage.frame.origin.y+sImage.frame.size.height + 10)];
#endif
            
//            [self.infoBtn setBackgroundColor:[UIColor whiteColor]];
//            
//            self.infoBtn.enabled = NO;
//            
//            [self.infoBtn addTarget:self action:@selector(showCourseInfo) forControlEvents:UIControlEventTouchUpInside];
//            
//            UILabel *infoString=[[UILabel alloc]initWithFrame:CGRectMake(boundsX-5,  sImage.frame.origin.y+sImage.frame.size.height-15, 60, 15)];
//            infoString.text=I(@"课程简介");
//            infoString.font=[UIFont systemFontOfSize:14.0];
//            infoString.textColor=UIColorRGB(0xa7a7a7);
//            [infoString setBackgroundColor:[UIColor clearColor]];
//            
//            [self.infoBtn addSubview:infoString];
//            CMRELEASE(infoString);
            
//# if ! __has_feature(objc_arc)
//            self.arrowHead=[[[UIImageView alloc]init] autorelease];
//# else
//            self.arrowHead=[[UIImageView alloc]init];
//# endif
            
//            if (courseDisplayed)
//                [self.arrowHead setImage:[UIImage imageNamed:@"arrowheadUp"]];
//            else
//                [self.arrowHead setImage:[UIImage imageNamed:@"arrowheadDown"]];
//            
//            [self.arrowHead setFrame:CGRectMake(boundsX+55,  sImage.frame.origin.y+sImage.frame.size.height-12, 10, 10)];
//            
//            [self.infoBtn addSubview:self.arrowHead];
//   
        }
        
		
 //       [self.infoBtn addTarget:self action:@selector(showCourseInfo) forControlEvents:UIControlEventTouchUpInside];

		boundsY = MAX(boundsY+15,hg+blank);
		boundsY += blank;
//		if (txtcontent == nil)
//		{
//			txtcontent = [[UILabel alloc] init];
//			[txtcontent setBackgroundColor:[UIColor clearColor]];
//			txtcontent.font =[UIFont systemFontOfSize:13];
//			txtcontent.text = [[NSString stringWithUTF8String:item->sDescription] trimString];
//            txtcontent.textColor = UIColorRGB(0x7e7e7e);
//			txtcontent.numberOfLines = 0;
//            txtcontent.lineBreakMode=UILineBreakModeWordWrap;
//            
//            txtcontent.adjustsFontSizeToFitWidth=YES;
//		}
//        else
//        {
//            txtcontent.text = [[NSString stringWithUTF8String:item->sDescription] trimString];
//        }
        
        //白色底层，挡住上面
        UIView *blankView =[[UIView alloc ]initWithFrame:CGRectMake(0, -150, UI_IOS_WINDOW_WIDTH, self.infoBtn.frame.origin.y+self.infoBtn.frame.size.height+155)];
        blankView.backgroundColor=[UIColor whiteColor];
        
        //分割线
//        if(!lblsep)
//		{
//			lblsep = [[UIImageView alloc] init];
//			lblsep.backgroundColor = UIColorRGB(0xcbcbcb);
//            
//            
//            UIImage *tempimage=[UIImage imageNamed:@"sep"];
//            
//       
//            lblsep.frame =  CGRectMake(0, self.infoBtn.frame.origin.y+self.infoBtn.frame.size.height+2, UI_IOS_WINDOW_WIDTH,tempimage.size.height);
//            [lblsep setImage:tempimage];
//            
//            lblsep.layer.shadowColor=[UIColor blackColor].CGColor;
//            lblsep.layer.shadowOffset=CGSizeMake(0,2);
//            lblsep.layer.shadowOpacity=0.3;
//            lblsep.layer.shadowRadius=1;
//            lblsep.layer.shadowPath = [UIBezierPath bezierPathWithRect:lblsep.bounds].CGPath;
//
//		}
        
        if(!btnlike)
        {
            btnlike = [[ComplexButton alloc] init];
            [btnlike setFrame:CGRectMake(self.bounds.size.width - 55 - 21,21,55,55)];
        }
        
    
//        [btnlike setTitleColor:[UIColor grayColor] forState:UIControlStateNormal];
//        [btnlike setTitleColor:UIColorRGB(0x065cc6) forState:UIControlStateHighlighted];
        
        [btnlike setImage:[UIImage imageNamed:@"courselike_n.png"] forState:UIControlStateNormal];

//        [btnlike setBackgroundImage:[UIImage imageNamed:@"courselike_n.png"] forState:UIControlStateNormal];
//        [btnlike setBackgroundImage:[UIImage imageNamed:@"courselike_s.png"] forState:UIControlStateHighlighted];
        [btnlike setImage:[UIImage imageNamed:@"courselike_s.png"] forState:UIControlStateSelected];
        
        [btnlike setImage:[UIImage imageNamed:@"courselike_s.png"] forState:UIControlStateHighlighted];

//        [btnlike setBackgroundImage:[UIImage imageNamed:@"courselike_s.png"] forState:UIControlStateSelected];
        [btnlike setImage:[UIImage imageNamed:@"courselike_h.png"] forState:UIControlStateDisabled];

        //[btnlike setBackgroundImage:[UIImage imageNamed:@"courselike_s.png"] forState:UIControlStateDisabled];
        [btnlike setAdjustsImageWhenDisabled:NO];
        [btnlike setAdjustsImageWhenHighlighted:NO];

        [btnlike setShowsTouchWhenHighlighted:NO];


        if(!lbllike){
# if ! __has_feature(objc_arc)
			lbllike = [[self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:14] retain];
# else
            lbllike = [self GetLabel:@"" textcolor:UIColorRGB(0xa7a7a7) fontsize:14];
# endif
        }
		
		
        //	X += viewimage.image.size.width + 2;
		lbllike.frame = CGRectMake(btnlike.frame.origin.x,btnlike.frame.origin.y + btnlike.frame.size.height + 10, btnlike.frame.size.width, 15);
        //  lbllike.frame = CGRectMake(0,0, 40, 15);
        [lbllike setTextAlignment:NSTextAlignmentCenter];
        
        
        [lbllike setCenter:CGPointMake(btnlike.center.x, btnlike.center.y + 20)];
       
        
        //课程简介部分
 
		//X = contentRect.size.width - blank*4;
		//CGSize size = CGSizeMake(X,MAXFLOAT);
		//CGSize labelsize = [[[NSString stringWithUTF8String:item->sDescription] trimString] sizeWithFont:[UIFont systemFontOfSize:13] constrainedToSize:size lineBreakMode:UILineBreakModeWordWrap];
        //labelsize.height=labelsize.height>200?200:labelsize.height;
        
        //CGSize size2=[txtcontent sizeThatFits:CGSizeMake(UI_IOS_WINDOW_WIDTH-2*5, 200)];
        //txtcontent.frame = CGRectMake(5, 10, UI_IOS_WINDOW_WIDTH-2*5, labelsize.height);
        
        
        
//        if(self.infoBack==nil)
//        {
//# if ! __has_feature(objc_arc)
//            self.infoBack=[[[UIImageView alloc]init] autorelease];
//# else
//            self.infoBack=[[UIImageView alloc]init];
//# endif
//            [self.infoBack addSubview:self.infoBackBtn];
//
//        }
        
           // UIImage *resultingImage = [UIImage imageNamed:@"back_courseInfo"];
//            
//            UIImage *upImage   = [UIImage imageNamed:@"infoBack_up"];
//            UIImage *midImage  = [UIImage imageNamed:@"infoBack_mid"];
//            UIImage *downImage = [UIImage imageNamed:@"infoBack_down"];
//            
//            UIGraphicsBeginImageContextWithOptions(CGSizeMake(UI_IOS_WINDOW_WIDTH, labelsize.height+20), NO, 2) ;
//            
//            // Draw image1
//            [upImage drawInRect:CGRectMake(0 , 0, UI_IOS_WINDOW_WIDTH,9)];
//            
//            // Draw image2
//            [midImage drawInRect:CGRectMake(0, 9, UI_IOS_WINDOW_WIDTH, labelsize.height+6)];
//            
//            
//            [downImage drawInRect:CGRectMake(0, 9+labelsize.height+6, UI_IOS_WINDOW_WIDTH, 5)];
//
//            
//            UIImage *resultingImage = UIGraphicsGetImageFromCurrentImageContext();
//            UIGraphicsEndImageContext();
//            

        
    //    [self.infoBack setFrame:CGRectMake(0, self.infoBtn.frame.origin.y+self.infoBtn.frame.size.height+5-resultingImage.size.height, UI_IOS_WINDOW_WIDTH, resultingImage.size.height)];
        

        
       //     [self.infoBack setImage:resultingImage];
            
          //  [self.infoBack setBackgroundColor:[UIColor clearColor]];
            
            
        
        
//		if(!txtbg)
//		{
//			txtbg = [[UIImageView alloc] init];
//			UIImage* tmp = [UIImage imageNamed:@"detailbg"];
//			tmp = [tmp stretchableImageWithLeftCapWidth:34 topCapHeight:9];
//			txtbg.image = tmp;
//		}
//		txtbg.frame =  CGRectMake(blank, boundsY, X+blank*2, labelsize.height+4*blank);
		//txtcontent.frame = CGRectMake(blank*2, boundsY+blank*2, X, labelsize.height);
     //   txtcontent.frame = CGRectMake(5, 10, UI_IOS_WINDOW_WIDTH-2*5, labelsize.height);
        
      //  [self.infoBack addSubview:txtcontent];

		
	//	boundsY += labelsize.height;
	//	boundsY += blank*4;
	
        
        
        //下方四个标签视图 简介，课件，评论，Top
        
        slideSwitchView = [[QCSlideSwitchView alloc]initWithFrame:CGRectMake(0, CGRectGetMaxY(self.infoBtn.frame), UI_IOS_WINDOW_WIDTH, contentRect.size.height - CGRectGetMaxY(self.infoBtn.frame))];
        slideSwitchView.slideSwitchViewDataSource =self;
        slideSwitchView.slideSwitchViewDelegate = self;
        slideSwitchView.tabItemNormalColor = [QCSlideSwitchView colorFromHexRGB:@"0x676767"];
        slideSwitchView.tabItemSelectedColor = [QCSlideSwitchView colorFromHexRGB:@"0x0092DD"];
        slideSwitchView.shadowImage = [[UIImage imageNamed:@"blue_line_and_shadow"]
                                            stretchableImageWithLeftCapWidth:59.0f topCapHeight:0.0f];
        slideSwitchView.tabTitleArray = [NSMutableArray arrayWithObjects:I(@"简介"),I(@"课件"),I(@"评论"),I(@"Top"), nil];
        [slideSwitchView buildUI];
        [slideSwitchView setUserInteractionEnabled:NO];
        
        
        CGRect f = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, contentRect.size.height - CGRectGetMaxY(self.infoBtn.frame) - 38);//-38是因为slideswitchview自带tab拦，需要减去这个高度，目前还没想到更好的解决办法 #王建斌
        
        
        
        //课程简介
        if (introView == nil)
        {
            introView = [[CMClassIntroductionView alloc]initWithFrame:f];
        }
        
        //[introView layoutSubviews];
        
        
		//数据列表
		if (TableViewList == nil)
		{
			TableViewList = [[CMTableView alloc] init];
			//[TableViewList setAutoresizingMask: UIViewAutoresizingFlexibleHeight];
		}
        
        TableViewList.frame = f;
        
        //评论列表
        if (commentView == nil)
        {
            commentView = [[CMCommentView alloc]initWithFrame:f];
        }
        
//        commentView.frame = CGRectMake(0, catview.frame.origin.y+catview.frame.size.height, UI_IOS_WINDOW_WIDTH,UI_IOS_WINDOW_HEIGHT);
        
        //Top
        if (topView == nil)
        {
            topView = [[CMClassTopView alloc]initWithFrame:f];
        }
        
        

		if (scrollView == nil)
		{
			scrollView = [[UIScrollView alloc]initWithFrame:contentRect];
			//scrollView.pagingEnabled = YES;
			scrollView.scrollEnabled = NO;
			scrollView.showsVerticalScrollIndicator = NO;
            
            scrollView.clipsToBounds=YES;
			[self addSubview:scrollView];
		}
            NSArray *subViews = [scrollView subviews];
        
		if([subViews count] != 0) {
			[subViews makeObjectsPerformSelector:@selector(removeFromSuperview)];
		}
        
        
//        if (downPartView==nil) {
//                 downPartView =[[UIView alloc]initWithFrame:CGRectMake(0, lblsep.frame.origin.y+lblsep.frame.size.height, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-(lblsep.frame.origin.y+lblsep.frame.size.height)) ];
//            
//            [scrollView addSubview:downPartView];
//
//        }
////       downPartView =[[UIView alloc]initWithFrame:CGRectMake(0, lblsep.frame.origin.y+lblsep.frame.size.height, UI_IOS_WINDOW_WIDTH, UI_IOS_WINDOW_HEIGHT-(lblsep.frame.origin.y+lblsep.frame.size.height)) ];
//        
//        
//        [downPartView setBackgroundColor:UIColorMakeRGBA(242.0f, 242.0f, 242.0f, 1)];
        
        
          //[downPartView setBackgroundColor:[UIColor blueColor]];

        
        
        //[scrollView addSubview:self.infoBack];
        [scrollView addSubview:blankView];
        CMRELEASE(blankView);

        // [scrollView addSubview:self.infoBackBtn];

		[scrollView addSubview:sImage];
	//	[scrollView addSubview:viewimage];
		[scrollView addSubview:lblview];
        [scrollView addSubview:lblviewtl];
	//	[scrollView addSubview:likeimage];
		[scrollView addSubview:lbllike];
	
		
        //[scrollView addSubview:lbltime];
		//[scrollView addSubview:btnplay];
		//[scrollView addSubview:txtbg];
		//[scrollView addSubview:txtcontent];
//        [scrollView addSubview:lblsep];
        
        
        
        [scrollView addSubview:slideSwitchView];
        


        [scrollView addSubview:self.lbclassName];
//        [scrollView addSubview:self.infoBtn];
        //[scrollView setBackgroundColor:[UIColor whiteColor]];
        
        [scrollView addSubview:lblcredittl];
		[scrollView addSubview:lblcredit];
        
        [scrollView addSubview:btnlike];
        [scrollView addSubview:btnMark];
        

		[self setViewsFrame];
	}
	catch (NSException* ex) {
		NSLog(@"exception= %@",ex);
	}
		
}

// set marktitle
- (void)setMarkTitle:(NSString *)marktitle markId:(NSInteger)markid{
    if (!markid) {
        [btnMark setBackgroundImage:nil forState:UIControlStateNormal];
        [btnMark setBackgroundImage:nil forState:UIControlStateHighlighted];
    }
    else if([marktitle isEqualToString:@"精品"]){
        [btnMark setBackgroundImage:[UIImage imageNamed:@"learn_Boutique_normal"] forState:UIControlStateNormal];
        [btnMark setBackgroundImage:[UIImage imageNamed:@"learn_Boutique_select"] forState:UIControlStateHighlighted];
    }
    else if ([marktitle isEqualToString:@"热点"]){
        [btnMark setBackgroundImage:[UIImage imageNamed:@"learn_hot_normal"] forState:UIControlStateNormal];
        [btnMark setBackgroundImage:[UIImage imageNamed:@"learn_hot_select"] forState:UIControlStateHighlighted];
    }
    else if (markid == 500){//500 mark id
        [btnMark setBackgroundImage:[UIImage imageNamed:@"learn_teacher_normal"] forState:UIControlStateNormal];
        [btnMark setBackgroundImage:[UIImage imageNamed:@"learn_teacher_select"] forState:UIControlStateHighlighted];
    }
    else if([marktitle isEqualToString:@"默认"]){
        [btnMark setBackgroundImage:[UIImage imageNamed:@"learn_project_normal"] forState:UIControlStateNormal];
        [btnMark setBackgroundImage:[UIImage imageNamed:@"learn_project_select"] forState:UIControlStateHighlighted];
    }
    if (marktitle == nil || [marktitle length] <= 0) {
        [btnMark setBackgroundImage:nil forState:UIControlStateNormal];
        [btnMark setBackgroundImage:nil forState:UIControlStateHighlighted];
    }
    btnMark.tag = markid;
    [btnMark setTitle:marktitle forState:UIControlStateNormal];
    
}

-(void)searchByMarkid:(id)sender event:(id)event
{
    UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {
		nextResponder = [next nextResponder];
		if ([nextResponder isKindOfClass:[UIViewController class]]) {
			break;
		}
	}
	if(!nextResponder)
		return;
    
    UIViewController *viewControl = (UIViewController *)nextResponder;
    
    CMMarkViewController* markviewControl=[[CMMarkViewController alloc]init];
    markviewControl.hidesBottomBarWhenPushed=YES;
    UIButton *btn = (UIButton *)sender;
    markviewControl.title = btn.titleLabel.text;
    markviewControl.MarkID = [NSString stringWithUTF8String:item->sMarkID];
    [viewControl.navigationController pushViewController:markviewControl animated:YES];
    CMRELEASE(markviewControl);
    
}

-(void)slideView:(UIView*)v heightChange:(CGFloat)heightChange
{
    CGRect rawframe=v.frame;
    rawframe.origin.y +=heightChange;
    v.frame=rawframe;
    
    if([v isKindOfClass:[UITableView class]])
    {
        
    }
}

//-(void)showCourseInfo
//{
//    CGFloat h= self.infoBack.frame.size.height;
//
//    if(courseDisplayed)
//    {         courseDisplayed=NO;
//        
//        [UIView animateWithDuration:0.25
//                         animations:^{
//                             
//                             [self slideView:TableViewList heightChange:-h];
//                             [self slideView:lblsep heightChange:-h];
//                             [self slideView:self.infoBack heightChange:-h];
//                             
//                         } completion:^(BOOL finished){
//                             
//                             [self.arrowHead setImage:[UIImage imageNamed:@"arrowheadDown"]];
//                             [self.infoBackBtn setEnabled:NO];
//                             
//                             
//                    //         [scrollView setFrame:CGRectMake(scrollView.frame.origin.x, scrollView.frame.origin.y, scrollView.frame.size.width, scrollView.frame.size.height-h)];
//                             
//                         }];
//        
//    }else
//    {
//        
//        courseDisplayed=YES;
//        //展开课程简介
//        [UIView animateWithDuration:0.25
//                         animations:^{
//                             
//                             [self slideView:TableViewList heightChange:h];
//                             [self slideView:lblsep heightChange:h];
//                             [self slideView:self.infoBack heightChange:h];
//                             
//                         } completion:^(BOOL finished){
//                             
//                             [self.arrowHead setImage:[UIImage imageNamed:@"arrowheadUp"]];
//                             
//                             if(self.infoBackBtn==nil)
//                             {
//# if ! __has_feature(objc_arc)
//                                 self.infoBackBtn=[[[UIButton alloc]initWithFrame:self.infoBack.frame] autorelease];
//# else
//                                 self.infoBackBtn=[[UIButton alloc]initWithFrame:self.infoBack.frame];
//# endif
//                                 //     [infoBackBtn setBackgroundColor:[UIColor clearColor]];
//                                 
//                                 [self.infoBackBtn addTarget:self action:@selector(showCourseInfo) forControlEvents:UIControlEventTouchUpInside];
//                                 
//                                 [scrollView addSubview:self.infoBackBtn];
//                                 
//                                 
//                             }
//                             
//                             [self.infoBackBtn setEnabled:YES];
//                             
//                         //    [scrollView setFrame:CGRectMake(scrollView.frame.origin.x, scrollView.frame.origin.y, scrollView.frame.size.width, scrollView.frame.size.height+h)];
//                         }];
//            }
//}

-(void)updateview
{
	[self GetCourseList];
}

-(BOOL)GetCourseList
{
    [tool ShowActivityIndicator:self];
	if(!m_CourseInfo)
		return NO;
    if (m_pUpdateDataListener == nil)
        m_pUpdateDataListener = new CMClassInfoUpdateDataListener();
    
    m_CourseInfo->SetListener(m_pUpdateDataListener, NULL);
    m_CourseInfo->SetUserData((__bridge void*)self);
    
    m_CourseInfo->SetRequestType(1);
    m_CourseInfo->RequestCourseAndClass([setid UTF8String]);
    
    
    //这个方法只做请求，不应在这里更新视图数据， 应该在listener侦听到数据回来时才去更新视图   ##廖宏兴
   // [self courseInit];
    //    if (m_CourseInfo->CoursewareCount() == 0) {
//        if (!CMGlobal::TheOne().IsOffline()) {
//        }
//    }
//    else{
//        [self loadTableList];
//    }
    
    return NO;
}

-(void)setViewsFrame
{
	if(TableViewList == nil || m_CourseInfo->CoursewareCount() <= 0)
		return;
    
	CGFloat hg = 0.0;
	for(int i=0;i < m_CourseInfo->CoursewareCount();i++)
	{
		NSIndexPath* indexPath = [NSIndexPath indexPathForRow:i inSection:0];
		hg += [self tableView:TableViewList heightForRowAtIndexPath:indexPath];
	}
	CGRect rc = TableViewList.frame;
	rc.size.height = hg;
	TableViewList.frame = rc;
    scrollView.contentSize = CGSizeMake(rc.size.width, MAX(rc.origin.y+hg+44,scrollView.frame.size.height));


    [scrollView setScrollEnabled:NO];
}


-(CMCourseInfo *)getCourseInfo{
    return m_CourseInfo;
}

-(void)setInfo:(TBrowserItem&)bitem
{
	if (m_pUpdateDataListener == nil)
		m_pUpdateDataListener = new CMClassInfoUpdateDataListener();
    
    if(m_CourseInfo)
    {
        SAFEDELETE(m_CourseInfo);
    }
    
    m_CourseInfo = new CMCourseInfo();
    nModel = bitem.nModel;
    
    self.setid=[NSString stringWithUTF8String:bitem.sID];

    m_CourseInfo->SetListener(m_pUpdateDataListener, NULL);
    m_CourseInfo->SetUserData((__bridge void*)self);

}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
-(id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame];
	if(self != nil)
	{
        self.backgroundColor = kColorBackground;
        m_CourseInfo=NULL;
        
        m_pGetImageListener= new CMClassInfoGetImageListener();
        
        m_pWebImage = new CMWebImage(m_pGetImageListener);
        m_pWebImage -> SetUserData((__bridge void*)self);
	}
	return self;
}

#pragma mark - QCSlideView Delegate

- (NSUInteger)numberOfTab:(QCSlideSwitchView *)view
{
    return 4;
}

- (UIViewController *)slideSwitchView:(QCSlideSwitchView *)view viewOfTab:(NSUInteger)number
{
    CMBrowserControl *sliderSwitchCtrl = [[CMBrowserControl alloc]init];
    NSArray *subV = [sliderSwitchCtrl.view subviews];
    
    if (subV.count != 0)
    {
        [subV makeObjectsPerformSelector:@selector(removeFromSuperview)];
    }
    
    CGRect f = CGRectMake(0, 0, UI_IOS_WINDOW_WIDTH, self.bounds.size.height - CGRectGetMaxY(self.infoBtn.frame) - 38);
    
    switch (number)
    {
        case 0:
        {
            sliderSwitchCtrl.title = I(@"简介");
            if (introView == nil)
            {
                introView = [[CMClassIntroductionView alloc]initWithFrame:f];
            }
            
            //不在这里填数据，统一在courseDataFillIn 方法里更新数据   #廖宏兴
//            introView.authorName = NSStringFrom(item->sAuthor);
//            introView.language = NSStringFrom(item->sLanguage);
//            introView.classType = NSStringFrom(item->sCourseType);
//            introView.classLevel = NSStringFrom(item->sCourseLevel);
//            introView.developTime = NSStringFrom(item->sDevelopTime);
//            introView.versionCode = NSStringFrom(item->sCourseVersion);
//            introView.introduction = [NSString stringWithUTF8String:item->sDescription];
            introView.hidden = NO;
            [sliderSwitchCtrl.view addSubview:introView];
        }
            break;
        case 1:
        {
            sliderSwitchCtrl.title = I(@"课件");
            if (TableViewList == nil)
            {
                TableViewList = [[CMTableView alloc] init];
                TableViewList.scrollEnabled = YES;
                //[TableViewList setAutoresizingMask: UIViewAutoresizingFlexibleHeight];
            }
            if (m_CourseInfo->CoursewareCount() * 60 < f.size.height)
            {
                f.size.height = m_CourseInfo->CoursewareCount() * 60;
                TableViewList.scrollEnabled = NO;
            }
            TableViewList.frame = f;
            
            [sliderSwitchCtrl.view addSubview:TableViewList];
        }
            break;
        case 2:
        {
            sliderSwitchCtrl.title = I(@"评论");
            if (commentView == nil)
            {
                commentView = [[CMCommentView alloc]initWithFrame:f];
            }
            commentView.cannotComment = !item->bEnablecomment;
            [commentView setCourseID:item->sID type:@"course"];
            [commentView setBrowserItem:*item];
            [sliderSwitchCtrl.view addSubview:commentView];
        }
            break;
        case 3:
        {
            sliderSwitchCtrl.title = I(@"Top");
            if (topView == nil)
            {
                topView = [[CMClassTopView alloc]initWithFrame:f];
            }
            
            [topView setCourseID:item->sID type:[NSString stringWithCString:item->sType encoding:NSUTF8StringEncoding]];
            [sliderSwitchCtrl.view addSubview:topView];
        }
            break;
        default:
            break;
    }
    
    return sliderSwitchCtrl;
}

- (void)slideSwitchView:(CMBrowserControl *)browserControler didselectTab:(NSUInteger)number
{
    [scrollView setContentOffset:CGPointMake(0, 0) animated:YES];
    if (number == 0)//简介
    {
//        scrollView.scrollEnabled = YES;
    }
    else if (number == 1)//课件
    {
//        scrollView.scrollEnabled = YES;
    }
    else if (number == 2)//评论
    {
//        scrollView.scrollEnabled = NO;
        
        [commentView viewDidShow];
    }
    else if (number == 3)//Top
    {
        [topView loadData];
//        scrollView.scrollEnabled = NO;
    }
}


- (void)dealloc {

    CMRELEASE(_infoBack);
    CMRELEASE(_infoBackBtn);
    CMRELEASE(_lbclassName);
    CMRELEASE(_arrowHead);
    CMRELEASE(_infoBtn);
    CMRELEASE(lblviewtl);
    CMRELEASE(sImage);
    CMRELEASE(viewimage);
    CMRELEASE(lblview);
    CMRELEASE(likeimage);
    CMRELEASE(lbllike);
    CMRELEASE(lblcredittl);
    CMRELEASE(lblcredit);
    CMRELEASE(lbltime);
    CMRELEASE(txtbg);
    CMRELEASE(txtcontent);
    CMRELEASE(lblsep);
    CMRELEASE(TableViewList);
    CMRELEASE(scrollView);
    CMRELEASE(btnMark);
    
    printf("xxxxxxxxxxxxxxxxxxxxx");
    SAFEDELETE(item);
	SAFEDELETE(m_CourseInfo);
	SAFEDELETE(m_pUpdateDataListener);
	SAFEDELETE(m_pGetImageListener);
	SAFEDELETE(m_pWebImage);
    printf("yyyyyyyyyyyyyyyyyyy");
# if ! __has_feature(objc_arc)
	[super dealloc];
# endif
}


@end

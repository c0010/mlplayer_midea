//
//  CMWebView.mm
//  MLPlayer
//
//  Created by sunjj on 11-6-9.
//  Copyright 2011 w. All rights reserved.
//

#import "CMWebView.h"
#import "tool.h"

@implementation CMWebView

UIActivityIndicatorView * activity;
UIView *viewLoading;


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
		
		[self setBackgroundColor:[UIColor grayColor]];		
		[self setUserInteractionEnabled:YES];
		[self setDelegate:self];
		[self setOpaque:NO];
		self.scalesPageToFit=YES;
		
        
        activity =NULL;
        
        viewLoading = NULL;
//       	viewLoading = [[UIView alloc] init] ;
//		viewLoading.frame =CGRectMake((self.frame.size.width-100)/2-35, 140, 120, 50);
//		//viewLoading.backgroundColor=[UIColor clearColor];
//		[viewLoading setAlpha:0.8];
//		
//		CGRect frame = CGRectMake((viewLoading.frame.size.width-20)/2+20, (viewLoading.frame.size.height-20)/2+5, 20, 20);
//		activity = [[UIActivityIndicatorView alloc] initWithFrame:frame];
//		
//		CGRect logo_frame=CGRectMake(35, (viewLoading.frame.size.height-20)/2, 100, 25);
//		UIImageView *myImageLogo = [[UIImageView alloc] initWithFrame:logo_frame];	
//		myImageLogo.backgroundColor=[UIColor clearColor];
////		myImageLogo.image=[UIImage imageNamed:@"loadingLogo.png"];
//		
////		if (sys_version == 2) {
////			myImageLogo.image=[UIImage imageNamed:@"loadingLogo_2.png"];
////		}
//		
//		[viewLoading addSubview:activity];
//		[viewLoading addSubview: myImageLogo];
//        [myImageLogo release];
//		
////		[self addSubview:viewLoading];
//        [viewLoading release];
    }
    return self;
}

//网页开始加载的时候调用
-(void )webViewDidStartLoad:(UIWebView  *)webView   
{
//	[activity startAnimating];
//	activity.hidden = NO;
	
	//NSLog(@"webViewDidStartLoad");
}

// 网页加载完成的时候调用
-(void )webViewDidFinishLoad:(UIWebView  *)webView 
{
//	[activity stopAnimating];
	[webView setBackgroundColor:[UIColor clearColor]];
//	[viewLoading removeFromSuperview];
	//NSLog(@"webViewDidFinishLoad");
    
    CGRect frame = webView.frame;
    
    /* 使用javascript代码获取原网页高度(宽度) */
    NSString *fitHeight = [webView stringByEvaluatingJavaScriptFromString:@"document.body.scrollHeight;"];
    
    /* 将webview的高度设置为原网页的高度(宽度) */
    frame.size.height = [fitHeight floatValue];
    
    webView.frame = frame;
    
    /* 获取该webview最适合的大小 */
    CGSize fitSize = [webView sizeThatFits:CGSizeZero];
    
    /* 并将其设置为webview的大小 */
    frame.size = fitSize;
    webView.frame = frame;
    
    /*根据javascript代码修改页面的meta的值使文本内容能显示占满整个屏幕的宽度 */
    NSString *meta = [NSString stringWithFormat:@"document.getElementsByName(\"viewport\")[0].content = \"width=%f\"",webView.frame.size.width];
    
    /* webview调用js代码 */
    [webView stringByEvaluatingJavaScriptFromString:meta];
    
    /*将webview的大小修改为屏幕大小此时内容会自动适应屏幕大小 */
    /*宽度设置319是为了控制表格不要太靠边显示 */
    webView.frame =CGRectMake(0,0,self.window.frame.size.width - 1, self.window.frame.size.height - 44 - 20);
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code.
}
*/



@end

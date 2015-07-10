//
//  CMBrowserView.m
//  MLPlayer
//
//  Created by luo on 12-7-25.
//  Copyright 2012 w. All rights reserved.
//

#import "CMSpecialtopicView.h"


@implementation CMSpecialtopicView

-(id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame refresh:false];
	if(self != nil)
	{
        
		m_pUpdataDataListerner = NULL;

		TopImage = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, 0)];
		TopImage.clipsToBounds = YES;
		TopImage.contentMode = UIViewContentModeCenter; 		
		[TopImage setBackgroundColor:[UIColor clearColor]];
		[self addSubview:TopImage];
	}
	return self;
}
-(void)LoadData:(NSString*)sID
{
	if(!m_pUpdataDataListerner)
		m_pUpdataDataListerner = new CMSpecialtopicUpdateDataListener();
	if(!self.Contenthandler)
	{
		CMSpecialTopic* pSpecialtopic = new CMSpecialTopic(m_pUpdataDataListerner);
		pSpecialtopic->SetUserData(BridgeObjectToC(self));
		self.Contenthandler = pSpecialtopic;
	}
	CMSpecialTopic* pSpecialtopic = (CMSpecialTopic*)self.Contenthandler;
    pSpecialtopic->SetUserData(BridgeObjectToC(self));
    pSpecialtopic->SetListener(m_pUpdataDataListerner, NULL);

    
    [tool ShowActivityIndicator:self];
	pSpecialtopic->GetSpecialTopic([sID UTF8String]);
	[self GetBrowserList];
	//[tool Wait];
}

-(void)GetBrowserList
{
	[super GetBrowserList];	
	
	if (TopImage.image != nil) 
		return;
	CMSpecialTopic* pSpecialtopic = (CMSpecialTopic*)self.Contenthandler;
	if(!pSpecialtopic)
		return;	

	if(self.m_pWebImage && pSpecialtopic && self.m_pWebImage->GetFromUrl(0, pSpecialtopic->GetImage()))
	{	
		UIImage* loadImage =   [CMImage imageWithContentsOfResolutionIndependentFile:[NSString stringWithUTF8String:m_pWebImage->GetFilePath(pSpecialtopic->GetImage())]];// m_image;
		TopImage.image = loadImage;
		TopImage.frame = CGRectMake(0, 0, self.frame.size.width, loadImage.size.height);
		tableviewlist.frame = CGRectMake(0, loadImage.size.height, self.frame.size.width, UI_IOS_WINDOW_HEIGHT-44-20- loadImage.size.height);
		
	}
	
	UIResponder* nextResponder = nil;
	for (UIView* next = [self superview]; next; next = next.superview) {     
		nextResponder = [next nextResponder];      
		if ([nextResponder isKindOfClass:[UIViewController class]]) {       
			break; 
		}    
	}
	if(nextResponder)
		((UIViewController*)nextResponder).title = [NSString stringWithUTF8String:pSpecialtopic->GetTitle()];
}
- (void)dealloc {
	
	CMRELEASE(TopImage);
	
	SAFEDELETE(m_pUpdataDataListerner);
	SAFEDELETE(self->m_pContenthandler);
}


@end


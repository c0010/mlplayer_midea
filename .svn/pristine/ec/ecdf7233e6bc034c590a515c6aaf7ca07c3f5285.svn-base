	//
	//  CMPlayerControl.h
	//  MLPlayer
	//
	//  Created by wunding on 5/17/11.
	//  Copyright 2011 w. All rights reserved.
	//

#import <UIKit/UIKit.h>

#import "EAGLView.h"
#include "stdafx.h"
#include "mplayerinterface.h"
#import "cmcourseinfo.h"
#import "cmcontenthandler.h"
#import "tool.h"

class CMPlayerUtility;
class CMPlayerListener;
class CMPlayRatingListener;



@interface PlayNavigationBar : UINavigationBar
{}
@end


#define typeCourse  1
#define typeNews 2
@interface CMPlayerControl : UIViewController {
    CMContenthandler* m_pContenthandler;
    CMPlayRatingListener *m_pRatingListener;

	CMPlayerListener* m_listener;
	int               m_nVol;
	BOOL              m_bMute;
	NSString*         m_sUrl;
    NSString*         m_sLocalFilePath;
	int               m_nMode;
	int               m_nOldPlayPos;
	BOOL              m_bFullScreen;
	CGRect            m_movieRect;
	CGRect			  m_fullmovieRect;
	
	UIImage*          playBtnBG;
	UIImage*          pauseBtnBG;	
	UIImage*          fullBtnBG;
	UIImage*          normalBtnBG;		
	EAGLView*         m_movieView;
	
	NSString*		  commentUrl;
		//char		  m_courseid[64];
	BOOL              istrue;
	BOOL			  ispause;
	UIImageView*      contentView;
    
	TBrowserItem	  m_pBrowserItem;
    
	NSInteger		  curpos;
	NSString*		  m_type;

	
	UIButton *myFavoriteBtn;
	UIButton *myCommentBtn;
    
    
    NSInteger typeFlag;
    
    
    NSString* sflag;
    NSString* classid;//课程id
    NSString* coursewareid;//课件id
    NSString* pubdate;
    NSInteger pv;
    BOOL israted;
    
    
    //定时刷新取视屏时间
    NSTimer *playerTimer;
    
    
@public
    CMPlayerUtility*  m_playUtil;
    BOOL bIsHiddenList;    //NO 显示右上角下拉列表， YES 不显示

}

@property (nonatomic,copy)   NSString                      *         m_sUrl;
@property (nonatomic,copy)   NSString                      *         m_sLocalFilePath;


@property (nonatomic,copy)   NSString                   * pubdate;
@property (nonatomic,assign) NSInteger                    pv;
@property (nonatomic,assign) BOOL                         israted;

@property (nonatomic,copy)   NSString                   * sflag;
@property (nonatomic,copy)   NSString * classid      ;//  课程id
@property (nonatomic,copy)   NSString * coursewareid ;//  课程id

@property (nonatomic,copy)   NSString                      * commentUrl;
//@property (nonatomic,retain) UISlider                      *progressSlider;
//@property (nonatomic,retain) UIView                        *controlBar;
//@property (nonatomic,retain) UILabel                       *currTime;
//@property (nonatomic,retain) UILabel                       *totaTime;
//@property (nonatomic,retain) UIButton                      *playBtn;
@property (nonatomic,assign) NSInteger                      typeFlag;


@property (nonatomic,strong) IBOutlet EAGLView             *movieView;
@property (nonatomic,strong) IBOutlet PlayNavigationBar    *titleBar;
@property (nonatomic,strong) IBOutlet UINavigationItem     *titleItem;
@property (nonatomic,strong) IBOutlet UIBarButtonItem      *fullBut;


@property (strong, nonatomic) IBOutlet UIView *startPlayView;
@property (strong, nonatomic) IBOutlet UIView *finishPlayView;

@property (nonatomic,strong) IBOutlet UIToolbar *controlBar;
@property (nonatomic,strong) IBOutlet UIBarButtonItem *playBut;
@property (nonatomic,strong) IBOutlet UIBarButtonItem *currTime;
@property (nonatomic,strong) IBOutlet UIBarButtonItem *totaTime;
@property (nonatomic,strong) IBOutlet UISlider *progressSlider;
@property (strong, nonatomic) IBOutlet UIImageView *progressImageView;
@property (strong, nonatomic) IBOutlet UILabel *progressLabel;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *menuBtn;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *onbackItem;


@property (strong, nonatomic)  UIToolbar *audioContolBar;
@property (strong, nonatomic)  UISlider *audioSlider;
@property (strong, nonatomic)  UIImageView *voiceImageView;

- (IBAction)replayButtonPressed:(UIButton *)sender;


-(id)init;
- (void)startPlay:(NSString *)url;
-(IBAction)onPlayPause;
- (void)onPause;
-(IBAction)onBack;
-(IBAction)onMute;
- (IBAction)showChoiceList;

- (IBAction)scrubbingDidBegin:(UISlider*)sender;
- (IBAction)scrubbingDidEnd:(UISlider*)sender;
- (IBAction)onProgressChange:(UISlider*)sender;

-(IBAction)onFullScreen;
-(BOOL)setItem:(TBrowserItem&)item;

-(void)onAppFocus:(BOOL)isForeground;

- (void)showAlertView:(NSString *)string;

- (void)sdl_thread;

-(void)interrupt:(NSNotification*)notification;

@end


class CMPlayerListener : public IMPlayerUtilityObserver
{
public:
	CMPlayerListener(void* control);
	
    virtual void StateChange(void* UserData, INT32 nNew, INT32 nOld);
	
    virtual void ProgressChange(void* UserData, INT32 nBufPer, INT32 nPlayPos);
	
    virtual void OnAllCompleted(void* UserData);
	
    virtual void OnError(void* UserData, INT32 nErrorCode);
	
	virtual void VideoDraw(UINT8* data, INT32 width, INT32 height);
	
	virtual void NotifyStop();
private:
	void* m_control;
};
class CMPlayRatingListener : public IMRatingListener
{
	void OnRating(void* UserData, int nNewRating, int Result)
	{
        CMPlayerControl *control = (__bridge CMPlayerControl *)UserData;
		if(Result == TResult::ESuccess || Result == TResult::ENothing)
		{
          //  [tool ShowAlert:I(@"喜欢成功")];
            [control showAlertView:I(@"喜欢成功")];
		}
        else if (Result == TResult::ENotSupportOffline)
        {
            NSString *str = [NSString stringWithFormat:I(@"网络不给力")];
            [control showAlertView:str];
        }
        else {
          //  [tool ShowAlert:I(@"只能喜欢一次")];
            [control showAlertView:I(@"只能喜欢一次")];

		}
	}
};



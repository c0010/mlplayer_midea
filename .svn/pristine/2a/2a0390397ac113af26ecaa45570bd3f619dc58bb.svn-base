// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
////////////////////////////////////////////////////////////////////////////////

#ifndef CMCOMMON_H_HEADER_INCLUDED_B249D7FB
#define CMCOMMON_H_HEADER_INCLUDED_B249D7FB

#include "sqlite3.h"
#include "stdafx.h"
#include "cmmutex.h"
#include "tinyxml.h"
using namespace tinyxml;
#include "cmcommoninterface.h"
#include <string>
using namespace std;

//更新数据监听器接口
class IMUpdateDataListener
{
  public:
    virtual void OnUpdateDataProgress(void* UserData, int nPercent) = 0;

    virtual void OnUpdateDataFinish(void* UserData, int Result) = 0;

};

//简单返回结果监听器接口
class IMSimpleResultListener
{
  public:
    virtual void OnRequestFinish(void* UserData, int Result) = 0;

};

//登录监听器接口
class IMLoginListener
{
  public:
    virtual void OnLogin(void* UserData, int Result, int HasNewVersion) = 0;

};

//课程评价监听器接口
class IMRatingListener
{
  public:
    virtual void OnRating(void* UserData, int nNewRating, int Result) = 0;

};


// 获取网络图片监听器接口
class IMGetImageListener
{
  public:
    virtual void OnFinish(void* UserData, int Result, int nID) = 0;

};

// 异步操作请求返回结果码
class TResult
{
/*
	服务器内部错误	ERR_SERVER	-1
	客户端未登录，需要登录后才能进行相关访问操作	ERR_NEEDLOGIN	-2
	客户端版本太低	ERR_VERSION	-3
	用户名或密码错误	ERR_USERNAMEPWD	-10
	修改密码失败	ERR_ ALTERPSW	-11
	该用户己登录	ERR_USERUSING	-12
	该用户己被禁用	ERR_USERDISABLED	-13
	不允许重复评价课程	ERR_DUPLICATERATING	-14
*/
	
  public:
	const static int ENotSupportOffline = 8;//不支持离线模式

    const static int EProtocolFormatError = 7;//协议格式错误

    const static int EUnknownFormat = 6;//未知格式

    const static int ENotSupportFormat = 5;//不支持格式

    const static int ENothing = 4;//对获取数据的请求处理正确，但没有符合条件的结果返回

    const static int EPartialContent = 3;//只返回了请求数据中的一部分

    const static int ENetTimeout = 2;//请求超时

    const static int ENetDisconnect = 1;//网络连接异常

    const static int ESuccess = 0;//成功

    const static int ESuccessCache = 100;//成功从缓存读取出来

    const static int EUnknownError = -1;//服务器发生未定义的错误

    const static int EUserOrPassError = -10;//用户名或密码错误

    const static int EVersionError = -3;//版本不被服务器支持

	const static int EKicked = -4; //被T了

    const static int ESmscode = -5; //短信授权码不正确

    const static int ECer = -6; //登录签证不正确

    const static int EAlreadyDone = -7; //已完成，已提交

    const static int EParams = -8; //参数错误

    const static int EUserusing = -12;//用户已经登录，不允许重复登录

    const static int EUserdisabled = -13;//用户已被禁用

    const static int EDuplicaterating = -14;//不允许重复评价课程 ()

    const static int EIsGone = -15; //状态已改变

    const static int EBound = -16;//帐号已绑定其它设备

    const static int ENoPowerCourse = -17;//无权限查看该课程(协议215)

    const static int EJoinGroupError = -20;//加入群失败 协议811

    const static int ECreateGroupError = -21;//创建群失败 协议810

    const static int EGetGroupListError = -22;//获取群列表失败 协议800 820

    const static int EGetGroupInfoError = -23;//获取群详细信息失败 协议801

    const static int EApplyGroupError = -24; //申请加入群失败 协议812

    const static int EGroupManagementError = -25; //群管理操作失败 协议830

    const static int EGroupInexistence = -26; //群组已解散或不存在(协议811 812 830) 及其他不存在的情况

    const static int ENotMideaUid = -27;//非美的帐号不能登录

    const static int ETimeNotStart = -30; //未开始错误

    const static int ETimeEnd = -31; //已结束

    const static int EBeCancel = -32; //已经取消

    const static int ENotBelong = -33; //不属于

    const static int EOutNum = -34; //超出人数

    const static int EExamTimeOut = -35; //考试超时

    const static int ESameData = -36;//本地数据与服务器数据相同 不返回数据

    const static int ECantExam = -37;
};


template <typename T> class CMList;

class TCommentItem
{
public:
  	char sUsername[32];
    
    char sFullName[32];
    
    char sHeadImage[300];
    
    char sDepartment[100];
    
    char sDatetime[20];
    
    //char sComment[700];
    string sComment;
	
	char sID[64];
	
	int  npv;
	
	int  nreply;
    
    BOOL bIsLiked;
    
    TCommentItem& operator=(const TCommentItem& right);
    
    BOOL GetChildItem(int index,TCommentItem& item);
    
    int GetChildItemCount();
    
    TCommentItem();
    
    ~TCommentItem();
    
    friend class CMComment;
    
    
private:
    
    void DoClear();
    
    CMList<TCommentItem*>* m_lstChildItem;
};


//课程、资讯、知识列表项数据结构

template <typename T> class CMList;

class TBrowserItem :public IMNotifySession
{
  public:
    TBrowserItem(const TBrowserItem& right);
    TBrowserItem();

    virtual ~TBrowserItem();
    
    virtual  TBrowserItem& operator=(const TBrowserItem& right);
    
    BOOL Refresh();
    
    BOOL Update();
    
    void Cancel();
    /**
     *	对此课件发表评论
     *
     *	@param	sContent	评论内容
     *	@param	bsyncqa	是否同步到提问
     *
     *	@return
     */
    BOOL SendComment(const char* sContent, BOOL bsyncqa);
    
    void SetListener(IMUpdateDataListener* pUpdateDataListener, IMRatingListener* pRatingListener,IMSimpleResultListener* pSimpleListener);
    
    void SetUserData(void* UserData);
    
    BOOL Rating();
    
    BOOL RatingCourseinfo();

    char sID[64];
    
    char sFlag[16];
    
    char sTitle[100];
    
    char sBrief[120];
    
    char sLargeimage[300];

    char sImage[300];
    
    char sThumbs[300];

    char sType[64];

    int nCoursewarecount;

    char sUrl[300];

    char sPubdate[100];

    //浏览数
    int nVC;

    //喜欢数
    int nPV;

    int nCommentcount;

    BOOL bEnablecomment;

    BOOL bEnabledownload;

    BOOL bEnablerating;

    BOOL bEnableShare;//是否可分享

    char sDescription[450];

    char sTag[64];
    
    // 收藏时间（收藏专用属性）
    char sFavoritedate[20];

    // 是否本公司
    BOOL bMyCompany;
    
    BOOL bIsRated;
    
    int nModel; //0为课程  1为课件

    
    char sMarkID[64];//标记id
    
    char sMarkTitle[20];
    
    char sMarkPicUrl[300];
    
//    char sCategoryID[64];

    BOOL bIsHeadItem;

 protected:
    
    virtual BOOL DoComment(const char* sContent, BOOL bsyncqa) ;

    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

    sqlite3* CheckTable(const char* table);
    
    BOOL DoCreate(sqlite3* db);
    
    int BindParam(sqlite3_stmt* stmt,int col,int value) const;
    
    int BindParam(sqlite3_stmt* stmt,int col,const char* value) const;
    
    int BindParam(sqlite3_stmt* stmt,int col,float value) const;
    
    //绑定属性,sql中使用
    virtual  void bindItem(sqlite3_stmt* stmt) const;
    //取出数据,sql中使用
    virtual  void fetchItem(sqlite3_stmt* stmt);
    
    virtual  TBrowserItem& operator=(const TiXmlElement* right);

	TiXmlElement* CreateXmlElement() const;

	friend class CMContenthandler;

	friend class CMFavorites;

	friend class CMGetNewContent;
    
    friend class CMCourseInfo;
        
    friend class CMBrowser;
    
    friend class CMSpecialTopic;
    
    friend class CMDBHelper;
    
    CMSession *m_pSession;

    IMRatingListener* m_pRatingListener;
    
    IMUpdateDataListener* m_pListener;

    IMSimpleResultListener* m_pSimpleListener;

    void* m_UserData;
    
private:
    
	BOOL	m_bRatting;
    
};

class TClassItem: public TBrowserItem
{

public:
    //课程特有属性
	char sSpecialtopic[64];
	
	char sCredit[32];
    
	int nStudyduration;
    
	int nStudyprogress;
    
	char sLaststudydate[32];
    
	string fCommonStar;//综合星级

	int nMyStar;//自评星级

	string sAuthor;//课程作者

	string sLanguage;//课程语言种类

	string sCourseType;//课程类别

	string sCourseLevel;//课程级别

	string sDevelopTime;//课程开发时间

	string sCourseVersion;//课程版本号

	int nStarCount;//参与评星人数

	BOOL CommitStar(int myStar);//提交评星等级

    TClassItem();
    
    virtual ~TClassItem();
    
    TClassItem& operator=(const TBrowserItem& right);
    
    void SetListener(IMUpdateDataListener* pUpdateDataListener, IMRatingListener* pRatingListener,IMSimpleResultListener* pSimpleListener);
    
protected:
    
    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);
    
    virtual BOOL DoComment(const char* sContent, BOOL bsyncqa) ;

    //绑定属性,sql中使用
    virtual   void bindItem(sqlite3_stmt * stmt) const;
    //取出数据,sql中使用
    virtual  void fetchItem(sqlite3_stmt * stmt);

    TClassItem& operator=(const TiXmlElement* right);

	friend class CMContenthandler;
    
	friend class CMFavorites;
    
	friend class CMGetNewContent;
    
    friend class CMBrowser;
    
    friend class CMSpecialTopic;
    
    friend class CMCourseDownload;
    
    friend class CMCourseInfo;

    friend class CMDBHelper;

};


class TCoursewareItem : public TBrowserItem
{
    
public:
    //特殊标示，在download的时候标示是否下载 0 unchecked  1 checked 2 downloaded
    int nCheckStatus;
        
    TCoursewareItem();
    
    ~TCoursewareItem();
        
    BOOL bIsLearned;//是否已学
    
    char sSetID[64];//系列id,也就是课程id
    
    TCoursewareItem& operator=(const TBrowserItem& right);
    
    void SetListener(IMUpdateDataListener* pUpdateDataListener, IMRatingListener* pRatingListener);

    BOOL operator==(const TBrowserItem& right);
    
    char sDownloadUrl[300];//下载地址，若为视频文件，则和surl相同，若为图文课程，则为压缩包地址

    BOOL bDecompressed;//是否已经解压缩

    char sEntryFilePath[300];//入口html文件地址，不完整需要拼接

    char sLocalFilePath[300];//下载后文件地址

    char sOrientation[10];     //课件旋转方向


protected:
    
    virtual BOOL DoComment(const char* sContent, BOOL bsyncqa);

    //绑定属性,sql中使用
    virtual  void bindItem( sqlite3_stmt * stmt) const;
    //取出数据,sql中使用
    virtual  void fetchItem(sqlite3_stmt * stmt);
    
    TCoursewareItem& operator=(const TiXmlElement* right);
    
	friend class CMContenthandler;
    
	friend class CMFavorites;
    
	friend class CMGetNewContent;
    
    friend class CMBrowser;
    
    friend class CMSpecialTopic;
    
    friend class CMCourseDownload;
    
    friend class CMCourseInfo;

    friend class CMDBHelper;


};

class TRequestItem
{
public:
    char sName[64];

    int nCacheData;

    char sTime[64];
};

//用作CMHandler不使用链表时的dummy对象
class TDummyItem
{
public:
	int   nDummy;
};

#endif /* CMCOMMON_H_HEADER_INCLUDED_B249D7FB */

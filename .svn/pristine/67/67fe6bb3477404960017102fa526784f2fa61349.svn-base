// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:网络Http层接口类
//  Author:Roy Bi
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMSESSION_H_HEADER_INCLUDED_B5C1376C
#define CMSESSION_H_HEADER_INCLUDED_B5C1376C

#include "cmcommon.h"
#include "cmhttpc.h"
#if defined(PLAT_IOS)
#include "cmsession_iph.h"
#endif
#include <string>
using namespace std;


const UINT32 SERVICE_DEVICETOKEN		=	8;	//回传设备令牌(该条协议支持匿名访问（iOS专用）)
const UINT32 SERVICE_GETCUSTOMERLIST	=	9;	//获取客户列表

const UINT32 SERVICE_GETVERSIONVERIFY   =   98;//获取版本验证信息
const UINT32 SERVICE_LOGIN				=	100;//登录
const UINT32 SERVICE_ALTERPWD			=	110;//修改密码
const UINT32 SERVICE_RETRIEVEPASSWD     =   120;//找回密码
const UINT32 SERVICE_GETCATEGORYLIST	=	200;//获取分类目录
const UINT32 SERVICE_GETCONTENTLIST		=	210;//获取课程、资讯、知识下某分类的内容列表
const UINT32 SERVICE_GETSPECIALTOPIC	=	211;//专题课程
const UINT32 SERVICE_GETCOURSEWARELIST	=	212;//获取某课程的课件列表
const UINT32 SERVICE_GETSHAKECOURSE     =   213;//摇一摇
const UINT32 SERVICE_GETPOSITIONCOURSE  =   214;//获取岗位课程
const UINT32 SERVICE_GETCOURSEANDCLASS  =   215;//获取课程信息和课件列表
const UINT32 SERVICE_GETSAMEMARKCLASS   =   216;//获取相同标签的课程
const UINT32 SERVICE_GETCOURSEWAREBYID  =   217;//根据课件id获得课件全部数据
const UINT32 SERVICE_GETNEWSBYID        =   218;//根据资讯id获得资讯数据

const UINT32 SERVICE_SEARCH				=	220;//搜索
const UINT32 SERVICE_SEARCH_HOTKEY		=	221;//搜索热词
const UINT32 SERVICE_SEARCHCATEGERY     =	222;
const UINT32 SERVICE_GETNEWCONTENT		=	230;//获取新上线内容
const UINT32 SERVICE_GETRECENTCONTENT	=	231;//获取最近访问内容
const UINT32 SERVICE_GETCOMMENT			=	240;//查询评论
const UINT32 SERVICE_MAKECOMMENT		=	241;//发表评论
const UINT32 SERVICE_REPLYCOMMENT		=	242;//回复评论
const UINT32 SERVICE_LIKECOMMENT		=	243;//评论喜欢
const UINT32 SERVICE_GETCOMMENTREPLAY   =	244;//查询评论回复
const UINT32 SERVICE_RATING				=	250;//课程喜欢
const UINT32 SERVICE_RATINGCOURSEWARE	=	251;//课件喜欢
const UINT32 SERVICE_STARTLEVEL         =   252;//课程评星
const UINT32 SERVICE_GETTOPLIST         =   260;//获取相关课程top10

const UINT32 SERVICE_GETSURVEYLIST		=	300;//获取调研问卷列表
const UINT32 SERVICE_GETSERVEYBYID      =   301;//根据调研id获取调研信息
const UINT32 SERVICE_GETSURVEY			=	310;//获取调研题目
const UINT32 SERVICE_PUTSURVEYRESULT	=	320;//上传调研结果
const UINT32 SERVICE_FINDCONTACTS		=	400;//查通讯录
const UINT32 SERVICE_GETDETAILBYUSERID	=	401;//根据id获得用户详细信息
const UINT32 SERVICE_GETEXPERTS         =   408;//获取专家                          //新添加
const UINT32 SERVICE_QUICKFINDCONTACTS	=	410;//快速查找通讯录


const UINT32 SERVICE_FEEDBACK			=	500;//建议反馈
const UINT32 SERVICE_PERSONALINFORMATION=	600;//取个人信息
const UINT32 SERVICE_UPHEADPHTHO        =   601;//个人中心上传个人头像
const UINT32 SERVICE_GETQUESTIONCATEGORY=	700;//获取题目分类
const UINT32 SERVICE_GETEXAMLIST		=	710;//获取考试列表
const UINT32 SERVICE_GETEXERCISELIST	=	711;//获取专项练习列表
const UINT32 SERVICE_GETEXAMBYID        =   712;//根据考试id获取考试信息
const UINT32 SERVICE_GETEXERCISEBYID    =   713;//根据考试id获取考试信息

//const UINT32 SERVICE_GETQUESTION		=	720;//获取分类或考试的题目
const UINT32 SERVICE_GETEXERCISEQUESTION=	721;//获取专项练习的题目
const UINT32 SERVICE_GETWRONGQUESTION	=	722;//获取错题库的题目
const UINT32 SERVICE_GETEXAMQUESTION	=	723;//获取考试的题目
const UINT32 SERVICE_COMMITEXAM			=	730;//考试交卷
const UINT32 SERVICE_UPDATEQUESTION		=	740;//更新题库(提交错题和已做题目)

const UINT32 SERVICE_GETMYGROUP         =   800;//得到我的群列表
const UINT32 SERVICE_GETGROUPDETAIL     =   801;//得到群的详细信息
const UINT32 SERVICE_GETGROUPMEMBERLIST =   802;//得到群的成员列表
const UINT32 SERVICE_UPMESSAGEPICTURE   =   803;//发送图片消息 上传图片
const UINT32 SERVICE_UPGROUPHEADER      =   804;//上传群头像

const UINT32 SERVICE_CREATEGROUP        =   810;//创建群
const UINT32 SERVICE_ENTERGROUP         =   811;//进入群
const UINT32 SERVICE_APPLYENTERGROUP    =   812;//申请加入群
const UINT32 SERVICE_EXITRGROUP         =   813;//退出群
const UINT32 SERVICE_DISBANDGROUP       =   814;//解散群

const UINT32 SERVICE_SEARCHGROUP        =   820;//用关键字搜索所有群

const UINT32 SERVICE_GROUPMANAGEMENT    =   830;//群管理


const UINT32 SERVICE_GETQACATEGORY		=	909;//获取问题分类          //经过修改
const UINT32 SERVICE_GETQALIST			=	910;//获取特定的问题列表
const UINT32 SERVICE_GETQALISTBYCATEGORY=	911;//获取某分类的问题列表
const UINT32 SERVICE_GETQABYID          =   912;//根据问答id获得问答数据
const UINT32 SERVICE_SEARCHQA			=	920;//搜索问题
const UINT32 SERVICE_GETQADETAIL		=	930;//获取问题详情
const UINT32 SERVICE_SETBESTANSWER		=	931;//设置最佳答案
const UINT32 SERVICE_LIKEANSWER			=	932;//回答喜欢
const UINT32 SERVICE_ADDATTENTION		=	933;//问题关注
const UINT32 SERVICE_NEWQUESTION		=	940;//提问
const UINT32 SERVICE_ANSWERQUESTION		=	941;//回答问题
const UINT32 SERVICE_WE		            =	950;//we微课件工具
const UINT32 SERVICE_GETUNDONE	        =	2000;//获取未完成内容数值
const UINT32 SERVICE_UPDATECATEGORYLIST =	2001;//更新栏目

const UINT32 SERVICE_GETTRAINAPPLYLIST  =   2100;//获取培训报名列表
const UINT32 SERVICE_GETTRAINAPPLYINFO  =   2101;//获取某培训报名详情
const UINT32 SERVICE_TRAINAPPLY         =   2102;//未报名的培训报名
const UINT32 SERVICE_TRAINCANCELAPPLY   =   2103;//已报名的培训取消报名
const UINT32 SERVICE_TRAINSIGNINLIST    =   2110;//获取培训签到列表
const UINT32 SERVICE_TRAINSIGNININFO    =   2111;//获取某培训签到详情
const UINT32 SERVICE_TRAINSIGNIN        =   2112;//未签到的培训签到
const UINT32 SERVICE_GETMYTRAINLIST     =   2120;//获取我的培训班列表
const UINT32 SERVICE_GETMYTRAININFO     =   2121;//获取某培训班详情
const UINT32 SERVICE_GETMYTRAINCOURSELIST = 2122;//获取某培训班课程资讯列表
const UINT32 SERVICE_GETMYTRAINCXAMLIST =   2123;//获取某培训班测验列表
const UINT32 SERVICE_GETMYTRAINEXERCISELIST=2124;//获取某培训班练习列表
const UINT32 SERVICE_GETMYTRAINUSERLIST =   2125;//获取某培训班成员列表
const UINT32 SERVICE_GETMYTRAINSURVEYLIST =   2126;//获取某培训班调研列表

class CMHttpMgr;
//命令会话类，和IMNotifySession结合使用
//临时取用
//限制，会话数据仅限于较小数据交换，不考虑WAP分包
class CMSession : public IMNotifyHttpC
{
public:
	CMSession(IMNotifySession* pNotify);

    virtual ~CMSession();

    //登录命令
    void LogIn(const char* sEid, const char* sName, const char* sPass,const char* sUid,BOOL  isReLogin, int nLoginType);
	
    //其他命令，不包括登录
    void Command(UINT32 nCmdID, const CMString& sParams);

    //Post数据的命令（废弃，不再使用）
    void CommandPost(UINT32 nCmdID, const CHAR* sParams, const CHAR* pData, INT32 nLen);

    //Post form数据的命令
    void CommandPost(UINT32 nCmdID, const CHAR* sParams, CMList<FormData> lstForm, const CHAR* sSequence = "");
    
    //是否有命令在执行
	BOOL  IsRunning();
	
	//取消当前会话操作
	void Cancel();

private:
    void LogIn(int nLoginType);

    void Command();

    //interface from IMNotifyHttpC
    virtual void OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader);
    virtual void OnRead(UINT32 nCode, INT32 nLen);

    IMNotifySession*  m_pNotify;          //通知类指针
    CMHttpC*          m_pHttp;            //Http实现类
    INT8*             m_pBuf;             //接受缓冲
    UINT32            m_nCurCmd;          //当前命令ID，登录命令不在其中
    CMString          m_sParams;          //命令参数
    BOOL              m_bRun;             //是否在执行中
    BOOL              m_bPost;            //是否是post命令
    
    CMHTTPReqHeader   m_req;
    
    
    char sCustomer[100];
    char sUsername[100];
    char sPassword[100];
    char sUserid[100];

    BOOL m_bRelogin;//标示是否是重登陆
    
    string            m_sSequence;
    friend class CMSessionSequence;
};

#endif /* CMSESSION_H_HEADER_INCLUDED_B5C1376C */

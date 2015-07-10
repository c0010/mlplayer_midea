//
//  cmgroup.h
//  MLPlayer
//
//  Created by 王浩沣 on 14-6-16.
//  Copyright (c) 2014年 w. All rights reserved.
//

#ifndef __MLPlayer__cmgroup__
#define __MLPlayer__cmgroup__
#include "cmcommon.h"
#include "cmhandler.h"
#include <string>

using namespace std;

class TGroupInfoItem:public IMNotifySession
{
  public:
    //群id
    string sID;
    //群的房间jid
    string sJID;
    //群名
    string sName;
    //群简介
    string sDescription;
    //进入群的密码
    string sPwd;
    //昵称
    string sNickName;
    //房间总人数
    int nUserCount;
    //房间图标地址
    string sIconUrl;
    //加入类型：0不能加入 1不需要验证  2需要验证
    int nFlag;

    string sRoomNumber;//房间号

    string sOwner;//房主名

    string sOwnerId;//房主id

    int nIsOccupant;//-1非成员 0成员  2管理员  5群主

    TGroupInfoItem();
    ~TGroupInfoItem();

    void SetListener(IMUpdateDataListener* pUpdateDataListener,IMSimpleResultListener* pSimpleListener);

    void SetUserData(void* userdata);

    void Cancel();

    //根据群id去请求
    BOOL RequestDetailInfo();

    //请求入群
    BOOL RequestEnterGroup(const char* key);

    //申请加入群
    BOOL ApplyEnterGroup(const char* reason);

    /**
     *  踢出群
     *
     *  @param sids    被踢出群用户的id集合，用','分割
     *  @param groupid 操作的群组id
     */
    BOOL KickGroupOccupant(const char* sids);

    /**
     *  邀请加入群
     *
     *  @param sids    被被邀请用户的id集合，用','分割
     *  @param groupid 操作的群组id
     */
    BOOL InviteToGroup(const char* sids);

    /**
     *  设定管理员
     *
     *  @param sids    被设为管理员的用户的id集合，用','分割
     *  @param groupid 操作的群组id
     */
    BOOL SetGroupAdmin(const char* sids);


    /**
     *  取消管理员
     *
     *  @param sids    被取消管理员的用户的id集合，用','分割
     *  @param groupid 操作的群组id
     */

    BOOL RemoveGroupAdmin(const char* sids);


    /**
     *  通过某用户的进群申请
     *
     *  @param sids    被取消管理员的用户的id集合，用','分割
     *  @param groupid 操作的群组id
     */

    BOOL AcceptUserApply(const char* sids);


    /**
     *  拒绝某用户的进群申请
     *
     *  @param sids   单个用户的id，非集合！！
     *  @param reason 拒绝原因
     *
     *  @return
     */
    BOOL RefuseUserApply(const char* sids, const char* reason);

    TGroupInfoItem& operator=(const TGroupInfoItem& right);

    /**
     *  退出群
     *
     *  @return
     */
    BOOL ExitGroup();
    
    /**
     *  解散群
     *
     *  @return
     */
    BOOL DisbandGroup();
    
    /**
     *  更新群名称
     *
     *  @param sids   单个用户的id，非集合！！
     *  @param reason 群名称
     *
     *  @return
     */
    BOOL updateGruopInfoWithName(const char* reason);
    /**
     *  更新群简介
     *
     *  @param sids   单个用户的id，非集合！！
     *  @param reason 群简介
     *
     *  @return
     */
    BOOL updateGruopInfoWithDesc( const char* reason);
    /**
     *  更新群权限
     *
     *  @param sids   单个用户的id，非集合！！
     *  @param reason 群名称
     *
     *  @return
     */
    BOOL updateGruopInfoWithPermis(const char* reason);

    //上传群头像
    BOOL UploadHead(const char* filename);


protected:

    
    friend class CMGroup;

    TGroupInfoItem& operator=(const TiXmlElement* right);

    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc) ;
    CMSession *m_pSession;

    IMUpdateDataListener* m_pListener;

    IMSimpleResultListener* m_pSimpleListener;

    void*    m_UserData;
    //更新群信息
    BOOL UpdateGroupInfo(int operateType,const char* reason);
    BOOL GroupManagement(int operateType,const char* sids,const char* reason);

    void fetchItem(sqlite3_stmt* stmt);
    void bindItem(sqlite3_stmt* stmt) const;
};


class  CMGroup: public CMHandler<TGroupInfoItem>
{
  public:

	CMGroup();

    virtual ~CMGroup();

    void SetListener(IMUpdateDataListener* m_pListener,IMSimpleResultListener* m_pSimpleListener);

    BOOL RequestMyGroup();

    BOOL SearchGroup(const char* keyword);

    BOOL CreateNewGroup(const char* name, const char* desc, const char* iconPath, int flag);

  protected:

    //缓存建表
    virtual BOOL DoCreate(sqlite3* db) ;
    //网络回来数据，要加入缓存并刷新对象
    virtual BOOL DoPutItem(TiXmlElement* pItem, sqlite3* db, TGroupInfoItem& item) ;
    //清除内存以及缓存里的相关数据
    virtual void DoClear();

    virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

  private:



    IMSimpleResultListener* m_pSimpleListener;

};

#endif /* defined(__MLPlayer__cmgroup__) */

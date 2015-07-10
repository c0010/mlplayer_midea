#ifndef CMREPALYCOMMENT_H_HEADER_INCLUDED_B19B6617
#define CMREPALYCOMMENT_H_HEADER_INCLUDED_B19B6617

#include "cmcommon.h"
#include "cmmyinfo.h"

template <typename T> class CMList;

class TRepalymentItem
{
   public:
    char sUsername[32];

    char sFullName[32];

    char sHeadImage[300];

    char sDepartment[100];

    char sDatetime[20];

   // char sComment[700];

    string sComment;
	
   char sID[64];
	
   int  nreply;
    
   //不再支持status
//    int nStatus; //0已完成，1发送中，2发送失败
  
};

class CMRepalycomment:public IMNotifySession
{
  public:
    CMRepalycomment(IMUpdateDataListener* pUpdateDataListener, IMSimpleResultListener* pSimpleResultListener);

    virtual ~CMRepalycomment();

    void SetUserData(void* UserData);

   BOOL ReplyComment(const char* sFlag,const char* ClassID,const char* CoursewareID, const char* sReplyID,const char* sContent);

    
   

    BOOL RequestRepalyCommentList(const char* sFlag, const char* sID);

    BOOL RequestMore();

    int GetItemCount();

    BOOL GetItem(int nIndex, TRepalymentItem& item);

   void Cancel();

  BOOL IsEnd();

  protected:
	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

 private:
    void MakeTempItem(const char* sFlag,const char* sID,const char* sReplyID,const char* sContent,TRepalymentItem &item);


	BOOL CurrentRepalyComment(const char* param,int pageno,int pagesize);

	IMUpdateDataListener* m_pUpdateDataListener;
	
	IMSimpleResultListener* m_pSimpleResultListener;

      void* m_UserData;

	CMList<TRepalymentItem>* m_lstItem;

	CMSession* m_pSession;

	int m_nCmdId;

	char m_sReqComment[100];

	int m_nPageNo;

	int m_nPageSize;

	int m_nPageCount;
    
      char ratingReplyID[64];

};



#endif /* CMCOMMENT_H_HEADER_INCLUDED_B19B6617 */


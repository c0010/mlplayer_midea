#pragma once

#include "cmhttpc.h"

class CMHttpS;

class CMHttpSNotify : public IMNotifySocketC, IMNotifyHttpC
{
public:
    CMHttpSNotify(CMSocketC* pSocketC, CMHttpS* pHttpS);
    ~CMHttpSNotify();

    BOOL IsInService() {return m_bInService;};
    void ChangeSocket(CMSocketC* pSocketC);

    //��ʼ����http����
    void Start();

    void OnConnect(UINT32 nCode);
    //���յ�����
    void OnRecv(UINT32 nCode, INT32 nLen);
    //��Ӧ���ͳɹ�
    void OnSend(UINT32 nCode, INT32 nLen);

    void OnResponse(UINT32 nCode, const CMHTTPRspHeader* pRespHeader);
    void OnRead(UINT32 nCode, INT32 nLen);
private:
    CMSocketC* m_pSocketC;
    CMHttpS*   m_pHttpS;             //��Ӧhttp Server
    CMHttpC*   m_pHttpC;             //�ⲿhttp����
    CMFile*    m_pFile;              //����file
    CMHTTPReqHeader    m_cReqHeader;    //����Http����ͷ
//    CMHTTPRspHeader    m_cRspHeader;    //����Http��Ӧͷ
    CMUrl              m_rUrl;          //������ⲿ��ַ
    INT8*              m_pHeadBuf;      //���ͷ�Ļ���������Ҫ����������
    UINT32             m_nHeadPos;      //ͷ�������ĵ�ǰָ��λ��
    UINT32             m_nTotalSize;    //�ܵ������С
    UINT32             m_nStart;        //��ǰ��ʼ
    UINT32             m_nEnd;          //��ǰ��ֹ
    UINT32             m_nSize;            //������http�����ļ���С
    UINT32             m_nSendSize;        //������socket�����ļ���С
    INT8*              m_pBuf;             //http���ջ���
    //UINT32             m_nBufSize;         //http���ջ����С
    UINT32             m_nPos;             //http���ջ�����socket����λ��
    BOOL               m_bInService;
    UINT32             m_nStatus;          //0 ����, 1 ��������ͷ 2 ��������  3�����ļ�����ͷ 4�����ļ�����

};

//��Զ��url��ɱ���url���ṩhttp������������iis����ͬ����iis�ṩĿ¼ӳ�䣬�˷�����ֻ�ṩ�ļ���Զ��urlӳ��
class CMHttpS : public IMNotifySocketS
{
public:
	static CMHttpS& Instance();

    //����ʱɾ����������
    ~CMHttpS();

    ////�����ⲿ����
    //void SetUrl(const CMUrl& rUrl, const CMUrl& lUrl);
    ////���ñ����ļ�����
    //void SetFile(const CMString& sFileName, const CMUrl&  lUrl);

    //const CMUrl* GetUrl(const CMUrl& lUrl);

    //const CMString* GetFile(const CMUrl& lUrl);

    //Զ��http://11.22.33.44:555/ccc/ddd/ ����http://localhost/ccc/ddd/, �� SetRemote("http://11.22.33.44:555/ccc/ddd/"=SetRemote("http://11.22.33.44:555");
    void SetRemote(const CMUrl& rUrl);
    // SetFolder("//");
    void SetFolder(const CMString& sFolder);

    //�ѱ���url���Զ��url
    CMUrl ToRemote(const CMUrl& lUrl);
    //��Զ��url��ɱ���url
    CMUrl GetLocal(const CMUrl& rUrl);

    //���÷���˿�
    void SetPort(UINT16 nPort);
    //��������
    BOOL Start();
    //ֹͣ���񣬶ϵ���������
    void Stop();

protected:
    CMHttpS();

private:
    void OnAccept(UINT32 nCode, CMSocketC* pSocketC);

    CMSocketS* m_pSocketS;
    CMList<CMHttpSNotify*>      m_lstNotify;
    //CMMap<CMUrl*, CMUrl>        m_mapUrl;
    //CMMap<CMUrl*, CMString>     m_mapFile;
    CMUrl                       m_remote;     //ӳ���Զ��url
    CMString                    m_folder;     //ӳ��ı���Ŀ¼
    UINT16                      m_nPort;

	static CMHttpS* m_pHttpS;
};


#ifndef __CMSESSION_JNI_H__
#define __CMSESSION_JNI_H__

#include <jni.h>
#include "cmcommon.h"

class CMNotifySessionAndroid : public IMNotifySession
{
public:
	CMNotifySessionAndroid(IMNotifySession* pNotify);

	~CMNotifySessionAndroid();

	virtual void OnSessionCmd(unsigned int nCmdID, unsigned int nCode, TiXmlDocument* pDoc);

private:
	jobject m_obj;
	IMNotifySession* m_pNotify;
};


#endif


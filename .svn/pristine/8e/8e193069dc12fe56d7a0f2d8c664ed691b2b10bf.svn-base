#ifndef __CMDOWNLOADER_JNI_H__
#define __CMDOWNLOADER_JNI_H__

#include <jni.h>
#include "cmcommoninterface.h"

class CMNotifyDownloadAndroid : public IMNotifyDownload
{
public:
	CMNotifyDownloadAndroid(IMNotifyDownload* pNotify);

	~CMNotifyDownloadAndroid();

	IMNotifyDownload* SetNotify(IMNotifyDownload* pNotify);

	virtual void OnProgress(unsigned int nRate);
	virtual void OnDownload(unsigned int nCode, CMDownloader* pDownloader);
private:
	jobject m_obj;
	IMNotifyDownload* m_pNotify;
};


#endif


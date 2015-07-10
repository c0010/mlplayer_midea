#ifndef _CMSWAP_H_HEADER_INCLUDED
#define _CMSWAP_H_HEADER_INCLUDED
#include "mplayerinterface.h"
#include <jni.h>
#include "cmmutex.h"
class CMSwap:public IMPlayerUtilityObserver
{
	public :

		CMSwap(jobject obj);

		~CMSwap();

	    virtual void StateChange(void* UserData, INT32 nNew, INT32 nOld);

	    virtual void ProgressChange(void* UserData, INT32 nBufPer, INT32 nPlayPos);

	    virtual void OnAllCompleted(void* UserData);

	    virtual void OnError(void* UserData, INT32 nErrorCode);

		virtual void VideoDraw(UINT8* data, INT32 width, INT32 height);

		virtual void NotifyStop();

	private:
		void Post(int no,int one, int two);

		jobject      SwapObj;
};
#endif

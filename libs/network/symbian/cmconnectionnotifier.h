
#ifndef __CONNECTION_NOTIFIER_H__
#define __CONNECTION_NOTIFIER_H__

#include <e32base.h>
#include <Es_sock.h>

class IMConnectionObserver 
{
public:
	virtual void OnConnectionNotifier( TInt aStage, TInt aError ){};
	virtual void OnConnectionClose(){};
};

class CMConnectionNotifier : public CActive
{
public:
	CMConnectionNotifier(IMConnectionObserver* aObserver, RConnection& aConnection);
	~CMConnectionNotifier();
	void Start();
protected: // from CActive
	void DoCancel();
	void RunL();
private:    
	TNifProgressBuf iProgress;    
	RConnection& iConnection;
	IMConnectionObserver* iObserver;    
};

#endif // __CONNECTION_NOTIFIER_H__


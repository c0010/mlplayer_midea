
// INCLUDES
#include "stdafx.h"
#include "cmconnectionnotifier.h"
CMConnectionNotifier::CMConnectionNotifier(IMConnectionObserver* aObserver, RConnection& aConnection)
: CActive(CActive::EPriorityStandard), 
iConnection(aConnection), 
iObserver(aObserver)
{
	CActiveScheduler::Add(this);
}

CMConnectionNotifier::~CMConnectionNotifier()
{
	Cancel();
}
void CMConnectionNotifier::DoCancel()
{
	iConnection.CancelProgressNotification();
}

 void CMConnectionNotifier::Start()
 {
	 if(!IsActive())
	{
		iConnection.ProgressNotification(iProgress, iStatus);
		SetActive();
	}
 }

void CMConnectionNotifier::RunL()
{
	if (iStatus == KErrNone)
	{
		CM_ERRP("CMConnectionNotifier::RunL()%d................",iProgress().iStage);
		switch (iProgress().iStage)
		{
	
			// Connection closed
		case KConnectionClosed:
		case KLinkLayerClosed:
			{
				Cancel();
				iObserver->OnConnectionClose();
			}
			return;
		default:
			break;
		}
		iConnection.ProgressNotification(iProgress, iStatus);
		SetActive();
	}
	else
		iObserver->OnConnectionNotifier( iProgress().iStage, iProgress().iError);
}


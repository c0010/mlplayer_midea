#include "makecall.h"
 
CCallDialer* CCallDialer::NewL(MDialObserver* aCallBack, const TDesC& aNumber)
{
    CCallDialer* self = CCallDialer::NewLC(aCallBack, aNumber);
    CleanupStack::Pop(self);
    return self;
}
 
CCallDialer* CCallDialer::NewLC(MDialObserver* aCallBack, const TDesC& aNumber)
{
    CCallDialer* self = new (ELeave) CCallDialer(aCallBack);
    CleanupStack::PushL(self);
    self->ConstructL(aNumber);
    return self;
}
 
 
CCallDialer::~CCallDialer()
{
    Cancel();
    delete iTelephony;
}
 
void CCallDialer::ConstructL(const TDesC& aNumber)
{
    iTelephony = CTelephony::NewL();
    CTelephony::TTelNumber telNumber(aNumber);
 
    iCallParams.iIdRestrict = CTelephony::ESendMyId;
 
    iTelephony->DialNewCall(iStatus, iCallParamsPckg, telNumber, iCallId);
    SetActive();
}
 
CCallDialer::CCallDialer(MDialObserver* aObserver)
: CActive(EPriorityNormal),iObserver(aObserver), iCallParamsPckg(iCallParams)
{
    CActiveScheduler::Add(this);
}
 
void CCallDialer::RunL()
{
    if (iObserver)
        iObserver->CallDialedL(iStatus.Int());
}
 
void CCallDialer::DoCancel()
{
    iTelephony->CancelAsync(CTelephony::EDialNewCallCancel);
}

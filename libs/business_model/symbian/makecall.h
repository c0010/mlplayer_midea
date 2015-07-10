#ifndef __MAKECALL_H__
#define __MAKECALL_H__

#include <Etel3rdParty.h>
// link to etel3rdparty.lib
 
class MDialObserver
{
    public:
        virtual void CallDialedL(TInt aError) = 0;
};
 
class CCallDialer : public CActive
{ 
    public:
        static CCallDialer* NewL(MDialObserver* aCallBack, const TDesC& aNumber);
        static CCallDialer* NewLC(MDialObserver* aCallBack, const TDesC& aNumber);
        ~CCallDialer();
 
    protected:
        CCallDialer(MDialObserver* aObserver);
        void ConstructL(const TDesC& aNumber);
 
    private:
        void RunL();
        void DoCancel();
 
    private:
        MDialObserver*                iObserver;
        CTelephony*                   iTelephony;
        CTelephony::TCallId           iCallId;
        CTelephony::TCallParamsV1     iCallParams;
        CTelephony::TCallParamsV1Pckg iCallParamsPckg;
};

#endif

// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#ifndef CMGLOBALLISTENER_H_HEADER_INCLUDED_B19B2DC3
#define CMGLOBALLISTENER_H_HEADER_INCLUDED_B19B2DC3

class CMGlobalListener
{
  public:
    static void SetListener(CMGlobalListener* pListener);
    
    static CMGlobalListener* GetListener();

    virtual ~CMGlobalListener();    

    virtual void OnKicked(int nErr) = 0;

  protected:
    CMGlobalListener();

  private:
    static CMGlobalListener* m_pTHIS;

};

#if defined(PLAT_AND)
class CMGlobalListenerAnd:public CMGlobalListener
{
  public:

    virtual void OnKicked(int nErr);
};
#endif

#endif /* CMGLOBALLISTENER_H_HEADER_INCLUDED_B19B2DC3 */

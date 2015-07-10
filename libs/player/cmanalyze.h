#ifndef __MVANALYZE_INCLUDE_
#define __MVANALYZE_INCLUDE_
#include"cmstreambuffer.h"
class CMAnalyze
{
public:
	CMAnalyze();
	~CMAnalyze();
private:
	Med_Info	*m_pHeadInfo;
	Med_Index	*m_pMedIndex;
	int         m_nIndexCount;
public:
	Med_Info*	GetMedInfo();
	Med_Index*	GetMedIndex();
	BOOL        AnalyzeHead(CHAR* buf,int len);
	//BOOL        GetHeadComplete(){return m_bHeadComplete;};
	int         GetMedIndexCount(){return m_nIndexCount;};
};
#endif

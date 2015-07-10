#include "cmqalist.h"

template<typename T> class CMList;

class CMQalistUpload: public IMNotifyDownload {
public:
	static CMQalistUpload* GetInstance();

	virtual ~CMQalistUpload();

	void Release();

	void SetListener(IMUpdateDataListener* pListener);

	int GetItemCount();

	BOOL GetItem(int nIndex, TQAItem& item);

	void LoadFromFile();

	int Append(const TQAItem& tqa);

	void Delete(int nImageIndex);

	BOOL Start(int nImageIndex);

	void Stop();
	virtual BOOL DoCreate(sqlite3* db);
	BOOL IsUpwloaded(const TQAItem& item)

	static int EStatusError = -1;

	const static int EStatusUploading = 1;

	const static int EStatusComplete = 2;

	const static int EStatusInDownloadList = 3;
	;

	void SetUserData(void* userdata);

	int Status(int nImageIndex);

protected:
	CMQalistUpload();

	void SaveToFile();

	virtual void OnUpload(unsigned int nCode);
private:
	static CMQalistUpload*m_pTHIS;

	CMList<TQAItem>* m_lstItem;

	void* m_UserData;

	int m_nImageIndex;

	IMUpdateDataListener *m_pUpdateListener;

};

#endif /* CMCOURSEDOWNLOAD_H_HEADER_INCLUDED_B18384D3 */

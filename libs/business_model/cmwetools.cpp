/*
 * cmwetools.cpp
 *
 *  Created on: 2013-10-10
 *      Author: mazhen
 */

#include "stdafx.h"
#include "tinyxml.h"
#include "cmsession.h"
#include "utf8ncpy.h"
#include "cmversion.h"
#include "cmwetools.h"

CMWetools::CMWetools(IMUpdateDataListener* pUpdateDataListener) {

	m_pUpdateDataListener = pUpdateDataListener;
	m_UserData = NULL;
	m_pSession = NULL;

}

const char* CMWetools::GetWesize() const {

	return sWesize;
}

const char* CMWetools::GetWeversion() const {

	return sWeversion;
}

const char* CMWetools::GetWeUrl() const {

	return sWeurl;
}

CMWetools::~CMWetools() {

}

void CMWetools::SetUserData(void* UserData) {
	m_UserData = UserData;
}

void CMWetools::GetWetool() {

	char str[128];

	snprintf(str, sizeof(str),"&os=%d", CMVersion::SystemVersion().Platform);

	if (m_pSession == NULL) {

		m_pSession = new CMSession(this);
	}
	if (m_pSession && !m_pSession->IsRunning()) {

		m_pSession->Command(SERVICE_WE, str);
	}

}

void CMWetools::OnSessionCmd(unsigned int nCmdID, unsigned int nCode,
		TiXmlDocument* pDoc) {

//	INT32 result = TResult::EUnknownError;


	if (nCode == MER_OK&&pDoc) {
		TiXmlElement *pItem = pDoc->RootElement();

		if (pItem) {
			INT32 nCmdID = 0;
			pItem->QueryIntAttribute("no", &nCmdID);

			if (pItem->QueryIntAttribute("count", &m_nCount) != TIXML_SUCCESS) {
				m_nCount = 0;
			}

			INT32 nErr = 0;
			if (pItem->QueryIntAttribute("errno", &nErr) == TIXML_SUCCESS) {
				if (nErr == 0) {
					if (nCmdID == SERVICE_WE) {

						pItem = pItem->FirstChildElement();

						if(!pItem){
							goto ERR;
						}

						const char *pStr = NULL;

						pStr = pItem->Attribute("wesize");

						if (pStr)
							utf8ncpy(sWesize, pStr, 15);

						pStr = pItem->Attribute("weversion");

						if (pStr)
							utf8ncpy(sWeversion, pStr, 15);

						pStr = pItem->Attribute("weurl");

						if (pStr)
							utf8ncpy(sWeurl, pStr, 599);

						m_pUpdateDataListener->OnUpdateDataFinish(m_UserData,
								TResult::ESuccess);

						return;
					}

				} else if (nErr == MERS_NOTRETURN) {
					goto ERR;
				} else {
					m_pUpdateDataListener->OnUpdateDataFinish(m_UserData,
							TResult::ENothing);
					return;
				}
			}
		}
	} else {
		goto ERR;
	}

	ERR: if (nCmdID == SERVICE_WE)
		m_pUpdateDataListener->OnUpdateDataFinish(m_UserData,
				TResult::EUnknownError);

}

//---------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h>
#include "kbdde.h"

//---------------------------------------------------------------------------
HDDEDATA CALLBACK DefCallback(UINT uType, UINT uFmt,
	HCONV hConv, HSZ hszTpc1, HSZ hszTpc2, HDDEDATA hdata,
	DWORD dwData1, DWORD dwData2);
HDDEDATA CALLBACK DefCallback(UINT uType, UINT uFmt,
	HCONV hConv, HSZ hszTpc1, HSZ hszTpc2, HDDEDATA hdata,
	DWORD dwData1, DWORD dwData2)
{
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
KbDDE::KbDDE(PFNCALLBACK pfnCallBack, LPCWSTR cszTopic, LPCWSTR cszService)
{
	m_ddeInst = 0;
	m_hszService = NULL;
	m_hszTopic = NULL;
	wcscpy(m_szTopicName, cszTopic);
	wcscpy(m_szServiceName, cszService);
	if (!pfnCallBack) {
		pfnCallBack = DefCallback;
	}
	if (DdeInitialize(&m_ddeInst, pfnCallBack, APPCLASS_STANDARD, 0)
		!= DMLERR_NO_ERROR) {
		m_ddeInst = 0;
		return;
	}
	m_hszService = DdeCreateStringHandle(m_ddeInst, m_szServiceName, CP_WINANSI);
	m_hszTopic = DdeCreateStringHandle(m_ddeInst, m_szTopicName, CP_WINANSI);
	if (DdeGetLastError(m_ddeInst) != DMLERR_NO_ERROR) {
		DdeUninitialize(m_ddeInst);
		m_ddeInst = 0;
		m_hszService = NULL;
		m_hszTopic = NULL;
		return;
	}
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
KbDDE::~KbDDE(void)
{
	if (!m_ddeInst)
		return;
	DdeFreeStringHandle(m_ddeInst, m_hszService);
	DdeFreeStringHandle(m_ddeInst, m_hszTopic);
	DdeUninitialize(m_ddeInst);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
DWORD __fastcall KbDDEServer::QueryString(HSZ hsz, wchar_t  *szBuffer, int Size)
{
	return DdeQueryString(m_ddeInst, hsz, szBuffer, Size, CP_WINANSI);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
HDDEDATA __fastcall KbDDEServer::CreateDataHandle(LPBYTE pSrc, DWORD cb, HSZ hsz, UINT wFmt)
{
	return DdeCreateDataHandle(m_ddeInst, pSrc, cb, 0, hsz, wFmt, 0);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*

	KbDDEServer

	*/
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
KbDDEServer::KbDDEServer(PFNCALLBACK pfnCallBack, LPCWSTR cszTopic, LPCWSTR cszService)
:KbDDE(pfnCallBack, cszTopic, cszService)
{
	DdeNameService(m_ddeInst, m_hszService, 0, DNS_REGISTER);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
KbDDEServer::~KbDDEServer(void)
{
	if (m_ddeInst)
		DdeNameService(m_ddeInst, m_hszService, 0, DNS_UNREGISTER);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*

	KbDDEClient

	*/
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
KbDDEClient::KbDDEClient(PFNCALLBACK pfnCallBack, LPCWSTR cszTopic, LPCWSTR cszService)
:KbDDE(pfnCallBack, cszTopic, cszService)
{
	m_hConv = DdeConnect(m_ddeInst, m_hszService, m_hszTopic, NULL);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
KbDDEClient::~KbDDEClient(void)
{
	if (m_hConv) {
		DdeDisconnect(m_hConv);
	}
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
HDDEDATA KbDDEClient::ClientTransaction(
	LPBYTE pData,       // �T�[�o�[�ɓn���f�[�^�̐擪�o�C�g�̃|�C���^
	DWORD cbData,       // �f�[�^�̒���
	//    HCONV hConv,        // �ʐM�n���h��
	HSZ hszItem,        // �f�[�^���ڂ̃n���h��
	UINT wFmt,          // �N���b�v�{�[�h�t�H�[�}�b�g
	UINT wType,         // �g�����U�N�V�����^�C�v
	DWORD dwTimeout,    // �҂�����
	LPDWORD pdwResult   // �g�����U�N�V�����̌��ʂւ̃|�C���^
	)
{
	if (!m_hConv)return NULL;
	return DdeClientTransaction(
		pData,       // �T�[�o�[�ɓn���f�[�^�̐擪�o�C�g�̃|�C���^
		cbData,      // �f�[�^�̒���
		m_hConv,     // �ʐM�n���h��
		hszItem,     // �f�[�^���ڂ̃n���h��
		wFmt,        // �N���b�v�{�[�h�t�H�[�}�b�g
		wType,       // �g�����U�N�V�����^�C�v
		dwTimeout,   // �҂�����
		pdwResult    // �g�����U�N�V�����̌��ʂւ̃|�C���^
		);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool __fastcall KbDDEClient::Execute(LPCWSTR cszFileName,
	LPCWSTR cszCommand)
{
	HDDEDATA hRet;
	HSZ hszTopic;
	static LPCWSTR cszEmpty = L"";
	if (!m_hConv) {
		return false;
	}
	if (!cszCommand)
		cszCommand = cszEmpty;
	if (!cszFileName)
		cszFileName = cszEmpty;

	int lenFileName = wcslen(cszFileName);
	int lenCommand = wcslen(cszCommand);
	int szTopicLen = lenFileName + lenCommand + 8;
	wchar_t  *szTopic = new wchar_t[szTopicLen + 1];
	if (lenFileName) {
		szTopic[0] = '\"';
		wcscpy(&szTopic[1], cszFileName);
		wcscat(szTopic, L"\" ");
	} else {
		szTopic[0] = 0;
	}
	wcscat(szTopic, cszCommand);
	hszTopic = DdeCreateStringHandle(m_ddeInst, szTopic, CP_WINANSI);
	hRet = DdeClientTransaction(
		(BYTE*)szTopic,
		szTopicLen,
		m_hConv,
		NULL,
		NULL,/*CF_TEXT,*/
		XTYP_EXECUTE,
		2000,//�ҋ@����
		NULL);

	delete[] szTopic;
	if (!hRet && DdeGetLastError(m_ddeInst) != DMLERR_NO_ERROR) {
		//MessageBeep(MB_OK);
		return false;
	} else if (hRet) {
		DdeFreeStringHandle(m_ddeInst, hszTopic);
		DdeFreeDataHandle(hRet);
	}
	return true;
}

bool __fastcall KbDDEClient::Execute2(LPCWSTR cszFileName,
	LPCWSTR cszCommand)
{
	HDDEDATA hRet;
	HSZ hszTopic;
	static LPCWSTR cszEmpty = L"";
	if (!m_hConv) {
		return false;
	}
	if (!cszCommand)
		cszCommand = cszEmpty;
	if (!cszFileName)
		cszFileName = cszEmpty;

	int lenFileName = wcslen(cszFileName);
	int lenCommand = wcslen(cszCommand);
	int szTopicLen = lenFileName + lenCommand + 8;
	wchar_t  *szFileName = new wchar_t[lenFileName + 3 + 1];
	if (lenFileName) {
		wcscpy(szFileName, L" \"");
		wcscat(&szFileName[2], cszFileName);
		wcscat(szFileName, L"\"");
	} else {
		szFileName[0] = 0;
	}
	wchar_t  *szTopic = new wchar_t[szTopicLen + 1];
	wcscpy(szTopic, cszCommand);
	wcscat(szTopic, szFileName);
	hszTopic = DdeCreateStringHandle(m_ddeInst, szTopic, CP_WINANSI);
	hRet = DdeClientTransaction(
		(BYTE*)szTopic,
		szTopicLen,
		m_hConv,
		NULL,
		NULL,/*CF_TEXT,*/
		XTYP_EXECUTE,
		2000,//�ҋ@����
		NULL);

	delete[] szTopic;
	delete[] szFileName;
	if (!hRet && DdeGetLastError(m_ddeInst) != DMLERR_NO_ERROR) {
		//MessageBeep(MB_OK);
		return false;
	} else if (hRet) {
		DdeFreeStringHandle(m_ddeInst, hszTopic);
		DdeFreeDataHandle(hRet);
	}
	return true;
}

bool __fastcall KbDDEClient::Execute(LPCWSTR cszCommand, DWORD dwWait) /* Misirlou 138 */
{
	if (!m_hConv) {
		return false;
	}
	if (!cszCommand)
		return false;
	int cbData = wcslen(cszCommand) + 1;
	BYTE *pData = new BYTE[cbData];
	wcscpy((wchar_t*)pData, cszCommand);
	HDDEDATA hRet = DdeClientTransaction(
		pData,
		cbData,
		m_hConv,
		NULL,
		CF_TEXT,
		XTYP_EXECUTE,
		dwWait,//�ҋ@����
		NULL);
	delete[] pData;
	if (!hRet && DdeGetLastError(m_ddeInst) != DMLERR_NO_ERROR) {
		return false;
	} else {
		if (hRet) {
			DdeFreeDataHandle(hRet);
		}
		return true;
	}
}
/*
const wchar_t* __fastcall kbGetCommandLineParams(void)
{//�N�����̃R�}���h���C��������Ԃ�
//�i���s�t�@�C�����̕����͏����j
const wchar_t *szCommandLine = ::GetCommandLine();
const wchar_t *p = szCommandLine;
bool bDblQuote = false;
while(*p == ' ')p++;
if(*p == '"'){//��d���p���Ŋ����Ă���
p++;
bDblQuote = true;
}
while(*p){
if(bDblQuote && *p == '"'){//��d���p���̏I���
p++;
break;
}
else if(!bDblQuote && *p == ' '){
p++;
break;
}
if(IsDBCSLeadByte((BYTE)*p)){
p+=2;
}
else{
p++;
}
}
while(*p == ' ')p++;
return p;
}
*/
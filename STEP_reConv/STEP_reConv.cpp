// STEP_reConv.cpp : DLL �p�̏����������̒�`���s���܂��B
//

#include "stdafx.h"
#include "STEP_reConv.h"
#include "STEPlugin.h"

#include "imm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	����!
//
//		���� DLL �� MFC DLL �ɑ΂��ē��I�Ƀ����N�����ꍇ�A
//		MFC ���ŌĂяo����邱�� DLL ����G�N�X�|�[�g���ꂽ
//		�ǂ̊֐����֐��̍ŏ��ɒǉ������ AFX_MANAGE_STATE 
//		�}�N�����܂�ł��Ȃ���΂Ȃ�܂���B
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �ʏ�֐��̖{�̂͂��̈ʒu�ɂ���܂�
//		}
//
//		���̃}�N�����e�֐��Ɋ܂܂�Ă��邱�ƁAMFC ����
//		�ǂ̌Ăяo�����D�悷�邱�Ƃ͔��ɏd�v�ł��B
//		����͊֐����̍ŏ��̃X�e�[�g�����g�łȂ���΂�
//		��Ȃ����Ƃ��Ӗ����܂��A�R���X�g���N�^�� MFC 
//		DLL ���ւ̌Ăяo�����s���\��������̂ŁA�I�u
//		�W�F�N�g�ϐ��̐錾�����O�łȂ���΂Ȃ�܂���B
//
//		�ڍׂɂ��Ă� MFC �e�N�j�J�� �m�[�g 33 �����
//		58 ���Q�Ƃ��Ă��������B
//

/////////////////////////////////////////////////////////////////////////////
// CSTEP_reConvApp

BEGIN_MESSAGE_MAP(CSTEP_reConvApp, CWinApp)
	//{{AFX_MSG_MAP(CSTEP_reConvApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTEP_reConvApp �̍\�z

CSTEP_reConvApp::CSTEP_reConvApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance �̒��̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CSTEP_reConvApp �I�u�W�F�N�g

CSTEP_reConvApp theApp;

UINT nPluginID;

CString strINI;

// �R�}���hID
UINT nIDReConvHiragana;
UINT nIDReConvRomaji;

void AddConvMenu(HMENU hMenu) {
	InsertMenu(hMenu, MF_BYPOSITION, MF_BYPOSITION | MFT_SEPARATOR, 0, NULL);
	InsertMenu(hMenu, MF_BYPOSITION, MF_BYPOSITION | MFT_STRING, nIDReConvHiragana, "�Ђ炪�Ȃɕϊ�");
	InsertMenu(hMenu, MF_BYPOSITION, MF_BYPOSITION | MFT_STRING, nIDReConvRomaji, "���[�}���ɕϊ�");
}

STEP_API bool WINAPI STEPInit(UINT pID, LPCTSTR szPluginFolder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (Initialize() == false)	return false;
	nPluginID = pID;

	// INI�t�@�C���̓ǂݍ���
	strINI = szPluginFolder;
	strINI += "STEP_reConv.ini";

	nIDReConvHiragana = STEPGetCommandID();
	STEPKeyAssign(nIDReConvHiragana, "�Ђ炪�Ȃɕϊ�", "STEP_reConv_KEY_RE_CONV_HIRAGANA");
	nIDReConvRomaji = STEPGetCommandID();
	STEPKeyAssign(nIDReConvRomaji, "���[�}���ɕϊ�", "STEP_reConv_KEY_RE_CONV_ROMAJI");

	return true;
}

STEP_API void WINAPI STEPFinalize() {
	Finalize();
}

STEP_API UINT WINAPI STEPGetAPIVersion(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return STEP_API_VERSION;
}

STEP_API LPCTSTR WINAPI STEPGetPluginName(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return "STEP_reConv";
}

STEP_API LPCTSTR WINAPI STEPGetPluginInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return "Version 0.03 Copyright (C) 2003-2006 haseta\r\nMS-IME2000/2002�ɂ��Ђ炪��/���[�}���ɕϊ����܂�";
}

STEP_API LPCTSTR WINAPI STEPGetStatusMessage(UINT nID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (nID == nIDReConvHiragana) {
		return "�I������Ă���͈͂��Ђ炪�Ȃɕϊ����܂�";
	}
	if (nID == nIDReConvRomaji) {
		return "�I������Ă���͈͂����[�}���ɕϊ����܂�";
	}
	return NULL;
}

STEP_API bool WINAPI STEPOnUpdateCommand(UINT nID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (nID == nIDReConvHiragana) {
		if (STEPIsRangeSelected() || STEPIsCurrentCellEditOK()) return true;
		else return false;
	}
	if (nID == nIDReConvRomaji) {
		if (STEPIsRangeSelected() || STEPIsCurrentCellEditOK()) return true;
		else return false;
	}
	return false;
}

// strcnv.cpp
enum	{CONV_SUJI=1, CONV_ALPHA=2, CONV_KATA=4, CONV_KIGOU=8, CONV_ALL=15};
#ifdef __cplusplus
extern "C" {
#endif

extern	int conv_han2zens(wchar_t *, const wchar_t *, int);
extern	int conv_zen2hans(wchar_t *, const wchar_t *, int);
extern	void conv_kata2hira(wchar_t *);
extern	void conv_kata_erase_dakuon(wchar_t *);
extern	void conv_hira2kata(wchar_t *);
extern	void conv_upper(wchar_t *);
extern	void conv_lower(wchar_t *);
extern	void conv_first_upper(wchar_t *);
//extern	DWORD conv_kan2hira(HWND, wchar_t *, DWORD);
//extern	void conv_romaji(HWND hwnd, wchar_t *str, wchar_t *sRomaji);
#ifdef __cplusplus
}
#endif
CString conv_kan2hira(HWND hWnd, wchar_t * str)
{
	CString strText = str;
	// MS-IME2000�ł͂��܂����������AATOK16�ł͂��߁B�P��P�ʂł���΂ł���...
	HIMC himc = ::ImmGetContext(hWnd);
	DWORD dwRet = ::ImmGetConversionList(
					 ::GetKeyboardLayout(0), himc,
					 (const char *)str, NULL, 0,
					 GCL_REVERSECONVERSION);

	// �ǂ݉����i�[�̈���m�� 
	CANDIDATELIST *lpCand;
	lpCand = (CANDIDATELIST *)malloc(dwRet);
	// �ǂ݉������擾
	dwRet = ::ImmGetConversionList(
					 ::GetKeyboardLayout(0), himc,
					 (const char*)str, lpCand, dwRet,
					 GCL_REVERSECONVERSION);
	if (dwRet > 0 && lpCand->dwCount > 0) {
		char *work = (char*)lpCand + lpCand->dwOffset[0];
		strText = work;

		/*
		for (unsigned int i = 0; i< lpCand->dwCount; i++)
		{
			TRACE("%s", (LPBYTE)lpCand + lpCand->dwOffset[i]);
		}
		*/
	}

	free(lpCand);
	::ImmReleaseContext(hWnd, himc);
	return strText;
}

CString conv_romaji(HWND hwnd, wchar_t *str)
{
	static const char *romaji[] = {
		"������", "KKYA", "������", "KKYU", "������", "KYO",
		"����", "KYA", "����", "KYU", "����", "KYO",
		"������", "SSHA", "������", "SSHU", "������", "SSHO",
		"����", "SHA", "����", "SHU", "����", "SHO",
		"������", "CCHA", "������", "CCHU", "������", "CCHO",
		"����", "CHA", "����", "CHU", "����", "CHO",
		"���ɂ�", "NNYA", "���ɂ�", "NNYU", "���ɂ�", "NNYO",
		"�ɂ�", "NYA", "�ɂ�", "NYU", "�ɂ�", "NYO",
		"���Ђ�", "HHYA", "���Ђ�", "HHYU", "���Ђ�", "HHYO",
		"�Ђ�", "HYA", "�Ђ�", "HYU", "�Ђ�", "HYO",
		"���݂�", "MMYA", "���݂�", "MMYU", "���݂�", "MMYO",
		"�݂�", "MYA", "�݂�", "MYU", "�݂�", "MYO",
		"�����", "RRYA", "�����", "RRYU", "�����", "RRYO",
		"���", "RYA", "���", "RYU", "���", "RYO",
		"������", "GGYA", "������", "GGYU", "������", "GGYO",
		"����", "GYA", "����", "GYU", "����", "GYO",
		"������", "JJA", "������", "JJU", "������", "JJO",
		"����", "JA", "����", "JU", "����", "JO",
		"���т�", "BBYA", "���т�", "BBYU", "���т�", "BBYO",
		"�т�", "BYA", "�т�", "BYU", "�т�", "BYO",
		"���҂�", "PPYA", "���҂�", "PPYU", "���҂�", "PPYO",
		"�҂�", "PYA", "�҂�", "PYU", "�҂�", "PYO",

		"����", "KKA", "����", "KKI", "����", "KKU", "����", "KKE", "����", "KKO",
		"��", "KA", "��", "KI", "��", "KU", "��", "KE", "��", "KO",
		"����", "SSA", "����", "SSHI", "����", "SSU", "����", "SSE", "����", "SSO",
		"��", "SA", "��", "SHI", "��", "SU", "��", "SE", "��", "SO",
		"����", "TTA", "����", "CCHI", "����", "TTSU", "����", "TTE", "����", "TTO",
		"��", "TA", "��", "CHI", "��", "TSU", "��", "TE", "��", "TO",
		"����", "NNA", "����", "NNI", "����", "NNU", "����", "NNE", "����", "NNO",
		"��", "NA", "��", "NI", "��", "NU", "��", "NE", "��", "NO",
		"����", "HHA", "����", "HHI", "����", "FFU", "����", "HHE", "����", "HHO",
		"��", "HA", "��", "HI", "��", "FU", "��", "HE", "��", "HO",
		"����", "MMA", "����", "MMI", "����", "MMU", "����", "MME", "����", "MMO",
		"��", "MA", "��", "MI", "��", "MU", "��", "ME", "��", "MO",
		"����", "YYA", "����", "YUYU", "����", "YYO",
		"��", "YA", "��", "YU", "��", "YO",
		"����", "RRA", "����", "RRI", "����", "RRU", "����", "RRE", "����", "RRO",
		"��", "RA", "��", "RI", "��", "RU", "��", "RE", "��", "RO",
		"����", "WWA",
		"��", "WA",
		"����", "GGA", "����", "GGI", "����", "GGU", "����", "GGE", "����", "GGO",
		"��", "GA", "��", "GI", "��", "GU", "��", "GE", "��", "GO",
		"����", "ZZA", "����", "JJI", "����", "ZZU", "����", "ZZE", "����", "ZZO",
		"��", "ZA", "��", "JI", "��", "ZU", "��", "ZE", "��", "ZO",
		"����", "DDA", "����", "JJI", "����", "ZZU", "����", "DDE", "����", "DDO",
		"��", "DA", "��", "JI", "��", "ZU", "��", "DE", "��", "DO",
		"����", "BBA", "����", "BBI", "����", "BBU", "����", "BBE", "����", "BBO",
		"��", "BA", "��", "BI", "��", "BU", "��", "BE", "��", "BO",
		"����", "PPA", "����", "PPI", "����", "PPU", "����", "PPE", "����", "PPO",
		"��", "PA", "��", "PI", "��", "PU", "��", "PE", "��", "PO",

		"����", "AA", "����", "II", "����", "UU", "����", "EE", "����", "OO",
		"��", "A", "��", "I", "��", "U", "��", "E", "��", "O",
		"����", "OO", "����", "NN",
		"��", "O", "��", "N",
		"�[", "",
		NULL, NULL,
	};

	CString	strWork, strRep;
	int		nPos;
	int nRomaji = 0;

	strWork = str;
	/*
	while (romaji[nRomaji*2] != NULL) {
		while((nPos = strWork.Find(romaji[nRomaji*2])) != -1) {
			int		nLenOrg = strWork.GetLength();
			int		nLenKey = wcslen(romaji[nRomaji*2]);
			strRep = romaji[nRomaji*2+1];
			conv_lower((wchar_t *)strRep.GetBuffer(0));
			strRep.ReleaseBuffer();
			strWork.Format("%s%s%s", strWork.Left(nPos), strRep, strWork.Right(nLenOrg-(nPos+nLenKey)));
		}
		nRomaji++;
	}
	*/

	strWork = conv_kan2hira(hwnd, (unsigned char*)strWork.GetBuffer(0));

	nRomaji = 0;
	while (romaji[nRomaji*2] != NULL) {
		while((nPos = strWork.Find(romaji[nRomaji*2])) != -1) {
			int		nLenOrg = strWork.GetLength();
			int		nLenKey = wcslen(romaji[nRomaji*2]);
			strRep = romaji[nRomaji*2+1];
			conv_lower((wchar_t *)strRep.GetBuffer(0));
			strRep.ReleaseBuffer();
			conv_first_upper((wchar_t *)strRep.GetBuffer(0));
			strRep.ReleaseBuffer();
			strWork.Format("%s%s%s", strWork.Left(nPos), strRep, strWork.Right(nLenOrg-(nPos+nLenKey)));
		}
		nRomaji++;
	}

	conv_zen2hans((wchar_t *)strRep.GetBuffer(strWork.GetLength()*2+1), (const wchar_t *)(const char *)strWork, CONV_ALL);
	strWork.ReleaseBuffer();
	strRep.ReleaseBuffer();
	return strRep;
}

STEP_API bool WINAPI STEPOnCommand(UINT nID, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (nID == nIDReConvHiragana) {
		static	const char *sMessage = "MS-IME2002/2000�ȊO�ł͐���ɓ��삵�Ȃ��\��������܂��B\n\n"
									   "�ϊ������s���Ă���낵���ł����H";
		static bool bKan2HiraConfirmIME = false;
		if (bKan2HiraConfirmIME == true || MessageBox(hWnd, sMessage, "�Ђ炪�Ȃɕϊ�", MB_YESNO|MB_TOPMOST) == IDYES) {
			bKan2HiraConfirmIME = true;
			int sx, sy, ex, ey;
			if (STEPGetSelectedRange(&sx, &sy, &ex, &ey)) {
				for (int nItem = sy; nItem <= ey; nItem++) {
					if (STEPIsItemFile(nItem) == true) {
						//FILE_INFO info;
						//STEPGetFileInfo(nItem, &info);
						for (int nColumn = sx; nColumn <= ex; nColumn++) {
							CString	strText;
							// �Z���̃e�L�X�g���擾
							strText = conv_kan2hira(hWnd, (unsigned char*)STEPGetSubItemText(nItem, nColumn));
							STEPChangeSubItemText(nItem, nColumn, (LPCTSTR)conv_kan2hira(hWnd, (unsigned char*)strText.GetBuffer(0)));
						}
					}
				}
			}
		}
		return true;
	}
	if (nID == nIDReConvRomaji) {
		static	const char *sMessage = "MS-IME2002/2000�ȊO�ł͐���ɓ��삵�Ȃ��\��������܂��B\n\n"
									   "�ϊ������s���Ă���낵���ł����H";
		static bool bRomajiConfirmIME = false;
		if (bRomajiConfirmIME == true || MessageBox(hWnd, sMessage, "���[�}���ɕϊ�", MB_YESNO|MB_TOPMOST) == IDYES) {
			int sx, sy, ex, ey;
			if (STEPGetSelectedRange(&sx, &sy, &ex, &ey)) {
				for (int nItem = sy; nItem <= ey; nItem++) {
					if (STEPIsItemFile(nItem) == true) {
						//FILE_INFO info;
						//STEPGetFileInfo(nItem, &info);
						for (int nColumn = sx; nColumn <= ex; nColumn++) {
							CString	strText;
							// �Z���̃e�L�X�g���擾
							strText = conv_romaji(hWnd, (unsigned char*)STEPGetSubItemText(nItem, nColumn));
							STEPChangeSubItemText(nItem, nColumn, (LPCTSTR)conv_kan2hira(hWnd, (unsigned char*)strText.GetBuffer(0)));
						}
					}
				}
			}
		}
		return true;
	}
	return false;
}

STEP_API void WINAPI STEPOnLoadMenu(HMENU hMenu, UINT nType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	switch (nType) {
	case MENU_FILE_EDIT_OK:
		AddConvMenu(hMenu);
		break;
	}
}

STEP_API void WINAPI STEPOnLoadMainMenu()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// ���j���[�ւ̒ǉ�
	HMENU hMenu = STEPGetMenu(MENU_CONV);
	AddConvMenu(hMenu);
}

bool g_bZenHanKigouKana = true; /* STEP 016 */

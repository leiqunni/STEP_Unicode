// MyFileDialogPlaylist.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "MyFileDialogPlaylist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileDialogPlaylist

IMPLEMENT_DYNAMIC(CMyFileDialogPlaylist, CFileDialog)

CMyFileDialogPlaylist::CMyFileDialogPlaylist(BOOL bOpenFileDialog, LPCWSTR lpszDefExt, LPCWSTR lpszFileName,
		DWORD dwFlags, LPCWSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	custom = NULL;
	TRY {
		// Legacy OS [ - Windows XP]
		SetTemplate(0, IDD_CUSTOM_FILE_OPEN_PLAYLIST);
	} CATCH (CNotSupportedException,e){
		// New OS [ Windows Vista - ]
		custom = this->GetIFileDialogCustomize();
		if(custom != NULL){
			custom->AddCheckButton(IDC_CH_SHOW_LOAD_PLAYLIST,L"�v���C���X�g���͐ݒ�_�C�A���O��\������",false);
			custom->Release();
		}
	}
	END_CATCH
	m_bShowLoadPlaylistDlg = TRUE;
}


BEGIN_MESSAGE_MAP(CMyFileDialogPlaylist, CFileDialog)
	//{{AFX_MSG_MAP(CMyFileDialogPlaylist)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CMyFileDialogPlaylist::OnFileNameOK()
{
	if(custom == NULL){
		// Legacy OS [ - Windows XP]
		m_bShowLoadPlaylistDlg = ((CButton *)GetDlgItem(IDC_CH_SHOW_LOAD_PLAYLIST))->GetCheck();
	} else {
		// New OS [ Windows Vista - ]
		custom = this->GetIFileDialogCustomize();
		custom->GetCheckButtonState(IDC_CH_SHOW_LOAD_PLAYLIST,&m_bShowLoadPlaylistDlg);
		custom->Release();
	}
	return(0);
}

void  CMyFileDialogPlaylist::OnInitDone()
{
	CFileDialog::OnInitDone();
	((CButton *)GetDlgItem(IDC_CH_SHOW_LOAD_PLAYLIST))->SetCheck(m_bShowLoadPlaylistDlg);
}
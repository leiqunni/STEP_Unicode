// MyFileDialog.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "MyFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileDialog

IMPLEMENT_DYNAMIC(CMyFileDialog, CFileDialog)

CMyFileDialog::CMyFileDialog(BOOL bOpenFileDialog, LPCWSTR lpszDefExt, LPCWSTR lpszFileName,
		DWORD dwFlags, LPCWSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	custom = NULL;
	TRY {
		// Legacy OS [ - Windows XP]
		SetTemplate(0, IDD_CUSTOM_FILE_OPEN);
	} CATCH (CNotSupportedException,e){
		// New OS [ Windows Vista - ]
		custom = this->GetIFileDialogCustomize();
		if(custom != NULL){
			custom->AddCheckButton(IDC_CH_FILE_ADDPEND,L"�㏑���̏ꍇ�̓t�@�C���̍Ō�ɒǉ��o�͂���",false);
		}
		custom->Release();
	}
	END_CATCH
	m_bIsWriteAppend = FALSE;
}

BEGIN_MESSAGE_MAP(CMyFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CMyFileDialog)
		// ���� -  ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMyFileDialog::OnFileNameOK( )
{
	if(custom == NULL){
		// Legacy OS [ - Windows XP]
		m_bIsWriteAppend = ((CButton *)GetDlgItem(IDC_CH_FILE_ADDPEND))->GetCheck();
	} else {
		// New OS [ Windows Vista - ]
		custom = this->GetIFileDialogCustomize();
		custom->GetCheckButtonState(IDC_CH_FILE_ADDPEND,&m_bIsWriteAppend);
		custom->Release();
	}
	return(0);
}

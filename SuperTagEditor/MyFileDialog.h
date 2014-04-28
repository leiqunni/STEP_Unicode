#if !defined(AFX_MYFILEDIALOG_H__67E743D3_C819_4A59_ABA0_B0D25E9EB131__INCLUDED_)
#define AFX_MYFILEDIALOG_H__67E743D3_C819_4A59_ABA0_B0D25E9EB131__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFileDialog.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMyFileDialog �_�C�A���O

class CMyFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CMyFileDialog)

public:
	CMyFileDialog(BOOL bOpenFileDialog, // TRUE �Ȃ�� FileOpen�A FALSE �Ȃ�� FileSaveAs
		LPCWSTR lpszDefExt = NULL,
		LPCWSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,
		LPCWSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

	BOOL	m_bIsWriteAppend;
	IFileDialogCustomize* custom;

protected:
	//{{AFX_MSG(CMyFileDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	virtual BOOL OnFileNameOK( );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MYFILEDIALOG_H__67E743D3_C819_4A59_ABA0_B0D25E9EB131__INCLUDED_)

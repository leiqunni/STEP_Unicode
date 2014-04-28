#if !defined(AFX_MYFILEDIALOGPLAYLIST_H__ED73F544_5953_4A29_9311_7775A9CCB828__INCLUDED_)
#define AFX_MYFILEDIALOGPLAYLIST_H__ED73F544_5953_4A29_9311_7775A9CCB828__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFileDialogPlaylist.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMyFileDialogPlaylist �_�C�A���O

class CMyFileDialogPlaylist : public CFileDialog
{
	DECLARE_DYNAMIC(CMyFileDialogPlaylist)

public:
	BOOL OnFileNameOK();
	void OnInitDone();
	IFileDialogCustomize* custom;
	BOOL m_bShowLoadPlaylistDlg;
	CMyFileDialogPlaylist(BOOL bOpenFileDialog, // TRUE �Ȃ�� FileOpen�A FALSE �Ȃ�� FileSaveAs
		LPCWSTR lpszDefExt = NULL,
		LPCWSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCWSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(CMyFileDialogPlaylist)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MYFILEDIALOGPLAYLIST_H__ED73F544_5953_4A29_9311_7775A9CCB828__INCLUDED_)

#if !defined(AFX_DLGDEFINESHEET_H__2C765F2A_BD1E_11D3_9459_00402641B29B__INCLUDED_)
#define AFX_DLGDEFINESHEET_H__2C765F2A_BD1E_11D3_9459_00402641B29B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEnvSheet.h : �w�b�_�[ �t�@�C��
//

#include "OptionPage/OptionSheet.h"

class CSuperTagEditorDoc;

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvSheet

class CDlgEnvSheet : public COptionSheet/*CPropertySheet*/
{
	DECLARE_DYNAMIC(CDlgEnvSheet)

// �R���X�g���N�V����
public:
	CDlgEnvSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDlgEnvSheet(LPCWSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// �A�g���r���[�g
public:
	CSuperTagEditorDoc	*m_pDoc;

// �I�y���[�V����
public:
	enum	{ENV_NORMAL = 1, ENV_CONV = 2, ENV_ADVANCED = 4, ENV_ALL = 7};
	int		DoModal(int);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgEnvSheet)
	public:
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CDlgEnvSheet();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CDlgEnvSheet)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGDEFINESHEET_H__2C765F2A_BD1E_11D3_9459_00402641B29B__INCLUDED_)

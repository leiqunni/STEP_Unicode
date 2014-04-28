// DlgTeikeiPaste.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "DlgTeikeiPaste.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTeikeiPaste �_�C�A���O


CDlgTeikeiPaste::CDlgTeikeiPaste(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTeikeiPaste::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTeikeiPaste)
	m_nTeikeiPaste = -1;
	m_bAddSpace = FALSE;
	m_strFront = L"";
	m_strBack = L"";
	m_bAddChar = FALSE;
	m_bShowDialog = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgTeikeiPaste::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTeikeiPaste)
	DDX_Radio(pDX, IDC_RADIO_REPLACE, m_nTeikeiPaste);
	DDX_Check(pDX, IDC_CHECK_ADD_SPACE, m_bAddSpace);
	DDX_Text(pDX, IDC_EDIT_ADD_FRONT, m_strFront);
	DDX_Text(pDX, IDC_EDIT_ADD_BACK, m_strBack);
	DDX_Check(pDX, IDC_CHECK_ADD_CHAR, m_bAddChar);
	DDX_Check(pDX, IDC_CH_SHOW_DIALOG, m_bShowDialog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTeikeiPaste, CDialog)
	//{{AFX_MSG_MAP(CDlgTeikeiPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTeikeiPaste ���b�Z�[�W �n���h��

BOOL CDlgTeikeiPaste::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	if (!m_strTitle.IsEmpty()) {
		SetWindowText(m_strTitle);
	}
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

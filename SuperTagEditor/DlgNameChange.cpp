// DlgNameChange.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "DlgNameChange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNameChange �_�C�A���O


CDlgNameChange::CDlgNameChange(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNameChange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNameChange)
	m_strName = L"";
	//}}AFX_DATA_INIT
}


void CDlgNameChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNameChange)
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNameChange, CDialog)
	//{{AFX_MSG_MAP(CDlgNameChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNameChange ���b�Z�[�W �n���h��

BOOL CDlgNameChange::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// �I����Ԃɂ���
	m_editName.SetSel(0, -1);

	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CDlgNameChange::OnOK() 
{
	CDialog::OnOK();

	if (m_strName.IsEmpty() == TRUE) {
		m_strName = L"���̖��ݒ�";
	}
}

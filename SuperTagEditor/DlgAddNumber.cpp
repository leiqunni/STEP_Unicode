// DlgAddNumber.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "DlgAddNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAddNumber �_�C�A���O


DlgAddNumber::DlgAddNumber(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAddNumber::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAddNumber)
	m_nWidth = 0;
	m_strSeparator = L"";
	m_nAddPosition = -1;
	m_bSpaceInitNumber = TRUE;
	m_nAddNumber = 0;
	m_nInitNumber = 0;
	m_strAfter = L"";
	m_strBefore = L"";
	//}}AFX_DATA_INIT
}


void DlgAddNumber::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAddNumber)
	DDX_Text(pDX, IDC_EDIT_NUMBER_WIDTH, m_nWidth);
	DDV_MinMaxUInt(pDX, m_nWidth, 1, 99);
	DDX_Text(pDX, IDC_EDIT_NUMBER_SEPARATOR, m_strSeparator);
	DDX_Radio(pDX, IDC_RADIO_ADD_START, m_nAddPosition);
	DDX_Check(pDX, IDC_CH_SPACE_INIT, m_bSpaceInitNumber);
	DDX_Text(pDX, IDC_ED_ADD_NUMBER, m_nAddNumber);
	DDV_MinMaxUInt(pDX, m_nAddNumber, 1, 99);
	DDX_Text(pDX, IDC_ED_INIT_NUMBER, m_nInitNumber);
	DDV_MinMaxUInt(pDX, m_nInitNumber, 0, 9999);
	DDX_Text(pDX, IDC_EDIT_ADD_AFTER, m_strAfter);
	DDX_Text(pDX, IDC_EDIT_ADD_BEFORE, m_strBefore);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAddNumber, CDialog)
	//{{AFX_MSG_MAP(DlgAddNumber)
	ON_BN_CLICKED(IDC_RADIO_REPLACE, OnRadioReplace)
	ON_BN_CLICKED(IDC_RADIO_ADD_END, OnRadioReplace)
	ON_BN_CLICKED(IDC_RADIO_ADD_START, OnRadioReplace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAddNumber ���b�Z�[�W �n���h��

void DlgAddNumber::OnRadioReplace() /* Conspiracy 194 */
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	UpdateData();
	CWnd* item1 = GetDlgItem(IDC_EDIT_NUMBER_SEPARATOR);
	CWnd* item2 = GetDlgItem(IDC_EDIT_ADD_BEFORE);
	CWnd* item3 = GetDlgItem(IDC_EDIT_ADD_AFTER);
	if (m_nAddPosition == 2) {
		item1->EnableWindow(FALSE);
		item2->EnableWindow(TRUE);
		item3->EnableWindow(TRUE);
	} else {
		item1->EnableWindow(TRUE);
		item2->EnableWindow(FALSE);
		item3->EnableWindow(FALSE);
	}
}

BOOL DlgAddNumber::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	OnRadioReplace(); /* Conspiracy 194 */
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

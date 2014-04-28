// DlgTeikei.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "DlgTeikei.h"
#include "DlgTeikeiPaste.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTeikei �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CDlgTeikei, CPropertyPage)

CDlgTeikei::CDlgTeikei() : CPropertyPage(CDlgTeikei::IDD)
{
	//{{AFX_DATA_INIT(CDlgTeikei)
	m_strTeikei1 = L"";
	m_strTeikei10 = L"";
	m_strTeikei2 = L"";
	m_strTeikei3 = L"";
	m_strTeikei4 = L"";
	m_strTeikei5 = L"";
	m_strTeikei6 = L"";
	m_strTeikei7 = L"";
	m_strTeikei8 = L"";
	m_strTeikei9 = L"";
	m_strGroupName = L"";
	//}}AFX_DATA_INIT
}

CDlgTeikei::~CDlgTeikei()
{
}

void CDlgTeikei::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTeikei)
	DDX_Text(pDX, IDC_EDIT_TEIKEI_01, m_strTeikei1);
	DDV_MaxChars(pDX, m_strTeikei1, 255);
	DDX_Text(pDX, IDC_EDIT_TEIKEI_10, m_strTeikei10);
	DDV_MaxChars(pDX, m_strTeikei10, 255);
	DDX_Text(pDX, IDC_EDIT_TEIKEI_2, m_strTeikei2);
	DDV_MaxChars(pDX, m_strTeikei2, 255);
	DDX_Text(pDX, IDC_EDIT_TEIKEI_3, m_strTeikei3);
	DDV_MaxChars(pDX, m_strTeikei3, 255);
	DDX_Text(pDX, IDC_EDIT_TEIKEI_4, m_strTeikei4);
	DDV_MaxChars(pDX, m_strTeikei4, 255);
	DDX_Text(pDX, IDC_EDIT_TEIKEI_5, m_strTeikei5);
	DDV_MaxChars(pDX, m_strTeikei5, 255);
	DDX_Text(pDX, IDC_EDIT_TEIKEI_6, m_strTeikei6);
	DDV_MaxChars(pDX, m_strTeikei6, 255);
	DDX_Text(pDX, IDC_EDIT_TEIKEI_7, m_strTeikei7);
	DDV_MaxChars(pDX, m_strTeikei7, 255);
	DDX_Text(pDX, IDC_EDIT_TEIKEI_8, m_strTeikei8);
	DDV_MaxChars(pDX, m_strTeikei8, 255);
	DDX_Text(pDX, IDC_EDIT_TEIKEI_9, m_strTeikei9);
	DDV_MaxChars(pDX, m_strTeikei9, 255);
	DDX_Text(pDX, IDC_EDIT_TEIKEI_GROUP_NAME, m_strGroupName);
	DDV_MaxChars(pDX, m_strGroupName, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTeikei, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgTeikei)
	ON_BN_CLICKED(IDC_BT_DETAIL_01, OnBtDetail01)
	ON_BN_CLICKED(IDC_BT_DETAIL_10, OnBtDetail10)
	ON_BN_CLICKED(IDC_BT_DETAIL_02, OnBtDetail02)
	ON_BN_CLICKED(IDC_BT_DETAIL_03, OnBtDetail03)
	ON_BN_CLICKED(IDC_BT_DETAIL_04, OnBtDetail04)
	ON_BN_CLICKED(IDC_BT_DETAIL_05, OnBtDetail05)
	ON_BN_CLICKED(IDC_BT_DETAIL_06, OnBtDetail06)
	ON_BN_CLICKED(IDC_BT_DETAIL_07, OnBtDetail07)
	ON_BN_CLICKED(IDC_BT_DETAIL_08, OnBtDetail08)
	ON_BN_CLICKED(IDC_BT_DETAIL_09, OnBtDetail09)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTeikei ���b�Z�[�W �n���h��

BOOL CDlgTeikei::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������

	if (m_nGroupNumber == 1) {	// ������^�u�̃^�C�g����ύX
		CPropertySheet *poPropSheet = (CPropertySheet *)GetParent();
		TC_ITEM tcItem;
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = (LPTSTR)((LPCWSTR)"�O���[�v�P");
		poPropSheet->GetTabControl()->SetItem(0, &tcItem );
		tcItem.pszText = (LPTSTR)((LPCWSTR)"�O���[�v�Q");
		poPropSheet->GetTabControl()->SetItem(1, &tcItem );
		tcItem.pszText = (LPTSTR)((LPCWSTR)"�O���[�v�R");
		poPropSheet->GetTabControl()->SetItem(2, &tcItem );
	}
	m_strTeikei1 = m_teikeiInfo[0].strTeikei;
	m_strTeikei2 = m_teikeiInfo[1].strTeikei;
	m_strTeikei3 = m_teikeiInfo[2].strTeikei;
	m_strTeikei4 = m_teikeiInfo[3].strTeikei;
	m_strTeikei5 = m_teikeiInfo[4].strTeikei;
	m_strTeikei6 = m_teikeiInfo[5].strTeikei;
	m_strTeikei7 = m_teikeiInfo[6].strTeikei;
	m_strTeikei8 = m_teikeiInfo[7].strTeikei;
	m_strTeikei9 = m_teikeiInfo[8].strTeikei;
	m_strTeikei10 = m_teikeiInfo[9].strTeikei;

	UpdateData(FALSE);

	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CDlgTeikei::OnBtDetail01() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnDetail(0);
}

void CDlgTeikei::OnBtDetail02() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnDetail(1);
}

void CDlgTeikei::OnBtDetail03() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnDetail(2);
}

void CDlgTeikei::OnBtDetail04() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnDetail(3);
}

void CDlgTeikei::OnBtDetail05() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnDetail(4);
}

void CDlgTeikei::OnBtDetail06() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnDetail(5);
}

void CDlgTeikei::OnBtDetail07() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnDetail(6);
}

void CDlgTeikei::OnBtDetail08() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnDetail(7);
}

void CDlgTeikei::OnBtDetail09() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnDetail(8);
}

void CDlgTeikei::OnBtDetail10() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnDetail(9);
}

void CDlgTeikei::OnOK() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	m_teikeiInfo[0].strTeikei = m_strTeikei1;
	m_teikeiInfo[1].strTeikei = m_strTeikei2;
	m_teikeiInfo[2].strTeikei = m_strTeikei3;
	m_teikeiInfo[3].strTeikei = m_strTeikei4;
	m_teikeiInfo[4].strTeikei = m_strTeikei5;
	m_teikeiInfo[5].strTeikei = m_strTeikei6;
	m_teikeiInfo[6].strTeikei = m_strTeikei7;
	m_teikeiInfo[7].strTeikei = m_strTeikei8;
	m_teikeiInfo[8].strTeikei = m_strTeikei9;
	m_teikeiInfo[9].strTeikei = m_strTeikei10;
	
	CPropertyPage::OnOK();
}

void CDlgTeikei::OnDetail(int nIndex)
{
	CDlgTeikeiPaste dlgTeikei;

	dlgTeikei.m_nTeikeiPaste = m_teikeiInfo[nIndex].nTeikeiPaste;
	dlgTeikei.m_bAddSpace = m_teikeiInfo[nIndex].bAddSpace;
	dlgTeikei.m_bAddChar = m_teikeiInfo[nIndex].bAddChar;
	dlgTeikei.m_strFront = m_teikeiInfo[nIndex].strFront;
	dlgTeikei.m_strBack = m_teikeiInfo[nIndex].strBack;
	dlgTeikei.m_bShowDialog = m_teikeiInfo[nIndex].bShowDialog;
	if (dlgTeikei.DoModal() == IDOK) {
		m_teikeiInfo[nIndex].nTeikeiPaste = dlgTeikei.m_nTeikeiPaste;
		m_teikeiInfo[nIndex].bAddSpace = dlgTeikei.m_bAddSpace;
		m_teikeiInfo[nIndex].bAddChar = dlgTeikei.m_bAddChar;
		m_teikeiInfo[nIndex].strFront = dlgTeikei.m_strFront;
		m_teikeiInfo[nIndex].strBack = dlgTeikei.m_strBack;
		m_teikeiInfo[nIndex].bShowDialog = dlgTeikei.m_bShowDialog;
	}
}

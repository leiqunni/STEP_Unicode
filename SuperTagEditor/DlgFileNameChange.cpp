// DlgFileNameChange.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "supertageditor.h"
#include "DlgFileNameChange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFileNameChange �_�C�A���O


CDlgFileNameChange::CDlgFileNameChange(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFileNameChange::IDD, pParent)
{
	m_nMaxChar = 255;
	//{{AFX_DATA_INIT(CDlgFileNameChange)
	m_strFileName = L"";
	m_strMsg = L"";
	m_strOrgFileName = L"";
	//}}AFX_DATA_INIT
}


void CDlgFileNameChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFileNameChange)
	DDX_Control(pDX, IDC_STATIC_MSG, m_staticMsg);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strFileName);
	DDV_MaxChars(pDX, m_strFileName, m_nMaxChar);
	DDX_Text(pDX, IDC_STATIC_MSG, m_strMsg);
	DDX_Text(pDX, IDC_EDIT_NAME_ORG, m_strOrgFileName);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgFileNameChange, CDialog)
	//{{AFX_MSG_MAP(CDlgFileNameChange)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFileNameChange ���b�Z�[�W �n���h��

void CDlgFileNameChange::OnChangeEditName() 
{
	// TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A�R���g���[���́A lParam �}�X�N
	// ���ł̘_���a�� ENM_CHANGE �t���O�t���� CRichEditCrtl().SetEventMask()
	// ���b�Z�[�W���R���g���[���֑��邽�߂� CDialog::OnInitDialog() �֐����I�[�o�[
	// ���C�h���Ȃ����肱�̒ʒm�𑗂�܂���B
	
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CString strFileName;
	m_editName.GetLine(0, strFileName.GetBuffer(m_editName.LineLength(0)*2+sizeof(DWORD)+2), m_editName.LineLength(0)*2+sizeof(DWORD)+2); /* STEP 010 �o�b�t�@�T�C�Y���₵�� *//* �Ȃ�ł������Ǝ擾����Ȃ���������̂ł���ɂQ�{�� */
	strFileName.ReleaseBuffer();
	m_strMsg.Format(m_strMsgFormat, m_nMaxChar, strFileName.GetLength());
	m_staticMsg.SetWindowText(m_strMsg);
}

BOOL CDlgFileNameChange::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	OnChangeEditName();
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

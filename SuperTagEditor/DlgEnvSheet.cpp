// DlgEnvSheet.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "SuperTagEditor.h"
#include "SuperTagEditorView.h"
#include "SuperTagEditorDoc.h"
#include "DlgEnvConf.h"
#include "DlgEnvironment.h"
#include "DlgLyricFile.h"
#include "DlgEnvPlayer.h"
#include "DlgUserConvFormat.h"
#include "DlgKeyConfig.h"
#include "DlgSetClassification.h"
#include "DlgEditShowColumn.h"
#include "DlgReplaceFileName.h"
#include "DlgConvFormatEx.h"
#include "DlgMoveFolder.h"
#include "DlgSetupGenre.h"
#include "DlgFolderSync.h"
#include "DlgWriteForm.h"
#include "DlgEnvSheet.h"
#include "DlgFileNameMaxCheck.h"
#include "DlgDefaultValue.h"
#include "DlgCopyFormat.h" /* FunnyCorn 175 */
#include "DlgConv.h" /* STEP 026 */
#include "DlgUserConvFormartTag2Tag.h" /* STEP 034 */
#include "DlgFixedUpperLower.h" /* STEP 040 */

#include "OptionPage/OptionListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvSheet

IMPLEMENT_DYNAMIC(CDlgEnvSheet, COptionSheet)

CDlgEnvSheet::CDlgEnvSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:COptionSheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CDlgEnvSheet::CDlgEnvSheet(LPCWSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:COptionSheet(pszCaption, pParentWnd, iSelectPage)
{
}

CDlgEnvSheet::~CDlgEnvSheet()
{
}


BEGIN_MESSAGE_MAP(CDlgEnvSheet, COptionSheet)
	//{{AFX_MSG_MAP(CDlgEnvSheet)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvSheet ���b�Z�[�W �n���h��

int CDlgEnvSheet::DoModal(int nType) 
{
	int		i, nResult;
	CDlgEnvironment		pageEnv;
	CDlgLyricFile		pageLyric;
	CDlgEnvPlayer		pagePlayer;
	CDlgUserConvFormat	pageConv;
	CDlgConvFormatEx	pageConvEx;
	CDlgMoveFolder		pageMoveFolder;
	CDlgCopyFormat		pageCopyFormat; /* FunnyCorn 175 */
	CDlgKeyConfig		pageKey;
	CDlgEditShowColumn	pageColumn;
	CDlgEnvConf			pageConf;
	CDlgSetClassification	pageClass;
	CDlgReplaceFileName	pageReplace;
	CDlgSetupGenre		pageGenre;
	CDlgFolderSync		pageSync;
	CDlgWriteForm		pageWrite;
	CDlgFileNameMaxCheck	pageFileNameMax;
	//CDlgTeikei			pageTeikei; /* FreeFall 046 */
	CDlgDefaultValue	pageDefaultValue;
	CDlgUserConvFormartTag2Tag	pageConvTag2Tag; /* STEP 032 */
	CDlgFixedUpperLower	pageFixedUpperLower; /* STEP 040 */

	CDlgConv	pageConvTop; /* STEP 026*/
	COptionListBox	listBox;

	SetListControl(&listBox);

	pageGenre.m_genreListUSER = NULL;

	// �v���p�e�B�[�V�[�g�̃X�^�C����ύX
	m_psh.dwFlags |= PSH_NOAPPLYNOW;	// [�K�p]�{�^������

	// �ϐ��̏�����
	if (true || nType & ENV_NORMAL) {
		// ���ݒ�
		pageEnv.m_bESCEditCancel		= g_bOptESCEditCancel ? TRUE : FALSE;
		pageEnv.m_bEnableEditCursorExit	= g_bOptEnableEditCursorExit ? TRUE : FALSE;
		pageEnv.m_bEnterBeginEdit	= g_bOptEnterBeginEdit ? TRUE : FALSE;
		pageEnv.m_bEditOkDown		= g_bOptEditOkDown ? TRUE : FALSE;
		pageEnv.m_bKeepTimeStamp	= g_bOptKeepTimeStamp ? TRUE : FALSE;
		pageEnv.m_bSyncCreateTime	= g_bOptSyncCreateTime ? TRUE : FALSE;
		pageEnv.m_bAutoOpenFolder	= g_bOptAutoOpenFolder ? TRUE : FALSE;
		pageEnv.m_bLoadFileAdjustColumn	= g_bOptLoadFileAdjustColumn ? TRUE : FALSE;
		pageEnv.m_bLoadFileChecked	= g_bOptLoadFileChecked ? TRUE : FALSE;
		pageEnv.m_bHideMP3ListFile	= g_bOptHideMP3ListFile ? TRUE : FALSE;
		pageEnv.m_bDropSearchSubFolder	= g_bOptDropSearchSubFolder ? TRUE : FALSE;	/* TyphoonSwell 026 */
		pageEnv.m_bShowZenSpace	= g_bOptShowZenSpace ? TRUE : FALSE;	/* BeachMonster 107 */
		pageEnv.m_bSortIgnoreCase = g_bOptSortIgnoreCase ? TRUE : FALSE;	/* BeachMonster4 114 */
		pageEnv.m_bSortIgnoreZenHan = g_bOptSortIgnoreZenHan ? TRUE : FALSE;	/* BeachMonster4 114 */
		pageEnv.m_bSortIgnoreKataHita = g_bOptSortIgnoreKataHira ? TRUE : FALSE;	/* FunnyCorn 179 */
		pageEnv.m_bShowTotalParent = g_bOptShowTotalParent ? TRUE : FALSE;	/* RockDance 128 */
		pageEnv.m_bShowTips	= g_bOptShowTips ? TRUE : FALSE;	/* Rumble 188 */

		// �̎��t�@�C��
		pageLyric.m_bChangeTextFile		= g_bOptChangeTextFile ? TRUE : FALSE;
		pageLyric.m_bSetLyricsDir		= g_bOptSetLyricsDir ? TRUE : FALSE;
		pageLyric.m_bSearchLyricsSubDir	= g_bOptSearchLyricsSubDir ? TRUE : FALSE;
		pageLyric.m_strLyricsPath		= g_strOptLyricsPath;

		// �v���C���[
		pagePlayer.m_nPlayerType	= g_nOptPlayerType;
		pagePlayer.m_strWinAmpPath	= g_sOptWinAmpPath;

		// �m�F���b�Z�[�W
		pageConf.m_bConfDeleteFile	= g_bConfDeleteFile ? TRUE : FALSE;
		pageConf.m_bConfDeleteList	= g_bConfDeleteList ? TRUE : FALSE;
		pageConf.m_bConfEditModify	= g_bConfEditModify ? TRUE : FALSE;
		pageConf.m_bConfFolderSync	= g_bConfFolderSync ? TRUE : FALSE;

		// �L�[���蓖��
		// ���݂̃L�[���蓖�Ă����W�X�g���ɕۑ�
		((CSuperTagEditorApp *)AfxGetApp())->WriteKeyConfig();

		// �t�@�C�����ő啶����
		pageFileNameMax.m_bFileNameMaxCheck = g_bConfFileNameMaxCheck ? TRUE : FALSE;
		pageFileNameMax.m_nFileNameMaxChar = g_nConfFileNameMaxChar;
		pageFileNameMax.m_bFileNameMaxCellColor = g_bFileNameMaxCellColor ? TRUE : FALSE; /* SeaKnows 036 */
	}

	if (true || nType & ENV_CONV) {
		pageConvTop.m_bFirstUpperIgnoreWord = g_bFirstUpperIgnoreWord;
		pageConvTop.m_strFirstUpperIgnoreWords = g_strFirstUpperIgnoreWords;
		pageConvTop.m_strFirstUpperSentenceSeparator = g_strFirstUpperSentenceSeparator;
		pageConvTop.m_bUserConvAddMenu = g_bUserConvAddMenu;
		pageConvTop.m_bZenHanKigouKana = g_bZenHanKigouKana;
		// �t�@�C�����u��
		pageReplace.m_bFileNameReplace = (g_nOptCheckFileName == FILENAME_CONV_MULTIBYTE) ? TRUE : FALSE;
		for (i = 0; i < FILENAME_REPLACE_MAX; i++) {
			FILENAME_REPLACE	*pRep = &g_fileNameReplace[i];
			pageReplace.m_strBefore[i] = pRep->strBefore;
			pageReplace.m_strAfter[i] = pRep->strAfter;
		}
		// ���[�U�t�@�C�����u�� /* FreeFall 050 */
		for (i = 0; i < USER_FILENAME_REPLACE_MAX; i++) {
			FILENAME_REPLACE	*pRep = &g_userFileNameReplace[i];
			pageReplace.m_strUserBefore[i] = pRep->strBefore;
			pageReplace.m_strUserAfter[i] = pRep->strAfter;
		}
		// �t�@�C����������̓��� /* LastTrain 058 */
		pageReplace.m_nFileUnifyAlpha = g_nFileUnifyAlpha;
		pageReplace.m_nFileUnifyHiraKata = g_nFileUnifyHiraKata;
		pageReplace.m_nFileUnifyKata = g_nFileUnifyKata;
		pageReplace.m_nFileUnifyKigou = g_nFileUnifyKigou;
		pageReplace.m_nFileUnifySuji = g_nFileUnifySuji;
		pageReplace.m_nFileUnifyUpLow = g_nFileUnifyUpLow;

		// �g���q�ϊ� /* STEP 006 */
		pageReplace.m_nExtChange = g_nFileExtChange;

		// ���[�U�[�ϊ�����
		pageConv.m_nFormatType	= g_nUserConvFormatType;
		for (i = 0; i < USER_CONV_FORMAT_MAX; i++) {
			pageConv.m_userFormat[i] = g_userConvFormat[i];
		}

		// �g�����[�U�[�ϊ�����
		pageConvEx.m_nFormatType	= 0;
		for (i = 0; i < USER_CONV_FORMAT_EX_MAX; i++) {
			pageConvEx.m_userFormatEx[i] = g_userConvFormatEx[i];
		}

		// �ړ���t�H���_����
		pageMoveFolder.m_nFormatType	= 0;
		for (i = 0; i < USER_MOVE_FODLER_FORMAT_MAX; i++) {
			pageMoveFolder.m_userFormatEx[i] = g_userMoveFolder[i];
		}

		// �����R�s�[ /* FunnyCorn 175 */
		pageCopyFormat.m_nFormatType	= 0;
		for (i = 0; i < USER_COPY_FORMAT_FORMAT_MAX; i++) {
			pageCopyFormat.m_userFormatEx[i] = g_userCopyFormat[i];
		}

		// �^�O���ϊ� /* STEP 034 */
		pageConvTag2Tag.m_nFormatType	= 0;
		for (i = 0; i < USER_CONV_FORMAT_TAG2TAG_MAX; i++) {
			pageConvTag2Tag.m_userFormatTag2Tag[i] = g_userConvFormatTag2Tag[i];
		}

		// �啶���������Œ�ϊ� /* STEP 040 */
		for (i = 0; i<g_arFixedWords.GetSize(); i++) {
			pageFixedUpperLower.m_arFixedWords.Add(g_arFixedWords.GetAt(i));
		}
	}

	if (true || nType & ENV_ADVANCED) {
		// ���ސݒ�
		pageClass.m_nClassType	= g_classInfo.nType;
		pageClass.m_nClass1	= g_classInfo.nColumn[0] + 1;
		pageClass.m_nClass2	= g_classInfo.nColumn[1] + 1;
		pageClass.m_nClass3	= g_classInfo.nColumn[2] + 1;
		pageClass.m_nClass4	= g_classInfo.nColumn[3] + 1;
		pageClass.m_nClass5	= g_classInfo.nColumn[4] + 1;

		// �t�H���_�̓���
		pageSync.m_bEnableFolderSync	= g_bEnableFolderSync ? TRUE : FALSE;
		pageSync.m_strRootFolder		= g_strRootFolder;
		pageSync.m_bSelectAlways		= g_bSyncSelectAlways ? TRUE : FALSE;
		pageSync.m_bDeleteFolder		= g_bSyncDeleteFolder ? TRUE : FALSE;
		pageSync.m_bMoveLyricsFile		= g_bSyncLyricsFileMove ? TRUE : FALSE;

		// ���X�g�o�͏���
		pageWrite.m_nFormatType	= 0;
		for (i = 0; i < WRITE_FORMAT_MAX; i++) {
			pageWrite.m_writeFormat[i] = g_writeFormat[i];
		}

		// ���[�U�w��W������
		pageGenre.m_genreListUSER = new USER_GENRE_LIST[USER_GENRE_LIST_MAX];
		for (i = 0; i < USER_GENRE_LIST_MAX; i++) {
			pageGenre.m_genreListUSER[i] = g_genreListUSER[i];
		}

		// ���̑� /* SeaKnows 031,033 */ 
		pageDefaultValue.m_bValidFolderSelect = g_bValidFolderSelect;
		pageDefaultValue.m_bValidDupExec = g_bValidDupExec; /* FreeFall 045 */
		pageDefaultValue.m_nRecentFolder = g_nRecentFolder; /* StartInaction 053 */
		pageDefaultValue.m_bSaveRepDlgPos = g_bSaveRepDlgPos; /* WildCherry4 086 */
		pageDefaultValue.m_bAudioListShow = g_bAudioListShow; /* Conspiracy 199 */
	}

	// �y�[�W�̒ǉ�
	if (true || nType & ENV_NORMAL  ) AddGroup(&pageEnv);
	AddGroup(&pageConvTop);
	AddGroup(&pageDefaultValue);
	if (true || nType & ENV_NORMAL  ) AddPage(&pageLyric, &pageEnv);
	if (true || nType & ENV_NORMAL  ) AddPage(&pagePlayer, &pageEnv);
	if (true || nType & ENV_NORMAL  ) AddPage(&pageFileNameMax, &pageEnv);
	if (true || nType & ENV_CONV    ) AddPage(&pageConv, &pageConvTop);
	if (true || nType & ENV_CONV    ) AddPage(&pageConvEx, &pageConvTop);
	if (true || nType & ENV_CONV    ) AddPage(&pageConvTag2Tag, &pageConvTop);
	if (true || nType & ENV_CONV    ) AddPage(&pageMoveFolder, &pageConvTop);
	if (true || nType & ENV_CONV    ) AddPage(&pageCopyFormat, &pageConvTop);
	if (true || nType & ENV_ADVANCED) AddPage(&pageSync, &pageDefaultValue);
	if (true || nType & ENV_CONV    ) AddPage(&pageReplace, &pageConvTop);
	if (true || nType & ENV_ADVANCED) AddPage(&pageGenre, &pageDefaultValue);
	if (true || nType & ENV_NORMAL  ) AddPage(&pageConf, &pageEnv);
	if (true || nType & ENV_ADVANCED) AddPage(&pageColumn, &pageDefaultValue);
	if (true || nType & ENV_NORMAL  ) AddPage(&pageKey, &pageEnv);
	if (true || nType & ENV_ADVANCED) AddPage(&pageClass, &pageDefaultValue);
	if (true || nType & ENV_ADVANCED) AddPage(&pageWrite, &pageDefaultValue);
	//if (true || nType & ENV_ADVANCED) AddPage(&pageDefaultValue, &pageDefaultValue);
	if (true || nType & ENV_CONV    ) AddPage(&pageFixedUpperLower, &pageConvTop); /* STEP 040 */

	// �v���p�e�B�V�[�g�̎��s
	if ((nResult = COptionSheet::DoModal()) == IDOK) {
		if (true || nType & ENV_NORMAL) {
			// ���ݒ�
			g_bOptESCEditCancel			= pageEnv.m_bESCEditCancel ? true : false;
			g_bOptEnableEditCursorExit	= pageEnv.m_bEnableEditCursorExit ? true : false;
			g_bOptEnterBeginEdit	= pageEnv.m_bEnterBeginEdit ? true : false;
			g_bOptEditOkDown		= pageEnv.m_bEditOkDown ? true : false;
			g_bOptKeepTimeStamp		= pageEnv.m_bKeepTimeStamp ? true : false;
			g_bOptSyncCreateTime	= pageEnv.m_bSyncCreateTime ? true : false;
			g_bOptAutoOpenFolder	= pageEnv.m_bAutoOpenFolder ? true : false;
			g_bOptLoadFileAdjustColumn	= pageEnv.m_bLoadFileAdjustColumn ? true : false;
			g_bOptLoadFileChecked	= pageEnv.m_bLoadFileChecked ? true : false;
			g_bOptHideMP3ListFile	= pageEnv.m_bHideMP3ListFile ? true : false;
			g_bOptDropSearchSubFolder	= pageEnv.m_bDropSearchSubFolder ? true : false; /* TyphoonSwell 026 */
			g_bOptShowZenSpace	= pageEnv.m_bShowZenSpace ? true : false; /* BeachMonster 107 */
			g_bOptSortIgnoreCase =  pageEnv.m_bSortIgnoreCase ? true : false;	/* BeachMonster4 114 */
			g_bOptSortIgnoreZenHan = pageEnv.m_bSortIgnoreZenHan ? true : false;	/* BeachMonster4 114 */
			g_bOptSortIgnoreKataHira = pageEnv.m_bSortIgnoreKataHita ? true : false;	/* FunnyCorn 179 */
			g_bOptShowTotalParent = pageEnv.m_bShowTotalParent ? true : false;	/* RockDance 128 */
			g_bOptShowTips	= pageEnv.m_bShowTips ? true : false; /* Rumble 188 */

			// �̎��t�@�C��
			g_bOptChangeTextFile		= pageLyric.m_bChangeTextFile ? true : false;
			g_bOptSetLyricsDir			= pageLyric.m_bSetLyricsDir ? true : false;
			g_bOptSearchLyricsSubDir	= pageLyric.m_bSearchLyricsSubDir ? true : false;
			g_strOptLyricsPath			= pageLyric.m_strLyricsPath;

			// �v���C���[
			g_nOptPlayerType	= pagePlayer.m_nPlayerType;
			g_sOptWinAmpPath	= pagePlayer.m_strWinAmpPath;

			// �m�F���b�Z�[�W
			g_bConfDeleteFile		= pageConf.m_bConfDeleteFile ? true : false;
			g_bConfDeleteList		= pageConf.m_bConfDeleteList ? true : false;
			g_bConfEditModify		= pageConf.m_bConfEditModify ? true : false;
			g_bConfFolderSync		= pageConf.m_bConfFolderSync ? true : false;

			// �t�@�C�����ő啶����
			g_bConfFileNameMaxCheck	= pageFileNameMax.m_bFileNameMaxCheck ? true : false;
			g_nConfFileNameMaxChar	= pageFileNameMax.m_nFileNameMaxChar;
			g_bFileNameMaxCellColor = pageFileNameMax.m_bFileNameMaxCellColor ? true : false; /* SeaKnows 036 */
		}

		if (true || nType & ENV_CONV) {
			g_bFirstUpperIgnoreWord = pageConvTop.m_bFirstUpperIgnoreWord ? true : false;
			g_strFirstUpperIgnoreWords = pageConvTop.m_strFirstUpperIgnoreWords;
			g_strFirstUpperSentenceSeparator = pageConvTop.m_strFirstUpperSentenceSeparator;
			g_bUserConvAddMenu = pageConvTop.m_bUserConvAddMenu ? true : false;
			g_bZenHanKigouKana = pageConvTop.m_bZenHanKigouKana ? true : false;
			// �t�@�C�����u��
			g_nOptCheckFileName = pageReplace.m_bFileNameReplace ? FILENAME_CONV_MULTIBYTE : FILENAME_NO_CHECK;
			for (i = 0; i < FILENAME_REPLACE_MAX; i++) {
				FILENAME_REPLACE	*pRep = &g_fileNameReplace[i];
				pRep->strAfter = pageReplace.m_strAfter[i];
			}
			// ���[�U�t�@�C�����u�� /* FreeFall 050 */
			for (i = 0; i < USER_FILENAME_REPLACE_MAX; i++) {
				FILENAME_REPLACE	*pRep = &g_userFileNameReplace[i];
				pRep->strBefore = pageReplace.m_strUserBefore[i];
				pRep->strAfter = pageReplace.m_strUserAfter[i];
			}
			// �t�@�C����������̓��� /* LastTrain 058 */
			g_nFileUnifyAlpha = pageReplace.m_nFileUnifyAlpha;
			g_nFileUnifyHiraKata = pageReplace.m_nFileUnifyHiraKata;
			g_nFileUnifyKata = pageReplace.m_nFileUnifyKata;
			g_nFileUnifyKigou = pageReplace.m_nFileUnifyKigou;
			g_nFileUnifySuji = pageReplace.m_nFileUnifySuji;
			g_nFileUnifyUpLow = pageReplace.m_nFileUnifyUpLow;

			// �g���q�ϊ� /* STEP 006 */
			g_nFileExtChange = pageReplace.m_nExtChange;

			// ���[�U�[�ϊ�����
			g_nUserConvFormatType	= pageConv.m_nFormatType;
			for (i = 0; i < USER_CONV_FORMAT_MAX; i++) {
				g_userConvFormat[i] = pageConv.m_userFormat[i];
			}

			// �g�����[�U�[�ϊ�����
			for (i = 0; i < USER_CONV_FORMAT_EX_MAX; i++) {
				g_userConvFormatEx[i] = pageConvEx.m_userFormatEx[i];
			}

			// �ړ���t�H���_����
			for (i = 0; i < USER_MOVE_FODLER_FORMAT_MAX; i++) {
				g_userMoveFolder[i] = pageMoveFolder.m_userFormatEx[i];
			}

			// �����R�s�[ /* FunnyCorn 175 */
			for (i = 0; i < USER_COPY_FORMAT_FORMAT_MAX; i++) {
				g_userCopyFormat[i] = pageCopyFormat.m_userFormatEx[i];
			}

			// �^�O���ϊ� /* STEP 034 */
			for (i = 0; i < USER_CONV_FORMAT_TAG2TAG_MAX; i++) {
				g_userConvFormatTag2Tag[i] = pageConvTag2Tag.m_userFormatTag2Tag[i];
			}

			// �啶���������Œ�ϊ� /* STEP 040 */
			if (pageFixedUpperLower.m_bModify) {
				g_arFixedWords.RemoveAll();
				for (i = 0; i<pageFixedUpperLower.m_arFixedWords.GetSize(); i++) {
					g_arFixedWords.Add(pageFixedUpperLower.m_arFixedWords.GetAt(i));
				}
				((CSuperTagEditorApp *)AfxGetApp())->WriteFixedWordList();
			}
		}

		if (true || nType & ENV_ADVANCED) {
			// ���ސݒ�
			g_classInfo.nType		= pageClass.m_nClassType;
			g_classInfo.nColumn[0]	= pageClass.m_nClass1 - 1;
			g_classInfo.nColumn[1]	= pageClass.m_nClass2 - 1;
			g_classInfo.nColumn[2]	= pageClass.m_nClass3 - 1;
			g_classInfo.nColumn[3]	= pageClass.m_nClass4 - 1;
			g_classInfo.nColumn[4]	= pageClass.m_nClass5 - 1;

			// �t�H���_�̓���
			g_bEnableFolderSync		= pageSync.m_bEnableFolderSync ? true : false;
			g_strRootFolder			= pageSync.m_strRootFolder;
			g_bSyncSelectAlways		= pageSync.m_bSelectAlways ? true : false;
			g_bSyncDeleteFolder		= pageSync.m_bDeleteFolder ? true : false;
			g_bSyncLyricsFileMove	= pageSync.m_bMoveLyricsFile ? true : false;

			// ���ޕ\�����X�V
			if (pageClass.m_nClassType != 0
			&&  pageClass.m_bExecClassification) {
				m_pDoc->ExecClassification();
			}

			// ���X�g�o�͏���
			for (i = 0; i < WRITE_FORMAT_MAX; i++) {
				g_writeFormat[i] = pageWrite.m_writeFormat[i];
			}

			// �W�������̓_�C�A���O��OnOK()�Ń��W�X�g���ɏ������ނ̂Ń_�C�A���O���ŏ�������

			// ���̑� /* SeaKnows 031,033 */
			g_bValidFolderSelect = pageDefaultValue.m_bValidFolderSelect ? true : false;
			g_bValidDupExec = pageDefaultValue.m_bValidDupExec ? true : false; /* FreeFall 045 */
			g_nRecentFolder = pageDefaultValue.m_nRecentFolder; /* StartInaction 053 */
			g_bSaveRepDlgPos = pageDefaultValue.m_bSaveRepDlgPos ? true : false; /* WildCherry4 086 */
			g_bAudioListShow = pageDefaultValue.m_bAudioListShow ? true : false; /* Conspiracy 199 */
		}

		// �L�[���蓖��
		// ���݂̃L�[���蓖�Ă����W�X�g���ɕۑ�
		((CSuperTagEditorApp *)AfxGetApp())->WriteKeyConfig(true);

		((CSuperTagEditorApp *)AfxGetApp())->WriteRegistry();
	} else {
		if (true || nType & ENV_NORMAL) {
			// �ύX�O�̃L�[���蓖�Ă����W�X�g������ǂݍ���
			((CSuperTagEditorApp *)AfxGetApp())->ReadKeyConfig();
		}
	}
	delete [] pageGenre.m_genreListUSER;

	return(nResult);
}

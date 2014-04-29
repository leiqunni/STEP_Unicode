// SuperTagEditor.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`���s���܂��B
//

#include "stdafx.h"
#include "SuperTagEditor.h"
#include "AutoBuildCount.h"
#include "MainFrm.h"
#include "SuperTagEditorDoc.h"
#include "SuperTagEditorView.h"
//�ǉ� by Kobarin
#include "dde/kbdde.h"
#include <dos.h> //�R�}���h���C���̉�͂��߂�ǂ��̂�(^^;
#include "DlgCommonProg.h"

#include "FileMP3.h" /* WildCherry2 078 */

#include "Plugin.h"

#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

RECT		g_rectMainWindow;		// ���C���E�B���h�E�̍��W
BOOL		g_bMainFrameZoomed;
BOOL		g_bMainFrameIconic;
CString		g_strCurrentDirectory;
CString		g_strCurrentPlayList;
CString		g_strCurrentMoveDirectory;
bool		g_bIsVersionUp;
int			g_nUserConvFormatType;
USER_CONV_FORMAT	g_userConvFormat[USER_CONV_FORMAT_MAX];
USER_CONV_FORMAT_EX	g_userConvFormatEx[USER_CONV_FORMAT_EX_MAX];
USER_MOVE_FODLER_FORMAT	g_userMoveFolder[USER_MOVE_FODLER_FORMAT_MAX];
USER_COPY_FORMAT_FORMAT	g_userCopyFormat[USER_COPY_FORMAT_FORMAT_MAX]; /* FunnyCorn 175 */
USER_CONV_FORMAT_TAG2TAG g_userConvFormatTag2Tag[USER_CONV_FORMAT_TAG2TAG_MAX]; /* STEP 034 */
TEIKEI_INFO g_teikeiInfo[TEIKEI_INFO_MAX]; /* STEP 035 */
WRITE_FORMAT		g_writeFormat[WRITE_FORMAT_MAX];
bool		g_bOptESCEditCancel;
bool		g_bOptEnableEditCursorExit;
bool		g_bOptEnterBeginEdit;
bool		g_bOptEditOkDown;
bool		g_bOptKeepTimeStamp;
bool		g_bOptChangeFileExt;
bool		g_bOptSyncCreateTime;
bool		g_bOptChangeTextFile;
int			g_nOptCheckFileName;
CString		g_sOptWinAmpPath;
int			g_nOptPlayerType;
bool		g_bOptEditFieldSIF;
bool		g_bOptAutoOpenFolder;
bool		g_bOptLoadFileChecked;
bool		g_bOptHideMP3ListFile;
bool		g_bOptDropSearchSubFolder; /* TyphoonSwell 026 */
bool		g_bOptShowZenSpace; /* BeachMonster 107 */
CString		g_sOptShowOtherChar; /* BeachMonster 107 */ // �Ƃ肠��������Ƃ�
bool		g_bOptSortIgnoreCase; /* BeachMonster4 114 */
bool		g_bOptSortIgnoreZenHan; /* BeachMonster4 114 */
bool		g_bOptSortIgnoreKataHira; /* FunnyCorn 179 */
bool		g_bOptShowTotalParent; /* RockDance 128 */
bool		g_bOptShowTips; /* Rumble 188 */
bool		g_bOptLoadFileAdjustColumn;
bool		g_bOptSearchLyricFile;
bool		g_bOptSetLyricsDir;
bool		g_bOptSearchLyricsSubDir;
bool		g_bEnableSearchSubDir;
bool		g_bEnableMoveFolderCopy;
CString		g_strOptLyricsPath;
SORT_STATE	g_sortState[SORT_KEY_MAX];
CLASS_INFO	g_classInfo;
CHECK_WORD_STATE	g_chkWord[CHECK_STATE_MAX];

//bool		g_bOptID3v2GenreAddNumber;
bool		g_bConfFileNameMaxCheck;
bool		g_bFileNameMaxCellColor; /* SeaKnows 036 */
int			g_nConfFileNameMaxChar;

bool		g_bEnableFolderSync;
CString		g_strRootFolder;
bool		g_bSyncSelectAlways;
bool		g_bSyncDeleteFolder;
bool		g_bSyncLyricsFileMove;

bool		g_bConfDeleteFile;
bool		g_bConfDeleteList;
bool		g_bConfEditModify;
bool		g_bConfFolderSync;

bool		g_bPlayListClearList;
bool		g_bPlayListClearCheck;
bool		g_bPlayListAddList;
bool		g_bPlayListFileCheck;

/* STEP 035 *///CString		g_strTeikei[10+20];	/* SeaKnows 030 *//* FreeFall 046 */
CString		g_strTeikeiGroupName[3];	/* FreeFall 046 */
bool		g_bValidFolderSelect;	/* SeaKnows 033 */
bool		g_bValidDupExec;	/* FreeFall 045 */

int			g_nRecentFolder; /* StartInaction 053 */
bool		g_bSaveRepDlgPos; /* WildCherry4 086 */
int			g_nSaveRepDlgPosX; /* WildCherry4 086 */
int			g_nSaveRepDlgPosY; /* WildCherry4 086 */

// �����퓝�� /* StartInaction 054 */
UINT		g_nUnifyAlpha;
UINT		g_nUnifyHiraKata;
UINT		g_nUnifyKata;
UINT		g_nUnifyKigou;
UINT		g_nUnifySuji;
UINT		g_nUnifyUpLow;
UINT		g_nUnifyFixedUpLow; /* STEP 040 */

// �t�@�C���������퓝�� /* LastTrain 058 */
UINT		g_nFileUnifyAlpha;
UINT		g_nFileUnifyHiraKata;
UINT		g_nFileUnifyKata;
UINT		g_nFileUnifyKigou;
UINT		g_nFileUnifySuji;
UINT		g_nFileUnifyUpLow;

// �g���q�ϊ� /* STEP 006 */
UINT		g_nFileExtChange;

bool		g_bEndEditMoveRightCell; /* BeachMonster 091 */

bool		g_bShowLoadPlaylistDlg; /* RockDance 126 */

CString		g_strFavorite[10];	/* RockDance 129 */

int			g_nAddNumberWidth; /* Baja 159 */
int			g_nAddNumberPos; /* Baja 159 */
CString		g_strAddNumberSep; /* Baja 159 */
CString		g_strAddNumberBef; /* Conspiracy 194 */
CString		g_strAddNumberAft; /* Conspiracy 194 */

bool		g_bAudioListShow; /* Conspiracy 199 */

bool		g_bFirstUpperIgnoreWord; /* STEP 026 */
CString		g_strFirstUpperIgnoreWords; /* STEP 026 */
CString		g_strFirstUpperSentenceSeparator; /* STEP 026 */
bool		g_bUserConvAddMenu; /* STEP 030 */
bool		g_bZenHanKigouKana; /* STEP 016 */

LOGFONT		g_fontReport;			// ���|�[�g�E�B���h�E�̃t�H���g

FILENAME_REPLACE	g_fileNameReplace[FILENAME_REPLACE_MAX];

FILENAME_REPLACE	g_userFileNameReplace[USER_FILENAME_REPLACE_MAX];	/* FreeFall 050 */

const wchar_t *g_sRepTable[FILENAME_REPLACE_MAX][2] = {
	{ L"\"", L"�h" }, { L"*", L"��" }, { L",", L"�C" }, { L"/", L"�^" },
	{ L":", L"�F" }, { L";", L"�G" }, { L"<", L"��" }, { L">", L"��" },
	{ L"?", L"�H" }, { L"\\", L"��" }, { L"|", L"�b" }, { L" ", L" " },
};

CStringArray g_arFixedWords; /* STEP 040 */

#define HK_CTRL_C				0x00020043
#define HK_CTRL_D				0x00020044
#define HK_CTRL_F				0x00020046
#define HK_CTRL_H				0x00020048
#define HK_CTRL_N				0x0002004e
#define HK_CTRL_O				0x0002004f
#define HK_CTRL_S				0x00020053
#define HK_CTRL_V				0x00020056
#define HK_CTRL_X				0x00020058

KEY_CONFIG	g_listKeyConfig[] = {
	/**
	 �y���Ӂz�R�}���h��ǉ������ꍇ�́A_APS_NEXT_COMMAND_VALUE���X�V�����̂�STEP_api.cpp�����R���p�C�����邱��
	 **/
	// �t�@�C������
	{ ID_FILE_NEW, 0x00000000, COMMAND_GROUP_FILE, L"���X�g���N���AL", L"FileNewL" },
	{ ID_OPEN_FOLDER, HK_CTRL_O, COMMAND_GROUP_FILE, L"�t�H���_���J��L", L"FileOpenFolderL" },
	{ ID_SAVE_ALL_TAG, HK_CTRL_S, COMMAND_GROUP_FILE, L"�^�O�����X�VL", L"FileSaveAllTagL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_FILE, L"--------------------L", NULL },
	{ ID_WRITE_LIST1, 0x00000000, COMMAND_GROUP_FILE, L"���X�g�o�́F�����PL", L"WriteList1L" },
	{ ID_WRITE_LIST2, 0x00000000, COMMAND_GROUP_FILE, L"���X�g�o�́F�����QL", L"WriteList2L" },
	{ ID_WRITE_LIST3, 0x00000000, COMMAND_GROUP_FILE, L"���X�g�o�́F�����RL", L"WriteList3L" },
	{ ID_WRITE_LIST4, 0x00000000, COMMAND_GROUP_FILE, L"���X�g�o�́F�����SL", L"WriteList4L" },
	{ ID_WRITE_LIST5, 0x00000000, COMMAND_GROUP_FILE, L"���X�g�o�́F�����TL", L"WriteList5L" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_FILE, L"--------------------L", NULL },
	{ ID_MOVE_FOLDER_01, 0x00000000, COMMAND_GROUP_FILE, L"�t�@�C���ړ��F�����PL", L"MoveFolder1L" },
	{ ID_MOVE_FOLDER_02, 0x00000000, COMMAND_GROUP_FILE, L"�t�@�C���ړ��F�����QL", L"MoveFolder2L" },
	{ ID_MOVE_FOLDER_03, 0x00000000, COMMAND_GROUP_FILE, L"�t�@�C���ړ��F�����RL", L"MoveFolder3L" },
	{ ID_MOVE_FOLDER_04, 0x00000000, COMMAND_GROUP_FILE, L"�t�@�C���ړ��F�����SL", L"MoveFolder4L" },
	{ ID_MOVE_FOLDER_05, 0x00000000, COMMAND_GROUP_FILE, L"�t�@�C���ړ��F�����TL", L"MoveFolder5L" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_FILE, L"--------------------L", NULL },
	{ ID_FAVORITE_FOLDER_01, 0x00000000, COMMAND_GROUP_FILE, L"���C�ɓ���̃t�H���_�F���C�ɓ���PL", L"FavoriteFolder1L" },
	{ ID_FAVORITE_FOLDER_02, 0x00000000, COMMAND_GROUP_FILE, L"���C�ɓ���̃t�H���_�F���C�ɓ���QL", L"FavoriteFolder2L" },
	{ ID_FAVORITE_FOLDER_03, 0x00000000, COMMAND_GROUP_FILE, L"���C�ɓ���̃t�H���_�F���C�ɓ���RL", L"FavoriteFolder3L" },
	{ ID_FAVORITE_FOLDER_04, 0x00000000, COMMAND_GROUP_FILE, L"���C�ɓ���̃t�H���_�F���C�ɓ���SL", L"FavoriteFolder4L" },
	{ ID_FAVORITE_FOLDER_05, 0x00000000, COMMAND_GROUP_FILE, L"���C�ɓ���̃t�H���_�F���C�ɓ���TL", L"FavoriteFolder5L" },
	{ ID_FAVORITE_FOLDER_06, 0x00000000, COMMAND_GROUP_FILE, L"���C�ɓ���̃t�H���_�F���C�ɓ���UL", L"FavoriteFolder6L" },
	{ ID_FAVORITE_FOLDER_07, 0x00000000, COMMAND_GROUP_FILE, L"���C�ɓ���̃t�H���_�F���C�ɓ���VL", L"FavoriteFolder7L" },
	{ ID_FAVORITE_FOLDER_08, 0x00000000, COMMAND_GROUP_FILE, L"���C�ɓ���̃t�H���_�F���C�ɓ���WL", L"FavoriteFolder8L" },
	{ ID_FAVORITE_FOLDER_09, 0x00000000, COMMAND_GROUP_FILE, L"���C�ɓ���̃t�H���_�F���C�ɓ���XL", L"FavoriteFolder9L" },
	{ ID_FAVORITE_FOLDER_10, 0x00000000, COMMAND_GROUP_FILE, L"���C�ɓ���̃t�H���_�F���C�ɓ���10L", L"FavoriteFolder10L" },

	// �ҏW����
	{ ID_EDIT_COPY, HK_CTRL_C, COMMAND_GROUP_EDIT, L"�R�s�[L", L"EditCopyL" },
	{ ID_EDIT_PASTE, HK_CTRL_V, COMMAND_GROUP_EDIT, L"�\��t��L", L"EditPasteL" },
	{ ID_EDIT_CUT, HK_CTRL_X, COMMAND_GROUP_EDIT, L"�؂���L", L"EditCutL" },
	{ ID_EDIT_PASTE_ADD, 0x00000000, COMMAND_GROUP_EDIT, L"�ǉ��œ\��t��L", L"EditPasteAddL" }, /* FunnyCorn 176 */
	{ 0x0000, 0x00000000, COMMAND_GROUP_EDIT, L"----- ��^�� �O���[�v�P -----L", NULL },
	{ ID_TEIKEI_01, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���P-�PL", L"TeikeiPaste1-1L" }, /* SeaKnows 030 */
	{ ID_TEIKEI_02, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���P-�QL", L"TeikeiPaste1-2L" }, /* SeaKnows 030 */
	{ ID_TEIKEI_03, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���P-�RL", L"TeikeiPaste1-3L" }, /* SeaKnows 030 */
	{ ID_TEIKEI_04, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���P-�SL", L"TeikeiPaste1-4L" }, /* SeaKnows 030 */
	{ ID_TEIKEI_05, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���P-�TL", L"TeikeiPaste1-5L" }, /* SeaKnows 030 */
	{ ID_TEIKEI_06, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���P-�UL", L"TeikeiPaste1-6L" }, /* SeaKnows 030 */
	{ ID_TEIKEI_07, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���P-�VL", L"TeikeiPaste1-7L" }, /* SeaKnows 030 */
	{ ID_TEIKEI_08, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���P-�WL", L"TeikeiPaste1-8L" }, /* SeaKnows 030 */
	{ ID_TEIKEI_09, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���P-�XL", L"TeikeiPaste1-9L" }, /* SeaKnows 030 */
	{ ID_TEIKEI_10, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���P-�P�OL", L"TeikeiPaste1-10L" }, /* SeaKnows 030 */
	{ 0x0000, 0x00000000, COMMAND_GROUP_EDIT, L"----- ��^�� �O���[�v�Q -----L", NULL },
	{ ID_TEIKEI_2_01, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���Q-�PL", L"TeikeiPaste2-1L" }, /* FreeFall 046 */
	{ ID_TEIKEI_2_02, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���Q-�QL", L"TeikeiPaste2-2L" }, /* FreeFall 046 */
	{ ID_TEIKEI_2_03, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���Q-�RL", L"TeikeiPaste2-3L" }, /* FreeFall 046 */
	{ ID_TEIKEI_2_04, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���Q-�SL", L"TeikeiPaste2-4L" }, /* FreeFall 046 */
	{ ID_TEIKEI_2_05, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���Q-�TL", L"TeikeiPaste2-5L" }, /* FreeFall 046 */
	{ ID_TEIKEI_2_06, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���Q-�UL", L"TeikeiPaste2-6L" }, /* FreeFall 046 */
	{ ID_TEIKEI_2_07, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���Q-�VL", L"TeikeiPaste2-7L" }, /* FreeFall 046 */
	{ ID_TEIKEI_2_08, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���Q-�WL", L"TeikeiPaste2-8L" }, /* FreeFall 046 */
	{ ID_TEIKEI_2_09, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���Q-�XL", L"TeikeiPaste2-9L" }, /* FreeFall 046 */
	{ ID_TEIKEI_2_10, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���Q-�P�OL", L"TeikeiPaste2-10L" }, /* FreeFall 046 */
	{ 0x0000, 0x00000000, COMMAND_GROUP_EDIT, L"----- ��^�� �O���[�v�R -----L", NULL },
	{ ID_TEIKEI_3_01, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���R-�PL", L"TeikeiPaste3-1L" }, /* FreeFall 046 */
	{ ID_TEIKEI_3_02, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���R-�QL", L"TeikeiPaste3-2L" }, /* FreeFall 046 */
	{ ID_TEIKEI_3_03, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���R-�RL", L"TeikeiPaste3-3L" }, /* FreeFall 046 */
	{ ID_TEIKEI_3_04, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���R-�SL", L"TeikeiPaste3-4L" }, /* FreeFall 046 */
	{ ID_TEIKEI_3_05, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���R-�TL", L"TeikeiPaste3-5L" }, /* FreeFall 046 */
	{ ID_TEIKEI_3_06, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���R-�UL", L"TeikeiPaste3-6L" }, /* FreeFall 046 */
	{ ID_TEIKEI_3_07, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���R-�VL", L"TeikeiPaste3-7L" }, /* FreeFall 046 */
	{ ID_TEIKEI_3_08, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���R-�WL", L"TeikeiPaste3-8L" }, /* FreeFall 046 */
	{ ID_TEIKEI_3_09, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���R-�XL", L"TeikeiPaste3-9L" }, /* FreeFall 046 */
	{ ID_TEIKEI_3_10, 0x00000000, COMMAND_GROUP_EDIT, L"��^���\��t���R-�P�OL", L"TeikeiPaste3-10L" }, /* FreeFall 046 */
	{ 0x0000, 0x00000000, COMMAND_GROUP_FILE, L"--------------------L", NULL },
	{ ID_EDIT_COPY_FORMAT_01, 0x00000000, COMMAND_GROUP_FILE, L"�����R�s�[�F�����PL", L"CopyFormat1L" },
	{ ID_EDIT_COPY_FORMAT_02, 0x00000000, COMMAND_GROUP_FILE, L"�����R�s�[�F�����QL", L"CopyFormat2L" },
	{ ID_EDIT_COPY_FORMAT_03, 0x00000000, COMMAND_GROUP_FILE, L"�����R�s�[�F�����RL", L"CopyFormat3L" },
	{ ID_EDIT_COPY_FORMAT_04, 0x00000000, COMMAND_GROUP_FILE, L"�����R�s�[�F�����SL", L"CopyFormat4L" },
	{ ID_EDIT_COPY_FORMAT_05, 0x00000000, COMMAND_GROUP_FILE, L"�����R�s�[�F�����TL", L"CopyFormat5L" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_EDIT, L"--------------------L", NULL },
	{ ID_CELL_COPY_DOWN, HK_CTRL_D, COMMAND_GROUP_EDIT, L"�������փR�s�[L", L"EditCopyDownL" },
	{ ID_SET_NUMBER, HK_CTRL_N, COMMAND_GROUP_EDIT, L"�������֘A��L", L"EditSetNumberL" },
	{ ID_SET_NUMBER_ADD, 0x00000000, COMMAND_GROUP_EDIT, L"�������֘A�ԁi�擪�ɒǉ��jL", L"EditSetNumberAddL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_EDIT, L"--------------------L", NULL },
	{ ID_EDIT_FIND, 0x00000000, COMMAND_GROUP_EDIT, L"����L", L"EditFindL" },
	{ ID_EDIT_REPLACE, 0x00000000, COMMAND_GROUP_EDIT, L"�u��L", L"EditReplaceL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_EDIT, L"--------------------L", NULL },
	{ ID_SELECT_DELETE_LIST, 0x00000000, COMMAND_GROUP_EDIT, L"STE�̃��X�g����폜L", L"DeleteListL" },
	{ ID_SELECT_DELETE_FILE, 0x00000000, COMMAND_GROUP_EDIT, L"�t�@�C���̍폜L", L"DeleteFileL" },
	{ ID_SELECT_EDIT_DESTORY, 0x00000000, COMMAND_GROUP_EDIT, L"�ύX�O�̏�Ԃɖ߂�L", L"EditModifyL" },
	{ ID_FOLDER_TREE_SYNC, 0x00000000, COMMAND_GROUP_EDIT, L"�t�H���_�\���̓���L", L"FolderSyncL" },
	{ ID_CHECK_FILE_SYNC, 0x00000000, COMMAND_GROUP_EDIT, L"�t�H���_�\���̓���(�`�F�b�N�̂�)L", L"CheckFileSyncL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_EDIT, L"--------------------L", NULL },
	{ ID_DELETE_CHAR_SPACE, 0x00000000, COMMAND_GROUP_EDIT, L"�擪/�����̋󔒕������폜L", L"EditDeleteCharSpaceL" }, /* Rumble 192 */
	{ ID_DELETE_CHAR, 0x00000000, COMMAND_GROUP_EDIT, L"�擪/�����̂��������폜L", L"EditDeleteCharL" },

	// �\��
	{ ID_ADJUST_COLUMN_WIDTH, 0x00000000, COMMAND_GROUP_DISP, L"�S�ẴJ�������𒲐�L", L"AdjustColumnWidthL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_DISP, L"--------------------L", NULL },
	{ ID_SORT_LIST, 0x00000000, COMMAND_GROUP_DISP, L"���ёւ�L", L"ListSortL" },
	{ ID_SORT_LIST_DIRECT, 0x00000000, COMMAND_GROUP_DISP, L"���ёւ����Ď��sL", L"ListSortDirectL" },
	{ ID_EXEC_CLASSIFICATION, 0x00000000, COMMAND_GROUP_DISP, L"���ޕ\�����X�VL", L"ExecClassificationL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_DISP, L"--------------------L", NULL },
	{ ID_EDIT_FIELD_SI, 0x00000000, COMMAND_GROUP_DISP, L"SI�t�B�[���h��\��/�ҏWL", L"EditFieldSIL" },
	{ ID_EDIT_TD3_TAG, 0x00000000, COMMAND_GROUP_DISP, L"ID3 tag ��\��/�ҏWL", L"EditID3tagL" },
	{ ID_EDIT_CHANGE_FIELD, 0x00000000, COMMAND_GROUP_DISP, L"[ID3 tag]<=>[SI�t�B�[���h]�ؑ�L", L"EditChangeFieldL" },

	// �v���C���X�g
	{ ID_LOAD_PLAYLIST, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�v���C���X�g�̓ǂݍ���L", L"LoadPlayListL" },
	{ ID_WRITE_PLAYLIST, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�v���C���X�g�̏o��L", L"WritePlayListL" },
	{ ID_WRITE_TREE_PLAYLIST, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�c���[���ނ̃v���C���X�g�o��L", L"WriteTreePlayListL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_PLAYLIST, L"--------------------L", NULL },
	{ ID_ALL_FILES_CHECK, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�S�Ẵt�@�C�����`�F�b�N����L", L"AllFilesCheckL" },
	{ ID_ALL_FILES_UNCHECK, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�S�Ẵt�@�C���̃`�F�b�N���O��L", L"AllFilesUnCheckL" },
	{ ID_REVERSE_CHECK, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�`�F�b�N��Ԃ𔽓]����L", L"ReverseCheckL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_PLAYLIST, L"--------------------L", NULL },
	{ ID_CHECK_FILES_SELECT, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�`�F�b�N�t�@�C����I��L", L"CheckFilesSelectL" },
	{ ID_SELECT_FILES_CHECK, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�I���t�@�C�����`�F�b�NL", L"SelectFilesCheckL" },
	{ ID_SELECT_FILES_UNCHECK, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�I���t�@�C���̃`�F�b�N���O��L", L"SelectFilesUnCheckL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_PLAYLIST, L"--------------------L", NULL },
	{ ID_CHECK_WORD, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�������w�肵�ă`�F�b�NL", L"CheckWordL" },
	{ ID_CHECK_FILENAME_MAX, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�t�@�C�����̒������`�F�b�NL", L"CheckFileNameMaxL" }, /* SeaKnows 037 */
	{ 0x0000, 0x00000000, COMMAND_GROUP_PLAYLIST, L"--------------------L", NULL },
	{ ID_SELECT_TREE_COLUM, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�c���[�z���̃Z���ꊇ�I��L", L"SelectTreeColumnL" }, /* TyphoonSwell 025 */
	{ ID_SELECT_TREE_FILE, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�c���[�z���̃t�@�C���ꊇ�I��L", L"SelectTreeFileL" }, /* STEP 013 */
	{ 0x0000, 0x00000000, COMMAND_GROUP_PLAYLIST, L"--------------------L", NULL },
	{ ID_MOVE_TO_PARENT, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�J�[�\����e�c���[�ֈړ�L", L"MoveToParentL" }, /* STEP 014 */
	{ ID_MOVE_TO_PREVIOUS, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�J�[�\���ʒu�����̃c���[�ֈړ�L", L"MoveToPreviousL" }, /* STEP 014 */
	{ ID_MOVE_TO_NEXT, 0x00000000, COMMAND_GROUP_PLAYLIST, L"�J�[�\���ʒu������̃c���[�ֈړ�L", L"MoveToNextL" }, /* STEP 014 */

	// WinAmp ���䏈��
	{ ID_WINAMP_PLAY, 0x00000000, COMMAND_GROUP_PLAYER, L"�Đ�L", L"WinampPlayL" },
	{ ID_WINAMP_STOP, 0x00000000, COMMAND_GROUP_PLAYER, L"��~(Winamp�̂ݗL��)L", L"WinampStopL" },
	{ ID_WINAMP_EXIT, 0x00000000, COMMAND_GROUP_PLAYER, L"�I��L", L"WinampExitL" },
	{ ID_WINAMP_PLAY_PREV, 0x00000000, COMMAND_GROUP_PLAYER, L"�O�̋�(Winamp�̂ݗL��)L", L"WinampPlayPrevL" },
	{ ID_WINAMP_PLAY_NEXT, 0x00000000, COMMAND_GROUP_PLAYER, L"���̋�(Winamp�̂ݗL��)L", L"WinampPlayNextL" },

	// �ϊ�����
	{ 0x0000, 0x00000000, COMMAND_GROUP_CONV, L"----- �f�t�H���g�����ϊ� -----L", NULL },
	{ ID_CONV_FILENAME_TO_TRACKNAME, 0x00000000, COMMAND_GROUP_CONV, L"�t�@�C���� => �g���b�N��L", L"ConvFileNameToTrackNameL" },
	{ ID_CONV_TRACKNAME_TO_FILENAME, 0x00000000, COMMAND_GROUP_CONV, L"�g���b�N�� => �t�@�C����L", L"ConvTrackNameToFileNameL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_CONV, L"----- ���[�U�[�w�菑���ϊ� -----L", NULL },
	{ ID_CONV_TAG2FILE_USER, 0x00000000, COMMAND_GROUP_CONV, L"�^�O��� => �t�@�C����L", L"ConvUserTagToFileL" },
	{ ID_CONV_FILE2TAG_USER, 0x00000000, COMMAND_GROUP_CONV, L"�t�@�C���� => �^�O���L", L"ConvUserFileToTagL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_CONV, L"------ �����ϊ� -----L", NULL },
	{ ID_CONV_STR_HAN_ALL, 0x00000000, COMMAND_GROUP_CONV, L"�S�p=>���p(�S��)�ϊ�L", L"ConvHanAlL" },
	{ ID_CONV_STR_HAN_KIGOU, 0x00000000, COMMAND_GROUP_CONV, L"�S�p=>���p(�L��)�ϊ�L", L"ConvHanKigouL" },
	{ ID_CONV_STR_HAN_SUJI, 0x00000000, COMMAND_GROUP_CONV, L"�S�p=>���p(����)�ϊ�L", L"ConvHanSujiL" },
	{ ID_CONV_STR_HAN_KATA, 0x00000000, COMMAND_GROUP_CONV, L"�S�p=>���p(�J�^�J�i)�ϊ�L", L"ConvHanLataL" },
	{ ID_CONV_STR_HAN_ALPHA, 0x00000000, COMMAND_GROUP_CONV, L"�S�p=>���p(�A���t�@�x�b�g)�ϊ�L", L"ConvHanAlphaL" },
	{ ID_CONV_STR_ZEN_ALL, 0x00000000, COMMAND_GROUP_CONV, L"���p=>�S�p(�S��)�ϊ�L", L"ConvZenAlL" },
	{ ID_CONV_STR_ZEN_KIGOU, 0x00000000, COMMAND_GROUP_CONV, L"���p=>�S�p(�L��)�ϊ�L", L"ConvZenKigouL" },
	{ ID_CONV_STR_ZEN_SUJI, 0x00000000, COMMAND_GROUP_CONV, L"���p=>�S�p(����)�ϊ�L", L"ConvZenSujiL" },
	{ ID_CONV_STR_ZEN_KATA, 0x00000000, COMMAND_GROUP_CONV, L"���p=>�S�p(�J�^�J�i)�ϊ�L", L"ConvZenKataL" },
	{ ID_CONV_STR_ZEN_ALPHA, 0x00000000, COMMAND_GROUP_CONV, L"���p=>�S�p(�A���t�@�x�b�g)�ϊ�L", L"ConvZenAlphaL" },
	{ ID_CONV_STR_TO_UPPER, 0x00000000, COMMAND_GROUP_CONV, L"������=>�啶���ϊ�L", L"ConvToUpperL" },
	{ ID_CONV_STR_TO_LOWER, 0x00000000, COMMAND_GROUP_CONV, L"�啶��=>�������ϊ�L", L"ConvToLowerL" },
	{ ID_CONV_STR_FIRST_UPPER, 0x00000000, COMMAND_GROUP_CONV, L"�P��̂P�����ڂ̂ݑ啶��L", L"ConvFirstUpperL" },
	{ ID_CONV_STR_FIXED_UPPER_LOWER, 0x00000000, COMMAND_GROUP_CONV, L"�啶���������Œ�L", L"ConvFIxedUpLowL" }, /* STEP 040 */
	{ ID_CONV_STR_HIRA2KATA, 0x00000000, COMMAND_GROUP_CONV, L"�Ђ炪��=>�J�^�J�i�ϊ�L", L"ConvHira2KataL" },
	{ ID_CONV_STR_KATA2HIRA, 0x00000000, COMMAND_GROUP_CONV, L"�J�^�J�i=>�Ђ炪�ȕϊ�L", L"ConvKata2HiraL" },
	{ 0x0000, 0x00000000, COMMAND_GROUP_CONV, L"----- �g�������ϊ� -----L", NULL },
	{ ID_CONV_FORMAT_EX_01, 0x00000000, COMMAND_GROUP_CONV, L"�����PL", L"ConvFormatEx01L" },
	{ ID_CONV_FORMAT_EX_02, 0x00000000, COMMAND_GROUP_CONV, L"�����QL", L"ConvFormatEx02L" },
	{ ID_CONV_FORMAT_EX_03, 0x00000000, COMMAND_GROUP_CONV, L"�����RL", L"ConvFormatEx03L" },
	{ ID_CONV_FORMAT_EX_04, 0x00000000, COMMAND_GROUP_CONV, L"�����SL", L"ConvFormatEx04L" },
	{ ID_CONV_FORMAT_EX_05, 0x00000000, COMMAND_GROUP_CONV, L"�����TL", L"ConvFormatEx05L" },
	{ ID_CONV_FORMAT_EX_06, 0x00000000, COMMAND_GROUP_CONV, L"�����UL", L"ConvFormatEx06L" },
	{ ID_CONV_FORMAT_EX_07, 0x00000000, COMMAND_GROUP_CONV, L"�����VL", L"ConvFormatEx07L" },
	{ ID_CONV_FORMAT_EX_08, 0x00000000, COMMAND_GROUP_CONV, L"�����WL", L"ConvFormatEx08L" },
	{ ID_CONV_FORMAT_EX_09, 0x00000000, COMMAND_GROUP_CONV, L"�����XL", L"ConvFormatEx09L" },
	{ ID_CONV_FORMAT_EX_10, 0x00000000, COMMAND_GROUP_CONV, L"�����P�OL", L"ConvFormatEx10L" },
	{ ID_CONV_EX_SETUP, 0x00000000, COMMAND_GROUP_CONV, L"�g�������ϊ������ݒ�L", L"ConvUserSetupL" }, /* STEP 009 */
	{ 0x0000, 0x00000000, COMMAND_GROUP_CONV, L"----- ���[�U�[�w�菑���̐ؑ� -----L", NULL },
	{ ID_CONV_FORMAT_USER_01, 0x00000000, COMMAND_GROUP_CONV, L"�����PL", L"ConvFormatUser01L" },
	{ ID_CONV_FORMAT_USER_02, 0x00000000, COMMAND_GROUP_CONV, L"�����QL", L"ConvFormatUser02L" },
	{ ID_CONV_FORMAT_USER_03, 0x00000000, COMMAND_GROUP_CONV, L"�����RL", L"ConvFormatUser03L" },
	{ ID_CONV_FORMAT_USER_04, 0x00000000, COMMAND_GROUP_CONV, L"�����SL", L"ConvFormatUser04L" }, /* LastTrain 057 */
	{ ID_CONV_FORMAT_USER_05, 0x00000000, COMMAND_GROUP_CONV, L"�����TL", L"ConvFormatUser05L" }, /* LastTrain 057 */
	{ ID_CONV_USER_SETUP, 0x00000000, COMMAND_GROUP_CONV, L"���[�U�[�w�菑���ϊ������ݒ�L", L"ConvUserSetupL" }, /* STEP 009 */
	{ 0x0000, 0x00000000, COMMAND_GROUP_CONV, L"----- ���[�U�[�w�菑�� �^�O��� => �t�@�C���� -----L", NULL },
	{ ID_CONV_FORMAT_USER_T2F_01, 0x00000000, COMMAND_GROUP_CONV, L"�^�O��� => �t�@�C���� �����PL", L"ConvFormatUserT2F01L" }, /* STEP 030 */
	{ ID_CONV_FORMAT_USER_T2F_02, 0x00000000, COMMAND_GROUP_CONV, L"�^�O��� => �t�@�C���� �����QL", L"ConvFormatUserT2F02L" }, /* STEP 030 */
	{ ID_CONV_FORMAT_USER_T2F_03, 0x00000000, COMMAND_GROUP_CONV, L"�^�O��� => �t�@�C���� �����RL", L"ConvFormatUserT2F03L" }, /* STEP 030 */
	{ ID_CONV_FORMAT_USER_T2F_04, 0x00000000, COMMAND_GROUP_CONV, L"�^�O��� => �t�@�C���� �����SL", L"ConvFormatUserT2F04L" }, /* STEP 030 */
	{ ID_CONV_FORMAT_USER_T2F_05, 0x00000000, COMMAND_GROUP_CONV, L"�^�O��� => �t�@�C���� �����TL", L"ConvFormatUserT2F05L" }, /* STEP 030 */
	{ 0x0000, 0x00000000, COMMAND_GROUP_CONV, L"----- ���[�U�[�w�菑�� �t�@�C���� => �^�O��� -----L", NULL },
	{ ID_CONV_FORMAT_USER_F2T_01, 0x00000000, COMMAND_GROUP_CONV, L"�t�@�C���� => �^�O��� �����PL", L"ConvFormatUserF2T01L" }, /* STEP 030 */
	{ ID_CONV_FORMAT_USER_F2T_02, 0x00000000, COMMAND_GROUP_CONV, L"�t�@�C���� => �^�O��� �����QL", L"ConvFormatUserF2T02L" }, /* STEP 030 */
	{ ID_CONV_FORMAT_USER_F2T_03, 0x00000000, COMMAND_GROUP_CONV, L"�t�@�C���� => �^�O��� �����RL", L"ConvFormatUserF2T03L" }, /* STEP 030 */
	{ ID_CONV_FORMAT_USER_F2T_04, 0x00000000, COMMAND_GROUP_CONV, L"�t�@�C���� => �^�O��� �����SL", L"ConvFormatUserF2T04L" }, /* STEP 030 */
	{ ID_CONV_FORMAT_USER_F2T_05, 0x00000000, COMMAND_GROUP_CONV, L"�t�@�C���� => �^�O��� �����TL", L"ConvFormatUserF2T05L" }, /* STEP 030 */
	{ 0x0000, 0x00000000, COMMAND_GROUP_CONV, L"----- �^�O���ϊ� -----L", NULL }, /* STEP 034 */
	{ ID_CONV_TAG_TO_TAG_01, 0x00000000, COMMAND_GROUP_CONV, L"�����PL", L"ConvFormatTag2Tag01L" }, /* STEP 034 */
	{ ID_CONV_TAG_TO_TAG_02, 0x00000000, COMMAND_GROUP_CONV, L"�����QL", L"ConvFormatTag2Tag02L" }, /* STEP 034 */
	{ ID_CONV_TAG_TO_TAG_03, 0x00000000, COMMAND_GROUP_CONV, L"�����RL", L"ConvFormatTag2Tag03L" }, /* STEP 034 */
	{ ID_CONV_TAG_TO_TAG_04, 0x00000000, COMMAND_GROUP_CONV, L"�����SL", L"ConvFormatTag2Tag04L" }, /* STEP 034 */
	{ ID_CONV_TAG_TO_TAG_05, 0x00000000, COMMAND_GROUP_CONV, L"�����TL", L"ConvFormatTag2Tag05L" }, /* STEP 034 */

	{ 0x0000, 0x00000000, -1, NULL, NULL },		// �I�[�R�[�h
	/**
	�y���Ӂz�R�}���h��ǉ������ꍇ�́A_APS_NEXT_COMMAND_VALUE���X�V�����̂�STEP_api.cpp�����R���p�C�����邱��
	 **/
};

KEY_CONFIG *SearchKeyConfigID(WORD wCmdID)
{
	int		i;
	for (i = 0; g_listKeyConfig[i].sName != NULL; i++) {
		KEY_CONFIG	*pKey = &g_listKeyConfig[i];
		if (pKey->wCmdID == wCmdID) {
			return(pKey);
		}
	}
	extern CPlugin plugins;
	for (i = 0; i < plugins.arPluginKey.GetSize(); i++) {
		KEY_CONFIG* pKey = (KEY_CONFIG*)plugins.arPluginKey.GetAt(i);
		if (pKey->wCmdID == wCmdID) {
			return pKey;
		}
	}
	return(NULL);
}

static	char	*g_sKeyName[] = {
	"",				// 00
	"LBUTTON",		// 01	�}�E�X�̍��{�^��
	"RBUTTON",		// 02	�}�E�X�̉E�{�^��
	"CANCEL",		// 03	�R���g���[�� �u���[�N�����Ɏg�p
	"MBUTTON",		// 04	�}�E�X�̒����{�^�� (3�{�^���̃}�E�X)
	"", "", "",		// 05�`07	����`
	"BS",			// 08	BackSpace�L�[
	"Tab",			// 09	Tab�L�[
	"", "",			// 0A� 0B	����`
	"CLEAR",		// 0C	Clear�L�[
	"Enter",		// 0D	Enter�L�[
	"", "",			// 0E� 0F	����`
	"Shift",		// 10	Shift�L�[
	"Ctrl",			// 11	Ctrl�L�[
	"Alt",			// 12	Alt�L�[
	"PAUSE",		// 13	Pause�L�[
	"CAPITAL",		// 14	Caps Lock�L�[
	"KANA",			// 15	�p���J�i�L�[
	"", "", "",		// 16�`18	�����V�X�e���p�ɗ\��
	"KANJI",		// 19	�����V�X�e���p�ɗ\��
	"",				// 1A	����`
	"ESC",			// 1B	Esc�L�[
	"CONVERT",		// 1C	�����V�X�e���p�ɗ\��
	"NOCONVERT",	// 1D	�����V�X�e���p�ɗ\��
	"", "",			// 1E� 1F	�����V�X�e���p�ɗ\��
	"Space",		// 20	Space�L�[
	"PageUp",		// 21	Page Up�L�[
	"PageDown",		// 22	Page Down�L�[
	"End",			// 23	End�L�[
	"Home",			// 24	Home�L�[
	"��",			// 25	���L�[
	"��",			// 26	���L�[
	"��",			// 27	���L�[
	"��",			// 28	���L�[
	"SELECT",		// 29	Select�L�[
	"",				// 2A	OEM�w��
	"EXECUTE",		// 2B	Execute�L�[
	"SNAPSHOT",		// 2C	Print Screen�L�[ (Windows 3.0�ȍ~�p)
	"Ins",			// 2D	Ins�L�[
	"Del",			// 2E	Del�L�[
	"Help",			// 2F	Help�L�[
	"0",			// 30	0�L�[
	"1",			// 31	1�L�[
	"2",			// 32	2�L�[
	"3",			// 33	3�L�[
	"4",			// 34	4�L�[
	"5",			// 35	5�L�[
	"6",			// 36	6�L�[
	"7",			// 37	7�L�[
	"8",			// 38	8�L�[
	"9",			// 39	9�L�[
	"", "", "", "", "", "", "",	// 3A�`40	����`
	"A",			// 41	A�L�[
	"B",			// 42	B�L�[
	"C",			// 43	C�L�[
	"D",			// 44	D�L�[
	"E",			// 45	E�L�[
	"F",			// 46	F�L�[
	"G",			// 47	G�L�[
	"H",			// 48	H�L�[
	"I",			// 49	I�L�[
	"J",			// 4A	J�L�[
	"K",			// 4B	K�L�[
	"L",			// 4C	L�L�[
	"M",			// 4D	M�L�[
	"N",			// 4E	N�L�[
	"O",			// 4F	O�L�[
	"P",			// 50	P�L�[
	"Q",			// 51	Q�L�[
	"R",			// 52	R�L�[
	"S",			// 53	S�L�[
	"T",			// 54	T�L�[
	"U",			// 55	U�L�[
	"V",			// 56	V�L�[
	"W",			// 57	W�L�[
	"X",			// 58	X�L�[
	"Y",			// 59	Y�L�[
	"Z",			// 5A	Z�L�[
	"", "", "", "", "",	// 5B�`5F	����`
	"NUM0",			// 60	�e���L�[��0�L�[
	"NUM1",			// 61	�e���L�[��1�L�[
	"NUM2",			// 62	�e���L�[��2�L�[
	"NUM3",			// 63	�e���L�[��3�L�[
	"NUM4",			// 64	�e���L�[��4�L�[
	"NUM5",			// 65	�e���L�[��5�L�[
	"NUM6",			// 66	�e���L�[��6�L�[
	"NUM7",			// 67	�e���L�[��7�L�[
	"NUM8",			// 68	�e���L�[��8�L�[
	"NUM9",			// 69	�e���L�[��9�L�[
	"[*]",			// 6A	�e���L�[��*�L�[
	"[+]",			// 6B	�e���L�[��+�L�[
	"SEPARATOR",	// 6C	Separator�L�[
	"[-]",			// 6D	�e���L�[�́|�L�[
	"[.]",			// 6E	�e���L�[��.�L�[
	"[/]",			// 6F	�e���L�[��/�L�[
	"F1",			// 70	F1�L�[
	"F2",			// 71	F2�L�[
	"F3",			// 72	F3�L�[
	"F4",			// 73	F4�L�[
	"F5",			// 74	F5�L�[
	"F6",			// 75	F6�L�[
	"F7",			// 76	F7�L�[
	"F8",			// 77	F8�L�[
	"F9",			// 78	F9�L�[
	"F10",			// 79	F10�L�[
	"F11",			// 7A	F11�L�[
	"F12",			// 7B	F12�L�[
	"F13",			// 7C	F13�L�[
	"F14",			// 7D	F14�L�[
	"F15",			// 7E	F15�L�[
	"F16",			// 7F	F16�L�[
	"F17",			// 80H	F17�L�[
	"F18",			// 81H	F18�L�[
	"F19",			// 82H	F19�L�[
	"F20",			// 83H	F20�L�[
	"F21",			// 84H	F21�L�[
	"F22",			// 85H	F22�L�[
	"F23",			// 86H	F23�L�[
	"F24",			// 87H	F24�L�[
	"", "", "", "", "", "", "", "",	// 88�`8F	����`
	"NUMLOCK",		// 90	Num Lock�L�[
	"SCROLL",		// 91	Scroll Lock�L�[
};

/////////////////////////////////////////////////////////////////////////////
// CSuperTagEditorApp

BEGIN_MESSAGE_MAP(CSuperTagEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CSuperTagEditorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, OnUpdateFileMruFile)
	ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, OnOpenRecentFile)
	ON_UPDATE_COMMAND_UI(ID_FAVORITE_FOLDER_01, OnUpdateFavoriteFolder01)
	ON_UPDATE_COMMAND_UI(ID_FAVORITE_FOLDER_02, OnUpdateFavoriteFolder02)
	ON_UPDATE_COMMAND_UI(ID_FAVORITE_FOLDER_03, OnUpdateFavoriteFolder03)
	ON_UPDATE_COMMAND_UI(ID_FAVORITE_FOLDER_04, OnUpdateFavoriteFolder04)
	ON_UPDATE_COMMAND_UI(ID_FAVORITE_FOLDER_05, OnUpdateFavoriteFolder05)
	ON_UPDATE_COMMAND_UI(ID_FAVORITE_FOLDER_06, OnUpdateFavoriteFolder06)
	ON_UPDATE_COMMAND_UI(ID_FAVORITE_FOLDER_07, OnUpdateFavoriteFolder07)
	ON_UPDATE_COMMAND_UI(ID_FAVORITE_FOLDER_08, OnUpdateFavoriteFolder08)
	ON_UPDATE_COMMAND_UI(ID_FAVORITE_FOLDER_09, OnUpdateFavoriteFolder09)
	ON_UPDATE_COMMAND_UI(ID_FAVORITE_FOLDER_10, OnUpdateFavoriteFolder10)
	ON_COMMAND(ID_FAVORITE_FOLDER_01, OnFavoriteFolder01)
	ON_COMMAND(ID_FAVORITE_FOLDER_02, OnFavoriteFolder02)
	ON_COMMAND(ID_FAVORITE_FOLDER_03, OnFavoriteFolder03)
	ON_COMMAND(ID_FAVORITE_FOLDER_04, OnFavoriteFolder04)
	ON_COMMAND(ID_FAVORITE_FOLDER_05, OnFavoriteFolder05)
	ON_COMMAND(ID_FAVORITE_FOLDER_06, OnFavoriteFolder06)
	ON_COMMAND(ID_FAVORITE_FOLDER_07, OnFavoriteFolder07)
	ON_COMMAND(ID_FAVORITE_FOLDER_08, OnFavoriteFolder08)
	ON_COMMAND(ID_FAVORITE_FOLDER_09, OnFavoriteFolder09)
	ON_COMMAND(ID_FAVORITE_FOLDER_10, OnFavoriteFolder10)
	//}}AFX_MSG_MAP
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperTagEditorApp �N���X�̍\�z

CSuperTagEditorApp::CSuperTagEditorApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
	m_hAccel = 0;
	m_accelTable = NULL;		// �A�N�Z�����[�^�e�[�u��
	m_nAccelTable = 0;
}

CSuperTagEditorApp::~CSuperTagEditorApp()
{
	CString strINI = m_pszProfileName;
	SaveProfile();
	FreeProfile();
	m_pRecentFileList->WriteList();
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CSuperTagEditorApp �I�u�W�F�N�g

CSuperTagEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSuperTagEditorApp �N���X�̏�����
// =============================================
// CSuperTagEditorApp::MakeFileName
// �T�v  : ���A�v���P�[�V�����̃p�X����t�@�C������
//       : �t���p�X�ō쐬����
// ����  : sExt			= �t�@�C���g���q
// �߂�l: wchar_t *		= �t�@�C����(NULL=���s)
// =============================================
wchar_t *CSuperTagEditorApp::MakeFileName(wchar_t *sExt)
{
	wchar_t   drive[_MAX_DRIVE];
	wchar_t   dir[_MAX_DIR];
	wchar_t   fname[_MAX_FNAME];
	wchar_t   buff[_MAX_PATH] = { '\0' };

	//���ȃA�v���̃p�X�����i�召�������ʕt���j
	GetModuleFileName(m_hInstance, buff, _MAX_PATH);
	WIN32_FIND_DATA wfd;

	HANDLE  h = ::FindFirstFile(buff, &wfd);
	if (h == NULL) return(NULL);

	_tsplitpath(buff, drive, dir, NULL, NULL);
	_tmakepath(buff, drive, dir, wfd.cFileName, NULL);
	::FindClose(h);

	_tsplitpath(buff, drive, dir, fname, NULL);
	_tmakepath(buff, drive, dir, fname, sExt);
	return(_tcsdup(buff));
}


BOOL CSuperTagEditorApp::InitInstance()
{
	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������
	// ��������Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ���
	// ���폜���Ă��������B

	// ���d�N���֎~���� /* FreeFall 045 */

	// �ݒ肪�ۑ�����鉺�̃��W�X�g�� �L�[��ύX���܂��B
	// TODO: ���̕�������A��Ж��܂��͏����ȂǓK�؂Ȃ��̂�
	// �ύX���Ă��������B
	//SetRegistryKey(L"MERCURY");
	free((void *)m_pszProfileName);
	m_pszProfileName = MakeFileName(L"ini");
	{ /* STEP 031 */
		BOOL bFlag = FALSE;
		for (int i = 1; i < __argc; i++) {
			LPCWSTR pszParam = __wargv[i];
			if (bFlag) {
				free((void *)m_pszProfileName);
				m_pszProfileName = _wcsdup(pszParam);
				break;
			}
			if (pszParam[0] == '-' || pszParam[0] == '/') {
				if (wcscmp(pszParam, L"-I") == 0 || wcscmp(pszParam, L"/I") == 0) {
					bFlag = TRUE;
				}
			}
		}
	}
	//if (MyGetProfileInt(L"STEx", L"UseRegistry", 0) ? true : false) {
	//	SetRegistryKey(_T(L"MERCURY"));
	//}

	// �������Őݒ肵�� INI �t�@�C�����̂̓f�X�g���N�^�� free �����
	CString strINI = m_pszProfileName;
	InitProfile();
	ReadRegistry();

	LoadStdProfileSettings(g_nRecentFolder);  // �W���� INI �t�@�C���̃I�v�V���������[�ނ��܂� (MRU ���܂�)  /* StartInaction 053 */

	// ���d�N���֎~���� /* FreeFall 045 */
	if (!g_bValidDupExec) {
		wchar_t	*sMutexName = PROG_NAME;
		HANDLE hPrevMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, sMutexName);
		if (hPrevMutex) {
			//		MessageBox(NULL, L"���� "PROG_NAME" �͋N�����ł�", L"���d�N���G���[", MB_ICONSTOP|MB_OK|MB_TOPMOST);
			// �C�� by Kobarin
			// �N���ς݂� STE �Ƀt�@�C�����E�t�H���_����n��
			if (__argc >= 2) {
				KbDDEClient ddeClient(NULL, L"SuperTagEditor", L"SuperTagEditor");
				int i;
				for (i = 1; i < __argc; i++) {
					ddeClient.Execute(__wargv[i],//�t�@�C����
						L""        //�X�C�b�`�i�Ȃ��j
						);
				}
			}
			CloseHandle(hPrevMutex);
			//CloseHandle(hPrevMutex);
			return FALSE;
		}
		m_hMutex = CreateMutex(FALSE, 0, sMutexName);
	}

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSuperTagEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CSuperTagEditorView));
	AddDocTemplate(pDocTemplate);

	// DDE Execute open ���g�p�\�ɂ��܂��B
	EnableShellOpen();
	//	RegisterShellFileTypes(TRUE);

	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �ő剻�N���Ή�
	if (g_bMainFrameZoomed) {
		CWinApp::m_nCmdShow = SW_SHOWMAXIMIZED;
	} else if (g_bMainFrameIconic) {
		CWinApp::m_nCmdShow = SW_SHOWMINIMIZED;
	}

	// �R�}���h���C���Ńf�B�X�p�b�` �R�}���h���w�肵�܂��B
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// ProcessShellCommand()�ň����Ȃ��������̂������ŏ���
	{ /* Misirlou 140 */
		BOOL bFirst = TRUE;
		for (int i = 1; i < __argc; i++) {
			LPCWSTR pszParam = __targv[i];
			BOOL bFlag = FALSE;
			BOOL bLast = ((i + 1) == __argc);
			if (pszParam[0] == '-' || pszParam[0] == '/') {
				// remove flag specifier
				bFlag = TRUE;
				++pszParam;
			}
			if (!bFlag && !bFirst) {
				OpenDocumentFile(pszParam);
			}
			if (!bFlag)	bFirst = FALSE;
		}
	}

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	if (g_bMainFrameZoomed) {
		//		m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
		//		m_pMainWnd->UpdateWindow();
	} else if (g_bMainFrameIconic) {
		//		m_pMainWnd->ShowWindow(SW_SHOWMINIMIZED);
		//		m_pMainWnd->UpdateWindow();
	} else {
		m_pMainWnd->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateWindow();
	}

	// �h���b�O/�h���b�v �I�[�v���������܂�
	//	m_pMainWnd->DragAcceptFiles();

	//�ǉ� by Kobarin
	//KbSTE �̃t���p�X�t�@�C���������W�X�g���ɕۑ�
	//�iKbMedia Player �ƘA�g���邽�߁j
	//WriteKbSTEPathToRegistry();

	return TRUE;
}

int CSuperTagEditorApp::ExitInstance()
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	ReleaseMutex(m_hMutex);

	// �A�N�Z�����[�^�e�[�u���̉��
	DestroyAccelerator();

	delete[] g_genreListUSER;

	return CWinApp::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog {
public:
	CAboutDlg();

	// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_strVersion;
	//}}AFX_DATA

	// ClassWizard ���z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

	// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
	// ���b�Z�[�W �n���h���͂���܂���B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT

	// �o�[�W�������̐ݒ�
	m_strVersion.Format(PROG_NAME L" Ver " PROG_VERSION L"(Build:%d) ��", BUILDCOUNT_NUM);
	//m_strVersion.Format(PROG_NAME_ORG2 " PROG_NAME_ORG" Ver L"PROG_VERSION_ORG"��) Ver L"PROG_VERSION_ORG2" ��\n\n"PROG_NAMEL" Version L"PROG_VERSION);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_ST_VERSION, m_strVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	// ���b�Z�[�W �n���h���͂���܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CSuperTagEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSuperTagEditorApp ���b�Z�[�W �n���h��
static	wchar_t	*sSectionOption = L"Option";
static	wchar_t	*sKeyVersion = L"Version";
static	wchar_t	*sKeyCurrentDir = L"CurrentDir";
static	wchar_t	*sKeyCurrentPlayList = L"CurrentPlayList";
static	wchar_t	*sKeyEnterBeginEdit = L"EnterBeginEdit";
static	wchar_t	*sKeyESCEditCancel = L"ESCEditCance";
static	wchar_t	*sKeyEnableEditCursorExit = L"EnableEditCursorExit";
static	wchar_t	*sKeyEditOkDown = L"EditOkDown";
static	wchar_t	*sKeyKeepTimeStamp = L"KeepTimeStamp";
static	wchar_t	*sKeySyncCreateTime = L"SyncCreateTime";
static	wchar_t	*sKeyChangeFileExt = L"ChangeFileExt";
static	wchar_t	*sKeyLoadFileChecked = L"LoadFileChecked";
static	wchar_t	*sKeyHideMP3ListFile = L"HideMP3ListFile";
static	wchar_t	*sKeyDropSearchSubFolder = L"DropSearchSubFolder";	/* TyphoonSwell 026 */
static	wchar_t	*sKeyShowZenSpace = L"ShowZenSpace";	/* BeachMonster 107 */
static	wchar_t	*sKeyShowOtherChar = L"ShowOtherwchar_t";	/* BeachMonster 107 */
static	wchar_t	*sKeySortIgnoreCase = L"SortIgnoreCase";	/* BeachMonster4 114 */
static	wchar_t	*sKeySortIgnoreZenHan = L"SortIgnoreZenHan";	/* BeachMonster4 114 */
static	wchar_t	*sKeySortIgnoreKataHira = L"SortIgnoreKataHira";	/* FunnyCorn 179 */
static	wchar_t	*sKeyShowTotalParent = L"ShowTotalParent";	/* RockDance 128 */
static	wchar_t	*sKeyShowTips = L"ShowTips";	/* Rumble 188 */
static	wchar_t	*sKeyChangeTextFile = L"ChangeTextFile";
static	wchar_t	*sKeyEditFiledSIF = L"EditFiledSI";
static	wchar_t	*sKeyAutoOpenFolder = L"AutoOpenFolder";
static	wchar_t	*sKeyLoadFileAdjustColumn = L"LoadFileAdjustColumn";
static	wchar_t	*sKeySetLyricsDir = L"SetLyricsDir";
static	wchar_t	*sKeySearchLyricsSubDir = L"SearchLyricsSubDir";
static	wchar_t	*sKeyEnableSearchSubDir = L"EnableSearchSubDir";
static	wchar_t	*sKeyLyricsPath = L"LyricsPath";
static	wchar_t	*sKeyCheckFileName = L"CheckFileName";
static	wchar_t	*sKeyPlayerType = L"PlayerType";
static	wchar_t	*sKeyWinAmpPath = L"WinAmpPath";

static	wchar_t	*sKeyID3v2GenreAddNumber = L"ID3v2GenreAddNumber";
static	wchar_t	*sKeyFileNameMaxCheck = L"FileNameMaxCheck";
static	wchar_t	*sKeyFileNameMaxChar = L"FileNameMaxwchar_t";
static	wchar_t	*sKeyFileNameMaxCellColor = L"FileNameMaxCellColor";

static	wchar_t	*sSectionFolderSync = L"FolderSync";
static	wchar_t	*sKeyEnableFolderSync = L"EnableFolderSync";
static	wchar_t	*sKeySyncRootFolder = L"RootFolder";
static	wchar_t	*sKeySyncSelectAlways = L"SelectAlways";
static	wchar_t	*sKeySyncDeleteFolder = L"DeleteFolder";
static	wchar_t	*sKeySyncLyricsFileMove = L"LyricsFileMove";

static	wchar_t	*sSectionConfMessage = L"ConfMessage";
static	wchar_t	*sKeyConfConvMP3 = L"ConvMP3";
static	wchar_t	*sKeyConfConvRMP = L"ConvRMP";
static	wchar_t	*sKeyConfConvID3v2 = L"ConvID3v2";
static	wchar_t	*sKeyConfDeleteFile = L"DeleteFile";
static	wchar_t	*sKeyConfDeleteList = L"DeleteList";
static	wchar_t	*sKeyConfEditModify = L"EditModify";
static	wchar_t	*sKeyConfFolderSync = L"FolderSync";

static	wchar_t	*sSectionLoadPlayList = L"LoadPlayList";
static	wchar_t	*sKeyClearList = L"ClearList";
static	wchar_t	*sKeyClearCheck = L"ClearCheck";
static	wchar_t	*sKeyAddList = L"AddList";
static	wchar_t	*sKeyFileCheck = L"FileCheck";

static	wchar_t	*sSectionCheckWord[CHECK_STATE_MAX] = { L"CheckWord", L"ReplaceWord" };
static	wchar_t	*sKeySearchWord = L"SearchWord";
static	wchar_t	*sKeyReplaceWord = L"ReplaceWord";
static	wchar_t	*sKeyTargetColumn = L"TargetColumn";
static	wchar_t	*sKeyCheckDiffUL = L"CheckDiffU";
static	wchar_t	*sKeyRegExp = L"RegExp";
static	wchar_t	*sKeyRangeSelected = L"RangeSelected";
static	wchar_t	*sKeyMatchComplete = L"MatchComplete";
static	wchar_t	*sKeyMatchSelected = L"MatchSelected";

// ���[�U�[�����ϊ�
static	wchar_t	*sSectionUserConvFormat = L"UserConvFormat";
static	wchar_t	*sKeyConvFormatType = L"ConvFormatType";
static	wchar_t	*sKeyUserFormName = L"Name";
static	wchar_t	*sKeyUserFormTag2File = L"TagToFile";
static	wchar_t	*sKeyUserFormFile2Tag = L"FileToTag";

// �g���ŏ����ϊ�
static	wchar_t	*sSectionConvFormatEx = L"ConvFormatEx";
//static	wchar_t	*sKeyUserFormName		= L"Name";
static	wchar_t	*sKeyUserFormat = L"Format";
static	wchar_t	*sKeyUserFixString = L"FixString";
static	wchar_t	*sKeyUserInitNumber = L"InitNumber";
static	wchar_t	*sKeyUserAddNumber = L"AddNumber";
static	wchar_t	*sKeyUserColumnCount = L"ColumnCount";
static	wchar_t	*sKeyUserSpaceInit = L"SpaceInit";

// �ړ���t�H���_����
static	wchar_t	*sSectionMoveFolder = L"MoveFolderFormat";
//static	wchar_t	*sKeyUserFormName		= L"Name";
static	wchar_t	*sKeyMoveFolderFormat = L"Format";
static	wchar_t	*sKeyMoveFolderFixString = L"FixString";
static	wchar_t	*sKeyMoveFolderCopy = L"Copy";
static	wchar_t	*sKeyMoveFolderInitFolder = L"InitFolder";

// �����R�s�[ /* FunnyCorn 175 */
static	wchar_t	*sSectionCopyFormat = L"CopyFormatFormat";
//static	wchar_t	*sKeyUserFormName		= L"Name";
static	wchar_t	*sKeyCopyFormatFormat = L"Format";
static	wchar_t	*sKeyCopyFormatFixString = L"FixString";

// �^�O���ϊ� /* STEP 034 */
static	wchar_t	*sSectionConvFormatTag2Tag = L"ConvFormatTag2Tag";
static	wchar_t	*sKeyUserTag2TagFormName = L"Name";
static	wchar_t	*sKeyUserTagTagFormat = L"Format";

// ��^���\��t�� /* SeaKnows 030 */
static	wchar_t	*sSectionTeikei = L"Teikei";
static	wchar_t	*sSectionTeikeiGroupName = L"TeikeiGroupName";
static	wchar_t	*sSectionTeikeiPaste = L"TeikeiPaste";
static	wchar_t	*sSectionTeikeiAddSpace = L"TeikeiAddSpace";
static	wchar_t	*sSectionTeikeiAddChar = L"TeikeiAddwchar_t";
static	wchar_t	*sSectionTeikeiFront = L"TeikeiAddFront";
static	wchar_t	*sSectionTeikeiBack = L"TeikeiAddBack";
static	wchar_t	*sSectionTeikeiShowDialog = L"TeikeiShowDialog";

// �t�H���_�P��I�� /* SeaKnows 033 */
static	wchar_t	*sSectionValidFolderSelect = L"ValidFolderSelect";
// ���d�N���������� /* FreeFall 045 */
static	wchar_t	*sSectionValidDupExec = L"ValidDupExec";
// �ŋߎg�����t�H���_�̐�
static	wchar_t	*sSectionRecentFolderNum = L"RecentFolderNum";
// �����E�u���_�C�A���O�̈ʒu���L������
static	wchar_t	*sSectionSaveRepDlgPos = L"SaveRepDlgPos";
static	wchar_t	*sSectionSaveRepDlgPosX = L"SaveRepDlgPosX";
static	wchar_t	*sSectionSaveRepDlgPosY = L"SaveRepDlgPosY";
// �������ɘA�Ԃ�ǉ��_�C�A���O�̐ݒ� /* Baja 159 */
static	wchar_t	*sSectionAddNumberWidth = L"AddNumberWidth";
static	wchar_t	*sSectionAddNumberPos = L"AddNumberPos";
static	wchar_t	*sSectionAddNumberSep = L"AddNumberSep";
static	wchar_t	*sSectionAddNumberBef = L"AddNumberBef"; /* Conspiracy 194 */
static	wchar_t	*sSectionAddNumberAft = L"AddNumberAft"; /* Conspiracy 194 */
// Audio List�ɕ\�������t�H���_���Ȃǂ̕��ނ��Z���T�C�Y�𖳎�����(���ۂׂ͗R�Z�����܂�)�\������
static	wchar_t	*sSectionAudioListShow = L"AudioListShow"; /* Conspiracy 199 */

// �t�H���g�ݒ�
static	wchar_t	*sSectionFont = L"Font";
static	wchar_t	*sKeyFontFace = L"Face";
static	wchar_t	*sKeyFontHeight = L"Height";
static	wchar_t	*sKeyFontWidth = L"Width";
static	wchar_t	*sKeyFontEscapement = L"Escapement";
static	wchar_t	*sKeyFontOrientation = L"Orientation";
static	wchar_t	*sKeyFontWeight = L"Weight";
static	wchar_t	*sKeyFontItalic = L"Italic";
static	wchar_t	*sKeyFontUnderline = L"Underline";
static	wchar_t	*sKeyFontStrikeOut = L"StrikeOut";
static	wchar_t	*sKeyFontCharSet = L"wchar_tSet";
static	wchar_t	*sKeyFontOutPrecision = L"OutPrecision";
static	wchar_t	*sKeyFontClipPrecision = L"ClipPrecision";
static	wchar_t	*sKeyFontQuality = L"Quality";
static	wchar_t	*sKeyFontPitchAndFamily = L"PitchAndFamily";

// ���X�g�o�͏���
static	wchar_t	*sSectionWriteFormat = L"WriteFormat";
static	wchar_t	*sKeyWriteFormName = L"Name";
static	wchar_t	*sKeyWriteFileName = L"FileName";
static	wchar_t	*sKeyWriteExtName = L"ExtName";
static	wchar_t	*sKeyWriteSelected = L"WriteSelected";
static	wchar_t	*sKeyWriteCurrentFile = L"CurrentFile";
static	wchar_t	*sKeyWriteIsHtml = L"IsHtm";
static	wchar_t	*sKeyWriteHtml = L"WriteHtm"; /* BeachMonster5 120 */

static	wchar_t	*sSectionRepFileName = L"RepFileName";
static	wchar_t	*sKeyRepCharAfter = L"Repwchar_tAfter";
static	wchar_t	*sKeyRepCharBefore = L"Repwchar_tBefore";	/* FreeFall 050 */

static	wchar_t	*sSectionSort = L"Sort";
static	wchar_t	*sKeySortColumn = L"Column";
static	wchar_t	*sKeySortType = L"Type";

static	wchar_t	*sSectionClass = L"Class";
static	wchar_t	*sKeyClassType = L"Type";
static	wchar_t	*sKeyClassColumn = L"Column";

static	wchar_t	*sSectionWindow = L"Window";
static	wchar_t	*sKeyWinZoomed = L"Zoomed";
static	wchar_t	*sKeyWinIconic = L"Iconic";
static	wchar_t	*sKeyMainWindow = L"MainWindow";
static	wchar_t	*sKeySplitSize = L"SplitSize";

static	wchar_t	*sSectionKeyConfig = L"KeyConfig";

static	wchar_t	*sSectionGenreList = L"GenreList";
static	wchar_t	*sSectionUserGenreList = L"UserGenreList";
static	wchar_t	*sKeyUserGenreAddList = L"AddList";
static	wchar_t	*sKeyUserGenreNo = L"No";
static	wchar_t	*sKeyUserGenreName = L"Name";

// �����퓝�� /* StartInaction 054 */
static	wchar_t	*sKeyUnifyAlpha = L"UnifyAlpha";
static	wchar_t	*sKeyUnifyHiraKata = L"UnifyHiraKata";
static	wchar_t	*sKeyUnifyKata = L"UnifyKata";
static	wchar_t	*sKeyUnifyKigou = L"UnifyKigou";
static	wchar_t	*sKeyUnifySuji = L"UnifySuji";
static	wchar_t	*sKeyUnifyUpLow = L"UnifyUpLow";
static	wchar_t	*sKeyUnifyFixedUpLow = L"UnifyFixedUpLow"; /* STEP 040 */

// �g���q���� /* STE 007 */
static	wchar_t	*sKeyFileExtChange = L"FileExtChange";

// �t�@�C���������퓝�� /* LastTrain 058 */
static	wchar_t	*sKeyFileUnifyAlpha = L"FileUnifyAlpha";
static	wchar_t	*sKeyFileUnifyHiraKata = L"FileUnifyHiraKata";
static	wchar_t	*sKeyFileUnifyKata = L"FileUnifyKata";
static	wchar_t	*sKeyFileUnifyKigou = L"FileUnifyKigou";
static	wchar_t	*sKeyFileUnifySuji = L"FileUnifySuji";
static	wchar_t	*sKeyFileUnifyUpLow = L"FileUnifyUpLow";

// �v���C���X�g���͐ݒ�_�C�A���O��\������ /* RockDance 126 */
static	wchar_t	*sKeyShowLoadPlaylistDlg = L"ShowLoadPlaylistDlg";

// ���C�ɓ���̃t�H���_ /* RockDance 129 */
static	wchar_t	*sSectionFavorites = L"Favorites";

static	wchar_t	*sKeyFirstUpperIgnoreWord = L"FistUpperIgnoreWord";
static	wchar_t	*sKeyFirstUpperIgnoreWords = L"FistUpperIgnoreWords";
static	wchar_t	*sKeyFirstUpperSentenceSeparator = L"FistUpperSentenceSeparator";
static	wchar_t	*sKeyUserConvAddMenu = L"UserConvAddMenu";
static	wchar_t	*sKeyZenHanKigouKana = L"ZenHanKigouKana";

void CSuperTagEditorApp::ReadWindowStatus(wchar_t *sKey, RECT *rect)
{
	static	wchar_t	*sDefault = L"0 0 0 0";
	CString	str;
	LPCWSTR	sBuffer;
	CString strINI = m_pszProfileName;
	//Profile_Initialize(strINI, TRUE);
	str = MyGetProfileString(sSectionWindow, sKey, sDefault);
	sBuffer = (LPCWSTR)str;
	swscanf(sBuffer, L"%d %d %d %d", &rect->left,
		&rect->top,
		&rect->right,
		&rect->bottom);
	//Profile_Free();
}

void CSuperTagEditorApp::WriteWindowStatus(wchar_t *sKey, RECT *rect)
{
	CString	str;
	str.Format(L"%d %d %d %d", rect->left,
		rect->top,
		rect->right,
		rect->bottom);
	CString strINI = m_pszProfileName;
	//Profile_Initialize(strINI, TRUE);
	MyWriteProfileString(sSectionWindow, sKey, str);
	//Profile_Free();
}

void CSuperTagEditorApp::ReadRegistry(void)
{
	CString strINI = m_pszProfileName;
	//Profile_Initialize(strINI, TRUE);
	int		i;

	// �e��ݒ��ǂݍ���
	CString	strVersion;
	strVersion = MyGetProfileString(sSectionOption, sKeyVersion, L"");
	g_bIsVersionUp = wcscmp(strVersion, PROG_VERSION) ? true : false;

	g_strCurrentDirectory = MyGetProfileString(sSectionOption, sKeyCurrentDir, L"");
	g_strCurrentPlayList = MyGetProfileString(sSectionOption, sKeyCurrentPlayList, L"*.m3u");

	// ��� - ���[�U�[�C���^�[�t�F�[�X
	g_bOptESCEditCancel = MyGetProfileInt(sSectionOption, sKeyESCEditCancel, 0) ? true : false;
	g_bOptEnableEditCursorExit = MyGetProfileInt(sSectionOption, sKeyEnableEditCursorExit, 1) ? true : false;
	g_bOptEditOkDown = MyGetProfileInt(sSectionOption, sKeyEditOkDown, 1) ? true : false;
	g_bOptEnterBeginEdit = MyGetProfileInt(sSectionOption, sKeyEnterBeginEdit, 0) ? true : false;

	// ��� - ����ݒ�
	g_bOptKeepTimeStamp = MyGetProfileInt(sSectionOption, sKeyKeepTimeStamp, 0) ? true : false;
	g_bOptSyncCreateTime = MyGetProfileInt(sSectionOption, sKeySyncCreateTime, 0) ? true : false;
	g_bOptChangeFileExt = MyGetProfileInt(sSectionOption, sKeyChangeFileExt, 0) ? true : false;
	g_bOptAutoOpenFolder = MyGetProfileInt(sSectionOption, sKeyAutoOpenFolder, 0) ? true : false;
	g_bOptLoadFileAdjustColumn = MyGetProfileInt(sSectionOption, sKeyLoadFileAdjustColumn, 1) ? true : false;
	g_bOptLoadFileChecked = MyGetProfileInt(sSectionOption, sKeyLoadFileChecked, 1) ? true : false;
	g_bOptHideMP3ListFile = MyGetProfileInt(sSectionOption, sKeyHideMP3ListFile, 0) ? true : false;

	// ��� - �̎��t�@�C��
	g_bOptChangeTextFile = MyGetProfileInt(sSectionOption, sKeyChangeTextFile, 1) ? true : false;
	g_bOptSetLyricsDir = MyGetProfileInt(sSectionOption, sKeySetLyricsDir, 0) ? true : false;
	g_bOptSearchLyricsSubDir = MyGetProfileInt(sSectionOption, sKeySearchLyricsSubDir, 0) ? true : false;
	g_strOptLyricsPath = MyGetProfileString(sSectionOption, sKeyLyricsPath, L"");

	//
	g_bOptEditFieldSIF = MyGetProfileInt(sSectionOption, sKeyEditFiledSIF, 1) ? true : false;
	g_nOptCheckFileName = MyGetProfileInt(sSectionOption, sKeyCheckFileName, FILENAME_CONV_MULTIBYTE);
	g_bEnableSearchSubDir = MyGetProfileInt(sSectionOption, sKeyEnableSearchSubDir, 1) ? true : false;

	// �t�H���_�̓���
	g_bEnableFolderSync = MyGetProfileInt(sSectionFolderSync, sKeyEnableFolderSync, 0) ? true : false;
	g_strRootFolder = MyGetProfileString(sSectionFolderSync, sKeySyncRootFolder, L"");
	g_bSyncSelectAlways = MyGetProfileInt(sSectionFolderSync, sKeySyncSelectAlways, 0) ? true : false;
	g_bSyncDeleteFolder = MyGetProfileInt(sSectionFolderSync, sKeySyncDeleteFolder, 1) ? true : false;
	g_bSyncLyricsFileMove = MyGetProfileInt(sSectionFolderSync, sKeySyncLyricsFileMove, 1) ? true : false;

	// �m�F���b�Z�[�W�\��
	g_bConfDeleteFile = MyGetProfileInt(sSectionConfMessage, sKeyConfDeleteFile, 1) ? true : false;
	g_bConfDeleteList = MyGetProfileInt(sSectionConfMessage, sKeyConfDeleteList, 1) ? true : false;
	g_bConfEditModify = MyGetProfileInt(sSectionConfMessage, sKeyConfEditModify, 1) ? true : false;
	g_bConfFolderSync = MyGetProfileInt(sSectionConfMessage, sKeyConfFolderSync, 1) ? true : false;

	// �v���C���X�g
	g_bPlayListClearList = MyGetProfileInt(sSectionLoadPlayList, sKeyClearList, 0) ? true : false;
	g_bPlayListClearCheck = MyGetProfileInt(sSectionLoadPlayList, sKeyClearCheck, 1) ? true : false;
	g_bPlayListAddList = MyGetProfileInt(sSectionLoadPlayList, sKeyAddList, 0) ? true : false;
	g_bPlayListFileCheck = MyGetProfileInt(sSectionLoadPlayList, sKeyFileCheck, 1) ? true : false;

	// �����`�F�b�N�̏��
	for (i = 0; i < CHECK_STATE_MAX; i++) {
		CHECK_WORD_STATE	*pState = &g_chkWord[i];
		wchar_t 	*sSectionName = sSectionCheckWord[i];
		pState->strSearchWord = MyGetProfileString(sSectionName, sKeySearchWord, L"");
		pState->strReplaceWord = MyGetProfileString(sSectionName, sKeyReplaceWord, L"");
		pState->nTargetColumn = MyGetProfileInt(sSectionName, sKeyTargetColumn, -1);
		pState->bCheckDiffUL = MyGetProfileInt(sSectionName, sKeyCheckDiffUL, 0) ? true : false;
		pState->bRegExp = MyGetProfileInt(sSectionName, sKeyRegExp, 0) ? true : false;
		pState->bRangeSelected = MyGetProfileInt(sSectionName, sKeyRangeSelected, 0) ? true : false;
		pState->bMatchComplete = MyGetProfileInt(sSectionName, sKeyMatchComplete, 0) ? true : false;
		pState->bMatchSelected = MyGetProfileInt(sSectionName, sKeyMatchSelected, 0) ? true : false;
	}

	// ���[�U�[�ϊ�����
	const wchar_t *sDefFormatTag2File = L"%ARTIST_NAME%-%ALBUM_NAME%-%TRACK_NAME%";
	const wchar_t *sDefFormatFile2Tag = sDefFormatTag2File;
	//g_nUserConvFormatType	= MyGetProfileInt(sSectionUserConvFormat, sKeyConvFormatType, 0);
	{ /* ���𑝂₵���̂Ŗ{�ƕ��p���ɉe����^���Ȃ��悤�� LastTrain 057 */
		CString		strSectionName;
		strSectionName = L"haseta\\";
		strSectionName += sSectionUserConvFormat;
		g_nUserConvFormatType = MyGetProfileInt(strSectionName, sKeyConvFormatType, 0);
	}
	for (i = 0; i < USER_CONV_FORMAT_MAX; i++) {
		CString		strKeyName;
		// ����
		strKeyName.Format(L"%s%d", sKeyUserFormName, i);
		g_userConvFormat[i].strName = MyGetProfileString(sSectionUserConvFormat, strKeyName, L"���̖��ݒ�");
		// �^�O��� => �t�@�C����
		strKeyName.Format(L"%s%d", sKeyUserFormTag2File, i);
		g_userConvFormat[i].strTag2File = MyGetProfileString(sSectionUserConvFormat, strKeyName, sDefFormatTag2File);
		// �t�@�C���� => �^�O���
		strKeyName.Format(L"%s%d", sKeyUserFormFile2Tag, i);
		g_userConvFormat[i].strFile2Tag = MyGetProfileString(sSectionUserConvFormat, strKeyName, sDefFormatFile2Tag);
		// �Q�ڈȍ~�̓f�t�H���g������̓N���A
		sDefFormatTag2File = sDefFormatFile2Tag = L"";
	}

	// �g���Ń��[�U�[�ϊ�����
	for (i = 0; i < USER_CONV_FORMAT_EX_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"%s%d", sSectionConvFormatEx, i);
		// ����
		g_userConvFormatEx[i].strName = MyGetProfileString(strSectionName, sKeyUserFormName, L"���̖��ݒ�");
		// ����
		g_userConvFormatEx[i].strFormat = MyGetProfileString(strSectionName, sKeyUserFormat, L"");
		// �Œ蕶����
		g_userConvFormatEx[i].strFixString = MyGetProfileString(strSectionName, sKeyUserFixString, L"");
		// �A�ԁF�����l
		g_userConvFormatEx[i].nInitNumber = MyGetProfileInt(strSectionName, sKeyUserInitNumber, 1);
		// �A�ԁF���Z�l
		g_userConvFormatEx[i].nAddNumber = MyGetProfileInt(strSectionName, sKeyUserAddNumber, 1);
		// �A�ԁF����
		g_userConvFormatEx[i].nColumnCount = MyGetProfileInt(strSectionName, sKeyUserColumnCount, 1);
		// �������ݕs�̃Z���ŘA�ԃN���A
		g_userConvFormatEx[i].bSpaceInitNumber = MyGetProfileInt(strSectionName, sKeyUserSpaceInit, 0) ? true : false;
	}

	// �ړ���t�H���_����
	for (i = 0; i < USER_MOVE_FODLER_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"haseta\\%s%d", sSectionMoveFolder, i);
		// ����
		g_userMoveFolder[i].strName = MyGetProfileString(strSectionName, sKeyUserFormName, L"���̖��ݒ�");
		// ����
		g_userMoveFolder[i].strFormat = MyGetProfileString(strSectionName, sKeyMoveFolderFormat, L"");
		// �Œ蕶����
		g_userMoveFolder[i].strFixString = MyGetProfileString(strSectionName, sKeyMoveFolderFixString, L"");
		// �R�s�[
		g_userMoveFolder[i].bCopy = MyGetProfileInt(strSectionName, sKeyMoveFolderCopy, 0) ? true : false;
		// �����t�H���_
		g_userMoveFolder[i].strInitFolder = MyGetProfileString(strSectionName, sKeyMoveFolderInitFolder, L""); /* STEP 022 */
	}

	// �����R�s�[ /* FunnyCorn 175 */
	for (i = 0; i < USER_COPY_FORMAT_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"haseta\\%s%d", sSectionCopyFormat, i);
		// ����
		g_userCopyFormat[i].strName = MyGetProfileString(strSectionName, sKeyUserFormName, L"���̖��ݒ�");
		// ����
		g_userCopyFormat[i].strFormat = MyGetProfileString(strSectionName, sKeyCopyFormatFormat, L"");
		// �Œ蕶����
		g_userCopyFormat[i].strFixString = MyGetProfileString(strSectionName, sKeyCopyFormatFixString, L"");
	}

	// �^�O���ϊ� /* STEP 034 */
	for (i = 0; i < USER_CONV_FORMAT_TAG2TAG_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"haseta\\%s%d", sSectionConvFormatTag2Tag, i);
		// ����
		g_userConvFormatTag2Tag[i].strName = MyGetProfileString(strSectionName, sKeyUserTag2TagFormName, L"���̖��ݒ�");
		// ����
		g_userConvFormatTag2Tag[i].strFormat = MyGetProfileString(strSectionName, sKeyUserTagTagFormat, L"");
	}

	{
		CString		sSectionOption;
		sSectionOption = L"haseta";
		//g_bOptID3v2GenreAddNumber	= MyGetProfileInt(sSectionOption, sKeyID3v2GenreAddNumber, 1) ? true : false;
		g_bConfFileNameMaxCheck = MyGetProfileInt(sSectionOption, sKeyFileNameMaxCheck, 0) ? true : false;
		g_bFileNameMaxCellColor = MyGetProfileInt(sSectionOption, sKeyFileNameMaxCellColor, 0) ? true : false; /* SeaKnows 036 */
		g_nConfFileNameMaxChar = MyGetProfileInt(sSectionOption, sKeyFileNameMaxChar, 255);
		g_bOptDropSearchSubFolder = MyGetProfileInt(sSectionOption, sKeyDropSearchSubFolder, 0) ? true : false;	/* TyphoonSwell 026 */
		g_bOptShowZenSpace = MyGetProfileInt(sSectionOption, sKeyShowZenSpace, 1) ? true : false;	/* BeachMonster 107 */
		g_sOptShowOtherChar = MyGetProfileString(sSectionOption, sKeyShowOtherChar, L"");
		g_bOptSortIgnoreCase = MyGetProfileInt(sSectionOption, sKeySortIgnoreCase, 0) ? true : false;	/* BeachMonster4 114 */
		g_bOptSortIgnoreZenHan = MyGetProfileInt(sSectionOption, sKeySortIgnoreZenHan, 0) ? true : false;	/* BeachMonster4 114 */
		g_bOptSortIgnoreKataHira = MyGetProfileInt(sSectionOption, sKeySortIgnoreKataHira, 0) ? true : false;	/* FunnyCorn 179 */
		g_bOptShowTotalParent = MyGetProfileInt(sSectionOption, sKeyShowTotalParent, 0) ? true : false;	/* RockDance 128 */
		g_bOptShowTips = MyGetProfileInt(sSectionOption, sKeyShowTips, 1) ? true : false;	/* Rumble 188 */
	}
	// ��^���\��t�� /* SeaKnows 030 *//* FreeFall 046 */
	for (int k = 0; k < 3; k++) {
		CString		sSectionOption;
		CString		strSectionName;
		sSectionOption = L"haseta";
		strSectionName.Format(L"%s%d", sSectionTeikeiGroupName, k);
		g_strTeikeiGroupName[k] = MyGetProfileString(sSectionOption, strSectionName, L"���̖��ݒ�");
		for (i = 0; i < 10; i++) {
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikei, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikei, k, i);
			}
			g_teikeiInfo[i + k * 10].strTeikei/* STEP 035 */ = MyGetProfileString(sSectionOption, strSectionName, L"");
			/* STEP 035 */
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiPaste, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiPaste, k, i);
			}
			g_teikeiInfo[i + k * 10].nTeikeiPaste = MyGetProfileInt(sSectionOption, strSectionName, 0);
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiAddSpace, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiAddSpace, k, i);
			}
			g_teikeiInfo[i + k * 10].bAddSpace = MyGetProfileInt(sSectionOption, strSectionName, 0) ? true : false;
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiAddChar, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiAddChar, k, i);
			}
			g_teikeiInfo[i + k * 10].bAddChar = MyGetProfileInt(sSectionOption, strSectionName, 0) ? true : false;
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiFront, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiFront, k, i);
			}
			g_teikeiInfo[i + k * 10].strFront = MyGetProfileString(sSectionOption, strSectionName, L"");
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiBack, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiBack, k, i);
			}
			g_teikeiInfo[i + k * 10].strBack = MyGetProfileString(sSectionOption, strSectionName, L"");
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiShowDialog, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiShowDialog, k, i);
			}
			g_teikeiInfo[i + k * 10].bShowDialog = MyGetProfileInt(sSectionOption, strSectionName, 1) ? true : false;
		}
	}
	// �\�t�g�E�F�A�� /* SeaKnows 031 */
	{
		CString		strSectionName;
		strSectionName = L"haseta";
		g_bValidFolderSelect = MyGetProfileInt(strSectionName, sSectionValidFolderSelect, 0) ? true : false;
		g_bValidDupExec = MyGetProfileInt(strSectionName, sSectionValidDupExec, 0) ? true : false; /* FreeFall 045 */
		g_nRecentFolder = MyGetProfileInt(strSectionName, sSectionRecentFolderNum, 5); /* MyWriteProfileInt 053 */
		g_bSaveRepDlgPos = MyGetProfileInt(strSectionName, sSectionSaveRepDlgPos, 0) ? true : false; /* WildCherry4 086 */
		g_nSaveRepDlgPosX = MyGetProfileInt(strSectionName, sSectionSaveRepDlgPosX, -1); /* WildCherry4 086 */
		g_nSaveRepDlgPosY = MyGetProfileInt(strSectionName, sSectionSaveRepDlgPosY, -1); /* WildCherry4 086 */
		g_nAddNumberWidth = MyGetProfileInt(strSectionName, sSectionAddNumberWidth, 2); /* Baja 159 */
		g_nAddNumberPos = MyGetProfileInt(strSectionName, sSectionAddNumberPos, 0); /* Baja 159 */
		g_strAddNumberSep = MyGetProfileString(strSectionName, sSectionAddNumberSep, L""); /* Baja 159 */
		g_strAddNumberBef = MyGetProfileString(strSectionName, sSectionAddNumberBef, L""); /* Conspiracy 194 */
		g_strAddNumberAft = MyGetProfileString(strSectionName, sSectionAddNumberAft, L""); /* Conspiracy 194 */
		g_bAudioListShow = MyGetProfileInt(strSectionName, sSectionAudioListShow, 0) ? true : false; /* Conspiracy 199 */
	}

	// ���X�g�o�͏���
	for (i = 0; i < WRITE_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"%s%d", sSectionWriteFormat, i);
		// ����
		g_writeFormat[i].strName = MyGetProfileString(strSectionName, sKeyWriteFormName, L"���̖��ݒ�");
		// �����t�@�C����
		g_writeFormat[i].strFileName = MyGetProfileString(strSectionName, sKeyWriteFileName, L"");
		// �g���q
		g_writeFormat[i].strExtName = MyGetProfileString(strSectionName, sKeyWriteExtName, L".txt");
		// �I���t�@�C���̂ݏo��
		g_writeFormat[i].bWriteSelected = MyGetProfileInt(strSectionName, sKeyWriteSelected, 0) ? true : false;
		// �J�����g�t�@�C����
		g_writeFormat[i].strCurrentFile = MyGetProfileString(strSectionName, sKeyWriteCurrentFile, L"");
		// HTML �t�@�C���o�͗p(��̏ꍇ�ɑS�p�X�y�[�X���o��)
		g_writeFormat[i].bIsHtml = MyGetProfileInt(strSectionName, sKeyWriteIsHtml, 0) ? true : false;
		{ /* BeachMonster5 120 */
			g_writeFormat[i].bWriteHtml = MyGetProfileInt(L"haseta\\" + strSectionName, sKeyWriteHtml, 0) ? true : false;
		}
	}

	// �t�@�C�����u������
	for (i = 0; i < FILENAME_REPLACE_MAX; i++) {
		FILENAME_REPLACE	*pRep = &g_fileNameReplace[i];
		CString		strKeyName;
		// �u���㕶����
		strKeyName.Format(L"%s%d", sKeyRepCharAfter, i);
		pRep->strBefore = g_sRepTable[i][0];
		pRep->strAfter = MyGetProfileString(sSectionRepFileName, strKeyName, g_sRepTable[i][1]);
	}
	// ���[�U�t�@�C�����u������ /* FreeFall 050 */
	{
		CString		strSectionName;
		strSectionName = L"haseta\\User";
		strSectionName += sSectionRepFileName;
		for (i = 0; i < USER_FILENAME_REPLACE_MAX; i++) {
			FILENAME_REPLACE	*pRep = &g_userFileNameReplace[i];
			CString		strKeyName;
			// �u���㕶����
			strKeyName.Format(L"%s%d", sKeyRepCharBefore, i);
			pRep->strBefore = MyGetProfileString(strSectionName, strKeyName, L"");
			strKeyName.Format(L"%s%d", sKeyRepCharAfter, i);
			pRep->strAfter = MyGetProfileString(strSectionName, strKeyName, L"");
		}
	}

	// ���ސݒ���
	g_classInfo.nType = MyGetProfileInt(sSectionClass, sKeyClassType, 0);
	for (i = 0; i < CLASS_MAX; i++) {
		CString		strKeyName;
		// �J�����ԍ�
		strKeyName.Format(L"%s%d", sKeyClassColumn, i);
		g_classInfo.nColumn[i] = MyGetProfileInt(sSectionClass, strKeyName, -1);
	}

	// �\�[�g���
	for (i = 0; i < SORT_KEY_MAX; i++) {
		CString		strKeyName;
		SORT_STATE	*state = &g_sortState[i];
		// �L�[(�J����)
		strKeyName.Format(L"%s%d", sKeySortColumn, i);
		state->nKeyColumn = MyGetProfileInt(sSectionSort, strKeyName, -1);
		// �^�C�v
		strKeyName.Format(L"%s%d", sKeySortType, i);
		state->nType = MyGetProfileInt(sSectionSort, strKeyName, 0);
	}

	// �E�B���h�E�̃t�H���g��ǂݍ���
	CString	strFont;
	strFont = MyGetProfileString(sSectionFont, sKeyFontFace, L"");
	wcscpy(g_fontReport.lfFaceName, (const wchar_t *)strFont);
	g_fontReport.lfHeight = MyGetProfileInt(sSectionFont, sKeyFontHeight, 0);
	g_fontReport.lfWidth = MyGetProfileInt(sSectionFont, sKeyFontWidth, 0);
	g_fontReport.lfEscapement = MyGetProfileInt(sSectionFont, sKeyFontEscapement, 0);
	g_fontReport.lfOrientation = MyGetProfileInt(sSectionFont, sKeyFontOrientation, 0);
	g_fontReport.lfWeight = MyGetProfileInt(sSectionFont, sKeyFontWeight, 0);
	g_fontReport.lfItalic = (unsigned char)MyGetProfileInt(sSectionFont, sKeyFontItalic, 0);
	g_fontReport.lfUnderline = (unsigned char)MyGetProfileInt(sSectionFont, sKeyFontUnderline, 0);
	g_fontReport.lfStrikeOut = (unsigned char)MyGetProfileInt(sSectionFont, sKeyFontStrikeOut, 0);
	g_fontReport.lfCharSet = (unsigned char)MyGetProfileInt(sSectionFont, sKeyFontCharSet, 0);
	g_fontReport.lfOutPrecision = (unsigned char)MyGetProfileInt(sSectionFont, sKeyFontOutPrecision, 0);
	g_fontReport.lfClipPrecision = (unsigned char)MyGetProfileInt(sSectionFont, sKeyFontClipPrecision, 0);
	g_fontReport.lfQuality = (unsigned char)MyGetProfileInt(sSectionFont, sKeyFontQuality, 0);
	g_fontReport.lfPitchAndFamily = (unsigned char)MyGetProfileInt(sSectionFont, sKeyFontPitchAndFamily, 0);

	//g_nOptPlayerType		= MyGetProfileInt(sSectionOption, sKeyPlayerType, PLAYER_WINAMP);
	//g_sOptWinAmpPath		= MyGetProfileString(sSectionOption, sKeyWinAmpPath, L"");
	{ /* ���𑝂₵���̂Ŗ{�ƕ��p���ɉe����^���Ȃ��悤�� WildCherry 070 */
		CString		strSectionName;
		strSectionName = L"haseta\\";
		strSectionName += sSectionOption;
		g_nOptPlayerType = MyGetProfileInt(strSectionName, sKeyPlayerType, PLAYER_WINAMP);
		g_sOptWinAmpPath = MyGetProfileString(strSectionName, sKeyWinAmpPath, L"");
	}
	if (g_sOptWinAmpPath.IsEmpty()) {
		// WinAmp �̃p�X���擾
		GetWinampPath();
	}

	g_bMainFrameZoomed = MyGetProfileInt(sSectionWindow, sKeyWinZoomed, FALSE);
	g_bMainFrameIconic = MyGetProfileInt(sSectionWindow, sKeyWinIconic, FALSE);
	ReadWindowStatus(sKeyMainWindow, &g_rectMainWindow);

	// ���[�U�w��W������
	if (g_genreListUSER == NULL) {
		g_genreListUSER = new USER_GENRE_LIST[USER_GENRE_LIST_MAX];
	}

	// ������̓��� /* StartInaction 054 */
	{
		CString		strSectionName;
		strSectionName = L"haseta";
		g_nUnifyAlpha = MyGetProfileInt(strSectionName, sKeyUnifyAlpha, 0);
		g_nUnifyHiraKata = MyGetProfileInt(strSectionName, sKeyUnifyHiraKata, 0);
		g_nUnifyKata = MyGetProfileInt(strSectionName, sKeyUnifyKata, 0);
		g_nUnifyKigou = MyGetProfileInt(strSectionName, sKeyUnifyKigou, 0);
		g_nUnifySuji = MyGetProfileInt(strSectionName, sKeyUnifySuji, 0);
		g_nUnifyUpLow = MyGetProfileInt(strSectionName, sKeyUnifyUpLow, 0);
		g_nUnifyFixedUpLow = MyGetProfileInt(strSectionName, sKeyUnifyFixedUpLow, 0); /* STEP 040 */
	}

	// �t�@�C����������̓��� /* LastTrain 058 */
	{
		CString		strSectionName;
		strSectionName = L"haseta";
		g_nFileUnifyAlpha = MyGetProfileInt(strSectionName, sKeyFileUnifyAlpha, 0);
		g_nFileUnifyHiraKata = MyGetProfileInt(strSectionName, sKeyFileUnifyHiraKata, 0);
		g_nFileUnifyKata = MyGetProfileInt(strSectionName, sKeyFileUnifyKata, 0);
		g_nFileUnifyKigou = MyGetProfileInt(strSectionName, sKeyFileUnifyKigou, 0);
		g_nFileUnifySuji = MyGetProfileInt(strSectionName, sKeyFileUnifySuji, 0);
		g_nFileUnifyUpLow = MyGetProfileInt(strSectionName, sKeyFileUnifyUpLow, 0);
	}

	// �g���q�̓��� /* STEP 006 */
	{
		CString		strSectionName;
		strSectionName = L"haseta";
		g_nFileExtChange = MyGetProfileInt(strSectionName, sKeyFileExtChange, 0);
	}

	// �v���C���X�g���͐ݒ�_�C�A���O��\������ /* RockDance 126 */
	{
		CString		strSectionName;
		strSectionName = L"haseta";
		g_bShowLoadPlaylistDlg = MyGetProfileInt(strSectionName, sKeyShowLoadPlaylistDlg, 1) ? true : false;
	}

	// ���C�ɓ���̃t�H���_ /* RockDance 129 */
	{
		CString		sSectionOption;
		CString		strSectionName;
		sSectionOption = L"haseta";
		for (i = 0; i < 10; i++) {
			strSectionName.Format(L"%s%d", sSectionFavorites, i);
			g_strFavorite[i] = MyGetProfileString(sSectionOption, strSectionName, L"");
		}
	}

	{ /* STEP 026 */
		CString		strSectionName;
		strSectionName = L"haseta";
		g_bFirstUpperIgnoreWord = MyGetProfileInt(strSectionName, sKeyFirstUpperIgnoreWord, 0) ? true : false;
		g_strFirstUpperIgnoreWords = MyGetProfileString(sSectionOption, sKeyFirstUpperIgnoreWords, L"a,an,and,at,by,for,in,into,of,on,or,the,to,with");
		g_strFirstUpperSentenceSeparator = MyGetProfileString(sSectionOption, sKeyFirstUpperSentenceSeparator, L".");
		g_bUserConvAddMenu = MyGetProfileInt(strSectionName, sKeyUserConvAddMenu, 0) ? true : false;
		g_bZenHanKigouKana = MyGetProfileInt(strSectionName, sKeyZenHanKigouKana, 0) ? true : false;
	}

	//Profile_Free();
}

void CSuperTagEditorApp::WriteRegistry(void)
{
	CString strINI = m_pszProfileName;
	InitProfile();


	int		i;

	// �e��ݒ����������

	MyWriteProfileString(sSectionOption, sKeyVersion, CString(PROG_VERSION) + CString(L"M"));
	MyWriteProfileString(sSectionOption, sKeyCurrentDir, g_strCurrentDirectory);
	MyWriteProfileString(sSectionOption, sKeyCurrentPlayList, g_strCurrentPlayList);
	//dlgLoadProgress.SetPos(5);

	// ��� - ���[�U�[�C���^�[�t�F�[�X
	MyWriteProfileInt(sSectionOption, sKeyESCEditCancel, g_bOptESCEditCancel ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyEnableEditCursorExit, g_bOptEnableEditCursorExit ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyEditOkDown, g_bOptEditOkDown ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyEnterBeginEdit, g_bOptEnterBeginEdit ? 1 : 0);
	//dlgLoadProgress.SetPos(10);

	// ��� - ����ݒ�
	MyWriteProfileInt(sSectionOption, sKeyKeepTimeStamp, g_bOptKeepTimeStamp ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeySyncCreateTime, g_bOptSyncCreateTime ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyChangeFileExt, g_bOptChangeFileExt ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyAutoOpenFolder, g_bOptAutoOpenFolder ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyLoadFileAdjustColumn, g_bOptLoadFileAdjustColumn ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyLoadFileChecked, g_bOptLoadFileChecked ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyHideMP3ListFile, g_bOptHideMP3ListFile ? 1 : 0);
	//dlgLoadProgress.SetPos(15);

	// ��� - �̎��t�@�C��
	MyWriteProfileInt(sSectionOption, sKeyChangeTextFile, g_bOptChangeTextFile ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeySetLyricsDir, g_bOptSetLyricsDir ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeySearchLyricsSubDir, g_bOptSearchLyricsSubDir ? 1 : 0);
	MyWriteProfileString(sSectionOption, sKeyLyricsPath, g_strOptLyricsPath);
	//dlgLoadProgress.SetPos(20);

	//
	MyWriteProfileInt(sSectionOption, sKeyEditFiledSIF, g_bOptEditFieldSIF ? 1 : 0);
	MyWriteProfileInt(sSectionOption, sKeyCheckFileName, g_nOptCheckFileName);
	MyWriteProfileInt(sSectionOption, sKeyEnableSearchSubDir, g_bEnableSearchSubDir ? 1 : 0);
	//dlgLoadProgress.SetPos(25);

	// �t�H���_�̓���
	MyWriteProfileInt(sSectionFolderSync, sKeyEnableFolderSync, g_bEnableFolderSync ? 1 : 0);
	MyWriteProfileString(sSectionFolderSync, sKeySyncRootFolder, g_strRootFolder);
	MyWriteProfileInt(sSectionFolderSync, sKeySyncSelectAlways, g_bSyncSelectAlways ? 1 : 0);
	MyWriteProfileInt(sSectionFolderSync, sKeySyncDeleteFolder, g_bSyncDeleteFolder ? 1 : 0);
	MyWriteProfileInt(sSectionFolderSync, sKeySyncLyricsFileMove, g_bSyncLyricsFileMove ? 1 : 0);
	//dlgLoadProgress.SetPos(30);

	// �m�F���b�Z�[�W�\��
	MyWriteProfileInt(sSectionConfMessage, sKeyConfDeleteFile, g_bConfDeleteFile ? 1 : 0);
	MyWriteProfileInt(sSectionConfMessage, sKeyConfDeleteList, g_bConfDeleteList ? 1 : 0);
	MyWriteProfileInt(sSectionConfMessage, sKeyConfEditModify, g_bConfEditModify ? 1 : 0);
	MyWriteProfileInt(sSectionConfMessage, sKeyConfFolderSync, g_bConfFolderSync ? 1 : 0);
	//dlgLoadProgress.SetPos(35);

	// �v���C���X�g
	MyWriteProfileInt(sSectionLoadPlayList, sKeyClearList, g_bPlayListClearList ? 1 : 0);
	MyWriteProfileInt(sSectionLoadPlayList, sKeyClearCheck, g_bPlayListClearCheck ? 1 : 0);
	MyWriteProfileInt(sSectionLoadPlayList, sKeyAddList, g_bPlayListAddList ? 1 : 0);
	MyWriteProfileInt(sSectionLoadPlayList, sKeyFileCheck, g_bPlayListFileCheck ? 1 : 0);
	//dlgLoadProgress.SetPos(40);

	// �����`�F�b�N�̏��
	for (i = 0; i < CHECK_STATE_MAX; i++) {
		CHECK_WORD_STATE	*pState = &g_chkWord[i];
		wchar_t	*sSectionName = sSectionCheckWord[i];
		MyWriteProfileString(sSectionName, sKeySearchWord, pState->strSearchWord);
		MyWriteProfileString(sSectionName, sKeyReplaceWord, pState->strReplaceWord);
		MyWriteProfileInt(sSectionName, sKeyTargetColumn, pState->nTargetColumn);
		MyWriteProfileInt(sSectionName, sKeyCheckDiffUL, pState->bCheckDiffUL ? 1 : 0);
		MyWriteProfileInt(sSectionName, sKeyRegExp, pState->bRegExp ? 1 : 0);
		MyWriteProfileInt(sSectionName, sKeyRangeSelected, pState->bRangeSelected ? 1 : 0);
		MyWriteProfileInt(sSectionName, sKeyMatchComplete, pState->bMatchComplete ? 1 : 0);
		MyWriteProfileInt(sSectionName, sKeyMatchSelected, pState->bMatchSelected ? 1 : 0);
	}
	//dlgLoadProgress.SetPos(45);

	// �t�@�C�����u������
	for (i = 0; i < FILENAME_REPLACE_MAX; i++) {
		FILENAME_REPLACE	*pRep = &g_fileNameReplace[i];
		CString		strKeyName;
		// �u���㕶����
		strKeyName.Format(L"%s%d", sKeyRepCharAfter, i);
		MyWriteProfileString(sSectionRepFileName, strKeyName, pRep->strAfter);
	}
	//dlgLoadProgress.SetPos(50);
	// ���[�U�t�@�C�����u������ /* FreeFall 050 */
	{
		CString		strSectionName;
		strSectionName = L"haseta\\User";
		strSectionName += sSectionRepFileName;
		for (i = 0; i < USER_FILENAME_REPLACE_MAX; i++) {
			FILENAME_REPLACE	*pRep = &g_userFileNameReplace[i];
			CString		strKeyName;
			// �u���㕶����
			strKeyName.Format(L"%s%d", sKeyRepCharBefore, i);
			MyWriteProfileString(strSectionName, strKeyName, pRep->strBefore);
			strKeyName.Format(L"%s%d", sKeyRepCharAfter, i);
			MyWriteProfileString(strSectionName, strKeyName, pRep->strAfter);
		}
	}
	//dlgLoadProgress.SetPos(55);

	// ���[�U�[�ϊ�����
	//MyWriteProfileInt(sSectionUserConvFormat, sKeyConvFormatType, g_nUserConvFormatType);
	{ /* ���𑝂₵���̂Ŗ{�ƕ��p���ɉe����^���Ȃ��悤�� LastTrain 057 */
		CString		strSectionName;
		strSectionName = L"haseta\\";
		strSectionName += sSectionUserConvFormat;
		MyWriteProfileInt(strSectionName, sKeyConvFormatType, g_nUserConvFormatType);
	}
	//dlgLoadProgress.SetPos(60);
	for (i = 0; i < USER_CONV_FORMAT_MAX; i++) {
		CString		strKeyName;
		// ����
		strKeyName.Format(L"%s%d", sKeyUserFormName, i);
		MyWriteProfileString(sSectionUserConvFormat, strKeyName, g_userConvFormat[i].strName);
		// �^�O��� => �t�@�C����
		strKeyName.Format(L"%s%d", sKeyUserFormTag2File, i);
		MyWriteProfileString(sSectionUserConvFormat, strKeyName, g_userConvFormat[i].strTag2File);
		// �t�@�C���� => �^�O���
		strKeyName.Format(L"%s%d", sKeyUserFormFile2Tag, i);
		MyWriteProfileString(sSectionUserConvFormat, strKeyName, g_userConvFormat[i].strFile2Tag);
	}
	//dlgLoadProgress.SetPos(65);

	// �g���Ń��[�U�[�ϊ�����
	for (i = 0; i < USER_CONV_FORMAT_EX_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"%s%d", sSectionConvFormatEx, i);
		// ����
		MyWriteProfileString(strSectionName, sKeyUserFormName, g_userConvFormatEx[i].strName);
		// ����
		MyWriteProfileString(strSectionName, sKeyUserFormat, g_userConvFormatEx[i].strFormat);
		// �Œ蕶����
		MyWriteProfileString(strSectionName, sKeyUserFixString, g_userConvFormatEx[i].strFixString);
		// �A�ԁF�����l
		MyWriteProfileInt(strSectionName, sKeyUserInitNumber, g_userConvFormatEx[i].nInitNumber);
		// �A�ԁF���Z�l
		MyWriteProfileInt(strSectionName, sKeyUserAddNumber, g_userConvFormatEx[i].nAddNumber);
		// �A�ԁF����
		MyWriteProfileInt(strSectionName, sKeyUserColumnCount, g_userConvFormatEx[i].nColumnCount);
		// �������ݕs�̃Z���ŘA�ԃN���A
		MyWriteProfileInt(strSectionName, sKeyUserSpaceInit, g_userConvFormatEx[i].bSpaceInitNumber ? 1 : 0);
	}
	//dlgLoadProgress.SetPos(70);

	// �ړ���t�H���_����
	for (i = 0; i < USER_MOVE_FODLER_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"haseta\\%s%d", sSectionMoveFolder, i);
		// ����
		MyWriteProfileString(strSectionName, sKeyUserFormName, g_userMoveFolder[i].strName);
		// ����
		MyWriteProfileString(strSectionName, sKeyMoveFolderFormat, g_userMoveFolder[i].strFormat);
		// �Œ蕶����
		MyWriteProfileString(strSectionName, sKeyMoveFolderFixString, g_userMoveFolder[i].strFixString);
		// �R�s�[
		MyWriteProfileInt(strSectionName, sKeyMoveFolderCopy, g_userMoveFolder[i].bCopy ? 1 : 0);
		// ����
		MyWriteProfileString(strSectionName, sKeyMoveFolderInitFolder, g_userMoveFolder[i].strInitFolder); /* STEP 022 */
	}

	// �^�O���ϊ� /* STEP 034 */
	for (i = 0; i < USER_CONV_FORMAT_TAG2TAG_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"haseta\\%s%d", sSectionConvFormatTag2Tag, i);
		// ����
		MyWriteProfileString(strSectionName, sKeyUserTag2TagFormName, g_userConvFormatTag2Tag[i].strName);
		// ����
		MyWriteProfileString(strSectionName, sKeyUserTagTagFormat, g_userConvFormatTag2Tag[i].strFormat);
	}

	//dlgLoadProgress.SetPos(75);
	// �����R�s�[ /* FunnyCorn 175 */
	for (i = 0; i < USER_COPY_FORMAT_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"haseta\\%s%d", sSectionCopyFormat, i);
		// ����
		MyWriteProfileString(strSectionName, sKeyUserFormName, g_userCopyFormat[i].strName);
		// ����
		MyWriteProfileString(strSectionName, sKeyCopyFormatFormat, g_userCopyFormat[i].strFormat);
		// �Œ蕶����
		MyWriteProfileString(strSectionName, sKeyCopyFormatFixString, g_userCopyFormat[i].strFixString);
	}
	//dlgLoadProgress.SetPos(80);
	{
		CString		sSectionOption;
		sSectionOption = L"haseta";
		//		MyWriteProfileInt(sSectionOption, sKeyID3v2GenreAddNumber, g_bOptID3v2GenreAddNumber ? 1 : 0);
		MyWriteProfileInt(sSectionOption, sKeyFileNameMaxCheck, g_bConfFileNameMaxCheck ? 1 : 0);
		MyWriteProfileInt(sSectionOption, sKeyFileNameMaxCellColor, g_bFileNameMaxCellColor ? 1 : 0);
		MyWriteProfileInt(sSectionOption, sKeyFileNameMaxChar, g_nConfFileNameMaxChar);
		MyWriteProfileInt(sSectionOption, sKeyDropSearchSubFolder, g_bOptDropSearchSubFolder ? 1 : 0); /* TyphoonSwell 026 */
		MyWriteProfileInt(sSectionOption, sKeyShowZenSpace, g_bOptShowZenSpace ? 1 : 0); /* BeachMonster 107 */
		//MyWriteProfileInt(sSectionOption, sKeyShowZenSpace, g_bOptShowZenSpace ? 1 : 0); /* BeachMonster 107 */
		MyWriteProfileInt(sSectionOption, sKeySortIgnoreCase, g_bOptSortIgnoreCase ? 1 : 0); /* BeachMonster4 114 */
		MyWriteProfileInt(sSectionOption, sKeySortIgnoreZenHan, g_bOptSortIgnoreZenHan ? 1 : 0); /* BeachMonster4 114 */
		MyWriteProfileInt(sSectionOption, sKeySortIgnoreKataHira, g_bOptSortIgnoreKataHira ? 1 : 0); /* FunnyCorn 179 */
		MyWriteProfileInt(sSectionOption, sKeyShowTotalParent, g_bOptShowTotalParent ? 1 : 0); /* RockDance 128 */
		MyWriteProfileInt(sSectionOption, sKeyShowTips, g_bOptShowTips ? 1 : 0); /* Rumble 188 */
	}
	//dlgLoadProgress.SetPos(85);
	// ��^���\��t�� /* SeaKnows 030 */
	for (int k = 0; k < 3; k++) {
		CString		sSectionOption;
		CString		strSectionName;
		sSectionOption = L"haseta";
		strSectionName.Format(L"%s%d", sSectionTeikeiGroupName, k);
		MyWriteProfileString(sSectionOption, strSectionName, g_strTeikeiGroupName[k]);
		for (i = 0; i < 10; i++) {
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikei, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikei, k, i);
			}
			MyWriteProfileString(sSectionOption, strSectionName, g_teikeiInfo[i + k * 10].strTeikei/* STEP 035 */);
			/* STEP 035 */
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiPaste, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiPaste, k, i);
			}
			MyWriteProfileInt(sSectionOption, strSectionName, g_teikeiInfo[i + k * 10].nTeikeiPaste);
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiAddSpace, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiAddSpace, k, i);
			}
			MyWriteProfileInt(sSectionOption, strSectionName, g_teikeiInfo[i + k * 10].bAddSpace ? 1 : 0);
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiAddChar, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiAddChar, k, i);
			}
			MyWriteProfileInt(sSectionOption, strSectionName, g_teikeiInfo[i + k * 10].bAddChar ? 1 : 0);
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiFront, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiFront, k, i);
			}
			MyWriteProfileString(sSectionOption, strSectionName, g_teikeiInfo[i + k * 10].strFront);
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiBack, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiBack, k, i);
			}
			MyWriteProfileString(sSectionOption, strSectionName, g_teikeiInfo[i + k * 10].strBack);
			if (k == 0) {
				strSectionName.Format(L"%s%d", sSectionTeikeiShowDialog, i);
			} else {
				strSectionName.Format(L"%s%d-%d", sSectionTeikeiShowDialog, k, i);
			}
			MyWriteProfileInt(sSectionOption, strSectionName, g_teikeiInfo[i + k * 10].bShowDialog ? 1 : 0);
		}
	}

	// ���̑� /* SeaKnows 031,033 */
	{
		CString		strSectionName;
		strSectionName = L"haseta";
		MyWriteProfileInt(strSectionName, sSectionValidFolderSelect, g_bValidFolderSelect ? 1 : 0);
		MyWriteProfileInt(strSectionName, sSectionValidDupExec, g_bValidDupExec ? 1 : 0); /* FreeFall 045 */
		MyWriteProfileInt(strSectionName, sSectionRecentFolderNum, g_nRecentFolder); /* MyWriteProfileInt 053 */
		MyWriteProfileInt(strSectionName, sSectionSaveRepDlgPos, g_bSaveRepDlgPos ? 1 : 0); /* WildCherry4 086 */
		MyWriteProfileInt(strSectionName, sSectionSaveRepDlgPosX, g_nSaveRepDlgPosX); /* WildCherry4 086 */
		MyWriteProfileInt(strSectionName, sSectionSaveRepDlgPosY, g_nSaveRepDlgPosY); /* WildCherry4 086 */
		MyWriteProfileInt(strSectionName, sSectionAddNumberWidth, g_nAddNumberWidth); /* Baja 159 */
		MyWriteProfileInt(strSectionName, sSectionAddNumberPos, g_nAddNumberPos); /* Baja 159 */
		MyWriteProfileString(strSectionName, sSectionAddNumberSep, g_strAddNumberSep); /* Baja 159 */
		MyWriteProfileString(strSectionName, sSectionAddNumberBef, g_strAddNumberBef); /* Conspiracy 194 */
		MyWriteProfileString(strSectionName, sSectionAddNumberAft, g_strAddNumberAft); /* Conspiracy 194 */
		MyWriteProfileInt(strSectionName, sSectionAudioListShow, g_bAudioListShow ? 1 : 0); /* Conspiracy 199 */
	}

	// ���X�g�o�͏���
	for (i = 0; i < WRITE_FORMAT_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"%s%d", sSectionWriteFormat, i);
		// ����
		MyWriteProfileString(strSectionName, sKeyWriteFormName, g_writeFormat[i].strName);
		// �����t�@�C����
		MyWriteProfileString(strSectionName, sKeyWriteFileName, g_writeFormat[i].strFileName);
		// �g���q
		MyWriteProfileString(strSectionName, sKeyWriteExtName, g_writeFormat[i].strExtName);
		// �I���t�@�C���̂ݏo��
		MyWriteProfileInt(strSectionName, sKeyWriteSelected, g_writeFormat[i].bWriteSelected ? 1 : 0);
		// �J�����g�t�@�C����
		MyWriteProfileString(strSectionName, sKeyWriteCurrentFile, g_writeFormat[i].strCurrentFile);
		// HTML �t�@�C���o�͗p(��̏ꍇ�ɑS�p�X�y�[�X���o��)
		MyWriteProfileInt(strSectionName, sKeyWriteIsHtml, g_writeFormat[i].bIsHtml ? 1 : 0);
		{ /* BeachMonster5 120 */
			MyWriteProfileInt(L"haseta\\" + strSectionName, sKeyWriteHtml, g_writeFormat[i].bWriteHtml ? 1 : 0);
		}
	}
	//dlgLoadProgress.SetPos(90);

	// ���ސݒ���
	MyWriteProfileInt(sSectionClass, sKeyClassType, g_classInfo.nType);
	for (i = 0; i < CLASS_MAX; i++) {
		CString		strKeyName;
		// �J�����ԍ�
		strKeyName.Format(L"%s%d", sKeyClassColumn, i);
		MyWriteProfileInt(sSectionClass, strKeyName, g_classInfo.nColumn[i]);
	}

	// �\�[�g���
	for (i = 0; i < SORT_KEY_MAX; i++) {
		CString		strKeyName;
		SORT_STATE	*state = &g_sortState[i];
		// �L�[(�J����)
		strKeyName.Format(L"%s%d", sKeySortColumn, i);
		MyWriteProfileInt(sSectionSort, strKeyName, state->nKeyColumn);
		// �^�C�v
		strKeyName.Format(L"%s%d", sKeySortType, i);
		MyWriteProfileInt(sSectionSort, strKeyName, state->nType);
	}

	// �E�B���h�E�̃t�H���g����������
	MyWriteProfileString(sSectionFont, sKeyFontFace, g_fontReport.lfFaceName);
	MyWriteProfileInt(sSectionFont, sKeyFontHeight, g_fontReport.lfHeight);
	MyWriteProfileInt(sSectionFont, sKeyFontWidth, g_fontReport.lfWidth);
	MyWriteProfileInt(sSectionFont, sKeyFontEscapement, g_fontReport.lfEscapement);
	MyWriteProfileInt(sSectionFont, sKeyFontOrientation, g_fontReport.lfOrientation);
	MyWriteProfileInt(sSectionFont, sKeyFontWeight, g_fontReport.lfWeight);
	MyWriteProfileInt(sSectionFont, sKeyFontItalic, g_fontReport.lfItalic);
	MyWriteProfileInt(sSectionFont, sKeyFontUnderline, g_fontReport.lfUnderline);
	MyWriteProfileInt(sSectionFont, sKeyFontStrikeOut, g_fontReport.lfStrikeOut);
	MyWriteProfileInt(sSectionFont, sKeyFontCharSet, g_fontReport.lfCharSet);
	MyWriteProfileInt(sSectionFont, sKeyFontOutPrecision, g_fontReport.lfOutPrecision);
	MyWriteProfileInt(sSectionFont, sKeyFontClipPrecision, g_fontReport.lfClipPrecision);
	MyWriteProfileInt(sSectionFont, sKeyFontQuality, g_fontReport.lfQuality);
	MyWriteProfileInt(sSectionFont, sKeyFontPitchAndFamily, g_fontReport.lfPitchAndFamily);

	//MyWriteProfileInt(sSectionOption, sKeyPlayerType, (int)g_nOptPlayerType);
	//MyWriteProfileString(sSectionOption, sKeyWinAmpPath, g_sOptWinAmpPath);
	{ /* ���𑝂₵���̂Ŗ{�ƕ��p���ɉe����^���Ȃ��悤�� WildCherry 070 */
		CString		strSectionName;
		strSectionName = L"haseta\\";
		strSectionName += sSectionOption;
		MyWriteProfileInt(strSectionName, sKeyPlayerType, (int)g_nOptPlayerType);
		MyWriteProfileString(strSectionName, sKeyWinAmpPath, g_sOptWinAmpPath);
	}
	//dlgLoadProgress.SetPos(95);

	// �E�B���h�E�̏�Ԃ�ۑ�
	MyWriteProfileInt(sSectionWindow, sKeyWinZoomed, (int)g_bMainFrameZoomed);
	MyWriteProfileInt(sSectionWindow, sKeyWinIconic, (int)g_bMainFrameIconic);
	WriteWindowStatus(sKeyMainWindow, &g_rectMainWindow);

	// ������̓��� /* StartInaction 054 */
	{
		CString		strSectionName;
		strSectionName = L"haseta";
		MyWriteProfileInt(strSectionName, sKeyUnifyAlpha, g_nUnifyAlpha);
		MyWriteProfileInt(strSectionName, sKeyUnifyHiraKata, g_nUnifyHiraKata);
		MyWriteProfileInt(strSectionName, sKeyUnifyKata, g_nUnifyKata);
		MyWriteProfileInt(strSectionName, sKeyUnifyKigou, g_nUnifyKigou);
		MyWriteProfileInt(strSectionName, sKeyUnifySuji, g_nUnifySuji);
		MyWriteProfileInt(strSectionName, sKeyUnifyUpLow, g_nUnifyUpLow);
		MyWriteProfileInt(strSectionName, sKeyUnifyFixedUpLow, g_nUnifyFixedUpLow); /* STEP 040 */
	}

	// �t�@�C����������̓��� /* LastTrain 058 */
	{
		CString		strSectionName;
		strSectionName = L"haseta";
		MyWriteProfileInt(strSectionName, sKeyFileUnifyAlpha, g_nFileUnifyAlpha);
		MyWriteProfileInt(strSectionName, sKeyFileUnifyHiraKata, g_nFileUnifyHiraKata);
		MyWriteProfileInt(strSectionName, sKeyFileUnifyKata, g_nFileUnifyKata);
		MyWriteProfileInt(strSectionName, sKeyFileUnifyKigou, g_nFileUnifyKigou);
		MyWriteProfileInt(strSectionName, sKeyFileUnifySuji, g_nFileUnifySuji);
		MyWriteProfileInt(strSectionName, sKeyFileUnifyUpLow, g_nFileUnifyUpLow);
	}

	// �g���q�̓��� /* STEP 006 */
	{
		CString		strSectionName;
		strSectionName = L"haseta";
		MyWriteProfileInt(strSectionName, sKeyFileExtChange, g_nFileExtChange);
	}
	// �v���C���X�g���͐ݒ�_�C�A���O��\������ /* RockDance 126 */
	{
		CString		strSectionName;
		strSectionName = L"haseta";
		MyWriteProfileInt(strSectionName, sKeyShowLoadPlaylistDlg, g_bShowLoadPlaylistDlg ? 1 : 0);
	}
	//dlgLoadProgress.SetPos(100);
	// ���C�ɓ���̃t�H���_ /* RockDance 129 */
	{
		CString		sSectionOption;
		CString		strSectionName;
		sSectionOption = L"haseta";
		for (i = 0; i < 10; i++) {
			strSectionName.Format(L"%s%d", sSectionFavorites, i);
			MyWriteProfileString(sSectionOption, strSectionName, g_strFavorite[i]);
		}
	}

	{ /* STEP 026 */
		CString		strSectionName;
		strSectionName = L"haseta";
		MyWriteProfileInt(strSectionName, sKeyFirstUpperIgnoreWord, g_bFirstUpperIgnoreWord ? 1 : 0);
		MyWriteProfileString(sSectionOption, sKeyFirstUpperIgnoreWords, g_strFirstUpperIgnoreWords);
		MyWriteProfileString(sSectionOption, sKeyFirstUpperSentenceSeparator, g_strFirstUpperSentenceSeparator);
		MyWriteProfileInt(strSectionName, sKeyUserConvAddMenu, g_bUserConvAddMenu ? 1 : 0);
		MyWriteProfileInt(strSectionName, sKeyZenHanKigouKana, g_bZenHanKigouKana ? 1 : 0);
	}

	/*
	if (dlgLoadProgress.GetSafeHwnd() != NULL) {
	dlgLoadProgress.DestroyWindow();
	dlgLoadProgress.SetCanceled(FALSE);
	}
	*/
	SaveProfile();
	FreeProfile();
	//	m_pRecentFileList->WriteList();
}

// �L�[���蓖�Ă̓ǂݍ���
void CSuperTagEditorApp::ReadKeyConfig(bool bUpdate)
{
	CString strINI = m_pszProfileName;
	InitProfile();
	int		i;
	int		nTableMax = 0;
	for (i = 0; g_listKeyConfig[i].sName != NULL; i++) {
		KEY_CONFIG	*pKey = &g_listKeyConfig[i];
		if (pKey->wCmdID != 0x0000) {
			pKey->dwKeyCode = (DWORD)MyGetProfileInt(sSectionKeyConfig, pKey->sRegName, pKey->dwKeyCode);
			//pKey->dwKeyCode = (DWORD)Profile_GetInt(sSectionKeyConfig, pKey->sRegName, pKey->dwKeyCode, strINI);
			if (pKey->dwKeyCode != 0) nTableMax++;
		}
	}

	extern CPlugin plugins;
	for (i = 0; i < plugins.arPluginKey.GetSize(); i++) {
		KEY_CONFIG* pKey = (KEY_CONFIG*)plugins.arPluginKey.GetAt(i);
		if (pKey->wCmdID != 0x0000) {
			pKey->dwKeyCode = (DWORD)MyGetProfileInt(sSectionKeyConfig, pKey->sRegName, pKey->dwKeyCode);
			//pKey->dwKeyCode = (DWORD)Profile_GetInt(sSectionKeyConfig, pKey->sRegName, pKey->dwKeyCode, strINI);
			if (pKey->dwKeyCode != 0) nTableMax++;
		}
	}
	FreeProfile();

	// �A�N�Z�����[�^�L�[�e�[�u���̍X�V
	if (bUpdate) UpdateAccelerator(nTableMax);
}

// �L�[���蓖�Ă̕ۑ�
void CSuperTagEditorApp::WriteKeyConfig(bool bUpdate)
{
	CString strINI = m_pszProfileName;
	InitProfile();
	int		i;
	int		nTableMax = 0;
	//CString sValue;
	for (i = 0; g_listKeyConfig[i].sName != NULL; i++) {
		KEY_CONFIG	*pKey = &g_listKeyConfig[i];
		if (pKey->wCmdID != 0x0000) {
			//sValue.Format(L"%d", pKey->dwKeyCode);
			//WritePrivateProfileString(sSectionKeyConfig, pKey->sRegName, sValue, strINI);
			//Profile_WriteInt(sSectionKeyConfig, pKey->sRegName, pKey->dwKeyCode, strINI);
			MyWriteProfileInt(sSectionKeyConfig, pKey->sRegName, pKey->dwKeyCode);
			if (pKey->dwKeyCode != 0) nTableMax++;
		}
	}

	extern CPlugin plugins;
	for (i = 0; i < plugins.arPluginKey.GetSize(); i++) {
		KEY_CONFIG* pKey = (KEY_CONFIG*)plugins.arPluginKey.GetAt(i);
		if (pKey->wCmdID != 0x0000) {
			//sValue.Format(L"%ld", pKey->dwKeyCode);
			//WritePrivateProfileString(sSectionKeyConfig, pKey->sRegName, sValue, strINI);
			//Profile_WriteInt(sSectionKeyConfig, pKey->sRegName, pKey->dwKeyCode, strINI);
			MyWriteProfileInt(sSectionKeyConfig, pKey->sRegName, pKey->dwKeyCode);
			if (pKey->dwKeyCode != 0) nTableMax++;
		}
	}

	SaveProfile();
	FreeProfile();

	// �A�N�Z�����[�^�L�[�e�[�u���̍X�V
	if (bUpdate) UpdateAccelerator(nTableMax);
}

// �A�N�Z�����[�^�e�[�u���̉��
void CSuperTagEditorApp::DestroyAccelerator(void)
{
	if (m_hAccel != 0) {
		DestroyAcceleratorTable(m_hAccel);
		m_hAccel = 0;
	}
	if (m_accelTable != NULL) {
		delete[]	m_accelTable;		// �A�N�Z�����[�^�e�[�u��
		m_accelTable = NULL;
		m_nAccelTable = 0;
	}
}

// �A�N�Z�����[�^�e�[�u���̍X�V
CMenu convSubMenuT2F;
CMenu convSubMenuF2T;
CString convSubMenuT2FTitle;
CString convSubMenuF2TTitle;
void CSuperTagEditorApp::UpdateAccelerator(int nTableMax)
{
	if (nTableMax == -1) {
		nTableMax = m_nAccelTable;
	}

	// �A�N�Z�����[�^�e�[�u���̉��
	DestroyAccelerator();

	CMainFrame/* STEP 030 */	*pMainWnd = (CMainFrame*)/* STEP 030 */AfxGetMainWnd();
	CMenu	*pMenu = pMainWnd ? pMainWnd->GetMenu() : NULL;

	/* STEP 030 */
	pMenu->DestroyMenu();
	CMenu newMenu;
	newMenu.LoadMenu(IDR_MAINFRAME);
	pMainWnd->SetMenu(NULL);
	pMainWnd->SetMenu(&newMenu);
	pMainWnd->m_hMenuDefault = newMenu.m_hMenu;
	newMenu.Detach();

	/* STEP 030 */
	convSubMenuT2F.DestroyMenu();
	convSubMenuF2T.DestroyMenu();
	pMenu = pMainWnd ? pMainWnd->GetMenu() : NULL;
	if (pMenu != NULL && g_bUserConvAddMenu) {
		CMenu* pUConvMenu = NULL;
		int nCount = pMenu->GetMenuItemCount();
		int j; for (int j = 0; j < nCount; j++) {
			CString strTitle;
			pMenu->GetMenuString(j, strTitle, MF_BYPOSITION);
			if (strTitle == L"�ϊ�(&C)") {
				pMenu = pMenu->GetSubMenu(j);
				break;
			}
		}
		nCount = pMenu->GetMenuItemCount();
		for (j = 0; j < nCount; j++) {
			CString strTitle;
			pMenu->GetMenuString(j, strTitle, MF_BYPOSITION);
			if (strTitle == L"���[�U�[�w��ϊ�(&U)") {
				pUConvMenu = pMenu->GetSubMenu(j);
				break;
			}
		}
		convSubMenuT2F.LoadMenu(IDR_MENU_CONV_FORMAT_USER_T2F);
		pUConvMenu->GetMenuString(ID_CONV_TAG2FILE_USER, convSubMenuT2FTitle, MF_BYCOMMAND);
		pUConvMenu->ModifyMenu(ID_CONV_TAG2FILE_USER, MF_BYCOMMAND | MF_POPUP, (UINT)convSubMenuT2F.GetSubMenu(0)->GetSafeHmenu(), convSubMenuT2FTitle);
		//pUConvMenu->ModifyMenu(ID_CONV_TAG2FILE_USER, MF_BYCOMMAND | MF_STRING, ID_CONV_TAG2FILE_USER, convSubMenuT2FTitle);

		convSubMenuF2T.LoadMenu(IDR_MENU_CONV_FORMAT_USER_F2T);
		pUConvMenu->GetMenuString(ID_CONV_FILE2TAG_USER, convSubMenuF2TTitle, MF_BYCOMMAND);
		pUConvMenu->ModifyMenu(ID_CONV_FILE2TAG_USER, MF_BYCOMMAND | MF_POPUP, (UINT)convSubMenuF2T.GetSubMenu(0)->GetSafeHmenu(), convSubMenuF2TTitle);
		//pUConvMenu->ModifyMenu(ID_CONV_FILE2TAG_USER, MF_BYCOMMAND | MF_STRING, ID_CONV_FILE2TAG_USER, convSubMenuF2TTitle);
	}
	extern void OnLoadMainMenu();
	OnLoadMainMenu();

	pMenu = pMainWnd ? pMainWnd->GetMenu() : NULL;
	// �A�N�Z�����[�^�e�[�u���쐬
	m_accelTable = new ACCEL[nTableMax];
	m_nAccelTable = nTableMax;
	int		i, nCount = 0;
	for (i = 0; g_listKeyConfig[i].sName != NULL; i++) {
		KEY_CONFIG	*pKey = &g_listKeyConfig[i];
		if (pKey->wCmdID != 0x0000) {
			// �A�N�Z�����[�^�̍쐬
			ACCEL	*pAccel = NULL;
			WORD	wModifiers = 0x0000;
			if (pKey->dwKeyCode != 0) {
				wModifiers = HIWORD(pKey->dwKeyCode);
				pAccel = &m_accelTable[nCount];
				pAccel->fVirt = FNOINVERT | FVIRTKEY;
				if (wModifiers & HOTKEYF_ALT) pAccel->fVirt |= FALT;
				if (wModifiers & HOTKEYF_CONTROL) pAccel->fVirt |= FCONTROL;
				if (wModifiers & HOTKEYF_SHIFT) pAccel->fVirt |= FSHIFT;
				pAccel->key = LOWORD(pKey->dwKeyCode);
				pAccel->cmd = pKey->wCmdID;
				nCount++;
			}

			// ���j���[���ڂ̏�������
			if (pMenu != NULL) {
				CString	strName;
				// ���j���[���ږ����擾
				switch (pKey->wCmdID) {
				case ID_CONV_FORMAT_EX_01:
					strName.Format(L"01�F%s", g_userConvFormatEx[0].strName);
					break;
				case ID_CONV_FORMAT_EX_02:
					strName.Format(L"02�F%s", g_userConvFormatEx[1].strName);
					break;
				case ID_CONV_FORMAT_EX_03:
					strName.Format(L"03�F%s", g_userConvFormatEx[2].strName);
					break;
				case ID_CONV_FORMAT_EX_04:
					strName.Format(L"04�F%s", g_userConvFormatEx[3].strName);
					break;
				case ID_CONV_FORMAT_EX_05:
					strName.Format(L"05�F%s", g_userConvFormatEx[4].strName);
					break;
				case ID_CONV_FORMAT_EX_06:
					strName.Format(L"06�F%s", g_userConvFormatEx[5].strName);
					break;
				case ID_CONV_FORMAT_EX_07:
					strName.Format(L"07�F%s", g_userConvFormatEx[6].strName);
					break;
				case ID_CONV_FORMAT_EX_08:
					strName.Format(L"08�F%s", g_userConvFormatEx[7].strName);
					break;
				case ID_CONV_FORMAT_EX_09:
					strName.Format(L"09�F%s", g_userConvFormatEx[8].strName);
					break;
				case ID_CONV_FORMAT_EX_10:
					strName.Format(L"10�F%s", g_userConvFormatEx[9].strName);
					break;
				case ID_WRITE_LIST1:
					strName.Format(L"01�F%s", g_writeFormat[0].strName);
					break;
				case ID_WRITE_LIST2:
					strName.Format(L"02�F%s", g_writeFormat[1].strName);
					break;
				case ID_WRITE_LIST3:
					strName.Format(L"03�F%s", g_writeFormat[2].strName);
					break;
				case ID_WRITE_LIST4:
					strName.Format(L"04�F%s", g_writeFormat[3].strName);
					break;
				case ID_WRITE_LIST5:
					strName.Format(L"05�F%s", g_writeFormat[4].strName);
					break;
				case ID_MOVE_FOLDER_01:
					strName.Format(L"01�F%s", g_userMoveFolder[0].strName);
					break;
				case ID_MOVE_FOLDER_02:
					strName.Format(L"02�F%s", g_userMoveFolder[1].strName);
					break;
				case ID_MOVE_FOLDER_03:
					strName.Format(L"03�F%s", g_userMoveFolder[2].strName);
					break;
				case ID_MOVE_FOLDER_04:
					strName.Format(L"04�F%s", g_userMoveFolder[3].strName);
					break;
				case ID_MOVE_FOLDER_05:
					strName.Format(L"05�F%s", g_userMoveFolder[4].strName);
					break;
				case ID_CONV_FORMAT_USER_01: /* TyphoonSwell 027 */
				case ID_CONV_FORMAT_USER_T2F_01: /* STEP 030 */
				case ID_CONV_FORMAT_USER_F2T_01: /* STEP 030 */
					strName.Format(L"01�F%s", g_userConvFormat[0].strName);
					break;
				case ID_CONV_FORMAT_USER_02: /* TyphoonSwell 027 */
				case ID_CONV_FORMAT_USER_T2F_02: /* STEP 030 */
				case ID_CONV_FORMAT_USER_F2T_02: /* STEP 030 */
					strName.Format(L"02�F%s", g_userConvFormat[1].strName);
					break;
				case ID_CONV_FORMAT_USER_03: /* TyphoonSwell 027 */
				case ID_CONV_FORMAT_USER_T2F_03: /* STEP 030 */
				case ID_CONV_FORMAT_USER_F2T_03: /* STEP 030 */
					strName.Format(L"03�F%s", g_userConvFormat[2].strName);
					break;
				case ID_CONV_FORMAT_USER_04: /* LastTrain 057 */
				case ID_CONV_FORMAT_USER_T2F_04: /* STEP 030 */
				case ID_CONV_FORMAT_USER_F2T_04: /* STEP 030 */
					strName.Format(L"04�F%s", g_userConvFormat[3].strName);
					break;
				case ID_CONV_FORMAT_USER_05: /* LastTrain 057 */
				case ID_CONV_FORMAT_USER_T2F_05: /* STEP 030 */
				case ID_CONV_FORMAT_USER_F2T_05: /* STEP 030 */
					strName.Format(L"05�F%s", g_userConvFormat[4].strName);
					break;
				case ID_TEIKEI_01: /* SeaKnows 030 */
					strName.Format(L"01: %s", shortString(g_teikeiInfo[0].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_02: /* SeaKnows 030 */
					strName.Format(L"02: %s", shortString(g_teikeiInfo[1].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_03: /* SeaKnows 030 */
					strName.Format(L"03: %s", shortString(g_teikeiInfo[2].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_04: /* SeaKnows 030 */
					strName.Format(L"04: %s", shortString(g_teikeiInfo[3].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_05: /* SeaKnows 030 */
					strName.Format(L"05: %s", shortString(g_teikeiInfo[4].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_06: /* SeaKnows 030 */
					strName.Format(L"06: %s", shortString(g_teikeiInfo[5].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_07: /* SeaKnows 030 */
					strName.Format(L"07: %s", shortString(g_teikeiInfo[6].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_08: /* SeaKnows 030 */
					strName.Format(L"08: %s", shortString(g_teikeiInfo[7].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_09: /* SeaKnows 030 */
					strName.Format(L"09: %s", shortString(g_teikeiInfo[8].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_10: /* SeaKnows 030 */
					strName.Format(L"10: %s", shortString(g_teikeiInfo[9].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_2_01: /* FreeFall 046 */
					strName.Format(L"01: %s", shortString(g_teikeiInfo[10].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_2_02: /* FreeFall 046 */
					strName.Format(L"02: %s", shortString(g_teikeiInfo[11].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_2_03: /* FreeFall 046 */
					strName.Format(L"03: %s", shortString(g_teikeiInfo[12].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_2_04: /* FreeFall 046 */
					strName.Format(L"04: %s", shortString(g_teikeiInfo[13].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_2_05: /* FreeFall 046 */
					strName.Format(L"05: %s", shortString(g_teikeiInfo[14].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_2_06: /* FreeFall 046 */
					strName.Format(L"06: %s", shortString(g_teikeiInfo[15].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_2_07: /* FreeFall 046 */
					strName.Format(L"07: %s", shortString(g_teikeiInfo[16].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_2_08: /* FreeFall 046 */
					strName.Format(L"08: %s", shortString(g_teikeiInfo[17].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_2_09: /* FreeFall 046 */
					strName.Format(L"09: %s", shortString(g_teikeiInfo[18].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_2_10: /* FreeFall 046 */
					strName.Format(L"10: %s", shortString(g_teikeiInfo[19].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_3_01: /* FreeFall 046 */
					strName.Format(L"01: %s", shortString(g_teikeiInfo[20].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_3_02: /* FreeFall 046 */
					strName.Format(L"02: %s", shortString(g_teikeiInfo[21].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_3_03: /* FreeFall 046 */
					strName.Format(L"03: %s", shortString(g_teikeiInfo[22].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_3_04: /* FreeFall 046 */
					strName.Format(L"04: %s", shortString(g_teikeiInfo[23].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_3_05: /* FreeFall 046 */
					strName.Format(L"05: %s", shortString(g_teikeiInfo[24].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_3_06: /* FreeFall 046 */
					strName.Format(L"06: %s", shortString(g_teikeiInfo[25].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_3_07: /* FreeFall 046 */
					strName.Format(L"07: %s", shortString(g_teikeiInfo[26].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_3_08: /* FreeFall 046 */
					strName.Format(L"08: %s", shortString(g_teikeiInfo[27].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_3_09: /* FreeFall 046 */
					strName.Format(L"09: %s", shortString(g_teikeiInfo[28].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_TEIKEI_3_10: /* FreeFall 046 */
					strName.Format(L"10: %s", shortString(g_teikeiInfo[29].strTeikei/* STEP 035 */, TEIKEI_MENU_STRING_MAX) /* FreeFall 051 */);
					break;
				case ID_FAVORITE_FOLDER_01: /* RockDance 129 */
					strName.Format(L"&1 %s", shortFavorite(g_strFavorite[0]));
					break;
				case ID_FAVORITE_FOLDER_02: /* RockDance 129 */
					strName.Format(L"&2 %s", shortFavorite(g_strFavorite[1]));
					break;
				case ID_FAVORITE_FOLDER_03: /* RockDance 129 */
					strName.Format(L"&3 %s", shortFavorite(g_strFavorite[2]));
					break;
				case ID_FAVORITE_FOLDER_04: /* RockDance 129 */
					strName.Format(L"&4 %s", shortFavorite(g_strFavorite[3]));
					break;
				case ID_FAVORITE_FOLDER_05: /* RockDance 129 */
					strName.Format(L"&5 %s", shortFavorite(g_strFavorite[4]));
					break;
				case ID_FAVORITE_FOLDER_06: /* RockDance 129 */
					strName.Format(L"&6 %s", shortFavorite(g_strFavorite[5]));
					break;
				case ID_FAVORITE_FOLDER_07: /* RockDance 129 */
					strName.Format(L"&7 %s", shortFavorite(g_strFavorite[6]));
					break;
				case ID_FAVORITE_FOLDER_08: /* RockDance 129 */
					strName.Format(L"&8 %s", shortFavorite(g_strFavorite[7]));
					break;
				case ID_FAVORITE_FOLDER_09: /* RockDance 129 */
					strName.Format(L"&9 %s", shortFavorite(g_strFavorite[8]));
					break;
				case ID_FAVORITE_FOLDER_10: /* RockDance 129 */
					strName.Format(L"&0 %s", shortFavorite(g_strFavorite[9]));
					break;
				case ID_EDIT_COPY_FORMAT_01: /* FunnyCorn 175 */
					strName.Format(L"01�F%s", g_userCopyFormat[0].strName);
					break;
				case ID_EDIT_COPY_FORMAT_02: /* FunnyCorn 175 */
					strName.Format(L"02�F%s", g_userCopyFormat[1].strName);
					break;
				case ID_EDIT_COPY_FORMAT_03: /* FunnyCorn 175 */
					strName.Format(L"03�F%s", g_userCopyFormat[2].strName);
					break;
				case ID_EDIT_COPY_FORMAT_04: /* FunnyCorn 175 */
					strName.Format(L"04�F%s", g_userCopyFormat[3].strName);
					break;
				case ID_EDIT_COPY_FORMAT_05: /* FunnyCorn 175 */
					strName.Format(L"05�F%s", g_userCopyFormat[4].strName);
					break;
				case ID_CONV_TAG_TO_TAG_01: /* STEP 034 */
					strName.Format(L"01�F%s", g_userConvFormatTag2Tag[0].strName);
					break;
				case ID_CONV_TAG_TO_TAG_02: /* STEP 034 */
					strName.Format(L"02�F%s", g_userConvFormatTag2Tag[1].strName);
					break;
				case ID_CONV_TAG_TO_TAG_03: /* STEP 034 */
					strName.Format(L"03�F%s", g_userConvFormatTag2Tag[2].strName);
					break;
				case ID_CONV_TAG_TO_TAG_04: /* STEP 034 */
					strName.Format(L"04�F%s", g_userConvFormatTag2Tag[3].strName);
					break;
				case ID_CONV_TAG_TO_TAG_05: /* STEP 034 */
					strName.Format(L"05�F%s", g_userConvFormatTag2Tag[4].strName);
					break;
				default:
					pMenu->GetMenuString((UINT)pKey->wCmdID, strName, MF_BYCOMMAND);
					break;
				}

				// ���݂̃A�N�Z�����[�^�L�[�������폜
				int		nPos;
				if ((nPos = strName.Find('\t')) != -1) {
					strName = strName.Left(nPos);
				}

				if (pAccel != NULL) {
					// �V�����A�N�Z�����[�^�L�[������ǉ�
					strName += '\t';
					if (wModifiers & HOTKEYF_ALT) strName += L"Alt+";
					if (wModifiers & HOTKEYF_CONTROL) strName += L"Ctrl+";
					if (wModifiers & HOTKEYF_SHIFT) strName += L"Shift+";
					// �L�[������ǉ�
					if (pAccel->key <= 0x91) {
						strName += g_sKeyName[pAccel->key];
					} else {
						strName += L"?";
					}
				}

				// ���j���[��������X�V
				pMenu->ModifyMenu((UINT)pKey->wCmdID, MF_BYCOMMAND, pKey->wCmdID, (LPCWSTR)strName);
			}
		}
	}

	extern CPlugin plugins;
	for (i = 0; i < plugins.arPluginKey.GetSize(); i++) {
		KEY_CONFIG* pKey = (KEY_CONFIG*)plugins.arPluginKey.GetAt(i);
		if (pKey->wCmdID != 0x0000) {
			// �A�N�Z�����[�^�̍쐬
			ACCEL	*pAccel = NULL;
			WORD	wModifiers = 0x0000;
			if (pKey->dwKeyCode != 0) {
				wModifiers = HIWORD(pKey->dwKeyCode);
				pAccel = &m_accelTable[nCount];
				pAccel->fVirt = FNOINVERT | FVIRTKEY;
				if (wModifiers & HOTKEYF_ALT) pAccel->fVirt |= FALT;
				if (wModifiers & HOTKEYF_CONTROL) pAccel->fVirt |= FCONTROL;
				if (wModifiers & HOTKEYF_SHIFT) pAccel->fVirt |= FSHIFT;
				pAccel->key = LOWORD(pKey->dwKeyCode);
				pAccel->cmd = pKey->wCmdID;
				nCount++;
			}

			// ���j���[���ڂ̏�������
			if (pMenu != NULL) {
				CString	strName;
				pMenu->GetMenuString((UINT)pKey->wCmdID, strName, MF_BYCOMMAND);

				// ���݂̃A�N�Z�����[�^�L�[�������폜
				int		nPos;
				if ((nPos = strName.Find('\t')) != -1) {
					strName = strName.Left(nPos);
				}

				if (pAccel != NULL) {
					// �V�����A�N�Z�����[�^�L�[������ǉ�
					strName += '\t';
					if (wModifiers & HOTKEYF_ALT) strName += L"Alt+";
					if (wModifiers & HOTKEYF_CONTROL) strName += L"Ctrl+";
					if (wModifiers & HOTKEYF_SHIFT) strName += L"Shift+";
					// �L�[������ǉ�
					if (pAccel->key <= 0x91) {
						strName += g_sKeyName[pAccel->key];
					} else {
						strName += L"?";
					}
				}

				// ���j���[��������X�V
				pMenu->ModifyMenu((UINT)pKey->wCmdID, MF_BYCOMMAND, pKey->wCmdID, (LPCWSTR)strName);
			}
		}
	}

	// �A�N�Z�����[�^�e�[�u���̓o�^
	m_hAccel = CreateAcceleratorTable(m_accelTable, nCount);

	pMenu = pMainWnd ? pMainWnd->GetMenu() : NULL;
	if (pMenu != NULL) {
		CMenu* pTeikeiMenu = NULL;
		int nCount = pMenu->GetMenuItemCount();
		int j; for (int j = 0; j < nCount; j++) {
			CString strTitle;
			pMenu->GetMenuString(j, strTitle, MF_BYPOSITION);
			if (strTitle == L"�ҏW(&E)") {
				pMenu = pMenu->GetSubMenu(j);
				break;
			}
		}
		nCount = pMenu->GetMenuItemCount();
		for (j = 0; j < nCount; j++) {
			CString strTitle;
			pMenu->GetMenuString(j, strTitle, MF_BYPOSITION);
			if (strTitle == L"��^���\��t��") {
				pTeikeiMenu = pMenu->GetSubMenu(j);
				break;
			}
		}
		for (int k = 0; k < 3 && pTeikeiMenu; k++) {
			CMenu* pSubMenu = pTeikeiMenu->GetSubMenu(0);
			pTeikeiMenu->RemoveMenu(0, MF_BYPOSITION);
			pTeikeiMenu->AppendMenu(MF_POPUP, (UINT)pSubMenu->GetSafeHmenu(), (LPCWSTR)g_strTeikeiGroupName[k]);
		}
	}
}

//---------------------------------------------------------------------------
// func:	���W�X�g������Winamp�̃p�X�����o��
//---------------------------------------------------------------------------
void CSuperTagEditorApp::GetWinampPath(void)
{
	HKEY	hKey;
	CString strKeyString = L"Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Winamp.exe";

	g_sOptWinAmpPath = L"";

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strKeyString, 0, KEY_EXECUTE, &hKey) == ERROR_SUCCESS) {
		DWORD	dwValueType;
		DWORD	dwValueSize = FILENAME_MAX;
		unsigned char	sValue[FILENAME_MAX];

		/* ���W�X�g���l�̎擾 */
		RegQueryValueEx(hKey, L"", NULL, &dwValueType, &sValue[0], &dwValueSize);

		/* ���ʂ̕\�� */
		if (dwValueType == REG_SZ) g_sOptWinAmpPath = sValue;

		/* �I�� */
		RegCloseKey(hKey);
	}
}

// �W���������X�g�̐ݒ�����W�X�g������ǂ݂���
void CSuperTagEditorApp::ReadGenreList(void)
{
	CString strINI = m_pszProfileName;
	InitProfile();
	int nIndex; for (nIndex = 0; g_genreListSCMPX[nIndex].sName != L'\0'; nIndex++) {
		GENRE_LIST	*pGenre = &g_genreListSCMPX[nIndex];
		CString	strName;
		strName.Format(L"%d", pGenre->byGenre);
		pGenre->bAddList = (DWORD)MyGetProfileInt(sSectionGenreList, strName, 1) ? true : false;
	}
	int i; for (i = 0; i < USER_GENRE_LIST_MAX; i++) {
		CString		strSectionName;
		strSectionName.Format(L"haseta\\%s\\%d", sSectionUserGenreList, i);
		g_genreListUSER[i].bAddList = MyGetProfileInt(strSectionName, sKeyUserGenreAddList, 0) == 0 ? false : true;
		g_genreListUSER[i].byGenre = (BYTE)MyGetProfileInt(strSectionName, sKeyUserGenreNo, 255);
		g_genreListUSER[i].sName = MyGetProfileString(strSectionName, sKeyUserGenreName, NULL);
		if (g_genreListUSER[i].sName.GetLength() == 0) {
			g_genreListUSER[i].bUse = false;
		} else {
			g_genreListUSER[i].bUse = true;
		}
	}
	FreeProfile();
}

// �W���������X�g�̐ݒ�����W�X�g���ɏ����o��
void CSuperTagEditorApp::WriteGenreList(void)
{
	CString strINI = m_pszProfileName;
	InitProfile();
	int nIndex; for (nIndex = 0; g_genreListSCMPX[nIndex].sName != L'\0'; nIndex++) {
		GENRE_LIST	*pGenre = &g_genreListSCMPX[nIndex];
		CString	strName;
		strName.Format(L"%d", pGenre->byGenre);
		MyWriteProfileInt(sSectionGenreList, strName, pGenre->bAddList ? 1 : 0);
	}
	if (g_genreListUSER != NULL) {
		int i; for (i = 0; i < USER_GENRE_LIST_MAX; i++) {
			CString		strSectionName;
			strSectionName.Format(L"haseta\\%s\\%d", sSectionUserGenreList, i);
			MyWriteProfileInt(strSectionName, sKeyUserGenreAddList, g_genreListUSER[i].bAddList == true ? 1 : 0);
			MyWriteProfileInt(strSectionName, sKeyUserGenreNo, g_genreListUSER[i].byGenre);
			MyWriteProfileString(strSectionName, sKeyUserGenreName, g_genreListUSER[i].sName);
		}
	}
	SaveProfile();
	FreeProfile();
}

void CSuperTagEditorApp::LoadStdProfileSettings(UINT nMaxMRU)  /* StartInaction 053 */
{
	ASSERT_VALID(this);
	ASSERT(m_pRecentFileList == NULL);

	if (nMaxMRU != 0) {
		m_pRecentFileList = new CMyRecentFileList(0, L"haseta\\MRU", L"MRUFolder%d", nMaxMRU, 60);
		m_pRecentFileList->ReadList();
	}
}

void CSuperTagEditorApp::OnUpdateFileMruFile(CCmdUI* pCmdUI) /* StartInaction 053 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	m_pRecentFileList->UpdateMenu(pCmdUI);
}

void CSuperTagEditorApp::AddToRecentFileList(LPCWSTR lpszPathName) /* StartInaction 053 */
{
	CString strPath = lpszPathName; /* WildCherry2 079 */
	if (IsFolderName(lpszPathName) == true) {
		strPath.Delete(strPath.GetLength() - 1);
	}
	m_pRecentFileList->Add(strPath);
}

BOOL CSuperTagEditorApp::OnOpenRecentFile(UINT nID) /* BeachMonster 104 */
{
	// ���̂���������Ȃ������̂ŁAOnOpenRecentFile()���I�[�o�[���C�h���Ď��O�ŏ�������
	int nIndex = nID - ID_FILE_MRU_FILE1;
	ASSERT((*m_pRecentFileList)[nIndex].GetLength() != 0);

	TRACE2("MRU: open file (%d) '%s'.\n", (nIndex)+1,
		(LPCWSTR)(*m_pRecentFileList)[nIndex]);

	POSITION pos = GetFirstDocTemplatePosition();
	if (pos != NULL) {
		CDocTemplate* pDocTemp = GetNextDocTemplate(pos);
		if (pDocTemp != NULL) {
			POSITION docPos = pDocTemp->GetFirstDocPosition();
			if (docPos != NULL) {
				CSuperTagEditorDoc* pDoc = (CSuperTagEditorDoc*)pDocTemp->GetNextDoc(docPos);
				if (pDoc != NULL) {
					pDoc->OnOpenDocument((*m_pRecentFileList)[nIndex]);
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

void CSuperTagEditorApp::OnFavoriteFolder(CString& strFolder)
{
	POSITION pos = GetFirstDocTemplatePosition();
	if (pos != NULL) {
		CDocTemplate* pDocTemp = GetNextDocTemplate(pos);
		if (pDocTemp != NULL) {
			POSITION docPos = pDocTemp->GetFirstDocPosition();
			if (docPos != NULL) {
				CSuperTagEditorDoc* pDoc = (CSuperTagEditorDoc*)pDocTemp->GetNextDoc(docPos);
				if (pDoc != NULL) {
					pDoc->OnOpenDocument(strFolder);
					return;
				}
			}
		}
	}
}

void CSuperTagEditorApp::OnUpdateFavoriteFolder01(CCmdUI* pCmdUI) /* RockDance 124 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(!g_strFavorite[0].IsEmpty());
}

void CSuperTagEditorApp::OnFavoriteFolder01() /* RockDance 124 */
{
	OnFavoriteFolder(g_strFavorite[0]);
}

void CSuperTagEditorApp::OnUpdateFavoriteFolder02(CCmdUI* pCmdUI) /* RockDance 124 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(!g_strFavorite[1].IsEmpty());
}

void CSuperTagEditorApp::OnFavoriteFolder02() /* RockDance 124 */
{
	OnFavoriteFolder(g_strFavorite[1]);
}

void CSuperTagEditorApp::OnUpdateFavoriteFolder03(CCmdUI* pCmdUI) /* RockDance 124 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(!g_strFavorite[2].IsEmpty());
}

void CSuperTagEditorApp::OnFavoriteFolder03() /* RockDance 124 */
{
	OnFavoriteFolder(g_strFavorite[2]);
}

void CSuperTagEditorApp::OnUpdateFavoriteFolder04(CCmdUI* pCmdUI) /* RockDance 124 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(!g_strFavorite[3].IsEmpty());
}

void CSuperTagEditorApp::OnFavoriteFolder04() /* RockDance 124 */
{
	OnFavoriteFolder(g_strFavorite[3]);
}

void CSuperTagEditorApp::OnUpdateFavoriteFolder05(CCmdUI* pCmdUI) /* RockDance 124 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(!g_strFavorite[4].IsEmpty());
}

void CSuperTagEditorApp::OnFavoriteFolder05() /* RockDance 124 */
{
	OnFavoriteFolder(g_strFavorite[4]);
}

void CSuperTagEditorApp::OnUpdateFavoriteFolder06(CCmdUI* pCmdUI) /* RockDance 124 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(!g_strFavorite[5].IsEmpty());
}

void CSuperTagEditorApp::OnFavoriteFolder06() /* RockDance 124 */
{
	OnFavoriteFolder(g_strFavorite[5]);
}

void CSuperTagEditorApp::OnUpdateFavoriteFolder07(CCmdUI* pCmdUI) /* RockDance 124 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(!g_strFavorite[6].IsEmpty());
}

void CSuperTagEditorApp::OnFavoriteFolder07() /* RockDance 124 */
{
	OnFavoriteFolder(g_strFavorite[6]);
}

void CSuperTagEditorApp::OnUpdateFavoriteFolder08(CCmdUI* pCmdUI) /* RockDance 124 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(!g_strFavorite[7].IsEmpty());
}

void CSuperTagEditorApp::OnFavoriteFolder08() /* RockDance 124 */
{
	OnFavoriteFolder(g_strFavorite[7]);
}

void CSuperTagEditorApp::OnUpdateFavoriteFolder09(CCmdUI* pCmdUI) /* RockDance 124 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(!g_strFavorite[8].IsEmpty());
}

void CSuperTagEditorApp::OnFavoriteFolder09() /* RockDance 124 */
{
	OnFavoriteFolder(g_strFavorite[8]);
}

void CSuperTagEditorApp::OnUpdateFavoriteFolder10(CCmdUI* pCmdUI) /* RockDance 124 */
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
	pCmdUI->Enable(!g_strFavorite[9].IsEmpty());
}

void CSuperTagEditorApp::OnFavoriteFolder10() /* RockDance 124 */
{
	OnFavoriteFolder(g_strFavorite[9]);
}

void CSuperTagEditorApp::ReadFixedWordList()
{
	wchar_t   drive[_MAX_DRIVE];
	wchar_t   dir[_MAX_DIR];
	wchar_t   buff[_MAX_PATH] = { '\0' };

	//���ȃA�v���̃p�X�����i�召�������ʕt���j
	GetModuleFileName(m_hInstance, buff, _MAX_PATH);
	_tsplitpath(buff, drive, dir, NULL, NULL);
	_tmakepath(buff, drive, dir, L"FixedWordList", L"ini");

	g_arFixedWords.RemoveAll();
	TRY{
		CFile	file;
		if (file.Open(buff, CFile::modeRead | CFile::shareDenyNone)) {
			CArchive	ar(&file, CArchive::load);
			CString strLine;
			while (ar.ReadString(strLine)) {
				g_arFixedWords.Add(strLine);
			}
		}
	}
		CATCH(CFileException, e) {
			CString	str;
			str.Format(L"%s �̓ǂݍ��݂Ɏ��s���܂���", buff);
			MessageBox(NULL, str, L"�t�@�C���G���[", MB_ICONSTOP | MB_OK | MB_TOPMOST);
	}
	END_CATCH
}

void CSuperTagEditorApp::WriteFixedWordList()
{
	wchar_t   drive[_MAX_DRIVE];
	wchar_t   dir[_MAX_DIR];
	wchar_t   buff[_MAX_PATH] = { '\0' };

	//���ȃA�v���̃p�X�����i�召�������ʕt���j
	GetModuleFileName(m_hInstance, buff, _MAX_PATH);
	_tsplitpath(buff, drive, dir, NULL, NULL);
	_tmakepath(buff, drive, dir, L"FixedWordList", L"ini");

	TRY{
		CFile	file;
		if (file.Open(buff, CFile::modeCreate | CFile::modeWrite)) {
			CArchive	ar(&file, CArchive::store);
			CString strLine;
			for (int i = 0; i < g_arFixedWords.GetSize(); i++) {
				ar.WriteString(g_arFixedWords.GetAt(i) + "\n");
			}
		}
	}
		CATCH(CFileException, e) {
			CString	str;
			str.Format(L"%s �̏������݂Ɏ��s���܂���", buff);
			MessageBox(NULL, str, L"�t�@�C���G���[", MB_ICONSTOP | MB_OK | MB_TOPMOST);
	}
	END_CATCH
}

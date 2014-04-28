#ifndef _STEPLUGIN_H_
#define _STEPLUGIN_H_

#include "STEP_api.h"

//extern HINSTANCE g_hInstance;
//extern HINSTANCE hLib;

/* プラグインから呼び出せる関数 */
extern "C" {
extern STEP_API UINT (WINAPI *STEPGetCommandID)(void);
extern STEP_API HMENU (WINAPI *STEPGetMenu)(UINT);
extern STEP_API void (WINAPI *STEPAddToolBarButton)(HBITMAP, UINT, wchar_t*);
extern STEP_API UINT (WINAPI *STEPRegisterExt)(UINT, LPCWSTR, HBITMAP);
extern STEP_API UINT (WINAPI *STEPKeyAssign)(UINT, LPCWSTR, LPCWSTR);
extern STEP_API const wchar_t* (WINAPI *STEPGetGenreNameSIF)(BYTE byGenre);
extern STEP_API BYTE (WINAPI *STEPGetGenreCode)(const wchar_t* szGenre);
extern STEP_API bool (WINAPI *STEPIsUserGenre)(const wchar_t* szGenre);
extern STEP_API int (WINAPI *STEPGetNumericTrackNumber)(const wchar_t* szTrackNumber, wchar_t* szNumericNumber, int size); /* STEP 037 */
extern STEP_API int (WINAPI *STEPGetIntegerTrackNumber)(const wchar_t* szTrackNumber); /* STEP 037 */
extern STEP_API int (WINAPI *STEPGetNumericDiskNumber)(const wchar_t* szDiskNumber, wchar_t* szNumericNumber, int size); /* STEP 037 */
extern STEP_API int (WINAPI *STEPGetIntegerDiskNumber)(const wchar_t* szDiskNumber); /* STEP 037 */

extern STEP_API void (WINAPI *STEPProcessSelectedFiles)(LPCWSTR, STEPProcessSelectedFilesCB);
extern STEP_API void (WINAPI *STEPProcessSelectedFilesForUpdate)(LPCWSTR, STEPProcessSelectedFilesCB);

extern STEP_API bool (WINAPI *STEPIsRangeSelected)(void);
extern STEP_API int (WINAPI *STEPGetSelectedCount)(void);
extern STEP_API int (WINAPI *STEPGetSelectedItem)(void);
extern STEP_API bool (WINAPI *STEPIsCurrentCellEditOK)(void);
extern STEP_API bool (WINAPI *STEPItemHasChildren)(int);
extern STEP_API bool (WINAPI *STEPGetSelectedRange)(int*, int*, int* , int*);
extern STEP_API bool (WINAPI *STEPIsItemFile)(int);
extern STEP_API void (WINAPI *STEPChangeSubItemText)(int nItem, int nColumn, LPCWSTR szText);
extern STEP_API const wchar_t* (WINAPI *STEPGetSubItemText)(int nItem, int nColumn);
extern STEP_API void (WINAPI *STEPGetFileInfo)(int nItem, FILE_INFO* info);
extern STEP_API UINT (WINAPI *STEPGETColumnType)(int nColumn);
extern STEP_API bool (WINAPI *STEPIsCurrentCellEditOK)(void);
extern STEP_API bool (WINAPI *STEPIsNumeric)(const wchar_t* szText); /* STEP 037 */
extern STEP_API void (WINAPI *STEPConvSiFieldToId3tag)(FILE_INFO* pFileInfo); /* STEP 037 */

extern STEP_API void (WINAPI *STEPInitDataSIF)(FILE_INFO* info);
extern STEP_API void (WINAPI *STEPInitDataID3)(FILE_INFO* info); /* STEP 029 */
extern STEP_API void (WINAPI *STEPInitData)(FILE_INFO* info);
extern STEP_API bool (WINAPI *STEPFileNameChange)(FILE_INFO* pFileInfo, LPCWSTR szNewFileName);
extern STEP_API bool (WINAPI *STEPWriteTag)(FILE_INFO* pFileInfo);

extern STEP_API bool (WINAPI *STEPUpdateCellInfo)(void);
}

extern bool Initialize(void);
extern void Finalize(void);

/* タグ情報の取得／設定 */
extern LPCWSTR GetFullPath(FILE_INFO* info);
extern LPCWSTR GetFileName(FILE_INFO* info);
extern LPCWSTR GetFilePath(FILE_INFO* info);
extern LPCWSTR GetVisualFormat(FILE_INFO* info);
extern LPCWSTR GetAudioFormat(FILE_INFO* info);
extern LPCWSTR GetTrackName(FILE_INFO* info);
extern LPCWSTR GetArtistName(FILE_INFO* info);
extern LPCWSTR GetAlbumName(FILE_INFO* info);
extern LPCWSTR GetComment(FILE_INFO* info);
extern LPCWSTR GetYear(FILE_INFO* info);
extern LPCWSTR GetTrackNumber(FILE_INFO* info);
extern LPCWSTR GetDiskNumber(FILE_INFO* info);
extern LPCWSTR GetGenre(FILE_INFO* info);
extern LPCWSTR GetTrackNameSI(FILE_INFO* info);
extern LPCWSTR GetArtistNameSI(FILE_INFO* info);
extern LPCWSTR GetAlbumNameSI(FILE_INFO* info);
extern LPCWSTR GetCommentSI(FILE_INFO* info);
extern LPCWSTR GetYearSI(FILE_INFO* info);
extern LPCWSTR GetTrackNumberSI(FILE_INFO* info);
extern LPCWSTR GetDiskNumberSI(FILE_INFO* info);
extern LPCWSTR GetGenreSI(FILE_INFO* info);
extern LPCWSTR GetCopyrightSI(FILE_INFO* info);
extern LPCWSTR GetEngineerSI(FILE_INFO* info);
extern LPCWSTR GetSourceSI(FILE_INFO* info);
extern LPCWSTR GetSoftwareSI(FILE_INFO* info);
extern LPCWSTR GetKeywordSI(FILE_INFO* info);
extern LPCWSTR GetTechnicianSI(FILE_INFO* info);
extern LPCWSTR GetLyricSI(FILE_INFO* info);
extern LPCWSTR GetCommissionSI(FILE_INFO* info);
extern LPCWSTR GetWriterSI(FILE_INFO* info);
extern LPCWSTR GetComposerSI(FILE_INFO* info);
extern LPCWSTR GetAlbumArtistSI(FILE_INFO* info);
extern LPCWSTR GetOrigArtistSI(FILE_INFO* info);
extern LPCWSTR GetURLSI(FILE_INFO* info);
extern LPCWSTR GetEncodest(FILE_INFO* info);
extern LPCWSTR GetOther(FILE_INFO* info);
extern LPCWSTR GetFileTypeName(FILE_INFO* info);
extern void SetFullPathName(FILE_INFO* info, LPCWSTR szValue);
extern void SetFileName(FILE_INFO* info, LPCWSTR szValue);
extern void SetFilePath(FILE_INFO* info, LPCWSTR szValue);
extern void SetVisualFormat(FILE_INFO* info, LPCWSTR szValue);
extern void SetAudioFormat(FILE_INFO* info, LPCWSTR szValue);
extern void SetTrackName(FILE_INFO* info, LPCWSTR szValue);
extern void SetArtistName(FILE_INFO* info, LPCWSTR szValue);
extern void SetAlbumName(FILE_INFO* info, LPCWSTR szValue);
extern void SetComment(FILE_INFO* info, LPCWSTR szValue);
extern void SetYear(FILE_INFO* info, LPCWSTR szValue);
extern void SetTrackNumber(FILE_INFO* info, LPCWSTR szValue);
extern void SetGenre(FILE_INFO* info, LPCWSTR szValue);
extern void SetTrackNameSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetArtistNameSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetAlbumNameSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetCommentSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetYearSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetTrackNumberSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetDiskNumberSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetGenreSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetCopyrightSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetEngineerSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetSourceSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetSoftwareSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetKeywordSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetTechnicianSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetLyricSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetCommissionSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetWriterSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetComposerSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetAlbumArtistSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetOrigArtistSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetURLSI(FILE_INFO* info, LPCWSTR szValue);
extern void SetEncodest(FILE_INFO* info, LPCWSTR szValue);
extern void SetOther(FILE_INFO* info, LPCWSTR szValue);
extern void SetFileTypeName(FILE_INFO* info, LPCWSTR szValue);

extern bool isModify(FILE_INFO*);
extern void SetModifyFlag(FILE_INFO* pInfo, bool bModify);
extern bool isChecked(FILE_INFO* pInfo);
extern void SetCheckFlag(FILE_INFO* pInfo, bool bCheck);
extern bool isExistLyricFile(FILE_INFO* pInfo);
extern void SetExistLyricFile(FILE_INFO* pInfo, bool bExist);
extern long GetFileSize(FILE_INFO* pInfo);
extern void SetFileSize(FILE_INFO* pInfo, long size);
extern UINT GetFormat(FILE_INFO* pInfo);
extern void SetFormat(FILE_INFO* pInfo, UINT nFormat);
extern int  GetPlayTime(FILE_INFO* pInfo);
extern void SetPlayTime(FILE_INFO* pInfo, int nPlayTime);
extern BYTE GetBTrackNumber(FILE_INFO* pInfo);
extern void SetBTrackNumber(FILE_INFO* pInfo, BYTE nTrackNumber);
extern BYTE GetBDiskNumber(FILE_INFO* pInfo);
extern void SetBDiskNumber(FILE_INFO* pInfo, BYTE nDiskNumber);
extern BYTE GetBGenre(FILE_INFO* pInfo);
extern void SetBGenre(FILE_INFO* pInfo, BYTE nGenre);
extern void* GetFileSpecificInfo(FILE_INFO* pInfo);
extern void SetFileSpecificInfo(FILE_INFO* pInfo, void* info);

extern LPCWSTR GetValue(FILE_INFO* pInfo, FIELDTYPE nField);
extern void SetValue(FILE_INFO* pInfo, FIELDTYPE nField, LPCWSTR szValue);

#endif
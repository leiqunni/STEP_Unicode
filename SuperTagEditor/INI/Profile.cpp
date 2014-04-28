/**************************************************************************

	Profile.c

	(C) Copyright 1996-2002 By Tomoaki Nakashima. All right reserved.
		http://www.nakka.com/
		nakka@nakka.com

**************************************************************************/

/**************************************************************************
	Include Files
**************************************************************************/
#include "stdafx.h"

#define _INC_OLE
#include <windows.h>
#undef  _INC_OLE

#include "Profile.h"

/**************************************************************************
	Define
**************************************************************************/

#define BUF_SIZE				256
#define ALLOC_CNT				10

#ifdef UNICODE
#define a2i						_wtoi
#else
#define a2i						_wtoi
#endif

#ifndef CopyMemory
#define CopyMemory				memcpy
#endif


/**************************************************************************
	Global Variables
**************************************************************************/

typedef struct _KEY {
	wchar_t KeyName[BUF_SIZE];
	int hash;
	wchar_t *String;
	BOOL CommentFlag;
} KEY_INFO;

typedef struct _SECTION {
	wchar_t SectionName[BUF_SIZE];
	int hash;
	KEY_INFO *KeyInfo;
	int KeyCnt;
	int KeyAllocCnt;
} SECTION_INFO;


static SECTION_INFO *SectionInfo;
static int SectionCnt;
static int SectionAllocCnt;


/**************************************************************************
	Local Function Prototypes
**************************************************************************/

static BOOL Trim(wchar_t *buf);
static int str2hash(const wchar_t *str);
static wchar_t *StrCpy_Profile(wchar_t *ret, const wchar_t *buf);
static BOOL WriteAsciiFile(const HANDLE hFile, const wchar_t *buf, const int len);
static BOOL AddSection(const wchar_t *SectionName);
static int FindSection(const wchar_t *SectionName);
static BOOL AddKey(SECTION_INFO *si, const wchar_t *KeyName, const wchar_t *String, const BOOL cFlag);
static int FindKey(const SECTION_INFO *si, const wchar_t *KeyName);
static BOOL Profile_WriteData(const wchar_t *Section, const wchar_t *Key, const wchar_t *str, const wchar_t *File);


/******************************************************************************

	Trim

	������̑O��̋�, Tab����������

******************************************************************************/

static BOOL Trim(wchar_t *buf)
{
	wchar_t *p, *r;

	//�O��̋󔒂��������|�C���^���擾
	for(p = buf; (*p == TEXT(' ') || *p == TEXT('\t')) && *p != TEXT('\0'); p++);
	for(r = buf + wcslen(buf) - 1; r > p && (*r == TEXT(' ') || *r == TEXT('\t')); r--);
	*(r + 1) = TEXT('\0');

	//���̕�����ɃR�s�[���s��
	wcscpy(buf, p);
	return TRUE;
}


/******************************************************************************

	str2hash

	������̃n�b�V���l���擾

******************************************************************************/

static int str2hash(const wchar_t *str)
{
#define ToLower(c)		((c >= TEXT('A') && c <= TEXT('Z')) ? (c - TEXT('A') + TEXT('a')) : c)
	int hash = 0;

	for(; *str != TEXT('\0'); str++){
		hash = ((hash << 1) + ToLower(*str));
	}
	return hash;
}


/******************************************************************************

	StrCpy

	��������R�s�[���čŌ�̕����̃A�h���X��Ԃ�

******************************************************************************/

static wchar_t *StrCpy_Profile(wchar_t *ret, const wchar_t *buf)
{
	if(buf == NULL){
		*ret = TEXT('\0');
		return ret;
	}
	while(*(ret++) = *(buf++));
	ret--;
	return ret;
}


/******************************************************************************

	WriteAsciiFile

	�}���`�o�C�g�ɕϊ����ĕۑ�

******************************************************************************/

static BOOL WriteAsciiFile(const HANDLE hFile, const wchar_t *buf, const int len)
{
#ifdef UNICODE
	wchar_t *str;
	DWORD ret;
	int clen;

	clen = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
	str = (wchar_t *)LocalAlloc(LMEM_FIXED, clen + 1);
	if(str == NULL){
		return FALSE;
	}
	WideCharToMultiByte(CP_ACP, 0, buf, -1, str, clen, NULL, NULL);
	if(WriteFile(hFile, str, clen - 1, &ret, NULL) == FALSE){
		LocalFree(str);
		return FALSE;
	}
	LocalFree(str);
	return TRUE;
#else
	DWORD ret;

	return WriteFile(hFile, buf, len, &ret, NULL);
#endif
}


/******************************************************************************

	AddSection

	�Z�N�V�����̒ǉ�

******************************************************************************/

static BOOL AddSection(const wchar_t *SectionName)
{
	SECTION_INFO *TmpSection;

	if(SectionName == NULL || *SectionName == TEXT('\0')){
		return FALSE;
	}

	if(SectionAllocCnt < SectionCnt + 1){
		//�Ċm��
		SectionAllocCnt += ALLOC_CNT;
		TmpSection = (SECTION_INFO *)LocalAlloc(LPTR, sizeof(SECTION_INFO) * SectionAllocCnt);
		if(TmpSection == NULL){
			return FALSE;
		}
		if(SectionInfo != NULL){
			CopyMemory(TmpSection, SectionInfo, sizeof(SECTION_INFO) * SectionCnt);
			LocalFree(SectionInfo);
		}
		SectionInfo = TmpSection;
	}
	//�Z�N�V�����ǉ�
	wcscpyn((SectionInfo + SectionCnt)->SectionName, SectionName, BUF_SIZE);
	Trim((SectionInfo + SectionCnt)->SectionName);
	(SectionInfo + SectionCnt)->hash = str2hash((SectionInfo + SectionCnt)->SectionName);

	SectionCnt++;
	return TRUE;
}


/******************************************************************************

	FindSection

	�Z�N�V�����̌���

******************************************************************************/

static int FindSection(const wchar_t *SectionName)
{
	int hash;
	int i;

	if(SectionInfo == NULL || SectionName == NULL || *SectionName == TEXT('\0')){
		return -1;
	}

	hash = str2hash(SectionName);
	for(i = 0; i < SectionCnt; i++){
		if((SectionInfo + i)->hash != hash){
			continue;
		}
		if(wcscmpi((SectionInfo + i)->SectionName, SectionName) == 0){
			return i;
		}
	}
	return -1;
}


/******************************************************************************

	AddKey

	�L�[�̒ǉ�

******************************************************************************/

static BOOL AddKey(SECTION_INFO *si, const wchar_t *KeyName, const wchar_t *String, const BOOL cFlag)
{
	KEY_INFO *TmpKey;
	int index = -1;

	if(KeyName == NULL || *KeyName == TEXT('\0') || String == NULL){
		return FALSE;
	}

	if(si->KeyAllocCnt < si->KeyCnt + 1){
		//�Ċm��
		si->KeyAllocCnt += ALLOC_CNT;
		TmpKey = (KEY_INFO *)LocalAlloc(LPTR, sizeof(KEY_INFO) * si->KeyAllocCnt);
		if(TmpKey == NULL){
			return FALSE;
		}
		if(si->KeyInfo != NULL){
			CopyMemory(TmpKey, si->KeyInfo, sizeof(KEY_INFO) * si->KeyCnt);
			LocalFree(si->KeyInfo);
		}
		si->KeyInfo = TmpKey;
	}
	//�L�[�ǉ�
	(si->KeyInfo + si->KeyCnt)->String = (wchar_t *)LocalAlloc(LMEM_FIXED, sizeof(wchar_t) * (wcslen(String) + 1));
	if((si->KeyInfo + si->KeyCnt)->String == NULL){
		return FALSE;
	}
	wcscpyn((si->KeyInfo + si->KeyCnt)->KeyName, KeyName, BUF_SIZE);
	Trim((si->KeyInfo + si->KeyCnt)->KeyName);
	if(cFlag == FALSE){
		(si->KeyInfo + si->KeyCnt)->hash = str2hash((si->KeyInfo + si->KeyCnt)->KeyName);
	}
	wcscpy((si->KeyInfo + si->KeyCnt)->String, String);
	(si->KeyInfo + si->KeyCnt)->CommentFlag = cFlag;

	si->KeyCnt++;
	return TRUE;
}


/******************************************************************************

	FindKey

	�L�[�̌���

******************************************************************************/

static int FindKey(const SECTION_INFO *si, const wchar_t *KeyName)
{
	int hash;
	int i;

	if(si->KeyInfo == NULL || KeyName == NULL || *KeyName == TEXT('\0')){
		return -1;
	}

	hash = str2hash(KeyName);
	for(i = 0; i < si->KeyCnt; i++){
		if((si->KeyInfo + i)->CommentFlag == TRUE ||
			(si->KeyInfo + i)->hash != hash){
			continue;
		}
		if(wcscmpi((si->KeyInfo + i)->KeyName, KeyName) == 0){
			return i;
		}
	}
	return -1;
}


/******************************************************************************

	Profile_Initialize

	������

******************************************************************************/

BOOL Profile_Initialize(const wchar_t *path, const BOOL ReadFlag)
{
	HANDLE hFile;
	wchar_t *buf, *p, *r, *s;
	wchar_t tmp[BUF_SIZE];
	wchar_t *cBuf;
	DWORD fSizeLow, fSizeHigh;
	DWORD ret;
	long FileSize;
#ifdef UNICODE
	long Len;
#endif

	if(ReadFlag == FALSE){
		SectionInfo = NULL;
		return TRUE;
	}

	//�t�@�C�����J��
	hFile = CreateFile(path, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == NULL || hFile == (HANDLE)-1){
		return FALSE;
	}
	// �m�ۂ���T�C�Y�̎擾
	fSizeLow = GetFileSize(hFile, &fSizeHigh);
	if(fSizeLow == 0xFFFFFFFF){
		CloseHandle(hFile);
		return FALSE;
	}
	FileSize = (long)fSizeLow;

	//�ǂݎ��̈�̊m��
	cBuf = (wchar_t *)LocalAlloc(LMEM_FIXED, FileSize + 1);
	if(cBuf == NULL){
		CloseHandle(hFile);
		return FALSE;
	}
	//�t�@�C����ǂݍ���
	if(ReadFile(hFile, cBuf, fSizeLow, &ret, NULL) == FALSE){
		LocalFree(cBuf);
		CloseHandle(hFile);
		return FALSE;
	}
	CloseHandle(hFile);
	*(cBuf + FileSize) = '\0';

#ifdef UNICODE
	Len = MultiByteToWideChar(CP_ACP, 0, cBuf, -1, NULL, 0);
	buf = (wchar_t *)LocalAlloc(LMEM_FIXED, sizeof(wchar_t) * (Len + 1));
	if(buf == NULL){
		LocalFree(cBuf);
		CloseHandle(hFile);
		return FALSE;
	}
	MultiByteToWideChar(CP_ACP, 0, cBuf, -1, buf, Len);
	FileSize = Len;
	LocalFree(cBuf);
#else
	buf = cBuf;
#endif

	//�Z�N�V�����̊m��
	SectionInfo = (SECTION_INFO *)LocalAlloc(LPTR, sizeof(SECTION_INFO) * ALLOC_CNT);
	if(SectionInfo == NULL){
		LocalFree(buf);
		return FALSE;
	}
	SectionCnt = 1;
	SectionAllocCnt = ALLOC_CNT;

	p = buf;
	while((FileSize > (p - buf)) && *p != TEXT('\0')){
		for(r = p; (FileSize > (r - buf)) && (*r != TEXT('\r') && *r != TEXT('\n')); r++);

		switch(*p)
		{
		case TEXT('['):
			//�Z�N�V�����̒ǉ�
			if(p == r || *(r - 1) != TEXT(']')) break;
			*(r - 1) = TEXT('\0');
			AddSection(p + 1);
			break;

		case TEXT('\r'):
		case TEXT('\n'):
			break;

		default:
			if(SectionInfo == NULL || p == r) break;
			if(*p == TEXT('#')){
				//�R�����g
				for(s = tmp; p < r; p++, s++){
					*s = *p;
				}
				*s = TEXT('\0');
				AddKey((SectionInfo + SectionCnt - 1), tmp, TEXT(L""), TRUE);
			}else{
				//�L�[�̒ǉ�
				for(s = tmp; p < r; p++, s++){
					if(*p == TEXT('=')) break;
					*s = *p;
				}
				*s = TEXT('\0');
				if(*p == TEXT('=')) p++;
				*r = TEXT('\0');
				AddKey((SectionInfo + SectionCnt - 1), tmp, p, FALSE);
			}

			if(FileSize > (r - buf)) r++;
		}
		p = r;
		for(; (FileSize > (p - buf)) && (*p == TEXT('\r') || *p == TEXT('\n')); p++);
	}
	LocalFree(buf);
	return TRUE;
}


/******************************************************************************

	Profile_Flush

	�o�b�t�@���t�@�C���ɏ�������

******************************************************************************/

BOOL Profile_Flush(const wchar_t *path)
{
	HANDLE hFile;
	wchar_t *buf, *p;
	int len;
	int i, j;

	if(SectionInfo == NULL){
		return FALSE;
	}

	//�ۑ��T�C�Y�̌v�Z
	len = 0;
	for(i = 0; i < SectionCnt; i++){
		if((SectionInfo + i)->KeyInfo == NULL){
			continue;
		}

		//�Z�N�V������
		if(i != 0){
			len += wcslen((SectionInfo + i)->SectionName) + 2 + 2;
		}

		for(j = 0; j < (SectionInfo + i)->KeyCnt; j++){
			if(*((SectionInfo + i)->KeyInfo + j)->KeyName == TEXT('\0')){
				continue;
			}
			//�L�[��
			len += wcslen(((SectionInfo + i)->KeyInfo + j)->KeyName);
			if(((SectionInfo + i)->KeyInfo + j)->CommentFlag == FALSE){
				len++;
				if(((SectionInfo + i)->KeyInfo + j)->String != NULL){
					//������
					len += wcslen(((SectionInfo + i)->KeyInfo + j)->String);
				}
			}
			len += 2;
		}
		len += 2;
	}

	//�ۑ����邽�߂̗̈�̊m��
	p = buf = (wchar_t *)LocalAlloc(LMEM_FIXED, sizeof(wchar_t) * (len + 1));
	if(buf == NULL){
		return FALSE;
	}

	//�ۑ�������̍쐬
	for(i = 0; i < SectionCnt; i++){
		if((SectionInfo + i)->KeyInfo == NULL){
			continue;
		}

		//�Z�N�V������
		if(i != 0){
			*(p++) = TEXT('[');
			p = StrCpy_Profile(p, (SectionInfo + i)->SectionName);
			p = StrCpy_Profile(p, TEXT(L"]\r\n"));
		}

		for(j = 0; j < (SectionInfo + i)->KeyCnt; j++){
			if(*((SectionInfo + i)->KeyInfo + j)->KeyName == TEXT('\0')){
				continue;
			}
			//�L�[��
			p = StrCpy_Profile(p, ((SectionInfo + i)->KeyInfo + j)->KeyName);
			if(((SectionInfo + i)->KeyInfo + j)->CommentFlag == FALSE){
				*(p++) = TEXT('=');

				if(((SectionInfo + i)->KeyInfo + j)->String != NULL){
					//������
					p = StrCpy_Profile(p, ((SectionInfo + i)->KeyInfo + j)->String);
				}
			}
			p = StrCpy_Profile(p, TEXT(L"\r\n"));
		}
		p = StrCpy_Profile(p, TEXT(L"\r\n"));
	}
	*p = TEXT('\0');

	//�t�@�C�����J��
	hFile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == NULL || hFile == (HANDLE)-1){
		LocalFree(buf);
		return FALSE;
	}

	//�t�@�C���ɏ�������
	if(WriteAsciiFile(hFile, buf, len) == FALSE){
		LocalFree(buf);
		CloseHandle(hFile);
		return FALSE;
	}

	//�������̉��
	LocalFree(buf);
	//�t�@�C�������
	CloseHandle(hFile);
	return TRUE;
}


/******************************************************************************

	Profile_Free

	�ݒ���̉��

******************************************************************************/

void Profile_Free(void)
{
	int i, j;

	if(SectionInfo == NULL){
		return;
	}
	for(i = 0; i < SectionCnt; i++){
		if((SectionInfo + i)->KeyInfo == NULL){
			continue;
		}
		//�L�[�̉��
		for(j = 0; j < (SectionInfo + i)->KeyCnt; j++){
			if(((SectionInfo + i)->KeyInfo + j)->String != NULL){
				LocalFree(((SectionInfo + i)->KeyInfo + j)->String);
			}
		}
		LocalFree((SectionInfo + i)->KeyInfo);
	}
	LocalFree(SectionInfo);
	SectionInfo = NULL;
	SectionCnt = 0;
	SectionAllocCnt = 0;
}


/******************************************************************************

	Profile_GetString

	������̎擾

******************************************************************************/

long Profile_GetString(const wchar_t *Section, const wchar_t *Key, const wchar_t *Default, wchar_t *ret, const long size, const wchar_t *File)
{
	wchar_t *buf, *p;
	int SectionIndex;
	int KeyIndex;
	int len;

	//�Z�N�V�����̌���
	SectionIndex = FindSection(Section);
	if(SectionIndex == -1){
		wcscpyn(ret, Default, size);
		return wcslen(ret);
	}

	//�L�[�̌���
	KeyIndex = FindKey((SectionInfo + SectionIndex), Key);
	if(KeyIndex == -1 || ((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String == NULL){
		wcscpyn(ret, Default, size);
		return wcslen(ret);
	}

	//���e�̎擾
	buf = (wchar_t *)LocalAlloc(LMEM_FIXED, sizeof(wchar_t) * (wcslen(((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String) + 1));
	if(buf != NULL){
		wcscpy(buf, ((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String);
		Trim(buf);
		p = (*buf == TEXT('\"')) ? buf + 1 : buf;
		len = wcslen(p);
		if(len > 0){
			if(*(p + len - 1) == TEXT('\"')) *(p + len - 1) = TEXT('\0');
		}
		wcscpyn(ret, p, size);
		LocalFree(buf);
	}else{
		wcscpyn(ret, ((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String, size);
	}
	return wcslen(ret);
}


/******************************************************************************

	Profile_GetInt

	���l�̎擾

******************************************************************************/

int Profile_GetInt(const wchar_t *Section, const wchar_t *Key, const int Default, const wchar_t *File)
{
	wchar_t *buf, *p;
	int SectionIndex;
	int KeyIndex;
	int ret;
	int len;

	//�Z�N�V�����̌���
	SectionIndex = FindSection(Section);
	if(SectionIndex == -1){
		return Default;
	}

	//�L�[�̌���
	KeyIndex = FindKey((SectionInfo + SectionIndex), Key);
	if(KeyIndex == -1 || ((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String == NULL){
		return Default;
	}

	//���e�̎擾
	buf = (wchar_t *)LocalAlloc(LMEM_FIXED, sizeof(wchar_t) * (wcslen(((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String) + 1));
	if(buf != NULL){
		wcscpy(buf, ((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String);
		Trim(buf);
		p = (*buf == TEXT('\"')) ? buf + 1 : buf;
		len = wcslen(p);
		if(len > 0){
			if(*(p + len - 1) == TEXT('\"')) *(p + len - 1) = TEXT('\0');
		}
		ret = a2i(p);
		LocalFree(buf);
	}else{
		ret = a2i(((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String);
	}
	return ret;
}


/******************************************************************************

	Profile_WriteData

	�f�[�^�̏�������

******************************************************************************/

static BOOL Profile_WriteData(const wchar_t *Section, const wchar_t *Key, const wchar_t *str, const wchar_t *File)
{
	int SectionIndex;
	int KeyIndex;
	int j;

	if(Section == NULL){
		return FALSE;
	}

	if(SectionInfo == NULL){
		//�Z�N�V�����̊m��
		SectionInfo = (SECTION_INFO *)LocalAlloc(LPTR, sizeof(SECTION_INFO) * ALLOC_CNT);
		if(SectionInfo == NULL){
			return FALSE;
		}
		SectionCnt = 1;
		SectionAllocCnt = ALLOC_CNT;
	}

	//�Z�N�V�����̌���
	SectionIndex = FindSection(Section);
	if(SectionIndex == -1){
		//�Z�N�V�����̒ǉ�
		if(AddSection(Section) == FALSE){
			return FALSE;
		}
		SectionIndex = SectionCnt - 1;
	}

	if(Key == NULL){
		if((SectionInfo + SectionIndex)->KeyInfo != NULL){
			//�L�[�̍폜
			for(j = 0; j < (SectionInfo + SectionIndex)->KeyCnt; j++){
				if(((SectionInfo + SectionIndex)->KeyInfo + j)->String != NULL){
					LocalFree(((SectionInfo + SectionIndex)->KeyInfo + j)->String);
				}
			}
			LocalFree((SectionInfo + SectionIndex)->KeyInfo);
			(SectionInfo + SectionIndex)->KeyInfo = NULL;
			(SectionInfo + SectionIndex)->KeyCnt = 0;
			(SectionInfo + SectionIndex)->KeyAllocCnt = 0;
		}
		return TRUE;
	}

	//�L�[�̌���
	KeyIndex = FindKey((SectionInfo + SectionIndex), Key);
	if(KeyIndex == -1){
		//�L�[�̒ǉ�
		return AddKey((SectionInfo + SectionIndex), Key, str, FALSE);
	}else{
		//���e�̕ύX
		if(((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String != NULL){
			LocalFree(((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String);
		}
		if(str == NULL){
			*((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->KeyName = TEXT('\0');
			((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String = NULL;
			return TRUE;
		}
		((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String = (wchar_t *)LocalAlloc(LMEM_FIXED, sizeof(wchar_t) * (wcslen(str) + 1));
		if(((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String == NULL){
			return FALSE;
		}
		wcscpy(((SectionInfo + SectionIndex)->KeyInfo + KeyIndex)->String, str);
	}
	return TRUE;
}


/******************************************************************************

	Profile_WriteString

	������̏�������

******************************************************************************/

BOOL Profile_WriteString(const wchar_t *Section, const wchar_t *Key, const wchar_t *str, const wchar_t *File)
{
	wchar_t *buf, *p;
	BOOL ret;

	if(str == NULL || *str == TEXT('\0')){
		return Profile_WriteData(Section, Key, TEXT(L""), File);
	}

	buf = (wchar_t *)LocalAlloc(LMEM_FIXED, sizeof(wchar_t) * (wcslen(str) + 3));
	if(buf == NULL){
		return Profile_WriteData(Section, Key, str, File);
	}
	p = StrCpy_Profile(buf, TEXT(L"\""));
	p = StrCpy_Profile(p, str);
	p = StrCpy_Profile(p, TEXT(L"\""));
	ret = Profile_WriteData(Section, Key, buf, File);
	LocalFree(buf);
	return ret;
}


/******************************************************************************

	Profile_WriteInt

	���l�̏�������

******************************************************************************/

BOOL Profile_WriteInt(const wchar_t *Section, const wchar_t *Key, const int num, const wchar_t *File)
{
	wchar_t ret[BUF_SIZE];

	wsprintf(ret, TEXT(L"%d"), num);
	return Profile_WriteData(Section, Key, ret, File);
}
/* End of source */

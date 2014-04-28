/**************************************************************************

	Profile.h

	(C) Copyright 1996-2002 By Tomoaki Nakashima. All right reserved.
		http://www.nakka.com/
		nakka@nakka.com

**************************************************************************/

#ifndef _INC_PROFILE_H
#define _INC_PROFILE_H

/**************************************************************************
	Include Files
**************************************************************************/

/**************************************************************************
	Define
**************************************************************************/

/**************************************************************************
	Global Variables
**************************************************************************/

/**************************************************************************
	Struct
**************************************************************************/

/**************************************************************************
	Function Prototypes
**************************************************************************/

BOOL Profile_Initialize(const wchar_t *path, const BOOL ReadFlag);
BOOL Profile_Flush(const wchar_t *path);
void Profile_Free(void);
long Profile_GetString(const wchar_t *Section, const wchar_t *Key, const wchar_t *Default, wchar_t *ret, const long size, const wchar_t *File);
int Profile_GetInt(const wchar_t *Section, const wchar_t *Key, const int Default, const wchar_t *File);
BOOL Profile_WriteString(const wchar_t *Section, const wchar_t *Key, const wchar_t *str, const wchar_t *File);
BOOL Profile_WriteInt(const wchar_t *Section, const wchar_t *Key, const int num, const wchar_t *File);

#endif
/* End of source */

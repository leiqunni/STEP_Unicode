#ifndef __REGEXP_H__
#define __REGEXP_H__

////////////////////////////////////////////////////////////////////////
// RegExp.h
//
// This code has been derived from work by Henry Spencer. 
// The main changes are
// 1. All char variables and functions have been changed to wchar_t
//    counterparts
// 2. Added GetFindLen() & GetReplaceString() to enable search
//    and replace operations.
// 3. And of course, added the C++ Wrapper
//
// The original copyright notice follows:
//
// Copyright (c) 1986, 1993, 1995 by University of Toronto.
// Written by Henry Spencer.  Not derived from licensed software.
//
// Permission is granted to anyone to use this software for any
// purpose on any computer system, and to redistribute it in any way,
// subject to the following restrictions:
//
// 1. The author is not responsible for the consequences of use of
// this software, no matter how awful, even if they arise
// from defects in it.
//
// 2. The origin of this software must not be misrepresented, either
// by explicit claim or by omission.
//
// 3. Altered versions must be plainly marked as such, and must not
// be misrepresented (by explicit claim or omission) as being
// the original software.
//
// 4. This notice must not be removed or altered.
/////////////////////////////////////////////////////////////////////////////

#define NSUBEXP  10


class CRegExp
{
public:
	CRegExp();
	~CRegExp();

	CRegExp *RegComp( const wchar_t *re );
	int RegFind(const wchar_t *str);
	wchar_t* GetReplaceString( const wchar_t* sReplaceExp );
	int GetFindLen()
	{
		if( startp[0] == NULL || endp[0] == NULL )
			return 0;

		return endp[0] - startp[0];
	}


private:
	wchar_t *regnext(wchar_t *node);
	void reginsert(wchar_t op, wchar_t *opnd);

	int regtry(wchar_t *string);
	int regmatch(wchar_t *prog);
	size_t regrepeat(wchar_t *node);
	wchar_t *reg(int paren, int *flagp);
	wchar_t *regbranch(int *flagp);
	void regtail(wchar_t *p, wchar_t *val);
	void regoptail(wchar_t *p, wchar_t *val);
	wchar_t *regpiece(int *flagp);
	wchar_t *regatom(int *flagp);

	// Inline functions
private:
	wchar_t OP(wchar_t *p) {return *p;};
	wchar_t *OPERAND( wchar_t *p) {return (wchar_t*)((short *)(p+1)+1); };

	// regc - emit (if appropriate) a byte of code
	void regc(wchar_t b)
	{
		if (bEmitCode)
			*regcode++ = b;
		else
			regsize++;
	};

	// regnode - emit a node
	wchar_t *	regnode(wchar_t op)
	{
		if (!bEmitCode) {
			regsize += 3;
			return regcode;
		}

		*regcode++ = op;
		*regcode++ = _T('\0');		/* Null next pointer. */
		*regcode++ = _T('\0');

		return regcode-3;
	};


private:
	BOOL bEmitCode;
	BOOL bCompiled;
	wchar_t *sFoundText;

	wchar_t *startp[NSUBEXP];
	wchar_t *endp[NSUBEXP];
	wchar_t regstart;		// Internal use only. 
	wchar_t reganch;		// Internal use only. 
	wchar_t *regmust;		// Internal use only. 
	int regmlen;		// Internal use only. 
	wchar_t *program;		// Unwarranted chumminess with compiler. 

	wchar_t *regparse;	// Input-scan pointer. 
	int regnpar;		// () count. 
	wchar_t *regcode;		// Code-emit pointer; Rdummy = don't. 
	wchar_t regdummy[3];	// NOTHING, 0 next ptr 
	long regsize;		// Code size. 

	wchar_t *reginput;	// String-input pointer. 
	wchar_t *regbol;		// Beginning of input, for ^ check. 
};

#endif


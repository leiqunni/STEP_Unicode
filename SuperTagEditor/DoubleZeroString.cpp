// DoubleZeroString.cpp: implementation of the CDoubleZeroString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DoubleZeroString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDoubleZeroString::CDoubleZeroString()
:	m_buf(NULL)
{
	m_ar.SetSize(0, 16);
	Empty();
}

CDoubleZeroString::~CDoubleZeroString()
{
	Empty();
}

void CDoubleZeroString::Empty()
{
	m_ar.RemoveAll();
	m_ar.FreeExtra();

	delete[]	m_buf;
	m_buf	=	NULL;
}

bool CDoubleZeroString::Add(const wchar_t* str)
{
	ASSERT(str!=NULL);
	try
	{
		m_ar.Add(str);
	}
	catch(CMemoryException* ex)
	{
		ex->Delete();
		return	false;
	}
	return	true;
}

bool CDoubleZeroString::AddDoubleZero(const wchar_t * dzstring)
{
	ASSERT(dzstring!=NULL);
	const wchar_t*	p	=	dzstring;

	while(*p)
	{
		if(Add(p)==false)
			return	false;
		p	+=	(wcslen(p) + 1);
	}
	return	true;
}

int CDoubleZeroString::GetCount() const
{
	return	m_ar.GetSize();
}

CDoubleZeroString::operator const wchar_t*()
{
	delete[]	m_buf;
	m_buf	=	NULL;
		//	calculate the required buffer length
	size_t	tlen(0);
	if(m_ar.GetSize()>0)
	{
		int i; for(i=0;i<m_ar.GetSize();i++)
			tlen+=	(m_ar[i].GetLength() + 1); // add 1 for the normal zeroterm.
	}
	else
		tlen=1;
	tlen++;	//	for the double zeroterminator

	m_buf = new	wchar_t[tlen];
	ASSERT(m_buf!=NULL);
	ZeroMemory(m_buf, tlen);
	wchar_t* p = m_buf;
	int i; for(i=0;i<m_ar.GetSize();i++)
	{
		wcscpy(p, m_ar[i]);
		p+= (m_ar[i].GetLength() + 1);
	}

	return	m_buf;
}

const wchar_t* CDoubleZeroString::Get(int index)
{
		// assert on debug builds when index is out of bounds
	ASSERT(index>=0&&index<=m_ar.GetSize());
	if(index<0||index>=m_ar.GetSize())
		return	NULL;
	else
		return	m_ar[index];
}

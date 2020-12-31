#include "pch.h"
#include "CWinAPIFileW.h"

constexpr LARGE_INTEGER zero = { 0 };

CWinAPIFileW::CWinAPIFileW()
{

}



CWinAPIFileW::~CWinAPIFileW()
{
	if (this->m_hFile != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(this->m_hFile);
	} 
}

bool CWinAPIFileW::OpenForWriting(wchar_t* name)
{
	this->Close();
	this->m_hFile = CreateFileW(name, GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (this->m_hFile != INVALID_HANDLE_VALUE)
	{
		return true;
	}
	return false;
}

void CWinAPIFileW::WriteInAppend(const char* src, size_t len)
{
	if (::SetFilePointerEx(this->m_hFile, zero, NULL, FILE_END))
	/* If the function succeeds, the return value is nonzero. */
	{
		::WriteFile(this->m_hFile, src, len, &m_byteswriten, NULL);
	} 

}

bool CWinAPIFileW::OpenForReading(wchar_t* name)
{
	this->Close();
	this->m_hFile = CreateFileW(name, GENERIC_READ, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (this->m_hFile != INVALID_HANDLE_VALUE)
	{
		return true;
	}
	return false;
}

void CWinAPIFileW::ReadFrom(char* dst, size_t len)
{
	::ReadFile(this->m_hFile, dst, len, &m_bytesread, NULL);

}

void CWinAPIFileW::Truncate(wchar_t* name)
{
	this->Close();
	this->m_hFile = CreateFileW(name, GENERIC_READ | GENERIC_WRITE, 0, NULL,
		TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	this->Close();
}

bool CWinAPIFileW::IsFileExist(wchar_t* name) const
{
	HANDLE DummyBoi = INVALID_HANDLE_VALUE;
	DummyBoi = CreateFileW(name, 0, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (DummyBoi != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(DummyBoi);
		return true;
	}
	return false;
}

void CWinAPIFileW::Close()
{
	if (this->m_hFile != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(this->m_hFile);
	}
}

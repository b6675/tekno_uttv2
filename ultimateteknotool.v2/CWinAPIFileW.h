#pragma once
#include <windows.h>
#include "debugconsole.h"

class CWinAPIFileW
{
private:
	//static constexpr unsigned short MAX_LENOFNAME = 64;
	//wchar_t m_wsName[MAX_LENOFNAME] = { 0 };
	HANDLE m_hFile = INVALID_HANDLE_VALUE;
	DWORD m_byteswriten = 0;
	DWORD m_bytesread = 0;
public:
	CWinAPIFileW();
	~CWinAPIFileW();
	bool OpenForWriting(wchar_t* name);
	void WriteInAppend(const char* src, size_t len);
	bool OpenForReading(wchar_t* name);
	void ReadFrom(char* dst, size_t len);
	void Truncate(wchar_t* name);
	bool IsFileExist(wchar_t* name) const;
	void Close();
};


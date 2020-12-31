#pragma once
	#include <iostream>
	#include <fstream>
#include <memory>
#include <mutex>
#include <windows.h>
#define NOUTT2_DEBUG

#ifdef UTT2_DEBUG
class WinConsoleW
{
private:
	static std::wofstream m_woutstream;
	WinConsoleW();
	static std::once_flag m_createonceflag;
	static std::unique_ptr<WinConsoleW> m_pInstance;
	WinConsoleW(const WinConsoleW&) = delete;
	WinConsoleW(WinConsoleW&&) = delete;
	WinConsoleW& operator=(const WinConsoleW&) = delete;
	WinConsoleW& operator=(WinConsoleW&&) = delete;
public:
	~WinConsoleW();
	static WinConsoleW& Console();
	void print() {
		std::wcout << std::endl;
	}
	template <typename T> void print(const T& t) {
		std::wcout << t << std::endl;
	}
	template <typename First, typename... Rest> void print(const First& first, const Rest&... rest) {
		std::wcout << first;
		print(rest...); // recursive call using pack expansion syntax
	}

};
#endif

#ifdef UTT2_DEBUG
#define WCWOUT WinConsoleW::Console().print
#else
#define WCWOUT //WinConsoleW::Console().print
#endif

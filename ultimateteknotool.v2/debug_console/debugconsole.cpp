#include "pch.h"
#include "debugconsole.h"

#ifdef UTT2_DEBUG
 std::once_flag WinConsoleW::m_createonceflag;
 std::unique_ptr<WinConsoleW> WinConsoleW::m_pInstance;
 std::wofstream WinConsoleW::m_woutstream;

WinConsoleW::WinConsoleW()
{
    if (::AllocConsole() == TRUE)
    {
        this->m_woutstream.open("CONOUT$", std::wofstream::out);
        std::wcout.rdbuf(this->m_woutstream.rdbuf());
    }
    else
    {
        if (::AttachConsole(::GetCurrentProcessId()))
        {
            this->m_woutstream.open("CONOUT$", std::wofstream::out);
            std::wcout.rdbuf(this->m_woutstream.rdbuf());
        }
    }
}

WinConsoleW& WinConsoleW::Console()
{
    std::call_once(WinConsoleW::m_createonceflag, [] {
        WinConsoleW::m_pInstance.reset(new WinConsoleW);
        });
    return *WinConsoleW::m_pInstance.get();
}

WinConsoleW::~WinConsoleW()
{
    ::FreeConsole();
}

#endif
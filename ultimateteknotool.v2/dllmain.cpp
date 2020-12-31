#include "pch.h"
#include "ProcessController.h"
#include "TheWinMain.h"
#include "iw5mp_addresses_definition.h"
#include "iw5mp_functions_definition.h"
#include "cfg_functions.h"
#include "HooksAfterResumingThreads.h"
#include "HooksOnThreadsStart.h"
#include "debugconsole.h"
#include "debug_hooks.h"


DWORD WINAPI EntryPoint(LPVOID _arguments)
{
    UNREFERENCED_PARAMETER(_arguments);
    WCWOUT(L"debug ", L"string ", 123);
    WCWOUT(L"debug ", L"debug  ", 123);
    bool failed = true;
   
    ProcessController::SuspendThreads(true);
    if (iw5mp_functions_definition::DefineAndVerify() == true) { failed = false; }
    if (failed == false)
    {
        failed = !hooks_on_threads_start::Hook();
#ifdef UTT2_DEBUG
        hooks::DEBUG_HOOKS();
#endif
        cfg_functions::LoadCfgPreCreateWinInFile();
    }
    /* we suspend all threads to prevent any data transaction to masterserver before we hook socket and other stuff */
    ProcessController::SuspendThreads(false);
    if (failed == true)
    {
        return ERROR_POSSIBLE_DEADLOCK;
    }
    //Sleep(10000);
    if (hooks_after_resuming_threads::Hook() == false)
    {
        return ERROR_POSSIBLE_DEADLOCK;
    }
   
    iw5mp_addresses_definition::DefineAddresses_PatternSearching();
    
    if (windowsMain::WinStart())
    {
            // we really gonna kill iw5mp game via windows functions? we are mad
            // ... windows method via procid (weri smart way)
            // ::SendMessage(FindMainProcHWND(), WM_CLOSE, 0, 0);
        ::SendMessage(*(HWND*)0x05A86AF0, WM_CLOSE, 0, 0); 
    }
    return ERROR_POSSIBLE_DEADLOCK;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{

    UNREFERENCED_PARAMETER(hModule);
    UNREFERENCED_PARAMETER(lpReserved);
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        ::CreateThread(0, 0, static_cast<LPTHREAD_START_ROUTINE>(EntryPoint), 0, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        
        break;
    }
    return TRUE;
}


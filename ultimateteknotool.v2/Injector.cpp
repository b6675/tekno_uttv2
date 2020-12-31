#include "pch.h"
#include "Injector.h"

 std::unique_ptr<Injector> Injector::m_pInst;
 std::once_flag Injector::m_Initflag;

//void Injector::OverwriteTargetLibName(const char* target_lib_ASCII_nullterminated_string, const char* injecting_this)
// {
//     // src: http://dronesec.pw/blog/2017/09/19/abusing-delay-load-dll/
//    /* 
//    defined in winnt.h
//    typedef struct _IMAGE_DELAYLOAD_DESCRIPTOR {
//    union {
//        DWORD AllAttributes;
//        struct {
//            DWORD RvaBased : 1;             // Delay load version 2
//            DWORD ReservedAttributes : 31;
//        } DUMMYSTRUCTNAME;
//    } Attributes;
//
//    DWORD DllNameRVA;                       // RVA to the name of the target library (NULL-terminate ASCII string)
//    DWORD ModuleHandleRVA;                  // RVA to the HMODULE caching location (PHMODULE)
//    DWORD ImportAddressTableRVA;            // RVA to the start of the IAT (PIMAGE_THUNK_DATA)
//    DWORD ImportNameTableRVA;               // RVA to the start of the name table (PIMAGE_THUNK_DATA::AddressOfData)
//    DWORD BoundImportAddressTableRVA;       // RVA to an optional bound IAT
//    DWORD UnloadInformationTableRVA;        // RVA to an optional unload info table
//    DWORD TimeDateStamp;                    // 0 if not bound,
//                                            // Otherwise, date/time of the target DLL
//
//    } IMAGE_DELAYLOAD_DESCRIPTOR, *PIMAGE_DELAYLOAD_DESCRIPTOR;
//    */
//     PIMAGE_DOS_HEADER pImgDos = (PIMAGE_DOS_HEADER)GetModuleHandle(NULL);
//     PIMAGE_NT_HEADERS pImgNt = (PIMAGE_NT_HEADERS)((LPBYTE)pImgDos + pImgDos->e_lfanew);
//     PIMAGE_DELAYLOAD_DESCRIPTOR pImgDelay =
//         (PIMAGE_DELAYLOAD_DESCRIPTOR)((LPBYTE)pImgDos + pImgNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress);
//     DWORD dwBaseAddr = (DWORD)GetModuleHandle(NULL);
//     DWORD dwOldProtect = 0;
//     SIZE_T wBytes = 0;
//     for (IMAGE_DELAYLOAD_DESCRIPTOR* entry = pImgDelay; entry->ImportAddressTableRVA != NULL; entry++) {
//         char* _cDllName = (char*)(dwBaseAddr + entry->DllNameRVA);
//         if (::strcmp(_cDllName, target_lib_ASCII_nullterminated_string) == 0) {
//             DWORD dwEntryAddr = (DWORD)((DWORD)GetModuleHandle(NULL) + entry->DllNameRVA);
//             VirtualProtect((LPVOID)dwEntryAddr, sizeof(DWORD), PAGE_READWRITE, &dwOldProtect);
//             WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwEntryAddr, (LPVOID)injecting_this, strlen(injecting_this), &wBytes);
//             VirtualProtect((LPVOID)dwEntryAddr, sizeof(DWORD), dwOldProtect, &dwOldProtect);
//             return;
//         }
//     }
//     return;
// }

 Injector& Injector::Inject0r()
{
    std::call_once(m_Initflag, []()
        {
            m_pInst.reset(new Injector); // straight calling default constructor
        });
    return *m_pInst.get();
}




 bool Injector::APC_Inject(const std::wstring& dll_path)
 {
	 HANDLE CurrentProcess = 0;
	 CurrentProcess = ::GetCurrentProcess();
	 SIZE_T StringSizeInBytes = (dll_path.size() + 4) * sizeof(decltype(dll_path[0]));
	 if (CurrentProcess == 0) return false;
	 else
	 {
		 LPVOID pThreadData = 0;
		 pThreadData = VirtualAllocEx(CurrentProcess, NULL, StringSizeInBytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		 if (pThreadData == 0)
		 {
			 ::CloseHandle(CurrentProcess);
			 return false;
		 }
		 else
		 {
			 if (!WriteProcessMemory(CurrentProcess, pThreadData, (LPCVOID)dll_path.c_str(), StringSizeInBytes, NULL))
			 {
				 ::CloseHandle(CurrentProcess);
				 return false;
			 }
			 else
			 {
				 LPTHREAD_START_ROUTINE LoadLibraryAddress = 0;
				 HMODULE Kernel32Module = ::GetModuleHandleW(L"Kernel32");
				 if (Kernel32Module == 0)
				 {
					 ::CloseHandle(CurrentProcess);
					 return false;
				 }
				 else {
					 LoadLibraryAddress = (LPTHREAD_START_ROUTINE)::GetProcAddress(Kernel32Module, "LoadLibraryW");
					 if (LoadLibraryAddress == 0)
					 {
						 ::CloseHandle(CurrentProcess);
						 return false;
					 }
					 else {
						 HANDLE hThread = 0;
						 hThread = ::CreateRemoteThread(CurrentProcess, NULL, 0, LoadLibraryAddress, pThreadData, 0, NULL);
						 if (hThread == 0) {
							 ::CloseHandle(CurrentProcess);
							 return false;
						 }
						 else {
							 WaitForSingleObject(hThread, INFINITE);
							 ::CloseHandle(hThread);
							 ::CloseHandle(CurrentProcess);
							 return true;
						 }
					 }
				 }
			 }
		 }
	 }
 }

 bool Injector::APC_FreeDll(const std::wstring& dll_path)
 {

	 return false;
 }

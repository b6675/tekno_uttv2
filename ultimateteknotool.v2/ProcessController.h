#pragma once
#include <windows.h>
#include <tlhelp32.h>


namespace ProcessController
{
	/* following Raymond, 2006 microsoft devblog */
	void SuspendThreads(bool suspend)
	{
		DWORD ProcId = 0;
		DWORD ThreadId = 0;
		ProcId = ::GetCurrentProcessId();
		ThreadId = ::GetCurrentThreadId();
		HANDLE snapthreads = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (snapthreads == INVALID_HANDLE_VALUE) { return; }
		else
		{
			THREADENTRY32 threadentry = { 0 };
			threadentry.dwSize = sizeof(THREADENTRY32);
			if (::Thread32First(snapthreads, &threadentry) == TRUE)
			{
				HANDLE threadhandle = NULL;
				do
				{
					if (threadentry.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) +
						sizeof(threadentry.th32OwnerProcessID))
					{
						if (threadentry.th32OwnerProcessID == ProcId) {
							if (threadentry.th32ThreadID == ThreadId) {}
							else {
								threadhandle = ::OpenThread(THREAD_ALL_ACCESS, FALSE, threadentry.th32ThreadID);
								if (threadhandle != NULL && threadhandle != INVALID_HANDLE_VALUE)
								{
									if (suspend) { ::SuspendThread(threadhandle); }
									else { ::ResumeThread(threadhandle); }
									::CloseHandle(threadhandle);
								}
							}
						}
					}
					threadentry.dwSize = sizeof(threadentry);
				}
				while (::Thread32Next(snapthreads, &threadentry));
			}
			::CloseHandle(snapthreads);
		}
	}
	
};
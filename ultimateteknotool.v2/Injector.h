#pragma once
//#include <thread>
#include <mutex>
#include <memory>
#include <libloaderapi.h>

// must be singleton
class Injector
{
private:
	static std::unique_ptr<Injector> m_pInst;
	static std::once_flag m_Initflag;
	Injector() = default;

	Injector(const Injector&) = delete;
	Injector(Injector&&) = delete;
	Injector& operator=(const Injector&) = delete;
	Injector& operator=(Injector&&) = delete;

	bool VerifyInject(const std::wstring& dll_path);
	//[[deprecated]] void OverwriteTargetLibName(const char*, const char*);
public:
	~Injector() = default;
	static Injector& Inject0r();
	bool APC_Inject(const std::wstring& dll_path);
	bool APC_FreeDll(const std::wstring& dll_path);
};


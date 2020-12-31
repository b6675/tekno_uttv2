#include "pch.h"
#include "debug_hooks.h"
#include <sstream>
#include "Randomizer.h"
#include "windows_playerspage.h"

constexpr	static uint16_t bufferSIZE = 512;
static char buffer[bufferSIZE] = { 0 };
static char* v8;
static char v12[bufferSIZE] = { 0 };

void LogMessage(int a1, const char* a2, const char* a3, const char* a4, const char* a5, int a6, const char* a7, ...)
{
	va_list va;
	va_list ArgList;
	va_start(va, a7);
	::memset(buffer, 0, bufferSIZE);
	int vpret = 0;
	vpret = ::vprintf(a7, va);
	ArgList = va;
	_vsnprintf_s(buffer, bufferSIZE, 0xFFFFFFFF, a7, ArgList);
	if (vpret >= bufferSIZE)
	{
		WCWOUT("MsgTruncated");
	}
	ArgList = 0;
	v8 = (char*)a2;
	if (a2 && a3)
	{
		if (snprintf(v12, 0x100, "%s%s", a2, a3) >= bufferSIZE)
		{
			LogMessage(1, "warn", "bdPlatformLog", "[junk]", "LogMessage", 251, "Channel name truncated: %s%s.", 0);
		}
		v8 = v12;
	}
	WCWOUT(L'[', v8, L']', buffer, L' ');
}

typedef void(__cdecl* Dummy_bdLogMessage_t)();
Dummy_bdLogMessage_t Dummy = nullptr;


static std::wstringstream sstream;
static std::wstringstream sstreamdechex;
void PrintData_Text(uint8_t* src, size_t sz)
{
	sstream.clear();
	sstream.str(L"");
	for (uint32_t i = 0; i < sz; i++)
	{
		//if (src[i] == 0)
		//{
		//	sstream << "<end>";
		//	//break;
		//}
		sstream << (char)src[i];

	}
}

void PrintData_Dec(uint8_t* src, size_t sz)
{
	sstreamdechex.clear();
	sstreamdechex.str(L"");
	for (uint32_t i = 0; i < sz; i++)
	{
		sstreamdechex << std::dec << (uint32_t)src[i] << L'.';

	}
}

void PrintData_Text2(uint8_t* src, size_t sz)
{
	sstream.clear();
	sstream.str(L"");
	for (uint32_t i = 0; i < sz; i++)
	{
		//if (src[i] == 0)
		//{
		//	sstream << "<end>";
		//	//break;
		//}
		sstream << (char)(src[i] ^ '1');

	}
}

void RandomiseData(uint8_t* src, size_t sz)
{
	for (uint32_t i = 0; i < sz; i++)
	{
		src[i] = src[i] ^ (RANDBYTE & 0x000000FF);
	}
}

void RandomiseData2(uint8_t* src, size_t sz)
{
	for (uint32_t i = 0; i < sz; i++)
	{
		if (src[i] != 49) { src[i] = src[i] ^ (RANDBYTE & 0x000000FF); }
	}
}

typedef int(__cdecl* bdPlatformSocket_sendTo_t)(uint8_t* socket, uint32_t a2, uint16_t a3, uint8_t* buf, uint32_t len);
static bdPlatformSocket_sendTo_t Original_bdPlatformSocket_sendTo = nullptr;
typedef int(__cdecl* bdPlatformSocket_receiveFrom_t)(uint8_t* socket, int ip, int port, uint8_t* buf, uint32_t len);
static  bdPlatformSocket_receiveFrom_t Original_bdPlatformSocket_receiveFrom = nullptr;
typedef int(__thiscall* bdDTLSAssociation_sendData_t)(void* _this, uint32_t a2, uint8_t* a3, uint32_t a4, uint32_t a5);
bdDTLSAssociation_sendData_t Original_bdDTLSAssociation_sendData = nullptr;

int __cdecl HOOK_bdPlatformSocket_sendTo(uint8_t* socket, uint32_t ip, uint16_t port, uint8_t* buf, uint32_t len);
int __cdecl HOOK_bdPlatformSocket_receiveFrom(uint8_t* socket, int ip, int port, uint8_t* buf, uint32_t len);

int __cdecl HOOK_bdPlatformSocket_sendTo(uint8_t* socket, uint32_t ip, uint16_t port, uint8_t* buf, uint32_t len)
{

	return Original_bdPlatformSocket_sendTo(socket, ip, port, buf, len);
}

int __cdecl HOOK_bdPlatformSocket_receiveFrom(uint8_t* socket, int ip, int port, uint8_t* buf, uint32_t len)
{
	int ret;
	//std::cout << "[recv]: ";
	//PrintData_Text(buf, len);
	ret = Original_bdPlatformSocket_receiveFrom(socket, ip, port, buf, len);
	return ret;
}

typedef char(__thiscall* bdUPnPDevice_extractData_t)(void* th1s);
bdUPnPDevice_extractData_t original_bdUPnPDevice_extractData;
char __fastcall bdUPnPDevice_extractData(uint8_t* th1s, void* deadboi) 
{
	std::cout << "bdUPnPDevice_extractData: ";
	
	return original_bdUPnPDevice_extractData(th1s);
}

typedef void(__thiscall* bdUPnPDevice_pump_t)(DWORD* th1s);
bdUPnPDevice_pump_t original_bdUPnPDevice_pump;
void __fastcall bdUPnPDevice_pump(DWORD* th1s, DWORD edx)
{
	std::cout << "bdUPnPDevice_pump->state: " << *th1s << '\n';
	original_bdUPnPDevice_pump(th1s);
}

typedef char(__thiscall* bdUPnP_extractDeviceInfo_t)(void* th1s, int a2, char** a3, DWORD* a4);
bdUPnP_extractDeviceInfo_t original_bdUPnP_extractDeviceInfo;
char __fastcall bdUPnP_extractDeviceInfo(uint8_t* th1s, void* deadboi, int a2, char** a3, DWORD* a4)
{
	std::cout << "bdUPnPDevice_extractData: ";
	PrintData_Text(th1s, 0x200);
	return original_bdUPnP_extractDeviceInfo(th1s, a2, a3, a4);
}

typedef int (__cdecl* vsnprintf_8x8x8x8x_t)(DWORD* a1, char* a2, size_t a3);
vsnprintf_8x8x8x8x_t orig_vsnprintf_8x8x8x8x;
int __cdecl vsnprintf_8x8x8x8x(DWORD* a1, char* a2, size_t a3)
{
	int ret = orig_vsnprintf_8x8x8x8x(a1, a2, a3);
	PrintData_Text((uint8_t*)a2, a3);
	WCWOUT(L"[vsnprintf_8x8x8x8x]: ", sstream.str());
	return ret;
}

struct NetDataStructure
{
	DWORD netadresstype;
	DWORD dw_ip;
	DWORD dw_port;
	DWORD field_C;
	DWORD field_10;
	DWORD index;
};

struct unkstruct64
{
	DWORD isValid;
	DWORD field_4;
	DWORD xuid_part1;
	DWORD xuid_part2;
	DWORD field_10;
	NetDataStructure pNDS;
	DWORD v[5];
};

static_assert(sizeof(unkstruct64) == 64, "not 64");

struct gameSession_struct
{
	uint8_t bytes[58];
	unkstruct64 unk64x18[18];
	uint32_t field_4D8;
	uint32_t field_4DC;
	uint32_t field_4E0;
	uint32_t field_4E4;
	uint32_t field_4E8;
};

typedef void(__cdecl* sub_4D9E40_t)(gameSession_struct* a1, int a2);
sub_4D9E40_t sub_4D9E40_orig;
void __cdecl hook_sub_4D9E40(gameSession_struct* a1, int a2)
{
	sub_4D9E40_orig(a1, a2);
	WCWOUT("hook_sub_4D9E40 has been called");
	/* called very rare idk what s this */
}


typedef bool(__cdecl* doSmthWithNetData_pSrcHasLocalIpEtc_t)(void* a1, DWORD* a2, WORD* port_value);
doSmthWithNetData_pSrcHasLocalIpEtc_t doSmthWithNetData_pSrcHasLocalIpEtc_orig;
bool __cdecl hook_doSmthWithNetData_pSrcHasLocalIpEtc_(void* a1, DWORD* a2, WORD* port_value)
{
	bool ret = false;
	ret = doSmthWithNetData_pSrcHasLocalIpEtc_orig(a1, a2, port_value);
	uint8_t* data = (uint8_t*)a2 - (sizeof(NetDataStructure) - sizeof(NetDataStructure::index));
	NetDataStructure* pNDS = reinterpret_cast<NetDataStructure*>(data);
	WCWOUT("PlayerNetData: ip->", std::dec, pNDS->dw_ip, " port->", pNDS->dw_port, " fC->", pNDS->field_C, " f10->", pNDS->field_10, " index->", pNDS->index);

	return ret;
}

constexpr uint8_t ASMOPCODE_NOP = 0x90;
struct AddrDescriptor
{
	uint32_t address = 0;
	uint8_t overwritebytes = 0; // we don't really want overwrite more than 255 bytes, I m sure
	constexpr AddrDescriptor(uint32_t addr, uint8_t ovr)
	{
		this->address = addr;
		this->overwritebytes = ovr;
	}
	AddrDescriptor() = delete;
	//AddrDescriptor(uint32_t addr, uint8_t ovr) = delete;
	~AddrDescriptor() = default;
	bool IwantKillMyself() const
	{
		DWORD restore = 0;
		uint8_t* pbyteAddr = reinterpret_cast<uint8_t*>(this->address);
		bool notFailed = false;
		notFailed = ::VirtualProtect((LPVOID)this->address, overwritebytes, PAGE_EXECUTE_READWRITE, &restore);
		if (notFailed) {
			for (decltype(overwritebytes) i = 0; i < overwritebytes; i++)
			{
				pbyteAddr[i] = ASMOPCODE_NOP;
			}
			::VirtualProtect((LPVOID)address, overwritebytes, restore, &restore);
		}
		return notFailed;
	}
};

constexpr AddrDescriptor cringeArray[] = { {0x49814F, 2}, {0x498156, 2}, {0x57858c, 2}, {0x429bd7, 3}, {0x4a93e4, 3}, {0x429c1d, 7}, {0x429c2c, 7} };

typedef int(__cdecl* GenerateHashIndex_t)(const char* a1);
GenerateHashIndex_t orig = (GenerateHashIndex_t)0x006484D0;
int __cdecl GenerateHashIndexHook(const char* a1)
{
	const char* inputstr = a1;
	uint16_t hashindex = 0;
	uint32_t key = 119; // 'w' char
	if (!inputstr)
	{
		return 0;
		//CRITICALERR_BEGIN "GenerateHashIndex called with nullptr arg" CRITICALERR_END;
	}
	while (*inputstr)
	{
		hashindex += ::tolower(*inputstr) * key;
		inputstr++; key++;
	}
	WCWOUT("[GenerateHashIndex] name: ", a1, " idx: ", std::hex, hashindex & 1023);
	return hashindex & 1023;

}

typedef uint16_t (__cdecl* ScriptString_IndexList_RegisterNewData_t)(void* pdata, int a2, uint32_t size);
ScriptString_IndexList_RegisterNewData_t ScriptString_IndexList_RegisterNewData_torgi;

typedef void(__cdecl* EnterCriticalSection_ByIndex_t)(int a1);
EnterCriticalSection_ByIndex_t EnterCriticalSection_ByIndex = (EnterCriticalSection_ByIndex_t)0x004D6310;
typedef void(__cdecl* LeaveCriticalSection_byIndex_t)(int a1);
LeaveCriticalSection_byIndex_t LeaveCriticalSection_byIndex = (LeaveCriticalSection_byIndex_t)0x004DCF40;
static uint32_t maxsize = 0;
unsigned __int16 __cdecl ScriptString_IndexList_RegisterNewData(void* pdata, int a2, uint32_t size)
{
	EnterCriticalSection_ByIndex(14);
	if (maxsize < size) {
		maxsize = size;
		WCWOUT("[ScriptString_IndexList_RegisterNewData] <start> size: ", std::dec, size, " <end>");
	}
	LeaveCriticalSection_byIndex(14);
	return ScriptString_IndexList_RegisterNewData_torgi(pdata, a2, size);
}


void hooks::DEBUG_HOOKS()
{
	//Hooker_JMP::Hook32<ScriptString_IndexList_RegisterNewData_t, decltype(ScriptString_IndexList_RegisterNewData)>(
	//	0x0042CD10,
	//	ScriptString_IndexList_RegisterNewData,
	//	7,
	//	ScriptString_IndexList_RegisterNewData_torgi);
	//for (size_t i = 0; i < (sizeof(cringeArray) / sizeof(AddrDescriptor)); i++)
	//{
	//	cringeArray[i].IwantKillMyself();
	//}
	//Hooker_JMP::Hook32<doSmthWithNetData_pSrcHasLocalIpEtc_t>(
	//	0x0044A4A0,
	//	reinterpret_cast<uint8_t*>(hook_doSmthWithNetData_pSrcHasLocalIpEtc_),
	//	7,
	//	doSmthWithNetData_pSrcHasLocalIpEtc_orig);



	// *(BYTE*)(0x006EA960) = 0xC3;
	//Hooker_JMP::Hook32<Dummy_bdLogMessage_t>(
	//	0x006EA960,
	//	reinterpret_cast<uint8_t*>(LogMessage),
	//	5,
	//	Dummy
	//	);
	//Hooker_JMP::Hook32<bdPlatformSocket_sendTo_t>(
	//	0x006EAD40,
	//	reinterpret_cast<uint8_t*>(HOOK_bdPlatformSocket_sendTo),
	//	6,
	//	Original_bdPlatformSocket_sendTo);
	//Hooker_JMP::Hook32<bdPlatformSocket_receiveFrom_t>(
	//	0x006EAEF0,
	//	reinterpret_cast<uint8_t*>(HOOK_bdPlatformSocket_receiveFrom),
	//	6,
	//	Original_bdPlatformSocket_receiveFrom);
	//Hooker_JMP::Hook32<bdUPnPDevice_extractData_t>(
	//	0x006D0BD0,
	//	reinterpret_cast<uint8_t*>(bdUPnPDevice_extractData),
	//	6,
	//	original_bdUPnPDevice_extractData);
	//Hooker_JMP::Hook32<bdUPnPDevice_pump_t>(
	//	0x006CF9B0,
	//	reinterpret_cast<uint8_t*>(bdUPnPDevice_pump),
	//	6,
	//	original_bdUPnPDevice_pump);
		//Hooker_JMP::Hook32<bdUPnP_extractDeviceInfo_t>(
		//	0x006CF310,
		//	reinterpret_cast<uint8_t*>(bdUPnP_extractDeviceInfo),
		//	6,
		//	original_bdUPnP_extractDeviceInfo);
	//Hooker_JMP::Hook32<vsnprintf_8x8x8x8x_t>(
	//	0x004BE5E0,
	//	reinterpret_cast<uint8_t*>(vsnprintf_8x8x8x8x),
	//	7,
	//	orig_vsnprintf_8x8x8x8x);
}

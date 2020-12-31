#include "pch.h"
#include <stdlib.h>
#include <vector>
#include "Hooker_JMP.h"


struct MallocNoob
{
	std::vector<void*> holders;
	MallocNoob()
	{

	}
	unsigned char* doalloc(const size_t sz)
	{
		void* retard = 0;
		retard = ::malloc(sz);
		holders.push_back(retard);
		return static_cast<unsigned char*>(retard);
	}
	~MallocNoob()
	{
		for (auto& x : this->holders)
		{
			if (x != 0)
			{
				::free(x);
			}
		}
	}
};

MallocNoob allocer;


typedef BOOL(WINAPI* sys_VirtualProtect_t)(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);

#pragma optimize("" ,off)
void* Hooker_JMP::__Hook32_internal__NativeHook(uint8_t* addr, uint8_t* hook, uint8_t len)
{
	DWORD oldProtectID;
	if (::VirtualProtect(addr, len, PAGE_READWRITE, &oldProtectID) == TRUE) 
	{
		uint32_t jumpto, newjump;
		unsigned char* jmp = 0;
		if (addr[0] == 0xE9)
		{
			
			jmp = allocer.doalloc(10);
			if (jmp == 0) { return nullptr; }
			jumpto = (*reinterpret_cast<uint32_t*>((addr + 1))) + (reinterpret_cast<uint32_t>(addr)) + 5;
			newjump = (jumpto - reinterpret_cast<uint32_t>(jmp + 5));
			jmp[0] = 0xE9;
			*reinterpret_cast<uint32_t*>((jmp + 1)) = newjump;
			jmp += 5;
			jmp[0] = 0xE9;
			*(reinterpret_cast<uint32_t*>((jmp + 1))) = reinterpret_cast<uint32_t>(reinterpret_cast<uint32_t*>((addr - jmp)));
		}
		else
		{
			jmp = allocer.doalloc(5+len);
			if (jmp == 0) { return nullptr; }
			::memcpy(jmp, addr, len);
			jmp += len;
			jmp[0] = 0xE9;
			*reinterpret_cast<uint32_t*>((jmp + 1)) = reinterpret_cast<uint32_t>(reinterpret_cast<uint32_t*>(addr + len - jmp)) - 5;
		}
		addr[0] = 0xE9;
		*reinterpret_cast<uint32_t*>((addr + 1)) = reinterpret_cast<uint32_t>(reinterpret_cast<uint32_t*>(hook - addr)) - 5;

		for (uint32_t i = 5; i < len; i++)
			addr[i] = 0x90;


		::VirtualProtect(addr, len, oldProtectID, &oldProtectID);
		return (jmp - len);
	}

	return nullptr;
}
#pragma optimize("" ,on)


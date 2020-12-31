#pragma once
#include <stdint.h>
#include "Hooker_JMP.h"
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")
#include "debugconsole.h"

namespace hooks
{
	namespace iphlpapi_functions
	{
		bool JMPHook_GetInterfaceInfo(uint32_t addr, uint8_t asmlen);
	};
};
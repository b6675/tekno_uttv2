#pragma once
#include <stdint.h>
#include "Hooker_JMP.h"
#include "debugconsole.h"

namespace hooks
{
	namespace sysinfoapi_functions
	{
		bool JMPHook_GetSystemFirmwareTable(uint32_t addr, uint8_t asmlen);
		void GetSystemFirmwareTable_SetState_GenerateNewData();
		void GetSystemFirmwareTable_SetState_FakingDataEnabled(const bool& state);
		void GetSystemFirmwareTable_SetState_AlwaysGenerateNewDataEnabled(const bool& state);
		void GetSystemFirmwareTable_SetState_RandomiseAllDataEnabled(const bool& state);
	};
};
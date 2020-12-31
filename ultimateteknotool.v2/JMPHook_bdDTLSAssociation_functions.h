#pragma once
#include <stdint.h>
#include "Hooker_JMP.h"
#include "windows_accountpage.h"

namespace hooks
{
	namespace bdDTLSAssociation_functions
	{
		bool JMPHook_sendInit(uint32_t addr, uint8_t asmlen);
	};
};
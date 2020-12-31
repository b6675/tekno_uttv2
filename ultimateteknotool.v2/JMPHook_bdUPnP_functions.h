#pragma once
#include <stdint.h>
#include "Hooker_JMP.h"
#include "windows_accountpage.h"
#include "TextConvertors.h"
#include "compiletime_XORstring.h"
#include "debugconsole.h"

namespace hooks
{
	namespace bdUPnP_functions
	{
		bool JMPHook_extractDeviceInfo(uint32_t addr, uint8_t asmlen);
		void SetDeviceInfo_location(const wchar_t* str);
		void SetDeviceInfo_server(const wchar_t* str);
		void SetDeviceInfo_USN(const wchar_t* str);
		void SetDeviceInfo();
		namespace ns_extractDeviceInfo
		{
			constexpr unsigned short maxtext_field_location = 36;
			constexpr unsigned short maxtext_field_server = 36;
			constexpr unsigned short maxtext_field_USN = 72;
			uint8_t* GetFirstRightEntry();
		};
		
	};
};
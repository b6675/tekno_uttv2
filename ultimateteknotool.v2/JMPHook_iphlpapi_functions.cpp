#include "pch.h"
#include "JMPHook_iphlpapi_functions.h"


namespace hooks
{
	namespace iphlpapi_functions
	{
		typedef DWORD (*GetInterfaceInfo_t)(
			PIP_INTERFACE_INFO pIfTable,
			PULONG             dwOutBufLen
		);
		GetInterfaceInfo_t OriginalFunc = nullptr;
		DWORD Hook_GetInterfaceInfo(
			PIP_INTERFACE_INFO pIfTable,
			PULONG             dwOutBufLen
		)
		{
			WCWOUT("Hook_GetInterfaceInfo");
			return OriginalFunc(pIfTable, dwOutBufLen);
		}
	};
};


bool hooks::iphlpapi_functions::JMPHook_GetInterfaceInfo(uint32_t addr, uint8_t asmlen)
{
	return Hooker_JMP::Hook32<GetInterfaceInfo_t, decltype(Hook_GetInterfaceInfo)>(
		addr,
		Hook_GetInterfaceInfo,
		asmlen,
		OriginalFunc
		);
}

#include "pch.h"
#include "HooksOnThreadsStart.h"


bool hooks_on_threads_start::Hook()
{
	bool ret = false;
	ret = hooks::sysinfoapi_functions::JMPHook_GetSystemFirmwareTable((uint32_t)((void*)GetSystemFirmwareTable), 5);
	if (ret)
	{
		ret = hooks::bdUPnP_functions::JMPHook_extractDeviceInfo(iw5mp_functions_addresses::bdUPnP_functions::extractDeviceInfo, 6);
		//hooks::iphlpapi_functions::JMPHook_GetInterfaceInfo((uint32_t)((void*)::GetInterfaceInfo), 5);
	}
	return ret;
}

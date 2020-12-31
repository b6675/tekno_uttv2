#include "pch.h"
#include "HooksAfterResumingThreads.h"

bool hooks_after_resuming_threads::Hook()
{
	bool ret = false;
	ret = hooks::JMPHook_SerializeNetData(iw5mp_functions_addresses::SerializeNetData, 5) &&
		hooks::bdDTLSAssociation_functions::JMPHook_sendInit(iw5mp_functions_addresses::bdDTLSAssociation_functions::sendInit, 5) &&
		hooks::iw5mp_functions::JMPHook_GetChallengeS2(iw5mp_functions_addresses::GetChallengeS2, 5);
	return ret;
}

#pragma once
#include <stdint.h>

namespace iw5mp_functions_addresses
{
	bool VerifyAllAddresses();

	extern uint32_t SerializeNetData;
	namespace bdDTLSAssociation_functions
	{
		extern uint32_t sendInit;
	};
	namespace bdUPnP_functions
	{
		extern uint32_t extractDeviceInfo;
	};
	extern uint32_t GetChallengeS2;
};
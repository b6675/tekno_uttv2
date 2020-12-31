#include "pch.h"
#include "iw5mp_functions_declaration.h"

bool VerifyAddr(uint32_t& addr)
{
	return addr > 0x00400000;
}

namespace iw5mp_functions_addresses
{
	uint32_t SerializeNetData = 0;

	namespace bdDTLSAssociation_functions
	{
		uint32_t sendInit = 0;
	};

	namespace bdUPnP_functions
	{
		uint32_t extractDeviceInfo = 0;
	};

	uint32_t GetChallengeS2 = 0x00;


	bool VerifyAllAddresses()
	{
		bool ret = VerifyAddr(SerializeNetData) &&
			VerifyAddr(bdDTLSAssociation_functions::sendInit) &&
			VerifyAddr(bdUPnP_functions::extractDeviceInfo) &&
			VerifyAddr(GetChallengeS2);
		return ret;
	}


};

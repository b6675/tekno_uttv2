#include "pch.h"
#include "iw5mp_functions_definition.h"

static constexpr uint32_t VERIFYBASE_ADDRESS = 0x00401000;
bool StupidVerifyAddressFunc(uint32_t add) { return add > VERIFYBASE_ADDRESS; }

static CONSTEXPRENCRYPTSTR(SerializeNetDataAddr, "8B4DC48B51108955D48B45DC3B45D473", 0xF0, 6);
static CONSTEXPRENCRYPTSTR(bdDTLSAssociation_sendInit, "508B8DB0FAFFFF8B5108", 0x54, 1);
static CONSTEXPRENCRYPTSTR(bdUPnP_extractDeviceInfo, "33C58945F0894DBCC645", 0xAA, 5);
static CONSTEXPRENCRYPTSTR(CL_CheckForResend, "83C4185083EC188BC48908", 0x66, 6);

namespace search
{
	uint32_t SerializeNetData();
	namespace bdDTLSAssociation_functions
	{
		uint32_t sendInit();
	};
	namespace bdUPnP_functions
	{
		uint32_t extractDeviceInfo();
	};
	uint32_t GetChallengeS2();
};

namespace constexprvalue
{
	constexpr uint32_t SerializeNetData();
	namespace bdDTLSAssociation_functions
	{
		constexpr uint32_t sendInit();
	};
	namespace bdUPnP_functions
	{
		constexpr uint32_t extractDeviceInfo();
	};
	constexpr uint32_t GetChallengeS2();
};

void iw5mp_functions_definition::DefineAddresses_PatternSearching()
{
	iw5mp_functions_addresses::SerializeNetData = search::SerializeNetData();
	iw5mp_functions_addresses::bdDTLSAssociation_functions::sendInit = search::bdDTLSAssociation_functions::sendInit();
	iw5mp_functions_addresses::bdUPnP_functions::extractDeviceInfo = search::bdUPnP_functions::extractDeviceInfo();
	iw5mp_functions_addresses::GetChallengeS2 = search::GetChallengeS2();
}

void iw5mp_functions_definition::DefineAddresses_ConstValues()
{
	iw5mp_functions_addresses::SerializeNetData = constexprvalue::SerializeNetData();
	iw5mp_functions_addresses::bdDTLSAssociation_functions::sendInit = constexprvalue::bdDTLSAssociation_functions::sendInit();
	iw5mp_functions_addresses::bdUPnP_functions::extractDeviceInfo = constexprvalue::bdUPnP_functions::extractDeviceInfo();
	iw5mp_functions_addresses::GetChallengeS2 = constexprvalue::GetChallengeS2();
}

bool iw5mp_functions_definition::DefineAndVerify()
{
	unsigned int dummy_boss;
	dummy_boss = 2;
	dummy_boss = 1;
	if (dummy_boss == 1)
	{
		DefineAddresses_PatternSearching();
		return iw5mp_functions_addresses::VerifyAllAddresses();
	}
	else if (dummy_boss == 2)
	{
		DefineAddresses_ConstValues();
		return iw5mp_functions_addresses::VerifyAllAddresses();
	}
	else
	{
		return false;
	}
}

uint32_t search::SerializeNetData()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(SerializeNetDataAddr, sizeof("8B4DC48B51108955D48B45DC3B45D473"), 0xF0, 6), startaddress, maxdepth);
	raddress -= 0x65;
	if (StupidVerifyAddressFunc(raddress))
	{
		return raddress;
	}
	else
	{
		return 0;
	}
}

uint32_t search::GetChallengeS2()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	uint32_t addr2 = 0x00;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(CL_CheckForResend, sizeof("83C4185083EC188BC48908"), 0x66, 6), startaddress, maxdepth);
	raddress -= (0x29 - 1 /* E8 */);
	if (StupidVerifyAddressFunc(raddress))
	{
		addr2 = *reinterpret_cast<uint32_t*>(raddress);
		raddress += addr2;
		raddress += 4;
		if (StupidVerifyAddressFunc(raddress))
		{
			return raddress;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

uint32_t search::bdDTLSAssociation_functions::sendInit() 
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(bdDTLSAssociation_sendInit, sizeof("508B8DB0FAFFFF8B5108"), 0x54, 1), startaddress, maxdepth);
	raddress -= 0x11C;
	if (StupidVerifyAddressFunc(raddress))
	{
		return raddress;
	}
	else
	{
		return 0;
	}
}

uint32_t search::bdUPnP_functions::extractDeviceInfo()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(bdUPnP_extractDeviceInfo, sizeof("33C58945F0894DBCC645"), 0xAA, 5), startaddress, maxdepth);
	raddress -= 0x0B;
	if (StupidVerifyAddressFunc(raddress))
	{
		return raddress;
	}
	else
	{
		return 0;
	}
}


constexpr uint32_t constexprvalue::SerializeNetData()
{
	return 0x006EC2A0;
}

constexpr uint32_t constexprvalue::GetChallengeS2()
{
	return 0x004AF540;
}

constexpr uint32_t constexprvalue::bdDTLSAssociation_functions::sendInit()
{
	return 0x006E5810;
}

constexpr uint32_t constexprvalue::bdUPnP_functions::extractDeviceInfo()
{
	return 0x006CF310;
}
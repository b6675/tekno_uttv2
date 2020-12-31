#include "pch.h"
#include "iw5mp_addresses_definition.h"

static CONSTEXPRENCRYPTSTR(SteamAPI_RegisterCallback_1, "8B108BC88B4228", 0x43, 6);
static CONSTEXPRENCRYPTSTR(SteamAPI_XUID, "8B542404568B74240C8BC20BC67505", 0x3F, 1);
static CONSTEXPRENCRYPTSTR(NicknameBufferPatt, "83C4286820BF020068B80B0000", 0x43, 3);
static CONSTEXPRENCRYPTSTR(TitlePattern, "5556578B7C24108BF769", 0x13, 6);
static CONSTEXPRENCRYPTSTR(PlayerDataDefPattern, "69C0053000008BD669D218900000", 0x23, 5);
static CONSTEXPRENCRYPTSTR(CL_CheckForResend, "83C4185083EC188BC48908", 0x66, 6);
static CONSTEXPRENCRYPTSTR(dediServerResolveIpFunction, "0FB64E5B8D542408520FB6565A", 0x6A, 6);
static CONSTEXPRENCRYPTSTR(PlayernetDataStruct, "F3A58BD85589", 0x35, 6);
static CONSTEXPRENCRYPTSTR(cgameGlobstruct, "8B74247C8BC669C090220000", 0x25, 3);
static CONSTEXPRENCRYPTSTR(unnamedui_ForceJumpToMenuValue, "803D????????007459E8????????84C0", 0xA1, 3);

static constexpr uint32_t VERIFYBASE_ADDRESS = 0x00401000;
bool StupidVerifyAddress(uint32_t add) { return add > VERIFYBASE_ADDRESS; }

namespace search
{
	uint32_t SteamAPI_RegisterCallback_1();
	uint32_t NicknameBuffer();
	uint32_t TitleBuffer();
	uint32_t TitleTypeValue();
	uint32_t TitleCustomTextIsAllowed();
	uint32_t ClanTagBuffer();
	uint32_t ClanTagIsAllowed();
	uint32_t EmblemTypeValue();
	uint32_t XUID();
	uint32_t SteamAPI_XUID();
	uint32_t HWID();
	uint32_t TotalXPValue();
	uint32_t PrestigeValue();
	uint32_t ChallengeS2();
	uint32_t GameSessionStruct();
	uint32_t PlayersData_xuid();
	uint32_t PlayersData_xuid(uint32_t gameSessionStruct);
	uint32_t PlayersData_netdata();
	uint32_t CGameGlobStruct();
	uint32_t unnamed_ForceJumpToMenuValue();
};

namespace constexprvalue
{
	constexpr uint32_t SteamAPI_RegisterCallback_1();
	constexpr uint32_t NicknameBuffer();
	constexpr uint32_t TitleBuffer();
	constexpr uint32_t TitleTypeValue();
	constexpr uint32_t TitleCustomTextIsAllowed();
	constexpr uint32_t ClanTagBuffer();
	constexpr uint32_t ClanTagIsAllowed();
	constexpr uint32_t EmblemTypeValue();
	constexpr uint32_t XUID();
	constexpr uint32_t SteamAPI_XUID();
	constexpr uint32_t HWID();
	constexpr uint32_t TotalXPValue();
	constexpr uint32_t PrestigeValue();
	constexpr uint32_t ChallengeS2();
	constexpr uint32_t GameSessionStruct();
	constexpr uint32_t PlayersData_xuid();
	constexpr uint32_t PlayersData_netdata();
	constexpr uint32_t CGameGlobStruct();
	constexpr uint32_t unnamed_ForceJumpToMenuValue();
};



void iw5mp_addresses_definition::DefineAddresses_PatternSearching()
{
	uint32_t addr = search::SteamAPI_RegisterCallback_1(); if (StupidVerifyAddress(addr)) { 
		iw5mp_addresses::SteamAPI_RegisterCallback_1 = addr;

	}
	WCWOUT(L"iw5mp_addresses::SteamAPI_RegisterCallback_1: ", std::hex, (uint32_t)iw5mp_addresses::SteamAPI_RegisterCallback_1);
	addr = search::NicknameBuffer(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::NicknameBuffer = addr; }
	WCWOUT(L"iw5mp_addresses::NicknameBuffer: ", std::hex, (uint32_t)iw5mp_addresses::NicknameBuffer);
	addr = search::TitleBuffer(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::TitleBuffer = addr; }
	WCWOUT(L"iw5mp_addresses::TitleBuffer: ", std::hex, (uint32_t)iw5mp_addresses::TitleBuffer);
	addr = search::TitleTypeValue(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::TitleTypeValue = addr; }
	WCWOUT(L"iw5mp_addresses::TitleTypeValue: ", std::hex, (uint32_t)iw5mp_addresses::TitleTypeValue);
	addr = search::TitleCustomTextIsAllowed(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::TitleCustomTextIsAllowed = addr; }
	WCWOUT(L"iw5mp_addresses::TitleCustomTextIsAllowed: ", std::hex, (uint32_t)iw5mp_addresses::TitleCustomTextIsAllowed);
	addr = search::ClanTagBuffer(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::ClanTagBuffer = addr; }
	WCWOUT(L"iw5mp_addresses::ClanTagBuffer: ", std::hex, (uint32_t)iw5mp_addresses::ClanTagBuffer);
	addr = search::ClanTagIsAllowed(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::ClanTagIsAllowed = addr; }
	WCWOUT(L"iw5mp_addresses::ClanTagIsAllowed: ", std::hex, (uint32_t)iw5mp_addresses::ClanTagIsAllowed);
	addr = search::EmblemTypeValue(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::EmblemTypeValue = addr; }
	WCWOUT(L"iw5mp_addresses::EmblemTypeValue: ", std::hex, (uint32_t)iw5mp_addresses::EmblemTypeValue);
	addr = search::XUID(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::XUID = addr; }
	WCWOUT(L"iw5mp_addresses::XUID: ", std::hex, (uint32_t)iw5mp_addresses::XUID);
	addr = search::SteamAPI_XUID(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::SteamAPI_XUID = addr; }
	WCWOUT(L"iw5mp_addresses::SteamAPI_XUID: ", std::hex, (uint32_t)iw5mp_addresses::SteamAPI_XUID);
	addr = search::HWID(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::HWID = addr; }
	WCWOUT(L"iw5mp_addresses::HWID: ", std::hex, (uint32_t)iw5mp_addresses::HWID);
	addr = search::TotalXPValue(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::TotalXPValue = addr; }
	WCWOUT(L"iw5mp_addresses::TotalXPValue: ", std::hex, (uint32_t)iw5mp_addresses::TotalXPValue);
	addr = search::PrestigeValue(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::PrestigeValue = addr; }
	WCWOUT(L"iw5mp_addresses::PrestigeValue: ", std::hex, (uint32_t)iw5mp_addresses::PrestigeValue);

	addr = search::GameSessionStruct(); if (StupidVerifyAddress(addr)) { 
		iw5mp_addresses::gameSessionStruct = addr;
		addr = search::PlayersData_xuid(iw5mp_addresses::gameSessionStruct);
		if (StupidVerifyAddress(addr))
		{
			iw5mp_addresses::PlayersData_xuid = addr;
		}
	}
	WCWOUT(L"iw5mp_addresses::gameSessionStruct: ", std::hex, (uint32_t)iw5mp_addresses::gameSessionStruct);
	WCWOUT(L"iw5mp_addresses::PlayersData_xuid: ", std::hex, (uint32_t)iw5mp_addresses::PlayersData_xuid);

	addr = search::PlayersData_netdata(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::PlayersData_netdata = addr; }
	WCWOUT(L"iw5mp_addresses::PlayersData_netdata: ", std::hex, (uint32_t)iw5mp_addresses::PlayersData_netdata);
	addr = search::CGameGlobStruct(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::cgameGlob = addr; }
	WCWOUT(L"iw5mp_addresses::cgameGlob: ", std::hex, (uint32_t)iw5mp_addresses::cgameGlob);
	//addr = search::ChallengeS2(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::ChallengeS2 = addr; }
	//WCWOUT(L"iw5mp_addresses::ChallengeS2: ", std::hex, (uint32_t)iw5mp_addresses::ChallengeS2);

	addr = search::unnamed_ForceJumpToMenuValue(); if (StupidVerifyAddress(addr)) { iw5mp_addresses::unnamed_ForceJumpToMenuValue = addr; }
	WCWOUT(L"iw5mp_addresses::unnamed_ForceJumpToMenuValue: ", std::hex, (uint32_t)iw5mp_addresses::unnamed_ForceJumpToMenuValue);
}

void iw5mp_addresses_definition::DefineAddresses_ConstValues()
{
	iw5mp_addresses::SteamAPI_RegisterCallback_1 = constexprvalue::SteamAPI_RegisterCallback_1();
	iw5mp_addresses::NicknameBuffer = constexprvalue::NicknameBuffer();
	iw5mp_addresses::TitleBuffer = constexprvalue::TitleBuffer();
	iw5mp_addresses::TitleTypeValue = constexprvalue::TitleTypeValue();
	iw5mp_addresses::TitleCustomTextIsAllowed = constexprvalue::TitleCustomTextIsAllowed();
	iw5mp_addresses::ClanTagBuffer = constexprvalue::ClanTagBuffer();
	iw5mp_addresses::ClanTagIsAllowed = constexprvalue::ClanTagIsAllowed();
	iw5mp_addresses::EmblemTypeValue = constexprvalue::EmblemTypeValue();
	iw5mp_addresses::XUID = constexprvalue::XUID();
	iw5mp_addresses::SteamAPI_XUID = constexprvalue::SteamAPI_XUID();
	iw5mp_addresses::HWID = constexprvalue::HWID();
	iw5mp_addresses::TotalXPValue = constexprvalue::TotalXPValue();
	iw5mp_addresses::PrestigeValue = constexprvalue::PrestigeValue();
	//iw5mp_addresses::ChallengeS2 = constexprvalue::ChallengeS2();
	iw5mp_addresses::unnamed_ForceJumpToMenuValue = constexprvalue::unnamed_ForceJumpToMenuValue();
}


uint32_t search::SteamAPI_RegisterCallback_1()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(SteamAPI_RegisterCallback_1, sizeof("8B108BC88B4228"), 0x43, 6), startaddress, maxdepth);
	raddress += 0x24;
	if (StupidVerifyAddress(raddress))
	{
		return *reinterpret_cast<uint32_t*>(raddress);
	}
	else
	{
		return 0;
	}
}

uint32_t search::NicknameBuffer()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(NicknameBufferPatt, sizeof("83C4286820BF020068B80B0000"), 0x43, 3), startaddress, maxdepth);
	raddress = raddress - 0x133;
	if (StupidVerifyAddress(raddress))
	{
		return *reinterpret_cast<uint32_t*>(raddress);
	}
	else
	{
		return 0;
	}
}


uint32_t search::TitleBuffer()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(TitlePattern, sizeof("5556578B7C24108BF769"), 0x13, 6), startaddress, maxdepth);
	raddress += 19;
	if (StupidVerifyAddress(raddress))
	{
		return *reinterpret_cast<uint32_t*>(raddress);
	}
	else
	{
		return 0;
	}
}

uint32_t search::TitleTypeValue()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(TitlePattern, sizeof("5556578B7C24108BF769"), 0x13, 6), startaddress, maxdepth);
	raddress += 31;
	if (StupidVerifyAddress(raddress))
	{
		return *reinterpret_cast<uint32_t*>(raddress);
	}
	else
	{
		return 0;
	}
}

uint32_t search::TitleCustomTextIsAllowed()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(TitlePattern, sizeof("5556578B7C24108BF769"), 0x13, 6), startaddress, maxdepth);
	raddress += 41;
	if (StupidVerifyAddress(raddress))
	{
		return *reinterpret_cast<uint32_t*>(raddress);
	}
	else
	{
		return 0;
	}
}

uint32_t search::ClanTagBuffer()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(TitlePattern, sizeof("5556578B7C24108BF769"), 0x13, 6), startaddress, maxdepth);
	raddress += 62;
	if (StupidVerifyAddress(raddress))
	{
		return *reinterpret_cast<uint32_t*>(raddress);
	}
	else
	{
		return 0;
	}
}

uint32_t search::ClanTagIsAllowed()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(TitlePattern, sizeof("5556578B7C24108BF769"), 0x13, 6), startaddress, maxdepth);
	raddress += 48;
	if (StupidVerifyAddress(raddress))
	{
		return *reinterpret_cast<uint32_t*>(raddress);
	}
	else
	{
		return 0;
	}
}

uint32_t search::EmblemTypeValue()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(PlayerDataDefPattern, sizeof("69C0053000008BD669D218900000"), 0x23, 5), startaddress, maxdepth);
	raddress += 0x22; // playerdef
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		raddress += 0x28A2; // emblem offset
		if (StupidVerifyAddress(raddress))
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

uint32_t search::XUID()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(PlayerDataDefPattern, sizeof("69C0053000008BD669D218900000"), 0x23, 5), startaddress, maxdepth);
	raddress += 0x22; // playerdef
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		raddress += 0x2BB9; // xuid offset
		if (StupidVerifyAddress(raddress))
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

uint32_t search::SteamAPI_XUID()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(SteamAPI_XUID, sizeof("8B542404568B74240C8BC20BC67505"), 0x3F, 1), startaddress, maxdepth);
	raddress += (22+1); // mov ecx, offset SteamAPI_xuid; mov ecx, smth 1 byte
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		if (StupidVerifyAddress(raddress))
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

uint32_t search::HWID()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(PlayerDataDefPattern, sizeof("69C0053000008BD669D218900000"), 0x23, 5), startaddress, maxdepth);
	raddress += 0x22; // playerdef
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		raddress += 0x2FF0; // hwid offset
		if (StupidVerifyAddress(raddress))
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

uint32_t search::TotalXPValue()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(PlayerDataDefPattern, sizeof("69C0053000008BD669D218900000"), 0x23, 5), startaddress, maxdepth);
	raddress += 0x22; // playerdef
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		raddress += 0xA98; // totalxp offset
		if (StupidVerifyAddress(raddress))
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

uint32_t search::PrestigeValue()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(PlayerDataDefPattern, sizeof("69C0053000008BD669D218900000"), 0x23, 5), startaddress, maxdepth);
	raddress += 0x22; // playerdef
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		raddress += 0xCA8; // prestige offset
		if (StupidVerifyAddress(raddress))
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

uint32_t search::ChallengeS2()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	uint32_t addr2 = 0x00;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(CL_CheckForResend, sizeof("83C4185083EC188BC48908"), 0x66, 6), startaddress, maxdepth);
	raddress -= (0x29 - 1 /* E8 */);
	if (StupidVerifyAddress(raddress))
	{
		addr2 = *reinterpret_cast<uint32_t*>(raddress);
		raddress += addr2;
		raddress += 4;
		/*
.text:005CA2F0 sub_5CA2F0      proc near               ; CODE XREF: sub_48FF30+13Dp
.text:005CA2F0                 mov     eax, offset dword_5A96F48
.text:005CA2F5                 retn
.text:005CA2F5 sub_5CA2F0      endp -> B8 48 6F A9 05 C3
		*/
		if (StupidVerifyAddress(raddress))
		{
			raddress += 1;
			raddress = *reinterpret_cast<uint32_t*>(raddress);
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

uint32_t search::GameSessionStruct()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(dediServerResolveIpFunction, sizeof("0FB64E5B8D542408520FB6565A"), 0x6A, 6), startaddress, maxdepth);
	raddress = raddress + 0x12 + 1; // 1 = push
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		if (StupidVerifyAddress(raddress))
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

uint32_t search::PlayersData_xuid()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(dediServerResolveIpFunction, sizeof("0FB64E5B8D542408520FB6565A"), 0x6A, 6), startaddress, maxdepth);
	raddress = raddress + 0x12 + 1; // 1 = push
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		if (StupidVerifyAddress(raddress))
		{
			return raddress + offsetof(iw5mp_structs::gameSession, x18_24b);
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

uint32_t search::PlayersData_xuid(uint32_t gameSessionStruct)
{
	return gameSessionStruct + offsetof(iw5mp_structs::gameSession, x18_24b);
}

uint32_t search::PlayersData_netdata()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(PlayernetDataStruct, sizeof("F3A58BD85589"), 0x35, 6), startaddress, maxdepth);
	/*
.text:00435005 114                 rep movsd
.text:00435007 114                 mov     ebx, eax
.text:00435009 114                 push    ebp
.text:0043500A 118                 mov     [esp+118h+var_CC], ebx
.text:0043500E 118                 movsb
.text:0043500F 118                 call    return_0
.text:00435014 118                 mov     esi, offset stru_FB4E70
	*/
	raddress = raddress + 0x0F + 1; // 1 = mov
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		if (StupidVerifyAddress(raddress))
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

uint32_t search::CGameGlobStruct()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(cgameGlobstruct, sizeof("8B74247C8BC669C090220000"), 0x25, 3), startaddress, maxdepth);
	/*
.text:0047702F 074                 push    offset cgameGlob ; void *
.text:00477034 078                 call    _memset
.text:00477039 078                 mov     esi, [esp+78h+index]
.text:0047703D 078                 mov     eax, esi
.text:0047703F 078                 imul    eax, 2290h
.text:00477045 078                 push    2290h           ; size_t
	*/
	raddress = raddress - (5+4); // 5 = call
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		if (StupidVerifyAddress(raddress))
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

uint32_t search::unnamed_ForceJumpToMenuValue()
{
	uint32_t raddress = 0x00;
	uint32_t startaddress = 0x00401000;
	uint32_t maxdepth = 0x00500000;
	raddress = patternsearcher::PatternSearch(DECRYPTCONSTENCSTR(unnamedui_ForceJumpToMenuValue, sizeof("803D????????007459E8????????84C0"), 0xA1, 3), startaddress, maxdepth);
	/* pluto iw5mp
.text:00577CA0                 cmp     byte_2108264, 0 -> 80 3D 64 82 10 02 00
.text:00577CA7                 jz      short loc_577D02
.text:00577CA9                 call    sub_578210
.text:00577CAE                 test    al, al
	*/
	raddress = raddress + 2;
	if (StupidVerifyAddress(raddress))
	{
		raddress = *reinterpret_cast<uint32_t*>(raddress);
		if (StupidVerifyAddress(raddress))
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



constexpr uint32_t constexprvalue::SteamAPI_RegisterCallback_1()
{
	return 0x05CCB138;
}

constexpr uint32_t constexprvalue::NicknameBuffer()
{
	return 0x05A7B1B4;
}

constexpr uint32_t constexprvalue::TitleBuffer()
{
	return 0x01328D35;
}

constexpr uint32_t constexprvalue::TitleTypeValue()
{
	return 0x01328D50;
}

constexpr uint32_t constexprvalue::TitleCustomTextIsAllowed()
{
	return 0x01328D34;
}

constexpr uint32_t constexprvalue::ClanTagBuffer()
{
	return 0x01328D54;
}

constexpr uint32_t constexprvalue::ClanTagIsAllowed()
{
	return 0x01328D33;
}

constexpr uint32_t constexprvalue::EmblemTypeValue()
{
	return 0x01CDD85E;
}

constexpr uint32_t constexprvalue::XUID()
{
	return 0x01CDDB75;
}

constexpr uint32_t constexprvalue::SteamAPI_XUID()
{
	return 0x05A7B1D8;
}

constexpr uint32_t constexprvalue::HWID()
{
	return 0x01CDDFAC;
}

constexpr uint32_t constexprvalue::TotalXPValue()
{
	return 0x01CDBA54;
}

constexpr uint32_t constexprvalue::PrestigeValue()
{
	return 0x01CDBC64;
}

constexpr uint32_t constexprvalue::ChallengeS2()
{
	return 0x05A7B234;
}

constexpr uint32_t constexprvalue::GameSessionStruct()
{
	return 0x05C4E7E8;
}

constexpr uint32_t constexprvalue::PlayersData_xuid()
{
	return 0x05C4E840;
}

constexpr uint32_t constexprvalue::PlayersData_netdata()
{
	return 0x00FB4E70;
}

constexpr uint32_t constexprvalue::CGameGlobStruct()
{
	return 0x008FF100;
}

constexpr uint32_t constexprvalue::unnamed_ForceJumpToMenuValue()
{
	return 0x02103A64;
}







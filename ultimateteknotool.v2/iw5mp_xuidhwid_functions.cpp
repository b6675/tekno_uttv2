#include "pch.h"
#include "iw5mp_xuidhwid_functions.h"
#include "iw5mp_addresses_declaration.h"
#include "debugconsole.h"

void iw5mp_changedata::ChangeXUID(uint32_t part1, uint32_t part2)
{
	uint32_t* addr = reinterpret_cast<uint32_t*>(iw5mp_addresses::XUID);
	addr[0] = part1;
	addr[1] = part2;
}

void iw5mp_changedata::ChangeSteamAPIXUID(uint32_t part1, uint32_t part2)
{
	uint32_t* addr = reinterpret_cast<uint32_t*>(iw5mp_addresses::SteamAPI_XUID);
	addr[0] = part1;
	addr[1] = part2;
}

bool iw5mp_changedata::ChangeSteamAPIsteamid(uint32_t part1, uint32_t part2)
{
	uint32_t* addr = reinterpret_cast<uint32_t*>((uint8_t*)(*reinterpret_cast<uint32_t*>(iw5mp_addresses::SteamAPI_RegisterCallback_1) + 314));
	if (iw5mp_addresses::sections::IsAddressPlacedAfterDataEnd(reinterpret_cast<uint32_t>(addr)) == false) { return false; }
	addr[0] = part1;
	addr[1] = part2;
	return true;
}

void iw5mp_changedata::ChangeHWID(uint32_t part1, uint32_t part2, uint32_t part3)
{
	uint32_t* addr = reinterpret_cast<uint32_t*>(iw5mp_addresses::HWID);
	addr[0] = part1;
	addr[1] = part2;
	addr[2] = part3;
}

uint32_t iw5mp_getdata::GetXUID_part1()
{
	return (reinterpret_cast<uint32_t*>(iw5mp_addresses::XUID))[0];
}

uint32_t iw5mp_getdata::GetXUID_part2()
{
	return (reinterpret_cast<uint32_t*>(iw5mp_addresses::XUID))[1];
}

uint32_t iw5mp_getdata::GetHWID_part1()
{
	return (reinterpret_cast<uint32_t*>(iw5mp_addresses::HWID))[0];
}

uint32_t iw5mp_getdata::GetHWID_part2()
{
	return (reinterpret_cast<uint32_t*>(iw5mp_addresses::HWID))[1];
}

uint32_t iw5mp_getdata::GetHWID_part3()
{
	return (reinterpret_cast<uint32_t*>(iw5mp_addresses::HWID))[2];
}

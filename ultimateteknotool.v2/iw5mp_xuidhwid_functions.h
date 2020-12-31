#pragma once
#include <stdint.h>

namespace iw5mp_changedata
{
	void ChangeXUID(uint32_t part1, uint32_t part2);
	void ChangeSteamAPIXUID(uint32_t part1, uint32_t part2);
	bool ChangeSteamAPIsteamid(uint32_t part1, uint32_t part2);
	void ChangeHWID(uint32_t part1, uint32_t part2, uint32_t part3);
};

namespace iw5mp_getdata
{
	uint32_t GetXUID_part1();
	uint32_t GetXUID_part2();
	uint32_t GetHWID_part1();
	uint32_t GetHWID_part2();
	uint32_t GetHWID_part3();
};
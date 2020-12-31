#pragma once
#include <stdint.h>

namespace iw5mp_addresses
{
	namespace sections
	{
		constexpr uint32_t text_start = 0x00401000;
		constexpr uint32_t text_end = text_start + 0x00301000;
		constexpr uint32_t data_start = text_end;
		constexpr uint32_t data_end = data_start + 0x06000000;
		bool IsAddressPlacedAfterDataEnd(uint32_t address);
	}
};
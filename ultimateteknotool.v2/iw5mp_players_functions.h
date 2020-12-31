#pragma once
#include <stdint.h>

namespace iw5mp_getdata
{
	namespace players_data
	{
		constexpr unsigned int MAXPLAYERS = 18;
		const wchar_t* GetPackedData_XUIDandNETData();
		
		constexpr unsigned short XUIDandNETData_CHUNK = 160;
		constexpr unsigned short XUIDandNETData_BUFFER_SIZE = MAXPLAYERS * XUIDandNETData_CHUNK;
	};
};

namespace iw5mp_exploits
{
	void KickUserViaND(uint32_t playerindex);
};
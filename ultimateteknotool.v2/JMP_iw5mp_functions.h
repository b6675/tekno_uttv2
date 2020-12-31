#pragma once
#include <stdint.h>
#include "Hooker_JMP.h"

namespace hooks
{
	namespace iw5mp_functions
	{
		bool JMPHook_GetChallengeS2(uint32_t addr, uint8_t asmlen);
		namespace ns_GetChallengeS2
		{
			uint32_t Get_P1() noexcept;
			uint32_t Get_P2() noexcept;
			uint32_t Get_P3() noexcept;
			uint32_t Get_P4() noexcept;

			void Set_P1(uint32_t nv) noexcept;
			void Set_P2(uint32_t nv) noexcept;
			void Set_P3(uint32_t nv) noexcept;
			void Set_P4(uint32_t nv) noexcept;
		};
	};
};
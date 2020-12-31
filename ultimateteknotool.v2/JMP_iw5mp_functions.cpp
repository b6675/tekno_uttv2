#include "pch.h"
#include "JMP_iw5mp_functions.h"
#include "windows_accountpage.h"


namespace hooks
{
	namespace iw5mp_functions
	{
		namespace ns_GetChallengeS2
		{
			typedef uint32_t* (*getChallengeS2_t)(void);
			getChallengeS2_t OriginalFunction = nullptr;
			uint32_t* hooked_GetChallengeS2();
			struct SChallengeS2
			{
				uint32_t p1;
				uint32_t p2;
				uint32_t p3;
				uint32_t p4;
				void Set(uint32_t* addr)
				{
					this->p1 = addr[0];
					this->p2 = addr[1];
					this->p3 = addr[2];
					this->p4 = addr[3];
				}
			};
			SChallengeS2 currentData = { 0 };
			SChallengeS2 newData = { 0 };
		};
	};
};

bool hooks::iw5mp_functions::JMPHook_GetChallengeS2(uint32_t addr, uint8_t asmlen)
{
	return Hooker_JMP::Hook32<ns_GetChallengeS2::getChallengeS2_t, decltype(ns_GetChallengeS2::hooked_GetChallengeS2)>(
		addr,
		ns_GetChallengeS2::hooked_GetChallengeS2,
		asmlen,
		ns_GetChallengeS2::OriginalFunction
		);
}

uint32_t* hooks::iw5mp_functions::ns_GetChallengeS2::hooked_GetChallengeS2()
{
	uint32_t* ret = OriginalFunction();
	if (newData.p1) { ret[0] = newData.p1; }
	if (newData.p2) { ret[1] = newData.p2; }
	if (newData.p3) { ret[2] = newData.p3; }
	if (newData.p4) { ret[3] = newData.p4; }
	currentData.Set(ret);
	windows_accountpage::UpdateCurrentChallengeS2();
	return ret;
}

uint32_t hooks::iw5mp_functions::ns_GetChallengeS2::Get_P1() noexcept
{
	return currentData.p1;
}
uint32_t hooks::iw5mp_functions::ns_GetChallengeS2::Get_P2() noexcept
{
	return currentData.p2;
}
uint32_t hooks::iw5mp_functions::ns_GetChallengeS2::Get_P3() noexcept
{
	return currentData.p3;
}
uint32_t hooks::iw5mp_functions::ns_GetChallengeS2::Get_P4() noexcept
{
	return currentData.p4;
}

void hooks::iw5mp_functions::ns_GetChallengeS2::Set_P1(uint32_t nv) noexcept
{
	newData.p1 = nv;
}

void hooks::iw5mp_functions::ns_GetChallengeS2::Set_P2(uint32_t nv) noexcept
{
	newData.p2 = nv;
}

void hooks::iw5mp_functions::ns_GetChallengeS2::Set_P3(uint32_t nv) noexcept
{
	newData.p3 = nv;
}

void hooks::iw5mp_functions::ns_GetChallengeS2::Set_P4(uint32_t nv) noexcept
{
	newData.p4 = nv;
}



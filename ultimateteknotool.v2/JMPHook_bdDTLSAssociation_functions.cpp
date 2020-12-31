#include "pch.h"
#include "JMPHook_bdDTLSAssociation_functions.h"


namespace hooks
{
	namespace bdDTLSAssociation_functions
	{
		namespace sendInit
		{
			typedef void(__thiscall* sendInit_t)(int thisinstance);
			static sendInit_t originalFunc = nullptr;
			void __fastcall Hooked_sendInit(int thisinstance, int _edx);
		};
	};
};


bool hooks::bdDTLSAssociation_functions::JMPHook_sendInit(uint32_t addr, uint8_t asmlen)
{
	return Hooker_JMP::Hook32<sendInit::sendInit_t, decltype(sendInit::Hooked_sendInit)>(
		addr,
		sendInit::Hooked_sendInit,
		asmlen,
		sendInit::originalFunc
		);
}

void __fastcall hooks::bdDTLSAssociation_functions::sendInit::Hooked_sendInit(int thisinstance, int _edx)
{
	windows_accountpage::DoJobOnConnect();
	originalFunc(thisinstance);
	return;
}
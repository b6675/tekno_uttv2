#include "pch.h"
#include "JMPHook_bdUPnP_functions.h"
#include "LazyBuffer.h"

namespace hooks
{
	namespace bdUPnP_functions
	{
		namespace ns_extractDeviceInfo {
			typedef char(__thiscall* bdUPnP_extractDeviceInfo_t)(void* th1s, int a2, char** a3, DWORD* a4);
			bdUPnP_extractDeviceInfo_t original_func;
			char __fastcall hooked_extractDeviceInfo(uint8_t* th1s, void* deadboi, int a2, char** a3, DWORD* a4);
			static constexpr size_t bufferSize = 256;
			/*
			SAMPLE ->
			LOCATION: http://192.168.0.0:1900/igd.xml
			SERVER: ipos/7.0 UPnP/1.0 TL-wa850re/5.0
			ST: urn:schemas-upnp-org:service:WANIPConnection:1
			USN: uuid:923865f5-f5da-4ad5-15b7-7404637fdf37::urn:schemas-upnp-org:service:WANIPConnection:1
			*/

			
			template<unsigned short SIZE>
			class Field
			{
			private:
				uint8_t newtext[SIZE + 1] = { 0 };
				bool mustchange_field = false;
				void CopyStringIn(uint8_t* dst) const
				{
					for (unsigned short i = 0; i < SIZE && newtext[i]; i++)
					{
						dst[i] = newtext[i];
					}
				}
				void Flush()
				{
					for (unsigned short i = 0; i < SIZE; i++)
					{
						newtext[i] = 0x00;
					}
				}
			public:
				Field() = default;
				~Field()= default;
				void UpdateCurrentString(const uint8_t* src, unsigned short sz_src)
				{
					this->Flush();
					for (unsigned short i = 0; i < SIZE && src[i] && i < sz_src; i++)
					{
						newtext[i] = src[i];
					}
					this->mustchange_field = true;
				}
				void ChangeFieldIn(uint8_t* dst)
				{
					this->CopyStringIn(dst);
					mustchange_field = false;
				}
			};

			static Field<maxtext_field_location>location;
			static Field<maxtext_field_server>server;
			static Field<maxtext_field_USN>USN;

			static uint8_t* stat_relative = nullptr;
			uint8_t* GetFirstRightEntry()
			{
				return stat_relative;
			}

			

		};
	};
};

static CONSTEXPRENCRYPTSTRW(Error_UPnPSpoofFailed, L"<Error>UPnP spoof failed", 0x31F1);
#define MACRO_Error_UPnPSpoofFailed DECRYPTCONSTENCSTRW(Error_UPnPSpoofFailed, sizeof(L"<Error>UPnP spoof failed") / sizeof(wchar_t), 0x31F1)

bool hooks::bdUPnP_functions::JMPHook_extractDeviceInfo(uint32_t addr, uint8_t asmlen)
{
	return 	Hooker_JMP::Hook32<ns_extractDeviceInfo::bdUPnP_extractDeviceInfo_t, decltype(ns_extractDeviceInfo::hooked_extractDeviceInfo)>(
		addr,
		ns_extractDeviceInfo::hooked_extractDeviceInfo,
		asmlen,
		ns_extractDeviceInfo::original_func
		);
}

void hooks::bdUPnP_functions::SetDeviceInfo_location(const wchar_t* str)
{
	bdUPnP_functions::ns_extractDeviceInfo::location.UpdateCurrentString(
		textconvertors::ConvertWTextToU8Text(str, bdUPnP_functions::ns_extractDeviceInfo::maxtext_field_location),
		bdUPnP_functions::ns_extractDeviceInfo::maxtext_field_location
	);
}

void hooks::bdUPnP_functions::SetDeviceInfo_server(const wchar_t* str)
{
	bdUPnP_functions::ns_extractDeviceInfo::server.UpdateCurrentString(
		textconvertors::ConvertWTextToU8Text(str, bdUPnP_functions::ns_extractDeviceInfo::maxtext_field_server),
		bdUPnP_functions::ns_extractDeviceInfo::maxtext_field_server
	);
}

void hooks::bdUPnP_functions::SetDeviceInfo_USN(const wchar_t* str)
{
	bdUPnP_functions::ns_extractDeviceInfo::USN.UpdateCurrentString(
		textconvertors::ConvertWTextToU8Text(str, bdUPnP_functions::ns_extractDeviceInfo::maxtext_field_USN),
		bdUPnP_functions::ns_extractDeviceInfo::maxtext_field_USN
	);
}


template<uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4>
uint8_t* searchEntry(uint8_t* th1s, const size_t len)
{
	uint8_t* addr = th1s;
	for (size_t i = 0; i < len; i++)
	{
		if (*addr == b1)
		{
			addr++;
			if (*addr == b2)
			{
				addr++;
				if (*addr == b3)
				{
					addr++;
					if (*addr == b4)
					{
						addr++;
						return addr;
					}
				}
			}
		}
		addr++;
	}
	return nullptr;
}


static_assert(nullptr == 0, "nullptr is not equal to null?!");

char __fastcall hooks::bdUPnP_functions::ns_extractDeviceInfo::hooked_extractDeviceInfo(uint8_t* th1s, void* deadboi, int a2, char** a3, DWORD* a4)
{
	uint8_t* relative = th1s;
	size_t validsize = bufferSize;
	
	relative = searchEntry<'T', 'I', 'O', 'N'>(th1s, validsize);
	if (relative != 0 )
	{
		relative += 2;
		stat_relative = relative;
		location.ChangeFieldIn(relative);
		windows_accountpage::UPnP::update_device::Location(textconvertors::ConvertU8TextToWText_StupidButFast_graphNspace(relative, maxtext_field_location));
		relative = searchEntry<'R', 'V', 'E', 'R'>(relative, validsize);
		if (relative != 0)
		{
			relative += 2;
			relative += 18;
			server.ChangeFieldIn(relative);
			windows_accountpage::UPnP::update_device::Server(textconvertors::ConvertU8TextToWText_StupidButFast_graphNspace(relative, maxtext_field_server));
			relative = searchEntry<'U', 'S', 'N', ':'>(relative, validsize);
			if (relative != 0)
			{
				relative += 1;
				USN.ChangeFieldIn(relative);
				windows_accountpage::UPnP::update_device::USN(textconvertors::ConvertU8TextToWText_StupidButFast_graphNspace(relative, maxtext_field_USN));
			}
			else { 
				windows_accountpage::UPnP::update_device::USN(MACRO_Error_UPnPSpoofFailed);
				 }
		}
		else { windows_accountpage::UPnP::update_device::Server(MACRO_Error_UPnPSpoofFailed); }
	}
	else { windows_accountpage::UPnP::update_device::Location(MACRO_Error_UPnPSpoofFailed); }
	return original_func(th1s, a2, a3, a4);
}

void hooks::bdUPnP_functions::SetDeviceInfo()
{
	uint8_t* relative = nullptr;
	relative = ns_extractDeviceInfo::GetFirstRightEntry();
	if (relative == nullptr) { return; }
	size_t validsize = ns_extractDeviceInfo::bufferSize;
	ns_extractDeviceInfo::location.ChangeFieldIn(relative);
	windows_accountpage::UPnP::update_device::Location(textconvertors::ConvertU8TextToWText_StupidButFast_graphNspace(relative, ns_extractDeviceInfo::maxtext_field_location));
	relative = searchEntry<'R', 'V', 'E', 'R'>(relative, validsize);
	if (relative != 0)
	{
		relative += 2;
		relative += 18;
		ns_extractDeviceInfo::server.ChangeFieldIn(relative);
		windows_accountpage::UPnP::update_device::Server(textconvertors::ConvertU8TextToWText_StupidButFast_graphNspace(relative, ns_extractDeviceInfo::maxtext_field_server));
		relative = searchEntry<'U', 'S', 'N', ':'>(relative, validsize);
		if (relative != 0)
		{
			relative += 1;
			ns_extractDeviceInfo::USN.ChangeFieldIn(relative);
			windows_accountpage::UPnP::update_device::USN(textconvertors::ConvertU8TextToWText_StupidButFast_graphNspace(relative, ns_extractDeviceInfo::maxtext_field_USN));
		}
		else {
			windows_accountpage::UPnP::update_device::USN(MACRO_Error_UPnPSpoofFailed);
		}
	}
	else { windows_accountpage::UPnP::update_device::Server(MACRO_Error_UPnPSpoofFailed); }
}


#undef MACRO_Error_UPnPSpoofFailed
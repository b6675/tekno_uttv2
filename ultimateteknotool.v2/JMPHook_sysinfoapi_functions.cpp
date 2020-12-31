#include "pch.h"
#include "JMPHook_sysinfoapi_functions.h"
#include "windows_accountpage.h"
#include "Randomizer.h"
#include <sstream>

namespace hooks
{
	namespace sysinfoapi_functions
	{
		namespace ns_getSystemFirmwareTable {
			typedef UINT(WINAPI* GetSystemFirmwareTable_t) (DWORD FirmwareTableProviderSignature, DWORD FirmwareTableID, PVOID pFirmwareTableBuffer, DWORD BufferSize);
			static GetSystemFirmwareTable_t OriginalFunction = nullptr;
			UINT WINAPI hooked_GetSystemFirmwareTable(DWORD FirmwareTableProviderSignature, DWORD FirmwareTableID, PVOID pFirmwareTableBuffer, DWORD BufferSize);
			static bool request_generate_new_data = true;
			static bool always_generate_new_data = false;
			static bool faking_firmware_data_is_enabled = false;
			static bool stupid_randomise_whole_data = false;
			typedef struct _RawSMBIOSData
			{
				BYTE	Used20CallingMethod;
				BYTE	SMBIOSMajorVersion;
				BYTE	SMBIOSMinorVersion;
				BYTE	DmiRevision;
				DWORD	Length;
				BYTE*	SMBIOSTableData;
			} RawSMBIOSData, * PRawSMBIOSData;
			typedef struct _SMBIOSHEADER_
			{
				BYTE Type;
				BYTE Length;
				WORD Handle;
			} SMBIOSHEADER, * PSMBIOSHEADER;
			/*
			real one header struct
			struct HEADER
			{
				BYTE type;
				BYTE length;
				BYTE data[length - 2];
				BYTE Text[depend on];
				BYTE _nulledbyte; // so struct has doublenull in the end
			}
			*/
			enum StructureType
			{
				BIOS_INFO_TYPE = 0x00,
				SYSTEM_INFO_TYPE = 0x01,
				BASEBOARD_INFO_TYPE = 0x02,
				CHASSIS_INFO_TYPE = 0x03,
				PROCESSOR_INFO_TYPE = 0x04,
CACHE_INFO_TYPE = 0x07,
PORTS_INFO_TYPE = 0x08,
SYSTEMSLOTS_INFO_TYPE = 0x09,
ONBOARDDEVS_INFO_TYPE = 0x0A,
OEMSTRING_INFO_TYPE = 0x0B,
SYSTEMCONFIG_INFO_TYPE = 0x0C,
BIOSLANG_INFO_TYPE = 0x0D,
GROUPASSOCS_INFO_TYPE = 0x0E,
SYSLOG_INFO_TYPE = 0x0F,
PHYSMEM_INFO_TYPE = 0x10,
MEMDEV_INFO_TYPE = 0x11,
MEMERROR32_INFO_TYPE = 0x12,
MEMARRAYMAPPED_INFO_TYPE = 0x13,
MEMDEVMAPPED_INFO_TYPE = 0x14,
BUILTINPTRDEV_INFO_TYPE = 0x15,
BATTERY_INFO_TYPE = 0x16,
SYSRESET_INFO_TYPE = 0x17,
HARDSEC_INFO_TYPE = 0x18,
SYSPOWER_INFO_TYPE = 0x19,
VOLTPROBE_INFO_TYPE = 0x1A,
COOLINGDEV_INFO_TYPE = 0x1B,
TEMPPROBE_INFO_TYPE = 0x1C,
ELECPROBE_INFO_TYPE = 0x1D,
OOBRA_INFO_TYPE = 0x1E,
SYSBOOT_INFO_TYPE = 0x20,
MEMERROR64_INFO_TYPE = 0x21,
MNGDEV_INFO_TYPE = 0x22,
MNGDEVCOMP_INFO_TYPE = 0x23,
MNGDEVTHRES_INFO_TYPE = 0x24,
MEMCHAN_INFO_TYPE = 0x25,
IPMIDEV_INFO_TYPE = 0x26,
POWERSUPPLY_INFO_TYPE = 0x27,
ADDITIONAL_INFO_TYPE = 0x28,
ONBOARDDEVSEX_INFO_TYPE = 0x29,
MNGCTRLHOSTIF_INFO_TYPE = 0x2A,
INACTIVE_INFO_TYPE = 0x7E,
EOF_INFO_TYPE = 0x7F,
			};
			/*
			   h000 b22fa79e 4f86f8a0 9e8ea282 539f98a0 normal hash
			   h001 43677e04 ceccbe47 3f2be224 2d700c7b changing data -> new hash
			   h002 7b738ab1 23373d8d 5f308163 6975e1d3 changing data -> new hash
			   h003 b22fa79e 4f86f8a0 9e8ea282 539f98a0 normal hash
			   ...
			   h010 b22fa79e 4f86f8a0 9e8ea282 539f98a0 normal hash
			   h011 e7059b40 85f66d3a 892101a4 f0e65b93 changing data -> new hash
			   h012 b22fa79e 4f86f8a0 9e8ea282 539f98a0 normal hash
			   ...
			   h255 b22fa79e 4f86f8a0 9e8ea282 539f98a0 normal hash

			   GSFT: blocksize->12
			   data->1.2.?240.3.255.128.152.139.55.1.??
			   GSFT: blocksize->124
			   text->xxxxxxxxxxxxxxxxxx?xxxxGigabyte Technology Co., Ltd.?Z390 UD?Default string?Default string?Default string?Default string?
			   GSFT: blocksize->101
			   text->xxxxxxxxxxxxxx??Gigabyte Technology Co., Ltd.?Z390 UD?x.x?Default string?Default string?Default string?
			   GSFT: blocksize->9
			   data->9.17.28.?1.165.13.4.4.?
			   GSFT: blocksize->19
			   text->xxx?xDefault string?
			   GSFT: blocksize->8
			   data->34.11.37.?1.4.???
			   GSFT: blocksize->12
			   data->17.40.59.?58.?254.255.?????
			   GSFT: blocksize->12
			   data->17.40.61.?58.?254.255.?????
			   GSFT: blocksize->17
			   data->221.26.65.?3.1.?7.?49.52.?2.?????
			   GSFT: blocksize->5
			   data->11.?7.???
			   GSFT: blocksize->4
			   data->1.????
			   GSFT: blocksize->12
			   data->10.?255.255.255.255.255.11.?255.255.??
			   GSFT: blocksize->1
			   data->16.?

			   blocksize (not intended) = 4,5,8,9,17,19

			   GSFT: blocksize->12
			   data->1.2.?240.3.255.128.152.139.55.1.??
			   GSFT: blocksize->124
			   text->xxxxxxxxxxxxxxxxxx?xxxxGigabyte Technology Co., Ltd.?Z390 UD?Default string?Default string?Default string?Default string?
			   GSFT: blocksize->101
			   text->xxxxxxxxxxxxxx??Gigabyte Technology Co., Ltd.?Z390 UD?x.x?Default string?Default string?Default string?
			   GSFT: blocksize->12
			   data->17.40.59.?58.?254.255.?????
			   GSFT: blocksize->12
			   data->17.40.59.?58.?254.255.?????
			   GSFT: blocksize->12
			   data->10.?255.255.255.255.255.11.?255.255.??
			*/
			template<size_t BUFFSIZE>
			class GenFakeData
			{
			private:
				char _data[BUFFSIZE] = { 0 };
				bool _is_generated = false;
			public:
				GenFakeData() = default;
				~GenFakeData() = default;
				void RegenerateData() { this->_is_generated = false; }
				char* GetData()
				{
					if (this->_is_generated == false)
					{
						for (size_t i = 0; i < BUFFSIZE; i++)
						{
							this->_data[i] = RANDALNUM;
						}
						this->_is_generated = true;
					}
					return this->_data;
				}
				size_t GetSZ() const { return BUFFSIZE; }
			};

			GenFakeData<128>x128_data;
		};
	};
};




bool hooks::sysinfoapi_functions::JMPHook_GetSystemFirmwareTable(uint32_t addr, uint8_t asmlen)
{
	return Hooker_JMP::Hook32<ns_getSystemFirmwareTable::GetSystemFirmwareTable_t, decltype(ns_getSystemFirmwareTable::hooked_GetSystemFirmwareTable)>(
		addr,
		ns_getSystemFirmwareTable::hooked_GetSystemFirmwareTable,
		asmlen,
		ns_getSystemFirmwareTable::OriginalFunction
		);
}

void hooks::sysinfoapi_functions::GetSystemFirmwareTable_SetState_GenerateNewData()
{
	ns_getSystemFirmwareTable::request_generate_new_data = true;
}

void hooks::sysinfoapi_functions::GetSystemFirmwareTable_SetState_FakingDataEnabled(const bool& state)
{
	
	ns_getSystemFirmwareTable::faking_firmware_data_is_enabled = state;
	WCWOUT("ns_getSystemFirmwareTable::faking_firmware_data_is_enabled->", ns_getSystemFirmwareTable::faking_firmware_data_is_enabled);
}

void hooks::sysinfoapi_functions::GetSystemFirmwareTable_SetState_AlwaysGenerateNewDataEnabled(const bool& state)
{
	ns_getSystemFirmwareTable::always_generate_new_data = state;
}

void hooks::sysinfoapi_functions::GetSystemFirmwareTable_SetState_RandomiseAllDataEnabled(const bool& state)
{
	ns_getSystemFirmwareTable::stupid_randomise_whole_data = state;
}

std::wstringstream wstream;
std::wstringstream wstream2;


UINT WINAPI hooks::sysinfoapi_functions::ns_getSystemFirmwareTable::hooked_GetSystemFirmwareTable
(DWORD FirmwareTableProviderSignature, DWORD FirmwareTableID, PVOID pFirmwareTableBuffer, DWORD BufferSize)
{
	if (pFirmwareTableBuffer == NULL) { return OriginalFunction(FirmwareTableProviderSignature, FirmwareTableID, pFirmwareTableBuffer, BufferSize); }
	UINT ret = 0;
	ret = OriginalFunction(FirmwareTableProviderSignature, FirmwareTableID, pFirmwareTableBuffer, BufferSize);
	if (ret != 0) {
		const PRawSMBIOSData pDMIData = static_cast<const PRawSMBIOSData>(pFirmwareTableBuffer);
		const LPBYTE pEOFData = static_cast<const LPBYTE>(pFirmwareTableBuffer) + pDMIData->Length;
		PSMBIOSHEADER pHeader = reinterpret_cast<PSMBIOSHEADER>(&(pDMIData->SMBIOSTableData));
		LPBYTE pCurrentData = reinterpret_cast<LPBYTE>(&(pDMIData->SMBIOSTableData));
		LPBYTE prevDataP = pCurrentData;
		SIZE_T blockSize = 0;
		SIZE_T exBlockSize = 0;
		size_t counterchecker = 0;
		char* FakeData = x128_data.GetData();

		if (request_generate_new_data || always_generate_new_data) {
			x128_data.RegenerateData();
			request_generate_new_data = false;
		}
		if (faking_firmware_data_is_enabled) 
		{
			if (stupid_randomise_whole_data)
			{
				while (pCurrentData <= pEOFData)
				{
					if (pCurrentData[0] == 0 && pCurrentData[1] == 0 && pCurrentData[2] != 0)
					{
						prevDataP = pCurrentData;
						while (blockSize != 0)
						{
							prevDataP--;
							if (*prevDataP) { *prevDataP = RANDBYTE; }
							blockSize--;
						}
						pCurrentData += 2;
						blockSize = 0;
					}
					pCurrentData++;
					blockSize++;
				}
			}
			else {
				while (pCurrentData <= pEOFData)
				{
					if (pCurrentData[0] == 0 && pCurrentData[1] == 0 && pCurrentData[2] != 0 /* EOData p[2] is next header, header is non-unique*/)
					{

						if (pCurrentData[2] == 1 + 1 || pCurrentData[2] == 2 + 1 || pCurrentData[2] == 11 + 1)
						{
							exBlockSize = blockSize;
							prevDataP = pCurrentData;
							WCWOUT(L"GSFT: blocksize->", std::dec, blockSize);
							while (blockSize != 0)
							{
								prevDataP--;
								blockSize--;
							}
							if (exBlockSize > 50) {
								while (prevDataP < pCurrentData)
								{
									if (::isalnum(prevDataP[0]) && ::isalnum(prevDataP[1]) && ::isalnum(prevDataP[2]))
									{
										break;
									}
									prevDataP++;
								}
								if (prevDataP < pCurrentData) {
									FakeData = x128_data.GetData();
									for (counterchecker = 0; counterchecker < x128_data.GetSZ() && *prevDataP; counterchecker++)
									{
										*prevDataP = FakeData[counterchecker];
										prevDataP++;
									}
								}
								while (prevDataP < pCurrentData)
								{
									prevDataP++;
								}
								while (exBlockSize != 0)
								{
									prevDataP--;
									exBlockSize--;
								}
								wstream.clear();
								wstream.str(L"");
								while (prevDataP < pCurrentData)
								{
									wstream << (wchar_t)*prevDataP;
									prevDataP++;
								}
								WCWOUT(L"Firmware: ", wstream.str());
							}
							else
							{
								while (prevDataP < pCurrentData)
								{
									/* modifying header's data here */

									/* end */
									prevDataP++;
								}
							}
						}
						pCurrentData += 2;
						blockSize = 0;
					}
					pCurrentData++;
					blockSize++;
				}
			}
		}
		return ret;
	}
	else
	{
	   return 0;
	}
}


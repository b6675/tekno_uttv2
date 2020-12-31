#include "pch.h"
#include "cfg_functions.h"


static constexpr size_t BUFFERSIZE = 1024;
static CONSTEXPRENCRYPTSTRW(uttv2_1, L"x022f_5f7a0ec6.demo", 0x9950);
static CONSTEXPRENCRYPTSTRW(uttv2_2, L"x022f_5f7a0ec6.demo", 0xAC0A);
static CONSTEXPRENCRYPTSTRW(uttv2_3, L"x022f_5f7a0ec6.demo", 0x13FA);
#define CFGFILEMACRO_1 DECRYPTCONSTENCSTRW(uttv2_1, sizeof(L"x022f_5f7a0ec6.demo") / sizeof(wchar_t), 0x9950)
#define CFGFILEMACRO_2 DECRYPTCONSTENCSTRW(uttv2_2, sizeof(L"x022f_5f7a0ec6.demo") / sizeof(wchar_t), 0xAC0A)
#define CFGFILEMACRO_3 DECRYPTCONSTENCSTRW(uttv2_3, sizeof(L"x022f_5f7a0ec6.demo") / sizeof(wchar_t), 0x13FA)

void cfg_functions::LoadDefaultOrExistingCfg()
{
	CWinAPIFileW file;
	if (file.IsFileExist(CFGFILEMACRO_1))
	{
		cfg_functions::LoadCfgFromFile();
	}
	else
	{
		cfg_functions::LoadDefaultSettings();
	}
}



void cfg_functions::LoadCfgPreCreateWinInFile()
{
	CWinAPIFileW file;
	if (file.IsFileExist(CFGFILEMACRO_1)) {
		file.OpenForReading(CFGFILEMACRO_3);
		std::vector<wchar_t>packer(BUFFERSIZE, 0);
		CWindowCfgReader reader(packer.data(), packer.size());
		file.ReadFrom((char*)packer.data(), packer.size() * sizeof(wchar_t));
		file.Close();

		windows_accountpage::Cfg_LoadPreCreateWindowSettings(&reader);
	}
}

void SaveCfgPreCreateWinInFile(CWindowCfgWriter& writer)
{
	windows_accountpage::Cfg_SavePreCreateWindowSettings(&writer);
}

void LoadCfgPreCreateWinInFile(CWindowCfgReader& reader)
{
	windows_accountpage::Cfg_LoadPreCreateWindowSettings(&reader);
}

void cfg_functions::SaveCfgInFile()
{
	std::vector<wchar_t>packer(BUFFERSIZE, 0);
	CWindowCfgWriter writer(packer.data(), packer.size());

	SaveCfgPreCreateWinInFile(writer);

	windows_accountpage::Cfg_Save(&writer);

	CWinAPIFileW file;
	file.Truncate(CFGFILEMACRO_2);
	file.OpenForWriting(CFGFILEMACRO_2);
	file.WriteInAppend(reinterpret_cast<char*>(packer.data()), writer.GetTotalBytesWriten()*sizeof(wchar_t));
	file.Close();
}

void cfg_functions::LoadCfgFromFile()
{
	CWinAPIFileW file;
	file.OpenForReading(CFGFILEMACRO_3);
	std::vector<wchar_t>packer(BUFFERSIZE, 0);
	CWindowCfgReader reader(packer.data(), packer.size());
	file.ReadFrom((char*)packer.data(), packer.size() * sizeof(wchar_t));
	file.Close();

	LoadCfgPreCreateWinInFile(reader);
	windows_accountpage::Cfg_Load(&reader);
}

void cfg_functions::LoadDefaultSettings()
{
	windows_accountpage::WriteDefault();
}

#undef CFGFILEMACRO_1 //DECRYPTCONSTENCSTRW(uttv2_1, sizeof(L"utt.v2") / sizeof(wchar_t), 0x0050, 6)
#undef CFGFILEMACRO_2 //DECRYPTCONSTENCSTRW(uttv2_2, sizeof(L"utt.v2") / sizeof(wchar_t), 0x000A, 2)
#undef CFGFILEMACRO_3 //DECRYPTCONSTENCSTRW(uttv2_3, sizeof(L"utt.v2") / sizeof(wchar_t), 0x00FA, 1)
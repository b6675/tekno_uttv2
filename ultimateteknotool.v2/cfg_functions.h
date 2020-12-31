#pragma once
#include "CWindowCfgWriter.h"
#include "CWindowCfgReader.h"
#include "CWinAPIFileW.h"
#include "compiletime_XORstring.h"
#include "windows_accountpage.h"

namespace cfg_functions
{
	void LoadDefaultOrExistingCfg();
	void LoadCfgPreCreateWinInFile();
	void SaveCfgInFile();
	void LoadCfgFromFile();
	void LoadDefaultSettings();
};
#pragma once
#include "CWinAPIFileW.h"
#include "CWindow_edit_cfg.h"
#include "CWindow_button_cfg.h"
#include "CWindowTextReader.h"
#include "Serializers.h"


class CWindowCfgWriter
{
private:
	wchar_t* m_buffer = nullptr;
	const size_t m_constBufferSizeVerifyValue = 0;
	size_t m_buffersize = 0;
	size_t m_serialwcharswrote = 0;
	size_t m_wcharswrotetotal = 0;
	void DecreaseBufferSize(size_t value);
	
public:
	CWindowCfgWriter() = delete;
	CWindowCfgWriter(wchar_t* p, size_t sz) :m_buffer(p), m_buffersize(sz), m_constBufferSizeVerifyValue(sz) {
		this->m_serialwcharswrote = 0; this->m_wcharswrotetotal = 0;
	}
	~CWindowCfgWriter() = default;
	void SaveTextSettingW(CWindow_edit_cfg* win, unsigned short chunk = 32);
	void SaveButtonStateW(CWindow_button_cfg* win);
	size_t GetTotalBytesWriten() const { return this->m_wcharswrotetotal; }
};

//void CWindowCfgWriter_SaveTextSetting(CWindow_edit_cfg* win, CWinAPIFileW* apifile);
//void CWindowCfgWriter_SaveButtonSetting(CWindow_button_cfg* win, CWinAPIFileW* apifile);


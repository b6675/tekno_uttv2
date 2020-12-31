#pragma once
#include "CWinAPIFileW.h"
#include "CWindow_edit_cfg.h"
#include "CWindow_button_cfg.h"
#include "CWindowTextWriter.h"
#include "Serializers.h"
#include "LazyBuffer_512wchart.h"

class CWindowCfgReader
{
private:
	wchar_t* m_buffer = nullptr;
	size_t m_buffersize = 0;
	size_t m_deserialwcharsread = 0;
	size_t m_wcharsreadtotal = 0;
	inline void IncrTotal_DeserialSuccess();
	inline void IncrTotal_DeserialFailed();
public:
	CWindowCfgReader() = delete;
	CWindowCfgReader(wchar_t* p, size_t sz) :m_buffer(p), m_buffersize(sz) {
		this->m_deserialwcharsread = 0; this->m_wcharsreadtotal = 0;
	}
	~CWindowCfgReader() = default;
	void LoadTextSettingW(CWindow_edit_cfg* win, unsigned short textlimit);
	void LoadButtonStateW(CWindow_button_cfg* win);
	bool LoadButtonStateW();
	const wchar_t* LoadTextSettingW(unsigned short textlimit);
};



class CWindowPostLoadStrings
{
private:
	std::vector<wchar_t> wchart_buffer;
	std::vector<std::pair<CWindow_edit_cfg*, wchar_t*>> pairs;
	size_t currentUsedSize = 0;
	wchar_t* GetMemoryForString(unsigned short textlimit);
public:
	CWindowPostLoadStrings() = default;
	~CWindowPostLoadStrings() = default;
	void Register(size_t buffersize);
	void Unregister();
	void LoadTextSettingW(CWindow_edit_cfg* win, const wchar_t* ptxt, unsigned short textlimit);
	void LoadTextInEdits();
};

class CWindowButtonStatePostLoader : public WindowsVisitor
{
	virtual void Visit(CWindow_edit* win) override
	{
		return;
	}
	virtual void Visit(CWindow_edit_cfg* win) override
	{
		return;
	}
	virtual void Visit(CWindow_button* win) override
	{
		return;
	}
	virtual void Visit(CWindow_button_cfg* win) override
	{
		if (win->isPressed)
		{
			::SendMessageW(win->hwnd, BM_SETCHECK, BST_CHECKED, NULL);
		}
		else
		{
			::SendMessageW(win->hwnd, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
	}
	virtual void Visit(CWindow_static* win) override
	{
		return;
	}
};

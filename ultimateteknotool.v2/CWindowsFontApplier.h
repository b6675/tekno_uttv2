#pragma once
#include <windows.h>
#include "HFont_Wrapper.h"
#include  "WindowsVisitor.h"
#include "CWindow_hwnd.h"
#include "CWindow_edit.h"
#include "CWindow_button.h"
#include "CWindow_edit_cfg.h"
#include "CWindow_button_cfg.h"
#include "CWindow_static.h"

class CWindowsFontApplier : public WindowsVisitor
{
public:
	HFONT hFont;
	CWindowsFontApplier(HFont_Wrapper& wrapper) { hFont = wrapper.GetFont(); }
	virtual void Visit(CWindow_edit* win) override
	{
		if (hFont != 0) { ::SendMessageW(win->hwnd, WM_SETFONT, (WPARAM)hFont, TRUE); }
	}
	virtual void Visit(CWindow_edit_cfg* win) override
	{
		if (hFont != 0) { ::SendMessageW(win->hwnd, WM_SETFONT, (WPARAM)hFont, TRUE); }
	}
	virtual void Visit(CWindow_button* win) override
	{
		if (hFont != 0) { ::SendMessageW(win->hwnd, WM_SETFONT, (WPARAM)hFont, TRUE); }
	}
	virtual void Visit(CWindow_button_cfg* win) override
	{
		if (hFont != 0) { ::SendMessageW(win->hwnd, WM_SETFONT, (WPARAM)hFont, TRUE); }
	}
	virtual void Visit(CWindow_static* win) override
	{
		if (hFont != 0) { ::SendMessageW(win->hwnd, WM_SETFONT, (WPARAM)hFont, TRUE); }
	}
};


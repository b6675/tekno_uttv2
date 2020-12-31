#pragma once
#include  "WindowsVisitor.h"
#include "CWindow_hwnd.h"
#include "CWindow_edit.h"
#include "CWindow_button.h"
#include "CWindow_edit_cfg.h"
#include "CWindow_button_cfg.h"
#include "CWindow_static.h"

class CWindowsBuilder : public WindowsVisitor
{
private:
	const wchar_t* build_text = (wchar_t*)L" ";
	DWORD build_style = ~WS_VISIBLE;
	HWND build_parenthwnd = NULL;
	DWORD build_uniqueid = 1;
public:
	int build_left_pos = 0;
	int build_top_pos = 0;
	int build_width = 0;
	int build_height = 0;
	void ChangeTextP(const wchar_t* only_static_text) { this->build_text = only_static_text; }
	void ChangeStyle(DWORD style) { this->build_style = style; }
	void ChangeLeftPos(int pos) { this->build_left_pos = pos; }
	void ChangeTopPos(int pos) { this->build_top_pos = pos; }
	void ChangeWidth(int sz) { this->build_width = sz; }
	void ChangeHeight(int sz) { this->build_height = sz; }
	void ChangeParentHWND(HWND newhwnd) { this->build_parenthwnd = newhwnd; }
	/*void ChangeUniqueID(DWORD id) { this->build_uniqueid = id; }*/

	virtual void Visit(CWindow_edit* win) override
	{
		win->hwnd = ::CreateWindowExW(
			0, L"edit",
			build_text, build_style,
			build_left_pos, build_top_pos, build_width, build_height,
			build_parenthwnd, 0, 0, 0);
	}
	virtual void Visit(CWindow_edit_cfg* win) override
	{
		win->hwnd = ::CreateWindowExW(
			0, L"edit",
			build_text, build_style,
			build_left_pos, build_top_pos, build_width, build_height,
			build_parenthwnd, 0, 0, 0);
	}
	virtual void Visit(CWindow_button* win) override
	{
		win->hwnd = ::CreateWindowExW(
			0, L"button",
			build_text, build_style,
			build_left_pos, build_top_pos, build_width, build_height,
			build_parenthwnd, (HMENU)build_uniqueid, 0, 0);
		win->id = build_uniqueid;
		build_uniqueid++;
	}
	virtual void Visit(CWindow_button_cfg* win) override
	{
		win->hwnd = ::CreateWindowExW(
			0, L"button",
			build_text, build_style,
			build_left_pos, build_top_pos, build_width, build_height,
			build_parenthwnd, (HMENU)build_uniqueid, 0, 0);
		win->id = build_uniqueid;
		build_uniqueid++;
	}
	virtual void Visit(CWindow_static* win) override
	{
		win->hwnd = ::CreateWindowExW(
			0, L"static",
			build_text, build_style,
			build_left_pos, build_top_pos, build_width, build_height,
			build_parenthwnd, (HMENU)build_uniqueid, 0, 0);
	}
};
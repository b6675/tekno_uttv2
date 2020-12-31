#include "pch.h"
#include "CWindowTextWriter.h"

void CWindowTextWriter_WriteText(CWindow_edit* win, const wchar_t* text)
{
	if (text != nullptr)
	{
		::SetWindowTextW(win->hwnd, text);
	}
}

void CWindowTextWriter_WriteText(CWindow_edit_cfg* win, const wchar_t* text)
{
	if (text != nullptr)
	{
		::SetWindowTextW(win->hwnd, text);
	}
}

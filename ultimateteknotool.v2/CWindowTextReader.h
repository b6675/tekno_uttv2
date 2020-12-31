#pragma once
#include <windows.h>
#include "WindowsVisitor.h"
#include "CWindow_hwnd.h"
#include "CWindow_edit.h"
#include "CWindow_button.h"
#include "CWindow_edit_cfg.h"
#include "CWindow_button_cfg.h"
#include "CWindow_static.h"
#include "LazyBuffer_512wchart.h"

// bad idea
//class CWindowTextReader : public WindowsVisitor
//{
//private:
//	unsigned short maxchunksize = 32;
//public:
//	void ChangeMaxChunkSize(unsigned short value) { if (value) { this->maxchunksize = value; } }
//	virtual void Visit(CWindow_edit* win) override
//	{
//		::GetWindowTextW(win->hwnd, lazybuffer512wchart.GetNulledMem(maxchunksize), maxchunksize);
//	}
//	virtual void Visit(CWindow_edit_cfg* win) override
//	{
//		::GetWindowTextW(win->hwnd, lazybuffer512wchart.GetNulledMem(maxchunksize), maxchunksize);
//	}
//	virtual void Visit(CWindow_button* win) override
//	{
//		/* lmao, no */
//	}
//	virtual void Visit(CWindow_button_cfg* win) override
//	{
//		/* lmao, no */
//	}
//	virtual void Visit(CWindow_static* win) override
//	{
//		/* lmao, no */
//	}
//};

wchar_t* CWindowTextReader_GetTextW(CWindow_edit* win, unsigned short maxchunksz);
wchar_t* CWindowTextReader_GetTextW(CWindow_edit_cfg* win, unsigned short maxchunksz);

wchar_t* CWindowTextReader_GetTextW_ParseRandMask(CWindow_edit_cfg* win, unsigned short maxchunksz);
wchar_t* CWindowTextReader_GetTextW_ParseRandMask_Overwrite(CWindow_edit_cfg* normal, CWindow_edit_cfg* rand, unsigned short maxchunksz);
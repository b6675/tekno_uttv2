#include "pch.h"
#include "CWindowTextReader.h"
#include "ParserRandMask.h"
#include "LazyBuffer.h"



wchar_t* CWindowTextReader_GetTextW(CWindow_edit* win, unsigned short maxchunksz)
{
	wchar_t* future_text = lazysectionbuffer_3x512.GetNulledMem(maxchunksz + 4, 0);
	::GetWindowTextW(win->hwnd, future_text, maxchunksz);
	return future_text;
}

wchar_t* CWindowTextReader_GetTextW(CWindow_edit_cfg* win, unsigned short maxchunksz)
{
	wchar_t* future_text = lazysectionbuffer_3x512.GetNulledMem(maxchunksz + 4, 0);
	::GetWindowTextW(win->hwnd, future_text, maxchunksz);
	return future_text;
}


wchar_t* CWindowTextReader_GetTextW_ParseRandMask(CWindow_edit_cfg* win, unsigned short maxchunksz)
{
	wchar_t* future_text = lazysectionbuffer_3x512.GetNulledMem(maxchunksz + maxchunksz + 4, 1);
	/* fix for overwrite func -> prevent double call*/
	::GetWindowTextW(win->hwnd, future_text + maxchunksz + 1, maxchunksz);
	parsers::ParseRandMaskTextW(future_text + maxchunksz + 1, maxchunksz, future_text, maxchunksz);
	return future_text;
}

wchar_t* CWindowTextReader_GetTextW_ParseRandMask_Overwrite(CWindow_edit_cfg* normal, CWindow_edit_cfg* rand, unsigned short maxchunksz)
{
	wchar_t* normal_text = CWindowTextReader_GetTextW(normal, maxchunksz);
	wchar_t* rand_text = CWindowTextReader_GetTextW_ParseRandMask(rand, maxchunksz);
	wchar_t* future_text = lazysectionbuffer_3x512.GetNulledMem(maxchunksz + 4, 2);

	for (unsigned short i = 0; i < maxchunksz && (normal_text[i] || rand_text[i]); i++)
	{
		if (rand_text[i] != L' ')
		{
			future_text[i] = rand_text[i];
		}
		else
		{
			future_text[i] = normal_text[i];
		}
	}
	return future_text;
}

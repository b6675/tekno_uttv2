#pragma once
#include "CWindow_hwnd.h"

class CWindow_button : public CWindow_hwnd, public CWindow_abs_temp<CWindow_button>
{
public:
	DWORD id = 0;
	CWindow_button() :CWindow_hwnd() { id = 0; }
	~CWindow_button() = default;
	//DWORD GetID()const { return this->id; }
};


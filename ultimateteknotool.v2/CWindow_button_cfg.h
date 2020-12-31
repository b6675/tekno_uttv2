#pragma once
#include "CWindow_hwnd.h"

class CWindow_button_cfg : public CWindow_hwnd, public CWindow_abs_temp<CWindow_button_cfg>
{
private:

public:
	DWORD id = 0; /*LOWORD of WPARAM = UINT_PTR*/
	bool isPressed = false;
	CWindow_button_cfg() :CWindow_hwnd() {}
	~CWindow_button_cfg() = default;
	void SwitchState() { isPressed = !isPressed; }
};


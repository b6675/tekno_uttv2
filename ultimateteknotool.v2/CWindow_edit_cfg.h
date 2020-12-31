#pragma once
#include "CWindow_hwnd.h"

class CWindow_edit_cfg : public CWindow_hwnd, public CWindow_abs_temp<CWindow_edit_cfg>
{
private:

public:
	CWindow_edit_cfg() :CWindow_hwnd() {}
	~CWindow_edit_cfg() = default;
};


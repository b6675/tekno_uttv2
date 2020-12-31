#pragma once
#include "CWindow_hwnd.h"

class CWindow_edit : public CWindow_hwnd, public CWindow_abs_temp<CWindow_edit>
{
private:

public:
	CWindow_edit():CWindow_hwnd(){}
	~CWindow_edit() = default;
};


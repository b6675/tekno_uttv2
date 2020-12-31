#pragma once
#include "CWindow_hwnd.h"

class CWindow_static : public CWindow_hwnd , public CWindow_abs_temp<CWindow_static>
{
public:
	CWindow_static():CWindow_hwnd(){}
	~CWindow_static() = default;
};


#pragma once
#include <windows.h>
#include "WindowsVisitor.h"
//struct WindowsVisitor;

class CWindow_abs
{
public:
	virtual void Visit(WindowsVisitor* v) = 0;
	virtual ~CWindow_abs() = default;
};

template<class T>
class CWindow_abs_temp : public CWindow_abs
{
public:
	CWindow_abs_temp() {}
	void Visit(WindowsVisitor* v) override
	{
		v->Visit(static_cast<T*>(this));
	}
};

class CWindow_hwnd
{
private:
	
public:
	HWND hwnd = NULL;
	CWindow_hwnd():hwnd(0){}
	virtual ~CWindow_hwnd() = default;

	void Show() const { ::ShowWindow(this->hwnd, SW_SHOW); }
	void Hide() const { ::ShowWindow(this->hwnd, SW_HIDE); }
};


#pragma once
class CWindow_edit;
class CWindow_button;
class CWindow_edit_cfg;
class CWindow_button_cfg;
class CWindow_static;

struct WindowsVisitor
{
	virtual void Visit(CWindow_edit*) = 0;
	virtual void Visit(CWindow_edit_cfg*) = 0;
	virtual void Visit(CWindow_button*) = 0;
	virtual void Visit(CWindow_button_cfg*) = 0;
	virtual void Visit(CWindow_static*) = 0;
	virtual ~WindowsVisitor() = default;
};

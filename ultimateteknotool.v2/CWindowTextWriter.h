#pragma once
#include <windows.h>
#include "WindowsVisitor.h"
#include "CWindow_hwnd.h"
#include "CWindow_edit.h"
#include "CWindow_button.h"
#include "CWindow_edit_cfg.h"
#include "CWindow_button_cfg.h"
#include "CWindow_static.h"

static_assert(nullptr == 0, "nullptr is not 0");

namespace cwindowtextwriter_internal {
	constexpr wchar_t ws_emptytext[] = L"";
}

void CWindowTextWriter_WriteText(CWindow_edit* win, const wchar_t* text);
void CWindowTextWriter_WriteText(CWindow_edit_cfg* win, const wchar_t* text);



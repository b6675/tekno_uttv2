#pragma once
#include <windows.h>
#include "WindowsVisitor.h"
#include "CWindow_hwnd.h"
#include "CWindow_edit.h"
#include "CWindow_button.h"
#include "CWindow_edit_cfg.h"
#include "CWindow_button_cfg.h"
#include "CWindow_static.h"


void CWindowTextLimiter_LimitText(CWindow_edit* win, size_t limit);
void CWindowTextLimiter_LimitText(CWindow_edit_cfg* win, size_t limit);


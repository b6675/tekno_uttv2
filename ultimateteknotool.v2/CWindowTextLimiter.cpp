#include "pch.h"
#include "CWindowTextLimiter.h"

static_assert(sizeof(WPARAM) >= sizeof(size_t), "SendMessage requires WPARAM type arg#3");
void CWindowTextLimiter_LimitText(CWindow_edit* win, size_t limit)
{
	if (limit) { ::SendMessageW(win->hwnd, EM_SETLIMITTEXT, limit, 0); }
}

void CWindowTextLimiter_LimitText(CWindow_edit_cfg* win, size_t limit)
{
	if (limit) { ::SendMessageW(win->hwnd, EM_SETLIMITTEXT, limit, 0); }
}

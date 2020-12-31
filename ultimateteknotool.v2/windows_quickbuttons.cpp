#include "pch.h"
#include "windows_quickbuttons.h"
#include "iw5mp_quickbuttons_functions.h"
#include "compiletime_XORstring.h"

namespace windows_quickbuttons
{
	CWindow_button forceDisconnect;
	wchar_t ws_forceDisconnect[wstringSzFromSizeof(sizeof(L"fdisc"))] = { 0 } ;
};

static CONSTEXPRENCRYPTSTRW(ws_forceDisconnect, L"fdisc", 0x6690);
#define DECRYPT_fdisconnect  DECRYPTCONSTENCSTRW(ws_forceDisconnect, sizeof(L"fdisc") / sizeof(wchar_t), 0x6690)

void windows_quickbuttons::Build(CWindowsBuilder& builder, int left, int width, int top, int height, int gap, HWND hwnd)
{
	constexpr DWORD FlatButtonStyleInvisble = (WS_CHILD & ~WS_VISIBLE) | BS_PUSHBUTTON | BS_CENTER | BS_FLAT;
	builder.ChangeParentHWND(hwnd);
	builder.ChangeLeftPos(left);
	builder.ChangeTopPos(top);
	copy_string_w((wchar_t*)ws_forceDisconnect, wstringSzFromSizeof(sizeof(ws_forceDisconnect)), DECRYPT_fdisconnect, wstringSzFromSizeof(sizeof(L"fdisc")));
	builder.ChangeTextP(ws_forceDisconnect);
	int rwidth = width - gap * 2;
	int rheight = height - gap * 2;
	builder.ChangeHeight(rheight);
	builder.ChangeWidth(rwidth);
	builder.ChangeStyle(FlatButtonStyleInvisble);

	forceDisconnect.Visit(&builder);
}

void windows_quickbuttons::ApplyFonts(CWindowsFontApplier& fontappl)
{
	forceDisconnect.Visit(&fontappl);
}

void windows_quickbuttons::Show()
{
	forceDisconnect.Show();
}

void windows_quickbuttons::Hide()
{
	forceDisconnect.Hide();
}

void windows_quickbuttons::Handler_ClickButton(WPARAM wparam)
{
	if (LOWORD(wparam) == forceDisconnect.id)
	{
		iw5mp_changedata::ForceJumpToMenu();
	}
}

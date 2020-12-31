#include "pch.h"
#include "windows_cfgbuttons.h"
#include "compiletime_XORstring.h"

namespace windows_cfgbuttons
{
	 CWindow_button saveCfg;
	 CWindow_button loadCfg;
	 wchar_t ws_saveCfg[wstringSzFromSizeof(sizeof(L"save"))] = { 0 };
	 wchar_t ws_loadCfg[wstringSzFromSizeof(sizeof(L"load"))] = { 0 };
};

static CONSTEXPRENCRYPTSTRW(ws_saveCfg, L"save", 0x5690);
static CONSTEXPRENCRYPTSTRW(ws_loadCfg, L"load", 0x1690);
#define DECRYPT_saveCfg DECRYPTCONSTENCSTRW(ws_saveCfg, sizeof(L"save") / sizeof(wchar_t), 0x5690)
#define DECRYPT_loadCfg DECRYPTCONSTENCSTRW(ws_loadCfg, sizeof(L"load") / sizeof(wchar_t), 0x1690)

void windows_cfgbuttons::Build(CWindowsBuilder& builder, int left, int width, int top, int height, int gap, HWND hwnd)
{
	DWORD FlatButtonStyleInvisble = (WS_CHILD & ~WS_VISIBLE) | BS_PUSHBUTTON | BS_CENTER | BS_FLAT;
	builder.ChangeStyle(FlatButtonStyleInvisble);

	int rwidth = width / 2 - gap * 2;
	int rheight = height - gap * 2;

	builder.ChangeHeight(rheight);
	builder.ChangeWidth(rwidth);
	builder.ChangeParentHWND(hwnd);
	builder.ChangeLeftPos(left);
	builder.ChangeTopPos(top);
	copy_string_w((wchar_t*)ws_saveCfg, wstringSzFromSizeof(sizeof(ws_saveCfg)), DECRYPT_saveCfg, wstringSzFromSizeof(sizeof(L"save")));
	builder.ChangeTextP(ws_saveCfg);
	saveCfg.Visit(&builder);
	copy_string_w((wchar_t*)ws_loadCfg, wstringSzFromSizeof(sizeof(ws_loadCfg)), DECRYPT_loadCfg, wstringSzFromSizeof(sizeof(L"load")));
	builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
	builder.ChangeTextP(ws_loadCfg);
	loadCfg.Visit(&builder);
}

void windows_cfgbuttons::ApplyFonts(CWindowsFontApplier& fontappl)
{
	loadCfg.Visit(&fontappl);
	saveCfg.Visit(&fontappl);
}

void windows_cfgbuttons::Show()
{
	loadCfg.Show();
	saveCfg.Show();
}

void windows_cfgbuttons::Hide()
{
	loadCfg.Hide();
	saveCfg.Hide();
}



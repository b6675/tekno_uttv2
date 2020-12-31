#pragma once
#include "CWindowsBuilder.h"
#include "CWindowsFontApplier.h"

namespace windows_cfgbuttons
{
	extern CWindow_button saveCfg;
	extern CWindow_button loadCfg;

    void Build(CWindowsBuilder& builder, int left, int width, int top, int height, int gap, HWND hwnd);
    void ApplyFonts(CWindowsFontApplier& fontappl);
    void Show();
    void Hide();

};
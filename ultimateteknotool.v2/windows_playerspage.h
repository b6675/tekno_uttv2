#pragma once
#include "CWindowsBuilder.h"
#include "CWindowsFontApplier.h"
#include "CWindowTextWriter.h"
#include "CWindowTextReader.h"
#include "CWinAPIFileW.h"
#include "CWindowCfgWriter.h"
#include "CWindowCfgReader.h"
#include "CWindowTextLimiter.h"

namespace windows_playerspage
{
    void Build(CWindowsBuilder& builder, int left, int width, int top, int height, HWND hwnd);
    void ApplyFonts(CWindowsFontApplier& fontappl);
    void ApplyTextLimits();
    void Show();
    void Hide();

    void PrintPlayersData();
    void Handler_ClickButton(WPARAM wparam);
};
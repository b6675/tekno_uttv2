#pragma once
#include "CWindowsBuilder.h"
#include "CWindowsFontApplier.h"
#include "CWindowTextWriter.h"
#include "CWindowTextReader.h"

namespace windows_injectorpage {

    void Build(CWindowsBuilder& builder, int left, int width, int top, int height, HWND hwnd);
    void ApplyFonts(CWindowsFontApplier& fontappl);
    void Show();
    void Hide();
    void ButtonHandler(WPARAM& param);
};
#pragma once
#include "CWindowsBuilder.h"
#include "CWindowsFontApplier.h"
#include "windows_accountpage.h"
#include "windows_injectorpage.h"
#include "windows_playerspage.h"

namespace windows_maincontrolbuttons {
    constexpr wchar_t ws_Account[] = L"Account";
    constexpr wchar_t ws_Players[] = L"Players";
    constexpr wchar_t ws_Injector[] = L"Injector";
    extern CWindow_button Account;
    extern CWindow_button Players;
    extern CWindow_button Injector;


    void Build(CWindowsBuilder& builder, int left, int width, int top, int height, HWND hwnd);
    void ApplyFonts(CWindowsFontApplier& fontappl);
    void Show();
    void ButtonHandler(WPARAM& param);
};
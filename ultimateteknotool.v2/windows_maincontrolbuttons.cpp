#include "pch.h"
#include "windows_maincontrolbuttons.h"

namespace windows_maincontrolbuttons {
    CWindow_button Account;
    CWindow_button Players;
    CWindow_button Injector;

    void Build(CWindowsBuilder& builder,  int left, int width, int top, int height,  HWND hwnd)
    {
        builder.ChangeParentHWND(hwnd);
        builder.ChangeLeftPos(left);
        builder.ChangeTopPos(top);


        DWORD FlatButtonStyleInvisble = (WS_CHILD & ~WS_VISIBLE) | BS_PUSHBUTTON | BS_CENTER | BS_FLAT;
        builder.ChangeStyle(FlatButtonStyleInvisble);


        int freewidth = width - left * 2;
        int numberofbuttons = 3;
        int gap = 5;
        int rwidth = (freewidth - numberofbuttons * gap) / numberofbuttons;

        builder.ChangeTextP(ws_Account);
        builder.ChangeWidth(rwidth);
        builder.ChangeHeight(20);
       
        Account.Visit(&builder);

        builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
        builder.ChangeTextP(ws_Players);

        Players.Visit(&builder);

        builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
        builder.ChangeTextP(ws_Injector);

        Injector.Visit(&builder);
    }
    void ApplyFonts(CWindowsFontApplier& fontappl)
    {
        if (Account.hwnd != 0) { Account.Visit(&fontappl); }
        if (Players.hwnd != 0) { Players.Visit(&fontappl); }
        if (Injector.hwnd != 0) { Injector.Visit(&fontappl); }
    }
    void Show()
    {
        Account.Show();
        Players.Show();
        Injector.Show();
    }

    void Show_Account_HideOthers()
    {
        windows_injectorpage::Hide();
        windows_playerspage::Hide();
        windows_accountpage::Show();
    }

    void Show_Injector_HideOthers()
    {
        windows_accountpage::Hide();
        windows_playerspage::Hide();
        windows_injectorpage::Show();
    }

    void Show_Players_HideOthers()
    {
        windows_injectorpage::Hide();
        windows_accountpage::Hide();
        windows_playerspage::Show();
    }

	void ButtonHandler(WPARAM& param)
	{
        
        if (LOWORD(param) == Account.id)
        {
            Show_Account_HideOthers();
        }
        else if (LOWORD(param) == Players.id)
        {
            Show_Players_HideOthers();
        }
        else if (LOWORD(param) == Injector.id)
        {
            Show_Injector_HideOthers();
        }
        else
        {

        }
	}
};

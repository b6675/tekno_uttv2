#include "pch.h"
#include "constexprcolorcodes.h"
#include "WinMainProc.h"
#include "CWindowsBuilder.h"
#include "CWindowsFontApplier.h"
#include "CWindowTextWriter.h"
#include "MainWindowSizes.cpp"
#include "windows_maincontrolbuttons.h"
#include "windows_accountpage.h"
#include "windows_cfgbuttons.h"
#include "windows_injectorpage.h"
#include "cfg_functions.h"
#include "HFont_Wrapper.h"
#include "LazyBuffer_512wchart.h"
#include "PatternSearcher.h"
#include "windows_playerspage.h"
#include "windows_quickbuttons.h"


static HFont_Wrapper hFontWrap;
static HDC HDeviceC;
static PAINTSTRUCT PaintStruct = { 0 };
static constexpr int mainbuttonbackgroundtopoffset = 5;
static constexpr int mainbuttonbackgroundheight = 30;
static DWORD dynamic_background_color = constexprcolorcodes::Color_00DDDAFA;
static bool WindowAreInitedAndReadyToDispatchWMCOMMANDs = false;



LRESULT CALLBACK windowsMain::MainWinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			WindowAreInitedAndReadyToDispatchWMCOMMANDs = false;
			hFontWrap.HFONT_Wrap(CreateFontW(((int)(-11)), 0, 0, 0,
				FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				0x31u, L"Courier New"));
			RECT rect = { 0 };
			::GetClientRect(hwnd, &rect);
			CWindowsBuilder BUILDER;
			CWindowsFontApplier FONTAPPLER(hFontWrap);
			/*
				give free box for building, don't build windows with negative offsets?
			*/
			windows_maincontrolbuttons::Build(BUILDER, 5, MainWindowSizes::width, mainbuttonbackgroundtopoffset, MainWindowSizes::height, hwnd);
			windows_maincontrolbuttons::ApplyFonts(FONTAPPLER);
			windows_maincontrolbuttons::Show();

			int gap = 2;
			int freewidth = rect.right / 10;
			int leftpos = rect.right - freewidth * 3 ;

			int freeheight = rect.bottom / 18;
			int toppos = rect.bottom - freeheight;

			windows_quickbuttons::Build(BUILDER, leftpos, freewidth, toppos, freeheight, gap, hwnd);
			windows_quickbuttons::ApplyFonts(FONTAPPLER);
			windows_quickbuttons::Show();
			leftpos += freewidth;
			freewidth = freewidth + freewidth - freewidth / 5;
			windows_cfgbuttons::Build(BUILDER, leftpos, freewidth, toppos, freeheight, gap, hwnd);
			windows_cfgbuttons::ApplyFonts(FONTAPPLER);
			windows_cfgbuttons::Show();



			windows_accountpage::Build(BUILDER, 8, MainWindowSizes::width, mainbuttonbackgroundheight + 5, MainWindowSizes::height, hwnd);
			windows_accountpage::ApplyFonts(FONTAPPLER);
			windows_accountpage::ApplyTextLimits();
			windows_accountpage::Show();

			windows_injectorpage::Build(BUILDER, 8, rect.right, mainbuttonbackgroundheight + 5, rect.bottom, hwnd);
			windows_injectorpage::ApplyFonts(FONTAPPLER);
			windows_injectorpage::Hide();

			windows_playerspage::Build(BUILDER, 8, rect.right, mainbuttonbackgroundheight + 5, rect.bottom, hwnd);
			windows_playerspage::ApplyFonts(FONTAPPLER);
			windows_playerspage::ApplyTextLimits();
			windows_playerspage::Hide();

			cfg_functions::LoadDefaultOrExistingCfg();
			
#ifdef UTT2_DEBUG
			LazySectionBuffer<wchar_t, 256, 3> SectionBuffer;
			if (SectionBuffer.Test1()) {
				LazySectionBuffer<wchar_t, 32, 6> SectionBuffer2;
				WCWOUT("SectionBuffer.Test1() returned: success");
				if (SectionBuffer2.Test2()) { WCWOUT("SectionBuffer.Test2() returned: success"); }
			}
			
#endif
			WindowAreInitedAndReadyToDispatchWMCOMMANDs = true;
			break;
		}
		case WM_SETFOCUS:
		{
			break;
		}
		case WM_SIZE:
		{
			break;
		}
		case WM_SIZING:
		{
			break;
		}
		case WM_TIMER:
		{
			break;
		}
		case WM_COMMAND:
		{
			if (WindowAreInitedAndReadyToDispatchWMCOMMANDs) {
				
				if (LOWORD(wparam) == windows_cfgbuttons::loadCfg.id)
				{
					cfg_functions::LoadCfgFromFile();
					break;
				}
				else if (LOWORD(wparam) == windows_cfgbuttons::saveCfg.id)
				{
					cfg_functions::SaveCfgInFile();
					break;
				}
				else if (windows_maincontrolbuttons::Account.id == LOWORD(wparam))
				{

				}
				windows_maincontrolbuttons::ButtonHandler(wparam);
				windows_accountpage::Handler_ClickButton(wparam);
				windows_injectorpage::ButtonHandler(wparam);
				windows_playerspage::Handler_ClickButton(wparam);
				windows_quickbuttons::Handler_ClickButton(wparam);
			}
			break;
		}
		case WM_PAINT:
		{
			HDeviceC = ::BeginPaint(hwnd, &PaintStruct);
			HGDIOBJ original = NULL;
			original = ::SelectObject(HDeviceC, GetStockObject(DC_PEN));

			::SetBkColor(HDeviceC, dynamic_background_color);
			::SetTextColor(HDeviceC, dynamic_background_color);
			::SelectObject(HDeviceC, GetStockObject(DC_PEN));
			::SelectObject(HDeviceC, GetStockObject(DC_BRUSH));
			::SetDCPenColor(HDeviceC, dynamic_background_color);
			::SetDCBrushColor(HDeviceC, dynamic_background_color);
			::Rectangle(HDeviceC, 0, mainbuttonbackgroundtopoffset, MainWindowSizes::width, mainbuttonbackgroundheight- mainbuttonbackgroundtopoffset);
		
			::SelectObject(HDeviceC, original);
			::EndPaint(hwnd, &PaintStruct);
			::ReleaseDC(hwnd, HDeviceC);
			break;
		}

		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
		default:
		{break; }
	}
	return (DefWindowProc(hwnd, msg, wparam, lparam));
}

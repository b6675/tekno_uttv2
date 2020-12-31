#include "pch.h"
#include "constexprcolorcodes.h"
#include "TheWinMain.h"
#include "WinMainProc.h"
#include "MainWindowSizes.cpp"

static HWND MainHwnd = NULL;

bool windowsMain::WinStart()
{
	HBRUSH hbkgrbrush = CreateSolidBrush(constexprcolorcodes::Color_00FAFAFF);
	HICON hIconLarge = NULL;
	HICON hIconSmall = NULL;
	UINT ExtactRetL = 0;
	UINT ExtactRetS = 0;
	ExtactRetL = ::ExtractIconExA("iw5mp.exe", 0, &hIconLarge, 0, 1);
	ExtactRetS = ::ExtractIconExA("iw5mp.exe", 0, 0, &hIconSmall, 1);
	WNDCLASSEXW WClass;
	WClass.cbSize = sizeof(WNDCLASSEXW);
	WClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
	WClass.lpfnWndProc = windowsMain::MainWinProc;
	WClass.cbClsExtra = 0;
	WClass.cbWndExtra = 0;
	WClass.hInstance = ::GetModuleHandle(NULL);
	if (ExtactRetL) WClass.hIcon = hIconLarge;
	else WClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WClass.hbrBackground = hbkgrbrush;
	WClass.lpszMenuName = NULL;
	WClass.lpszClassName = classname;
	if (ExtactRetS) WClass.hIconSm = hIconSmall;
	else WClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!::RegisterClassEx(&WClass))
	{
		return false;
	}
	int v1 = ::GetSystemMetrics(SM_CXFULLSCREEN);
	int v2 = ::GetSystemMetrics(SM_CYFULLSCREEN);
	RECT rect = { 0, 0 , MainWindowSizes::width , MainWindowSizes::height };
	MainHwnd = ::CreateWindowExW(0, classname, L"iw5mp", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX | WS_VISIBLE,
		(v1 - MainWindowSizes::width) / 2, (v2 - MainWindowSizes::height) / 2,
		MainWindowSizes::width, MainWindowSizes::height, NULL, 0, ::GetModuleHandle(NULL), 0);
	if (!MainHwnd)
	{
		return false;
	}
	ShowWindow(MainHwnd, SW_SHOWDEFAULT);
	UpdateWindow(MainHwnd);
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	
	while (GetMessage(&msg, NULL, 0, 0))
	{

		//WinMainLoop();
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

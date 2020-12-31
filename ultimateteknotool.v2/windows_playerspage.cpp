#include "pch.h"
#include "windows_playerspage.h"
#include "TextConvertors.h"
#include "iw5mp_players_functions.h"
#include "compiletime_XORstring.h"

static CONSTEXPRENCRYPTSTRW(str18, L"18", 0x13FA);
static CONSTEXPRENCRYPTSTRW(str_initial, L"initial", 0x12FA);
static CONSTEXPRENCRYPTSTRW(str_refresh, L"refresh", 0x3031);
static CONSTEXPRENCRYPTSTRW(str_kick, L"kick", 0x5690);
#define DECRYPT_18 DECRYPTCONSTENCSTRW(str18, sizeof(L"18") / sizeof(wchar_t), 0x13FA)
#define DECRYPT_initial DECRYPTCONSTENCSTRW(str_initial, sizeof(L"initial") / sizeof(wchar_t), 0x12FA)
#define DECRYPT_refresh DECRYPTCONSTENCSTRW(str_refresh, sizeof(L"refresh") / sizeof(wchar_t), 0x3031)
#define DECRYPT_kick DECRYPTCONSTENCSTRW(str_kick, sizeof(L"kick") / sizeof(wchar_t), 0x5690)

namespace windows_playerspage
{
	CWindow_edit playersDataOutput;
	CWindow_button forceRefresh;
	CWindow_edit player_index;
	CWindow_button kickbutton;
	wchar_t ws_index[wstringSzFromSizeof(sizeof(L"18"))] = { 0 };
	wchar_t ws_initial[wstringSzFromSizeof(sizeof(L"initial"))] = { 0 };
	wchar_t ws_refresh[wstringSzFromSizeof(sizeof(L"refresh"))] = { 0 };
	wchar_t ws_kick[wstringSzFromSizeof(sizeof(L"kick"))] = { 0 };
	void SetText(const wchar_t* text)
	{
		::SendMessageW(playersDataOutput.hwnd, WM_SETTEXT, 0 /*not used */, reinterpret_cast<LPARAM>(text));
	}
	static bool shown = false;

	static uint32_t currentPlayerIndex = 20;

};

void windows_playerspage::Build(CWindowsBuilder& builder, int left, int width, int top, int height, HWND hwnd)
{
	constexpr DWORD EDITSTYLE = WS_CHILD & ~WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY;
	constexpr DWORD FlatButtonStyleInvisble = (WS_CHILD & ~WS_VISIBLE) | BS_PUSHBUTTON | BS_CENTER | BS_FLAT;
	constexpr DWORD NewEditStyle_Invisible = WS_CHILD & ~WS_VISIBLE | WS_BORDER;
	builder.ChangeParentHWND(hwnd);
	builder.ChangeLeftPos(left);
	builder.ChangeTopPos(top);

	int rwidth = width - width / 8;
	int rheight = height - height / 4;
	builder.ChangeHeight(rheight);
	builder.ChangeWidth(rwidth);
	builder.ChangeStyle(EDITSTYLE);
	copy_string_w((wchar_t*)ws_initial, wstringSzFromSizeof(sizeof(ws_initial)), DECRYPT_initial, wstringSzFromSizeof(sizeof(L"initial")));
	builder.ChangeTextP(ws_initial);
	playersDataOutput.Visit(&builder);

	builder.ChangeTopPos(builder.build_top_pos + builder.build_height + 5);
	rwidth = 70;
	rheight = 20;
	builder.ChangeHeight(rheight);
	builder.ChangeWidth(rwidth);
	builder.ChangeStyle(FlatButtonStyleInvisble);
	copy_string_w((wchar_t*)ws_refresh, wstringSzFromSizeof(sizeof(ws_refresh)), DECRYPT_refresh, wstringSzFromSizeof(sizeof(L"refresh")));
	builder.ChangeTextP(ws_refresh);
	forceRefresh.Visit(&builder);

	rwidth = 30;
	builder.ChangeStyle(NewEditStyle_Invisible);
	builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + 5);
	copy_string_w((wchar_t*)ws_index, wstringSzFromSizeof(sizeof(ws_index)), DECRYPT_18, wstringSzFromSizeof(sizeof(L"18")));
	builder.ChangeTextP(ws_index);
	player_index.Visit(&builder);

	rwidth = 60;
	builder.ChangeStyle(FlatButtonStyleInvisble);
	builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + 5);
	copy_string_w((wchar_t*)ws_kick, wstringSzFromSizeof(sizeof(ws_kick)), DECRYPT_kick, wstringSzFromSizeof(sizeof(L"kick")));
	builder.ChangeTextP(ws_kick);
	kickbutton.Visit(&builder);
}

void windows_playerspage::ApplyFonts(CWindowsFontApplier& fontappl)
{
	playersDataOutput.Visit(&fontappl);
	forceRefresh.Visit(&fontappl);
	kickbutton.Visit(&fontappl);
	player_index.Visit(&fontappl);
}

void windows_playerspage::ApplyTextLimits()
{
	CWindowTextLimiter_LimitText(&playersDataOutput, iw5mp_getdata::players_data::XUIDandNETData_BUFFER_SIZE);
}

void windows_playerspage::Show()
{
	playersDataOutput.Show();
	forceRefresh.Show();
	kickbutton.Show();
	player_index.Show();
	shown = true;
}

void windows_playerspage::Hide()
{
	playersDataOutput.Hide();
	forceRefresh.Hide();
	kickbutton.Hide();
	player_index.Hide();
	shown = false;
}

void windows_playerspage::PrintPlayersData()
{
	SetText(iw5mp_getdata::players_data::GetPackedData_XUIDandNETData());
}



void windows_playerspage::Handler_ClickButton(WPARAM wparam)
{
	if (LOWORD(wparam) == forceRefresh.id)
	{
		SetText(iw5mp_getdata::players_data::GetPackedData_XUIDandNETData());
	}
	else if (LOWORD(wparam) == kickbutton.id)
	{
		currentPlayerIndex = textconvertors::ConvertWTextDecTypeToU16(CWindowTextReader_GetTextW(&player_index, 4));
		WCWOUT("Kicking player, index: ", std::dec, currentPlayerIndex);
		iw5mp_exploits::KickUserViaND(currentPlayerIndex);
	}
	else
	{

	}
	
}

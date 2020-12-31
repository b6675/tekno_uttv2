#include "pch.h"
#include "iw5mp_nickname_etc_functions.h"
#include "iw5mp_addresses_declaration.h"
#include "iw5mp_constants.h"

#include "debugconsole.h"

namespace iw5mp_changedata
{

	// static_assert(sizeof(wchar_t) == sizeof(char) * 2, "something is weird!");
	static_assert(sizeof(wchar_t) == sizeof(uint8_t) * 2, "something is weird!");
	static_assert(L'A' == 'A', "");

	void ChangeTextData(wchar_t* textpointer, uint8_t* addr, const uint8_t maxtextlen)
	{
		uint8_t counter = 0;
		uint8_t counter_wchart = 0;
		uint8_t* raddr = addr;
		uint8_t* txtp = reinterpret_cast<uint8_t*>(textpointer);
		for (; counter < maxtextlen && txtp[counter_wchart];)
		{
			raddr[counter] = txtp[counter_wchart];
			counter_wchart += 2;
			counter++;
		}
		if (counter < maxtextlen)
		{
			raddr[counter] = 0x00;
		}
		else
		{
			raddr[maxtextlen - 1] = 0x00;
		}
	}

	void ChangeNickname(wchar_t* textpointer)
	{
		uint8_t* raddr = (uint8_t*)(*reinterpret_cast<uint32_t*>(iw5mp_addresses::SteamAPI_RegisterCallback_1) + 322);
		if (iw5mp_addresses::sections::IsAddressPlacedAfterDataEnd(reinterpret_cast<uint32_t>(raddr)) == false) { return; }
		ChangeTextData(textpointer, raddr, iw5mp_constants::MAX_LENGTH_NICKNAME);
		raddr = reinterpret_cast<uint8_t*>(iw5mp_addresses::NicknameBuffer);
		ChangeTextData(textpointer, raddr, iw5mp_constants::MAX_LENGTH_NICKNAME);

	}
	void ChangeTitle(wchar_t* textpointer)
	{
		AllowCustomTitle();
		uint8_t* raddr = reinterpret_cast<uint8_t*>(iw5mp_addresses::TitleBuffer);
		ChangeTextData(textpointer, raddr, iw5mp_constants::MAX_LENGTH_TITLE);
	}
	void ChangeClanTag(wchar_t* textpointer)
	{
		AllowClanTag();
		uint8_t* raddr = reinterpret_cast<uint8_t*>(iw5mp_addresses::ClanTagBuffer);
		ChangeTextData(textpointer, raddr, iw5mp_constants::MAX_LENGTH_CLANTAG);
	}

	void AllowCustomTitle()
	{
		uint8_t* raddr = reinterpret_cast<uint8_t*>(iw5mp_addresses::TitleCustomTextIsAllowed);
		*raddr = 0x01;
	}
	void DisableCustomTitle()
	{
		uint8_t* raddr = reinterpret_cast<uint8_t*>(iw5mp_addresses::TitleCustomTextIsAllowed);
		*raddr = 0x00;
	}
	void AllowClanTag()
	{
		uint8_t* raddr = reinterpret_cast<uint8_t*>(iw5mp_addresses::ClanTagIsAllowed);
		*raddr = 0x01;
	}
	void DisableClanTag()
	{
		uint8_t* raddr = reinterpret_cast<uint8_t*>(iw5mp_addresses::ClanTagIsAllowed);
		*raddr = 0x00;
	}
	void ChangeTitleType(uint32_t value)
	{
		uint32_t* raddr = reinterpret_cast<uint32_t*>(iw5mp_addresses::TitleTypeValue);
		*raddr = value;
	}
	void ChangeEmblemType(uint32_t value)
	{
		uint32_t* raddr = reinterpret_cast<uint32_t*>(iw5mp_addresses::EmblemTypeValue);
		*raddr = value;
	}

	void ChangePrestige(uint32_t value)
	{
		uint32_t* raddr = reinterpret_cast<uint32_t*>(iw5mp_addresses::PrestigeValue);
		*raddr = value;
	}

	void ChangeLevel(uint32_t value)
	{
		if (value >= 1)
		{
			value -= 1;
		}
		if (value <= iw5mp_constants::maxvalidlevel)
		{
			*(reinterpret_cast<uint32_t*>(iw5mp_addresses::TotalXPValue)) = iw5mp_constants::XP_TO_LEVEL[value];
		}
	}


};


namespace iw5mp_getdata
{
	static wchar_t ws_CurrentNickname[iw5mp_constants::MAX_LENGTH_NICKNAME] = { 0 };
	static wchar_t ws_CurrentTitle[iw5mp_constants::MAX_LENGTH_TITLE] = { 0 };
	static wchar_t ws_CurrentClanTag[iw5mp_constants::MAX_LENGTH_CLANTAG] = { 0 };


	void GetTextData(wchar_t* buf, const uint8_t bufsisze, uint8_t* src)
	{
		if (bufsisze < 2) { throw 1; }
		for (uint8_t i = 0; i < bufsisze; i++)
		{
			buf[i] = 0x0000;
		}
		for (uint8_t i = 0; i < bufsisze && src[i]; i++)
		{
			buf[i] = static_cast<wchar_t>(src[i]);
		}
		buf[bufsisze - 1] = 0x0000;
	}
	wchar_t* GetNickname()
	{
		uint8_t* raddr = reinterpret_cast<uint8_t*>(iw5mp_addresses::NicknameBuffer);
		static_assert(sizeof(ws_CurrentNickname)/sizeof(wchar_t) == iw5mp_constants::MAX_LENGTH_NICKNAME, "wrong size");
		GetTextData(ws_CurrentNickname, iw5mp_constants::MAX_LENGTH_NICKNAME, raddr);
		return ws_CurrentNickname;
	}
	wchar_t* GetTitle()
	{
		uint8_t* raddr = reinterpret_cast<uint8_t*>(iw5mp_addresses::TitleBuffer);
		static_assert(sizeof(ws_CurrentTitle) / sizeof(wchar_t) == iw5mp_constants::MAX_LENGTH_TITLE, "wrong size");
		GetTextData(ws_CurrentTitle, iw5mp_constants::MAX_LENGTH_TITLE, raddr);
		return ws_CurrentTitle;
	}
	wchar_t* GetClanTag()
	{
		uint8_t* raddr = reinterpret_cast<uint8_t*>(iw5mp_addresses::ClanTagBuffer);
		static_assert(sizeof(ws_CurrentClanTag) / sizeof(wchar_t) == iw5mp_constants::MAX_LENGTH_CLANTAG, "wrong size");
		GetTextData(ws_CurrentClanTag, iw5mp_constants::MAX_LENGTH_CLANTAG, raddr);
		return ws_CurrentClanTag;
	}

	uint32_t GetTitleType() noexcept
	{
		return *reinterpret_cast<uint32_t*>(iw5mp_addresses::TitleTypeValue);
	}

	uint32_t GetEmblem() noexcept
	{
		return *reinterpret_cast<uint32_t*>(iw5mp_addresses::EmblemTypeValue);
	}

	uint32_t GetPrestige() noexcept
	{
		return *reinterpret_cast<uint32_t*>(iw5mp_addresses::PrestigeValue);
	}

	uint8_t GetLevel() noexcept
	{
		uint32_t CurLevel = *(reinterpret_cast<uint32_t*>(iw5mp_addresses::TotalXPValue));
		for (uint8_t i = 0; i <= iw5mp_constants::maxvalidlevel; i++)
		{
			if (CurLevel < iw5mp_constants::XP_TO_LEVEL[i])
			{
				return i;
			}
		}
		return 0;
	}

	
};

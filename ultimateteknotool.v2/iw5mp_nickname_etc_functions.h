#pragma once
#include <stdint.h>

namespace iw5mp_changedata
{
	void ChangeNickname(wchar_t* textpointer);
	void ChangeTitle(wchar_t* textpointer);
	void ChangeClanTag(wchar_t* textpointer);
	void AllowCustomTitle();
	void DisableCustomTitle();
	void AllowClanTag();
	void DisableClanTag();
	void ChangeTitleType(uint32_t value);
	void ChangeEmblemType(uint32_t value);
	void ChangePrestige(uint32_t value);
	void ChangeLevel(uint32_t value);
};

namespace iw5mp_getdata
{
	wchar_t* GetNickname();
	wchar_t* GetTitle();
	wchar_t* GetClanTag();
	uint32_t GetTitleType()noexcept;
	uint32_t GetEmblem()noexcept;
	uint32_t GetPrestige()noexcept;
	uint8_t GetLevel()noexcept;
};
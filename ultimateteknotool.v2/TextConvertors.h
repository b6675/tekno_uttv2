#pragma once
#include <stdint.h>
#include <sstream>
#include "LazyBuffer.h"

namespace textconvertors
{
	/* never hold returned pointers if you don't know what you exactly do */

	uint32_t ConvertWTextHexTypeToU32(const wchar_t* text);
	uint32_t ConvertWTextDecTypeToU32(const wchar_t* text);
	const wchar_t* ConvertHexTypeU32ToWText(const uint32_t v);
	const wchar_t* ConvertDecTypeU32ToWText(const uint32_t v);

	uint16_t ConvertWTextDecTypeToU16(const wchar_t* text);
	const wchar_t* ConvertDecTypeToU16ToWText(const uint16_t v);

	void ConvertWTextToIP(const wchar_t* text, uint8_t NewIP[4]);
	const wchar_t* ConvertIPToWText(const uint8_t NewIP[4]);

	const wchar_t* ConvertU8TextToWText_StupidButFast(const uint8_t* data, unsigned short sz);
	
	const wchar_t* ConvertU8TextToWText_StupidButFast_graphNspace(const uint8_t* data, unsigned short sz);
	const wchar_t* ConvertCharTextToWText_StupidButFast(const char* data, unsigned short sz);

	const uint8_t* ConvertWTextToU8Text(const wchar_t* src, unsigned short sz);
	const char* ConvertWTextToCharText(const wchar_t* src, unsigned short sz);

	namespace ret_stdstring
	{
		const std::wstring& ConvertDecTypeU32ToWText(const uint32_t v);
		const std::wstring& ConvertHexTypeU32ToWText(const uint32_t v);
		const std::wstring& ConvertDecTypeU16ToWText(const uint16_t v);
		const std::wstring& ConvertIPToWText(const uint8_t NewIP[4]);
	};
};


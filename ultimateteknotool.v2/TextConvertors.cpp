#include "pch.h"
#include "TextConvertors.h"


static std::wistringstream inputWstringstream;
static std::wostringstream outputWstringstream(L"");
static std::wstring aaaaaa;
static LazyBuffer_wchart<256> LazyW256;
static LazyBuffer_char<256> LazyC256;

uint32_t textconvertors::ConvertWTextHexTypeToU32(const wchar_t* text)
{
	inputWstringstream.clear();
	inputWstringstream.str(text);
	uint32_t ret = 0;
	if (inputWstringstream >> std::hex >> ret)
	{
		return ret;
	}
	else
	{
		return 0;
	}
}

uint32_t textconvertors::ConvertWTextDecTypeToU32(const wchar_t* text)
{
	inputWstringstream.clear();
	inputWstringstream.str(text);
	uint32_t ret = 0;
	if (inputWstringstream >> std::dec >> ret)
	{
		return ret;
	}
	else
	{
		return 0;
	}
}



const wchar_t* textconvertors::ConvertHexTypeU32ToWText(const uint32_t value)
{
	//greatstringstream.clear();
	outputWstringstream.str(L"00000000");
	outputWstringstream << std::hex << value;
	aaaaaa = outputWstringstream.str();
	return aaaaaa.c_str();
}

const wchar_t* textconvertors::ConvertDecTypeU32ToWText(const uint32_t value)
{
	//greatstringstream.clear();
	outputWstringstream.str(L"0");
	outputWstringstream << std::dec << value;
	aaaaaa = outputWstringstream.str();
	return aaaaaa.c_str();
}

uint16_t textconvertors::ConvertWTextDecTypeToU16(const wchar_t* text)
{
	inputWstringstream.clear();
	inputWstringstream.str(text);
	uint16_t PortInput = 0;
	if (inputWstringstream >> std::dec >> PortInput) {
		return PortInput;
	}
	else
	{
		return 0;
	}
}

const wchar_t* textconvertors::ConvertDecTypeToU16ToWText(const uint16_t value)
{
	outputWstringstream.str(L"0");
	outputWstringstream << std::dec << value;
	aaaaaa = outputWstringstream.str();
	return aaaaaa.c_str();
}

void textconvertors::ConvertWTextToIP(const wchar_t* text, uint8_t NewIP[4])
{
	inputWstringstream.clear();
	inputWstringstream.str(text);
	wchar_t ignore;
	uint32_t NewIPinput[4];
	if (inputWstringstream >> std::dec >> NewIPinput[0] >> ignore >> NewIPinput[1] >> ignore >> NewIPinput[2] >> ignore >> NewIPinput[3])
	{
		NewIPinput[0] <<= 24; NewIPinput[1] <<= 24; NewIPinput[2] <<= 24; NewIPinput[3] <<= 24;
		NewIP[0] = ((NewIPinput[0] >> 24) & 0xFF);
		NewIP[1] = ((NewIPinput[1] >> 24) & 0xFF);
		NewIP[2] = ((NewIPinput[2] >> 24) & 0xFF);
		NewIP[3] = ((NewIPinput[3] >> 24) & 0xFF);
	}
	else
	{
		NewIP[0] = 0;
		NewIP[1] = 0;
		NewIP[2] = 0;
		NewIP[3] = 0;
	}
}

const wchar_t* textconvertors::ConvertIPToWText(const uint8_t NewIP[4])
{
	outputWstringstream.str(L"");
	outputWstringstream << std::dec <<
		static_cast<uint16_t>(NewIP[0]) << L'.' <<
		static_cast<uint16_t>(NewIP[1]) << L'.' <<
		static_cast<uint16_t>(NewIP[2]) << L'.' <<
		static_cast<uint16_t>(NewIP[3]);
	aaaaaa = outputWstringstream.str();
	return aaaaaa.c_str();
}

const wchar_t* textconvertors::ConvertU8TextToWText_StupidButFast(const uint8_t* data, unsigned short sz)
{
	wchar_t* diesoon = LazyW256.GetNulledMem(sz + 2);
	for (size_t i = 0; i < sz && data[i]; i++)
	{
		diesoon[i] = static_cast<wchar_t>(data[i]);
	}
	return diesoon;
}


const wchar_t* textconvertors::ConvertU8TextToWText_StupidButFast_graphNspace(const uint8_t* data, unsigned short sz)
{
	wchar_t* diesoon = LazyW256.GetNulledMem(sz + 2);
	for (size_t i = 0; i < sz && (::isgraph(data[i]) || data[i] == static_cast<uint8_t>(' ')); i++)
	{
		diesoon[i] = static_cast<wchar_t>(data[i]);
	}
	return diesoon;
}

const wchar_t* textconvertors::ConvertCharTextToWText_StupidButFast(const char* data, unsigned short sz)
{
	wchar_t* diesoon = LazyW256.GetNulledMem(sz + 2);
	for (size_t i = 0; i < sz && data[i]; i++)
	{
		diesoon[i] = static_cast<wchar_t>(data[i]);
	}
	return diesoon;
}

static_assert(sizeof(wchar_t) == sizeof(char) * 2, "size of wchar_t is not equal to size of two char");
static_assert(sizeof(wchar_t) == sizeof(uint8_t) * 2, "size of wchar_t is not equal to size of two uint8_t");
static_assert(sizeof(char) == sizeof(uint8_t), "size of char is not equal to size of uint8_t");

const uint8_t* textconvertors::ConvertWTextToU8Text(const wchar_t* src, unsigned short sz)
{
	uint8_t* diesoon = reinterpret_cast<uint8_t*>(LazyC256.GetNulledMem(sz + 2));
	const uint8_t* txtp = reinterpret_cast<const uint8_t*>(src);
	for (decltype(sz) i = 0; i < sz && txtp[2*i]; i++)
	{
		diesoon[i] = txtp[2 * i];
	}
	return diesoon;
}

const char* textconvertors::ConvertWTextToCharText(const wchar_t* src, unsigned short sz)
{
	char* diesoon = LazyC256.GetNulledMem(sz + 2);
	const char* txtp = reinterpret_cast<const char*>(src);
	for (decltype(sz) i = 0; i < sz && txtp[2 * i]; i++)
	{
		diesoon[i] = txtp[2 * i];
	}
	return diesoon;
}

const std::wstring& textconvertors::ret_stdstring::ConvertDecTypeU32ToWText(const uint32_t v)
{
	outputWstringstream.str(L"0");
	outputWstringstream << std::dec << v;
	aaaaaa = outputWstringstream.str();
	return aaaaaa;
}

const std::wstring& textconvertors::ret_stdstring::ConvertHexTypeU32ToWText(const uint32_t v)
{
	outputWstringstream.str(L"0");
	outputWstringstream << std::hex << v;
	aaaaaa = outputWstringstream.str();
	return aaaaaa; 
}

const std::wstring& textconvertors::ret_stdstring::ConvertDecTypeU16ToWText(const uint16_t v)
{
	outputWstringstream.str(L"0");
	outputWstringstream << std::dec << v;
	aaaaaa = outputWstringstream.str();
	return aaaaaa;
}

const std::wstring& textconvertors::ret_stdstring::ConvertIPToWText(const uint8_t NewIP[4])
{
	outputWstringstream.str(L"");
	outputWstringstream << std::dec <<
		static_cast<uint16_t>(NewIP[0]) << L'.' <<
		static_cast<uint16_t>(NewIP[1]) << L'.' <<
		static_cast<uint16_t>(NewIP[2]) << L'.' <<
		static_cast<uint16_t>(NewIP[3]);
	aaaaaa = outputWstringstream.str();
	return aaaaaa;
}

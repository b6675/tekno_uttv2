#include "pch.h"
#include "PatternSearcher.h"

static_assert(0xFF == (0x0F | 0xF0), "");
static_assert(0xFF == (0xF0 | 0x0F), "");

static constexpr uint8_t PATTERN_MAXSIZE_BYTES = 16;
struct SmartByte
{
	uint8_t value = 0;
	uint8_t mustbeskipped = 0;
};

uint8_t ConvertCharToByte(char left, char right)
{
	uint8_t ret = 0;
	switch (left)
	{
	case '0':
		ret = 0x00;
		break;
	case '1':
		ret = 0x10;
		break;
	case '2':
		ret = 0x20;
		break;
	case '3':
		ret = 0x30;
		break;
	case '4':
		ret = 0x40;
		break;
	case '5':
		ret = 0x50;
		break;
	case '6':
		ret = 0x60;
		break;
	case '7':
		ret = 0x70;
		break;
	case '8':
		ret = 0x80;
		break;
	case '9':
		ret = 0x90;
		break;
	case 'A':
		ret = 0xA0;
		break;
	case 'B':
		ret = 0xB0;
		break;
	case 'C':
		ret = 0xC0;
		break;
	case 'D':
		ret = 0xD0;
		break;
	case 'E':
		ret = 0xE0;
		break;
	case 'F':
		ret = 0xF0;
		break;
	default:
		break;
	}
	switch (right)
	{
	case '0':
		ret = ret | 0x00;
		break;
	case '1':
		ret = ret | 0x01;
		break;
	case '2':
		ret = ret | 0x02;
		break;
	case '3':
		ret = ret | 0x03;
		break;
	case '4':
		ret = ret | 0x04;
		break;
	case '5':
		ret = ret | 0x05;
		break;
	case '6':
		ret = ret | 0x06;
		break;
	case '7':
		ret = ret | 0x07;
		break;
	case '8':
		ret = ret | 0x08;
		break;
	case '9':
		ret = ret | 0x09;
		break;
	case 'A':
		ret = ret | 0x0A;
		break;
	case 'B':
		ret = ret | 0x0B;
		break;
	case 'C':
		ret = ret | 0x0C;
		break;
	case 'D':
		ret = ret | 0x0D;
		break;
	case 'E':
		ret = ret | 0x0E;
		break;
	case 'F':
		ret = ret | 0x0F;
		break;
	default:
		break;
	}
	return ret;
}


uint32_t patternsearcher::PatternSearch(char* pattern, uint32_t start_address, uint32_t maxdeep)
{
	SmartByte BYTES[PATTERN_MAXSIZE_BYTES] = { 0 };
	uint8_t counter = 0;
	uint8_t bytepos = 0;
	for (; pattern[counter] && pattern[counter + 1] && counter/2 < PATTERN_MAXSIZE_BYTES;)
	{
		if (pattern[counter] == '?' && pattern[counter + 1] == '?')
		{
			BYTES[counter/2].mustbeskipped = 0x01;
		}
		else
		{
			BYTES[counter/2].value = ConvertCharToByte(pattern[counter], pattern[counter + 1]);
		}
		counter += 2;
	}

	counter = counter / 2;
	uint32_t RET = start_address;
	uint8_t verify = 0;
	for (; RET < (start_address + maxdeep);)
	{
		if (*reinterpret_cast<uint8_t*>(RET) == BYTES[0].value)
		{
			for (verify = 1; verify < counter; verify++)
			{
				RET++;
				if (BYTES[verify].mustbeskipped == 0x00) {
					if (*reinterpret_cast<uint8_t*>(RET) != BYTES[verify].value)
					{
						break;
					}
					else
					{
						continue;
					}
				}
				else
				{
					continue;
				}
			}
			if (verify == counter) {
				return RET - verify + 1; }
		}
		RET++;
	}
	return 0;
}

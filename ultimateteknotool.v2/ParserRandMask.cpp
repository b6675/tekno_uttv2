#include "pch.h"
#include "ParserRandMask.h"
#include "Randomizer.h"

void parsers::ParseRandMaskTextW(const wchar_t* randmask, const size_t randmask_sz, wchar_t* output, const size_t output_sz)
{
	for (size_t i = 0; i < randmask_sz && i < output_sz; i++)
	{
		if (randmask[i] == 'd')
		{
			output[i] = static_cast<wchar_t>(RANDANSIDIGIT);
		}
		else if (randmask[i] == 'u')
		{
			output[i] = static_cast<wchar_t>(RANDANSIUPPERCASE);
		}
		else if (randmask[i] == 'l')
		{
			output[i] = static_cast<wchar_t>(RANDANSILOWCASE);
		}
		else if (randmask[i] == 'c')
		{
			output[i] = static_cast<wchar_t>(RANDANSICHAR);
		}
		else if (randmask[i] == 'h')
		{
			output[i] = static_cast<wchar_t>(RANDHEXSYMBOL);
		}
		else
		{
			output[i] = randmask[i];
		}
	}
}

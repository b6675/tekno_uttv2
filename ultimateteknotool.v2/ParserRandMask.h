#pragma once

namespace parsers
{
	typedef void (parserfunction_t)(const wchar_t* randmask, const size_t randmask_sz, wchar_t* output, const size_t output_sz);
	void ParseRandMaskTextW(const wchar_t* randmask, const size_t randmask_sz, wchar_t* output, const size_t output_sz);
};
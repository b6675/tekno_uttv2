#pragma once
#include <array>

namespace compile_time
{
	/*
		Encrypt normal char string with xor key +i on compile time
	*/
	template<unsigned char SLEN, unsigned char XKEY, unsigned char XBIT>
	class EncryptString
	{
	private:
		std::array<char, SLEN> _buf;
		constexpr char encrypt(unsigned char c, unsigned char index)
		{
			unsigned char KEY = XKEY;
			KEY += index;
			KEY ^= (1 << (XBIT & 7));
			return c ^ KEY;
		}

	public:
		template <unsigned char ... Is>
		constexpr EncryptString(const char* str, std::index_sequence<Is...>)
			: _buf { { encrypt(str[Is], Is)... } }
		{
		 /* can't do smth here, it is constexpr func */
		}
		char* getData() const { return (char*)this->_buf.data(); }
	};
	/*
		Decrypt to normal string with fake offset
	*/
	template<unsigned char SLEN, unsigned char XKEY, unsigned char XBIT, uint32_t Offset32bit>
	struct DecryptedString
	{
		char _buffer[SLEN + 1];
		DecryptedString(char* encstr)
		{
			char KEY = XKEY;
			for (unsigned char i = 0; i < SLEN; i++)
			{
				KEY = XKEY;
				KEY += i;
				KEY ^= (1 << XBIT);
				_buffer[i] = KEY ^ encstr[i - Offset32bit];
			}
			_buffer[SLEN] = 0;
		}

	};


	static_assert(static_cast<wchar_t>(0xFA00) == (static_cast<wchar_t>(0x00FA) << 8), "");
	template<wchar_t SLEN, wchar_t XKEY>
	class EncryptStringW
	{
	private:
		std::array<wchar_t, SLEN> _buf;
		static_assert(sizeof(wchar_t) == 2 * sizeof(char), "doing byte shit");
		constexpr wchar_t encrypt( wchar_t c, wchar_t index)
		{
			wchar_t KEY = XKEY;
			KEY += (index + (static_cast<wchar_t>(index) << 8));
			return c ^ KEY;
		}

	public:
		template <wchar_t... Is>
		constexpr EncryptStringW(const wchar_t* str, std::index_sequence<Is...>)
			: _buf{ { encrypt(str[Is], Is)... } }
		{
			/* can't do smth here, it is constexpr func */
		}
		wchar_t* getData() const { return (wchar_t*)this->_buf.data(); }
	};
	/*
		Decrypt to normal string with fake offset
	*/
	template<wchar_t SLEN,  wchar_t XKEY, uint32_t Offset32bit>
	struct DecryptedStringW
	{
		wchar_t _buffer[SLEN + 1];
		DecryptedStringW(wchar_t* encstr)
		{
			wchar_t KEY = XKEY;
			for (wchar_t i = 0; i < SLEN; i++)
			{
				KEY = XKEY;
				KEY += (i + (static_cast<wchar_t>(i) << 8));
				_buffer[i] = KEY ^ encstr[i - Offset32bit];
			}
			_buffer[SLEN] = 0;
		}

	};
	//constexpr long a = MAKELONG(MAKEWORD(__DATE__[2], __DATE__[0]), (MAKEWORD(__DATE__[1],0) >> 4));


	constexpr uint32_t CreateRandomOffset()
	{
		return MAKELONG(MAKEWORD(__DATE__[2], __DATE__[0]), (MAKEWORD(__DATE__[1], 0) >> 4));
	}
	
};
/* XREF KILLING DOESNT WORK WITH /O2 MAX PERFOMANCE */
/* XREF KILLING RARELY WORK WITH /O1 MIN SIZE */
/* XREF KILLING OFTEN WORK WITH /O disabled, but still you can find xref to "fdshgjsd" cause IDA has some deduction  */

#define CONSTEXPRENCRYPTSTR(n, s, key, charbit) constexpr compile_time::EncryptString<sizeof(s), key, charbit> encstr_##n( s,  std::make_index_sequence<sizeof(s)>())
#define DECRYPTCONSTENCSTR(n, slen, key, charbit) compile_time::DecryptedString<slen, key, charbit, compile_time::CreateRandomOffset()> (encstr_##n.getData() +  compile_time::CreateRandomOffset())._buffer
#define CONSTEXPRENCRYPTSTRW(n, s, key) constexpr compile_time::EncryptStringW<(sizeof(s)/sizeof(wchar_t)), key> encstr_##n( s,  std::make_index_sequence<(sizeof(s)/sizeof(wchar_t))>())
#define DECRYPTCONSTENCSTRW(n, slen, key) compile_time::DecryptedStringW<slen, key, compile_time::CreateRandomOffset()> (encstr_##n.getData() + compile_time::CreateRandomOffset())._buffer

constexpr inline size_t wstringSzFromSizeof(size_t sizeofvalue)
{
	return sizeofvalue / sizeof(wchar_t);
}
inline void copy_string_w(wchar_t* dst, size_t sz1, const wchar_t* src, size_t sz2)
{
	for (size_t i = 0; i < sz1 && i < sz2; i++)
	{
		dst[i] = src[i];
	}
	dst[sz1 - 1] = 0x00;
	WCWOUT("decrypted-string: ", dst, " sz1: ", sz1, " sz2: ", sz2 );
}



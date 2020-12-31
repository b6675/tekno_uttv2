#pragma once
namespace serializer
{
	namespace constants
	{
		constexpr wchar_t WDelimeter = 0x2049;
		constexpr wchar_t WButtonPressed = L'1';
		constexpr wchar_t WButtonIsNotPressed = L'0';
	};
	struct ButtonStateWDescriptor
	{
		static constexpr unsigned short SIZE = 2;
		wchar_t text[SIZE] = { 0 , 0 };
		void SetState(bool state)
		{
			if (state) { text[0] = constants::WButtonPressed; }
			else {
				text[0] = constants::WButtonIsNotPressed;
			}
			text[SIZE - 1] = constants::WDelimeter;
		}
		size_t RetSize() const { return SIZE; }
		// state, delimeter
	};
	size_t SerialTextW(const wchar_t* input, const size_t input_sz, wchar_t* output, const size_t sz);
	size_t SerialButtonStateW(bool state, ButtonStateWDescriptor& desc);
	size_t SerialButtonStateW(bool state, wchar_t* output, const size_t sz);
	size_t DeserialTextW(const wchar_t* inputdata, const size_t& inputsize, wchar_t* outputdata, const size_t& outputsize);
	size_t DeserialButtonStateW(const wchar_t* inputdata, const size_t& inputsize, bool& state);
};
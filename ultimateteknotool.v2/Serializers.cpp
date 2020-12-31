#include "pch.h"
#include "Serializers.h"

size_t serializer::SerialTextW(const wchar_t* input, const size_t input_sz, wchar_t* output, const size_t sz)
{
	size_t i = 0;
	for (; i < sz && i < input_sz; i++)
	{
		if (!input[i])
		{
			output[i] = serializer::constants::WDelimeter;
			return i + 1;
		}
		output[i] = input[i];
	}
	i--;
	output[i] = serializer::constants::WDelimeter;
	return i + 1;
}

size_t serializer::SerialButtonStateW(bool state, ButtonStateWDescriptor& desc)
{
	desc.SetState(state);
	return desc.RetSize();
}

size_t serializer::SerialButtonStateW(bool state, wchar_t* output, const size_t sz)
{
	ButtonStateWDescriptor desc = { 0 };
	desc.SetState(state);
	if (desc.RetSize() > sz) { return 0; }
	else
	{
		static_assert(ButtonStateWDescriptor::SIZE == 2, "ButtonStateWDescriptor::SIZE is not 2");
		output[0] = desc.text[0];
		output[1] = desc.text[1];
		return desc.RetSize();
	}
}

size_t serializer::DeserialTextW(const wchar_t* inputdata, const size_t& inputsize, wchar_t* outputdata, const size_t& outputsize)
{
	decltype(inputsize + outputsize)i = 0;
	for (; i < inputsize && i < outputsize; i++)
	{
		if (inputdata[i] == serializer::constants::WDelimeter)
		{
			return i + 1;
		}
		outputdata[i] = inputdata[i];
	}
	return 0u;
}

size_t serializer::DeserialButtonStateW(const wchar_t* inputdata, const size_t& inputsize, bool& state)
{
	if (inputsize < 2) { return 0u; }
	if (inputdata[0] == serializer::constants::WButtonPressed)
	{
		state = true;
		
	}
	else if(inputdata[0] == serializer::constants::WButtonIsNotPressed)
	{
		state = false;
	}
	else
	{
		return 0u;
	}
	if (inputdata[1] == serializer::constants::WDelimeter)
	{
		return 2;
	}
	else
	{
		return 0u;
	}
}

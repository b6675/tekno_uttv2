#include "pch.h"
#include "Randomizer.h"


 std::once_flag Randomizer::m_createonceflag;
 std::unique_ptr<Randomizer> Randomizer::m_pInstance;

  XORShiftSeeder Randomizer::m_xorshift;
   std::uniform_int_distribution<unsigned int> Randomizer::m_distrByte;
   std::uniform_int_distribution<unsigned int> Randomizer::m_distrByteHighBit_1;
   std::uniform_int_distribution<unsigned int> Randomizer::m_distrByteHighBit_0;
   std::uniform_int_distribution<unsigned int> Randomizer::m_ANSIdigit;
   std::uniform_int_distribution<unsigned int> Randomizer::m_ANSIuppercase;
   std::uniform_int_distribution<unsigned int> Randomizer::m_ANSIlowcase;
   std::uniform_int_distribution<unsigned int> Randomizer::m_ANSIchar;
   std::uniform_int_distribution<unsigned int> Randomizer::m_ANSIfromAtoF;
   std::uniform_int_distribution<unsigned int> Randomizer::m_ANSIfromAtoF_lower;

Randomizer & Randomizer::GetInstance()
{
	std::call_once(Randomizer::m_createonceflag, [] {
		Randomizer::m_pInstance.reset(new Randomizer);
	});
	return *Randomizer::m_pInstance.get();
}

uint8_t Randomizer::GetSingleByte(Randomizer::FillType type)
{
	switch (type)
	{
	case Randomizer::FillType::_0_to_127:
		return static_cast<uint8_t>(Randomizer::m_distrByteHighBit_0(Randomizer::m_xorshift));
	case Randomizer::FillType::_128_to_255:
		return static_cast<uint8_t>(Randomizer::m_distrByteHighBit_1(Randomizer::m_xorshift));
	case Randomizer::FillType::_0_to_255:
		return static_cast<uint8_t>(Randomizer::m_distrByte(Randomizer::m_xorshift));
	case Randomizer::FillType::ANSIchar:
		return static_cast<uint8_t>(Randomizer::m_ANSIchar(Randomizer::m_xorshift));
	case Randomizer::FillType::ANSIdigit:
		return static_cast<uint8_t>(Randomizer::m_ANSIdigit(Randomizer::m_xorshift));
	case Randomizer::FillType::ANSIlowcase:
		return static_cast<uint8_t>(Randomizer::m_ANSIlowcase(Randomizer::m_xorshift));
	case Randomizer::FillType::ANSIuppercase:
		return static_cast<uint8_t>(Randomizer::m_ANSIuppercase(Randomizer::m_xorshift));
	case Randomizer::FillType::ANSIfromAtoF:
		return static_cast<uint8_t>(Randomizer::m_ANSIfromAtoF(Randomizer::m_xorshift));
	case Randomizer::FillType::ANSIfromAtoF_lower:
		return static_cast<uint8_t>(Randomizer::m_ANSIfromAtoF_lower(Randomizer::m_xorshift));
	default:
		return static_cast<uint8_t>(Randomizer::m_distrByte(Randomizer::m_xorshift));
	}
}



Randomizer::Randomizer()
{
	std::random_device randomdevice;
	Randomizer::m_xorshift = XORShiftSeeder(randomdevice);
	Randomizer::m_distrByte = std::uniform_int_distribution<unsigned int>(0, 255);
	Randomizer::m_distrByteHighBit_1 = std::uniform_int_distribution<unsigned int>(128, 255);
	Randomizer::m_distrByteHighBit_0 = std::uniform_int_distribution<unsigned int>(0, 127);
	Randomizer::m_ANSIdigit = std::uniform_int_distribution<unsigned int>(48, 57);
	Randomizer::m_ANSIuppercase = std::uniform_int_distribution<unsigned int>(65, 90);
	Randomizer::m_ANSIlowcase = std::uniform_int_distribution<unsigned int>(97, 122);
	Randomizer::m_ANSIchar = std::uniform_int_distribution<unsigned int>(33, 126);
	Randomizer::m_ANSIfromAtoF = std::uniform_int_distribution<unsigned int>(65, 70);
	Randomizer::m_ANSIfromAtoF_lower = std::uniform_int_distribution<unsigned int>('a', 'f');
}

bool operator==(XORShiftSeeder const& lhs, XORShiftSeeder const& rhs)
{
	return lhs.m_seed == rhs.m_seed;
}
bool operator!=(XORShiftSeeder const& lhs, XORShiftSeeder const& rhs)
{
	return lhs.m_seed != rhs.m_seed;
}

#pragma once
#include <memory>
#include <mutex>
#include <random>

class XORShiftSeeder; // stolen from https://arvid.io/2018/07/02/better-cxx-prng/

class Randomizer
{
public:
	~Randomizer() = default;
	static Randomizer& GetInstance();
	enum FillType { _0_to_255, _0_to_127, _128_to_255, ANSIdigit, ANSIuppercase, ANSIlowcase, ANSIchar, ANSIfromAtoF, ANSIfromAtoF_lower
	};
	uint8_t GetSingleByte(FillType type);
private:
	Randomizer();
	static std::once_flag m_createonceflag;
	static std::unique_ptr<Randomizer> m_pInstance;
	Randomizer(const Randomizer&) = delete;
	Randomizer(Randomizer&&) = delete;
	Randomizer& operator=(const Randomizer&) = delete;
	Randomizer& operator=(Randomizer&&) = delete;

	static XORShiftSeeder m_xorshift;
	static std::uniform_int_distribution<unsigned int> m_distrByte;
	static std::uniform_int_distribution<unsigned int> m_distrByteHighBit_1;
	static std::uniform_int_distribution<unsigned int> m_distrByteHighBit_0;
	static std::uniform_int_distribution<unsigned int> m_ANSIdigit;
	static std::uniform_int_distribution<unsigned int> m_ANSIuppercase;
	static std::uniform_int_distribution<unsigned int> m_ANSIlowcase;
	static std::uniform_int_distribution<unsigned int> m_ANSIchar;
	static std::uniform_int_distribution<unsigned int> m_ANSIfromAtoF;
	static std::uniform_int_distribution<unsigned int> m_ANSIfromAtoF_lower;
};


#define RANDBYTE Randomizer::GetInstance().GetSingleByte(Randomizer::FillType::_0_to_255)
#define RANDBYTEH0 Randomizer::GetInstance().GetSingleByte(Randomizer::FillType::_0_to_127)
#define RANDBYTEH1 Randomizer::GetInstance().GetSingleByte(Randomizer::FillType::_128_to_255)
#define RANDANSIDIGIT Randomizer::GetInstance().GetSingleByte(Randomizer::FillType::ANSIdigit)
#define RANDANSIUPPERCASE Randomizer::GetInstance().GetSingleByte(Randomizer::FillType::ANSIuppercase)
#define RANDANSILOWCASE Randomizer::GetInstance().GetSingleByte(Randomizer::FillType::ANSIlowcase)
#define RANDANSICHAR Randomizer::GetInstance().GetSingleByte(Randomizer::FillType::ANSIchar)
#define RANDHEXSYMBOL (Randomizer::GetInstance().GetSingleByte(Randomizer::FillType::_0_to_127) < 64) ? \
Randomizer::GetInstance().GetSingleByte(Randomizer::FillType::ANSIfromAtoF_lower) : RANDANSIDIGIT
#define RANDALNUM RANDBYTEH0 < 64 ? RANDANSIUPPERCASE : (RANDBYTEH0 < 64 ? RANDANSILOWCASE : RANDANSIDIGIT)



class XORShiftSeeder
{
	public:
		using result_type = uint32_t;
		static constexpr result_type(min)() { return 0; }
		static constexpr result_type(max)() { return UINT32_MAX; }
		friend bool operator==(XORShiftSeeder const &, XORShiftSeeder const &);
		friend bool operator!=(XORShiftSeeder const &, XORShiftSeeder const &);

		XORShiftSeeder() : m_seed(0xc1f651c67c62c6e0ull) {}
		explicit XORShiftSeeder(std::random_device &rd)
		{
			seed(rd);
		}
		
		void seed(std::random_device &rd)
		{
			m_seed = uint64_t(rd()) << 31 | uint64_t(rd());
		}

		result_type operator()()
		{
			uint64_t result = m_seed * 0xd989bcaef137dcd5ull;
			m_seed ^= m_seed >> 11;
			m_seed ^= m_seed << 31;
			m_seed ^= m_seed >> 18;
			return uint32_t(result >> 32ull);
		}

		void discard(unsigned long long n)
		{
			for (unsigned long long i = 0; i < n; ++i)
				operator()();
		}

	private:
		uint64_t m_seed;
};


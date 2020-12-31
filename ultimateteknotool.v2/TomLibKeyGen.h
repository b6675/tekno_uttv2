#pragma once
#include <memory>
#include <mutex>
#include <random>
#include <tomcrypt.h>
#pragma comment (lib, "tommath.lib")
#pragma comment (lib, "tomcrypt.lib")
#include "Randomizer.h"
#include "debugconsole.h"

class TomLibKeyGen
{
private:
	TomLibKeyGen();
	static std::once_flag m_createonceflag;
	static std::unique_ptr<TomLibKeyGen> m_pInstance;
	TomLibKeyGen(const TomLibKeyGen&) = delete;
	TomLibKeyGen(TomLibKeyGen&&) = delete;
	TomLibKeyGen& operator=(const TomLibKeyGen&) = delete;
	TomLibKeyGen& operator=(TomLibKeyGen&&) = delete;

	void PreparePRGN();
	static bool m_boolPRGNisReady;
	static prng_state m_prng_yarrow;

	bool ECC_GenerateKey();
	static bool m_boolECCKEYisReady;
	static ::ecc_key m_ECCKey;
public:
	~TomLibKeyGen();
	static TomLibKeyGen& GetT0mLibKeyGen();

	void ECC_GetExportKey(unsigned char* outbuffer, unsigned char sz);
};
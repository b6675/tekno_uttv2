#include "pch.h"
#include "TomLibKeyGen.h"

std::once_flag TomLibKeyGen::m_createonceflag;
std::unique_ptr<TomLibKeyGen> TomLibKeyGen::m_pInstance;
bool TomLibKeyGen::m_boolPRGNisReady;
 prng_state TomLibKeyGen::m_prng_yarrow;

 bool TomLibKeyGen::m_boolECCKEYisReady;
 ::ecc_key TomLibKeyGen::m_ECCKey;
static_assert(sizeof(prng_state) > 10000, "we have to allocate prng somewhere");

void TomLibKeyGen::PreparePRGN()
{
	m_boolPRGNisReady = false;
	if (::register_prng(&::yarrow_desc) == -1)
	{
		WCWOUT("error/libtomcrypt/::register_prng failed register yarrow description");
		return;
	}
	constexpr uint8_t YABUFSIZE = 128;
	int error = 0;
	unsigned char yaBuffer[YABUFSIZE];
	for (uint8_t i = 0; i < YABUFSIZE; i++)
	{
		yaBuffer[i] = RANDBYTE;
	}
	if (error = ::yarrow_start(&this->m_prng_yarrow) != CRYPT_OK)
	{
		WCWOUT("error/libtomcrypt/::yarrow_start failed. Error description: ", ::error_to_string(error));
		return;
	}
	if (error = ::yarrow_add_entropy(yaBuffer, YABUFSIZE, &this->m_prng_yarrow) != CRYPT_OK)
	{
		WCWOUT("error/libtomcrypt/::yarrow_add_entropy failed. Error description: ", ::error_to_string(error));
		return;
	}
	if (error = ::yarrow_ready(&this->m_prng_yarrow) != CRYPT_OK)
	{
		WCWOUT("error/libtomcrypt/::yarrow_ready failed. Error description: ", ::error_to_string(error));
		return;
	}
	m_boolPRGNisReady = true;
}

TomLibKeyGen::~TomLibKeyGen()
{
	if (this->m_boolECCKEYisReady)
	{
		::ecc_free(&(this->m_ECCKey));
	}
}

TomLibKeyGen::TomLibKeyGen()
{
	/* libtom fix */
	ltc_mp = ltm_desc;
	/* libtom fix */
}

TomLibKeyGen& TomLibKeyGen::GetT0mLibKeyGen()
{
	std::call_once(TomLibKeyGen::m_createonceflag, [] {
		TomLibKeyGen::m_pInstance.reset(new TomLibKeyGen);
		});
	return *TomLibKeyGen::m_pInstance.get();
}

void TomLibKeyGen::ECC_GetExportKey(unsigned char* outbuffer, unsigned char sz)
{
	if (sz < 100) { throw 0xDEAD; }
	if (this->ECC_GenerateKey())
	{
		unsigned long outlen = 100;
		unsigned char outbuf[100];
		::ecc_export(outbuf, &outlen, PK_PUBLIC, &(this->m_ECCKey));
		if (outlen < 100)
		{
			memset(&outbuf[outlen], 0, 100 - outlen);
		}
		memcpy(outbuffer, outbuf, 100);
	}
}


bool TomLibKeyGen::ECC_GenerateKey()
{
	int error = 0;
	if (this->m_boolECCKEYisReady)
	{
		::ecc_free(&(this->m_ECCKey));
	}
	if (this->m_boolPRGNisReady == false)
	{
		this->PreparePRGN();
	}
	if (error = ::ecc_make_key(&this->m_prng_yarrow, ::find_prng("yarrow"), 28, &(this->m_ECCKey)) != CRYPT_OK)
	{
		WCWOUT("error/libtomcrypt/::ecc_make_key. Error description: ", ::error_to_string(error));
		this->m_boolECCKEYisReady = false;
		return false;
	}
	else
	{
		this->m_boolECCKEYisReady = true;
		return true;
	}
}

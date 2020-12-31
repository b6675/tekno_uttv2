#include "pch.h"
#include "iw5mp_address_verifier.h"

bool iw5mp_addresses::sections::IsAddressPlacedAfterDataEnd(uint32_t address)
{
	return address > iw5mp_addresses::sections::data_end;
}

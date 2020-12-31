#include "pch.h"
#include "iw5mp_quickbuttons_functions.h"
#include "iw5mp_addresses_declaration.h"

void iw5mp_changedata::ForceJumpToMenu()
{
	reinterpret_cast<uint8_t*>(iw5mp_addresses::unnamed_ForceJumpToMenuValue)[0] = 1;
}

#pragma once
#include "debugconsole.h"
#include <stdint.h>
namespace patternsearcher {
	uint32_t PatternSearch(char* pattern, uint32_t start_address, uint32_t maxdeep);
};
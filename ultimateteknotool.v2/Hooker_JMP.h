#pragma once
#include "stdint.h"
#include "debugconsole.h"
#include <memory>
#include <mutex>
#include "SystemFunctionXRefRemover.h"

namespace Hooker_JMP
{

	void* __Hook32_internal__NativeHook(uint8_t* addr, uint8_t* hook, uint8_t len);

	template<typename FunctionType, typename HookType>
	bool Hook32(uint32_t addr, HookType& hook, uint8_t asm_length_of_original_code, FunctionType& original_call)
	{
		original_call = nullptr;
		original_call = reinterpret_cast<FunctionType>(
			__Hook32_internal__NativeHook(reinterpret_cast<uint8_t*>(addr), reinterpret_cast<uint8_t*>(hook), asm_length_of_original_code)
			);

		return original_call != nullptr;
	}


};
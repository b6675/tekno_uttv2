#pragma once
#include <stdint.h>
#include "debugconsole.h"

template<size_t BFSZ>
struct XRefRemover_SysFunctionUI32
{
	uint32_t _pointers[BFSZ];
	XRefRemover_SysFunctionUI32()
	{
		if (BFSZ < 4) { throw 1; }
		_pointers[0] = 0x00;
		for (size_t sz = 1; sz < BFSZ; sz++)
		{
			_pointers[sz] = _pointers[0];
		}
	}
	~XRefRemover_SysFunctionUI32() = default;
#define XRefRemover_FAKEADR(index) index + fake_address - xfake_address
#pragma optimize("" ,off)
	template<uint32_t fake_address>
	void AddNewFunction(void* addr, uint32_t xfake_address)
	{

		_pointers[XRefRemover_FAKEADR(0)] = *reinterpret_cast<uint32_t*>(addr);
		_pointers[XRefRemover_FAKEADR(1)] = reinterpret_cast<uint32_t>(addr) ^ _pointers[0];
		_pointers[XRefRemover_FAKEADR(2)] = *(reinterpret_cast<uint32_t*>(addr) + 1);
	}
	template<uint32_t fake_address>
	void* GetFunction(uint32_t xfake_address) const
	{
		return reinterpret_cast<void*>(_pointers[XRefRemover_FAKEADR(1)] ^ _pointers[XRefRemover_FAKEADR(0)]);
	}
	void VerifyFunction() const
	{
		uint32_t addr = 0x00;
		if (
			*reinterpret_cast<uint32_t*>(_pointers[1] ^ _pointers[0]) != _pointers[0]
			)
		{
			addr = 0x7F340000;
			__asm {
				jmp [addr];
			}
		}
		else if (*(reinterpret_cast<uint32_t*>(_pointers[1] ^ _pointers[0]) + 1) != _pointers[2])
		{
			addr = 0x0010AB00;
			__asm {
				jmp [addr];
			}
		}
		else
		{

		}
	}
	template<uint32_t fake_address>
	void* GetVerifiedFunction(uint32_t xfake_address) const
	{
		this->VerifyFunction();
		return this->GetFunction<fake_address>(xfake_address);
	}

	size_t Size() const noexcept { return BFSZ; }
#undef XRefRemover_FAKEADR
#pragma optimize("" ,on)
};
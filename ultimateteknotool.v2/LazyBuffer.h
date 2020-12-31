#pragma once
#include <vector>
#include "debugconsole.h"

template<typename T1, unsigned short SIZE>
class LazyBuffer
{
private:
	std::vector<T1> m_vec;
	unsigned short m_currentNullPos = 0;
public:
	LazyBuffer():m_vec(SIZE+4, 0) 
	{

	}
	~LazyBuffer() = default;
	T1* GetNulledMem(unsigned short sz)
	{
		if (sz > SIZE)
		{
			throw 1;
		}

		if (sz + m_currentNullPos > SIZE)
		{
			for (auto& x : this->m_vec) { x = 0; }
			this->m_currentNullPos = 0;
			this->m_currentNullPos += sz;
			return &(this->m_vec[0]);
		}
		else
		{
			this->m_currentNullPos += sz;
			return this->m_vec.data() + (this->m_currentNullPos - sz);
		}
	}
#ifdef UTT2_DEBUG
	void fill(T1* p, unsigned short sz, T1 value = 1)
	{
		for (unsigned short i = 0; i < sz; i++)
		{
			p[i] = value;
		}
	}
	bool checvalid()
	{
		// asked sz -> next byte/wchar_t must be null
		unsigned short verifyer = this->m_currentNullPos;
		while (verifyer < SIZE+1)
		{
			if (*(this->m_vec.data() + verifyer) != 0)
			{
				WCWOUT(std::dec,L"Check failed at this->m_vec[",verifyer,L"]");
				return false;
			}
			verifyer++;
		}
		return true;
	}
	bool Test()
	{
		T1* p = nullptr;
		unsigned short sz = SIZE / 2;
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; };
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		p = this->GetNulledMem(sz+1);
		fill(p, sz);
		if (!checvalid()) { return false; }
		sz = 100;
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		sz = SIZE - 1;
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		sz = 1;
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		sz = SIZE - 1;
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		sz = 2;
		p = this->GetNulledMem(sz);
		fill(p, sz);
		if (!checvalid()) { return false; }
		return true;
	}
#endif
};

template<unsigned short SIZE>
using LazyBuffer_wchart = LazyBuffer<wchar_t, SIZE>;

template<unsigned short SIZE>
using LazyBuffer_char = LazyBuffer<char, SIZE>;

template<typename T1, unsigned short SECTIONSIZE, unsigned char NUMBEROFSECTIONS>
class LazySectionBuffer
{
private:
	std::vector<T1> m_vec;
	T1* retAddr[NUMBEROFSECTIONS] = { nullptr };
public:
	LazySectionBuffer():m_vec(SECTIONSIZE * NUMBEROFSECTIONS + 4, 0)
	{
		for(unsigned char i = 0; i < NUMBEROFSECTIONS; i++)
		{
			this->retAddr[i] = this->m_vec.data() + SECTIONSIZE * i;
		}
	}
	~LazySectionBuffer() = default;
	T1* GetNulledMem(unsigned short sz, unsigned char section_id)
	{
		if (sz > SECTIONSIZE || section_id >= NUMBEROFSECTIONS)
		{
			throw 1;
		}

		//WCWOUT(L"ret[", std::dec, section_id, L"] = &(this->m_vec[", retAddr[section_id] - this->m_vec.data(), L"]) when size = ", sz);
		if (retAddr[section_id] + sz > this->m_vec.data() + SECTIONSIZE * section_id + SECTIONSIZE)
		{
			retAddr[section_id] = this->m_vec.data() + SECTIONSIZE * section_id;
			for (size_t i = 0; i < SECTIONSIZE; i++)
			{
				retAddr[section_id][i] = 0x00;
			}
			retAddr[section_id] += sz;
			//WCWOUT(L"return = ", std::dec, retAddr[section_id] - this->m_vec.data() - sz);
			return retAddr[section_id] - sz;
		}
		else
		{
			retAddr[section_id] += sz;
			//WCWOUT(L"return = ", std::dec, retAddr[section_id] - this->m_vec.data() - sz );
			return retAddr[section_id] - sz;
		}
	}
#ifdef UTT2_DEBUG
	bool VerifyMem_OnlyOneSection(unsigned char secID)
	{
		T1* vecData = this->m_vec.data() + SECTIONSIZE * secID;
		size_t SZ = retAddr[secID] - vecData;
		if (SZ > SECTIONSIZE)
		{
			WCWOUT(L"LazySectionBuffer->VerifyMem(): false->SZ > SECTIONSIZE");
			return false;
		}
		for (size_t i = SZ; i < SECTIONSIZE; i++)
		{
			if (retAddr[secID][i] != 0)
			{
				WCWOUT(L"LazySectionBuffer->VerifyMem(): false->retAddr[", std::dec, secID, L"][", i , L"] != 0" );
				return false;
			}
		}
		if ((this->m_vec.data() + SECTIONSIZE * secID)[SECTIONSIZE] != 0)
		{
			WCWOUT(L"LazySectionBuffer->VerifyMem(): false->(this->m_vec.data() + SECTIONSIZE * secID)[SECTIONSIZE] != 0");
			return false;
		}
		return true;
	}
	bool VerifyMem_allfilled(unsigned char secID, unsigned short size)
	{
		T1* vecData = this->m_vec.data() + secID * SECTIONSIZE;
		size_t SZ = retAddr[secID] - vecData;
		if (SZ != size)
		{
			WCWOUT(L"LazySectionBuffer->VerifyMem_allfilled(): false->wrong pointer, size is ", SZ, L" when expect ", size);
			return false;
		}
		for (size_t i = 0; i < size; i++)
		{
			if (vecData[i] == 0)
			{
				WCWOUT(L"LazySectionBuffer->VerifyMem(): false->not filled");
				return false;
			}
		}
		return true;
	}
	void fill(T1* p, unsigned short sz, T1 value = 1)
	{
		if (p == nullptr)
		{
			WCWOUT(L"LazySectionBuffer->fill(): nullptr?");
		}
		else {
			for (unsigned short i = 0; i < sz; i++)
			{
				p[i] = value;
			}
		}
	}
	bool Test1()
	{
		unsigned short memSize = SECTIONSIZE / 2;
		T1* pData = this->GetNulledMem(memSize, 0); this->fill(pData, memSize);
		if (VerifyMem_OnlyOneSection(0))
		{
			pData = this->GetNulledMem(memSize, 0); this->fill(pData, memSize);
			if (VerifyMem_OnlyOneSection(0))
			{
				return true;
			}
		}
		return false;
	}
	bool Test2()
	{
		unsigned short memSize = SECTIONSIZE / 2;
		T1* pData = nullptr;
		for (auto& x : this->m_vec) { x = 0; }
		for (unsigned char i = 0; i < NUMBEROFSECTIONS; i++)
		{
			pData = this->GetNulledMem(memSize, i);
			this->fill(pData, memSize);
			pData = this->GetNulledMem(memSize, i);
			this->fill(pData, memSize);
			if (VerifyMem_allfilled(i, memSize * 2) == false || VerifyMem_OnlyOneSection(i) == false) { return false; }
		}
		memSize = 1;
		if (SECTIONSIZE - memSize * 2)
		{
			memSize = 2;
		}
		for (unsigned char i = 0; i < NUMBEROFSECTIONS; i++)
		{
			pData = this->GetNulledMem(memSize, i);
			this->fill(pData, memSize);
			pData = this->GetNulledMem(memSize, i);
			this->fill(pData, memSize);
			if (VerifyMem_allfilled(i, memSize * 2) == false) { return false; }
		}
		memSize = SECTIONSIZE / 2 + 1;
		for (unsigned char i = 0; i < NUMBEROFSECTIONS; i++)
		{
			pData = this->GetNulledMem(memSize, i);
			this->fill(pData, memSize);
			pData = this->GetNulledMem(memSize, i);
			this->fill(pData, memSize);
			if (VerifyMem_allfilled(i, memSize) == false) { return false; }
		}
		return true;
	}
#endif
};

template<unsigned short SECTIONSIZE, unsigned char NUMBEROFSECTIONS>
using LazySectionBuffer_wchart = LazySectionBuffer<wchar_t, SECTIONSIZE, NUMBEROFSECTIONS>;

template<unsigned short SECTIONSIZE, unsigned char NUMBEROFSECTIONS>
using LazySectionBuffer_char = LazySectionBuffer<char, SECTIONSIZE, NUMBEROFSECTIONS>;

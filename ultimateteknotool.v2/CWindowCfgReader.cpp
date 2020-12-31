#include "pch.h"
#include "CWindowCfgReader.h"

//static constexpr unsigned short chuck_sz = 32;

inline void CWindowCfgReader::IncrTotal_DeserialSuccess()
{
	this->m_wcharsreadtotal += this->m_deserialwcharsread;
	if (this->m_buffersize > this->m_deserialwcharsread) { this->m_buffersize -= this->m_deserialwcharsread; }
	else
	{
		this->m_buffersize = 0;
	}
}

inline void CWindowCfgReader::IncrTotal_DeserialFailed()
{
	this->m_wcharsreadtotal++;
	if (this->m_buffersize > 0) { this->m_buffersize--; }
	else
	{
		this->m_buffersize = 0;
	}
}

void CWindowCfgReader::LoadTextSettingW(CWindow_edit_cfg* win, unsigned short textlimit)
{
	wchar_t* pointer;
	pointer = lazysectionbuffer_3x512.GetNulledMem(textlimit + 4, 0);
	this->m_deserialwcharsread = serializer::DeserialTextW(&this->m_buffer[this->m_wcharsreadtotal], this->m_buffersize, pointer, textlimit);
	if (this->m_deserialwcharsread)
	{
		//if (chuck_sz > textlimit && textlimit >= 1)
		//{
		//	pointer[textlimit - 1] = 0x00;
		//}
		//else
		//{
		//	pointer[chuck_sz - 1] = 0x00;
		//}
		CWindowTextWriter_WriteText(win, pointer);
		this->IncrTotal_DeserialSuccess();
	}
	else
	{
		this->IncrTotal_DeserialFailed();
	}
}

void CWindowCfgReader::LoadButtonStateW(CWindow_button_cfg* win)
{
	this->m_deserialwcharsread = serializer::DeserialButtonStateW(&this->m_buffer[this->m_wcharsreadtotal], this->m_buffersize, win->isPressed);
	if (this->m_deserialwcharsread)
	{
		if (win->isPressed) 
		{
			::SendMessageW(win->hwnd, BM_SETCHECK, BST_CHECKED, NULL); 
		}
		else
		{
			::SendMessageW(win->hwnd, BM_SETCHECK, BST_UNCHECKED, NULL);
		}
		this->IncrTotal_DeserialSuccess();
	}
	else
	{
		this->IncrTotal_DeserialFailed();
	}
}

bool CWindowCfgReader::LoadButtonStateW()
{
	bool ret = false;
	this->m_deserialwcharsread = serializer::DeserialButtonStateW(&this->m_buffer[this->m_wcharsreadtotal], this->m_buffersize, ret);
	if (this->m_deserialwcharsread)
	{
		this->IncrTotal_DeserialSuccess();
	}
	else
	{
		this->IncrTotal_DeserialFailed();
	}
	return ret;
}

const wchar_t* CWindowCfgReader::LoadTextSettingW(unsigned short textlimit)
{
	wchar_t* pointer;
	pointer = lazysectionbuffer_3x512.GetNulledMem(textlimit + 4, 0);
	this->m_deserialwcharsread = serializer::DeserialTextW(&this->m_buffer[this->m_wcharsreadtotal], this->m_buffersize, pointer, textlimit);
	if (this->m_deserialwcharsread)
	{
		//if (chuck_sz > textlimit && textlimit >= 1)
		//{
		//	pointer[textlimit - 1] = 0x00;
		//}
		//else
		//{
		//	pointer[chuck_sz - 1] = 0x00;
		//}
		this->IncrTotal_DeserialSuccess();
	}
	else
	{
		pointer[0] = 0x0000;
		this->IncrTotal_DeserialFailed();
	}
	return pointer;
}

constexpr unsigned char EXTRA_SPACE_BUFF = 1;

wchar_t* CWindowPostLoadStrings::GetMemoryForString(unsigned short textlimit)
{
	if ((textlimit + this->currentUsedSize) >= wchart_buffer.size())
	{
		return nullptr;
	}
	else
	{
		this->currentUsedSize += textlimit;
		return  wchart_buffer.data() + (this->currentUsedSize - textlimit);
	}
}

void CWindowPostLoadStrings::Register(size_t buffersize)
{
	this->Unregister();
	wchart_buffer.resize(buffersize, 0x0000);
}

void CWindowPostLoadStrings::Unregister()
{
	if (this->wchart_buffer.empty() == false)
	{
		this->wchart_buffer.clear();
	}
	if (this->pairs.empty() == false)
	{
		this->pairs.clear();
	}
	this->currentUsedSize = 0;
}

void CWindowPostLoadStrings::LoadTextSettingW(CWindow_edit_cfg* win, const wchar_t* ptxt, unsigned short textlimit)
{
	wchar_t* pp = nullptr;
	pp = this->GetMemoryForString(textlimit + EXTRA_SPACE_BUFF);
	if (pp != nullptr)
	{
		for (unsigned short i = 0; i < textlimit && ptxt[i]; i++)
		{
			pp[i] = ptxt[i];
		}
		this->pairs.push_back(std::pair<CWindow_edit_cfg*, wchar_t*>(win, pp));
	}
}

void CWindowPostLoadStrings::LoadTextInEdits()
{
	for (auto& x : this->pairs)
	{
		CWindowTextWriter_WriteText(x.first, x.second);
	}
}


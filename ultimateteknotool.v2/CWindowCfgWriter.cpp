#include "pch.h"
#include "CWindowCfgWriter.h"

static constexpr wchar_t dummytext[] = L"\0\0\0\0";

//void CWindowCfgWriter_SaveTextSetting(CWindow_edit_cfg* win, CWinAPIFileW* apifile)
//{
//	// read window
//	// serialize
//	// write file
//	//
//}
//
//
//void CWindowCfgWriter_SaveButtonSetting(CWindow_button_cfg* win, CWinAPIFileW* apifile)
//{
//	serializer::ButtonStateWDescriptor desc = { 0 };
//	bytes_serialized = serializer::SerialButtonStateW(win->isPressed, desc);
//	apifile->WriteInAppend((char*)desc.text, bytes_serialized * sizeof(wchar_t));
//}

void CWindowCfgWriter::DecreaseBufferSize(size_t value)
{
	if (value >= this->m_buffersize)
	{
		this->m_buffersize = 0;
	}
	else
	{
		this->m_buffersize = this->m_buffersize - value;
	}
}

void CWindowCfgWriter::SaveTextSettingW(CWindow_edit_cfg* win, unsigned short chunk)
{
	const wchar_t* dummyboi = dummytext;
	dummyboi = CWindowTextReader_GetTextW(win, chunk);
	if (this->m_wcharswrotetotal >= this->m_constBufferSizeVerifyValue) { throw 1; }
	this->m_serialwcharswrote = serializer::SerialTextW(dummyboi, chunk, &(this->m_buffer[this->m_wcharswrotetotal]), this->m_buffersize);
	this->m_wcharswrotetotal += this->m_serialwcharswrote;
	this->DecreaseBufferSize(this->m_serialwcharswrote);
}

void CWindowCfgWriter::SaveButtonStateW(CWindow_button_cfg* win)
{
	if (this->m_wcharswrotetotal >= this->m_constBufferSizeVerifyValue) { throw 1; }
	this->m_serialwcharswrote = serializer::SerialButtonStateW(win->isPressed, &(this->m_buffer[this->m_wcharswrotetotal]), this->m_buffersize);
	this->m_wcharswrotetotal += this->m_serialwcharswrote;
	this->DecreaseBufferSize(this->m_serialwcharswrote);
}

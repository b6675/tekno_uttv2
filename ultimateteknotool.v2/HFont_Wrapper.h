#pragma once
#include <windows.h>
class HFont_Wrapper
{
private:
	HFONT font;
public:
	HFont_Wrapper() { font = 0; }
	void HFONT_Wrap(HFONT vfont) { font = vfont; }
	const HFONT& GetFont() { return this->font; }
	~HFont_Wrapper()
	{
		::DeleteObject(this->font);
	}
};


#include "pch.h"
#include "windows_injectorpage.h"
#include "Injector.h"
#include "debugconsole.h"

namespace windows_injectorpage {

	const wchar_t ws_inject[] = L"inject";
	const wchar_t ws_emptytext[] = L"";
	constexpr unsigned short maxlen_injectpathtofile = (128 - 32);

	class PathAndInjectButton
	{
	private:
		CWindow_edit_cfg path;
		CWindow_button injectorbutton;
	public:
		PathAndInjectButton() = default;
		~PathAndInjectButton() = default;
		void Build(CWindowsBuilder& builder, int editwidth, int buttonwidth, int height, int gap)
		{
			constexpr DWORD FlatButtonStyleInvisble = (WS_CHILD & ~WS_VISIBLE) | BS_PUSHBUTTON | BS_CENTER | BS_FLAT;
			constexpr DWORD NewEditStyle_Invisible = WS_CHILD & ~WS_VISIBLE | WS_BORDER;

			builder.ChangeStyle(NewEditStyle_Invisible);
			builder.ChangeHeight(height);
			builder.ChangeWidth(editwidth);
			builder.ChangeTextP(ws_emptytext);
			this->path.Visit(&builder);
			builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
			builder.ChangeStyle(FlatButtonStyleInvisble);
			builder.ChangeWidth(buttonwidth);
			builder.ChangeTextP(ws_inject);
			this->injectorbutton.Visit(&builder);
		}
		void Show() const
		{
			path.Show();
			injectorbutton.Show();
		}
		void Hide() const
		{
			path.Hide();
			injectorbutton.Hide();
		}
		void ButtonHandler(WPARAM& wparam)
		{
			if (injectorbutton.id == LOWORD(wparam))
			{
				Injector::Inject0r().APC_Inject(CWindowTextReader_GetTextW(&path, maxlen_injectpathtofile));
			}
		}
		void ApplyFonts(CWindowsFontApplier& fontmaster)
		{
			this->injectorbutton.Visit(&fontmaster);
			this->path.Visit(&fontmaster);
		}
	};

	PathAndInjectButton path1;
	PathAndInjectButton path2;

};

void windows_injectorpage::Build(CWindowsBuilder& builder, int left, int width, int top, int height, HWND hwnd)
{
	builder.ChangeParentHWND(hwnd);
	builder.ChangeLeftPos(left);
	builder.ChangeTopPos(top);

	int gap = 5;
	int bwidth = 50;
	int editwidth = width - (left*2 + gap + bwidth);
	int rheight = 20;

	path1.Build(builder, editwidth, bwidth, rheight, gap);
	builder.ChangeLeftPos(left);
	builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap);
	path2.Build(builder, editwidth, bwidth, rheight, gap);
}

void windows_injectorpage::ApplyFonts(CWindowsFontApplier& fontappl)
{
	path1.ApplyFonts(fontappl);
	path2.ApplyFonts(fontappl);
}

void windows_injectorpage::Show()
{
	path1.Show();
	path2.Show();
}

void windows_injectorpage::Hide()
{
	path1.Hide();
	path2.Hide();
}

void windows_injectorpage::ButtonHandler(WPARAM& param)
{
	path1.ButtonHandler(param);
	path2.ButtonHandler(param);
}


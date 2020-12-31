#pragma once
#include "CWindowsBuilder.h"
#include "CWindowsFontApplier.h"
#include "CWindowTextWriter.h"
#include "CWindowTextReader.h"
#include "CWinAPIFileW.h"
#include "CWindowCfgWriter.h"
#include "CWindowCfgReader.h"
#include "CWindowTextLimiter.h"

namespace windows_accountpage
{
    struct WinCombo
    {
        CWindow_edit edit_show;
        CWindow_edit_cfg edit_new;
        CWindow_edit_cfg edit_new_randmask;
        void Show()
        {
            edit_show.Show();
            edit_new.Show();
            edit_new_randmask.Show();
        }
        void Hide()
        {
            edit_show.Hide();
            edit_new.Hide();
            edit_new_randmask.Hide();
        }
        void ApplyFont(CWindowsFontApplier& fontappl)
        {
            edit_show.Visit(&fontappl);
            edit_new.Visit(&fontappl);
            edit_new_randmask.Visit(&fontappl);
        }
        void ApplyTextLimit(size_t limit)
        {
            CWindowTextLimiter_LimitText(&edit_show, limit);
            CWindowTextLimiter_LimitText(&edit_new, limit);
            CWindowTextLimiter_LimitText(&edit_new_randmask, limit);
        }
        inline void SetTextInShowEdit(const wchar_t* txt)
        {
            CWindowTextWriter_WriteText(&edit_show, txt);
        }
        inline wchar_t* GetNormalWText(unsigned short sz)
        {
           return CWindowTextReader_GetTextW(&this->edit_new, sz);
        }
        inline wchar_t* GetRandWText(unsigned short sz)
        {
           return CWindowTextReader_GetTextW_ParseRandMask(&this->edit_new_randmask, sz);
        }
        inline wchar_t* GetRandmaskWText(unsigned short sz)
        {
           return CWindowTextReader_GetTextW_ParseRandMask_Overwrite(&this->edit_new, &this->edit_new_randmask, sz);
        }
        template<size_t id>
        inline wchar_t* GetTextW(unsigned short sz)
        {
            /* decompiled versions of utt proved that compiles only 1 variant*/
            if (id == 0) {
                return CWindowTextReader_GetTextW(&this->edit_new, sz);
            }
            else if (id == 1)
            {
                return CWindowTextReader_GetTextW_ParseRandMask(&this->edit_new_randmask, sz);
            }
            else if (id == 2)
            {
                return CWindowTextReader_GetTextW_ParseRandMask_Overwrite(&this->edit_new, &this->edit_new_randmask, sz);
            }
            else
            {
                return CWindowTextReader_GetTextW(&this->edit_new, sz);
            }
        }
    };

    namespace changeonconnect
    {
        extern bool xuidhwidetc;
        extern bool nicknameetc;
        extern bool localexternalipetc;
    };

    void Build(CWindowsBuilder& builder, int left, int width, int top, int height, HWND hwnd);
    void ApplyFonts(CWindowsFontApplier& fontappl);
    void WriteDefault();
    void ApplyTextLimits();
    void Show();
    void Hide();

    void Show_XuidHwidPage();
    void Hide_XuidHwidPage();
    void Show_LocalExternalIPPage();
    void Hide_LocalExternalIPPage();
    void Show_FirmwarePage();
    void Hide_FirmwarePage();
    void Show_UPnPPage();
    void Hide_UPnPPage();

    void Show_XuidHwidPageHideOthers();
    void Show_LocalExternalIPHideOthers();
    void Show_FirmwareHideOthers();
    void Show_UPnPPageHideOthers();

    void Handler_ClickButton(WPARAM wparam);

    void Cfg_SavePreCreateWindowSettings(CWindowCfgWriter* writer);
    void Cfg_LoadPreCreateWindowSettings(CWindowCfgReader* reader);
    void Cfg_Save(CWindowCfgWriter* writer);
    void Cfg_Load(CWindowCfgReader* reader);

    void ReadData_ChangeNicknameEtc_andUpdate();
    void ReadRandData_ChangeNicknameEtc_andUpdate();
    void ReadRandDataMask_ChangeNicknameEtc_andUpdate();
    void ReadData_ChangeXUIDHWID_andUpdate();
    void ReadRandData_ChangeXUIDHWID_andUpdate();
    void ReadRandDataMask_ChangeXUIDHWID_andUpdate();
    void ReadData_ChangeNETData();
    void ReadRandData_ChangeNETData();
    void ReadRandDataMask_ChangeNETData();
   

    void UpdateCurrentNickanameEtc();
    void UpdateCurrentXUIDHWID();
    void UpdateCurrentNETData();

    namespace UPnP
    {
        namespace update_device
        {
            void Location(const wchar_t* text);
            void Server(const wchar_t* text);
            void USN(const wchar_t* text);
        };
        void ReadData_ChangeDeviceInfo();
        void ReadRandData_ChangeDeviceInfo();
        void ReadRandDataMask_ChangeDeviceInfo();
   };

    void UpdateCurrentChallengeS2();

    void DoJobOnConnect();
};
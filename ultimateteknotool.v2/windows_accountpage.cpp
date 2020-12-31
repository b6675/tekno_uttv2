#include "pch.h"
#include "windows_accountpage.h"
#include "TextConvertors.h"
#include "iw5mp_nickname_etc_functions.h"
#include "iw5mp_xuidhwid_functions.h"
#include "iw5mp_constants.h"
#include "JMPHook_SerializeNetdata.h"
#include "JMPHook_sysinfoapi_functions.h"
#include "JMPHook_bdUPnP_functions.h"
#include "JMP_iw5mp_functions.h"
#include "ParserRandMask.h"


namespace windows_accountpage
{

    constexpr DWORD NewEditStyle_Invisible = WS_CHILD & ~WS_VISIBLE | WS_BORDER;
    constexpr DWORD ShowEditStyle_Invisible = WS_CHILD & ~WS_VISIBLE | WS_BORDER | ES_READONLY; 
    constexpr DWORD FlatButtonStyleInvisble = (WS_CHILD & ~WS_VISIBLE) | BS_PUSHBUTTON | BS_CENTER | BS_FLAT;
    constexpr DWORD FlatRadioButtonStyleInvisble = (WS_CHILD & ~WS_VISIBLE) | BS_AUTOCHECKBOX | BS_FLAT | BS_LEFTTEXT;
    constexpr DWORD FlatRadioButtonStyleInvisble_RIGHT = (WS_CHILD & ~WS_VISIBLE) | BS_AUTOCHECKBOX | BS_FLAT | BS_RIGHT;
    constexpr DWORD FlatRadioButtonStyleInvisble_CENTER = (WS_CHILD & ~WS_VISIBLE) | BS_AUTOCHECKBOX | BS_FLAT | BS_CENTER;

    constexpr size_t txtlimit_nickname = iw5mp_constants::MAX_LENGTH_NICKNAME - 1;
    constexpr size_t txtlimit_title = iw5mp_constants::MAX_LENGTH_TITLE - 1;
    constexpr size_t txtlimit_clantag = iw5mp_constants::MAX_LENGTH_CLANTAG - 1;
    constexpr size_t txtlimit_emlem_and_title_types = 3;
    constexpr size_t txtlimit_level_and_prestiges_values = 2;
    constexpr size_t txtlimit_ip = 3 + 1 + 3 + 1 + 3 + 1 + 3;
    constexpr size_t txtlimit_port = 5; // 66 666

    constexpr size_t txtlimit_xuid_hwid_values = 8;

    void MisterDummyDum(void){}
    void MisterDummyDum(const bool&) {}
     inline void BuildTripleBar(CWindowsBuilder& builder, WinCombo& combo, int gap)
     {
         builder.ChangeStyle(ShowEditStyle_Invisible);
         combo.edit_show.Visit(&builder);
         builder.ChangeStyle(NewEditStyle_Invisible);
         builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap);
         combo.edit_new.Visit(&builder);
         builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap);
         combo.edit_new_randmask.Visit(&builder);
     }

     typedef void doJobwhenChanged_t(void);


     const wchar_t ws_empty_text[] = L"";
     const wchar_t ws_buttontext[] = L"^";

     WinCombo nickname;
     WinCombo title;
     WinCombo titletype;
     WinCombo emblem;
     WinCombo prestige;
     WinCombo level;
     WinCombo clantag;

     class CWinControlBlock
     {
     private:
         doJobwhenChanged_t* Job_apply = &MisterDummyDum;
         doJobwhenChanged_t* Job_applyRand = &MisterDummyDum;
         doJobwhenChanged_t* Job_applyRand_mask = &MisterDummyDum;
         CWindow_button apply;
         CWindow_button applyrand;
         CWindow_button_cfg randmasksymbolsreplacenormaldata_autochange;
     public:
         CWinControlBlock() = delete;
         CWinControlBlock(doJobwhenChanged_t& appl, doJobwhenChanged_t& applrand, doJobwhenChanged_t& applrandmask)
         {
             this->Job_apply = &appl;
             this->Job_applyRand = &applrand;
             this->Job_applyRand_mask = &applrandmask;
         }
         void Build(CWindowsBuilder& builder, int left, int top, int buttonwidth, int bheight, int gap)
         {

             builder.ChangeLeftPos(left);
             builder.ChangeWidth(buttonwidth);
             builder.ChangeHeight(bheight);
             builder.ChangeTopPos(top);
             builder.ChangeTextP(ws_empty_text);
             builder.ChangeStyle(FlatRadioButtonStyleInvisble_CENTER);
             this->randmasksymbolsreplacenormaldata_autochange.Visit(&builder);
             builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap);
             builder.ChangeStyle(FlatButtonStyleInvisble);
             builder.ChangeTextP(ws_buttontext);
             this->apply.Visit(&builder);
             builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap);
             this->applyrand.Visit(&builder);
         }
         void ApplyFont(CWindowsFontApplier& fontmaster)
         {
             apply.Visit(&fontmaster);
             applyrand.Visit(&fontmaster);
             randmasksymbolsreplacenormaldata_autochange.Visit(&fontmaster);
         }
         void Show() const
         {
             randmasksymbolsreplacenormaldata_autochange.Show();
             apply.Show();
             applyrand.Show();
         }
         void Hide() const
         {
             randmasksymbolsreplacenormaldata_autochange.Hide();
             apply.Hide();
             applyrand.Hide();
         }
         void SaveCfg(CWindowCfgWriter& writer)
         {
             writer.SaveButtonStateW(&(this->randmasksymbolsreplacenormaldata_autochange));
         }
         void LoadCfg(CWindowCfgReader& reader, size_t txtlimit = 8)
         {
             reader.LoadButtonStateW(&(this->randmasksymbolsreplacenormaldata_autochange));
         }
         void ButtonHandler(WPARAM& wparam)
         {
             if (this->apply.id == LOWORD(wparam))
             {
                 this->Job_apply();
             }
             else if (this->applyrand.id == LOWORD(wparam))
             {
                 if (randmasksymbolsreplacenormaldata_autochange.isPressed) {
                     this->Job_applyRand_mask();
                 }
                 else {
                     this->Job_applyRand();
                 }
             }
             else if (this->randmasksymbolsreplacenormaldata_autochange.id == LOWORD(wparam))
             {
                 randmasksymbolsreplacenormaldata_autochange.SwitchState();
             }
         }
         void ForceExecuteJob_ApplyRand()
         {
             if (randmasksymbolsreplacenormaldata_autochange.isPressed) {
                 this->Job_applyRand_mask();
             }
             else {
                 this->Job_applyRand();
             }
         }
     };


     CWinControlBlock control_nicknameetc(ReadData_ChangeNicknameEtc_andUpdate, ReadRandData_ChangeNicknameEtc_andUpdate, ReadRandDataMask_ChangeNicknameEtc_andUpdate);
     CWindow_button_cfg nickname_autochage;

     CWindow_button xuidhwid_page;
     CWindow_button localexternalip_page;
     CWindow_button firmware_page;
     CWindow_button upnp_page;
     bool firmware_page_is_opened = false;
     CWindow_button_cfg xuidhwid_autochange;
     CWindow_button_cfg localexternalip_autochange;
     CWindow_button_cfg firmware_autochange;
     CWindow_button_cfg upnp_autochange;

     WinCombo xuid_part1;
     WinCombo xuid_part2;
     WinCombo hwid_part1;
     WinCombo hwid_part2;
     WinCombo hwid_part3;
     CWinControlBlock control_xuidhwid(ReadData_ChangeXUIDHWID_andUpdate, ReadRandData_ChangeXUIDHWID_andUpdate, ReadRandDataMask_ChangeXUIDHWID_andUpdate);

     WinCombo localip;
     WinCombo lip_port;
     WinCombo externalip;
     WinCombo exip_port;
     WinCombo someip1;
     WinCombo someip1_port;
     WinCombo someip2;
     WinCombo someip2_port;
     CWinControlBlock control_externallocalips(ReadData_ChangeNETData, ReadRandData_ChangeNETData, ReadRandDataMask_ChangeNETData);
     

     namespace firmware
     {
         CWindow_edit challengeS2_part_1;
         CWindow_edit challengeS2_part_2;
         CWindow_edit challengeS2_part_3;
         CWindow_edit challengeS2_part_4;
         wchar_t ws_generate[] = L"generate";
         CWindow_button generate_new_firmware;
         wchar_t ws_randall[] = L"rand all";
         CWindow_button_cfg rand_all_firmware;
         wchar_t ws_alwaysnew[] = L"always new";
         CWindow_button_cfg generate_always_new;
         void ButtonHandler(WPARAM& param)
         {
             if (LOWORD(param) == generate_new_firmware.id)
             {
                 hooks::sysinfoapi_functions::GetSystemFirmwareTable_SetState_GenerateNewData();
                 hooks::sysinfoapi_functions::GetSystemFirmwareTable_SetState_FakingDataEnabled(true);
             }
             else if (LOWORD(param) == rand_all_firmware.id)
             {
                 rand_all_firmware.SwitchState();
                 hooks::sysinfoapi_functions::GetSystemFirmwareTable_SetState_RandomiseAllDataEnabled(rand_all_firmware.isPressed);

             }
             else if (LOWORD(param) == generate_always_new.id)
             {
                 generate_always_new.SwitchState();
                 hooks::sysinfoapi_functions::GetSystemFirmwareTable_SetState_AlwaysGenerateNewDataEnabled(generate_always_new.isPressed);
             }
             else
             {

             }
         }
         void SaveSettings_PreCreateVer(CWindowCfgWriter* writer);
         void LoadSettings_PreCreateVer(CWindowCfgReader* reader);
         void SaveSettings_PreCreateVer(CWindowCfgWriter* writer)
         {
             writer->SaveButtonStateW(&firmware_autochange);
         }
         void LoadSettings_PreCreateVer(CWindowCfgReader* reader)
         {
             firmware_autochange.isPressed = reader->LoadButtonStateW();
             hooks::sysinfoapi_functions::GetSystemFirmwareTable_SetState_FakingDataEnabled(firmware_autochange.isPressed);
         }
         void SaveCfg(CWindowCfgWriter* writer)
         {
             writer->SaveButtonStateW(&rand_all_firmware);
             writer->SaveButtonStateW(&generate_always_new);
         }
         void LoadCfg(CWindowCfgReader* reader)
         {
             reader->LoadButtonStateW(&rand_all_firmware);
             reader->LoadButtonStateW(&generate_always_new);
         }
     };

     namespace UPnP
     {
         namespace textlim
         {
             constexpr size_t device_field_location = hooks::bdUPnP_functions::ns_extractDeviceInfo::maxtext_field_location;
             constexpr size_t device_field_server = hooks::bdUPnP_functions::ns_extractDeviceInfo::maxtext_field_server;
             constexpr size_t device_field_USN = hooks::bdUPnP_functions::ns_extractDeviceInfo::maxtext_field_USN;
         };
         WinCombo device_field_location;
         WinCombo device_field_server;
         WinCombo device_field_USN;
         CWinControlBlock control_deviceinfo(ReadData_ChangeDeviceInfo, ReadRandData_ChangeDeviceInfo, ReadRandDataMask_ChangeDeviceInfo);
         void SaveSettings_PreCreateVer(CWindowCfgWriter* writer);
         void LoadSettings_PreCreateVer(CWindowCfgReader* reader);
     };

     const wchar_t ws_xuidhwid[] = L"xuid/hwid";
     const wchar_t ws_localexternalip[] = L"NAT";
     const wchar_t ws_UPnP[] = L"UPnP";
     const wchar_t ws_firmware[] = L"firmware";
     const wchar_t ws_auto[] = L"auto";
     const wchar_t ws_hhhhhhhh[] = L"hhhhhhhh";
         
     CWindowPostLoadStrings WinStringsPostLoader;
     void ButtonStatesPostLoader();
}

void CWindowCfgWriter_Wrapper_SaveWinCombo(windows_accountpage::WinCombo& combo, CWindowCfgWriter* writer, unsigned short textlim = 32)
{
    writer->SaveTextSettingW(&combo.edit_new, textlim);
    writer->SaveTextSettingW(&combo.edit_new_randmask, textlim);
}

void CWindowCfgWriter_Wrapper_LoadWinCombo(CWindowCfgReader* reader, windows_accountpage::WinCombo& combo, unsigned short textlim = 64)
{
    reader->LoadTextSettingW(&combo.edit_new, textlim);
    reader->LoadTextSettingW(&combo.edit_new_randmask, textlim);
}


void windows_accountpage::Build(CWindowsBuilder& builder, int left, int width, int top, int height, HWND hwnd)
{
    constexpr int applybuttonwidth = 18;
    builder.ChangeParentHWND(hwnd);
    builder.ChangeLeftPos(left);
    builder.ChangeTopPos(top);
    builder.ChangeTextP(ws_empty_text);

    int freewidth = width - left * 2;
    int gap = 5;
    int rheight = 20;
    int rwidth = 140;
    int savetop = top;
    int rwidth2 = 50;

    builder.ChangeWidth(rwidth);
    builder.ChangeHeight(20);
    BuildTripleBar(builder, nickname, gap);
    
    rwidth = 175;
    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, title, gap);

    rwidth = 28;
    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, titletype, gap);

    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, emblem, gap);

    rwidth = 23;
    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, prestige, gap);

    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    //builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, level, gap);

    rwidth = 70;
    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, clantag, gap);

    rwidth = applybuttonwidth;

    control_nicknameetc.Build(builder, /*hwnd,*/ builder.build_left_pos + builder.build_width + gap, savetop, applybuttonwidth, rheight, gap);

    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeStyle(FlatRadioButtonStyleInvisble_RIGHT);
    builder.ChangeWidth(rwidth2);
    builder.ChangeTextP(ws_auto);
    nickname_autochage.Visit(&builder);
    builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap);
    builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap);

    constexpr int numberofbuttons = 4;
    rwidth = (freewidth - numberofbuttons * gap) / numberofbuttons;
    rwidth -= gap * numberofbuttons / 2;

    builder.ChangeStyle(FlatButtonStyleInvisble);
    builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap * 2);
    builder.ChangeLeftPos(left);
    builder.ChangeWidth(rwidth);
    builder.ChangeTextP(ws_xuidhwid);
    xuidhwid_page.Visit(&builder);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeTextP(ws_localexternalip);
    localexternalip_page.Visit(&builder);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeTextP(ws_firmware);
    firmware_page.Visit(&builder);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeTextP(ws_UPnP);
    upnp_page.Visit(&builder);

    rwidth2 = 20 + 40;
    builder.ChangeTopPos(builder.build_top_pos + builder.build_height);
    builder.ChangeLeftPos(left);
    builder.ChangeWidth(rwidth2);
    builder.ChangeTextP(ws_auto);
    builder.ChangeStyle(FlatRadioButtonStyleInvisble);
    xuidhwid_autochange.Visit(&builder);
    builder.ChangeLeftPos(left + rwidth + gap);
    localexternalip_autochange.Visit(&builder);
    builder.ChangeLeftPos(builder.build_left_pos + rwidth + gap);
    firmware_autochange.Visit(&builder);
    builder.ChangeLeftPos(builder.build_left_pos + rwidth + gap);
    upnp_autochange.Visit(&builder);

    builder.ChangeStyle(NewEditStyle_Invisible);

    rwidth = 70;
    savetop = builder.build_top_pos + builder.build_height +  gap * 2;
    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(left);
    builder.ChangeTextP(ws_empty_text);
    builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, xuid_part1, gap);

    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    BuildTripleBar(builder, xuid_part2, gap);

    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap * 2);
    BuildTripleBar(builder, hwid_part1, gap);

    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    BuildTripleBar(builder, hwid_part2, gap);

    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    BuildTripleBar(builder, hwid_part3, gap);
    

    control_xuidhwid.Build(builder, /*hwnd,*/ builder.build_left_pos + builder.build_width + gap, savetop, applybuttonwidth, rheight, gap);

    builder.ChangeStyle(NewEditStyle_Invisible);

    rwidth = 116;
    int rwidth_port = 46;
    builder.ChangeTextP(ws_empty_text);
    //savetop = builder.build_top_pos + builder.build_height + gap * 2;
    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(left);
    builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, localip, gap);

    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth_port);
    BuildTripleBar(builder, lip_port, gap);

    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, externalip, gap);

    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth_port);
    BuildTripleBar(builder, exip_port, gap);

    control_externallocalips.Build(builder, /*hwnd,*/ builder.build_left_pos + builder.build_width + gap, savetop, applybuttonwidth, rheight, gap);

    builder.ChangeStyle(NewEditStyle_Invisible);

    rwidth = 116;
    builder.ChangeTextP(ws_empty_text);
    int savetop2 = builder.build_top_pos + builder.build_height + gap;
    builder.ChangeTopPos(savetop2);
    builder.ChangeLeftPos(left);
    builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, someip1, gap);

    builder.ChangeTopPos(savetop2);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth_port);
    BuildTripleBar(builder, someip1_port, gap);

    builder.ChangeTopPos(savetop2);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth);
    BuildTripleBar(builder, someip2, gap);

    builder.ChangeTopPos(savetop2);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    builder.ChangeWidth(rwidth_port);
    BuildTripleBar(builder, someip2_port, gap);

    rwidth = 280;
    builder.ChangeWidth(rwidth);
    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(left);
    builder.ChangeStyle(NewEditStyle_Invisible);
    builder.ChangeTextP(ws_empty_text);
    BuildTripleBar(builder, UPnP::device_field_location, gap);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    //rwidth = 250;
    builder.ChangeWidth(rwidth);
    builder.ChangeTopPos(savetop);
    BuildTripleBar(builder, UPnP::device_field_server, gap);
    rwidth = rwidth*2 + gap;
    builder.ChangeWidth(rwidth);
    builder.ChangeLeftPos(left);
    builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap);
    BuildTripleBar(builder, UPnP::device_field_USN, gap);

    builder.ChangeTopPos(savetop);
    UPnP::control_deviceinfo.Build(builder, /*hwnd,*/ builder.build_left_pos + builder.build_width + gap, savetop, applybuttonwidth, rheight, gap);
    UPnP::update_device::Location(L"<Error> no UPnP device");
    UPnP::update_device::Server(L"<Error> no UPnP device");
    UPnP::update_device::USN(L"<Error> no UPnP device");

    rwidth = 70;
    builder.ChangeWidth(rwidth);
    builder.ChangeTopPos(savetop);
    builder.ChangeLeftPos(left);
    builder.ChangeStyle(NewEditStyle_Invisible);
    builder.ChangeTextP(ws_empty_text);
    firmware::challengeS2_part_1.Visit(&builder);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    firmware::challengeS2_part_2.Visit(&builder);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    firmware::challengeS2_part_3.Visit(&builder);
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap);
    firmware::challengeS2_part_4.Visit(&builder);
    rwidth = 60;
    builder.ChangeLeftPos(builder.build_left_pos + builder.build_width + gap*2);
    builder.ChangeStyle(FlatButtonStyleInvisble);
    builder.ChangeTextP(firmware::ws_generate);
    firmware::generate_new_firmware.Visit(&builder);

    builder.ChangeLeftPos(left);
    builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap);
    rwidth2 = 20 + 70;
    builder.ChangeWidth(rwidth2);
    builder.ChangeTextP(firmware::ws_alwaysnew);
    builder.ChangeStyle(FlatRadioButtonStyleInvisble);
    firmware::generate_always_new.Visit(&builder);
    builder.ChangeTopPos(builder.build_top_pos + builder.build_height + gap);
    builder.ChangeTextP(firmware::ws_randall);
    firmware::rand_all_firmware.Visit(&builder);
}

void windows_accountpage::ApplyFonts(CWindowsFontApplier& fontappl)
{
    nickname.ApplyFont(fontappl);
    title.ApplyFont(fontappl);
    titletype.ApplyFont(fontappl);
    emblem.ApplyFont(fontappl);
    level.ApplyFont(fontappl);
    prestige.ApplyFont(fontappl);
    clantag.ApplyFont(fontappl);
    control_nicknameetc.ApplyFont(fontappl);
    nickname_autochage.Visit(&fontappl);

    xuidhwid_page.Visit(&fontappl);
    xuidhwid_autochange.Visit(&fontappl);;
    localexternalip_page.Visit(&fontappl);;
    localexternalip_autochange.Visit(&fontappl);
    upnp_page.Visit(&fontappl);
    upnp_autochange.Visit(&fontappl);

    xuid_part1.ApplyFont(fontappl);
    xuid_part2.ApplyFont(fontappl);
    hwid_part1.ApplyFont(fontappl);
    hwid_part2.ApplyFont(fontappl);
    hwid_part3.ApplyFont(fontappl);
    control_xuidhwid.ApplyFont(fontappl);

    localip.ApplyFont(fontappl);
    lip_port.ApplyFont(fontappl);
    externalip.ApplyFont(fontappl);
    exip_port.ApplyFont(fontappl);
    someip1.ApplyFont(fontappl);
    someip1_port.ApplyFont(fontappl);
    someip2.ApplyFont(fontappl);
    someip2_port.ApplyFont(fontappl);
    control_externallocalips.ApplyFont(fontappl);

    firmware_page.Visit(&fontappl);
    firmware_autochange.Visit(&fontappl);

    UPnP::device_field_location.ApplyFont(fontappl);
    UPnP::device_field_server.ApplyFont(fontappl);
    UPnP::device_field_USN.ApplyFont(fontappl);
    UPnP::control_deviceinfo.ApplyFont(fontappl);
         
    firmware::challengeS2_part_1.Visit(&fontappl);
    firmware::challengeS2_part_2.Visit(&fontappl);
    firmware::challengeS2_part_3.Visit(&fontappl);
    firmware::challengeS2_part_4.Visit(&fontappl);
    firmware::generate_new_firmware.Visit(&fontappl);
    firmware::generate_always_new.Visit(&fontappl);
    firmware::rand_all_firmware.Visit(&fontappl);
}


void windows_accountpage::WriteDefault()
{
    CWindowTextWriter_WriteText(&nickname.edit_new_randmask, L"uull0xdd");
    CWindowTextWriter_WriteText(&title.edit_new_randmask, L"my ip d.dd.dd.d");
    CWindowTextWriter_WriteText(&titletype.edit_new, L"124");
    CWindowTextWriter_WriteText(&emblem.edit_new, L"34");
    CWindowTextWriter_WriteText(&titletype.edit_new_randmask, L"0dd");
    CWindowTextWriter_WriteText(&emblem.edit_new_randmask, L"0dd");
    CWindowTextWriter_WriteText(&prestige.edit_new_randmask, L"0d");
    CWindowTextWriter_WriteText(&level.edit_new_randmask, L"0d");

    CWindowTextWriter_WriteText(&xuid_part2.edit_new_randmask, L"01100001");
    CWindowTextWriter_WriteText(&xuid_part1.edit_new_randmask, ws_hhhhhhhh);
    CWindowTextWriter_WriteText(&hwid_part1.edit_new_randmask, ws_hhhhhhhh);
    CWindowTextWriter_WriteText(&hwid_part2.edit_new_randmask, ws_hhhhhhhh);
    CWindowTextWriter_WriteText(&hwid_part3.edit_new_randmask, ws_hhhhhhhh);

    CWindowTextWriter_WriteText(&localip.edit_new_randmask, L"192.168.d.d");
    CWindowTextWriter_WriteText(&externalip.edit_new_randmask, L"76.dd.dd.dd");

}

void windows_accountpage::ApplyTextLimits()
{

    nickname.ApplyTextLimit(txtlimit_nickname);
    title.ApplyTextLimit(txtlimit_title);
    clantag.ApplyTextLimit(txtlimit_clantag);
    emblem.ApplyTextLimit(txtlimit_emlem_and_title_types);
    titletype.ApplyTextLimit(txtlimit_emlem_and_title_types);
    prestige.ApplyTextLimit(txtlimit_level_and_prestiges_values);
    level.ApplyTextLimit(txtlimit_level_and_prestiges_values);
    xuid_part1.ApplyTextLimit(txtlimit_xuid_hwid_values);
    xuid_part2.ApplyTextLimit(txtlimit_xuid_hwid_values);
    hwid_part1.ApplyTextLimit(txtlimit_xuid_hwid_values);
    hwid_part2.ApplyTextLimit(txtlimit_xuid_hwid_values);
    hwid_part3.ApplyTextLimit(txtlimit_xuid_hwid_values);
    UPnP::device_field_location.ApplyTextLimit(UPnP::textlim::device_field_location);
    UPnP::device_field_server.ApplyTextLimit(UPnP::textlim::device_field_server);
    UPnP::device_field_USN.ApplyTextLimit(UPnP::textlim::device_field_USN);
}

void windows_accountpage::Show()
{
    nickname.Show();
    title.Show();
    titletype.Show();
    emblem.Show();
    level.Show();
    prestige.Show();
    clantag.Show();
    control_nicknameetc.Show();
    nickname_autochage.Show();

    xuidhwid_page.Show();
    xuidhwid_autochange.Show();
    localexternalip_page.Show();
    localexternalip_autochange.Show();
    firmware_page.Show();
    firmware_autochange.Show();
    upnp_page.Show();
    upnp_autochange.Show();

    

}

void windows_accountpage::Hide()
{
    nickname.Hide();
    title.Hide();
    titletype.Hide();
    emblem.Hide();
    level.Hide();
    prestige.Hide();
    clantag.Hide();
    control_nicknameetc.Hide();
    nickname_autochage.Hide();

    xuidhwid_page.Hide();
    xuidhwid_autochange.Hide();
    localexternalip_page.Hide();
    localexternalip_autochange.Hide();

    firmware_page.Hide();
    firmware_autochange.Hide();
    upnp_page.Hide();
    upnp_autochange.Hide();

    Hide_XuidHwidPage();
    Hide_LocalExternalIPPage();
    Hide_FirmwarePage();
    Hide_UPnPPage();
}

void windows_accountpage::Show_XuidHwidPage()
{
    xuid_part1.Show();
    xuid_part2.Show();
    hwid_part1.Show();
    hwid_part2.Show();
    hwid_part3.Show();
    control_xuidhwid.Show();
}

void windows_accountpage::Hide_XuidHwidPage()
{
    xuid_part1.Hide();
    xuid_part2.Hide();
    hwid_part1.Hide();
    hwid_part2.Hide();
    hwid_part3.Hide();
    control_xuidhwid.Hide();
}

void windows_accountpage::Show_LocalExternalIPPage()
{
    localip.Show();
    lip_port.Show();
    externalip.Show();
    exip_port.Show();
    someip1.Show();
    someip1_port.Show();
    someip2.Show();
    someip2_port.Show();
    control_externallocalips.Show();
}

void windows_accountpage::Hide_LocalExternalIPPage()
{
    localip.Hide();
    lip_port.Hide();
    externalip.Hide();
    exip_port.Hide();
    someip1.Hide();
    someip1_port.Hide();
    someip2.Hide();
    someip2_port.Hide();
    control_externallocalips.Hide();
}

void windows_accountpage::Show_FirmwarePage()
{
    firmware::challengeS2_part_1.Show();
    firmware::challengeS2_part_2.Show();
    firmware::challengeS2_part_3.Show();
    firmware::challengeS2_part_4.Show();
    firmware::generate_new_firmware.Show();
    firmware::generate_always_new.Show();
    firmware::rand_all_firmware.Show();
    firmware_page_is_opened = true;
}

void windows_accountpage::Hide_FirmwarePage()
{
    firmware::challengeS2_part_1.Hide();
    firmware::challengeS2_part_2.Hide();
    firmware::challengeS2_part_3.Hide();
    firmware::challengeS2_part_4.Hide();
    firmware::generate_new_firmware.Hide();
    firmware::generate_always_new.Hide();
    firmware::rand_all_firmware.Hide();
    firmware_page_is_opened = false;
}

void windows_accountpage::Show_UPnPPage()
{
    UPnP::device_field_location.Show();
    UPnP::device_field_server.Show();
    UPnP::device_field_USN.Show();
    UPnP::control_deviceinfo.Show();
}

void windows_accountpage::Hide_UPnPPage()
{
    UPnP::device_field_location.Hide();
    UPnP::device_field_server.Hide();
    UPnP::device_field_USN.Hide();
    UPnP::control_deviceinfo.Hide();
}

void windows_accountpage::Show_XuidHwidPageHideOthers()
{
    Hide_LocalExternalIPPage();
    Hide_FirmwarePage();
    Hide_UPnPPage();
    Show_XuidHwidPage();
}

void windows_accountpage::Show_LocalExternalIPHideOthers()
{
    Hide_XuidHwidPage();
    Hide_FirmwarePage();
    Hide_UPnPPage();
    Show_LocalExternalIPPage();
}

void windows_accountpage::Show_FirmwareHideOthers()
{
    Hide_LocalExternalIPPage();
    Hide_XuidHwidPage();
    Hide_UPnPPage();
    Show_FirmwarePage();
}

void windows_accountpage::Show_UPnPPageHideOthers()
{
    Hide_LocalExternalIPPage();
    Hide_XuidHwidPage();
    Hide_FirmwarePage();
    Show_UPnPPage();
}


void windows_accountpage::Handler_ClickButton(WPARAM wparam)
{
    
    WORD low = LOWORD(wparam);
    control_nicknameetc.ButtonHandler(wparam);
    control_xuidhwid.ButtonHandler(wparam);
    control_externallocalips.ButtonHandler(wparam);
    UPnP::control_deviceinfo.ButtonHandler(wparam);
    firmware::ButtonHandler(wparam);
    if (low == xuidhwid_page.id)
    {
        Show_XuidHwidPageHideOthers();
    }
    else if (low == localexternalip_page.id)
    {
        Show_LocalExternalIPHideOthers();
    }
    else if (low == firmware_page.id)
    {
        Show_FirmwareHideOthers();
     }
    else if (low == upnp_page.id)
    {
        Show_UPnPPageHideOthers();
    }
    else if (low == nickname_autochage.id)
    {
        nickname_autochage.SwitchState();
    }
    else if (low == xuidhwid_autochange.id)
    {
        xuidhwid_autochange.SwitchState();
    }
    else if (low == localexternalip_autochange.id)
    {
        localexternalip_autochange.SwitchState();
    }
    else if (low == firmware_autochange.id)
    {
         firmware_autochange.SwitchState();
         hooks::sysinfoapi_functions::GetSystemFirmwareTable_SetState_FakingDataEnabled(firmware_autochange.isPressed);
    }
    else if (low == upnp_autochange.id)
    {
        upnp_autochange.SwitchState();

    }
    else
    {

    }

}


void windows_accountpage::UPnP::SaveSettings_PreCreateVer(CWindowCfgWriter* writer)
{
    writer->SaveButtonStateW(&upnp_autochange);
    writer->SaveTextSettingW(&UPnP::device_field_location.edit_new_randmask, UPnP::textlim::device_field_location);
    writer->SaveTextSettingW(&UPnP::device_field_server.edit_new_randmask, UPnP::textlim::device_field_server);
    writer->SaveTextSettingW(&UPnP::device_field_USN.edit_new_randmask, UPnP::textlim::device_field_USN);
    writer->SaveTextSettingW(&UPnP::device_field_location.edit_new, UPnP::textlim::device_field_location);
    writer->SaveTextSettingW(&UPnP::device_field_server.edit_new, UPnP::textlim::device_field_server);
    writer->SaveTextSettingW(&UPnP::device_field_USN.edit_new, UPnP::textlim::device_field_USN);
}

namespace windows_accountpage
{
    namespace UPnP
    {
        typedef void setinfo_t(const wchar_t*);
        void SingleLoad(CWindowCfgReader* reader, WinCombo& edit, unsigned short sz, CWindow_button_cfg& cfgb, setinfo_t& func)
        {
            const wchar_t* pp = ws_empty_text;
            pp = reader->LoadTextSettingW(sz);
            WinStringsPostLoader.LoadTextSettingW(&edit.edit_new_randmask, pp, sz);
            if (cfgb.isPressed)
            {
                wchar_t* data = lazysectionbuffer_3x512.GetNulledMem(sz + 4, 0);
                parsers::ParseRandMaskTextW(pp, sz, data, sz);
                func(data);
            }
        }
    };
};

void windows_accountpage::UPnP::LoadSettings_PreCreateVer(CWindowCfgReader* reader)
{
    upnp_autochange.isPressed = reader->LoadButtonStateW();
    SingleLoad(reader, UPnP::device_field_location, UPnP::textlim::device_field_location, upnp_autochange, hooks::bdUPnP_functions::SetDeviceInfo_location);
    SingleLoad(reader, UPnP::device_field_server, UPnP::textlim::device_field_server, upnp_autochange, hooks::bdUPnP_functions::SetDeviceInfo_server);
    SingleLoad(reader, UPnP::device_field_USN, UPnP::textlim::device_field_USN, upnp_autochange, hooks::bdUPnP_functions::SetDeviceInfo_USN);
    const wchar_t* pp = nullptr;
    pp = reader->LoadTextSettingW(UPnP::textlim::device_field_location);
    WinStringsPostLoader.LoadTextSettingW(&UPnP::device_field_location.edit_new, pp, UPnP::textlim::device_field_location);
    pp = reader->LoadTextSettingW(UPnP::textlim::device_field_server);
    WinStringsPostLoader.LoadTextSettingW(&UPnP::device_field_server.edit_new, pp, UPnP::textlim::device_field_location);
    pp = reader->LoadTextSettingW(UPnP::textlim::device_field_USN);
    WinStringsPostLoader.LoadTextSettingW(&UPnP::device_field_USN.edit_new, pp, UPnP::textlim::device_field_location);

}

void windows_accountpage::Cfg_SavePreCreateWindowSettings(CWindowCfgWriter* writer)
{
    writer->SaveButtonStateW(&localexternalip_autochange);
    firmware::SaveSettings_PreCreateVer(writer);
    UPnP::SaveSettings_PreCreateVer(writer);
}

void windows_accountpage::Cfg_LoadPreCreateWindowSettings(CWindowCfgReader* reader)
{
    WinStringsPostLoader.Register(256);
    localexternalip_autochange.isPressed = reader->LoadButtonStateW();
    firmware::LoadSettings_PreCreateVer(reader);
    UPnP::LoadSettings_PreCreateVer(reader);

    //ExecutionAfterSettingsPreload();
}

void windows_accountpage::ButtonStatesPostLoader()
{
    CWindowButtonStatePostLoader loader;
    localexternalip_autochange.Visit(&loader);
    firmware_autochange.Visit(&loader);
    upnp_autochange.Visit(&loader);
}

void windows_accountpage::Cfg_Save(CWindowCfgWriter* writer)
{

    CWindowCfgWriter_Wrapper_SaveWinCombo(nickname, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(title, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(titletype, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(emblem, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(level, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(prestige, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(clantag, writer);

    writer->SaveButtonStateW(&nickname_autochage);

    CWindowCfgWriter_Wrapper_SaveWinCombo(xuid_part1, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(xuid_part2, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(hwid_part1, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(hwid_part2, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(hwid_part3, writer);
    
    writer->SaveButtonStateW(&xuidhwid_autochange);

    CWindowCfgWriter_Wrapper_SaveWinCombo(localip, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(lip_port, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(externalip, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(exip_port, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(someip1, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(someip1_port, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(someip2, writer);
    CWindowCfgWriter_Wrapper_SaveWinCombo(someip2_port, writer);

    control_nicknameetc.SaveCfg(*writer);
    control_externallocalips.SaveCfg(*writer);
    control_xuidhwid.SaveCfg(*writer);
    UPnP::control_deviceinfo.SaveCfg(*writer);

    firmware::SaveCfg(writer);
}

void windows_accountpage::Cfg_Load(CWindowCfgReader* reader)
{

    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, nickname);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, title);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, titletype);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, emblem);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, level);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, prestige);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, clantag);

    reader->LoadButtonStateW(&nickname_autochage);

    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, xuid_part1);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, xuid_part2);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, hwid_part1);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, hwid_part2);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, hwid_part3);

    reader->LoadButtonStateW(&xuidhwid_autochange);

    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, localip);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, lip_port);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, externalip);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, exip_port);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, someip1);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, someip1_port);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, someip2);
    CWindowCfgWriter_Wrapper_LoadWinCombo(reader, someip2_port);

    control_nicknameetc.LoadCfg(*reader);
    control_externallocalips.LoadCfg(*reader);
    control_xuidhwid.LoadCfg(*reader);
    UPnP::control_deviceinfo.LoadCfg(*reader);

    firmware::LoadCfg(reader);

    WinStringsPostLoader.LoadTextInEdits();
    WinStringsPostLoader.Unregister();
    ButtonStatesPostLoader();
}

namespace windows_accountpage
{
    template<size_t id>
    void ReadSmth_ChangeNicknameEtc_andUpdate()
    {
        iw5mp_changedata::ChangeNickname(nickname.GetTextW<id>(txtlimit_nickname + 4));
        iw5mp_changedata::ChangeTitle(title.GetTextW<id>(txtlimit_title + 4));
        iw5mp_changedata::ChangeClanTag(clantag.GetTextW<id>(txtlimit_clantag + 4));

        iw5mp_changedata::ChangeTitleType(textconvertors::ConvertWTextDecTypeToU32(titletype.GetTextW<id>(txtlimit_emlem_and_title_types + 4)));
        iw5mp_changedata::ChangeEmblemType(textconvertors::ConvertWTextDecTypeToU32(emblem.GetTextW<id>(txtlimit_emlem_and_title_types + 4)));
        iw5mp_changedata::ChangePrestige(textconvertors::ConvertWTextDecTypeToU32(prestige.GetTextW<id>(txtlimit_level_and_prestiges_values + 4)));
        iw5mp_changedata::ChangeLevel(textconvertors::ConvertWTextDecTypeToU32(level.GetTextW<id>(txtlimit_level_and_prestiges_values + 4)));
        UpdateCurrentNickanameEtc();
    }
}

void windows_accountpage::ReadData_ChangeNicknameEtc_andUpdate()
{
    ReadSmth_ChangeNicknameEtc_andUpdate<0>();
}

void windows_accountpage::ReadRandData_ChangeNicknameEtc_andUpdate()
{
    ReadSmth_ChangeNicknameEtc_andUpdate<1>();
}

void windows_accountpage::ReadRandDataMask_ChangeNicknameEtc_andUpdate()
{
    ReadSmth_ChangeNicknameEtc_andUpdate<2>();
}

namespace windows_accountpage
{
    template<size_t id>
    void ReadSmth_ChangeXUIDHWID_andUpdate()
    {
        uint32_t xpart1 = 0;
        uint32_t xpart2 = 0;
        bool updateAllowed = false;
        xpart1 = textconvertors::ConvertWTextHexTypeToU32(xuid_part1.GetTextW<id>(txtlimit_xuid_hwid_values + 4));
        xpart2 = textconvertors::ConvertWTextHexTypeToU32(xuid_part2.GetTextW<id>(txtlimit_xuid_hwid_values + 4));
        iw5mp_changedata::ChangeXUID(xpart1, xpart2);
        iw5mp_changedata::ChangeSteamAPIXUID(xpart1, xpart2);
        updateAllowed = iw5mp_changedata::ChangeSteamAPIsteamid(xpart1, xpart2);
        iw5mp_changedata::ChangeHWID( 
            textconvertors::ConvertWTextHexTypeToU32(hwid_part1.GetTextW<id>(txtlimit_xuid_hwid_values + 4)),
                textconvertors::ConvertWTextHexTypeToU32(hwid_part2.GetTextW<id>(txtlimit_xuid_hwid_values + 4)),
                    textconvertors::ConvertWTextHexTypeToU32(hwid_part3.GetTextW<id>(txtlimit_xuid_hwid_values + 4))
        );
        if (updateAllowed == true) {
            UpdateCurrentXUIDHWID();
        }
        else
        {

        }
    }
};


void windows_accountpage::ReadData_ChangeXUIDHWID_andUpdate()
{
    ReadSmth_ChangeXUIDHWID_andUpdate<0>();
}

void windows_accountpage::ReadRandData_ChangeXUIDHWID_andUpdate()
{
    ReadSmth_ChangeXUIDHWID_andUpdate<1>();
}

void windows_accountpage::ReadRandDataMask_ChangeXUIDHWID_andUpdate()
{
    ReadSmth_ChangeXUIDHWID_andUpdate<2>();
}

namespace windows_accountpage
{
    template<size_t id>
    void ReadSmth_ChangeNETData()
    {
        uint8_t ExactlyNewIP[4] = { 0 };
        textconvertors::ConvertWTextToIP(externalip.GetTextW<id>(txtlimit_ip + 4), ExactlyNewIP);
        if (ExactlyNewIP[0]) { hooks::serializeNetData_change::ExternalIP(ExactlyNewIP); }
        textconvertors::ConvertWTextToIP(localip.GetTextW<id>(txtlimit_ip + 4), ExactlyNewIP);
        if (ExactlyNewIP[0]) { hooks::serializeNetData_change::LocalIP(ExactlyNewIP); }
        textconvertors::ConvertWTextToIP(someip1.GetTextW<id>(txtlimit_ip + 4), ExactlyNewIP);
        if (ExactlyNewIP[0]) { hooks::serializeNetData_change::OtherlIP1(ExactlyNewIP); }
        textconvertors::ConvertWTextToIP(someip2.GetTextW<id>(txtlimit_ip + 4), ExactlyNewIP);
        if (ExactlyNewIP[0]) { hooks::serializeNetData_change::OtherlIP2(ExactlyNewIP); }
        uint16_t Port = 0;
        Port = textconvertors::ConvertWTextDecTypeToU16(exip_port.GetTextW<id>(txtlimit_port + 4));
        if (Port != 0) { hooks::serializeNetData_change::ExternalPort(Port); }
        Port = textconvertors::ConvertWTextDecTypeToU16(lip_port.GetTextW<id>(txtlimit_port + 4));
        if (Port != 0) { hooks::serializeNetData_change::LocalPort(Port); }
        Port = textconvertors::ConvertWTextDecTypeToU16(someip1_port.GetTextW<id>(txtlimit_port + 4));
        if (Port != 0) { hooks::serializeNetData_change::OtherPort1(Port); }
        Port = textconvertors::ConvertWTextDecTypeToU16(someip2_port.GetTextW<id>(txtlimit_port + 4));
        if (Port != 0) { hooks::serializeNetData_change::OtherPort2(Port); }
    }
}


void windows_accountpage::ReadData_ChangeNETData()
{
    ReadSmth_ChangeNETData<0>();
}

void windows_accountpage::ReadRandData_ChangeNETData()
{
    ReadSmth_ChangeNETData<1>();
}

void windows_accountpage::ReadRandDataMask_ChangeNETData()
{
    ReadSmth_ChangeNETData<2>();
}

void windows_accountpage::UpdateCurrentNickanameEtc()
{
    CWindowTextWriter_WriteText(&titletype.edit_show, textconvertors::ConvertDecTypeU32ToWText(iw5mp_getdata::GetTitleType()));
    CWindowTextWriter_WriteText(&emblem.edit_show, textconvertors::ConvertDecTypeU32ToWText(iw5mp_getdata::GetEmblem()));
    CWindowTextWriter_WriteText(&prestige.edit_show, textconvertors::ConvertDecTypeU32ToWText(iw5mp_getdata::GetPrestige()));
    CWindowTextWriter_WriteText(&level.edit_show, textconvertors::ConvertDecTypeU32ToWText(iw5mp_getdata::GetLevel()));

    CWindowTextWriter_WriteText(&title.edit_show, iw5mp_getdata::GetTitle());
    CWindowTextWriter_WriteText(&clantag.edit_show, iw5mp_getdata::GetClanTag());
    
    CWindowTextWriter_WriteText(&nickname.edit_show, iw5mp_getdata::GetNickname());
}

void windows_accountpage::UpdateCurrentXUIDHWID()
{
    CWindowTextWriter_WriteText(&xuid_part1.edit_show, textconvertors::ConvertHexTypeU32ToWText(iw5mp_getdata::GetXUID_part1()));
    CWindowTextWriter_WriteText(&xuid_part2.edit_show, textconvertors::ConvertHexTypeU32ToWText(iw5mp_getdata::GetXUID_part2()));

    CWindowTextWriter_WriteText(&hwid_part1.edit_show, textconvertors::ConvertHexTypeU32ToWText(iw5mp_getdata::GetHWID_part1()));
    CWindowTextWriter_WriteText(&hwid_part2.edit_show, textconvertors::ConvertHexTypeU32ToWText(iw5mp_getdata::GetHWID_part2()));
    CWindowTextWriter_WriteText(&hwid_part3.edit_show, textconvertors::ConvertHexTypeU32ToWText(iw5mp_getdata::GetHWID_part3()));
}

void windows_accountpage::UpdateCurrentNETData()
{
    uint8_t addrIP[4] = { 0 };
    hooks::serializeNetData_get::ExternalIP(addrIP);
    CWindowTextWriter_WriteText(&externalip.edit_show, textconvertors::ConvertIPToWText(addrIP));
    hooks::serializeNetData_get::LocalIP(addrIP);
    CWindowTextWriter_WriteText(&localip.edit_show, textconvertors::ConvertIPToWText(addrIP));
    hooks::serializeNetData_get::OtherlIP1(addrIP);
    CWindowTextWriter_WriteText(&someip1.edit_show, textconvertors::ConvertIPToWText(addrIP));
    hooks::serializeNetData_get::OtherlIP2(addrIP);
    CWindowTextWriter_WriteText(&someip2.edit_show, textconvertors::ConvertIPToWText(addrIP));

    CWindowTextWriter_WriteText(&exip_port.edit_show, textconvertors::ConvertDecTypeToU16ToWText(hooks::serializeNetData_get::ExternalPort()));
    CWindowTextWriter_WriteText(&lip_port.edit_show, textconvertors::ConvertDecTypeToU16ToWText(hooks::serializeNetData_get::LocalPort()));
    CWindowTextWriter_WriteText(&someip1_port.edit_show, textconvertors::ConvertDecTypeToU16ToWText(hooks::serializeNetData_get::OtherPort1()));
    CWindowTextWriter_WriteText(&someip2_port.edit_show, textconvertors::ConvertDecTypeToU16ToWText(hooks::serializeNetData_get::OtherPort2()));
}

void windows_accountpage::UpdateCurrentChallengeS2()
{
    CWindowTextWriter_WriteText(&firmware::challengeS2_part_1, textconvertors::ConvertHexTypeU32ToWText(hooks::iw5mp_functions::ns_GetChallengeS2::Get_P1()));
    CWindowTextWriter_WriteText(&firmware::challengeS2_part_2, textconvertors::ConvertHexTypeU32ToWText(hooks::iw5mp_functions::ns_GetChallengeS2::Get_P2()));
    CWindowTextWriter_WriteText(&firmware::challengeS2_part_3, textconvertors::ConvertHexTypeU32ToWText(hooks::iw5mp_functions::ns_GetChallengeS2::Get_P3()));
    CWindowTextWriter_WriteText(&firmware::challengeS2_part_4, textconvertors::ConvertHexTypeU32ToWText(hooks::iw5mp_functions::ns_GetChallengeS2::Get_P4()));
}

void windows_accountpage::DoJobOnConnect()
{
    if (nickname_autochage.isPressed)
    {
        control_nicknameetc.ForceExecuteJob_ApplyRand();
    }
    if (xuidhwid_autochange.isPressed)
    {
        control_xuidhwid.ForceExecuteJob_ApplyRand();
    }
    if (localexternalip_autochange.isPressed)
    {
        control_externallocalips.ForceExecuteJob_ApplyRand();
    }
    if (upnp_autochange.isPressed)
    {
        UPnP::control_deviceinfo.ForceExecuteJob_ApplyRand();
    }
    UpdateCurrentNickanameEtc();

}

void windows_accountpage::UPnP::update_device::Location(const wchar_t* text)
{
   CWindowTextWriter_WriteText(&UPnP::device_field_location.edit_show, text);
}

void windows_accountpage::UPnP::update_device::Server(const wchar_t* text)
{
    CWindowTextWriter_WriteText(&UPnP::device_field_server.edit_show, text);
}

void windows_accountpage::UPnP::update_device::USN(const wchar_t* text)
{
    CWindowTextWriter_WriteText(&UPnP::device_field_USN.edit_show, text);
}


namespace windows_accountpage
{
    template<size_t id>
    void ReadSmth_ChangeDeviceInfo()
    {
        hooks::bdUPnP_functions::SetDeviceInfo_location(UPnP::device_field_location.GetTextW<id>(UPnP::textlim::device_field_location));
        hooks::bdUPnP_functions::SetDeviceInfo_server(UPnP::device_field_server.GetTextW<id>(UPnP::textlim::device_field_server));
        hooks::bdUPnP_functions::SetDeviceInfo_USN(UPnP::device_field_USN.GetTextW<id>(UPnP::textlim::device_field_USN));
        hooks::bdUPnP_functions::SetDeviceInfo();
    }
}

void windows_accountpage::UPnP::ReadData_ChangeDeviceInfo()
{
    ReadSmth_ChangeDeviceInfo<0>();
}


void windows_accountpage::UPnP::ReadRandData_ChangeDeviceInfo()
{
    ReadSmth_ChangeDeviceInfo<1>();

}

void windows_accountpage::UPnP::ReadRandDataMask_ChangeDeviceInfo()
{
    ReadSmth_ChangeDeviceInfo<2>();
}

#include "pch.h"
#include "JMPHook_SerializeNetdata.h"

namespace hooks
{
	typedef void* (__fastcall* SerializeNETData_t)(void* _this, void* edx, void* pDst); // game is using this function for serialize net data in cookieecho
	void* __fastcall hooked_SerializeNetData(void* _this, void* edx, void* pDst);
};


static hooks::SerializeNETData_t OriginalFunction;

struct _sub_6EC2A0_data
{
	uint8_t LocalIP[4]; // 0-3
	uint16_t LPort; // 4-5
	uint8_t RouteIP1[4];
	uint16_t RPort1;
	uint8_t RouteIP2[4];
	uint16_t RPort2;
	uint8_t ExternalIP[4]; // 18-21
	uint16_t EPort; // 22-23 LPort==EPort
};

static _sub_6EC2A0_data NewData = { 0 };
static _sub_6EC2A0_data CurrentData = { 0 };

namespace MustBeChanged
{
	bool ExternalIP = false;
	bool LocalIP = false;
	bool OtherIP1 = false;
	bool OtherIP2 = false;
	bool ExternalPort = false;
	bool LocalPort = false;
	bool OtherPort1 = false;
	bool OtherPort2 = false;
};


inline void __copy_4bytes__in__4bytes__(uint8_t dstIP[4], const uint8_t srcIP[4])
{
	dstIP[0] = srcIP[0];
	dstIP[1] = srcIP[1];
	dstIP[2] = srcIP[2];
	dstIP[3] = srcIP[3];
}

inline void __copy_sub_6EC2A0_data__in___sub_6EC2A0_data__(_sub_6EC2A0_data* dst, _sub_6EC2A0_data* src)
{
	__copy_4bytes__in__4bytes__(dst->ExternalIP, src->ExternalIP);
	__copy_4bytes__in__4bytes__(dst->LocalIP, src->LocalIP);
	__copy_4bytes__in__4bytes__(dst->RouteIP1, src->RouteIP1);
	__copy_4bytes__in__4bytes__(dst->RouteIP2, src->RouteIP2);
	dst->EPort = src->EPort;
	dst->LPort = src->LPort;
	dst->RPort1 = src->RPort1;
	dst->RPort2 = src->RPort2;
}

#define MACRO_CHANGEIP(boolv, dst, src) if(boolv){ __copy_4bytes__in__4bytes__(dst, src); }
#define MACRO_CHANGEPORT(boolv, dst, src) if(boolv){ dst = src ; }

void* __fastcall hooks::hooked_SerializeNetData(void* _this, void* edx, void* pDst)
{
	void* ret;
	ret = OriginalFunction(_this, edx, pDst);

	_sub_6EC2A0_data* pdata = static_cast<_sub_6EC2A0_data*>(pDst);
	MACRO_CHANGEIP(MustBeChanged::ExternalIP, pdata->ExternalIP, NewData.ExternalIP);
	MACRO_CHANGEIP(MustBeChanged::LocalIP, pdata->LocalIP, NewData.LocalIP);
	MACRO_CHANGEIP(MustBeChanged::OtherIP1, pdata->RouteIP1, NewData.RouteIP1);
	MACRO_CHANGEIP(MustBeChanged::OtherIP2, pdata->RouteIP2, NewData.RouteIP2);

	MACRO_CHANGEPORT(MustBeChanged::ExternalPort, pdata->EPort, NewData.EPort);
	MACRO_CHANGEPORT(MustBeChanged::LocalPort, pdata->LPort, NewData.LPort);
	MACRO_CHANGEPORT(MustBeChanged::OtherPort1, pdata->RPort1, NewData.RPort1);
	MACRO_CHANGEPORT(MustBeChanged::OtherPort2, pdata->RPort2, NewData.RPort2);

	__copy_sub_6EC2A0_data__in___sub_6EC2A0_data__(&CurrentData, pdata);

	windows_accountpage::UpdateCurrentNETData();

	return ret;
}

#undef MACRO_CHANGEIP
#undef MACRO_CHANGEPORT

bool hooks::JMPHook_SerializeNetData(uint32_t addr, uint8_t asmlen)
{
	return Hooker_JMP::Hook32<SerializeNETData_t, decltype(hooked_SerializeNetData)>(
		addr,
		hooked_SerializeNetData,
		asmlen,
		OriginalFunction
		);
}




void hooks::serializeNetData_change::ExternalIP(const uint8_t newIP[4])
{
	MustBeChanged::ExternalIP = true;
	__copy_4bytes__in__4bytes__(NewData.ExternalIP, newIP);
}

void hooks::serializeNetData_change::LocalIP(const uint8_t newIP[4])
{
	MustBeChanged::LocalIP = true;
	__copy_4bytes__in__4bytes__(NewData.LocalIP, newIP);
}

void hooks::serializeNetData_change::OtherlIP1(const uint8_t newIP[4])
{
	MustBeChanged::OtherIP1 = true;
	__copy_4bytes__in__4bytes__(NewData.RouteIP1, newIP);
}

void hooks::serializeNetData_change::OtherlIP2(const uint8_t newIP[4])
{
	MustBeChanged::OtherIP2 = true;
	__copy_4bytes__in__4bytes__(NewData.RouteIP2, newIP);
}

void hooks::serializeNetData_change::ExternalPort(const uint16_t newPort)
{
	MustBeChanged::ExternalPort = true;
	NewData.EPort = newPort;
}

void hooks::serializeNetData_change::LocalPort(const uint16_t newPort)
{
	MustBeChanged::LocalPort = true;
	NewData.LPort = newPort;
}

void hooks::serializeNetData_change::OtherPort1(const uint16_t newPort)
{
	MustBeChanged::OtherPort1 = true;
	NewData.RPort1 = newPort;
}

void hooks::serializeNetData_change::OtherPort2(const uint16_t newPort)
{
	MustBeChanged::OtherPort2 = true;
	NewData.RPort2 = newPort;
}

void hooks::serializeNetData_get::ExternalIP(uint8_t newIP[4])
{
	__copy_4bytes__in__4bytes__(newIP, CurrentData.ExternalIP);
}

void hooks::serializeNetData_get::LocalIP(uint8_t newIP[4])
{
	__copy_4bytes__in__4bytes__(newIP, CurrentData.LocalIP);
}

void hooks::serializeNetData_get::OtherlIP1(uint8_t newIP[4])
{
	__copy_4bytes__in__4bytes__(newIP, CurrentData.RouteIP1);
}

void hooks::serializeNetData_get::OtherlIP2(uint8_t newIP[4])
{
	__copy_4bytes__in__4bytes__(newIP, CurrentData.RouteIP2);
}

uint16_t hooks::serializeNetData_get::ExternalPort()
{
	return CurrentData.EPort;
}

uint16_t hooks::serializeNetData_get::LocalPort()
{
	return  CurrentData.LPort;
}

uint16_t hooks::serializeNetData_get::OtherPort1()
{
	return CurrentData.RPort1;
}

uint16_t hooks::serializeNetData_get::OtherPort2()
{
	return  CurrentData.RPort2;
}


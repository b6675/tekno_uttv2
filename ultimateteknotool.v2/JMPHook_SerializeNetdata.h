#pragma once
#include <stdint.h>
#include "Hooker_JMP.h"
#include "windows_accountpage.h"

namespace hooks
{
	bool JMPHook_SerializeNetData(uint32_t addr, uint8_t asmlen);

	namespace serializeNetData_change {
		void ExternalIP(const uint8_t newIP[4]);
		void LocalIP(const uint8_t newIP[4]);
		void OtherlIP1(const uint8_t newIP[4]);
		void OtherlIP2(const uint8_t newIP[4]);
		void ExternalPort(const uint16_t newPort);
		void LocalPort(const uint16_t newPort);
		void OtherPort1(const uint16_t newPort);
		void OtherPort2(const uint16_t newPort);
	};
	namespace serializeNetData_get {
		void ExternalIP(uint8_t newIP[4]);
		void LocalIP(uint8_t newIP[4]);
		void OtherlIP1(uint8_t newIP[4]);
		void OtherlIP2(uint8_t newIP[4]);
		uint16_t ExternalPort();
		uint16_t LocalPort();
		uint16_t OtherPort1();
		uint16_t OtherPort2();
	};
};
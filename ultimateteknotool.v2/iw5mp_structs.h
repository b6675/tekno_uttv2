#pragma once
#include <stdint.h>
#include <stddef.h>

namespace iw5mp_structs
{
	static_assert(sizeof(uint32_t) == 4, "uint32_t is not 4?");
	static_assert(sizeof(uint16_t) == 2, "uint16_t is not 2?");
	static_assert(sizeof(uint8_t) == 1, "uint8_t is not 1?");
#pragma pack(push, 1)

	struct NetDataStructure
	{
		uint32_t netaddresstype;
		uint32_t dw_ip;
		uint16_t w_port;
		uint16_t field_A;
		uint32_t field_C;
		uint32_t field_10;
		uint32_t index;
	};
	static_assert(sizeof(NetDataStructure) == 0x18, "NetDataStructure struct is not 0x18");

	struct ipNport
	{
		uint8_t ip[4];
		uint16_t port;
		ipNport& operator=(const ipNport& data)
		{
			this->ip[0] = data.ip[0];
			this->ip[1] = data.ip[1];
			this->ip[2] = data.ip[2];
			this->ip[3] = data.ip[3];
			this->port = data.port;
			return *this;
		}
	};
	static_assert(sizeof(ipNport) == 6, "ipNport struct is not 6");


	struct playerNetData
	{
		ipNport local;
		ipNport route1;
		ipNport route2;
		ipNport external;
		uint8_t isValid;
		playerNetData& operator=(const playerNetData& data)
		{
			this->local = data.local;
			this->route1 = data.route1;
			this->route2 = data.route2;
			this->external = data.external;
			this->isValid = data.isValid;
			return *this;
		}
		void SetData(const playerNetData* nd)
		{
			this->local = nd->local;
			this->route1 = nd->route1;
			this->route2 = nd->route2;
			this->external = nd->external;
			this->isValid = nd->isValid;
		}
	};
	static_assert(sizeof(playerNetData) == 0x19, "playerNetData struct is not 0x19");

	struct bdSecurityKeyMap_bdSecurityID
	{
		uint8_t id[8];
		bdSecurityKeyMap_bdSecurityID& operator=(const bdSecurityKeyMap_bdSecurityID& data)
		{
			::memcpy(id, data.id, sizeof(id));
			return *this;
		}
		void Init(uint8_t v)
		{
			::memset(this->id, v, sizeof(id));
		}
		void Set(bdSecurityKeyMap_bdSecurityID* res)
		{
			::memcpy(id, res->id, sizeof(id));
		}
	};
	struct bdSecurityKeyMap_bdSecurityKey
	{
		uint8_t key[16];
	};

	struct hostInfo
	{
		uint8_t isValid;
		bdSecurityKeyMap_bdSecurityID bdID;
		playerNetData ND;
		bdSecurityKeyMap_bdSecurityKey bdKey;

	}; static_assert(sizeof(hostInfo) == 0x32, "hostInfo struct is not 0x32");

	struct gamesession_unkstruct64b
	{
		uint8_t isValid;
		uint8_t b1;
		uint8_t b2;
		uint8_t b3;
		uint32_t x4;
		uint64_t xuid;
		uint8_t bi1;
		uint8_t bi2;
		uint8_t bi3;
		uint8_t bi4;
		NetDataStructure netdata;
		uint32_t i5;
		uint32_t i6;
		uint8_t x34;
		uint8_t x35;
		uint8_t x36;
		uint8_t x37;
		uint32_t i7;
		uint32_t i8;
	};
	static_assert(sizeof(gamesession_unkstruct64b) == 64, "gamesession_unkstruct64b struct is not 64");

	struct gamesession_unkstruct24b
	{
		uint8_t isValid;
		uint8_t b1;
		uint8_t b2;
		uint8_t b3;
		uint32_t x4;
		uint64_t xuid;
		uint32_t x10;
		uint32_t x14;

	};
	static_assert(sizeof(gamesession_unkstruct24b) == 0x18, "gamesession_unkstruct24b struct is not 24");

	struct gameSession
	{
		uint32_t off_STRgameSession;
		uint8_t b1;
		uint8_t b2;
		uint8_t b3;
		uint8_t b4;
		hostInfo serverinfo;
		uint8_t x3A;
		uint8_t x3B;
		uint32_t x3C;
		uint64_t fakexuid;
		uint32_t privClients;
		uint32_t totalNumSlots;
		uint32_t mask;
		uint32_t x54;
		gamesession_unkstruct64b x18_64b[18];
		uint32_t x4D8;
		uint32_t IndexND;
		uint32_t x4E0;
		uint32_t x4E4;
		gamesession_unkstruct24b x18_24b[18];
	}; static_assert(sizeof(gameSession) == 0x698, "session struct is not 0x698");
	struct snapshot_unkstruct13068
	{
		uint32_t f0;
		uint32_t type;
		uint32_t f8;
		uint32_t fC;
		uint32_t bytemask;
		uint32_t f14;
		uint32_t f18[78];
		uint32_t index;
		uint32_t arr[3181];
		uint32_t end;
	};
	struct unkstruct256
	{
		uint8_t idk[256];
	};
	struct PlayerInfo_1
	{
		uint32_t id;															//  4
		uint32_t team; //0 - ffa, 1 - team1, 2 - team2, 3 - spectator			//  8
		uint8_t bytes[60];														// 68
		uint8_t name[16]; // last byte should be null							// 84
		uint8_t abytes[4];														// 88
		uint32_t level; // value - 1 = level									// 92
		uint32_t prestige;														// 96
		uint8_t cbytes[16];														//112
		uint32_t emblem;														//116
		uint32_t _0x0000000B;													//120
		uint8_t bytez[4];														//124
		uint32_t ec_usingTag; // bool value										//128
		uint32_t ec_usingTitle; // bool value									//132
		uint8_t ec_Title[24];													//156
		uint32_t ec_TitleBg;													//160
		uint8_t ec_ClanTag[8]; // last byte should be null						//168
	};

	struct cgameGlobstruct_snapshotEntry
	{
		snapshot_unkstruct13068 snapshot;
		uint32_t f330C;
		uint32_t f3310;
		uint32_t f3314;
		uint32_t number_structs256b;
		uint32_t number_structs168b;
		unkstruct256 x768_256b[768];
		PlayerInfo_1 x18_PlayerInfo[18];
		uint32_t end;
	}; static_assert(sizeof(cgameGlobstruct_snapshotEntry) == 0x33EF4, "cgameGlobstruct_snapshotEntry struct is not 0x33EF4");

	struct cgameGlob
	{
		uint32_t f0;
		uint32_t field_4;
		uint32_t field_8;
		uint32_t field_C;
		uint32_t field_10;
		uint32_t field_14;
		uint32_t field_18;
		uint32_t field_1C;
		uint32_t field_20;
		uint32_t field_24;
		uint32_t field_28;
		uint32_t field_2C;
		uint32_t field_30;
		uint32_t field_34[3629];
		uint32_t field_38E8;
		uint32_t field_38EC;
		uint32_t field_38F0[52827];
		uint32_t field_3725C;
		cgameGlobstruct_snapshotEntry snapshotEntry;
	};
	static_assert(offsetof(cgameGlob, snapshotEntry) == 0x3725C + 4, "cgameGlob has wrong offset for cgameGlobstruct_snapshotEntry");


	namespace DTLS
	{
		struct InitPacket
		{
			uint8_t header_high;
			uint8_t header_low;
			uint32_t unknown;
			uint16_t m_initTag;
			iw5mp_structs::bdSecurityKeyMap_bdSecurityID bdSecurityID;
		}; static_assert(sizeof(InitPacket) == 16, "InitPacket struct is not 16");
		struct CookieAck
		{
			uint16_t m_localTag;
			uint16_t localTag;
		};
		struct InitAck
		{
			uint8_t header_high;
			uint8_t header_low;
			uint32_t m_initTag;
			uint32_t d_0;
			uint32_t d_1;
			CookieAck cookie;
			uint32_t m_peerTag;
			uint16_t _idk;
			uint32_t client_ip;
			uint16_t client_port;
			iw5mp_structs::bdSecurityKeyMap_bdSecurityID bdSecurityID;
		}; 
		static_assert(sizeof(InitAck) == 38, "InitAck struct is not 38");
		static_assert(offsetof(InitAck, cookie) == 14, "cookie offset is not 14");
		struct CookieAckPacket
		{
			uint8_t header_high;
			uint8_t header_low;
			CookieAck cookie;
			InitAck initack;
			playerNetData pND;
			iw5mp_structs::bdSecurityKeyMap_bdSecurityID bdSecurityID;
			uint8_t ECCkey_exportkey[100];
		};
		static_assert(sizeof(CookieAckPacket) == 177, "CookieAckPacket struct is not 177");
		static_assert(offsetof(CookieAckPacket, ECCkey_exportkey) == 77, "ECCkey_exportkey offset is not 77");
	};


#pragma pack(pop)
};
